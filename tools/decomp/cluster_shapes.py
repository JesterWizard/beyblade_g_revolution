#!/usr/bin/env python3
"""Cluster remaining readable-Thumb functions by opcode skeleton.

Strips registers/immediates so clones of the same shape surface as one family.
Use this to grow c_patterns.py instead of converting each clone by hand.

  python3 tools/decomp/cluster_shapes.py
  python3 tools/decomp/cluster_shapes.py --min 3 --limit 20
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from classify_semantic_targets import asm_body, classify  # noqa: E402
from opcode_stubs import list_readable_asm  # noqa: E402

_REG = re.compile(r"\b(r1[0-5]|r[0-9]|lr|sp|ip|pc)\b")
_IMM = re.compile(r"#-?(?:0x[0-9A-Fa-f]+|\d+)")
_HEX = re.compile(r"\b0x[0-9A-Fa-f]+\b")
_SUB = re.compile(r"\bsub_08[0-9A-Fa-f]+\b")
_LBL = re.compile(r"\b_08[0-9A-Fa-f]+\b")
_WS = re.compile(r"\s+")


def insn_lines(body: str) -> list[str]:
    out: list[str] = []
    for raw in body.splitlines():
        s = raw.strip()
        if not s or s.startswith(("@", ".")):
            continue
        if s.startswith(".4byte") or s.startswith(".byte"):
            continue
        first = s.split()[0]
        if first.endswith(":"):
            rest = s.split(":", 1)[1].strip()
            if not rest:
                continue
            s = rest
        if s.startswith("."):
            continue
        out.append(s)
    return out


def normalize_insn(line: str) -> str:
    s = line.split("@", 1)[0].strip()
    s = _SUB.sub("FN", s)
    s = _LBL.sub("LBL", s)
    s = _REG.sub("REG", s)
    s = _IMM.sub("IMM", s)
    s = _HEX.sub("HEX", s)
    s = _WS.sub(" ", s)
    return s


def skeleton(body: str) -> str:
    insns = insn_lines(body)
    return "; ".join(normalize_insn(ln) for ln in insns)


def opcode_seq(body: str) -> str:
    ops: list[str] = []
    for ln in insn_lines(body):
        op = ln.split()[0] if ln.split() else ""
        if op:
            ops.append(op)
    return " ".join(ops)


def cluster(names: list[str] | None = None, min_size: int = 2) -> list[dict]:
    if names is None:
        names = list_readable_asm()
    buckets, _missing, _cse = classify()
    skip = set(buckets.get("naked_only") or [])
    groups: dict[str, list[str]] = defaultdict(list)
    opcodes: dict[str, str] = {}
    sizes: dict[str, int] = {}
    for name in names:
        if name in skip:
            continue
        body = asm_body(name)
        key = skeleton(body)
        if not key:
            continue
        groups[key].append(name)
        opcodes[key] = opcode_seq(body)
        sizes[key] = len(insn_lines(body))
    families = []
    for key, members in groups.items():
        if len(members) < min_size:
            continue
        families.append(
            {
                "count": len(members),
                "insns": sizes[key],
                "opcodes": opcodes[key],
                "shape": key,
                "members": sorted(members),
            }
        )
    families.sort(key=lambda r: (-r["count"], r["insns"], r["members"][0]))
    return families


def format_human(families: list[dict], limit: int) -> str:
    lines = [
        f"==> {len(families)} clone families (remaining readable-Thumb, naked_only skipped)"
        if families
        else "==> no clone families",
        "",
    ]
    for i, fam in enumerate(families[:limit]):
        shape = fam["shape"]
        if len(shape) > 160:
            shape = shape[:157] + "..."
        lines.append(f"[{fam['count']}] {fam['insns']} insns  {fam['opcodes'][:80]}")
        lines.append(f"     {shape}")
        shown = ", ".join(fam["members"][:8])
        extra = f" (+{len(fam['members']) - 8})" if len(fam["members"]) > 8 else ""
        lines.append(f"     {shown}{extra}")
        lines.append("")
    if limit < len(families):
        lines.append(f"... {len(families) - limit} more families (raise --limit)")
    return "\n".join(lines).rstrip() + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--min", type=int, default=2, help="minimum family size")
    parser.add_argument("--limit", type=int, default=25, help="families to print")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    families = cluster(min_size=args.min)
    if args.json:
        print(json.dumps(families[: args.limit], indent=2))
        return 0
    print(format_human(families, args.limit), end="")
    if families:
        print()
        print("Next: turn the largest family into one c_patterns.py matcher.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
