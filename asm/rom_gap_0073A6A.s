@ Unmatched ROM 0x08073A6A..0x08073AEB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0073A6A
gRomGap0073A6A:
	.incbin "baserom.gba", 0x73A6A, 0x32
	.4byte gRom_083D27A4
	.incbin "baserom.gba", 0x73AA0, 0x4C
