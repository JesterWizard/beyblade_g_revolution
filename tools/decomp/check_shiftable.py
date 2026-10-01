#!/usr/bin/env python3
"""Phase 5 shiftable-ROM checks. Exits 0 when the layout is sequential.

Head may stay pinned at 0x08000000. Function and gap peels must not have
per-section 0x08…… assignments — the linker packs them in order. Thumb
function-entry words and `gData_*` table words in those peels must be
`.4byte`, pointer-table runs of ROM data pointers must be `.4byte` with
`gRom_*` / `_08*` target labels, and ROM `gData_*` symbols must be peel labels
(not `SET_DATA` pins).
"""

from __future__ import annotations

import json
import re
import sys
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from gen_rom_layout import (  # noqa: E402
    ASM_DIR,
    BASEROM,
    ROM_BASE,
    SIZE_CACHE,
    fn_ptr_sites,
    matched_coverage,
    merge_peel_labels,
    MIN_PTR_RUN,
    pointer_table_sites,
    reloc_sites,
    reloc_word_map,
    rom_data_symbols,
    thumb_fn_map,
    unmatched_sub_labels,
)

MANIFEST = ROOT / "build" / "matched.json"
LAYOUT = ROOT / "asm" / "rom_layout.ld"
TOTAL_FUNCTIONS = 633

# Output-section VMA: `.name 0x08XXXXXX :`
SECTION_VMA_RE = re.compile(
    r"^\s*(\.\S+)\s+(0x[0-9A-Fa-f]+)\s*:",
    re.M,
)
INCBIN_RE = re.compile(r'\.incbin "baserom\.gba", 0x([0-9A-Fa-f]+), 0x([0-9A-Fa-f]+)')
LABEL_RE = re.compile(r"^(gData_[0-9A-Fa-f]+):", re.M)
ALLOWED_HEAD = {(".rom_head", "0x08000000"), (".rom", "0x08000000")}


@lru_cache(maxsize=1)
def peel_incbin_ranges() -> tuple[tuple[int, int], ...]:
    ranges: list[tuple[int, int]] = []
    for path in peel_paths():
        for match in INCBIN_RE.finditer(path.read_text()):
            start = int(match.group(1), 16)
            length = int(match.group(2), 16)
            ranges.append((start, start + length))
    return tuple(ranges)


def peel_paths() -> list[Path]:
    paths = [ASM_DIR / "rom.s", ASM_DIR / "rom_tail.s", *sorted(ASM_DIR.glob("rom_gap_*.s"))]
    return [path for path in paths if path.is_file()]


def unmatched_fn_ptr_sites() -> list[tuple[int, str]]:
    """Thumb function-entry words that live in head/gap/tail peels."""
    if not BASEROM.is_file() or not SIZE_CACHE.is_file():
        return []
    rom = BASEROM.read_bytes()
    fns = json.loads(MANIFEST.read_text()).get("functions", [])
    cache = json.loads(SIZE_CACHE.read_text())
    covered = bytearray(len(rom))
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if not rec:
            continue
        off = int(fn["addr"], 16) - ROM_BASE
        covered[off : off + rec[1]] = b"\x01" * rec[1]
    sites = []
    for off, name in fn_ptr_sites(rom, 0, len(rom), thumb_fn_map(fns)):
        if not covered[off]:
            sites.append((off, name))
    return sites


def unmatched_table_ptr_sites() -> list[tuple[int, str]]:
    """Pointer-table words (runs of ROM pointers) that live in peels."""
    if not BASEROM.is_file() or not SIZE_CACHE.is_file() or not MANIFEST.is_file():
        return []
    rom = BASEROM.read_bytes()
    fns = json.loads(MANIFEST.read_text()).get("functions", [])
    cache = json.loads(SIZE_CACHE.read_text())
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if rec:
            fn["size"] = rec[1]
    covered = matched_coverage(fns, len(rom))
    labels = merge_peel_labels(fns)
    _anon, sites = pointer_table_sites(rom, covered, labels)
    return sorted(sites.items())


def unmatched_data_ptr_sites() -> list[tuple[int, str]]:
    """Words in peels that point at a ROM `gData_*` (or a Thumb fn entry)."""
    if not BASEROM.is_file() or not SIZE_CACHE.is_file() or not MANIFEST.is_file():
        return []
    rom = BASEROM.read_bytes()
    fns = json.loads(MANIFEST.read_text()).get("functions", [])
    cache = json.loads(SIZE_CACHE.read_text())
    covered = bytearray(len(rom))
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if not rec:
            continue
        off = int(fn["addr"], 16) - ROM_BASE
        covered[off : off + rec[1]] = b"\x01" * rec[1]
    mapping = reloc_word_map(fns, rom_data_symbols())
    sites = []
    for off, name in reloc_sites(rom, 0, len(rom), mapping):
        if not covered[off]:
            sites.append((off, name))
    return sites


