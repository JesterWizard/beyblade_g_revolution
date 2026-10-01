@ Unmatched ROM 0x0803FE10..0x0803FFAF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003FE10
gRomGap003FE10:
	.incbin "baserom.gba", 0x3FE10, 0x1A0
