#!/usr/bin/env python3
"""Emit readable Thumb (not .byte) from nonmatchings asm for opcode stubs."""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts" / "decomp"))
NON = ROOT / "asm" / "nonmatchings"

from c_patterns import CCandidate  # noqa: E402


def _function_slice(function: str, asm_lines: list[str]) -> list[str]:
    start = None
    for i, line in enumerate(asm_lines):
        if line.strip() == f"{function}:":
            start = i + 1
            break
    if start is None:
        return []
    end = len(asm_lines)
    for j in range(start, len(asm_lines)):
        stripped = asm_lines[j].strip()
        if stripped.endswith(":") and not stripped.startswith(".") and not stripped.startswith("_"):
            end = j
            break
    return asm_lines[start:end]


def guess_readable_asm(function: str, asm_lines: list[str] | None = None) -> CCandidate | None:
    if asm_lines is None:
        path = NON / f"{function}.s"
        if not path.is_file():
            return None
        asm_lines = path.read_text().splitlines()
    body_lines = []
    for line in _function_slice(function, asm_lines):
        stripped = line.strip()
        if not stripped or stripped.startswith("@"):
            continue
        if stripped.startswith(".syntax") or stripped in (".thumb", ".text"):
            continue
        body_lines.append(line.rstrip())
    if not body_lines:
        return None
    # Keep Thumb as written (unified syntax + pools).
    escaped = []
    for ln in body_lines:
        ln = ln.replace("\\", "\\\\").replace('"', '\\"')
        escaped.append(ln)
    inner = "\\n".join(s.strip() if not s.startswith("\t") else s[1:] for s in escaped)
    body = (
        f"__attribute__((naked))\n"
        f"void {function}(void)\n{{\n"
        f'    asm(".syntax unified\\n{inner}");\n}}'
    )
    return CCandidate(body, "readable thumb")
