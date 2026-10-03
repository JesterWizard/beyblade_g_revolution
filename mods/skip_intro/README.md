# Skip Intro

## 🧩 Introduction

Retail shows six splash screens (Nintendo licence, copyright, Nelvana, D Rights, Atari, Fullfat) before the title screen. This mod removes them: the game goes straight to the title screen.

## 🛠️ How To Use

```
make MOD=skip_intro     # only this mod
make                    # all default mods, this one included
```

It is part of `DEFAULT_MOD`; remove `skip_intro` from that list in the Makefile to get the splash screens back.

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Splash sequence** | `patch 0x080663E0` in [`hooks.txt`](hooks.txt) | The boot function `sub_080663C8` calls `0x08065C7C`, which plays the six screens (table `0x080B9000`). That `bl` is replaced by two nops |

## 🐛 Limitations & Bugs

- Checked in the emulator: the title screen shows within 30 frames of boot and Start reaches the main menu. Whether anything else relied on the splash code running (it is skipped entirely) is only covered by that boot-to-menu check.
