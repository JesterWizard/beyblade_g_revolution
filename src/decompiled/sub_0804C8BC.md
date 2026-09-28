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
