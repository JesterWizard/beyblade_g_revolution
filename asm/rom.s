@ Unmatched ROM head 0x08000000..0x08033A93
	.section .rodata
	.global gBaserom
gBaserom:
	.incbin "baserom.gba", 0x0, 0x33A94
