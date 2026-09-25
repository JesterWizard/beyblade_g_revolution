"""Shared permuter + dashboard runner for auto.py and dashboard.py."""

from __future__ import annotations

import os
import select
import signal
import subprocess
import sys
import threading
import time
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from tools.decomp.permuter.dashboard.server import DashboardServer, pick_port  # noqa: E402
from tools.decomp.permuter.dashboard.state import PermuterState, retail_byte_count  # noqa: E402

STATE_PATH = ROOT / "build" / "permuter-dashboard" / "state.json"


@dataclass
class RoundResult:
    interrupted: bool = False
    timed_out: bool = False


def start_dashboard_server(
    *,
    function: str,
    workdir: Path,
    budget_sec: int,
    jobs: int,
    host: str = "127.0.0.1",
    port: int = 8765,
    open_browser: bool = True,
) -> tuple[DashboardServer, PermuterState]:
    state = PermuterState()
    state.begin(
        function=function,
        workdir=workdir,
        budget_sec=budget_sec,
        jobs=jobs,
        retail_bytes=retail_byte_count(function),
    )
    state.set_phase("loading")
    state.write_json(STATE_PATH)

    port = pick_port(host, port)
    server = DashboardServer(
        state_path=STATE_PATH,
        get_state=state.snapshot,
        host=host,
        port=port,
    )
    server.start(open_browser=open_browser)
    print(f"Dashboard: {server.url}")
    return server, state


def best_score_from_state(state: PermuterState) -> int:
    best = state.base_score if state.base_score else state.best_score
    if state.top_candidates:
        best = min(best, min(c.score for c in state.top_candidates))
    elif state.best_score and (state.iteration or state.recent_attempts):
        best = min(best, state.best_score)
    return best


def finalize_dashboard_state(
    state: PermuterState,
    *,
    interrupted: bool = False,
    timed_out: bool = False,
) -> int:
    """Write final dashboard state. Returns the best score seen."""
    best = best_score_from_state(state)
    matched = best == 0 and (state.iteration > 0 or state.top_candidates)
    if interrupted:
        state.finalize(reason="interrupted", best_score=best)
    elif timed_out:
        state.finalize(reason="timeout", best_score=best)
    else:
        state.finalize(reason="done", matched=matched, best_score=best)
    state.write_json(STATE_PATH)
    return best


def run_round_with_dashboard(
    *,
    workdir: Path,
    cmd: list[str],
    seconds: int,
    jobs: int,
    round_no: int,
    state: PermuterState | None = None,
) -> RoundResult:
    """Run one permuter.py round, streaming stdout into dashboard state."""
    if state is None:
        state = PermuterState()
        if STATE_PATH.is_file():
            import json

            data = json.loads(STATE_PATH.read_text())
            for key, value in data.items():
                if hasattr(state, key) and not key.startswith("_"):
                    setattr(state, key, value)

    state.budget_sec = seconds
    state.jobs = jobs
    state.round_no = round_no
    state.set_phase("running")
    state.write_json(STATE_PATH)

    proc = subprocess.Popen(
        cmd,
        cwd=str(ROOT),
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
        start_new_session=True,
    )
    assert proc.stdout is not None

    deadline = time.time() + seconds
    stop = threading.Event()
    result = RoundResult()

    def poll_outputs() -> None:
        while not stop.is_set():
            state.poll_workdir(workdir)
            state.write_json(STATE_PATH)
            time.sleep(1.0)

    poller = threading.Thread(target=poll_outputs, daemon=True)
    poller.start()

    prev_handlers: dict = {}

    def on_stop(signum=None, _frame=None) -> None:
        result.interrupted = True
        stop.set()
        from tools.decomp.permuter.auto import kill_permuter_tree

        kill_permuter_tree(workdir, proc)

    for sig in (signal.SIGTERM, signal.SIGINT, signal.SIGHUP):
        prev_handlers[sig] = signal.getsignal(sig)
        signal.signal(sig, on_stop)

    try:
        while True:
            if result.interrupted:
                break
            if time.time() >= deadline:
                result.timed_out = True
                print(f"budget of {seconds}s reached")
                from tools.decomp.permuter.auto import kill_permuter_tree

                kill_permuter_tree(workdir, proc)
                break
            ready, _, _ = select.select([proc.stdout], [], [], 0.2)
            if ready:
                line = proc.stdout.readline()
                if not line:
                    break
                print(line, end="", flush=True)
                state.ingest_line(line, workdir=workdir)
                state.write_json(STATE_PATH)
            elif proc.poll() is not None:
                for line in proc.stdout:
                    print(line, end="", flush=True)
                    state.ingest_line(line, workdir=workdir)
                break
        proc.wait(timeout=15)
    except subprocess.TimeoutExpired:
        proc.kill()
    finally:
        stop.set()
        poller.join(timeout=2)
        for sig, handler in prev_handlers.items():
            signal.signal(sig, handler)

    state.poll_workdir(workdir)
    state.write_json(STATE_PATH)
    return result
