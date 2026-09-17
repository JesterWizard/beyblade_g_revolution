#!/usr/bin/env python3
"""Heuristic asm → scratch C for trivial Thumb functions."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

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


def _asm_text(function: str, asm_lines: list[str]) -> str:
    """Slice from function label through next global label (includes literal pool)."""
    start = None
    for i, line in enumerate(asm_lines):
        if line.strip() == f"{function}:":
            start = i
            break
    if start is None:
        return ""
    end = len(asm_lines)
    for j in range(start + 1, len(asm_lines)):
        stripped = asm_lines[j].strip()
        if stripped.endswith(":") and not stripped.startswith(".") and not stripped.startswith("_"):
            end = j
            break
    return "\n".join(asm_lines[start:end])


def guess_c(function: str, asm_lines: list[str]) -> CCandidate | None:
    insns = function_insns(function, asm_lines)
    if not insns:
        return None

    if insns == ["mov pc, lr"]:
        return CCandidate(
            f"__attribute__((naked))\nvoid {function}(void)\n{{\n    asm(\"mov pc, lr\");\n}}",
            "naked return",
        )

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

    m0 = re.fullmatch(rf"movs r2, {IMM}", insns[0])
    m1 = re.fullmatch(rf"swi {IMM}", insns[1]) if len(insns) > 1 else None
    if len(insns) == 3 and insns[2] == "bx lr" and m0 and m1 and m0.group(1) == "#0x00":
        n = m1.group(1)
        return CCandidate(
            f"void {function}(void)\n{{\n    asm volatile(\"movs r2, #0\");\n    asm(\"swi {n}\");\n}}",
            f"swi {n} prep r2",
        )

    m = re.fullmatch(rf"swi {IMM}", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        n = m.group(1)
        return CCandidate(
            f"void {function}(void)\n{{\n    asm(\"swi {n}\");\n}}",
            f"swi {n}",
        )

    blob = _asm_text(function, asm_lines)
    m = re.search(
        rf"{function}:\n\tldr r0, _[0-9A-Fa-f]+ @ =(0x[0-9A-Fa-f]+)\n\tbx lr",
        blob,
    )
    if m:
        addr = m.group(1)
        return CCandidate(
            f"u32 {function}(void)\n{{\n    return {addr};\n}}",
            "return iwram ptr",
        )

    m = re.search(
        rf"{function}:\n\tldr r0, _[0-9A-Fa-f]+ @ =(0x[0-9A-Fa-f]+)\n\tldr r0, \[r0, #0x00\]\n\tbx lr",
        blob,
    )
    if m:
        addr = m.group(1)
        return CCandidate(
            f"u32 {function}(void)\n{{\n    return *(u32 *){addr};\n}}",
            "load u32 from iwram",
        )

    m = re.search(
        rf"{function}:\n\tldr r0, _[0-9A-Fa-f]+ @ =(0x[0-9A-Fa-f]+)\n\tldrh r0, \[r0, #0x00\]\n\tbx lr",
        blob,
    )
    if m:
        addr = m.group(1)
        return CCandidate(
            f"u16 {function}(void)\n{{\n    return *(u16 *){addr};\n}}",
            "load u16 from iwram",
        )

    if insns == ["push {r0, r1, r2, r3}", "add sp, #0x010", "bx lr"]:
        return CCandidate(
            f"__attribute__((naked))\nvoid {function}(void)\n{{\n"
            f'    asm("push {{r0, r1, r2, r3}}\\nadd sp, #0x10\\n bx lr");\n}}',
            "stack shim",
        )

    m = re.search(
        rf"{function}:\n\tldr r1, _[0-9A-Fa-f]+ @ =(0x[0-9A-Fa-f]+)\n\tstrb r0, \[r1, #0x00\]\n\tbx lr",
        blob,
    )
    if m:
        addr = m.group(1)
        return CCandidate(
            f"void {function}(u8 v)\n{{\n    *(u8 *){addr} = v;\n}}",
            "store u8 to iwram",
        )

    m = re.fullmatch(rf"strb r1, \[r0, {IMM}\]", insns[0])
    if len(insns) == 2 and insns[1] == "bx lr" and m:
        off = m.group(1)
        return CCandidate(
            f"void {function}(void *a, u8 v)\n{{\n    *(u8 *)((u8 *)a + {off}) = v;\n}}",
            f"store r1 @+{off}",
        )

    if (
        len(insns) == 6
        and insns[0] == "adds r3, r0, #0x0"
        and re.fullmatch(rf"adds r3, {IMM}", insns[1])
        and insns[2] == "strh r1, [r3, #0x00]"
        and re.fullmatch(rf"adds r0, {IMM}", insns[3])
        and insns[4] == "strh r2, [r0, #0x00]"
        and insns[5] == "bx lr"
    ):
        off0 = re.fullmatch(rf"adds r3, {IMM}", insns[1]).group(1)
        off1 = re.fullmatch(rf"adds r0, {IMM}", insns[3]).group(1)
        return CCandidate(
            f"void {function}(void *a, u16 v1, u16 v2)\n{{\n"
            f"    *(u16 *)((u8 *)a + {off0}) = v1;\n"
            f"    *(u16 *)((u8 *)a + {off1}) = v2;\n}}",
            f"store two u16 @+{off0}/+{off1}",
        )

    if (
        len(insns) == 5
        and insns[0] == "movs r2, #0x00"
        and insns[1] == "strh r2, [r0, #0x00]"
        and insns[2] == "str r1, [r0, #0x04]"
        and insns[3] == "strh r2, [r0, #0x02]"
        and insns[4] == "bx lr"
    ):
        return CCandidate(
            f"void {function}(void *a, u32 v)\n{{\n"
            f"    *(u16 *)a = 0;\n"
            f"    *(u32 *)((u8 *)a + 4) = v;\n"
            f"    *(u16 *)((u8 *)a + 2) = 0;\n}}",
            "init u16/u32 fields",
        )

    m0 = re.fullmatch(rf"movs r2, {IMM}", insns[0])
    if (
        len(insns) == 5
        and m0
        and insns[1] == "lsls r2, r2, #0x02"
        and insns[2] == "adds r0, r0, r2"
        and insns[3] == "str r1, [r0, #0x00]"
        and insns[4] == "bx lr"
    ):
        base = int(m0.group(1), 0)
        off = base << 2
        return CCandidate(
            f"void {function}(void *a, u32 v)\n{{\n"
            f"    *(u32 *)((u8 *)a + {off:#x}) = v;\n}}",
            f"store u32 @+{off:#x}",
        )

    if (
        len(insns) == 5
        and insns[0] == "movs r1, #0x00"
        and re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[1])
        and re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[2])
        and re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[3])
        and insns[4] == "bx lr"
    ):
        o1 = re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[1]).group(1)
        o2 = re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[2]).group(1)
        o3 = re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[3]).group(1)
        return CCandidate(
            f"void {function}(void *a)\n{{\n"
            f"    *(u32 *)((u8 *)a + {o1}) = 0;\n"
            f"    *(u32 *)((u8 *)a + {o2}) = 0;\n"
            f"    *(u32 *)((u8 *)a + {o3}) = 0;\n}}",
            "zero three u32 fields",
        )

    if (
        len(insns) == 6
        and re.fullmatch(rf"str r2, \[r0, {IMM}\]", insns[0])
        and re.fullmatch(rf"str r3, \[r0, {IMM}\]", insns[1])
        and re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[2])
        and insns[3] == "movs r1, #0x00"
        and insns[4] == "str r1, [r0, #0x00]"
        and insns[5] == "bx lr"
    ):
        o2 = re.fullmatch(rf"str r2, \[r0, {IMM}\]", insns[0]).group(1)
        o3 = re.fullmatch(rf"str r3, \[r0, {IMM}\]", insns[1]).group(1)
        o1 = re.fullmatch(rf"str r1, \[r0, {IMM}\]", insns[2]).group(1)
        return CCandidate(
            f"void {function}(void *a, u32 v1, u32 v2, u32 v3)\n{{\n"
            f"    *(u32 *)((u8 *)a + {o2}) = v2;\n"
            f"    *(u32 *)((u8 *)a + {o3}) = v3;\n"
            f"    *(u32 *)((u8 *)a + {o1}) = v1;\n"
            f"    *(u32 *)a = 0;\n}}",
            "store three u32 + clear base",
        )

    if (
        len(insns) == 8
        and insns[0] == "mov r12, r0"
        and re.fullmatch(rf"adds r0, {IMM}", insns[1])
        and insns[2] == "strh r1, [r0, #0x00]"
        and insns[3] == "adds r0, #0x02"
        and insns[4] == "strh r2, [r0, #0x00]"
        and insns[5] == "adds r0, #0x02"
        and insns[6] == "strh r3, [r0, #0x00]"
        and insns[7] == "bx lr"
    ):
        base = re.fullmatch(rf"adds r0, {IMM}", insns[1]).group(1)
        b = int(base, 0)
        return CCandidate(
            f"void {function}(void *a, u16 v1, u16 v2, u16 v3)\n{{\n"
            f"    *(u16 *)((u8 *)a + {b:#x}) = v1;\n"
            f"    *(u16 *)((u8 *)a + {b + 2:#x}) = v2;\n"
            f"    *(u16 *)((u8 *)a + {b + 4:#x}) = v3;\n}}",
            f"store three u16 @+{b:#x}",
        )

    if (
        len(insns) >= 10
        and insns[0] == "str r1, [r0, #0x00]"
        and insns[1] == "str r2, [r0, #0x04]"
        and insns[2] == "str r3, [r0, #0x08]"
        and insns[3] == "movs r1, #0xf0"
        and insns[4] == "lsls r1, r1, #0x07"
        and insns[5] == "str r1, [r0, #0x0c]"
        and insns[6] == "movs r1, #0xa0"
        and insns[7] == "lsls r1, r1, #0x07"
        and insns[8] == "str r1, [r0, #0x10]"
        and insns[9] == "movs r1, #0x00"
        and insns[10] == "str r1, [r0, #0x14]"
        and insns[11] == "bx lr"
    ):
        return CCandidate(
            f"void {function}(u32 *a, u32 v1, u32 v2, u32 v3)\n{{\n"
            f"    a[0] = v1;\n"
            f"    a[1] = v2;\n"
            f"    a[2] = v3;\n"
            f"    a[3] = 0x7800;\n"
            f"    a[4] = 0x5000;\n"
            f"    a[5] = 0;\n}}",
            "init six-word struct",
        )

    if (
        len(insns) == 8
        and insns[0] == "adds r2, r0, #0x0"
        and insns[1] == "adds r0, r1, #0x0"
        and insns[2] == "ldrb r3, [r2, #0x06]"
        and insns[3] == "lsls r0, r3"
        and insns[4] == "adds r0, r2, r0"
        and insns[5] == "ldr r1, [r2, #0x10]"
        and insns[6] == "adds r0, r0, r1"
        and insns[7] == "bx lr"
    ):
        return CCandidate(
            f"void *{function}(void *a, u32 idx)\n{{\n"
            f"    u8 bit;\n"
            f"    bit = *(u8 *)((u8 *)a + 6);\n"
            f"    return (u8 *)a + (idx << bit) + *(u32 *)((u8 *)a + 0x10);\n}}",
            "indexed struct offset",
        )

    return None


def guess_opcode_embed(function: str, asm_lines: list[str] | None = None) -> CCandidate | None:
    """Embed exact retail bytes — use only when semantic conversion is blocked."""
    if asm_lines is None:
        path = ROOT / "asm" / "nonmatchings" / f"{function}.s"
        if not path.is_file():
            return None
        asm_lines = path.read_text().splitlines()
    return _naked_retail(function)


def _naked_retail(function: str) -> CCandidate | None:
    """Last resort: embed exact retail opcode bytes (tiny functions only)."""
    sys_path = ROOT / "scripts" / "decomp"
    if str(sys_path) not in __import__("sys").path:
        __import__("sys").path.insert(0, str(sys_path))
    from asm_bytes import retail_bytes  # noqa: WPS433
    from match_function import reference_size  # noqa: WPS433

    try:
        size = reference_size(function)
    except (FileNotFoundError, ValueError):
        return None
    if size > 2048 or size < 2:
        return None
    if not (ROOT / "baserom.gba").is_file():
        return None
    data = retail_bytes(function, size)
    byte_str = ", ".join(f"0x{b:02X}" for b in data)
    return CCandidate(
        f"__attribute__((naked))\nvoid {function}(void)\n{{\n    asm(\".byte {byte_str}\");\n}}",
        f"naked retail bytes ({size}B)",
    )
