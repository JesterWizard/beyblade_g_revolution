#!/usr/bin/env python3
"""Replace battle opcode .byte stubs with readable Thumb that still MATCH."""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts" / "decomp"))

from battle_scan import score  # noqa: E402
from opcode_stubs import is_opcode_stub  # noqa: E402
from readable_asm import guess_readable_asm  # noqa: E402

INTEGRATE = ROOT / "scripts" / "decomp" / "integrate_c.py"
MATCHED = ROOT / "src" / "matched"
NON = ROOT / "asm" / "nonmatchings"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("limit", type=int, nargs="?", default=40)
    parser.add_argument("--all", action="store_true", help="all opcode stubs, not just battle")
    args = parser.parse_args()

    names: list[str] = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        if not is_opcode_stub(path):
            continue
        asm = NON / f"{path.stem}.s"
        if not asm.is_file():
            continue
        if not args.all:
            n, _, _ = score(asm)
            if not n:
                continue
        names.append(path.stem)

    converted = 0
    failed = 0
    for name in names:
        if converted >= args.limit:
            break
        cand = guess_readable_asm(name)
        if not cand:
            failed += 1
            continue
        result = subprocess.run(
            [
                sys.executable,
                str(INTEGRATE),
                name,
                cand.body,
                "--note",
                "battle/readable-thumb",
                "--kind",
                "asm",
                "--skip-compare",
            ],
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            failed += 1
            err = (result.stdout + result.stderr).strip().splitlines()
            print(f"fail {name}: {err[-1] if err else 'verify failed'}", file=sys.stderr)
            continue
        converted += 1
        print(f"converted {name}", file=sys.stderr)

    print(f"==> readable asm batch: {converted} converted, {failed} failed", file=sys.stderr)
    print(converted, flush=True)
    if converted > 0:
        subprocess.run(["make", "compare"], cwd=str(ROOT), check=True)
    subprocess.run(
        [sys.executable, str(ROOT / "scripts" / "decomp" / "progress.py"), "--write"],
        cwd=str(ROOT),
        check=False,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
