#!/usr/bin/env python3
"""Decompilation progress: semantic C vs original function bytes.

Opcode `.byte` embeds are the retail machine code pasted into a C wrapper —
they do not count as decompiled. Readable Thumb is matching asm, not C.

  python3 tools/decomp/progress.py           # human summary
  python3 tools/decomp/progress.py --json
  python3 tools/decomp/progress.py --write   # JSON + SVG + status table
  python3 tools/decomp/progress.py --top 15
"""

from __future__ import annotations

import argparse
import json
import re
from datetime import datetime, timezone
from pathlib import Path
from typing import Any
from xml.sax.saxutils import escape
import sys

ROOT = Path(__file__).resolve().parents[2]
MATCHED_SRC = ROOT / "src" / "matched"
MATCH_ASM = ROOT / "asm" / "matchings"
NON_ASM = ROOT / "asm" / "nonmatchings"
MANIFEST = ROOT / "build" / "matched.json"
STATUS = ROOT / "docs" / "decomp-status.md"
README = ROOT / "README.md"
PROGRESS_JSON = ROOT / "docs" / "decomp-progress.json"
PROGRESS_SVG = ROOT / "docs" / "decomp-progress.svg"

EXPECTED_FUNCTIONS = 633
PHASE_LABEL = "3b in progress — replace opcode stubs with semantic C / readable Thumb"

STATUS_START = "<!-- decomp-progress:start -->"
STATUS_END = "<!-- decomp-progress:end -->"

_SHORT = re.compile(r"^\s*\.short\b", re.M)
_INCBIN = re.compile(
    r'\.incbin\s+"baserom\.gba",\s*0x[0-9A-Fa-f]+,\s*(0x[0-9A-Fa-f]+|\d+)'
)
_HEX_BYTE = re.compile(r"0x[0-9A-Fa-f]{2}")

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import file_kind  # noqa: E402


def _pct(part: int, whole: int, digits: int = 1) -> float:
    if whole <= 0:
        return 0.0
    return round(100.0 * part / whole, digits)


def _parse_int(raw: str) -> int:
    if raw.lower().startswith("0x"):
        return int(raw, 16)
    return int(raw)


def opcode_byte_size(c_path: Path) -> int | None:
    text = c_path.read_text()
    parts = re.findall(r"\.byte\s+([^\"\\]+)", text)
    hexes: list[str] = []
    for part in parts:
        hexes.extend(_HEX_BYTE.findall(part))
    return len(hexes) if hexes else None


def function_size(name: str, c_path: Path | None = None) -> int:
    """Retail function length from matching asm (`.short` / `.incbin`), else `.byte`."""
    for base in (MATCH_ASM, NON_ASM):
        path = base / f"{name}.s"
        if not path.is_file():
            continue
        text = path.read_text()
        match = _INCBIN.search(text)
        if match:
            return _parse_int(match.group(1))
        n_short = len(_SHORT.findall(text))
        if n_short:
            return n_short * 2
    if c_path is not None and c_path.is_file():
        nbytes = opcode_byte_size(c_path)
        if nbytes:
            return nbytes
    raise FileNotFoundError(name)


def _linked_count() -> int:
    if MANIFEST.is_file():
        data = json.loads(MANIFEST.read_text())
        return len(data.get("functions", []))
    if MATCH_ASM.is_dir():
        return len(list(MATCH_ASM.glob("sub_*.s")))
    return 0


def _battle_names() -> set[str]:
    if not NON_ASM.is_dir():
        return set()
    try:
        from battle_scan import score  # noqa: WPS433
    except ImportError:
        return set()
    names: set[str] = set()
    for path in NON_ASM.glob("sub_*.s"):
        n, _, _ = score(path)
        if n:
            names.add(path.stem)
    return names


