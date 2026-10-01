@ Unmatched ROM 0x0804CA54..0x0804CE2B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004CA54
gRomGap004CA54:
	.global _0804CA54
	.thumb_func
_0804CA54:
	.incbin "baserom.gba", 0x4CA54, 0xB0
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _0804CB0C
	.thumb_func
_0804CB0C:
	.incbin "baserom.gba", 0x4CB0C, 0x70
	.global _0804CB7C
	.thumb_func
_0804CB7C:
	.incbin "baserom.gba", 0x4CB7C, 0xB0
	.global _0804CC2C
	.thumb_func
_0804CC2C:
	.incbin "baserom.gba", 0x4CC2C, 0x90
	.4byte gRom_083A7E94
	.global _0804CCC0
	.thumb_func
_0804CCC0:
	.incbin "baserom.gba", 0x4CCC0, 0x38
	.global _0804CCF8
	.thumb_func
_0804CCF8:
	.incbin "baserom.gba", 0x4CCF8, 0x34
	.global _0804CD2C
	.thumb_func
_0804CD2C:
	.incbin "baserom.gba", 0x4CD2C, 0xF0
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7EB0
	.4byte gRom_083A7EC8
