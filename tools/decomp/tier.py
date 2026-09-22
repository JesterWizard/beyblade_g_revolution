#!/usr/bin/env python3
"""Single lifecycle vocabulary for decompiled functions.

A function's progress is three *independent* facts, not one ladder position:

    has_c    — a C seed exists (src/matched/ semantic, or src/decompiled/)
    named    — analysis/symbols.json has a confident, evidenced entry
    matches  — compiles byte-identical to retail (matched / identical_diff)

The derived tier is the highest rung reached, so a function that is hard to
byte-match never blocks symbol naming, and a named function never blocks
matching. Both axes progress in parallel.

    UNKNOWN     no C seed at all (readable Thumb only)
    DECOMPILED  a C seed exists, does not match yet
    UNDERSTOOD  named with confidence + evidence, still does not match
    MATCHING    byte-identical to retail

Other tools import these constants instead of hardcoding status strings, so
the vocabulary lives in exactly one place.

  python3 tools/decomp/tier.py            # tier summary
  python3 tools/decomp/tier.py --json     # machine-readable rows
  python3 tools/decomp/tier.py --json --tier DECOMPILED
"""

from __future__ import annotations

import argparse
import json
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"
DECOMPILED = ROOT / "src" / "decompiled"
LEGACY_WIP = ROOT / "src" / "wip"
SYMBOLS_JSON = ROOT / "analysis" / "symbols.json"
MANIFEST = ROOT / "build" / "matched.json"
FUNCTIONS_JSON = ROOT / "docs" / "decomp-functions.json"
VERIFIED = ROOT / "build" / "semantic_verified.json"

# --- tiers (ascending) -------------------------------------------------------

TIER_UNKNOWN = "UNKNOWN"
TIER_DECOMPILED = "DECOMPILED"
TIER_UNDERSTOOD = "UNDERSTOOD"
TIER_MATCHING = "MATCHING"

TIERS: tuple[str, ...] = (
    TIER_UNKNOWN,
    TIER_DECOMPILED,
    TIER_UNDERSTOOD,
    TIER_MATCHING,
)

TIER_RANK: dict[str, int] = {tier: i for i, tier in enumerate(TIERS)}

#: `function_scores` / `match_function` statuses that mean byte-identical.
MATCHING_STATUSES: frozenset[str] = frozenset({"matched", "identical_diff"})

#: Legacy statuses mapped onto their nearest tier rung.
STATUS_TIER: dict[str, str] = {
    "matched": TIER_MATCHING,
    "identical_diff": TIER_MATCHING,
    "same_size": TIER_DECOMPILED,
    "size_mismatch": TIER_DECOMPILED,
    "wip": TIER_DECOMPILED,
    "not_started": TIER_UNKNOWN,
    "blocked": TIER_UNKNOWN,
}

#: Minimum confidence, plus at least one evidence line, before `named` is true.
NAME_CONFIDENCE_THRESHOLD = 0.5


def derive_tier(*, has_c: bool, named: bool, matches: bool) -> str:
    """Highest rung reached. Matching wins: it is the strongest signal."""
    if matches:
        return TIER_MATCHING
    if named:
        return TIER_UNDERSTOOD
    if has_c:
        return TIER_DECOMPILED
    return TIER_UNKNOWN


def tier_for_status(status: str) -> str:
    """Map a legacy per-function status string onto a tier rung."""
    return STATUS_TIER.get(status, TIER_UNKNOWN)


# --- symbol knowledge --------------------------------------------------------


def load_symbols() -> dict[str, dict[str, Any]]:
    """analysis/symbols.json keyed by address, or {} when absent."""
    if not SYMBOLS_JSON.is_file():
        return {}
    try:
        data = json.loads(SYMBOLS_JSON.read_text())
    except json.JSONDecodeError:
        return {}
    return dict(data.get("symbols") or {})


def symbol_for(name: str, symbols: dict[str, dict[str, Any]] | None = None) -> dict[str, Any]:
    """Look up a function's symbol entry by name, via its address key."""
    table = load_symbols() if symbols is None else symbols
    if name in table:
        return table[name]
    addr = f"0x{int(name.replace('sub_', ''), 16):08X}"
    return table.get(addr) or {}


def is_named(entry: dict[str, Any] | None) -> bool:
    """Confident *and* evidenced. A guess without evidence is not a name."""
    if not entry:
        return False
    symbol = str(entry.get("symbol") or "")
    if not symbol:
        return False
    # A symbol that is just the raw label restated is not a name.
    if symbol in {str(a) for a in entry.get("aliases") or []}:
        return False
    if float(entry.get("confidence") or 0.0) < NAME_CONFIDENCE_THRESHOLD:
        return False
    return bool(entry.get("evidence"))


# --- per-function facts ------------------------------------------------------


