# Parking incomplete decomp (WIP)

Unmatched C is **work**, not a failed experiment. Do not revert a function
back to naked Thumb and walk away. `src/matched/` stays MATCH-clean;
the reconstruction lives in `src/wip/` so the next session can resume.

## Split

| Path | What belongs there |
|------|--------------------|
| `src/matched/sub_XXXXXXXX.c` | Byte-matched semantic C **or** readable Thumb. Never a non-matching draft. |
| `src/wip/sub_XXXXXXXX.c` | Best C so far (may DIFF). Feed this to `match_function.py`. |
| `src/wip/sub_XXXXXXXX.md` | Process log: tried, score, blocker, **next step**. |
| `docs/decomp-queue.toml` `[[wip]]` | Index so `make queue` lists **Resume first**. |

`src/wip/` is **not** linked into the ROM (`Makefile` `C_SRCS` does not pick it up). Parking cannot break `make compare`.

## When to park (stop guessing)

After 1–2 serious hand attempts, or a short permuter run that does not hit score 0:

```bash
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c \
    --status "same-size DIFF; extra r8/r9 spill" \
    --next "independent per-field addressing like sub_08046230; then permuter" \
    --score "NN/MM"
make queue
```

Then restore readable Thumb in `src/matched/` if you had replaced it with a draft.

## Resume (next session)

1. `make queue` — **Resume (WIP)** is above generic recommended.
2. Read `src/wip/sub_XXXXXXXX.md` before rewriting anything.
3. `python3 tools/decomp/match_function.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c`
4. Change the seed, re-run, **update the `.md`** (append a process line; do not delete old ones).
5. On MATCH: `integrate_c.py` as usual, then delete the `src/wip/` pair and the `[[wip]]` row.

## Notes file (required sections)

Copy the template in `src/wip/README.md`. Minimum:

- **Role** — what the function does in one sentence
- **Process** — dated attempts (shape tried, score, why it failed)
- **Current state** — matched vs retail (size, prologue, remaining DIFF)
- **Next** — one concrete action, not “try more C”

## Anti-patterns

- Reverting `src/matched/` to naked asm **without** a `src/wip/` seed
- Logging a near-miss only in `decomp-status.md` (that log is not a resume queue)
- Leaving a non-matching draft in `src/matched/` (breaks semantic audit / progress counts)
- Rewriting a parked function from disasm without reading the `.md` first
