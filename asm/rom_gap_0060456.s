@ Unmatched ROM 0x08060456..0x08060457
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0060456
gRomGap0060456:
	.incbin "baserom.gba", 0x60456, 0x2
