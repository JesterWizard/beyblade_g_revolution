@ Unmatched ROM 0x0802F57C..0x0802FA93
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002F57C
gRomGap002F57C:
	.global _0802F57C
	.thumb_func
_0802F57C:
	.incbin "baserom.gba", 0x2F57C, 0xB8
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x2F638, 0xC
	.global _0802F644
	.thumb_func
_0802F644:
	.incbin "baserom.gba", 0x2F644, 0x48
	.global _0802F68C
	.thumb_func
_0802F68C:
	.incbin "baserom.gba", 0x2F68C, 0x88
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2F718, 0xF8
	.global _0802F810
	.thumb_func
_0802F810:
	.incbin "baserom.gba", 0x2F810, 0x64
	.global _0802F874
	.thumb_func
_0802F874:
	.incbin "baserom.gba", 0x2F874, 0x6C
	.global _0802F8E0
	.thumb_func
_0802F8E0:
	.incbin "baserom.gba", 0x2F8E0, 0x44
	.global _0802F924
	.thumb_func
_0802F924:
	.incbin "baserom.gba", 0x2F924, 0x40
	.global _0802F964
	.thumb_func
_0802F964:
	.incbin "baserom.gba", 0x2F964, 0x90
	.global gRom_0802F9F4
gRom_0802F9F4:
	.incbin "baserom.gba", 0x2F9F4, 0x10
	.global gRom_0802FA04
gRom_0802FA04:
	.incbin "baserom.gba", 0x2FA04, 0x74
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833C024
	.4byte gRom_0833C040
	.4byte gRom_0833C05C
	.4byte gData_082BCD00
	.4byte gData_080B738E
