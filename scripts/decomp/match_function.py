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
NONMATCH = ROOT / "asm" / "nonmatchings"
MATCH = ROOT / "asm" / "matchings"
AGBCC = ROOT / "tools/agbcc/bin/agbcc"
CPPFLAGS = [
    "-iquote",
    "include",
    "-Wno-trigraphs",
    "-DMODERN=0",
    "-I",
    "tools/agbcc/include",
    "-I",
    "tools/agbcc",
    "-nostdinc",
    "-undef",
    "-std=gnu89",
]


def preprocess(c_path: Path, out_path: Path) -> None:
    subprocess.run(
        ["arm-none-eabi-gcc", "-E", *CPPFLAGS, str(c_path), "-o", str(out_path)],
        check=True,
        cwd=str(ROOT),
    )


def compile_c(c_path: Path, obj_path: Path) -> Path:
    asm_path = obj_path.with_suffix(".s")
    with tempfile.NamedTemporaryFile(suffix=".i", delete=False) as tmp:
        i_path = Path(tmp.name)
    try:
        preprocess(c_path, i_path)
        subprocess.run(
            [
                str(AGBCC),
                str(i_path),
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
            cwd=str(ROOT),
        )
    finally:
        i_path.unlink(missing_ok=True)
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

    asm_file = MATCH / f"{args.function}.s"
    if not asm_file.is_file():
        asm_file = NONMATCH / f"{args.function}.s"
    if not asm_file.is_file():
        print(f"missing asm for {args.function}", file=sys.stderr)
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
