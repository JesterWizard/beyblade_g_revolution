#!/usr/bin/env python3
"""Rebuild with 0x1000 inserted after `.rom_head` and check live relocs follow.

Does not replace `beyblade_g_revolution.gba`. High-confidence peel `.4byte`
sites and matched-C ABS32 pools must slide; unlabeled baked singletons are
counted but do not fail the run.
"""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from gen_rom_layout import (  # noqa: E402
    BASEROM,
    MANIFEST,
    ROM_BASE,
    ROM_SIZE,
    SIZE_CACHE,
    is_counting_bytes,
    matched_coverage,
    merge_peel_labels,
    pointer_table_sites,
    reloc_sites,
    reloc_word_map,
    rom_data_symbols,
)

SHIFT = 0x1000
RETAIL_GBA = ROOT / "beyblade_g_revolution.gba"
SHIFT_ELF = ROOT / "build" / "shift_test.elf"
SHIFT_ROM = ROOT / "build" / "shift_test.gba"
SHIFT_MAP = ROOT / "build" / "shift_test.map"


def expected_word(word: int, first_off: int, shift: int) -> int:
    tgt = (word - ROM_BASE) & ~1
    if not (0 <= tgt < ROM_SIZE):
        return word
    if tgt >= first_off:
        return word + shift
    return word


def high_confidence_sites(rom: bytes, fns: list[dict]) -> dict[int, str]:
    covered = matched_coverage(fns, len(rom))
    labels = merge_peel_labels(fns)
    _anon, table_sites = pointer_table_sites(rom, covered, labels)
    mapping = reloc_word_map(fns, rom_data_symbols())
    sites = dict(table_sites)
    for off, name in reloc_sites(rom, 0, len(rom), mapping):
        if not covered[off]:
            sites.setdefault(off, name)
    return sites


def check_head(
    retail: bytes, shifted: bytes, first_off: int, sites: dict[int, str]
) -> str | None:
    """Head payload stays put; live `.4byte` words that point past the pad may change."""
    skip = bytearray(first_off)
    for off in sites:
        if 0 <= off < first_off:
            end = min(off + 4, first_off)
            skip[off:end] = b"\x01" * (end - off)
    n = min(first_off, len(retail), len(shifted))
    if len(shifted) < first_off:
        return "head length mismatch"
    for i in range(n):
        if skip[i]:
            continue
        if retail[i] != shifted[i]:
            return f"head mismatch at 0x{i:06X}: retail {retail[i]:02X} shifted {shifted[i]:02X}"
    return None


def check_site(
    retail: bytes, shifted: bytes, off: int, first_off: int
) -> str | None:
    word = int.from_bytes(retail[off : off + 4], "little")
    want = expected_word(word, first_off, SHIFT)
    shifted_off = off if off < first_off else off + SHIFT
    if shifted_off + 4 > len(shifted):
        return f"0x{off:06X}: shifted ROM too short"
    got = int.from_bytes(shifted[shifted_off : shifted_off + 4], "little")
    if got != want:
        return (
            f"0x{off:06X}: want 0x{want:08X} got 0x{got:08X} "
            f"(retail 0x{word:08X})"
        )
    return None


def check_function(
    retail: bytes, shifted: bytes, off: int, size: int, first_off: int, name: str
) -> str | None:
    a = retail[off : off + size]
    b = shifted[off + SHIFT : off + SHIFT + size]
    if len(b) != size:
        return f"{name}: shifted .text truncated"
    if a == b:
        return None
    seen: set[int] = set()
    for i, (x, y) in enumerate(zip(a, b)):
        if x == y:
            continue
        word_off = (off + i) & ~3
        rel = word_off - off
        if rel < 0 or rel + 4 > size or word_off in seen:
            continue
        seen.add(word_off)
        word = int.from_bytes(a[rel : rel + 4], "little")
        got = int.from_bytes(b[rel : rel + 4], "little")
        want = expected_word(word, first_off, SHIFT)
        if got == want:
            continue
        return (
            f"{name} +0x{rel:X}: want 0x{want:08X} got 0x{got:08X} "
            f"(retail 0x{word:08X})"
        )
    for i, (x, y) in enumerate(zip(a, b)):
        word_off = (off + i) & ~3
        if x != y and word_off not in seen:
            return f"{name} +0x{i:X}: non-word mismatch {x:02X} vs {y:02X}"
    return None


