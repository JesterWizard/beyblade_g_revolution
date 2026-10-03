"""Shared by the audio mods (custom_music, custom_voices): turns sound files into chunks of the
game's own sound engine.

The engine mixes eight channels at 8000 Hz. A chunk is a 16-byte header (u32 type = 0 for
ADPCM, u32 byte length, u32 loop start = 0, u32 0) followed by one byte per two samples. The
decoder is the mixer routine in IWRAM (0x03004B74 area), two tables from the ROM:
  step delta   0x083D299C  s16 [49][16]   (nibble 0-7 add, 8-15 subtract)
  next step    0x083D2FBC  u8  [49][8]
and every byte is XORed with 0xEC. A new chunk starts from predictor 0, step 0.
"""

import bisect
import math
import os
import struct
import subprocess
import sys
import wave

import numpy as np
from scipy import signal

RATE = 8000
FADE = 16                    # samples faded at every cut (the decoder restarts from 0 there)
ROM_BUDGET = 11 * 1024 * 1024  # all mods' audio together; the ROM must stay under 16 MB (EEPROM sits at 0x0D000000); retail is 4 MB

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



def prepare_clip(path, start, end, gain, where):
    """-> mono float samples at 8000 Hz: cut to start/end seconds, centred, peak at 98% plus gain dB."""
    a = load_audio(path)
    if len(a) < RATE:
        sys.exit("%s: %s is shorter than a second" % (where, path))
    first = int(round(start * RATE))
    last = len(a) if end is None else int(round(end * RATE))
    if not 0 <= first < last <= len(a):
        sys.exit("%s: start=%s end=%s is outside the file (%.1f s long)" % (where, start, end, len(a) / RATE))
    a = a[first:last]
    if len(a) < RATE:
        sys.exit("%s: %s is shorter than a second after start/end" % (where, path))
    a = a - a.mean()
    peak = float(np.abs(a).max())
    if peak > 0:
        a = a * (0.98 / peak)
    a = np.clip(a * 10 ** (gain / 20), -1, 1)
    if len(a) % 2:
        a = a[:-1]
    return a


def snr_db(source, decoded):
    src = np.asarray(source) * 2047.0
    err = src - np.array(decoded[:len(src)])
    return 10 * math.log10(max((src ** 2).sum(), 1) / max((err ** 2).sum(), 1))


def write_preview(path, decoded):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    pcm = (np.array(decoded, dtype=np.int32) * 16).astype("<i2")
    with wave.open(path, "wb") as w:
        w.setnchannels(1)
        w.setsampwidth(2)
        w.setframerate(RATE)
        w.writeframes(pcm.tobytes())


def human(n):
    return "%.2f MB" % (n / 2**20) if n >= 2**20 else "%.1f KB" % (n / 1024)


def write_sizes(path, rows, title="Music sizes", kind="Track"):
    """music/SIZES.md: each file's size on disk against what it takes in the ROM."""
    lines = ["# " + title, "",
             "Written by the mod's generator on every build; do not edit.",
             "*Original* is the file in this folder, *in game* the chunks in the ROM (16-byte header + 4-bit ADPCM, mono, 8000 Hz).", ""]
    if rows:
        lines += ["| " + kind + " | Name | File | Original | In game | Reduction |", "|---:|---|---|---:|---:|---:|"]
        for n, name, f, orig, ingame in rows:
            lines.append("| %d | %s | %s | %s | %s | %.1f%% |" % (n, name, os.path.basename(f), human(orig), human(ingame), 100 * (1 - ingame / orig)))
        to, ti = sum(r[3] for r in rows), sum(r[4] for r in rows)
        lines.append("| | **Total** | | **%s** | **%s** | **%.1f%%** |" % (human(to), human(ti), 100 * (1 - ti / to)))
    else:
        lines.append("No tracks in `tracks.txt` yet.")
    text = "\n".join(lines) + "\n"
    if not os.path.isfile(path) or open(path).read() != text:
        open(path, "w").write(text)

