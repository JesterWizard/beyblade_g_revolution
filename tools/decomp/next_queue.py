#!/usr/bin/env python3
"""Rank functions still needing semantic C; write docs/decomp-queue.{md,json}.

Phase 3b: every function is linked, but readable Thumb is not decompiled C.
Use this queue to pick the next batch without scanning the tree.

  python3 tools/decomp/next_queue.py           # print top picks
  python3 tools/decomp/next_queue.py --write   # refresh docs/decomp-queue.*
  python3 tools/decomp/next_queue.py --json -n 20
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
MATCHED = ROOT / "src" / "matched"
NON = ROOT / "asm" / "nonmatchings"
MATCH_ASM = ROOT / "asm" / "matchings"
CONFIG = ROOT / "docs" / "decomp-queue.toml"
OUT_MD = ROOT / "docs" / "decomp-queue.md"
OUT_JSON = ROOT / "docs" / "decomp-queue.json"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import file_kind  # noqa: E402
from progress import function_size  # noqa: E402

_TABLE_ROW = re.compile(r"^\[\[(pin|block|wip)\]\]\s*$", re.M)
_KV = re.compile(r'^(\w+)\s*=\s*"([^"]*)"\s*$')
_KV_BARE = re.compile(r"^(\w+)\s*=\s*(\S+)\s*$")


def _load_toml(path: Path) -> dict[str, Any]:
    empty = {
        "settings": {"top": 40, "prefer": "battle"},
        "pin": [],
        "block": [],
        "wip": [],
    }
    if not path.is_file():
        return empty
    try:
        import toml  # type: ignore

        data = toml.load(path)
    except ImportError:
        data = _parse_minimal_toml(path.read_text())
    settings = data.get("settings") or {}
    return {
        "settings": {
            "top": int(settings.get("top", 40)),
            "prefer": str(settings.get("prefer", "battle")),
        },
        "pin": list(data.get("pin") or []),
        "block": list(data.get("block") or []),
        "wip": list(data.get("wip") or []),
    }


def _parse_minimal_toml(text: str) -> dict[str, Any]:
    """Subset parser for [[pin]] / [[block]] / [[wip]] tables when `toml` is missing."""
    out: dict[str, Any] = {"settings": {}, "pin": [], "block": [], "wip": []}
    section: str | None = None
    table: dict[str, str] = {}
    for raw in text.splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        if line == "[settings]":
            _flush_table(out, section, table)
            section, table = "settings", {}
            continue
        m = _TABLE_ROW.match(line)
        if m:
            _flush_table(out, section, table)
            section, table = m.group(1), {}
            continue
        for pat in (_KV, _KV_BARE):
            km = pat.match(line)
            if km:
                table[km.group(1)] = km.group(2)
                break
    _flush_table(out, section, table)
    return out


def _flush_table(out: dict[str, Any], section: str | None, table: dict[str, str]) -> None:
    if not section or not table:
        return
    if section == "settings":
        out["settings"] = table
    else:
        out.setdefault(section, []).append(dict(table))


def _asm_path(name: str) -> Path | None:
    for base in (NON, MATCH_ASM):
        path = base / f"{name}.s"
        if path.is_file():
            return path
    return None


def _asm_stats(name: str) -> dict[str, Any]:
    path = _asm_path(name)
    if path is None:
        return {"insns": 0, "bl": 0, "has_pool": False}
    text = path.read_text()
    lines = text.splitlines()
    insns = sum(
        1
        for ln in lines
        if ln.strip()
        and not ln.strip().startswith(("@", ".", "_"))
        and ":" not in ln.strip()
    )
    bl = sum(1 for ln in lines if " bl " in f" {ln} " or ln.strip().startswith("bl "))
    return {"insns": insns, "bl": bl, "has_pool": ".4byte" in text}


def _battle_refs(name: str) -> tuple[int, list[str]]:
    path = _asm_path(name)
    if path is None:
        return 0, []
    try:
        from battle_scan import score  # noqa: WPS433

        n, _, hits = score(path)
        return n, hits
    except ImportError:
        return 0, []


def _addr(name: str) -> str:
    return f"0x{int(name.replace('sub_', ''), 16):08X}"


def collect() -> dict[str, Any]:
    cfg = _load_toml(CONFIG)
    settings = cfg["settings"]
    prefer = settings.get("prefer", "battle")
    top_n = int(settings.get("top", 40))

    pin_rows = []
    for i, row in enumerate(cfg.get("pin") or []):
        name = row.get("name", "")
        if name:
            pin_rows.append({"name": name, "note": row.get("note", ""), "order": i})

    blocked: dict[str, str] = {}
    for row in cfg.get("block") or []:
        name = row.get("name", "")
        if name:
            blocked[name] = row.get("reason", "")

    wip_cfg: list[dict[str, Any]] = []
    wip_names: set[str] = set()
    for row in cfg.get("wip") or []:
        name = row.get("name", "")
        if name:
            wip_names.add(name)
            wip_cfg.append(row)

    pending: list[dict[str, Any]] = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        kind = file_kind(path)
        if kind == "semantic":
            continue
        name = path.stem
        try:
            size = function_size(name, path)
        except FileNotFoundError:
            size = 0
        battle_n, battle_syms = _battle_refs(name)
        asm = _asm_stats(name)
        score = asm["insns"] + asm["bl"] * 3
        pending.append(
            {
                "name": name,
                "addr": _addr(name),
                "kind": kind,
                "bytes": size,
                "score": score,
                "battle_refs": battle_n,
                "battle_syms": battle_syms[:4],
                "has_pool": asm["has_pool"],
                "blocked": name in blocked,
                "block_reason": blocked.get(name, ""),
            }
        )

    def rank_key(row: dict[str, Any]) -> tuple:
        if prefer == "smallest":
            return (row["bytes"], row["score"], -row["battle_refs"], row["name"])
        if prefer == "all":
            return (-row["battle_refs"], row["bytes"], row["score"], row["name"])
        # battle: refs desc, then smaller / easier
        return (-row["battle_refs"], row["bytes"], row["score"], row["name"])

    auto = sorted(
        (r for r in pending if not r["blocked"] and r["name"] not in wip_names),
        key=rank_key,
    )

    pin_names = [p["name"] for p in pin_rows]
    pinned: list[dict[str, Any]] = []
    seen: set[str] = set()
    by_name = {r["name"]: r for r in pending}

    for pin in pin_rows:
        name = pin["name"]
        seen.add(name)
        base = by_name.get(name)
        if base:
            row = dict(base)
            row["pin_note"] = pin.get("note", "")
            pinned.append(row)
        else:
            pinned.append(
                {
                    "name": name,
                    "addr": _addr(name),
                    "kind": "done",
                    "bytes": 0,
                    "pin_note": pin.get("note", ""),
                    "note": "already semantic C",
                }
            )

    recommended: list[dict[str, Any]] = []
    for row in pinned:
        if row.get("kind") != "done":
            recommended.append(row)
    for row in auto:
        if row["name"] in seen:
            continue
        recommended.append(row)
        seen.add(row["name"])
        if len(recommended) >= top_n:
            break

    battle_pending = [r for r in pending if r["battle_refs"] > 0 and not r["blocked"]]
    battle_semantic = 0
    for path in MATCHED.glob("sub_*.c"):
        if file_kind(path) != "semantic":
            continue
        n, _ = _battle_refs(path.stem)
        if n:
            battle_semantic += 1

    block_list = []
    for name, reason in sorted(blocked.items()):
        base = by_name.get(name)
        block_list.append(
            {
                "name": name,
                "addr": _addr(name),
                "reason": reason,
                "kind": base["kind"] if base else "missing",
                "bytes": base["bytes"] if base else 0,
            }
        )

    wip_list = []
    for row in wip_cfg:
        name = row.get("name", "")
        base = by_name.get(name)
        wip_list.append(
            {
                "name": name,
                "addr": _addr(name) if name.startswith("sub_") else "",
                "kind": base["kind"] if base else "missing",
                "bytes": base["bytes"] if base else 0,
                "seed": row.get("seed", f"src/wip/{name}.c"),
                "notes": row.get("notes", f"src/wip/{name}.md"),
                "status": row.get("status", ""),
                "next": row.get("next", ""),
                "score": row.get("score", ""),
            }
        )

    generated = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    return {
        "generated": generated,
        "settings": {"top": top_n, "prefer": prefer},
        "summary": {
            "pending": len(pending),
            "semantic_done": len(list(MATCHED.glob("sub_*.c"))) - len(pending),
            "readable_asm": sum(1 for r in pending if r["kind"] == "asm"),
            "opcode": sum(1 for r in pending if r["kind"] == "opcode"),
            "battle_pending": len(battle_pending),
            "battle_semantic": battle_semantic,
            "blocked": len(block_list),
            "wip": len(wip_list),
        },
        "pinned": pinned,
        "wip": wip_list,
        "recommended": recommended[:top_n],
        "blocked": block_list,
        "backlog": auto,
    }


def _fmt_row(row: dict[str, Any]) -> str:
    kind = row.get("kind", "?")
    refs = row.get("battle_refs", 0)
    pool = "pool" if row.get("has_pool") else "    "
    note = row.get("pin_note") or row.get("note") or ""
    sym = ", ".join(row.get("battle_syms") or [])[:48]
    extra = f" — {note}" if note else ""
    sym_part = f" ({sym})" if sym else ""
    return (
        f"| `{row['name']}` | `{row.get('addr', '')}` | {row.get('bytes', 0)} | "
        f"{refs} | {pool} | {kind} |{sym_part}{extra} |"
    )


def render_md(data: dict[str, Any]) -> str:
    s = data["summary"]
    pref = data["settings"]["prefer"]
    top = data["settings"]["top"]
    lines = [
        "# Decompilation queue",
        "",
        "_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); "
        "refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._",
        "",
        f"_Updated: {data['generated']}_",
        "",
        "## Summary",
        "",
        "| Metric | Count |",
        "|--------|------:|",
        f"| Semantic C done | {s['semantic_done']} |",
        f"| Still need semantic C | **{s['pending']}** |",
        f"| Readable Thumb remaining | {s['readable_asm']} |",
        f"| Opcode embeds remaining | {s['opcode']} |",
        f"| Battle pending | {s['battle_pending']} ({s['battle_semantic']} already semantic) |",
        f"| Blocked (documented) | {s['blocked']} |",
        f"| WIP (resume these first) | {s.get('wip', 0)} |",
        "",
        f"Ranking: **{pref}** · showing top **{top}**",
        "",
        "Park unmatched C in [`src/wip/`](../src/wip/README.md) — see [`decomp-wip.md`](decomp-wip.md).",
        "",
    ]
    wip_rows = data.get("wip") or []
    if wip_rows:
        lines.extend(
            [
                "## Resume (WIP)",
                "",
                "_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._",
                "",
                "| Function | Bytes | Score | Seed | Status | Next |",
                "|----------|------:|-------|------|--------|------|",
            ]
        )
        for row in wip_rows:
            lines.append(
                f"| `{row['name']}` | {row.get('bytes', 0)} | {row.get('score', '')} | "
                f"`{row.get('seed', '')}` | {row.get('status', '')} | {row.get('next', '')} |"
            )
        lines.extend(["", "Per-function notes: `src/wip/<fn>.md`.", ""])

    lines.extend(
        [
            "## Recommended next",
            "",
            "| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |",
            "|----------|---------|------:|------------:|:----:|------|-------|",
        ]
    )
    if data["recommended"]:
        for row in data["recommended"]:
            lines.append(_fmt_row(row))
    else:
        lines.append("| _none_ | | | | | | All functions are semantic C |")

    if data["pinned"]:
        lines.extend(
            [
                "",
                "## Pinned (manual)",
                "",
                "| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |",
                "|----------|---------|------:|------------:|:----:|------|-------|",
            ]
        )
        for row in data["pinned"]:
            lines.append(_fmt_row(row))

    if data["blocked"]:
        lines.extend(
            [
                "",
                "## Blocked",
                "",
                "| Function | Address | Bytes | Reason |",
                "|----------|---------|------:|--------|",
            ]
        )
        for row in data["blocked"]:
            lines.append(
                f"| `{row['name']}` | `{row['addr']}` | {row['bytes']} | {row['reason']} |"
            )

    lines.extend(
        [
            "",
            "## Commands",
            "",
            "```bash",
            "make queue                              # refresh this file",
            "python3 tools/decomp/next_queue.py -n 10",
            "python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c --status \"…\" --next \"…\"",
            "python3 tools/decomp/match_function.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c",
            "python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate",
            "python3 tools/decomp/function_scores.py --close",
            "python3 tools/decomp/c_patterns.py --list",
            "python3 tools/decomp/battle_scan.py -n 20",
            "tools/decomp/battle_semantic_batch.sh 10",
            "tools/decomp/semantic_convert_batch.sh 30 --pool-free-only",
            "```",
            "",
            f"Full ranked backlog ({len(data['backlog'])} functions): [`decomp-queue.json`](decomp-queue.json)",
            "",
            "Patterns: [`decomp-patterns.md`](decomp-patterns.md)",
            "",
        ]
    )
    return "\n".join(lines)


def format_human(data: dict[str, Any], n: int) -> str:
    s = data["summary"]
    lines = [
        "=== Decomp queue (needs semantic C) ===",
        f"  Pending: {s['pending']}  (battle: {s['battle_pending']}, "
        f"blocked: {s['blocked']}, wip: {s.get('wip', 0)})",
        f"  Prefer: {data['settings']['prefer']}  top {n}",
        "",
        "  Resume (WIP):",
    ]
    wip_rows = data.get("wip") or []
    if wip_rows:
        for row in wip_rows:
            lines.append(
                f"    {row['name']}  {row.get('score', '')}  {row.get('seed', '')}  "
                f"next: {row.get('next', '')}"
            )
    else:
        lines.append("    (none)")
    lines.extend(
        [
            "",
            "  Recommended next:",
        ]
    )
    for row in data["recommended"][:n]:
        pin = " [pin]" if row.get("pin_note") else ""
        pool = " pool" if row.get("has_pool") else ""
        refs = row.get("battle_refs", 0)
        lines.append(
            f"    {row['name']}  {row.get('bytes', 0):4d}B  "
            f"battle={refs}{pool}{pin}"
        )
    return "\n".join(lines)


def write_artifacts(data: dict[str, Any]) -> None:
    OUT_MD.write_text(render_md(data))
    OUT_JSON.write_text(json.dumps(data, indent=2) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-n", type=int, default=0, help="limit printed rows (default: settings.top)")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--write", action="store_true", help="write docs/decomp-queue.md + .json")
    args = parser.parse_args()

    data = collect()
    n = args.n or data["settings"]["top"]

    if args.write:
        write_artifacts(data)

    if args.json:
        payload = dict(data)
        payload["recommended"] = data["recommended"][:n]
        print(json.dumps(payload, indent=2))
        return 0

    print(format_human(data, n))
    if args.write:
        print()
        print(f"  wrote {OUT_MD.relative_to(ROOT)}")
        print(f"  wrote {OUT_JSON.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
