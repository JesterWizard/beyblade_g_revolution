# Architecture

Beyblade G Revolution is a commercial GBA ROM (`baserom.gba`) being decompiled
into matching C. Mods are made by editing that source, not by hooking the ROM.

## The mental model

1. `baserom.gba` is the unmodified retail ROM. It is never edited directly.
2. `src/matched/*.c` holds **decompiled** vanilla functions. `make` compiles
   them (agbcc, per-file `match-compiler` / `match-flags` / `match-fixup`) and
   places each `.text` at its retail address.
3. `asm/` supplies the rest of the image: `rom.s` / gap incbins / `rom_layout.ld`
   still pin those functions to retail VMAs until Phase 5 drops the addresses.

## Directory map

| Path | What's in it |
|---|---|
| `src/matched/*.c` | One matched function per file. `make` compiles these into the ROM. |
| `src/decompiled/` | Unmatched C seeds + process notes (the DECOMPILED lifecycle tier). Not linked. See `docs/decomp-wip.md`. |
| `analysis/` | Generated analysis DB: functions, xrefs, structs, systems, symbols. See `docs/decomp-pipeline.md`. |
| `include/*.h` | Headers: types (`unknown-types.h`), prototypes, generated `symbols.h`, and `ram_map.h` (EWRAM/IWRAM symbol table). |
| `asm/*.s` | Hand-written trampolines, `ram_map*.s` (address registry), and `rom.s` (raw ROM segment definitions). |
| `data/`, `graphics/`, `sound/`, `constants/` | Extracted assets / asm constants (pret layout; mostly reserved). |
| `docs/` | Decomp notes, RAM map, progress counter. |
| `tools/decomp/` | Matching pipeline (was `scripts/decomp/`). |
| `build_tools.sh` | pret-style bootstrap (`agbcc`, Luvdis, permuter). |

## Matching

Shrink `asm/rom.s` `.incbin` ranges as real C replaces them.
`make compare` checks `rom.sha1` against the retail dump. A mod that edits
`src/matched/` will rebuild from that C; until the ROM is shiftable, growing a
function still overlaps the next peel.
