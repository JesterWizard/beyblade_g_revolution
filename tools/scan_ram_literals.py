#!/usr/bin/env python3
"""Scan baserom Thumb LDR literal pools for IWRAM / EWRAM / SRAM-bus addresses.

Prefer pool-backed hits over raw absolute word matches (graphics/data false positives).

Usage:
  python3 tools/scan_ram_literals.py [--rom baserom.gba]
  python3 tools/scan_ram_literals.py --emit-asm    # refresh asm/*_pool.inc
  python3 tools/scan_ram_literals.py --emit-h      # refresh include/ram_map_pool.h
  python3 tools/scan_ram_literals.py --emit-doc      # refresh documentation/ram-map.md
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from collections import defaultdict
from datetime import date
from pathlib import Path

ROM_BASE = 0x08000000

SKIP_SYMBOL_PREFIXES = (
    "FreeRam",
    "FreeEwram",
    "FreeFlash",
    "UsedFree",
)

DOC_BEGIN = "<!-- AUTO-GENERATED: scan_ram_literals.py --begin -->"
DOC_END = "<!-- AUTO-GENERATED: scan_ram_literals.py --end -->"


def in_iwram(a: int) -> bool:
    return 0x03000000 <= a <= 0x03007FFF


def in_ewram(a: int) -> bool:
    return 0x02000000 <= a <= 0x0203FFFF


def in_sram(a: int) -> bool:
    return 0x0E000000 <= a <= 0x0E00FFFF


def load_known_from_ram_map(path: Path) -> dict[int, str]:
    """Parse SET_DATA / SET_ARRAY lines from a manual ram_map fragment."""
    if not path.is_file():
        return {}
    known: dict[int, str] = {}
    for raw in path.read_text().splitlines():
        line = raw.split("@")[0].strip()
        m = re.match(
            r"SET_(?:DATA|ARRAY)\s+(\w+),\s+(0x[0-9A-Fa-f]+)",
            line,
        )
        if not m:
            continue
        name, addr = m.group(1), int(m.group(2), 16)
        if any(name.startswith(prefix) for prefix in SKIP_SYMBOL_PREFIXES):
            continue
        known[addr] = name
    return known


def load_known_symbols(root: Path) -> tuple[dict[int, str], dict[int, str]]:
    asm = root / "asm"
    iwram = load_known_from_ram_map(asm / "ram_map_iwram.s")
    ewram = load_known_from_ram_map(asm / "ram_map_ewram.s")
    return iwram, ewram


def scan_pools(rom: bytes) -> dict[str, dict[int, list[int]]]:
    """Return region -> {address: [ldr_file_offsets]}."""
    hits: dict[str, dict[int, list[int]]] = {
        "iwram": defaultdict(list),
        "ewram": defaultdict(list),
        "sram": defaultdict(list),
    }
    size = len(rom)
    for off in range(0, size - 2, 2):
        hw = rom[off] | (rom[off + 1] << 8)
        if (hw & 0xF800) != 0x4800:
            continue
        imm = hw & 0xFF
        pc = (ROM_BASE + off + 4) & ~2
        pool_off = pc + imm * 4 - ROM_BASE
        if pool_off < 0 or pool_off + 4 > size:
            continue
        word = struct.unpack_from("<I", rom, pool_off)[0]
        if in_iwram(word):
            hits["iwram"][word].append(off)
        elif in_ewram(word):
            hits["ewram"][word].append(off)
        elif in_sram(word):
            hits["sram"][word].append(off)
    return hits


def clusters(addrs: list[int], merge_gap: int) -> list[tuple[int, int]]:
    if not addrs:
        return []
    out: list[tuple[int, int]] = []
    start = end = addrs[0]
    for a in addrs[1:]:
        if a - end <= merge_gap:
            end = a
        else:
            out.append((start, end))
            start = end = a
    out.append((start, end))
    return out


def iwram_high_water(hits: dict[int, list[int]], stack_floor: int = 0x03007B00) -> int | None:
    aligned = [a for a in hits if a % 4 == 0 and a < stack_floor]
    return max(aligned) if aligned else None


def emit_iwram_asm(
    hits: dict[int, list[int]], known: dict[int, str], out: Path
) -> int:
    aligned = sorted(
        a
        for a in hits
        if a % 4 == 0 and a < 0x03007CA0 and a not in known
    )
    lines: list[str] = []
    lines.append("@ =============================================================================")
    lines.append("@ AUTO-GENERATED — do not edit by hand.")
    lines.append("@   python3 tools/scan_ram_literals.py --emit-asm")
    lines.append("@ Word-aligned Thumb LDR literal-pool IWRAM targets below user stack,")
    lines.append("@ excluding symbols already named in ram_map_iwram.s.")
    lines.append("@ =============================================================================")
    lines.append("")
    for a in aligned:
        n = len(hits[a])
        lines.append(f"SET_DATA gUnk_{a:08X}, 0x{a:08X}  @ pool hits={n}")
    out.write_text("\n".join(lines) + "\n")
    print(f"Wrote {out} ({len(aligned)} symbols)", file=sys.stderr)
    return len(aligned)


def emit_ewram_asm(
    hits: dict[int, list[int]], known: dict[int, str], out: Path
) -> int:
    aligned = sorted(
        a
        for a in hits
        if a % 4 == 0
        and a < 0x02030000
        and len(hits[a]) >= 2
        and a not in known
    )
    lines: list[str] = []
    lines.append("@ =============================================================================")
    lines.append("@ AUTO-GENERATED — do not edit by hand.")
    lines.append("@   python3 tools/scan_ram_literals.py --emit-asm")
    lines.append("@ Word-aligned EWRAM pool targets with hits>=2 below FreeEwramSpaceTop.")
    lines.append("@ Excludes symbols already named in ram_map_ewram.s.")
    lines.append("@ Single-hit / unaligned / >=0x02030000 omitted (likely false positives).")
    lines.append("@ =============================================================================")
    lines.append("")
    for a in aligned:
        n = len(hits[a])
        lines.append(f"SET_DATA gUnk_{a:08X}, 0x{a:08X}  @ pool hits={n}")
    out.write_text("\n".join(lines) + "\n")
    print(f"Wrote {out} ({len(aligned)} symbols)", file=sys.stderr)
    return len(aligned)


def collect_pool_symbols(pool_path: Path) -> dict[int, str]:
    if not pool_path.is_file():
        return {}
    out: dict[int, str] = {}
    for raw in pool_path.read_text().splitlines():
        m = re.match(r"SET_DATA\s+(gUnk_[0-9A-Fa-f]+),\s+(0x[0-9A-Fa-f]+)", raw.strip())
        if m:
            out[int(m.group(2), 16)] = m.group(1)
    return out


def emit_c_header(
    known_iwram: dict[int, str],
    known_ewram: dict[int, str],
    iwram_pool: Path,
    ewram_pool: Path,
    out: Path,
) -> None:
    symbols: dict[int, str] = {}
    symbols.update(known_iwram)
    symbols.update(known_ewram)
    symbols.update(collect_pool_symbols(iwram_pool))
    symbols.update(collect_pool_symbols(ewram_pool))
    lines = [
        "/* AUTO-GENERATED — do not edit by hand.",
        " *   python3 tools/scan_ram_literals.py --emit-h",
        " * Absolute IWRAM/EWRAM addresses for C (agbcc matching paths).",
        " */",
        "#ifndef GUARD_RAM_MAP_POOL_H",
        "#define GUARD_RAM_MAP_POOL_H",
        "",
    ]
    for addr in sorted(symbols):
        lines.append(f"#define {symbols[addr]} 0x{addr:08X}")
    lines.extend(["", "#endif /* GUARD_RAM_MAP_POOL_H */", ""])
    out.write_text("\n".join(lines) + "\n")
    print(f"Wrote {out} ({len(symbols)} defines)", file=sys.stderr)


def render_doc_section(
    hits: dict[str, dict[int, list[int]]],
    known_iwram: dict[int, str],
    known_ewram: dict[int, str],
    iwram_pool_count: int,
    ewram_pool_count: int,
) -> str:
    today = date.today().isoformat()
    iw = hits["iwram"]
    ew = hits["ewram"]
    aligned_iw = sorted(a for a in iw if a % 4 == 0 and a < 0x03007B00)
    high = iwram_high_water(iw)
    high_end = f"0x{high + 4:08X}" if high is not None else "n/a"

    lines = [
        DOC_BEGIN,
        f"_Last scan: {today} (`baserom.gba` Thumb LDR literal pools)._",
        "",
        "## Scan summary",
        "",
        "| Region | Pool-backed (aligned) | Named (manual) | Auto `gUnk_*` | High-water (below stack) |",
        "|--------|----------------------:|---------------:|--------------:|--------------------------|",
        f"| IWRAM | {len(aligned_iw)} | {len(known_iwram)} | {iwram_pool_count} | {high_end} |",
        f"| EWRAM | {len([a for a in ew if a % 4 == 0 and a < 0x02030000])} | {len(known_ewram)} | {ewram_pool_count} | (see occupancy) |",
        f"| SRAM bus | {len([a for a in hits['sram'] if a % 4 == 0])} | 0 | 0 | — |",
        "",
        "## Occupancy (provisional)",
        "",
        "| Range | Status | Notes |",
        "|-------|--------|-------|",
        "| `0x03000000` – vanilla high-water | **USED** | Literal-pool references; see clusters below |",
        f"| vanilla high-water – `FreeRamSpaceTop` (`0x03007A00`) | **UNKNOWN** | No pool refs; may be runtime BSS — verify in mGBA before reuse |",
        "| `FreeRamSpaceTop` – `FreeRamSpaceBottom` | **FREE** | Custom `_kernel_malloc` bump (hack pool) |",
        "| `0x03007B00` – `0x03008000` | **USED** | User + IRQ stacks (leave alone) |",
        "| `0x02000000` – `FreeEwramSpaceTop` (`0x02030000`) | **USED** | Retail EWRAM; almost no pool refs in this ROM |",
        "| `FreeEwramSpaceTop` – `FreeEwramSpaceBottom` | **FREE** | Custom `_kernel_malloc_ewram` bump |",
        "| `0x0E000000` – `FreeFlashSpaceBottom` | **FREE*** | Opt-in SRAM-bus scratch (`ram_map_sram.s`) |",
        "",
        "## IWRAM clusters (merge gap `< 0x40`)",
        "",
        "| Start | End | Unique addrs | Pool hits | Span |",
        "|-------|-----|-------------:|----------:|-----:|",
    ]
    for s, e in clusters(aligned_iw, 0x40):
        n = sum(1 for a in aligned_iw if s <= a <= e)
        h = sum(len(iw[a]) for a in aligned_iw if s <= a <= e)
        lines.append(
            f"| `0x{s:08X}` | `0x{e:08X}` | {n} | {h} | `0x{e - s + 4:X}` |"
        )

    lines.extend(
        [
            "",
            "## Top IWRAM literal-pool targets",
            "",
            "| Address | Hits | Symbol |",
            "|---------|-----:|--------|",
        ]
    )
    freq = sorted(
        ((a, len(iw[a])) for a in iw if a % 4 == 0),
        key=lambda x: -x[1],
    )
    for a, c in freq[:25]:
        name = known_iwram.get(a, f"`gUnk_{a:08X}`")
        if not name.startswith("`"):
            name = f"`{name}`"
        lines.append(f"| `0x{a:08X}` | {c} | {name} |")

    if known_iwram:
        lines.extend(
            [
                "",
                "## Named IWRAM symbols (manual)",
                "",
                "| Symbol | Address |",
                "|--------|---------|",
            ]
        )
        for addr, name in sorted(known_iwram.items()):
            lines.append(f"| `{name}` | `0x{addr:08X}` |")

    lines.extend(["", DOC_END, ""])
    return "\n".join(lines)


def emit_doc(
    hits: dict[str, dict[int, list[int]]],
    known_iwram: dict[int, str],
    known_ewram: dict[int, str],
    iwram_pool_count: int,
    ewram_pool_count: int,
    out: Path,
) -> None:
    section = render_doc_section(
        hits, known_iwram, known_ewram, iwram_pool_count, ewram_pool_count
    )
    preamble = """# RAM map

