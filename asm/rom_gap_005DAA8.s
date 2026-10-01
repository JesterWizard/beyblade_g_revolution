@ Unmatched ROM 0x0805DAA8..0x0805E043
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap005DAA8
gRomGap005DAA8:
	.incbin "baserom.gba", 0x5DAA8, 0x2C
	.4byte gRom_0805DAD8
	.global gRom_0805DAD8
gRom_0805DAD8:
	.4byte gRom_0805DB08
	.4byte gRom_0805DB80
	.4byte gRom_0805DCB4
	.4byte gRom_0805DD2C
	.incbin "baserom.gba", 0x5DAE8, 0xC
	.4byte gRom_0805DBFC
	.4byte gRom_0805DDA0
	.4byte gRom_0805DDE4
	.4byte gRom_0805DE28
	.4byte gRom_0805DE68
	.global gRom_0805DB08
gRom_0805DB08:
	.incbin "baserom.gba", 0x5DB08, 0x78
	.global gRom_0805DB80
gRom_0805DB80:
	.incbin "baserom.gba", 0x5DB80, 0x7C
	.global gRom_0805DBFC
gRom_0805DBFC:
	.incbin "baserom.gba", 0x5DBFC, 0xB8
	.global gRom_0805DCB4
gRom_0805DCB4:
	.incbin "baserom.gba", 0x5DCB4, 0x78
	.global gRom_0805DD2C
gRom_0805DD2C:
	.incbin "baserom.gba", 0x5DD2C, 0x74
	.global gRom_0805DDA0
gRom_0805DDA0:
	.incbin "baserom.gba", 0x5DDA0, 0x44
	.global gRom_0805DDE4
gRom_0805DDE4:
	.incbin "baserom.gba", 0x5DDE4, 0x44
	.global gRom_0805DE28
gRom_0805DE28:
	.incbin "baserom.gba", 0x5DE28, 0x40
	.global gRom_0805DE68
gRom_0805DE68:
	.incbin "baserom.gba", 0x5DE68, 0x1DC
