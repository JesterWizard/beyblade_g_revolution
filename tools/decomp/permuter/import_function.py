#!/usr/bin/env python3
"""Import one function into decomp-permuter's nonmatchings/ workdir.

Converts Luvdis nonmatching asm to `glabel` form, builds a semantic C seed
(m2c, cleaned, or existing readable src), then runs import.py.

Does not replace src/matched/*.c — integrate only after permuter score 0
and match_function.py MATCH.
"""

from __future__ import annotations

import argparse
import os
import re
import shlex
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from m2c_asm import m2c_decompile  # noqa: E402
from m2c_cleanup import cleanup_text  # noqa: E402
from opcode_stubs import is_opcode_stub  # noqa: E402

NON = ROOT / "asm" / "nonmatchings"
MATCHED = ROOT / "src" / "matched"
WIP = ROOT / "src" / "wip"
PERM = ROOT / "tools" / "decomp-permuter"
COMPILE_SH = ROOT / "tools" / "decomp" / "permuter" / "compile.sh"

# Per-function agbcc flags carried in a `/* match-flags: ... */` comment.
# Must stay in sync with match_function.py ALLOWED_MATCH_FLAGS, and with the
# whitelist in permuter/compile.sh.
MATCH_FLAGS_RE = re.compile(r"/\*\s*match-flags:\s*(.*?)\s*\*/")
ALLOWED_MATCH_FLAGS = frozenset({"-fprologue-bugfix", "-fomit-frame-pointer"})

# Must stay in sync with match_function.py MATCH_COMPILER_RE / COMPILERS, and with
# the `compiler` sidecar handling in permuter/compile.sh. pret/agbcc installs two
# compilers; a subset of functions only reaches retail with the older one.
MATCH_COMPILER_RE = re.compile(r"/\*\s*match-compiler:\s*(\S+?)\s*\*/")
ALLOWED_COMPILERS = ("agbcc", "old_agbcc")

_UNCOMPILABLE = ("?", "M2C_FIELD", "M2C_UNK", "BITCAST", "/* extern */")


def to_glabel_asm(function: str) -> str:
    src = (NON / f"{function}.s").read_text()
    lines: list[str] = []
    for line in src.splitlines():
        stripped = line.strip()
        if stripped.startswith("@") or stripped.startswith(".syntax") or stripped in (
            ".thumb",
            ".text",
        ):
            continue
        if stripped == f"{function}:":
            lines.append(f"glabel {function}")
            continue
        lines.append(line.rstrip())
    return "\n".join(lines) + "\n"


def clean_m2c(text: str) -> str | None:
    if not text or "M2C_ERROR" in text or "Decompilation failure" in text:
        return None
    # `*(expr)` without a type is invalid; wrap as u8* when it's a return of byte load.
    text = re.sub(
        r"return \*\(([^;]+)\);",
        r"return *(u8 *)(\1);",
        text,
    )
    text = text.replace("->unk", "->unk_")
    return text


def looks_uncompilable(body: str) -> bool:
    return any(tok in body for tok in _UNCOMPILABLE)


def match_flags(function: str, seed_text: str) -> list[str]:
    """Flags from the seed, else the parked/matched C for this function.

    The permuter preprocesses base.c before calling compile.sh, so the comment
    cannot be read at compile time — this is written to a `matchflags` sidecar
    that compile.sh picks up from the workdir.
    """
    texts = [seed_text]
    for path in (WIP / f"{function}.c", MATCHED / f"{function}.c"):
        if path.is_file():
            texts.append(path.read_text())
    for text in texts:
        found = MATCH_FLAGS_RE.search(text)
        if not found:
            continue
        flags = [f for f in shlex.split(found.group(1)) if f in ALLOWED_MATCH_FLAGS]
        if flags:
            return flags
    return []


