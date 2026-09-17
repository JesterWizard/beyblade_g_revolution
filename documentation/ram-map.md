# RAM map

Absolute IWRAM / EWRAM / save-bus symbols live in `asm/ram_map*.s` and are
included into a single `asm/ram_map.s` object. C code should include
`include/ram_map.h` instead of hardcoding `0x03…` / `0x02…` addresses.

## Rescan

```bash
python3 tools/scan_ram_literals.py --emit-asm
```

This refreshes `asm/ram_map_iwram_pool.inc` and `asm/ram_map_ewram_pool.inc`.

## Free pools (provisional)

The scaffold ships conservative placeholder bounds. Tighten
`FreeRamSpaceTop` / `FreeEwramSpaceTop` after a literal-pool scan and a live
mGBA canary pass on this baserom — do not assume the sigma_star_saga margins
apply here.
