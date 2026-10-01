@ Unmatched ROM 0x08073660..0x080737BF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0073660
gRomGap0073660:
	.incbin "baserom.gba", 0x73660, 0x78
	.4byte gRom_083D270C
	.incbin "baserom.gba", 0x736DC, 0xE4
