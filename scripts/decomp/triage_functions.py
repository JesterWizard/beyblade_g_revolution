#!/usr/bin/env python3
"""Rank non-matching asm functions by estimated difficulty (smaller = easier)."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM_DIR = ROOT / "asm" / "nonmatchings"

LABEL_RE = re.compile(r"^([A-Za-z0-9_]+):\s*$")


def score_file(path: Path) -> tuple[int, str]:
    if not path.name.startswith("sub_"):
        return (10**9, path.stem)
    lines = path.read_text().splitlines()
    insns = sum(
        1
        for ln in lines
        if ln.strip()
        and not ln.strip().startswith(".")
        and not ln.strip().startswith("@")
        and not ln.strip().startswith(".byte")
        and ":" not in ln
    )
    if insns == 0:
        return (10**9, path.stem)
    bl_count = sum(1 for ln in lines if " bl " in f" {ln} " or ln.strip().startswith("bl "))
    name = path.stem
    # Lower score = easier
    return (insns + bl_count * 3, name)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", type=int, default=10, help="How many to list")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    if not ASM_DIR.is_dir():
        print(f"error: {ASM_DIR} missing — run scripts/setup.sh", file=sys.stderr)
        return 1

    files = list(ASM_DIR.glob("*.s"))
    if not files:
        print(f"error: no .s files in {ASM_DIR}", file=sys.stderr)
        return 1

    ranked = sorted(score_file(p) for p in files)
    pick = ranked[: args.n]

    if args.json:
        import json

        print(json.dumps([name for _, name in pick]))
    else:
        for score, name in pick:
            print(f"{score:5d}  {name}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
