# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

<!-- decomp-progress:start -->
| Metric | Value |
|--------|-------|
| Linked in ROM | **633/633** (100% peeled) |
| **Decompiled C (functions)** | **403/633 (63.7%)** |
| **Decompiled C (bytes)** | **27,676/90,272 (30.7%)** |
| Not opcode (C + readable Thumb) | 633/633 (100.0% fn, 100.0% bytes) |
| Readable Thumb | 230/633 (36.3%) |
| Opcode `.byte` embeds | 0/633 (0.0%) |
| `src/matched/*.c` | 633/633 |
| Phase | **3b in progress — replace opcode stubs with semantic C / readable Thumb** |
| Battle semantic C | 75/160 (46.9% fn, 19.1% bytes) |
| Counter | [`decomp-progress.svg`](decomp-progress.svg) · [`decomp-progress.json`](decomp-progress.json) · [`decomp-functions.md`](decomp-functions.md) |
<!-- decomp-progress:end -->

## Batch log

### 2026-09-22 — the permuter had been permuting asm wrappers; sub_08038580 24 → 82/92

Writing off `sub_08031300` needed a permuter verdict, and the verdict turned out to
be worthless: `tools/decomp/permuter/import_function.py` still declared
`WIP = ROOT / "src" / "wip"`. That directory was deleted when the drafts were
promoted to `src/decompiled/` — `agent_packet.py` and `script_first.py` were updated
in the same commit, the importer was missed. So `seed_c()` searched a path that no
longer exists, fell through to `src/matched/`, and imported the **readable-Thumb
wrapper** as the permuter's base. Three tells, all present in the run headers:

- `base score 100` on a function that is ~20 bytes from matching,
- `match-compiler: agbcc` printed for a seed whose comment asks for `old_agbcc`
  (`match_compiler()` looked in the same dead directory),
- `No perm macros found. Defaulting to randomization.` — an asm body has none.

One-line fix. Runs recorded before the promotion stand; the two from today were
void. `sub_08031300` was re-run properly (base 1245 → best 790, no zero), which
confirms its documented register-destination blocker on evidence that now holds.

While checking the same class of rot, three agent-facing skills
(`gba-decomp-session`, `gba-decomp-improve`, `gba-decomp-matching`) still taught
`src/wip/` as the drafts directory, and 38 notes in the gitignored
`build/matched.json` still said "semantic draft from src/wip", which is what
`analysis/functions.json` was rendering. Both corrected.

**Then the actual decomp work — `sub_08038580`, 24/92 → 82/92.** Three source-shape
wins, all legal C, none needing register pins:

1. Inline the global (`if (gUnk_030003CC != 0)`) instead of hoisting it into a
   local — the pointer lands in `r0`, matching `ldr r0,[r5]; ldrh r0,[r0,#0x20]`.
   59/92.
2. Hoist the deref into a local (`src = (void *)*gData_080BB8C0;`) — fixes the
   **literal-pool order**, which came out `030003CC, 05000200, 080BB8C0` with the
   deref inline and `030003CC, 080BB8C0, 05000200` (as retail) hoisted. 76/92. This
   one was the permuter's idea, and it is the reason a working seed path matters.
3. `(one = 1)` as an assignment *inside the condition* rather than a statement —
   sinks `movs r6,#1` to after the `asrs`, as retail. 82/92.

A six-shape sweep of argument and pointer orderings plateaus at 82/92 (74/92 for
variants that split the palette pointer into its own local). The remaining 10 bytes
are scheduler ordering only: retail materialises both address constants and
dereferences last, agbcc sinks the dereference to its use and then reloads the
palette base into a different register — the `sub_08061308` / `sub_08062A74`
family. A 300 s × 8-job permuter run from the 82/92 seed (base 95, best 85) agrees.
Parked at 82/92 with `retry = false` and a note to revisit only on a compiler change.

### Queue bookkeeping made self-consistent

The picker offered `sub_08031300` — a function whose notes say "do not re-attempt by
hand or by permuter" — because `park_wip.py` only wrote a `[[wip]]` block when the
name was *new*. Re-parking left the previous `status`/`next`/`score` in place, so the
queue kept advertising finished work while the notes said otherwise.

- `park_wip.py` now upserts via `queue_toml.upsert_block()`, rewriting only the given
  fields; `--exhausted` writes `retry = false`.
- `agent_packet.py --next` skips `retry = false` (override: `--force-exhausted`).
- New `tools/decomp/queue_toml.py` owns all queue edits, splitting at line-initial
  `[[section]]` headers. Its `--check` asserts split/join is the identity and that
  rewriting a field with its own value is a no-op — the queue's prose is full of
  brackets (`[r2]`, `[sp, #8]`) that a whole-text regex happily tears in half, which
  is exactly what the first prune attempt did (restored from git, reimplemented).
- Backfilled `retry = false` on `sub_08031300`, `sub_0803DCFC`, `sub_08061C48` with
  the reason in `next`, so the four exhausted entries now say so in machine-readable
  form rather than in prose the picker cannot see.

Void evidence was also cleared for `sub_08038580` (queue said 24/92; the real figure
on `old_agbcc` was 59/92) and `sub_08031300` (queue said 6/78 with an invitation to
re-run the permuter). Result: `make compare` OK, `make audit` 633/633,
`make signatures` 0 conflicts, MATCHING 413/633.

### 2026-09-22 — VBlankIntrWait regression recovered as semantic C; draft prune

`make tier` fell 413 → 412 after the stub-arity batch. The cause was the
VBlankIntrWait repair itself: the honest `(void)` signature was unreachable from
the old two-dummy-parameter form, so the file had been rewritten as a
`__attribute__((naked))` wrapper. That byte-matches, but it reclassifies the file as
**readable Thumb**, so a genuine semantic match was traded for cosmetic honesty and
dropped out of the MATCHING tier.

The original's `movs r2, #0` only lands in `r2` while another register holds the
zero operand, which is why the old version kept two pointer parameters it never
used. A clobber list says the same thing honestly — the BIOS ABI gives r0–r3 to
SWI input and result — and frees `r2` for the constant:

```c
void VBlankIntrWait(void)
{
    asm("swi 5" : : "r"(0) : "r0", "r1");
}
```

Verified 6/6 bytes, still `file_kind() == semantic`, MATCHING restored to **413**.
The two other BIOS wrappers touched in the same batch (`Div`, `LZ77UnCompWram`)
were checked for the same trap and are unaffected.

Then the draft tier was cleaned up, since it turned out to be mostly stale:

- **85 `src/decompiled/*.c` drafts** duplicate a function whose `src/matched/`
  file is already semantic C — leftovers of attempts that succeeded. A draft only
  means something while the function is unmatched, so they inflated DECOMPILED and
  kept dead `[[wip]]` tasks alive.
- **83 paired `.md` notes** were still the machine-generated `park_wip.py` stub;
  the **2 hand-written notes** (`sub_0803531C`, `sub_08062CC8`) are kept.
- **90 stale `[[wip]]` blocks** in `docs/decomp-queue.toml` (80 for now-matched
  functions, 10 whose seed file had vanished) — 227 → 137 entries.

New tool `prune_drafts.py` (`make prune-drafts`) enforces this, with `--keep-notes`.
It edits the queue **block-wise**, splitting on line-initial `[[section]]` headers,
never by regex over the whole text: the first attempt used `\[\[wip\]\]([^\[]*)`,
which a status note containing `[r2]` terminated early, leaving a torn block and a
TOML parse error. Caught by `next_queue.py`, restored from git, reimplemented
structurally. A readable-Thumb wrapper does *not* count as superseding a draft —
there the draft may be the only C that exists.

Result: `make compare` OK, `make audit` 633/633, `make signatures` 0 conflicts,
MATCHING 413/633, `next_queue.py` parses and runs.

### 2026-09-22 — signature arity audit (`make signatures`) + 13 stub fixes

The VBlankIntrWait find was not a one-off: a function can compile everywhere and
still be declared, defined and called three different ways, because each C file
compiles in isolation and the C is never linked. Built the machine check for it.

`make signatures` (`audit_signatures.py`) cross-checks the three sources of truth
per function — `unknown-functions.h` prototypes, `src/matched/*.c` definitions, and
all 1474 call sites across `src/matched/` + `src/decompiled/`. It folds readable
names back to their `sub_` label via `symbols.h` so renamed functions stay
checkable, blanks comments/strings/preprocessor so `asm("bl sub_…")` is not read as
a call, and reports each disagreement **once** with every claim and its source
rather than a wall of call-site lines.

Sources are not equally trustworthy, so claims are weighted: header prototype 3,
caller's local prototype 2, semantic definition 2, call site 1, and a
**readable-Thumb asm stub 0** — a stub says `(void)` only because its body ignores
the registers, so it is a placeholder, not a claim. Deliberately open signatures
(`void f();`, `f(...)` — the stripped `DebugPrint` stubs) are never reported, since
varying arity is their whole point.

First run found **13 functions whose sources disagreed on arity**, all the same
shape: a `src/matched/` readable-Thumb stub declaring `(void)` while its callers
passed 1–7 arguments, with the truth sitting in the callers' local prototypes.
None was in `unknown-functions.h`, which is why nothing had ever noticed.

`make fix-stub-arities` repairs them. Types get picked up from prototypes, but a
stub is its own translation unit, so a type named only in a *caller's* local
prototype is not visible where the stub is compiled — the first attempt on
`sub_0803139C` copied `struct Unk3114C *` from `sub_0803114C.c` and the stub stopped
compiling. Fixed by trying candidate parameter lists in order (header, local
prototype, opaque `void *`) and keeping the first that still byte-matches.
`sub_0803139C` fell back to opaque pointers; the other 12 kept their real types.
All 13 verified byte-identical with `match_function.py`.

Result: 13 conflicts → **0**, and 0 call sites on the wrong arity. `make audit`
633/633, `make compare` OK on a forced rebuild.

Also from this round: `make audit-drafts` / `make repair-drafts` to surface draft
compile health (114 of 130 drafts compile; the 16 failures are hand work, tracked
below), and `document.py` now prunes stale pages on rename.

Still open: `sub_0803139C` and any future stub may want its *return type* synced
too — the audit only compares arity, and that stub still says `void` where callers
expect `s32`.

### 2026-09-22 — BIOS wrapper + pool naming batch (33 → 43); draft audit targets

Named 10 more, taking named 33 → **43/633** (battle 22/87, graphics 8/34). Two of
them had C seeds, so DECOMPILED went 130 → 128 and UNDERSTOOD 6 → 8.

**The BIOS wrapper family** (`sub_080674A0…B4`) — five adjacent functions at
`0x080674A0`, all `<swi> ; bx lr`. Read off the retail bytes, cross-checked
against call-site behaviour:

| Function | Retail | BIOS | Name |
|----------|--------|------|------|
| `sub_080674A0` | `swi #6` | Div (quotient) | `Div` |
| `sub_080674A4` | `swi #6 ; r0 = r1` | Div (remainder) | `DivRemainder` |
| `sub_080674B0` | `swi #8` | Sqrt | `Sqrt` |
| `sub_080674AC` | `swi #17` | LZ77UnCompWram | `LZ77UnCompWram` |
| `sub_080674B4` | `movs r2,#0 ; swi #5` | VBlankIntrWait | `VBlankIntrWait` |

`Div`/`DivRemainder` click immediately against `TextFormatInt`, which peels digits
with exactly that pair (`num = Div(num, 10)`, `digit = DivRemainder(num, 10)`).

- **`sub_080674B4` had a lying signature.** It was declared and defined as
  `(const void *src, void *dest)` — a memory-copy shape — but every one of its
  **38 call sites** calls it with no arguments, and the header only compiled
  because the declaration was left unprototyped (`void sub_080674B4();`). The
  retail body is `swi #5`, which is VBlankIntrWait. Every call site is the same
  frame sequence — `sub_08061BE8` (queue a VRAM upload) → update → **wait for
  VBlank** → `_08073C40` commit — which is exactly where you must wait before
  presenting. Rewrote it as a `naked` wrapper with an honest `(void)` signature
  and tightened the header prototype. This is the single most-called function in
  the ROM, so the old shape was the most misleading comment in the tree.
- `sub_0806FDD0` / `sub_0806FE84` → `BtlObjPoolAlloc` / `BtlObjPoolFree` — an
  exact alloc/free pair over a pool keyed at `node->unk22`: Alloc pops the free
  list at `0x030040AC` and links into the active list at `0x030040A4` ordered by
  key; Free unlinks, relinquishes the node's status bit via `sub_0806FBF8`, and
  pushes back onto the free list. The pool head sits directly beside
  `gBtlObjListHead` (`0x030040A8`), the list `BtlObjListMoveToHead` uses.
- `sub_08067A9C` → `DebugMessage`. Its retail body is **empty** (a bare `bx lr`),
  yet callers pass strings read straight out of the ROM: *"No sprites left!"*,
  *"Error allocating memory for actor motion modifiers\n"*, *"Spline count for
  collision data exceeds maximum available"*. So the shipping build has the
  diagnostic reporting stripped out — these paths fail silently. Sibling
  `DebugPrint` (`sub_08067B98`) is the varargs half of the same stripped pair.
- `sub_080705DC` → `TextEntrySetPaletteBank` (26 callers) — writes `(b & 0xF) << 12`
  into an entry's `unk14` under the `0xFFF` mask, i.e. bits 12–15 of a GBA screen
  entry, which is the palette bank. Sibling `TextSetPaletteBank` sets the engine's
  global bank (`gUnk_03000798->unk96`); this one sets it on a single entry.
  Callers pass real banks (`0x0E`, and bank 2 across a run of entries).
- `sub_080617C4` → `TextSetActiveObject` (0.7, 17 callers) — stores a descriptor at
  `engine+0x88`, its data pointer at `+0x8C`, publishes descriptor bytes into
  `+0xA0/+0xA2` and derives `+0x9C`. Every call site passes two ROM addresses, so
  it activates a ROM-described resource; the early-out tests a flag at
  descriptor `+0x0C`. Lower confidence — the evidence is the register traffic, not
  the domain.

**Draft compile health is now visible.** `make audit` only ever covered
`src/matched/`. Added `make audit-drafts` (and `make repair-drafts`), and taught
`repair_naked_signatures.py` about `--dirs`: matched repairs are still gated on
byte-identity and reverted on regression, while drafts only have to compile, since
they are not expected to match yet. Current state of the 130 drafts: **114 compile,
16 do not** (9 cross-function `conflicting types`, 6 warnings-as-errors, 1 syntax
error). Only 1 was auto-repairable and it still failed to compile, so the tool
reverted it — correctly leaving all 16 for hand work. Deliberately not mass-fixed:
several of those conflicts mean the *draft's* signature is the better guess than
the header's, so aligning them blindly would destroy information. Tracked here as
the next tooling/quality item.

Verified: `symbols.py apply` rewrote 57 files / 140 occurrences (string literals
untouched); all 10 renamed functions re-checked, plus the 5 earlier BIOS wrappers —
100% each; `make audit` 633/633; `make compare` OK on a forced full rebuild;
`make analyze` idempotent.

### 2026-09-22 — battle naming batch (23 → 33); document.py prune fix

Named 10 battle functions from the analysis DB plus verified source reads, taking
named from 23 to **33/633** (battle 21/87, graphics 7/34). No new byte-matches.

- `sub_080735DC` → `TextFormatInt` (10 callers) — signed decimal formatter:
  repeated div/mod 10 via `sub_080674A4`/`sub_080674A0`, sign slot, zero special
  case, tail-call into the digit copy. Highest fan-in unnamed function left.
- `sub_080628B4` → `RandRange` (9 callers) — the battle LCG. Advances the state at
  `gMainWorkPtr->unk1800` by `0x36F1ACE3`, scales the high bits with `0x9FBF1 >> 16`,
  then bounds it through `sub_08074264`. Call sites confirm the bound: the result is
  used directly as an array index, and `sub_080628B4(3)` is passed as a mode.
- `sub_08067890` → `TimerAdvance` — identified `gUnk_03000180` as a timer from its
  readers (`delta = unk00 - unk04` is elapsed time, and `unk00` is saved into a
  timestamp field). This function rotates the triple: `unk04 = unk00` then
  `unk00 += unk08`.
- `sub_08044EE8` → `BtlClearUnk1688Entry`, `sub_080433F4` → `BtlClearUnk1834`,
  `sub_0802C5DC` → `BtlUnk1694FindAndMark`, `sub_0803E440` → `BtlCountLiveSlots`,
  `sub_080603E0` → `BtlSetAllUnk1710`, `sub_0802BA4C` → `BtlFreeUnk1694Obj`,
  `sub_08070678` → `BtlReleaseEntry` (0.7–0.85) — each evidenced in `symbols.json`
  and rendered into the generated "Why this name" section.
- **`document.py` now prunes stale pages.** It only ever wrote, never deleted, so a
  rename left the old page behind (the `BgMapSetPaletteBankRun.md` orphan from the
  previous batch was still on disk). This broke the "generated view" invariant —
  the tree was no longer a faithful view of `symbols.json`. Now anything carrying
  the generator banner that is not in the current output set is removed; 1 stale
  page pruned, second run prunes 0. Hand-written markdown in the same directory is
  untouched.

Verified after the batch: `symbols.py apply` rewrote 31 files / 37 occurrences; all
10 renamed functions re-checked with `match_function.py` — **10/10 still 100%**;
`make audit` 633/633 clean; `make compare` OK on a forced full rebuild;
`make analyze` still idempotent.

### 2026-09-22 — matched-C integrity fix: 65 files did not compile

Found while verifying a rename: **65 of the 633 files counted as matched could not
be compiled at all** (568 clean, 65 failing). All 65 failed with agbcc's
`conflicting types`, because a `__attribute__((naked))` wrapper was declared
`(void)` while `include/unknown-functions.h` declares the real parameter list —
plus a handful of wrong return types (`void` vs `s32`, `void` vs `void *`) and one
wrong parameter type (`u32 a` vs `u16 a`).

This was **pre-existing and independent of naming** (the sampled offender
`sub_0803114C` is unchanged at `HEAD` and is not in `symbols.json`), and nothing
caught it: `make compare` is green because matched C is never linked — the
Makefile's `C_SRCS` is empty and the ROM links generated `asm/matchings/*.s`. So
the "403/633 semantic C" figure was resting in part on source that does not
compile.

- **`tools/decomp/audit_c_compiles.py`** (`make audit`): compiles every
  `src/matched/*.c` standalone through agbcc, honouring each file's
  `match-flags` / `match-compiler` comments, and reports the first diagnostic.
- **`tools/decomp/repair_naked_signatures.py`** (`make repair-signatures`): copies
  the prototype's return type and parameter list into a definition whose signature
  disagrees. Deliberately narrow — it only rewrites a definition anchored by a
  `__attribute__((naked))` line or that is the file's own top-level definition of
  its own stem, because a loose pattern over `src/matched/*.c` also matches call
  sites and forward declarations (an earlier draft "repaired" 290 files that way).
  It only touches files that actually fail to compile, so a signature differing
  solely in parameter *names* is left as is — 27 such files were skipped as
  cosmetic.
- Applied to 63 files plus 2 hand-fixed (`sub_08073988`, which a rename had
  renamed to `TextMeasureWidth`). A signature change *can* alter codegen for an
  ordinary function, so every touched file was re-checked with
  `match_function.py`: **63 kept, 0 reverted** — no match regressed.

**Result: `make audit` 633/633 clean (was 568), `make compare` OK** (forced full
rebuild). The C corpus is now verifiable from its own sources.

### 2026-09-22 — text/BG naming batch; target-picker fix; 1 blocked

No new byte-matches (the matching axis remains blocked on a compiler
behavioural difference; see below). Naming advanced 15 → 23 and the session
target picker was repaired.

