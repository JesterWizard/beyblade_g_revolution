@ =============================================================================
@ IWRAM occupancy map (provisional — rescan baserom before relying on pool)
@ =============================================================================
@ Hardware window:     0x03000000 – 0x03008000   (32 KiB)
@ Rescan: python3 tools/scan_ram_literals.py [--emit-asm]
@
@   0x03007A00 ── FreeRamSpaceTop ──────────── SAFE custom pool (FREE*)
@              bump _kernel_malloc grows UP toward Bottom (away from stack)
@   0x03007B00 ── FreeRamSpaceBottom            (reserved for user stack)
@   0x03007B00 – 0x03008000   user/IRQ stacks   (USED)
@
@ * Conservative placeholder until a literal-pool scan + live canary run.
@ =============================================================================

SET_DATA FreeRamSpaceTop, 0x03007A00
SET_DATA FreeRamSpaceBottom, 0x03007B00
SET_DATA UsedFreeRamSpaceTop, FreeRamSpaceTop

.macro _kernel_malloc name, size
    SET_DATA \name, UsedFreeRamSpaceTop
    .set UsedFreeRamSpaceTop, UsedFreeRamSpaceTop + \size
.endm

.include "ram_map_iwram_pool.inc"

@ -- Custom free-space allocations ---------------------------------------------
@ Prefer _kernel_malloc here for small hot-path scratch. Grow upward from Top.
@ NEVER use C `static` locals in APPEND_TEXT — the linker puts .bss at
@ 0x03000000 and will stomp vanilla IWRAM.

_kernel_malloc gNoCashPrintBuf, 0x100

.if UsedFreeRamSpaceTop > FreeRamSpaceBottom
    .error "IWRAM free pool overflowed into the user stack"
.endif
