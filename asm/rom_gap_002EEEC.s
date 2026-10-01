@ Unmatched ROM 0x0802EEEC..0x0802F51F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002EEEC
gRomGap002EEEC:
	.global _0802EEEC
	.thumb_func
_0802EEEC:
	.incbin "baserom.gba", 0x2EEEC, 0xC8
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2EFB8, 0x14
	.global _0802EFCC
	.thumb_func
_0802EFCC:
	.incbin "baserom.gba", 0x2EFCC, 0x80
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2F050, 0xD4
	.global _0802F124
	.thumb_func
_0802F124:
	.incbin "baserom.gba", 0x2F124, 0x68
	.global _0802F18C
	.thumb_func
_0802F18C:
	.incbin "baserom.gba", 0x2F18C, 0x48
	.global _0802F1D4
	.thumb_func
_0802F1D4:
	.incbin "baserom.gba", 0x2F1D4, 0x74
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2F24C, 0x90
	.global _0802F2DC
	.thumb_func
_0802F2DC:
	.incbin "baserom.gba", 0x2F2DC, 0x38
	.global _0802F314
	.thumb_func
_0802F314:
	.incbin "baserom.gba", 0x2F314, 0x44
	.global _0802F358
	.thumb_func
_0802F358:
	.incbin "baserom.gba", 0x2F358, 0x34
	.global _0802F38C
	.thumb_func
_0802F38C:
	.incbin "baserom.gba", 0x2F38C, 0x78
	.global _0802F404
	.thumb_func
_0802F404:
	.incbin "baserom.gba", 0x2F404, 0xEC
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833BFE8
	.4byte gRom_0833BFFC
	.4byte gRom_0833C010
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_0809705C
	.incbin "baserom.gba", 0x2F510, 0x8
	.4byte gRom_08097070
	.4byte gRom_080977B4
