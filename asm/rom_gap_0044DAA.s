@ Unmatched ROM 0x08044DAA..0x08044EE7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0044DAA
gRomGap0044DAA:
	.incbin "baserom.gba", 0x44DAA, 0xF2
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x44EA0, 0x48
