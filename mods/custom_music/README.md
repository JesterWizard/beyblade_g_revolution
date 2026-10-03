# Custom Music

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [How It Works](#-how-it-works)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

Adds your own background music to the game's 17 tracks. Put an `.mp3` or `.wav` in [`music/`](music), list it in [`tracks.txt`](tracks.txt) and `make`. Each file becomes track 17, 18, ... of the game's own BGM player (`BgmPlay`, `sub_0805FED4`), so it plays through the same sound engine, volume and fades as the retail music.

A track can also:

- **replace** a retail track (`replace=TITLE`), so the game plays yours where it would have played that one;
- join the **overworld's random draw** (`overworld=yes`), which normally picks among the first six tracks;
- have an **intro** that plays once before the part that repeats (`loop=12.5`), or play **once** (`loop=none`).

The debug menu's BGM entry lists the new tracks after the retail ones, by name.

---

## 🛠️ How To Use

1. Copy the audio file into `mods/custom_music/music/`.
2. Add a line to [`tracks.txt`](tracks.txt):

   ```
   track music/my_song.mp3 name="My Song" overworld=yes
   track music/boss.wav name="Boss Fight" loop=12.5 replace=BATTLE_THEME_E
   ```

   | Option | Meaning |
   |--------|---------|
   | `name=` | Name in the debug menu, 18 characters of ASCII. Default: the file name |
   | `loop=` | Seconds into the track where the repeat starts (the part before plays once). `none` plays the track once. Default: the whole track repeats |
   | `xfade=` | Seconds the end is crossfaded into the start of the repeat (default `0.01`). Raise it, e.g. `0.5`, for a track that ends in a long fade or a held note |
   | `overworld=yes` | Adds the track to the overworld's random draw |
   | `replace=` | A retail track to play this one instead: a number `0`-`16` or a name from [`include/bgm.h`](../../include/bgm.h) (`TITLE`, `DOJO_PRACTICE`, `BATTLE_THEME_A`, ...). One track per retail track |
   | `start=`, `end=` | Seconds to cut from the start / end of the file, for a shorter (smaller) song |
   | `gain=` | dB on top of the automatic level (the loudest peak is set to 98% of full scale) |

3. `make` (it is a default mod), or `make MOD="debug_menu custom_music"`.
4. Open the debug menu (Select on the overworld), go to **BGM** and press Right past "Lost Battle".

Every build also writes [`music/SIZES.md`](music/SIZES.md): each file's size on disk, its size in the ROM and the percentage saved.

[`gen_music.py`](tools/gen_music.py) prints one line per track with its length, size and signal-to-noise ratio, and writes what the game will play to `build/bbgr/mod/custom_music/preview/track17.wav`, `track18.wav`, ... so the result can be heard on a PC before it is flashed.

WAV files (8/16/24/32-bit PCM) are read directly. Anything else (mp3, ogg, flac, m4a, float WAV) goes through `ffmpeg`, which must be installed (or `imageio-ffmpeg` for Python). Encoded tracks are cached in the build folder by file content and options, so a rebuild only encodes what changed.

---

## 🔊 How It Works

The game does not use the GBA's usual m4a/MP2K engine. It has a small software mixer of its own: eight channels mixed at **8000 Hz** into a direct-sound FIFO, with the mixing core in IWRAM (`0x03004B74`, copied from ROM). Everything in the mod follows from how that mixer reads a sound:

- A sound is a **chunk**: a 16-byte header (`u32` type, `u32` byte length, `u32` loop start, `u32` 0) and the data. Type 0 is **4-bit ADPCM** (two samples per byte); type 1 is signed 8-bit PCM at the channel's pitch.
- The ADPCM decoder is IMA-like: every byte is XORed with `0xEC`, then each nibble adds `delta[step][nibble]` (`s16 [49][16]` at `0x083D299C`) to a 12-bit predictor and moves `step` along `next[step][nibble & 7]` (`u8 [49][8]` at `0x083D2FBC`). A chunk starts from predictor 0, step 0. The tool reads both tables from `baserom.gba` and encodes with them, so the output is exactly what the mixer decodes.
- The retail tracks are lists of chunks. `SoundPlayFromList(list, index)` plays `list[index[0]]`; when a chunk ends the mixer plays the chunk named by the next `index` entry, and `-1` goes back to `index[0]`. A one-entry list with index `{0, -1}` repeats forever; that is how a custom track loops, with no gap beyond the decoder restart.
- `SoundPlay(chunk, 0)` plays one chunk once and stops the channel at its end (`loop=none`).
- An intro is the same channel started on the intro chunk instead: the mod starts the loop chunk through `SoundPlayFromList`, then (interrupts off) points the channel at the intro; when the intro ends the mixer follows the list into the loop chunk.

**Seamless repeats.** A repeating track is cut at its first and last sound (leading and trailing silence would be a gap in every repeat). The repeating part starts at the loop point and ends with the file's last `xfade` seconds crossfaded (equal power) into the audio just before that point, which is what the first sample continues. Without `loop=` the repeat starts at the first sound, so it goes straight from the last note to the first. A given `loop=` is moved to the quietest sample within 5 ms, because the decoder restarts from zero there.

Why 8 kHz mono: that is the mixer's output rate, and ADPCM chunks ignore the channel's pitch. A file is mixed to mono, resampled to 8000 Hz with an anti-alias filter, scaled, faded for 2 ms at every cut (the decoder restarts from zero at a cut) and encoded greedily (nearest of 16 deltas per sample). Retail music is the same format, so loudness matches it.

**The BgmPlay hook.** `BgmPlay` stops the old track, stores the new number and jumps through a 17-entry table; numbers above 16 fall out of the function. The hook at `0x0805FEF4` (the `cmp r4, #0x10`) replaces those 16 bytes with `CustomBgmDispatch` ([`dispatch.s`](src/dispatch.s)), which runs the displaced instructions itself:

- track 17 and up: `CustomBgmStart`, then the retail epilogue;
- a retail track that `tracks.txt` replaces: the retail case runs first (so the state that goes with the track is set, e.g. the countdown the result jingles store), returning through a stacked copy of the epilogue frame into `CustomBgmAfter`, which stops the retail channel and starts the custom one;
- anything else: the retail jump table, unchanged.

The overworld draws its track with `RandRange(6)` in three places (`0x0803B336`, `0x080465BC`, `0x08043E2A`); `CustomBgmRand` widens the draw by the number of `overworld=yes` tracks.

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Track list** | [`tracks.txt`](tracks.txt) | One `track` line per file |
| **Converter** | [`gen_music.py`](tools/gen_music.py) | Decode, resample, ADPCM encode, write chunks and `music_data.s`; run by [`mod.mk`](mod.mk) |
| **Playback** | `CustomBgmFind`, `CustomBgmStart` in [`music.c`](src/music.c) | Picks the track for a BGM number and starts it on the sound engine |
| **Dispatch hook** | [`dispatch.s`](src/dispatch.s), `0x0805FEF4` in [`hooks.txt`](hooks.txt) | The displaced `BgmPlay` table jump, with the custom and replace paths |
| **Overworld draw** | `CustomBgmRand` in [`music.c`](src/music.c), three `call` lines in [`hooks.txt`](hooks.txt) | Adds `overworld=yes` tracks to `RandRange(6)` |
| **Debug menu** | `CustomBgmCount`, `CustomBgmName` in [`music.c`](src/music.c); weak stubs in [`bgm_weak.s`](../debug_menu/src/bgm_weak.s) | The BGM entry lists the new tracks; without this mod the stubs report none |

---

## 📝 TODO

- Play the result on hardware (everything so far ran in mGBA)
- Per-track volume in `tracks.txt` (the mixer's volume field is 0-256)
- A lookahead encoder: a beam search gained under 1 dB over the greedy one, so it was left out

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Sound quality is that of the game's own music: mono, 8 kHz, 4-bit.
- The ROM has to stay under 16 MB (the save EEPROM is mapped at `0x0D000000` for smaller ROMs), so the tool refuses more than 11 MB of music, about 23 minutes. Retail is 4 MB.
- Names are ASCII; the debug menu has room for about 18 characters.
- A looping track restarts the decoder at the seam. The repeat is cut at silence and crossfaded, so it is usually inaudible, but a loop point on a loud, steep part of the wave can still tick; move `loop=` a little or raise `xfade=`.
- Checked in mGBA: the mixer's output buffer matches the tool's own decode (correlation 0.9999), retail tracks still use their own table, a replaced track (`TITLE`) plays through the title screen and the main menu, looping and the intro switch work, `loop=none` stops at the end, the overworld draw is uniform. The sound itself was not listened to.
- Mods cannot combine with `compare`; the SHA1 differs by design.

---
