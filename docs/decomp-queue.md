# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-10-01T16:11:42Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 626 |
| Still need semantic C | **7** |
| Readable Thumb remaining | 7 |
| Opcode embeds remaining | 0 |
| Battle pending | 0 (160 already semantic) |
| Blocked (documented) | 2 |
| WIP (resume these first) | 6 |

Ranking: **battle** · showing top **40**

Park unmatched C in [`src/decompiled/`](../src/decompiled/README.md) — see [`decomp-wip.md`](decomp-wip.md).

## Resume (WIP)

_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._

| Function | Bytes | Score | Seed | Status | Next |
|----------|------:|-------|------|--------|------|
| `sub_08035624` | 114 | 45/114 (size 112 vs 114; old 71/114 seed saved only in scratch) | `src/decompiled/sub_08035624.c` | structure matches; only key/list/scratch register choice differs (retail key=r4, list=r2, const scratch=r0; ours r0/r0/r2). 37 differing insns vs 59 for the old seed | find C that makes key addr r4 and list addr r2 (forcing them with a debug compiler makes output equal retail); try permuter on this draft with a time limit |
| `sub_0804BD38` | 328 | 302/328 | `src/decompiled/sub_0804BD38.c` | same-size DIFF 302/328; permuter 300s best 870 (base 905); decl/init-order perms and first-read shape variants no change | first two s16 loads: retail base r3/zero r4 then base r0/zero r2; ours r0/r4 and r0/r4. Likely needs a different source shape for what keeps r1/r2 conflicts alive |
| `sub_0804C8BC` | 372 | 74/372 | `src/decompiled/sub_0804C8BC.c` | New semantic draft (the old one was a junk stub): five list rows from gData_080989F0 (struct Unk4C8BCRow). Logic exact, 4 bytes long. Retail has five loop givs (palette pointer, i*4, two row givs, i*16) and copies the i*16 giv into a stack local for the sprite y; every shape tried either drops the i*16 giv or adds a (y+0x38)<<8 giv. | Find the source form of the sprite y ((i*16 + 0x38) << 8) that reuses the i*16 giv through a copy. |
| `sub_0806EC20` | 516 | 155/516 | `src/decompiled/sub_0806EC20.c` | old_agbcc 155/516, 508 vs 516; a in r5, cfg in r8; bits in r9 not sp+0x14 | pin bits to sp+0x14 so py can take r9 and 0x35E/0x362 go to the pool |
| `sub_0806E060` | 492 | 89/492 | `src/decompiled/sub_0806E060.c` | bezier keyframe sampler 468/492 | idx in r10, f in r12, p0/p1 in sp0/sp4; 0x180 not folded |
| `sub_080706B0` | 626 | 61/626 | `src/decompiled/sub_080706B0.c` | logic complete, old_agbcc, 620/626 B | retail spills spacing (sp24) and keeps glyph width in r8 in the per-glyph check; case 1 tail is cross-jumped with the no-widths path; first=head load sits between count-- and the loop test |

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
