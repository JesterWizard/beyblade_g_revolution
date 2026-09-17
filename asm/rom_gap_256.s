@ Unmatched ROM 0x08068806..0x08068807
	.section .rodata
	.global gRomGap256
gRomGap256:
	.incbin "baserom.gba", 0x68806, 0x2
