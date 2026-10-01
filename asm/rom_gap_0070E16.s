@ Unmatched ROM 0x08070E16..0x080712CB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0070E16
gRomGap0070E16:
	.incbin "baserom.gba", 0x70E16, 0x13A
	.4byte gRom_083D2300
	.4byte gRom_083D2304
	.4byte gRom_083D2308
	.incbin "baserom.gba", 0x70F5C, 0xAC
	.4byte gRom_083D2300
	.4byte gRom_083D2304
	.4byte gRom_083D2308
	.incbin "baserom.gba", 0x71014, 0x2B8
