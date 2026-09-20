#!/usr/bin/env python3
"""Park unmatched semantic C so the next session can resume.

  python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c
  python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c \\
      --status "same-size DIFF" --next "permuter" --score "64/64"

Copies the seed into src/wip/, writes a notes stub if missing, and appends
[[wip]] to docs/decomp-queue.toml when the name is new.

Does not touch src/matched/ and does not link into the ROM.
"""

from __future__ import annotations

import argparse
import shutil
import sys
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WIP_DIR = ROOT / "src" / "wip"
QUEUE = ROOT / "docs" / "decomp-queue.toml"
MATCHED = ROOT / "src" / "matched"

_NOTES_STUB = """# {name} — WIP

| | |
|--|--|
| ROM | `{addr}` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/{name}.c` |
| Last `match_function.py` | {score}
| Sibling / types | |

## Role

(one sentence)

## Process

- {today} — parked. Status: {status}

## Current state

{status}

## Next

{nxt}
"""


def _addr(name: str) -> str:
    return f"0x{int(name.replace('sub_', ''), 16):08X}"


def _has_wip_name(text: str, name: str) -> bool:
    in_wip = False
    for raw in text.splitlines():
        line = raw.split("#", 1)[0].strip()
        if line.startswith("[[") and line.endswith("]]"):
            in_wip = line == "[[wip]]"
            continue
        if in_wip and line.startswith("name"):
            _, _, val = line.partition("=")
            if val.strip().strip('"') == name:
                return True
    return False


def _append_wip(
    name: str, seed_rel: str, notes_rel: str, status: str, nxt: str, score: str
) -> None:
    block = (
        f"\n[[wip]]\n"
        f'name = "{name}"\n'
        f'seed = "{seed_rel}"\n'
        f'notes = "{notes_rel}"\n'
        f'status = "{status}"\n'
        f'next = "{nxt}"\n'
        f'score = "{score}"\n'
    )
    text = QUEUE.read_text() if QUEUE.is_file() else ""
    if _has_wip_name(text, name):
        return
    if text and not text.endswith("\n"):
        text += "\n"
    QUEUE.write_text(text + block)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name", help="sub_XXXXXXXX")
    parser.add_argument("seed", help="path to the C seed (copied into src/wip/)")
    parser.add_argument("--status", default="unmatched C parked; see notes")
    parser.add_argument("--next", dest="nxt", default="read notes; match_function.py this seed")
    parser.add_argument("--score", default="unscored")
    args = parser.parse_args()

    name = args.name
    if not name.startswith("sub_"):
        print("name must be sub_XXXXXXXX", file=sys.stderr)
        return 2

    src = Path(args.seed)
    if not src.is_file():
        src = ROOT / args.seed
    if not src.is_file():
        print(f"seed not found: {args.seed}", file=sys.stderr)
        return 2

    WIP_DIR.mkdir(parents=True, exist_ok=True)
    dest = WIP_DIR / f"{name}.c"
    if src.resolve() != dest.resolve():
        shutil.copy2(src, dest)

    notes = WIP_DIR / f"{name}.md"
    if not notes.is_file():
        notes.write_text(
            _NOTES_STUB.format(
                name=name,
                addr=_addr(name),
                score=args.score,
                today=date.today().isoformat(),
                status=args.status,
                nxt=args.nxt,
            )
        )

    seed_rel = dest.relative_to(ROOT).as_posix()
    notes_rel = notes.relative_to(ROOT).as_posix()
    _append_wip(name, seed_rel, notes_rel, args.status, args.nxt, args.score)

    matched = MATCHED / f"{name}.c"
    print(f"parked {name}")
    print(f"  seed  {seed_rel}")
    print(f"  notes {notes_rel}")
    print(f"  queue {QUEUE.relative_to(ROOT).as_posix()} [[wip]]")
    if matched.is_file():
        print(f"  matched still {matched.relative_to(ROOT).as_posix()} (do not leave a DIFF draft there)")
    print("  next: make queue")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
