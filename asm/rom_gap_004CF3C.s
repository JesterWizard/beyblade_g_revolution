@ Unmatched ROM 0x0804CF3C..0x0804D41F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004CF3C
gRomGap004CF3C:
	.global _0804CF3C
	.thumb_func
_0804CF3C:
	.incbin "baserom.gba", 0x4CF3C, 0x94
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _0804CFD8
	.thumb_func
_0804CFD8:
	.incbin "baserom.gba", 0x4CFD8, 0x70
	.global _0804D048
	.thumb_func
_0804D048:
	.incbin "baserom.gba", 0x4D048, 0x128
	.global _0804D170
	.thumb_func
_0804D170:
	.incbin "baserom.gba", 0x4D170, 0x68
	.4byte gRom_083A7EF8
	.global _0804D1DC
	.thumb_func
_0804D1DC:
	.incbin "baserom.gba", 0x4D1DC, 0x38
	.global _0804D214
	.thumb_func
_0804D214:
	.incbin "baserom.gba", 0x4D214, 0x4C
	.global _0804D260
	.thumb_func
_0804D260:
	.incbin "baserom.gba", 0x4D260, 0x1A0
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7F14
	.4byte gRom_083A7F30
	.4byte gRom_083A7F4C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_0811A764
