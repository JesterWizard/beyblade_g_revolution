#!/usr/bin/env python3
"""Turns the audio files named in tracks.txt into BGM data for the game's own sound engine.

    gen_music.py <mod dir> <build dir>

Reads <mod dir>/tracks.txt, decodes each file (WAV directly, anything else through
ffmpeg), makes it mono at 8000 Hz (the engine's mixing rate), encodes it in the
engine's 4-bit ADPCM and writes, into <build dir>:

    music_data.s        gCustomBgmCount / gCustomBgm, which src/music.c reads
    <key>_*.bin         the encoded chunks (cached by file content and options)
    preview/<n>.wav     what the game will play, decoded the way its mixer does

A chunk is the engine's own sound format: a 16-byte header (u32 type = 0 for ADPCM,
u32 byte length, u32 loop start = 0, u32 0) and one byte per two samples. The
decoder is the mixer routine in IWRAM (0x03004B74 area), two tables from the ROM:
  step delta   0x083D299C  s16 [49][16]   (nibble 0-7 add, 8-15 subtract)
  next step    0x083D2FBC  u8  [49][8]
and every byte is XORed with 0xEC. A new chunk starts from predictor 0, step 0.
"""

import hashlib
import math
import os
import re
import shlex
import shutil
import sys

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "tools", "mod"))
from gba_adpcm import (RATE, ROM_BUDGET, chunk, decode, encode, fade, human, load_tables,  # noqa: E402
                       prepare_clip, repo_root, snr_db, write_preview, write_sizes)

MAX_NAME = 18                # characters the debug menu has room for
MAX_TRACKS = 200             # debug menu stores the BGM number in a u8 (17 retail + custom)
TOOL_VERSION = "2"


# ---------------------------------------------------------------- tracks.txt

def bgm_names(root):
    names = {}
    for line in open(os.path.join(root, "include", "bgm.h")):
        m = re.match(r"#define BGM_([A-Z_]+) (\d+)\b", line)
        if m and m.group(1) != "TRACKS":
            names[m.group(1)] = int(m.group(2))
    return names


def parse_tracks(path, root):
    retail = bgm_names(root)
    tracks = []
    for n, line in enumerate(open(path), 1):
        words = shlex.split(line, comments=True)
        if not words:
            continue
        if words[0] != "track" or len(words) < 2:
            sys.exit("%s:%d: expected 'track <file> [key=value ...]'" % (path, n))
        t = dict(file=words[1], name=None, loop=0.0, overworld=False, replace=None, gain=0.0, start=0.0, end=None, xfade=0.01, line=n)
        for opt in words[2:]:
            key, eq, val = opt.partition("=")
            if not eq:
                sys.exit("%s:%d: '%s' is not key=value" % (path, n, opt))
            if key == "name":
                t["name"] = val
            elif key == "loop":
                t["loop"] = None if val.lower() in ("none", "no", "off") else float(val)
            elif key == "overworld":
                t["overworld"] = val.lower() in ("yes", "true", "1", "on")
            elif key == "gain":
                t["gain"] = float(val)
            elif key in ("start", "end", "xfade"):
                t[key] = float(val)
            elif key == "replace":
                v = val.upper().replace(" ", "_")
                v = v[4:] if v.startswith("BGM_") else v
                if v.isdigit():
                    t["replace"] = int(v)
                elif v in retail:
                    t["replace"] = retail[v]
                else:
                    sys.exit("%s:%d: unknown track '%s' (use 0-16 or one of: %s)" % (path, n, val, ", ".join(sorted(retail))))
                if not 0 <= t["replace"] < len(retail):
                    sys.exit("%s:%d: replace is a retail track, 0-%d" % (path, n, len(retail) - 1))
            else:
                sys.exit("%s:%d: unknown option '%s' (name, loop, overworld, replace, gain, start, end, xfade)" % (path, n, key))
        tracks.append(t)
    if len(tracks) > MAX_TRACKS:
        sys.exit("%s: at most %d tracks" % (path, MAX_TRACKS))
    seen = {}
    for t in tracks:
        if t["replace"] is not None:
            if t["replace"] in seen:
                sys.exit("%s:%d: retail track %d is already replaced on line %d" % (path, t["line"], t["replace"], seen[t["replace"]]))
            seen[t["replace"]] = t["line"]
    return tracks


