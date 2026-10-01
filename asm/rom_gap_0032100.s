@ Unmatched ROM 0x08032100..0x08032603
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0032100
gRomGap0032100:
	.incbin "baserom.gba", 0x32100, 0x504
