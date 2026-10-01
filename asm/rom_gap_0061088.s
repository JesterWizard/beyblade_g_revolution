@ Unmatched ROM 0x08061088..0x080610A7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0061088
gRomGap0061088:
	.incbin "baserom.gba", 0x61088, 0x20
