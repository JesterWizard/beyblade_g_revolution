# RAM map

Absolute IWRAM / EWRAM / save-bus symbols live in `asm/ram_map*.s` and are
included into a single `asm/ram_map.s` object. C code should include
`include/ram_map.h` (hand-written symbols) and `include/ram_map_pool.h`
(auto-generated pool inventory) instead of hardcoding `0x03…` / `0x02…`.

## Regeneration

```bash
scripts/decomp/ram_map_pass.sh
# or:
python3 tools/scan_ram_literals.py --emit-asm --emit-h --emit-doc
make compare
```

Manual symbols belong in `asm/ram_map_iwram.s` / `asm/ram_map_ewram.s`
**before** the `.include "*_pool.inc"` line. Re-run the scan after adding names
so duplicates drop out of the pool fragments.

<!-- AUTO-GENERATED: scan_ram_literals.py --begin -->
_Last scan: 2026-09-17 (`baserom.gba` Thumb LDR literal pools)._

## Scan summary

| Region | Pool-backed (aligned) | Named (manual) | Auto `gUnk_*` | High-water (below stack) |
|--------|----------------------:|---------------:|--------------:|--------------------------|
| IWRAM | 250 | 3 | 247 | 0x03005698 |
| EWRAM | 0 | 0 | 0 | (see occupancy) |
| SRAM bus | 0 | 0 | 0 | — |

## Occupancy (provisional)

| Range | Status | Notes |
|-------|--------|-------|
| `0x03000000` – vanilla high-water | **USED** | Literal-pool references; see clusters below |
| vanilla high-water – `FreeRamSpaceTop` (`0x03007A00`) | **UNKNOWN** | No pool refs; may be runtime BSS — verify in mGBA before reuse |
| `FreeRamSpaceTop` – `FreeRamSpaceBottom` | **FREE** | Custom `_kernel_malloc` bump (hack pool) |
| `0x03007B00` – `0x03008000` | **USED** | User + IRQ stacks (leave alone) |
| `0x02000000` – `FreeEwramSpaceTop` (`0x02030000`) | **USED** | Retail EWRAM; almost no pool refs in this ROM |
| `FreeEwramSpaceTop` – `FreeEwramSpaceBottom` | **FREE** | Custom `_kernel_malloc_ewram` bump |
| `0x0E000000` – `FreeFlashSpaceBottom` | **FREE*** | Opt-in SRAM-bus scratch (`ram_map_sram.s`) |

## IWRAM clusters (merge gap `< 0x40`)

| Start | End | Unique addrs | Pool hits | Span |
|-------|-----|-------------:|----------:|-----:|
| `0x03000000` | `0x03000008` | 2 | 10 | `0xC` |
| `0x03000068` | `0x03000120` | 12 | 38 | `0xBC` |
| `0x03000180` | `0x030001B0` | 4 | 1014 | `0x34` |
| `0x03000258` | `0x030002F8` | 16 | 344 | `0xA4` |
| `0x03000354` | `0x03000380` | 6 | 18 | `0x30` |
| `0x030003C8` | `0x03000480` | 26 | 159 | `0xBC` |
| `0x03000504` | `0x03000560` | 14 | 92 | `0x60` |
| `0x030005F0` | `0x030007B0` | 82 | 637 | `0x1C4` |
| `0x030008CC` | `0x030008F0` | 8 | 55 | `0x28` |
| `0x03000960` | `0x030009C0` | 7 | 34 | `0x64` |
| `0x03000AF0` | `0x03000B40` | 6 | 17 | `0x54` |
| `0x03000F00` | `0x03000F00` | 1 | 1 | `0x4` |
| `0x03002B00` | `0x03002B00` | 1 | 1 | `0x4` |
| `0x03003F40` | `0x03003F70` | 8 | 49 | `0x34` |
| `0x03004000` | `0x03004000` | 1 | 2 | `0x4` |
| `0x03004060` | `0x03004168` | 54 | 289 | `0x10C` |
| `0x03005124` | `0x03005124` | 1 | 1 | `0x4` |
| `0x03005694` | `0x03005694` | 1 | 1 | `0x4` |

## Top IWRAM literal-pool targets

| Address | Hits | Symbol |
|---------|-----:|--------|
| `0x03000198` | 989 | `gMainWorkPtr` |
| `0x03000290` | 185 | `gBattleWork` |
| `0x03000748` | 87 | `gUnk_03000748` |
| `0x030002A0` | 83 | `gUnk_030002A0` |
| `0x03004060` | 45 | `gBattlerArena` |
| `0x03000798` | 37 | `gUnk_03000798` |
| `0x03000278` | 28 | `gUnk_03000278` |
| `0x03000674` | 24 | `gUnk_03000674` |
| `0x030008E4` | 21 | `gUnk_030008E4` |
| `0x03000400` | 20 | `gUnk_03000400` |
| `0x03003F60` | 20 | `gUnk_03003F60` |
| `0x03000670` | 20 | `gUnk_03000670` |
| `0x03000678` | 20 | `gUnk_03000678` |
| `0x0300026C` | 19 | `gUnk_0300026C` |
| `0x03000538` | 19 | `gUnk_03000538` |
| `0x0300047C` | 18 | `gUnk_0300047C` |
| `0x03000180` | 18 | `gUnk_03000180` |
| `0x0300040C` | 17 | `gUnk_0300040C` |
| `0x03000750` | 17 | `gUnk_03000750` |
| `0x030040A4` | 16 | `gUnk_030040A4` |
| `0x03000504` | 15 | `gUnk_03000504` |
| `0x03000664` | 15 | `gUnk_03000664` |
| `0x030006AC` | 15 | `gUnk_030006AC` |
| `0x03004084` | 15 | `gUnk_03004084` |
| `0x0300066C` | 14 | `gUnk_0300066C` |

## Named IWRAM symbols (manual)

| Symbol | Address |
|--------|---------|
| `gMainWorkPtr` | `0x03000198` |
| `gBattleWork` | `0x03000290` |
| `gBattlerArena` | `0x03004060` |

<!-- AUTO-GENERATED: scan_ram_literals.py --end -->
