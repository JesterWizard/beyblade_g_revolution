#!/usr/bin/env python3
"""Insert 4 bytes after the first matched .text and check later peels slide.

Does not replace `beyblade_g_revolution.gba` or rewrite `src/matched/`.
`make GROW=1 COMPARE=0 rom` is the same mechanism for a real C edit.
"""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from fnfiles import stem_for  # noqa: E402
from gen_rom_layout import (  # noqa: E402
    BASEROM,
    LAYOUT_LD,
    MANIFEST,
    ROM_BASE,
    SIZE_CACHE,
    matched_coverage,
    merge_peel_labels,
    pointer_table_sites,
    reloc_sites,
    reloc_word_map,
    rom_data_symbols,
)

PAD = 4
RETAIL_GBA = ROOT / "beyblade_g_revolution.gba"
RETAIL_ELF = ROOT / "beyblade_g_revolution.elf"
GROW_ELF = ROOT / "build" / "grow_test.elf"
GROW_ROM = ROOT / "build" / "grow_test.gba"
GROW_MAP = ROOT / "build" / "grow_test.map"
GROW_LD = ROOT / "build" / "grow_ld_script.ld"
GROW_LAYOUT = ROOT / "build" / "grow_rom_layout.ld"
GROW_PAD_S = ROOT / "build" / "grow_pad.s"
GROW_PAD_O = ROOT / "build" / "bbgr" / "grow_pad.o"


def sorted_functions() -> list[dict]:
    fns = json.loads(MANIFEST.read_text()).get("functions", [])
    cache = json.loads(SIZE_CACHE.read_text())
    for fn in fns:
        rec = cache.get(f"{fn['name']}.s")
        if rec:
            fn["size"] = rec[1]
    return sorted(fns, key=lambda f: int(f["addr"], 16))


def nm_addr(elf: Path, name: str) -> int | None:
    result = subprocess.run(
        ["arm-none-eabi-nm", str(elf)],
        capture_output=True,
        text=True,
        check=True,
    )
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[-1] == name:
            return int(parts[0], 16)
    return None


def assemble_pad() -> None:
    GROW_PAD_S.parent.mkdir(parents=True, exist_ok=True)
    GROW_PAD_O.parent.mkdir(parents=True, exist_ok=True)
    GROW_PAD_S.write_text(
        '\t.section .text,"ax",%progbits\n'
        "\t.balign 2\n"
        "\t.short 0x46C0\n"
        "\t.short 0x46C0\n"
    )
    subprocess.run(
        [
            "arm-none-eabi-as",
            "-mcpu=arm7tdmi",
            "-mthumb-interwork",
            "-o",
            str(GROW_PAD_O),
            str(GROW_PAD_S),
        ],
        check=True,
    )


def write_grow_scripts(first_name: str) -> None:
    needle = f"src/matched/{stem_for(first_name)}.o(.text)"
    layout = LAYOUT_LD.read_text()
    if needle not in layout:
        raise SystemExit(f"test_grow: {needle} missing from rom_layout.ld")
    if "grow_pad.o(.text)" not in layout:
        layout = layout.replace(needle, needle + "\n        grow_pad.o(.text)", 1)
    GROW_LAYOUT.write_text(layout)
    ld = (ROOT / "ld_script.ld").read_text().replace(
        "INCLUDE rom_layout.ld", "INCLUDE grow_rom_layout.ld", 1
    )
    GROW_LD.write_text(ld)


def build_grown() -> None:
    for path in (GROW_ELF, GROW_ROM, GROW_MAP):
        path.unlink(missing_ok=True)
    subprocess.run(
        [
            "make",
            f"ELF={GROW_ELF.relative_to(ROOT)}",
            f"ROM={GROW_ROM.relative_to(ROOT)}",
            f"MAP={GROW_MAP.relative_to(ROOT)}",
            f"LD_SCRIPT={GROW_LD.relative_to(ROOT)}",
            "EXTRA_OBJS=grow_pad.o",
            "LDFLAGS=-Map ../../build/grow_test.map -L ../../build -L ../../asm",
            "COMPARE=0",
            "PAD_CART=0",
            "rom",
        ],
        cwd=ROOT,
        check=True,
    )


