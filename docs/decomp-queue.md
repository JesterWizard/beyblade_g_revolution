# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-10-01T20:54:33Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 631 |
| Still need semantic C | **2** |
| Readable Thumb remaining | 2 |
| Opcode embeds remaining | 0 |
| Battle pending | 0 (160 already semantic) |
| Blocked (documented) | 2 |
| WIP (resume these first) | 2 |

Ranking: **battle** · showing top **40**

Park unmatched C in [`src/decompiled/`](../src/decompiled/README.md) — see [`decomp-wip.md`](decomp-wip.md).

## Resume (WIP)

_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._

| Function | Bytes | Score | Seed | Status | Next |
|----------|------:|-------|------|--------|------|
| `sub_08035624` | 114 | 45/114 | `src/decompiled/sub_08035624.c` | structure matches; only key/list/scratch register choice differs (retail key=r4, list=r2, const scratch=r0; ours r0/r0/r2). 37 differing insns vs 59 for the old seed | find C that makes key addr r4 and list addr r2 (forcing them with a debug compiler makes output equal retail); try permuter on this draft with a time limit |
| `sub_080706B0` | 0 | 452/626 | `src/decompiled/sub_080706B0.c` | same-size DIFF after permuter, allocation only | init-load order of locals, spacing spill (sp24), glyph width kept in r8 |

Per-function notes: `src/decompiled/<fn>.md`.

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| _none_ | | | | | | All functions are semantic C |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_08038314` | `0x08038314` | 0 | battle countdown gate: same-size DIFF (59/108); mask loaded+ANDed before vs after the #3 immediate. Needs permuter. |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c --status "…" --next "…"
python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/function_scores.py --close
python3 tools/decomp/script_first.py
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/cluster_shapes.py
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
```

Full ranked backlog (0 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
