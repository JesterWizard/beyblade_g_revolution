@ Unmatched ROM 0x0806A5B0..0x0806A6F7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006A5B0
gRomGap006A5B0:
	.incbin "baserom.gba", 0x6A5B0, 0x40
	.4byte gRom_083D1BA8
	.4byte gRom_083D1BB4
	.incbin "baserom.gba", 0x6A5F8, 0x44
	.4byte gRom_083D1BA8
	.4byte gRom_083D1BE4
	.incbin "baserom.gba", 0x6A644, 0x5C
	.4byte gRom_083D1C14
	.4byte gRom_083D1C28
	.4byte gRom_083D1C38
	.incbin "baserom.gba", 0x6A6AC, 0x44
	.4byte gRom_083D1C64
	.4byte gRom_083D1C28
