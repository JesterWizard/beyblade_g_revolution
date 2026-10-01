@ Unmatched ROM 0x0803EC5C..0x0803ECB7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003EC5C
gRomGap003EC5C:
	.incbin "baserom.gba", 0x3EC5C, 0x20
	.4byte gData_0807BB80
	.4byte gRom_0803EC84
	.global gRom_0803EC84
gRom_0803EC84:
	.4byte gRom_0803ECA8
	.4byte gRom_0803ECA8
	.4byte gRom_0803ECA8
	.4byte gRom_0803ECAC
	.4byte gRom_0803ECAC
	.4byte gRom_0803ECAC
	.4byte gRom_0803ECB0
	.4byte gRom_0803ECB0
	.4byte gRom_0803ECB0
	.global gRom_0803ECA8
gRom_0803ECA8:
	.incbin "baserom.gba", 0x3ECA8, 0x4
	.global gRom_0803ECAC
gRom_0803ECAC:
	.incbin "baserom.gba", 0x3ECAC, 0x4
	.global gRom_0803ECB0
gRom_0803ECB0:
	.incbin "baserom.gba", 0x3ECB0, 0x8
