#!/usr/bin/env python3
"""Try semantic C on readable-Thumb near-misses; integrate verified matches.

Reads hand seeds (battle_semantic_batch, permuter import_function), c_patterns,
and m2c. Skips functions in decomp-queue.toml [[block]].

  python3 tools/decomp/near_miss_batch.py 20
  python3 tools/decomp/near_miss_batch.py --verify-only
  python3 tools/decomp/near_miss_batch.py --list-broken
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from battle_semantic_batch import BATTLE_SEEDS  # noqa: E402
from next_queue import _load_toml  # noqa: E402
from c_patterns import guess_c  # noqa: E402
from m2c_asm import m2c_decompile  # noqa: E402
from match_function import write_single_function_c  # noqa: E402
from opcode_stubs import file_kind, list_readable_asm, list_semantic  # noqa: E402

INTEGRATE = ROOT / "tools" / "decomp" / "integrate_c.py"
MATCH = ROOT / "tools" / "decomp" / "match_function.py"
NON = ROOT / "asm" / "nonmatchings"
MATCH_ASM = ROOT / "asm" / "matchings"
QUEUE_TOML = ROOT / "docs" / "decomp-queue.toml"
MATCHED = ROOT / "src" / "matched"

# Extra seeds from permuter import_function (subset with semantic intent).
IMPORT_SEEDS: dict[str, str] = {}
_import_py = ROOT / "tools" / "decomp" / "permuter" / "import_function.py"
if _import_py.is_file():
    text = _import_py.read_text()
    m = re.search(r"KNOWN_SEEDS[^=]*=\s*\{", text)
    if m:
        block = text[m.start() :]
        for fn_m in re.finditer(r'"(sub_[0-9A-Fa-f]+)":\s*"""(.*?)"""', block, re.S):
            IMPORT_SEEDS[fn_m.group(1)] = fn_m.group(2).strip()


def blocked() -> set[str]:
    cfg = _load_toml(QUEUE_TOML)
    return {row["name"] for row in cfg.get("block", []) if row.get("name")}


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


def body_from_seed(seed: str) -> str:
    lines = seed.splitlines()
    if lines and lines[0].startswith("#include"):
        lines = [ln for ln in lines if not ln.startswith("#include")]
    return "\n".join(lines).strip()


def candidates(function: str, *, no_m2c: bool = False) -> list[tuple[str, str]]:
    out: list[tuple[str, str]] = []

    for name, body, note in BATTLE_SEEDS:
        if name == function:
            out.append((body, f"battle-seed/{note}"))

    if function in IMPORT_SEEDS:
        out.append((body_from_seed(IMPORT_SEEDS[function]), "import-seed"))

    asm = asm_lines(function)
    if asm:
        cand = guess_c(function, asm)
        if cand:
            out.append((cand.body, cand.note))
        if not no_m2c:
            for valid in (False, True):
                m2c = m2c_decompile(function, valid_syntax=valid)
                if m2c:
                    tag = "m2c-valid" if valid else "m2c"
                    out.append((m2c, tag))

    seen: set[str] = set()
    uniq: list[tuple[str, str]] = []
    for body, note in out:
        if body in seen:
            continue
        seen.add(body)
        uniq.append((body, note))
    return uniq


def broken_semantic() -> list[tuple[str, str]]:
    bad: list[tuple[str, str]] = []
    for fn in list_semantic():
        path = MATCHED / f"{fn}.c"
        result = subprocess.run(
            [sys.executable, str(MATCH), fn, str(path)],
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            first = (result.stdout or result.stderr or "").splitlines()
            bad.append((fn, first[0] if first else "fail"))
    return bad


def readable_todo(blocked_names: set[str]) -> list[str]:
    out: list[str] = []
    for fn in list_readable_asm():
        if fn in blocked_names:
            continue
        out.append(fn)
    return out


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("limit", type=int, nargs="?", default=20)
    parser.add_argument("--verify-only", action="store_true")
    parser.add_argument("--list-broken", action="store_true")
    parser.add_argument(
        "--seeds-only",
        action="store_true",
        help="Only try BATTLE_SEEDS + import_function KNOWN_SEEDS",
    )
    parser.add_argument(
        "--no-m2c",
        action="store_true",
        help="Skip m2c (faster; patterns + seeds only)",
    )
    args = parser.parse_args()

    if args.list_broken or args.verify_only:
        bad = broken_semantic()
        print(f"broken semantic: {len(bad)}/{len(list_semantic())}")
        for fn, msg in bad:
            print(f"  {fn}: {msg}")
        if args.verify_only:
            return 1 if bad else 0
        return 0

    skip = blocked()
    seed_names = {n for n, _, _ in BATTLE_SEEDS} | set(IMPORT_SEEDS)
    if args.seeds_only:
        todo = sorted(seed_names - skip)
    else:
        todo = readable_todo(skip)

    converted = 0
    for name in todo:
        if converted >= args.limit:
            break
        if file_kind(MATCHED / f"{name}.c") == "semantic":
            continue
        for body, note in candidates(name, no_m2c=args.no_m2c or args.seeds_only):
            if not verify(name, body):
                continue
            if integrate(name, body, f"near-miss/{note}"):
                converted += 1
                print(f"converted {name} ({note})")
            break

    print(f"==> near_miss_batch: {converted} integrated", file=sys.stderr)
    print(converted)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
