# Architecture

Beyblade G Revolution is a commercial GBA ROM (`baserom.gba`) being decompiled
into matching C. Mods are made by editing that source, not by hooking the ROM.

## The mental model

1. `baserom.gba` is the unmodified retail ROM. It is never edited directly.
2. `src/matched/*.c` holds **decompiled** vanilla functions — C (or readable
   Thumb) that compiles to the same bytes as the retail function at that
   address.
3. `asm/` assembles the ROM: `rom.s` / `rom_layout.ld` place the matched
   functions at their retail addresses and `.incbin` the rest of the baserom.

## Directory map

| Path | What's in it |
|---|---|
| `src/matched/*.c` | One matched function per file (semantic C or readable Thumb). |
| `src/decompiled/` | Unmatched C seeds + process notes (the DECOMPILED lifecycle tier). Not linked. See `docs/decomp-wip.md`. |
| `analysis/` | Generated analysis DB: functions, xrefs, structs, systems, symbols. See `docs/decomp-pipeline.md`. |
| `include/*.h` | Headers: types (`unknown-types.h`), prototypes, generated `symbols.h`, and `ram_map.h` (EWRAM/IWRAM symbol table). |
| `asm/*.s` | Hand-written trampolines, `ram_map*.s` (address registry), and `rom.s` (raw ROM segment definitions). |
| `data/`, `graphics/`, `sound/`, `constants/` | Extracted assets / asm constants (pret layout; mostly reserved). |
| `docs/` | Decomp notes, RAM map, progress counter. |
| `tools/decomp/` | Matching pipeline (was `scripts/decomp/`). |
| `build_tools.sh` | pret-style bootstrap (`agbcc`, Luvdis, permuter). |

## Matching

Shrink `asm/rom.s` `.incbin` ranges as real asm/C replaces them.
`make compare` checks `rom.sha1` against the retail dump. A mod that edits the
source will naturally stop matching that SHA1.
