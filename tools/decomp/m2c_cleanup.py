#!/usr/bin/env python3
"""Deterministic cleanup of m2c output for agbcc matching C.

Rewrites M2C_FIELD / offset-casts toward struct members, replaces IWRAM/EWRAM
literals with ram_map names, strips m2c prototypes and `?` types. Does not
claim a MATCH — callers still run match_function.py.

  python3 tools/decomp/m2c_cleanup.py sub_08030938
  python3 tools/decomp/m2c_cleanup.py --stdin sub_08030938 < seed.c
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from unknown_types import struct_exists, struct_from_function, unk_name  # noqa: E402

RAM_MAP = ROOT / "include" / "ram_map.h"
RAM_POOL = ROOT / "include" / "ram_map_pool.h"

_DEREF = re.compile(
    r"#define\s+(\w+)\s+\(\*\(([^)]+)\)(0x[0-9A-Fa-f]+)\)"
)
_LOC = re.compile(
    r"#define\s+(\w+)\s+\(\(([^)]+)\)(0x[0-9A-Fa-f]+)\)"
)
_CONST = re.compile(r"#define\s+(\w+)\s+(0x[0-9A-Fa-f]+)\s*(?:/\*.*)?$")
_M2C_FIELD = re.compile(
    r"M2C_FIELD\(([^()]+),\s*([^,]+?)\s*,\s*(0x[0-9A-Fa-f]+|\d+)\)"
)
_OFFSET_CAST = re.compile(
    r"\*\(\s*(u8|u16|u32|s8|s16|s32|void\s*\*)\s*\*\s*\)\s*"
    r"\(\s*(?:\(u8\s*\*\)\s*)?(\w+)\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)"
)
_UNK_FIELD = re.compile(r"->unk([0-9A-Fa-f]+)\b")
_RAM_HEX = re.compile(r"0x0[23][0-9A-Fa-f]{6,7}")
_STAR_CAST_ADDR = re.compile(
    r"\*\(\s*(?:const\s+)?(?:void|u8|u16|u32|s8|s16|s32)\s*\*+\s*\)\s*"
    r"(0x0[23][0-9A-Fa-f]{6,7})"
)
_Q_DECL = re.compile(r"(?<![\w?])\?(?=\s+\w)")
_EXTERN_LINE = re.compile(
    r"^\s*(?:\?|M2C_UNK|[A-Za-z_][\w\s\*]*)\s+\w+\s*\([^;]*\)\s*;\s*(?:/\*\s*extern\s*\*/)?\s*$"
)
_WARN = re.compile(r"^\s*/\*\s*Warning:.*\*/\s*$")
_Q_PTR = re.compile(r"\?\s*\*")
_Q_TYPE = re.compile(r"\b\?\b")
_BITCAST = re.compile(r"BITCAST\s*\(\s*([^,]+)\s*,\s*(.*?)\s*\)")
_ARG0_VOID = re.compile(
    r"^((?:void|s32|u32|s16|u16|s8|u8)\s+\w+\s*\()\s*void\s*\*\s*(arg0)\s*([,)])",
    re.M,
)


def _prefer_name(old: str | None, new: str) -> str:
    if old is None:
        return new
    old_unk = old.startswith("gUnk_")
    new_unk = new.startswith("gUnk_")
    if old_unk and not new_unk:
        return new
    if new_unk and not old_unk:
        return old
    # Prefer shorter named symbols (gBattleWork over gBattleWorkPtrLoc noise)
    if len(new) < len(old):
        return new
    return old


def load_ram_maps() -> tuple[dict[int, str], dict[int, str]]:
    """addr → deref-macro name, addr → address-constant name."""
    deref: dict[int, str] = {}
    const: dict[int, str] = {}
    for path in (RAM_POOL, RAM_MAP):
        if not path.is_file():
            continue
        for line in path.read_text().splitlines():
            stripped = line.strip()
            if stripped.startswith("#undef"):
                continue
            m = _DEREF.search(stripped)
            if m:
                name, _typ, addr = m.groups()
                val = int(addr, 16)
                deref[val] = _prefer_name(deref.get(val), name)
                continue
            m = _LOC.search(stripped)
            if m:
                name, _typ, addr = m.groups()
                val = int(addr, 16)
                # Loc is the address of a pointer; use as const fallback.
                const[val] = _prefer_name(const.get(val), name)
                continue
            m = _CONST.match(stripped)
            if m:
                name, addr = m.groups()
                val = int(addr, 16)
                const[val] = _prefer_name(const.get(val), name)
    return deref, const


def _rewrite_m2c_fields(text: str) -> str:
    prev = None
    while prev != text:
        prev = text
        text = _M2C_FIELD.sub(
            lambda m: f"{m.group(1).strip()}->{unk_name(_parse_off(m.group(3)))}",
            text,
        )
    return text


def _parse_off(raw: str) -> int:
    return int(raw, 0)


def _rewrite_offset_casts(text: str) -> str:
    def repl(m: re.Match[str]) -> str:
        expr = m.group(2)
        off = _parse_off(m.group(3))
        return f"{expr}->{unk_name(off)}"

    return _OFFSET_CAST.sub(repl, text)


def _normalize_unk(text: str) -> str:
    def repl(m: re.Match[str]) -> str:
        try:
            return "->" + unk_name(int(m.group(1), 16))
        except ValueError:
            return m.group(0)

    return _UNK_FIELD.sub(repl, text)


def _replace_ram(text: str, deref: dict[int, str], const: dict[int, str]) -> str:
    def star_repl(m: re.Match[str]) -> str:
        addr = int(m.group(1), 16)
        if addr not in deref:
            return m.group(0)
        name = deref[addr]
        if re.search(r"\(\s*(?:s32|u32)\s*\*\s*\)", m.group(0)):
            return f"(s32){name}"
        return name

    text = _STAR_CAST_ADDR.sub(star_repl, text)

    def hex_repl(m: re.Match[str]) -> str:
        addr = int(m.group(0), 16)
        if addr in const:
            return const[addr]
        if addr in deref:
            # leftover bare address of a deref global → Loc if present, else hex
            loc = const.get(addr)
            return loc if loc else m.group(0)
        return m.group(0)

    return _RAM_HEX.sub(hex_repl, text)


def _strip_m2c_chrome(text: str, function: str) -> str:
    kept: list[str] = []
    for line in text.splitlines():
        if _WARN.match(line):
            continue
        if "/* extern */" in line:
            continue
        if _EXTERN_LINE.match(line) and function not in line.split("(")[0]:
            continue
        if line.strip().startswith("#include") and "m2c" in line:
            continue
        kept.append(line)
    return "\n".join(kept).strip()


def _fix_question_types(text: str) -> str:
    text = _Q_PTR.sub("void *", text)
    text = _Q_DECL.sub("s32", text)
    text = _Q_TYPE.sub("s32", text)
    text = text.replace("M2C_UNK", "s32")
    return text


def _retype_arg0(text: str, function: str) -> str:
    st = struct_from_function(function)
    if not struct_exists(st):
        return text

    def repl(m: re.Match[str]) -> str:
        return f"{m.group(1)}struct {st} *{m.group(2)}{m.group(3)}"

    return _ARG0_VOID.sub(repl, text, count=1)


def _bitcast(text: str) -> str:
    prev = None
    while prev != text:
        prev = text
        text = _BITCAST.sub(r"(\1)(\2)", text)
    return text


def cleanup_text(text: str, function: str) -> str:
    """Return a cleaned C fragment (function definition, no #include)."""
    deref, const = load_ram_maps()
    text = _strip_m2c_chrome(text, function)
    text = _bitcast(text)
    text = _rewrite_m2c_fields(text)
    text = _rewrite_offset_casts(text)
    text = _fix_question_types(text)
    text = _normalize_unk(text)
    text = _replace_ram(text, deref, const)
    text = _retype_arg0(text, function)
    text = re.sub(r"\n{3,}", "\n\n", text).strip()
    return text + "\n"


def cleanup_function(function: str, valid_syntax: bool = False) -> str | None:
    from m2c_asm import m2c_decompile  # noqa: WPS433

    raw = m2c_decompile(function, valid_syntax=valid_syntax)
    if not raw:
        return None
    return cleanup_text(raw, function)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("--valid-syntax", action="store_true")
    parser.add_argument(
        "--stdin",
        action="store_true",
        help="clean stdin instead of running m2c",
    )
    args = parser.parse_args()

    if args.stdin:
        raw = sys.stdin.read()
        print(cleanup_text(raw, args.function), end="")
        return 0

    out = cleanup_function(args.function, valid_syntax=args.valid_syntax)
    if not out:
        print(f"m2c failed for {args.function}", file=sys.stderr)
        return 1
    print(out, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
