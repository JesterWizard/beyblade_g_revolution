@ Unmatched ROM 0x0803FE10..0x0803FFAF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003FE10
gRomGap003FE10:
	.global _0803FE10
	.thumb_func
_0803FE10:
	.incbin "baserom.gba", 0x3FE10, 0xC0
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.incbin "baserom.gba", 0x3FED8, 0x8
	.4byte gRom_0833DC34
	.4byte gRom_0833DC18
	.4byte gRom_0833DC50
	.incbin "baserom.gba", 0x3FEEC, 0xB8
	.4byte gRom_0833DC34
	.4byte gRom_0833DC18
	.4byte gRom_0833DC50
