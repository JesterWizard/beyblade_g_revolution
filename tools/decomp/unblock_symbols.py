#!/usr/bin/env python3
"""Draft unknown-functions.h prototypes for bare `bl _080XXXXXX` labels.

Guesses arity from registers written in the few instructions before each call.
Default is dry-run. Use --write to append missing lines.

  python3 tools/decomp/unblock_symbols.py
  python3 tools/decomp/unblock_symbols.py --write
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HEADER = ROOT / "include" / "unknown-functions.h"
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from classify_semantic_targets import asm_body, classify, declared_symbols  # noqa: E402

_DST = re.compile(
    r"\b(?:movs?|adds?|subs?|ldr|ldrb|ldrh|ldrsh|ldrsb|mov)\s+(r[0-3])\b"
)
_BL = re.compile(r"\bbl\s+(_[0-9A-Fa-f]{7,8})\b")


def _arity_at_call(lines: list[str], idx: int) -> int:
    window = lines[max(0, idx - 12) : idx]
    seen: set[int] = set()
    for ln in window:
        m = _DST.search(ln)
        if m:
            seen.add(int(m.group(1)[1:]))
    if not seen:
        return 1
    return max(seen) + 1


def guess_prototypes() -> dict[str, dict]:
    _buckets, missing_by_symbol, _cse = classify()
    declared = declared_symbols()
    out: dict[str, dict] = {}
    for sym, callers in missing_by_symbol.items():
        if sym in declared:
            continue
        arities: list[int] = []
        for caller in callers:
            body = asm_body(caller)
            lines = body.splitlines()
            for i, ln in enumerate(lines):
                m = _BL.search(ln)
                if m and m.group(1) == sym:
                    arities.append(_arity_at_call(lines, i))
        arity = max(arities) if arities else 1
        arity = min(max(arity, 1), 4)
        params = ", ".join(f"s32 a{i}" for i in range(arity))
        decl = f"s32 {sym}({params});"
        out[sym] = {
            "decl": decl,
            "arity": arity,
            "callers": callers,
        }
    return out


def format_human(rows: dict[str, dict]) -> str:
    if not rows:
        return "no missing bare-label prototypes\n"
    lines = [f"==> {len(rows)} undeclared bl-target(s)\n"]
    for sym, info in sorted(rows.items(), key=lambda kv: -len(kv[1]["callers"])):
        n = len(info["callers"])
        shown = ", ".join(info["callers"][:5])
        extra = f" (+{n - 5})" if n > 5 else ""
        lines.append(f"{info['decl']}  /* {n} caller(s): {shown}{extra} */")
    lines.append("")
    lines.append("Dry-run only. Re-run with --write to append to unknown-functions.h")
    return "\n".join(lines) + "\n"


def write_header(rows: dict[str, dict]) -> int:
    if not rows:
        return 0
    text = HEADER.read_text()
    existing = declared_symbols()
    block = []
    for sym, info in sorted(rows.items()):
        if sym in existing or info["decl"] in text:
            continue
        block.append(info["decl"])
    if not block:
        return 0
    marker = "#endif /* GUARD_UNKNOWN_FUNCTIONS_H */"
    addition = (
        "\n/* auto-drafted by unblock_symbols.py — check arity before relying */\n"
        + "\n".join(block)
        + "\n\n"
    )
    if marker not in text:
        HEADER.write_text(text.rstrip() + "\n" + addition)
    else:
        HEADER.write_text(text.replace(marker, addition + marker))
    return len(block)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--write",
        action="store_true",
        help="append missing prototypes to include/unknown-functions.h",
    )
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    rows = guess_prototypes()
    if args.json:
        import json

        print(json.dumps(rows, indent=2))
        return 0
    print(format_human(rows), end="")
    if args.write:
        n = write_header(rows)
        print(f"wrote {n} prototype(s) to {HEADER.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
