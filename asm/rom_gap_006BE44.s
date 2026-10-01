@ Unmatched ROM 0x0806BE44..0x0806C387
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006BE44
gRomGap006BE44:
	.incbin "baserom.gba", 0x6BE44, 0x1B8
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x6C000, 0xF8
	.4byte gRom_083D1E20
	.4byte gRom_083D1E5C
	.4byte gRom_083D1E60
	.incbin "baserom.gba", 0x6C104, 0x284
