@ Unmatched ROM 0x0804C38C..0x0804C8BB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004C38C
gRomGap004C38C:
	.global _0804C38C
	.thumb_func
_0804C38C:
	.incbin "baserom.gba", 0x4C38C, 0xC4
	.4byte gData_080989F0
	.incbin "baserom.gba", 0x4C454, 0x1C
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _0804C478
	.thumb_func
_0804C478:
	.incbin "baserom.gba", 0x4C478, 0x70
	.global _0804C4E8
	.thumb_func
_0804C4E8:
	.incbin "baserom.gba", 0x4C4E8, 0x114
	.global _0804C5FC
	.thumb_func
_0804C5FC:
	.incbin "baserom.gba", 0x4C5FC, 0x90
	.4byte gRom_083A7E28
	.4byte gData_080989F0
	.incbin "baserom.gba", 0x4C694, 0xC
	.global _0804C6A0
	.thumb_func
_0804C6A0:
	.incbin "baserom.gba", 0x4C6A0, 0x38
	.global _0804C6D8
	.thumb_func
_0804C6D8:
	.incbin "baserom.gba", 0x4C6D8, 0x4C
	.global _0804C724
	.thumb_func
_0804C724:
	.incbin "baserom.gba", 0x4C724, 0x17C
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7E40
	.4byte gRom_083A7E5C
	.4byte gRom_083A7E78
	.4byte gData_082BCD00
	.4byte gData_080B738E