def collect(top: int = 15) -> dict[str, Any]:
    files = sorted(MATCHED_SRC.glob("sub_*.c")) if MATCHED_SRC.is_dir() else []
    rows: list[dict[str, Any]] = []
    by_kind = {
        "semantic": {"functions": 0, "bytes": 0},
        "asm": {"functions": 0, "bytes": 0},
        "opcode": {"functions": 0, "bytes": 0},
    }
    missing_size = 0
    for path in files:
        kind = file_kind(path)
        try:
            size = function_size(path.stem, path)
        except FileNotFoundError:
            size = 0
            missing_size += 1
        by_kind[kind]["functions"] += 1
        by_kind[kind]["bytes"] += size
        rows.append(
            {
                "name": path.stem,
                "addr": f"0x{int(path.stem.replace('sub_', ''), 16):08X}",
                "kind": kind,
                "bytes": size,
            }
        )

    total_fn = len(files)
    total_bytes = sum(v["bytes"] for v in by_kind.values())
    semantic_fn = by_kind["semantic"]["functions"]
    semantic_bytes = by_kind["semantic"]["bytes"]
    readable_fn = by_kind["asm"]["functions"]
    readable_bytes = by_kind["asm"]["bytes"]
    opcode_fn = by_kind["opcode"]["functions"]
    opcode_bytes = by_kind["opcode"]["bytes"]
    non_blob_fn = semantic_fn + readable_fn
    non_blob_bytes = semantic_bytes + readable_bytes
    linked = _linked_count()
    expected = max(EXPECTED_FUNCTIONS, total_fn, linked)

    for key, bucket in by_kind.items():
        bucket["pct_functions"] = _pct(bucket["functions"], expected)
        bucket["pct_bytes"] = _pct(bucket["bytes"], total_bytes)

    largest_opcode = sorted(
        (r for r in rows if r["kind"] == "opcode"),
        key=lambda r: r["bytes"],
        reverse=True,
    )[:top]

    battle = _battle_names()
    battle_stats = None
    if battle:
        b_kind = {"semantic": 0, "asm": 0, "opcode": 0, "bytes": 0, "semantic_bytes": 0}
        for row in rows:
            if row["name"] not in battle:
                continue
            b_kind[row["kind"]] += 1
            b_kind["bytes"] += row["bytes"]
            if row["kind"] == "semantic":
                b_kind["semantic_bytes"] += row["bytes"]
        battle_n = sum(b_kind[k] for k in ("semantic", "asm", "opcode"))
        battle_stats = {
            "functions": battle_n,
            "semantic": b_kind["semantic"],
            "readable_asm": b_kind["asm"],
            "opcode": b_kind["opcode"],
            "bytes": b_kind["bytes"],
            "semantic_bytes": b_kind["semantic_bytes"],
            "pct_functions": _pct(b_kind["semantic"], battle_n) if battle_n else 0.0,
            "pct_bytes": _pct(b_kind["semantic_bytes"], b_kind["bytes"])
            if b_kind["bytes"]
            else 0.0,
        }

    generated = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    return {
        "generated": generated,
        "phase": PHASE_LABEL,
        "expected_functions": expected,
        "src_matched": total_fn,
        "linked_in_rom": linked,
        "total_bytes": total_bytes,
        "missing_size": missing_size,
        "kinds": {
            "semantic": by_kind["semantic"],
            "readable_asm": by_kind["asm"],
            "opcode": by_kind["opcode"],
        },
        "decomp": {
            "headline": "semantic C vs original function code",
            "functions": semantic_fn,
            "bytes": semantic_bytes,
            "pct_functions": _pct(semantic_fn, expected),
            "pct_bytes": _pct(semantic_bytes, total_bytes),
        },
        "non_blob": {
            "note": "semantic C + readable Thumb (no .byte retail paste)",
            "functions": non_blob_fn,
            "bytes": non_blob_bytes,
            "pct_functions": _pct(non_blob_fn, expected),
            "pct_bytes": _pct(non_blob_bytes, total_bytes),
        },
        "readable_asm": {"functions": readable_fn, "bytes": readable_bytes},
        "opcode": {"functions": opcode_fn, "bytes": opcode_bytes},
        "battle": battle_stats,
        "largest_opcode": largest_opcode,
    }


def _bar(pct: float, width: int = 40) -> str:
    filled = int(round(width * pct / 100.0))
    filled = max(0, min(width, filled))
    return "#" * filled + "." * (width - filled)