- **`agent_packet.py --next` was picking the wrong end of the queue.** All 15
  `small_clean` plus all 4 `leaf_branch` and all 77 `large` targets are parked
  seeds, so the old two-pass logic (fresh targets first, parked seeds only as a
  last resort) skipped every cheap bucket and returned a fresh **1552-byte
  `high_reg_pressure`** function — the most expensive target in the ROM. It also
  never looked at `leaf_branch` at all. Rewritten so the difficulty bucket is the
  primary key and parked-vs-fresh is only a tiebreak inside a bucket; `--next`
  now returns a 78-byte seed. `leaf_branch` is now reachable.
- **`symbols.py`: renaming an already-applied symbol corrupted the source.** The
  rewriter only mapped `sub_XXXXXXXX` → readable name, and `put` discarded the
  previous name. So re-naming an already-migrated function left the old readable
  identifier in every call site while `symbols.h` stopped defining it — a compile
  error. Now the superseded name is retained in `aliases[]` and `apply` rewrites
  every alias. Caught by re-naming `BgMapSetPaletteBankRun` → `TextRowSetPaletteBank`
  (23 files were in the broken state); repaired and re-verified.
- **Text rendering subsystem identified.** The `graphics`-classified cluster around
  `gUnk_03000798` is a text engine, established from the call sites rather than
  guessed: `TextDrawAlign(data, x, mode)` aligns by measured string width across
  three modes (0 = centre, 1 = right, 2 = left); callers write
  `TextDrawAlign(d, TextGetAreaWidth() >> 1, 0)` to centre. The nine new names:
  - `sub_08069908` → `BgGetHofsReg`, `sub_08069948` → `BgGetVofsReg` (conf 0.95) —
    `0x04000010|0x04000012 + sel*4`, the GBA BGxHOFS/BGxVOFS register pair.
  - `sub_080615EC` → `TextSetCursor`, `sub_08061784` → `TextGetAreaWidth`,
    `sub_0806171C` → `TextDrawAlign`, `sub_08061610` → `TextSetPaletteBank`,
    `sub_08061564` → `TextDraw`, `sub_08073988` → `TextMeasureWidth` (0.8–0.85).
  - `sub_08061D68` → `TextRowSetPaletteBank` (0.7), refining the previous
    less-specific `BgMapSetPaletteBankRun` now that its callers are known to be
    text code.
  Engine layout recovered: `+0x90` cursor x, `+0x92` cursor y, `+0x96` palette
  bank, `+0x98` text area width, `+0xA0/+0xA2` byte size and line height, `+0x9C`
  size in words.
- **`make compare` after the batch: OK.** Verified with a forced full rebuild
  (`rm` the `.gba` and ELF) plus per-function `match_function.py` re-checks of four
  rewritten callers — all still 100%.

### Blocker: `sub_08031300` (parked, do not re-attempt)

Wrote clean semantic C for the 78-byte text-palette tick. Result: **same size
(78/78), 22/78 bytes matched** — the best result seen for it. A 6-shape variant
sweep on both compilers scored 15–31/78 and the local permuter (240 s × 8 jobs)
found no score 0 (best 920). The mismatch is a register **destination** choice:
retail keeps the incoming parameter in `r2` and gives `r1` to the shifted palette
value, while agbcc coalesces it into `r1`. Control flow and size are identical;
only the register and its dependent operands differ. Same family as the
`sub_08061308` finding, so it is unlikely to be reachable by source reshaping.
Full reasoning in `src/decompiled/sub_08031300.md`.

### 2026-09-22 — pipeline rework: analysis DB, DECOMPILED tier, naming layer

No new byte-matches this batch. This restructures the workflow so matching is one
axis of progress rather than the entry gate. Design:
[docs/decomp-pipeline.md](decomp-pipeline.md).

- **Lifecycle vocabulary** (`tools/decomp/tier.py`): `UNKNOWN` → `DECOMPILED` →
  `UNDERSTOOD` → `MATCHING`, derived from independent `has_c` / `named` / `matches`
  flags, so one hard function never blocks the pipeline. `function_scores.py` and
  `progress.py` now import it instead of each carrying their own status strings.
- **Analysis DB** (`tools/decomp/analyze.py`, `make analyze`): emits
  `analysis/functions.json` (633 rows), `xrefs.json`, `structs.json`,
  `systems.json`. Adds the global call graph — `callers[]` / `callees[]` did not
  exist anywhere before — plus per-function `ram_refs[]`, `pool[]`, `offsets[]`,
  `insn_count`. Verified idempotent: two consecutive runs are byte-identical apart
  from timestamps.
- **`src/wip/` promoted to `src/decompiled/`** (`tools/decomp/promote_wip.py`):
  219 `.c` + 221 `.md` moved flat, `[[wip]]` seed/notes paths in
  `docs/decomp-queue.toml` rewritten so `make queue` is unaffected. The DECOMPILED
  tier is first-class and navigable; it remains non-linked (the Makefile's
  `C_SRCS` is empty — matched code links as generated `asm/matchings/*.s`).
- **Symbol layer** (`tools/decomp/symbols.py`, `make symbols`): names live in
  `analysis/symbols.json`, keyed by address, with `AUTO`/`AI`/`HUMAN` provenance
  where a lower-provenance pass can never overwrite a higher one. It generates
  `include/symbols.h` as `#define <Name> sub_XXXXXXXX` alias macros, included from
  `include/global.h`, so the preprocessor still emits the original link label and
  `make compare` **cannot** be broken by naming. `[renames]` in the `.toml` is now
  a generated read-only view. Collisions are skipped and flagged, not emitted.
- **Naming is decoupled from matching.** A naming pass reads `callers[]` /
  `callees[]` / `ram_refs[]` plus `structs.json` and must supply `--confidence`
  and at least one `--evidence` line; the evidence is rendered into the generated
  docs as a "Why this name" section. All 633 functions are eligible immediately,
  so the previously 0-of-633 named gap starts closing without waiting on any
  single hard match. 15 named so far.
