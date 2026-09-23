# Agent notes — hands-off matching decompilation

You are the **autonomous decompilation agent** for Beyblade G Revolution. The user is
hands-off: you run tools, integrate results, and report summaries. Do not ask the user
to run commands unless a hard blocker requires credentials they alone control
(e.g. baserom missing). **Cursor is the agent** — Mizuchi/Claude API is optional.

Read **[docs/decomp-mission.md](docs/decomp-mission.md)** only if a packet is insufficient — do **not**
re-read it every session. Workspace rules already carry the fork policy.

## Mission

Produce **byte-matching** C (`make compare` → `beyblade_g_revolution.gba: OK`) by
automating: `script_first.py` → packet → integrate → verify → report.

Since the pipeline rework there are **four parallel axes**, and matching no longer
gates the others:

| Axis | Output | Tool |
|------|--------|------|
| Matching C | `src/matched/*.c` | `script_first.py`, `match_function.py`, `integrate_c.py` |
| Drafts (DECOMPILED tier) | `src/decompiled/*.c` | `park_wip.py`, `promote_wip.py` |
| Analysis DB | `analysis/*.json` | `analyze.py` (`make analyze`) |
| Names | `analysis/symbols.json` | `symbols.py` (`make symbols`) |
| Docs | `docs/systems/`, `docs/functions/` | `document.py` (`make document`) |

Design: **[docs/decomp-pipeline.md](docs/decomp-pipeline.md)**. Lifecycle
vocabulary: `tools/decomp/tier.py`.

## One-time bootstrap (run if not done)

```bash
bash build_tools.sh
```

This installs agbcc, gbafix, Luvdis, m2c, generates `asm/nonmatchings/`, and verifies
`make compare`. Mizuchi (npm) is optional.

**Primary batch runner:** `python3 tools/decomp/script_first.py` — no API key required.

## Every work session (repeat until done)

**Autonomous loop — no user approval between batches.** See
[docs/decomp-roadmap.md](docs/decomp-roadmap.md) for phases.

```bash
# 1. Status
python3 tools/decomp/report_status.py
make compare

# 2. Deterministic pass (no model)
python3 tools/decomp/script_first.py

# 3. Remainder: one compact packet, then C (max 1 attempt → permuter → park)
python3 tools/decomp/agent_packet.py --next

# 4. Naming — independent of matching, so all 633 are eligible
make analyze
python3 tools/decomp/symbols.py set sub_XXXXXXXX --symbol Name \
    --confidence 0.8 --source ai --evidence "why you believe this"
python3 tools/decomp/symbols.py apply

# 5. Every 3–5 batches: RAM map pass, then refresh derived views
tools/decomp/ram_map_pass.sh
make analyze && make document

# 6. Report
python3 tools/decomp/report_status.py
```

Optional: `python3 tools/decomp/cluster_shapes.py` to grow `c_patterns.py` from clone families.

`./decomp {setup,analyze,decompile,rename,document,verify,status}` is a dispatch
shim over all of the above.

### Commit policy

**Commit after every successful semantic batch** (`script_first.py` or `integrate_c.py`) — do not ask the user. Message:
`decomp: C batch (+N functions, M/633 in src/matched)`. Never commit if `make compare` fails.

If `asm/nonmatchings/` is empty:

```bash
python3 tools/decomp/generate_asm.py --force
make compare
```

If agbcc is missing:

```bash
bash build_tools.sh
```

## What you may edit

| Area | Rule |
|------|------|
| `src/*.c` | Add matched decomp; comment header with ROM address |
| `src/decompiled/` | Unmatched C + notes, the DECOMPILED tier (`park_wip.py`); not linked |
| `analysis/*.json` | Generated analysis DB + `symbols.json` (names live here, not in source) |
| `include/symbols.h` | Generated view of `symbols.json` — regenerate, never hand-edit |
| `docs/systems/`, `docs/functions/` | Generated docs from the analysis DB |
| `asm/rom.s` | Shrink `.incbin` as matched code replaces baserom peels |
| `include/*.h` | Types discovered during decomp |
| `beyblade_g_revolution.toml` | Function renames (`[renames]`) |
| `docs/decomp-status.md` | Progress log after each batch |
| `docs/decomp-progress.json` | Live C-vs-original counters (functions + bytes) |
| `docs/decomp-progress.svg` | Optional chart in `docs/` only — **never** README |
| `ld_script.ld` / `Makefile` | When adding new `src/` objects |

## What you must NOT do

- Hand-edit `asm/nonmatchings/*.s` (regenerate via `tools/decomp/generate_asm.py`)
- Revert unmatched C without parking `src/decompiled/` + notes ([docs/decomp-wip.md](docs/decomp-wip.md))
- Accept a match without objdiff 0-diff (Mizuchi enforces; still re-run `make compare`)
- Use C99 in matching paths or “fix” UB without `UBFIX`/`BUGFIX` guards
- Hardcode IWRAM/EWRAM addresses — use `asm/ram_map*.s`
- Hand-edit `include/symbols.h`, `[renames]`, or `analysis/*.json` — all are generated views; edit `analysis/symbols.json` via `symbols.py`
- Rename identifiers with a plain text replace — it will corrupt `asm("...")` string literals, where the preprocessor cannot expand a macro. Use `symbols.py apply`
- Use offset-casts (`*(u16 *)((u8 *)p + off)`), `register`, `asm volatile`, GCC asm labels, or empty `asm("")` barriers in semantic C — struct members in `unknown-types.h`. Inline `asm()` is only for BIOS `swi` and naked Thumb wrappers.
- Enable `HACKS=1` during matching work (`make compare` must stay green)

## Matching vs hacking

