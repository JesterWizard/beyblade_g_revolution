#!/usr/bin/env python3
"""Phase 5 shiftable-ROM checks. Exits 0 when the layout is sequential.

Head may stay pinned at 0x08000000. Function and gap peels must not have
per-section 0x08…… assignments — the linker packs them in order.
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "build" / "matched.json"
LAYOUT = ROOT / "asm" / "rom_layout.ld"
TOTAL_FUNCTIONS = 633

# Output-section VMA: `.name 0x08XXXXXX :`
SECTION_VMA_RE = re.compile(
    r"^\s*(\.\S+)\s+(0x[0-9A-Fa-f]+)\s*:",
    re.M,
)
ALLOWED_HEAD = {(".rom_head", "0x08000000"), (".rom", "0x08000000")}


def main() -> int:
    if not MANIFEST.is_file():
        print("check_shiftable: no build/matched.json", file=sys.stderr)
        return 1

    linked = len(json.loads(MANIFEST.read_text()).get("functions", []))
    pct = 100.0 * linked / TOTAL_FUNCTIONS

    gates = []
    gates.append((pct >= 80.0, f"matched >= 80% ({linked}/{TOTAL_FUNCTIONS}, {pct:.1f}%)"))

    if LAYOUT.is_file():
        text = LAYOUT.read_text()
        extra = [
            f"{name} {addr}"
            for name, addr in SECTION_VMA_RE.findall(text)
            if (name, addr) not in ALLOWED_HEAD
        ]
        gates.append(
            (
                not extra,
                "no per-function/gap VMAs in rom_layout.ld"
                + (f" (found {len(extra)}: {extra[0]}…)" if extra else ""),
            )
        )
        sequential = ".rom_body" in text and "SUBALIGN(2)" in text
        gates.append((sequential, "sequential .rom_body SUBALIGN(2)"))
    else:
        gates.append((False, "rom_layout.ld missing"))

    print("=== Shiftable ROM preflight ===")
    ok_all = True
    for ok, msg in gates:
        mark = "OK" if ok else "NO"
        print(f"  [{mark}] {msg}")
        ok_all = ok_all and ok

    if ok_all:
        print(
            "Layout is sequential. Pointer tables in unextracted data still "
            "use absolute 0x08…… — growing a function will desync those."
        )
        return 0

    print("Not sequential yet — see docs/decomp-roadmap.md Phase 5.")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