- **End-to-end alias validation** (the plan's byte-neutrality gate): named
  `sub_08061D68` → `BgMapSetPaletteBankRun`, then `symbols.py apply` rewrote **137
  identifier occurrences across 23 files** of semantic C. `make compare` → **OK**,
  and `asm/matchings/sub_08061D68.s` still emits `.global sub_08061D68`. The
  rewriter skips string literals, char literals, and comments, so the ~222
  readable-Thumb wrappers that carry `bl sub_XXXXXXXX` inside `asm("...")` are left
  alone — a macro cannot expand inside a string, and a naive text replace
  regressed 38 matching files before this was fixed.
- **Docs** (`tools/decomp/document.py`, `make document`): `docs/systems/*.md` and
  `docs/functions/*.md` generated from the DB with readable names throughout. The
  generated scoreboard `docs/decomp-functions.md` is unchanged.
- **CLI** (`./decomp` → `tools/decomp/cli.py`): `setup` / `analyze` /
  `decompile` / `rename` / `document` / `verify` / `status`, dispatched over the
  existing tools. New `make analyze` / `symbols` / `tier` / `document` targets.

Lifecycle after the batch: `UNKNOWN 84 | DECOMPILED 132 | UNDERSTOOD 4 | MATCHING 413`.
Named 15/633. `make compare`: **OK**.

### 2026-09-21 — ten semantic matches (384→394/633)
Small call-sequence and register-scheduling functions. `make compare` after the batch.

- `sub_080674A4` — SWI 6 remainder (`asm("swi 6")`, return the second result).
- `sub_080604C8` (`old_agbcc`) — pack window bytes. The last halfword store stays `strh [rN]` because an if/else join keeps the pointer increment live.
- `sub_08043B58` (`old_agbcc`) — table walk. The key is `gMainWorkPtr->unk1690->unk00`, and `*walk++` is the `ldmia`.
- `sub_08051444` — battle gfx setup. Pointer locals are assigned after the first two calls so the loads are not hoisted.
- `sub_08052934` — gfx row. `gData_080995AC + 0xC` stays a separate `adds #0xC`, and `&unk1818` is taken before the table load.
- `sub_0805264C` — menu row. Symbol load before `idx << 4`; sign-extended `unk2D5` is read before the highlight constant so that constant reuses the object's register.
- `sub_08061E8C` — fill `Unk61E8C`. `u16` tail arguments are real parameters (in-place `lsls`/`lsrs`), and `0x200` is `0x80 << 2`.
- `sub_080735DC` — signed decimal text. `pos` and the sign flag are set after the template copy.
- `sub_0804495C` (`old_agbcc`) — copy 32 palette halfwords. The table symbol is loaded before `unk181F`.
- `sub_08071B4C` — sound register reset. A dead `z = w` drops the halfword zero from r1 so the word stores use the callee-saved zero. `gData_0300410C` is its own symbol (`0x030040DC + 0x30` would fold).

### 2026-09-21 — packet `sub_0803715C`, then smallest non-WIP `sub_08067F3C` (no new match)
`agent_packet.py --next` returned `sub_0803715C` (444 B, high register pressure, m2c failed). The asm is a 20..100 score folded into `MainWork.unk0874` and an `Unk002A0` slot. Types added (`struct Unk3715C`, `struct Unk3715CTail`, `Unk002A0Record.unk24`) and `s32 sub_08042C3C(s32)` declared. The transcription scores 33/444 and is 20 bytes short: `a` stays in r4 instead of `mov r8, r0`. Parked. `make compare` OK — the linked file is still the Thumb wrapper.

`sub_08067F3C` (92 B) is the smallest remaining function that was not already a WIP seed. 58/92, 4 bytes over: the product is `muls r3, r2` instead of `muls r2, r3`, and the `u16` loop count is a `lsls`/`lsrs` pair instead of `subs r1, #1`. Parked.

### 2026-09-21 — two clone families (+4, 380→384/633)
Both pairs `script_first` listed as remaining readable-Thumb clones.

- `sub_08071E84` / `sub_08071EE4` (96 B, `old_agbcc`) — free-slot scan of the `Unk71E84` array. Plain agbcc folds the entry test `(byte - 1) != -1` into `cmp r0,#0`. `for (i = *(u8 *)gData_030040C4 - 1; i != -1; i--)` keeps retail's materialised -1, and an `id` local makes the counter increment reuse the value just stored into `unk18`. The twin only swaps `sub_08071E44` for `sub_08071E04`.
- `sub_08062D80` / `sub_08062E88` (264 B) — walk palette indices `a..b`, add or subtract `d` from an RGB555 triplet, clamp at 31 or 0. `if/else` saved `a` into another register and inverted the `c` test; gotos restore `beq` / `beq` / `b`. The three channel stores have to land before any clamp so the first sum stays in r1, and `v0 <<= 24; v0 >>= 24` is the in-place sign extend (`(s8)v0` shifts through r0). The twin swaps in `sub_08062CC8` / `sub_08062CF4`.

`make compare` OK.

### 2026-09-21 — 3E328 clone family, byte-offset rows (+2, 378→380/633)
`sub_0803E328` was already matched (`old_agbcc`, `table[scaled + 0]`). Its two clones read the same 4-byte rows at byte 1 and byte 2.

- `sub_0803E374` (76B) — `table[scaled + 1]` compiles to `adds r0,#1` then `ldrb [r0]` (80B). A member of new `struct Unk3E374Row` (`->unk01`) puts the offset back on `ldrb [rN,#1]`.
- `sub_0803E3C0` (76B) — same shape, `->unk02`.

The other delta was pool-load order. Retail emits `ldr r3,=table` *before* `movs r1,#imm` / `ldsb` for the 2nd and 3rd tables. A discarded `v2 = table[index];` immediately before the real member read hoists that load; both discards are required (dropping one falls back to 67/76 or worse). `make compare` OK.

### 2026-09-21 — sweep-ranked near-miss batch: table-lookup family + sum-order fix (+4, 374→378/633)
Worked the top of a fresh `sweep_seeds.py` ranking (155 scored seeds). Four matches,
all needing `/* match-compiler: old_agbcc */`, all landed via `match_function.py` +
`integrate_c.py`; `make compare` OK after each sub-batch.

- `sub_0803DDD8` / `sub_0803DDB0` (40B each, were 34/40) — the 85% twins from the
  ranking. Winning shape: `u8 *tbl = <symbol>;` as a **local**, then
  `u32 *row = (u32 *)(tbl + (a - 1) * 4);` and the dereference left **inline** as
  `*row`. The local is what keeps `subs r0,#1` / `lsls r2,r0,#2` unfolded instead of
  the `lsls #4` fold; the inline deref is what makes old_agbcc hoist `ldr r1,=tbl`
  above the decrement. Cracked one, the twin followed with a table swap.
- `sub_0803DD88` (40B, was 30/40) — same family, 40-byte stride, value return:
  `off = gMainWorkPtr->unk1818 * 4 + a * 40;` must be a **separate** local
  (`ldrb r1,[r1]` + `lsls r2,r1,#2` index handling). This is the clean replacement
  for the parked `register asm` version.
- `sub_08061800` (76B, was 71/76) — `off = arg0 * stride + 0x06000000;` as its own
  local. Accumulation order is the whole delta: retail forms `arg0*stride + 0x06000000`
  first and adds `lo` last; left-associating in one expression accumulates
  `lo + arg0*stride` first.

Negative results banked (each with a new `src/wip/<fn>.md` write-up and a
`docs/decomp-queue.toml` status, so they are not re-attempted):

- `sub_08033158` — 45/46. The permuter's `if (b || sign) r = b; else r = b;` shape
  settles the tail compare on `b`; the last 2 bytes are **jump threading**: retail
  redirects the loop-exit `beq` past the dead `r = b` copy straight to `movs r2,#1`,
  agbcc targets the block entry. 8 tail rewrites (plain form, `!b`, if/else, `for`,
  ternary, braces) floor at 44–45/46.
- `sub_08073988` — 94/96, unchanged after 12 more `default_char` shapes; `old_agbcc`
  is worse (90/96). The pool load destination (retail r0, agbcc r2) is an allocator
  heuristic. Confirms the note already in this log.
- `sub_0802C2B0` — 92/100 after 9 more variants over the tail sum order and prologue
  pointer plumbing. Two 2-byte deltas remain: `mov r12,r1` scheduling and an
  `adds r1,r0,r1` / `adds r1,r1,r0` Rn/Rm swap that GCC canonicalises, so writing
  `off + base` does not flip it.
- `sub_08069F00` — 11/24. 13 shapes (2- and 3-deep copy chains, `u32` copy, operator
  variants on the sign test, split assignment) are **all byte-identical**: agbcc's
  copy coalescing always removes retail's `adds r1,r0,#0`. Reinforces the
  un-coalesced-load finding already documented above.

`script_first.py` permuter runs (120s × 8 jobs each) over the same queue: `sub_0803DCFC`
best 30/48, `sub_08061C48` best 10/56, `sub_08061DC0` best 40/72 — no score 0, so each
is parked rather than parked-and-retried. `sub_08043B90` went *backwards* under the
randomizing permuter (67/76 seed → best 200); its queue entry now says not to re-run a
randomizing permuter on that seed.

### 2026-09-21 — `data_symbols.s` addressing sweep (+3, 371→374/633)
The breakthrough this batch: **when retail's two pool words are 0x20 apart, plain
literals make agbcc collapse the second into `subs r0, #0x20`.** Switching the address to
a symbol from `asm/data_symbols.s` (see `include/data_symbols.h`) stops the folding and
also changes register colouring. Two of the three matches below needed it.
- `sub_080617C4` (60B) — register the object with the engine: `a`/`b` into
  `gUnk_03000798->unk88/unk8C`, `a->unk04`/`unk05` into `unkA0`/`unkA2`, then
  `unk9C = unkA0 >> 2` (read **back** from the field, not from a local).
- `sub_08071F44` (64B) — scan `*gData_030040C4` records of 0x28 bytes at
  `*gData_030040E4`. Requires **both** `i != -1` (retail materialises -1 once and compares
  a register at both the entry guard and the back edge; `i >= 0` gives 18/64) **and** the
  two `gData_` symbols (0x030040C4 is 0x20 below 0x030040E4; literals give a 60-byte
  `subs r0, #0x20` version).
- `sub_0802C62C` (64B) — count entries of `gMainWorkPtr->unk1694` whose signed +3 byte
  equals the argument. `val = (s8)a;` must be initialised **before** `count = 0;`: with
  `s32 count = 0;` declared/initialised first the `movs r3,#0` lands ahead of the argument
  truncation (59/64).
- Re-parked with much stronger seeds (same technique):
  `sub_08061C48` 36/56 → **52/56** (only `ldr r5` vs `lsls` scheduling swapped at +0x0e),
  `sub_08043B90` 67/76 (struct-field form; tail return must reuse r0 == 0 — note symbols
  make it *worse*, 14/76, because retail synthesises 0x16E0 with `movs #0xB7 << 5`),
  `sub_08043B58` 38/54 (`ldm r3!,{r1}` vs `adds/ldr` and key/table register swap),
  `sub_080739E8` 11/36 (rotated bottom test with a separate entry guard that agbcc merges).
- New symbol added: `gData_08096794` (the pointer array walked by `sub_08043B58`).
- Swept **every** `src/wip` seed for symbol-able literals. Only three improved further:
  `sub_0803E2AC` 70/124 → 106/124, `sub_08061D00` 27/104 → 41/104,
  `sub_0803E374`/`sub_0803E3C0` 41/76 → 43/76. (Most of the 0x080BB8xx-family seeds
  store raw addresses in `u32` locals, so the symbol form trips
  `-Werror=pointer-to-int`; they need rewriting before the trick applies.)
- `sub_080620D4` (72B) parked at 37/72: retail walks the `a->unk0C` pointer array with
  **two** registers (base r5 for the once-only snapshot, walker r3), so the source needs
  `for (i = 0, q = p; ...; i++, q++)`; plain `p[i]` makes agbcc unswitch the `i == 0` arm
  and hoist the `p[0] == 0` test (11/72).
- Removed three stale `src/wip` duplicates of already-matched functions
  (`sub_0803E848`, `sub_0804A438`, `sub_08062A74`).

### 2026-09-21 — permuter + inline-literal sweep (+6, 365→371/633)
- `sub_08031294` (28B) — flags/word init. The two ORs must be written **inline** with an
  explicit `(u8)` cast (`a->unk00 = (s8)((u8)a->unk00 | 0xFF);`); a `u8 m = 0xFF;` local
  makes agbcc emit the `ldrb`/`orrs` pair in the opposite register order (5/28) and adds
  a stack frame.
- `sub_08042B78` — matched by `permuter/auto.py` (base seed scored 0), integrated by the
  permuter itself.
- Parked with shape analyses: `sub_08062D50` (12/46 — retail keeps the 0x05000000 base in
  r5 from the first instruction, agbcc materialises it at the store), `sub_0806D748`
  (retail pushes r4/r5/r6 and truncates the unused 4th arg; agbcc keeps `a` in r2 and
  drops the truncation), `sub_0803DD8x` family, `sub_08069F00`, `sub_08073114`.

### 2026-09-21 — tiny-function sweep: local-initialisation order wins (+5, 365→370/633)
- `sub_08035908` (36B) — the loop must be `if (e != 0) { while (...) }`, not an
  early `if (e == 0) return 1;` (that flips the entry branch layout and floors at 18/36).
- `sub_08065E0C` (92B) — keyed tile-blit wrapper: the two helpers and the callee take
  the record's **first word** (`p->unk00`), not the record pointer; returning the
  pointer keeps retail's high-register live ranges.
- `sub_08062728` (18B) — word-array clear. The zero must be a real local, initialised
  **after** `i` but **before** the count/pointer (`u32 i = 0; u32 z = 0; ... *p++ = z;`).
  Inline `*p++ = 0` puts the `movs r3,#0` after the two loads (13/18); zero declared
  first swaps the two `movs` (16/18).
- `sub_08033F30` (24B) — if/else **polarity is observable**: retail's `blt` jumps over
  the `movs r0,#0` into the 0x800 block, so the non-negative arm must be the inline one.
  Also added `union Unk33F30Unk1C` (+0x1C is written as a byte here, read as an inner
  pointer by `sub_08033D90`).
- `sub_08034894` (84B) — plain `if`/`else` with the three stores spelled out in both
  arms; factoring the shared store through a temporary floors at 75/84.
- **New rule of thumb: retry the obvious source shape (and its local-initialisation
  order) before reaching for the permuter.** Four of these five were found that way.
- Parked with shape analyses: `sub_08073114` (18/112, table pseudo wants r1),
  `sub_08069F00` (11/24, missing `adds r1,r0,#0` copy), and the `sub_0803DD8x` family
  (`sub_0803DD88` 30/40, `sub_0803DDB0`/`sub_0803DDD8` 27/40 — register/schedule only).

### 2026-09-21 — natural-C form beats permuter-mangled seeds (+1, 365→366/633)
- `sub_08034894` (84B) — matched with **plain `if`/`else`** (`old_agbcc`). The parked
  seed scored only 75/84 because it factored the shared trailing store through a
  temporary; spelling the three stores out in *both* arms is what retail wants.
  **Rule of thumb: when a hand/permtuer-mangled seed stalls, retry the obvious
  source shape before reaching for the permuter.**
- New declarations added for it and for `sub_08067FC8`:
  `struct Unk680CCRec` grew `unk04` (u16 element count) + `unk06`, and
  `s32 sub_08067F3C(void *a, u32 v);` was declared.
- `sub_08067FC8` parked at 43/74 (same size): retail sets `total = 0` *before* the
  `sub_08067F98` call and the rotated entry check compares the accumulator's known
  zero; hoisting that initialiser in C costs 17 bytes of accuracy.
- Also parked/annotated: `sub_08042784` (35/100 — retail keeps the ring pointer in
  r12, no source shape reaches that), `sub_080699C8` (size mismatch — retail shares
  a 2-store tail between the BG2/BG3 cases via `adds r1,#4` folding).
- `sub_08074144` confirmed **toolchain-blocked**: the single `mov pc, lr` in the ROM
  (2 bytes); both bundled agbcc builds emit `bx lr` for an empty function, with or
  without `-mthumb-interwork`.

### 2026-09-21 — sweep tool v2 + 3 more semantic C (+3, 362→365/633)
- `sweep_seeds.py` rewritten to call `match_function.compile_and_score` directly
  (no subprocess per seed) and to *classify* each near-miss:
  - `SIGNONLY` — every differing byte is a Thumb conditional-branch condition byte
    and the pair is a signed/unsigned twin (`bcs`/`bge`, `blo`/`blt`, `bls`/`ble`,
    `bhi`/`bgt`), so the fix is a signedness change on the compared expression.
  - `branch-target` — same size, only branch offsets differ.
- **Signedness is now a pinned repair.** Three functions this batch were one
  signedness change away from retail:
  | Function | DIFF | Fix |
  |--|--|--|
  | `sub_08068988` (126B) | `bcs` where retail has `bge` (x2) | `u32 width/height` → `s32` |
  | `sub_08035020` (52B) | `blo`/`bls` where retail has `blt`/`ble` | `switch ((s32)a->unk2CC)` |
  | `sub_0806BE20` (36B) | already right shape | swap `s32 i` / `u8 *p` declaration order |
- Landed (100%, `make compare` OK):
  | Function | Bytes | How |
  |--|--|--|
  | `sub_08035020` | 52 | signed `switch` over the +0x2CC state word |
  | `sub_0806BE20` | 36 | size-prefixed entry walk; declaration order fixes the first insn |
  | `sub_08068988` | 126 | stale seed, fixed by signed clamp locals |
- **Declaration order matters.** agbcc emits locals in declaration/initialisation
  order, so reordering two declarations is a legitimate (and often sufficient) fix
  for a same-size DIFF whose first instruction is swapped.
- Permuter chain 3 (`--strict-branches`): `sub_08033158` best 1 (confirmed residual:
  `cmp r1,#0` retail vs `cmp r2,#0` agbcc), `sub_0803DDB0` best 10. Both floor.
- Parked/annotated: `sub_0802C2B0` (92/100, agbcc hoists `mov r12,r1` one insn early),
  `sub_0803DCFC` (44/48), `sub_08043B90` (67/76), `sub_08073988` (94/96 — the last
  2 bytes need the pool constant in r0 instead of r2; every declaration-order and
  assignment shape tried floors at 89/96, so the permuter should have another go),
  `sub_08062D50` / `sub_08062CF4` (leaf that nevertheless pushes r4/r5/r6 — no source
  shape found), `sub_08074144` (**blocked by toolchain**: retail is `mov pc, lr`,
  both agbcc builds emit `bx lr`; the only `mov pc, lr` in the ROM, 2 bytes).

### 2026-09-21 — WIP-seed sweep tool + semantic C conversions (+3, 359→362/633)
- **New tool `tools/decomp/sweep_seeds.py`.** Scores *every* parked `src/wip/*.c`
  seed (both compilers) for functions whose linked `src/matched/<fn>.c` is still a
  naked asm block, and reports the best. Rationale: a seed can already match retail
  100% while the linked file stayed readable Thumb, so the whole queue may hide
  finished work. One run scored 159 seeds in ~4 min and found 2 such matches.
- Matched and landed (100% via `match_function.py`, `make compare` OK):
  | Function | Bytes | How |
  |--|--|--|
  | `sub_0803E848` | 160 | `sweep_seeds.py` — stale seed already matched (agbcc) |
  | `sub_08068798` | 110 | `sweep_seeds.py` — stale seed already matched (agbcc) |
  | `sub_08033C1C` | 32 | permuter chain (was 21/32 naked asm) |
- Permuter chains: `sub_08042C3C` / `sub_08062C38` / `sub_08042BB0` seeds turned out
  to score 0 on import (stale duplicates — their linked C was already semantic);
  `sub_08073988` (best 10), `sub_08061BE8` (best 60), `sub_08069894` (best 230) floor.
- **Permuter false zero identified:** `sub_08033158` reports "score 0 but no candidate
  verifies (branch-target false zero)" — run `permuter/auto.py <fn> --strict-branches`
  (scores branch targets too). Under strict scoring its best is 1, confirming the real
  residual DIFF is `cmp r1,#0` (retail) vs `cmp r2,#0` (agbcc) in the tail.
- Parked with better seeds + notes:
  | Seed | Before → after |
  |--|--|
  | `sub_08043B90` | 36/76 → **67/76** (88.2%, same size; `struct Unk43B90` added, tail `return 0` vs reuse-loaded value) |
  | `sub_0803DCFC` | unscored → **44/48** (91.7%, same size; index in r1 vs retail r2) |
  | `sub_0803DBD0` | 23/80 (same size; `-fprologue-bugfix` + distinct table symbols) |
  | `sub_080361A8` | 23/36 (union `Unk361A8Word` explains `ldrh` + word store at +0x1C) |
  | `sub_0804495C` | 34/60 (do-while form) |
  | `sub_08033F30` | 16/24 (branch layout inverted) |
  | `sub_08069F00`, `sub_08062728` | unscored → parked with diagnosis |
- Include changes: `union Unk361A8Word` (u16/u32 overlay at +0x1C), `struct Unk43B90`
  (8-byte scan entry), `gData_0807A1F4` / `gData_0833D1E0` / `gData_0833D1F4` /
  `gData_080796DC` / `gData_08097458` symbols (moved inside the header guard).

### 2026-09-21 — asm-stub → semantic C conversions (+2, 357→359/633)
- Two `src/matched/*.c` readable-Thumb stubs rewritten as semantic C (`old_agbcc`,
  both 100% via `match_function.py`, `make compare` OK):
  | Function | Bytes | How |
  |--|--|--|
  | `sub_080320CC` | 52 | 4 unrolled `gUnk_030002A0.records[i].unk0C` clamps; struct-index form reproduces retail's `adds r1,#0x90` for the 4th record |
  | `sub_080428C4` | 44 | `gMainWorkPtr->unk1808 & 0x2000` gate + two byte stores through `gUnk_03000538` (retail reloads the pointer between the two stores) |
- Re-landed cleaner semantic versions of `sub_0806FEFC` (list pop-head/push-tail through
  `gData_030040A8`/`gData_030040B8`) and `sub_08041858` (net 0 — replaced awkward prior forms).
- **New pinned technique:** two RAM addresses that differ by a small constant must go through
  *distinct* `gData_*` symbols, otherwise agbcc folds the second into `adds rX,#imm`
  (raw literals: `0x030040B8` became `0x030040A8 + 0x10`). Same trick already used by
  `sub_08041858` / `sub_08037318`.
- Parked with notes: `sub_08033158` (44/46), `sub_08036A68` (58/240), `sub_08033F30` (16/24,
  branch layout), `sub_0804495C` (34/60), `sub_0803DD88`.
- Permuter chain over the top-scoring WIP seeds: `sub_08042C3C` re-landed; `sub_08073988`
  floored at best 10.

### 2026-09-21 — register-shape batch: +6 semantic C (312→318/633), past 50% functions
- Targets were the twelve worst "matched only with GCC asm labels; stripped DIFF"
  entries in `decomp-functions.md`. Method per the fork order: `script_first.py`
  first, then a bounded local permuter per function (`build/perm_batch.sh`, 4
  concurrent × 2 jobs, `--no-integrate`, re-verified with `match_function.py`).
- **`old_agbcc` does not help this family.** Scoring all twelve with both binaries
  (`build/score_list.py`) gives identical percentages; only 2 of the 12 improve and
  none reach 100%. This is a different failure mode from the `sub_08061308` family.
- Matched (all 100% via `match_function.py`, `make compare` OK):
  | Function | Bytes | How |
  |--|--|--|
  | `sub_0806105C` | 44 | `script_first.py` cleaned-m2c pattern |
  | `sub_08062D24` | 42 | permuter: re-materialize `shifted` through a pointer local |
  | `sub_0806F430` | 48 | move the `0x10` mask materialization before the `unk14` read |
  | `sub_08045128` | 80 | permuter: pointer local keeps the shifted index live |
  | `sub_0802B994` | 58 | permuter: `&row` local stops the second table address folding |
  | `sub_080674B4` | 6 | parameterised BIOS `swi` operands (new technique, below) |
- **New pattern — BIOS `swi` with pass-through registers** (`sub_080674B4`): a
  6-byte trampoline that only zeroes `r2` before `swi 5`. `CpuSet(src, dest, 0)`
  emits `push/bl CpuSet/pop` (this repo's `gba/syscall.h` declares a real function)
  and inline `asm("movs r2,#0\n\tswi #5")` is rejected by the semantic-asm policy.
  Giving the function the register-carrying parameters and letting the operand list
  place the zero is byte-exact:
  ```c
  void sub_080674B4(const void *src, void *dest)
  {
      asm("swi 5" : : "r"(src), "r"(dest), "r"(0));
  }
  ```
  `include/unknown-functions.h` declares it with an empty parameter list so the
  existing no-argument callers keep compiling. Documented in
  `docs/decomp-patterns.md`.
- **Parked after permutation** (300 s then 900 s each, no score 0 — permuter score
  in brackets): `sub_08071B4C` (335→5), `sub_0806B3E8` (95→10), `sub_08043B58`
  (45→20), `sub_08066224` (110→55), `sub_08034A68` (130→110), `sub_08070604`
  (140→10). All stay readable Thumb with the specific residual gap recorded in
  `src/wip/*.md`.
- `src/wip/*.c` now holds the matching form for every function landed (verified
  byte-exact from the seed too), so a re-import cannot regress to the old DIFF.
- `make compare` → **OK** — 318/633 functions (50.2%), 20,144 bytes (22.3%).

### 2026-09-21 — `old_agbcc` backlog sweep: +8 semantic C (304→312/633)
- `build/dual_compiler_sweep.py` re-scored every WIP seed with both compiler
  binaries. **10 seeds** reach 100% bytes only under `old_agbcc` (2 were already
  landed last batch); the rest were parked as "blocked on register allocation".
- Integrated this batch (all with `/* match-compiler: old_agbcc */`, verified
  `match_function.py` 100%):
  | Function | Bytes | Parked DIFF |
  |--|--|--|
  | `sub_080312B0` | 40 | `ldrh` destination r0 vs r5 (had "GCC asm label" draft) |
  | `sub_08033574` | 80 | pool addend `0x3B` vs `0x3A`, r4/r5 vs retail r5/r1/r6 |
  | `sub_080353A0` | 200 | 105/200 — mask scheduling + argument registers |
  | `sub_08040088` | 56 | 41/56 — target pointer r1 vs r3, timer addr r2 vs r1 |
  | `sub_0804245C` | 140 | 133/140 — ring-location pointer r2 vs r1 |
  | `sub_080427E8` | 220 | 119/220 — MainWork in r2, ring mode in r1 |
  | `sub_08043944` | 48 | 37/48 — r3/r4 hint attempts |
  | `sub_08067F98` | 48 | "GCC asm label" draft; still register-shaped C (see caveat) |
- The shared cause is the same one found for `sub_08061308`: for this codebase's
  shapes `agbcc` coalesces a `ldrb`/`ldrh` into the register that consumes it or
  reuses a still-live address register, while `old_agbcc` reproduces retail's
  extra load. No C rephrasing reproduces that with `agbcc`.
- Cleanups applied while landing: deduplicated the doubled `#include "global.h"`
  headers four seeds carried, and replaced `sub_0804245C`'s `u8 *base/ring` mask
  hack with `gUnk_03000538->unk00 = 0x1F & ...` (still byte-exact under
  `old_agbcc`).
- Caveat: `sub_08067F98`'s matching form is register-named pseudo-C (`r0`…`r4`
  locals + `*(u16 *)` record walk) — byte-exact, but every natural
  `Unk68014Rec` walk written instead is a same-size DIFF (best 6/48 bytes), and a
  600 s bounded permuter run from the semantic seed did not reach score 0. The
  register-shaped C is what is landed; the walk needs a different source shape
  (or a newer tool) before it can be called semantic C.
- `make compare` → **OK** (312/633 semantic C, 19,866 bytes).

### 2026-09-21 — per-function compiler split: +2 semantic C (302→304/633)
- **Found the real blocker behind the `ldrb`/`lsls` family:** `pret/agbcc`'s
  `install.sh` ships **two** compilers, `tools/agbcc/bin/agbcc` and
  `tools/agbcc/bin/old_agbcc`, and they do not generate identical code. The
  parked seeds that were "unreachable in semantic C" only needed the older one.
- New per-function selector, parsed from a comment and honoured end to end:
  ```c
  // @ 0x08061308
  /* match-compiler: old_agbcc */
  ```
  `match_function.py` (`MATCH_COMPILER_RE` / `COMPILERS`) picks the binary;
  `import_function.py` writes a `compiler` sidecar because the permuter
  preprocesses `base.c` before `compile.sh` runs; `permuter/compile.sh` reads it
  and swaps `CC`. Default stays `agbcc` when the comment is absent.
- Matched **`sub_08061308`** (48/48): the `u16 tmp` baseline that was stuck at
  46/48. `old_agbcc` emits the un-coalesced `ldrb r0,[r0]; lsls r1,r0` retail
  form that a 4,000-variant `agbcc` sweep and a synthetic probe both declared
  impossible for `agbcc`.
- Matched **`sub_08062A74`** (76/76): the nested-assign form
  (`r1 = (r3 = r4 << 5)`) that `agbcc` compiles with `lsls r3` reaches retail
  under `old_agbcc` once the palette constant is written twice
  (`r2 = 0x080BB8C0; r2 = 0x080BB8C0;`) and the OBJ-PAL offset is folded into
  `r1 = (r4 << 5) + 0x05000200;`.
- Both were naked Thumb wrappers in `src/matched/`; they are now semantic C.
- `sub_08073988` (94/96) did **not** benefit: `old_agbcc` gives the same
  `base→ip / constant→r7` split, and a flag matrix, 30 register-named forms, 46
  tmp-reuse forms and 38 chain forms modelled on the matched sibling
  `sub_0806B3E8` all land at 94/96 or worse. A bounded `old_agbcc` permuter run
  is the current attempt.
- `make compare`: OK

### 2026-09-21 — semantic C +1 (299→300/633)
- Matched `sub_08061E40` with direct `Unk61E40` field stores; this preserves
  retail's zero-constant materialization order without register annotations.
- Improved the parked `sub_08062A74` seed to 74/76 through a valid source
  permutation; it remains parked because the final shift/add register pair
  still differs.
- Fixed permuter imports to prefer parked WIP C and to select newly suffixed
  work directories. Tightened address-word classification so instruction
  bytes are not misreported as pool-only differences.
- `make compare`: OK

### 2026-09-21 — semantic C rematch (+1, 298→299/633)
- Matched `sub_080726E0` (halfword-stride transfer helper). Reusing the
  object parameter for `unk04` reproduces retail's `ldrh r4` register reuse
  without fixed-register annotations.
- `make compare`: OK

### 2026-09-21 — parked near-miss rematch (+2, 296→298/633)
- Target list from `decomp-functions.md` 38–49 (12 parked same-size DIFF after the GCC-asm ban).
- Matched `sub_08062CC8` (palette RGB extract): `&shifted` so `ldr =0x05000200` sits between `lsls #24` and `lsrs #23`.
- Matched `sub_0803531C` (mask-first flags on unk2C5): dummy `ldrb` into another u32 before the last mask pins earlier `ands` operands.
- Leftovers still same-size DIFF (Thumb left in `src/matched/`): `sub_08073988` 94/96, `sub_08061308` 46/48, `sub_08061BE8` 92/96, `sub_08040F4C` 319/336, `sub_08062A74` 72/76, `sub_080442FC` 132/144, `sub_08037318` 91/100, `sub_08034A68` 91/112, `sub_08069894` 85/96.
- `make compare`: OK

### 2026-09-21 — ban `register` in semantic C
- The `register` storage class is banned the same as GCC asm labels. `match_function.py` rejects it.
- All 19 remaining semantic functions that still used `register` MATCH after dropping it (including `sub_08042BB0`).
- `make compare`: OK

### 2026-09-20 — ban GCC asm labels (363→296/633 semantic)
- `register T x asm("rN")` and empty `asm("")` are not a match. `match_function.py` now rejects them in semantic C (BIOS `swi` and naked Thumb still allowed).
- Honest rematch: `sub_080475C4` / `sub_080475F4` still MATCH as struct copies (`unk40`/`unk44` ↔ `unk1798`/`unk179C`).
- 19 functions still MATCH after dropping the labels (pins were unused).
- 67 functions only matched with labels → parked honest C in `src/wip/`, Thumb restored in `src/matched/` (including `sub_08043B58` 47/54 same-size).
- `make compare`: OK

### 2026-09-20 — semantic C more `bx lr` leaves (+15, 348→363/633)
- `/* match-flags: -fprologue-bugfix */` on remaining leaf-branch helpers.
- Matched `sub_080615EC` (clamp x/y, `unk90`/`unk92`; `u32` args so no callee `lsls/lsrs`; callers `sub_08052934` / `sub_0804ED90` still MATCH).
- Matched `sub_080617C4` (mask-first AND 1 on `unk0C`, fill `Unk0798` slots).
- Matched `sub_0802D8C4` (`u16` into `unk08->unk18` if non-NULL).
- Matched null-check stores `sub_08061BDC`, `sub_08061E40` (`*(u16 *)&field` for zeroed `r0`), `sub_08062634`, `sub_08062684`.
- Matched `sub_08033958`, `sub_0806DEF4`, `sub_0806AC68`.
- Matched BG I/O switches `sub_08069908` / `sub_08069948` / `sub_08069988` (copy to `r1`, `==1` / `(s32)>1` / `==0` gotos).
- Matched `sub_0806FEFC` / `sub_0806FF28` (list splice; `+r` so tail is not `head+0x10`; head loc in `r1` on the push-to-head path).
- `sub_080699C8` still DIFF (76 vs 80).
- `make compare`: OK

### 2026-09-20 — semantic C leaf `-fprologue-bugfix` family (+5, 343→348/633)
- Matched `sub_08043B58` (NULL-terminated `Unk447CC *` table at `0x08096794`). Key in `r2`; `r1 = *table`; cursor `r3`; `r1 = *r3++` is `ldm`. Same `/* match-flags: -fprologue-bugfix */` as `sub_0802B994`.
- Matched `sub_0803DBD0` (ROM table `0x080796DC` with `sub_0803DD88` index math, fallback `0x08097458[unk1818]`). `goto done` over the mid-function pool; `+r` on each table base.
- Matched `sub_0804495C` (32 halfwords from `0x08094E00[unk181F]` to PLTT `0x050001C0`). Table pointer `+r` before `unk181F`; `do { … n--; } while (n >= 0)`.
- Matched `sub_080475C4` / `sub_080475F4` (copy `unk40`/`unk44` ↔ `unk1798`/`unk179C`). Addend in `r0`, then `dst = base + r0`.
- `make compare`: OK

### 2026-09-20 — semantic C sub_0802B994 (+1, 342→343/633)
- Matched `sub_0802B994` (Unk7709C `{key,value}` ROM table at `0x0807709C`, keyed on `gMainWorkPtr->unk1690->unk00`). Dual-cursor walk (`r2` table, `r1 = &unk04`, `r1 += 2` / `table++`) with a shared `goto done` epilogue. `/* match-flags: -fprologue-bugfix */` drops the extra `push {lr}` / `pop {r1}; bx r1` so the leaf stays `bx lr` (58/58). Do not add that flag globally. Minimal null-check store leaves still extra-push.
- `make compare`: OK

### 2026-09-20 — semantic C six parked near-misses (+6, 336→342/633)
- Matched `sub_08042540` (AND ring flag 2, store 0x40, copy ring slots). Clone of `sub_080425B8`: `addr = &unk0479; mask = 2; value = *addr; mask &= value` so `movs r0,#2` precedes `ldrb`.
- Matched `sub_08033084` (palette fade blit). `u32 flag`, `dst = a`, then `flag <<= 24` (low-byte test, no `lsrs`). Clamp is `0x800` (`movs #0x80; lsls #4`), not `0x8000`. Reload `*loc` on the `<=0` path.
- Matched `sub_08061BE8` (blit last Unk0770 slot). `+r` so the table literal loads before `lsls #3`; `entry = n + table`; loc in r4 for the post-call reload; VRAM base `0xC0 << 19`.
- Matched `sub_0803E328` (signed ROM table blend). `ldr table1` plus `+r` before `unk1E`; `entry = index + table`; next table literal immediately; `value = table3[i] + value` for `adds r0, r1, r0`. Same shape should unlock `sub_0803E374` / `sub_0803E3C0`.
- Matched `sub_08066224` (select Unk66224 entry). `unk04` before `unk28`; `movs #1; ldrh flags; ands`. Changed `sub_08072F94` return from `u8` to `u32` so the caller does `lsls r0, r0, #2` without zero-extend (callee still MATCH).
- Matched `sub_08052934` (menu table `0x080995AC+0xC`). Copy arg, then `(u8)<<4`; `+r` split `ldr base; adds #0xC`; set up `gMainWorkPtr+0x1818` before `ldr r1, [r4]`.
- Parked: `sub_08034420` 76/328 (prologue matches); `sub_08032DC4` 418/660; `sub_08035984` 232/348; `sub_08032908` 235/384. `sub_0802B994` still blocked (`bx lr` leaf).
- `make compare`: OK

### 2026-09-20 — semantic C ten parked/blocked near-misses (+10, 326→336/633)
- Matched `sub_08045128` (copy `unk1688[idx].unk08` to `unk1788`, `sub_08045590`). Follow retail’s shift/sub chain for `idx*0x18` and `idx*0x1F60`; keep `gMainWorkPtr` in `r3`.
- Matched `sub_08067F98` (variable-stride key search). `u32` key so `lsls/lsrs` land in `r3`; clobber `a` with `ldrh r0, [r0, #0x28]`; `r2 = r4 + r2` for the stride add.
- Matched `sub_0806B3E8` (string → `Unk6B3E8Item`). Char lives in `r1`; `r0 = ch + 0x080BB748`; fill tail with `r0 = count; count--; if (r0 == 0)`.
- Matched `sub_0807179C` (swap two node chains). Both `i++` and `count--` then `cmp count, i`; `unk18` is `u16`.
- Matched `sub_08062A74` (OBJ palette slot). `u32` arg so `adds r5, r1` precedes the `u8` extend; keep `&gUnk_030008D0` in `r6`.
- Matched `sub_0802E048` (init `Unk026C` overlay records). Flag is `0x80 << 7` (`0x4000`), not `0x80000000`; keep `&gUnk_0300026C` in `r4`; `movs+lsls` for the 0x3B00/0x4B00/… constants.
- Matched `sub_08047624` (snap x/y to 8px). Cases 0–2 share `r0 = count; asm("+r"); goto done` so the branch skips case 3.
- Matched `sub_08071BA0` (sound DMA1 + timers). Walk `0x04000084` with `+r` barriers so stores stay `str; adds #4`, not `stmia`; reuse `r2 = 0x10000` for the last subtract.
- Matched `sub_08040F4C` (0x328-byte state loop). `done` in `r5`; blend case 1 compares `lsls #16` without `asrs`; modes 0 and 2 share the handler load.
- Matched `sub_080442FC` (optional key lookup + `sub_08043C70`). Use parameter `a` across calls (no `obj = a` / `r5` pin); `ldrb r3, [r0]` for `unk181B`; `r0 = 0x08091208` then `r1 += r0`.
- `sub_0802B994` still blocked: `bx lr` leaf, extra `push {lr}`, pool in the middle of the loop.
- `make compare`: OK

### 2026-09-20 — semantic C four parked/blocked near-misses (+4, 322→326/633)
- Matched `sub_08031300` (Unk312EC countdown). Pin `a` to `r2`; `n = n - 1` in `r3`; `ldsb` toggle of `unk00`/`unk01`.
- Matched `sub_080523A4` (init six `Unk2F520` slots). `r3 = 0x2D5` plus `+r` barrier so `adds r2, r4, r3` precedes `ldsb`; reuse `r3` as `0x2C00`.
- Matched `sub_08037430` (battle overlay blit). Do **not** `register asm("r7")` — that skips `push {r7}` while still using `r7`. Leave `first` unpinned. `if (count <= 3) goto` keeps `bls`; reload `*count_ptr` on that path; table `0x08096ECC` in `r1` before the index.
- Matched `sub_0806A3A4` (arena node from `0x03000B30`). Same IWRAM barrier for `0x03000B3C`/`0x03000B38`; evaluate `*current` into `r3` after `r0`/`r1`/`r2` and before stack args. Same shape should unlock `sub_0806A314`.
- `sub_0802B994` still blocked: dual-cursor ROM table is right, but any C loop adds `push {lr}` on a `bx lr` leaf (64 vs 58).
- `make compare`: OK

### 2026-09-20 — semantic C six parked near-misses (+6, 316→322/633)
- Matched `sub_08042B28` / `sub_08042B50` (lazy ROM pointer tables). `r0 = table; asm("" : "+r"(r0)); r1 = idx << 2; r4 = r1 + r0` loads the base before the shift.
- Matched `sub_08071B4C` (sound IO reset + `_08073C4C`). Walk `0x04000084` by add/sub, then the `41858` IWRAM barrier so `gUnk_0300410C` is a separate literal from `gUnk_030040DC` (0x30 apart).
- Matched `sub_0803531C` (dispatch three `Unk68574` blocks from `unk2C5`). `u32` mask in `r0` then flags in `r1`, `r0 &= r1`; last test does `ldrb r5, [r5]`.
- Matched `sub_08042390` (quadrant 0–3 from `py/y` and `px/x` with a 0xB threshold). `if (py >= y) goto …` plus return labels in retail fallthrough order (`ret3` then `ret1`/`ret2`/`ret0`) keeps `bge`/`ble`.
- Matched `sub_08043B90` (walk `unk16E0` vs `unk16C8`). `while ((r0 = p->unk00) != 0)` with `r0` pinned, body reloads `p->unk00` for the call, `return (s32)r0` avoids extra `movs r0, #0`.
- Same IWRAM barrier may unblock `sub_08071F44` / `sub_08071E84` / `sub_080473F8`.
- `make compare`: OK

### 2026-09-20 — semantic C five parked near-misses (+5, 311→316/633)
- Matched `sub_08033978` (bind two `Unk346C0` into `Unk33A5C`). `asm("" : "+r"(r1))` after loading `0x08078158` emits `ldr r1` before `lsls r0,r6,#2`; `-1` via `r1 = 1; r1 = -r1` then `r8`.
- Matched `sub_08073988` (string-width parser). Goto-shaped control flow; `r0 = ch + table` (not `table + ch`) for `adds r0, r1, r0`.
- Matched `sub_08069894` / `sub_08041858` (IWRAM store pairs). `asm("" : "+r"(r0), "+r"(r1) : : "memory")` then a fresh pool `ldr` stops agbcc folding `0x1B0`/`0x504` as `add/sub #imm`.
- Matched `sub_08037318` (Unk002A0 record by stride `0x2C`). Same `+r` barrier so `ldr r1,=0x030002A0` precedes `movs r0,#0x2C`.
- `Unk33A5C` gained `unk0D`. Same pool-fold barrier may unblock `sub_080473F8` / `sub_08052934`.
- `make compare`: OK

### 2026-09-20 — semantic C sub_0804109C + sub_0802D6D4 (+2, 309→311/633)
- Matched `sub_0804109C` (copy Unk4109CInput into Unk40F4C, then blend-flag setup). Extra `a = a_arg` locals swapped the `r2`/`r3` copies; typed parameters plus `&= ~0x20` (agbcc `movs #0x21; negs`) matched 336/336.
- Matched `sub_0802D6D4` (allocate/init Unk026C sprite slots). Direct `gUnk_0300026C->field` stores at the tail reloaded the pointer; one `w = gUnk_0300026C` local kept it across unk00/unk4C/unk04/unk48.
- Prototype: `void sub_0804109C(struct Unk40F4C *, struct Unk4109CInput *)`. Cast at `sub_080632F8` call site (`Unk632F8` overlay).
- `make compare`: OK

### 2026-09-20 — semantic C cleanup: +1 (275→276/633)
- Matched `sub_08042718` (snapshot and reset the MainWork movement
  vectors, then clear the transient object); verified 108/108 bytes and
  integrated it.
- Modeled the object anchor at MainWork `+0x448` while preserving the
  existing neighboring fields and offsets.
- `sub_0803DCFC`, `sub_0803E328`, `sub_0803E374`, `sub_0803E3C0`, and
  `sub_08040EF4` remain parked after clone-shape and register-allocation
  attempts.
- The follow-on lookup sweep parked `sub_08042B28`, `sub_08042B50`,
  `sub_08042B78`, `sub_08042BB0`, `sub_08042BE8`, `sub_08042C3C`,
  `sub_08042F4C`, and `sub_08043B90`; the best near-match is
  `sub_08042C3C` at 54/56 bytes.
- `make compare`: OK

### 2026-09-20 — semantic C cleanup: +1 (274→275/633)
- Matched `sub_0803D4C4` (process the 48 BattleWork entries at
  `0x0BCC`, reclaiming entries whose signed counter exceeds `0xA000`);
  verified 88/88 bytes and integrated it.
- Extended the shared `Unk62634` record to its `+0x28` signed threshold
  field and modeled the BattleWork record array without changing offsets.
- `sub_08033574`, `sub_08046278`, and `sub_08038580` remain parked after
  focused register-allocation attempts.
- `make compare`: OK

### 2026-09-20 — WIP near-match cleanup: +2 semantic C (272→274/633)
- Matched `sub_080726E0` (halfword-stride transfer helper). An explicit
  `r4`-pinned offset reproduces retail's final register reuse; verified
  52/52 bytes and integrated it.
- Matched `sub_08044F64` (scan three consecutive table entries). Pinning the
  multiplied product to `r0` and ordering the end calculation before the loop
  copy reproduces the retail multiply/copy sequence; verified 74/74 bytes.
- `sub_08033084` reached 63/100 but remains parked; `sub_08041858` stayed
  47/52 after a direct-store attempt.
- `make compare`: OK

### 2026-09-20 — WIP near-match cleanup: +1 semantic C (271→272/633)
- Matched `sub_08070604` (initialize `Unk70604` projectile state and derive
  the trailing byte). An `r1`-pinned value plus explicit `val += 4` ordering
  reproduced the retail tail; verified 92/92 bytes and integrated it.
- Removed its WIP and block entries.
- `make compare`: OK

### 2026-09-20 — WIP near-match cleanup: +1 semantic C (270→271/633)
- Matched `sub_08033878` (reset five `BattleWork` state fields and release/
  clear four transient entries). A shared loop/zero local was the source
  shape found by decomp-permuter; verified 108/108 bytes and integrated it.
- Restored `BattleWork.unk0B70`, which retail clears between `unk0B6C` and
  `unk0B78`.
- `sub_0802BC14`, `sub_0802BF04`, `sub_080385DC`, `sub_08069B78`, and
  `sub_0802D2C0` remain parked after targeted attempts; no matched-file
  changes for those functions.
- `make compare`: OK

### 2026-09-20 — WIP near-match cleanup: +1 semantic C (268→269/633)
- Matched `sub_080312B0` (initialize `Unk312EC` from `Unk705DC` metadata).
  Explicit `r5`/`r0` register locals preserve the retail halfword-load and
  shifted-nibble allocation; `match_function.py` verified 40/40 bytes.
- Removed the completed WIP entry and refreshed the queue.
- `make compare`: OK

### 2026-09-20 — WIP near-match cleanup: +1 semantic C (269→270/633)
- Matched `sub_08033DD4` (IWRAM target-state gate for effect processing),
  restoring `Unk0380Target` and its pointer field. A function-pointer cast
  preserves the raw `u8` callee return in the truthiness branch; verified
  104/104 bytes.
- `sub_08041858` remained 47/52 after volatile/r0-pinned variants and a
  short permuter run; `sub_08043944` reached 37/48 after r3/r4 hints but
  still has normalization-order drift. Both remain parked as WIP.
- `make compare`: OK

### 2026-09-20 — near-match follow-up (2 WIPs retained)
- `sub_08031300`: roughly 10,000 decomp-permuter iterations reached best
  permuter score 1295 without a zero-score candidate.
- `sub_080726E0`: the documented `r4` register hint and a short permuter run
  did not improve the existing 50/52 score. Both remain readable Thumb with
  their WIP seeds intact.
- `make compare`: OK

### 2026-09-20 — semantic C session: +6 matched (257→263/633), 4 near-misses parked
- **Matched (6):** `sub_0802D52C`, `sub_08043638`, `sub_08059AE0`, `sub_08059B74`,
  `sub_08059BD8` (freelist-node family sharing new `struct Unk59AE0Src` /
  `struct Unk59AE0Node` types at `gUnk_03000730`), plus earlier session
  asm-wrapper integrations already committed. All verified MATCH via
  `match_function.py` and integrated; `make compare` OK after every batch.
- **New types:** `struct Unk59AE0Src`, `struct Unk59AE0Node` (0x3C freelist
  node, `unk28` retyped to `struct Unk59AE0Src *`); `struct Unk0380Target`
  (parked, see below); narrowed several `MainWork`/`BattleWork` filler spans
  (`unk036C`, `unk039D`, `unk1810`, `BattleWork.unk0B54[4]`/`unk0B64..0B78`);
  `gUnk_0554.unk01` promoted from filler.
- **Parked as WIP (`src/wip/`, not reverted — see notes there):**
  - `sub_0802D2C0` — 92/108 bytes; agbcc DCEs a reachable-but-redundant
    `else if` branch retail keeps. Table-lookup logic itself is correct.
  - `sub_0802E048` — 188/228 bytes (82.5%); r4/r5 register role swap vs
    retail, resistant to declaration-order / caching changes.
  - `sub_08033DD4` — 93/104 bytes (89.4%); one stray `lsls r0,r0,#24` on a
    `u8`-return truthiness test. Needs `struct Unk0380Target` type re-added.
  - `sub_080338F0` — 20/104 bytes (19.2%); real structural bug (table
    indexing) flagged in the parked draft, needs a rewrite not a tweak.
  - `sub_08033878` — 28/108 bytes (25.9%); BattleWork field-write CSE
    ordering doesn't match retail's persistent-register pattern.
- **Bytes:** 12,372/90,272 (13.7%, +578 from session start).
- **Next:** resume any of the 5 parked WIPs (`make queue` → Resume (WIP)),
  or continue `classify_semantic_targets.py --bucket large`.

### 2026-09-20 — park/resume process (`src/wip/`); first seed `sub_08046278`
- **Process change:** unmatched C is no longer discarded. Drafts go in `src/wip/` with a process log; `src/matched/` stays MATCH-clean. Index via `[[wip]]` in `decomp-queue.toml` (`make queue` → **Resume (WIP)**). Helper: `tools/decomp/park_wip.py`. Policy: `docs/decomp-wip.md`.
- **Parked `sub_08046278`:** both `MainWork.unk16B0[2]` slots → `{0,-1,-1}`. Sibling `sub_08046230` already MATCH. Seed scores **11/92** (56B vs 92B). Resume from `src/wip/sub_08046278.md`.
- No ROM change; `make compare` untouched this step.

### 2026-09-20 — deep permuter search on 6 near-miss candidates (0 landed, 246/633 unchanged)
- Investigated the 12 flagged near-miss candidates; deprioritized `sub_0802B994` and `sub_0802C2B0` after finding prior/fresh permuter base scores of 2055+ (not simple register-order quirks — real structural mismatches), and `sub_08046278`/`sub_0806F910` after m2c failed and manual C reconstruction couldn't reach the retail register-spill shape (extra live r8/r9 across a leaf with no calls) even with correct logic.
- Ran full-budget (~15-18 min wall clock, `-j2`–`-j4`, `--stop-on-zero`) decomp-permuter searches on the 4 genuinely clean near-misses (base score exactly 100 or a 78-79% same-size DIFF, correct logic, differing only in agbcc's register/instruction-order choice):
  - `sub_08062D50` (RGB15 pack → 0xA0<<19 VRAM slot): base 78.3% (36/46 bytes), plateaued at score 120 across ~47,000 iterations across two runs (default + weighted `perm_temp_for_expr`/`perm_reorder_stmts`/`perm_duplicate_assignment` passes). Manual reconstruction (12+ hand variants: mask as separate var, `register asm("r3")` pin, split-statement forms, 3-temp forms) reproduced the 78% shape repeatedly but never the retail `push {r4,r5,r6,lr}` 3-register spill from a 2-register-sufficient algorithm.
  - `sub_08062CF4` (same pack, fixed `0x05000200` OBJ palette base): base 79.2% (38/48 bytes) via `match_function.py` (real headers), plateaued at score 120 across ~48,000 iterations. Note: an isolated typedef-only test compile (matching the permuter's stripped base.c) misleadingly showed a byte-exact match — real `global.h` headers change codegen enough that only `match_function.py`'s output is trustworthy.
  - `sub_0802C55C` (Unk1694 slot match-and-flag, single `bl` to `sub_0803E0CC`): base 100, ran 129,548 iterations, never improved.
  - `sub_0802E2F8` (ROM table `0x08077AC0` linear scan + `_080740B0` tail-call proportional-damage calc): base 100, ran 80,702 iterations, never improved.
- Also explored adding a `struct Unk08D0Table` type to unlock `sub_08062B9C` (bitmask+word-array clear loop at `*gUnk_030008D0`, base 100) but the macro promotion broke the existing verified match on `sub_08062AC0`; reverted cleanly before touching headers permanently.
- **Conclusion, consistent with 4 prior sessions' notes in this log**: this batch of near-misses is the documented agbcc leaf-function register-allocation/extra-push quirk, and it is resistant to both hand C rephrasing and decomp-permuter's randomization passes at real (tens-of-thousands-of-iterations) search depth — not just short 3-5 min runs. No functions integrated, no partial/broken state left in `src/matched/` or `include/`.
- `make compare`: OK (unchanged, verified before and after)
- Decompiled C: 246/633 (38.9%) — unchanged

### 2026-09-19 — semantic C +3 (239→242/633); Unk0798 CpuFill helpers + affine register store
- Matched `sub_08060D28` and `sub_08061308` (both `_08073C4C` CpuFill-style calls building dest from `gUnk_03000798`'s `unk5D`/`unk94` fields, via `*0x080BB8BC`) — needed a `register u32 tmp asm("r0")` pin per field load to steer agbcc's register choice to match retail's `ldrb r0`/`ldrh r0` then shift-into-r1/r2 pattern; a plain local variable picked the wrong register.
- Matched `sub_08069A18` (write 4 halfwords to one of two affine I/O register blocks selected by an enum-like `u8` arg) — first `if`/`else if` shape 51/72 (retail uses `beq`/`beq`/`b` positive branches, not `bne`-invert-and-skip); switching to an explicit `switch` statement landed 72/72 exactly.
- Near-miss, reverted (no partial state left): `sub_08061BE8` (74/96, `Unk0770` slot pop + `_08073C4C` — pool-load ordering and a `*(void**)slot->unk00` extra deref close but not exact), `sub_08061DC0`/`sub_08061D68` (BGR pack helpers, same-size DIFF, register-choice only), `sub_08062A74` (88.2%, flag-bitmap set + `_08073C4C` + table store, one register off), `sub_08068020`/`sub_08066BF0` (table-walk helpers, same-size DIFF), `sub_08069894` (90.6%, three back-to-back IWRAM byte stores 0x108/0x1A8/0x1B0 — agbcc folds two via `adds`-from-cached-address when retail doesn't; no C rephrasing tried stopped the fold).
- `make compare`: OK
- Decompiled C: 239 → 242/633 (37.8% → 38.2%)

### 2026-09-19 — semantic C +2 (231→233/633); Unk705DC list walk + Unk047C init
- Matched `sub_080712CC` (walk `Unk712CC.unk14` linked `Unk705DC` list `unk1C-1` times, `sub_080705A4` each node, store flag at `unk0E`). First shape was 53/56 same-size (`ldr r0,[r7,#0x1C]; sub r4,r0,#1`). Split to `n = a->unk1C; n = n - 1;` → 56/56. Added `Unk705DC.unk04` next-pointer; re-verified `sub_080705A4` / `sub_080705DC` / `sub_08034788` still MATCH. Also split `Unk62044.unk10`/`unk14` (re-verified `sub_08062044` / `sub_0806209C`).
- Matched `sub_080405A8` (zero `Unk047C.unk80C`/`unk808`, fill `unk00[0..0x1FF]` with `-1`, reload `*gUnk_0300047CLoc` each store). Added `gUnk_0300047CLoc`. Pin `r3` as the IWRAM address, copy to `r4` after the head stores; `unk808` is `adds r0, r0, r1` with `r1=0x808` then store through `unk00[0]`.
- Near-miss (readable Thumb kept): `sub_08042B28`/`sub_08042B50` 36/40 same-size (`lsl` before `ldr` of the ROM table vs retail `ldr` then `lsl`); `sub_080620D4` 64/72 leaf uses `r7` without `push {r7}`; `sub_08071F44` mid-function IWRAM pool; `sub_0806D748` unused `u16` r3 DCE + epilogue `u8` truncate; `sub_0806F1A0` packed `i++` via `+0x10000` in-loop is close; `sub_08073568` true proto is 3-arg (`dest, n, size`).
- `make compare`: OK
- Decompiled C: 231 → 233/633 (36.5% → 36.8%)

### 2026-09-19 — semantic C +4 (227→231/633); per-function score ledger
- Matched `sub_08061C48` (pop one `Unk0770` slot at `gUnk_03000794`/`gUnk_03000770`, free via `sub_0806A434`) — needed `tmp[]` + `r4`/`r5` pool pin, same trick as `sub_08033C1C`.
- Matched `sub_0806209C` (walk `Unk62044.unk0C[0..0x7F]`, `sub_0806FE84` each non-NULL then clear; typed `unk0C` as `void **`; re-verified `sub_08062044` still MATCH).
- Matched `sub_08073A28` (insert a byte into a string, shifting the tail) — first shape was 60/66 same-size; matching retail's `do { s[i+1]=s[i]; } while (i >= n)` plus the `(u16)(n-1)` truncation landed 66/66.
- Matched `sub_080618A8` (`Unk618A8` init, 6 halfwords + flags, two stack `u16` args) on the first real attempt once store order followed the disasm.
- Easy-win miss: smallest no-`push` helpers (`sub_08033958`, `sub_0806DEF4`, `sub_0806AC68`, …) are the documented agbcc-extra-`push {lr}` leaf-branch class (+4B). Prefer already-framed functions next.
- New ledger: [`decomp-functions.md`](decomp-functions.md) lists all 633 with completion % and `N/M` bytes. Status **matched** vs **byte-identical DIFF** (same size, only pool/reloc words differ — not counted as decompiled). `match_function.py --record` updates scores.
- `make compare`: OK
- Decompiled C: 227 → 231/633 (35.9% → 36.5%)

### 2026-09-19 — semantic C sub_08073218 (+1, 226→227/633); permuter batch running
- Matched `sub_08073218` (bounded string copy `src`→`dst` up to `n` bytes, zero-pads `dst[n-1]` on overflow, returns copied length) — took 4 iterations: first attempt had `src`/`dst` params swapped (re-read the disasm's `strb`/`ldrb` operand order to fix), second needed the branch *and* condition-polarity both flipped to match retail's physical block order, third needed `n`/`i` retyped `u32` (not `s32`) since retail's bounds check is `bcs`/unsigned, not `bge`/signed.
- Tried `sub_08031300` (`Unk312EC` counter/callback dispatch) and `sub_08069988` (4-way hardware-register-address switch) — both reverted; the switch-style one hit the already-documented agbcc-leaf-push wall again, `sub_08031300` got to a 2-byte gap (missing explicit `u8` truncation on a ternary) before running out of shape variations that helped.
- `sub_08071E04` (struct-init + ROM-table clamp-and-index) also near-missed and was hform-imported into the permuter batch (see below) — left its header prototype exactly as it was (2 params) since the correct 3-param signature isn't verified yet and touches a naked-asm caller.
- 9 near-miss functions now running through decomp-permuter in the background (added `sub_08071E04` to the 8 from the prior entry).
- `make compare`: OK
- Decompiled C: 226 → 227/633 (35.7% → 35.9%)

### 2026-09-19 — semantic C sub_08038D10 + sub_0803E1F4 (+2, 224→226/633); 8 near-misses handed to the permuter
- Matched `sub_08038D10` (dispatches `BattleWork.unk023C[4]` slots to `sub_08070AD4`/`sub_08070678` based on a shared ROM/RAM table `gUnk_030003E0[a->unk2FC+i]`) — new `struct Unk7069C unk023C[4]` field carved into `BattleWork` right where the earlier `Unk38314.unk2FC` boundary sits (0x23C–0x2FC), moved `struct Unk7069C`'s definition earlier in the header so it can be nested by value. Took a few iterations to realize the "array" field on the caller's struct is actually an `s32` *index* added to a separate global table, not an array of pointers on the struct itself.
- Matched `sub_0803E1F4` (search `MainWork.unk08D0[]` by two new fields — `unk23`/`unk1C` — plus the existing `unk087C` flag) — same-size DIFF on the first real attempt; the only bug was the two `s16` parameters being compared against the wrong struct fields (swapped `a`/`b`). New `unk23` field added to the existing `struct Unk8D0`; re-verified `sub_0803E258` (which also uses this struct) still matches.
- **Near-miss batch handed to decomp-permuter**, running in the background (`-j1` each, `--stop-on-zero`, imported via `tools/decomp/permuter/import_function.py`): `sub_08062068`, `sub_08042C3C`, `sub_08067F98`, `sub_08034810`, `sub_08040088`, `sub_08042BB0`, `sub_080312B0`, `sub_0803DCFC`. All 8 are same-or-near byte count as retail with correct logic (verified via `match_function.py` DIFF), blocked only on a specific register-allocation choice or branch-fold agbcc makes that no C rephrasing tried could steer — exactly the class the permuter's random search is built for. `src/matched/*.c` reverted to naked-asm for all 8 while permuting (the permuter works from its own `nonmatchings/<fn>/base.c` copy); whichever ones land should be integrated from the permuter's zero-score output, not re-derived by hand.
- `make compare`: OK
- Decompiled C: 224 → 226/633 (35.4% → 35.7%)

### 2026-09-19 — semantic C sub_08031368 (+1, 223→224/633); pace note for the 40% ask
- Matched `sub_08031368` (reverse array-of-pointers search skipping index 0, returns two fields via out-params) — matched on the first real attempt once the loop bounds were traced precisely (`for i = n-1 downto 1`, index 0 never checked — a real, deliberate asymmetry, not a bug).
- Extensive near-miss work, all reverted (no partial/broken state left): `sub_08062068` (48B=48B; a `switch`/if-chain 3-way branch where retail's second comparison is a genuine `bcc` unsigned-less-than against 1 that no phrasing — `c<1`, `(u32)c<1`, `(s32)c<1`, `switch` case order — stopped agbcc from folding to `beq ,#0`; likely needs the exact original variable rather than a derived comparison), `sub_08067F98` (56B vs 48B; a variable-stride "linked record" walk needs real byte-pointer arithmetic for the next-offset, which added register pressure beyond retail's shape), `sub_08042BB0` (48B vs 56B; a ROM-table search where retail tracks the loop pointer in *two* registers rather than one — same "independent per-access addressing beats a cached pointer" lesson as `sub_08046230`, got the register set to match but 8 bytes still differ).
- **Honest pace check against the 40% target (253/633):** today's realized rate across ~15 attempted functions is roughly 1 landed match per 3-5 real attempts, several needing multiple disassembly-diff rounds each. A large fraction of what remains in the small/easy tier is gated by one of: the confirmed-unfixable agbcc-extra-push-on-leaf quirk, still-fully-naked large callees (`sub_0804109C`, `sub_08060E48`, the `sub_08061E8C` particle-effect group), or raw unnamed ROM/RAM addresses shared with not-yet-understood structs. Getting from 224 to 253 at this rate is a lot of ground; flagging this now rather than after stalling silently.
- `make compare`: OK
- Decompiled C: 223 → 224/633 (35.2% → 35.4%)

### 2026-09-19 — semantic C sub_08034788 (+1, 222→223/633)
- Matched `sub_08034788` (midpoint of two `Unk705DC*`'s `unk0C`/`unk10` fields) — needed an explicit `(s32)` cast on the sum before the `>>1`, since retail used `asrs` (arithmetic/signed shift) on what the shared struct currently types as `u32`. Cast locally rather than changing `Unk705DC.unk0C`/`unk10` to `s32` globally, since 5 other matched functions already depend on the current (unsigned) field type and re-typing them wasn't verified safe this session.
- Near misses reverted: `sub_080312B0` (40B=40B, only a `ldrh` register choice — r0 vs r5 — differs; tried caching the shifted value in an explicit local before/after the other stores, no effect), `sub_0803DCFC` (48B=48B modulo the still-placeholder `gUnk_0807A1F4` pool word *and* one register-choice byte pair on the initial parameter copy; branch-order fix got it very close but the r1-vs-r2 allocation didn't move with any source reshaping tried).
- Re-confirmed the "agbcc extra push on leaf" quirk (see entry below) hits yet more candidates when tried fresh: `sub_08062684` (24B vs 20B, null-check-and-3-field-write shape, same class as `sub_0802B994`/`sub_0802C62C`) — not pursued further, matches the already-documented pattern exactly.
- `sub_0806105C` (battle-adjacent, calls `sub_08060E48`) skipped: its only callee is a ~200-line glyph/font-rendering function still fully naked-asm — too large and unrelated to hand-convert as a side dependency.
- `make compare`: OK
- Decompiled C: 222 → 223/633 (34.9% → 35.2%)

### 2026-09-19 — correction to the ROM-symbol note below, +1 more match (221→222/633)
- **Correction:** the "ROM-symbol tooling gap fix" logged in the entry below was based on a misdiagnosis. `integrate_c.py` doesn't actually link `src/matched/*.c` into the final ROM at all — once a function verifies byte-perfect, `write_matching_bytes()` freezes the *verified retail bytes* directly as `.short` literals in `asm/matchings/<fn>.s`, and that frozen file (not the C source) is what gets linked. So `sub_080435D8` matched and integrated correctly regardless of whether `gUnk_08094BB4` ever resolves as a real symbol — the `rom_tail.s` incbin split was unnecessary, and it silently got wiped by the next `gen_rom_layout.py` regeneration anyway (confirmed: reverted the split, `make compare` still OK). Not reapplying it. The underlying limitation is real for *re-verifying* a match with `match_function.py` standalone (it'll always show that pool word as a placeholder) but has no effect on `make compare` / actual integration once `write_matching_bytes` has run once. No tooling change needed after all.
- Matched `sub_08044D8C` (sums `a[1..0x7D7]` as `u32`) — needed retail's exact loop shape: `u32 *p = a + 1;` declared *after* the sum/bound locals (not `a++` inside the loop), post-increment `*p++` (not pre-increment), and critically **unsigned** loop counter/bound (`u32 i`, `u32 bound`) — a signed `s32 i < bound` compiles to `blt`, but retail used `bcc` (unsigned), 1 byte different despite otherwise-identical codegen. Took 4 iterations narrowing from "right idea, wrong pointer-arithmetic shape" to exact match.
- `make compare`: OK
- Decompiled C: 221 → 222/633 (34.9% → 35.1%)

### 2026-09-19 — root-caused the agbcc-extra-push-on-leaf quirk (no fix found, no change to counters)
- Directly tested the recurring "agbcc extra push {lr} on leaf" blocker (already hit 10+ times across sessions: `sub_0802D8C4`, `sub_08061BDC`, `sub_0802B994`, `sub_0802C62C`, `sub_08043B58`, `sub_08062684`, etc.) rather than rediscovering it per-function. Compiled a minimal true-leaf function (`if (a) { 3 field writes }`, no calls, `bx lr` in retail) directly with `tools/agbcc/bin/agbcc` under every combination of `-fomit-frame-pointer`, `-fprologue-bugfix`, and with/without `-mthumb-interwork` — **agbcc emits `push {lr}` / `pop {pc}`-equivalent framing in every case**, with no flag that suppresses it for a leaf with a conditional branch.
- **Conclusion:** this is not a source-shape or flag problem — agbcc (this vendored 2.9-arm-000512 build) appears to always frame any leaf with more than a trivial straight-line body, while retail's binary does not, meaning retail's leaves either used a different/patched compiler build, or (more likely for the null-check-and-store shape specifically) were hand-written in assembly rather than compiled from C. **Stop trying C-shape variations on this class** — every remaining true-leaf candidate (no `bl`, ends in bare `bx lr`, retail push-list shorter than 4 registers) will hit this. Either leave them as naked-asm (current default) or feed them to the permuter in bulk; don't spend more manual-C-iteration time on them individually.
- `make compare`: OK (no functional changes)
- Decompiled C: 221/633 unchanged

### 2026-09-19 — fixed the ROM-symbol tooling gap, landed sub_080435D8 (+1, 220→221/633)
- **Root-caused and fixed** the "can't reference a raw ROM rodata address from new C" gap flagged last batch: `asm/rom_tail.s`'s single giant `.incbin` (0x08074146..ROM end) has no symbols inside it, so `extern const T x[]` at a ROM address a function needs can never link. RAM globals (`gMainWorkPtr` etc.) dodge this entirely — the C headers `#define` them as raw address literals, never as real `extern` symbols, so they don't depend on `ram_map.s`'s `SET_DATA` for *linking* (that file's symbols are for other assembly, not C).
- Fix: split `rom_tail.s`'s incbin in two at the needed offset and inserted a `.global gUnk_08094BB4` label at the split point — same total bytes, zero-cost, `make compare` byte-identical before/after the split alone.
- With the real symbol in place, `sub_080435D8` (blocked last batch on the pool-word-only diff) links and matches for real: confirmed by a full `make compare` (not just the standalone `match_function.py` check, which still can't link against `rom_tail.o` and will keep showing that word as `00000000` — that's a known, harmless limitation of the standalone checker, not a sign of a real mismatch, *once the ROM symbol actually exists*). Manifest updated by hand (`kind: asm` → `semantic`) since `integrate_c.py`'s internal verify still uses the standalone checker.
- **Reusable pattern for next session:** any future "known ROM address, no symbol" blocker (there may be others in the `sub_080436B0` family / similar table lookups) can be fixed the same way — find which `rom_gap_*.s`/`rom_tail.s` incbin covers the address, split it, add a `.global` label, confirm `make compare` stays green on the split alone, then the function's `extern` reference will link for real even though `match_function.py` standalone still shows a stale pool word.
- `make compare`: OK
- Decompiled C: 220 → 221/633 (34.8% → 34.9%)

### 2026-09-19 — semantic C (+1, 219→220/633), continued near-misses
- Matched `sub_08044A20` (`MainWork.unk17B4`/`unk17B8`/`unk17C4`/`unk17C8` swap-then-invalidate, mirrored to `unk044C`/`unk0450`) — matched first try; new fields carved from `filler_0428`/`filler_17A0`, offsets cross-checked with `arm-none-eabi-gcc offsetof`.
- Re-attempted `sub_08043B90` with the now-real `sub_08073440` callee — still the same confirmed 1-instruction near-miss from last session (76B, tail re-reads `entry->unk00` instead of reusing the loop-exit register); tried `for`, `while`, `do-while(1)+break`, and a cached-key `for(;;)` form, all landed on the identical extra-`ldr` shape. Genuinely needs a permuter, not more C reshaping — parking it.
- New near-misses found and reverted: `sub_08043B58` (52B vs 54B — same agbcc-extra-push-on-leaf class as `sub_0802B994`/etc., confirmed again on a linked-list-of-pointers search), `sub_08042390` (96B vs 98B — nested-if reconstruction is 2 bytes *shorter* than retail because agbcc shares a `x-refX` subexpression across two basic blocks that retail's source apparently recomputed independently; tried duplicating the expression via redundant if/else nesting, no effect — CSE happens regardless of source phrasing here), `sub_08042784` (108B vs 100B — ring-buffer struct `Unk0538` extension is very likely right structurally but the compiled shape diverges enough — 8 bytes — that it needs more investigation, not a quick fix).
- `struct Unk0538` (`*gUnk_03000538`) extended from the existing 2-byte cursor (`sub_080428C4`) to a full 0x144-byte ring buffer (`unk04[32]`/`unk44[32]`/`unkC4[32]`) — verified `sub_080428C4` still matches unchanged.
- New `struct Unk0554` (`*gUnk_03000554`) and `gUnk_03000538`/`gUnk_03000554` pointer macros added to `ram_map.h`; `sub_08043974` updated to cast the pointer directly (`(u32)gUnk_03000554`) instead of double-dereferencing, to stay consistent with the new typed macro — still matches.
- `sub_080435D8` reconstructed correctly (96B=96B, only the not-yet-linked `gUnk_08094BB4` ROM-table pool word differs) but **could not be integrated**: referencing a raw ROM rodata address with no linker symbol isn't supported by the current `match_function.py`/`integrate_c.py` flow (no `SET_DATA`-style ROM equivalent exists yet, only IWRAM/EWRAM). Flagged as a tooling gap, not a logic problem — worth adding ROM-address symbol support to `asm/ram_map.s` conventions.
- `make compare`: OK
- Decompiled C: 219 → 220/633 (34.6% → 34.8%)

### 2026-09-19 — semantic C (+5, 214→219/633)
- Matched `sub_08046230` (2-slot `MainWork.unk16B0[]` reset — retail addresses each of the 3 fields as its own independent computation rather than one struct-member access; using explicit `gMainWorkPtr->unk16B0[a].unkNN` per field, not a cached pointer, produced the byte-identical shape).
- Matched `sub_080330F4` (`BattleWork.unk1F90`/`unk1F94`/`unk1F98` trio; the `if(a>=0)` branch had to be written as the *positive* case first — agbcc mapped my initial `if(a<0){...}else{...}` to the opposite fallthrough retail used — and the else-branch literal was `0x800`, not `0x800000` as first guessed from the raw `movs #0x80; lsls #4` bytes).
- Matched `sub_08073440` (byte-array 3-way compare, `-2`/`-1`/`0`/`1`, strcmp-shaped) — matched first try once the existing `s32 sub_08073440(void*, void*)` prototype was reused verbatim.
- Matched `sub_0803E258` (0x53-slot `MainWork.unk08D0[]` search by `unk1C` key + `unk087C[]` flag byte, returns `&unk08D0[i]`) — new `struct Unk8D0` (0x28-stride) and `unk087C[0x53]`/`unk08D0[0x53]` fields added, offsets cross-checked with `arm-none-eabi-gcc offsetof`.
- Matched `sub_08038638` (`Unk3CC.unk22[]` countdown + `sub_080385DC` retrigger) — new `struct Unk3CC` (`*gUnk_030003CC`, `unk00[16]`/`unk20`/`unk22[16]`) plus the `gUnk_030003CC` pointer macro in `ram_map.h`. Needed retail's exact dual-read shape: an unsigned `u16 raw` copy of the field used only for the decrement math, kept separate from the `s16`-typed field read used for the `>0`/`==0` comparisons — collapsing them into one read landed 4-8 bytes short every time.
- Near misses parked (reverted to naked-asm, not committed): `sub_08043B90` (76B, 1 redundant instruction — final return re-reads `entry->unk00` instead of reusing the register from the loop-exit test), `sub_08052934` (84B, 2 instructions swapped — `ldr`+`ldrb` order differs after adding a `Unk995AC`/pointer-indirection struct for the `0x080995AC` table), `sub_08033574` (80B, 1-byte pool-constant offset differs — `unk1FE6`-relative addend came out `0x3B` instead of `0x3A`, points 1 byte before `unk1FAC`; likely fixable with a different statement order but not found this session).
- `make compare`: OK
- Decompiled C: 214 → 219/633 (33.8% → 34.6%)

### 2026-09-19 — struct scaffolding + 2 new blocks (214/633 unchanged)
- Split `struct BattleWork` filler to name `unk19C[4]` (`struct Unk62044`, 0x19C/0x1C4/0x1EC/0x214 — confirmed via agbcc offsetof cross-check); moved `struct Unk62044` earlier in `unknown-types.h` so it can be nested by value. Added new `struct Unk38314` (countdown @0x2FC, flag @0x304).
- Attempted hand-conversion of `sub_08038314` and `sub_08045C5C` (both top-of-queue battle candidates). Both reconstruct the correct logic (verified via `match_function.py` DIFF — same/near-same size, only instruction-order/register-alloc differences) but agbcc lands on a different register choice than retail in each case. 20k+ permuter iterations on `sub_08038314` never found a zero (floor stuck at score 70). Documented both in `decomp-queue.toml` as blocked (needs permuter); see reasons there.
- `sub_08062D50` heads-up from previous session confirmed correct: it's the same BGR555-pack register-swap shape as blocked `sub_08062CF4` and is already parked as a naked-asm placeholder, not a fresh candidate — no action needed.
- `make compare`: OK (no functional changes, only header/type scaffolding)
- Blocked (documented): 29 → 31

### 2026-09-19 — moved down queue, 4 more agbcc-leaf blocks (214/633 unchanged)
- Worked down the "battle=2" tier (`sub_08033188`, `sub_0807309C`, `sub_08037430`, `sub_0803C5DC`, `sub_0803C500`, `sub_08036A68`, `sub_0803D51C`, `sub_08038F30`): all depend on a shared cluster of still-naked, multi-arg callees (`sub_08061E8C`, `sub_08073AEC`, `sub_08061EF8`, `sub_080735DC`, `sub_0802C314`, `sub_0806A3A4`/`sub_0806A4D8`) with no established prototypes — hand-converting the callers would mean guessing signatures. Skipped rather than risk wrong prototypes; someone should prototype `sub_0807309C`'s allocator group first to unblock this whole tier at once.
- Dropped to "battle=1" tier and found a **systemic pattern**: `sub_0802B994`, `sub_0804495C`, `sub_0802C62C`, `sub_0803DBD0` all reconstruct provably-correct logic (verified via `match_function.py`, `sub_0802C62C` even hit byte-identical *size*, 64=64) but agbcc inserts a `push{lr}...pop{r1};bx r1` leaf frame that retail's build doesn't have (`bx lr` direct, or a tighter push set), no matter which C shape/declaration-order is tried. This is the same class as the already-documented `sub_0802D8C4`/`sub_08061BDC`/`sub_08062634`/`sub_08061E40` "agbcc extra push {lr} on leaf" blockers — now confirmed to hit small ROM-table-lookup and counting-loop leaves too, not just null-check leaves. 7000+ permuter iterations on `sub_0802C62C` (the closest, byte-count-identical case) never found a zero, floor stuck at score 95. All 4 documented in `decomp-queue.toml`.
- **Takeaway for next session:** this agbcc leaf-framing quirk is now confirmed across ≥9 functions in 3+ shapes (null-check leaf, counting loop, table lookup, table copy). Worth investigating directly — e.g. does forcing `-Wl,--no-...`/a different agbcc leaf heuristic, or an explicit `register` hint, suppress the frame — before spending more permuter cycles rediscovering it function-by-function.
- `make compare`: OK (no functional changes; all attempted `.c` files reverted to naked-asm since none reached a byte-perfect match)
- Blocked (documented): 31 → 35



### 2026-09-18 — Semantic audit fix (+15 prototypes) + near-miss batch

- **Prototype fixes:** added `sub_08061BE8`; fixed `sub_08033F24` (`sub_08072CC0(a)`), `sub_080400D4` (cast), `sub_08070678` (`BtlObj` cast)
- **Semantic audit:** **0/182 broken** (was 15 compile failures + 4 same-size DIFF reverted earlier)
- `near_miss_batch.py`: `--no-m2c` for faster runs; blocked `sub_080473E4` (dual IWRAM CSE, permuter best score ~5)
- Near-miss still open: `sub_0803DD60` family (pool order), `sub_0806FEFC` (leaf `push {lr}`), `sub_0802C62C` (loop regs)
- `make compare`: **OK**

### 2026-09-18 — Near-miss triage + semantic audit

- Added `tools/decomp/near_miss_batch.py` / `.sh` — seeds + c_patterns on readable Thumb; `--list-broken` audits semantic C
- Added IWRAM pointer-slot macros in `ram_map.h` (`gBattleWorkPtrLoc`, `gMainWorkPtrLoc`, …) for pool-pin matching
- **Semantic audit:** 4 integrated files failed `match_function.py` (same-size DIFF) — reverted to verified asm:
  - `sub_08033530` → readable Thumb (`subs r2, #0x6C` offset reuse; blocked in queue)
  - `sub_08033F48` / `sub_0803403C` / `sub_0803413C` → opcode embed (semantic store order/reg alloc)
- Removed broken `sub_08033530` from `BATTLE_SEEDS`
- Near-miss attempts (same-size DIFF, permuter): `sub_0803DD60` family (pool order), `sub_080473E4` (dual IWRAM CSE), `sub_0806FEFC` (extra `push {lr}`), `sub_0802C62C` (loop reg alloc)
- 15 semantic files still fail agbcc (missing/wrong prototypes) — run `python3 tools/decomp/near_miss_batch.py --list-broken`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_0806F430` (`Unk4084` flags @ `gUnk_03004084` — bit 0x08/0x10 check, `sub_08067B98`; register `r0`/`r1` flow)
- Semantic C: `sub_08033C1C` (`Unk0380` @ `gUnk_03000380` — clear `unk09`/`unk0A`, call `sub_080358CC`; `r1` + `tmp[]` pool pin)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08031294` (`Unk312EC` init — OR flags on `unk00`/`unk01`, `unk04 = -1`, clear `unk0C`/`unk08`; register-pinned `r1`/`r2`)
- Prep (next): `BattleWork` `unk1FE6`/`unk2089`, `sub_08038638` proto, permuter seeds for `33574`/`473E4`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b battle semantic C (+1)

- Added `tools/decomp/battle_semantic_batch.py` / `.sh` — hand seeds + m2c/heuristics for battle readable Thumb
- Semantic C: `sub_08033530` (`gBattleWork->unk2088` branch → `33574` or `686D8`/`68418` on `unk1FAC`)
- Proto: `sub_08033530(void)` in `unknown-functions.h`
- Near-miss: `sub_080601C4` (r8 pool pin, 92B→84B), table-lookup family still pool-blocked
- `make compare`: **OK**

### 2026-09-18 — Phase 3b readable Thumb sweep (100% not opcode)

- Fixed `readable_asm.py`: prototypes from `unknown-functions.h` (pointer return types), multi-line `asm()`
- `readable_asm_batch.py --all`: converted remaining **227** opcode `.byte` stubs → readable unified Thumb
- Final fix: `sub_08069988` / `sub_08071E84` / `sub_08071F44` (header `void *` / `struct *` names)
- **0 opcode embeds remain** — not opcode **100%** (451 readable + 182 semantic)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b readable Thumb leaf batch (+20)

- Fixed `readable_asm.py`: preserve matched-file prototypes + multi-line `asm()` (`.byte` embeds now convert reliably)
- Converted 20 straight-line leaf opcode stubs → readable unified Thumb (`--kind asm`)
- Batch 1: `sub_0802D8C4`/`31294`/`33958`/`33F30`/`347E4`/`35908`/`361CC`/`42E78`/`473E4`/`61BDC`
- Batch 2: `sub_08061E40`/`62634`/`62684`/`62728`/`62CC8`/`62D24`/`68884`/`69F00`/`6A954`/`6AC68`
- Semantic C: `sub_080674BC` (dispatch table pointer via `0x030009B0`, register-pinned `r0`/`r2`)
- Other leaf semantic seeds still blocked (agbcc `push {lr}` / pool fold); `sub_080615EC` asm compile fail (branchy)
- `make compare`: **OK** — 264 opcode embeds remain (was 304); 187 readable Thumb (+40)

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_0802B8BC` (halfword table lookup via `gUnk_03000264`, `register asm` for `r0`/`r1` dest reg)
- Permuter on `sub_0803DD60`: best score **100** (~32k iters) — stays readable Thumb
- Leaf null-check stubs (`61BDC`/`62634`/`61E40`) still blocked by agbcc extra `push {lr}` on any branch
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_08072F94` (battle lookup byte via `gBtlLookupBase`/`Ptr` stack pool), `sub_0806DEC8` (indexed byte-chain walk), `sub_08066434`/`66440`/`6644C` (IWRAM `0x970` bytes @+0x34/+0x35), `sub_08062A1C` (store word @ `0x7B0+0x114`), `sub_0806639C` (ROM table `0x80BA1A8` indexed by `gUnk_03000964`)
- Types: `UnkDEC8`/`UnkDEC8Head`; protos fixed (`66434`/`66440` as `u8`, `615EC` as `u16`, `62A1C` as `u32`, `6639C` as `void *`)
- Permuter seeds added in `import_function.py` for pool-order leaves
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+4)

- Semantic C: `sub_0802D898` (write `0xFFFFF800` into `Unk026C->unk08` coords), `sub_0806EE24` (copy `unk358` to DISPCNT, set `unk356`/`unk355`), `sub_0802D3F0` (free `unk08`–`unk40` via `6FE84`, then `6A434` on `*0x03000270`), `sub_0802D8DC` (sync `Unk705DC` overlays via `2E18C`/`2E1B4`/`2E210`)
- Grew `Unk026C` (`unk08`–`unk40` as `Unk705DC *`, `unk48`/`unk4C`), `Unk705DC` (`unk08`/`unk0C`/`unk18`), `MainWork` (`unk0424`, `unk0878`, `unk1838`/`unk183A`), `Unk0798` (`unkA2`); added `Unk6EE24`/`Unk617C4`
- Near-miss: `sub_0802D52C`/`2E048`/`312B0`/`61800` (same-size dest regs), `sub_0802D6D4` (pool order C000 vs 63CC), `sub_0802DEA0` (CSE of `0xFFFFC000`), extra-`lr` leaves (`2D8C4`/`615EC`/`61BDC`/`617C4`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+5)

- Semantic C: `sub_080603A4` (optional `71FC8` on `unk177C` then store `unk1819`), `sub_080705A4` (pack 2 bits into `unk10` at bit 10), `sub_080705DC` (pack 4 bits into `unk14` at bit 12), `sub_0802D598` (clear `Unk026C` then write `0xFFFFC000` into inner +8/+0xC), `sub_08061610` (low 4 bits of arg into `unk96` at bit 12)
- Grew `Unk705DC` (`unk10`), `Unk0798` (`unk96`), `Unk026C`/`Unk026CInner`, `MainWork` (`unk15C8`–`unk15D2`), `Unk447CC` (`unk00`), `Unk6FDB4` (`unk22`); added `Unk2C314`; `sub_0803DD88` now takes `s32`
- Rematch: `sub_080312EC` (`(u8)unk01` into `705DC`)
- Near-miss: `sub_0802C62C`/`2B8BC` (same-size dest regs), `sub_0802C5DC`/`2C2B0` (slot+off reload vs rematerialize), `sub_080447CC` (unk18 in r1 vs r0), `sub_08042B78`/`42BB0` (pool in middle), extra-`lr` string leaves (`73078`/`731F4`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_080611A4` (alloc `0xAC` into 790/798/794 slots + CpuFill via `*0x080BB8BC`), `sub_08059C98` (first empty stride-`0x3C` slot + optional `6A3A4`), `sub_0806F8C4` (list integrity checks via `67B98`), `sub_080680CC` (key walk then `68180`), `sub_080408C4` (`2C314` then `3DD88`), `sub_0802B95C` (stride-12 search via `2B994`/`73440`)
- Grew `Unk0798` (`unk5C`/`unk88`), `Unk59C6C` (full 0x3C), `Unk0770` (`unk04`/`unk06`), `Unk346C0Inner` (`unk00`); added `Unk59C98Src`/`Unk59C98Owner`/`Unk680CC`/`Unk2B95C`; `sub_0803DD88` now returns `s32`
- Near-miss: `sub_08062BF0`/`62C38` (ble/bge skip 0 vs 1), `sub_08059B74` (bne skip 3 vs 6), `sub_08062A74` (p in r2 vs r1), `sub_08061308`/`60D28` (ldrb r1 vs r0), `sub_080615EC` (extra `lr` on leaf)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_08030F00` (copy inner `unk08`/`unk0C-0x1000`, optional `70354` from `unk30`), `sub_08033EA4` (`726A4` to BG pal + `72A38`), `sub_0803C6B8` (`74B40` pair into `74798`/`74634`/`74148`)
- Added `Unk30F00`/`Unk302A8`/`Unk6D748`/`Unk3E328`/`Unk71E84`; grew `Unk42E78`/`Unk59C6C`/`Unk705DC`/`Unk0798`; `_08073C44` now returns `u32`
- Near-miss: `sub_08062BF0`/`62C38` (ble/bge skip offset 0 vs 1), `sub_080473F8`/`71B4C` (pool-fold 630/638 and 40DC/410C), `sub_08059B74` (bne skip 3 vs 6), `sub_080611A4` (794 folded as 798-8)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08062640` (tick `unk20`/`unk1C`, optional `_08073C44` + `62684`), `sub_08066BC4` (indexed `705DC` then store 8 at +0x310)
- Added `Unk66BC4`
- Near-miss: `sub_0806F430` (dead `flags & 0x10` vs `cmp r1, #0`), `sub_08073A28` (string shift extra regs), `sub_08038638` (03CC reload vs rematerialize)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+4)

- Semantic C: `sub_08062AC0` (CpuFill `*08D0` + OBJ pal via `*0x080BB8BC`), `sub_0805DA70` (CpuSet `unk164` to `0x05000340`), `sub_08059D08` (optional `_08073C44` then free `unk0C`), `sub_0806D958` (optional `_08073C4C` then clear `unk80`/`unk84`/`unk88`)
- Added `Unk59D08`/`Unk6D958`; `_08073C44` prototype
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_08063104` (CpuSet `*08DC` to BG pal + free `*08E0`), `sub_08033A5C` (swap `34A68` slots then `35020`/`330F4`), `sub_08060468`/`60758` (alloc via `6A3A4` then CpuFill via `*0x080BB8BC`), `sub_0806A580` (first empty 16-byte slot), `sub_08062758` (walk `unk04` table into `62790`), `sub_08041394` (free 8 pointers at +0x220)
- Grew `Unk62044` (`unk24`), `Unk33F30` nested layout; added `Unk33A5C`/`Unk6A580`/`Unk0758`/`Unk62790Obj`; `sub_080330F4`/`6A3A4`/`62790` signatures aligned
- Near-miss: `sub_08061C48` (770 rematerialized vs r5), `sub_0806209C` (store 0 in r0 vs r1), `sub_0804745C` (630 in r6 vs r1 then copy)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+5)

- Semantic C: `sub_080679A4`/`679C0` (CpuSet to BG/OBJ palettes), `sub_080733BC` (append byte + NUL), `sub_080735B0` (walk pointer list via `73114`), `sub_08059C6C` (20 stride-`0x3C` slots)
- Grew `Unk047C` (`unk810[9]`); added `Unk59C6C`
- Near-miss: `sub_080447CC` (unk18 in r1 vs r0), `sub_0803DCFC` (index in r2 vs r1), `sub_0806105C` (counter vs string regs), `sub_08068884` (extra `lr`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_08035884` (Unk35878 range walk + optional `_08073C4C`), `sub_08036264` (midpoint + scaled distance via `674B0`), `sub_0806306C` (palette CpuSet + free IWRAM slots), `sub_0803EDF0` (byte at +3 on `Unk0C` stride-12), `sub_08072CC0` (free `unk10`), `sub_080720F0` (indexed `71EE4`)
- Grew `Unk346C0` (`unk08`/`unk2CC`/`unk2DC`/`unk2E0`/`unk2F8`/`unk2FC`/`unk30C`–`unk314`), `Unk0C` (`unk03`), `Unk312EC` (`s8 unk00/unk01`, `Unk705DC *unk0C`); added `Unk705DC`/`Unk36264`
- Near-miss: extra-`lr` leaves (`61BDC`/`62634`/`62728`/`33958`/`61E40`/`62684`/`6DEF4`/`6AC68`/`2D8C4`/`69F00`/`6BE08`/`35908`/`347E4`), pool-fold (`66434`/`66440`/`6644C`/`62A1C`/`473E4`), same-size (`44F64` muls vs shift-add, `42B28`/`42B50` index regs, `34A68` `0x314-0x1C` reuse, `31300` ldrsb else)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08032D5C` (stack pair into `unk2E4`/`unk2E8`, then `35054`/`628B4`/`3559C`/`60254`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08031094` (clamp via `31124` then `346A8`), `sub_0802E1B4` (`42BE8`/`42BB0`/`42B78` then `31124`)
- Grew `Unk346A8` (`unk04`), `Unk310F0Inner2` (`unk21`); `sub_080674B0` now returns the SWI 8 result; `sub_08042BE8`/`42BB0`/`42B78` take/return word-width values
- Near-miss: `sub_08041858` (pool-fold `0x504`), `sub_08054454` (zero vs addr regs), `sub_080360BC` (r8/r9), `sub_08067F3C` (extra r8)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+11)

- Semantic C: `sub_0802E18C` (div/mod tens), `sub_08070AD4`/`70DF4` (`7069C` then draw), `sub_08041980` (free 32 `Unk68574` slots), `sub_080686B4` (callback or copy 3 words), `sub_0806F174` (store + optional `6F05C`/`73C4C`), `sub_080310F0` (clamp via `31124`), `sub_08043ADC` (stride-`0xDC` free + `6A434`), `sub_08033D90` (rng index + `35878`), `sub_0802E210` (`42E78`/`42BE8`), `sub_0803413C` (Unk33F30 setup)
- Grew `Unk33F30` (front fields, `unk1C` inner), `Unk070C` (`unk00[13]`), `Unk0798` (`unk5D`/`unk94`), `Unk312EC` (`unk08` as byte); `sub_080674A4` now takes dividend/divisor
- Near-miss: `sub_08033C1C` (pool-fold `&unk0C` → `0x0300038C`), `sub_08062C80` (extra 4B), `sub_080408C4` (epilogue / extra sxt), `sub_08060D28`/`61308` (pool order)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+1)

- Semantic C: `sub_08061BAC` (free 4 stride-8 slots at `0x03000770`, clear `0x03000794`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+2)

- Semantic C: `sub_08043C28` (free four pointers at `0x030005F0`), `sub_08068808` (free `unkB8`/`unk7C`, clear `unk74`–`unk7C`)
- Grew `Unk68574` (`unk74`/`unk78`/`unk7C`/`unkB8`); added `Unk05F0`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+6)

- Semantic C: `sub_08062044` (free `unk00` then clear `unk0C`), `sub_0807069C`/`703FC`, `sub_08054558` (nested `Unk7069C` at +0x34), `sub_0806EBF8` (8-word stack pair), `sub_08040618` (pop `Unk047C` table)
- Grew `Unk7069C` (`unk0A`), `Unk047C` (`unk808`); added `Unk070C`/`Unk703FC`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+16)

- Semantic C: `sub_08033F48`/`3403C`/`34360`/`33E3C` (Unk33F30 init/tick), `sub_0803484C`, `sub_08040530`, `sub_0802EECC`/`2FD80` (VBlank + `_08073C40`), `sub_080312EC`, `sub_08034FBC`, `sub_08045AA8`, `sub_08060254`, `sub_080608D4`, `sub_08067634`, `sub_08070C98`, `sub_08031124`
- Grew `Unk33F30`/`Unk68574`/`Unk0798`/`Unk047C`/`Unk026C`/`Unk0748`; promoted `gUnk_0300026C`; `sub_080674A0` now takes dividend/divisor
- Near-miss: `sub_080447CC` (ld r1 vs r0), `sub_08033C1C`/`615EC` (pool fold / extra lr), `sub_080679A4`/`679C0`/`5DA70` (pool order)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_080405E8` (append to `Unk047C` pointer table), `sub_0805D1AC` (nested `sub_08068418` / `sub_08067CE8`), `sub_08062238` (free `unk08` then `sub_08062684`)
- Grew `Unk047C` (`unk00[0x200]`, `unk80C`)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+7)

- Semantic C: `sub_0804BE80`/`4CA30`/`4D58C`, `sub_0803A1E4` (VBlank + `_08073C40`), `sub_08062960`, `sub_080611F0`, `sub_08070678`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+18)

- Semantic C: `sub_08048D0C`/`50864`/`538A0`/`54108`/`56380`/`56AF0` (VBlank + `sub_08061BE8` wrappers), `sub_08035238`, `sub_08071FC8`, `sub_08068558`, `sub_08034FF8`/`34FDC`, `sub_0807339C`, `sub_08073184`, `sub_080400D4`, `sub_080604A4`/`60798`, `sub_080626B8`, `sub_08045A84`
- Grew `Unk71F84` (`unk10`), `Unk68574` (`unkA8`–`unkAE`); added `Unk34FF8`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+3)

- Semantic C: `sub_080674A4` (SWI 6 remainder), `sub_080447B4` (NULL-terminated `sub_08059AE0` list), `sub_080346C0` (store 4 fields if `*a`)
- Grew `Unk312EC` / `Unk68014`; extra-`push {lr}` still blocks `sub_08061E40`/`62728`/`6AC68`/`69F00`/`6BE08`/`717F0`
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+10)

- Semantic C: `sub_08071FAC`, `sub_080312D8`, `sub_080400C0`, `sub_08061784`/`B4`, `sub_08061A98`/`AA8`, `sub_08067890`, `sub_08069C14`, `sub_08068014`
- Promoted RAM: `gUnk_03000180` (`Unk0180`), `gUnk_0300047C` (`Unk047C *`), `gUnk_03000798` (`Unk0798 *` with `unk98`/`unk9C`/`unkA0` packing)
- Near-miss: `sub_080312EC` (`ldrb r1` vs `r0`), `sub_080473E4` (CSE of `0x03000634`/`63C`), `sub_0807069C` (`strh` +2 vs +4), `sub_08062A1C`/`66434`/`66440` (folded `base+off` pool)
- `make compare`: **OK**

### 2026-09-18 — Phase 3b semantic C (+14)

- Semantic C: `sub_080603E0`, `sub_08043BDC`, `sub_08060428`/`38`/`48`/`58`, `sub_08060394`, `sub_080602C0`, `sub_08033F24`, `sub_08034414`, `sub_08032DB8`, `sub_080686D8`, `sub_08071F84`, `sub_08071F98`
- Grew `MainWork` (`unk16C8`/`unk16E0`/`unk16E4`/`unk181A`/`unk181F`) and `BattleWork` (`unk1FAC`/`unk201C`/`unk2088`)
- Tooling: decomp scripts import `tools/decomp/` (leftover `scripts/decomp` Path joins)
- Near-miss: `sub_08043B90` (extra `movs r0,#0`), `sub_08033530` (reg alloc), `sub_0804495C` (leaf prologue)
- `make compare`: **OK**

### 2026-09-17 — Phase 3b battle: reloc + readable Thumb + semantic C (+8)

- `match_function.py`: Thumb `R_ARM_THM_CALL` reloc patcher also covers `_080…` local labels (not only `sub_*`)
- Remaining **36** battle `.byte` stubs → readable Thumb (`readable_asm_batch.py`); **0 battle opcode left**
- Semantic C: `sub_080433F4`, `sub_0802E1EC`, `sub_0802BA4C`, `sub_08044EE8`, `sub_0803E440`, `sub_0806013C`, `sub_08060220`, `sub_080628B4`
- Grew `MainWork`: `unk1688`/`unk1694`/`unk1710[]`/`unk177C`/`unk1780`/`unk1798`/`unk179C`/`unk1819`/`unk1861[]`
- Near-miss (keep readable Thumb): `sub_080428C4`/`sub_080475C4`/`sub_080475F4`/`sub_0806FF28` (extra `push {lr}`), `sub_0806FEFC` (CSE `tail = head+0x10`), table family (pool order / `idx-1` fold)
- `make compare`: **OK**

### 2026-09-17 — C convention: struct members (aw2bhr style)

- Added `include/unknown-types.h` / `unknown-functions.h`; growing structs with `filler_XX` + `unkXX`
- Typed RAM macros: `gMainWorkPtr`, `gBattleWork` in `ram_map.h`
- Converted existing semantic C from offset-casts to `a->unkXX` / `g->unkXX`
- `c_patterns.py` now emits member stores; SWI r2=0 uses a register asm local, not `asm volatile`
- `make compare`: **OK**

### 2026-09-17 — decomp-permuter + battle readable Thumb (+122)

- Wired [decomp-permuter](https://github.com/simonlindholm/decomp-permuter): `permuter_settings.toml`, `tools/decomp/permuter/`
- `match_function.py` now applies `R_ARM_THM_CALL` so `bl sub_*` matches retail encodings
- Battle `.byte` stubs → readable Thumb (`--kind asm`): **122 converted**, 36 still opcode (BL to non-`sub_*`)
- Permuter on `sub_08072F94`: base score 50 (agbcc always deref-first); 11k+ iters, no score-0 — keep as readable Thumb until C matches
- `make compare`: **OK**

### 2026-09-17 — Phase 3b semantic batch (+15)

- `c_patterns.py`: field init, offset stores, three-u16/u32 patterns
- Converted: `sub_080338E4`, `sub_080346A8`, `sub_080358CC`, `sub_08035878`, `sub_08068574`, `sub_0806BB38`, `sub_0806B5B8`, `sub_0803EDC8`, `sub_08036190`, …
- `make compare`: **OK**

### 2026-09-17 — Phase 3b semantic C bootstrap

- Goal: replace `__attribute__((naked))` + `.byte` opcode embeds with readable, byte-matched C
- Added `tools/decomp/semantic_convert_batch.py`, `m2c_asm.py`, `opcode_stubs.py`
- `c_patterns.guess_c()` no longer falls back to opcode embed (use `guess_opcode_embed()` explicitly)
- First semantic replacement: `sub_08068584` (two `strh` field stores)
- Run: `tools/decomp/semantic_convert_batch.sh 30 --pool-free-only` for easy wins
- Pool/literal-pool functions (e.g. `sub_08061610`) need m2c + hand refine or permuter

### 2026-09-17 — Phase 3 complete (633/633 C placeholders)

- `c_patterns.py`: semantic patterns + `_naked_retail()` fallback (embeds exact retail opcodes)
- Batched conversion: trivial/IWRAM accessors → naked bytes ≤48B → ≤128B → ≤256B → remainder (≤1552B)
- `triage_functions.py` json fix; `c_convert_batch.sh` stdout fix
- `ram_map_pass.sh` run mid-session
- `make compare`: **OK**; `check_shiftable.py`: 633/633 linked, 980 fixed-VMA sections remain (Phase 5)

**Note:** Many functions use `__attribute__((naked))` + `.byte` opcode embedding where agbcc cannot reproduce literal-pool/ordering. Semantic C exists for early batches (battle, IWRAM loaders, swi stubs). Phase 4 should replace `sub_*` names; Phase 5 can migrate to shiftable layout.

### 2026-09-17 — Phase 3 C batch (+15 naked retail bytes)

- `c_patterns.py`: fallback embeds exact retail opcodes for functions ≤12B
- Converted 14 via batch + `sub_080674A4` (swi + adds r0,r1)
- `make compare`: **OK**

### 2026-09-17 — Phase 3 C batch (+9 patterns)

- Fixed `triage_functions.py` (`json` shadowing bug)
- Extended `c_patterns.py`: naked return, swi+r2 prep, IWRAM pool loaders, stack shim
- Fixed `c_convert_batch.sh` stdout capture from `integrate_c.py`
- New C: `sub_0802B90C`, `sub_080429C0`, `sub_08043974`, `sub_08062A14`, `sub_08066390`, `sub_080674B4`, `sub_08071808`, `sub_08074144`, `sub_08067B98`
- `make compare`: **OK**

### 2026-09-17 — Phase 3 battle C batch (+1)

- `sub_080314FC` → `src/matched/sub_080314FC.c` (battle work field @ +0x118)
- `tools/decomp/battle_convert_batch.sh` added
- `make compare`: **OK**

### Asm-only (documented blockers)

agbcc cannot reproduce these as C (literal-pool / instruction scheduling). They now have **readable Thumb** in `src/matched/` instead of `.byte` blobs. Permuter target when C is close.

| Function | Reason |
|----------|--------|
| `sub_08072F94` | agbcc loads `gBtlLookupPtr` before the addend (permuter score 50) |
| `sub_0803DD60` family | main-work table via `+0x1818`; same-size pool/reg order (`idx-1` folds into `base-4`) |
| `sub_08034894` | agbcc extra prologue / pool ordering |
| `sub_0806FEFC` | Freelist pop; agbcc CSEs `gBtlObjListTail` as `head+0x10` |
| `sub_0806FF28` / `sub_080428C4` / `sub_080475C4` / `sub_080475F4` | C adds `push {lr}` on a retail leaf |
| `sub_0802C62C` | Same size; count/`want` register swap (`r3` vs `r4`) |
| `sub_0806A6F8` | Large input hub; C not attempted |

### 2026-09-17 — Phase 3 battle subsystem bootstrap

- `include/battle.h`, `docs/battle.md`, `tools/decomp/battle_scan.py`
- Named battle IWRAM: `gBtlInputMask`, `gBtlKeysHeld`, object table, key queue, …
- First battle C: `sub_080628E4` (main-work arena write @ `+0x1800`)
- `make compare`: **OK**

### 2026-09-17 — Phase 3 C batch (trivial patterns)

- Fixed `match_function.py` (retail baserom byte compare; was broken objdump filter)
- Added `integrate_c.py`, `c_patterns.py`, `c_convert_batch.sh`
- Converted **9** trivial functions → `src/matched/*.c` (`make compare`: **OK**)
- Patterns: empty return, `ldrb` load, `ldr` + offset, `strb` field set, `swi` stubs

### 2026-09-17 — Phase 2 RAM map pass

- Rescanned `baserom.gba` literal pools: 250 IWRAM refs, high-water `0x03005694`
- Removed sigma_star_saga placeholder `KNOWN_IWRAM`; known symbols now parsed from `asm/ram_map_*.s`
- Emitted `asm/ram_map_iwram_pool.inc` (247 `gUnk_*`), `include/ram_map_pool.h`, `docs/ram-map.md`
- Promoted: `gMainWorkPtr`, `gBattleWork`, `gBattlerArena`
- Added `tools/decomp/ram_map_pass.sh`; `make compare`: **OK**

### 2026-09-17 — batch 3 (20 functions)

Integrated 20 asm-verified functions including literal-pool loaders (`sub_0802B90C`, `sub_080429C0`, …), IWRAM accessors, and field setters. `make compare`: **OK**.

### 2026-09-17 — linker integration + batch 2

11 functions linked via ROM peel tooling.

### 2026-09-17 — bootstrap + batch 1

First 4 functions + `src/stubs.c`.

## Tooling

| Script | Purpose |
|--------|---------|
| `tools/decomp/cursor_batch.sh` | Triage + m2c seeds |
| `tools/decomp/integrate_match.py` | Link match into ROM peel |
| `tools/decomp/match_function.py` | Verify scratch C vs asm (now runs CPP; patches Thumb BL relocs) |
| `tools/decomp/worddiff.py` | Word-aligned retail-vs-compiled table for hand matching (wraps `match_function.py --full`) |
| `tools/decomp/test_variants.py` | Batch a `@@BODY@@` template against a list of source variants |
| `tools/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |
| `tools/decomp/permuter/` | decomp-permuter wrappers (agbcc pool/order search) |

## Next

- **Phase 3b:** More battle semantic C (`sub_080428C4` family, freelist, table lookups via permuter); types on `gUnk_03000268` / `gUnk_03000630`
- **Phase 4:** Batch `[renames]` in `beyblade_g_revolution.toml` (battle subsystem first)
- **Phase 5:** Shiftable ROM migration (`check_shiftable.py` gates: 633/633 ✓, fixed-VMA sections ✗)

## Blockers

- None (`make compare` OK with all 633 functions linked)

### 2026-09-17 — match_batch (+10, 41/633 linked)
- Functions: `sub_080473E4`, `sub_08061BDC`, `sub_08062634`, `sub_08062A1C`, `sub_0806644C`, `sub_08068584`, `sub_08072F94`, `sub_0802B8BC`, `sub_0803EDC8`, `sub_080400C0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 51/633 linked)
- Functions: `sub_080628E4`, `sub_08067890`, `sub_080314FC`, `sub_0803EDF0`, `sub_08068574`, `sub_0806BB38`, `sub_0802D598`, `sub_0802D8C4`, `sub_08062728`, `sub_0806639C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 61/633 linked)
- Functions: `sub_080717F0`, `sub_08033958`, `sub_08061610`, `sub_08061E40`, `sub_08062684`, `sub_0806DEF4`, `sub_0806AC68`, `sub_080705A4`, `sub_080705DC`, `sub_08033F30`
- make compare: OK

### 2026-09-17 — match_batch (+10, 71/633 linked)
- Functions: `sub_08036190`, `sub_08042E78`, `sub_08068884`, `sub_08069F00`, `sub_0806A954`, `sub_0806BE08`, `sub_080346C0`, `sub_0803DD60`, `sub_0803EBB0`, `sub_0803EC34`
- make compare: OK

### 2026-09-17 — match_batch (+10, 81/633 linked)
- Functions: `sub_08033F24`, `sub_08034414`, `sub_08032DB8`, `sub_080686D8`, `sub_080602C0`, `sub_08060394`, `sub_08060428`, `sub_08060438`, `sub_08060448`, `sub_08060458`
- make compare: OK

### 2026-09-17 — match_batch (+10, 91/633 linked)
- Functions: `sub_080312EC`, `sub_08060254`, `sub_08067634`, `sub_080679C0`, `sub_08069C14`, `sub_0807069C`, `sub_08071F84`, `sub_08071F98`, `sub_08034FDC`, `sub_0803ECB8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 101/633 linked)
- Functions: `sub_08040530`, `sub_08042B00`, `sub_080447B4`, `sub_080679A4`, `sub_0806BDA8`, `sub_08031294`, `sub_080312D8`, `sub_0803DD88`, `sub_0803DDB0`, `sub_0803DDD8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 111/633 linked)
- Functions: `sub_080433F4`, `sub_080608D4`, `sub_08068558`, `sub_0806FDB4`, `sub_08072CC0`, `sub_0802E1EC`, `sub_08044D8C`, `sub_080475C4`, `sub_080475F4`, `sub_08071FAC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 121/633 linked)
- Functions: `sub_08033C1C`, `sub_0803484C`, `sub_08034FF8`, `sub_080361A8`, `sub_080428C4`, `sub_080604A4`, `sub_08060798`, `sub_080615EC`, `sub_0806EE24`, `sub_08033E3C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 131/633 linked)
- Functions: `sub_08034360`, `sub_08034FBC`, `sub_080447CC`, `sub_08062960`, `sub_08070C98`, `sub_08071FC8`, `sub_08073078`, `sub_0807339C`, `sub_0802D898`, `sub_08035908`
- make compare: OK

### 2026-09-17 — match_batch (+10, 141/633 linked)
- Functions: `sub_08042B28`, `sub_08042B50`, `sub_08044EE8`, `sub_08048D0C`, `sub_08050864`, `sub_080538A0`, `sub_08054108`, `sub_08056380`, `sub_08056AF0`, `sub_080626B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 151/633 linked)
- Functions: `sub_0806BE20`, `sub_0806FEFC`, `sub_08073184`, `sub_080731F4`, `sub_080739E8`, `sub_0802B930`, `sub_0803DCFC`, `sub_080405E8`, `sub_08045A84`, `sub_080720F0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 161/633 linked)
- Functions: `sub_0802BA4C`, `sub_0802E210`, `sub_080312B0`, `sub_080408C4`, `sub_08047594`, `sub_080628B4`, `sub_08062CC8`, `sub_080686B4`, `sub_0806FF28`, `sub_0802EECC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 171/633 linked)
- Functions: `sub_0802FD80`, `sub_08031124`, `sub_0803E440`, `sub_080400D4`, `sub_08040618`, `sub_08041394`, `sub_08041980`, `sub_08043944`, `sub_08043B58`, `sub_0804495C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 181/633 linked)
- Functions: `sub_08059C6C`, `sub_080611F0`, `sub_08062238`, `sub_08062D24`, `sub_080703FC`, `sub_08070AD4`, `sub_08070DF4`, `sub_08034788`, `sub_080347E4`, `sub_08035238`
- make compare: OK

### 2026-09-17 — match_batch (+10, 191/633 linked)
- Functions: `sub_080361CC`, `sub_08054558`, `sub_08061308`, `sub_08061BAC`, `sub_08062044`, `sub_08062CF4`, `sub_0806DEC8`, `sub_0806EBF8`, `sub_0806F430`, `sub_080733BC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 201/633 linked)
- Functions: `sub_0802B994`, `sub_0802E18C`, `sub_080320CC`, `sub_08033158`, `sub_08041858`, `sub_08060D28`, `sub_08062D50`, `sub_080674BC`, `sub_08069908`, `sub_08069948`
- make compare: OK

