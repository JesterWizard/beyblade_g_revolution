#!/usr/bin/env python3
"""Print a human-readable decompilation progress summary."""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

import sys

sys.path.insert(0, str(ROOT / "tools" / "decomp"))
from progress import collect, format_human, write_artifacts  # noqa: E402

STATUS = ROOT / "docs" / "decomp-status.md"
STATUS_START = "<!-- decomp-progress:start -->"
STATUS_END = "<!-- decomp-progress:end -->"


def _progress_excerpt() -> str:
    if not STATUS.is_file():
        return ""
    text = STATUS.read_text()
    if STATUS_START in text and STATUS_END in text:
        body = text.split(STATUS_START, 1)[1].split(STATUS_END, 1)[0].strip()
        return body
    return ""


def main() -> None:
    data = collect()
    write_artifacts(data)
    print(format_human(data))
    excerpt = _progress_excerpt()
    if excerpt:
        print()
        print(excerpt)
    queue_md = ROOT / "docs" / "decomp-queue.md"
    if queue_md.is_file():
        print()
        print(f"  Queue: {queue_md.relative_to(ROOT)}  (make queue to refresh)")


if __name__ == "__main__":
    main()
