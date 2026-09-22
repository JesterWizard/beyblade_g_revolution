# Decompilation patterns reference

Quick reference once you have a target from [`decomp-queue.md`](decomp-queue.md).
Automatic matchers live in [`tools/decomp/c_patterns.py`](../tools/decomp/c_patterns.py).

## Fast path (one function)

```bash
# 0. Session start — no agent
python3 tools/decomp/script_first.py

# 1. Compact packet (only leftover functions). The packet runs the local
#    permuter on near-miss/WIP seeds before asking the agent to write anything.
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/agent_packet.py sub_08034894

# 2. If the packet has no MATCH, write C from its seed (max 1 attempt)
python3 tools/decomp/try_convert.py sub_08034894 --integrate --note battle/input
python3 tools/decomp/match_function.py sub_08034894 scratch.c   # compact DIFF by default
python3 tools/decomp/integrate_c.py sub_08034894 @scratch.c --kind semantic --note "…"

# 3. Same-size DIFF → local permuter (imports, scores, searches, integrates):
python3 tools/decomp/permuter/auto.py sub_08034894 --seconds 240

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

### 2. Evaluation order (no GCC asm labels)

`register` and empty `asm("")` are **banned**. If agbcc will not emit retail bytes without them, park the C and leave Thumb in `src/matched/`.

`n = a->unkXX - 1` often compiles `ldr r0,[…]; sub r4,r0,#1`. Retail wants `ldr r4,[…]; sub r4,#1` — split it:

```c
n = a->unk1C;
n = n - 1;
```

Win: `sub_080712CC`. Split statements and operand order (`ch + table` vs `table + ch`) are still allowed — they are ordinary C.

`n = a->unkXX - 1` often compiles `ldr r0,[…]; sub r4,r0,#1`. Retail wants `ldr r4,[…]; sub r4,#1` — split it:

```c
n = a->unk1C;
n = n - 1;
```

Win: `sub_080712CC`.

Incoming pointer copies: do **not** add `a = a_arg; b = b_arg` locals. Use the parameters as the live pointers so agbcc's `assign_parms` emits `adds r2, r0; adds r3, r1` in order. Extra locals save `r1` first (scratch conflict) and swap those two insns. Win: `sub_0804109C`.

Same for a 4-arg function that must start `adds r5, r0; adds r7, r2; adds r6, r3; movs r4, #0`: keep using `a` across calls (do not `obj = a`). Extra copies change save order. Win: `sub_080442FC`.

`u8` args emit `lsls/lsrs` before any other copy. If retail copies `r1` to `r5` first, take `u32` and extend after that copy. Win: `sub_08062A74`.

If retail is `adds r5, r0` then only `lsls r1, #24; cmp r1, #0` (low-byte nonzero, no `lsrs`), take `u32 flag`, copy `dst = a`, then `flag <<= 24`. Clamp `0x800` is `movs #0x80; lsls #4`, not `0x8000`. Reload `*loc` on the `<=0` store. Win: `sub_08033084`.

Mask-first AND (clone of `sub_080425B8`): `addr = &byte; mask = 2; value = *addr; mask &= value` so `movs r0,#2` precedes `ldrb`. Win: `sub_08042540`.

`entry = index + table` not `table + index`. Final add `table3[i] + value` for `adds r0, r1, r0`.

If retail `bl fn; lsls r0, r0, #2` with no caller zero-extend, change the callee prototype from `u8` to `u32` and re-check the callee still MATCH. Win: `sub_08066224` / `sub_08072F94`.

A loop that both `i++` and `count--` then `cmp count, i` is not `while (count > i)` with only `i++`. Win: `sub_0807179C`.

`x &= ~0x20` compiles as `movs rN, #0x21; negs rN` (`-0x21 == ~0x20`). `&= ~0x21` emits `#0x22` instead.

Keep a struct pointer across a store cluster: `gUnk->a = …; gUnk->b = …` reloads from the IWRAM loc after the first add clobbers the pointer. `w = gUnk; w->a = …; w->b = …` matches retail. Win: `sub_0802D6D4` tail.

Add operand order is a real Thumb encoding: `r0 = ch + table` emits `adds r0, r1, r0`; `r0 = table + ch` emits `adds r0, r0, r1`. Win: `sub_08073988`.

`if (a >= b) goto label` emits `cmp; bge` as fallthrough-false. Nested `if/else` often inverts to `blt` and moves the literal pool. Place shared `return N` labels in retail order. Win: `sub_08042390`.

Loop exit that already has `0` in `r0` (`ldr; cmp; bne body; pop`) must `return r0`, not `return 0`. `while ((r0 = p->unk00) != 0) { call(p->unk00, …); } return (s32)r0` keeps the load. Plain `return 0` adds `movs r0,#0`. Win: `sub_08043B90`.

Mask tests: `r0 = mask; r1 = *flags; r0 &= r1; if (r0 != 0)` with `u32` locals (not `u8`, which becomes `ands r1, r0`).

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

Retail `push {r4, lr}` (or more) → worth hand C.

True `bx lr` leaves with a branch: default agbcc emits extra `push {lr}` / `pop {r1}; bx r1` (+4–6B).

**`/* match-flags: -fprologue-bugfix */`:** per-file (parsed by `match_function.py`; not global `CFLAGS`). Honest wins include null-check stores (`sub_0802D8C4`, `sub_08061BDC`, `sub_08062684`, `sub_080475C4`), clamp `u32` args (`sub_080615EC`), and small helpers (`sub_08033958`, `sub_0806AC68`). Table walks / `+r` barriers that only matched with GCC asm labels were parked.

