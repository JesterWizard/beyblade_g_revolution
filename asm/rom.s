@ Unmatched ROM head 0x08000000..0x0802B90B
	.section .rodata
	.global gBaserom
gBaserom:
	.incbin "baserom.gba", 0x0, 0x2B90C
