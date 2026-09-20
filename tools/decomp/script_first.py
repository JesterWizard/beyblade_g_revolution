#!/usr/bin/env python3
"""Script-first Phase 3b batch: patterns + cleaned m2c, integrate on MATCH.

No agent required. Run this at the start of every session before writing C.

  python3 tools/decomp/script_first.py
  python3 tools/decomp/script_first.py 40 --park-near-miss
  python3 tools/decomp/script_first.py --cluster-only
"""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WIP = ROOT / "src" / "wip"
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from classify_semantic_targets import classify  # noqa: E402
from cluster_shapes import cluster, format_human  # noqa: E402
from match_function import try_compile_and_score, write_single_function_c  # noqa: E402
from next_queue import collect  # noqa: E402
from try_convert import asm_lines, candidates, integrate  # noqa: E402
from unblock_symbols import format_human as format_unblock  # noqa: E402
from unblock_symbols import guess_prototypes  # noqa: E402


def _blocked() -> set[str]:
    data = collect()
    return {r["name"] for r in data.get("blocked") or [] if r.get("name")}


def _targets() -> list[str]:
    buckets, _missing, _cse = classify()
    blocked = _blocked()
    skip = set(buckets.get("naked_only") or []) | blocked
    ordered: list[str] = []
    seen: set[str] = set()
    for key in ("small_clean", "unblock_first", "large", "high_reg_pressure"):
        for name in buckets.get(key) or []:
            if name in skip or name in seen:
                continue
            seen.add(name)
            ordered.append(name)
    return ordered


def _near_miss(info: dict) -> bool:
    if info.get("status") not in ("same_size", "identical_diff"):
        return False
    return float(info.get("pct") or 0) >= 80.0


def _park(name: str, body: str, info: dict) -> None:
    dest = WIP / f"{name}.c"
    if dest.is_file():
        return
    dest.parent.mkdir(parents=True, exist_ok=True)
    write_single_function_c(name, body, dest)
    subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/decomp/park_wip.py"),
            name,
            str(dest),
            "--status",
            f"script_first near-miss {info.get('status')} {info.get('score')}",
            "--next",
            "permuter or one register-pin pass from this seed",
            "--score",
            str(info.get("score", "")),
        ],
        cwd=str(ROOT),
        check=False,
    )


def convert_one(name: str, park_near: bool) -> str:
    """Return 'match' | 'fail' | 'parked' | 'skip'."""
    asm = asm_lines(name)
    if asm is None:
        return "skip"
    best_body: str | None = None
    best_info: dict | None = None
    for src, note, body in candidates(name, asm):
        with tempfile.TemporaryDirectory() as tmp:
            scratch = Path(tmp) / "scratch.c"
            write_single_function_c(name, body, scratch)
            scored = try_compile_and_score(name, scratch)
            if scored is None:
                continue
            got, want, info = scored
        if got == want:
            tag = f"script_first/{src}"
            if integrate(name, body, tag):
                print(f"MATCH {name} ({note})", flush=True)
                return "match"
            print(f"MATCH-but-integrate-failed {name}", flush=True)
            return "fail"
        if best_info is None or info["pct"] > best_info["pct"]:
            best_info = info
            best_body = body
    if park_near and best_body and best_info and _near_miss(best_info):
        _park(name, best_body, best_info)
        print(f"PARK  {name} ({best_info.get('score')} {best_info.get('status')})", flush=True)
        return "parked"
    return "fail"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("limit", nargs="?", type=int, default=30)
    parser.add_argument("--park-near-miss", action="store_true")
    parser.add_argument("--cluster-only", action="store_true")
    parser.add_argument("--skip-unblock", action="store_true")
    parser.add_argument("--write-prototypes", action="store_true")
    args = parser.parse_args()

    if not args.skip_unblock:
        rows = guess_prototypes()
        print(format_unblock(rows), end="")
        if args.write_prototypes and rows:
            from unblock_symbols import write_header  # noqa: WPS433

            n = write_header(rows)
            print(f"wrote {n} prototype(s)")

    if args.cluster_only:
        print(format_human(cluster(), 20), end="")
        return 0

    names = _targets()[: args.limit]
    print(f"==> script_first: trying {len(names)} remaining functions")
    matched = parked = failed = 0
    for name in names:
        result = convert_one(name, args.park_near_miss)
        if result == "match":
            matched += 1
        elif result == "parked":
            parked += 1
        elif result == "fail":
            failed += 1

    print(
        f"==> script_first: {matched} MATCH, {parked} parked, {failed} still Thumb "
        f"(attempted {len(names)})"
    )

    if matched:
        subprocess.run(["make", "compare"], cwd=str(ROOT), check=True)
        subprocess.run(
            [sys.executable, str(ROOT / "tools/decomp/progress.py"), "--write"],
            cwd=str(ROOT),
            check=False,
            stdout=subprocess.DEVNULL,
        )
        subprocess.run(
            [sys.executable, str(ROOT / "tools/decomp/next_queue.py"), "--write"],
            cwd=str(ROOT),
            check=False,
            stdout=subprocess.DEVNULL,
        )

    families = cluster()
    print()
    print(format_human(families, 8), end="")
    print()
    print("Next (agent): python3 tools/decomp/agent_packet.py --next")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
