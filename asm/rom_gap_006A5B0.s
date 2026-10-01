@ Unmatched ROM 0x0806A5B0..0x0806A6F7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006A5B0
gRomGap006A5B0:
	.incbin "baserom.gba", 0x6A5B0, 0xF0
	.4byte gRom_083D1C14
	.4byte gRom_083D1C28
	.4byte gRom_083D1C38
	.incbin "baserom.gba", 0x6A6AC, 0x4C
