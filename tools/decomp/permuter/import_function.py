#!/usr/bin/env python3
"""Import one function into decomp-permuter's nonmatchings/ workdir.

Converts Luvdis nonmatching asm to `glabel` form, builds a semantic C seed
(m2c, cleaned, or existing readable src), then runs import.py.

Does not replace src/matched/*.c — integrate only after permuter score 0
and match_function.py MATCH.
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from m2c_asm import m2c_decompile  # noqa: E402
from opcode_stubs import is_opcode_stub  # noqa: E402

NON = ROOT / "asm" / "nonmatchings"
MATCHED = ROOT / "src" / "matched"
PERM = ROOT / "tools" / "decomp-permuter"
COMPILE_SH = ROOT / "tools" / "decomp" / "permuter" / "compile.sh"


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
    register u8 m asm("r1");
    m = 0xFF;
    a->unk00 = (s8)((u8)a->unk00 | m);
    a->unk01 = (s8)((u8)a->unk01 | m);
    m = 1;
    m = (u8)-m;
    a->unk04 = (s32)m;
    a->unk0C = 0;
    a->unk08 = 0;
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
    register u16 v asm("r0");
    register u32 r2 asm("r2");

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
    register struct Unk617C4 *r2 asm("r2");
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
    register u16 r2 asm("r2");
    register u16 r3 asm("r3");

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
    register u16 v asm("r1");
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
    register struct Unk6FDB4 *cur asm("r0");
    register u16 k asm("r1");
    register struct Unk6FDB4 *prev asm("r2");

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
    register struct BtlObj *r3 asm("r3");
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
    if function in KNOWN_SEEDS:
        return KNOWN_SEEDS[function]
    existing = MATCHED / f"{function}.c"
    if existing.is_file() and not is_opcode_stub(existing):
        return existing.read_text()

    m2c = m2c_decompile(function, valid_syntax=True) or m2c_decompile(function)
    cleaned = clean_m2c(m2c) if m2c else None
    if cleaned:
        return f'#include "global.h"\n#include "ram_map.h"\n#include "battle.h"\n\n{cleaned}\n'

    raise SystemExit(
        f"no semantic seed for {function}: m2c failed and src is an opcode stub"
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function")
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
    c_path.write_text(seed_c(name))
    s_path.write_text(to_glabel_asm(name))
    result = subprocess.run(
        [sys.executable, str(PERM / "import.py"), str(c_path), str(s_path)],
        cwd=str(ROOT),
    )
    if result.returncode != 0:
        return result.returncode

    workdir = ROOT / "nonmatchings" / name
    if not workdir.is_dir():
        # import.py may suffix -2, -3 on reimport
        matches = sorted((ROOT / "nonmatchings").glob(f"{name}*"))
        if not matches:
            print("import.py did not create nonmatchings/", file=sys.stderr)
            return 1
        workdir = matches[-1]

    shutil.copy(COMPILE_SH, workdir / "compile.sh")
    (workdir / "compile.sh").chmod(0o755)
    print(f"imported {name} -> {workdir.relative_to(ROOT)}")
    print(f"next: tools/decomp/permuter/permute.sh run {workdir.relative_to(ROOT)} -j 4 --stop-on-zero")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
