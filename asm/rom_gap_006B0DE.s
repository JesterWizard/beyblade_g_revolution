@ Unmatched ROM 0x0806B0DE..0x0806B2EF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006B0DE
gRomGap006B0DE:
	.incbin "baserom.gba", 0x6B0DE, 0xB2
	.4byte gRom_080BB774
	.incbin "baserom.gba", 0x6B194, 0x40
	.4byte gRom_080BB774 + 1
	.incbin "baserom.gba", 0x6B1D8, 0xF8
	.4byte gData_080BB748
	.incbin "baserom.gba", 0x6B2D4, 0x1C
