@ Unmatched ROM 0x08042F9C..0x080433F3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0042F9C
gRomGap0042F9C:
	.incbin "baserom.gba", 0x42F9C, 0x4C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x42FEC, 0x4
	.4byte gRom_08094B68
	.incbin "baserom.gba", 0x42FF4, 0x28
	.global _0804301C
	.thumb_func
_0804301C:
	.incbin "baserom.gba", 0x4301C, 0x30
	.global _0804304C
	.thumb_func
_0804304C:
	.incbin "baserom.gba", 0x4304C, 0x37C
	.global _080433C8
	.thumb_func
_080433C8:
	.incbin "baserom.gba", 0x433C8, 0x2C
