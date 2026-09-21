#!/usr/bin/env bash
# usage: try_compilers.sh FUNCTION  -- tests the WIP seed under agbcc and old_agbcc
cd /home/username/Github/beyblade_g_revolution
fn="$1"
seed="src/wip/$fn.c"
for cc in agbcc old_agbcc; do
  out="/tmp/v/${fn}_${cc}.c"
  # strip any existing match-compiler line, then prepend ours
  { echo "/* match-compiler: $cc */"; grep -v '^/\* match-compiler' "$seed"; } > "$out"
  r=$(python3 tools/decomp/match_function.py "$fn" "$out" 2>&1 | head -2 | tr '\n' ' ')
  echo "[$cc] $r"
done
