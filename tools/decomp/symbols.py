#!/usr/bin/env python3
"""The symbol knowledge layer: names live in data, not in source.

`analysis/symbols.json` is the single source of truth for what a function is
called. Source files, headers, and config are all generated *views* of it, so
re-running a naming pass is never destructive and a wrong name is always cheap
to revert.

Every entry carries provenance and evidence:

    source      AUTO    derived mechanically (RAM symbol reuse, etc.)
                AI      proposed by a model pass, with stated evidence
                HUMAN   confirmed or written by hand

A pass may never overwrite an entry from a *higher* provenance. That is the
property that makes iterative, automated naming safe.

Names reach the compiler as macros, never as renamed symbols:

    #define GetItem sub_08012340

so `src/matched/sub_08012340.c` reads as `u16 GetItem(s32 a)` while the
preprocessor still emits the `sub_08012340` symbol. The ROM, the linker script,
and `make compare` are untouched by construction.

  python3 tools/decomp/symbols.py list
  python3 tools/decomp/symbols.py set sub_0802B8BC --symbol GetItemData \\
      --confidence 0.8 --source ai --evidence "returns a u16 from a table"
  python3 tools/decomp/symbols.py generate
  python3 tools/decomp/symbols.py check
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from datetime import date, datetime, timezone
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
SYMBOLS_JSON = ROOT / "analysis" / "symbols.json"
SYMBOLS_H = ROOT / "include" / "symbols.h"
TOML = ROOT / "beyblade_g_revolution.toml"
INCLUDE = ROOT / "include"

# --- provenance --------------------------------------------------------------

SOURCE_AUTO = "auto"
SOURCE_AI = "ai"
SOURCE_HUMAN = "human"

#: Higher rank wins. A lower-or-equal-provenance write never clobbers a higher.
SOURCE_RANK: dict[str, int] = {SOURCE_AUTO: 0, SOURCE_AI: 1, SOURCE_HUMAN: 2}

#: Below this confidence an entry is recorded but never emitted as a macro.
EMIT_CONFIDENCE = 0.5

_C_KEYWORDS = frozenset(
    """
    auto break case char const continue default do double else enum extern float
    for goto if inline int long register restrict return short signed sizeof
    static struct switch typedef union unsigned void volatile while
    """.split()
)

_DEFINE = re.compile(r"^\s*#\s*define\s+([A-Za-z_]\w*)", re.M)
# Single-line only: a negated class would happily span newlines and pull field
# names out of a multi-line typedef, which would over-reserve identifiers.
_TYPEDEF = re.compile(r"^\s*typedef\b[^;\n]*?([A-Za-z_]\w*)\s*;", re.M)
_TAG = re.compile(r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)", re.M)
_SUB_LABEL = re.compile(r"^sub_[0-9A-Fa-f]{8}$")


# --- storage -----------------------------------------------------------------


def load() -> dict[str, Any]:
    if not SYMBOLS_JSON.is_file():
        return {"symbols": {}}
    try:
        data = json.loads(SYMBOLS_JSON.read_text())
    except json.JSONDecodeError:
        return {"symbols": {}}
    data.setdefault("symbols", {})
    return data


def save(data: dict[str, Any]) -> None:
    SYMBOLS_JSON.parent.mkdir(parents=True, exist_ok=True)
    data["count"] = len(data["symbols"])
    data["generated"] = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    SYMBOLS_JSON.write_text(json.dumps(data, indent=2, sort_keys=True) + "\n")


def key_for(name: str) -> str:
    """Accept `sub_XXXXXXXX` or `0xXXXXXXXX` and return the canonical key."""
    if name.lower().startswith("0x"):
        return f"0x{int(name, 16):08X}"
    if name.startswith("sub_"):
        return f"0x{int(name[4:], 16):08X}"
    if re.fullmatch(r"[0-9A-Fa-f]{8}", name):
        return f"0x{int(name, 16):08X}"
    raise ValueError(f"not a function label or address: {name}")


def label_for(key: str) -> str:
    return f"sub_{key[2:].upper()}"


# --- reserved identifiers ----------------------------------------------------


def reserved_names() -> set[str]:
    """Identifiers already defined by the headers; a macro must not shadow one.

    `include/symbols.h` is excluded: it is this tool's own output, so counting
    it would make every emitted alias collide with itself.
    """
    names: set[str] = set(_C_KEYWORDS)
    if not INCLUDE.is_dir():
        return names
    for path in sorted(INCLUDE.rglob("*.h")):
        if path.resolve() == SYMBOLS_H.resolve():
            continue
        text = path.read_text(errors="replace")
        names |= set(_DEFINE.findall(text))
        names |= set(_TYPEDEF.findall(text))
        names |= set(_TAG.findall(text))
    return names


# --- collision detection -----------------------------------------------------


def detect_collisions(data: dict[str, Any]) -> list[dict[str, str]]:
    """Problems that must stop a macro from being emitted."""
    problems: list[dict[str, str]] = []
    reserved = reserved_names()

    seen: dict[str, str] = {}
    for key, entry in sorted(data["symbols"].items()):
        symbol = str(entry.get("symbol") or "")
        if not symbol:
            continue
        if _SUB_LABEL.match(symbol):
            problems.append(
                {"key": key, "symbol": symbol, "reason": "symbol is a raw label"}
            )
            continue
        if symbol in _C_KEYWORDS:
            problems.append(
                {"key": key, "symbol": symbol, "reason": "C keyword"}
            )
            continue
        if symbol in reserved:
            problems.append(
                {"key": key, "symbol": symbol, "reason": "already defined in include/"}
            )
            continue
        if symbol in seen:
            problems.append(
                {
                    "key": key,
                    "symbol": symbol,
                    "reason": f"duplicate of {seen[symbol]}",
                }
            )
            continue
        seen[symbol] = key
    return problems


def emit_set(data: dict[str, Any]) -> tuple[dict[str, str], list[dict[str, str]]]:
    """(key -> symbol) that are safe to emit, plus everything skipped."""
    problems = detect_collisions(data)
    blocked = {p["key"] for p in problems}
    emitted: dict[str, str] = {}
    for key, entry in sorted(data["symbols"].items()):
        if key in blocked:
            continue
        symbol = str(entry.get("symbol") or "")
        if not symbol:
            continue
        if float(entry.get("confidence") or 0.0) < EMIT_CONFIDENCE:
            continue
        if not entry.get("evidence"):
            continue
        emitted[key] = symbol
    return emitted, problems


# --- generated views ---------------------------------------------------------

_HEADER = """#ifndef GUARD_SYMBOLS_H
#define GUARD_SYMBOLS_H

