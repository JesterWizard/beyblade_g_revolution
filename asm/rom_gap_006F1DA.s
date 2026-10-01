@ Unmatched ROM 0x0806F1DA..0x0806F42F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006F1DA
gRomGap006F1DA:
	.incbin "baserom.gba", 0x6F1DA, 0x2A
	.global gRom_0806F204
gRom_0806F204:
	.incbin "baserom.gba", 0x6F204, 0xB8
	.4byte gRom_080BB8B4
	.incbin "baserom.gba", 0x6F2C0, 0xF8
	.4byte gRom_083D1FB0
	.4byte gRom_083D2000
	.incbin "baserom.gba", 0x6F3C0, 0x4
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x6F3C8, 0x68
