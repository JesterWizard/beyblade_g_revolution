#!/usr/bin/env python3
"""Generate ROM peel asm + linker fragment from build/matched.json."""

from __future__ import annotations

import hashlib
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


def write_incbin(path: Path, symbol: str, start: int, length: int, comment: str) -> None:
    """Write a peel stub, but leave the file (and its mtime) alone when it is
    already byte-identical.

    Touching a stub makes `make` reassemble it, so rewriting all ~340 gap files
    on every integration costs ~6 s of needless work in `make compare`. Gap
    filenames are address-based (see `main`) precisely so untouched ranges keep
    their identity across integrations.
    """
    if length == 0:
        text = f"@ {comment} (empty)\n"
    else:
        text = (
            f"@ {comment}\n"
            f"\t.section .rodata\n"
            f"\t.global {symbol}\n"
            f"{symbol}:\n"
            f'\t.incbin "baserom.gba", 0x{start:X}, 0x{length:X}\n'
        )
    if path.is_file() and path.read_text() == text:
        return
    path.write_text(text)


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
                    gap_path = ASM_DIR / f"rom_gap_{gap_start:07X}.s"
                    gap_name = f"gRomGap{gap_start:07X}"
                    write_incbin(
                        gap_path,
                        gap_name,
                        gap_start,
                        gap_len,
                        f"Unmatched ROM {hexaddr(end)}..{hexaddr(next_addr - 1)}",
                    )
                    ld_lines.append(f"    .rom_gap_{gap_start:07X} {hexaddr(end)} : {{")
                    ld_lines.append(f"        asm/rom_gap_{gap_start:07X}.o(.rodata)")
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
