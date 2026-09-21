#!/usr/bin/env python3
"""Score parked WIP seeds for functions still linked as readable Thumb.

Cheap, high-value sweep: many src/wip seeds already match retail 100% while the
linked src/matched/<fn>.c is still a naked asm block. Re-scoring every such seed
surfaces those for integrate_c.py. Runs match_function.py with both agbcc and
old_agbcc and reports the best.

usage: sweep_seeds.py [--jobs N] [--all]
"""
from __future__ import annotations

import argparse
import concurrent.futures as cf
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent
if not (ROOT / "tools").is_dir():
    ROOT = pathlib.Path("/home/username/Github/beyblade_g_revolution")
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from opcode_stubs import file_kind  # noqa: E402

SCORE_RE = re.compile(r"(\d+)/(\d+) bytes matched")


def score(fn: str, c_path: pathlib.Path, cc: str) -> tuple[int, int]:
    src = c_path.read_text()
    if cc == "old_agbcc":
        src = re.sub(r"/\*\s*match-compiler:.*?\*/", "", src)
        src = "/* match-compiler: old_agbcc */\n" + src
    else:
        src = re.sub(r"/\*\s*match-compiler:.*?\*/", "", src)
    tmp = pathlib.Path("/tmp/sweep_seeds_%s.c" % fn)
    tmp.write_text(src)
    r = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", fn, str(tmp)],
        capture_output=True, text=True, cwd=str(ROOT),
    )
    m = SCORE_RE.search(r.stdout + r.stderr)
    if not m:
        return (-1, 0)
    return int(m.group(1)), int(m.group(2))


def worker(c_path: pathlib.Path, want_all: bool) -> str | None:
    fn = c_path.stem
    linked = ROOT / "src" / "matched" / (fn + ".c")
    if not linked.exists():
        return None
    if not want_all and file_kind(linked) == "semantic":
        return None
    best = (0, 0)
    best_cc = ""
    for cc in ("agbcc", "old_agbcc"):
        try:
            got, tot = score(fn, c_path, cc)
        except Exception:  # noqa: BLE001
            continue
        if got > best[0]:
            best = (got, tot)
            best_cc = cc
    if best[1] == 0:
        return "%-14s compile error" % fn
    pct = 100.0 * best[0] / best[1]
    flag = "MATCH" if best[0] == best[1] else ("size" if best[0] else "")
    return "%-14s %3d/%-4d %5.1f%% %-10s %s" % (fn, best[0], best[1], pct, best_cc, flag)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--all", action="store_true", help="include seeds whose linked C is already semantic")
    args = ap.parse_args()
    seeds = sorted((ROOT / "src" / "wip").glob("sub_*.c"))
    out = []
    with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(worker, p, args.all): p for p in seeds}
        for fut in cf.as_completed(futs):
            res = fut.result()
            if res:
                out.append((futs[fut].stem, res))
                print(res, flush=True)
    matches = [r for _, r in out if "MATCH" in r]
    print("\nscored %d seeds; %d full matches" % (len(out), len(matches)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
