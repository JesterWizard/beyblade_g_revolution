@ Unmatched ROM tail from 0x08074146
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomTail
gRomTail:
	.incbin "baserom.gba", 0x74146, 0x38BEBA
