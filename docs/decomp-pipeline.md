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
`make audit`, `make repair-signatures`, `make audit-drafts`, `make repair-drafts`.

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


## Non-negotiables

- **`make compare` stays `OK`.** It is the only objective correctness signal for
  the ROM.
- **`make audit` reports `0` failures.** `make compare` cannot see the C, so the
  C corpus needs its own gate.
- The naming layer is alias-only: no file renames, no manifest changes, no
  linker edits. A hard-rename command is explicitly out of scope.
- A wrong name must stay cheap to revert — guaranteed by the generated-view
  design, since `symbols.json` is the only place a name lives.
- `analysis/*.json` must be idempotent.
- Grouping in `systems.json` is seeded deterministically from objective evidence
  (hardware address ranges, specific named RAM symbols), never from guesses.
  Batch bookkeeping notes such as `battle/readable-thumb` are explicitly *not*
  treated as subsystem evidence.
