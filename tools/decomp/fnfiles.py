#!/usr/bin/env python3
"""Map between function identities (`sub_XXXXXXXX`) and `src/matched/*.c` files.

A function's identity is its ROM-address name (`sub_0802B930`): the manifest,
`analysis/`, the asm peels and the linker layout all key on it. Its *source
file* is named after the recorded symbol once there is one
(`src/matched/BeybladeGetProfile.c`), and stays `sub_XXXXXXXX.c` until then.

Every tool that used to assume "file stem == function name" goes through here:

    matched_file("sub_0802B930")  -> Path of the .c (named or sub_ form)
    stem_for("sub_0802B930")      -> "BeybladeGetProfile" (or the sub_ name)
    name_for(path)                -> "sub_0802B930"
    iter_matched()                -> [(name, path), ...]

`python3 tools/decomp/fnfiles.py sync [--apply]` renames files to match
`analysis/symbols.json` (git mv when tracked); `--revert` restores `sub_` names.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"
SYMBOLS_JSON = ROOT / "analysis" / "symbols.json"

_SUB = re.compile(r"sub_[0-9A-Fa-f]{8}")
_IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")

_fwd: dict[str, str] | None = None  # sub_XXXXXXXX -> symbol
_rev: dict[str, str] | None = None  # symbol -> sub_XXXXXXXX


def _load() -> None:
    global _fwd, _rev
    _fwd, _rev = {}, {}
    if not SYMBOLS_JSON.is_file():
        return
    data = json.loads(SYMBOLS_JSON.read_text()).get("symbols", {})
    for addr, entry in data.items():
        if entry.get("kind", "function") != "function":
            continue
        sym = entry.get("symbol")
        if not sym or not _IDENT.fullmatch(sym) or _SUB.fullmatch(sym):
            continue
        name = "sub_%08X" % int(addr, 16)
        _fwd[name] = sym
        _rev[sym] = name


def reload() -> None:
    global _fwd, _rev
    _fwd = _rev = None


def stem_for(name: str, directory: Path = MATCHED) -> str:
    """File stem for a function: the symbol if its named file exists, else the
    address name (new files keep `sub_XXXXXXXX.c` until `sync` renames them)."""
    if _fwd is None:
        _load()
    sym = _fwd.get(name)
    if sym and (directory / f"{sym}.c").is_file():
        return sym
    return name


def matched_file(name: str, directory: Path = MATCHED) -> Path:
    return directory / f"{stem_for(name, directory)}.c"


def name_for(path: Path | str) -> str:
    """Function identity for a matched C file (or bare stem)."""
    stem = Path(path).stem
    if _SUB.fullmatch(stem):
        return stem
    if _rev is None:
        _load()
    return _rev.get(stem, stem)


def iter_matched(directory: Path = MATCHED) -> list[tuple[str, Path]]:
    return [(name_for(p), p) for p in sorted(directory.glob("*.c"))]


def matched_names(directory: Path = MATCHED) -> set[str]:
    return {name for name, _ in iter_matched(directory)}


def _git_tracked(path: Path) -> bool:
    return (
        subprocess.run(
            ["git", "ls-files", "--error-unmatch", str(path)],
            cwd=ROOT,
            capture_output=True,
        ).returncode
        == 0
    )


def plan(revert: bool = False) -> list[tuple[Path, Path]]:
    if _fwd is None:
        _load()
    moves: list[tuple[Path, Path]] = []
    seen: dict[str, Path] = {}
    for name, sym in sorted(_fwd.items()):
        old, new = (MATCHED / f"{sym}.c", MATCHED / f"{name}.c") if revert else (
            MATCHED / f"{name}.c",
            MATCHED / f"{sym}.c",
        )
        if not old.is_file():
            continue
        if new.exists():
            print(f"fnfiles: skip {old.name}: {new.name} already exists")
            continue
        if sym.lower() in seen:
            print(f"fnfiles: skip {old.name}: {sym} collides with {seen[sym.lower()].name}")
            continue
        seen[sym.lower()] = old
        moves.append((old, new))
    return moves


LAYOUT_LD = ROOT / "asm" / "rom_layout.ld"
_LD_OBJ = re.compile(r"src/matched/([A-Za-z_][A-Za-z0-9_]*)\.o")


def sync_layout() -> int:
    """Point `asm/rom_layout.ld` at the objects the current file names produce."""
    if not LAYOUT_LD.is_file():
        return 0
    reload()
    changed = 0

    def swap(m: re.Match) -> str:
        nonlocal changed
        new = stem_for(name_for(m.group(1)))
        changed += new != m.group(1)
        return f"src/matched/{new}.o"

    text = LAYOUT_LD.read_text()
    out = _LD_OBJ.sub(swap, text)
    if out != text:
        LAYOUT_LD.write_text(out)
    return changed


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    ap.add_argument("cmd", choices=["sync"])
    ap.add_argument("--apply", action="store_true", help="perform the renames")
    ap.add_argument("--revert", action="store_true", help="rename back to sub_XXXXXXXX.c")
    args = ap.parse_args()
    moves = plan(args.revert)
    for old, new in moves:
        if args.apply:
            if _git_tracked(old):
                subprocess.run(["git", "mv", str(old), str(new)], cwd=ROOT, check=True)
            else:
                old.rename(new)
        elif len(moves) <= 20:
            print(f"  {old.name} -> {new.name}")
    print(f"fnfiles: {len(moves)} file(s) {'renamed' if args.apply else 'would be renamed'}")
    if args.apply:
        print(f"fnfiles: {sync_layout()} line(s) updated in asm/rom_layout.ld")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
