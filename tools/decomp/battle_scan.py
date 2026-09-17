#!/usr/bin/env python3
"""List functions that reference battle IWRAM symbols (for Phase 3 prioritization)."""

from __future__ import annotations

import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NON = ROOT / "asm" / "nonmatchings"

BATTLE_SYMBOLS = {
    0x03000198: "gMainWorkPtr",
    0x03000290: "gBattleWork",
    0x03003F60: "gBtlInputMask",
    0x03003F64: "gBtlState",
    0x03004060: "gBattlerArena/gBtlKeysHeld",
    0x0300406C: "gBtlKeysNew",
    0x03004070: "gBtlKeyQueuePtr",
    0x03004074: "gBtlKeyQueueCount",
    0x030040A8: "gBtlObjListHead",
    0x030040B8: "gBtlObjListTail",
    0x03004130: "gBtlLookupBase",
    0x03004148: "gBtlLookupPtr",
    0x03004150: "gBtlObjTable",
    0x03004154: "gBtlObjTableCount",
    0x03004158: "gBtlObjLiveCount",
}


def score(path: Path) -> tuple[int, int, list[str]]:
    text = path.read_text()
    hits: list[str] = []
    for addr, name in BATTLE_SYMBOLS.items():
        if f"0x{addr:08X}" in text:
            hits.append(name)
    insns = sum(
        1
        for ln in text.splitlines()
        if ln.strip()
        and not ln.strip().startswith(("@", ".", "_"))
        and ":" not in ln.strip()
    )
    bl = text.count(" bl ")
    return len(hits), insns + bl * 3, hits


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("-n", type=int, default=40)
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    rows: list[tuple[int, int, str, list[str]]] = []
    for path in sorted(NON.glob("sub_*.s")):
        n, complexity, names = score(path)
        if n:
            rows.append((n, complexity, path.stem, names))
    rows.sort(key=lambda r: (-r[0], r[1]))

    if args.json:
        import json

        print(json.dumps([name for _, _, name, _ in rows[: args.n]]))
        return 0

    print(f"Battle-related functions: {len(rows)} / {len(list(NON.glob('sub_*.s')))}")
    for n, complexity, name, names in rows[: args.n]:
        sym = ", ".join(names[:3])
        if len(names) > 3:
            sym += ", …"
        print(f"{n:2d} refs  score={complexity:4d}  {name}  ({sym})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
