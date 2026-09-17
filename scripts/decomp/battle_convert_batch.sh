#!/usr/bin/env bash
# Battle subsystem C batch: try hand-verified candidates, integrate, compare once.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
LIMIT="${1:-10}"

CONVERTED=$(python3 - <<'PY' "$LIMIT"
import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(".")
LIMIT = int(sys.argv[1])
MANIFEST = ROOT / "build" / "matched.json"
manifest = json.loads(MANIFEST.read_text()) if MANIFEST.is_file() else {"functions": []}
have = {f["src"] for f in manifest["functions"] if f.get("src")}

# Hand-maintained battle C candidates: function -> (body, note)
CANDIDATES: list[tuple[str, str, str]] = [
    (
        "sub_080314FC",
        """void sub_080314FC(void)
{
    u8 *base;
    base = *(u8 **)0x03000290;
    *(u32 *)(base + 0x118) = 0x3C;
}""",
        "battle/work-init-field-118",
    ),
]

sys.path.insert(0, str(ROOT / "scripts" / "decomp"))
from match_function import write_single_function_c

converted = 0
for name, body, note in CANDIDATES:
    if converted >= LIMIT:
        break
    rel = f"src/matched/{name}.c"
    if rel in have:
        continue
    with tempfile.TemporaryDirectory() as tmp:
        scratch = Path(tmp) / "scratch.c"
        write_single_function_c(name, body, scratch)
        result = subprocess.run(
            ["python3", "scripts/decomp/match_function.py", name, str(scratch)],
            capture_output=True,
            text=True,
        )
    if result.returncode != 0:
        print(f"skip {name}: verify failed", file=sys.stderr)
        continue
    subprocess.run(
        [
            "python3",
            "scripts/decomp/integrate_c.py",
            name,
            body,
            "--note",
            note,
            "--skip-compare",
        ],
        check=True,
    )
    converted += 1
    print(f"converted {name} ({note})")

print(converted)
PY
)

if [ "${CONVERTED:-0}" -gt 0 ]; then
  make compare
fi
python3 scripts/decomp/progress.py --write

echo "==> battle_convert_batch: ${CONVERTED:-0} integrated"
