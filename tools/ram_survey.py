#!/usr/bin/env python3
"""Dynamic RAM survey: drive the ROM in the headless mGBA harness and record
which IWRAM / EWRAM bytes are ever non-zero (RAM is cleared at boot, so non-zero
means the game wrote it). Results accumulate in build/ram_survey.json so repeated
runs (more seeds, other ROMs, other saves) only add coverage.

Usage:
  python3 tools/ram_survey.py [--rom baserom.gba] [--sav baserom.sav]
                              [--seeds 3] [--presses 400] [--seed N]
Needs tools/mod/emu/build.sh to have been run once.
"""
from __future__ import annotations

import argparse
import json
import random
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools" / "mod" / "emu"))

OUT = ROOT / "build" / "ram_survey.json"
REGIONS = {"ewram": (0x02000000, 0x40000), "iwram": (0x03000000, 0x8000)}
KEYS = ["A", "B", "START", "SELECT", "UP", "DOWN", "LEFT", "RIGHT", "L", "R",
        "A+UP", "A+DOWN", "B+LEFT"]


def accumulate(e, base: int, buf: bytearray) -> None:
    for o in range(0, len(buf), 4):
        v = e.r32(base + o)
        if v:
            for k in range(4):
                if (v >> (8 * k)) & 0xFF:
                    buf[o + k] = 1


# Allocator state (HeapAlloc sub_0806A3A4 / FastAllocate sub_0806A314). Both keep a
# list of address-ordered nodes {+0 start, +4 size, +8 prev, +C next} and place
# blocks first-fit from the bottom, so the end of the last node is the footprint.
HEAPS = {
    "main": {"head": 0x03000B30, "start": 0x02000800, "len": 0xFE << 10},
    "fast": {"head": 0x03003F44, "start": 0x03000B40, "len": 0xD0 << 6},
}


def heap_footprint(e, h) -> tuple[int, int]:
    """Return (bytes from region start to the end of the last block, block count)."""
    node, end, n = e.r32(h["head"]), 0, 0
    while h["start"] - 0x1000000 <= node < 0x04000000 and n < 0x100:
        start, size = e.r32(node), e.r32(node + 4)
        if start:
            end = max(end, start + size)
            n += 1
        node = e.r32(node + 0xC)
    return (end - h["start"] if end else 0), n


def runs(buf: bytearray, base: int) -> list[list[int]]:
    out, s = [], None
    for i, v in enumerate(buf):
        if v and s is None:
            s = i
        elif not v and s is not None:
            out.append([base + s, base + i])
            s = None
    if s is not None:
        out.append([base + s, base + len(buf)])
    return out


def run_seed(a, seed: int) -> None:
    from emu import Emu

    bufs = {n: bytearray(sz) for n, (_, sz) in REGIONS.items()}
    old = {}
    if OUT.is_file():
        old = json.loads(OUT.read_text())
        for n, (base, _) in REGIONS.items():
            for lo, hi in old.get(n, []):
                for i in range(lo - base, hi - base):
                    bufs[n][i] = 1

    e = Emu(a.rom, a.sav if a.sav and Path(a.sav).is_file() else None)
    rng = random.Random(seed)
    peak = dict(old.get("heap_peak", {}))

    def sample() -> None:
        for name, h in HEAPS.items():
            used, n = heap_footprint(e, h)
            cur = peak.setdefault(name, {"bytes": 0, "blocks": 0})
            cur["bytes"] = max(cur["bytes"], used)
            cur["blocks"] = max(cur["blocks"], n)

    def run(frames: int, keys: str = "") -> None:
        # Short steps: blocks are often freed within a few frames.
        for _ in range(0, frames, 3):
            e.frames(3, keys)
            sample()

    for it in range(a.presses):
        run(rng.randint(2, 20), rng.choice(KEYS))
        run(rng.randint(5, 40))
        if it % 4 == 0:
            run(rng.randint(30, 200))
        if it % 10 == 0:
            for n, (base, _) in REGIONS.items():
                accumulate(e, base, bufs[n])
    for n, (base, _) in REGIONS.items():
        accumulate(e, base, bufs[n])

    OUT.parent.mkdir(exist_ok=True)
    out = {n: runs(bufs[n], REGIONS[n][0]) for n in REGIONS}
    out["heap_peak"] = peak
    OUT.write_text(json.dumps(out))
    print(f"seed {seed}: " + ", ".join(f"{n} {sum(b)} B" for n, b in bufs.items())
          + f", heap peak {peak}", file=sys.stderr)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", default="baserom.gba")
    ap.add_argument("--sav", default="baserom.sav")
    ap.add_argument("--seeds", type=int, default=3)
    ap.add_argument("--presses", type=int, default=400)
    ap.add_argument("--seed", type=int, help="run exactly this seed in-process")
    a = ap.parse_args()
    if a.seed is not None:
        run_seed(a, a.seed)
        return
    # The emulator core is a singleton per process: one subprocess per seed.
    for seed in range(a.seeds):
        subprocess.run([sys.executable, __file__, "--rom", a.rom, "--sav", a.sav,
                        "--presses", str(a.presses), "--seed", str(seed)], check=True)


if __name__ == "__main__":
    main()
