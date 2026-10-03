# Finishers

## 🧩 Introduction

In retail there are three ways to end a match, but only one of them is practical: wearing the opponent's spin down to 0. A blade also **breaks** when its wear reaches 100% ("Ray's Driger G Beyblade has broken.", the match ends on the spot and you win), and a blade is **rung out** when it is airborne above the wall. Neither ever happens on purpose:

- Wear grows by only half of what a hit does beyond the target's endurance, divided by the spin the blade started with. Against a 3,500 RPM opponent that is hundreds of hits.
- Nothing in a clash throws a blade into the air. The wall only counts as a ring-out when the blade is above `z = 0x8000`, which only the dodge jump reaches, and the wall pushes a grounded blade back inside.

This mod gives both of them a way in. Both are decided by the same number, the damage the winner of a clash dealt (a charged attack hits three times as hard as a plain one, and a blocked hit does nothing).

| Finisher | What a hit now does |
|----------|---------------------|
| **Break** | Adds 0.0625% of wear to the loser for every point of damage, at most 3.125% for one hit (so even a late-game blade needs 32). A plain hit from an early blade is about 18 damage, which is about 1.1%: around 90 hits against an average blade, 30 to 50 for a charged one. |
| **Ring-out** | The loser is thrown directly away from the winner at 45 units/256 per frame per point of damage (capped at 3200). Only a **green** (medium charge) or **red** (high charge) attack also lifts the loser, and only when more than half of the attack's full power got through: a clash between two attackers halves both powers, and a block takes the rest off, so those leave the loser on the ground. A red attack lifts a bit higher than a green one. A blade thrown over the wall while it is lifted is out; one thrown at the middle just lands back in the dish. Hitting a blade that is near the wall, from the side that faces the middle, is what rings it out. |

Spin-out still works exactly as before; the two new ways just stop being a joke next to it. Blocking (defence) is the counter to both, since a blocked hit deals no damage.

## 🛠️ How To Use

```
make MOD=finishers      # only this mod
make                    # all default mods, this one included
```

It is enabled by `MOD_FINISHERS` in [`mods/mods.h`](../mods.h); set it to 0 to get the retail rules back. The numbers are `#define`s at the top of [`finishers.c`](src/finishers.c):

| Define | Default | Meaning |
|--------|---------|---------|
| `BREAK_UNITS` | 625 | Wear for each point of damage, in millionths of the blade's starting spin (625 = 0.0625%) |
| `BREAK_HIT_MAX` | 31250 | Most wear (same unit) one hit can add |
| `BREAK_PLAYER` | 0 | 1: **your** blade wears the same way. Off by default because a broken player blade is taken from you for good |
| `KNOCK_PLAYER` | 1 | 0: only the opponent is thrown. On by default, so ring-outs cut both ways |
| `KNOCK_SPEED` / `KNOCK_MAX` | 45 / 3200 | Speed of the throw per point of damage, and its cap (the physics step itself clamps an axis at 4096) |
| `HOP_GREEN` / `HOP_RED` | 4800 / 5300 | Upward velocity of the lift for a medium / high charge. About 4570 just reaches the wall's height, so these stay above it for about 10 / 17 frames |

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Clash hook** | `call 0x08032B3C` in [`hooks.txt`](hooks.txt) | `sub_08032A88` resolves a clash with `sub_0802FFAC` and, when somebody won, shows the damage number with `sub_08033630(damage, 80, 60, winner index)`. That call is the only place that has the damage and the winner together, so it is wrapped |
| **Break** | Adds 0.0625% of wear to the loser for every point of damage, at most 3.125% for one hit (so even a late-game blade needs 32). A plain hit from an early blade is about 18 damage, which is about 1.1%: around 90 hits against an average blade, 30 to 50 for a charged one. |
| **Ring-out** | The loser is thrown directly away from the winner at 45 units/256 per frame per point of damage (capped at 3200). Only a **green** (medium charge) or **red** (high charge) attack also lifts the loser, and only when more than half of the attack's full power got through: a clash between two attackers halves both powers, and a block takes the rest off, so those leave the loser on the ground. A red attack lifts a bit higher than a green one. A blade thrown over the wall while it is lifted is out; one thrown at the middle just lands back in the dish. Hitting a blade that is near the wall, from the side that faces the middle, is what rings it out. |

## 🐛 Limitations & Bugs


- Checked in the headless emulator on the first duel of a new game with the attack stat raised: at the earlier, four times stronger setting a 32-damage hit added 16% wear and six hits broke the opponent (now 2%, about 50 hits) (the result screen shows the credits for a win), and a green or red hit that landed on a blade near the wall rang it out about 20 frames after the clash scene. Not played through by hand.
- The knockback is applied when the clash is resolved, then the clash scene plays, so the throw only becomes visible when it ends.
- Throwing the player is on by default, so a charged hit from the opponent next to the wall can end a match at once. The retail AI does not know about this and does not try to avoid or aim for it.
- `BREAK_PLAYER=1` makes a broken player blade permanent (retail's own rule when the wear reaches 100%); `keep_blade` only covers losing the match, not a blade that broke.
