@ Unmatched ROM 0x0803EE04..0x0803FDCF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003EE04
gRomGap003EE04:
	.incbin "baserom.gba", 0x3EE04, 0x28
	.global _0803EE2C
	.thumb_func
_0803EE2C:
	.incbin "baserom.gba", 0x3EE2C, 0x80
	.4byte gData_0807BE04
	.incbin "baserom.gba", 0x3EEB0, 0xAC
	.global _0803EF5C
	.thumb_func
_0803EF5C:
	.incbin "baserom.gba", 0x3EF5C, 0x50
	.global _0803EFAC
	.thumb_func
_0803EFAC:
	.incbin "baserom.gba", 0x3EFAC, 0x80
	.4byte gData_0807BE04
	.incbin "baserom.gba", 0x3F030, 0xA0
	.global _0803F0D0
	.thumb_func
_0803F0D0:
	.incbin "baserom.gba", 0x3F0D0, 0xC0
	.4byte gData_0807BE04
	.incbin "baserom.gba", 0x3F194, 0xFC
	.global _0803F290
	.thumb_func
_0803F290:
	.incbin "baserom.gba", 0x3F290, 0x38
	.4byte gRom_0803F2CC
	.global gRom_0803F2CC
gRom_0803F2CC:
	.4byte gRom_0803F2FC
	.4byte gRom_0803F358
	.incbin "baserom.gba", 0x3F2D4, 0x4
	.4byte gRom_0803F40C
	.incbin "baserom.gba", 0x3F2DC, 0x8
	.4byte gRom_0803F494
	.incbin "baserom.gba", 0x3F2E8, 0x8
	.4byte gRom_0803F55C
	.4byte gRom_0803F598
	.4byte gRom_0803F5D0
	.global gRom_0803F2FC
gRom_0803F2FC:
	.incbin "baserom.gba", 0x3F2FC, 0x5C
	.global gRom_0803F358
gRom_0803F358:
	.incbin "baserom.gba", 0x3F358, 0xB4
	.global gRom_0803F40C
gRom_0803F40C:
	.incbin "baserom.gba", 0x3F40C, 0x88
	.global gRom_0803F494
gRom_0803F494:
	.incbin "baserom.gba", 0x3F494, 0xC8
	.global gRom_0803F55C
gRom_0803F55C:
	.incbin "baserom.gba", 0x3F55C, 0x3C
	.global gRom_0803F598
gRom_0803F598:
	.incbin "baserom.gba", 0x3F598, 0x38
	.global gRom_0803F5D0
gRom_0803F5D0:
	.incbin "baserom.gba", 0x3F5D0, 0x40
	.global _0803F610
	.thumb_func
_0803F610:
	.incbin "baserom.gba", 0x3F610, 0x8C
	.4byte gData_0807BE04
	.incbin "baserom.gba", 0x3F6A0, 0xB0
	.global _0803F750
	.thumb_func
_0803F750:
	.incbin "baserom.gba", 0x3F750, 0xC0
	.4byte gData_0807BE04
	.incbin "baserom.gba", 0x3F814, 0xA0
	.global _0803F8B4
	.thumb_func
_0803F8B4:
	.incbin "baserom.gba", 0x3F8B4, 0x184
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x3FA40, 0x2C
	.global _0803FA6C
	.thumb_func
_0803FA6C:
	.incbin "baserom.gba", 0x3FA6C, 0x170
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.incbin "baserom.gba", 0x3FBE4, 0x68
	.4byte gRom_0833DC18
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x3FC58, 0xA8
	.global _0803FD00
	.thumb_func
_0803FD00:
	.incbin "baserom.gba", 0x3FD00, 0xD0
