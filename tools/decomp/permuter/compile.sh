#!/usr/bin/env bash
# decomp-permuter compile script (agbcc pipeline).
#
# Called as: compile.sh <input.c> -o <output.o>
# <input.c> is already preprocessed (import.py / permuter base.c).
# -Werror is dropped so a warning-only permutation still compiles.
set -euo pipefail

INPUT="$(realpath "$1")"
OUTPUT="$(realpath "$3")"
here="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
ROOT="$here"
while [ ! -f "$ROOT/permuter_settings.toml" ] && [ "$ROOT" != / ]; do
  ROOT="$(dirname "$ROOT")"
done
cd "$ROOT"

if [ ! -x tools/agbcc/bin/agbcc ]; then
  echo "error: tools/agbcc/bin/agbcc missing — run scripts/setup.sh" >&2
  exit 1
fi

ASM="$(mktemp --suffix=.s)"
trap 'rm -f "$ASM"' EXIT

tools/agbcc/bin/agbcc \
  "$INPUT" -o "$ASM" \
  -mthumb-interwork -Wimplicit -Wparentheses -O2 -g -fhex-asm
arm-none-eabi-as -mcpu=arm7tdmi -mthumb-interwork "$ASM" -o "$OUTPUT"
