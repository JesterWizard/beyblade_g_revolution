@ Unmatched ROM 0x08035014..0x0803501F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0035014
gRomGap0035014:
	.incbin "baserom.gba", 0x35014, 0xC
