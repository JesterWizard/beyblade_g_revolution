# ROM → decomp project pipeline

The goal is not "byte-match everything" as a gate. It is to progressively turn an
opaque ROM into a navigable codebase where **progress on understanding is not
gated on progress on bytes**.

Byte-matching is one axis. Naming is another. Documentation is a third. They
advance in parallel, and no single hard function blocks the pipeline.

## The four stages

```
baserom.gba
    │
    ├─ 1. ROM → ASM          deterministic    asm/, ELF, .map, size cache
    │
    ├─ 2. ASM → C            deterministic +  src/matched/ (matching)
    │                        AI               src/decompiled/ (drafts)
    │
    ├─ 3. analyse            deterministic    analysis/*.json
    │                                            call graph, RAM refs, structs, systems
    ├─ 4. name               AI, evidenced    analysis/symbols.json
    │                                            → include/symbols.h, [renames]
    └─ 5. document           generated        docs/systems/, docs/functions/
                                                 → make compare OK
```

Stage 1 and the deterministic half of stage 2 already exist. Stages 3–5 are the
pipeline added on top.

## Lifecycle vocabulary

One enum lives in `tools/decomp/tier.py`. Every tool imports it; nothing
hardcodes status strings.

A function has three **independent** flags:

| Flag | Meaning |
|------|---------|
| `has_c` | a C seed exists — `src/matched/` (semantic) or `src/decompiled/` |
| `named` | `analysis/symbols.json` entry with confidence ≥ 0.5 *and* ≥1 evidence line |
| `matches` | status is `matched` / `identical_diff` |

The derived tier is the **highest rung reached**:

```
UNKNOWN ──▶ DECOMPILED ──▶ UNDERSTOOD ──▶ MATCHING
 no C        C seed,         named,          byte-identical
             no match        no match        (top)
```

`make tier` prints the spread. Because the flags are independent, a function can
be `UNDERSTOOD` for a long time and that still counts as real progress.

## The analysis database (`analysis/`)

Deterministic, model-free, idempotent. `decomp analyze` (or `make analyze`)
rebuilds it from the ROM, the disassembly, and the build artifacts.

| File | Contents |
|------|----------|
| `functions.json` | 633 rows: size, tier, status, `callers[]`, `callees[]`, `ram_refs[]`, `ram_names[]`, `data_refs[]`, `pool[]`, `offsets[]`, `insn_count`, `system` |
| `xrefs.json` | bidirectional call graph, data references, unresolved external callees |
| `structs.json` | struct field offsets and widths, plus an offset-level access index |
| `systems.json` | subsystem membership with the evidence for each assignment |

The genuinely new product is the **global call graph**. Before this, callee
extraction was transient inside `agent_packet.py` and a callee→callers index
existed only for undeclared labels.

Idempotence is enforced: `python3 tools/decomp/analyze.py --check` runs it twice
and fails if anything but the timestamp moved.

## The naming layer (`analysis/symbols.json`)

Names live in **data**, never in source. Source, headers, and config are all
generated *views*, so re-running a naming pass is never destructive.

```json
{
  "0x0802B8BC": {
    "symbol": "GetIndexedRecordWord",
    "aliases": ["sub_0802B8BC"],
    "kind": "function",
    "confidence": 0.6,
    "source": "ai",
    "evidence": ["a is a u16 index scaled by 4 into a record array at gUnk_03000264"],
    "updated": "2026-09-22"
  }
}
```

Provenance is `auto` < `ai` < `human`. **A lower-provenance pass may never
overwrite a higher one** — that is what makes repeated automated naming safe.

Names reach the compiler as macros, never as renamed symbols:

```c
#define GetIndexedRecordWord sub_0802B8BC
```

so `src/matched/sub_0802B8BC.c` reads as `u16 GetIndexedRecordWord(s32 a)` while
the preprocessor still emits `sub_0802B8BC`. The ROM, the linker script, and
`make compare` are untouched by construction.

### Vocabulary

