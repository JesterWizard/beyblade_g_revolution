#!/usr/bin/env bash
# decomp-permuter compile script (agbcc pipeline).
#
# Called as: compile.sh <input.c> -o <output.o>
# <input.c> is already preprocessed (import.py / permuter base.c), so comments
# are gone by the time we run. -Werror is dropped so a warning-only permutation
# still compiles.
#
# Per-function agbcc flags live in a `matchflags` sidecar next to this script
# (written by import_function.py from the `/* match-flags: ... */` comment in
# the seed C). This is required to match retail: 21 functions in this repo need
# `-fprologue-bugfix`, without which agbcc emits a `push {lr}` / `pop {pc}`
# prologue that retail does not have, so the permuter can never reach score 0.
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
  echo "error: tools/agbcc/bin/agbcc missing — run build_tools.sh" >&2
  exit 1
fi

# Match flags are the only supported extra flags (see match_function.py
# ALLOWED_MATCH_FLAGS); anything else here is a typo we want to fail loudly on.
EXTRA_FLAGS=()
FLAGS_FILE="$here/matchflags"
if [ -f "$FLAGS_FILE" ]; then
  while IFS= read -r flag; do
    flag="${flag%%#*}"
    flag="$(echo "$flag" | tr -d '[:space:]')"
    [ -n "$flag" ] || continue
    case "$flag" in
      -fprologue-bugfix | -fomit-frame-pointer) EXTRA_FLAGS+=("$flag") ;;
      *)
        echo "error: unsupported match flag '$flag' in $FLAGS_FILE" >&2
        exit 1
        ;;
    esac
  done <"$FLAGS_FILE"
fi

# Compiler choice. pret/agbcc installs two compilers and they do not generate
# identical code, so a function that only matches with the older one records
# `/* match-compiler: old_agbcc */`, which import_function.py writes to a
# `compiler` sidecar next to this script.
CC="tools/agbcc/bin/agbcc"
COMPILER_FILE="$here/compiler"
if [ -f "$COMPILER_FILE" ]; then
  want="$(tr -d '[:space:]' <"$COMPILER_FILE")"
  case "$want" in
    "" | agbcc) ;;
    old_agbcc) CC="tools/agbcc/bin/old_agbcc" ;;
    *)
      echo "error: unsupported match-compiler '$want' in $COMPILER_FILE" >&2
      exit 1
      ;;
  esac
fi
if [ ! -x "$CC" ]; then
  echo "error: $CC missing — run build_tools.sh" >&2
  exit 1
fi

ASM="$(mktemp --suffix=.s)"
trap 'rm -f "$ASM"' EXIT

"$CC" \
  "$INPUT" -o "$ASM" \
  -mthumb-interwork -Wimplicit -Wparentheses -O2 -g -fhex-asm \
  "${EXTRA_FLAGS[@]}"
arm-none-eabi-as -mcpu=arm7tdmi -mthumb-interwork "$ASM" -o "$OUTPUT"
