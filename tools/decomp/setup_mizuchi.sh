#!/usr/bin/env bash
# Clone and build Mizuchi into tools/mizuchi/ (gitignored).
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
MIZ="$ROOT/tools/mizuchi"
REPO="https://github.com/macabeus/mizuchi.git"

cd "$ROOT"

if [ ! -d "$MIZ/.git" ]; then
  echo "==> Cloning Mizuchi"
  git clone --depth 1 "$REPO" "$MIZ"
fi

cd "$MIZ"

# Submodule URLs may be SSH; rewrite to HTTPS for keyless clones.
if [ -f .gitmodules ]; then
  git config -f .gitmodules --get-regexp '^submodule\..*\.url$' 2>/dev/null \
    | while read -r key url; do
      case "$url" in
        git@github.com:*)
          https="https://github.com/${url#git@github.com:}"
          https="${https%.git}.git"
          sect="${key%.url}"
          git config "$sect.url" "$https"
          ;;
      esac
    done
  git submodule sync --recursive 2>/dev/null || true
  git submodule update --init --recursive 2>/dev/null || true
fi

if command -v npm >/dev/null 2>&1; then
  npm ci 2>/dev/null || npm install
  npm run build
else
  echo "warning: npm not found — install Node.js to build Mizuchi CLI" >&2
fi

echo "Mizuchi ready at $MIZ"
