@ Unmatched ROM 0x0803DE00..0x0803DEC7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003DE00
gRomGap003DE00:
	.global _0803DE00
	.thumb_func
_0803DE00:
	.incbin "baserom.gba", 0x3DE00, 0x74
	.4byte gData_0807BDB8
	.4byte gData_0807BB80
	.4byte gData_0807B6F0
	.4byte gRom_0803DE84
	.global gRom_0803DE84
gRom_0803DE84:
	.4byte gRom_0803DEB4
	.4byte gRom_0803DEB4
	.4byte gRom_0803DEB4
	.4byte gRom_0803DEB8
	.4byte gRom_0803DEB8
	.4byte gRom_0803DEB8
	.4byte gRom_0803DEBC
	.4byte gRom_0803DEBC
	.4byte gRom_0803DEBC
	.4byte gRom_0803DEC0
	.4byte gRom_0803DEC0
	.4byte gRom_0803DEC0
	.global gRom_0803DEB4
gRom_0803DEB4:
	.incbin "baserom.gba", 0x3DEB4, 0x4
	.global gRom_0803DEB8
gRom_0803DEB8:
	.incbin "baserom.gba", 0x3DEB8, 0x4
	.global gRom_0803DEBC
gRom_0803DEBC:
	.incbin "baserom.gba", 0x3DEBC, 0x4
	.global gRom_0803DEC0
gRom_0803DEC0:
	.incbin "baserom.gba", 0x3DEC0, 0x8
