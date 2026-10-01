@ Unmatched ROM 0x08069F18..0x0806A313
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0069F18
gRomGap0069F18:
	.incbin "baserom.gba", 0x69F18, 0x120
	.4byte gData_083C9544
	.incbin "baserom.gba", 0x6A03C, 0x2D8
