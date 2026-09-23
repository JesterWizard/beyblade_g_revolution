#!/usr/bin/env python3
"""Block-wise editing of `docs/decomp-queue.toml`.

The queue is a TOML document of `[[wip]]` blocks whose values are prose, and that
prose is full of brackets — register pins (`[r2]`), addressing modes
(`[sp, #8]`), compiler flags (`-fprologue-bugfix`). Splitting the file with a
regex over the whole text therefore tears blocks in half: `\\[\\[wip\\]\\]([^\\[]*)`
stops at the first `[r2]` inside a status note and leaves a fragment behind, which
surfaces later as a TOML parse error.

So edits here are **structural and surgical**:

  * the file is cut at *line-initial* `[[section]]` headers, which cannot occur
    inside a value, and
  * a changed field is rewritten by replacing that one line. Comments, blank
    lines, key order and formatting in untouched blocks survive byte for byte.

`--check` asserts the invariants that make that safe: splitting and rejoining is
the identity, and rewriting every field with its own parsed value is a no-op.
"""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
QUEUE = ROOT / "docs" / "decomp-queue.toml"

SECTION_HEADER = re.compile(r"^\[\[[^\]]+\]\]\s*$")
# Values are strings in this file (`name = "sub_08031300"`), but a bare TOML
# boolean is accepted too so a hand-written `retry = false` is not invisible to
# the picker, which filters on that field.
_FIELD = re.compile(r'^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(?:"(.*)"|(true|false))\s*$')


def split_sections(text: str) -> list[tuple[str, str]]:
    """(header line, body) per block; the preamble is the block with header ""."""
    out: list[tuple[str, str]] = []
    header = ""
    body: list[str] = []
    for line in text.splitlines(keepends=True):
        if SECTION_HEADER.match(line):
            out.append((header, "".join(body)))
            header, body = line, []
        else:
            body.append(line)
    out.append((header, "".join(body)))
    return out


def join_sections(sections: list[tuple[str, str]]) -> str:
    return "".join(header + body for header, body in sections)


def section_name(header: str) -> str:
    return header.strip().strip("[]").strip() if header else ""


def parse_fields(body: str) -> dict[str, str]:
    fields: dict[str, str] = {}
    for line in body.splitlines():
        hit = _FIELD.match(line.strip())
        if hit:
            fields[hit.group(1)] = hit.group(2) if hit.group(2) is not None else hit.group(3)
    return fields


def _escape(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n")


def set_fields(body: str, updates: dict[str, str]) -> str:
    """Rewrite `key = "value"` lines in place; append keys that are absent."""
    lines = body.splitlines(keepends=True)
    seen: set[str] = set()
    for index, line in enumerate(lines):
        hit = _FIELD.match(line.strip())
        if not hit or hit.group(1) not in updates:
            continue
        key = hit.group(1)
        indent = line[: len(line) - len(line.lstrip())]
        ending = "\n" if line.endswith("\n") else ""
        lines[index] = f'{indent}{key} = "{_escape(updates[key])}"{ending}'
        seen.add(key)

    pending = [(k, v) for k, v in updates.items() if k not in seen]
    if pending:
        tail = len(lines)
        while tail and not lines[tail - 1].strip():
            tail -= 1
        added = [f'{key} = "{_escape(value)}"\n' for key, value in pending]
        if tail and not lines[tail - 1].endswith("\n"):
            added[0] = "\n" + added[0]
        lines[tail:tail] = added
    return "".join(lines)


def read_sections(path: Path = QUEUE) -> list[tuple[str, str]]:
    """(section name, body) for every section, in file order."""
    if not path.is_file():
        return []
    return [
        (section_name(header), body)
        for header, body in split_sections(path.read_text())
        if header
    ]


def read_blocks(section: str = "wip", path: Path = QUEUE) -> list[dict[str, str]]:
    return [parse_fields(body) for name, body in read_sections(path) if name == section]


def block_names(path: Path = QUEUE) -> set[str]:
    return {b["name"] for b in read_blocks("wip", path) if b.get("name")}


def upsert_block(
    section: str,
    fields: dict[str, str],
    *,
    key: str = "name",
    path: Path = QUEUE,
) -> bool:
    """Insert or update the block whose `key` field matches. True if inserted.

    Updating only touches the fields given, so re-parking a name cannot silently
    leave a stale `status`/`next`/`score` behind — which is how the queue used to
    keep inviting work on functions already parked as unreachable.
    """
    identity = fields.get(key)
    if not identity:
        raise ValueError(f"fields lack the {key!r} used to identify the block")

    sections = split_sections(path.read_text()) if path.is_file() else [("", "")]
    for index, (header, body) in enumerate(sections):
        if section_name(header) != section:
            continue
        if parse_fields(body).get(key) != identity:
            continue
        sections[index] = (header, set_fields(body, fields))
        path.write_text(join_sections(sections))
        return False

    text = path.read_text() if path.is_file() else ""
    if text and not text.endswith("\n"):
        text += "\n"
    block = f"[[{section}]]\n" + "".join(
        f'{k} = "{_escape(v)}"\n' for k, v in fields.items()
    )
    path.write_text(text + "\n" + block)
    return True


def remove_blocks(
    names: set[str], *, section: str = "wip", path: Path = QUEUE
) -> int:
    if not names or not path.is_file():
        return 0
    kept: list[tuple[str, str]] = []
    removed = 0
    for header, body in split_sections(path.read_text()):
        if section_name(header) == section and parse_fields(body).get("name") in names:
            removed += 1
            continue
        kept.append((header, body))
    if removed:
        path.write_text(join_sections(kept))
    return removed


def main() -> int:
    import argparse

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="assert the invariants")
    args = parser.parse_args()

    if not args.check:
        print(f"docs/decomp-queue.toml: {len(read_blocks())} [[wip]] block(s)")
        return 0

    original = QUEUE.read_text()
    if join_sections(split_sections(original)) != original:
        print("FAIL: split/join is not the identity")
        return 1
    for header, body in split_sections(original):
        if not header:
            continue
        before = parse_fields(body)
        after = parse_fields(set_fields(body, before))
        if after != before:
            lost = {k: v for k, v in before.items() if after.get(k) != v}
            print(f"FAIL: rewriting unchanged fields in [[{section_name(header)}]] loses {lost}")
            return 1
    print(f"round-trip OK ({len(read_blocks())} blocks, formatting preserved)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
