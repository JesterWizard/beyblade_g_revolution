# Beyblade G Revolution

Decompilation scaffold for *Beyblade G Revolution* (GBA), structured after [pret/pokeemerald](https://github.com/pret/pokeemerald). Custom hacks follow the [ygodm8](https://github.com/JesterWizard/ygodm8) pattern: append ROM past the retail image, LynJump hooks, and `configs/runtime.c` toggles.

## Status

<!-- decomp-progress:start -->

Decompiled C is **48.5%** of functions (307/633) and **20.2%** of original function bytes (18,232/90,272).

| Metric | | Percent | Count |
| :--- | :--- | ---: | ---: |
| Decompiled C (functions) | `████████████████░░░░░░░░░░░░░░░░` | **48.5%** | 307/633 |
| Decompiled C (bytes) | `██████░░░░░░░░░░░░░░░░░░░░░░░░░░` | **20.2%** | 18,232/90,272 |
| Not opcode (functions) | `████████████████████████████████` | **100.0%** | 633/633 |
| Not opcode (bytes) | `████████████████████████████████` | **100.0%** | 90,272/90,272 |
| Linked in ROM | `████████████████████████████████` | **100.0%** | 633/633 |

| Kind | Functions | Bytes |
| :--- | ---: | ---: |
| Semantic C | 307 (48.5%) | 18,232 (20.2%) |
| Readable Thumb | 326 (51.5%) | 72,040 (79.8%) |
| Opcode embed | 0 (0.0%) | 0 (0.0%) |

Battle: **36.2%** functions / **13.9%** bytes in semantic C (58/160; 0 opcode left).

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

All 633 functions are already in the ROM peel (`make compare` green). Remaining work is **semantic C**: replace readable Thumb in `src/matched/` with C that still byte-matches. Agent notes: [AGENTS.md](AGENTS.md).

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

Max two `match_function.py` retries. On DIFF:

```bash
python3 tools/decomp/park_wip.py sub_XXXXXXXX scratch.c --status "…" --next "…" --score "N/M"
```

Same-size DIFF → permuter, not a long retry loop. Clone families → one new matcher in `c_patterns.py`:

```bash
python3 tools/decomp/cluster_shapes.py
tools/decomp/permuter/permute.sh import sub_XXXXXXXX
tools/decomp/permuter/permute.sh run nonmatchings/sub_XXXXXXXX -j 4 --stop-on-zero
```

### Commands

| Command | Role |
|---------|------|
| `python3 tools/decomp/script_first.py` | Deterministic convert batch |
| `python3 tools/decomp/agent_packet.py --next` | Compact context for one leftover function |
| `python3 tools/decomp/match_function.py FN file.c` | Compile + compact DIFF vs retail |
| `python3 tools/decomp/integrate_c.py FN @file.c --kind semantic` | Land MATCH into `src/matched/` |
| `python3 tools/decomp/park_wip.py FN file.c` | Save unmatched C in `src/wip/` |
| `python3 tools/decomp/cluster_shapes.py` | Find Thumb clones for new patterns |
| `python3 tools/decomp/unblock_symbols.py` | Draft prototypes for `bl _080…` |
| `make compare` | Must stay `beyblade_g_revolution.gba: OK` |

Matching C is `src/matched/` (one file per function). Unmatched drafts are `src/wip/` (not linked). Patterns: [docs/decomp-patterns.md](docs/decomp-patterns.md). Queue: `make queue`.

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
