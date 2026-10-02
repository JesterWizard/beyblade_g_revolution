#!/usr/bin/env python3
"""Group matched functions into shared C files (pokeemerald-style) without
touching the per-function ROM layout.

Source of truth (committed):
  src/<group>.c      many functions, e.g. src/text.c, src/palette.c
  src/matched/*.c    the *inbox*: ungrouped functions (new matches, `sub_*`)

Build input (generated, git-ignored): `build/split/<stem>.c`, one file per
function, exactly what the old `src/matched/<stem>.c` was. `split` writes it;
the Makefile, `compile_matched.py` and every read-only tool consume it. This is
why `asm/rom_layout.ld` can keep placing one object per function between the
unmatched ROM gaps: grouping is a *source* concern, not a link-order one.

A group file is a shared prelude followed by chunks, one per function:

    #include "global.h"
    #include "ram_map.h"

    /* fn: sub_0802BC14 */
    // @ 0x0802bc14
    s32 CollectionIsFull(s16 a) { ... }

Edit functions in `src/<group>.c`, never in `build/split/`. Per-function
comments (`match-compiler:`, `match-fixup:`) live in the chunk and keep
working because each chunk is compiled on its own.

  python3 tools/decomp/groups.py split          # regenerate build/split (idempotent)
  python3 tools/decomp/groups.py pack [--apply] # fold inbox files into groups
  python3 tools/decomp/groups.py where NAME     # file:line of a function
  python3 tools/decomp/groups.py tidy           # hoist stray #includes to the top
  python3 tools/decomp/groups.py report         # group sizes, ungrouped names
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

import fnfiles  # noqa: E402

SRC = ROOT / "src"
INBOX = SRC / "matched"
VIEW = ROOT / "build" / "split"

#: (group file stem, regex on the recorded symbol). First match wins, so
#: specific rules precede broad ones. Functions matching nothing (and every
#: still-unnamed `sub_XXXXXXXX`) stay in the inbox until they earn a group.
GROUPS: list[tuple[str, str]] = [
    ("debug", r"^Debug"),
    ("string_util", r"String|SplitString"),
    ("text_window", r"TextWindow"),
    ("text", r"Text|Glyph|DigitRowDraw"),
    ("message", r"Message"),
    ("fade", r"Fade|ScreenBrightness|ScreenWhiteout"),
    ("palette", r"Palette|ObjPalLoadSlot"),
    ("bg", r"^(Bg(?!m)|AffineBg)"),
    ("sound", r"^(Sound|Sfx|Bgm)"),
    ("anim", r"^(Anim|Keyframe)"),
    ("eeprom", r"^Eeprom"),
    ("save", r"^(Save|LoadGameSave)"),
    ("heap", r"^(Heap|FastAllocate|GetValidAllocatedBlock|MemClear|BufferClear|LinkedListValidate)"),
    ("decompress", r"^(Lz77|LZ77)"),
    ("math", r"^(Div|Sqrt|Fixed|RandRange|ScaleRatio|SegCrossSide)"),
    ("task", r"^Task"),
    ("cursor", r"^Cursor"),
    ("camera", r"^Camera"),
    ("sparkles", r"^Sparkles"),
    ("vram", r"^(Vram|TileAddrFromIndex)"),
    ("collection", r"^(Collection|BeybladeCollectionEntry|RemoveBladeFrom|ItemListDraw)"),
    ("hud", r"^(StatusHud|Hud|Bar[A-Z]|SegmentedBar|ExpBar|DigitSprites)"),
    ("exp", r"^(Exp|MatchBladerExperience)"),
    ("menu", r"^(Menu|ScrollListRedraw|PartMenu)"),
    ("map", r"^(Map|Field|ProximityTrigger)"),
    ("script", r"^(Script|EventFlag|EventByte|ActiveFlag)"),
    ("scene", r"^Scene"),
    ("battle_obj", r"^BtlObj"),
    ("battle", r"^(Btl|Battle|CleanBattle|Collision)"),
    ("beyblade", r"^(Beyblade|Launch|Ripcord|BitBeast)"),
    ("actor", r"^(Actor|Motion)"),
    ("sprite", r"^(Sprite|Obj[A-Z]|Oam|Affine|WindowEffect|WindowRegs)"),
]
_RULES = [(g, re.compile(p)) for g, p in GROUPS]

# Fixed order so a union prelude is stable and `data_symbols.h` follows `global.h`.
_INCLUDE_ORDER = ["global.h", "ram_map.h", "battle.h", "data_symbols.h"]

_CHUNK = re.compile(r"^/\* fn: (sub_[0-9A-Fa-f]{8}) \*/[ \t]*$", re.M)
_INC = re.compile(r'^\s*#include\s+"([^"]+)"\s*$')


def group_for(symbol: str) -> str | None:
    for group, rx in _RULES:
        if rx.search(symbol):
            return group
    return None


def view_stem(name: str) -> str:
    """Split-view file stem: the recorded symbol, else the address name."""
    if fnfiles._fwd is None:
        fnfiles._load()
    return fnfiles._fwd.get(name, name)


# --- group file parsing -------------------------------------------------------


def group_files() -> list[Path]:
    return sorted(p for p in SRC.glob("*.c") if _CHUNK.search(p.read_text()))


def parse_group(text: str) -> tuple[str, dict[str, str]]:
    """(prelude, {sub_name: chunk body}) with bodies stripped of outer blank lines."""
    marks = list(_CHUNK.finditer(text))
    prelude = text[: marks[0].start()] if marks else text
    chunks: dict[str, str] = {}
    for i, m in enumerate(marks):
        end = marks[i + 1].start() if i + 1 < len(marks) else len(text)
        chunks[m.group(1).upper().replace("SUB_", "sub_")] = text[m.end() : end].strip("\n")
    return prelude, chunks


def render_group(includes: list[str], chunks: dict[str, str]) -> str:
    out = [f'#include "{h}"' for h in includes] + [""]
    for name in sorted(chunks):
        out += [f"/* fn: {name} */", chunks[name], ""]
    return "\n".join(out).rstrip("\n") + "\n"


def split_includes(body: str) -> tuple[list[str], str]:
    """Peel every `#include "x"` line off a function body (they all belong in the
    group prelude, even ones that followed a leading comment)."""
    incs: list[str] = []
    kept: list[str] = []
    for line in body.splitlines():
        m = _INC.match(line)
        if m:
            if m.group(1) not in incs:
                incs.append(m.group(1))
        else:
            kept.append(line)
    return incs, re.sub(r"\n{3,}", "\n\n", "\n".join(kept)).strip("\n")


def order_includes(headers: set[str]) -> list[str]:
    known = [h for h in _INCLUDE_ORDER if h in headers]
    return known + sorted(headers - set(known))


# --- split --------------------------------------------------------------------


def desired_view() -> dict[str, str]:
    """{stem: file text} for every function: group chunks + inbox files."""
    files: dict[str, str] = {}
    for path in group_files():
        prelude, chunks = parse_group(path.read_text())
        prelude = prelude.rstrip("\n") + "\n"
        for name, body in chunks.items():
            stem = view_stem(name)
            if stem in files:
                raise SystemExit(f"groups: {name} ({stem}) defined twice (last in {path.name})")
            files[stem] = f"{prelude}\n{body}\n"
    for path in sorted(INBOX.glob("*.c")):
        stem = view_stem(fnfiles.name_for(path))
        if stem in files:
            raise SystemExit(f"groups: {path.name} duplicates a grouped function; remove one")
        files[stem] = path.read_text()
    return files


def split() -> int:
    VIEW.mkdir(parents=True, exist_ok=True)
    want = desired_view()
    changed = 0
    for stem, text in want.items():
        dst = VIEW / f"{stem}.c"
        if dst.is_file() and dst.read_text() == text:
            continue
        dst.write_text(text)
        changed += 1
    for old in VIEW.glob("*.c"):
        if old.stem not in want:
            old.unlink()
            changed += 1
    return changed


# --- pack ---------------------------------------------------------------------


def _tracked(path: Path) -> bool:
    return subprocess.run(
        ["git", "ls-files", "--error-unmatch", str(path)], cwd=ROOT, capture_output=True
    ).returncode == 0


def pack(apply: bool, only: set[str] | None = None) -> int:
    """Fold inbox files whose symbol matches a group into `src/<group>.c`."""
    plan: dict[str, list[tuple[str, Path]]] = {}
    for path in sorted(INBOX.glob("*.c")):
        sym = path.stem
        if only is not None and fnfiles.name_for(path) not in only:
            continue
        group = group_for(sym) if not sym.startswith("sub_") else None
        if group:
            plan.setdefault(group, []).append((fnfiles.name_for(path), path))
    for group, items in sorted(plan.items()):
        print(f"  {group}.c  +{len(items)}")
    total = sum(len(v) for v in plan.values())
    if not apply:
        print(f"groups: {total} function(s) would move into {len(plan)} group file(s) (use --apply)")
        return 0
    for group, items in plan.items():
        dst = SRC / f"{group}.c"
        headers: set[str] = set()
        chunks: dict[str, str] = {}
        if dst.is_file():
            prelude, chunks = parse_group(dst.read_text())
            headers |= {m.group(1) for l in prelude.splitlines() if (m := _INC.match(l))}
        for name, path in items:
            incs, body = split_includes(path.read_text())
            headers |= set(incs)
            chunks[name] = body
        dst.write_text(render_group(order_includes(headers), chunks))
        for _, path in items:
            if _tracked(path):
                subprocess.run(["git", "rm", "-q", "-f", str(path)], cwd=ROOT, check=True)
            else:
                path.unlink()
    print(f"groups: packed {total} function(s) into {len(plan)} group file(s)")
    split()
    return 0


def tidy() -> int:
    """Hoist stray `#include`s inside chunks up into each group's prelude."""
    for path in group_files():
        prelude, chunks = parse_group(path.read_text())
        headers = {m.group(1) for l in prelude.splitlines() if (m := _INC.match(l))}
        for name, body in chunks.items():
            incs, chunks[name] = split_includes(body)
            headers |= set(incs)
        path.write_text(render_group(order_includes(headers), chunks))
    split()
    return 0


