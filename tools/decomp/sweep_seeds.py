#!/usr/bin/env python3
"""Score parked WIP seeds for functions still linked as readable Thumb.

Cheap, high-value sweep: a seed in `src/wip/` can already match retail 100% while
the linked `src/matched/<fn>.c` is still a naked asm block.  One run over the
whole wip directory surfaces those for `integrate_c.py`.

Two extra diagnostics make the remaining near-misses actionable:

* `SIGNONLY` — every differing byte is the *condition* byte of a Thumb
  conditional branch (0xD0..0xDE at an odd offset) and the retail/compiled pair
  is a signed/unsigned twin (`bhi`/`bgt`, `bls`/`ble`, `bcs`/`bge`,
  `blo`/`blt`, ...).  The fix is nearly always one signedness change on the
  compared expression; see 2026-09-21 batch log for examples.
* `branch-target` — same size and only branch *offsets* differ, i.e. a layout
  rather than a shape problem.

usage:
    sweep_seeds.py [--jobs N] [--all] [--sign-only]
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import pathlib
import re
import sys

ROOT = pathlib.Path("/home/username/Github/beyblade_g_revolution")
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

import match_function as mf  # noqa: E402
from opcode_stubs import file_kind  # noqa: E402

COMPILER_RE = re.compile(r"/\*\s*match-compiler:\s*\S+?\s*\*/")

# Thumb conditional-branch condition bytes (second byte of a B<cond> halfword)
# and their signed/unsigned twins.
SIGNED_UNSIGNED = {
    0xD2: 0xDA,  # bcs/bhs  <-> bge
    0xD3: 0xDB,  # bcc/blo  <-> blt
    0xD8: 0xDC,  # bhi      <-> bgt
    0xD9: 0xDD,  # bls      <-> ble
}


def score_with(function: str, text: str, want_pragma: str | None) -> tuple[bytes, bytes, dict] | None:
    """Compile `text` with the named match-compiler pragma and score it."""
    body = COMPILER_RE.sub("", text)
    if want_pragma:
        body = "/* match-compiler: %s */\n" % want_pragma + body
    tmp = pathlib.Path("/tmp/sweep_seed_%s.c" % function)
    tmp.write_text(body)
    return mf.try_compile_and_score(function, tmp)


def branch_cond_only(got: bytes, want: bytes) -> str | None:
    """Classify a diff that touches only conditional-branch condition bytes."""
    if len(got) != len(want):
        return None
    diffs = [i for i in range(len(got)) if got[i] != want[i]]
    if not diffs:
        return None
    pairs = set()
    for i in diffs:
        if i % 2 == 0:
            return None
        a, b = want[i], got[i]
        if a not in SIGNED_UNSIGNED and b not in SIGNED_UNSIGNED:
            return None
        if SIGNED_UNSIGNED.get(a) != b and SIGNED_UNSIGNED.get(b) != a:
            return None
        pairs.add((a, b))
    return "SIGNONLY:" + ",".join("retail->compiled %02X/%02X" % p for p in sorted(pairs))


def branch_offset_only(got: bytes, want: bytes) -> bool:
    """True when only branch offsets / pool padding differ (same size, no shape change)."""
    if len(got) != len(want):
        return False
    diffs = [i for i in range(len(got)) if got[i] != want[i]]
    if not diffs:
        return False
    for i in diffs:
        partner = i - 1 if i % 2 else i + 1
        if partner >= len(got):
            return False
        hw = want[i] if i % 2 == 0 else want[i - 1]
        if not (0xD000 <= hw <= 0xDEFF) and not (0xE000 <= hw <= 0xE7FF):
            return False
    return True


def worker(c_path: pathlib.Path, want_all: bool) -> tuple[str, str] | None:
    fn = c_path.stem
    linked = ROOT / "src" / "matched" / (fn + ".c")
    if not linked.exists():
        return None
    if not want_all and file_kind(linked) == "semantic":
        return None
    text = c_path.read_text()
    best = None
    for cc in ("agbcc", "old_agbcc"):
        try:
            res = score_with(fn, text, cc)
        except Exception:  # noqa: BLE001
            continue
        if res is None:
            continue
        info = res[2]
        if best is None or info["matched_bytes"] > best[2]["matched_bytes"]:
            best = (res[0], res[1], info, cc)
    if best is None:
        return fn, "%-14s compile error" % fn
    got, want, info, cc = best
    pct = 100.0 * info["matched_bytes"] / info["retail_bytes"]
    tags = ""
    if info["matched_bytes"] == info["retail_bytes"]:
        tags = "MATCH"
    else:
        cls = branch_cond_only(got, want)
        if cls:
            tags = cls
        elif len(got) == len(want) and branch_offset_only(got, want):
            tags = "branch-target"
    line = "%-14s %3d/%-4d %5.1f%% %-10s %s" % (
        fn, info["matched_bytes"], info["retail_bytes"], pct, cc, tags)
    return fn, line


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--all", action="store_true",
                    help="include seeds whose linked C is already semantic")
    ap.add_argument("--sign-only", action="store_true",
                    help="print only SIGNONLY near-misses")
    args = ap.parse_args()

    seeds = sorted((ROOT / "src" / "wip").glob("sub_*.c"))
    rows: list[str] = []
    with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(worker, p, args.all): p for p in seeds}
        for fut in cf.as_completed(futs):
            res = fut.result()
            if res is None:
                continue
            rows.append(res[1])
    def key(r: str) -> float:
        parts = r.split()
        if len(parts) > 1 and "compile" in parts[1]:
            return 0.0
        try:
            return -float(parts[1].split("/")[0])
        except (IndexError, ValueError):
            return 0.0

    rows.sort(key=key)
    for r in rows:
        if args.sign_only and "SIGNONLY" not in r:
            continue
        print(r, flush=True)
    print("\nscored %d seeds; %d MATCH, %d SIGNONLY, %d branch-target" % (
        len(rows),
        sum("MATCH" in r for r in rows),
        sum("SIGNONLY" in r for r in rows),
        sum("branch-target" in r for r in rows),
    ))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
