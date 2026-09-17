#!/usr/bin/env python3
"""Generate ROM peel asm + linker fragment from build/matched.json."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BASEROM = ROOT / "baserom.gba"
MANIFEST = ROOT / "build" / "matched.json"
MATCH_DIR = ROOT / "asm" / "matchings"
ASM_DIR = ROOT / "asm"
LAYOUT_LD = ASM_DIR / "rom_layout.ld"

ROM_BASE = 0x08000000
ROM_SIZE = 0x400000


def hexaddr(value: int) -> str:
    return f"0x{value:08X}"


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


def write_incbin(path: Path, symbol: str, start: int, length: int, comment: str) -> None:
    if length == 0:
        path.write_text(f"@ {comment} (empty)\n")
        return
    path.write_text(
        f"@ {comment}\n"
        f"\t.section .rodata\n"
        f"\t.global {symbol}\n"
        f"{symbol}:\n"
        f'\t.incbin "baserom.gba", 0x{start:X}, 0x{length:X}\n'
    )


def main() -> int:
    if not MANIFEST.is_file():
        print(f"gen_rom_layout: no manifest at {MANIFEST}", file=sys.stderr)
        return 1
    if not BASEROM.is_file():
        print("gen_rom_layout: missing baserom.gba", file=sys.stderr)
        return 1

    data = json.loads(MANIFEST.read_text())
    functions = sorted(data.get("functions", []), key=lambda f: int(f["addr"], 16))

    for fn in functions:
        asm = MATCH_DIR / f"{fn['name']}.s"
        if not asm.is_file():
            print(f"gen_rom_layout: missing {asm}", file=sys.stderr)
            return 1
        fn["size"] = asm_text_size(asm)

    for old in ASM_DIR.glob("rom_gap_*.s"):
        old.unlink()

    ld_lines: list[str] = []

    if not functions:
        write_incbin(
            ASM_DIR / "rom.s",
            "gBaserom",
            0,
            ROM_SIZE,
            "Full baserom (no matched functions yet)",
        )
        write_incbin(ASM_DIR / "rom_tail.s", "gRomTail", ROM_SIZE, 0, "empty tail")
        ld_lines = [
            f"    .rom {hexaddr(ROM_BASE)} : {{",
            "        asm/rom.o(.rodata)",
            "    } > ROM",
        ]
    else:
        first_off = int(functions[0]["addr"], 16) - ROM_BASE
        write_incbin(
            ASM_DIR / "rom.s",
            "gBaserom",
            0,
            first_off,
            f"Unmatched ROM head {hexaddr(ROM_BASE)}..{hexaddr(ROM_BASE + first_off - 1)}",
        )
        ld_lines.append(f"    .rom_head {hexaddr(ROM_BASE)} : {{")
        ld_lines.append("        asm/rom.o(.rodata)")
        ld_lines.append("    } > ROM")

        gap_idx = 0
        for i, fn in enumerate(functions):
            addr = int(fn["addr"], 16)
            name = fn["name"]
            ld_lines.append(f"    .rom_{name} {hexaddr(addr)} : {{")
            ld_lines.append(f"        asm/matchings/{name}.o(.text)")
            ld_lines.append("    } > ROM")
            end = addr + fn["size"]

            if i + 1 < len(functions):
                next_addr = int(functions[i + 1]["addr"], 16)
                gap_start = end - ROM_BASE
                gap_len = next_addr - end
                if gap_len < 0:
                    print(f"gen_rom_layout: overlap after {name}", file=sys.stderr)
                    return 1
                if gap_len > 0:
                    gap_path = ASM_DIR / f"rom_gap_{gap_idx:03d}.s"
                    write_incbin(
                        gap_path,
                        f"gRomGap{gap_idx:03d}",
                        gap_start,
                        gap_len,
                        f"Unmatched ROM {hexaddr(end)}..{hexaddr(next_addr - 1)}",
                    )
                    ld_lines.append(f"    .rom_gap_{gap_idx:03d} {hexaddr(end)} : {{")
                    ld_lines.append(f"        asm/rom_gap_{gap_idx:03d}.o(.rodata)")
                    ld_lines.append("    } > ROM")
                    gap_idx += 1
            else:
                tail_start = end - ROM_BASE
                tail_len = ROM_SIZE - tail_start
                if tail_len < 0:
                    print("gen_rom_layout: matched functions extend past ROM end", file=sys.stderr)
                    return 1
                write_incbin(
                    ASM_DIR / "rom_tail.s",
                    "gRomTail",
                    tail_start,
                    tail_len,
                    f"Unmatched ROM tail from {hexaddr(end)}",
                )
                ld_lines.append(f"    .rom_tail {hexaddr(end)} : {{")
                ld_lines.append("        asm/rom_tail.o(.rodata)")
                ld_lines.append("    } > ROM")

    LAYOUT_LD.write_text("\n".join(ld_lines) + "\n")
    print(f"gen_rom_layout: {len(functions)} matched function(s)")
    print(f"gen_rom_layout: wrote {LAYOUT_LD}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
