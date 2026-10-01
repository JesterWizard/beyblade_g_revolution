@ Unmatched ROM 0x08072714..0x08072A37
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0072714
gRomGap0072714:
	.incbin "baserom.gba", 0x72714, 0x100
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x72818, 0x220
