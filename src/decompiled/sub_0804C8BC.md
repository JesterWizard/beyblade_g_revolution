# sub_0804C8BC — WIP

| | |
|--|--|
| ROM | `0x0804C8BC` |
| Seed | `src/decompiled/sub_0804C8BC.c` |
| Last `match_function.py` | 74/372 |

## Process

- 2026-09-28 (final sweep): New semantic draft (the old one was a junk stub): five list rows from gData_080989F0 (struct Unk4C8BCRow). Logic exact, 4 bytes long. Retail has five loop givs (palette pointer, i*4, two row givs, i*16) and copies the i*16 giv into a stack local for the sprite y; every shape tried either drops the i*16 giv or adds a (y+0x38)<<8 giv. Next: Find the source form of the sprite y ((i*16 + 0x38) << 8) that reuses the i*16 giv through a copy.

## Current state

New semantic draft (the old one was a junk stub): five list rows from gData_080989F0 (struct Unk4C8BCRow). Logic exact, 4 bytes long. Retail has five loop givs (palette pointer, i*4, two row givs, i*16) and copies the i*16 giv into a stack local for the sprite y; every shape tried either drops the i*16 giv or adds a (y+0x38)<<8 giv.

## Next

Find the source form of the sprite y ((i*16 + 0x38) << 8) that reuses the i*16 giv through a copy.

- 2026-10-01 (second attempt, mechanical sweep of ~3000 variants + permuter 420 s) — best is now same-size 185/372 (49.7%): `y = i * 16;` just before `if (i == gData_03000684)`, sprite y as `(y << 8) + 0x3800`, alloc and the row block wrapped in `do { } while (0)`. Permuter found nothing below its base score (1870).
  - Loop-dump (`-dL`) root cause of the remaining gap: retail reduces the `i*16` giv (r8) for the cursor `+24` and keeps `(y+56)<<8` as plain arithmetic on a stack copy of the PRE reaching reg. We either reduce `(i*16+56)<<8` into its own counter (c0 shape) or, with `y` as a user variable, the `i*16` group fails the benefit test (`copy_cost` penalty, "-4620 vs 131") and nothing is reduced (b1 shape).
  - With a debug-compiler hook that skips reduction of the two derived givs (NOGIV=274,275) the output is within ~80 diff lines of retail, and only register naming / the stack copy remain, so this is purely the giv decision.
  - Tried: y local at 6 positions, u16/u8/s32 y, explicit biv `y += 16`, 4 sprite expression forms, sy temp, do-while weights on 4 statements. Next idea: find a form where the shift/add on the copy is not a candidate giv (e.g. make the use go through memory or a non-linear op that costs no code).
