@ Unmatched ROM 0x0803DD2C..0x0803DD5F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003DD2C
gRomGap003DD2C:
	.incbin "baserom.gba", 0x3DD2C, 0x10
	.4byte gRom_08097548
	.incbin "baserom.gba", 0x3DD40, 0x14
	.4byte gRom_08097534
	.incbin "baserom.gba", 0x3DD58, 0x8
