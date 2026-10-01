#!/usr/bin/env python3
"""Compile one src/matched/*.c into a ROM-peel object.

Uses the same agbcc / flags / fixups as match_function.py, verifies .text
against retail (patching relocs only for the score), then keeps the ELF
`.text` plus its relocs so the linker can retarget BLs and `gData_*` pools
when later peels slide. Extra sections are stripped so they cannot leak
into `.append_rodata`. The object's exported `.text` symbol is the filename
stem so clone C (`void sub_0804B4B4` in `sub_0804C324.c`) does not collide.
"""

from __future__ import annotations

import argparse
import re
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from match_function import (  # noqa: E402
    BannedAsmError,
    check_semantic_asm,
    compile_c,
    normalize_compiled,
    obj_text_bytes,
    reference_size,
    retail_bytes,
    score_bytes,
)

_OBJDUMP_SEC_RE = re.compile(r"^\s+\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+")
_SKIP_SECTIONS = frozenset(
    {
        ".text",
        ".rel.text",
        ".rela.text",
        ".symtab",
        ".strtab",
        ".shstrtab",
        ".comment",
        ".note",
        ".ARM.attributes",
    }
)


def defined_text_globals(obj_path: Path) -> list[str]:
    """Global `.text` symbols (`T`), excluding mapping / compiler sentinels."""
    result = subprocess.run(
        ["arm-none-eabi-nm", "-g", "--defined-only", str(obj_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    names: list[str] = []
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) < 3 or parts[1] not in {"T", "t"}:
            continue
        name = parts[-1]
        if name.startswith(".") or name.startswith("$"):
            continue
        names.append(name)
    return names


def export_filename_symbol(obj_path: Path, stem: str) -> None:
    """Clone / alias C must link as the filename (`sub_0804C324.o` → `sub_0804C324`)."""
    names = defined_text_globals(obj_path)
    if stem in names:
        return
    if len(names) != 1:
        raise SystemExit(
            f"{obj_path}: expected one global .text symbol to rename to {stem}, "
            f"got {names}"
        )
    subprocess.run(
        [
            "arm-none-eabi-objcopy",
            f"--redefine-sym={names[0]}={stem}",
            str(obj_path),
        ],
        check=True,
    )


def extra_sections(obj_path: Path) -> list[str]:
    """Non-.text sections that would leak into the append ROM if linked raw."""
    result = subprocess.run(
        ["arm-none-eabi-objdump", "-h", str(obj_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    bad: list[str] = []
    for line in result.stdout.splitlines():
        match = _OBJDUMP_SEC_RE.match(line)
        if not match:
            continue
        name, size_hex = match.group(1), match.group(2)
        size = int(size_hex, 16)
        if not size or name in _SKIP_SECTIONS or name.startswith(".debug"):
            continue
        bad.append(f"{name} ({size} bytes)")
    return bad


def shrink_elf32_text(obj_path: Path, new_size: int) -> None:
    """Set `.text` sh_size without dropping `.rel.text` (objcopy cannot)."""
    data = bytearray(obj_path.read_bytes())
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        raise SystemExit(f"{obj_path}: expected ELF32 little-endian")
    e_shoff = struct.unpack_from("<I", data, 32)[0]
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 46)
    str_off = struct.unpack_from(
        "<I", data, e_shoff + e_shstrndx * e_shentsize + 16
    )[0]
    for i in range(e_shnum):
        sh = e_shoff + i * e_shentsize
        name_off = struct.unpack_from("<I", data, sh)[0]
        end = data.find(b"\x00", str_off + name_off)
        name = data[str_off + name_off : end].decode("ascii")
        if name != ".text":
            continue
        struct.pack_into("<I", data, sh + 20, new_size)
        obj_path.write_bytes(data)
        return
    raise SystemExit(f"{obj_path}: no .text section")


def emit_text_with_relocs(raw: Path, dest: Path, size: int) -> None:
    """Keep `.text` and its relocs; drop debug / leftover .rodata."""
    shutil.copy(raw, dest)
    subprocess.run(
        [
            "arm-none-eabi-objcopy",
            "--strip-debug",
            "-R",
            ".rodata",
            "-R",
            ".data",
            "-R",
            ".bss",
            str(dest),
        ],
        check=True,
    )
    with tempfile.TemporaryDirectory() as tmp:
        bin_path = Path(tmp) / "fn.bin"
        subprocess.run(
            [
                "arm-none-eabi-objcopy",
                "-O",
                "binary",
                "-j",
                ".text",
                str(dest),
                str(bin_path),
            ],
            check=True,
        )
        got = bin_path.stat().st_size
    if got == size:
        return
    if got > size:
        shrink_elf32_text(dest, size)
        return
    raise SystemExit(f"{dest}: compiled .text is {got} bytes, retail is {size}")


def compile_matched(c_path: Path, obj_path: Path) -> None:
    name = c_path.stem
    if not name.startswith("sub_"):
        raise SystemExit(f"compile_matched: expected sub_*.c, got {c_path}")

    check_semantic_asm(c_path)
    size = reference_size(name)
    want = retail_bytes(name, size)

    obj_path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        raw = Path(tmp) / "raw.o"
        compile_c(c_path, raw)
        got = normalize_compiled(obj_text_bytes(raw, name), size)
        if got != want:
            info = score_bytes(got, want)
            extra = extra_sections(raw)
            hint = f" extra sections: {', '.join(extra)}" if extra else ""
            raise SystemExit(
                f"{c_path}: compiled .text is not retail "
                f"({info['score']}, {info['status']}).{hint} "
                f"Keep matching C; do not land a DIFF in the peel."
            )
        emit_text_with_relocs(raw, obj_path, size)
        export_filename_symbol(obj_path, name)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("c_file", type=Path)
    parser.add_argument("obj_file", type=Path)
    args = parser.parse_args()
    c_path = args.c_file if args.c_file.is_absolute() else ROOT / args.c_file
    obj_path = args.obj_file if args.obj_file.is_absolute() else ROOT / args.obj_file
    try:
        compile_matched(c_path, obj_path)
    except BannedAsmError as exc:
        print(f"BANNED ASM: {exc}", file=sys.stderr)
        return 2
    except subprocess.CalledProcessError as exc:
        print(exc, file=sys.stderr)
        return exc.returncode or 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