### 2026-09-17 — match_batch (+10, 211/633 linked)
- Functions: `sub_08069988`, `sub_080735B0`, `sub_080405A8`, `sub_0804BE80`, `sub_0804CA30`, `sub_0804D58C`, `sub_0805DA70`, `sub_08060220`, `sub_0806105C`, `sub_08062068`
- make compare: OK

### 2026-09-17 — match_batch (+10, 221/633 linked)
- Functions: `sub_08066BC4`, `sub_08067F98`, `sub_0806A580`, `sub_08070678`, `sub_08031368`, `sub_08042B78`, `sub_08042BB0`, `sub_08042C3C`, `sub_0806013C`, `sub_080603A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 231/633 linked)
- Functions: `sub_08061C48`, `sub_08062AC0`, `sub_0806D748`, `sub_080330F4`, `sub_08035020`, `sub_0805D1AC`, `sub_080699C8`, `sub_0806F174`, `sub_080726E0`, `sub_0802C62C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 241/633 linked)
- Functions: `sub_08030F00`, `sub_0803DBD0`, `sub_08059D08`, `sub_08060468`, `sub_080617C4`, `sub_080310F0`, `sub_0803A1E4`, `sub_08040088`, `sub_08066BF0`, `sub_08071F44`
- make compare: OK

