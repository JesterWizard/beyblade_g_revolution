#!/usr/bin/env python3
"""Compile one src/matched/*.c into a ROM-peel object.

Uses the same agbcc / flags / fixups / BL-reloc patch as match_function.py, then
emits a .text blob of exactly the retail size. The linker still places the
object at a fixed VMA (Phase 5 step 1); live relocs come later.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from asm_bytes import write_matching_bytes  # noqa: E402
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
        blob_s = Path(tmp) / "blob.s"
        write_matching_bytes(name, got, blob_s)
        subprocess.run(
            [
                "arm-none-eabi-as",
                "-mcpu=arm7tdmi",
                "-mthumb-interwork",
                "-o",
                str(obj_path),
                str(blob_s),
            ],
            check=True,
        )


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
