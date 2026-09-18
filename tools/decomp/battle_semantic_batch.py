#!/usr/bin/env python3
"""Try semantic C for battle readable-Thumb functions; integrate on MATCH."""

from __future__ import annotations

import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from battle_scan import score  # noqa: E402
from c_patterns import guess_c  # noqa: E402
from m2c_asm import m2c_decompile  # noqa: E402
from match_function import reference_size, write_single_function_c  # noqa: E402
from opcode_stubs import file_kind  # noqa: E402

INTEGRATE = ROOT / "tools" / "decomp" / "integrate_c.py"
MATCH = ROOT / "tools" / "decomp" / "match_function.py"
NON = ROOT / "asm" / "nonmatchings"
MATCHED = ROOT / "src" / "matched"

# Hand-verified seeds: function -> (body without includes, note)
BATTLE_SEEDS: list[tuple[str, str, str]] = [
    (
        "sub_08033530",
        """void sub_08033530(void)
{
    if (gBattleWork->unk2088 == 1)
    {
        if (gBattleWork->unk201C == 0)
            sub_08033574();
        else
        {
            sub_080686D8(&gBattleWork->unk1FAC);
            sub_08068418(&gBattleWork->unk1FAC);
        }
    }
}""",
        "battle/state-2088-branch",
    ),
]


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


def battle_readable() -> list[str]:
    out: list[str] = []
    for path in sorted(MATCHED.glob("sub_*.c")):
        n, _, _ = score(NON / f"{path.stem}.s")
        if not n:
            continue
        if file_kind(path) != "asm":
            continue
        out.append(path.stem)
    return out


def candidates_for(function: str, *, seeds_only: bool = False) -> list[tuple[str, str]]:
    out: list[tuple[str, str]] = []

    for name, body, note in BATTLE_SEEDS:
        if name == function:
            out.append((body, note))

    if seeds_only:
        seen: set[str] = set()
        uniq: list[tuple[str, str]] = []
        for body, note in out:
            if body in seen:
                continue
            seen.add(body)
            uniq.append((body, note))
        return uniq

    asm_path = NON / f"{function}.s"
    if not asm_path.is_file():
        return out
    asm_lines = asm_path.read_text().splitlines()

    cand = guess_c(function, asm_lines)
    if cand:
        out.append((cand.body, cand.note))

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


def main() -> int:
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("limit", type=int, nargs="?", default=10)
    parser.add_argument(
        "--seeds-only",
        action="store_true",
        help="Only try hand-maintained BATTLE_SEEDS (skip m2c/heuristics)",
    )
    args = parser.parse_args()

    seed_names = {name for name, _, _ in BATTLE_SEEDS}
    if args.seeds_only:
        todo = sorted(seed_names)
    else:
        ranked: list[tuple[int, str]] = []
        for name in battle_readable():
            try:
                sz = reference_size(name)
            except (FileNotFoundError, ValueError):
                continue
            ranked.append((sz, name))
        ranked.sort()
        todo = [name for _, name in ranked]

    converted = 0
    for name in todo:
        if converted >= args.limit:
            break
        cands = candidates_for(name, seeds_only=args.seeds_only)
        for body, note in cands:
            if not verify(name, body):
                continue
            if integrate(name, body, f"battle/{note}"):
                converted += 1
                print(f"converted {name} ({note})")
            break

    print(f"==> battle_semantic_batch: {converted} integrated", file=sys.stderr)
    print(converted, flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
