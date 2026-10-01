@ Unmatched ROM 0x08041FDC..0x0804238F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0041FDC
gRomGap0041FDC:
	.incbin "baserom.gba", 0x41FDC, 0x3B4
