@ Unmatched ROM 0x08034074..0x0803413B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0034074
gRomGap0034074:
	.incbin "baserom.gba", 0x34074, 0xC0
	.4byte gRom_08078C18
	.4byte gRom_08078B98
