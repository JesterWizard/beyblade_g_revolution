#!/usr/bin/env python3
"""Generate ROM peel asm + linker fragment from build/matched.json.

Matched functions are compiled from src/matched/*.c (see compile_matched.py).
The linker packs head → function .text → gap peels → tail in order, with
only the head pinned at 0x08000000. Sizes still come from asm/matchings/*.s so
gap peels stay stable without compiling C first. Pointer words in those peels (Thumb function entries, `gData_*` tables, and
runs of ROM data pointers) are `.4byte` relocs. `gData_*` / `gRom_*` symbols
are labels in the peel, not `SET_DATA` pins.
"""

from __future__ import annotations

import hashlib
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from fnfiles import stem_for   # noqa: E402

BASEROM = ROOT / "baserom.gba"
MANIFEST = ROOT / "build" / "matched.json"
MATCH_DIR = ROOT / "asm" / "matchings"
ASM_DIR = ROOT / "asm"
LAYOUT_LD = ASM_DIR / "rom_layout.ld"

ROM_BASE = 0x08000000
ROM_SIZE = 0x400000


DATA_SYMBOLS = ROOT / "asm" / "data_symbols.s"
SET_DATA_RE = re.compile(
    r"^(?:SET_DATA|SET_ROM_DATA)\s+([A-Za-z_][A-Za-z0-9_]*)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\s*$"
)


def thumb_fn_map(functions: list[dict]) -> dict[int, str]:
    """Retail Thumb pointer word (entry|1) → matched symbol."""
    return {int(fn["addr"], 16) | 1: fn["name"] for fn in functions}


def rom_data_symbols() -> dict[int, str]:
    """File offset → `gData_*` for symbols in the ROM window."""
    out: dict[int, str] = {}
    if not DATA_SYMBOLS.is_file():
        return out
    for line in DATA_SYMBOLS.read_text().splitlines():
        match = SET_DATA_RE.match(line.split("@")[0].strip())
        if not match:
            continue
        addr = int(match.group(2), 0)
        if ROM_BASE <= addr < ROM_BASE + ROM_SIZE:
            out[addr - ROM_BASE] = match.group(1)
    return out


UNKNOWN_FNS = ROOT / "include" / "unknown-functions.h"
THUNK_RE = re.compile(r"\b(_08[0-9A-Fa-f]{6})\b")
CALL_VIA_BASE = 0x08073C40
CALL_VIA_REGS = [
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
    "sl", "fp", "ip", "sp", "lr",
]


def thunk_labels() -> dict[int, list[str]]:
    """File offset → names for unmatched libgcc / `_080*` veneers."""
    out: dict[int, list[str]] = {}

    def add(addr: int, name: str) -> None:
        if not (ROM_BASE <= addr < ROM_BASE + ROM_SIZE):
            return
        names = out.setdefault(addr - ROM_BASE, [])
        if name not in names:
            names.append(name)

    for i, reg in enumerate(CALL_VIA_REGS):
        add(CALL_VIA_BASE + 4 * i, f"_call_via_{reg}")
    add(0x080740B0, "__divsi3")
    add(0x080740B0, "_080740B0")
    if UNKNOWN_FNS.is_file():
        for name in sorted(set(THUNK_RE.findall(UNKNOWN_FNS.read_text()))):
            add(int(name[1:], 16), name)
    return out


SUB_RE = re.compile(r"\b(sub_08[0-9A-Fa-f]{6})\b")


def unmatched_sub_labels(functions: list[dict]) -> dict[int, list[str]]:
    """`sub_*` called from C but not a matched object — live in peels."""
    matched = {fn["name"] for fn in functions}
    covered: list[tuple[int, int]] = []
    for fn in functions:
        start = int(fn["addr"], 16) - ROM_BASE
        size = int(fn.get("size") or 1)
        covered.append((start, start + max(size, 1)))
    names: set[str] = set()
    matched_dir = ROOT / "src" / "matched"
    if matched_dir.is_dir():
        for path in matched_dir.glob("*.c"):
            names.update(SUB_RE.findall(path.read_text()))
    if UNKNOWN_FNS.is_file():
        names.update(SUB_RE.findall(UNKNOWN_FNS.read_text()))
    out: dict[int, list[str]] = {}
    for name in names:
        if name in matched:
            continue
        addr = int(name[4:], 16)
        if not (ROM_BASE <= addr < ROM_BASE + ROM_SIZE):
            continue
        off = addr - ROM_BASE
        if any(lo <= off < hi for lo, hi in covered):
            continue
        out.setdefault(off, []).append(name)
    return out