This is a licensed game, and its vocabulary is evidence. Reach for the game's own
words before inventing a mechanical one: *beyblade/blade*, *battle* (`Btl`),
*bit-beast*, *part*, *roster*, *arena*, *team*, *spin*, alongside the system words
already in use (`Text`, `Bg`, `Vram`, `Heap`, `Timer`, `Mem`, `Gfx`, `Sfx`).

A prefix is a **claim**, not decoration. `Btl*` says "this belongs to the battle
subsystem", and the subsystem grouping in `systems.json` and `docs/systems/` will
be read that way by everyone afterwards. So a wrong prefix is worse than an
honest `Unk`: `sub_0806A434` sat as `BtlObjFree` while being the *generic two-region
heap free* (`0x03000B30` EWRAM list / `0x03003F44` IWRAM list, 25 callers spanning
battle, VRAM teardown and text), which misfiles it for every reader. Names proven
from callers beat names inferred from a prefix that was already there.

- `Unk<ADDR>` / `Unk<OFFSET>` (e.g. `BtlUnk1694FindAndMark`) is the honest fallback
  when the structure is known and the meaning is not. Discouraged: `Unk<STRIDE>`
  (`Unk84FindIndexByKey`) — the number should identify *where the data is*, not how
  wide a record is, or it cannot be looked up later.
- Name the **type** even when the address must stay a literal
  (`struct BeybladeDef`, not `struct Unk75AB8`). A ROM table usually cannot be
  converted to a data symbol without changing codegen — see the note at the top of
  `asm/data_symbols.s` — but the struct costs nothing and carries the meaning.
- Prefer what the caller *does* with a value over what the code looks like. The
  62-entry table at `0x08075AB8` only became a roster because `sub_08044648` walks
  an id list and stores `obj+0xD4 = id`; and `+0x00` only became a profile id
  because it selects which shared parameter block is used.
- Every name needs `--confidence` and at least one `--evidence` line, ideally
  naming the caller or the address that proves it.

### The one real hazard: string literals

`symbols.py apply` rewrites source text **outside** strings, character literals,
and comments. This is not cosmetic caution — 272 files carry Thumb mnemonics
inside `asm("...")` string literals, and the preprocessor does **not** expand
macros inside a string. Rewriting `bl sub_08067B98` to `bl DebugPrint` inside
such a literal emits a reference to a symbol that does not exist.

Collision detection additionally refuses to emit a macro whose name is already
defined by anything in `include/`, is a C keyword, or duplicates another symbol.
Refused names are recorded as a comment block in `include/symbols.h`.

## Documentation (`docs/systems/`, `docs/functions/`)

Generated views of the analysis database and the symbol layer.

| Path | Contents |
|------|----------|
| `docs/systems/index.md` | subsystem overview |
| `docs/systems/<system>.md` | member functions with tiers, RAM, call counts, and why they are grouped |
| `docs/functions/index.md` | every function, by readable name and address |
| `docs/functions/<Name>.md` | one page per *named* function |

Unnamed functions get no page — there is nothing readable to title it with — but
they still appear in the index and on their subsystem page. `--all` emits a page
for everything.

The scoreboard `docs/decomp-functions.md` is unchanged and stays the
"how much is done" view.

## Commands

```bash
./decomp setup <rom>      # install the ROM, bootstrap, first compare
./decomp analyze          # rebuild analysis/*.json
./decomp decompile        # deterministic pass + one AI packet
./decomp rename list      # symbol layer
./decomp rename set sub_XXXXXXXX --symbol Name --confidence 0.8 --evidence "…"
./decomp rename apply     # rewrite source to use the readable names
./decomp document         # regenerate docs/systems/ and docs/functions/
./decomp verify           # match_function + make compare
./decomp status           # lifecycle tier table
```

Every stage is also directly runnable and has a `make` target:
`make analyze`, `make symbols`, `make tier`, `make document`, `make status`,
`make audit`, `make repair-signatures`, `make audit-drafts`, `make repair-drafts`,
`make prune-drafts`, `make signatures`, `make fix-stub-arities`,
`make sync-verified`, `make check-verified`.