def format_human(data: dict[str, Any]) -> str:
    d = data["decomp"]
    nb = data["non_blob"]
    k = data["kinds"]
    expected = data["expected_functions"]
    total_b = data["total_bytes"]
    lines = [
        "=== Beyblade G Revolution decomp ===",
        f"  Decompiled C (functions): {d['pct_functions']:5.1f}%   "
        f"{d['functions']}/{expected}",
        f"  Decompiled C (bytes):     {d['pct_bytes']:5.1f}%   "
        f"{d['bytes']:,}/{total_b:,}",
        f"  [{_bar(d['pct_functions'])}]  {d['pct_functions']:.1f}%  semantic C",
        f"  [{_bar(nb['pct_functions'])}]  {nb['pct_functions']:.1f}%  not opcode",
        "",
        f"  Mix  {k['semantic']['functions']} semantic C  |  "
        f"{k['readable_asm']['functions']} readable Thumb  |  "
        f"{k['opcode']['functions']} opcode embed",
        f"  Linked in ROM: {data['linked_in_rom']}/{expected}",
        f"  Phase: {data['phase']}",
    ]
    battle = data.get("battle")
    if battle:
        lines.append(
            f"  Battle: {battle['semantic']}/{battle['functions']} semantic C "
            f"({battle['pct_functions']:.1f}% fn, {battle['pct_bytes']:.1f}% bytes)"
        )
    return "\n".join(lines)


_SVG_FONT = (
    "font-family='-apple-system,BlinkMacSystemFont,Segoe UI,Helvetica,Arial,sans-serif'"
)
_SVG_MONO = "font-family='ui-monospace,SFMono-Regular,Menlo,Consolas,monospace'"
_COL_C = "#1a7f37"
_COL_ASM = "#0969da"
_COL_OP = "#8c959f"
_COL_TRACK = "#eaeef2"
_COL_TEXT = "#1f2328"
_COL_MUTED = "#656d76"


def _md_bar(pct: float, width: int = 24) -> str:
    filled = int(round(width * pct / 100.0))
    filled = max(0, min(width, filled))
    if pct > 0 and filled == 0:
        filled = 1
    return "█" * filled + "░" * (width - filled)


def _svg_track(x: float, y: float, w: float, h: float) -> str:
    return f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" rx="4" fill="{_COL_TRACK}"/>'


def _svg_fill(x: float, y: float, w: float, h: float, color: str) -> str:
    if w <= 0:
        return ""
    return (
        f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
        f'rx="4" fill="{color}"/>'
    )


def _svg_pct_bar(
    y: float,
    label: str,
    pct: float,
    color: str,
    *,
    x_label: float,
    x_bar: float,
    bar_w: float,
    bar_h: float,
    x_pct: float,
) -> str:
    fill_w = bar_w * max(0.0, min(100.0, pct)) / 100.0
    return (
        f'<text x="{x_label:.0f}" y="{y + 14:.0f}" {_SVG_FONT} font-size="13" fill="{_COL_TEXT}">{escape(label)}</text>'
        + _svg_track(x_bar, y, bar_w, bar_h)
        + _svg_fill(x_bar, y, fill_w, bar_h, color)
        + f'<text x="{x_pct:.0f}" y="{y + 14:.0f}" text-anchor="end" {_SVG_MONO} font-size="13" font-weight="700" fill="{color}">{pct:.1f}%</text>'
    )


def _svg_stack(
    y: float,
    label: str,
    parts: list[tuple[int, str]],
    whole: int,
    *,
    x_label: float,
    x_bar: float,
    bar_w: float,
    bar_h: float,
) -> str:
    chunks = [_svg_track(x_bar, y, bar_w, bar_h)]
    cursor = x_bar
    remaining = bar_w
    for i, (n, color) in enumerate(parts):
        if whole <= 0 or n <= 0:
            continue
        w = bar_w * n / whole
        if i == len(parts) - 1:
            w = remaining
        chunks.append(
            f'<rect x="{cursor:.2f}" y="{y:.2f}" width="{w:.2f}" height="{bar_h:.2f}" fill="{color}"/>'
        )
        cursor += w
        remaining = x_bar + bar_w - cursor
    return (
        f'<text x="{x_label:.0f}" y="{y + 14:.0f}" {_SVG_FONT} font-size="13" fill="{_COL_TEXT}">{escape(label)}</text>'
        + "".join(chunks)
    )


