#!/usr/bin/env python3
"""Deterministic subsystem membership for decompiled functions.

Seeded from hardware address ranges, named RAM symbols, and the hand-written
`note` field in `build/matched.json` — never from a guess. Everything carries
the evidence that produced it, so a wrong grouping is auditable and cheap to
correct rather than an article of faith.

Membership is decided in two passes:

  1. direct   — the function references an address owned by a subsystem, or its
                recorded note names one.
  2. derived  — an unassigned function inherits the subsystem shared by the
                majority of its call neighbours, when that majority is strong.
                Always marked `derived`, never mixed in silently.

  python3 tools/decomp/systems.py            # membership summary
  python3 tools/decomp/systems.py --json
  python3 tools/decomp/systems.py --system battle
"""

from __future__ import annotations

import argparse
from collections import Counter
from typing import Any

# --- hardware / RAM ranges that identify a subsystem -------------------------

#: Inclusive (lo, hi) address spans owned by each subsystem. Order matters:
#: the first range that matches wins, so the audio block is listed before the
#: broader graphics register window that contains it.
SYSTEM_RANGES: dict[str, list[tuple[int, int]]] = {
    "input": [(0x04000130, 0x04000133)],
    "dma": [(0x040000B0, 0x040000E0)],
    "audio": [(0x04000060, 0x040000A8)],
    "graphics": [
        (0x04000000, 0x0400005F),  # DISPCNT / BG / OBJ registers
        (0x05000000, 0x050003FF),  # palette
        (0x06000000, 0x06017FFF),  # VRAM
        (0x07000000, 0x070003FF),  # OAM
    ],
    "save": [(0x0E000000, 0x0E00FFFF)],
}

#: Global roots referenced by most functions. They identify no subsystem, so
#: they are excluded from evidence (see the `notes` block in systems.json).
UNIVERSAL_SYMBOLS: tuple[str, ...] = ("gMainWorkPtr", "gMainWork")

#: Named RAM symbols that imply a subsystem, from `asm/ram_map_*.s`.
#: `gMainWorkPtr` is deliberately absent: it is the global root every function
#: reaches through, so it identifies nothing.
SYSTEM_SYMBOLS: dict[str, tuple[str, ...]] = {
    "battle": (
        "gBattleWork",
        "gBtl",
        "gBattlerArena",
    ),
    "save": ("Flash", "Sram", "SRAM"),
}

#: Substrings in `build/matched.json` notes that hint at a subsystem.
#: Notes are *weak* evidence: the field is also used for batch bookkeeping
#: ("battle/readable-thumb", "semantic C"), so a hit only ever produces a
#: derived assignment, never a direct one.
SYSTEM_NOTE_HINTS: dict[str, tuple[str, ...]] = {
    "battle": ("battle", "btl"),
    "audio": ("sound", "audio", "gax", "bgm", "music", "sfx"),
    "graphics": ("gfx", "graphic", "sprite", "palette", "vram", "render", "draw"),
    "save": ("save", "sram", "flash"),
    "input": ("input", "key"),
    "menu": ("menu", "ui", "screen", "title"),
}

#: Notes that are integration bookkeeping rather than subsystem evidence.
_BATCH_NOTE_MARKERS: tuple[str, ...] = (
    "readable-thumb",
    "readable thumb",
    "semantic c",
    "semantic draft",
    "phase 3b",
    "semantic/",
    "m2c",
    "opcode",
    "empty stub",
)

#: Minimum share of call neighbours that must agree before inheriting.
INHERIT_RATIO = 0.7
INHERIT_MIN_NEIGHBOURS = 3


def _in_ranges(addr: int, ranges: list[tuple[int, int]]) -> bool:
    return any(lo <= addr <= hi for lo, hi in ranges)


def note_system(note: str) -> tuple[str | None, list[str]]:
    """Subsystem hinted by a hand-written note, ignoring batch labels."""
    lowered = (note or "").lower()
    if not lowered:
        return None, []
    if any(marker in lowered for marker in _BATCH_NOTE_MARKERS):
        return None, []
    for system, hints in SYSTEM_NOTE_HINTS.items():
        for hint in hints:
            if hint in lowered:
                return system, [f"note mentions {hint!r}"]
    return None, []


def classify_direct(
    *,
    ram_refs: list[int],
    ram_names: list[str],
) -> tuple[str | None, list[str]]:
    """Objective subsystem evidence only: named RAM symbols, then hardware."""
    for system, needles in SYSTEM_SYMBOLS.items():
        for needle in needles:
            for name in sorted(ram_names):
                if name.startswith(needle):
                    return system, [f"references {name}"]

    for system, ranges in SYSTEM_RANGES.items():
        hits = [a for a in ram_refs if _in_ranges(a, ranges)]
        if hits:
            shown = ", ".join(f"0x{a:08X}" for a in sorted(hits)[:2])
            return system, [f"hardware ref {shown}"]

    return None, []


