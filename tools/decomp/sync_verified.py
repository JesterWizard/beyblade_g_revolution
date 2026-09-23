#!/usr/bin/env python3
"""Keep `build/semantic_verified.json` in step with the manifest.

`progress.py` and `tier.py` count "semantic C" from `build/matched.json` only for
functions listed in `build/semantic_verified.json`: `file_kind()` infers the kind
from the text of `src/matched/*.c` (a semantic body has no `asm()`), and a text
guess is demoted to `asm` unless the name is recorded. That makes the list the
authority, which is right — but it is only ever written by
`matched_rescore.py --write-verified`, so anything that lands semantic C another
way (a hand edit to `src/matched/*.c`, as with the BIOS wrappers
`sub_080674A0`..`sub_080674B4`) is invisible to the progress counter.

`integrate_c.py` now records what it lands. This tool repairs the rest, and is
safe to re-run: it registers exactly the functions the manifest calls semantic
whose bodies still look semantic.

usage: sync_verified.py [--apply] [--check]
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

import integrate_c  # noqa: E402
from opcode_stubs import file_kind  # noqa: E402

MANIFEST = ROOT / "build" / "matched.json"
VERIFIED = ROOT / "build" / "semantic_verified.json"


def missing() -> list[str]:
    if not MANIFEST.is_file():
        return []
    manifest = json.loads(MANIFEST.read_text()).get("functions", [])
    verified = set()
    if VERIFIED.is_file():
        verified = set(json.loads(VERIFIED.read_text()).get("functions", {}))
    out: list[str] = []
    for entry in manifest:
        if entry.get("kind") != "semantic" or entry["name"] in verified:
            continue
        path = ROOT / entry["src"]
        # The manifest is written after verification, so `kind` is trustworthy;
        # the body check is a second opinion in case the file was replaced by a
        # readable-Thumb wrapper since.
        if path.is_file() and file_kind(path) == "semantic":
            out.append(entry["name"])
    return sorted(out)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true", help="record them")
    parser.add_argument(
        "--check", action="store_true", help="exit 1 if any are missing (for CI/batch gates)"
    )
    args = parser.parse_args()

    names = missing()
    if not names:
        print("semantic_verified.json is in step with the manifest")
        return 0
    print(f"{len(names)} semantic function(s) missing from semantic_verified.json:")
    for name in names:
        print(f"  {name}")
    if args.apply:
        manifest = json.loads(MANIFEST.read_text()).get("functions", [])
        src_of = {e["name"]: e["src"] for e in manifest}
        for name in names:
            body = (ROOT / src_of[name]).read_text()
            integrate_c.record_semantic_verified(name, body, "semantic")
        print(f"recorded {len(names)} entr(ies) in build/semantic_verified.json")
        return 0
    if args.check:
        return 1
    print("re-run with --apply to record them")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