| Goal | Command |
|------|---------|
| Matching decomp | `make compare` (`HACKS=0`, default) |
| Append / hacks | `make HACKS=1 modern` (breaks SHA1 compare) |

## Tooling map

| Tool | Path | Role |
|------|------|------|
| Signature arity | `tools/decomp/audit_signatures.py` | Prototypes vs definitions vs call sites |
| Fix stub arity | `tools/decomp/fix_stub_arities.py` | Align asm stubs to the agreed arity |
| Prune drafts | `tools/decomp/prune_drafts.py` | Drop drafts a semantic match superseded |
| Queue state | `tools/decomp/queue_toml.py` | Block-wise `[[wip]]` edits + `--check` |
| Lifecycle vocabulary | `tools/decomp/tier.py` | Single enum: has_c / named / matches → tier |
| Analysis DB | `tools/decomp/analyze.py` | `analysis/{functions,xrefs,structs,systems}.json` |
| Subsystems | `tools/decomp/systems.py` | Deterministic, evidence-backed membership |
| Symbols | `tools/decomp/symbols.py` | `symbols.json` CRUD + alias header generation |
| Promote tier | `tools/decomp/promote_wip.py` | One-time legacy `src/wip/` → `src/decompiled/` migration |
| Documentation | `tools/decomp/document.py` | `docs/systems/`, `docs/functions/` |
| Pipeline CLI | `tools/decomp/cli.py` | `./decomp <stage>` dispatch shim |
| Script-first | `tools/decomp/script_first.py` | Patterns + cleaned m2c; integrate MATCH |
| Function packet | `tools/decomp/agent_packet.py` | Compact context for one leftover function |
| m2c cleanup | `tools/decomp/m2c_cleanup.py` | RAM names, struct fields, strip m2c chrome |
| Shape cluster | `tools/decomp/cluster_shapes.py` | Clone families → new `c_patterns.py` matchers |
| Unblock symbols | `tools/decomp/unblock_symbols.py` | Draft prototypes for `bl _080…` |
| Try convert | `tools/decomp/try_convert.py` | One-function patterns + cleaned m2c |
| Verify C | `tools/decomp/match_function.py` | Compile + compact DIFF vs retail |
| C compile audit | `tools/decomp/audit_c_compiles.py` | `make audit` — find matched C that will not compile |
| Signature repair | `tools/decomp/repair_naked_signatures.py` | `make repair-signatures` — align defs with prototypes |
| Word diff | `tools/decomp/worddiff.py` | Word-aligned retail-vs-compiled table (16-bit words, DIFF flagged) |
| Variant sweep | `tools/decomp/test_variants.py` | Test many `@@BODY@@` source variants against one function |
| Integrate C | `tools/decomp/integrate_c.py` | Land MATCH into `src/matched/` |
| Park WIP | `tools/decomp/park_wip.py` | Save unmatched C + notes (`src/decompiled/`) |
| Local permuter | `tools/decomp/permuter/auto.py` | Import → score → search → integrate on score 0 |
| decomp-permuter | `tools/decomp/permuter/` | agbcc literal-pool / instruction-order search |
| agbcc | `tools/agbcc/bin/agbcc` | Matching compiler |
| Luvdis | `tools/luvdis/` | Initial disassembly |
| ROM layout | `tools/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |
| Shiftable check | `tools/decomp/check_shiftable.py` | Phase 5 gate |
| Status | `tools/decomp/report_status.py` | Progress summary + refresh counter |
| Progress bar | `tools/decomp/progress.py` | Semantic C % vs original (JSON + SVG) |
| Per-function compiler | `/* match-compiler: old_agbcc */` in the .c | `agbcc` and `old_agbcc` generate different code; `match_function.py` + the permuter honour the comment |

## User report template

Post this after every batch (fill in values):

```
## Decomp batch report

- **Matched this batch:** N / attempted M
- **Decompiled C:** X% functions / Y% bytes (from `progress.py`)
- **Lifecycle:** UNKNOWN n / DECOMPILED n / UNDERSTOOD n / MATCHING n (from `make tier`)
- **Named:** N/633 (from `analysis/symbols.json`)
- **make compare:** OK / FAILED
- **Blockers:** none / <describe>

### Newly matched
- `FunctionName` → `src/matched/FunctionName.c`

### Next
- `python3 tools/decomp/script_first.py` then `agent_packet.py --next`
```

## Where things are documented

| Question | Look here |
|----------|-----------|
| **End-to-end process** | [README.md](README.md) § Decompilation |
| **Pipeline + lifecycle** | [docs/decomp-pipeline.md](docs/decomp-pipeline.md) |
| **Analysis DB / symbols** | [docs/decomp-pipeline.md](docs/decomp-pipeline.md), `analysis/` |
| **Standing mission / fork policy** | [docs/decomp-mission.md](docs/decomp-mission.md) |
| Pipeline / directories | [architecture.md](docs/architecture.md) |
| Master plan | [docs/decomp-roadmap.md](docs/decomp-roadmap.md) |
| **Which function to convert next** | [docs/decomp-semantic-plan.md](docs/decomp-semantic-plan.md) — run `tools/decomp/classify_semantic_targets.py` |
| Battle subsystem | [docs/battle.md](docs/battle.md) |
| Live progress | [docs/decomp-status.md](docs/decomp-status.md), [decomp-progress.svg](docs/decomp-progress.svg) |
| Parked unmatched C | [docs/decomp-wip.md](docs/decomp-wip.md), `src/decompiled/` |
| RAM addresses | [docs/ram-map.md](docs/ram-map.md) |
| Install / deps | [INSTALL.md](INSTALL.md) |

## Escalation (only then ask the user)

- baserom.gba missing or wrong SHA1
- agbcc build fails on their machine after `build_tools.sh`
- Persistent `make compare` failure after a claimed match (include log + diff)
