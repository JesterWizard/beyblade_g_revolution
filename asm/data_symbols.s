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
SET_DATA gData_0807B6F0, 0x0807B6F0
SET_DATA gData_0807BB80, 0x0807BB80
SET_DATA gData_0807BDB8, 0x0807BDB8
SET_DATA gData_0807B0C4, 0x0807B0C4
SET_DATA gData_0807B6DC, 0x0807B6DC
SET_DATA gData_0807BB6C, 0x0807BB6C
SET_DATA gData_0807BDA4, 0x0807BDA4
SET_DATA gData_08090FF0, 0x08090FF0
SET_DATA gData_080D79CC, 0x080D79CC
SET_DATA gData_080B7429, 0x080B7429
SET_DATA gData_083A6BE0, 0x083A6BE0
SET_DATA gData_082BCD00, 0x082BCD00
SET_DATA gData_080B738E, 0x080B738E

@ IWRAM (kept separate from the ram_map_pool.h numeric macros, which are for
@ C that matches retail with literal addressing)
SET_DATA gData_03000198, 0x03000198
SET_DATA gData_03000290, 0x03000290
SET_DATA gData_030002A0, 0x030002A0
SET_DATA gData_03000504, 0x03000504
SET_DATA gData_030003CC, 0x030003CC
SET_DATA gData_05000200, 0x05000200
SET_DATA gData_08079068, 0x08079068
SET_DATA gData_08079358, 0x08079358
SET_DATA gData_03000508, 0x03000508
SET_DATA gData_03000534, 0x03000534
SET_DATA gData_03000770, 0x03000770
SET_DATA gData_03000794, 0x03000794
SET_DATA gData_03000798, 0x03000798
SET_DATA gData_083A7404, 0x083A7404
SET_DATA gData_083A75A8, 0x083A75A8
SET_DATA gData_083A7DF8, 0x083A7DF8
SET_DATA gData_083A7EE0, 0x083A7EE0
SET_DATA gData_083A8424, 0x083A8424
SET_DATA gData_083A734C, 0x083A734C
SET_DATA gData_083A83F4, 0x083A83F4
SET_DATA gData_083A85A4, 0x083A85A4
SET_DATA gData_083A8724, 0x083A8724
SET_DATA gData_0807AEEC, 0x0807AEEC
SET_DATA gData_0807AEFC, 0x0807AEFC
SET_DATA gData_04000010, 0x04000010
SET_DATA gData_04000012, 0x04000012
SET_DATA gData_04000014, 0x04000014
SET_DATA gData_04000016, 0x04000016
SET_DATA gData_04000018, 0x04000018
SET_DATA gData_0400001A, 0x0400001A
SET_DATA gData_0400001C, 0x0400001C
SET_DATA gData_0400001E, 0x0400001E
SET_DATA gData_04000040, 0x04000040
SET_DATA gData_04000042, 0x04000042
SET_DATA gData_030040E4, 0x030040E4
SET_DATA gData_030040C4, 0x030040C4
SET_DATA gData_030000C8, 0x030000C8
SET_DATA gData_083D2578, 0x083D2578
SET_DATA gData_03000634, 0x03000634
SET_DATA gData_0300063C, 0x0300063C
SET_DATA gData_030040A8, 0x030040A8
SET_DATA gData_030040B8, 0x030040B8
SET_DATA gData_080796DC, 0x080796DC
SET_DATA gData_08097458, 0x08097458
SET_DATA gData_0807A1F4, 0x0807A1F4
SET_DATA gData_0833D1E0, 0x0833D1E0
SET_DATA gData_0833D1F4, 0x0833D1F4
SET_DATA gData_08096794, 0x08096794
SET_DATA gData_083A858C, 0x083A858C
SET_DATA gData_083A8598, 0x083A8598
SET_DATA gData_080969CC, 0x080969CC
SET_DATA gData_080969E0, 0x080969E0
SET_DATA gData_080995AC, 0x080995AC
SET_DATA gData_08094E00, 0x08094E00
SET_DATA gData_050001C0, 0x050001C0
SET_DATA gData_04000084, 0x04000084
SET_DATA gData_030040DC, 0x030040DC
SET_DATA gData_0300410C, 0x0300410C
SET_DATA gData_030000C0, 0x030000C0
SET_DATA gData_083D26F0, 0x083D26F0
SET_DATA gData_083D2708, 0x083D2708
