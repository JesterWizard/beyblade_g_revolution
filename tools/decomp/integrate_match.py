#!/usr/bin/env python3
"""Integrate a verified match into asm/matchings and regenerate the ROM peel."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "build" / "matched.json"
NON = ROOT / "asm" / "nonmatchings"
MATCH = ROOT / "asm" / "matchings"
GEN = ROOT / "tools" / "decomp" / "gen_rom_layout.py"
MATCH_SCRIPT = ROOT / "tools" / "decomp" / "match_function.py"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from asm_bytes import addr_from_name, integration_plan, write_matching_asm  # noqa: E402


def load_manifest() -> dict:
    if MANIFEST.is_file():
        return json.loads(MANIFEST.read_text())
    return {"functions": []}


def save_manifest(data: dict) -> None:
    MANIFEST.parent.mkdir(parents=True, exist_ok=True)
    MANIFEST.write_text(json.dumps(data, indent=2) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description="Integrate a byte-matched function")
    parser.add_argument("function", help="sub_08033A94")
    parser.add_argument("c_file", nargs="?", help="optional scratch C to verify before integrate")
    args = parser.parse_args()

    name = args.function
    non_asm = NON / f"{name}.s"
    if not non_asm.is_file():
        print(f"missing {non_asm}", file=sys.stderr)
        return 1

    if args.c_file:
        result = subprocess.run(
            [sys.executable, str(MATCH_SCRIPT), name, args.c_file],
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            print(result.stdout)
            print(result.stderr, file=sys.stderr)
            return result.returncode

    plan = integration_plan(name)
    if plan is None:
        print(f"cannot integrate {name}", file=sys.stderr)
        return 1
    mode, size = plan

    MATCH.mkdir(parents=True, exist_ok=True)
    write_matching_asm(name, mode, size, MATCH / f"{name}.s", non_asm)

    data = load_manifest()
    entry = {
        "name": name,
        "addr": f"0x{addr_from_name(name):08X}",
        "src": args.c_file or "",
        "mode": mode,
    }
    data["functions"] = [f for f in data["functions"] if f["name"] != name]
    data["functions"].append(entry)
    save_manifest(data)

    result = subprocess.run([sys.executable, str(GEN)], check=False)
    if result.returncode != 0:
        return result.returncode

    print(f"integrated {name} @ {entry['addr']} ({mode}, {size}B)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
