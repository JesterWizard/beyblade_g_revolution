@ =============================================================================
@ Save / SRAM-bus occupancy map (provisional)
@ =============================================================================
@ Rescan: python3 tools/scan_ram_literals.py
@
@ GBA SRAM bus window (hardware): 0x0E000000 – 0x0E010000  (64 KiB mirror)
@
@   0x0E000000 ── FreeFlashSpaceTop ────────── opt-in scratch (FREE**)
@              bump _kernel_malloc_flash_free grows downward toward Top
@   0x0E000100 ── FreeFlashSpaceBottom         (256 B reserved here)
@
@ ** Opt-in only. Verify on hardware/mGBA before relying on it.
@ =============================================================================

SET_DATA FreeFlashSpaceTop, 0x0E000000
SET_DATA FreeFlashSpaceBottom, 0x0E000100
SET_DATA UsedFreeFlashSpaceTop, FreeFlashSpaceBottom

.macro _kernel_malloc_flash_free name, size
    .set UsedFreeFlashSpaceTop, UsedFreeFlashSpaceTop - \size
    SET_DATA \name, UsedFreeFlashSpaceTop
.endm
