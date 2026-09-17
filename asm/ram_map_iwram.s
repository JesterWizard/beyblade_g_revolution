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

@ -- Promoted from baserom literal-pool scan (Phase 2) -------------------------
@ Deref'd as the root arena pointer across battle + menu code (989 pool hits).
SET_DATA gMainWorkPtr, 0x03000198
@ Battle / menu work block (185 pool hits; see sub_0803C500 et al.).
SET_DATA gBattleWork, 0x03000290
@ Battle arena scratch cluster referenced by sub_0806A6F8 / sub_08065CD0.
SET_ARRAY gBattlerArena, 0x03004060, 0x10C

@ -- Battle subsystem fields (Phase 3 — traced from battle input / object code) -----
SET_DATA gBtlInputMask, 0x03003F60
SET_DATA gBtlState, 0x03003F64
SET_DATA gBtlKeysHeld, 0x03004060
SET_DATA gBtlKeysNew, 0x0300406C
SET_DATA gBtlKeyQueuePtr, 0x03004070
SET_DATA gBtlKeyQueueCount, 0x03004074
SET_DATA gBtlObjListHead, 0x030040A8
SET_DATA gBtlObjListTail, 0x030040B8
SET_DATA gBtlObjTable, 0x03004150
SET_DATA gBtlObjTableCount, 0x03004154
SET_DATA gBtlObjLiveCount, 0x03004158
SET_DATA gBtlLookupBase, 0x03004130
SET_DATA gBtlLookupPtr, 0x03004148

.include "ram_map_iwram_pool.inc"

@ -- Custom free-space allocations ---------------------------------------------
@ Prefer _kernel_malloc here for small hot-path scratch. Grow upward from Top.
@ NEVER use C `static` locals in APPEND_TEXT — the linker puts .bss at
@ 0x03000000 and will stomp vanilla IWRAM.

_kernel_malloc gNoCashPrintBuf, 0x100

.if UsedFreeRamSpaceTop > FreeRamSpaceBottom
    .error "IWRAM free pool overflowed into the user stack"
.endif