Absolute IWRAM / EWRAM / save-bus symbols live in `asm/ram_map*.s` and are
included into a single `asm/ram_map.s` object. C code should include
`include/ram_map.h` (hand-written symbols) and `include/ram_map_pool.h`
(auto-generated pool inventory) instead of hardcoding `0x03…` / `0x02…`.

## Regeneration

```bash
scripts/decomp/ram_map_pass.sh
# or:
python3 tools/scan_ram_literals.py --emit-asm --emit-h --emit-doc
make compare
```

Manual symbols belong in `asm/ram_map_iwram.s` / `asm/ram_map_ewram.s`
**before** the `.include "*_pool.inc"` line. Re-run the scan after adding names
so duplicates drop out of the pool fragments.

"""
    if out.is_file():
        text = out.read_text()
        if DOC_BEGIN in text and DOC_END in text:
            before = text.split(DOC_BEGIN, 1)[0].rstrip() + "\n\n"
            out.write_text(before + section)
            print(f"Updated {out} (auto section)", file=sys.stderr)
            return
    out.write_text(preamble + section)
    print(f"Wrote {out}", file=sys.stderr)


def print_report(
    hits: dict[str, dict[int, list[int]]],
    known_iwram: dict[int, str],
    known_ewram: dict[int, str],
) -> None:
    known_by_region = {"iwram": known_iwram, "ewram": known_ewram, "sram": {}}
    for region, merge in (("iwram", 0x40), ("ewram", 0x100), ("sram", 0x100)):
        d = hits[region]
        known = known_by_region[region]
        aligned = sorted(a for a in d if a % 4 == 0)
        print(f"\n=== {region.upper()} pool-backed aligned: {len(aligned)} ===")
        if not aligned:
            continue
        print(f"range 0x{min(aligned):08X}–0x{max(aligned):08X}")
        freq = sorted(((a, len(v)) for a, v in d.items() if a % 4 == 0), key=lambda x: -x[1])
        print("top 20:")
        for a, c in freq[:20]:
            name = known.get(a, "")
            print(f"  0x{a:08X}  hits={c:4d}  {name}")
        print(f"clusters (merge gap < {merge:#x}):")
        for s, e in clusters(aligned, merge):
            n = sum(1 for a in aligned if s <= a <= e)
            h = sum(len(d[a]) for a in aligned if s <= a <= e)
            print(f"  0x{s:08X}–0x{e:08X}  unique={n:3d}  hits={h:5d}  span={e - s + 4:#x}")
    hw = iwram_high_water(hits["iwram"])
    if hw is not None:
        print(f"\nIWRAM high-water (below stack): 0x{hw:08X}")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rom", type=Path, default=Path("baserom.gba"))
    ap.add_argument(
        "--emit-asm",
        action="store_true",
        help="Write inventory fragments under asm/ (included by ram_map_*.s)",
    )
    ap.add_argument(
        "--emit-h",
        action="store_true",
        help="Write include/ram_map_pool.h from named + pool symbols",
    )
    ap.add_argument(
        "--emit-doc",
        action="store_true",
        help="Refresh auto-generated section in documentation/ram-map.md",
    )
    args = ap.parse_args()
    root = Path.cwd()
    if not args.rom.is_file():
        print(f"missing ROM: {args.rom}", file=sys.stderr)
        return 1

    known_iwram, known_ewram = load_known_symbols(root)
    rom = args.rom.read_bytes()
    hits = scan_pools(rom)
    print_report(hits, known_iwram, known_ewram)

    iwram_pool_count = 0
    ewram_pool_count = 0
    if args.emit_asm:
        asm = root / "asm"
        asm.mkdir(parents=True, exist_ok=True)
        iwram_pool_count = emit_iwram_asm(
            hits["iwram"], known_iwram, asm / "ram_map_iwram_pool.inc"
        )
        ewram_pool_count = emit_ewram_asm(
            hits["ewram"], known_ewram, asm / "ram_map_ewram_pool.inc"
        )
    else:
        iwram_pool_count = len(collect_pool_symbols(root / "asm" / "ram_map_iwram_pool.inc"))
        ewram_pool_count = len(collect_pool_symbols(root / "asm" / "ram_map_ewram_pool.inc"))

    if args.emit_h:
        emit_c_header(
            known_iwram,
            known_ewram,
            root / "asm" / "ram_map_iwram_pool.inc",
            root / "asm" / "ram_map_ewram_pool.inc",
            root / "include" / "ram_map_pool.h",
        )

    if args.emit_doc:
        emit_doc(
            hits,
            known_iwram,
            known_ewram,
            iwram_pool_count,
            ewram_pool_count,
            root / "documentation" / "ram-map.md",
        )

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
