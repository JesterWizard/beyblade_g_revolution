# Skip Intro

## 🧩 Introduction

Retail shows six splash screens (Nintendo licence, copyright, Nelvana, D Rights, Atari, Fullfat) before the title screen. This mod removes them: the game goes straight to the title screen.

## 🛠️ How To Use

```
make MOD=skip_intro     # only this mod
make                    # all default mods, this one included
```

It is enabled by `MOD_SKIP_INTRO` in [`mods/mods.h`](../mods.h); set it to 0 to get the splash screens back.

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Splash sequence** | `call 0x080663E0` in [`hooks.txt`](hooks.txt) | The boot function `sub_080663C8` calls `0x08065C7C`, which plays the six screens (table `0x080B9000`). That call goes to `SkipIntro` in [`skip_intro.c`](src/skip_intro.c) instead |
| **Save check** | `SkipIntro` | The first splash screen also runs `SaveDataVerify` (`0x08044A8C`, called only from `0x08065D84`), which reads the save header and slot for the title menu. `SkipIntro` calls it, so saves are still recognised |

## 🐛 Limitations & Bugs

- Checked in the emulator: the title screen shows within 50 frames of boot, Start reaches the main menu, and after boot the save header and slot are loaded into memory exactly as in the retail game (`MainWork+0x1688` / `+0x168C` set, flags `+0x185B` / `+0x185C` = 0 / 1). Whether anything else relied on the rest of the splash code is only covered by that check.
- The first version of this mod skipped the whole routine, `SaveDataVerify` included, so saves were not recognised.
