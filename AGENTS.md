# Agent notes — hands-off matching decompilation

You are the **autonomous decompilation agent** for Beyblade G Revolution. The user is
hands-off: you run tools, integrate results, and report summaries. Do not ask the user
to run commands unless a hard blocker requires credentials they alone control
(e.g. baserom missing). **Cursor is the agent** — Mizuchi/Claude API is optional.

Read **[docs/decomp-mission.md](docs/decomp-mission.md)** (standing goal + fork policy),
**[architecture.md](docs/architecture.md)**, **[docs/decomp-roadmap.md](docs/decomp-roadmap.md)** (master plan), and **[docs/decomp-agent.md](docs/decomp-agent.md)** first.

## Mission

Produce **byte-matching** C (`make compare` → `beyblade_g_revolution.gba: OK`) by
automating: disassembly → triage → Cursor batch → integrate → verify → report.

## One-time bootstrap (run if not done)

```bash
bash build_tools.sh
```

This installs agbcc, gbafix, Luvdis, m2c, generates `asm/nonmatchings/`, and verifies
`make compare`. Mizuchi (npm) is optional.

**Primary batch runner:** `tools/decomp/cursor_batch.sh` — no API key required.

## Every work session (repeat until done)

**Autonomous loop — no user approval between batches.** See
[docs/decomp-roadmap.md](docs/decomp-roadmap.md) for phases.

```bash
# 1. Status
python3 tools/decomp/report_status.py
make compare

# 2. Match + integrate + commit (10 functions)
tools/decomp/match_batch.sh 10

# 3. Every 3–5 batches: RAM map pass
tools/decomp/ram_map_pass.sh
# Promote gUnk_* → named SET_DATA in asm/ram_map_*.s as roles become clear

# 4. Phase 3: trivial C batch, or hand-convert + integrate
tools/decomp/c_convert_batch.sh 30
python3 tools/decomp/match_function.py sub_XXXXXXXX src/matched/sub_XXXXXXXX.c
python3 tools/decomp/integrate_c.py sub_XXXXXXXX src/matched/sub_XXXXXXXX.c

# 5. Phase 5 gate check (shiftable ROM)
python3 tools/decomp/check_shiftable.py

# 6. Report to user (template below)
python3 tools/decomp/report_status.py
```

Optional: `tools/decomp/cursor_batch.sh 10` for m2c seeds when tackling hard functions.

### Commit policy

**Commit after every successful `match_batch.sh`** — do not ask the user. Message:
`decomp: match batch (+N functions, M/633 total)`. Never commit if `make compare` fails.

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
| `asm/rom.s` | Shrink `.incbin` as matched code replaces baserom peels |
| `include/*.h` | Types discovered during decomp |
| `beyblade_g_revolution.toml` | Function renames (`[renames]`) |
| `docs/decomp-status.md` | Progress log after each batch |
| `docs/decomp-progress.json` | Live C-vs-original counters (functions + bytes) |
| `docs/decomp-progress.svg` | README percentage bar |
| `ld_script.ld` / `Makefile` | When adding new `src/` objects |

## What you must NOT do

- Hand-edit `asm/nonmatchings/*.s` (regenerate via `tools/decomp/generate_asm.py`)
- Accept a match without objdiff 0-diff (Mizuchi enforces; still re-run `make compare`)
- Use C99 in matching paths or “fix” UB without `UBFIX`/`BUGFIX` guards
- Hardcode IWRAM/EWRAM addresses — use `asm/ram_map*.s`
- Use offset-casts (`*(u16 *)((u8 *)p + off)`) or `asm volatile` in new semantic C — struct members in `unknown-types.h`
- Enable `HACKS=1` during matching work (`make compare` must stay green)

## Matching vs hacking

| Goal | Command |
|------|---------|
| Matching decomp | `make compare` (`HACKS=0`, default) |
| Append / hacks | `make HACKS=1 modern` (breaks SHA1 compare) |

## Tooling map

| Tool | Path | Role |
|------|------|------|
| Cursor batch | `tools/decomp/cursor_batch.sh` | Triage → m2c seed → agent refine → match |
| decomp-permuter | `tools/decomp/permuter/` | agbcc literal-pool / instruction-order search |
| Mizuchi (opt.) | `tools/mizuchi/` | Full m2c → permuter → Claude pipeline (needs npm) |
| Config | `mizuchi.yaml` | Mizuchi config (`enable: false` by default) |
| agbcc | `tools/agbcc/bin/agbcc` | Matching compiler |
| m2ctx | `tools/m2ctx.py` | Context for decompiler |
| Luvdis | `tools/luvdis/` | Initial disassembly |
| Triage | `tools/decomp/triage_functions.py` | Pick easy functions first |
| Match batch | `tools/decomp/match_batch.sh` | **Primary:** verify asm → integrate → compare → commit |
| Verify asm | `tools/decomp/verify_asm_bytes.py` | Baserom byte check before integrate |
| Integrate | `tools/decomp/integrate_match.py` | Land match into ROM peel |
| ROM layout | `tools/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |
| Shiftable check | `tools/decomp/check_shiftable.py` | Phase 5 gate |
| Cursor batch | `tools/decomp/cursor_batch.sh` | m2c seeds for hard functions |
| decomp-permuter | `tools/decomp/permuter/` | agbcc pool/ordering search |
| Mizuchi batch | `tools/decomp/run_batch.sh` | Optional Mizuchi runner |
| Status | `tools/decomp/report_status.py` | Progress summary + refresh counter |
| Progress bar | `tools/decomp/progress.py` | Semantic C % vs original (JSON + SVG) |

## User report template

Post this after every batch (fill in values):

```
## Decomp batch report

- **Matched this batch:** N / attempted M
- **Decompiled C:** X% functions / Y% bytes (from `progress.py`)
- **make compare:** OK / FAILED
- **Log:** mizuchi-output/batch-*.log
- **Blockers:** none / <describe>

### Newly matched
- `FunctionName` → `src/module.c`

### Next
- Run another batch of 10, or investigate failures in log
```

## Where things are documented

| Question | Look here |
|----------|-----------|
| **Standing mission / fork policy** | [docs/decomp-mission.md](docs/decomp-mission.md) |
| Pipeline / directories | [architecture.md](docs/architecture.md) |
| Hands-off commands | [docs/decomp-agent.md](docs/decomp-agent.md) |
| Master plan | [docs/decomp-roadmap.md](docs/decomp-roadmap.md) |
| Battle subsystem | [docs/battle.md](docs/battle.md) |
| Live progress | [docs/decomp-status.md](docs/decomp-status.md), [decomp-progress.svg](docs/decomp-progress.svg) |
| RAM addresses | [docs/ram-map.md](docs/ram-map.md) |
| Install / deps | [INSTALL.md](INSTALL.md) |

## Escalation (only then ask the user)

- Mizuchi/Claude needed and `ANTHROPIC_API_KEY` not set (use Cursor batch instead)
- baserom.gba missing or wrong SHA1
- agbcc build fails on their machine after `build_tools.sh`
- Persistent `make compare` failure after a claimed match (include log + diff)
