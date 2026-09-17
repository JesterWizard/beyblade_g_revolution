#!/usr/bin/env bash
# Clone decomp-permuter and install Python deps. Re-run to update.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
cd "$ROOT"

if [ ! -d tools/decomp-permuter/.git ]; then
  echo "==> Cloning decomp-permuter -> tools/decomp-permuter"
  git clone --depth 1 https://github.com/simonlindholm/decomp-permuter tools/decomp-permuter
else
  echo "==> Updating tools/decomp-permuter"
  git -C tools/decomp-permuter pull --ff-only || true
fi

python3 -m pip install -q toml 2>/dev/null || pip3 install -q toml || true
python3 -c "import toml" || { echo "error: python3 module toml required" >&2; exit 1; }
chmod +x scripts/decomp/permuter/compile.sh scripts/decomp/permuter/permute.sh
echo "Done. Import a function: scripts/decomp/permuter/permute.sh import sub_08072F94"
