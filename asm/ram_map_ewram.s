@ =============================================================================
@ EWRAM occupancy map (provisional — rescan baserom before relying on pool)
@ =============================================================================
@ Hardware window:     0x02000000 – 0x02040000   (256 KiB)
@ Rescan: python3 tools/scan_ram_literals.py [--emit-asm]
@
@   0x02020800 ── FreeEwramSpaceTop ────────── custom pool (FREE*): end of the mod-shrunk heap
@              bump _kernel_malloc_ewram grows downward toward Top
@   0x0203F000 ── FreeEwramSpaceBottom (mod state page below it, 4 KB)
@
@ * Conservative placeholder until a literal-pool scan + live canary run.
@ =============================================================================

SET_DATA FreeEwramSpaceTop, 0x02020800
SET_DATA FreeEwramSpaceBottom, 0x0203F000
SET_DATA UsedFreeEwramSpaceTop, FreeEwramSpaceBottom

.macro _kernel_malloc_ewram name, size
    .set UsedFreeEwramSpaceTop, UsedFreeEwramSpaceTop - \size
    SET_DATA \name, UsedFreeEwramSpaceTop
.endm

@ -- Engine-reserved space ------------------------------------------------------
@ Format: SET_ARRAY name, start, size   @ kind: evidence
@ kind = heap | stack | bios | mod. Read by tools/ram_coverage.py (docs/ram-coverage.md).
@ EWRAM is not referenced by fixed address anywhere in the ROM: it is all allocator
@ state and heap. Both allocators (HeapAlloc sub_0806A3A4, FastAllocate sub_0806A314)
@ share HeapRegionInsert and keep 16-byte nodes {start, size, prev, next}:
@   0x02000000  FastAllocate node table, 0x20 nodes (pool ptr 0x03003F40)
@   0x02000200  HeapAlloc node table,    0x60 nodes (pool ptr 0x03003F50)
@   0x02000800  HeapAlloc heap, first-fit from the bottom (start in 0x03000B34)
SET_ARRAY gEwramFastNodes, 0x02000000, 0x200                 @ heap: sub_0806A314
SET_ARRAY gEwramHeapNodes, 0x02000200, 0x600                 @ heap: sub_0806A3A4
@ Retail sizes the heap 0xFE << 10 = 0x3F800 (to 0x02040000). The mods patch
@ both sites (0x0806A3DE, 0x0806A622) to 0x80 << 10 = 0x20000, because a survey
@ peaks at ~0x107B0 (tools/ram_survey.py). This map describes the mod build; a
@ vanilla ROM has no free EWRAM and nothing allocates from the pool below.
SET_ARRAY gEwramHeap, 0x02000800, 0x20000                    @ heap: sub_0806A3A4, mod-shrunk

@ Top 4 KB: state pages of the default mods (mods/*/src/ram.s), outside the heap.
SET_ARRAY gBitBeastBarsBuf, 0x02038000, 0x7000                @ mod: bitbeast_bars popup picture, tile and OAM backup
SET_ARRAY gModStatePage, 0x0203F000, 0x1000                  @ mod: debug_menu gDebug +0, thought_bubbles gBubble +0x800

.include "ram_map_ewram_pool.inc"

.if UsedFreeEwramSpaceTop < FreeEwramSpaceTop
    .error "EWRAM free pool underflowed past FreeEwramSpaceTop"
.endif