def _verified_semantic() -> set[str] | None:
    """Names whose C is byte-verified, or None when the audit has not run."""
    if not VERIFIED.is_file():
        return None
    try:
        data = json.loads(VERIFIED.read_text())
    except json.JSONDecodeError:
        return None
    return {
        name
        for name, row in (data.get("functions") or {}).items()
        if float(row.get("pct") or 0.0) >= 100.0
    }


def _status_by_name() -> dict[str, str]:
    if not FUNCTIONS_JSON.is_file():
        return {}
    try:
        data = json.loads(FUNCTIONS_JSON.read_text())
    except json.JSONDecodeError:
        return {}
    out: dict[str, str] = {}
    for row in data.get("functions") or []:
        name = row.get("name")
        if name:
            out[name] = str(row.get("status") or "not_started")
    return out


def _function_names() -> list[str]:
    """Every known function, from the linked manifest then the source trees."""
    names: set[str] = set()
    if MANIFEST.is_file():
        try:
            data = json.loads(MANIFEST.read_text())
            names |= {f["name"] for f in data.get("functions") or [] if f.get("name")}
        except (json.JSONDecodeError, KeyError, TypeError):
            pass
    for base in (MATCHED, DECOMPILED, LEGACY_WIP):
        if base.is_dir():
            names |= {p.stem for p in base.glob("sub_*.c")}
    return sorted(names)


def _matched_has_c(path: Path, verified: set[str] | None) -> bool:
    """A `src/matched` file is a C seed only when it is not a naked asm stub."""
    from opcode_stubs import file_kind  # noqa: WPS433

    kind = file_kind(path)
    if kind != "semantic":
        return False
    if verified is not None and path.stem not in verified:
        return False
    return True


def collect() -> list[dict[str, Any]]:
    """One row per function: the three flags, the derived tier, and the name."""
    verified = _verified_semantic()
    statuses = _status_by_name()
    symbols = load_symbols()
    rows: list[dict[str, Any]] = []

    for name in _function_names():
        matched_path = MATCHED / f"{name}.c"
        has_c = False
        if matched_path.is_file():
            has_c = _matched_has_c(matched_path, verified)
        if not has_c and (DECOMPILED / f"{name}.c").is_file():
            has_c = True
        if not has_c and (LEGACY_WIP / f"{name}.c").is_file():
            has_c = True

        status = statuses.get(name, "not_started")
        entry = symbol_for(name, symbols)
        named = is_named(entry)
        matches = status in MATCHING_STATUSES

        rows.append(
            {
                "name": name,
                "addr": f"0x{int(name.replace('sub_', ''), 16):08X}",
                "has_c": has_c,
                "named": named,
                "matches": matches,
                "status": status,
                "tier": derive_tier(has_c=has_c, named=named, matches=matches),
                "symbol": str(entry.get("symbol") or ""),
                "confidence": float(entry.get("confidence") or 0.0),
                "source": str(entry.get("source") or ""),
            }
        )
    return rows


def summarize(rows: list[dict[str, Any]]) -> dict[str, Any]:
    counts = {tier: 0 for tier in TIERS}
    for row in rows:
        counts[row["tier"]] = counts.get(row["tier"], 0) + 1
    total = len(rows)
    named = sum(1 for r in rows if r["named"])
    return {
        "generated": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
        "total": total,
        "tiers": {
            tier: {
                "functions": counts[tier],
                "pct": round(100.0 * counts[tier] / total, 1) if total else 0.0,
            }
            for tier in TIERS
        },
        "flags": {
            "has_c": sum(1 for r in rows if r["has_c"]),
            "named": named,
            "matches": sum(1 for r in rows if r["matches"]),
        },
        "pct_named": round(100.0 * named / total, 1) if total else 0.0,
    }


def format_human(summary: dict[str, Any]) -> str:
    total = summary["total"]
    lines = [f"=== Function lifecycle ({total} functions) ===", ""]
    for tier in TIERS:
        row = summary["tiers"][tier]
        bar_w = 28
        filled = int(round(bar_w * row["pct"] / 100.0))
        bar = "#" * filled + "." * (bar_w - filled)
        lines.append(f"  {tier:<11} [{bar}] {row['pct']:5.1f}%  {row['functions']:>3}")
    flags = summary["flags"]
    lines += [
        "",
        f"  has C seed   {flags['has_c']:>3}/{total}",
        f"  named        {flags['named']:>3}/{total}  ({summary['pct_named']:.1f}%)",
        f"  byte-matches {flags['matches']:>3}/{total}",
    ]
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true", help="emit full rows as JSON")
    parser.add_argument("--tier", help="filter to one tier (with --json)")
    args = parser.parse_args()

    rows = collect()
    if args.tier:
        rows = [r for r in rows if r["tier"] == args.tier.upper()]

    if args.json:
        print(json.dumps({"summary": summarize(rows), "functions": rows}, indent=2))
        return 0

    print(format_human(summarize(rows)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
