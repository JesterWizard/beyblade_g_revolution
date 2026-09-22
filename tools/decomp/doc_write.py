#!/usr/bin/env python3
"""Idempotent writes for generated docs.

The status tools rewrite several docs on every invocation.  Their payloads
almost always differ only in a `generated` timestamp (or in a couple of
counters), so a naive `write_text` dirties 5-6 tracked files per call, makes
every batch commit touch a dozen files, and forces a full re-read.

`write_doc` skips the write when the file would change only in its timestamp
line, so a batch commit touches the docs only when the numbers actually moved.
"""

from __future__ import annotations

import json
import re
from pathlib import Path

_TIMESTAMP_RE = re.compile(
    r'"(?:generated|updated)"\s*:\s*"[^"]*"|_Updated: [^\n_]*_'
)


def strip_timestamps(text: str) -> str:
    return _TIMESTAMP_RE.sub("", text)


def write_doc(path: Path, text: str) -> bool:
    """Write `text` unless the file already matches apart from timestamps.

    Returns True when the file was (re)written.
    """
    path = Path(path)
    if path.is_file():
        old = path.read_text()
        if old == text or strip_timestamps(old) == strip_timestamps(text):
            return False
    path.write_text(text)
    return True


def dump_json(payload: object) -> str:
    return json.dumps(payload, indent=2) + "\n"