def render_svg(data: dict[str, Any]) -> str:
    d = data["decomp"]
    k = data["kinds"]
    nb = data["non_blob"]
    expected = data["expected_functions"]
    total_b = data["total_bytes"]
    width = 760
    height = 268
    x_label = 16
    x_bar = 200
    bar_w = 460
    bar_h = 18
    x_pct = width - 16
    label = (
        f"Decompiled C {d['pct_functions']:.1f}% functions, "
        f"{d['pct_bytes']:.1f}% bytes "
        f"({d['functions']}/{expected}, {d['bytes']:,}/{total_b:,})"
    )
    mix_fn = [
        (k["semantic"]["functions"], _COL_C),
        (k["readable_asm"]["functions"], _COL_ASM),
        (k["opcode"]["functions"], _COL_OP),
    ]
    mix_b = [
        (k["semantic"]["bytes"], _COL_C),
        (k["readable_asm"]["bytes"], _COL_ASM),
        (k["opcode"]["bytes"], _COL_OP),
    ]
    rows = [
        _svg_pct_bar(56, "Decompiled C — functions", d["pct_functions"], _COL_C,
                     x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h, x_pct=x_pct),
        _svg_pct_bar(86, "Decompiled C — bytes", d["pct_bytes"], _COL_C,
                     x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h, x_pct=x_pct),
        _svg_pct_bar(116, "Not opcode — functions", nb["pct_functions"], _COL_ASM,
                     x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h, x_pct=x_pct),
        _svg_pct_bar(146, "Not opcode — bytes", nb["pct_bytes"], _COL_ASM,
                     x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h, x_pct=x_pct),
        _svg_stack(186, "Function mix", mix_fn, expected,
                   x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h),
        _svg_stack(216, "Byte mix", mix_b, total_b,
                   x_label=x_label, x_bar=x_bar, bar_w=bar_w, bar_h=bar_h),
    ]
    legend_y = 250
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}" role="img" aria-label="{escape(label)}">
  <title>{escape(label)}</title>
  <rect width="{width}" height="{height}" rx="6" fill="#ffffff" stroke="#d0d7de"/>
  <text x="{x_label}" y="28" {_SVG_FONT} font-size="16" font-weight="600" fill="{_COL_TEXT}">Decompiled C vs original</text>
  <text x="{x_pct}" y="28" text-anchor="end" {_SVG_MONO} font-size="16" font-weight="700" fill="{_COL_C}">{d['pct_functions']:.1f}%</text>
  {"".join(rows)}
  <rect x="{x_bar}" y="{legend_y - 9}" width="10" height="10" rx="2" fill="{_COL_C}"/>
  <text x="{x_bar + 16}" y="{legend_y}" {_SVG_FONT} font-size="11" fill="{_COL_MUTED}">semantic C {k['semantic']['functions']}/{expected} ({d['pct_functions']:.1f}%)</text>
  <rect x="{x_bar + 200}" y="{legend_y - 9}" width="10" height="10" rx="2" fill="{_COL_ASM}"/>
  <text x="{x_bar + 216}" y="{legend_y}" {_SVG_FONT} font-size="11" fill="{_COL_MUTED}">readable Thumb {k['readable_asm']['pct_functions']:.1f}%</text>
  <rect x="{x_bar + 380}" y="{legend_y - 9}" width="10" height="10" rx="2" fill="{_COL_OP}"/>
  <text x="{x_bar + 396}" y="{legend_y}" {_SVG_FONT} font-size="11" fill="{_COL_MUTED}">opcode {k['opcode']['pct_functions']:.1f}%</text>
