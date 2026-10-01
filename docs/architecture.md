# Architecture

Beyblade G Revolution is a commercial GBA ROM (`baserom.gba`) being decompiled
into matching C. Mods are made by editing that source, not by hooking the ROM.

## The mental model

1. `baserom.gba` is the unmodified retail ROM. It is never edited directly.
2. `src/matched/*.c` holds **decompiled** vanilla functions. `make` compiles
   them (agbcc, per-file `match-compiler` / `match-flags` / `match-fixup`) and
   places each `.text` at its retail address.
3. `asm/` supplies the rest of the image: `rom.s` (head at 0x08000000) then
   `rom_layout.ld` packs matched `.text` and gap incbins in order (`SUBALIGN(2)`).
   Functions land at retail addresses only while they keep retail sizes.

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
`src/matched/` will rebuild from that C. Growing a function slides later peels.
Function-entry words and `gData_*` table words in gap/tail peels are `.4byte`.
ROM `gData_*` are peel labels. Matched C keeps live BL / ABS32 relocs. Pointer
tables of two or more ROM words, and singletons that already point at a peel
label, are `.4byte` `gRom_*`. Sparse leftover singleton data words are also
`.4byte`. Dense graphics-like `0x08……` clusters stay absolute. `make shift-test`
inserts `0x1000` after `.rom_head`; `make grow-test` inserts 4 bytes after the
first matched `.text`. Mods: `make GROW=1 COMPARE=0 rom`.
