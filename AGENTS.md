# Agent notes

Read **[ARCHITECTURE.md](ARCHITECTURE.md)** first — it explains the
decompile-and-append build model and the directory layout.

## Where things are documented

| Question | Look here |
|---|---|
| "What does this file/directory do?" | [ARCHITECTURE.md](ARCHITECTURE.md) |
| "What does this RAM address do?" | [documentation/ram-map.md](documentation/ram-map.md) |
| "What's shipped vs. still planned?" | [README.md](README.md) and [TODO.md](TODO.md) |

## Non-obvious defaults worth knowing up front

- `configs/runtime.c` is the build-time source of truth for which cheats
  exist in the ROM **at all**.
- `asm/ram_map_iwram.s` / `asm/ram_map_ewram.s` use **provisional** free-pool
  bounds until `tools/scan_ram_literals.py` is run against this baserom.
- Never use C `static` buffers in `APPEND_TEXT` code — link `.bss` at
  `0x03000000` and stomp vanilla IWRAM. Use `_kernel_malloc` in the ram map.