def land(name: str, text: str) -> Path:
    """Store verified C for `name`: replace its chunk if it is already grouped,
    else write it to the inbox and fold it into its group when one matches.
    Returns the file the source now lives in."""
    for path in group_files():
        prelude, chunks = parse_group(path.read_text())
        if name in chunks:
            incs, body = split_includes(text)
            headers = {m.group(1) for l in prelude.splitlines() if (m := _INC.match(l))}
            chunks[name] = body
            path.write_text(render_group(order_includes(headers | set(incs)), chunks))
            split()
            return path
    dst = INBOX / f"{fnfiles.stem_for(name)}.c"
    INBOX.mkdir(parents=True, exist_ok=True)
    dst.write_text(text)
    fnfiles.reload()
    pack(True, only={name})
    for path in group_files():
        if name in parse_group(path.read_text())[1]:
            return path
    split()
    return dst


# --- queries ------------------------------------------------------------------


def where(query: str) -> int:
    name = fnfiles.name_for(query)
    for path in group_files():
        for i, line in enumerate(path.read_text().splitlines(), 1):
            if line.strip().lower() == f"/* fn: {name} */".lower():
                print(f"{path.relative_to(ROOT)}:{i}")
                return 0
    hit = fnfiles.matched_file(name, INBOX)
    if hit.is_file():
        print(f"{hit.relative_to(ROOT)}:1")
        return 0
    print(f"groups: {query} not found", file=sys.stderr)
    return 1


def report() -> int:
    total = 0
    for path in group_files():
        _, chunks = parse_group(path.read_text())
        total += len(chunks)
        print(f"  {path.name:<18}{len(chunks):>4}")
    inbox = sorted(INBOX.glob("*.c"))
    named = [p.stem for p in inbox if not p.stem.startswith("sub_")]
    print(f"grouped {total}; inbox {len(inbox)} ({len(named)} named without a group, "
          f"{len(inbox) - len(named)} unnamed sub_*)")
    if named:
        print("  ungrouped named:", " ".join(named))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    ap.add_argument("cmd", choices=["split", "pack", "where", "report", "tidy"])
    ap.add_argument("name", nargs="?")
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()
    if args.cmd == "split":
        split()
        return 0
    if args.cmd == "pack":
        return pack(args.apply)
    if args.cmd == "tidy":
        return tidy()
    if args.cmd == "where":
        return where(args.name or "")
    return report()


if __name__ == "__main__":
    raise SystemExit(main())
