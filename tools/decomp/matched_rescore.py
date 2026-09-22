#!/usr/bin/env python3
"""Rescore linked-but-draft C against retail.

A function can sit in `build/matched.json` as `kind: "asm"` (readable Thumb is
what the ROM links) while `src/matched/<name>.c` already holds a *semantic draft*
that nobody verified.  Those drafts are free wins whenever they happen to be
byte-exact, and near-misses are prime permuter seeds -- both are invisible to
tools that only look at `src/wip/`.

usage:
    matched_rescore.py [-n N] [--min-pct P] [--integrate] [--jobs N]
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / "tools" / "decomp"))
MANIFEST = ROOT / "build" / "matched.json"
ASM_MARKER = re.compile(r"asm\(")
CMP_RE = re.compile(r"^\s*/\*\s*match-compiler:")
PCT_RE = re.compile(r"(\d+)/(\d+) bytes matched \(([\d.]+)%\)")


def has_semantic_body(path: Path) -> bool:
    """True when the draft is C rather than one big inline-asm blob."""
    try:
        text = path.read_text()
    except OSError:
        return False
    body = "\n".join(
        l for l in text.splitlines() if not l.strip().startswith("//")
    )
    return not ASM_MARKER.search(body)


def score(name: str, src: Path, compiler: str) -> tuple[str, int, int, float]:
    if compiler == "old_agbcc":
        text = src.read_text()
        text = "\n".join(l for l in text.splitlines() if not CMP_RE.match(l))
        path = Path(f"/tmp/rescore_{name}_old.c")
        path.write_text("/* match-compiler: old_agbcc */\n" + text)
    else:
        path = src
    proc = subprocess.run(
        [sys.executable, "tools/decomp/match_function.py", name, str(path)],
        capture_output=True,
        text=True,
    )
    out = proc.stdout
    first = out.splitlines()[0] if out.strip() else "?"
    m = PCT_RE.search(out)
    matched, total, pct = (int(m.group(1)), int(m.group(2)), float(m.group(3))) if m else (0, 0, 0.0)
    return first, matched, total, pct


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("-n", type=int, default=0, help="limit functions scored")
    ap.add_argument("--min-pct", type=float, default=0.0)
    ap.add_argument("--integrate", action="store_true")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument(
        "--kind",
        default="non-semantic",
        choices=["non-semantic", "semantic", "all"],
        help="which manifest kinds to rescore (default: drafts linked as non-semantic)",
    )
    ap.add_argument(
        "--write-verified",
        action="store_true",
        help="record every draft's score in build/semantic_verified.json",
    )
    args = ap.parse_args()

    funcs = json.loads(MANIFEST.read_text())["functions"]
    todo = []
    for fn in funcs:
        is_semantic = fn.get("kind") == "semantic"
        if args.kind == "non-semantic" and is_semantic:
            continue
        if args.kind == "semantic" and not is_semantic:
            continue
        src = ROOT / fn["src"]
        if not src.is_file() or not has_semantic_body(src):
            continue
        todo.append((fn["name"], src))
    if args.n:
        todo = todo[: args.n]
    print(f"matched_rescore: {len(todo)} semantic draft(s) linked as non-semantic")

    def work(item):
        name, src = item
        best = None
        for compiler in ("agbcc", "old_agbcc"):
            first, matched, total, pct = score(name, src, compiler)
            if best is None or pct > best[4]:
                best = (name, src, compiler, first, pct, matched, total)
        return best

    hits = []
    results: dict[str, dict] = {}
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for i, best in enumerate(pool.map(work, todo), 1):
            name, src, compiler, first, pct, matched, total = best
            flag = ""
            if "MATCH" in first and "DIFF" not in first:
                flag = "  <-- MATCH"
                hits.append((name, src, compiler))
            results[name] = {"pct": pct, "compiler": compiler, "score": f"{matched}/{total}"}
            if pct >= args.min_pct or flag:
                print(f"[{i:>3}/{len(todo)}] {pct:5.1f}% {compiler:10s} {name}{flag}")

    if args.write_verified:
        out = ROOT / "build" / "semantic_verified.json"
        out.write_text(
            json.dumps({"functions": results}, indent=2, sort_keys=True) + "\n"
        )
        print(f"wrote {out.relative_to(ROOT)} ({len(results)} entries)")

    print(f"\nmatched_rescore: {len(hits)} exact match(es)")
    for name, src, compiler in hits:
        print(f"  {name} ({compiler}) -> {src}")
    if args.integrate and hits:
        for name, src, compiler in hits:
            cmd = [sys.executable, "tools/decomp/integrate_c.py", name, f"@{src}", "--kind", "semantic"]
            if compiler == "old_agbcc":
                cmd += ["--note", "rescored semantic draft (old_agbcc)"]
            subprocess.run(cmd, cwd=str(ROOT), check=False)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
