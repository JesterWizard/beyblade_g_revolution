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

import bisect
import hashlib
import io
import math
import os
import re
import shlex
import shutil
import struct
import subprocess
import sys
import wave

import numpy as np
from scipy import signal

RATE = 8000
FADE = 16                    # samples faded at every cut (the decoder restarts from 0 there)
MAX_NAME = 18                # characters the debug menu has room for
MAX_TRACKS = 200             # debug menu stores the BGM number in a u8 (17 retail + custom)
ROM_BUDGET = 11 * 1024 * 1024  # the ROM must stay under 16 MB (EEPROM sits at 0x0D000000); retail is 4 MB
TOOL_VERSION = "1"

DELTA_TABLE, NEXT_TABLE, STEPS = 0x3D299C, 0x3D2FBC, 49


def repo_root(mod):
    return os.path.abspath(os.path.join(mod, "..", ".."))


def load_tables(root):
    rom = open(os.path.join(root, "baserom.gba"), "rb").read()
    flat = struct.unpack_from("<%dh" % (STEPS * 16), rom, DELTA_TABLE)
    delta = [flat[i * 16:(i + 1) * 16] for i in range(STEPS)]
    nxt = [list(rom[NEXT_TABLE + i * 8:NEXT_TABLE + i * 8 + 8]) for i in range(STEPS)]
    assert all(max(n) < STEPS for n in nxt), "baserom.gba is not the expected ROM"
    for row in delta:
        assert list(row[:8]) == sorted(row[:8]) and all(row[8 + k] == -row[k] for k in range(8)), "baserom.gba is not the expected ROM"
    return delta, nxt


# ---------------------------------------------------------------- ADPCM

def encode(samples, delta, nxt):
    """samples: floats in [-1, 1]. -> bytes, decoded samples (the predictor, +-2048)."""
    mags = [list(row[:8]) for row in delta]
    x = np.clip(np.round(np.asarray(samples) * 2047.0), -2048, 2047).astype(int).tolist()
    if len(x) % 2:
        x.append(0)
    lr, st = 0, 0
    out = bytearray()
    dec = []
    pending = None
    for v in x:
        m = mags[st]
        d = v - lr
        a = -d if d < 0 else d
        k = bisect.bisect_left(m, a)
        if k >= 8:
            k = 7
        elif k > 0 and a - m[k - 1] <= m[k] - a:
            k -= 1
        n = k | (8 if d < 0 else 0)
        lr += delta[st][n]
        lr = 2047 if lr > 2047 else (-2048 if lr < -2048 else lr)
        st = nxt[st][k]
        dec.append(lr)
        if pending is None:
            pending = n
        else:
            out.append(((pending << 4) | n) ^ 0xEC)
            pending = None
    return bytes(out), dec


def decode(data, delta, nxt):
    """The mixer's own decoder: bytes -> predictor values."""
    lr, st = 0, 0
    dec = []
    for b in data:
        b ^= 0xEC
        for n in (b >> 4, b & 15):
            lr += delta[st][n]
            lr = 2047 if lr > 2047 else (-2048 if lr < -2048 else lr)
            st = nxt[st][n & 7]
            dec.append(lr)
    return dec


def chunk(data):
    return struct.pack("<IIII", 0, len(data), 0, 0) + data + b"\0" * ((-len(data)) % 4)


# ---------------------------------------------------------------- audio input

def ffmpeg_exe():
    for cand in ("ffmpeg",):
        try:
            subprocess.run([cand, "-version"], capture_output=True, check=True)
            return cand
        except (OSError, subprocess.CalledProcessError):
            pass
    try:
        import imageio_ffmpeg
        return imageio_ffmpeg.get_ffmpeg_exe()
    except ImportError:
        sys.exit("gen_music: this file needs ffmpeg to decode (install ffmpeg, or use a PCM .wav)")


def read_wav(path):
    with wave.open(path, "rb") as w:
        ch, width, sr, n = w.getnchannels(), w.getsampwidth(), w.getframerate(), w.getnframes()
        raw = w.readframes(n)
    if width == 1:
        a = (np.frombuffer(raw, np.uint8).astype(np.float32) - 128) / 128
    elif width == 2:
        a = np.frombuffer(raw, "<i2").astype(np.float32) / 32768
    elif width == 3:
        b = np.frombuffer(raw, np.uint8).reshape(-1, 3)
        a = ((b[:, 0].astype(np.int32) | (b[:, 1].astype(np.int32) << 8) | (b[:, 2].astype(np.int32) << 16)) << 8 >> 8) / 8388608
        a = a.astype(np.float32)
    elif width == 4:
        a = np.frombuffer(raw, "<i4").astype(np.float32) / 2147483648
    else:
        raise wave.Error("unsupported sample width")
    return a.reshape(-1, ch).mean(axis=1), sr


def load_audio(path):
    """-> mono float32 samples at 8000 Hz."""
    if path.lower().endswith(".wav"):
        try:
            a, sr = read_wav(path)
        except (wave.Error, EOFError):
            a = None  # float / extensible WAV: let ffmpeg have it
        if a is not None:
            return resample(a, sr)
    cmd = [ffmpeg_exe(), "-v", "error", "-i", path, "-vn", "-ac", "1", "-ar", "48000", "-f", "f32le", "pipe:1"]
    r = subprocess.run(cmd, capture_output=True)
    if r.returncode != 0 or not r.stdout:
        sys.exit("gen_music: ffmpeg could not read %s: %s" % (path, r.stderr.decode(errors="replace").strip()))
    return resample(np.frombuffer(r.stdout, "<f4"), 48000)


