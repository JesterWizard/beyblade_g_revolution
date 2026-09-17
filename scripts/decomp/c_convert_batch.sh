#!/usr/bin/env bash
# Phase 3: auto-convert trivial asm patterns to C (verified against baserom).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
LIMIT="${1:-30}"

CONVERTED=$(python3 - <<'PY' "$LIMIT"
import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(".")
LIMIT = int(sys.argv[1])
MATCH = ROOT / "asm" / "matchings"
MANIFEST = ROOT / "build" / "matched.json"
manifest = json.loads(MANIFEST.read_text()) if MANIFEST.is_file() else {"functions": []}
already = {f["src"] for f in manifest["functions"] if f.get("src")}

sys.path.insert(0, str(ROOT / "scripts" / "decomp"))
from c_patterns import guess_c
from match_function import write_single_function_c

converted = 0
skipped = 0
for asm_path in sorted(MATCH.glob("sub_*.s")):
    if converted >= LIMIT:
        break
    name = asm_path.stem
    rel = f"src/matched/{name}.c"
    if rel in already:
        continue
    src_asm = ROOT / "asm" / "nonmatchings" / f"{name}.s"
    lines = src_asm.read_text().splitlines() if src_asm.is_file() else asm_path.read_text().splitlines()
    cand = guess_c(name, lines)
    if cand is None:
        continue
    with tempfile.TemporaryDirectory() as tmp:
        scratch = Path(tmp) / "scratch.c"
        write_single_function_c(name, cand.body, scratch)
        result = subprocess.run(
            ["python3", "scripts/decomp/match_function.py", name, str(scratch)],
            capture_output=True,
            text=True,
        )
    if result.returncode != 0:
        skipped += 1
        continue
    subprocess.run(
        [
            "python3",
            "scripts/decomp/integrate_c.py",
            name,
            cand.body,
            "--note",
            cand.note,
            "--skip-compare",
        ],
        check=True,
        stdout=subprocess.DEVNULL,
    )
    converted += 1
    print(f"converted {name} ({cand.note})", file=sys.stderr)

print(f"==> batch: {converted} converted, {skipped} failed verify", file=sys.stderr)
print(converted, flush=True)
PY
)

if [ "${CONVERTED:-0}" -gt 0 ]; then
  make compare
fi
