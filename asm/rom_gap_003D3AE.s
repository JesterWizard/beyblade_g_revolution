@ Unmatched ROM 0x0803D3AE..0x0803D4C3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003D3AE
gRomGap003D3AE:
	.incbin "baserom.gba", 0x3D3AE, 0x4E
	.4byte gRom_08096E2C
	.incbin "baserom.gba", 0x3D400, 0x2C
	.4byte gRom_08097200
	.incbin "baserom.gba", 0x3D430, 0x38
	.4byte gRom_08097214
	.incbin "baserom.gba", 0x3D46C, 0x8
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3D47C, 0x2C
	.4byte gRom_08097228
	.incbin "baserom.gba", 0x3D4AC, 0x8
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3D4BC, 0x8
