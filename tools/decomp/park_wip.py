#!/usr/bin/env python3
"""Park unmatched semantic C so the next session can resume.

  python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
  python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c \\
      --status "same-size DIFF" --next "permuter" --score "64/64"

Copies the seed into src/decompiled/ (the DECOMPILED lifecycle tier), writes a
notes stub if missing, and appends [[wip]] to docs/decomp-queue.toml when the
name is new.

Does not touch src/matched/ and does not link into the ROM.
"""

from __future__ import annotations

import argparse
import shutil
import sys
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from queue_toml import QUEUE, upsert_block  # noqa: E402

DECOMPILED_DIR = ROOT / "src" / "decompiled"
MATCHED = ROOT / "src" / "matched"

_NOTES_STUB = """# {name} — WIP

| | |
|--|--|
| ROM | `{addr}` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/{name}.c` |
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


def _append_wip(
    name: str,
    seed_rel: str,
    notes_rel: str,
    status: str,
    nxt: str,
    score: str,
    *,
    exhausted: bool = False,
) -> bool:
    fields = {
        "name": name,
        "seed": seed_rel,
        "notes": notes_rel,
        "status": status,
        "next": nxt,
        "score": score,
    }
    if exhausted:
        # Machine-readable, so agent_packet.py can stop offering a function that
        # is documented as unreachable instead of parsing prose.
        fields["retry"] = "false"
    return upsert_block("wip", fields)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name", help="sub_XXXXXXXX")
    parser.add_argument("seed", help="path to the C seed (copied into src/decompiled/)")
    parser.add_argument("--status", default="unmatched C parked; see notes")
    parser.add_argument("--next", dest="nxt", default="read notes; match_function.py this seed")
    parser.add_argument("--score", default="unscored")
    parser.add_argument(
        "--exhausted",
        action="store_true",
        help="record retry = false: hand and permuter attempts are documented as "
        "unreachable, so agent_packet.py --next stops offering this function",
    )
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

    DECOMPILED_DIR.mkdir(parents=True, exist_ok=True)
    dest = DECOMPILED_DIR / f"{name}.c"
    if src.resolve() != dest.resolve():
        shutil.copy2(src, dest)

    notes = DECOMPILED_DIR / f"{name}.md"
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
    inserted = _append_wip(
        name, seed_rel, notes_rel, args.status, args.nxt, args.score,
        exhausted=args.exhausted,
    )

    matched = MATCHED / f"{name}.c"
    print(f"parked {name} ({'new' if inserted else 'updated'} queue block)")
    print(f"  seed  {seed_rel}")
    print(f"  notes {notes_rel}")
    print(f"  queue {QUEUE.relative_to(ROOT).as_posix()} [[wip]]")
    if args.exhausted:
        print("  retry = false — agent_packet.py --next will skip this until --force-exhausted")
    if matched.is_file():
        print(f"  matched still {matched.relative_to(ROOT).as_posix()} (do not leave a DIFF draft there)")
    print("  next: make queue")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
