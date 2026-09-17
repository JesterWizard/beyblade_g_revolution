# Agent notes — hands-off matching decompilation

You are the **autonomous decompilation agent** for Beyblade G Revolution. The user is
hands-off: you run tools, integrate results, and report summaries. Do not ask the user
to run commands unless a hard blocker requires credentials they alone control
(e.g. baserom missing). **Cursor is the agent** — Mizuchi/Claude API is optional.

Read **[ARCHITECTURE.md](ARCHITECTURE.md)**, **[documentation/decomp-roadmap.md](documentation/decomp-roadmap.md)** (master plan), and **[documentation/decomp-agent.md](documentation/decomp-agent.md)** first.

## Mission

Produce **byte-matching** C (`make compare` → `beyblade_g_revolution.gba: OK`) by
automating: disassembly → triage → Cursor batch → integrate → verify → report.

## One-time bootstrap (run if not done)

```bash
bash scripts/setup.sh
```

This installs agbcc, gbafix, Luvdis, m2c, generates `asm/nonmatchings/`, and verifies
`make compare`. Mizuchi (npm) is optional.

**Primary batch runner:** `scripts/decomp/cursor_batch.sh` — no API key required.

## Every work session (repeat until done)

**Autonomous loop — no user approval between batches.** See
[documentation/decomp-roadmap.md](documentation/decomp-roadmap.md) for phases.

```bash
# 1. Status
python3 scripts/decomp/report_status.py
make compare

# 2. Match + integrate + commit (10 functions)
scripts/decomp/match_batch.sh 10

# 3. Every 3–5 batches: RAM map pass
python3 tools/scan_ram_literals.py --emit-asm
# Update asm/ram_map_*.s + documentation/ram-map.md

# 4. When match_function.py passes: add C to src/, plan asm removal
python3 scripts/decomp/match_function.py sub_XXXXXXXX src/module.c

# 5. Phase 5 gate check (shiftable ROM)
python3 scripts/decomp/check_shiftable.py

# 6. Report to user (template below)
python3 scripts/decomp/report_status.py
```

Optional: `scripts/decomp/cursor_batch.sh 10` for m2c seeds when tackling hard functions.

### Commit policy

**Commit after every successful `match_batch.sh`** — do not ask the user. Message:
`decomp: match batch (+N functions, M/633 total)`. Never commit if `make compare` fails.

If `asm/nonmatchings/` is empty:

```bash
python3 scripts/generate_asm.py --force
make compare
```

If agbcc is missing:

```bash
bash scripts/setup.sh
```

## What you may edit

| Area | Rule |
|------|------|
| `src/*.c` | Add matched decomp; comment header with ROM address |
| `asm/rom.s` | Shrink `.incbin` as matched code replaces baserom peels |
| `include/*.h` | Types discovered during decomp |
| `beyblade_g_revolution.toml` | Function renames (`[renames]`) |
| `documentation/decomp-status.md` | Progress log after each batch |
| `ld_script.ld` / `Makefile` | When adding new `src/` objects |

## What you must NOT do

- Hand-edit `asm/nonmatchings/*.s` (regenerate via `scripts/generate_asm.py`)
- Accept a match without objdiff 0-diff (Mizuchi enforces; still re-run `make compare`)
- Use C99 in matching paths or “fix” UB without `UBFIX`/`BUGFIX` guards
- Hardcode IWRAM/EWRAM addresses — use `asm/ram_map*.s`
- Enable `HACKS=1` during matching work (`make compare` must stay green)

## Matching vs hacking

| Goal | Command |
|------|---------|
| Matching decomp | `make compare` (`HACKS=0`, default) |
| Append / hacks | `make HACKS=1 modern` (breaks SHA1 compare) |

## Tooling map

| Tool | Path | Role |
|------|------|------|
| Cursor batch | `scripts/decomp/cursor_batch.sh` | Triage → m2c seed → agent refine → match |
| Mizuchi (opt.) | `tools/mizuchi/` | Full m2c → permuter → Claude pipeline (needs npm) |
| Config | `mizuchi.yaml` | Mizuchi config (`enable: false` by default) |
| agbcc | `tools/agbcc/bin/agbcc` | Matching compiler |
| m2ctx | `tools/m2ctx.py` | Context for decompiler |
| Luvdis | `tools/luvdis/` | Initial disassembly |
| Triage | `scripts/decomp/triage_functions.py` | Pick easy functions first |
| Match batch | `scripts/decomp/match_batch.sh` | **Primary:** verify asm → integrate → compare → commit |
| Verify asm | `scripts/decomp/verify_asm_bytes.py` | Baserom byte check before integrate |
| Integrate | `scripts/decomp/integrate_match.py` | Land match into ROM peel |
| ROM layout | `scripts/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |
| Shiftable check | `scripts/decomp/check_shiftable.py` | Phase 5 gate |
| Cursor batch | `scripts/decomp/cursor_batch.sh` | m2c seeds for hard functions |
| Mizuchi batch | `scripts/decomp/run_batch.sh` | Optional Mizuchi runner |
| Status | `scripts/decomp/report_status.py` | Progress summary |

## User report template

Post this after every batch (fill in values):

```
## Decomp batch report

- **Matched this batch:** N / attempted M
- **Total asm matched:** X% (from report_status.py)
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
| Pipeline / directories | [ARCHITECTURE.md](ARCHITECTURE.md) |
| Hands-off commands | [documentation/decomp-agent.md](documentation/decomp-agent.md) |
| Master plan | [documentation/decomp-roadmap.md](documentation/decomp-roadmap.md) |
| Live progress | [documentation/decomp-status.md](documentation/decomp-status.md) |
| RAM addresses | [documentation/ram-map.md](documentation/ram-map.md) |
| Install / deps | [INSTALL.md](INSTALL.md) |

## Escalation (only then ask the user)

- Mizuchi/Claude needed and `ANTHROPIC_API_KEY` not set (use Cursor batch instead)
- baserom.gba missing or wrong SHA1
- agbcc build fails on their machine after `scripts/setup.sh`
- Persistent `make compare` failure after a claimed match (include log + diff)
