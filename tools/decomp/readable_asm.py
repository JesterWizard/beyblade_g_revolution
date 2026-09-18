#!/usr/bin/env python3
"""Emit readable Thumb (not .byte) from nonmatchings asm for opcode stubs."""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
NON = ROOT / "asm" / "nonmatchings"
MATCHED = ROOT / "src" / "matched"

from c_patterns import CCandidate  # noqa: E402


def _signature_from_matched(function: str) -> str | None:
    """Reuse prototype from an existing opcode stub (naked + params)."""
    path = MATCHED / f"{function}.c"
    if not path.is_file():
        return None
    text = path.read_text()
    marker = "__attribute__((naked))"
    if marker not in text:
        return None
    start = text.index(marker)
    brace = text.index("{", start)
    return text[start:brace].rstrip()


def _asm_insn_lines(body_lines: list[str]) -> list[str]:
    out: list[str] = []
    for line in body_lines:
        s = line.rstrip()
        if s.startswith("\t"):
            s = s[1:]
        out.append(s)
    return out


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
    sig = _signature_from_matched(function)
    if sig is None:
        sig = f"__attribute__((naked))\nvoid {function}(void)"
    insns = _asm_insn_lines(body_lines)
    asm_lines = ['        ".syntax unified\\n"']
    for insn in insns:
        asm_lines.append(f'        "{insn}\\n"')
    asm_block = "\n".join(asm_lines)
    body = f"{sig}\n{{\n    asm(\n{asm_block}\n    );\n}}\n"
    return CCandidate(body, "readable thumb")
