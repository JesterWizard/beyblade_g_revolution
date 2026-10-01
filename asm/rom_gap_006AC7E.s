@ Unmatched ROM 0x0806AC7E..0x0806B063
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006AC7E
gRomGap006AC7E:
	.incbin "baserom.gba", 0x6AC7E, 0x136
	.4byte gRom_083D1CB4
	.incbin "baserom.gba", 0x6ADB8, 0x2AC
