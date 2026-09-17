#!/usr/bin/env python3
"""Prepare Luvdis nonmatching asm for m2c (GBA / Thumb)."""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
M2C = ROOT / "tools" / "m2c" / "m2c.py"
NON = ROOT / "asm" / "nonmatchings"

POOL_RE = re.compile(
    r"^(\s*)ldr\s+([rR]\d+),\s+(_[0-9A-Fa-f]+)\s+@\s+=(0x[0-9A-Fa-f]+)\s*$"
)
LABEL_POOL_RE = re.compile(r"^(_[0-9A-Fa-f]+):\s+\.4byte\s+(0x[0-9A-Fa-f]+)\s*$")


def prepare_asm_text(function: str, asm_lines: list[str] | None = None) -> str:
    """Convert generate_asm.py syntax to m2c-friendly Thumb asm."""
    if asm_lines is None:
        path = NON / f"{function}.s"
        asm_lines = path.read_text().splitlines()

    pools: list[str] = []
    out: list[str] = [".syntax unified", ".thumb", f"{function}:"]
    in_fn = False
    for line in asm_lines:
        stripped = line.strip()
        if stripped == f"{function}:":
            in_fn = True
            continue
        if not in_fn:
            continue
        m = LABEL_POOL_RE.match(stripped)
        if m:
            pools.append(m.group(2))
            continue
        if stripped.startswith(".byte"):
            break
        if stripped.endswith(":") and not stripped.startswith("."):
            break
        m = POOL_RE.match(line)
        if m:
            indent, reg, _label, val = m.groups()
            pool = f".L{function}_pool{len(pools)}"
            pools.append(val)
            out.append(f"{indent}ldr {reg}, {pool}")
            continue
        if stripped and not stripped.startswith("@") and not stripped.startswith("."):
            out.append(line.rstrip())

    for i, val in enumerate(pools):
        out.append(f".L{function}_pool{i}:")
        out.append(f".word {val}")
    return "\n".join(out) + "\n"


def m2c_decompile(function: str, valid_syntax: bool = False) -> str | None:
    if not M2C.is_file():
        return None
    asm = prepare_asm_text(function)
    cmd = [
        sys.executable,
        str(M2C),
        "-t",
        "gba",
        "-f",
        function,
        "/dev/stdin",
    ]
    if valid_syntax:
        cmd.append("--valid-syntax")
    result = subprocess.run(
        cmd,
        input=asm,
        capture_output=True,
        text=True,
        env={"PYTHONPATH": str(ROOT / "tools" / "m2c")},
    )
    if result.returncode != 0:
        return None
    text = result.stdout.strip()
    if not text or "Decompilation failure" in text:
        return None
    return text


def main() -> int:
    import argparse

    parser = argparse.ArgumentParser(description="m2c one function from nonmatchings asm")
    parser.add_argument("function")
    parser.add_argument("--valid-syntax", action="store_true")
    parser.add_argument("--asm-only", action="store_true", help="print prepared asm only")
    args = parser.parse_args()

    if args.asm_only:
        print(prepare_asm_text(args.function), end="")
        return 0

    out = m2c_decompile(args.function, valid_syntax=args.valid_syntax)
    if not out:
        print(f"m2c failed for {args.function}", file=sys.stderr)
        return 1
    print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
