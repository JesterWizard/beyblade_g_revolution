#!/usr/bin/env python3
"""Try semantic C (patterns + m2c) for opcode-embedded stubs; integrate on MATCH."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts" / "decomp"))

from c_patterns import guess_c  # noqa: E402
from m2c_asm import m2c_decompile  # noqa: E402
from match_function import reference_size, write_single_function_c  # noqa: E402
from opcode_stubs import list_opcode_stubs  # noqa: E402

INTEGRATE = ROOT / "scripts" / "decomp" / "integrate_c.py"
MATCH = ROOT / "scripts" / "decomp" / "match_function.py"
NON = ROOT / "asm" / "nonmatchings"


def verify(function: str, body: str) -> bool:
    with tempfile.TemporaryDirectory() as tmp:
        scratch = Path(tmp) / "scratch.c"
        write_single_function_c(function, body, scratch)
        result = subprocess.run(
            [sys.executable, str(MATCH), function, str(scratch)],
            capture_output=True,
            text=True,
        )
    return result.returncode == 0


def integrate(function: str, body: str, note: str) -> bool:
    result = subprocess.run(
        [
            sys.executable,
            str(INTEGRATE),
            function,
            body,
            "--note",
            note,
            "--kind",
            "semantic",
            "--skip-compare",
        ],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        if result.stdout:
            print(result.stdout, file=sys.stderr)
        if result.stderr:
            print(result.stderr, file=sys.stderr)
        return False
    return True


def candidates_for(function: str) -> list[tuple[str, str]]:
    """Return (body, note) attempts in order."""
    asm_path = NON / f"{function}.s"
    if not asm_path.is_file():
        return []
    asm_lines = asm_path.read_text().splitlines()
    out: list[tuple[str, str]] = []

    cand = guess_c(function, asm_lines)
    if cand:
        out.append((cand.body, cand.note))

    for valid in (False, True):
        m2c = m2c_decompile(function, valid_syntax=valid)
        if m2c:
            tag = "m2c-valid" if valid else "m2c"
            out.append((m2c, tag))

    # dedupe bodies
    seen: set[str] = set()
    uniq: list[tuple[str, str]] = []
    for body, note in out:
        if body in seen:
            continue
        seen.add(body)
        uniq.append((body, note))
    return uniq


def main() -> int:
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("limit", type=int, nargs="?", default=30)
    parser.add_argument("--pool-free-only", action="store_true")
    args = parser.parse_args()

    stubs = list_opcode_stubs()
    ranked: list[tuple[int, str]] = []
    for name in stubs:
        asm = NON / f"{name}.s"
        if not asm.is_file():
            continue
        text = asm.read_text()
        if args.pool_free_only and ".4byte" in text:
            continue
        try:
            size = reference_size(name)
        except (FileNotFoundError, ValueError):
            continue
        ranked.append((size, name))
    ranked.sort()

    converted = 0
    skipped = 0
    for size, name in ranked:
        if converted >= args.limit:
            break
        for body, note in candidates_for(name):
            if not verify(name, body):
                continue
            if integrate(name, body, f"semantic/{note}"):
                converted += 1
                print(f"converted {name} ({note}, {size}B)", file=sys.stderr)
                break
        else:
            skipped += 1

    print(f"==> semantic batch: {converted} converted, {skipped} still opcode", file=sys.stderr)
    print(converted, flush=True)

    if converted > 0:
        subprocess.run(["make", "compare"], cwd=str(ROOT), check=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