### 2026-09-17 — match_batch (+10, 251/633 linked)
- Functions: `sub_080302A8`, `sub_08033F48`, `sub_08035204`, `sub_08060758`, `sub_08062758`, `sub_08068808`, `sub_0806B724`, `sub_0806F1A0`, `sub_08071E44`, `sub_0803C6B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 261/633 linked)
- Functions: `sub_08045AA8`, `sub_08046230`, `sub_0806209C`, `sub_08066AD4`, `sub_08069A18`, `sub_080712CC`, `sub_08071E04`, `sub_08038638`, `sub_08043BDC`, `sub_080603E0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 271/633 linked)
- Functions: `sub_080726A4`, `sub_0802B95C`, `sub_0803403C`, `sub_08034810`, `sub_08034894`, `sub_08033530`, `sub_0803E328`, `sub_0803E374`, `sub_0803E3C0`, `sub_08041348`
- make compare: OK

### 2026-09-17 — match_batch (+10, 281/633 linked)
- Functions: `sub_08043B90`, `sub_08045128`, `sub_08059DC8`, `sub_080618A8`, `sub_08061DC0`, `sub_08073218`, `sub_0803593C`, `sub_08043ADC`, `sub_08054454`, `sub_080611A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 291/633 linked)
- Functions: `sub_08062A74`, `sub_08063104`, `sub_0806D958`, `sub_08071B4C`, `sub_0802C5DC`, `sub_08033574`, `sub_08033EA4`, `sub_080385DC`, `sub_0803E258`, `sub_0803FDD0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 301/633 linked)
- Functions: `sub_08062C38`, `sub_08073A28`, `sub_0802E1B4`, `sub_08033A5C`, `sub_08041F88`, `sub_080424E8`, `sub_080435D8`, `sub_08061800`, `sub_080620D4`, `sub_08062B9C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 311/633 linked)
- Functions: `sub_08062BF0`, `sub_08033D90`, `sub_08040EF4`, `sub_080449C4`, `sub_08044A20`, `sub_0806F8C4`, `sub_08073440`, `sub_08073568`, `sub_0802C6AC`, `sub_08035884`
- make compare: OK

### 2026-09-17 — match_batch (+10, 321/633 linked)
- Functions: `sub_08035D1C`, `sub_08042BE8`, `sub_08044F64`, `sub_08046278`, `sub_08052934`, `sub_08062C80`, `sub_080680CC`, `sub_08057234`, `sub_0806C78C`, `sub_0803D4C4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 331/633 linked)
- Functions: `sub_08042F4C`, `sub_0804745C`, `sub_0805D99C`, `sub_08061D68`, `sub_08062640`, `sub_080677A8`, `sub_08043C28`, `sub_0806114C`, `sub_08067FC8`, `sub_08068020`
- make compare: OK

