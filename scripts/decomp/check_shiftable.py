#!/usr/bin/env python3
"""Preflight checks for Phase 5 (shiftable ROM). Exits 0 when migration is allowed."""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "build" / "matched.json"
LAYOUT = ROOT / "asm" / "rom_layout.ld"
TOTAL_FUNCTIONS = 633

FIXED_VMA_RE = re.compile(r"\.rom_(?:sub_|gap_|head|tail)")


def main() -> int:
    if not MANIFEST.is_file():
        print("check_shiftable: no build/matched.json", file=sys.stderr)
        return 1

    linked = len(json.loads(MANIFEST.read_text()).get("functions", []))
    pct = 100.0 * linked / TOTAL_FUNCTIONS

    gates = []
    gates.append((pct >= 80.0, f"matched >= 80% ({linked}/{TOTAL_FUNCTIONS}, {pct:.1f}%)"))

    if LAYOUT.is_file():
        fixed_sections = len(FIXED_VMA_RE.findall(LAYOUT.read_text()))
        gates.append((fixed_sections == 0, f"no fixed-VMA sections in rom_layout.ld (found {fixed_sections})"))
    else:
        gates.append((False, "rom_layout.ld missing"))

    print("=== Shiftable ROM preflight ===")
    ok_all = True
    for ok, msg in gates:
        mark = "OK" if ok else "NO"
        print(f"  [{mark}] {msg}")
        ok_all = ok_all and ok

    if ok_all:
        print("Shiftable migration may proceed.")
        return 0

    print("Not shiftable yet — continue Phase 1–4 (see documentation/decomp-roadmap.md).")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
