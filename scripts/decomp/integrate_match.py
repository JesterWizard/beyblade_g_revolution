#!/usr/bin/env python3
"""Integrate a verified match into asm/matchings and regenerate the ROM peel."""

from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "build" / "matched.json"
NON = ROOT / "asm" / "nonmatchings"
MATCH = ROOT / "asm" / "matchings"
GEN = ROOT / "scripts" / "decomp" / "gen_rom_layout.py"
MATCH_SCRIPT = ROOT / "scripts" / "decomp" / "match_function.py"

HEADER = """@ Matched — integrated by scripts/decomp/integrate_match.py
.syntax unified
.thumb
.text
"""


def load_manifest() -> dict:
    if MANIFEST.is_file():
        return json.loads(MANIFEST.read_text())
    return {"functions": []}


def save_manifest(data: dict) -> None:
    MANIFEST.parent.mkdir(parents=True, exist_ok=True)
    MANIFEST.write_text(json.dumps(data, indent=2) + "\n")


def addr_from_name(name: str) -> str:
    return f"0x{name.replace('sub_', '')}"


def normalize_asm(name: str, src: Path, dst: Path) -> None:
    lines = src.read_text().splitlines()
    body: list[str] = []
    for line in lines:
        s = line.strip()
        if not s or s.startswith("@") or s in {".syntax unified", ".text", ".thumb"}:
            continue
        body.append(line)
    dst.write_text(HEADER + "\n".join(body) + "\n")


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

    MATCH.mkdir(parents=True, exist_ok=True)
    normalize_asm(name, non_asm, MATCH / f"{name}.s")

    data = load_manifest()
    entry = {
        "name": name,
        "addr": addr_from_name(name),
        "src": args.c_file or "",
    }
    data["functions"] = [f for f in data["functions"] if f["name"] != name]
    data["functions"].append(entry)
    save_manifest(data)

    result = subprocess.run([sys.executable, str(GEN)], check=False)
    if result.returncode != 0:
        return result.returncode

    print(f"integrated {name} @ {entry['addr']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
