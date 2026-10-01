@ Unmatched ROM 0x0806B0DE..0x0806B2EF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006B0DE
gRomGap006B0DE:
	.incbin "baserom.gba", 0x6B0DE, 0x1F2
	.4byte gData_080BB748
	.incbin "baserom.gba", 0x6B2D4, 0x1C
