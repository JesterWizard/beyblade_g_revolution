#!/usr/bin/env python3
"""Compile scratch C and compare .text to retail baserom bytes."""

from __future__ import annotations

import argparse
import difflib
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NONMATCH = ROOT / "asm" / "nonmatchings"
MATCH = ROOT / "asm" / "matchings"
BASEROM = ROOT / "baserom.gba"
AGBCC = ROOT / "tools/agbcc/bin/agbcc"
ROM_BASE = 0x08000000
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

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from asm_bytes import addr_from_name, asm_text_bytes, retail_bytes  # noqa: E402


def preprocess(c_path: Path, out_path: Path) -> None:
    subprocess.run(
        ["arm-none-eabi-gcc", "-E", *CPPFLAGS, str(c_path), "-o", str(out_path)],
        check=True,
        cwd=str(ROOT),
    )


def compile_c(c_path: Path, obj_path: Path) -> None:
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


def encode_thumb_bl(from_addr: int, to_addr: int) -> bytes:
    """R_ARM_THM_CALL: 32-bit Thumb BL from `from_addr` to `to_addr`."""
    offset = to_addr - (from_addr + 4)
    hw1 = 0xF000 | ((offset >> 12) & 0x7FF)
    hw2 = 0xF800 | ((offset >> 1) & 0x7FF)
    return hw1.to_bytes(2, "little") + hw2.to_bytes(2, "little")


def reloc_target_addr(name: str) -> int | None:
    """ROM address for a Thumb BL reloc symbol (`sub_080…` or `_080…`)."""
    if name.startswith("sub_"):
        return addr_from_name(name)
    if re.fullmatch(r"_[0-9A-Fa-f]{7,8}", name):
        return int(name[1:], 16)
    return None


def apply_thm_call_relocs(obj_path: Path, function: str, data: bytes) -> bytes:
    """Patch unlinked Thumb BL stubs using ROM addresses from symbol names."""
    result = subprocess.run(
        ["arm-none-eabi-readelf", "-r", str(obj_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode != 0 or "R_ARM_THM_CALL" not in result.stdout:
        return data
    base = addr_from_name(function)
    out = bytearray(data)
    for line in result.stdout.splitlines():
        if "R_ARM_THM_CALL" not in line:
            continue
        parts = line.split()
        if len(parts) < 5:
            continue
        off = int(parts[0], 16)
        target_name = parts[-1]
        target = reloc_target_addr(target_name)
        if target is None:
            continue
        if off + 4 > len(out):
            continue
        encoded = encode_thumb_bl(base + off, target)
        out[off : off + 4] = encoded
    return bytes(out)


def obj_text_bytes(obj_path: Path, function: str | None = None) -> bytes:
    with tempfile.TemporaryDirectory() as tmp:
        bin_path = Path(tmp) / "fn.bin"
        subprocess.run(
            ["arm-none-eabi-objcopy", "-O", "binary", "-j", ".text", str(obj_path), str(bin_path)],
            check=True,
        )
        data = bin_path.read_bytes()
    if function:
        data = apply_thm_call_relocs(obj_path, function, data)
    return data


def reference_size(function: str) -> int:
    for base in (NONMATCH, MATCH):
        asm = base / f"{function}.s"
        if not asm.is_file():
            continue
        text = asm.read_text()
        if "incbin" in text:
            for line in text.splitlines():
                m = re_incbin(line)
                if m:
                    return int(m.group(2), 16)
        data = asm_text_bytes(asm)
        if data:
            return len(data)
    raise FileNotFoundError(function)


def re_incbin(line: str):
    return re.search(
        r'\.incbin\s+"baserom\.gba",\s*0x[0-9A-Fa-f]+,\s*(0x[0-9A-Fa-f]+|\d+)',
        line,
    )


def normalize_compiled(data: bytes, retail_size: int) -> bytes:
    if len(data) == retail_size:
        return data
    if len(data) == retail_size + 2 and data[:retail_size] == data[:retail_size]:
        tail = data[retail_size:]
        if tail in (b"\xc0\x46", b"\x00\x00"):
            return data[:retail_size]
    return data


def write_single_function_c(function: str, body: str, out: Path) -> None:
    out.write_text(f'#include "global.h"\n\n// @ {addr_from_name(function):#010x}\n{body}\n')


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function", help="sub_0802B90C")
    parser.add_argument("c_file", help="scratch .c with the function")
    parser.add_argument(
        "--function-only",
        action="store_true",
        help="Compile only the named function (temp single-function translation unit)",
    )
    args = parser.parse_args()

    if not BASEROM.is_file():
        print("missing baserom.gba", file=sys.stderr)
        return 1
    if not AGBCC.is_file():
        print("missing agbcc — run build_tools.sh", file=sys.stderr)
        return 1

    try:
        size = reference_size(args.function)
    except FileNotFoundError:
        print(f"missing asm for {args.function}", file=sys.stderr)
        return 1

    want = retail_bytes(args.function, size)

    with tempfile.TemporaryDirectory() as tmp:
        compile_path = Path(args.c_file)
        if args.function_only:
            src = Path(args.c_file).read_text()
            marker = f"{args.function}("
            if marker not in src:
                print(f"{args.function} not found in {args.c_file}", file=sys.stderr)
                return 1
            compile_path = Path(tmp) / "one.c"
            compile_path.write_text(src)

        obj = Path(tmp) / "scratch.o"
        compile_c(compile_path, obj)
        got = normalize_compiled(obj_text_bytes(obj, args.function), size)

        if got == want:
            print("MATCH")
            return 0

        print("DIFF")
        print(f"retail size {size}, compiled size {len(got)}")
        for line in difflib.unified_diff(
            [want.hex()],
            [got.hex()],
            fromfile="retail",
            tofile="compiled",
            lineterm="",
        ):
            print(line)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
