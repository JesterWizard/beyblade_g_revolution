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

- `register` (storage class) and `register T x asm("rN");`
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

Use when retail has `ldr rN, =0x03……` before use. Do not use `register`.

`r0 = ch + table` → `adds r0, r1, r0`. Swapping operands is a 1-byte DIFF. Win: `sub_08073988`.

### 2. Register flow for and/cmp

Write the operations in retail order (`mask = 8; mask &= flags`). Mirror evaluation order, not hardware register names.

Mask-first tests (`movs r0,#N; ldrb r1,[r5]; ands r0,r1`) need `u32` locals. `u8` becomes `ands r1, r0` / `cmp r1, #0`. Clone of `sub_080425B8`: `addr = &byte; mask = 2; value = *addr; mask &= value`.

### 3. Parameter registers (don’t re-assign early)

Thumb args: `r0`, `r1`, `r2`, `r3`. Keep using the C parameter names so `assign_parms` matches. Do **not** `obj = a` when retail starts `adds r5, r0; …`.

`u8` args emit `lsls/lsrs` before other copies. If retail copies `r1` first, take `u32` and extend after.

If retail `bl fn; lsls r0, r0, #2` with no caller zero-extend, change the callee from `u8` to `u32` and re-check that callee still MATCH.

### 3b. Pointer parameter types (prototype = codegen)

`void *` in the prototype is not interchangeable with `const u8 *` for matching. agbcc's
`assign_parms` emits different prologue copies depending on the declared type, and adding
`text = text_arg; base = base_arg;` locals on top makes it worse.

| Prototype + body | Typical score (`TextMeasureWidth`) |
|------------------|-------------------------------------|
| `void *` + locals, `old_agbcc` | 89/96 — wrong save order from byte 2 |
| `const u8 *` direct use, `old_agbcc` | **96/96 MATCH** |

When retail opens `adds r4,r0; adds r7,r1; …` on pointer args, try **`const u8 *` /
`u8 *` in both the definition and `include/unknown-functions.h`** before goto chains or
`index = (r0 = pool)` side-effect tricks. `match_function.py` preprocesses through
`global.h`, so a prototype mismatch silently rescores the same body.

Workflow when the first mismatch is in the prologue (+0x2..+0x8):

1. Refine `void *` → `const u8 *` (or `u32` when retail skips `lsls/lsrs`).
2. Drop param-copy locals; use parameter names in the loop body.
3. Score with **both** `agbcc` and `old_agbcc` (`test_variants.py` defaults to both).
4. Update `unknown-functions.h` when the refined prototype is the fix — callers pass
   pointers and remain ABI-compatible.

### 4. Struct members (required)

```c
a->unk302 = *(u16 *)gBtlInputMask;   // OK with ram_map.h constants
```

Not: `*(u16 *)((u8 *)a + 0x302) = …`. Add fields to `include/unknown-types.h` first.

### 5. Control flow

`if (a >= b) goto label` keeps `cmp; bge`. Nested if/else often inverts to `blt` and moves the pool. Put shared `return N` labels in retail fallthrough order. Win: `sub_08042390`.

Loop that exits with `0` already in `r0`: `while ((r0 = p->unk00) != 0) { call(p->unk00, …); } return (s32)r0`. Plain `return 0` adds `movs r0,#0`.

A readable **`switch` on the scanned byte** can match where a goto chain copied from
disasm stalls at a same-size DIFF (`TextMeasureWidth`: goto seed 94/96 for months;
`switch` + `const u8 *` + `old_agbcc` → 96/96). Do not keep rewriting goto mimicry —
try switch (or `if` ladder) with the typed-param / dual-compiler checklist first.

Same-size `subs`/`adds` dest off by one register (`081a` vs `091a`): assign that
expression to the **return local** (`result`) so agbcc keeps it in r0. Win:
`sub_0806E7BC` (149/152 → MATCH). A newly declared temp for the same sub often
pushes extra regs and collapses the score.

### 6. Leaf `bx lr` + `-fprologue-bugfix`

Default agbcc frames a branching leaf (`push {lr}` / `pop {r1}; bx r1`). `/* match-flags: -fprologue-bugfix */` in the C file (not global `CFLAGS`) drops that frame for many `bx lr` leaves.

Wins that stay MATCH without asm labels: null-check stores (`sub_0802D8C4`, `sub_08061BDC`, `sub_08062684`), clamp `u32` args (`sub_080615EC`), `sub_08033958` / `sub_0806AC68`. Table walks and `+r` barriers that needed GCC asm labels were parked.

`match_function.py` reads the comment from the original `.c` (gcc `-E` strips it). If it still extra-pushes after the flag + retail register order, park.

### 6b. Per-function compiler: `/* match-compiler: old_agbcc */`

`pret/agbcc`'s `install.sh` installs **two** compilers — `tools/agbcc/bin/agbcc` and `tools/agbcc/bin/old_agbcc` — and they do not generate identical code. The older one keeps some loads un-coalesced (e.g. `ldrb r0,[r0]; lsls r1,r0`) where the newer one folds the load into its consumer, and prefers different registers for nested assignments. When a seed is stuck on a *destination* register of a load/shift, score it with both compilers before parking:

```c
// @ 0x08061308
/* match-compiler: old_agbcc */
```

`match_function.py` parses it (`MATCH_COMPILER_RE`), `import_function.py` writes a `compiler` sidecar (the permuter preprocesses `base.c`, so `compile.sh` cannot read the comment itself) and `permuter/compile.sh` swaps `CC`. Wins: `sub_08061308` (48/48 vs 46/48), `sub_08062A74` (76/76 vs 74/76), `sub_08073988` / `TextMeasureWidth` (96/96 vs 94/96 on goto+side-effect seeds). `build/dual_compiler_sweep.py` scores the whole `src/decompiled` backlog with both.