### 2026-09-17 — match_batch (+10, 341/633 linked)
- Functions: `sub_0806B3E8`, `sub_08038580`, `sub_08041DB4`, `sub_08061BE8`, `sub_08031300`, `sub_08033084`, `sub_08038D10`, `sub_0803E1F4`, `sub_0807179C`, `sub_0802D52C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 351/633 linked)
- Functions: `sub_0803413C`, `sub_08042784`, `sub_0806184C`, `sub_08071E84`, `sub_08071EE4`, `sub_0802C2B0`, `sub_08030938`, `sub_08033878`, `sub_080601C4`, `sub_080733E4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 361/633 linked)
- Functions: `sub_08042390`, `sub_08070604`, `sub_08073988`, `sub_08042718`, `sub_080473F8`, `sub_08067504`, `sub_0802D2C0`, `sub_08065560`, `sub_08069DBC`, `sub_08073114`
- make compare: OK

### 2026-09-17 — match_batch (+10, 371/633 linked)
- Functions: `sub_080338F0`, `sub_08042630`, `sub_08069894`, `sub_080426A4`, `sub_0805264C`, `sub_08052FC8`, `sub_080604C8`, `sub_08067F3C`, `sub_0802F520`, `sub_08042540`
- make compare: OK

### 2026-09-17 — match_batch (+10, 381/633 linked)
- Functions: `sub_080425B8`, `sub_08045C5C`, `sub_08059B74`, `sub_08061D00`, `sub_08031094`, `sub_08059AE0`, `sub_0802BC14`, `sub_08038D68`, `sub_080392D0`, `sub_08041E14`
- make compare: OK

