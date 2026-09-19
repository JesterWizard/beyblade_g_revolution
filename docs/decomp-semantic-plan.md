# Semantic-C conversion plan (handoff doc)

**Purpose**: a categorization any agent can pick up cold, run one command
against, and get a prioritized worklist of functions to convert from
readable-Thumb (`__attribute__((naked))` asm wrapper) to semantic C. Refresh
this doc's numbers by re-running the classifier — don't hand-maintain the
counts below.

Current state (2026-09-19): 234/633 functions are semantic C. Of the
remaining 399 readable-Thumb functions, **all of them are already
byte-matched at the asm level** (`asm/matchings/*.s` exists for every one) —
there is no more assembly-matching work left, only semantic-C conversion.
`match_batch.sh`/`cursor_batch.sh` will correctly report "nothing to do" for
this reason; that is not a bug (see `tools/decomp/triage_functions.py`'s
docstring).

## Run this first

```bash
python3 tools/decomp/classify_semantic_targets.py
```

Buckets (all counts as of 2026-09-19; re-run for current numbers — an earlier
version of the classifier undercounted `unblock_first`/`cse_risk` because it
didn't normalize the two source styles `src/matched/*.c` uses for the asm
string literal; fixed now, these numbers are from the corrected version):

| Bucket | Count | What it means | Do this |
|---|---|---|---|
| `unblock_first` | 35 | Calls a bare-label symbol (`bl _XXXXXXXX`) with no prototype anywhere in `include/*.h` yet | **Start here.** One declaration unblocks every caller — see below |
| `small_clean` | 117 | ≤40 real instructions, no r8–r12, no missing symbols | **Best ROI.** Straightforward hand-conversion |
| `large` | 119 | >40 real instructions, otherwise clean | Doable, budget more time per function; break into sub-blocks mentally |
| `high_reg_pressure` | 126 | Touches r8–r12 (`mov rX, r8`/`r9`/`r10`/`r12`) | agbcc's allocator is touchy here — expect a few hand-write attempts to land within 80–95% byte match and stall; budget permuter time, don't force it |
| `naked_only` | 2 | Structurally can't become plain C (ARM/Thumb interworking veneer, raw variadic stack splice) | **Skip.** Not a decomp gap, just leave as asm |

Plus a cross-cutting **`--cse-risk`** tag (16 functions currently) that
applies on top of any bucket above — see "Known trap" below.

## Step 1 — unblock_first (do this before anything else)

```bash
python3 tools/decomp/classify_semantic_targets.py --symbols
```

This groups the 35 blocked functions by the missing symbol. As of writing:

```
_08073C48    blocks   8 callers
_080740B0    blocks   5 callers
_080741EC    blocks   4 callers   <-- NOTE: see below, this one is a real bug
_080563A8    blocks   3 callers
_0802BA7C    blocks   2 callers   <-- this is the one from sub_0802BAD4/BC14 last session
_0803DE00    blocks   2 callers
_08075A58    blocks   2 callers
_0802D058    blocks   1 caller
_08056428    blocks   1 caller
_08032458    blocks   1 caller
_080672A8    blocks   1 caller
_0803E9A4    blocks   1 caller
_080408E4    blocks   1 caller
_0805FED4    blocks   1 caller
_08041E88    blocks   1 caller
_080505AC    blocks   1 caller
_0806D998    blocks   1 caller
_08073C64    blocks   1 caller
```

Highest leverage: `_08073C48` (8 callers) and `_080740B0` (5 callers) —
declare those two first.

**Every one of these is a bare Luvdis label inside another function's ROM
range, not a structural blocker.** This project already has a working
pattern for this (`_08073C40`/`_08073C44`/`_08073C4C` are declared in
`include/unknown-functions.h:164-166` and used freely, e.g.
`src/matched/sub_0802DEA0.c`-style calls). To unblock a symbol:

1. Find a call site (`grep -rn "bl _080741EC" src/matched/ asm/nonmatchings/`)
   and read the registers going in/out to guess the signature (arg count,
   signedness, return use).
2. Add one line to `include/unknown-functions.h` in the same style as the
   `_08073C4X` cluster, e.g. `s32 _080741EC(s32 a, u32 b);`.
3. Re-run `make compare` — it should still be `OK` (declaring a prototype
   changes nothing about the linked bytes).
4. That symbol drops out of `unblock_first` and its callers move into
   whichever bucket they actually belong in.

**Known bug in this batch**: `_080741EC` is a bare label with no matching
declaration, but `include/unknown-functions.h:168` already declares
`s32 sub_080741EC(u32 a, u32 b);` — a *different* name at what looks like the
same address. That's almost certainly a stale/incorrect rename from an
earlier session, not a second real function. Whoever picks up `_080741EC`
should confirm whether `sub_080741EC` is dead (nothing calls it) and if so
either delete it or fix its name to match the real label.

## Step 2 — small_clean (best ROI)

