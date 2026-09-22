#!/usr/bin/env python3
"""Promote `src/wip/` to the first-class `src/decompiled/` tier.

`src/wip/` was a dead end: ~220 unmatched C seeds with real analysis value,
invisible to the workflow because the parking tool treated them as failures
rather than as a progress state. This promotes them to `src/decompiled/`, the
DECOMPILED rung of the lifecycle, where `analyze.py` and the naming pass read
them like any other source.

The tier is still NOT linked: `C_SRCS` in the Makefile is empty and nothing
globs `src/**`, so promotion cannot affect the ROM or `make compare`.

Idempotent and re-runnable — a file that already exists at the destination is
left alone, so an interrupted run can simply be repeated.

  python3 tools/decomp/promote_wip.py --dry-run
  python3 tools/decomp/promote_wip.py --apply
"""

from __future__ import annotations

import argparse
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WIP = ROOT / "src" / "wip"
DECOMPILED = ROOT / "src" / "decompiled"
QUEUE = ROOT / "docs" / "decomp-queue.toml"

OLD_REF = "src/wip/"
NEW_REF = "src/decompiled/"

_README = """# Decompiled C (not linked)

Unmatched semantic C: every function that has a C representation but does not
yet compile byte-identical to retail. This is the **DECOMPILED** tier — see
`tools/decomp/tier.py` for the lifecycle vocabulary.

These files are real work, not failures. They are:

- readable — close to the original logic, transcribed from the disassembly
- navigable — indexed in `analysis/functions.json` with callers, callees and
  RAM references
- named — picked up by the symbol layer like any other function

They are **not linked**. `C_SRCS` in the Makefile is empty and nothing globs
`src/**`, so nothing here can affect `make compare`.

Promote a seed once it byte-matches:

```bash
python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
python3 tools/decomp/integrate_c.py sub_XXXXXXXX @src/decompiled/sub_XXXXXXXX.c \\
    --kind semantic --note "…"
```

Park a new draft with `tools/decomp/park_wip.py`.

## Notes template (`src/decompiled/sub_XXXXXXXX.md`)

```markdown
# sub_XXXXXXXX — WIP

| | |
|--|--|
| ROM | `0x080XXXXX` |
| Retail | NB |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_XXXXXXXX.c` |
| Last `match_function.py` | STATUS, N/M bytes |
| Sibling / types | |

## Role

## Process

- YYYY-MM-DD — …

## Current state

## Next
```
"""


def _move(src: Path, dest: Path, *, apply: bool) -> str:
    """git mv when possible so history follows; otherwise a plain move."""
    if dest.exists():
        return "skipped"
    if not apply:
        return "would move"
    dest.parent.mkdir(parents=True, exist_ok=True)
    rel = src.relative_to(ROOT).as_posix()
    rel_dest = dest.relative_to(ROOT).as_posix()
    try:
        subprocess.run(
            ["git", "mv", rel, rel_dest],
            cwd=ROOT,
            check=True,
            capture_output=True,
        )
        return "moved"
    except (subprocess.CalledProcessError, FileNotFoundError):
        shutil.move(str(src), str(dest))
        return "moved"


def migrate_files(*, apply: bool) -> dict[str, int]:
    counts = {"moved": 0, "skipped": 0, "would move": 0}
    if not WIP.is_dir():
        return counts
    DECOMPILED.mkdir(parents=True, exist_ok=True)
    for path in sorted(WIP.iterdir()):
        if path.is_dir() or path.name == "README.md":
            continue
        result = _move(path, DECOMPILED / path.name, apply=apply)
        counts[result] = counts.get(result, 0) + 1
    return counts


def rewrite_notes_refs(*, apply: bool) -> int:
    """Point the parked-seed notes at the new location."""
    changed = 0
    if not DECOMPILED.is_dir():
        return 0
    for path in sorted(DECOMPILED.glob("*.md")):
        text = path.read_text()
        if OLD_REF not in text:
            continue
        changed += 1
        if apply:
            path.write_text(text.replace(OLD_REF, NEW_REF))
    return changed


def rewrite_queue(*, apply: bool) -> int:
    """Repoint `[[wip]]` seed/notes rows so `make queue` keeps working."""
    if not QUEUE.is_file():
        return 0
    text = QUEUE.read_text()
    if OLD_REF not in text:
        return 0
    rows = text.count(OLD_REF)
    if apply:
        QUEUE.write_text(text.replace(OLD_REF, NEW_REF))
    return rows


def write_readme(*, apply: bool) -> bool:
    dest = DECOMPILED / "README.md"
    if dest.exists() and dest.read_text() == _README:
        return False
    if apply:
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(_README)
    return True


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--apply", action="store_true", help="perform the migration")
    ap.add_argument("--dry-run", action="store_true", help="report only (default)")
    args = ap.parse_args()
    apply = args.apply and not args.dry_run

    counts = migrate_files(apply=apply)
    notes = rewrite_notes_refs(apply=apply)
    rows = rewrite_queue(apply=apply)
    readme = write_readme(apply=apply)

    mode = "applied" if apply else "dry-run"
    processed = (
        counts.get("moved", 0)
        + counts.get("skipped", 0)
        + counts.get("would move", 0)
    )
    print(f"=== promote src/wip/ -> src/decompiled/ ({mode}) ===")
    print(f"  files seen      {processed}")
    print(f"  moved           {counts.get('moved', 0)}")
    print(f"  already present {counts.get('skipped', 0)}")
    print(f"  notes updated   {notes}")
    print(f"  queue refs      {rows}")
    print(f"  README          {'written' if readme else 'unchanged'}")

    if not apply:
        print("\n  re-run with --apply to perform the migration")
        return 0

    legacy_readme = WIP / "README.md"
    if legacy_readme.is_file():
        legacy_readme.unlink()
    if WIP.is_dir() and not any(WIP.iterdir()):
        WIP.rmdir()
    print("\n  next: python3 tools/decomp/analyze.py")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
