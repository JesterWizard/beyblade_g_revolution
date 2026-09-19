#!/usr/bin/env python3
"""Rank functions for C conversion by estimated difficulty (smaller = easier).

Phase 3b: triage functions still peeled as readable Thumb (naked asm wrapper
in src/matched/*.c) — these are the real remaining-work pool. Every function
in build/matched.json has a ``src`` entry once peeled (readable-Thumb stubs
count too), so that field alone can't tell "done" from "still asm"; the
opcode_stubs helpers (naked/asm-body sniffing) can.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM_DIR = ROOT / "asm" / "nonmatchings"
MANIFEST = ROOT / "build" / "matched.json"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import list_readable_asm, list_opcode_stubs  # noqa: E402

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
        print(f"error: {ASM_DIR} missing — run build_tools.sh", file=sys.stderr)
        return 1

    # Candidate pool = still readable-Thumb or opcode-stub (not yet semantic C).
    pending = set(list_readable_asm()) | set(list_opcode_stubs())
    files = [p for p in ASM_DIR.glob("*.s") if p.stem in pending]
    if not files:
        print(f"error: no functions left to convert in {ASM_DIR}", file=sys.stderr)
        return 1

    ranked = sorted(score_file(p) for p in files)
    pick = ranked[: args.n]

    if args.json:
        print(json.dumps([name for _, name in pick]))
    else:
        for score, name in pick:
            print(f"{score:5d}  {name}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
