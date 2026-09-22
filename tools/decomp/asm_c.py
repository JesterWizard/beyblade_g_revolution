#!/usr/bin/env python3
"""Dump the agbcc-generated asm for a scratch C file (diff vs retail asm).

usage: asm_c.py <function> <scratch.c> [compiler]
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
import match_function as mf  # noqa: E402


def main() -> int:
    fn, c_path = sys.argv[1], Path(sys.argv[2])
    if len(sys.argv) > 3:
        text = c_path.read_text()
        if not mf.MATCH_COMPILER_RE.search(text):
            text = f"/* match-compiler: {sys.argv[3]} */\n" + text
        c_path = Path("/tmp/asmc_dump.c")
        c_path.write_text(text)
    obj = ROOT / "build" / "asmc_dump.o"
    obj.parent.mkdir(parents=True, exist_ok=True)
    mf.compile_c(c_path, obj)
    asm = obj.with_suffix(".s")
    print(asm.read_text())
    return 0


if __name__ == "__main__":
    sys.exit(main())