```bash
python3 tools/decomp/classify_semantic_targets.py --bucket small_clean
```

Pick from the top. These typically have:
- an already-`struct`-typed pointer arg (check `include/unknown-types.h`
  first — most of the state this codebase touches already has a named
  struct; don't invent offset-casts, extend the existing struct instead)
- a handful of `if`/branch blocks, no loops with heavy register shuffling

Workflow per function (same as `sub_0802C5DC` in `docs/decomp-status.md`):
1. Read the `asm(...)` body, map each `ldr/str [reg, #imm]` to a struct
   field (grep `include/unknown-types.h` for the struct first).
2. Write semantic C by hand.
3. `python3 tools/decomp/match_function.py <fn> <scratch.c>` — iterate on
   statement order until `MATCH`.
4. `python3 tools/decomp/integrate_c.py <fn> "@<scratch.c-or-body-file>" --note "<one line>"`
   — this recompiles through the *real* project headers and re-links, which
   is the authoritative check (see "Known trap" — `match_function.py` alone
   can lie).
5. Append one line to `docs/decomp-status.md`, commit per the repo's commit
   policy (after every successful integration; never if `make compare`
   fails).

## Step 3 — large

Same workflow as `small_clean`, just budget more read time to map all the
fields before writing any C. Good candidate for splitting across a few
short sessions per function rather than rushing.

## Step 4 — high_reg_pressure (approach differently)

Don't hand-write-and-iterate blindly here — agbcc's register allocator for
r8–r12 spill/reuse is sensitive to code shape in ways that aren't visibly
motivated by the C. If a hand-written version gets close (80%+ byte match,
same size) but won't close the last few bytes after 2-3 tries:

```bash
python3 tools/decomp/permuter/import_function.py <fn>
bash tools/decomp/permuter/permute.sh bg nonmatchings/<fn> -j 4 --stop-on-zero
# check back later:
tail -f nonmatchings/<fn>/permute.log
```

**Caveat proven this session (`sub_0802C62C`)**: the permuter compiles in
isolation with its own minimal typedefs, not the project's real
`include/global.h`. It can report a genuine 0-diff match that then *fails*
when the same C is compiled through the real headers, because agbcc's
register allocation is sensitive to unrelated declarations earlier in the
same translation unit. Treat a permuter zero-score as "probably right,
verify through `integrate_c.py` before trusting it" — if it doesn't survive
that, the permuter needs to be re-seeded with real headers in
`tools/decomp/permuter/compile.sh` (not yet done; would be a good
infrastructure task for whoever hits this repeatedly).

## Known trap: CSE risk (register-agnostic, cuts across buckets)

```bash
python3 tools/decomp/classify_semantic_targets.py --cse-risk
```

Flags functions where retail's asm reloads the same base pointer + field
3+ times across sibling `if` blocks instead of caching it once — e.g.
`ldr r0,[r4]; ldr r1,[r0,#0xC]` repeated with different offsets each time.

If your C naturally writes `base->field` (a macro like `gUnk_0300026C` or a
local pointer) more than once, agbcc's `-O2` will common-subexpression-hoist
the *first* reload and reuse the cached register for the rest — producing
code that's logically identical but a few bytes shorter than retail, which
never converges to a byte match no matter how you reorder statements.

Confirmed on `sub_0802DEA0` this session: hand-written C using
`gUnk_0300026C->fieldN` came out 396 bytes vs retail's 424, stable across
several rewrites (including forcing a `volatile` re-read, which overshot to
560 bytes instead). **Don't sink time re-deriving this by hand** — either
accept the permuter-caveat workflow above, or skip it for now and note it in
your batch report so the next agent doesn't repeat the investigation.

Current flagged list: `sub_0802D52C`, `sub_0802D6D4`, `sub_0802DCDC`,
`sub_0802DEA0`, `sub_0802E048`, `sub_080302E0`, `sub_080353A0`,
`sub_08038D68`, `sub_08038F30`, `sub_080436B0`, `sub_08056D68`,
`sub_080593A4`, `sub_08062F90`, `sub_08066224`, `sub_08067CE8`,
`sub_0806C388`.

## Quick reference — all commands

```bash
# Overview + counts
python3 tools/decomp/classify_semantic_targets.py

# One bucket's function list
python3 tools/decomp/classify_semantic_targets.py --bucket small_clean

# Which symbols to declare first, and who they unblock
python3 tools/decomp/classify_semantic_targets.py --symbols

# Functions at risk of the CSE-hoisting trap above
python3 tools/decomp/classify_semantic_targets.py --cse-risk

# Verify a hand-written candidate (isolated compile, fast iteration)
python3 tools/decomp/match_function.py <fn> <scratch.c>

# Land a verified match (recompiles through real headers + relinks + make compare)
python3 tools/decomp/integrate_c.py <fn> "@<file-with-just-the-function>" --note "<summary>"

# Overall progress
python3 tools/decomp/report_status.py
```
