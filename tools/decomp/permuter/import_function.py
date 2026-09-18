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
#include "ram_map.h"
#include "battle.h"

u32 sub_0803DD60(u32 idx)
{
    u32 **tables;
    u32 *row;

    tables = (u32 **)0x0807B0C4;
    row = tables[gMainWorkPtr->unk1818];
    return row[idx];
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
