@ Unmatched ROM 0x08033E5A..0x08033EA3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0033E5A
gRomGap0033E5A:
	.incbin "baserom.gba", 0x33E5A, 0x46
	.4byte gRom_08078348