</svg>
"""


def status_table(data: dict[str, Any]) -> str:
    d = data["decomp"]
    nb = data["non_blob"]
    k = data["kinds"]
    expected = data["expected_functions"]
    total_b = data["total_bytes"]
    battle = data.get("battle")
    rows = [
        f"| Metric | Value |",
        f"|--------|-------|",
        f"| Linked in ROM | **{data['linked_in_rom']}/{expected}** (100% peeled) |",
        f"| **Decompiled C (functions)** | **{d['functions']}/{expected} ({d['pct_functions']:.1f}%)** |",
        f"| **Decompiled C (bytes)** | **{d['bytes']:,}/{total_b:,} ({d['pct_bytes']:.1f}%)** |",
        f"| Not opcode (C + readable Thumb) | {nb['functions']}/{expected} ({nb['pct_functions']:.1f}% fn, {nb['pct_bytes']:.1f}% bytes) |",
        f"| Readable Thumb | {k['readable_asm']['functions']}/{expected} ({k['readable_asm']['pct_functions']:.1f}%) |",
        f"| Opcode `.byte` embeds | {k['opcode']['functions']}/{expected} ({k['opcode']['pct_functions']:.1f}%) |",
        f"| `src/matched/*.c` | {data['src_matched']}/{expected} |",
        f"| Phase | **{data['phase']}** |",
    ]
    if battle:
        rows.append(
            f"| Battle semantic C | {battle['semantic']}/{battle['functions']} "
            f"({battle['pct_functions']:.1f}% fn, {battle['pct_bytes']:.1f}% bytes) |"
        )
    rows.append(
        f"| Counter | [`decomp-progress.svg`](decomp-progress.svg) · "
        f"[`decomp-progress.json`](decomp-progress.json) · "
        f"[`decomp-functions.md`](decomp-functions.md) |"
    )
    body = "\n".join(rows)
    return f"{STATUS_START}\n{body}\n{STATUS_END}\n"


def readme_section(data: dict[str, Any]) -> str:
    d = data["decomp"]
    nb = data["non_blob"]
    k = data["kinds"]
    expected = data["expected_functions"]
    total_b = data["total_bytes"]
    linked_pct = _pct(data["linked_in_rom"], expected)
    battle = data.get("battle")
    rows = [
        (
            "Decompiled C (functions)",
            d["pct_functions"],
            f"{d['functions']}/{expected}",
        ),
        (
            "Decompiled C (bytes)",
            d["pct_bytes"],
            f"{d['bytes']:,}/{total_b:,}",
        ),
        (
            "Not opcode (functions)",
            nb["pct_functions"],
            f"{nb['functions']}/{expected}",
        ),
        (
            "Not opcode (bytes)",
            nb["pct_bytes"],
            f"{nb['bytes']:,}/{total_b:,}",
        ),
        (
            "Linked in ROM",
            linked_pct,
            f"{data['linked_in_rom']}/{expected}",
        ),
    ]
    table = [
        "| Metric | | Percent | Count |",
        "| :--- | :--- | ---: | ---: |",
    ]
    for name, pct, count in rows:
        table.append(f"| {name} | `{_md_bar(pct, 32)}` | **{pct:.1f}%** | {count} |")

    mix = [
        "| Kind | Functions | Bytes |",
        "| :--- | ---: | ---: |",
        f"| Semantic C | {k['semantic']['functions']} ({k['semantic']['pct_functions']:.1f}%) | "
        f"{k['semantic']['bytes']:,} ({k['semantic']['pct_bytes']:.1f}%) |",
        f"| Readable Thumb | {k['readable_asm']['functions']} ({k['readable_asm']['pct_functions']:.1f}%) | "
        f"{k['readable_asm']['bytes']:,} ({k['readable_asm']['pct_bytes']:.1f}%) |",
        f"| Opcode embed | {k['opcode']['functions']} ({k['opcode']['pct_functions']:.1f}%) | "
        f"{k['opcode']['bytes']:,} ({k['opcode']['pct_bytes']:.1f}%) |",
    ]
    mermaid = (
        "```mermaid\n"
        "xychart-beta\n"
        '    title "Decompiled C vs original (%)"\n'
        '    x-axis ["C functions", "C bytes", "Not opcode (fn)", "Not opcode (bytes)"]\n'
        '    y-axis "Percent" 0 --> 100\n'
        f"    bar [{d['pct_functions']:.1f}, {d['pct_bytes']:.1f}, "
        f"{nb['pct_functions']:.1f}, {nb['pct_bytes']:.1f}]\n"
        "```"
    )

    battle_line = ""
    if battle:
        battle_line = (
            f"\n\nBattle: **{battle['pct_functions']:.1f}%** functions / "
            f"**{battle['pct_bytes']:.1f}%** bytes in semantic C "
            f"({battle['semantic']}/{battle['functions']}; "
            f"{battle['opcode']} opcode left).\n"
        )
    return (
        f"{STATUS_START}\n\n"
        f"Decompiled C is **{d['pct_functions']:.1f}%** of functions "
        f"({d['functions']}/{expected}) and **{d['pct_bytes']:.1f}%** of original "
        f"function bytes ({d['bytes']:,}/{total_b:,}).\n\n"
        + "\n".join(table)
        + "\n\n"
        + mermaid
        + "\n\n"
        + "![Decompiled C vs original](docs/decomp-progress.svg)\n\n"
        + "\n".join(mix)
        + battle_line
        + "\nOpcode `.byte` embeds are the retail machine code and do not count as "
        "decompiled C. Readable Thumb is matching asm. Unmatched ROM ranges stay "
        "`.incbin`'d from `baserom.gba` so `make compare` can stay green. "
        "Refresh with `python3 tools/decomp/progress.py --write` or `make progress`. "
        "Per-function scores: [`docs/decomp-functions.md`](docs/decomp-functions.md).\n"
        + f"\n{STATUS_END}\n"
    )


def _patch_marked(path: Path, block: str, *, heading: str, fallback_end: str | None) -> None:
    if not path.is_file():
        path.write_text(f"# {path.stem}\n\n{heading}\n\n{block}")
        return
    text = path.read_text()
    if STATUS_START in text and STATUS_END in text:
        pre, rest = text.split(STATUS_START, 1)
        _, post = rest.split(STATUS_END, 1)
        path.write_text(pre.rstrip() + "\n\n" + block.strip() + "\n\n" + post.lstrip("\n"))
        return
    if heading in text:
        pre, rest = text.split(heading, 1)
        rest = rest.lstrip("\n")
        if fallback_end and fallback_end in rest:
            _, post = rest.split(fallback_end, 1)
            path.write_text(
                pre.rstrip()
                + "\n\n"
                + heading
                + "\n\n"
                + block.strip()
                + "\n\n"
                + fallback_end
                + post
            )
            return
        path.write_text(pre.rstrip() + "\n\n" + heading + "\n\n" + block.strip() + "\n\n" + rest)
        return
    path.write_text(text.rstrip() + f"\n\n{heading}\n\n{block}")


def patch_status_md(data: dict[str, Any]) -> None:
    _patch_marked(
        STATUS,
        status_table(data),
        heading="## Progress",
        fallback_end="## Batch log",
    )


def patch_readme(data: dict[str, Any]) -> None:
    _patch_marked(
        README,
        readme_section(data),
        heading="## Status",
        fallback_end="## Quick start",
    )


def _history_point(data: dict[str, Any]) -> dict[str, Any]:
    return {
        "generated": data["generated"],
        "semantic": data["decomp"]["functions"],
        "readable_asm": data["kinds"]["readable_asm"]["functions"],
        "opcode": data["kinds"]["opcode"]["functions"],
        "semantic_bytes": data["decomp"]["bytes"],
        "total_bytes": data["total_bytes"],
        "pct_functions": data["decomp"]["pct_functions"],
        "pct_bytes": data["decomp"]["pct_bytes"],
    }


def merge_history(data: dict[str, Any]) -> list[dict[str, Any]]:
    point = _history_point(data)
    hist: list[dict[str, Any]] = []
    if PROGRESS_JSON.is_file():
        try:
            prev = json.loads(PROGRESS_JSON.read_text())
            hist = list(prev.get("history") or [])
        except json.JSONDecodeError:
            hist = []
    keys = ("semantic", "readable_asm", "opcode", "semantic_bytes")
    if hist and all(hist[-1].get(k) == point.get(k) for k in keys):
        hist[-1] = point
    else:
        hist.append(point)
    return hist[-200:]


def write_artifacts(data: dict[str, Any]) -> None:
    payload = dict(data)
    payload["history"] = merge_history(data)
    PROGRESS_JSON.parent.mkdir(parents=True, exist_ok=True)
    PROGRESS_JSON.write_text(json.dumps(payload, indent=2) + "\n")
    PROGRESS_SVG.write_text(render_svg(data))
    patch_status_md(data)
    patch_readme(data)
    try:
        from next_queue import collect as queue_collect, write_artifacts as queue_write

        queue_write(queue_collect())
    except Exception:
        pass
    try:
        from function_scores import collect as scores_collect, write_artifacts as scores_write

        scores_write(scores_collect())
    except Exception:
        pass


def refresh(top: int = 15) -> dict[str, Any]:
    data = collect(top=top)
    write_artifacts(data)
    return data


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true", help="print JSON to stdout")
    parser.add_argument(
        "--write",
        action="store_true",
        help="write JSON + SVG and patch README.md / decomp-status.md",
    )
    parser.add_argument("--top", type=int, default=15, help="largest remaining opcode stubs")
    args = parser.parse_args()

    data = collect(top=args.top)
    if args.write:
        write_artifacts(data)
    if args.json:
        print(json.dumps(data, indent=2))
        return 0
    print(format_human(data))
    if args.top and data.get("largest_opcode"):
        print()
        print(f"  Largest remaining opcode stubs (top {args.top}):")
        for row in data["largest_opcode"]:
            print(f"    {row['bytes']:5d} B  {row['name']}")
    if args.write:
        print()
        print(f"  wrote {PROGRESS_JSON.relative_to(ROOT)}")
        print(f"  wrote {PROGRESS_SVG.relative_to(ROOT)}")
        print(f"  patched {STATUS.relative_to(ROOT)}")
        print(f"  patched {README.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