def count_baked_leftovers(retail: bytes, covered: bytearray, sites: dict[int, str]) -> int:
    n = 0
    off = 0
    end = min(len(retail), len(covered))
    while off + 4 <= end:
        if not covered[off] and off not in sites:
            word = int.from_bytes(retail[off : off + 4], "little")
            if ROM_BASE <= word < ROM_BASE + ROM_SIZE and not is_counting_bytes(
                retail, off
            ):
                n += 1
        off += 4
    return n


def build_shifted() -> None:
    SHIFT_ELF.parent.mkdir(parents=True, exist_ok=True)
    for path in (SHIFT_ELF, SHIFT_ROM, SHIFT_MAP):
        path.unlink(missing_ok=True)
    subprocess.run(
        [
            "make",
            f"ELF={SHIFT_ELF.relative_to(ROOT)}",
            f"ROM={SHIFT_ROM.relative_to(ROOT)}",
            f"MAP={SHIFT_MAP.relative_to(ROOT)}",
            f"SHIFT_BYTES={SHIFT:#x}",
            "COMPARE=0",
            "rom",
        ],
        cwd=ROOT,
        check=True,
    )


def main() -> int:
    if not BASEROM.is_file():
        print("test_shift: missing baserom.gba", file=sys.stderr)
        return 1
    if not MANIFEST.is_file() or not SIZE_CACHE.is_file():
        print("test_shift: missing build/matched.json or size cache", file=sys.stderr)
        return 1

    if not RETAIL_GBA.is_file():
        subprocess.run(["make", "rom"], cwd=ROOT, check=True)

    fns = sorted(
        json.loads(MANIFEST.read_text()).get("functions", []),
        key=lambda f: int(f["addr"], 16),
    )
    cache = json.loads(SIZE_CACHE.read_text())
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if rec:
            fn["size"] = rec[1]
    if not fns:
        print("test_shift: no matched functions", file=sys.stderr)
        return 1

    first_off = int(fns[0]["addr"], 16) - ROM_BASE
    retail = RETAIL_GBA.read_bytes()
    print(f"test_shift: linking with __rom_shift_bytes={SHIFT:#x}")
    build_shifted()
    shifted = SHIFT_ROM.read_bytes()

    print("=== Slide rebuild ===")
    want_size = len(retail) + SHIFT
    gates: list[tuple[bool, str]] = []
    gates.append(
        (
            len(shifted) == want_size,
            f"shifted ROM is retail+{SHIFT:#x} ({len(shifted)}/{want_size})",
        )
    )
    sites = high_confidence_sites(retail, fns)
    head_err = check_head(retail, shifted, first_off, sites)
    gates.append(
        (
            head_err is None,
            "head bytes unchanged (except live peel relocs)"
            + (f"; {head_err}" if head_err else ""),
        )
    )
    site_fail: str | None = None
    n_ok = 0
    for off in sorted(sites):
        err = check_site(retail, shifted, off, first_off)
        if err:
            site_fail = err
            break
        n_ok += 1
    gates.append(
        (
            site_fail is None,
            f"high-confidence peel pointers slide ({n_ok}/{len(sites)})"
            + (f"; {site_fail}" if site_fail else ""),
        )
    )

    fn_fail: str | None = None
    n_fn = 0
    for fn in fns:
        off = int(fn["addr"], 16) - ROM_BASE
        err = check_function(retail, shifted, off, fn["size"], first_off, fn["name"])
        if err:
            fn_fail = err
            break
        n_fn += 1
    gates.append(
        (
            fn_fail is None,
            f"matched C .text ABS32 pools slide ({n_fn}/{len(fns)})"
            + (f"; {fn_fail}" if fn_fail else ""),
        )
    )

    covered = matched_coverage(fns, len(retail))
    n_baked = count_baked_leftovers(retail, covered, sites)

    ok_all = True
    for ok, msg in gates:
        print(f"  [{'OK' if ok else 'NO'}] {msg}")
        ok_all = ok_all and ok
    print(
        f"  leftover dense/unaligned singleton 0x08…… words (not required to slide): {n_baked}"
    )

    if ok_all:
        print(
            f"Live relocs follow a {SHIFT:#x} insert after .rom_head. "
            "Retail `make compare` image is unchanged."
        )
        return 0
    print("Shift test failed — a live reloc did not follow the pad.")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
