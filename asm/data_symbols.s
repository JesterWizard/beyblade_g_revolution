@ =============================================================================
@ Data symbols referenced by decompiled C (see include/data_symbols.h)
@ =============================================================================
@ The retail build referenced these blocks through *symbols*, not bare integer
@ literals.  That distinction is visible in the generated code: agbcc will
@ constant-fold / substitute / reschedule a literal address (e.g. folding a
@ second pool load into `subs r0, #0x30`), but it cannot do that to a symbol
@ reference.  Functions that only reproduce retail with symbol addressing use
@ the `gData_*` names declared in include/data_symbols.h.
@
@ Values here are the single source of truth for tools/decomp/match_function.py,
@ which passes them to the assembler as --defsym so verification resolves the
@ same way the original build did.  (Integrated bytes are written straight into
@ asm/matchings/*.s, so nothing here is linked into the ROM.)
@ =============================================================================

@ ROM data
SET_DATA gData_08091004, 0x08091004
SET_DATA gData_080910E8, 0x080910E8
SET_DATA gData_080BB888, 0x080BB888
SET_DATA gData_080BB8BC, 0x080BB8BC
SET_DATA gData_080BB8C0, 0x080BB8C0
SET_DATA gData_080BB748, 0x080BB748
SET_DATA gData_08091204, 0x08091204
SET_DATA gData_08091208, 0x08091208

@ IWRAM (kept separate from the ram_map_pool.h numeric macros, which are for
@ C that matches retail with literal addressing)
SET_DATA gData_03000198, 0x03000198
SET_DATA gData_030002A0, 0x030002A0
SET_DATA gData_03000504, 0x03000504
SET_DATA gData_03000508, 0x03000508
SET_DATA gData_03000534, 0x03000534
SET_DATA gData_03000770, 0x03000770
SET_DATA gData_03000794, 0x03000794
SET_DATA gData_03000798, 0x03000798