def match_compiler(function: str, seed_text: str) -> str:
    """Compiler from the seed, else the parked/matched C for this function.

    Like match_flags, this has to be a sidecar: the permuter preprocesses base.c,
    so compile.sh cannot read the comment itself.
    """
    texts = [seed_text]
    for path in (WIP / f"{function}.c", MATCHED / f"{function}.c"):
        if path.is_file():
            texts.append(path.read_text())
    for text in texts:
        found = MATCH_COMPILER_RE.search(text)
        if not found:
            continue
        name = found.group(1).strip()
        if name in ALLOWED_COMPILERS:
            return name
        print(
            f"warning: unsupported match-compiler `{name}` for {function}; "
            f"allowed: {', '.join(ALLOWED_COMPILERS)}",
            file=sys.stderr,
        )
    return "agbcc"


KNOWN_SEEDS = {
    "sub_08072F94": """#include "global.h"
#include "ram_map.h"

u8 sub_08072F94(void)
{
    u32 tmp[2];
    u32 *ptr;

    tmp[0] = gBtlLookupBase;
    ptr = (u32 *)gBtlLookupPtr;
    tmp[0] = tmp[0] + *ptr;
    return *(u8 *)tmp[0];
}
""",
    "sub_0806DEC8": """#include "global.h"

struct UnkDEC8Head
{
    u32 unk00;
    s32 unk04;
};

struct UnkDEC8
{
    struct UnkDEC8Head *unk00;
    u8 filler04[4];
    u8 *unk08;
};

u8 *sub_0806DEC8(struct UnkDEC8 *a, s32 index)
{
    u8 *node;
    s32 count;
    s32 i;

    node = a->unk08;
    count = a->unk00->unk04;
    for (i = 0; i < count; i++)
    {
        if (i == index)
            return node;
        node += *(u32 *)(node + 4);
    }
    return 0;
}
""",
    "sub_08061BDC": """#include "global.h"

void sub_08061BDC(struct Unk61BDC *a)
{
    if (a == 0)
        return;
    a->unk14 = 1;
}
""",
    "sub_08062634": """#include "global.h"

void sub_08062634(struct Unk62634 *a, u32 b, u32 c, u32 d)
{
    if (a == 0)
        return;
    a->unk1C = b;
    a->unk20 = c;
    a->unk18 = d;
}
""",
    "sub_08066434": """#include "global.h"

u8 sub_08066434(void)
{
    u32 tmp[2];
    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x34;
    return *(u8 *)tmp[0];
}
""",
    "sub_08066440": """#include "global.h"

void sub_08066440(u8 v)
{
    u32 tmp[2];
    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    *(u8 *)tmp[0] = v;
}
""",
    "sub_0806644C": """#include "global.h"

s8 sub_0806644C(void)
{
    u32 tmp[2];
    s32 val;
    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    val = *(u8 *)tmp[0];
    val <<= 24;
    val >>= 24;
    return (s8)val;
}
""",
    "sub_08062A1C": """#include "global.h"

void sub_08062A1C(u32 v)
{
    u32 tmp[2];
    tmp[0] = gUnk_030007B0;
    tmp[0] += 0x114;
    *(u32 *)tmp[0] = v;
}
""",
    "sub_0806639C": """#include "global.h"

void *sub_0806639C(void)
{
    u32 tmp[2];
    void **base;
    s32 idx;

    tmp[0] = 0x080BA1A8;
    base = (void **)tmp[0];
    idx = (s8)*(u8 *)gUnk_03000964;
    idx <<= 2;
    return *(void **)((u8 *)base + idx);
}
""",
    "sub_08031294": """#include "global.h"

void sub_08031294(struct Unk312EC *a)
{
    u8 r1;
    u8 r2;

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
}
""",
    "sub_0803DD60": """#include "global.h"

u32 sub_0803DD60(u32 idx)
{
    u32 tmp[3];
    u32 **tables;
    u32 *row;
    u8 sel;

    tmp[0] = 0x0807B0C4;
    tables = (u32 **)tmp[0];
    tmp[1] = (u32)gMainWorkPtr + 0x1818;
    sel = *(u8 *)tmp[1];
    row = tables[sel];
    return row[idx];
}
""",
    "sub_080674BC": """#include "global.h"

u32 sub_080674BC(u32 a)
{
    u16 v;
    u32 r2;

    v = (u16)a;
    r2 = 0;
    if (v == 4)
        *(u32 *)gUnk_030009B0 = 0x083A93C8;
    else if (v == 0x40)
        *(u32 *)gUnk_030009B0 = 0x083A93D4;
    else
    {
        *(u32 *)gUnk_030009B0 = 0x083A93C8;
        r2 = 1;
    }
    return r2;
}
""",
    "sub_080617C4": """#include "global.h"

void sub_080617C4(struct Unk617C4 *a, u32 b)
{
    struct Unk617C4 *r2;
    struct Unk0798 *mw;

    r2 = a;
    if ((a->unk0C & 1) == 0)
        return;
    mw = gUnk_03000798;
    mw->unk88 = (void *)a;
    mw->unk8C = b;
    mw->unkA0 = a->unk04;
    mw->unkA2 = a->unk05;
    mw->unk9C = mw->unkA0 >> 2;
}
""",
    "sub_080615EC": """#include "global.h"

void sub_080615EC(u16 x, u16 y)
{
    u32 tmp[2];
    u16 r2;
    u16 r3;

    r2 = x;
    r3 = y;
    if (r2 > 0xEF)
        r2 = 0;
    if (r3 > 0x9F)
        r3 = 0;
    tmp[0] = (u32)gUnk_03000798;
    tmp[0] += 0x90;
    *(u16 *)tmp[0] = r2;
    tmp[0] = (u32)gUnk_03000798;
    tmp[0] += 0x92;
    *(u16 *)tmp[0] = r3;
}
""",
    "sub_0802D8C4": """#include "global.h"

void sub_0802D8C4(s32 a)
{
    u16 v;
    struct Unk026C *mw;
    struct Unk705DC *p;

    v = (u16)a;
    mw = *(struct Unk026C **)gUnk_0300026C;
    p = mw->unk08;
    if (p != 0)
        p->unk18 = v;
}
""",
    "sub_0803DD88": """#include "global.h"

s32 sub_0803DD88(s32 a)
{
    u32 base;
    u32 idx;
    u32 row;

    base = 0x0807A1F4;
    row = gMainWorkPtr->unk1818;
    idx = a;
    idx = (idx << 2) + idx;
    idx <<= 3;
    idx += row << 2;
    return *(s32 *)(base + idx);
}
""",
    "sub_0806FDB4": """#include "global.h"

struct Unk6FDB4 *sub_0806FDB4(struct Unk6FDB4 *p, u16 key)
{
    struct Unk6FDB4 *cur;
    u16 k;
    struct Unk6FDB4 *prev;

    cur = p;
    k = key;
    k &= 0xFFFF;
    prev = 0;
    if (cur == 0)
        return prev;
    while (1)
    {
        if (cur->unk22 >= k)
            break;
        prev = cur;
        cur = cur->unk04;
        if (cur == 0)
            break;
    }
    return prev;
}
""",
    "sub_0806A954": """#include "global.h"

void *sub_0806A954(u8 a)
{
    u32 tmp[2];
    u8 idx;

    idx = a;
    if (idx > 9)
        return 0;
    tmp[0] = 0x03003F70;
    return (void *)(tmp[0] + (u32)idx * 24);
}
""",
    "sub_0806FF28": """#include "global.h"
#include "ram_map.h"

void sub_0806FF28(struct BtlObj *a)
{
    struct BtlObj *r3;
    struct BtlObjNode *prev;
    struct BtlObjNode *next;
    struct BtlObjNode *old;

    r3 = a;
    if (a->unk19 != 0)
        return;
    prev = a->next;
    next = a->prev;
    if (prev != 0)
        prev->prev = next;
    else
        gBtlObjListTail = next;
    if (next != 0)
        next->next = prev;
    old = gBtlObjListHead;
    a->prev = old;
    gBtlObjListHead = (struct BtlObjNode *)a;
}
""",
    "sub_08031294": """#include "global.h"

void sub_08031294(struct Unk312EC *a)
{
    u8 r1;
    u8 r2;

    r1 = 0xFF;
    r2 = (u8)a->unk00;
    r2 = (u8)(r2 | r1);
    a->unk00 = (s8)r2;
    r2 = (u8)a->unk01;
    r1 = (u8)(r1 | r2);
    a->unk01 = (s8)r1;
    r1 = 1;
    r1 = (u8)(-((s8)r1));
    a->unk04 = (s32)(s8)r1;
    r1 = 0;
    a->unk0C = 0;
    a->unk08 = r1;
}
""",
    "sub_080473E4": """#include "global.h"

void sub_080473E4(void)
{
    u32 *p634;
    u32 *p63c;

    p634 = (u32 *)gUnk_03000634;
    p63c = (u32 *)gUnk_0300063C;
    *p634 = 0;
    *p63c = 0;
}
""",
    "sub_08033958": """#include "global.h"

s32 sub_08033958(struct Unk33958 *a)
{
    s32 r2;
    u32 r3;
    s32 r1;

    r2 = 0;
    r3 = 0;
    r1 = a->unk00;
    if (r1 == *a->unk04)
        r2 = 1;
    return r2;
}
""",
    "sub_08033574": """#include "global.h"

void sub_08033574(void)
{
    u32 v;

    if (gBattleWork->unk2088 == 1)
    {
        v = gBattleWork->unk1FE6;
        v >>= 1;
        sub_08068808((struct Unk68574 *)&gBattleWork->unk1FAC);
        sub_08038638((u16)v);
    }
    gBattleWork->unk2089 = 0xFF;
    gBattleWork->unk2088 = 0;
}
""",
    "sub_080312B0": """#include "global.h"

void sub_080312B0(struct Unk312EC *a, struct Unk705DC *b, u8 c, s32 d)
{
    u16 raw;
    u8 shifted;

    if (a->unk08 != 0 || b == NULL)
        return;

    raw = b->unk14;
    shifted = raw >> 0xC;
    a->unk00 = c;
    a->unk01 = shifted;
    a->unk04 = d;
    a->unk0C = b;
    a->unk08 = 1;
}
""",
    "sub_08031300": """#include "global.h"

void sub_08031300(struct Unk312EC *a)
{
    s32 n;
    struct Unk705DC *node;
    s8 val;

    if (a->unk08 == 0)
        return;
    n = a->unk04;
    if (n < 0)
    {
        sub_080312D8(a);
        return;
    }
    n--;
    a->unk04 = n;
    node = a->unk0C;
    if (node == NULL)
        return;
    if ((n & 5) != 0)
        return;

    if ((node->unk14 >> 0xC) == a->unk01)
        val = a->unk00;
    else
        val = a->unk01;
    sub_080705DC(node, val);
}
""",
    "sub_0806FEFC": """#include "global.h"
#include "ram_map.h"
#include "battle.h"

struct BtlObjNode *sub_0806FEFC(void)
{
    struct BtlObjNode *node;
    struct BtlObjNode *tail;

    node = gBtlObjListHead;
    if (node != 0)
    {
        gBtlObjListHead = node->prev;
        tail = gBtlObjListTail;
        if (tail != 0)
            tail->next = node;
        node->prev = gBtlObjListTail;
        node->next = 0;
        gBtlObjListTail = node;
    }
    return node;
}
""",
}


