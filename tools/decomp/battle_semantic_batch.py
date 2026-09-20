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
        "sub_08033084",
        """void sub_080726E0(struct Unk726E0 *a, void *dst, s32 idx);

void sub_08033084(struct Unk726E0 *a, u32 flag)
{
    register struct Unk726E0 *dst asm("r5");
    register struct BattleWork **loc asm("r4");
    struct BattleWork *w;
    s32 value;

    dst = a;
    flag <<= 24;
    if (flag != 0)
    {
        loc = gBattleWorkPtrLoc;
        w = *loc;
        w->unk1F94 += w->unk1F90;
        value = w->unk1F94;
        if (value > 0x7FF)
        {
            value = 0x800;
            w->unk1F98 = 0;
        }
        if (value <= 0)
        {
            value = 0;
            (*loc)->unk1F98 = 0;
        }
        sub_080726E0(dst, (void *)0x05000000, value >> 8);
    }
}""",
        "palette-fade-blit",
    ),
    (
        "sub_08031294",
        """void sub_08031294(struct Unk312EC *a)
{
    register u8 r1 asm("r1");
    register u8 r2 asm("r2");

    r1 = 0xFF;
    r2 = *(u8 *)&a->unk00;
    r2 |= r1;
    *(u8 *)&a->unk00 = r2;
    r2 = *(u8 *)&a->unk01;
    r1 |= r2;
    *(u8 *)&a->unk01 = r1;
    a->unk04 = -1;
    r1 = 0;
    a->unk0C = 0;
    a->unk08 = r1;
}""",
        "init-312EC-flags",
    ),
    (
        "sub_08033C1C",
        """void sub_08033C1C(void)
{
    register struct Unk0380 *r1 asm("r1");
    u32 tmp[1];

    tmp[0] = gUnk_03000380;
    r1 = (struct Unk0380 *)tmp[0];
    if (r1->unk09 == 1)
    {
        r1->unk09 = 0;
        r1->unk0A = 0;
        sub_080358CC(&r1->unk0C);
    }
}""",
        "iwram-0380-flag-clear",
    ),
    (
        "sub_0806F430",
        """u32 sub_0806F430(void)
{
    register u32 r0 asm("r0");
    register u32 r1 asm("r1");
    struct Unk4084 *p;
    u32 tmp[1];

    tmp[0] = gUnk_03004084;
    p = *(struct Unk4084 **)tmp[0];
    r1 = p->unk14;
    r0 = 8;
    r0 &= r1;
    if (r0 != 0)
        return 1;
    r0 = 0x10;
    r1 &= r0;
    if (r1 != 0)
        return 0;
    sub_08067B98((void *)0x083D2030);
    return 0;
}""",
        "unk4084-flag-check",
    ),
    (
        "sub_0806209C",
        """void sub_0806209C(struct Unk62044 *a)
{
    s32 i;
    void *p;

    if (a == 0)
        return;
    if (a->unk0C != 0)
    {
        i = 0;
        do
        {
            p = a->unk0C[i];
            if (p == 0)
                break;
            sub_0806FE84(p);
            a->unk0C[i] = 0;
            i++;
        } while (i <= 0x7F);
    }
    a->unk24 = 0;
}""",
        "unk62044-free-slot-table",
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