/*
 * AUTO-GENERATED by tools/decomp/symbols.py - do not edit.
 *
 * Readable names for named functions. Each alias expands to the real link
 * label, so the preprocessor emits `sub_XXXXXXXX` exactly as before and
 * `make compare` is unaffected by naming.
 *
 * Names live in analysis/symbols.json. Regenerate with `make symbols`.
 */

"""


def render_header(emitted: dict[str, str], problems: list[dict[str, str]]) -> str:
    lines = [_HEADER]
    if emitted:
        for key, symbol in emitted.items():
            lines.append(f"#define {symbol} {label_for(key)}\n")
    else:
        lines.append("/* No symbols emitted yet. */\n")

    if problems:
        lines.append(
            "\n/*\n * Skipped (not emitted as macros):\n"
        )
        for problem in problems:
            lines.append(
                f" *   {label_for(problem['key'])} -> {problem['symbol']}"
                f"  ({problem['reason']})\n"
            )
        lines.append(" */\n")

    lines.append("\n#endif // GUARD_SYMBOLS_H\n")
    return "".join(lines)


def render_toml(data: dict[str, Any]) -> str:
    """Regenerate only the `[renames]` block, preserving everything else."""
    text = TOML.read_text() if TOML.is_file() else ""
    rows = []
    for key, entry in sorted(data["symbols"].items()):
        symbol = str(entry.get("symbol") or "")
        if symbol:
            rows.append(f'{label_for(key)} = "{symbol}"')

    body = "\n".join(rows)
    block = f"[renames]\n{body}\n" if body else "[renames]\n"

    lines = text.splitlines(keepends=True)
    out: list[str] = []
    skipping = False
    seen_renames = False
    for line in lines:
        stripped = line.strip()
        is_section = stripped.startswith("[") and stripped.endswith("]")
        if is_section and stripped == "[renames]":
            skipping = True
            seen_renames = True
            out.append(block)
            continue
        if is_section and skipping:
            skipping = False
        if not skipping:
            out.append(line)

    if not seen_renames:
        if out and not out[-1].endswith("\n"):
            out.append("\n")
        out.append("\n" + block)

    return "".join(out)


def generate(data: dict[str, Any] | None = None) -> dict[str, Any]:
    data = load() if data is None else data
    emitted, problems = emit_set(data)
    SYMBOLS_H.write_text(render_header(emitted, problems))
    TOML.write_text(render_toml(data))
    return {"emitted": len(emitted), "skipped": len(problems), "problems": problems}


# --- mutation ----------------------------------------------------------------


def put(
    data: dict[str, Any],
    key: str,
    *,
    symbol: str,
    confidence: float,
    source: str,
    evidence: list[str],
    kind: str = "function",
) -> tuple[bool, str]:
    """Store a name, refusing to downgrade provenance. Returns (written, why)."""
    source = source.lower()
    incoming = SOURCE_RANK.get(source)
    if incoming is None:
        return False, f"unknown provenance: {source}"

    existing = data["symbols"].get(key)
    if existing:
        current = SOURCE_RANK.get(str(existing.get("source") or "").lower(), -1)
        if current > incoming:
            return False, (
                f"refused: {existing.get('source')} entry "
                f"({existing.get('symbol')}) outranks {source}"
            )

    data["symbols"][key] = {
        "symbol": symbol,
        "aliases": [label_for(key)],
        "kind": kind,
        "confidence": round(float(confidence), 2),
        "source": source,
        "evidence": list(evidence),
        "updated": date.today().isoformat(),
    }
    return True, "written"


def remove(data: dict[str, Any], key: str) -> bool:
    return data["symbols"].pop(key, None) is not None


# --- cli ---------------------------------------------------------------------


def cmd_list(args: argparse.Namespace) -> int:
    data = load()
    rows = sorted(data["symbols"].items())
    if not rows:
        print("no symbols recorded — see tools/decomp/symbols.py --help")
        return 0
    print(f"{'address':<12} {'symbol':<28} {'source':<7} {'conf':>5}  evidence")
    for key, entry in rows:
        evidence = (entry.get("evidence") or [""])[0]
        print(
            f"{key:<12} {str(entry.get('symbol')):<28} "
            f"{str(entry.get('source')):<7} {float(entry.get('confidence') or 0):>5.2f}  "
            f"{evidence[:44]}"
        )
    return 0


def cmd_set(args: argparse.Namespace) -> int:
    data = load()
    try:
        key = key_for(args.name)
    except ValueError as exc:
        print(exc, file=sys.stderr)
        return 2

    written, why = put(
        data,
        key,
        symbol=args.symbol,
        confidence=args.confidence,
        source=args.source,
        evidence=args.evidence or [],
        kind=args.kind,
    )
    print(f"{label_for(key)} -> {args.symbol}: {why}")
    if not written:
        return 1
    save(data)
    result = generate(data)
    print(f"  generated {SYMBOLS_H.relative_to(ROOT)} ({result['emitted']} macros)")
    return 0


def cmd_unset(args: argparse.Namespace) -> int:
    data = load()
    key = key_for(args.name)
    if not remove(data, key):
        print(f"no symbol for {label_for(key)}")
        return 1
    save(data)
    generate(data)
    print(f"removed {label_for(key)}")
    return 0


def cmd_generate(_: argparse.Namespace) -> int:
    result = generate()
    print(f"=== symbols ===")
    print(f"  macros emitted  {result['emitted']}")
    print(f"  skipped         {result['skipped']}")
    for problem in result["problems"]:
        print(
            f"    {label_for(problem['key'])} -> {problem['symbol']}"
            f"  ({problem['reason']})"
        )
    print(f"  wrote {SYMBOLS_H.relative_to(ROOT)}")
    print(f"  wrote [renames] in {TOML.relative_to(ROOT)}")
    return 0


def cmd_check(_: argparse.Namespace) -> int:
    data = load()
    problems = detect_collisions(data)
    total = len(data["symbols"])
    if not problems:
        print(f"ok: {total} symbols, no collisions")
        return 0
    print(f"{len(problems)} collision(s) among {total} symbols:")
    for problem in problems:
        print(
            f"  {label_for(problem['key'])} -> {problem['symbol']}"
            f"  ({problem['reason']})"
        )
    return 1


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="cmd")

    sub.add_parser("list", help="list recorded symbols")

    p_set = sub.add_parser("set", help="record a name")
    p_set.add_argument("name", help="sub_XXXXXXXX or 0xXXXXXXXX")
    p_set.add_argument("--symbol", required=True)
    p_set.add_argument("--confidence", type=float, default=0.5)
    p_set.add_argument(
        "--source", default=SOURCE_AI, type=str.lower,
        choices=[SOURCE_AUTO, SOURCE_AI, SOURCE_HUMAN]
    )
    p_set.add_argument("--evidence", action="append")
    p_set.add_argument("--kind", default="function")

    p_unset = sub.add_parser("unset", help="drop a name")
    p_unset.add_argument("name")

    sub.add_parser("generate", help="write include/symbols.h + [renames]")
    sub.add_parser("check", help="report collisions")

    args = ap.parse_args()
    if args.cmd in (None, "list"):
        return cmd_list(args)
    if args.cmd == "set":
        return cmd_set(args)
    if args.cmd == "unset":
        return cmd_unset(args)
    if args.cmd == "generate":
        return cmd_generate(args)
    if args.cmd == "check":
        return cmd_check(args)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
