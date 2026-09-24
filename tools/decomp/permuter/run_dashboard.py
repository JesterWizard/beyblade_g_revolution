#!/usr/bin/env python3
"""Run decomp-permuter with a live web dashboard.

Usage:
  python3 tools/decomp/permuter/run_dashboard.py sub_08073988
  python3 tools/decomp/permuter/run_dashboard.py sub_08073988 --seconds 600 --jobs 8
  python3 tools/decomp/permuter/run_dashboard.py --serve-only

Opens http://127.0.0.1:8765/ in your browser and streams permuter progress:
iterations, scores, top candidates, ETA, and a log of what was tried.
"""

from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from tools.decomp.permuter.dashboard.runner import (  # noqa: E402
    STATE_PATH,
    finalize_dashboard_state,
    run_round_with_dashboard,
    start_dashboard_server,
)
from tools.decomp.permuter.dashboard.state import PermuterState  # noqa: E402

PERM = ROOT / "tools" / "decomp-permuter"
WORKROOT = ROOT / "nonmatchings"
IMPORT = ROOT / "tools" / "decomp" / "permuter" / "import_function.py"


def ensure_import(name: str, *, force: bool) -> int:
    workdir = WORKROOT / name
    if workdir.is_dir() and not force:
        return 0
    result = subprocess.run(
        [sys.executable, str(IMPORT), name],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
    )
    for line in (result.stdout or "").splitlines():
        if line.startswith(
            ("imported ", "match-flags:", "match-compiler:", "removed stale")
        ):
            print(line)
    if result.returncode != 0:
        sys.stderr.write(result.stdout or "")
        sys.stderr.write(result.stderr or "")
        return result.returncode
    return 0


def permuter_cmd(workdir: Path, *, jobs: int, strict_branches: bool) -> list[str]:
    cmd = [
        sys.executable,
        str(PERM / "permuter.py"),
        str(workdir),
        "-j",
        str(jobs),
        "--stop-on-zero",
        "--no-context-output",
    ]
    if strict_branches:
        cmd.append("--no-ignore-branch-targets")
    return cmd


def serve_only(host: str, port: int, open_browser: bool) -> int:
    state = PermuterState()
    if STATE_PATH.is_file():
        data = json.loads(STATE_PATH.read_text())
        for key, value in data.items():
            if hasattr(state, key) and not key.startswith("_"):
                setattr(state, key, value)

    from tools.decomp.permuter.dashboard.server import DashboardServer, pick_port

    port = pick_port(host, port)
    server = DashboardServer(
        state_path=STATE_PATH,
        get_state=state.snapshot,
        host=host,
        port=port,
    )
    server.start(open_browser=open_browser)
    print(f"Dashboard: {server.url}")
    print(f"State file: {STATE_PATH.relative_to(ROOT)}")
    print("Press Ctrl+C to stop.")
    try:
        while True:
            if STATE_PATH.is_file():
                data = json.loads(STATE_PATH.read_text())
                for key, value in data.items():
                    if hasattr(state, key) and not key.startswith("_"):
                        setattr(state, key, value)
            time.sleep(1)
    except KeyboardInterrupt:
        server.stop()
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function", nargs="?", help="sub_080XXXXXX")
    parser.add_argument("--seconds", type=int, default=180)
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    parser.add_argument("--reuse", action="store_true")
    parser.add_argument("--strict-branches", action="store_true")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8765)
    parser.add_argument("--no-browser", action="store_true")
    parser.add_argument(
        "--serve-only",
        action="store_true",
        help="only serve the dashboard (read build/permuter-dashboard/state.json)",
    )
    args = parser.parse_args()

    if args.serve_only:
        return serve_only(args.host, args.port, open_browser=not args.no_browser)

    if not args.function:
        parser.error("function is required unless --serve-only")
    if not PERM.is_dir():
        print("run tools/decomp/permuter/setup.sh first", file=sys.stderr)
        return 2

    name = args.function
    rc = ensure_import(name, force=not args.reuse)
    if rc != 0:
        return rc
    workdir = WORKROOT / name
    if not workdir.is_dir():
        print(f"missing workdir {workdir}", file=sys.stderr)
        return 2

    server, state = start_dashboard_server(
        function=name,
        workdir=workdir,
        budget_sec=args.seconds,
        jobs=args.jobs,
        host=args.host,
        port=args.port,
        open_browser=not args.no_browser,
    )

    round_result = run_round_with_dashboard(
        workdir=workdir,
        cmd=permuter_cmd(workdir, jobs=args.jobs, strict_branches=args.strict_branches),
        seconds=args.seconds,
        jobs=args.jobs,
        round_no=1,
        state=state,
    )

    finalize_dashboard_state(
        state,
        interrupted=round_result.interrupted,
        timed_out=round_result.timed_out,
    )
    server.stop()
    if round_result.interrupted:
        return 130
    best = state.best_score
    return 0 if best == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