### 2026-09-17 — match_batch (+10, 391/633 linked)
- Functions: `sub_08051BBC`, `sub_080610A8`, `sub_0806171C`, `sub_08071BA0`, `sub_08043638`, `sub_08065E0C`, `sub_08068798`, `sub_08070468`, `sub_0802E2F8`, `sub_08032D5C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 401/633 linked)
- Functions: `sub_0803E2AC`, `sub_0804737C`, `sub_080607BC`, `sub_08068118`, `sub_08036264`, `sub_080462D4`, `sub_08059C98`, `sub_08061AB8`, `sub_08038314`, `sub_0804B4B4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 411/633 linked)
- Functions: `sub_0804C324`, `sub_0804CED4`, `sub_08066224`, `sub_0806FDD0`, `sub_0807309C`, `sub_0803559C`, `sub_080360BC`, `sub_08061E8C`, `sub_08068E54`, `sub_08033DD4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 421/633 linked)
- Functions: `sub_08037318`, `sub_0806BC0C`, `sub_0806FE84`, `sub_08073910`, `sub_08034A68`, `sub_08035624`, `sub_0804A4E0`, `sub_0806A434`, `sub_0806B064`, `sub_0802C55C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 431/633 linked)
- Functions: `sub_0804AC3C`, `sub_0803E934`, `sub_0806A314`, `sub_0802BF04`, `sub_08062988`, `sub_0806A3A4`, `sub_08041C8C`, `sub_08048168`, `sub_08051504`, `sub_080523A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 441/633 linked)
- Functions: `sub_0806EE48`, `sub_08061564`, `sub_08062F90`, `sub_080691E4`, `sub_08031204`, `sub_08031C98`, `sub_08041774`, `sub_0804245C`, `sub_08068988`, `sub_080442FC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 451/633 linked)
- Functions: `sub_08062AF8`, `sub_0806306C`, `sub_0806C704`, `sub_080735DC`, `sub_080428F0`, `sub_08034618`, `sub_0803531C`, `sub_08056F84`, `sub_0806E7BC`, `sub_08044FB0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 461/633 linked)
- Functions: `sub_08041B74`, `sub_08059BD8`, `sub_0806E31C`, `sub_080419B0`, `sub_0806833C`, `sub_08070354`, `sub_08073AEC`, `sub_080302E0`, `sub_0803114C`, `sub_08068180`
- make compare: OK

### 2026-09-17 — match_batch (+10, 471/633 linked)
- Functions: `sub_08034568`, `sub_08049F98`, `sub_0804E17C`, `sub_08051578`, `sub_08053218`, `sub_080686F4`, `sub_0806A4D8`, `sub_08047624`, `sub_08067584`, `sub_08069B78`
- make compare: OK

### 2026-09-17 — match_batch (+10, 481/633 linked)
- Functions: `sub_0807000C`, `sub_0802C4A4`, `sub_08057274`, `sub_0806FF58`, `sub_0806E420`, `sub_0806FBF8`, `sub_080700CC`, `sub_0803E848`, `sub_080415FC`, `sub_080427E8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 491/633 linked)
- Functions: `sub_0804A028`, `sub_0802C314`, `sub_08070D44`, `sub_0802C3DC`, `sub_08035D68`, `sub_08062358`, `sub_08033978`, `sub_08047A94`, `sub_0804A438`, `sub_0804B40C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 501/633 linked)
- Functions: `sub_0804C27C`, `sub_0804CE2C`, `sub_0804E4F4`, `sub_080507B8`, `sub_08066B10`, `sub_0804E20C`, `sub_08035258`, `sub_080416C4`, `sub_08054494`, `sub_08035C64`
- make compare: OK

### 2026-09-17 — match_batch (+10, 511/633 linked)
- Functions: `sub_0806225C`, `sub_080688C8`, `sub_08032604`, `sub_08051444`, `sub_08037430`, `sub_0804EBF0`, `sub_0803C5DC`, `sub_0807027C`, `sub_0802E048`, `sub_0805E044`
- make compare: OK

### 2026-09-17 — match_batch (+10, 521/633 linked)
- Functions: `sub_0803C500`, `sub_080632F8`, `sub_08054CF4`, `sub_080553B8`, `sub_08063D68`, `sub_080353A0`, `sub_08038438`, `sub_080474AC`, `sub_0802D8DC`, `sub_0803FFB0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 531/633 linked)
- Functions: `sub_08052F0C`, `sub_0806DF38`, `sub_08030638`, `sub_08060D58`, `sub_08061628`, `sub_0804188C`, `sub_08069270`, `sub_0806121C`, `sub_08070188`, `sub_0803B078`
- make compare: OK

