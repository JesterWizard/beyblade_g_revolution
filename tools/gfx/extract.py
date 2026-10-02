#!/usr/bin/env python3
"""Extract graphics from baserom.gba into graphics/<category>/<name>.png.

Driven by tools/gfx/assets.json. Runs automatically on the first `make` (see the
`graphics/.extracted` stamp in the Makefile); run it by hand with:

    python3 tools/gfx/extract.py              # extract everything in the manifest
    python3 tools/gfx/extract.py --discover   # list BG containers not in the manifest
    python3 tools/gfx/extract.py --check      # decode only, write nothing
    python3 tools/gfx/extract.py --discover-portraits         # list dialogue portraits
    python3 tools/gfx/extract.py --discover-portraits --write # ...and update the manifest

Output is regenerable from the ROM and git-ignored.
"""

import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from gba import GfxError  # noqa: E402
from bg import load_bg, palette_after, write_bg_png  # noqa: E402
from sprite import load_sprite, write_sprite_png  # noqa: E402
import portraits  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MANIFEST = os.path.join(REPO, "tools", "gfx", "assets.json")
ROM_PATH = os.path.join(REPO, "baserom.gba")
OUT_DIR = os.path.join(REPO, "graphics")


def parse_addr(v):
    return int(v, 16) if isinstance(v, str) else int(v)


def extract_bg(rom, asset, out_dir, write):
    off = parse_addr(asset["rom"])
    res, end = load_bg(rom, off)
    pal = asset.get("palette", "after")
    if pal == "after":
        pal_off = palette_after(rom, end)
        if pal_off is None:
            raise GfxError("no palette after the stream ending at 0x%X" % end)
    else:
        pal_off = parse_addr(pal)
    path = os.path.join(out_dir, asset["category"], asset["name"] + ".png")
    if not write:
        res.render()  # decode fully so --check catches bad maps
        return path, res.width * 8, res.height * 8
    os.makedirs(os.path.dirname(path), exist_ok=True)
    w, h = write_bg_png(rom, res, pal_off, path)
    return path, w, h


def extract_sprite(rom, asset, out_dir, write):
    tpl = load_sprite(rom, parse_addr(asset["rom"]))
    frame = asset.get("frame", 0)
    path = os.path.join(out_dir, asset["category"], asset["name"] + ".png")
    if not write:
        tpl.render(frame)  # decode fully so --check catches bad frames
        return path, tpl.width, tpl.height
    os.makedirs(os.path.dirname(path), exist_ok=True)
    w, h = write_sprite_png(rom, tpl, frame, parse_addr(asset["palette"]), path)
    return path, w, h


EXTRACTORS = {"bg": extract_bg, "sprite": extract_sprite}


def run(args):
    if not os.path.isfile(ROM_PATH):
        print("error: baserom.gba not found", file=sys.stderr)
        return 1
    rom = open(ROM_PATH, "rb").read()
    manifest = json.load(open(MANIFEST))
    failed = 0
    done = 0
    for asset in manifest["assets"]:
        try:
            path, w, h = EXTRACTORS[asset["type"]](rom, asset, OUT_DIR, not args.check)
        except (GfxError, KeyError) as e:
            print("  FAIL %-28s %s: %s" % (asset.get("name", "?"), asset.get("rom", "?"), e))
            failed += 1
            continue
        done += 1
        if args.verbose:
            print("  %-34s %4dx%-4d <- %s" % (os.path.relpath(path, REPO), w, h, asset["rom"]))
    print("gfx: %d extracted, %d failed" % (done, failed))
    return 1 if failed else 0


def discover(args):
    rom = open(ROM_PATH, "rb").read()
    known = set(parse_addr(a["rom"]) for a in json.load(open(MANIFEST))["assets"])
    print("%-10s %-9s %-5s %s" % ("rom", "size", "bpp", "palette"))
    for off in range(0, len(rom) - 4, 4):
        if rom[off] != 0x10 or off in known:
            continue
        try:
            res, end = load_bg(rom, off)
            res.map_cells()
        except GfxError:
            continue
        pal = palette_after(rom, end)
        if pal is None and not args.all:
            continue
        print("0x%06X   %3dx%-4d  %dbpp  %s" % (
            off, res.width * 8, res.height * 8, 4 if res.is_4bpp else 8,
            "after (0x%06X)" % pal if pal else "-"))
    return 0


def portrait_line(template, palette):
    return ('    {"name": "portrait_%06x", "category": "portraits", "type": "sprite", '
            '"rom": "0x%X", "palette": "0x%X"}' % (template, template, palette))


def discover_portraits(args):
    rom = open(ROM_PATH, "rb").read()
    found, skipped = portraits.discover(rom)
    print("%-10s %s" % ("rom", "palette"))
    for template, palette in found:
        print("0x%06X   0x%06X" % (template, palette))
    for template in skipped:
        print("0x%06X   (no palette found, skipped)" % template)
    print("%d portraits" % len(found))
    if not args.write:
        return 0
    lines = [l for l in open(MANIFEST).read().split("\n") if '"category": "portraits"' not in l]
    end = max(i for i, l in enumerate(lines) if l.strip() == "]")
    while lines[end - 1].strip() == "":
        del lines[end - 1]
        end -= 1
    body = [portrait_line(t, p) for t, p in found]
    # last asset line before the closing bracket must end with a comma
    prev = max(i for i in range(end) if lines[i].lstrip().startswith("{"))
    lines[prev] = lines[prev].rstrip(",") + ","
    lines[end:end] = ["", ",\n".join(body)]
    open(MANIFEST, "w").write("\n".join(lines))
    print("wrote %d portrait entries to %s" % (len(found), os.path.relpath(MANIFEST, REPO)))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--discover-portraits", action="store_true",
                    help="find the dialogue portraits and their palettes")
    ap.add_argument("--write", action="store_true",
                    help="with --discover-portraits, update tools/gfx/assets.json")
    ap.add_argument("--discover", action="store_true",
                    help="list BG containers in the ROM that are not in the manifest")
    ap.add_argument("--all", action="store_true",
                    help="with --discover, include containers without a trailing palette")
    ap.add_argument("--check", action="store_true", help="decode but write nothing")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()
    if args.discover_portraits:
        return discover_portraits(args)
    return discover(args) if args.discover else run(args)


if __name__ == "__main__":
    sys.exit(main())
