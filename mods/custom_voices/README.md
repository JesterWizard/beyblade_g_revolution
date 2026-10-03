# Custom Voices

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

Plays your own voice clips in the game. Put an `.mp3` or `.wav` in [`voices/`](voices), list it in [`voices.txt`](voices.txt) and `make`. A clip can

- **play when the player's blade is launched** (`on=launch`; with several, one is picked at random each launch), or
- **replace one of the game's 16 sound effects** (`replace=3`), wherever the game plays it.

It uses the same converter as [`custom_music`](../custom_music) ([`tools/mod/gba_adpcm.py`](../../tools/mod/gba_adpcm.py)) and the same sound engine, so a clip is mono, 8 kHz, 4-bit ADPCM, about 4 KB per second. The ipatix HQ mixer from the Yu-Gi-Oh project is for the m4a engine and has no place here; this game has its own mixer (see the music mod's README).

---

## 🛠️ How To Use

1. Copy the audio file into `mods/custom_voices/voices/`.
2. Add a line to [`voices.txt`](voices.txt):

   ```
   voice voices/let_it_rip.wav name="Let it rip" on=launch
   voice voices/hit.wav name="Hit" replace=3
   ```

   | Option | Meaning |
   |--------|---------|
   | `on=launch` | Plays when the player's blade is launched |
   | `replace=` | Plays instead of retail sound effect `0`-`15`. One clip per effect |
   | `name=` | Only used in `voices/SIZES.md`. Default: the file name |
   | `gain=` | dB on top of the automatic level (the loudest peak is set to 98% of full scale) |
   | `start=`, `end=` | Seconds to cut from the start / end of the file |

3. `make` (it is a default mod), or `make MOD="custom_voices"`.

To choose a `replace=` number by ear, the build writes the 16 retail effects to `build/bbgr/mod/custom_voices/sfx/sfx00.wav` ... `sfx15.wav` (pitch is approximate: the game plays them at a note it chooses). `build/bbgr/mod/custom_voices/preview/voice0.wav`, ... is what the game will play for each clip. Every build also writes [`voices/SIZES.md`](voices/SIZES.md): original size, size in the ROM and percentage saved.

Keep clips short: the ROM has to stay under 16 MB, and `custom_music` shares that budget (11 MB of audio in all).

---

## 🔊 How It Works

- A clip is one ADPCM chunk played with `SoundPlay(chunk, 0)` on a free mixer channel at the sound effect volume; the mixer stops the channel at the end. The game's eight channels are shared with the music and effects, so a clip can be dropped if all eight are busy (the engine prints a debug message and plays nothing).
- **Launch.** The battle code reaches state 9 of the launch, calls `sub_0803CECC` (the launch RPM; `debug_menu` hooks that `bl` at `0x0803C230`), then stores state 5 at `+0x12C`. The hook at `0x0803C234` ([`launch.s`](src/launch.s)) takes the 16 bytes from that store on, calls `VoiceOnLaunch`, and runs the displaced instructions. It does not touch the `bl`, so it works with or without `debug_menu`.
- **Replacing an effect.** Every effect goes through `SfxPlayInSlot` (`sub_080601C4`): effect number, note. The replacement hook plays your clip when `voices.txt` replaces that number and otherwise does what retail did. The clip's handle goes in the effect's own handle slot, so stopping the effect stops the clip. A replaced effect loses the note variation some effects have (effect 4 is played at a random note).

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Clip list** | [`voices.txt`](voices.txt) | One `voice` line per file |
| **Converter** | [`gen_voices.py`](tools/gen_voices.py), [`gba_adpcm.py`](../../tools/mod/gba_adpcm.py) | Decode, resample, ADPCM encode, write chunks and `voices_data.s`; run by [`mod.mk`](mod.mk) |
| **Launch** | `VoiceOnLaunch` in [`voices.c`](src/voices.c), [`launch.s`](src/launch.s), `0x0803C234` in [`hooks.txt`](hooks.txt) | Picks and plays an `on=launch` clip |
| **Effect replacement** | `SfxPlayInSlot__Voices` in [`voices.c`](src/voices.c), `sub_080601C4` in [`hooks.txt`](hooks.txt) | Retail `SfxPlayInSlot` with the replacement lookup |

---

## 📝 TODO

- More events than the launch (win, loss, clash, ...): each needs its own hook in the battle code
- Name the 16 retail effects once they are identified
- Voices for the opponent's launch

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Sound quality is that of the game's own audio: mono, 8 kHz, 4-bit.
- Checked in mGBA by calling the game's own functions: `SfxPlayInSlot` plays a replaced effect on a channel and still plays retail ones, `VoiceOnLaunch` plays the clip, and the patched ROM bytes at `0x0803C234` jump to the hook. A duel was not played through, and nothing was listened to, so the launch moment itself has not been seen in game.
- Mods cannot combine with `compare`; the SHA1 differs by design.

---