def inherit(
    assigned: dict[str, str],
    neighbours: dict[str, set[str]],
) -> dict[str, tuple[str, list[str]]]:
    """Derived membership for functions with no direct evidence."""
    out: dict[str, tuple[str, list[str]]] = {}
    for name, peers in neighbours.items():
        if name in assigned:
            continue
        known = [p for p in peers if p in assigned]
        if not known:
            continue
        votes: Counter[str] = Counter(assigned[p] for p in known)
        system, count = votes.most_common(1)[0]
        if count < INHERIT_MIN_NEIGHBOURS:
            continue
        if count / len(known) < INHERIT_RATIO:
            continue
        out[name] = (
            system,
            [f"{count}/{len(known)} call neighbours in {system}"],
        )
    return out


def build(
    functions: list[dict[str, Any]],
    *,
    ram_names: dict[int, str] | None = None,
) -> dict[str, Any]:
    """Assign every function to a subsystem, or to `unassigned`."""
    names = ram_names or {}
    assigned: dict[str, str] = {}
    evidence: dict[str, list[str]] = {}
    origin: dict[str, str] = {}

    # Pass 1: objective evidence — named RAM symbols and hardware windows.
    for row in functions:
        refs = [int(a, 16) if isinstance(a, str) else int(a) for a in row.get("ram_refs") or []]
        ref_names = [names.get(a, "") for a in refs]
        system, why = classify_direct(
            ram_refs=refs,
            ram_names=[n for n in ref_names if n],
        )
        if system:
            assigned[row["name"]] = system
            evidence[row["name"]] = why
            origin[row["name"]] = "direct"

    # Pass 2: hand-written notes, but only where they are not batch labels.
    for row in functions:
        name = row["name"]
        if name in assigned:
            continue
        system, why = note_system(str(row.get("note") or ""))
        if system:
            assigned[name] = system
            evidence[name] = why
            origin[name] = "note"

    neighbours: dict[str, set[str]] = {}
    for row in functions:
        name = row["name"]
        peers = set(row.get("callers") or []) | set(row.get("callees") or [])
        neighbours[name] = peers

    # Pass 3: inherit from call neighbours of already-assigned functions.
    for name, (system, why) in inherit(assigned, neighbours).items():
        assigned[name] = system
        evidence[name] = why
        origin[name] = "derived"

    per_system: dict[str, list[str]] = {}
    for name, system in assigned.items():
        per_system.setdefault(system, []).append(name)

    systems = {
        system: {
            "functions": sorted(members),
            "count": len(members),
        }
        for system, members in sorted(per_system.items())
    }

    unassigned = sorted(r["name"] for r in functions if r["name"] not in assigned)

    return {
        "systems": systems,
        "membership": {
            name: {
                "system": assigned[name],
                "origin": origin[name],
                "evidence": evidence[name],
            }
            for name in sorted(assigned)
        },
        "unassigned": unassigned,
        "counts": {
            **{system: len(members) for system, members in sorted(per_system.items())},
            "unassigned": len(unassigned),
        },
        "notes": {
            "universal_symbols_excluded": list(UNIVERSAL_SYMBOLS),
            "why": (
                "Global roots such as gMainWorkPtr are referenced by most functions, "
                "so treating them as subsystem evidence inflates membership. "
                "Only subsystem-specific symbols assign a system."
            ),
        },
    }


def main() -> int:
    import json

    from analyze import load_functions, ram_name_map

    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--system", help="list functions in one subsystem")
    args = ap.parse_args()

    functions = load_functions()
    if not functions:
        print("no analysis/functions.json — run: python3 tools/decomp/analyze.py")
        return 1

    data = build(functions, ram_names=ram_name_map())

    if args.system:
        row = data["systems"].get(args.system.lower())
        if not row:
            print(f"unknown subsystem: {args.system}")
            return 1
        for name in row["functions"]:
            print(name)
        return 0

    if args.json:
        print(json.dumps(data, indent=2))
        return 0

    total = len(functions)
    print(f"=== Subsystems ({total} functions) ===")
    for system, row in data["systems"].items():
        pct = 100.0 * row["count"] / total if total else 0.0
        print(f"  {system:<10} {row['count']:>3}  ({pct:5.1f}%)")
    print(f"  {'unassigned':<10} {data['counts']['unassigned']:>3}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