def main() -> int:
    if not BASEROM.is_file() or not MANIFEST.is_file() or not SIZE_CACHE.is_file():
        print("test_grow: missing baserom or matched manifest", file=sys.stderr)
        return 1
    if not RETAIL_GBA.is_file() or not RETAIL_ELF.is_file():
        subprocess.run(["make", "rom"], cwd=ROOT, check=True)

    fns = sorted_functions()
    if len(fns) < 2:
        print("test_grow: need at least two matched functions", file=sys.stderr)
        return 1
    first, second = fns[0], fns[1]
    first_addr = int(first["addr"], 16)
    second_addr = int(second["addr"], 16)

    print(f"test_grow: +{PAD} bytes after {first['name']}")
    assemble_pad()
    write_grow_scripts(first["name"])
    build_grown()

    retail_first = nm_addr(RETAIL_ELF, first["name"])
    retail_second = nm_addr(RETAIL_ELF, second["name"])
    grown_first = nm_addr(GROW_ELF, first["name"])
    grown_second = nm_addr(GROW_ELF, second["name"])
    if None in (retail_first, retail_second, grown_first, grown_second):
        print("test_grow: missing nm symbols", file=sys.stderr)
        return 1

    retail = RETAIL_GBA.read_bytes()
    grown = GROW_ROM.read_bytes()
    first_end = first_addr + first["size"] - ROM_BASE
    second_off = second_addr - ROM_BASE
    second_size = second["size"]
    body_ok = (
        grown[second_off + PAD : second_off + PAD + second_size]
        == retail[second_off : second_off + second_size]
    )

    fns_for_sites = list(fns)
    covered = matched_coverage(fns_for_sites, len(retail))
    labels = merge_peel_labels(fns_for_sites)
    _anon, table_sites = pointer_table_sites(retail, covered, labels)
    mapping = reloc_word_map(fns_for_sites, rom_data_symbols())
    sites = dict(table_sites)
    for off, name in reloc_sites(retail, 0, len(retail), mapping):
        if not covered[off]:
            sites.setdefault(off, name)

    ptr_msg = "no live peel ptr whose target is after the grown function"
    ptr_ok = False
    for off in sorted(sites):
        word = int.from_bytes(retail[off : off + 4], "little")
        tgt = (word - ROM_BASE) & ~1
        if tgt < first_end:
            continue
        want = word + PAD
        slide_off = off if off < first_end else off + PAD
        if slide_off + 4 > len(grown):
            continue
        got = int.from_bytes(grown[slide_off : slide_off + 4], "little")
        ptr_ok = got == want
        ptr_msg = (
            f"live ptr at 0x{off:06X}: want {want:#x} got {got:#x} "
            f"(retail {word:#x})"
        )
        break

    gates: list[tuple[bool, str]] = []
    gates.append(
        (
            grown_first == retail_first == first_addr,
            f"{first['name']} stays at {first['addr']}",
        )
    )
    gates.append(
        (
            grown_second == retail_second + PAD == second_addr + PAD,
            f"{second['name']} slides to {second_addr + PAD:#x} "
            f"(was {second_addr:#x})",
        )
    )
    gates.append(
        (
            len(grown) == len(retail) + PAD,
            f"ROM is retail+{PAD} ({len(grown)}/{len(retail) + PAD})",
        )
    )
    gates.append(
        (body_ok, f"{second['name']} .text bytes sit {PAD} bytes later")
    )
    gates.append((ptr_ok, ptr_msg))

    print("=== Grow a function ===")
    ok_all = True
    for ok, msg in gates:
        print(f"  [{'OK' if ok else 'NO'}] {msg}")
        ok_all = ok_all and ok
    if ok_all:
        print(
            f"Later peels follow a {PAD}-byte grow after {first['name']}. "
            "Edit src/matched/*.c and `make GROW=1 COMPARE=0 rom` for mods."
        )
        return 0
    print("Grow test failed — later objects did not slide.")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
