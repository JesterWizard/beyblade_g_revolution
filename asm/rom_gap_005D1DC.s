@ Unmatched ROM 0x0805D1DC..0x0805D99B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap005D1DC
gRomGap005D1DC:
	.incbin "baserom.gba", 0x5D1DC, 0x2C
	.4byte gRom_0805D20C
	.global gRom_0805D20C
gRom_0805D20C:
	.4byte gRom_0805D22C
	.4byte gRom_0805D294
	.4byte gRom_0805D374
	.4byte gRom_0805D3D4
	.incbin "baserom.gba", 0x5D21C, 0xC
	.4byte gRom_0805D2F8
	.global gRom_0805D22C
gRom_0805D22C:
	.incbin "baserom.gba", 0x5D22C, 0x68
	.global gRom_0805D294
gRom_0805D294:
	.incbin "baserom.gba", 0x5D294, 0x64
	.global gRom_0805D2F8
gRom_0805D2F8:
	.incbin "baserom.gba", 0x5D2F8, 0x7C
	.global gRom_0805D374
gRom_0805D374:
	.incbin "baserom.gba", 0x5D374, 0x60
	.global gRom_0805D3D4
gRom_0805D3D4:
	.incbin "baserom.gba", 0x5D3D4, 0xCC
	.4byte gRom_0805D4A4
	.global gRom_0805D4A4
gRom_0805D4A4:
	.4byte gRom_0805D4D4
	.4byte gRom_0805D54C
	.4byte gRom_0805D6C0
	.4byte gRom_0805D738
	.incbin "baserom.gba", 0x5D4B4, 0xC
	.4byte gRom_0805D5C4
	.4byte gRom_0805D7AC
	.4byte gRom_0805D7F0
	.4byte gRom_0805D834
	.4byte gRom_0805D874
	.global gRom_0805D4D4
gRom_0805D4D4:
	.incbin "baserom.gba", 0x5D4D4, 0x78
	.global gRom_0805D54C
gRom_0805D54C:
	.incbin "baserom.gba", 0x5D54C, 0x78
	.global gRom_0805D5C4
gRom_0805D5C4:
	.incbin "baserom.gba", 0x5D5C4, 0xFC
	.global gRom_0805D6C0
gRom_0805D6C0:
	.incbin "baserom.gba", 0x5D6C0, 0x78
	.global gRom_0805D738
gRom_0805D738:
	.incbin "baserom.gba", 0x5D738, 0x74
	.global gRom_0805D7AC
gRom_0805D7AC:
	.incbin "baserom.gba", 0x5D7AC, 0x44
	.global gRom_0805D7F0
gRom_0805D7F0:
	.incbin "baserom.gba", 0x5D7F0, 0x44
	.global gRom_0805D834
gRom_0805D834:
	.incbin "baserom.gba", 0x5D834, 0x40
	.global gRom_0805D874
gRom_0805D874:
	.incbin "baserom.gba", 0x5D874, 0x128
