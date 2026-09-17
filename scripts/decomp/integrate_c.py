#!/usr/bin/env python3
"""Verify byte-matched C and land it in src/matched/ + matched.json."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MANIFEST = ROOT / "build" / "matched.json"
MATCH = ROOT / "asm" / "matchings"
SRC_MATCHED = ROOT / "src" / "matched"
MATCH_SCRIPT = ROOT / "scripts" / "decomp" / "match_function.py"
GEN = ROOT / "scripts" / "decomp" / "gen_rom_layout.py"

sys.path.insert(0, str(ROOT / "scripts" / "decomp"))
from asm_bytes import addr_from_name, retail_bytes, write_matching_bytes  # noqa: E402
from match_function import (  # noqa: E402
    compile_c,
    normalize_compiled,
    obj_text_bytes,
    reference_size,
    write_single_function_c,
)


def load_manifest() -> dict:
    if MANIFEST.is_file():
        return json.loads(MANIFEST.read_text())
    return {"functions": []}


def save_manifest(data: dict) -> None:
    MANIFEST.parent.mkdir(parents=True, exist_ok=True)
    MANIFEST.write_text(json.dumps(data, indent=2) + "\n")


def verify(function: str, c_path: Path) -> bool:
    result = subprocess.run(
        [sys.executable, str(MATCH_SCRIPT), function, str(c_path)],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        if result.stdout:
            print(result.stdout)
        if result.stderr:
            print(result.stderr, file=sys.stderr)
    return result.returncode == 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Integrate verified C for a matched function")
    parser.add_argument("function")
    parser.add_argument("c_body", help='C function body (or "@" + path to read body from)')
    parser.add_argument("--note", default="", help="conversion note for manifest")
    parser.add_argument(
        "--skip-compare",
        action="store_true",
        help="skip make compare (batch runners verify once at end)",
    )
    args = parser.parse_args()

    name = args.function
    if args.c_body.startswith("@") and len(args.c_body) > 1:
        body_path = Path(args.c_body[1:])
        if not body_path.is_file():
            body_path = ROOT / args.c_body[1:]
        body = body_path.read_text()
    else:
        body = args.c_body

    SRC_MATCHED.mkdir(parents=True, exist_ok=True)
    rel_src = f"src/matched/{name}.c"
    dst = ROOT / rel_src

    with tempfile.TemporaryDirectory() as tmp:
        scratch = Path(tmp) / "scratch.c"
        write_single_function_c(name, body, scratch)
        if not verify(name, scratch):
            return 2
        compile_c(scratch, Path(tmp) / "out.o")
        size = reference_size(name)
        got = normalize_compiled(obj_text_bytes(Path(tmp) / "out.o"), size)
        want = retail_bytes(name, size)
        if got != want:
            print(f"bytes mismatch after normalize for {name}", file=sys.stderr)
            return 2
        dst.write_text(scratch.read_text())

    write_matching_bytes(name, want, MATCH / f"{name}.s")

    data = load_manifest()
    entry = {
        "name": name,
        "addr": f"0x{addr_from_name(name):08X}",
        "src": rel_src,
        "mode": "c",
    }
    if args.note:
        entry["note"] = args.note
    data["functions"] = [f for f in data["functions"] if f["name"] != name]
    data["functions"].append(entry)
    save_manifest(data)

    result = subprocess.run([sys.executable, str(GEN)], check=False)
    if result.returncode != 0:
        return result.returncode

    if not args.skip_compare:
        subprocess.run(["make", "compare"], cwd=str(ROOT), check=True)
    print(f"integrated C for {name} -> {rel_src}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
