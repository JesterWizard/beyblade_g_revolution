#!/usr/bin/env python3
"""Deterministic ROM analysis database.

Turns the ROM, the disassembly, and the matching build artifacts into a
queryable knowledge base under `analysis/`. This is the project-wide context
that later stages (naming, documentation, system discovery) read instead of
re-deriving facts per function.

Nothing here uses a model. It ingests what already exists rather than
recomputing it:

  build/matched.json          identity: name -> address, kind, note
  build/asm_size_cache.json   retail size (the ELF has no `.size` directives)
  docs/decomp-functions.json  per-function match status and byte counts
  asm/nonmatchings/*.s        readable Thumb for all 633 — the call graph source
  asm/ram_map_*.s             address -> RAM symbol names
  include/unknown-types.h     struct field offsets and widths

The genuinely new products are the global call graph (only per-function callees
existed before) and the per-function RAM/pool reference sets.

  python3 tools/decomp/analyze.py            # build analysis/*.json
  python3 tools/decomp/analyze.py --check    # verify idempotence
  python3 tools/decomp/analyze.py --json     # print the summary
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[2]
NON_ASM = ROOT / "asm" / "nonmatchings"
MANIFEST = ROOT / "build" / "matched.json"
SIZE_CACHE = ROOT / "build" / "asm_size_cache.json"
FUNCTIONS_JSON = ROOT / "docs" / "decomp-functions.json"
ANALYSIS = ROOT / "analysis"
OUT_FUNCTIONS = ANALYSIS / "functions.json"
OUT_XREFS = ANALYSIS / "xrefs.json"
OUT_STRUCTS = ANALYSIS / "structs.json"
OUT_SYSTEMS = ANALYSIS / "systems.json"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))

_BL = re.compile(r"^\s*bl\s+(sub_[0-9A-Fa-f]{8}|_[0-9A-Fa-f]{8})\b")
_POOL_ANNOT = re.compile(r"@\s*=0x([0-9A-Fa-f]{1,8})")
_FOURBYTE = re.compile(r"^\s*\.4byte\s+0x([0-9A-Fa-f]{1,8})")
_LABEL = re.compile(r"^[_.A-Za-z0-9]+:")
_INSN = re.compile(r"^\s+[a-z][a-z0-9.]*(\s|$)")
#: `[rN, #0xNN]` memory operands — the struct field offsets a function touches.
_OFFSET = re.compile(r"\[r\d+,\s*#(0x[0-9A-Fa-f]+|\d+)\]")

# Literal classes by address range.
_EWRAM = (0x02000000, 0x02FFFFFF)
_IWRAM = (0x03000000, 0x03FFFFFF)
_ROM = (0x08000000, 0x09FFFFFF)
_SRAM = (0x0E000000, 0x0E00FFFF)


def _load_json(path: Path) -> Any:
    if not path.is_file():
        return None
    try:
        return json.loads(path.read_text())
    except json.JSONDecodeError:
        return None


def ram_name_map() -> dict[int, str]:
    """address -> best RAM symbol name, from the asm RAM maps."""
    from m2c_cleanup import load_ram_maps  # noqa: WPS433

    deref, const = load_ram_maps()
    names: dict[int, str] = {}
    for table in (const, deref):
        for addr, name in table.items():
            # Prefer a real name over an auto-generated `gUnk_*` placeholder.
            current = names.get(addr, "")
            if not current or (current.startswith("gUnk_") and not name.startswith("gUnk_")):
                names[addr] = name
    return names


def parse_asm(name: str) -> dict[str, Any]:
    """Calls, pool literals and instruction count for one function."""
    path = NON_ASM / f"{name}.s"
    if not path.is_file():
        return {"callees": [], "pool": [], "offsets": [], "insn_count": 0}

    callees: list[str] = []
    pool: list[int] = []
    offsets: set[int] = set()
    insn_count = 0

    for line in path.read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("@"):
            continue
        if stripped.startswith("."):
            m = _FOURBYTE.match(line)
            if m:
                pool.append(int(m.group(1), 16))
            continue
        if _LABEL.match(stripped):
            continue

        m = _BL.match(line)
        if m:
            target = m.group(1)
            # `_XXXXXXXX` is Luvdis' name for a label it could not resolve;
            # normalise so both spellings of the same target unify.
            canonical = f"sub_{target[1:]}" if target.startswith("_") else target
            if canonical not in callees:
                callees.append(canonical)

        for lit in _POOL_ANNOT.findall(line):
            value = int(lit, 16)
            if value not in pool:
                pool.append(value)

        for off in _OFFSET.findall(line):
            offsets.add(int(off, 16) if off.lower().startswith("0x") else int(off))

        if _INSN.match(line):
            insn_count += 1

    return {
        "callees": callees,
        "pool": pool,
        "offsets": sorted(offsets),
        "insn_count": insn_count,
    }


def _classify_literal(value: int) -> str:
    lo, hi = _EWRAM
    if lo <= value <= hi:
        return "ewram"
    lo, hi = _IWRAM
    if lo <= value <= hi:
        return "iwram"
    lo, hi = _ROM
    if lo <= value <= hi:
        return "rom"
    lo, hi = _SRAM
    if lo <= value <= hi:
        return "sram"
    return "const"


def _function_set() -> list[str]:
    names: set[str] = set()
    data = _load_json(MANIFEST) or {}
    for row in data.get("functions") or []:
        if row.get("name"):
            names.add(row["name"])
    if NON_ASM.is_dir():
        names |= {p.stem for p in NON_ASM.glob("sub_*.s")}
    return sorted(names)


def collect() -> list[dict[str, Any]]:
    """The full per-function table."""
    from opcode_stubs import file_kind  # noqa: WPS433
    from tier import collect as tier_collect  # noqa: WPS433

    manifest = {r["name"]: r for r in (_load_json(MANIFEST) or {}).get("functions") or []}
    sizes_raw = _load_json(SIZE_CACHE) or {}
    statuses = {
        r["name"]: r
        for r in (_load_json(FUNCTIONS_JSON) or {}).get("functions") or []
    }
    tiers = {r["name"]: r for r in tier_collect()}
    names_map = ram_name_map()

    rows: list[dict[str, Any]] = []
    for name in _function_set():
        parsed = parse_asm(name)
        size_entry = sizes_raw.get(f"{name}.s")
        size = int(size_entry[1]) if size_entry else 0

        ram_refs: list[str] = []
        data_refs: list[str] = []
        for value in parsed["pool"]:
            kind = _classify_literal(value)
            if kind == "rom":
                data_refs.append(f"0x{value:08X}")
            elif kind in ("ewram", "iwram", "sram"):
                ram_refs.append(f"0x{value:08X}")

        tier_row = tiers.get(name) or {}
        status_row = statuses.get(name) or {}
        manifest_row = manifest.get(name) or {}
        c_path = ROOT / str(manifest_row.get("src") or "")
        kind = file_kind(c_path) if c_path.is_file() else "asm"

        rows.append(
            {
                "name": name,
                "addr": f"0x{int(name.replace('sub_', ''), 16):08X}",
                "size": size,
                "kind": kind,
                "status": str(status_row.get("status") or "not_started"),
                "tier": str(tier_row.get("tier") or "UNKNOWN"),
                "symbol": str(tier_row.get("symbol") or ""),
                "note": str(manifest_row.get("note") or ""),
                "insn_count": parsed["insn_count"],
                "offsets": [f"0x{o:02X}" for o in parsed["offsets"]],
                "callees": parsed["callees"],
                "callers": [],
                "ram_refs": sorted(set(ram_refs)),
                "ram_names": sorted(
                    {names_map.get(int(a, 16), "") for a in ram_refs} - {""}
                ),
                "data_refs": sorted(set(data_refs)),
                "pool": [f"0x{v:08X}" for v in parsed["pool"]],
            }
        )

    # Second pass: invert callees into callers. Done here so a callee that is
    # not itself one of the 633 still gets recorded in xrefs.json.
    by_name = {r["name"]: r for r in rows}
    for row in rows:
        for callee in row["callees"]:
            target = by_name.get(callee)
            if target is not None and row["name"] not in target["callers"]:
                target["callers"].append(row["name"])

    for row in rows:
        row["callers"].sort()
        row["callees"].sort()
    return rows


def build_xrefs(functions: list[dict[str, Any]]) -> dict[str, Any]:
    callers: dict[str, list[str]] = {}
    callees: dict[str, list[str]] = {}
    data_refs: dict[str, list[str]] = defaultdict(list)

    for row in functions:
        name = row["name"]
        callers[name] = list(row["callers"])
        callees[name] = list(row["callees"])
        for addr in row["ram_refs"] + row["data_refs"]:
            data_refs[addr].append(name)

    external = sorted(
        {
            c
            for row in functions
            for c in row["callees"]
            if c not in callers
        }
    )

    return {
        "callers": {k: v for k, v in sorted(callers.items()) if v},
        "callees": {k: v for k, v in sorted(callees.items()) if v},
        "data_refs": {k: sorted(set(v)) for k, v in sorted(data_refs.items())},
        "external_callees": external,
        "counts": {
            "edges": sum(len(v) for v in callees.values()),
            "data_addresses": len(data_refs),
            "external_callees": len(external),
        },
    }


def build_structs(functions: list[dict[str, Any]]) -> dict[str, Any]:
    from unknown_types import fields_of_struct, struct_from_function, width_of  # noqa: WPS433

    users: dict[str, list[str]] = defaultdict(list)
    by_offset: dict[str, list[str]] = defaultdict(list)
    for row in functions:
        struct = struct_from_function(row["name"])
        if struct:
            users[struct].append(row["name"])
        for offset in row.get("offsets") or []:
            by_offset[offset].append(row["name"])

    structs: dict[str, Any] = {}
    for struct, members in sorted(users.items()):
        fields = fields_of_struct(struct)
        if not fields:
            continue
        structs[struct] = {
            "functions": sorted(members),
            "function_count": len(members),
            "fields": [
                {
                    "offset": f"0x{offset:02X}",
                    "width": width_of(spec.split(" ", 1)[0]) if spec else 0,
                    "ctype": spec.split(" ", 1)[0] if spec else "",
                    "name": spec.split(" ", 1)[1] if " " in spec else "",
                }
                for offset, spec in sorted(fields.items())
            ],
        }

    return {
        "structs": structs,
        "count": len(structs),
        # Offset-level access index. Resolving an offset to a *struct* needs
        # dataflow the deterministic pass does not have, so this stays honest:
        # it answers "who touches 0x50?" without claiming which struct it is.
        "by_offset": {
            offset: {"functions": sorted(set(names)), "count": len(set(names))}
            for offset, names in sorted(by_offset.items())
        },
    }


_GAP_HEADER = re.compile(r"0x([0-9A-Fa-f]+)\.\.0x([0-9A-Fa-f]+)")
_THUMB_MEM = re.compile(r"\[(?:r\d+|sp|pc),\s*#(0x[0-9A-Fa-f]+|\d+)\]")
_MAX_FUNC = 0x2000


def _gap_ranges() -> list[tuple[int, int]]:
    """Inclusive (start, end) ROM addresses of every `.incbin` gap file."""
    ranges: list[tuple[int, int]] = []
    for path in sorted((ROOT / "asm").glob("rom_gap_*.s")):
        with path.open() as fh:
            m = _GAP_HEADER.search(fh.readline())
        if m:
            ranges.append((int(m.group(1), 16), int(m.group(2), 16)))
    return ranges


def _scan_gap_function(md: Any, rom: bytes, start: int, limit: int) -> int | None:
    """End (exclusive) of the code run at `start`, or None if it is not code.

    Decodes Thumb forward until a terminator (`bx rN`, `pop {..pc}`, or an
    unconditional branch that leaves the run). Any undecodable halfword, or no
    terminator inside the cap, means this was data that merely looked like a
    prologue.
    """
    off = start - 0x08000000
    end = min(limit, start + _MAX_FUNC)
    pos = start
    while pos < end:
        word = rom[pos - 0x08000000 : pos - 0x08000000 + 4]
        insns = list(md.disasm(word, pos, count=1))
        if not insns:
            return None
        ins = insns[0]
        pos += ins.size
        if ins.mnemonic == "bx" or (ins.mnemonic == "pop" and "pc" in ins.op_str):
            return pos
        if ins.mnemonic == "b":
            target = int(ins.op_str.lstrip("#"), 16)
            if not (start <= target < pos):
                return pos
    return None


def collect_gap() -> list[dict[str, Any]]:
    """Functions that live in `asm/rom_gap_*.s` (still `.incbin`, undecompiled).

    The per-function table above only knows the functions Luvdis split into
    `asm/nonmatchings`. Everything else is a raw baserom blob, so boundaries
    are recovered from the bytes: Thumb `push {..lr}` prologues that decode
    cleanly to a return, plus every `bl` target landing inside a gap.
    """
    try:
        import capstone  # noqa: WPS433
    except ImportError:
        print("capstone missing: gap functions skipped (pip install capstone)", file=sys.stderr)
        return []

    rom = (ROOT / "baserom.gba").read_bytes()
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    md.detail = False
    ranges = _gap_ranges()

    def gap_of(addr: int) -> tuple[int, int] | None:
        for lo, hi in ranges:
            if lo <= addr <= hi:
                return lo, hi
        return None

    # Pass 1: candidate starts, per gap, then validate by decoding.
    starts: dict[int, int] = {}  # start -> end of the decoded code run
    for lo, hi in ranges:
        limit = hi + 1
        pos = lo + (lo & 1)
        while pos + 2 <= limit:
            half = int.from_bytes(rom[pos - 0x08000000 : pos - 0x08000000 + 2], "little")
            if (half & 0xFF00) == 0xB500:  # push {.., lr}
                code_end = _scan_gap_function(md, rom, pos, limit)
                if code_end is not None:
                    starts[pos] = code_end
                    pos = code_end
                    continue
            pos += 2

    # Pass 2: `bl` targets inside a gap that pass 1 did not see (no push).
    changed = True
    while changed:
        changed = False
        for start in sorted(starts):
            for ins in md.disasm(rom[start - 0x08000000 : starts[start] - 0x08000000], start):
                if ins.mnemonic != "bl":
                    continue
                target = int(ins.op_str.lstrip("#"), 16)
                rng = gap_of(target)
                if rng and target not in starts and not any(
                    s <= target < e for s, e in starts.items()
                ):
                    end = _scan_gap_function(md, rom, target, rng[1] + 1)
                    if end is not None:
                        starts[target] = end
                        changed = True

    # Size runs to the next function (or gap end), so trailing literal pools
    # count towards the function, as they do for the split functions.
    ordered = sorted(starts)
    sym_json = _load_json(ANALYSIS / "symbols.json") or {}
    symbols = sym_json.get("symbols") or {}
    names_map = ram_name_map()

    rows: list[dict[str, Any]] = []
    for idx, start in enumerate(ordered):
        lo, hi = gap_of(start) or (start, start)
        nxt = ordered[idx + 1] if idx + 1 < len(ordered) else hi + 1
        end = min(nxt, hi + 1)
        code_end = starts[start]
        callees: list[str] = []
        offsets: set[int] = set()
        pool: list[int] = []
        insn_count = 0
        for ins in md.disasm(rom[start - 0x08000000 : code_end - 0x08000000], start):
            insn_count += 1
            if ins.mnemonic == "bl":
                name = f"sub_{int(ins.op_str.lstrip('#'), 16):08X}"
                if name not in callees:
                    callees.append(name)
            elif ins.mnemonic == "ldr" and "[pc," in ins.op_str:
                m = _THUMB_MEM.search(ins.op_str)
                if m:
                    imm = int(m.group(1), 0)
                    lit = ((ins.address + 4) & ~3) + imm
                    if lit + 4 <= len(rom) + 0x08000000:
                        value = int.from_bytes(
                            rom[lit - 0x08000000 : lit - 0x08000000 + 4], "little"
                        )
                        if value not in pool:
                            pool.append(value)
            else:
                m = _THUMB_MEM.search(ins.op_str)
                if m and "sp" not in ins.op_str and "pc" not in ins.op_str:
                    offsets.add(int(m.group(1), 0))

        ram_refs = [v for v in pool if _classify_literal(v) in ("ewram", "iwram", "sram")]
        data_refs = [v for v in pool if _classify_literal(v) == "rom"]
        sym = symbols.get(f"0x{start:08X}") or {}
        rows.append(
            {
                "name": f"sub_{start:08X}",
                "addr": f"0x{start:08X}",
                "size": end - start,
                "kind": "gap",
                "status": "not_started",
                "tier": "UNKNOWN",
                "symbol": str(sym.get("symbol") or ""),
                "note": "",
                "insn_count": insn_count,
                "offsets": [f"0x{o:02X}" for o in sorted(offsets)],
                "callees": sorted(callees),
                "callers": [],
                "ram_refs": [f"0x{v:08X}" for v in sorted(set(ram_refs))],
                "ram_names": sorted({names_map.get(v, "") for v in ram_refs} - {""}),
                "data_refs": [f"0x{v:08X}" for v in sorted(set(data_refs))],
                "pool": [f"0x{v:08X}" for v in pool],
                "system": "",
            }
        )

    by_name = {r["name"]: r for r in rows}
    for row in rows:
        for callee in row["callees"]:
            target = by_name.get(callee)
            if target is not None and row["name"] not in target["callers"]:
                target["callers"].append(row["name"])
    for row in rows:
        row["callers"].sort()
    return rows


def _write(path: Path, payload: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2, sort_keys=False) + "\n")


def load_functions() -> list[dict[str, Any]]:
    """Read the generated per-function table, or [] when it does not exist."""
    data = _load_json(OUT_FUNCTIONS)
    if not data:
        return []
    return list(data.get("functions") or [])


def run() -> dict[str, Any]:
    import systems as systems_mod  # noqa: WPS433

    functions = collect()
    gap_functions = collect_gap()
    xrefs = build_xrefs(functions)
    structs = build_structs(functions)

    system_data = systems_mod.build(functions, ram_names=ram_name_map())
    membership = system_data["membership"]
    for row in functions:
        entry = membership.get(row["name"])
        row["system"] = entry["system"] if entry else ""

    generated = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")

    _write(
        OUT_FUNCTIONS,
        {
            "generated": generated,
            "total": len(functions),
            "functions": functions,
            "gap_total": len(gap_functions),
            "gap_functions": gap_functions,
        },
    )
    _write(OUT_XREFS, {"generated": generated, **xrefs})
    _write(OUT_STRUCTS, {"generated": generated, **structs})
    _write(OUT_SYSTEMS, {"generated": generated, **system_data, "membership": membership})

    return {
        "generated": generated,
        "functions": len(functions),
        "gap_functions": len(gap_functions),
        "structs": structs["count"],
        "systems": system_data["counts"],
        "xrefs": xrefs["counts"],
    }


def _strip_generated(obj: Any) -> Any:
    """Drop the timestamp so two runs can be compared for idempotence."""
    if isinstance(obj, dict):
        return {k: _strip_generated(v) for k, v in obj.items() if k != "generated"}
    if isinstance(obj, list):
        return [_strip_generated(v) for v in obj]
    return obj


def check_idempotent() -> int:
    before = {
        path.name: _strip_generated(_load_json(path))
        for path in (OUT_FUNCTIONS, OUT_XREFS, OUT_STRUCTS, OUT_SYSTEMS)
    }
    run()
    after = {
        path.name: _strip_generated(_load_json(path))
        for path in (OUT_FUNCTIONS, OUT_XREFS, OUT_STRUCTS, OUT_SYSTEMS)
    }
    drifted = [name for name in before if before[name] != after[name]]
    if drifted:
        print(f"NOT idempotent: {', '.join(sorted(drifted))}")
        return 1
    print("idempotent: analysis/*.json stable across runs")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--json", action="store_true", help="print the summary as JSON")
    ap.add_argument("--check", action="store_true", help="verify idempotence")
    args = ap.parse_args()

    if args.check:
        return check_idempotent()

    summary = run()
    if args.json:
        print(json.dumps(summary, indent=2))
        return 0

    print("=== Analysis database ===")
    print(f"  functions   {summary['functions']}")
    print(f"  gap funcs   {summary['gap_functions']} (still .incbin)")
    print(f"  structs     {summary['structs']}")
    print(f"  call edges  {summary['xrefs']['edges']}")
    print(f"  data addrs  {summary['xrefs']['data_addresses']}")
    print(f"  external    {summary['xrefs']['external_callees']} unresolved callees")
    for system, count in sorted(summary["systems"].items()):
        print(f"  system {system:<10} {count}")
    for path in (OUT_FUNCTIONS, OUT_XREFS, OUT_STRUCTS, OUT_SYSTEMS):
        print(f"  wrote {path.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
