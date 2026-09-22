#!/usr/bin/env python3
"""Per-function decomp score ledger (completion % + N/M bytes).

Statuses:
  matched         — semantic C, match_function MATCH, integrated
  identical_diff  — compiled size matches retail; remaining diffs are only
                    pool/reloc words (byte-identical code, still a DIFF)
  same_size       — same size, instruction bytes differ (near miss)
  size_mismatch   — compiled length != retail
  not_started     — readable Thumb / opcode, no recorded C attempt
  blocked         — documented in docs/decomp-queue.toml (score still shown)
  wip             — unmatched C parked in src/wip/ (resume, do not restart)

  python3 tools/decomp/function_scores.py           # summary
  python3 tools/decomp/function_scores.py --write   # docs/decomp-functions.md
  python3 tools/decomp/function_scores.py --close   # near misses only
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
MATCHED_SRC = ROOT / "src" / "matched"
SCORES_JSON = ROOT / "docs" / "decomp-function-scores.json"
OUT_MD = ROOT / "docs" / "decomp-functions.md"
OUT_JSON = ROOT / "docs" / "decomp-functions.json"
QUEUE_TOML = ROOT / "docs" / "decomp-queue.toml"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import file_kind  # noqa: E402
from progress import function_size  # noqa: E402
from next_queue import _load_toml  # noqa: E402

# "5/108 bytes" after "differ" / "short" → unmatched count, not matched count.
_DIFFER = re.compile(
    r"(?:~)?(\d+)\s*/\s*(\d+)\s*bytes(?:\s+(?:differ|short|missing))?",
    re.I,
)
_SAME_SIZE_SCORE = re.compile(
    r"same-size DIFF,\s*(?:~)?(\d+)\s*/\s*(\d+)\s*bytes",
    re.I,
)
_SAME_SIZE = re.compile(r"(\d+)\s*B\s*=\s*\1\s*B", re.I)
_SIZE_VS = re.compile(
    r"(\d+)\s*B\s+(?:retail\s+)?vs\.?\s+(\d+)\s*B\s+compiled",
    re.I,
)


def _pct(part: int, whole: int) -> float:
    if whole <= 0:
        return 0.0
    return round(100.0 * part / whole, 1)


def _load_attempts() -> dict[str, dict[str, Any]]:
    if not SCORES_JSON.is_file():
        return {}
    try:
        data = json.loads(SCORES_JSON.read_text())
    except json.JSONDecodeError:
        return {}
    return dict(data.get("attempts") or {})


def _seed_from_reason(reason: str, retail: int) -> dict[str, Any] | None:
    """Best-effort score from a queue.toml blocker reason."""
    m = _SAME_SIZE_SCORE.search(reason)
    if m:
        unmatched, total = int(m.group(1)), int(m.group(2))
        if total == retail and unmatched <= total:
            matched = total - unmatched
            return {
                "matched_bytes": matched,
                "retail_bytes": retail,
                "compiled_bytes": retail,
                "pct": _pct(matched, retail),
                "status": "same_size",
                "score": f"{matched}/{retail}",
                "note": "seeded from queue.toml same-size DIFF",
                "seeded": True,
            }
    m = _DIFFER.search(reason)
    if m:
        unmatched, total = int(m.group(1)), int(m.group(2))
        if total == retail and unmatched <= total:
            matched = total - unmatched
            compiled = retail
            kind = "same_size"
            vs = _SIZE_VS.search(reason)
            if vs:
                compiled = int(vs.group(2))
                if compiled != retail:
                    kind = "size_mismatch"
            return {
                "matched_bytes": matched,
                "retail_bytes": retail,
                "compiled_bytes": compiled,
                "pct": _pct(matched, retail),
                "status": kind,
                "score": f"{matched}/{retail}",
                "note": "seeded from queue.toml",
                "seeded": True,
            }
    m = _SIZE_VS.search(reason)
    if m:
        retail_n, compiled = int(m.group(1)), int(m.group(2))
        if retail_n == retail:
            return {
                "matched_bytes": 0,
                "retail_bytes": retail,
                "compiled_bytes": compiled,
                "pct": 0.0,
                "status": "size_mismatch" if compiled != retail else "same_size",
                "score": f"0/{retail}",
                "note": f"seeded size {compiled}B vs {retail}B",
                "seeded": True,
            }
    if _SAME_SIZE.search(reason) and retail:
        return {
            "matched_bytes": 0,
            "retail_bytes": retail,
            "compiled_bytes": retail,
            "pct": 0.0,
            "status": "same_size",
            "score": f"?/{retail}",
            "note": "seeded same-size DIFF (matched-byte count unknown)",
            "seeded": True,
        }
    return None


def collect() -> dict[str, Any]:
    attempts = _load_attempts()
    cfg = _load_toml(QUEUE_TOML)
    blocked = {}
    for row in cfg.get("block") or []:
        name = row.get("name", "")
        if name:
            blocked[name] = row.get("reason", "")
    wip = {}
    for row in cfg.get("wip") or []:
        name = row.get("name", "")
        if name:
            wip[name] = row

    functions: list[dict[str, Any]] = []
    for path in sorted(MATCHED_SRC.glob("sub_*.c")):
        name = path.stem
        kind = file_kind(path)
        try:
            size = function_size(name, path)
        except FileNotFoundError:
            size = 0
        addr = f"0x{int(name.replace('sub_', ''), 16):08X}"
        block_reason = blocked.get(name, "")
        attempt = attempts.get(name)

        if kind == "semantic":
            status = "matched"
            matched_n = size
            compiled_n = size
            pct = 100.0
            score = f"{size}/{size}"
            source = "integrated"
            note = ""
        elif attempt and not attempt.get("seeded"):
            status = attempt.get("status", "not_started")
            matched_n = int(attempt.get("matched_bytes") or 0)
            compiled_n = int(attempt.get("compiled_bytes") or 0)
            pct = float(attempt.get("pct") or _pct(matched_n, size or 1))
            score = attempt.get("score") or f"{matched_n}/{size}"
            source = "attempt"
            note = attempt.get("note") or ""
        else:
            seed = _seed_from_reason(block_reason, size) if block_reason else None
            if attempt and attempt.get("seeded") and not seed:
                seed = attempt
            if seed:
                status = seed.get("status", "not_started")
                matched_n = int(seed.get("matched_bytes") or 0)
                compiled_n = int(seed.get("compiled_bytes") or 0)
                pct = float(seed.get("pct") or 0.0)
                score = seed.get("score") or f"{matched_n}/{size}"
                source = "seed"
                note = seed.get("note") or ""
            else:
                status = "not_started"
                matched_n = 0
                compiled_n = 0
                pct = 0.0
                score = f"0/{size}"
                source = "none"
                note = ""

        display = status
        if name in wip and status != "matched":
            display = "wip"
            if not note:
                note = wip[name].get("status") or wip[name].get("seed", "")
            wip_score = str(wip[name].get("score") or "")
            parsed = re.match(r"(\d+)\s*/\s*(\d+)", wip_score)
            if parsed and matched_n == 0:
                matched_n = int(parsed.group(1))
                score = wip_score
                pct = _pct(matched_n, int(parsed.group(2)) or size or 1)
                if source == "none":
                    source = "wip"
        elif name in blocked and status != "matched":
            display = "blocked"

        functions.append(
            {
                "name": name,
                "addr": addr,
                "kind": kind,
                "status": status,
                "display": display,
                "blocked": name in blocked,
                "wip": name in wip,
                "block_reason": block_reason,
                "retail_bytes": size,
                "matched_bytes": matched_n,
                "compiled_bytes": compiled_n,
                "pct": pct,
                "score": score,
                "source": source,
                "note": note,
            }
        )

    counts: dict[str, int] = {}
    for row in functions:
        counts[row["display"]] = counts.get(row["display"], 0) + 1

    generated = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    return {
        "generated": generated,
        "counts": counts,
        "total": len(functions),
        "functions": functions,
    }


def _status_label(display: str) -> str:
    return {
        "matched": "matched",
        "identical_diff": "byte-identical DIFF",
        "same_size": "same-size DIFF",
        "size_mismatch": "size DIFF",
        "not_started": "not started",
        "blocked": "blocked",
        "wip": "WIP (parked C)",
    }.get(display, display)


def _sort_key(row: dict[str, Any]) -> tuple:
    order = {
        "wip": 0,
        "identical_diff": 1,
        "same_size": 2,
        "size_mismatch": 3,
        "not_started": 4,
        "blocked": 5,
        "matched": 6,
    }
    return (
        order.get(row["display"], 9),
        -row["pct"],
        row["retail_bytes"],
        row["name"],
    )


def render_md(data: dict[str, Any]) -> str:
    counts = data["counts"]
    total = data["total"]
    rows = sorted(data["functions"], key=_sort_key)
    close = [
        r
        for r in rows
        if r["status"] != "matched" and (r["matched_bytes"] > 0 or r["display"] == "wip")
    ]
    close.sort(key=lambda r: (-r["pct"], r["retail_bytes"], r["name"]))
    lines = [
        "# Function scores",
        "",
        "_Auto-generated. Do not edit. Refresh with "
        "`python3 tools/decomp/function_scores.py --write` or `make progress`._",
        "",
        f"_Updated: {data['generated']}_",
        "",
        "## Legend",
        "",
        "| Status | Meaning | Counted as decompiled? |",
        "|--------|---------|------------------------|",
        "| **matched** | Semantic C, `match_function.py` MATCH, integrated | yes |",
        "| **byte-identical DIFF** | Same size as retail; remaining diffs are only "
        "unresolved pool/reloc words | **no** |",
        "| **same-size DIFF** | Same size, instruction bytes differ | no |",
        "| **size DIFF** | Compiled length ≠ retail | no |",
        "| **not started** | Readable Thumb, no C attempt recorded | no |",
        "| **WIP (parked C)** | Unmatched draft in [`src/wip/`](../src/wip/README.md) — resume, do not restart | no |",
        "| **blocked** | Documented in [`decomp-queue.toml`](decomp-queue.toml) | no |",
        "",
        "Score is **matched bytes / retail bytes** (e.g. `68/70`). "
        "Completion % is that ratio. A function that compiles to the same "
        "bytes *except* a literal-pool address is **byte-identical DIFF**, "
        "not matched.",
        "",
        "## Summary",
        "",
        "| Status | Count |",
        "|--------|------:|",
        f"| matched | {counts.get('matched', 0)} |",
        f"| byte-identical DIFF | {counts.get('identical_diff', 0)} |",
        f"| same-size DIFF | {counts.get('same_size', 0)} |",
        f"| size DIFF | {counts.get('size_mismatch', 0)} |",
        f"| WIP (parked C) | {counts.get('wip', 0)} |",
        f"| not started | {counts.get('not_started', 0)} |",
        f"| blocked | {counts.get('blocked', 0)} |",
        f"| **total** | **{total}** |",
        "",
        "## Close / attempted",
        "",
        "| Function | Status | % | Bytes | Note |",
        "|----------|--------|--:|------:|------|",
    ]
    if close:
        for row in close:
            note = row["note"] or row["block_reason"]
            if len(note) > 80:
                note = note[:77] + "…"
            lines.append(
                f"| `{row['name']}` | {_status_label(row['display'])} | "
                f"{row['pct']:.1f}% | {row['score']} | {note} |"
            )
    else:
        lines.append("| _none yet_ | | | | run `match_function.py --record` |")

    lines.extend(
        [
            "",
            f"## All {total} functions",
            "",
            "| Function | Address | Status | % | Bytes | Kind |",
            "|----------|---------|--------|--:|------:|------|",
        ]
    )
    for row in rows:
        lines.append(
            f"| `{row['name']}` | `{row['addr']}` | {_status_label(row['display'])} | "
            f"{row['pct']:.1f}% | {row['score']} | {row['kind']} |"
        )
    lines.append("")
    return "\n".join(lines)


def format_human(data: dict[str, Any], *, close_only: bool = False) -> str:
    counts = data["counts"]
    lines = [
        "=== Function scores ===",
        f"  matched              {counts.get('matched', 0):4d}",
        f"  byte-identical DIFF  {counts.get('identical_diff', 0):4d}",
        f"  same-size DIFF       {counts.get('same_size', 0):4d}",
        f"  size DIFF            {counts.get('size_mismatch', 0):4d}",
        f"  WIP (parked C)       {counts.get('wip', 0):4d}",
        f"  not started          {counts.get('not_started', 0):4d}",
        f"  blocked              {counts.get('blocked', 0):4d}",
        f"  total                {data['total']:4d}",
        "",
    ]
    rows = sorted(data["functions"], key=_sort_key)
    show = [
        r
        for r in rows
        if r["status"] != "matched" and (r["matched_bytes"] > 0 or r["display"] == "wip")
    ]
    show.sort(key=lambda r: (-r["pct"], r["retail_bytes"], r["name"]))
    if not close_only:
        show = show[:30]
    if show:
        lines.append("  Close:")
        for row in show:
            lines.append(
                f"    {row['name']}  {row['score']:10s}  {row['pct']:5.1f}%  "
                f"{_status_label(row['display'])}"
            )
    return "\n".join(lines)


def write_artifacts(data: dict[str, Any]) -> None:
    from doc_write import write_doc

    write_doc(OUT_MD, render_md(data))
    payload = {
        "generated": data["generated"],
        "counts": data["counts"],
        "total": data["total"],
        "functions": data["functions"],
    }
    write_doc(OUT_JSON, json.dumps(payload, indent=2) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--close", action="store_true", help="print attempted/near-miss only")
    args = parser.parse_args()

    data = collect()
    if args.write:
        write_artifacts(data)
    if args.json:
        print(json.dumps(data, indent=2))
        return 0
    print(format_human(data, close_only=args.close))
    if args.write:
        print()
        print(f"  wrote {OUT_MD.relative_to(ROOT)}")
        print(f"  wrote {OUT_JSON.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