def merge_peel_labels(functions: list[dict]) -> dict[int, list[str]]:
    """gData_* ROM symbols plus unmatched code veneers, keyed by file offset."""
    out: dict[int, list[str]] = {}
    for off, name in rom_data_symbols().items():
        out.setdefault(off, []).append(name)
    for extra in (thunk_labels(), unmatched_sub_labels(functions)):
        for off, names in extra.items():
            slot = out.setdefault(off, [])
            for name in names:
                if name not in slot:
                    slot.append(name)
    return out


def is_code_label(name: str) -> bool:
    return (
        name.startswith("_080")
        or name.startswith("_call_via_")
        or name.startswith("sub_")
        or name == "__divsi3"
    )


def reloc_word_map(
    functions: list[dict], data_off_to_name: dict[int, str]
) -> dict[int, str]:
    """Little-endian word value → symbol for peel `.4byte` relocs."""
    mapping = thumb_fn_map(functions)
    for off, name in data_off_to_name.items():
        mapping.setdefault(ROM_BASE + off, name)
    return mapping


def matched_coverage(functions: list[dict], rom_len: int) -> bytearray:
    covered = bytearray(rom_len)
    for fn in functions:
        off = int(fn["addr"], 16) - ROM_BASE
        size = int(fn.get("size") or 0)
        if size > 0 and 0 <= off < rom_len:
            covered[off : off + size] = b"\x01" * size
    return covered


MIN_PTR_RUN = 2
# GBA header; leftover words that "point" here are almost never data pointers.
ROM_HEADER_SIZE = 0xC0
# Isolated 0x08…… words in a low-density window are struct fields; a ~0.5
# fraction is graphics / palettes (leave those baked so a slide keeps pixels).
PTR_SPARSE_FRAC = 0.25
PTR_NEIGHBOR_BYTES = 128


def rom_window_frac(rom: bytes, off: int, radius: int = PTR_NEIGHBOR_BYTES) -> float:
    """Fraction of 4-aligned words in `[off-radius, off+radius)` in the ROM window."""
    lo = max(0, (off - radius) & ~3)
    hi = min(len(rom), (off + radius + 3) & ~3)
    total = 0
    hits = 0
    pos = lo
    while pos + 4 <= hi:
        total += 1
        word = int.from_bytes(rom[pos : pos + 4], "little")
        if ROM_BASE <= word < ROM_BASE + ROM_SIZE:
            hits += 1
        pos += 4
    return hits / total if total else 0.0


def pointer_table_sites(
    rom: bytes, covered: bytearray, labels: dict[int, list[str]]
) -> tuple[dict[int, list[str]], dict[int, str]]:
    """High-confidence ROM pointers in peels → target labels + site `.4byte` map.

    Runs of `MIN_PTR_RUN` or more 4-aligned words in the ROM window are tables
    (pairs included). Leftover singletons become `.4byte` when they already
    point at a peel label, or when they sit in a sparse window (`PTR_SPARSE_FRAC`)
    with a target past the ROM header — graphics clusters stay baked.
    """
    n = len(rom)
    words: list[tuple[int, int]] = []
    off = 0
    while off + 4 <= n:
        if not covered[off]:
            word = int.from_bytes(rom[off : off + 4], "little")
            if ROM_BASE <= word < ROM_BASE + ROM_SIZE and not is_counting_bytes(
                rom, off
            ):
                words.append((off, word))
        off += 4

    new_labels: dict[int, list[str]] = {}
    sites: dict[int, str] = {}

    def name_at(target_off: int, thumb: bool, create: bool) -> str | None:
        existing = labels.get(target_off) or new_labels.get(target_off)
        if existing:
            if thumb:
                for name in existing:
                    if is_code_label(name):
                        return name
            for name in existing:
                if name.startswith("gData_") or name.startswith("gRom_"):
                    return name
            return existing[0]
        if not create:
            return None
        addr = ROM_BASE + target_off
        name = f"_{addr:08X}" if thumb else f"gRom_{addr:08X}"
        new_labels.setdefault(target_off, []).append(name)
        return name

    def add_site(site: int, word: int, create: bool) -> None:
        if (word & 3) not in (0, 1):
            return
        tgt = (word - ROM_BASE) & ~1
        if tgt < 0 or tgt >= n or covered[tgt]:
            return
        name = name_at(tgt, bool(word & 1), create)
        if name:
            # Peel labels live in .rodata; `.thumb_func` does not set the
            # ELF thumb bit, so ABS32 function pointers need an explicit +1.
            sites[site] = f"{name} + 1" if word & 1 else name

    i = 0
    nw = len(words)
    while i < nw:
        j = i + 1
        while j < nw and words[j][0] == words[j - 1][0] + 4:
            j += 1
        if j - i >= MIN_PTR_RUN:
            for site, word in words[i:j]:
                add_site(site, word, create=True)
        i = j
    for site, word in words:
        if site not in sites:
            add_site(site, word, create=False)
    for site, word in words:
        if site in sites:
            continue
        tgt = (word - ROM_BASE) & ~1
        if tgt < ROM_HEADER_SIZE:
            continue
        if rom_window_frac(rom, site) > PTR_SPARSE_FRAC:
            continue
        add_site(site, word, create=True)
    return new_labels, sites


