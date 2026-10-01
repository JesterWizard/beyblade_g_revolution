@ Unmatched ROM 0x08034AD8..0x08034FBB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0034AD8
gRomGap0034AD8:
	.incbin "baserom.gba", 0x34AD8, 0x1BC
	.4byte gRom_08034C98
	.global gRom_08034C98
gRom_08034C98:
	.4byte gRom_08034CAC
	.4byte gRom_08034CAC
	.4byte gRom_08034CB4
	.4byte gRom_08034CE4
	.4byte gRom_08034CFC
	.global gRom_08034CAC
gRom_08034CAC:
	.incbin "baserom.gba", 0x34CAC, 0x8
	.global gRom_08034CB4
gRom_08034CB4:
	.incbin "baserom.gba", 0x34CB4, 0x30
	.global gRom_08034CE4
gRom_08034CE4:
	.incbin "baserom.gba", 0x34CE4, 0x18
	.global gRom_08034CFC
gRom_08034CFC:
	.incbin "baserom.gba", 0x34CFC, 0x108
	.4byte gRom_08034E08
	.global gRom_08034E08
gRom_08034E08:
	.4byte gRom_08034E1C
	.4byte gRom_08034E1C
	.4byte gRom_08034E28
	.4byte gRom_08034E28
	.incbin "baserom.gba", 0x34E18, 0x4
	.global gRom_08034E1C
gRom_08034E1C:
	.incbin "baserom.gba", 0x34E1C, 0xC
	.global gRom_08034E28
gRom_08034E28:
	.incbin "baserom.gba", 0x34E28, 0x194
