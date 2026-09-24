#!/usr/bin/env bash
# Wrappers around simonlindholm/decomp-permuter for this repo.
#
#   tools/decomp/permuter/permute.sh import <function>
#   tools/decomp/permuter/permute.sh run nonmatchings/<function> [-j N] [--stop-on-zero]
#   tools/decomp/permuter/permute.sh bg  nonmatchings/<function> [-j N] [--stop-on-zero]
#   tools/decomp/permuter/permute.sh dashboard <function> [--seconds N] [--jobs N]
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
PERM="$ROOT/tools/decomp-permuter"
cd "$ROOT"

if [ ! -d "$PERM" ]; then
  echo "decomp-permuter not set up. Run: tools/decomp/permuter/setup.sh" >&2
  exit 1
fi

cmd="${1:-}"; shift || true
case "$cmd" in
  import)
    exec python3 "$ROOT/tools/decomp/permuter/import_function.py" "$@"
    ;;
  run)
    exec python3 "$PERM/permuter.py" "$@"
    ;;
  bg)
    dir="${1:?usage: $0 bg nonmatchings/<function> [permuter args]}"
    shift || true
    log="${dir%/}/permute.log"
    mkdir -p "${dir%/}"
    setsid python3 "$PERM/permuter.py" "$dir" "$@" >"$log" 2>&1 < /dev/null &
    echo "permuter detached pid $!; log: $log"
    echo "  watch: tail -f $log"
    echo "  stop:  pkill -f 'permuter.py.*$(basename "${dir%/}")'"
    ;;
  dashboard)
    fn="${1:?usage: $0 dashboard <function> [--seconds N] [--jobs N]}"
    shift || true
    exec python3 "$ROOT/tools/decomp/permuter/run_dashboard.py" "$fn" "$@"
    ;;
  *)
    echo "usage: $0 {import <function> | run <dir> [-j N] [--stop-on-zero] | bg <dir> ... | dashboard <function> [--seconds N] [--jobs N]}" >&2
    exit 1
    ;;
esac