def is_counting_bytes(rom: bytes, off: int) -> bool:
    """Reject 05 06 07 08-style runs that collide with a pointer word."""
    chunk = rom[off : off + 4]
    if len(chunk) < 4:
        return False
    up = bytes((chunk[0] + i) & 0xFF for i in range(4))
    down = bytes((chunk[0] - i) & 0xFF for i in range(4))
    return chunk == up or chunk == down


def reloc_sites(
    rom: bytes, start: int, length: int, word_to_name: dict[int, str]
) -> list[tuple[int, str]]:
    """4-aligned file offsets of known pointer words in a peel."""
    sites: list[tuple[int, str]] = []
    end = start + length
    off = (start + 3) & ~3
    while off + 4 <= end:
        word = int.from_bytes(rom[off : off + 4], "little")
        name = word_to_name.get(word)
        if name is not None and not is_counting_bytes(rom, off):
            sites.append((off, name))
        off += 4
    return sites


def fn_ptr_sites(
    rom: bytes, start: int, length: int, thumb_map: dict[int, str]
) -> list[tuple[int, str]]:
    """4-aligned file offsets of Thumb function-entry words in a peel."""
    return reloc_sites(rom, start, length, thumb_map)


def hexaddr(value: int) -> str:
    return f"0x{value:08X}"


SIZE_CACHE = ROOT / "build" / "asm_size_cache.json"


def cached_text_size(asm_path: Path, cache: dict[str, list]) -> int:
    """`asm_text_size` with a content-hash-keyed cache.

    Assembling + objcopy'ing all 633 stubs costs ~13 s per call, but an
    integration only rewrites one of them; every other size is unchanged.
    """
    digest = hashlib.sha1(asm_path.read_bytes()).hexdigest()
    key = asm_path.name
    hit = cache.get(key)
    if hit and hit[0] == digest:
        return hit[1]
    size = asm_text_size(asm_path)
    cache[key] = [digest, size]
    return size


def asm_text_size(asm_path: Path) -> int:
    with tempfile.TemporaryDirectory() as tmp:
        obj = Path(tmp) / "fn.o"
        bin_path = Path(tmp) / "fn.bin"
        subprocess.run(
            [
                "arm-none-eabi-as",
                "-mcpu=arm7tdmi",
                "-mthumb-interwork",
                "-o",
                str(obj),
                str(asm_path),
            ],
            check=True,
            capture_output=True,
        )
        subprocess.run(
            ["arm-none-eabi-objcopy", "-O", "binary", "-j", ".text", str(obj), str(bin_path)],
            check=True,
            capture_output=True,
        )
        return bin_path.stat().st_size


