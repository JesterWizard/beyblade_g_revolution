@ The popup's scratch memory: the picture being drawn (8 KB, OBJ tile layout), a
@ copy of the OBJ tiles it covers (8 KB), a copy of OAM (1 KB) and a few words
@ of state: 0x4800 bytes in a 28 KB block, 0x02038000..0x0203F000. It sits below
@ the shared mod state page (0x0203F000, debug_menu and thought_bubbles) and
@ above the shrunk heap, which ends at 0x02020800 (debug_menu patches
@ HeapAlloc; see docs/modding.md, "Mod RAM").
	.global gBars
	.set gBars, 0x02038000
