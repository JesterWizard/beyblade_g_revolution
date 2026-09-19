#!/usr/bin/env python3
"""Categorize the remaining readable-Thumb functions for semantic-C conversion.

Instruction count alone is a bad difficulty signal (see docs/decomp-semantic-plan.md
for the story): the shortest functions are often ARM/Thumb interworking veneers or
raw variadic-stack trampolines that *must* stay naked asm, while a 40-line function
with a fully-typed struct can be a clean 10-minute conversion.

This buckets every not-yet-semantic function (src/matched/*.c still naked asm) by
real risk signals:

  - naked_only        : provably can't become plain C (mode-switch / stack-splice
                        trampolines) — skip, don't spend time here.
  - unblock_first      : calls a bare-label symbol (bl _XXXXXXXX) with no prototype
                        anywhere yet. Fastest lever: declare the symbol once in
                        include/unknown-functions.h (name + guessed signature from
                        the call site's register usage), which unblocks every
                        caller in one shot. Grouped by the missing symbol.
  - high_reg_pressure  : touches r8-r12 (mov rX, r8/r9/r10/r12). agbcc's register
                        allocator is picky here — hand-written C can drift a few
                        bytes even when logically correct (see sub_0802C62C /
                        sub_0802DEA0 in docs/decomp-status.md). Budget permuter
                        time, don't expect first-try matches.
  - small_clean        : <=40 real instructions, no r8-r12, no unresolved calls.
                        Best ROI — start here.
  - large              : >40 real instructions. Bigger state machines; still
                        doable but budget more time per function.

Usage:
    python3 tools/decomp/classify_semantic_targets.py            # summary counts
    python3 tools/decomp/classify_semantic_targets.py --bucket small_clean
    python3 tools/decomp/classify_semantic_targets.py --json > plan.json
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"
HEADERS = [ROOT / "include" / "unknown-functions.h", ROOT / "include" / "ram_map.h"]

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import list_readable_asm  # noqa: E402

CALL_RE = re.compile(r"\bbl (sub_[0-9A-Fa-f]{8}|_[0-9A-Fa-f]{8})\b")
HIGH_REG_RE = re.compile(r"\b(r8|r9|r10|r12)\b")
NAKED_MARKERS = (
    "mov pc, lr",
    "push {r0, r1, r2, r3}",  # variadic arg spill trampoline
)

# "reload base pointer, then load a field from it" repeated 3+ times = retail
# deliberately re-reads a cached global/struct pointer across sibling if-blocks
# instead of hoisting it. agbcc's -O2 CSE will happily hoist that read the first
# time your C repeats the same `expr->field` textually, producing a byte-exact
# LOGIC match that's still a few bytes short structurally (see sub_0802DEA0 in
# docs/decomp-status.md). Register-agnostic on purpose.
CSE_RISK_RE = re.compile(
    r"ldr r\d+, \[r\d+, #0x00\]\nldr r\d+, \[r\d+, #0x[0-9A-Fa-f]+\]"
)


def declared_symbols() -> set[str]:
    out: set[str] = set()
    for hdr in HEADERS:
        if not hdr.is_file():
            continue
        text = hdr.read_text()
        for m in re.finditer(r"\b(sub_[0-9A-Fa-f]{8}|_[0-9A-Fa-f]{8})\s*\(", text):
            out.add(m.group(1))
    return out


STRING_LIT_RE = re.compile(r'"((?:[^"\\]|\\.)*)"')


def asm_body(name: str) -> str:
    """Extract the asm(...) call's text, normalized to one real-newline-joined blob.

    Two source styles exist in src/matched/*.c: one big "...\\n...\\n" literal
    (the \\n is the two-char escape sequence, meaning "newline" once the C
    string is unescaped), or several adjacent "...\\n" literals — one per
    asm line, relying on C string-literal concatenation. Unescape every
    string literal inside the asm(...) parens and join with a real newline
    either way, so downstream regexes (instruction counting, CSE-risk
    detection, call-target extraction) see one consistent shape and a real
    line/word boundary between instructions regardless of source style.
    """
    text = (MATCHED / f"{name}.c").read_text()
    call = re.search(r"asm\(\s*(.*?)\s*\);", text, re.S)
    if not call:
        return text
    parts = STRING_LIT_RE.findall(call.group(1))
    if not parts:
        return text
    unescaped = [p.replace("\\n", "\n").replace('\\"', '"').replace("\\\\", "\\") for p in parts]
    return "\n".join("\n".join(p.splitlines()) for p in unescaped)


def real_insn_count(body: str) -> int:
    lines = [ln for ln in body.splitlines() if ln.strip() and not ln.strip().startswith("@")]
    return sum(1 for ln in lines if ":" not in ln and not ln.strip().startswith("."))


def classify() -> dict[str, list[str]]:
    names = list_readable_asm()
    declared = declared_symbols()
    all_matched_stems = {p.stem for p in MATCHED.glob("sub_*.c")}

    buckets: dict[str, list[str]] = {
        "naked_only": [],
        "unblock_first": [],
        "high_reg_pressure": [],
        "small_clean": [],
        "large": [],
    }
    missing_by_symbol: dict[str, list[str]] = {}
    cse_risk: list[str] = []

    for n in names:
        body = asm_body(n)

        if any(marker in body for marker in NAKED_MARKERS):
            buckets["naked_only"].append(n)
            continue

        if len(CSE_RISK_RE.findall(body)) >= 3:
            cse_risk.append(n)

        calls = set(CALL_RE.findall(body))
        missing = {
            c
            for c in calls
            if c not in declared
            and c not in all_matched_stems
            and not (MATCHED / f"{c}.c").exists()
        }
        if missing:
            buckets["unblock_first"].append(n)
            for sym in missing:
                missing_by_symbol.setdefault(sym, []).append(n)
            continue

        n_insns = real_insn_count(body)
        high_regs = bool(HIGH_REG_RE.search(body))

        if high_regs:
            buckets["high_reg_pressure"].append(n)
        elif n_insns <= 40:
            buckets["small_clean"].append(n)
        else:
            buckets["large"].append(n)

    return buckets, missing_by_symbol, cse_risk


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--bucket", help="print just this bucket's function names")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--symbols", action="store_true", help="show missing-symbol groups")
    parser.add_argument("--cse-risk", action="store_true", help="show repeated-reload CSE-risk functions")
    args = parser.parse_args()

    buckets, missing_by_symbol, cse_risk = classify()

    if args.cse_risk:
        if args.json:
            print(json.dumps(cse_risk))
        else:
            for n in cse_risk:
                print(n)
        return 0

    if args.symbols:
        if args.json:
            print(json.dumps(missing_by_symbol, indent=2))
        else:
            for sym, callers in sorted(missing_by_symbol.items(), key=lambda kv: -len(kv[1])):
                print(f"{sym:12s} blocks {len(callers):3d} callers: {', '.join(callers[:6])}"
                      + (" ..." if len(callers) > 6 else ""))
        return 0

    if args.bucket:
        names = buckets.get(args.bucket)
        if names is None:
            print(f"error: unknown bucket {args.bucket!r} (have: {', '.join(buckets)})", file=sys.stderr)
            return 1
        if args.json:
            print(json.dumps(names))
        else:
            for n in names:
                print(n)
        return 0

    if args.json:
        out = {k: len(v) for k, v in buckets.items()}
        out["cse_risk_flagged"] = len(cse_risk)
        print(json.dumps(out, indent=2))
    else:
        total = sum(len(v) for v in buckets.values())
        print(f"remaining readable-Thumb: {total}")
        for k, v in buckets.items():
            print(f"  {k:18s} {len(v):4d}")
        print(f"  {'cse_risk (tag)':18s} {len(cse_risk):4d}  (cuts across the buckets above)")
        print()
        print("Recommended order: unblock_first (symbols) -> small_clean -> large -> high_reg_pressure")
        print("Never: naked_only (structurally can't become plain C)")
        print("Before hand-writing anything: check --cse-risk; if flagged, budget permuter time")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
