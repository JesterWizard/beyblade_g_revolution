@ Unmatched ROM 0x0803E9A4..0x0803EBAF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003E9A4
gRomGap003E9A4:
	.global _0803E9A4
	.thumb_func
_0803E9A4:
	.incbin "baserom.gba", 0x3E9A4, 0x3C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_0803E9EC
	.global gRom_0803E9EC
gRom_0803E9EC:
	.4byte gRom_0803EA04
	.incbin "baserom.gba", 0x3E9F0, 0x4
	.4byte gRom_0803EA24
	.incbin "baserom.gba", 0x3E9F8, 0xC
	.global gRom_0803EA04
gRom_0803EA04:
	.incbin "baserom.gba", 0x3EA04, 0x20
	.global gRom_0803EA24
gRom_0803EA24:
	.incbin "baserom.gba", 0x3EA24, 0x40
	.4byte gRom_0803EA68
	.global gRom_0803EA68
gRom_0803EA68:
	.4byte gRom_0803EA80
	.incbin "baserom.gba", 0x3EA6C, 0x4
	.4byte gRom_0803EA94
	.incbin "baserom.gba", 0x3EA74, 0x4
	.4byte gRom_0803EAA8
	.incbin "baserom.gba", 0x3EA7C, 0x4
	.global gRom_0803EA80
gRom_0803EA80:
	.incbin "baserom.gba", 0x3EA80, 0x14
	.global gRom_0803EA94
gRom_0803EA94:
	.incbin "baserom.gba", 0x3EA94, 0x14
	.global gRom_0803EAA8
gRom_0803EAA8:
	.incbin "baserom.gba", 0x3EAA8, 0x108
