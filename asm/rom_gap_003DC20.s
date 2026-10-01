@ Unmatched ROM 0x0803DC20..0x0803DCFB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003DC20
gRomGap003DC20:
	.incbin "baserom.gba", 0x3DC20, 0x24
	.4byte gData_080796DC
	.incbin "baserom.gba", 0x3DC48, 0x1C
	.4byte gData_08097458
	.incbin "baserom.gba", 0x3DC68, 0x6C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x3DCD8, 0x4
	.4byte gData_0807A1F4
	.incbin "baserom.gba", 0x3DCE0, 0x14
	.4byte gRom_0833D19C
	.4byte gRom_0833D1C4
