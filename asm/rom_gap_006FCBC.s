@ Unmatched ROM 0x0806FCBC..0x0806FDB3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006FCBC
gRomGap006FCBC:
	.incbin "baserom.gba", 0x6FCBC, 0x50
	.4byte gRom_083D21E0
	.4byte gRom_083D21F4
	.incbin "baserom.gba", 0x6FD14, 0x4
	.4byte gRom_083D2204
	.4byte gRom_083D221C
	.incbin "baserom.gba", 0x6FD20, 0x94
