@ Unmatched ROM 0x0806F460..0x0806F8C3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006F460
gRomGap006F460:
	.incbin "baserom.gba", 0x6F460, 0xD0
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x6F534, 0x144
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x6F67C, 0x4
	.4byte gRom_080BB84C
	.incbin "baserom.gba", 0x6F684, 0x8
	.4byte gRom_080BB848
	.incbin "baserom.gba", 0x6F690, 0x44
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x6F6D8, 0xFC
	.4byte _0806F844 + 1
	.incbin "baserom.gba", 0x6F7D8, 0x6C
	.global _0806F844
	.thumb_func
_0806F844:
	.incbin "baserom.gba", 0x6F844, 0x78
	.4byte gRom_080BB854
	.incbin "baserom.gba", 0x6F8C0, 0x4
