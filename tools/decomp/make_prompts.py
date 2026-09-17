#!/usr/bin/env python3
"""Write Mizuchi prompt stubs for the easiest N non-matching functions."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PROMPTS = ROOT / "tools" / "decomp" / "prompts"
ASM = ROOT / "asm" / "nonmatchings"


def triage(n: int) -> list[str]:
    out = subprocess.check_output(
        [sys.executable, str(ROOT / "tools/decomp/triage_functions.py"), "-n", str(n), "--json"],
        text=True,
    )
    return json.loads(out)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", type=int, default=10)
    args = parser.parse_args()

    PROMPTS.mkdir(parents=True, exist_ok=True)

    # Clear old batch prompts only (keep hand-crafted ones without batch_ prefix)
    for old in PROMPTS.glob("batch_*.md"):
        old.unlink()

    names = triage(args.n)
    for name in names:
        asm_path = ASM / f"{name}.s"
        if not asm_path.is_file():
            continue
        body = asm_path.read_text()
        prompt = PROMPTS / f"batch_{name}.md"
        prompt.write_text(
            f"# Decompile `{name}`\n\n"
            f"Target function: `{name}`\n\n"
            f"```asm\n{body}\n```\n"
        )

    print(f"make_prompts: wrote {len(names)} prompts to {PROMPTS}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
