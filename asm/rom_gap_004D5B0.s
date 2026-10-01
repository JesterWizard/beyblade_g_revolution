@ Unmatched ROM 0x0804D5B0..0x0804DB27
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004D5B0
gRomGap004D5B0:
	.global _0804D5B0
	.thumb_func
_0804D5B0:
	.incbin "baserom.gba", 0x4D5B0, 0x78
	.global _0804D628
	.thumb_func
_0804D628:
	.incbin "baserom.gba", 0x4D628, 0xD0
	.global _0804D6F8
	.thumb_func
_0804D6F8:
	.incbin "baserom.gba", 0x4D6F8, 0x80
	.global _0804D778
	.thumb_func
_0804D778:
	.incbin "baserom.gba", 0x4D778, 0x94
	.4byte gData_080BB8BC
	.global _0804D810
	.thumb_func
_0804D810:
	.incbin "baserom.gba", 0x4D810, 0x78
	.global _0804D888
	.thumb_func
_0804D888:
	.incbin "baserom.gba", 0x4D888, 0x140
	.4byte gData_08098A20
	.incbin "baserom.gba", 0x4D9CC, 0x4C
	.4byte gData_08098A20
	.incbin "baserom.gba", 0x4DA1C, 0xE8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8374
	.4byte gRom_083A838C
	.4byte gRom_083A83A4
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_083A83BC
	.4byte gRom_083A83C8
