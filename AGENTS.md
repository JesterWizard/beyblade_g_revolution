# Agent notes — hands-off matching decompilation

You are the **autonomous decompilation agent** for Beyblade G Revolution. The user is
hands-off: you run tools, integrate results, and report summaries. Do not ask the user
to run commands unless a hard blocker requires credentials they alone control
(e.g. baserom missing). **Cursor is the agent** — Mizuchi/Claude API is optional.

Read **[ARCHITECTURE.md](ARCHITECTURE.md)** and **[documentation/decomp-agent.md](documentation/decomp-agent.md)** first.

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

```bash
# 1. Status
python3 scripts/decomp/report_status.py

# 2. Ensure map + asm exist
make compare
test -d asm/nonmatchings && test "$(ls -A asm/nonmatchings)"

# 3. Batch decompile (default 10 easiest functions)
scripts/decomp/cursor_batch.sh 10
# Then fix/refine m2c seeds in mizuchi-output/ and verify:
#   python3 scripts/decomp/match_function.py sub_XXXXXXXX mizuchi-output/sub_XXXXXXXX.c

# 4. Full-ROM verify
make compare

# 5. Report to user (see template below)
python3 scripts/decomp/report_status.py
```

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
| Batch | `scripts/decomp/cursor_batch.sh` | Cursor-native batch (primary) |
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
| Live progress | [documentation/decomp-status.md](documentation/decomp-status.md) |
| RAM addresses | [documentation/ram-map.md](documentation/ram-map.md) |
| Install / deps | [INSTALL.md](INSTALL.md) |

## Escalation (only then ask the user)

- Mizuchi/Claude needed and `ANTHROPIC_API_KEY` not set (use Cursor batch instead)
- baserom.gba missing or wrong SHA1
- agbcc build fails on their machine after `scripts/setup.sh`
- Persistent `make compare` failure after a claimed match (include log + diff)
