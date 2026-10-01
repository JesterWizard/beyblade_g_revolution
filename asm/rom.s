@ Unmatched ROM head 0x08000000..0x0802B8BB
	.section .rodata,"a",%progbits
	.balign 2
	.global gBaserom
gBaserom:
	.incbin "baserom.gba", 0x0, 0x2B8BC
