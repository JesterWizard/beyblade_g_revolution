# Bootstrap checklist — new GBA decomp from this repo

## 1. ROM + toolchain

- Place verified `baserom.gba` (correct SHA1 in Makefile/docs)
- `bash build_tools.sh` — agbcc, Luvdis, m2c context, `asm/nonmatchings/`
- `make compare` → OK on asm-only baseline

## 2. Project config

- Rename TOML / ld script / game title strings
- `tools/decomp/gen_rom_layout.py` — regenerate layout after first matches
- `mizuchi.yaml` — optional; `cursor_batch.sh` works without API key

## 3. Agent setup

- Copy `.cursor/skills/gba-decomp-*` to new repo (or keep as submodule pattern)
- Copy `.cursor/rules/decomp-autonomous-mission.mdc` and edit game name
- `AGENTS.md` + `docs/decomp-mission.md` — adjust function totals, subsystem names

## 4. First milestones (same phases)

| Phase | Goal |
|-------|------|
| 1–2 | All functions in ROM peel as asm |
| 3 | `src/matched/*.c` for every fn (readable Thumb OK) |
| 3b | Semantic C % ↑ |
| 4 | `[renames]` readable names |
| 5 | Shiftable ROM (`check_shiftable.py`) |

## 5. Subsystem discovery

- Write one `docs/<subsystem>.md` per cluster (like `docs/battle.md`)
- Add a `*_scan.py` if a subsystem has 50+ functions (mirror `battle_scan.py`)

## 6. Self-improvement from day one

- Create empty `docs/decomp-queue.toml` pins/blocks early
- Log every near-miss in `decomp-status.md` — compound interest on patterns
- Grow `c_patterns.py` before running wide auto-convert
