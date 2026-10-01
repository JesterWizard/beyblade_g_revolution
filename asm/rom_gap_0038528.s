@ Unmatched ROM 0x08038528..0x0803857F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0038528
gRomGap0038528:
	.incbin "baserom.gba", 0x38528, 0x54
	.4byte gRom_0833B768
