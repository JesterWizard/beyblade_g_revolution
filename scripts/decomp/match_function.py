#!/usr/bin/env python3
"""Compile + objdump-diff a scratch C function against target asm (Cursor-native Mizuchi)."""

from __future__ import annotations

import argparse
import difflib
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM_DIR = ROOT / "asm" / "nonmatchings"
AGBCC = ROOT / "tools/agbcc/bin/agbcc"


def compile_c(c_path: Path, obj_path: Path) -> Path:
    asm_path = obj_path.with_suffix(".s")
    subprocess.run(
        [
            str(AGBCC),
            str(c_path),
            "-o",
            str(asm_path),
            "-mthumb-interwork",
            "-Wimplicit",
            "-Wparentheses",
            "-Werror",
            "-O2",
            "-g",
            "-fhex-asm",
        ],
        check=True,
    )
    subprocess.run(
        [
            "arm-none-eabi-as",
            "-mcpu=arm7tdmi",
            "-mthumb-interwork",
            str(asm_path),
            "-o",
            str(obj_path),
        ],
        check=True,
    )
    return asm_path


def objdump(path: Path) -> list[str]:
    out = subprocess.check_output(
        ["arm-none-eabi-objdump", "-d", str(path)],
        text=True,
    )
    lines = []
    for line in out.splitlines():
        if "\t" in line and ":" not in line.split("\t", 1)[0]:
            lines.append(line.strip())
    return lines


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function", help="sub_0802B90C")
    parser.add_argument("c_file", help="scratch .c with the function")
    args = parser.parse_args()

    asm_file = ASM_DIR / f"{args.function}.s"
    if not asm_file.is_file():
        print(f"missing {asm_file}", file=sys.stderr)
        return 1
    if not AGBCC.is_file():
        print("missing agbcc — run scripts/setup.sh", file=sys.stderr)
        return 1

    with tempfile.TemporaryDirectory() as tmp:
        obj = Path(tmp) / "scratch.o"
        compile_c(Path(args.c_file), obj)
        target_obj = Path(tmp) / "target.o"
        subprocess.run(
            [
                "arm-none-eabi-as",
                "-mcpu=arm7tdmi",
                "-mthumb-interwork",
                str(asm_file),
                "-o",
                str(target_obj),
            ],
            check=True,
        )

        got = objdump(obj)
        want = objdump(target_obj)
        if got == want:
            print("MATCH")
            return 0

        print("DIFF")
        for line in difflib.unified_diff(want, got, fromfile="target", tofile="compiled", lineterm=""):
            print(line)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
