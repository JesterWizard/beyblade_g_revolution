# Decompilation roadmap (autonomous)

This is the **master plan** for hands-off progress. The agent follows this
without waiting for user approval between batches. Escalate only on hard
blockers (see [AGENTS.md](../AGENTS.md)).

## Current baseline

| Metric | Value (2026-09-17) |
|--------|-------------------|
| Luvdis functions | 633 (`asm/nonmatchings/`) |
| Linked in ROM | 31 (`asm/matchings/`, `build/matched.json`) |
| C in `src/` | 4 stubs in `stubs.c` |
| `make compare` | Must stay **OK** every batch |
| ROM layout | Fixed-VMA peel (`asm/rom_layout.ld`) |

---

## Phase 1 — Match ASM (primary loop)

**Goal:** Every `sub_*` from Luvdis is byte-verified and linked via the ROM peel.

### Per batch (repeat until `matching_asm == 633`)

```bash
scripts/decomp/match_batch.sh 10    # integrate + compare + commit
```

What the batch does:

1. Triage 10 easiest **unmatched** functions (`triage_functions.py` skips `asm/matchings/`).
2. For each candidate, assemble `asm/nonmatchings/*.s` and compare `.text` bytes to `baserom.gba`.
3. On match → `integrate_match.py` → regenerate `asm/rom_layout.ld` + gap incbins.
4. `make compare` (full ROM SHA1).
5. **Git commit** on success (see [Commit policy](#commit-policy)).
6. Append one line to `documentation/decomp-status.md`.

### Matching rules

| Do | Don't |
|----|-------|
| Integrate when asm objdump bytes == baserom | Hand-edit `asm/nonmatchings/*.s` |
| Keep `make compare` green | Enable `HACKS=1` during matching |
| Prefer asm integration for literal-pool loaders | Force C that doesn't `match_function.py` |

### Exit criteria (Phase 1 done)

- `python3 scripts/decomp/report_status.py` → `matching_asm: 633`
- `build/matched.json` lists all functions
- `make compare` OK

**Estimate:** ~60 batches × 10 functions (31 done → ~60 remaining).

---

## Phase 2 — RAM map (parallel, every 3–5 batches)

**Goal:** Document **used vs free** IWRAM/EWRAM; stop hardcoding `0x03…` in new C.

### Each RAM pass

```bash
python3 tools/scan_ram_literals.py              # human-readable clusters
python3 tools/scan_ram_literals.py --emit-asm   # refresh pool .inc files
make compare
```

### Agent tasks

1. **Rescan** literal pools from `baserom.gba` (not sigma_star_saga addresses).
2. **Promote** high-confidence hits from `gUnk_*` in `ram_map_*_pool.inc` to named
   `SET_DATA` in `asm/ram_map_iwram.s` / `asm/ram_map_ewram.s` when role is clear
   (e.g. `0x03000264` seen in `sub_0802B90C` → name after tracing).
3. **Update** `include/ram_map.h` and `documentation/ram-map.md` with a used/free table
   (mirror sigma_star_saga format: hardware span, vanilla high-water, safe pool, stack).
4. **Tighten** `FreeRamSpaceTop` / `FreeEwramSpaceTop` only after scan + margin;
   keep `.error` guards in `ram_map_iwram.s`.

### RAM map deliverable

`documentation/ram-map.md` must contain:

- Occupancy table (USED / SAFE / leave-alone)
- Named symbols table (growing as functions are understood)
- Regeneration commands

Phase 2 is **never finished** but should be **non-blocking** for Phase 1 batches.

---

## Phase 3 — ASM → C conversion

**Goal:** Replace `asm/matchings/*.s` with byte-matched C in `src/` where possible.

### When to convert

| Convert to C | Leave as asm |
|--------------|--------------|
| `match_function.py` prints `MATCH` | Literal-pool PC-relative loads agbcc won't reproduce |
| Simple loads/stores once RAM symbols exist | `swi #N` stubs (until syscall wrappers exist) |
| Struct field access with known types | Hand-written asm (`asm/*.s` trampolines, LynJump veneers) |
| Empty returns, trivial getters | `mov pc, lr` and other agbcc mismatches |

### Per-function workflow

```bash
# 1. Write/refine C (use global.h, ram_map.h — no raw 0x03 unless unavoidable)
# 2. Verify
python3 scripts/decomp/match_function.py sub_XXXXXXXX src/module.c
# 3. Integrate C into build (future: link src/*.o in peel; today asm stays until C linked)
# 4. Remove asm/matchings/sub_XXXXXXXX.s only after C is in ROM peel
make compare
```

### C rules

- C89 / agbcc only on matching paths
- Comment header: `// @ 0x080XXXXXX`
- One subsystem per `src/<module>.c` (e.g. `iwram.c`, `swi.c`, `stubs.c`)
- No `static` locals in append code that land in IWRAM `.bss`

### Exit criteria (Phase 3 ongoing)

- Track `% matched asm also has C` in `decomp-status.md`
- Target: 100% of **convertible** stubs in C; asm-only list documented

---

## Phase 4 — Naming functions

**Goal:** Replace `sub_080XXXXXX` with readable names without breaking matching.

### Mechanism

`beyblade_g_revolution.toml`:

```toml
[renames]
sub_0802B90C = "GetIwramWord_264"
sub_080705CC = "SetField19One"
```

Then:

```bash
python3 scripts/generate_asm.py --force   # regen labels (do not hand-edit nonmatchings)
# Update C identifiers + integrator manifest to match
make compare
```

### Naming rules

1. Name only after the function's **role** is understood (not just "it's a stub").
2. Prefix by subsystem: `Btl`, `Menu`, `Save`, `Gax`, etc. when known.
3. One rename per commit batch max when it touches many call sites (avoid churn).
4. Keep ROM symbol = C name = asm label after rename regen.

### Exit criteria

- `[renames]` covers all matched functions
- `src/` and headers use descriptive names; `sub_*` only in generated asm until regen

---

## Phase 5 — Shiftable ROM

**Goal:** Retail image is built from **relocatable** linked objects, not hundreds of
fixed-VMA `.rom_sub_*` sections — so future code/data can be inserted without
manual address surgery.

### Why we're not shiftable yet

Current peel (`gen_rom_layout.py`) assigns each matched function a **fixed VMA**
(`0x08033A94`, etc.). That is correct for matching but not shiftable.

### Migration gates (start Phase 5 when ANY is true)

- [ ] ≥ **80%** functions matched (≥ 506 / 633), **or**
- [ ] Largest unmatched incbin gap **< 4 KiB**, **or**
- [ ] User requests hack/append feature that needs insertable ROM

### Migration steps

1. **Contiguous grouping** — merge adjacent matched regions into single `src/*.o` or asm objects.
2. **Sequential linker script** — sigma_star_saga style:
   `rom.s` (head incbin) → `src/foo.o(.text)` → `rom_after_a.s` → …
3. **Remove** per-function `0x08……` assignments from `rom_layout.ld`.
4. **Audit** hardcoded ROM pointers in C/asm/data → replace with symbols / linker labels.
5. **Add** `scripts/decomp/check_shiftable.py`:
   - No `ORG`/` . = 0x08` in generated layout (except head/tail incbin bounds)
   - `make compare` OK
   - Optional: rebuild at `ROM_BASE + 0x1000` test (future)

### Handwritten asm

These stay **outside** the shiftable C pool forever (unless rewritten deliberately):

- `asm/ram_map*.s`
- Future trampolines / LynJump stubs in `asm/*.s`
- `src_custom/` append code (`HACKS=1`)

### Exit criteria (Phase 5 done)

- `check_shiftable.py` passes
- `make compare` OK
- New matched code added by editing `src/` + shrinking one incbin, not adding ld VMA lines
- Documentation updated in this file + `ARCHITECTURE.md`

---

## Commit policy

**The agent commits after every successful `match_batch.sh` without asking.**

### Pre-commit checklist

- [ ] `make compare` → `beyblade_g_revolution.gba: OK`
- [ ] Only intended files staged (no `baserom.gba`, `*.gba`, `build/`)

### Commit message format

```
decomp: match batch N (+10 functions, M/633 total)

Integrate sub_080…, sub_080…, …
make compare: OK
```

### Typical staged paths

- `asm/matchings/*.s`
- `asm/rom.s`, `asm/rom_tail.s`, `asm/rom_gap_*.s`
- `asm/rom_layout.ld`
- `build/matched.json`
- `src/*.c`, `include/*.h` (when C lands)
- `beyblade_g_revolution.toml` (renames)
- `documentation/decomp-status.md`, `documentation/ram-map.md`

### When NOT to commit

- `make compare` failed (fix or revert integration)
- Batch partially applied (< 10) due to verify failures — commit only if user asked; default: fix or skip failed fns and still commit if compare OK with fewer than 10

---

## Agent session checklist (no user approval)

```
1. python3 scripts/decomp/report_status.py
2. scripts/decomp/match_batch.sh 10
3. [every 3rd batch] python3 tools/scan_ram_literals.py --emit-asm && update ram-map.md
4. [when MATCH] convert 1–3 functions to C + match_function.py
5. [when role known] add rename to beyblade_g_revolution.toml
6. Report summary (template in AGENTS.md)
7. If Phase 5 gates met → begin shiftable migration branch
```

---

## Timeline (rough)

| Phase | Trigger | Effort |
|-------|---------|--------|
| 1 ASM match | Now | ~60 batches |
| 2 RAM map | Every 3–5 batches | Ongoing |
| 3 C conversion | After RAM names for literals | Ongoing from batch ~10 |
| 4 Naming | As roles understood | Ongoing |
| 5 Shiftable | ≥80% matched | 1–2 focused sessions |

---

## References

- [decomp-agent.md](decomp-agent.md) — command cheat sheet
- [decomp-status.md](decomp-status.md) — live log
- [ram-map.md](ram-map.md) — IWRAM/EWRAM occupancy
- [ARCHITECTURE.md](../ARCHITECTURE.md) — matching vs hacking
