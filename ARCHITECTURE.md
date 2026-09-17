# Architecture

Beyblade G Revolution is a commercial GBA ROM (`baserom.gba`) being modded/patched
via a hybrid decompile-and-append strategy, not a full decompile. Read this
before touching build output, hook wiring, or the runtime toggle system.

## The mental model

1. `baserom.gba` is the unmodified retail ROM. It is never edited directly.
2. `src/*.c` holds **decompiled** vanilla functions — real C recreations of
   specific baserom addresses, compiled and appended into the ROM to
   *replace* the original machine code at that address.
3. `src_custom/*.c` holds **new** functionality that has no vanilla
   equivalent. These call into vanilla ROM addresses as opaque function
   pointers/hooks — there's no compiler-checked struct backing them, just
   raw offsets (see `include/ram_map.h` and `documentation/ram-map.md`).
4. `tools/apply_lynjump.py` is the final build step: it patches compiled
   veneers/hooks into the ELF/ROM at specific byte offsets, guarded by
   `RuntimeConfig` flags in `configs/runtime.c`.
5. Everything is gated by **build-time** flags in `configs/runtime.c`
   (`gRuntimeConfigRom`) — a feature that's `FALSE` there may have its
   entire hook *not installed at all* in the ROM.

## Directory map

| Path | What's in it |
|---|---|
| `src/*.c` | Decompiled vanilla functions, one file per subsystem. Comment header always states the baserom address + span it replaces. |
| `src_custom/*.c` | New hooks/features with no vanilla equivalent. |
| `include/*.h` | Headers for both of the above, plus `ram_map.h` (EWRAM/IWRAM symbol table) and `runtime.h` (`RuntimeConfig` + `APPEND_*` macros). |
| `asm/*.s` | Hand-written trampolines, `ram_map*.s` (address registry), and `rom.s` (raw ROM segment definitions). |
| `src_custom/LynJump.event` | Declarative full-function replacements in `ygodm8` LynJump format. |
| `tools/apply_lynjump.py` | Post-link patcher for LynJump stubs and runtime-gated veneers. |
| `configs/runtime.c` | Build-time toggles (`gRuntimeConfigRom`). |
| `data/`, `graphics/`, `sound/` | Extracted assets and generated table inputs. |
| `documentation/*.md` | Deep-dive docs per subsystem. |

## Matching vs. hacking

- **Matching**: shrink `asm/rom.s` `.incbin` ranges as real asm/C replaces them.
  `make compare` checks `rom.sha1` against the retail dump.
- **Hacking**: link `src_custom/` and `configs/` into the append region past 4MB.
  Once append code is linked, `make compare` no longer matches the retail SHA1.
