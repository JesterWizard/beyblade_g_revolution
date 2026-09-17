#!/usr/bin/env python3
"""Detect opcode-embedded vs semantic matched C."""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"


def is_opcode_stub(path: Path) -> bool:
    text = path.read_text()
    return "__attribute__((naked))" in text and 'asm(".byte' in text


def is_semantic_c(path: Path) -> bool:
    text = path.read_text()
    if 'asm(".byte' in text:
        return False
    if "__attribute__((naked))" in text and "asm(" in text:
        # naked asm shims (stack shim, mov pc lr) count as semantic enough
        return True
    return True


def list_opcode_stubs() -> list[str]:
    out: list[str] = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        if is_opcode_stub(path):
            out.append(path.stem)
    return out


def list_semantic() -> list[str]:
    out: list[str] = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        if not is_opcode_stub(path):
            out.append(path.stem)
    return out


def main() -> int:
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("--opcode", action="store_true")
    parser.add_argument("--semantic", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    if args.opcode:
        names = list_opcode_stubs()
    elif args.semantic:
        names = list_semantic()
    else:
        opcode = list_opcode_stubs()
        semantic = list_semantic()
        print(f"semantic: {len(semantic)}")
        print(f"opcode stubs: {len(opcode)}")
        return 0

    if args.json:
        import json

        print(json.dumps(names))
    else:
        for n in names:
            print(n)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
