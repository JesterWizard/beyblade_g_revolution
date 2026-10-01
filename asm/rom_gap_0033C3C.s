@ Unmatched ROM 0x08033C3C..0x08033D8F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0033C3C
gRomGap0033C3C:
	.incbin "baserom.gba", 0x33C3C, 0x150
	.4byte gRom_0833C59C
