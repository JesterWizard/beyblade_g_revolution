# Beyblade G Revolution

Decompilation scaffold for *Beyblade G Revolution* (GBA), structured after [pret/pokeemerald](https://github.com/pret/pokeemerald). Custom hacks follow the [ygodm8](https://github.com/JesterWizard/ygodm8) pattern: append ROM past the retail image, LynJump hooks, and `configs/runtime.c` toggles.

## Status

<!-- decomp-progress:start -->

Decompiled C is **71.2%** of functions (451/633) and **36.5%** of original function bytes (32,988/90,272).

| Metric | | Percent | Count |
| :--- | :--- | ---: | ---: |
| Decompiled C (functions) | `███████████████████████░░░░░░░░░` | **71.2%** | 451/633 |
| Decompiled C (bytes) | `████████████░░░░░░░░░░░░░░░░░░░░` | **36.5%** | 32,988/90,272 |
| Not opcode (functions) | `████████████████████████████████` | **100.0%** | 633/633 |
| Not opcode (bytes) | `████████████████████████████████` | **100.0%** | 90,272/90,272 |
| Linked in ROM | `████████████████████████████████` | **100.0%** | 633/633 |

| Kind | Functions | Bytes |
| :--- | ---: | ---: |
| Semantic C | 451 (71.2%) | 32,988 (36.5%) |
| Readable Thumb | 182 (28.8%) | 57,284 (63.5%) |
| Opcode embed | 0 (0.0%) | 0 (0.0%) |

Battle: **53.1%** functions / **23.8%** bytes in semantic C (85/160; 0 opcode left).

Opcode `.byte` embeds are the retail machine code and do not count as decompiled C. Readable Thumb is matching asm. Unmatched ROM ranges stay `.incbin`'d from `baserom.gba` so `make compare` can stay green. Refresh with `python3 tools/decomp/progress.py --write` or `make progress`. Per-function scores: [`docs/decomp-functions.md`](docs/decomp-functions.md).

<!-- decomp-progress:end -->

## Quick start

See [INSTALL.md](INSTALL.md).

```bash
# after placing baserom.gba
make compare          # vanilla rebuild (default HACKS=0)
make HACKS=1 modern   # link append ROM (runtime + src_custom)
```

## Decompilation

All 633 functions are already in the ROM peel (`make compare` green). What remains
is not one grind but **four parallel axes**: semantic C, an analysis database,
evidenced names, and generated documentation. Byte-matching is one axis — progress
on names is *not* gated on matching bytes. Full design:
[docs/decomp-pipeline.md](docs/decomp-pipeline.md). Agent notes: [AGENTS.md](AGENTS.md).

| Axis | Question it answers | Where it lives |
|------|--------------------|----------------|
| **Matching** | does the C compile byte-identical? | `src/matched/*.c` |
| **Drafts** | what is the best C so far? | `src/decompiled/*.c` |
| **Analysis** | what calls what, and what RAM is touched? | `analysis/*.json` |
| **Names** | what is this function called? | `analysis/symbols.json` |
| **Docs** | what is this subsystem? | `docs/systems/`, `docs/functions/` |

Lifecycle: one vocabulary in `tools/decomp/tier.py`. Three independent flags —
`has_c`, `named`, `matches` — derive a tier:

```
UNKNOWN ──▶ DECOMPILED ──▶ UNDERSTOOD ──▶ MATCHING
 no C        C seed,         named,          byte-identical
             no match        no match        (top)
```

`make tier` prints the spread.

### One-time

```bash
bash build_tools.sh    # agbcc, Luvdis, m2c — no API key
make compare
```

### Every session (scripts first)

```bash
python3 tools/decomp/report_status.py
make compare
python3 tools/decomp/script_first.py     # patterns + cleaned m2c; integrate MATCH
```

`script_first.py` is the cheap path. Do not re-run pattern/m2c tools by hand for the same functions.

### Leftover function

```bash
python3 tools/decomp/agent_packet.py --next    # --battle / --wip to retarget
# Write C from that packet only (cleaned m2c seed, offsets, callees).
python3 tools/decomp/match_function.py sub_XXXXXXXX scratch.c
python3 tools/decomp/integrate_c.py sub_XXXXXXXX @scratch.c --kind semantic --note "…"
make compare
```

Max one `match_function.py` attempt. On DIFF:

```bash
# Same-size DIFF → the local permuter, NOT another hand edit.
python3 tools/decomp/permuter/auto.py sub_XXXXXXXX --seconds 240
python3 tools/decomp/park_wip.py sub_XXXXXXXX scratch.c --status "…" --next "…" --score "N/M"
```

`permuter/auto.py` imports the seed, scores it, searches, and lands score 0 for you — it costs no tokens, so it always runs before a second model attempt. It honours per-function `/* match-flags: -fprologue-bugfix */` (21 functions need it) and `/* match-compiler: old_agbcc */` (the toolchain ships two agbcc builds that emit different code). Clone families → one new matcher in `c_patterns.py`:

```bash
python3 tools/decomp/cluster_shapes.py
```

### Naming (independent of matching)

Names live in `analysis/symbols.json`, never in source. `include/symbols.h` is a
generated view that defines `#define Name sub_XXXXXXXX`, so the source reads with
human names while the linker still sees `sub_*` — naming **cannot** break
`make compare`. Provenance is `auto` < `ai` < `human`, and a lower-provenance pass
never overwrites a higher one.

```bash
make analyze                                    # rebuild analysis/*.json
python3 tools/decomp/symbols.py set sub_XXXXXXXX --symbol BtlFoo \
    --confidence 0.8 --source ai --evidence "why you believe this"
python3 tools/decomp/symbols.py apply           # rewrite source to use the names
python3 tools/decomp/symbols.py check           # collisions
make compare
```

All 633 functions are eligible immediately — a parked draft or an unmatched
function can be named as soon as its role is understood.

### Documentation

```bash
make document     # docs/systems/*.md, docs/functions/*.md, docs/functions/index.md
make tier         # lifecycle spread
```

Unnamed functions get no page (nothing readable to title it with) but always
appear in the index and on their subsystem page. The scoreboard
[docs/decomp-functions.md](docs/decomp-functions.md) is unchanged.

### Commands

| Command | Role |
|---------|------|
| `./decomp status` | Lifecycle tier table + progress |
| `./decomp analyze` | Rebuild `analysis/*.json` (idempotent) |
| `./decomp decompile` | Deterministic pass + one packet |
| `./decomp rename …` | Symbol layer (`list`/`set`/`apply`/`check`/`generate`) |
| `./decomp document` | Regenerate `docs/systems/` + `docs/functions/` |
| `./decomp verify` | `match_function` + `make compare` |
| `python3 tools/decomp/script_first.py` | Deterministic convert batch |
| `python3 tools/decomp/agent_packet.py --next` | Compact context for one leftover function |
| `python3 tools/decomp/match_function.py FN file.c` | Compile + compact DIFF vs retail |
| `python3 tools/decomp/integrate_c.py FN @file.c --kind semantic` | Land MATCH into `src/matched/` |
| `python3 tools/decomp/park_wip.py FN file.c` | Park unmatched C in `src/decompiled/` |
| `python3 tools/decomp/cluster_shapes.py` | Find Thumb clones for new patterns |
| `python3 tools/decomp/permuter/auto.py FN` | Local permuter: import → score → search → integrate on score 0 |
| `make compare` | Must stay `beyblade_g_revolution.gba: OK` |

Matching C is `src/matched/` (one file per function). Unmatched drafts are
`src/decompiled/` (not linked — `C_SRCS` is empty). Patterns:
[docs/decomp-patterns.md](docs/decomp-patterns.md). Queue: `make queue`.

Do not enable `HACKS=1` while matching — that breaks the SHA1 compare.

## Layout

pret/pokeemerald-style matching tree, plus a small ygodm8 hack overlay:

| Path | Role |
|------|------|
| `asm/` | Matching ARM/Thumb + baserom peels |
| `src/` | Matching C (`src/matched/` until Phase 5 packs by module) |
| `include/` | Headers (`gba/`, `ram_map.h`, types) |
| `data/` | Extracted data (`data/event_scripts/` reserved) |
| `docs/` | Decomp notes, RAM map, progress tables |
| `graphics/`, `sound/`, `constants/` | Extracted assets / asm constants (reserved) |
| `tools/` | pret tools + `tools/decomp/` matching pipeline |
| `libagbsyscall/` | BIOS syscall helpers |
| `ld_script.ld`, `sym_*.txt`, `rom.sha1` | Linker map, RAM symbols, compare checksum |
| `src_custom/`, `configs/` | ygodm8-style append hacks (not used by `make compare`) |

## Adding a hack (ygodm8-style)

1. Add a toggle in `configs/runtime.c` / `include/runtime.h`.
2. Implement `Name__Replacement` in `src_custom/*_hooks.c` (linked in append ROM).
3. Add a stub in `src_custom/LynJump.event` (`ORG` vanilla offset + `POIN` replacement).
4. `make` — linker places append code past 4MB; `apply_lynjump.py` patches the entry.

Target ROM: **USA/Europe**, SHA1 `a89f7b4eb77dc986022201db51a676451ba7c5e4`.