For ROM-table lookups, prefer a **symbol subscript** (`base[gData_080BB748[ch]]`) over
manual `ch + 0x080BB748` / `index = (r0 = pool)` chains — with `old_agbcc` and typed
pointer params the compiler emits retail's `ldr r0,=pool; adds r0,ch` without asm-shaped C.

### 7. Schedule a pool load between two ops on one local

Retail `lsls r0,#24; ldr r2,=0x05000200; lsrs r0,#23`. agbcc delays the `ldr` until the add. Win: take the address of the shifted local so the second shift reloads it:

```c
shifted = idx << 24;
base = 0x05000200;
sh = 23;
p = &shifted;
shifted = *p >> sh;
shifted += base;
```

`sub_08062CC8`. Permuter invented this in 9 iterations; `match_function.py` still has to confirm against retail (permuter `target.o` can warn about pool alignment).

### 7b. A table *base* local pins the literal before the index shift

Retail:
```
str r0,[r4]; ldr r5,[pc,#36]; lsls r0,r0,#3; adds r0,r0,r5; ldr r0,[r0]
```
agbcc from `tbl[i].unk00`:
```
str r0,[r4]; lsls r0,r0,#3;  ldr r5,[pc,#32]; adds r0,r0,r5; ldr r0,[r0]
```
Only the two middle instructions swap (4 bytes, `same_size`). Subscripting, `(tbl + i)->unk00`, a *slot address* local (`slot = tbl + i;`) and a `u8 *` byte-offset form all stay at 52/56; `slot`/`tbl` locals assigned after the decrement also get hoisted. What works is a local for the **base only**, leaving the index inside the subscript so the scaled index stays its own operand:

```c
base = (struct Unk0770 *)gData_03000770;
if (base[i].unk00 != 0)
{
    BtlObjFree(base[i].unk00);
    base[gData_03000794[0]].unk00 = 0;
}
```

`base` is live across the `BtlObjFree` call and reused by the second subscript, which is why one `ldr r5` serves both — and the load is now needed before the shift, so it schedules first. Win: `sub_08061C48` (52/56 -> 56/56), found by `test_variants.py` in one 7-variant sweep after the permuter's randomization stalled at 52/56. Reach for this before the permuter when a symbol base feeds an indexed field twice.

### 8. Dummy reload to pin `ands` operands

Mask-first `movs r0,#N; ldrb r1,[r5]; ands r0,r1` can compile as `movs r1,#N; ldrb r0; ands r1,r0`. An extra `value = *addr` into a different u32 before a later mask test can fix the earlier tests too (`sub_0803531C`).

## Permuter workflow

```bash
# Import → score the seed → search → verify → integrate, all in one command.
python3 tools/decomp/permuter/auto.py sub_XXXXXXXX --seconds 240 --jobs 8
```

`auto.py` prints the base score first. If the seed already scores 0 it skips the search and integrates immediately (that is the `-fprologue-bugfix` case). It exits 0 only after `match_function.py` confirms **MATCH**.

Manual equivalent when you want to look at candidates:

```bash
python3 tools/decomp/permuter/import_function.py sub_XXXXXXXX
tools/decomp/permuter/permute.sh run nonmatchings/sub_XXXXXXXX -j 8 --stop-on-zero
# Score 0 → still verify:
python3 tools/decomp/match_function.py sub_XXXXXXXX <permuter-output.c>
```

`import_function.py` writes `matchflags` and `compiler` sidecars from the seed's `/* match-flags: … */` and `/* match-compiler: … */` comments; `permuter/compile.sh` passes them to agbcc. Without it the permuter cannot reach score 0 for the 21 functions needing `-fprologue-bugfix` (agbcc emits a `push {lr}` retail does not have). If `auto.py` reports a base score that does not match `match_function.py`'s DIFF, the flags or the seed are wrong — fix that before letting it search.

Run overnight on near-misses; don't babysit interactive retries.

## When to stop (document, don’t spin)

Park the C, then block auto-queue. See [docs/decomp-wip.md](docs/decomp-wip.md):

```bash
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c \
    --status "leaf branch adds push {lr}" --next "permuter or stay Thumb" --score "N/M"
```

```toml
[[wip]]
name = "sub_080XXXXXXXX"
seed = "src/decompiled/sub_080XXXXXXXX.c"
notes = "src/decompiled/sub_080XXXXXXXX.md"
status = "…"
next = "…"

[[block]]
name = "sub_080XXXXXXXX"
reason = "leaf branch adds push {lr} / permuter score N; seed in src/decompiled/"
```

Leave **readable Thumb** in `src/matched/` (`--kind asm`). Keep the draft in `src/decompiled/`. Log in `docs/decomp-status.md` with a path to the notes.

## Known blocker families (this project)

- **Leaf + branch (still hard after `-fprologue-bugfix`):** `sub_08034894`, `sub_08062728` (`stm` fill), `sub_080699C8`. Try the flag first.
- **Table lookup + pool order:** `sub_0803DD60` family
- **Dual IWRAM store CSE:** `sub_080473E4`, `sub_080473F8` (nearby literals fold unless the first pointer stays live)

## m2c seeds

```bash
python3 tools/decomp/m2c_asm.py sub_XXXXXXXX
```

Fix types → `gMainWorkPtr` / `gBattleWork` → evaluation order → `match_function.py`. m2c `--valid-syntax` helps permuter feeds (see ecosystem skill). Do not use `register`.

## Reference

Project detail: [docs/decomp-patterns.md](docs/decomp-patterns.md)
