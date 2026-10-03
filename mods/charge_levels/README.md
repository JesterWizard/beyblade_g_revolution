# Charge Levels

## 🧩 Introduction

An attack has three charge levels, decided by how long the button was held when it is released: light (counter 0 to 29), medium (30 to 59) and heavy (60 to 120). In retail they differ in damage (attack x1, x2, x3), in the RPM spent on release (endurance / 2, x1, x1.5) and in the recovery before the next attack (75, 90, 120 frames). Spending RPM per damage is the same at every level, so heavy only wins on speed. This mod lets you change what each level does, using the retail values as the reference. For now it sets the recovery.

## 🛠️ How To Use

```
make MOD=charge_levels     # only this mod
make                       # all default mods, this one included
```

It is enabled by `MOD_CHARGE_LEVELS` in [`mods/mods.h`](../mods.h); set it to 0 to get the retail values back. [`settings.txt`](settings.txt) holds the numbers; edit one and run `make`:

| Setting | Default | Retail | Meaning |
|---------|---------|--------|---------|
| `recovery_light` | 40 | 75 | Frames of recovery after a light attack (1 to 255) |
| `recovery_medium` | 80 | 90 | After a medium attack |
| `recovery_heavy` | 120 | 120 | After a heavy attack |

Damage and RPM spent per level are meant to follow as more settings.

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Recovery** | [`tools/gen_settings.py`](tools/gen_settings.py), [`mod.mk`](mod.mk) | The attack release (`sub_08030388`) stores the recovery with a `movs r0, #n` per level (`0x0803055C`, `0x0803058C`, `0x080305FA`). The script turns `settings.txt` into `patch` lines for those immediates, applied with the other mods' hooks |

## 🐛 Limitations & Bugs

- The number is the timer's start value, set when the attack is released (checked in the emulator: 40, 80 and 120). It does not count down one per frame the whole time, so the real wait is longer: a light attack set to 40 was ready again after about 106 frames, a heavy one set to 120 after about 106 as well, and the medium one after 234. I have not worked out why, so the levels will not feel like 40/80/120 in play.
