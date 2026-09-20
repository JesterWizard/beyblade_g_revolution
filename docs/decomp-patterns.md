# Decompilation patterns reference

Quick reference once you have a target from [`decomp-queue.md`](decomp-queue.md).
Automatic matchers live in [`tools/decomp/c_patterns.py`](../tools/decomp/c_patterns.py).

## Fast path (one function)

```bash
# 1. Pick target
python3 tools/decomp/next_queue.py -n 5

# 2. Try patterns → m2c → verify (no integrate)
python3 tools/decomp/try_convert.py sub_08034894

# 3. Land on MATCH
python3 tools/decomp/try_convert.py sub_08034894 --integrate --note battle/input

# Or manual steps:
python3 tools/decomp/c_patterns.py sub_08034894 --verify   # trivial pattern only
python3 tools/decomp/m2c_asm.py sub_08034894              # m2c seed → edit → verify
python3 tools/decomp/match_function.py sub_08034894 scratch.c
python3 tools/decomp/integrate_c.py sub_08034894 @scratch.c --kind semantic --note "…"
make compare
```

List all auto-detected patterns:

```bash
python3 tools/decomp/c_patterns.py --list
```

---

## Automatic patterns (`c_patterns.py`)

These are tried first by `try_convert.py`, `c_convert_batch.sh`, and `semantic_convert_batch.sh`.

| Pattern | Typical asm | C shape |
|---------|-------------|---------|
| Empty return | `bx lr` | `void fn(void) { }` |
| Member load u8 | `ldrb r0,[r0,#off]` | `return a->unkXX;` |
| Member load u32 | `ldr r0,[r0,#off]` | `return a->unkXX;` |
| Return immediate | `movs r0,#N` | `return N;` |
| Store byte constant | `movs r1,#V; strb r1,[r0,#off]` | `a->unkXX = V;` |
| Store arg byte | `strb r1,[r0,#off]` | `a->unkXX = v;` |
| SWI | `swi #N` | `asm("swi N");` or r2 prep |
| IWRAM pool load | `ldr r0,=0x03…` | `return gUnk_0300…;` or `*(u32*)…` |
| IWRAM pool store | `ldr r1,=0x03…; strb` | `*(u8*)gUnk_… = v;` |
| Stack shim | `push {r0-r3}; add sp,#0x10` | naked unified asm |
| Store two u16 | twin `strh` at offsets | two struct fields |
| Init u16/u32 trio | `strh 0; str; strh 0` | `unk00=0; unk04=v; unk02=0` |
| Zero three u32 | three `str r1` with r1=0 | three fields = 0 |
| Store three u32 | `str r2/r3/r1` + clear base | four field writes |
| Store three u16 | three consecutive `strh` | `unkXX` halfwords |
| Init six-word | stores `0x7800`, `0x5000` | common struct init |
| Indexed offset | `ldrb unk06; lsl; add unk10` | `(u8*)a + (idx<<bit) + off` |
| IWRAM addend ldrb | pool + add + ldrb | battle lookup byte |
| Main-work table | `gMainWorkPtr` + ROM table | `row[gMainWorkPtr->unk1818][idx]` |

Before integrating a new offset: add the field to a struct in `include/unknown-types.h` (split a `filler_`).

---

## Manual techniques (when auto-match fails)

### 1. m2c seed + hand edit

```bash
python3 tools/decomp/m2c_asm.py sub_XXXXXXXX > scratch.c
# Fix: struct types, gMainWorkPtr/gBattleWork, remove wrong casts
python3 tools/decomp/match_function.py sub_XXXXXXXX scratch.c
```

Use `--valid-syntax` if m2c output needs extra cleanup.

### 2. Register pinning (`register asm`)

agbcc picks different registers than retail. Pin the dest reg the asm expects:

```c
u16 sub_0802B8BC(s32 a)
{
    register s32 r0 asm("r0");
    register u8 *r1 asm("r1");

    r0 = a;
    r0 <<= 16;
    r1 = *(u8 **)gUnk_03000264;
    r0 >>= 14;
    r0 += (u32)r1;
    return *(u16 *)(r0 + 2);
}
```

