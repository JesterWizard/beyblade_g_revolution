---
name: gba-decomp-session
description: >-
  Runs byte-matching GBA decompilation sessions on this repo (agbcc, match_function.py,
  make compare). Use when decomping, matching functions, Phase 3b semantic C, battle
  subsystem work, autonomous decomp batches, or bootstrapping work from this scaffold.
---

# GBA decomp session (Beyblade G Revolution)

Do **not** re-read mission/roadmap/architecture — they are already in workspace rules.
Start with scripts. Only open a packet when scripts leave a remainder.

## Gate

```bash
python3 tools/decomp/report_status.py
make compare
python3 tools/decomp/script_first.py          # patterns + cleaned m2c; integrate MATCH
```

## If scripts left work: one packet, then stop guessing

```bash
python3 tools/decomp/agent_packet.py --next   # cheapest remaining; --battle / --wip to retarget
# Write C from the packet seed only. Max 2 match_function.py retries, then:
python3 tools/decomp/park_wip.py sub_XXXXXXXX scratch.c --status "…" --next "…" --score "N/M"
```

Do not grep headers or dump full objdump. The packet has offsets, callees, cleaned m2c, and compact DIFF.

## Fork policy

```
script_first MATCH?     → already integrated; make compare
c_patterns / m2c-clean? → try_convert.py --integrate
same-size DIFF?         → permuter (not 15 hand retries)
still DIFF?             → park_wip.py; restore Thumb in src/matched
clone family?           → cluster_shapes.py → one new c_patterns.py matcher
```

## Batch runners

| Command | Use when |
|---------|----------|
| `python3 tools/decomp/script_first.py` | **Every session first** |
| `python3 tools/decomp/agent_packet.py --next` | One leftover function |
| `python3 tools/decomp/cluster_shapes.py` | Grow `c_patterns.py` |
| `python3 tools/decomp/unblock_symbols.py` | Bare `bl _080…` prototypes |

## Non-negotiables

- Never hand-edit `asm/nonmatchings/*.s` — `tools/decomp/generate_asm.py --force`
- C89 on matching paths; no offset-casts / `asm volatile` in new semantic C
- RAM via `ram_map.h` / struct members in `unknown-types.h`
- `make compare` must stay OK every batch

## After each green batch

1. Update [docs/decomp-status.md](docs/decomp-status.md)
2. Run **gba-decomp-improve** checklist (patterns from clusters, seeds, queue)
3. Unmatched C → `src/wip/` (`park_wip.py`)
4. Commit per AGENTS.md unless user forbids

## Related skills

- **gba-decomp-matching** — near-miss fixes, register pin, permuter
- **gba-decomp-improve** — self-improvement loop, capture learnings
- **gba-decomp-ecosystem** — external guides, new-repo bootstrap
