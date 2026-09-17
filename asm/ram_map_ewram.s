@ =============================================================================
@ EWRAM occupancy map (provisional — rescan baserom before relying on pool)
@ =============================================================================
@ Hardware window:     0x02000000 – 0x02040000   (256 KiB)
@ Rescan: python3 tools/scan_ram_literals.py [--emit-asm]
@
@   0x02030000 ── FreeEwramSpaceTop ────────── SAFE custom pool (FREE*)
@              bump _kernel_malloc_ewram grows downward toward Top
@   0x02040000 ── FreeEwramSpaceBottom
@
@ * Conservative placeholder until a literal-pool scan + live canary run.
@ =============================================================================

SET_DATA FreeEwramSpaceTop, 0x02030000
SET_DATA FreeEwramSpaceBottom, 0x02040000
SET_DATA UsedFreeEwramSpaceTop, FreeEwramSpaceBottom

.macro _kernel_malloc_ewram name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_DATA \name, UsedFreeEwramSpaceTop
.endm

.include "ram_map_ewram_pool.inc"

.if UsedFreeEwramSpaceTop < FreeEwramSpaceTop
    .error "EWRAM free pool underflowed past FreeEwramSpaceTop"
.endif
