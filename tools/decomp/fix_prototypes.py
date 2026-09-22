#!/usr/bin/env python3
"""Align draft C definitions with `include/unknown-functions.h`.

Drafts that were never compiled often declare a signature that disagrees with
the shared prototype header; agbcc then fails with `conflicting types` and the
file silently sits in `src/matched/` while the ROM links readable Thumb.  This
rewrites the *definition line* in the draft to the header's prototype (same name
and parameter count only) and rescores.

usage: fix_prototypes.py [fn ...] [--all] [--dry-run]
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
HEADER = ROOT / "include" / "unknown-functions.h"
MANIFEST = ROOT / "build" / "matched.json"
PCT_RE = re.compile(r"(\d+)/(\d+) bytes matched \(([\d.]+)%\)")
PROTO_RE = re.compile(
    r"^\s*(?P<ret>[A-Za-z_][\w \t*]*?)\s+(?P<name>[A-Za-z_]\w*)\s*\((?P<args>[^)]*)\)\s*;",
    re.M,
)


def prototypes() -> dict[str, str]:
    text = HEADER.read_text()
    out = {}
    for m in PROTO_RE.finditer(text):
        out[m.group("name")] = f"{m.group('ret')} {m.group('name')}({m.group('args')})"
    return out


def score(name: str, path: Path, compiler: str) -> str:
    p = path
    if compiler == "old_agbcc":
        p = Path(f"/tmp/fixproto_{name}.c")
        p.write_text("/* match-compiler: old_agbcc */\n" + path.read_text())
    proc = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", name, str(p)],
        capture_output=True,
        text=True,
    )
    return proc.stdout + proc.stderr


def pct_of(out: str) -> float:
    m = PCT_RE.search(out)
    return float(m.group(3)) if m else 0.0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("functions", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    protos = prototypes()
    funcs = json.loads(MANIFEST.read_text())["functions"]
    if args.functions:
        names = args.functions
    elif args.all:
        names = [f["name"] for f in funcs]
    else:
        ap.error("pass function names or --all")

    fixed = []
    for name in names:
        path = ROOT / "src" / "matched" / f"{name}.c"
        if not path.is_file():
            continue
        out = score(name, path, "agbcc")
        if "conflicting types" not in out:
            continue
        proto = protos.get(name)
        if not proto:
            print(f"  {name}: no prototype in header")
            continue
        text = path.read_text()
        # The definition duplicates the name at line start with no trailing `;`.
        new_text, n = re.subn(
            rf"^([A-Za-z_][\w \t*]*?)\b{re.escape(name)}\s*\([^)]*\)",
            proto,
            text,
            count=1,
            flags=re.M,
        )
        if not n or new_text == text:
            print(f"  {name}: could not rewrite definition line")
            continue
        if args.dry_run:
            print(f"  {name}: {proto}")
            continue
        path.write_text(new_text)
        best = None
        for compiler in ("agbcc", "old_agbcc"):
            out2 = score(name, path, compiler)
            p = pct_of(out2)
            if best is None or p > best[1]:
                best = (compiler, p, out2)
        tag = "MATCH" if "MATCH" in best[2].splitlines()[0] else "DIFF"
        print(f"  {name}: {best[1]:5.1f}% [{best[0]}] {tag}   ({proto})")
        if tag == "MATCH":
            fixed.append(name)
    print(f"\nfix_prototypes: {len(fixed)} now matching: {', '.join(fixed)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
