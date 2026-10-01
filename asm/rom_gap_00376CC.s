@ Unmatched ROM 0x080376CC..0x08038313
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00376CC
gRomGap00376CC:
	.incbin "baserom.gba", 0x376CC, 0x140
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_0809728C
	.incbin "baserom.gba", 0x37818, 0xD0
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x378F0, 0xC8
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x379C0, 0x25C
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_0809728C
	.incbin "baserom.gba", 0x37C28, 0xC4
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_08097818
	.incbin "baserom.gba", 0x37CF8, 0x1FC
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_080978A4
	.incbin "baserom.gba", 0x37F00, 0x2CC
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_0809787C
	.incbin "baserom.gba", 0x381D8, 0x80
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x38260, 0xB4