def display_name(t):
    name = t["name"] or os.path.splitext(os.path.basename(t["file"]))[0].replace("_", " ").replace("-", " ")
    name = "".join(c if 32 <= ord(c) < 127 and c != '"' else "?" for c in name).strip() or "Track"
    if len(name) > MAX_NAME:
        print("gen_music: name '%s' cut to %d characters" % (name, MAX_NAME), file=sys.stderr)
        name = name[:MAX_NAME].rstrip()
    return name


# ---------------------------------------------------------------- build

SILENCE = 0.003              # below this (about -50 dB) the start and end of a file count as silence


def loop_parts(a, loop, xfade, line):
    """-> (intro samples or None, body samples) for a track that repeats.

    The body is what repeats: it starts at the loop point S and ends with the file's last sound
    crossfaded (`xfade` seconds, equal power) into the audio just before S, which is exactly what
    the body's first sample continues. With no loop point S is where the music starts (leading
    silence is dropped), so the repeat goes straight from the last note to the first. Leading
    silence and a silent tail are cut, since they would be a gap in every repeat. The decoder
    restarts from zero at the body's first sample, so S is moved to the quietest sample within
    5 ms when it was given.
    """
    loud = np.nonzero(np.abs(a) > SILENCE)[0]
    if len(loud) == 0:
        sys.exit("tracks.txt:%d: the track is silent" % line)
    end = int(loud[-1]) + 1
    xf = int(round(xfade * RATE))
    if loop:
        start = int(round(loop * RATE))
        if not 0 < start < end - RATE:
            sys.exit("tracks.txt:%d: loop=%s is outside the track (%.1f s long)" % (line, loop, end / RATE))
        near = np.arange(max(1, start - 40), min(end, start + 40))
        start = int(near[np.argmin(np.abs(a[near]) + 4 * np.abs(a[near + 1] - a[near]))])
    else:
        start = int(loud[0])
    first = start
    if start < xf:
        # nothing before the loop point to crossfade from: the repeat starts xf later
        # and the head is what the end fades into
        partner = a[start:start + xf]
        start += xf
    else:
        partner = a[start - xf:start]
    xf = min(xf, end - start - 1)
    body = a[start:end].copy()
    if xf > 0:
        t = np.linspace(0, np.pi / 2, xf)
        body[-xf:] = body[-xf:] * np.cos(t) + partner[:xf] * np.sin(t)
    body = np.clip(body, -1, 1)
    # intro: everything before the loop point, unless it is silence
    intro = a[:first]
    if first == 0 or np.abs(intro).max() <= SILENCE:
        intro = None
    else:
        intro = fade(intro[: len(intro) & ~1], True, False)
    return intro, body[: len(body) & ~1]


