# Decompilation patterns reference

Quick reference once you have a target from [`decomp-queue.md`](decomp-queue.md).
Automatic matchers live in [`tools/decomp/c_patterns.py`](../tools/decomp/c_patterns.py).

## Fast path (one function)

```bash
# 0. Session start — no agent
python3 tools/decomp/script_first.py

# 1. Compact packet (only leftover functions)
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/agent_packet.py sub_08034894

# 2. If the packet has no MATCH, write C from its seed (max 2 retries)
python3 tools/decomp/try_convert.py sub_08034894 --integrate --note battle/input
python3 tools/decomp/match_function.py sub_08034894 scratch.c   # compact DIFF by default
python3 tools/decomp/integrate_c.py sub_08034894 @scratch.c --kind semantic --note "…"

# Grow patterns from clones instead of converting each by hand:
python3 tools/decomp/cluster_shapes.py
```

List all auto-detected patterns:

```bash
python3 tools/decomp/c_patterns.py --list
```

---

## Automatic patterns (`c_patterns.py`)

These are tried first by `try_convert.py` and `script_first.py`.

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

Incoming pointer copies: do **not** add `a = a_arg; b = b_arg` locals. Use the parameters as the live pointers so agbcc's `assign_parms` emits `adds r2, r0; adds r3, r1` in order. Extra locals save `r1` first (scratch conflict) and swap those two insns. Win: `sub_0804109C`.

`x &= ~0x20` compiles as `movs rN, #0x21; negs rN` (`-0x21 == ~0x20`). `&= ~0x21` emits `#0x22` instead.

Keep a struct pointer across a store cluster: `gUnk->a = …; gUnk->b = …` reloads from the IWRAM loc after the first add clobbers the pointer. `w = gUnk; w->a = …; w->b = …` matches retail. Win: `sub_0802D6D4` tail.

Force a pool `ldr` before an index shift/mul (agbcc otherwise computes the index first):

```c
register u32 r1 asm("r1");
register u32 r0 asm("r0");

r1 = (u32)&gUnk_030002A0; /* or ROM table address */
asm("" : "+r"(r1));
r0 = stride;              /* or idx << 2 */
```

Wins: `sub_08037318` (`ldr r1,=0x030002A0` then `movs r0,#0x2C`), `sub_08033978` (`ldr r1,=0x08078158` then `lsls r0,r6,#2`), `sub_08042B28` / `sub_08042B50` (`ldr r0,=table` then `lsls r1,r2,#2`; `r4 = r1 + r0`).

Do **not** `register … asm("r7")`. agbcc will use `r7` and omit `push {r7}`. Leave the `r7` local unpinned. Win: `sub_08037430`.

`-1` as `movs r1,#1; negs r1; mov r8,r1`: `r1 = 1; r1 = -r1; minusOne = r1` with `minusOne` pinned to `r8`. Win: `sub_08033978`.

Add operand order is a real Thumb encoding: `r0 = ch + table` emits `adds r0, r1, r0`; `r0 = table + ch` emits `adds r0, r0, r1`. Win: `sub_08073988`.

Nearby IWRAM stores (`0x03000534` then `0x03000504`, or `0x108` then `0x1B0`) fold to `sub/add #imm` unless the first pointer is kept live across a memory barrier, then reloaded:

```c
r0 = gUnk_03000534;
r1 = 0;
*(s32 *)r0 = r1;
asm("" : "+r"(r0), "+r"(r1) : : "memory");
r0 = gUnk_03000504;
asm("" : "+r"(r0));
*(u16 *)r0 = (u16)r1;
```

Wins: `sub_08041858`, `sub_08069894`, `sub_08071B4C`, `sub_0806A3A4` (`0x03000B3C` then `0x03000B38`, 4 apart). Same family still parked: `sub_080473F8`, `sub_08052934`, `sub_08071F44`, `sub_08071E84`, `sub_0806A314`.

`if (a >= b) goto label` emits `cmp; bge` as fallthrough-false. Nested `if/else` often inverts to `blt` and moves the literal pool. Place shared `return N` labels in retail order so the first path is `ble; b` (pool island + padding) rather than `bgt` plus an inlined return. Win: `sub_08042390`.

Loop exit that already has `0` in `r0` (`ldr; cmp; bne body; pop`) must `return r0`, not `return 0`. `while ((r0 = p->unk00) != 0) { call(p->unk00, …); } return (s32)r0` with `r0` pinned keeps the load and still reloads in the body. Plain `return 0` adds `movs r0,#0` and steals the epilogue padding. Win: `sub_08043B90`.

Mask tests: `r0 = mask; r1 = *flags; r0 &= r1; if (r0 != 0)` with `u32` pins (not `u8`, which becomes `ands r1, r0`). Last test may `ldrb r5, [r5]`. Win: `sub_0803531C`.

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

`match_function.py` prints `N/M bytes matched` and a **compact** DIFF (first mismatch). Pass `--full` for a whole-function hex dump.
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

1. `script_first.py` / `c_patterns` trivial match
2. m2c + hand refine → `match_function.py` MATCH
3. Readable Thumb + **park** unmatched C (`docs/decomp-wip.md`) — do not discard the draft
4. Document blocker / `[[wip]]`
5. Promote RAM names → retry later

---

## Batch runners (many functions)

| Command | When |
|---------|------|
| `python3 tools/decomp/script_first.py` | Every session first (patterns + cleaned m2c) |
| `python3 tools/decomp/agent_packet.py --next` | One leftover function |
| `python3 tools/decomp/cluster_shapes.py` | Clone families → new `c_patterns.py` matcher |
| `tools/decomp/battle_semantic_batch.sh 10 --seeds-only` | Hand-verified battle seeds |

After any batch: `make compare` must stay **OK**. End-to-end: [README.md](../README.md) § Decompilation.