Use for: table walks, halfword loads after shifts, dispatch tables (`sub_080674BC`).

**Do not** use `asm volatile("movs r0, …")` for register forcing — use `register … asm("rN")`.

`n = a->unkXX - 1` often compiles `ldr r0,[…]; sub r4,r0,#1`. Retail wants `ldr r4,[…]; sub r4,#1` — split it:

```c
n = a->unk1C;
n = n - 1;
```

Win: `sub_080712CC`.

### 3. Literal pool / load order

Symptom: same-size diff, wrong pool slot or extra `push {lr}` on branches.

```bash
tools/decomp/permuter/permute.sh import sub_XXXXXXXX
tools/decomp/permuter/permute.sh run nonmatchings/sub_XXXXXXXX -j 4 --stop-on-zero
```

If permuter score stays >0: add to [`decomp-queue.toml`](decomp-queue.toml) `[[block]]` and keep readable Thumb.

### 4. Readable Thumb fallback

If semantic C is blocked but asm already matches:

- Leave as unified `asm("…")` in `src/matched/` (`--kind asm`)
- Document blocker in queue TOML + batch log
- Revisit when types/RAM map clarifies the function

### 5. Framed vs leaf-branch

Retail `push {r4, lr}` (or more) → worth hand C. True leaves (`bx lr`, no push) with an `if` hit the agbcc extra-`push {lr}` wall — skip.

`match_function.py` prints `N/M bytes matched` and a status:
- **matched** — integrate
- **identical_diff** — same size, only pool/reloc words differ (not counted as decompiled)
- **same_size** / **size_mismatch** — near miss; `--record` saves to `docs/decomp-function-scores.json`

Full ledger: [`decomp-functions.md`](decomp-functions.md).

### 6. Hand seeds (battle)

Verified battle C templates go in `BATTLE_SEEDS` in
[`battle_semantic_batch.py`](../tools/decomp/battle_semantic_batch.py):

```bash
tools/decomp/battle_semantic_batch.sh 1 --seeds-only
```

Add a seed when you've manually matched a function that m2c/heuristics miss repeatedly.

---

## Function score ledger

Every function is listed in [`decomp-functions.md`](decomp-functions.md) with completion % and `N/M` bytes. Refresh with `make progress` or `make scores`.

```bash
python3 tools/decomp/match_function.py sub_XXXXXXXX scratch.c --record
python3 tools/decomp/function_scores.py --close
```

---

## Known blockers (this project)

| Symptom | Example | Workaround |
|---------|---------|------------|
| Extra `push {lr}` on branch | `sub_0802D8C4`, null-check leaves | Block; permuter or stay readable Thumb |
| rN pool pin | `sub_080601C4` | Permuter; may stay asm-only |
| Dest reg mismatch (same size) | table lookup family | `register asm` on r0/r1/r2 |
| Pool in middle of fn | `sub_08042B78` | Permuter or readable Thumb |
| Branchy leaf | `sub_080615EC` | Readable Thumb until types clear |

---

## Fork order (reminder)

From [`decomp-mission.md`](decomp-mission.md):

1. `try_convert.py` / `c_patterns` trivial match
2. m2c + hand refine → `match_function.py` MATCH
3. Readable Thumb + **park** unmatched C (`docs/decomp-wip.md`) — do not discard the draft
4. Document blocker / `[[wip]]`
5. Promote RAM names → retry later

---

## Batch runners (many functions)

| Command | When |
|---------|------|
| `tools/decomp/c_convert_batch.sh 30` | Trivial patterns only |
| `tools/decomp/semantic_convert_batch.sh 30 --pool-free-only` | Opcode stubs (legacy) |
| `tools/decomp/battle_semantic_batch.sh 10` | Battle readable Thumb |
| `tools/decomp/cursor_batch.sh 10` | Hard functions (m2c seeds) |

After any batch: `make compare` must stay **OK**.
