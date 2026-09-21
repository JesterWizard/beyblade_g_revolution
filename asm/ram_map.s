.section .rodata

@ =============================================================================
@ RAM map entry — assembles region fragments into one object (build/bbgr/asm/ram_map.o)
@ =============================================================================
@
@ Region sources (edit these, not this file, when adding symbols):
@   ram_map_iwram.s          — IWRAM free pool + named symbols
@   ram_map_iwram_pool.inc   — auto gUnk_* from tools/scan_ram_literals.py
@   ram_map_ewram.s          — EWRAM free pool (provisional)
@   ram_map_ewram_pool.inc   — auto gUnk_* (hits>=2)
@   ram_map_sram.s           — save-bus note + optional scratch window
@
@ Pattern: https://github.com/JesterWizard/ygodm8/blob/master/asm/ram_map.s
@ Guide: documentation/ram-map.md
@ =============================================================================

.macro SET_DATA name, value
    .global \name
    .type \name, object
    .set \name, \value
.endm

.macro SET_ARRAY name, value, size
    SET_DATA \name, \value
    .global \name\()End
    .type \name\()End, object
    .set \name\()End, (\value + \size)
.endm

.macro dat value, name
    SET_DATA \name, \value
.endm

.include "ram_map_iwram.s"
.include "ram_map_ewram.s"
.include "ram_map_sram.s"
.include "data_symbols.s"
