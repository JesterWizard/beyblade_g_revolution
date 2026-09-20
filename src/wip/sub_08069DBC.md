# sub_08069DBC — WIP

| | |
|--|--|
| ROM | `0x08069DBC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/wip/sub_08069DBC.c` |
| Last `match_function.py` | 25/96 then 63/96
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-20 — parked. Status: Two semantic attempts: direct tiled copy 25/96, then deferred shift load and matching size reached 63/96. Source addressing now matches retail; remaining mismatch is destination/loop register shape (retail keeps destination in r2, source in r5, destination increment in r4, and state +0x5F pointer in r3).

## Current state

Two semantic attempts: direct tiled copy 25/96, then deferred shift load and matching size reached 63/96. Source addressing now matches retail; remaining mismatch is destination/loop register shape (retail keeps destination in r2, source in r5, destination increment in r4, and state +0x5F pointer in r3).

## Next

Pin destination r2, source r5, source stride r1, destination stride r4, and a state +0x5F byte pointer r3. Build the VRAM base in r2 before adding the shifted destination offset, then use pointer increments matching the retail loop.
