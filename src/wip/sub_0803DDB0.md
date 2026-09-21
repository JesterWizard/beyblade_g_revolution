# sub_0803DDB0 — WIP

| | |
|--|--|
| ROM | `0x0803DDB0` |
| Retail | 40 B: identical structure to `sub_0803DDD8` with the pointer table at `0x0807AEEC` |
| `src/matched` | `src/matched/sub_0803DDB0.c` — **MATCHED** (old_agbcc) |
| Seed | `src/wip/sub_0803DDB0.c` |
| Last `match_function.py` | 40/40 (`old_agbcc`) |
| Sibling / types | Twin of `sub_0803DDD8` |

## Role

Same slot/offset lookup as `sub_0803DDD8`, against the second pointer table.

## Process

- 2026-09-21 — **matched** by cloning the `sub_0803DDD8` shape and swapping the table
  symbol. Cracked one, the twin followed with no further work — exactly as the sweep
  predicted for the 85% pair.

## Current state

Matched and integrated; `make compare` OK.

## Next

Done.
