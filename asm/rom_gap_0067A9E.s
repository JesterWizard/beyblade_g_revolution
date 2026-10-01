@ Unmatched ROM 0x08067A9E..0x08067B97
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0067A9E
gRomGap0067A9E:
	.incbin "baserom.gba", 0x67A9E, 0x2
	.global _08067AA0
	.thumb_func
_08067AA0:
	.incbin "baserom.gba", 0x67AA0, 0xBC
	.4byte gRom_083A9440
	.4byte gRom_083A947C
	.4byte gRom_083A9490
	.4byte gRom_083A9494
	.4byte gRom_083A94A4
	.4byte gRom_083A94B4
	.4byte gRom_083A94C4
	.incbin "baserom.gba", 0x67B78, 0x20
