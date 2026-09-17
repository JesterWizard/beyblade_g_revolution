# Beyblade G Revolution

Decompilation scaffold for *Beyblade G Revolution* (GBA), structured after [pret/pokeemerald](https://github.com/pret/pokeemerald). Custom hacks follow the [ygodm8](https://github.com/JesterWizard/ygodm8) pattern: append ROM past the retail image, LynJump hooks, and `configs/runtime.c` toggles.

## Status

<!-- decomp-progress:start -->

Decompiled C is **5.7%** of functions (36/633) and **0.7%** of original function bytes (676/90,272).

| Metric | | Percent | Count |
| :--- | :--- | ---: | ---: |
| Decompiled C (functions) | `██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░` | **5.7%** | 36/633 |
| Decompiled C (bytes) | `█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░` | **0.7%** | 676/90,272 |
| Not opcode (functions) | `██████████░░░░░░░░░░░░░░░░░░░░░░` | **29.7%** | 188/633 |
| Not opcode (bytes) | `██████████████░░░░░░░░░░░░░░░░░░` | **42.4%** | 38,238/90,272 |
| Linked in ROM | `████████████████████████████████` | **100.0%** | 633/633 |

| Kind | Functions | Bytes |
| :--- | ---: | ---: |
| Semantic C | 36 (5.7%) | 676 (0.7%) |
| Readable Thumb | 152 (24.0%) | 37,562 (41.6%) |
| Opcode embed | 445 (70.3%) | 52,034 (57.6%) |

Battle: **6.2%** functions / **1.1%** bytes in semantic C (10/160; 0 opcode left).

Opcode `.byte` embeds are the retail machine code and do not count as decompiled C. Readable Thumb is matching asm. Unmatched ROM ranges stay `.incbin`'d from `baserom.gba` so `make compare` can stay green. Refresh with `python3 scripts/decomp/progress.py --write` or `make progress`.

<!-- decomp-progress:end -->

## Quick start

See [INSTALL.md](INSTALL.md).

```bash
# after placing baserom.gba
make compare          # vanilla rebuild (default HACKS=0)
make HACKS=1 modern   # link append ROM (runtime + src_custom)
```

## Hands-off AI decompilation

See [AGENTS.md](AGENTS.md). One-time setup, then batch runs:

```bash
bash scripts/setup.sh              # agbcc, Luvdis, Mizuchi
export ANTHROPIC_API_KEY=...       # for Mizuchi Claude phase
scripts/decomp/run_batch.sh 10     # decompile 10 easy functions
python3 scripts/decomp/report_status.py
```

## Layout

| Path | Role |
|------|------|
| `asm/` | Hand-written / disassembled ARM/Thumb + baserom peels |
| `asm/ram_map*.s` | IWRAM / EWRAM / save address registry ([ygodm8](https://github.com/JesterWizard/ygodm8/blob/master/asm/ram_map.s)-style) |
| `src/` | Decompiled vanilla C |
| `src_custom/` | Hack hooks (`*_hooks.c`) + `LynJump.event` |
| `configs/runtime.c` | Boolean / value toggles for hacks |
| `data/`, `graphics/`, `sound/` | Extracted assets (empty for now) |
| `ld_script.ld` | Memory map; append region starts after the 4MB baserom |
| `tools/apply_lynjump.py` | Post-link absolute jump stubs into the ROM |
| `rom.sha1` | Matching checksum for `make compare` |

## Matching workflow

1. Disassemble / analyze `baserom.gba` (Ghidra, etc.).
2. Replace a range in `asm/rom.s` with a real object in `asm/` or `src/`.
3. Update `ld_script.ld` and the Makefile source lists.
4. `make compare` — keep the SHA1 green (vanilla peels only).

## Adding a hack (ygodm8-style)

1. Add a toggle in `configs/runtime.c` / `include/runtime.h`.
2. Implement `Name__Replacement` in `src_custom/*_hooks.c` (linked in append ROM).
3. Add a stub in `src_custom/LynJump.event` (`ORG` vanilla offset + `POIN` replacement).
4. `make` — linker places append code past 4MB; `apply_lynjump.py` patches the entry.

Target ROM: **USA/Europe**, SHA1 `a89f7b4eb77dc986022201db51a676451ba7c5e4`.
