#!/usr/bin/env bash
# One-shot bootstrap for hands-off decompilation tooling.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"

echo "==> Beyblade G Revolution decomp bootstrap"

need() {
  command -v "$1" >/dev/null 2>&1 || { echo "error: missing $1" >&2; exit 1; }
}

need git
need python3
need arm-none-eabi-as
need arm-none-eabi-ld
need gcc

if [ ! -f baserom.gba ]; then
  echo "error: baserom.gba not found in repo root" >&2
  exit 1
fi

# agbcc (matching compiler)
if [ ! -x tools/agbcc/bin/agbcc ]; then
  echo "==> Installing agbcc into tools/agbcc"
  if [ ! -d ../agbcc/.git ]; then
    git clone https://github.com/pret/agbcc ../agbcc
  fi
  (cd ../agbcc && ./build.sh && ./install.sh "$ROOT")
fi

# pret build tools (gbafix only — preproc needs full pokeemerald tree)
if [ ! -x tools/gbafix/gbafix ]; then
  echo "==> Building gbafix"
  make -C tools gbafix || true
fi

# Luvdis Python deps
pip3 install -q click-default-group click tqdm 2>/dev/null || true

# Luvdis disassembler (optional submodule)
if [ ! -d tools/luvdis/.git ]; then
  echo "==> Cloning Luvdis"
  git submodule add https://github.com/aarant/luvdis tools/luvdis 2>/dev/null \
    || git clone --depth 1 https://github.com/aarant/luvdis tools/luvdis
fi

# Generate per-function assembly if missing
if [ ! -d asm/nonmatchings ] || [ -z "$(ls -A asm/nonmatchings 2>/dev/null || true)" ]; then
  echo "==> Generating assembly from baserom"
  python3 tools/decomp/generate_asm.py
fi

# Mizuchi (optional — needs npm; Cursor uses script_first.py / agent_packet.py)
if command -v npm >/dev/null 2>&1 && [ ! -d tools/mizuchi/.git ]; then
  echo "==> Setting up Mizuchi (optional)"
  bash tools/decomp/setup_mizuchi.sh || true
fi

# m2c for programmatic decomp seeds
if [ ! -d tools/m2c/m2c ]; then
  echo "==> Cloning m2c"
  git clone --depth 1 https://github.com/matt-kempster/m2c tools/m2c
fi

# decomp-permuter (agbcc matching at scale)
if [ ! -d tools/decomp-permuter/.git ]; then
  echo "==> Setting up decomp-permuter"
  bash tools/decomp/permuter/setup.sh || true
fi

echo "==> Verifying matching build"
make compare

echo "==> Bootstrap complete"
echo "    Next: tools/decomp/run_batch.sh 10"