def baked_ptr_sites(sites: list[tuple[int, str]]) -> list[tuple[int, str]]:
    """Sites still covered by a peel `.incbin` (not emitted as `.4byte`)."""
    ranges = peel_incbin_ranges()
    if not sites or not ranges:
        return []
    end = max(hi for _, hi in ranges)
    mask = bytearray(end)
    for start, hi in ranges:
        mask[start:hi] = b"\x01" * (hi - start)
    return [(off, name) for off, name in sites if off < end and mask[off]]


def missing_unmatched_sub_labels() -> list[str]:
    """Unmatched `sub_*` callees that never got a peel label."""
    if not MANIFEST.is_file() or not SIZE_CACHE.is_file():
        return []
    fns = json.loads(MANIFEST.read_text()).get("functions", [])
    cache = json.loads(SIZE_CACHE.read_text())
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if rec:
            fn["size"] = rec[1]
    wanted = [name for names in unmatched_sub_labels(fns).values() for name in names]
    if not wanted:
        return []
    named: set[str] = set()
    label_re = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*):", re.M)
    for path in peel_paths():
        named.update(label_re.findall(path.read_text()))
    return [name for name in wanted if name not in named]


def missing_data_labels() -> list[str]:
    """ROM `gData_*` that are not peel labels (still inside an incbin)."""
    labels = rom_data_symbols()
    if not labels:
        return []
    named = set()
    for path in peel_paths():
        named.update(LABEL_RE.findall(path.read_text()))
    ranges = peel_incbin_ranges()
    missing = []
    for off, name in sorted(labels.items()):
        interior = any(start < off < end for start, end in ranges)
        if name not in named or interior:
            missing.append(name)
    return missing


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

    sites = unmatched_fn_ptr_sites()
    baked = baked_ptr_sites(sites) if sites else []
    n_ok = len(sites) - len(baked)
    gates.append(
        (
            not baked,
            f"Thumb fn-entry pointers in peels are .4byte ({n_ok}/{len(sites)})"
            + (f"; baked: 0x{baked[0][0]:X} {baked[0][1]}" if baked else ""),
        )
    )

    data_sites = unmatched_data_ptr_sites()
    baked_data = baked_ptr_sites(data_sites) if data_sites else []
    n_data_ok = len(data_sites) - len(baked_data)
    gates.append(
        (
            not baked_data,
            f"gData_* / fn-entry pointer words are .4byte ({n_data_ok}/{len(data_sites)})"
            + (
                f"; baked: 0x{baked_data[0][0]:X} {baked_data[0][1]}"
                if baked_data
                else ""
            ),
        )
    )
    missing = missing_data_labels()
    n_lab = len(rom_data_symbols())
    gates.append(
        (
            not missing,
            f"ROM gData_* are peel labels ({n_lab - len(missing)}/{n_lab})"
            + (f"; missing {missing[0]}" if missing else ""),
        )
    )
    missing_subs = missing_unmatched_sub_labels()
    n_subs = 0
    if MANIFEST.is_file() and SIZE_CACHE.is_file():
        fns = json.loads(MANIFEST.read_text()).get("functions", [])
        cache = json.loads(SIZE_CACHE.read_text())
        for fn in fns:
            rec = cache.get(f"{fn['name']}.s")
            if rec:
                fn["size"] = rec[1]
        n_subs = sum(len(v) for v in unmatched_sub_labels(fns).values())
    gates.append(
        (
            not missing_subs,
            f"unmatched sub_* callees are peel labels ({n_subs - len(missing_subs)}/{n_subs})"
            + (f"; missing {missing_subs[0]}" if missing_subs else ""),
        )
    )
    table_sites = unmatched_table_ptr_sites()
    baked_table = baked_ptr_sites(table_sites) if table_sites else []
    n_table_ok = len(table_sites) - len(baked_table)
    gates.append(
        (
            not baked_table,
            f"data-pointer tables (runs>={MIN_PTR_RUN}) are .4byte "
            f"({n_table_ok}/{len(table_sites)})"
            + (
                f"; baked: 0x{baked_table[0][0]:X} {baked_table[0][1]}"
                if baked_table
                else ""
            ),
        )
    )

    print("=== Shiftable ROM preflight ===")
    ok_all = True
    for ok, msg in gates:
        mark = "OK" if ok else "NO"
        print(f"  [{mark}] {msg}")
        ok_all = ok_all and ok

    if ok_all:
        print(
            "Layout is sequential; function-entry, gData_*, veneer, and data-pointer "
            "table labels in peels relocate. Matched C .text keeps live BL / ABS32 "
            "relocs. Singleton/pair data-to-data 0x08…… words are still absolute."
        )
        return 0

    print("Not sequential yet — see docs/decomp-roadmap.md Phase 5.")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