def resample(a, sr):
    if sr != RATE:
        g = math.gcd(sr, RATE)
        a = signal.resample_poly(a, RATE // g, sr // g)
    return a.astype(np.float64)


def fade(a, head, tail):
    a = a.copy()
    r = np.linspace(0, 1, FADE, endpoint=False)
    if head:
        a[:FADE] *= r
    if tail:
        a[-FADE:] *= r[::-1]
    return a


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
        t = dict(file=words[1], name=None, loop=0.0, overworld=False, replace=None, gain=0.0, start=0.0, end=None, line=n)
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
            elif key in ("start", "end"):
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
                sys.exit("%s:%d: unknown option '%s' (name, loop, overworld, replace, gain, start, end)" % (path, n, key))
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

def build_track(t, mod, out, delta, nxt):
    """-> (intro bytes or None, body bytes, preview samples)."""
    path = os.path.join(mod, t["file"])
    if not os.path.isfile(path):
        sys.exit("tracks.txt:%d: %s not found" % (t["line"], path))
    key = hashlib.sha1(open(path, "rb").read() + repr((t["loop"], t["gain"], t["start"], t["end"], TOOL_VERSION)).encode()).hexdigest()[:16]
    cache = {k: os.path.join(out, "%s_%s.bin" % (key, k)) for k in ("intro", "body")}
    prev = os.path.join(out, "preview", "%s.wav" % key)
    if os.path.isfile(cache["body"]) and os.path.isfile(prev):
        intro = open(cache["intro"], "rb").read() if os.path.isfile(cache["intro"]) else None
        return intro, open(cache["body"], "rb").read(), prev

    a = load_audio(path)
    if len(a) < RATE:
        sys.exit("tracks.txt:%d: %s is shorter than a second" % (t["line"], t["file"]))
    first = int(round(t["start"] * RATE))
    last = len(a) if t["end"] is None else int(round(t["end"] * RATE))
    if not 0 <= first < last <= len(a):
        sys.exit("tracks.txt:%d: start=%s end=%s is outside the track (%.1f s long)" % (t["line"], t["start"], t["end"], len(a) / RATE))
    a = a[first:last]
    if len(a) < RATE:
        sys.exit("tracks.txt:%d: %s is shorter than a second after start/end" % (t["line"], t["file"]))
    a = a - a.mean()
    peak = float(np.abs(a).max())
    if peak > 0:
        a = a * (0.98 / peak)
    a = np.clip(a * 10 ** (t["gain"] / 20), -1, 1)
    if len(a) % 2:
        a = a[:-1]

    split = 0
    if t["loop"]:
        split = int(round(t["loop"] * RATE)) & ~1
        if not 0 < split < len(a) - RATE:
            sys.exit("tracks.txt:%d: loop=%s is outside the track (%.1f s long)" % (t["line"], t["loop"], len(a) / RATE))
    looping = t["loop"] is not None
    parts = []
    if split:
        parts.append(("intro", fade(a[:split], True, True)))
        parts.append(("body", fade(a[split:], True, True)))
    else:
        parts.append(("body", fade(a, True, True)))

    decoded, blobs, source = [], {}, []
    for name, samples in parts:
        data, dec = encode(samples, delta, nxt)
        assert decode(data, delta, nxt) == dec, "encoder and decoder disagree"
        blobs[name] = chunk(data)
        open(cache[name], "wb").write(blobs[name])
        decoded += dec
        source += list(samples)
    src = np.array(source) * 2047.0
    err = src - np.array(decoded[:len(src)])
    print("gen_music: %s encoded, signal-to-noise %.1f dB" % (t["file"], 10 * math.log10(max((src ** 2).sum(), 1) / max((err ** 2).sum(), 1))))
    if "intro" not in blobs and os.path.isfile(cache["intro"]):
        os.remove(cache["intro"])

    os.makedirs(os.path.dirname(prev), exist_ok=True)
    pcm = (np.array(decoded, dtype=np.int32) * 16).astype("<i2")
    with wave.open(prev, "wb") as w:
        w.setnchannels(1)
        w.setsampwidth(2)
        w.setframerate(RATE)
        w.writeframes(pcm.tobytes())
    return blobs.get("intro"), blobs["body"], prev


def human(n):
    return "%.2f MB" % (n / 2**20) if n >= 2**20 else "%.1f KB" % (n / 1024)


def write_sizes(path, rows):
    """music/SIZES.md: each file's size on disk against what it takes in the ROM."""
    lines = ["# Music sizes", "",
             "Written by `tools/gen_music.py` on every build; do not edit.",
             "*Original* is the file in this folder, *in game* the chunks in the ROM (16-byte header + 4-bit ADPCM, mono, 8000 Hz).", ""]
    if rows:
        lines += ["| Track | Name | File | Original | In game | Reduction |", "|---:|---|---|---:|---:|---:|"]
        for n, name, f, orig, ingame in rows:
            lines.append("| %d | %s | %s | %s | %s | %.1f%% |" % (n, name, os.path.basename(f), human(orig), human(ingame), 100 * (1 - ingame / orig)))
        to, ti = sum(r[3] for r in rows), sum(r[4] for r in rows)
        lines.append("| | **Total** | | **%s** | **%s** | **%.1f%%** |" % (human(to), human(ti), 100 * (1 - ti / to)))
    else:
        lines.append("No tracks in `tracks.txt` yet.")
    text = "\n".join(lines) + "\n"
    if not os.path.isfile(path) or open(path).read() != text:
        open(path, "w").write(text)


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
    write_sizes(os.path.join(mod, "music", "SIZES.md"), rows)
    open(os.path.join(out, "music_data.s"), "w").write("\n".join(lines + [""] + tail) + "\n")


main()
