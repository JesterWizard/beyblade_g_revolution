---
name: gba-decomp-matching
description: >-
  Fixes agbcc byte-matching failures for GBA decomp (match_function.py DIFF, near-misses,
  literal pools, decomp-permuter). Use when semantic C compiles but bytes differ,
  same-size DIFF, pool order issues, or leaf-branch push lr blockers.
---

# GBA byte-matching techniques

Oracle: `python3 tools/decomp/match_function.py FN path/to.c` → **MATCH** or compact **DIFF** (first mismatch + 16 bytes). Pass `--full` for a whole-function hex dump.

## Diagnose from DIFF output

| Symptom | Likely cause | Try first |
|---------|--------------|-----------|
| Compiled **larger** (+4–16B), retail has no `push` | C `if` on leaf function | `-fprologue-bugfix`; else park |
| **Same size**, wrong bytes at pool | IWRAM address CSE / wrong `ldr` | `tmp[]` local; statement order |
| **Same size**, wrong insn order | agbcc reordered setup | Match evaluation order in C; permuter |
| **muls** mismatch | Compiler multiply vs `muls` | Permuter; or readable Thumb |
| Extra register in prologue | Extra live locals | Fewer locals; permuter; else park |

## Banned (not a match)

Do **not** use GCC asm labels or compiler barriers in semantic C:

- `register T x asm("rN");`
- `asm("" : "+r"(x));` / `asm volatile`

`match_function.py` rejects these. If retail bytes need them, park (`park_wip.py`) and leave Thumb in `src/matched/`.

Allowed `asm()`: BIOS `asm("swi N");`, and `__attribute__((naked))` Thumb wrappers.

## Proven patterns (this repo)

### 1. IWRAM pool (`tmp[]`)

```c
struct Unk0380 *p;
u32 tmp[1];

tmp[0] = gUnk_03000380;
p = (struct Unk0380 *)tmp[0];
```

Use when retail has `ldr rN, =0x03……` before use. `register` without an asm label is ordinary C (a hint only).

`r0 = ch + table` → `adds r0, r1, r0`. Swapping operands is a 1-byte DIFF. Win: `sub_08073988`.

### 2. Register flow for and/cmp

Write the operations in retail order (`mask = 8; mask &= flags`). Mirror evaluation order, not hardware register names.

Mask-first tests (`movs r0,#N; ldrb r1,[r5]; ands r0,r1`) need `u32` locals. `u8` becomes `ands r1, r0` / `cmp r1, #0`. Clone of `sub_080425B8`: `addr = &byte; mask = 2; value = *addr; mask &= value`.

### 3. Parameter registers (don’t re-assign early)

Thumb args: `r0`, `r1`, `r2`, `r3`. Keep using the C parameter names so `assign_parms` matches. Do **not** `obj = a` when retail starts `adds r5, r0; …`.

`u8` args emit `lsls/lsrs` before other copies. If retail copies `r1` first, take `u32` and extend after.

If retail `bl fn; lsls r0, r0, #2` with no caller zero-extend, change the callee from `u8` to `u32` and re-check that callee still MATCH.

### 4. Struct members (required)

```c
a->unk302 = *(u16 *)gBtlInputMask;   // OK with ram_map.h constants
```

Not: `*(u16 *)((u8 *)a + 0x302) = …`. Add fields to `include/unknown-types.h` first.

### 5. Control flow

`if (a >= b) goto label` keeps `cmp; bge`. Nested if/else often inverts to `blt` and moves the pool. Put shared `return N` labels in retail fallthrough order. Win: `sub_08042390`.

Loop that exits with `0` already in `r0`: `while ((r0 = p->unk00) != 0) { call(p->unk00, …); } return (s32)r0`. Plain `return 0` adds `movs r0,#0`.

### 6. Leaf `bx lr` + `-fprologue-bugfix`

Default agbcc frames a branching leaf (`push {lr}` / `pop {r1}; bx r1`). `/* match-flags: -fprologue-bugfix */` in the C file (not global `CFLAGS`) drops that frame for many `bx lr` leaves.

Wins that stay MATCH without asm labels: null-check stores (`sub_0802D8C4`, `sub_08061BDC`, `sub_08062684`), clamp `u32` args (`sub_080615EC`), `sub_08033958` / `sub_0806AC68`. Table walks and `+r` barriers that needed GCC asm labels were parked.

`match_function.py` reads the comment from the original `.c` (gcc `-E` strips it). If it still extra-pushes after the flag + retail register order, park.

## Permuter workflow

```bash
python3 tools/decomp/permuter/import_function.py sub_XXXXXXXX
tools/decomp/permuter/permute.sh run nonmatchings/sub_XXXXXXXX -j 8 --stop-on-zero
# Score 0 → still verify:
python3 tools/decomp/match_function.py sub_XXXXXXXX <permuter-output.c>
```

Run overnight on near-misses; don’t babysit interactive retries.

## When to stop (document, don’t spin)

Park the C, then block auto-queue. See [docs/decomp-wip.md](docs/decomp-wip.md):

```bash
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c \
    --status "leaf branch adds push {lr}" --next "permuter or stay Thumb" --score "N/M"
```

```toml
[[wip]]
name = "sub_080XXXXXXXX"
seed = "src/wip/sub_080XXXXXXXX.c"
notes = "src/wip/sub_080XXXXXXXX.md"
status = "…"
next = "…"

[[block]]
name = "sub_080XXXXXXXX"
reason = "leaf branch adds push {lr} / permuter score N; seed in src/wip/"
```

Leave **readable Thumb** in `src/matched/` (`--kind asm`). Keep the draft in `src/wip/`. Log in `docs/decomp-status.md` with a path to the notes.

## Known blocker families (this project)

- **Leaf + branch (still hard after `-fprologue-bugfix`):** `sub_08034894`, `sub_08062728` (`stm` fill), `sub_080699C8`. Try the flag first.
- **Table lookup + pool order:** `sub_0803DD60` family
- **Dual IWRAM store CSE:** `sub_080473E4`, `sub_080473F8` (nearby literals fold unless the first pointer stays live)

## m2c seeds

```bash
python3 tools/decomp/m2c_asm.py sub_XXXXXXXX
```

Fix types → `gMainWorkPtr` / `gBattleWork` → evaluation order → `match_function.py`. m2c `--valid-syntax` helps permuter feeds (see ecosystem skill). Do not add `register … asm("rN")`.

## Reference

Project detail: [docs/decomp-patterns.md](docs/decomp-patterns.md)
