@ Unmatched ROM 0x0802BA7C..0x0802BAD3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002BA7C
gRomGap002BA7C:
	.global _0802BA7C
	.thumb_func
_0802BA7C:
	.incbin "baserom.gba", 0x2BA7C, 0x14
	.4byte gRom_0802BA94
	.global gRom_0802BA94
gRom_0802BA94:
	.4byte gRom_0802BAC8
	.4byte gRom_0802BAB8
	.4byte gRom_0802BABC
	.4byte gRom_0802BABC
	.4byte gRom_0802BAC4
	.4byte gRom_0802BAC0
	.4byte gRom_0802BAC0
	.4byte gRom_0802BAC4
	.4byte gRom_0802BAC8
	.global gRom_0802BAB8
gRom_0802BAB8:
	.incbin "baserom.gba", 0x2BAB8, 0x4
	.global gRom_0802BABC
gRom_0802BABC:
	.incbin "baserom.gba", 0x2BABC, 0x4
	.global gRom_0802BAC0
gRom_0802BAC0:
	.incbin "baserom.gba", 0x2BAC0, 0x4
	.global gRom_0802BAC4
gRom_0802BAC4:
	.incbin "baserom.gba", 0x2BAC4, 0x4
	.global gRom_0802BAC8
gRom_0802BAC8:
	.incbin "baserom.gba", 0x2BAC8, 0xC
