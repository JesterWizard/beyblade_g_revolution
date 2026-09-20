#!/usr/bin/env python3
"""Fast single-function pipeline: c_patterns → cleaned m2c → match_function.

Use after picking a target from docs/decomp-queue.md.

  python3 tools/decomp/try_convert.py sub_08034894
  python3 tools/decomp/try_convert.py sub_08034894 --integrate --note battle/input
  python3 tools/decomp/try_convert.py sub_08034894 --write scratch.c
"""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NON = ROOT / "asm" / "nonmatchings"
MATCH_ASM = ROOT / "asm" / "matchings"
MATCH_SCRIPT = ROOT / "tools" / "decomp" / "match_function.py"
INTEGRATE = ROOT / "tools" / "decomp" / "integrate_c.py"

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from c_patterns import PATTERN_CATALOG, guess_c  # noqa: E402
from m2c_asm import m2c_decompile  # noqa: E402
from m2c_cleanup import cleanup_text  # noqa: E402
from match_function import write_single_function_c  # noqa: E402


def _looks_uncompilable(body: str) -> bool:
    return any(tok in body for tok in ("?", "M2C_FIELD", "M2C_UNK", "BITCAST", "/* extern */"))


def asm_lines(function: str) -> list[str] | None:
    for base in (NON, MATCH_ASM):
        path = base / f"{function}.s"
        if path.is_file():
            return path.read_text().splitlines()
    return None


def verify(function: str, body: str) -> bool:
    with tempfile.TemporaryDirectory() as tmp:
        scratch = Path(tmp) / "scratch.c"
        write_single_function_c(function, body, scratch)
        result = subprocess.run(
            [sys.executable, str(MATCH_SCRIPT), function, str(scratch)],
            capture_output=True,
            text=True,
        )
    return result.returncode == 0


def candidates(function: str, asm: list[str]) -> list[tuple[str, str, str]]:
    """Return (source, note, body) in try order."""
    out: list[tuple[str, str, str]] = []

    cand = guess_c(function, asm)
    if cand:
        out.append(("c_patterns", cand.note, cand.body))

    for valid in (False, True):
        m2c = m2c_decompile(function, valid_syntax=valid)
        if not m2c:
            continue
        tag = "m2c-valid" if valid else "m2c"
        cleaned = cleanup_text(m2c, function)
        if cleaned.strip() and not _looks_uncompilable(cleaned):
            out.append((f"{tag}-clean", f"{tag}-clean", cleaned))
        if not _looks_uncompilable(m2c):
            out.append((tag, tag, m2c))

    seen: set[str] = set()
    uniq: list[tuple[str, str, str]] = []
    for src, note, body in out:
        if body in seen:
            continue
        seen.add(body)
        uniq.append((src, note, body))
    return uniq


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


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function", help="e.g. sub_08034894")
    parser.add_argument("--integrate", action="store_true", help="land first MATCH")
    parser.add_argument("--note", default="", help="integrate_c note (default: try_convert/<source>)")
    parser.add_argument("--write", metavar="PATH", help="write first MATCH body to file")
    parser.add_argument("--list-patterns", action="store_true", help="print pattern catalog and exit")
    args = parser.parse_args()

    if args.list_patterns:
        for row in PATTERN_CATALOG:
            print(f"{row['id']:24s}  {row['note']}")
            print(f"  {row['summary']}")
        return 0

    function = args.function
    asm = asm_lines(function)
    if asm is None:
        print(f"error: no asm for {function} in nonmatchings/ or matchings/", file=sys.stderr)
        return 1

    print(f"=== {function} ===")
    matched: tuple[str, str, str] | None = None
    for src, note, body in candidates(function, asm):
        ok = verify(function, body)
        mark = "MATCH" if ok else "FAIL "
        print(f"  [{mark}] {src}: {note}")
        if ok and matched is None:
            matched = (src, note, body)

    if matched is None:
        print()
        print("No automatic candidate matched. Next steps:")
        print(f"  python3 tools/decomp/m2c_asm.py {function}          # inspect m2c output")
        print(f"  python3 tools/decomp/match_function.py {function} scratch.c")
        print("  See docs/decomp-patterns.md — manual fixes (register asm, permuter, block)")
        return 2

    src, note, body = matched
    print()
    print(f"Best: {src} ({note})")

    if args.write:
        out = Path(args.write)
        write_single_function_c(function, body, out)
        print(f"Wrote {out}")

    if args.integrate:
        tag = args.note or f"try_convert/{src}"
        if integrate(function, body, tag):
            print(f"Integrated as semantic C ({tag})")
            subprocess.run(
                [sys.executable, str(ROOT / "tools" / "decomp" / "next_queue.py"), "--write"],
                cwd=str(ROOT),
                check=False,
            )
        else:
            return 3

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
