@ Unmatched ROM 0x0804E2B0..0x0804E4F3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004E2B0
gRomGap004E2B0:
	.global _0804E2B0
	.thumb_func
_0804E2B0:
	.incbin "baserom.gba", 0x4E2B0, 0x20
	.global _0804E2D0
	.thumb_func
_0804E2D0:
	.incbin "baserom.gba", 0x4E2D0, 0x50
	.global _0804E320
	.thumb_func
_0804E320:
	.incbin "baserom.gba", 0x4E320, 0x6C
	.global _0804E38C
	.thumb_func
_0804E38C:
	.incbin "baserom.gba", 0x4E38C, 0x18
	.global _0804E3A4
	.thumb_func
_0804E3A4:
	.incbin "baserom.gba", 0x4E3A4, 0xCC
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8404
	.4byte gRom_080972C8
	.incbin "baserom.gba", 0x4E480, 0x74