## Verifying the C corpus itself

`make compare` proves the **ROM** is reproduced. It does **not** prove the C is
valid, because matched C is never linked — the Makefile's `C_SRCS` is empty and
the ROM links generated `asm/matchings/*.s` at fixed VMAs. A file can therefore be
counted as matched while not compiling at all.

`make audit` closes that gap: it compiles every `src/matched/*.c` standalone
through agbcc (honouring each file's `match-flags` / `match-compiler` comments)
and reports the first diagnostic. It must report **0 failures**.

The dominant defect it finds is a signature that disagrees with
`include/unknown-functions.h` — usually a `__attribute__((naked))` wrapper declared
`(void)` against a real parameter list. `make repair-signatures` copies the
prototype's return type and parameter list into the definition, re-runs
`match_function.py` on every file it touches, and reverts any whose match
regresses, since a signature change *can* alter codegen for an ordinary function.

### Drafts

`src/decompiled/` is not linked either, and is held to a lower bar: a draft is a
record of a decompilation attempt, so it must **compile**, not match.
`make audit-drafts` reports where that fails, and `make repair-drafts` applies the
same signature repair with the verification swapped — a draft is kept if it
compiles afterwards, reverted if it still does not. Nothing here gates
`make audit`.

These are *not* mass-fixed on purpose. Several cross-function `conflicting types`
failures mean the draft's guess at a callee's signature is better than the
header's, so rewriting the draft to agree with the header would throw away the
draft's information. They are triaged per file.

### The semantic counter has its own allowlist

`file_kind()` guesses "semantic" from the text of `src/matched/*.c` (a semantic
body contains no `asm()`), which is trivially wrong in both directions, so
`progress.py` and `tier.py` demote a text-guess to `asm` unless the function is
listed in `build/semantic_verified.json`. The list is the authority.

Only `matched_rescore.py --write-verified` used to write it, which meant semantic C
that landed any other way was **invisible to the progress counter**: the byte-match
count moved, the semantic-C milestone did not. Six functions were in that state —
five BIOS wrappers (`sub_080674A0`..`sub_080674B4`, converted by hand-editing
`src/matched/`) plus a permuter integration. The count was 403 when the manifest
already said 412.

- `integrate_c.py` now records every semantic function it lands, so the permuter
  and script-first paths stay correct by construction.
- `make sync-verified` / `make check-verified` repair and gate the list for
  hand-edited files; `check-verified` exits 1 when it is out of step.

A hand edit to `src/matched/*.c` is the one path that still bypasses the record, so
run `make check-verified` after one.

### Retiring superseded drafts

A draft only means something while the function is unmatched. Once
`src/matched/<name>.c` holds **semantic** C, the draft in `src/decompiled/` is a
stale duplicate: the DECOMPILED tier is inflated by work that already landed, and
`docs/decomp-queue.toml` keeps a `[[wip]]` task for a function that is done.

`make prune-drafts` (dry run: `python3 tools/decomp/prune_drafts.py`) deletes the
draft `.c`, the matching `[[wip]]` queue block, and the draft's `.md` note **when
that note is still the generated stub from `park_wip.py`**. Hand-written notes are
kept, and a readable-Thumb wrapper does *not* count as superseding a draft — the
draft may be the only C that exists. The queue is edited block-wise (line-initial
`[[section]]` headers), never by regex over text, because status notes contain
brackets like `[r2]` that would split a block.

The first pass retired 85 drafts, 83 stub notes and 90 stale queue blocks
(227 → 137 `[[wip]]` entries).

## The permuter's seed path

The local permuter can only reshuffle correct C, so it has to be handed the parked
draft — not the readable-Thumb wrapper in `src/matched/`. It was handed the wrapper
for a whole day: `tools/decomp/permuter/import_function.py` still declared
`WIP = ROOT / "src" / "wip"` after `src/wip/` was promoted to `src/decompiled/`, so
`seed_c()`, `match_flags()` and `match_compiler()` all missed the draft and fell
through to `src/matched/`.

The failure is silent and expensive, and every symptom is visible in a run's header:

| Symptom | Cause |
|---------|-------|
| `base score 100` on a function that scores ~20 bytes off | the base was the asm wrapper, so the permuter randomises assembly |
| `match-compiler: agbcc` when the seed says `old_agbcc` | `match_compiler()` searched the same dead path for the sidecar comment |
| `No perm macros found. Defaulting to randomization.` | an asm body has no perm macros to permute |

Two runs recorded on 2026-09-22 were therefore void. Anything recorded *before* the
promotion is unaffected. When a directory is promoted, grep for the old path in
`tools/` — the schema (`build/`, `analysis/`) can be migrated while one loader is
missed, and nothing in `make compare` or `make audit` will notice.

## A permuter run outlives the batch that started it

`run_permuter` spawns `permuter.py` with `start_new_session=True` so that
`_kill_group` can reach the whole worker pool on timeout. That is correct, but it
also detaches the pool from any signal the *caller* receives: when `timeout 900`
SIGTERMs the batch, the `except TimeoutExpired` branch never runs and eight workers
keep permuting forever. Two such trees were found alive after ~2.7 h, holding the
load average at 19.6 on 8 cores and slowing every later batch.

They also hang the next command rather than failing it. The workers inherit the
batch's stdout pipe, so a pipeline like `script_first.py | tail` never sees EOF:
the shell waits on a writer that no longer has a reader. The fix is two-sided.

- `reap_stale_permuters()` (called at the start of `auto.run_permuter`,
  `script_first.main`, `agent_packet.main`) kills only processes carrying our
  `permuter.py` path whose parent is not in the current ancestor chain.
- `run_permuter` installs SIGTERM/SIGINT/SIGHUP handlers that `_kill_group` the
  worker pool and then re-raise the default disposition.

Rule of thumb: never launch a child into a new session without forwarding the
signals you expect to die from. Batch output also goes to a file, not a pipe, so a
survivor cannot wedge the shell.

## Queue state

`decomp-queue.toml` is read by `agent_packet.py --next` to choose the next target,
so it is machine state with prose in it. `park_wip.py` used to write a block only
when the name was *new*, which meant re-parking a function left the previous
`status`/`next`/`score` in place. That is how `--next` came to offer
`sub_08031300` while its notes said "do not re-attempt by hand or by permuter": the
picker read the stale half.

- `park_wip.py` now upserts (`queue_toml.upsert_block`), rewriting only the fields
  it is given and preserving the rest of the file byte for byte.
- `park_wip.py --exhausted` writes `retry = false`; `agent_packet.py --next` skips
  those names unless `--force-exhausted` is passed.
- All queue edits go through `queue_toml.py`, which splits the file at *line-initial*
  `[[section]]` headers. A regex over the whole text tears blocks apart on the
  brackets in a status note (`[r2]`, `[sp, #8]`) — that produced a torn block and a
  TOML parse error caught by `next_queue.py`.
- `queue_toml.py --check` asserts the invariants: split/join is the identity, and
  rewriting every field with its own parsed value is a no-op.

## Agreeing on arity

Compiling is necessary but not sufficient: a file can compile perfectly while
*lying* about a function it defines or calls. `sub_080674B4` was declared `()` and
defined `(const void *src, void *dest)` while all 38 call sites passed nothing —
it was BIOS VBlankIntrWait. Every gate stayed green, because each file compiles in
isolation and the C is never linked.

`make signatures` cross-checks the three sources of truth per function:
`include/unknown-functions.h` prototypes, the definitions in `src/matched/*.c`, and
every call site in `src/matched/` + `src/decompiled/`. Where they disagree it
reports the function once, with each claim and its source, rather than a wall of
call-site lines.

Weights decide who is right, because the sources are not equally trustworthy:

| Source | Weight |
|--------|--------|
| header prototype | 3 |
| local prototype in a caller | 2 |
| semantic definition | 2 |
| call site | 1 |
| readable-Thumb asm stub definition | 0 |

An asm stub ranks *below* a call site deliberately: it says `(void)` only because
its body ignores the registers, which makes it a placeholder rather than a claim.
A signature that is deliberately open (`void f();` / `f(...)`, e.g. the stripped
`DebugPrint` stubs) is never reported, since varying arity is its whole point.

`make fix-stub-arities` then repairs the stubs this finds: it takes the parameter
list from the best prototype stating the agreed arity and rewrites the stub. A stub
is its own translation unit, so a type named only in some caller's local prototype
is *not* visible there — candidate parameter lists are therefore tried in order
(header, then local prototype, then opaque `void *` pointers) and the first that
still byte-matches is kept. Every change is re-verified with `match_function.py`
and reverted if the bytes move.

Arity repair must not change what a file *is*. `sub_080674B4` (VBlankIntrWait) is
the cautionary case: it was semantic C using an `asm("swi 5")` wrapper with two
dummy pointer parameters, and the honest `(void)` signature is not byte-reproducible
from an empty parameter list, because the original's `movs r2, #0` only lands in
`r2` while `r0`/`r1` are occupied. Rewriting it as a `__attribute__((naked))`
wrapper "fixed" the signature but reclassified the file as readable Thumb — a real
match traded for cosmetic honesty, and the count dropped 413 → 412. The fix that
keeps both is an empty parameter list plus the clobber list the ABI justifies:

```c
void VBlankIntrWait(void)
{
    asm("swi 5" : : "r"(0) : "r0", "r1");
}
```

The clobbers say what the BIOS ABI says (r0–r3 belong to SWI input/result), and
they also free `r2` for the zero. Rule of thumb: when a signature fix would move a
file between `opcode_stubs.file_kind()` categories, find the semantic form first.


## Non-negotiables

- **`make compare` stays `OK`.** It is the only objective correctness signal for
  the ROM.
- **`make audit` reports `0` failures.** `make compare` cannot see the C, so the
  C corpus needs its own gate.
- **`make signatures` reports `0` conflicts.** Compiling is not the same as
  agreeing: a function can compile everywhere and still be declared, defined and
  called three different ways.
- **Arity repair never reclassifies a file.** A semantic match stays semantic C;
  `opcode_stubs.file_kind()` must not move as a side effect of a signature fix.
- **`src/decompiled/` holds no draft whose function already matches semantically.**
  `make prune-drafts` is the gate; a stale draft inflates DECOMPILED and leaves a
  dead `[[wip]]` task in the queue.
- The naming layer is alias-only: no file renames, no manifest changes, no
  linker edits. A hard-rename command is explicitly out of scope.
- A wrong name must stay cheap to revert — guaranteed by the generated-view
  design, since `symbols.json` is the only place a name lives.
- **Prefer the game's vocabulary, and do not borrow a prefix you cannot support.**
  A prefix is a claim: `Btl*` files a function into the battle subsystem for every
  later reader and for `docs/systems/`. `BtlObjFree` was the *generic heap free*
  for 25 callers across battle, VRAM and text; `Unk<ADDR>` would have been honest,
  and `Heap*` is correct. See [Vocabulary](#vocabulary).
- `analysis/*.json` must be idempotent.
- Grouping in `systems.json` is seeded deterministically from objective evidence
  (hardware address ranges, specific named RAM symbols), never from guesses.
  Batch bookkeeping notes such as `battle/readable-thumb` are explicitly *not*
  treated as subsystem evidence.
- Note hints are the weakest tier and are matched as plain substrings, so a hint
  must not be a word that appears in another sense. Bare `"key"` filed five
  table-lookup helpers under `input` because their notes read "lookup by key";
  the hint is now `keyinput`/`button`/`held` and friends. When a hint produces a
  subsystem whose members share nothing else, suspect the hint before the members.
