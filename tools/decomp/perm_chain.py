#!/usr/bin/env python3
"""Background permuter chain for near-miss parked seeds only.

Selection: every unmatched `src/decompiled/sub_*.c` whose recorded score is a
*same-size* DIFF at >= MIN_PCT, sorted best-first.  The permuter only reliably
closes small deltas, so low-similarity seeds are left to hand work.

usage: perm_chain.py [seconds] [jobs] [min_pct]
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from opcode_stubs import file_kind  # noqa: E402

SECONDS = sys.argv[1] if len(sys.argv) > 1 else "300"
JOBS = sys.argv[2] if len(sys.argv) > 2 else "8"
MIN_PCT = float(sys.argv[3]) if len(sys.argv) > 3 else 75.0


def candidates() -> list[tuple[float, str]]:
    raw = subprocess.run(
        [sys.executable, "tools/decomp/function_scores.py", "--json"],
        capture_output=True, text=True,
    ).stdout
    data = json.loads(raw)
    out = []
    for f in data["functions"]:
        if f["status"] == "matched":
            continue
        seed = Path(f"src/decompiled/{f['name']}.c")
        matched = Path(f"src/matched/{f['name']}.c")
        if not seed.exists():
            continue
        if matched.exists() and file_kind(matched) == "semantic":
            continue
        if f["pct"] >= MIN_PCT:
            out.append((f["pct"], f["name"]))
    out.sort(reverse=True)
    return out


def main() -> int:
    for pct, fn in candidates():
        print(f"=== {fn} ({pct}%)", flush=True)
        subprocess.run(
            [sys.executable, "tools/decomp/permuter/auto.py", fn,
             "--seconds", SECONDS, "--jobs", JOBS],
            check=False,
        )
    print("CHAIN_DONE", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
