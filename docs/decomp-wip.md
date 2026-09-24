# The DECOMPILED tier (`src/decompiled/`)

Unmatched C is **work**, not a failed experiment. Do not revert a function back
to naked Thumb and walk away. `src/matched/` stays MATCH-clean; the
reconstruction lives in `src/decompiled/` so the next stage can use it.

`src/decompiled/` is a first-class lifecycle tier, not a parking lot. It is the
**DECOMPILED** rung of the vocabulary in `tools/decomp/tier.py`.

## Split

| Path | What belongs there |
|------|--------------------|
| `src/matched/sub_XXXXXXXX.c` | Byte-matched semantic C **or** readable Thumb. Never a non-matching draft. |
| `src/decompiled/sub_XXXXXXXX.c` | Best C so far (may DIFF). Indexed by `analyze.py`; feed this to `match_function.py`. |
| `src/decompiled/sub_XXXXXXXX.md` | Process log: tried, score, blocker, **next step**. |
| `docs/decomp-queue.toml` `[[wip]]` | Index so `make queue` lists **Resume first**. |

`src/decompiled/` is **not** linked into the ROM. `C_SRCS` in the Makefile is
empty and nothing globs `src/**`, so nothing here can affect `make compare`.

## Lifecycle

A function is described by three independent facts, not one ladder position:

| Flag | Meaning |
|------|---------|
| `has_c` | a C seed exists — in `src/matched/` (semantic) or `src/decompiled/` |
| `named` | `analysis/symbols.json` has a confident entry with evidence |
| `matches` | compiles byte-identical to retail |

The derived tier is the highest rung reached:

```
UNKNOWN      no C seed at all (readable Thumb only)
DECOMPILED   a C seed exists, does not match yet
UNDERSTOOD   named with confidence + evidence, still does not match
MATCHING     byte-identical to retail
```

Because the flags are independent, a hard-to-match function never blocks naming,
and an unnamed function never blocks matching. `make tier` reports the spread.

## Prologue / pointer-param playbook (before parking)

When logic is right but bytes differ in the first 8–16 bytes (save order, wrong pool
register), try this **before** goto mimicry or register-named locals:

1. **Refine the prototype** — `const u8 *` / `u8 *` instead of `void *`; update
   `include/unknown-functions.h` so `match_function.py` (via `global.h`) scores the same
   binary you hand-tested standalone.
2. **Use parameters directly** — no `text = text_arg` copies unless retail spills to
   callee-saved regs before the first use.
3. **Readable control flow** — `switch` on scanned bytes often beats a goto chain from
   objdump (`TextMeasureWidth`: 94/96 goto → 96/96 switch).
4. **Dual-compiler score** — `python3 tools/decomp/try_compilers.sh sub_XXXXXXXX` or
   `test_variants.py` (defaults to both `agbcc` and `old_agbcc`).
5. **Symbol subscript for ROM tables** — `base[gData_080BB748[i]]` before
   `index = (r0 = pool)` side-effect tricks.

Details: [decomp-patterns.md](decomp-patterns.md) case study `TextMeasureWidth`.

## When to park (stop guessing)

After 1–2 serious hand attempts, or a short permuter run that does not hit score 0:

```bash
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c \
    --status "same-size DIFF; extra r8/r9 spill" \
    --next "independent per-field addressing like sub_08046230; then permuter" \
    --score "NN/MM"
make queue
```

Then restore readable Thumb in `src/matched/` if you had replaced it with a draft.

## Resume (next session)

1. `make queue` — **Resume (WIP)** is above generic recommended.
2. Read `src/decompiled/sub_XXXXXXXX.md` before rewriting anything.
3. `python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c`
4. Change the seed, re-run, **update the `.md`** (append a process line; do not delete old ones).
5. On MATCH: `integrate_c.py` as usual, then delete the `src/decompiled/` pair and the `[[wip]]` row.

## Naming is independent of matching

A parked seed is fully eligible for naming. `analysis/functions.json` indexes it
with callers, callees and RAM references like any matched function, so the
naming pass can give it a readable name long before it byte-matches:

```bash
python3 tools/decomp/symbols.py set sub_XXXXXXXX --symbol SomeName \
    --confidence 0.7 --source ai --evidence "…"
python3 tools/decomp/symbols.py apply
```

That is the point of the tier: progress on understanding is not gated on
progress on bytes.

## Notes file (required sections)

Copy the template in `src/decompiled/README.md`. Minimum:

- **Role** — what the function does in one sentence
- **Process** — dated attempts (shape tried, score, why it failed)
- **Current state** — matched vs retail (size, prologue, remaining DIFF)
- **Next** — one concrete action, not “try more C”

## Queue state

`docs/decomp-queue.toml` is machine state, not prose: `agent_packet.py --next` reads
it to decide what to offer. Two keys matter beyond `status`/`next`/`score`:

| Key | Meaning |
|-----|---------|
| `retry = false` | Documented as unreachable by hand *and* by permuter. `--next` skips it; `park_wip.py --exhausted` writes it. Override with `agent_packet.py --next --force-exhausted`. |
| (none) | Still live. The default. |

A `retry = false` claim must rest on evidence you would defend: a source-shape
sweep plus a permuter run against the **semantic** seed. `make queue` /
`next_queue.py` and `queue_toml.py --check` both refuse to work on a queue that has
been corrupted, and `park_wip.py` now *updates* an existing block instead of
ignoring the name — a re-park used to leave the old `status`/`next`/`score` in
place, so the queue kept advertising work a previous session had already exhausted.

## Anti-patterns

- Reverting `src/matched/` to naked asm **without** a `src/decompiled/` seed
- Logging a near-miss only in `decomp-status.md` (that log is not a resume queue)
- Leaving a non-matching draft in `src/matched/` (breaks the semantic audit)
- Rewriting a parked function from disasm without reading the `.md` first
- Hand-editing `src/decompiled/*.c` names directly instead of via `symbols.py`
- Quoting a permuter score without checking which seed it ran on — a permuter that
  imported the asm wrapper reports a large base score and proves nothing
