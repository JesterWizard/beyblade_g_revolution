#!/usr/bin/env bash
# Build a headless mGBA and the small helper library used by emu.py.
# Output goes to build/emu/ (git-ignored). Needs cmake, gcc, make and curl.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
OUT="$ROOT/build/emu"
VER=0.10.2
mkdir -p "$OUT"
cd "$OUT"

if [ ! -f "mgba-$VER/build/libmgba.so" ]; then
  [ -d "mgba-$VER" ] || { curl -sL "https://github.com/mgba-emu/mgba/archive/refs/tags/$VER.tar.gz" | tar xz; }
  mkdir -p "mgba-$VER/build" && cd "mgba-$VER/build"
  cmake .. -DBUILD_QT=OFF -DBUILD_SDL=OFF -DBUILD_SHARED=ON -DBUILD_STATIC=OFF \
    -DBUILD_GL=OFF -DBUILD_GLES2=OFF -DBUILD_GLES3=OFF -DUSE_EPOXY=OFF -DUSE_FFMPEG=OFF \
    -DUSE_LIBZIP=OFF -DUSE_MINIZIP=OFF -DUSE_SQLITE3=OFF -DUSE_LZMA=OFF -DUSE_DISCORD_RPC=OFF \
    -DUSE_EDITLINE=OFF -DUSE_ELF=OFF -DBUILD_PYTHON=OFF -DBUILD_TEST=OFF -DBUILD_EXAMPLE=OFF \
    -DENABLE_SCRIPTING=OFF -DUSE_PNG=ON -DCMAKE_BUILD_TYPE=Release >/dev/null
  make -j"$(nproc)" >/dev/null
  cd "$OUT"
fi

gcc -shared -fPIC -O2 -o libemuh.so "$ROOT/tools/mod/emu/helper.c" \
  -I"mgba-$VER/include" -I"mgba-$VER/build/include" -L"mgba-$VER/build" -lmgba \
  -Wl,-rpath,"$OUT/mgba-$VER/build"
echo "built $OUT/libemuh.so"
