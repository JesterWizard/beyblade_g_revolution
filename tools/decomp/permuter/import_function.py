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
    return *(u8 *)(gBtlLookupBase + *(u32 *)gBtlLookupPtr);
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
