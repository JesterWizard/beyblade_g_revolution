#!/usr/bin/env python3
"""Heuristic asm → scratch C for trivial Thumb functions."""

from __future__ import annotations

import re
from dataclasses import dataclass

REG = r"r([0-9]|1[0-5])"
IMM = r"#(0x[0-9A-Fa-f]+|\d+)"


@dataclass
class CCandidate:
    body: str
    note: str


def _norm_line(line: str) -> str | None:
    s = line.split("@")[0].strip().lower()
    if not s or s.startswith(".byte"):
        return None
    if s.endswith(":"):
        return None
    return s


def function_insns(function: str, asm_lines: list[str]) -> list[str]:
    """Thumb instructions for one function (stop at tail, pool, or next label)."""
    out: list[str] = []
    in_fn = False
    for line in asm_lines:
        stripped = line.strip()
        if stripped.startswith(f"{function}:"):
            in_fn = True
            continue
        if not in_fn:
            continue
        if stripped.startswith(".byte") or stripped.startswith("_"):
            break
        if stripped.endswith(":") and not stripped.startswith("."):
            break
        norm = _norm_line(line)
        if norm is None:
            continue
        out.append(norm)
        if norm == "bx lr":
            break
    return out


def guess_c(function: str, asm_lines: list[str]) -> CCandidate | None:
    insns = function_insns(function, asm_lines)
    if not insns:
        return None

    if insns == ["bx lr"]:
        return CCandidate(f"void {function}(void)\n{{\n}}", "empty return")

    m = re.fullmatch(rf"ldrb r0, \[r0, {IMM}\]", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        return CCandidate(
            f"u8 {function}(u8 *a)\n{{\n    return *a;\n}}",
            "load u8",
        )

    m = re.fullmatch(rf"ldr r0, \[r0, {IMM}\]", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        off = m.group(1)
        return CCandidate(
            f"u32 {function}(void *a)\n{{\n    return *(u32 *)((u8 *)a + {off});\n}}",
            f"load u32 +{off}",
        )

    m = re.fullmatch(rf"movs r0, {IMM}", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        return CCandidate(
            f"u32 {function}(void)\n{{\n    return {m.group(1)};\n}}",
            "return imm",
        )

    m0 = re.fullmatch(rf"movs r1, {IMM}", insns[0])
    m1 = re.fullmatch(rf"strb r1, \[r0, {IMM}\]", insns[1]) if len(insns) > 1 else None
    if len(insns) == 3 and insns[2] == "bx lr" and m0 and m1:
        val = m0.group(1)
        off = m1.group(1)
        return CCandidate(
            f"void {function}(void *a)\n{{\n    *(u8 *)((u8 *)a + {off}) = {val};\n}}",
            f"store byte {val} @+{off}",
        )

    m = re.fullmatch(rf"swi {IMM}", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        n = m.group(1)
        return CCandidate(
            f"void {function}(void)\n{{\n    asm(\"swi {n}\");\n}}",
            f"swi {n}",
        )

    m = re.fullmatch(rf"strb r1, \[r0, {IMM}\]", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        off = m.group(1)
        return CCandidate(
            f"void {function}(void *a, u8 v)\n{{\n    *(u8 *)((u8 *)a + {off}) = v;\n}}",
            f"store r1 @+{off}",
        )

    return None