**`/* match-compiler: old_agbcc */`:** per-file compiler choice. `pret/agbcc`'s `install.sh` installs **two** compilers (`tools/agbcc/bin/agbcc`, `tools/agbcc/bin/old_agbcc`) and they do **not** generate identical code — the older one emits some un-coalesced load forms the newer one folds, and vice versa. `match_function.py` parses the comment (`MATCH_COMPILER_RE`), `import_function.py` mirrors it into a `compiler` sidecar so `permuter/compile.sh` swaps `CC`, and the default stays `agbcc`. This is the escape hatch for "unreachable in semantic C" seeds:

| Function | Old compiler wins |
|----------|-------------------|
| `sub_08061308` | un-coalesced `ldrb r0,[r0]; lsls r1,r0` (48/48, `agbcc` 46/48 in 4,000 variants) |
| `sub_08062A74` | `lsls r1,r4,#5` with the handler pool held in `r2` (76/76, `agbcc` 74/76) |

Before parking a seed whose DIFF is a register *destination* on a load, score it with both compilers (`build/dual_compiler_sweep.py` does the whole `src/decompiled` backlog).

Clamp helpers take `u32` args so the callee has no `lsls/lsrs` (`sub_080615EC`). Head/tail IWRAM 0x10 apart and BG I/O switch trees still need honest C (parked: `sub_0806FEFC`, `sub_08061E40`, `sub_08069908`).

Retry remaining `bx lr` + branch functions with the comment before parking (`sub_08034894`, `sub_08062728` stm-fill, `sub_080699C8`).

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
| Dest reg mismatch (same size) | table lookup family | evaluation order; `&local` reload (`sub_08062CC8`, `sub_08062D24`); dummy `ldrb` (`sub_0803531C`); else park |
| Pool in middle of fn | `sub_08042B78` | Permuter or readable Thumb |
| Branchy leaf | `sub_080615EC` | Readable Thumb until types clear |
| Load coalesced into its consumer | `sub_08061308` family | Compile that file with `old_agbcc` (see below) |
| BIOS `swi` with pass-through registers | `sub_080674B4` | Parameterised `swi` operands (see below) |

### `/* match-compiler: old_agbcc */` (load/coalesce family)

`pret/agbcc` ships **two** compilers (`tools/agbcc/bin/agbcc` and `bin/old_agbcc`) and
they do not generate identical code. For a specific shape — a `ldrb`/`ldrh` whose result
is shifted immediately, or a `str` that reuses a still-live address register — `agbcc`
coalesces the load into the consuming instruction (or drops the redundant one) while
`old_agbcc` reproduces retail's extra instruction. No C rephrasing steers `agbcc` there.

Mark the file and every tool follows:

```c
// @ 0x08061308
/* match-compiler: old_agbcc */
```

`match_function.py` (`MATCH_COMPILER_RE`) picks the binary; `import_function.py` writes a
`compiler` sidecar (the permuter preprocesses `base.c` before `compile.sh` runs);
`permuter/compile.sh` swaps `CC`. Absent the comment the default stays `agbcc`.
To find candidates, score the whole backlog with both binaries:

```bash
python3 build/dual_compiler_sweep.py
```

### BIOS `swi` wrapper with pass-through registers (`sub_080674B4`)

A 6-byte trampoline that only zeroes `r2` before `swi 5` cannot be written as a call
(the repo's `gba/syscall.h` declares `CpuSet` as a real function, so `CpuSet(src, dest, 0)`
emits `push/bl/pop`). Inline `asm` is allowed for BIOS `swi` only, and a bare
`asm("swi 5")` never materialises the zero. Give the function the register-carrying
parameters and let the operand list do the placement:

```c
void sub_080674B4(const void *src, void *dest)
{
    asm("swi 5" : : "r"(src), "r"(dest), "r"(0));
}
```

`src`/`dest` are already live in `r0`/`r1`, so only `movs r2, #0` is emitted. The
prototype in `include/unknown-functions.h` uses an empty parameter list (`void f();`)
because the repo's C callers invoke it with no arguments.

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
| `python3 tools/decomp/script_first.py` | Every session first (patterns + cleaned m2c + permuter on near-misses) |
| `python3 tools/decomp/agent_packet.py --next` | One leftover function |
| `python3 tools/decomp/permuter/auto.py FN` | Bounded permuter run; integrates on verified score 0 |
| `python3 tools/decomp/cluster_shapes.py` | Clone families → new `c_patterns.py` matcher |
| `tools/decomp/battle_semantic_batch.sh 10 --seeds-only` | Hand-verified battle seeds |

After any batch: `make compare` must stay **OK**. End-to-end: [README.md](../README.md) § Decompilation.

---

## Permuter notes

`tools/decomp/permuter/auto.py` is the only entry point you need:

1. imports a fresh seed (`src/decompiled/FN.c` first, then m2c) and writes a
   `matchflags` sidecar from the seed's `/* match-flags: … */` comment
2. scores the seed once (`permuter.py --debug`) — score 0 means the seed already
   matches, so the search is skipped
3. otherwise searches, bounded by `--seconds`, then
4. verifies every score-0 candidate with `match_function.py` and integrates the
   first one that is byte-exact.

Gotchas:

- **`-fprologue-bugfix` is required for 21 functions.** `matchflags` is the only
  way the permuter compiler sees it (the permuter strips comments before
  compiling). Without it agbcc emits `push {lr}` / `pop {pc}` and score 0 is
  unreachable.
- **Score 0 is not proof.** The permuter ignores branch targets, so a candidate
  can score 0 and still differ by a branch offset (`sub_0806DEF4`). `auto.py`
  always re-verifies; if every score-0 candidate fails, retry with
  `--strict-branches`.
- Configured compile flags live in `tools/decomp/permuter/compile.sh` and must
  stay in sync with `match_function.py` `ALLOWED_MATCH_FLAGS`.