### 2026-09-17 — match_batch (+10, 541/633 linked)
- Functions: `sub_08062790`, `sub_08068EC0`, `sub_0803E0CC`, `sub_080333E4`, `sub_08072A38`, `sub_0806B2F0`, `sub_08060C30`, `sub_080429CC`, `sub_08036A68`, `sub_080593A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 551/633 linked)
- Functions: `sub_08068598`, `sub_08068418`, `sub_08062D80`, `sub_08062E88`, `sub_0806F05C`, `sub_08038F30`, `sub_0803D284`, `sub_08069A60`, `sub_0806B5C8`, `sub_0803D51C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 561/633 linked)
- Functions: `sub_08035468`, `sub_0806211C`, `sub_08030F38`, `sub_0804109C`, `sub_08067BB8`, `sub_08034420`, `sub_0803019C`, `sub_08056250`, `sub_08065CD0`, `sub_0802BAD4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 571/633 linked)
- Functions: `sub_08043C70`, `sub_0803370C`, `sub_08067648`, `sub_08040680`, `sub_08035984`, `sub_0804BD38`, `sub_0804ED90`, `sub_080411EC`, `sub_08045D3C`, `sub_0804AE94`
- make compare: OK

### 2026-09-17 — match_batch (+10, 581/633 linked)
- Functions: `sub_08043420`, `sub_0804438C`, `sub_0806A6F8`, `sub_08040F4C`, `sub_08061EF8`, `sub_0802D3F0`, `sub_080737C0`, `sub_08044648`, `sub_08066FB8`, `sub_0804C8BC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 591/633 linked)
- Functions: `sub_080444BC`, `sub_0806314C`, `sub_080447E8`, `sub_0803139C`, `sub_0804AAF0`, `sub_08068BD4`, `sub_0806EEC8`, `sub_08032908`, `sub_08035AE0`, `sub_0804D420`
- make compare: OK

### 2026-09-17 — match_batch (+10, 601/633 linked)
- Functions: `sub_0803715C`, `sub_08056D68`, `sub_080348E8`, `sub_0802DEA0`, `sub_080618EC`, `sub_08070AF8`, `sub_08070930`, `sub_08035054`, `sub_08030D4C`, `sub_08068A08`
- make compare: OK

### 2026-09-17 — match_batch (+10, 611/633 linked)
- Functions: `sub_0803DEC8`, `sub_0802DCDC`, `sub_08045EF0`, `sub_08037508`, `sub_0806E060`, `sub_08056BA4`, `sub_0802D6D4`, `sub_0806EC20`, `sub_08048DB8`, `sub_08060E48`
- make compare: OK

### 2026-09-17 — match_batch (+10, 621/633 linked)
- Functions: `sub_08053690`, `sub_08067CE8`, `sub_0806F910`, `sub_0802ECD8`, `sub_0806B764`, `sub_08033188`, `sub_080706B0`, `sub_08054120`, `sub_0806960C`, `sub_080436B0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 631/633 linked)
- Functions: `sub_08044A8C`, `sub_0806C388`, `sub_0802FA94`, `sub_08032DC4`, `sub_08046E7C`, `sub_0804DB28`, `sub_08045198`, `sub_08045590`, `sub_0806C7D4`, `sub_08043DB4`
- make compare: OK

### 2026-09-17 — match_batch (+2, 633/633 linked)
- Functions: `sub_0804FFCC`, `sub_08039BD4`
- make compare: OK

### 2026-09-19 — hand C convert (+1, 234/633 semantic)
- Function: `sub_0802C5DC` (battle Unk1694 find-and-mark lookup)
- make compare: OK

### 2026-09-20 — hand C convert batch (+6, 258/633 semantic C, 40.8%)
- Functions: `sub_0804745C`, `sub_08047594` (0x03000630/0x638 array cleanup loops),
  `sub_0805D99C`, `sub_0803FDD0` (Unk0748 slot + MainWork unk181C/unk1708 combo,
  added those struct fields), `sub_08062BF0` (BLDCNT/BLDALPHA fade loop),
  `sub_0802D598` (Unk026C reset helper)
- make compare: OK
- Skipped near-misses (60–96% byte match, agbcc register-allocation drift,
  not worth further permuter time this session): `sub_08030938`, `sub_0803DCFC`,
  `sub_08041858` (90%), `sub_08042C3C`, `sub_08061800`, `sub_0806D748`,
  `sub_080726E0`, `sub_08071B4C` (81%), `sub_080312B0` (90%), `sub_08031300`,
  `sub_08034810`, `sub_0802D52C` (72%), `sub_0802D8C4` (push/pop leaf quirk,
  likely same class as the confirmed dead-end leaf-function list)

### 2026-09-21 — permuter repair (+2 semantic C, 302/633, 47.7%)

- Fixed `tools/decomp/permuter/compile.sh`: it never passed per-function
  `/* match-flags: */`, so the **21 functions needing `-fprologue-bugfix`**
  could never reach permuter score 0. Proof: `sub_08061BDC` scored **205**
  before (agbcc emitted `push {lr}`/`pop {pc}`) and **0** after.
- Added `tools/decomp/permuter/auto.py`: fresh import → base score → bounded
  search → re-verify with `match_function.py` → integrate. Kills the worker
  pool on timeout (previously leaked processes and blocked the output pipe).
- `script_first.py` now tries parked WIP seeds first and permutes near-misses
  (`--permute-seconds`, default 120) instead of only parking them.
- `agent_packet.py` permutes near-miss/WIP seeds before asking for C, and the
  hand-retry budget is **1** attempt.
- **Matches from functions previously written off as unreachable:**
  `sub_08069988`, `sub_0806FF28` (both score 0 in 2s from their parked seeds).
- `sub_0806DEF4`: permuter reports score 0 but `match_function.py` says 95% —
  the permuter ignores branch targets. `auto.py` refuses to integrate it;
  `--strict-branches` reaches best 1. Do not trust score 0 alone.
- make compare: OK

### 2026-09-21 — close-out on three register-allocation near-misses (+0 semantic C, 302/633)

Attempted `sub_08073988` (94/96), `sub_08062A74` (74/76), `sub_08061308` (46/48)
— the top three entries in `docs/decomp-functions.md`. **No new semantic C**; all
three are already byte-identical via the naked Thumb wrappers in `src/matched/`,
so `make compare` was never at risk. The semantic-C gap is now characterised and
documented in each `src/wip/<fn>.md`.

What was tried (all negative):

- ~4,000 enumerated C variants across the three (temp types, split/absent temps,
  named shift temporaries, nested-assignment "register reservation" tricks,
  constant typing, statement reorders, declaration-order shuffles), the last
  2,300 as a randomized sweep.
- Both allowed `match-flags` (`-fomit-frame-pointer`, `-fprologue-bugfix`) — no change.
- 20 min × 8 jobs of `permuter/auto.py` per function — base score 10, never below 10.

Decisive finding for `sub_08061308` and its six-function family: for the shape
`(t << n) + (C << 19)` agbcc **always** coalesces the load into the register that
consumes it (`ldrb rX,[rX]; lsls rX,rX,#n`). Retail has `ldrb r0,[r0]; lsls r1,r0`
— the load stays in the dead address register and the shift writes a *different*
register. A synthetic sweep over 0–6 extra live values produced the coalesced form
in every configuration, so the load destination is not a free choice in the source.
The retail ROM does contain the un-coalesced idiom (52 of 443 self-reusing loads in
the full disassembly), confirming a compiler behavioural difference rather than a
source-shape difference. This is why 331/633 "matched" functions are asm wrappers,
and why siblings `sub_08060D58` / `sub_08060E48` are integrated as wrappers.

Also noted: the two attractors for `sub_08062A74` are mutually exclusive (fixing
`ldrh r2` costs `lsls r1`), and the `sub_08073988` register file is saturated at
`default_char`, so retail's constant lands in the only free register `r0` while
agbcc picks `r2`.

- `docs/decomp-queue.toml`: the three entries now say "do not re-attempt".
- make compare: OK
