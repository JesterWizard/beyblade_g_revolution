#!/usr/bin/env python3
"""Turns the audio files named in voices.txt into voice data for the game's own sound engine.

    gen_voices.py <mod dir> <build dir>

Reads <mod dir>/voices.txt, decodes each file (WAV directly, anything else through ffmpeg),
makes it mono at 8000 Hz and encodes it in the engine's 4-bit ADPCM (tools/mod/gba_adpcm.py,
shared with mods/custom_music) and writes, into <build dir>:

    voices_data.s       gVoiceCount / gVoices, which src/voices.c reads
    <key>.bin           the encoded chunk (cached by file content and options)
    preview/voiceN.wav  what the game will play, decoded the way its mixer does
    sfx/sfxNN.wav       the 16 retail sound effects, to pick a `replace=` from
"""

import hashlib
import os
import shlex
import struct
import sys
import wave

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "tools", "mod"))
from gba_adpcm import (RATE, ROM_BUDGET, chunk, decode, encode, fade, human, load_tables,  # noqa: E402
                       prepare_clip, repo_root, snr_db, write_preview, write_sizes)

SFX_COUNT = 16               # entries of the retail effect table
TOOL_VERSION = "1"


def parse_voices(path):
    voices = []
    for n, line in enumerate(open(path), 1):
        words = shlex.split(line, comments=True)
        if not words:
            continue
        if words[0] != "voice" or len(words) < 2:
            sys.exit("%s:%d: expected 'voice <file> [key=value ...]'" % (path, n))
        v = dict(file=words[1], name=None, launch=False, replace=None, gain=0.0, start=0.0, end=None, line=n)
        for opt in words[2:]:
            key, eq, val = opt.partition("=")
            if not eq:
                sys.exit("%s:%d: '%s' is not key=value" % (path, n, opt))
            if key == "name":
                v["name"] = val
            elif key == "on":
                if val.lower() != "launch":
                    sys.exit("%s:%d: unknown event '%s' (launch)" % (path, n, val))
                v["launch"] = True
            elif key == "replace":
                if not val.isdigit() or int(val) >= SFX_COUNT:
                    sys.exit("%s:%d: replace is a sound effect number, 0-%d" % (path, n, SFX_COUNT - 1))
                v["replace"] = int(val)
            elif key in ("gain", "start", "end"):
                v[key] = float(val)
            else:
                sys.exit("%s:%d: unknown option '%s' (name, on, replace, gain, start, end)" % (path, n, key))
        if not v["launch"] and v["replace"] is None:
            print("gen_voices: %s:%d: %s has neither on= nor replace=, so nothing plays it" % (path, n, v["file"]), file=sys.stderr)
        voices.append(v)
    seen = {}
    for v in voices:
        if v["replace"] is not None:
            if v["replace"] in seen:
                sys.exit("%s:%d: sound effect %d is already replaced on line %d" % (path, v["line"], v["replace"], seen[v["replace"]]))
            seen[v["replace"]] = v["line"]
    return voices


def build_voice(v, mod, out, delta, nxt):
    path = os.path.join(mod, v["file"])
    if not os.path.isfile(path):
        sys.exit("voices.txt:%d: %s not found" % (v["line"], path))
    key = hashlib.sha1(open(path, "rb").read() + repr((v["gain"], v["start"], v["end"], TOOL_VERSION)).encode()).hexdigest()[:16]
    cache = os.path.join(out, key + ".bin")
    prev = os.path.join(out, "preview", key + ".wav")
    if os.path.isfile(cache) and os.path.isfile(prev):
        return open(cache, "rb").read(), prev
    a = fade(prepare_clip(path, v["start"], v["end"], v["gain"], "voices.txt:%d" % v["line"]), True, True)
    data, dec = encode(a, delta, nxt)
    assert decode(data, delta, nxt) == dec, "encoder and decoder disagree"
    blob = chunk(data)
    open(cache, "wb").write(blob)
    write_preview(prev, dec)
    print("gen_voices: %s encoded, signal-to-noise %.1f dB" % (v["file"], snr_db(a, dec)))
    return blob, prev


def export_sfx(root, out, delta, nxt):
    """The retail effects as wav files, to choose a `replace=` by ear. The table is a struct at
    0x0802B7E0 (count at +4) followed by the chunk pointers at 0x0802B7F0. The effects are PCM8
    chunks whose pitch comes from the note the game asks for; 8771 Hz is the rate of note 0x38,
    the one most use, so the length and pitch here are approximate."""
    rom = open(os.path.join(root, "baserom.gba"), "rb").read()
    count = struct.unpack_from("<I", rom, 0x2B7E4)[0]
    assert count == SFX_COUNT, "baserom.gba is not the expected ROM"
    os.makedirs(os.path.join(out, "sfx"), exist_ok=True)
    for i in range(count):
        at = struct.unpack_from("<I", rom, 0x2B7F0 + 4 * i)[0] - 0x08000000
        kind, length = struct.unpack_from("<II", rom, at)
        data = rom[at + 16:at + 16 + length]
        if kind == 1:
            pcm = np.frombuffer(data, np.int8).astype(np.int16) * 256
        else:
            pcm = np.array(decode(data, delta, nxt), dtype=np.int16) * 16
        with wave.open(os.path.join(out, "sfx", "sfx%02d.wav" % i), "wb") as w:
            w.setnchannels(1)
            w.setsampwidth(2)
            w.setframerate(8771)
            w.writeframes(pcm.astype("<i2").tobytes())


def main():
    mod, out = sys.argv[1:3]
    root = repo_root(mod)
    os.makedirs(out, exist_ok=True)
    voices = parse_voices(os.path.join(mod, "voices.txt"))
    delta, nxt = load_tables(root)

    lines = ["@ Generated by mods/custom_voices/tools/gen_voices.py. Do not edit.",
             "\t.section .rodata", "\t.align 2",
             "\t.global gVoiceCount", "gVoiceCount:", "\t.4byte %d" % len(voices), "",
             "\t.global gVoices", "gVoices:"]
    tail, rows, total = [], [], 0
    for i, v in enumerate(voices):
        blob, prev = build_voice(v, mod, out, delta, nxt)
        total += len(blob)
        lines.append("\t.4byte gVoiceChunk%d" % i)
        lines.append("\t.byte %d, %d, 0, 0" % (int(v["launch"]), 255 if v["replace"] is None else v["replace"]))
        key = os.path.basename(prev)[:-4]
        tail += ["\t.align 2", "gVoiceChunk%d:" % i, '\t.incbin "%s.bin"' % os.path.join(out, key)]
        name = v["name"] or os.path.splitext(os.path.basename(v["file"]))[0].replace("_", " ")
        rows.append((i, name, v["file"], os.path.getsize(os.path.join(mod, v["file"])), len(blob)))
        listen = os.path.join(out, "preview", "voice%d.wav" % i)
        write_preview(listen, decode(blob[16:16 + struct.unpack_from("<I", blob, 4)[0]], delta, nxt))
        print("gen_voices: voice %d  %-20s %5.1f s  %4.1f KB  preview %s" % (i, name, struct.unpack_from("<I", blob, 4)[0] * 2 / RATE, len(blob) / 1024, listen))
    if total > ROM_BUDGET:
        sys.exit("gen_voices: %.1f MB of voices; the ROM has to stay under 16 MB" % (total / 2**20))
    write_sizes(os.path.join(mod, "voices", "SIZES.md"), rows, "Voice sizes", "Voice")
    export_sfx(root, out, delta, nxt)
    open(os.path.join(out, "voices_data.s"), "w").write("\n".join(lines + [""] + tail) + "\n")


main()