def build_track(t, mod, out, delta, nxt):
    """-> (intro bytes or None, body bytes, preview samples)."""
    path = os.path.join(mod, t["file"])
    if not os.path.isfile(path):
        sys.exit("tracks.txt:%d: %s not found" % (t["line"], path))
    key = hashlib.sha1(open(path, "rb").read() + repr((t["loop"], t["gain"], t["start"], t["end"], t["xfade"], TOOL_VERSION)).encode()).hexdigest()[:16]
    cache = {k: os.path.join(out, "%s_%s.bin" % (key, k)) for k in ("intro", "body")}
    prev = os.path.join(out, "preview", "%s.wav" % key)
    if os.path.isfile(cache["body"]) and os.path.isfile(prev):
        intro = open(cache["intro"], "rb").read() if os.path.isfile(cache["intro"]) else None
        return intro, open(cache["body"], "rb").read(), prev

    a = prepare_clip(path, t["start"], t["end"], t["gain"], "tracks.txt:%d" % t["line"])

    if t["loop"] is None:
        parts = [("body", fade(a, True, True))]
    else:
        intro, body = loop_parts(a, t["loop"], t["xfade"], t["line"])
        parts = ([("intro", intro)] if intro is not None else []) + [("body", body)]

    decoded, blobs, source = [], {}, []
    for name, samples in parts:
        data, dec = encode(samples, delta, nxt)
        assert decode(data, delta, nxt) == dec, "encoder and decoder disagree"
        blobs[name] = chunk(data)
        open(cache[name], "wb").write(blobs[name])
        decoded += dec
        source += list(samples)
    print("gen_music: %s encoded, signal-to-noise %.1f dB" % (t["file"], snr_db(source, decoded)))
    if "intro" not in blobs and os.path.isfile(cache["intro"]):
        os.remove(cache["intro"])

    write_preview(prev, decoded)
    return blobs.get("intro"), blobs["body"], prev




def main():
    mod, out = sys.argv[1:3]
    root = repo_root(mod)
    os.makedirs(out, exist_ok=True)
    tracks = parse_tracks(os.path.join(mod, "tracks.txt"), root)
    delta, nxt = load_tables(root)

    lines = ["@ Generated by mods/custom_music/tools/gen_music.py. Do not edit.",
             "\t.section .rodata", "\t.align 2",
             "\t.global gCustomBgmCount", "gCustomBgmCount:", "\t.4byte %d" % len(tracks), "",
             "\t.global gCustomBgm", "gCustomBgm:"]
    total = 0
    tail = []
    rows = []
    for i, t in enumerate(tracks):
        intro, body, prev = build_track(t, mod, out, delta, nxt)
        key = os.path.basename(prev)[:-4]
        total += len(body) + (len(intro) if intro else 0)
        # list, intro, name, replace, overworld, loop
        lines.append("\t.4byte gCustomBgmList%d, %s, gCustomBgmName%d" % (i, "gCustomBgmIntro%d" % i if intro else "0", i))
        lines.append("\t.byte %d, %d, %d, 0" % (255 if t["replace"] is None else t["replace"], int(t["overworld"]), int(t["loop"] is not None)))
        tail += ["\t.align 2", "gCustomBgmList%d:" % i, "\t.4byte gCustomBgmBody%d" % i,
                 "\t.align 2", "gCustomBgmBody%d:" % i, '\t.incbin "%s_body.bin"' % os.path.join(out, key)]
        if intro:
            tail += ["\t.align 2", "gCustomBgmIntro%d:" % i, '\t.incbin "%s_intro.bin"' % os.path.join(out, key)]
        tail += ["gCustomBgmName%d:" % i, '\t.asciz "%s"' % display_name(t)]
        secs = (len(body) + (len(intro) if intro else 0)) * 2 / RATE
        rows.append((17 + i, display_name(t), t["file"], os.path.getsize(os.path.join(mod, t["file"])),
                     len(body) + (len(intro) if intro else 0)))
        listen = os.path.join(out, "preview", "track%d.wav" % (17 + i))
        shutil.copyfile(prev, listen)
        print("gen_music: track %d  %-18s %6.1f s  %4d KB  preview %s" % (17 + i, display_name(t), secs, (len(body) + (len(intro) if intro else 0)) // 1024, listen))
    if total > ROM_BUDGET:
        sys.exit("gen_music: %.1f MB of music; the ROM has to stay under 16 MB, so %.1f MB is the limit" % (total / 2**20, ROM_BUDGET / 2**20))
    write_sizes(os.path.join(mod, "music", "SIZES.md"), rows, "Music sizes", "Track")
    open(os.path.join(out, "music_data.s"), "w").write("\n".join(lines + [""] + tail) + "\n")


main()
