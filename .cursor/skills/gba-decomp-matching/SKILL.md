---
name: gba-decomp-matching
description: >-
  Fixes agbcc byte-matching failures for GBA decomp (match_function.py DIFF, near-misses,
  register pinning, literal pools, decomp-permuter). Use when semantic C compiles but
  bytes differ, same-size DIFF, pool order issues, or leaf-branch push lr blockers.
---

# GBA byte-matching techniques

Oracle: `python3 tools/decomp/match_function.py FN path/to.c` → **MATCH** or compact **DIFF** (first mismatch + 16 bytes). Pass `--full` for a whole-function hex dump.

## Diagnose from DIFF output

| Symptom | Likely cause | Try first |
|---------|--------------|-----------|
| Compiled **larger** (+4–16B), retail has no `push` | C `if` on leaf function | Block; permuter; or readable Thumb |
| **Same size**, wrong bytes at pool | IWRAM address CSE / wrong `ldr` | `tmp[]` + `register` dest |
| **Same size**, wrong insn order | agbcc reordered setup | Pin `register … asm("rN")`; match asm evaluation order |
| **muls** mismatch | Compiler multiply vs `muls` | Permuter; or readable Thumb |
| Extra register in prologue | Missing pinned callee-saved reg | Pin `r4`/`r5` used in asm |

## Proven patterns (this repo)

### 1. IWRAM pool pin (`tmp[]`)

```c
register struct Unk0380 *r1 asm("r1");
u32 tmp[1];

tmp[0] = gUnk_03000380;
r1 = (struct Unk0380 *)tmp[0];
```

Wins: `sub_08033C1C`. Use when retail has `ldr rN, =0x03……` before use.

Nearby IWRAM addresses fold (`0x534-0x30`, `0x108+0xA8`). Keep the first pointer live, then reload:

```c
r0 = gUnk_03000534;
r1 = 0;
*(s32 *)r0 = r1;
asm("" : "+r"(r0), "+r"(r1) : : "memory");
r0 = gUnk_03000504;
asm("" : "+r"(r0));
*(u16 *)r0 = (u16)r1;
```

Wins: `sub_08041858`, `sub_08069894`, `sub_08071B4C`, `sub_0806A3A4`.

Table address before index (empty `+r` barrier, same as `sub_0803DDD8`):

```c
r1 = (u32)&gUnk_030002A0;
asm("" : "+r"(r1));
r0 = 0x2C;
```

Wins: `sub_08037318`, `sub_08033978`, `sub_08042B28`, `sub_08042B50`.

`r0 = ch + table` → `adds r0, r1, r0`. Swapping operands is a 1-byte DIFF. Win: `sub_08073988`.

### 2. Register flow for and/cmp

```c
register u32 r0 asm("r0");
register u32 r1 asm("r1");
r1 = p->unk14;
r0 = 8;
r0 &= r1;
if (r0 != 0) return 1;
```

Win: `sub_0806F430`. Mirror retail’s register roles, not abstract logic.

Mask-first tests (`movs r0,#N; ldrb r1,[r5]; ands r0,r1`) need `u32` pins. `u8` becomes `ands r1, r0` / `cmp r1, #0`. Last test may `ldrb r5, [r5]`. Win: `sub_0803531C`.

### 3. Parameter registers (don’t re-assign early)

Thumb args: `r0`, `r1`, `r2`, `r3`. If asm uses `r1` without `mov` from `r1`, declare `register T *r1 asm("r1");` and **do not** assign from the C parameter name before the asm-equivalent point.

### 4. Struct members (required)

```c
a->unk302 = *(u16 *)gBtlInputMask;   // OK with ram_map.h constants
```

Not: `*(u16 *)((u8 *)a + 0x302) = …`. Add fields to `include/unknown-types.h` first.

### 5. Register-pinned byte ops

See `sub_08031294`: `register u8 r1 asm("r1");` + `*(u8 *)&a->unk00` when retail does byte-wide OR/AND sequence.

`if (a >= b) goto label` keeps `cmp; bge`. Nested if/else often inverts to `blt` and moves the pool. Put shared `return N` labels in retail fallthrough order. Win: `sub_08042390`.

Loop that exits with `0` already in `r0`: `while ((r0 = p->unk00) != 0) { call(p->unk00, …); } return (s32)r0`. Plain `return 0` adds `movs r0,#0`. Win: `sub_08043B90`.

Do **not** `register … asm("r7")`. agbcc will use `r7` and omit `push {r7}`. Leave the `r7` local unpinned. Win: `sub_08037430`.

Keep a struct pointer in `r2` with `register T *r2 asm("r2"); r2 = a;`. Win: `sub_08031300`.

Force an addend literal into `r3` before `adds r2, r4, r3`: `r3 = off; asm("" : "+r"(r3), "+r"(r4)); r2 = r4 + r3;`. Win: `sub_080523A4`.

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

- **Leaf + branch:** `sub_0802D8C4`, `sub_08061BDC`, `sub_08034894`
- **Table lookup + pool order:** `sub_0803DD60` family
- **Dual IWRAM store CSE:** `sub_080473E4`, `sub_080473F8`, `sub_08052934` (`sub_08041858` / `sub_08069894` matched via `+r` + memory barrier)

## m2c seeds

```bash
python3 tools/decomp/m2c_asm.py sub_XXXXXXXX
```

Fix types → `gMainWorkPtr` / `gBattleWork` → pin registers → `match_function.py`. m2c `--valid-syntax` helps permuter feeds (see ecosystem skill).

## Reference

Project detail: [docs/decomp-patterns.md](docs/decomp-patterns.md)
