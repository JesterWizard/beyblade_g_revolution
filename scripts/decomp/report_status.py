#!/usr/bin/env python3
"""Print a human-readable decompilation progress summary."""

from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NON = ROOT / "asm" / "nonmatchings"
MATCH = ROOT / "asm" / "matchings"
SRC = ROOT / "src"
STATUS = ROOT / "documentation" / "decomp-status.md"


def count_s(dirpath: Path) -> int:
    return len(list(dirpath.glob("*.s"))) if dirpath.is_dir() else 0


def main() -> None:
    non = count_s(NON)
    matched_asm = count_s(MATCH)
    src_c = len(list(SRC.glob("*.c"))) if SRC.is_dir() else 0

    summary = {
        "nonmatching_asm": non,
        "matching_asm": matched_asm,
        "src_c_files": src_c,
        "total_tracked": non + matched_asm,
        "pct_asm_matched": round(100 * matched_asm / (non + matched_asm), 1)
        if (non + matched_asm)
        else 0.0,
    }

    print("=== Beyblade G Revolution decomp status ===")
    for k, v in summary.items():
        print(f"  {k}: {v}")
    if STATUS.is_file():
        print()
        print(STATUS.read_text())


if __name__ == "__main__":
    main()
