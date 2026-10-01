@ Unmatched ROM 0x0806F460..0x0806F8C3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006F460
gRomGap006F460:
	.incbin "baserom.gba", 0x6F460, 0xD0
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x6F534, 0x144
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x6F67C, 0x58
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x6F6D8, 0x1EC