def format_peel(
    symbol: str,
    start: int,
    length: int,
    comment: str,
    rom: bytes | None = None,
    word_to_name: dict[int, str] | None = None,
    labels: dict[int, list[str]] | None = None,
    extra_relocs: dict[int, str] | None = None,
) -> str:
    """Incbin with `.4byte` pointer relocs and peel labels spliced in."""
    if length == 0:
        return f"@ {comment} (empty)\n"

    header = (
        f"@ {comment}\n"
        f'\t.section .rodata,"a",%progbits\n'
        f"\t.balign 2\n"
        f"\t.global {symbol}\n"
        f"{symbol}:\n"
    )
    end = start + length
    local_labels = {
        off: list(names)
        for off, names in (labels or {}).items()
        if start <= off < end
    }
    relocs = dict(
        reloc_sites(rom, start, length, word_to_name)
        if rom is not None and word_to_name
        else []
    )
    if extra_relocs:
        for off, name in extra_relocs.items():
            if start <= off < end:
                relocs.setdefault(off, name)
    if not local_labels and not relocs:
        return header + f'\t.incbin "baserom.gba", 0x{start:X}, 0x{length:X}\n'

    lines = [header.rstrip()]
    keys = sorted(set(local_labels) | set(relocs))
    ki = 0
    nkeys = len(keys)
    pos = start
    emitted: set[int] = set()
    while pos < end:
        while ki < nkeys and keys[ki] < pos:
            ki += 1
        if pos in local_labels and pos not in emitted:
            for name in local_labels[pos]:
                lines.append(f"\t.global {name}")
                if is_code_label(name):
                    lines.append("\t.thumb_func")
                lines.append(f"{name}:")
            emitted.add(pos)
            continue
        if pos in relocs:
            lines.append(f"\t.4byte {relocs[pos]}")
            pos += 4
            continue
        nxt = keys[ki] if ki < nkeys else end
        if nxt <= pos:
            ki += 1
            nxt = keys[ki] if ki < nkeys else end
        if nxt > pos:
            lines.append(f'\t.incbin "baserom.gba", 0x{pos:X}, 0x{nxt - pos:X}')
        pos = nxt
    return "\n".join(lines) + "\n"


def write_incbin(
    path: Path,
    symbol: str,
    start: int,
    length: int,
    comment: str,
    rom: bytes | None = None,
    word_to_name: dict[int, str] | None = None,
    labels: dict[int, list[str]] | None = None,
    extra_relocs: dict[int, str] | None = None,
) -> tuple[int, int]:
    """Write a peel stub, but leave the file (and its mtime) alone when it is
    already byte-identical.

    Touching a stub makes `make` reassemble it, so rewriting all ~340 gap files
    on every integration costs ~6 s of needless work in `make compare`. Gap
    filenames are address-based (see `main`) precisely so untouched ranges keep
    their identity across integrations.

    Returns (`.4byte` count, `gData_*` labels in this peel).
    """
    text = format_peel(
        symbol, start, length, comment, rom, word_to_name, labels, extra_relocs
    )
    n_ptr = text.count("\t.4byte ")
    n_lab = sum(
        len(names)
        for off, names in (labels or {}).items()
        if start <= off < start + length
    )
    if path.is_file() and path.read_text() == text:
        return n_ptr, n_lab
    path.write_text(text)
    return n_ptr, n_lab


