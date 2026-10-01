@ Unmatched ROM 0x0804DEAC..0x0804E17B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004DEAC
gRomGap004DEAC:
	.global _0804DEAC
	.thumb_func
_0804DEAC:
	.incbin "baserom.gba", 0x4DEAC, 0x68
	.global _0804DF14
	.thumb_func
_0804DF14:
	.incbin "baserom.gba", 0x4DF14, 0x48
	.global _0804DF5C
	.thumb_func
_0804DF5C:
	.incbin "baserom.gba", 0x4DF5C, 0xA0
	.global _0804DFFC
	.thumb_func
_0804DFFC:
	.incbin "baserom.gba", 0x4DFFC, 0x38
	.global _0804E034
	.thumb_func
_0804E034:
	.incbin "baserom.gba", 0x4E034, 0x34
	.global _0804E068
	.thumb_func
_0804E068:
	.incbin "baserom.gba", 0x4E068, 0xF4
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A83D4
	.4byte gRom_08097318
	.incbin "baserom.gba", 0x4E16C, 0x10
