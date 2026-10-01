@ Unmatched ROM 0x0803906C..0x080392CF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003906C
gRomGap003906C:
	.incbin "baserom.gba", 0x3906C, 0x178
	.4byte gRom_08111CB4
	.4byte gRom_0833C640
	.4byte gRom_0833C674
	.incbin "baserom.gba", 0x391F0, 0xE0
