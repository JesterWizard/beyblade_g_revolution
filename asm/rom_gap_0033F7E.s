@ Unmatched ROM 0x08033F7E..0x0803403B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0033F7E
gRomGap0033F7E:
	.incbin "baserom.gba", 0x33F7E, 0xAE
	.4byte gRom_08078C88
	.incbin "baserom.gba", 0x34030, 0xC
