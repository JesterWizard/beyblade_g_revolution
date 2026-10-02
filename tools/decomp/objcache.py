#!/usr/bin/env python3
"""Content-addressed cache for compile_matched.py, so `make clean` does not
mean recompiling every function.

  objcache.py --env                       print the toolchain/header fingerprint
  objcache.py [--env HASH] [flags] in.c out.o
                                          copy a cached object, or compile and keep it

An object is reused only when the function source, the compile flags and the
fingerprint all match. The fingerprint covers everything the compile reads
besides the source: include/, the data/RAM symbol files, the compile tooling,
agbcc, and baserom.gba (the compile checks bytes against it). Cached objects
live in .cache/objs/ (git-ignored); delete it to start over.
"""
from __future__ import annotations

import hashlib
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CACHE = ROOT / ".cache" / "objs"

ENV_FILES = [
    "baserom.gba",
    "asm/data_symbols.s",
    "asm/ram_map.s",
    "asm/ram_map_iwram.s",
    "asm/ram_map_ewram.s",
    "asm/ram_map_sram.s",
    "asm/ram_map_iwram_pool.inc",
    "asm/ram_map_ewram_pool.inc",
    "asm/macros.inc",
    "tools/decomp/compile_matched.py",
    "tools/decomp/match_function.py",
    "tools/decomp/fnfiles.py",
    "tools/decomp/objcache.py",
]
ENV_DIRS = ["include", "tools/agbcc/bin", "tools/agbcc/include"]


def env_hash() -> str:
    h = hashlib.sha1()
    paths = [ROOT / f for f in ENV_FILES]
    for d in ENV_DIRS:
        paths += sorted(p for p in (ROOT / d).rglob("*") if p.is_file())
    for p in paths:
        if p.is_file():
            h.update(str(p.relative_to(ROOT)).encode())
            h.update(p.read_bytes())
    return h.hexdigest()[:16]


def main(argv: list[str]) -> int:
    if argv == ["--env"]:
        print(env_hash())
        return 0
    env = None
    if argv[:1] == ["--env"]:
        env, argv = argv[1], argv[2:]
    env = env or env_hash()
    *flags, src, out = argv
    key = hashlib.sha1()
    key.update(env.encode())
    key.update(" ".join(flags).encode())
    key.update(Path(src).read_bytes())
    cached = CACHE / env / (key.hexdigest() + ".o")
    out_path = Path(out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    if cached.is_file():
        shutil.copyfile(cached, out_path)
        return 0
    r = subprocess.run([sys.executable, str(ROOT / "tools/decomp/compile_matched.py"), *flags, src, out])
    if r.returncode == 0 and out_path.is_file():
        cached.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(out_path, cached)
    return r.returncode


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
