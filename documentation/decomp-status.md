# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

| Metric | Value |
|--------|-------|
| Non-matching asm | 633 |
| Matching asm (linked) | 31 |
| `src/*.c` files | 1 |
| `pct_asm_matched` | 4.8% |

## Batch log

### 2026-09-17 — batch 3 (20 functions)

Integrated 20 asm-verified functions including literal-pool loaders (`sub_0802B90C`, `sub_080429C0`, …), IWRAM accessors, and field setters. `make compare`: **OK**.

### 2026-09-17 — linker integration + batch 2

11 functions linked via ROM peel tooling.

### 2026-09-17 — bootstrap + batch 1

First 4 functions + `src/stubs.c`.

## Tooling

| Script | Purpose |
|--------|---------|
| `scripts/decomp/cursor_batch.sh` | Triage + m2c seeds |
| `scripts/decomp/integrate_match.py` | Link match into ROM peel |
| `scripts/decomp/match_function.py` | Verify scratch C vs asm (now runs CPP) |
| `scripts/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |

## Next

- Replace asm matchings with byte-matched C (`match_function.py` + `src/`)
- Add IWRAM symbols to `asm/ram_map*.s` instead of hardcoded `0x03…` in C
- Continue integrating score-5 triage candidates

## Blockers

- None (`make compare` green with 31 peeled functions)

### 2026-09-17 — match_batch (+10, 41/633 linked)
- Functions: `sub_080473E4`, `sub_08061BDC`, `sub_08062634`, `sub_08062A1C`, `sub_0806644C`, `sub_08068584`, `sub_08072F94`, `sub_0802B8BC`, `sub_0803EDC8`, `sub_080400C0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 51/633 linked)
- Functions: `sub_080628E4`, `sub_08067890`, `sub_080314FC`, `sub_0803EDF0`, `sub_08068574`, `sub_0806BB38`, `sub_0802D598`, `sub_0802D8C4`, `sub_08062728`, `sub_0806639C`
- make compare: OK
