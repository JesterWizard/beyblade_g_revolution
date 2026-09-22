# Decompiled C (not linked)

Unmatched semantic C: every function that has a C representation but does not
yet compile byte-identical to retail. This is the **DECOMPILED** tier — see
`tools/decomp/tier.py` for the lifecycle vocabulary.

These files are real work, not failures. They are:

- readable — close to the original logic, transcribed from the disassembly
- navigable — indexed in `analysis/functions.json` with callers, callees and
  RAM references
- named — picked up by the symbol layer like any other function

They are **not linked**. `C_SRCS` in the Makefile is empty and nothing globs
`src/**`, so nothing here can affect `make compare`.

Promote a seed once it byte-matches:

```bash
python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
python3 tools/decomp/integrate_c.py sub_XXXXXXXX @src/decompiled/sub_XXXXXXXX.c \
    --kind semantic --note "…"
```

Park a new draft with `tools/decomp/park_wip.py`.

## Notes template (`src/decompiled/sub_XXXXXXXX.md`)

```markdown
# sub_XXXXXXXX — WIP

| | |
|--|--|
| ROM | `0x080XXXXX` |
| Retail | NB |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_XXXXXXXX.c` |
| Last `match_function.py` | STATUS, N/M bytes |
| Sibling / types | |

## Role

## Process

- YYYY-MM-DD — …

## Current state

## Next
```
