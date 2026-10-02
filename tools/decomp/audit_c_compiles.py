#!/usr/bin/env python3
"""Scan src/matched/*.c for files that do not compile standalone.

`make` already compiles matched C into the peel (`compile_matched.py`). This
audit still compiles each file in isolation and reports the first agbcc
diagnostic, which is faster than a full ROM link when hunting a signature bug.

Usage: python3 tools/decomp/audit_c_compiles.py [--dirs matched,decompiled]
"""

import argparse
import concurrent.futures as cf
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
import sys as _sys
_sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import fnfiles  # noqa: E402
from fnfiles import matched_file, name_for  # noqa: E402,F401
AGBCC = ROOT / "tools" / "agbcc" / "bin" / "agbcc"
CPPFLAGS = ["-Iinclude", "-Itools/agbcc/include", "-Itools/agbcc"]
CFLAGS = [
    "-mthumb-interwork",
    "-Wimplicit",
    "-Wparentheses",
    "-Werror",
    "-O2",
    "-g",
    "-fhex-asm",
]

_FLAGS = re.compile(r"/\*\s*match-flags:\s*([^*]*)\*/")
_COMPILER = re.compile(r"/\*\s*match-compiler:\s*([A-Za-z0-9_]+)\s*\*/")


def compile_one(path: pathlib.Path) -> tuple[str, str]:
    text = path.read_text(errors="replace")
    extra: list[str] = []
    m = _FLAGS.search(text)
    if m:
        extra += m.group(1).split()
    binary = AGBCC
    mc = _COMPILER.search(text)
    if mc and mc.group(1) == "old_agbcc":
        binary = AGBCC.parent / "old_agbcc"

    i_path = path.with_suffix(".audit.i")
    s_path = path.with_suffix(".audit.s")
    try:
        pp = subprocess.run(
            ["arm-none-eabi-gcc", "-E", *CPPFLAGS, str(path), "-o", str(i_path)],
            capture_output=True,
            text=True,
            timeout=120,
        )
        if pp.returncode != 0:
            return name_for(path), f"preprocess: {pp.stderr.strip().splitlines()[-1][:150]}"
        cc = subprocess.run(
            [str(binary), str(i_path), "-o", str(s_path), *CFLAGS, *extra],
            capture_output=True,
            text=True,
            timeout=120,
        )
        if cc.returncode != 0:
            first = next(
                (ln for ln in cc.stderr.splitlines() if ln.strip()), "(no stderr)"
            )
            return name_for(path), first[:160]
        return name_for(path), ""
    except subprocess.TimeoutExpired:
        return name_for(path), "timeout"
    except Exception as exc:  # noqa: BLE001
        return name_for(path), f"{type(exc).__name__}: {exc}"[:160]
    finally:
        i_path.unlink(missing_ok=True)
        s_path.unlink(missing_ok=True)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dirs", default="matched", help="comma-separated src/ subdirs")
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()

    if not AGBCC.is_file():
        print("missing agbcc — run build_tools.sh", file=sys.stderr)
        return 2

    files = []
    for d in args.dirs.split(","):
        d = d.strip()
        # `matched` is audited through the per-function view of the group files.
        base = fnfiles.view() if d == "matched" else ROOT / "src" / d
        files += sorted(base.glob("*.c"))
    if not files:
        print("no C files found")
        return 1

    bad: list[tuple[str, str]] = []
    with cf.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for name, err in pool.map(compile_one, files):
            if err:
                bad.append((name, err))

    print(f"=== C compile audit ({len(files)} files) ===")
    print(f"  compiled clean : {len(files) - len(bad)}")
    print(f"  FAILED         : {len(bad)}")
    if bad:
        print()
        for name, err in sorted(bad):
            print(f"  {name}  {err}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
