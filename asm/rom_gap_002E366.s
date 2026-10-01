@ Unmatched ROM 0x0802E366..0x0802ECD7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002E366
gRomGap002E366:
	.incbin "baserom.gba", 0x2E366, 0x46
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2E3B0, 0x234
	.4byte gRom_080D7374
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.4byte gRom_08077F10
	.incbin "baserom.gba", 0x2E5F4, 0x8
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x2E600, 0x3C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x2E640, 0xA4
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2E6E8, 0x10
	.global _0802E6F8
	.thumb_func
_0802E6F8:
	.incbin "baserom.gba", 0x2E6F8, 0xA4
	.global _0802E79C
	.thumb_func
_0802E79C:
	.incbin "baserom.gba", 0x2E79C, 0x48
	.global _0802E7E4
	.thumb_func
_0802E7E4:
	.incbin "baserom.gba", 0x2E7E4, 0x90
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2E878, 0x48
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2E8C4, 0x1CC
	.global _0802EA90
	.thumb_func
_0802EA90:
	.incbin "baserom.gba", 0x2EA90, 0x6C
	.global _0802EAFC
	.thumb_func
_0802EAFC:
	.incbin "baserom.gba", 0x2EAFC, 0x44
	.global _0802EB40
	.thumb_func
_0802EB40:
	.incbin "baserom.gba", 0x2EB40, 0x40
	.global _0802EB80
	.thumb_func
_0802EB80:
	.incbin "baserom.gba", 0x2EB80, 0x13C
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833BF94
	.4byte gRom_0833BFB0
	.4byte gRom_0833BFCC
	.4byte gData_082BCD00
	.4byte gData_080B738E
