---
name: gba-decomp-improve
description: >-
  Self-improvement loop for GBA matching decomp: capture wins as seeds/patterns, log
  near-misses and blockers, refresh queue and status, track metrics. Use after each
  decomp batch, when documenting blockers, growing c_patterns/BATTLE_SEEDS, or
  preparing the repo as a template for new decomp projects.
---

# Decomp self-improvement loop

Run this **after every successful batch** and **after every documented near-miss**.

## Metrics snapshot

```bash
python3 tools/decomp/report_status.py
python3 tools/decomp/progress.py --write   # JSON + status tables (no mermaid/SVG in README)
make compare
```

Track: semantic C % (functions + bytes), readable Thumb backlog, battle %.

## On MATCH (semantic C landed)

Copy checklist:

- [ ] `integrate_c.py --kind semantic` + `make compare` OK
- [ ] Field types in `unknown-types.h` if new offsets used
- [ ] Prototype in `unknown-functions.h` if others call it — use the **winning** types
      (`const u8 *` not `void *` when that fixed the prologue; see `TextMeasureWidth`)
- [ ] `/* match-compiler: old_agbcc */` in the file if only `old_agbcc` reached MATCH
- [ ] **Reusable body?** → add to `BATTLE_SEEDS` in [tools/decomp/battle_semantic_batch.py](tools/decomp/battle_semantic_batch.py)
- [ ] **Repeating asm shape?** → add pattern to [tools/decomp/c_patterns.py](tools/decomp/c_patterns.py) + note in [docs/decomp-patterns.md](docs/decomp-patterns.md)
- [ ] Log in [docs/decomp-status.md](docs/decomp-status.md) batch section
- [ ] Commit: `decomp: semantic C sub_XXXXXXXX (+1 function, M/633 total)`

### Seed template (battle_semantic_batch.py)

```python
(
    "sub_080XXXXXX",
    """void sub_080XXXXXX(void)
{
    ...
}""",
    "short-role-tag",
),
```

Verify with `battle_semantic_batch.sh 1 --seeds-only` before relying on it.

## On near-miss (DIFF, especially same-size)

Before parking, if the first mismatch is in the **prologue** (+0x2..+0x8):

- [ ] Try `void *` → `const u8 *` / `u8 *` in prototype **and** drop param-copy locals
- [ ] Score with **both** compilers (`test_variants.py` or `try_compilers.sh`)
- [ ] Try readable `switch` instead of goto chain (win: `TextMeasureWidth`)

- [ ] **Park the C** — `python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c --status "…" --next "…" --score "N/M"` (see [docs/decomp-wip.md](docs/decomp-wip.md))
- [ ] Write `src/decompiled/sub_XXXXXXXX.md`: role, process (what was tried), current state, **one** next step
- [ ] Restore readable Thumb in `src/matched/` (do not leave a DIFF draft there)
- [ ] `[[wip]]` in [docs/decomp-queue.toml](docs/decomp-queue.toml); `make queue`
- [ ] Record in `docs/decomp-status.md`: function, symptom, bytes, pointer to `src/decompiled/`
- [ ] If permuter imported: `nonmatchings/sub_XXXXXXXX/` — note best score **and** keep the `src/decompiled/` seed
- [ ] After 1–2 hand attempts + short permuter run → also `[[block]]` if auto-queue should skip it

Do **not** throw away unmatched C. Reverting `src/matched/` without a `src/decompiled/` seed is a process failure.

## On role discovery (RAM / naming)

- [ ] Promote `gUnk_*` → named symbol in `asm/ram_map_*.s` via `tools/decomp/ram_map_pass.sh`
- [ ] Update [docs/ram-map.md](docs/ram-map.md) / [docs/battle.md](docs/battle.md) if battle-related
- [ ] Phase 4 only: `[renames]` in `beyblade_g_revolution.toml` when role is stable

## Refresh work queue

```bash
python3 tools/decomp/next_queue.py --write   # or: make queue
python3 tools/decomp/cluster_shapes.py       # clone families → new c_patterns.py entry
```

Edit [docs/decomp-queue.toml](docs/decomp-queue.toml):

- `[[pin]]` — high-value targets (battle input, small IWRAM helpers)
- `[[block]]` — permuter-hard / leaf-branch class (skip in auto-ranking)

## Retrospective (every 5–10 semantic wins)

Ask:

1. Which **pattern** produced the most matches this week?
2. Any **family** of functions (same struct, same IWRAM) to batch next?
3. Should a blocker class get a **dedicated doc section** or permuter macro set?
4. Is blind m2c scan worth re-running? (Usually **no** until `c_patterns` grows.)

## Template for new repos (from this foundation)

When cloning this scaffold for another GBA title:

| Keep | Retarget |
|------|----------|
| `tools/decomp/*` pipeline | `baserom.gba` SHA1, `beyblade_g_revolution.toml` |
| agbcc + permuter layout | Function count, `asm/rom.s` peel |
| These `.cursor/skills/*` | Game-specific `unknown-types.h`, battle docs |
| Fork policy in `decomp-mission.md` | Subsystem order in roadmap |

Bootstrap checklist: [reference.md](reference.md)

## Anti-patterns (slow the loop)

- Long blind `m2c` scans on all readable Thumb (low yield here)
- Re-reading mission/roadmap instead of `agent_packet.py --next`
- Re-trying blocked leaf-branch functions without new technique
- Integrating without `match_function.py` MATCH
- Hand-editing `asm/nonmatchings/*.s`
- Skipping status doc updates (lose near-miss knowledge)
- Using `register` or empty `asm("")` to force a match (park instead)
