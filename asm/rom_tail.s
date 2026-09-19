@ Unmatched ROM tail from 0x08074146
	.section .rodata
	.global gRomTail
gRomTail:
	.incbin "baserom.gba", 0x74146, 0x20A6E
@ Named split for gUnk_08094BB4 (rodata table, sub_080435D8 / sub_080436B0 family).
	.global gUnk_08094BB4
gUnk_08094BB4:
	.incbin "baserom.gba", 0x94BB4, 0x36B44C