def seed_c(function: str) -> str:
    wip = WIP / f"{function}.c"
    if wip.is_file():
        return wip.read_text()
    if function in KNOWN_SEEDS:
        return KNOWN_SEEDS[function]
    existing = MATCHED / f"{function}.c"
    if existing.is_file() and not is_opcode_stub(existing):
        return existing.read_text()

    header = '#include "global.h"\n#include "ram_map.h"\n#include "battle.h"\n\n'
    m2c = m2c_decompile(function, valid_syntax=True) or m2c_decompile(function)
    if not m2c:
        raise SystemExit(
            f"no semantic seed for {function}: m2c failed and src is an opcode stub"
        )
    # Prefer the same cleaned seed the agent packet shows; the permuter can only
    # reshuffle correct C, so a m2c-valid seed that still has `?` types is worse
    # than a slightly less literal cleaned one.
    cleaned = cleanup_text(m2c, function)
    if cleaned.strip() and not looks_uncompilable(cleaned):
        return header + cleaned.rstrip() + "\n"
    fallback = clean_m2c(m2c)
    if fallback and not looks_uncompilable(fallback):
        return header + fallback.rstrip() + "\n"
    raise SystemExit(
        f"no semantic seed for {function}: m2c output is not compilable C"
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function")
    parser.add_argument(
        "--keep",
        action="store_true",
        help="keep existing nonmatchings/<function>* workdirs instead of a fresh import",
    )
    args = parser.parse_args()
    name = args.function

    if not (NON / f"{name}.s").is_file():
        print(f"missing {NON / name}.s", file=sys.stderr)
        return 1
    if not PERM.is_dir():
        print("run tools/decomp/permuter/setup.sh first", file=sys.stderr)
        return 1

    staging = ROOT / "build" / "permuter-import"
    staging.mkdir(parents=True, exist_ok=True)
    c_path = staging / f"{name}.c"
    s_path = staging / f"{name}.s"
    existing_workdirs = set((ROOT / "nonmatchings").glob(f"{name}*"))
    if not args.keep:
        # Stale workdirs force import.py into `<name>-2`, `<name>-3` … and the
        # permuter then runs on an out-of-date seed. Re-import is always fresh.
        for old in sorted(existing_workdirs):
            shutil.rmtree(old, ignore_errors=True)
            print(f"removed stale workdir {old.relative_to(ROOT)}")
        existing_workdirs = set()
    seed = seed_c(name)
    c_path.write_text(seed)
    s_path.write_text(to_glabel_asm(name))
    result = subprocess.run(
        [sys.executable, str(PERM / "import.py"), str(c_path), str(s_path)],
        cwd=str(ROOT),
    )
    if result.returncode != 0:
        return result.returncode

    matches = sorted(
        set((ROOT / "nonmatchings").glob(f"{name}*")) - existing_workdirs
    )
    if matches:
        workdir = matches[-1]
    else:
        workdir = ROOT / "nonmatchings" / name
        if not workdir.is_dir():
            print("import.py did not create nonmatchings/", file=sys.stderr)
            return 1

    shutil.copy(COMPILE_SH, workdir / "compile.sh")
    (workdir / "compile.sh").chmod(0o755)

    flags = match_flags(name, seed)
    flags_path = workdir / "matchflags"
    if flags:
        flags_path.write_text("\n".join(flags) + "\n")
    else:
        flags_path.unlink(missing_ok=True)

    compiler = match_compiler(name, seed)
    compiler_path = workdir / "compiler"
    if compiler == "agbcc":
        compiler_path.unlink(missing_ok=True)
    else:
        compiler_path.write_text(compiler + "\n")

    print(f"imported {name} -> {workdir.relative_to(ROOT)}")
    if flags:
        print(f"match-flags: {' '.join(flags)} (permuter compile.sh honours these)")
    else:
        print("match-flags: none")
    print(f"match-compiler: {compiler}")
    print(
        f"next: tools/decomp/permuter/permute.sh run {workdir.relative_to(ROOT)} "
        f"-j {os.cpu_count() or 4} --stop-on-zero"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
