# Hands-off decompilation agent

This document describes how the AI agent runs the toolchain without user intervention.

## Prerequisites (agent runs once)

```bash
bash scripts/setup.sh
```

This installs agbcc, pret tools, Luvdis, generates `asm/nonmatchings/`, builds Mizuchi, and verifies `make compare`.

## Per-session loop

1. **Status** — `python3 scripts/decomp/report_status.py`
2. **Triage** — `python3 scripts/decomp/triage_functions.py -n 20`
3. **Batch** — `scripts/decomp/cursor_batch.sh 10`
4. **Integrate** — `python3 scripts/decomp/integrate_match.py sub_XXXXXXXX [scratch.c]`
5. **Verify** — `make compare` (must print `beyblade_g_revolution.gba: OK`)
6. **Report** — update `documentation/decomp-status.md` with counts, matched names, blockers

## What to tell the user

After each batch, post a short summary:

- Functions attempted / matched / failed
- Current `pct_asm_matched` (from `report_status.py`)
- Whether `make compare` still passes
- Link to latest log in `mizuchi-output/`
- Any blockers (missing agbcc, empty asm dir, Mizuchi timeout)

## Rules

- Never edit `asm/nonmatchings/*.s` by hand — use `beyblade_g_revolution.toml` renames + `scripts/generate_asm.py --force`
- Never accept a match without objdiff 0-diff (Mizuchi enforces this)
- Always run full-ROM `make compare` after integrating matches
- C89 only for matching paths; no silent UB fixes
- RAM symbols go in `asm/ram_map*.s`, not hardcoded `0x03…` addresses

## Tool paths

| Tool | Location |
|------|----------|
| Cursor batch | `scripts/decomp/cursor_batch.sh` |
| Integrate | `scripts/decomp/integrate_match.py` |
| ROM layout | `scripts/decomp/gen_rom_layout.py` |
| Mizuchi (opt.) | `tools/mizuchi/` |
| Config | `mizuchi.yaml` |
| agbcc | `tools/agbcc/bin/agbcc` |
| m2ctx | `tools/m2ctx.py` |
| Luvdis | `tools/luvdis/` |
