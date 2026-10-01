@ Unmatched ROM 0x08071C34..0x08071E03
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0071C34
gRomGap0071C34:
	.incbin "baserom.gba", 0x71C34, 0x88
	.4byte gRom_080BB898
	.incbin "baserom.gba", 0x71CC0, 0x138
	.4byte gRom_080BB89C
	.incbin "baserom.gba", 0x71DFC, 0x8
