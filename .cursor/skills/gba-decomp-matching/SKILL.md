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

### 3. Parameter registers (don’t re-assign early)

Thumb args: `r0`, `r1`, `r2`, `r3`. If asm uses `r1` without `mov` from `r1`, declare `register T *r1 asm("r1");` and **do not** assign from the C parameter name before the asm-equivalent point.

### 4. Struct members (required)

```c
a->unk302 = *(u16 *)gBtlInputMask;   // OK with ram_map.h constants
```

Not: `*(u16 *)((u8 *)a + 0x302) = …`. Add fields to `include/unknown-types.h` first.

### 5. Register-pinned byte ops

See `sub_08031294`: `register u8 r1 asm("r1");` + `*(u8 *)&a->unk00` when retail does byte-wide OR/AND sequence.

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
- **Dual IWRAM store CSE:** `sub_080473E4`, `sub_08041858`

## m2c seeds

```bash
python3 tools/decomp/m2c_asm.py sub_XXXXXXXX
```

Fix types → `gMainWorkPtr` / `gBattleWork` → pin registers → `match_function.py`. m2c `--valid-syntax` helps permuter feeds (see ecosystem skill).

## Reference

Project detail: [docs/decomp-patterns.md](docs/decomp-patterns.md)
