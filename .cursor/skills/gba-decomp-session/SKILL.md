---
name: gba-decomp-session
description: >-
  Runs byte-matching GBA decompilation sessions on this repo (agbcc, match_function.py,
  make compare). Use when decomping, matching functions, Phase 3b semantic C, battle
  subsystem work, autonomous decomp batches, or bootstrapping work from this scaffold.
---

# GBA decomp session (Beyblade G Revolution)

## Read first (every session)

1. [docs/decomp-mission.md](docs/decomp-mission.md) — fork policy, done criteria
2. [AGENTS.md](AGENTS.md) — tools, commit policy, must-nots
3. [docs/decomp-patterns.md](docs/decomp-patterns.md) — fast path per function

## Gate

```bash
python3 tools/decomp/report_status.py
make compare   # must print beyblade_g_revolution.gba: OK before integrating
```

## Pick targets (fastest yield)

```bash
python3 tools/decomp/next_queue.py -n 10   # or: make queue
python3 tools/decomp/battle_scan.py -n 20  # battle subsystem first
```

**Prefer:** `push {lr}` prologue, no leaf-only branches, IWRAM/struct field stores, ≤60B.

**Defer / block:** leaf + `if` (extra `push {lr}`), table-lookup pool family, multi-pool epilogues. See [docs/decomp-queue.toml](docs/decomp-queue.toml) `[[block]]`.

## Per-function loop

```bash
python3 tools/decomp/try_convert.py sub_XXXXXXXX              # patterns → m2c → verify
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate --note "role-hint"
# Or manual:
python3 tools/decomp/match_function.py sub_XXXXXXXX src/matched/sub_XXXXXXXX.c
python3 tools/decomp/integrate_c.py sub_XXXXXXXX @file.c --kind semantic --note "…"
python3 tools/decomp/function_scores.py --write   # N/M bytes + status per function
make compare
```

## Fork policy (stop guessing)

```
trivial c_patterns?     → integrate
m2c + hand C → MATCH?   → integrate (--kind semantic)
same-size DIFF?         → register pin / tmp[] pool (see gba-decomp-matching skill)
still DIFF?             → permuter, then block + readable Thumb
role clear?             → ram_map_pass.sh, then retry
```

## Batch runners

| Command | Use when |
|---------|----------|
| `tools/decomp/battle_semantic_batch.sh 10 --seeds-only` | Battle; hand seeds first |
| `tools/decomp/c_convert_batch.sh 30` | Trivial patterns only |
| `tools/decomp/cursor_batch.sh 10` | Hard fn; m2c seeds |
| `tools/decomp/match_batch.sh 10` | Asm verify → integrate peel |

## Non-negotiables

- Never hand-edit `asm/nonmatchings/*.s` — `tools/decomp/generate_asm.py --force`
- C89 on matching paths; no offset-casts / `asm volatile` in new semantic C
- RAM via `ram_map.h` / struct members in `unknown-types.h`
- `make compare` must stay OK every batch

## After each green batch

1. Update [docs/decomp-status.md](docs/decomp-status.md)
2. Run **gba-decomp-improve** checklist (patterns, seeds, queue)
3. Commit per AGENTS.md unless user forbids

## Related skills

- **gba-decomp-matching** — near-miss fixes, register pin, permuter
- **gba-decomp-improve** — self-improvement loop, capture learnings
- **gba-decomp-ecosystem** — external guides, new-repo bootstrap
