#!/usr/bin/env python3
"""Prune drafts in src/decompiled/ that a semantic match has superseded.

A draft (`src/decompiled/sub_XXXXXXXX.c`) only means something while the function
is unmatched.  Once `src/matched/sub_XXXXXXXX.c` holds *semantic* C the draft is a
stale duplicate of work that already landed, and it keeps the DECOMPILED tier
inflated and the WIP queue full of tasks that are already done.

  python3 tools/decomp/prune_drafts.py            # report only
  python3 tools/decomp/prune_drafts.py --apply    # delete drafts + stub notes
  python3 tools/decomp/prune_drafts.py --apply --keep-notes

What counts as superseded:

  * `src/matched/<name>.c` exists and `opcode_stubs.file_kind()` says `semantic`
    (a readable-Thumb wrapper does *not* supersede a draft — the draft may be the
    only C that exists), and
  * the draft is not newer than the matched file's last commit-less mtime… in
    practice the matched file is the verified one, so age is not consulted.

Deleted: the draft `.c`, its `[[wip]]` block in docs/decomp-queue.toml, and — when
`--keep-notes` is absent — its `src/decompiled/<name>.md` note *if* that note is
still the machine-generated stub from park_wip.py.  Hand-written notes are always
kept, because they may record knowledge that never made it into the C.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from opcode_stubs import file_kind  # noqa: E402
from queue_toml import read_blocks, remove_blocks  # noqa: E402

DECOMPILED = ROOT / "src" / "decompiled"
MATCHED = ROOT / "src" / "matched"


def _is_stub_note(path: Path, name: str) -> bool:
    try:
        return path.read_text(errors="replace").startswith(f"# {name} — WIP")
    except OSError:
        return False


def _superseded() -> list[str]:
    out: list[str] = []
    for draft in sorted(DECOMPILED.glob("sub_*.c")):
        matched = MATCHED / draft.name
        if matched.is_file() and file_kind(matched) == "semantic":
            out.append(draft.stem)
    return out


def _queue_wip_names() -> list[tuple[str, str]]:
    """(name, seed) for every `[[wip]]` block, in file order."""
    return [(b["name"], b.get("seed", "")) for b in read_blocks() if b.get("name")]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true", help="delete instead of report")
    parser.add_argument(
        "--keep-notes",
        action="store_true",
        help="keep every src/decompiled/<name>.md, including generated stubs",
    )
    args = parser.parse_args()

    names = _superseded()
    stale_queue = {
        name
        for name, seed in _queue_wip_names()
        if name in names or not (ROOT / seed).is_file()
    }

    if not names and not stale_queue:
        print("no superseded drafts — src/decompiled/ and the WIP queue are clean")
        return 0

    drafts = [DECOMPILED / f"{n}.c" for n in names if (DECOMPILED / f"{n}.c").is_file()]
    stub_notes = [
        DECOMPILED / f"{n}.md"
        for n in names
        if (DECOMPILED / f"{n}.md").is_file()
        and not args.keep_notes
        and _is_stub_note(DECOMPILED / f"{n}.md", n)
    ]
    kept_notes = [
        DECOMPILED / f"{n}.md"
        for n in names
        if (DECOMPILED / f"{n}.md").is_file()
        and (args.keep_notes or not _is_stub_note(DECOMPILED / f"{n}.md", n))
    ]

    print(f"superseded by semantic matched C: {len(names)}")
    print(f"  draft .c to delete       {len(drafts)}")
    print(f"  notes .md to delete      {len(stub_notes)}")
    print(f"  notes .md kept           {len(kept_notes)}")
    print(f"  docs/decomp-queue.toml   {len(stale_queue)} stale [[wip]] block(s)")
    if not args.apply:
        for path in drafts[:20]:
            print(f"    {path.relative_to(ROOT).as_posix()}")
        if len(drafts) > 20:
            print(f"    … and {len(drafts) - 20} more")
        print("\nre-run with --apply to delete")
        return 0

    for path in drafts + stub_notes:
        path.unlink(missing_ok=True)
    removed = remove_blocks(stale_queue)

    print(f"pruned {len(drafts)} drafts, {len(stub_notes)} stub notes, {removed} queue blocks")
    if kept_notes:
        print("kept (hand-written notes):")
        for path in kept_notes:
            print(f"  {path.relative_to(ROOT).as_posix()}")
    print("\nnext: make analyze && make tier   # drafts no longer pollute DECOMPILED")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