def main() -> int:
    if not MANIFEST.is_file():
        print(f"gen_rom_layout: no manifest at {MANIFEST}", file=sys.stderr)
        return 1
    if not BASEROM.is_file():
        print("gen_rom_layout: missing baserom.gba", file=sys.stderr)
        return 1

    data = json.loads(MANIFEST.read_text())
    functions = sorted(data.get("functions", []), key=lambda f: int(f["addr"], 16))

    try:
        cache = json.loads(SIZE_CACHE.read_text())
    except (FileNotFoundError, json.JSONDecodeError):
        cache = {}

    for fn in functions:
        asm = MATCH_DIR / f"{fn['name']}.s"
        if not asm.is_file():
            print(f"gen_rom_layout: missing {asm}", file=sys.stderr)
            return 1
        fn["size"] = cached_text_size(asm, cache)

    SIZE_CACHE.parent.mkdir(parents=True, exist_ok=True)
    SIZE_CACHE.write_text(json.dumps(cache))

    rom = BASEROM.read_bytes()
    data_labels = merge_peel_labels(functions)
    word_to_name = reloc_word_map(functions, rom_data_symbols())
    covered = matched_coverage(functions, len(rom))
    anon_labels, table_sites = pointer_table_sites(rom, covered, data_labels)
    for off, names in anon_labels.items():
        slot = data_labels.setdefault(off, [])
        for name in names:
            if name not in slot:
                slot.append(name)
    n_relocs = 0
    n_labels = 0
    n_table = len(table_sites)
    n_anon = sum(len(v) for v in anon_labels.values())

    for old in ASM_DIR.glob("rom_gap_*.s"):
        old.unlink()

    ld_lines: list[str] = []

    if not functions:
        n_r, n_l = write_incbin(
            ASM_DIR / "rom.s",
            "gBaserom",
            0,
            ROM_SIZE,
            "Full baserom (no matched functions yet)",
            rom,
            word_to_name,
            data_labels,
            table_sites,
        )
        n_relocs += n_r
        n_labels += n_l
        n_r, n_l = write_incbin(
            ASM_DIR / "rom_tail.s", "gRomTail", ROM_SIZE, 0, "empty tail"
        )
        n_relocs += n_r
        n_labels += n_l
        ld_lines = [
            f"    .rom {hexaddr(ROM_BASE)} : {{",
            "        asm/rom.o(.rodata)",
            "    } > ROM",
        ]
    else:
        first_off = int(functions[0]["addr"], 16) - ROM_BASE
        n_r, n_l = write_incbin(
            ASM_DIR / "rom.s",
            "gBaserom",
            0,
            first_off,
            f"Unmatched ROM head {hexaddr(ROM_BASE)}..{hexaddr(ROM_BASE + first_off - 1)}",
            rom,
            word_to_name,
            data_labels,
            table_sites,
        )
        n_relocs += n_r
        n_labels += n_l
        ld_lines.append(f"    .rom_head {hexaddr(ROM_BASE)} : {{")
        ld_lines.append("        asm/rom.o(.rodata)")
        ld_lines.append("    } > ROM")
        # Output section so ld keeps the hole; a bare `. = . + N` is ignored.
        ld_lines.append("    .rom_shift : {")
        ld_lines.append("        . = . + __rom_shift_bytes;")
        ld_lines.append("    } > ROM")
        # SUBALIGN(2): Thumb sites are 2-byte aligned; default .rodata is 4.
        # Without this the linker pads 2-mod-4 gaps and SHA1 breaks.
        ld_lines.append("    .rom_body : SUBALIGN(2) {")

        for i, fn in enumerate(functions):
            addr = int(fn["addr"], 16)
            name = fn["name"]
            ld_lines.append(f"        src/matched/{stem_for(name)}.o(.text)")
            end = addr + fn["size"]

            if i + 1 < len(functions):
                next_addr = int(functions[i + 1]["addr"], 16)
                gap_start = end - ROM_BASE
                gap_len = next_addr - end
                if gap_len < 0:
                    print(f"gen_rom_layout: overlap after {name}", file=sys.stderr)
                    return 1
                if gap_len > 0:
                    gap_path = ASM_DIR / f"rom_gap_{gap_start:07X}.s"
                    gap_name = f"gRomGap{gap_start:07X}"
                    n_r, n_l = write_incbin(
                        gap_path,
                        gap_name,
                        gap_start,
                        gap_len,
                        f"Unmatched ROM {hexaddr(end)}..{hexaddr(next_addr - 1)}",
                        rom,
                        word_to_name,
                        data_labels,
                        table_sites,
                    )
                    n_relocs += n_r
                    n_labels += n_l
                    ld_lines.append(f"        asm/rom_gap_{gap_start:07X}.o(.rodata)")
            else:
                tail_start = end - ROM_BASE
                tail_len = ROM_SIZE - tail_start
                if tail_len < 0:
                    print("gen_rom_layout: matched functions extend past ROM end", file=sys.stderr)
                    return 1
                n_r, n_l = write_incbin(
                    ASM_DIR / "rom_tail.s",
                    "gRomTail",
                    tail_start,
                    tail_len,
                    f"Unmatched ROM tail from {hexaddr(end)}",
                    rom,
                    word_to_name,
                    data_labels,
                    table_sites,
                )
                n_relocs += n_r
                n_labels += n_l
                ld_lines.append("        asm/rom_tail.o(.rodata)")

        ld_lines.append("    } > ROM")

    LAYOUT_LD.write_text("\n".join(ld_lines) + "\n")
    print(f"gen_rom_layout: {len(functions)} matched function(s)")
    print(f"gen_rom_layout: {n_relocs} pointer word(s) as .4byte")
    print(
        f"gen_rom_layout: {n_table} high-confidence data-pointer word(s) "
        f"(runs>={MIN_PTR_RUN} + labeled refs + sparse singletons)"
    )
    print(f"gen_rom_layout: {n_anon} gRom_/_08* table-target label(s)")
    print(f"gen_rom_layout: {n_labels} peel label(s) (gData_* + veneers + unmatched sub_* + gRom_*)")
    print(f"gen_rom_layout: wrote {LAYOUT_LD}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
