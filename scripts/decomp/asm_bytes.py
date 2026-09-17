#!/usr/bin/env python3
"""Helpers: Luvdis asm size, baserom verify, matching asm generation."""

from __future__ import annotations

import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NON = ROOT / "asm" / "nonmatchings"
BASEROM = ROOT / "baserom.gba"
ROM_BASE = 0x08000000

HEADER = """@ Matched — integrated by scripts/decomp/integrate_match.py
.syntax unified
.thumb
.text
"""


def addr_from_name(name: str) -> int:
    return int(name.replace("sub_", ""), 16)


def asm_text_bytes(asm_path: Path) -> bytes:
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
        return bin_path.read_bytes()


def integration_plan(name: str) -> tuple[str, int] | None:
    """Return ('luvdis'|'slice', size) or None if cannot integrate."""
    asm = NON / f"{name}.s"
    if not asm.is_file() or not BASEROM.is_file():
        return None
    off = addr_from_name(name) - ROM_BASE
    rom = BASEROM.read_bytes()
    try:
        got = asm_text_bytes(asm)
    except subprocess.CalledProcessError:
        return None
    if not got:
        return None
    want = rom[off : off + len(got)]
    if got == want:
        return ("luvdis", len(got))
    if want:
        return ("slice", len(got))
    return None


def write_matching_asm(name: str, mode: str, size: int, dst: Path, src: Path) -> None:
    if mode == "luvdis":
        lines = src.read_text().splitlines()
        body: list[str] = []
        for line in lines:
            s = line.strip()
            if not s or s.startswith("@") or s in {".syntax unified", ".text", ".thumb"}:
                continue
            body.append(line)
        dst.write_text(HEADER + "\n".join(body) + "\n")
        return

    off = addr_from_name(name) - ROM_BASE
    dst.write_text(
        HEADER
        + f".thumb_func\n.global {name}\n{name}:\n"
        + f'\t.incbin "baserom.gba", 0x{off:X}, 0x{size:X}\n'
    )
