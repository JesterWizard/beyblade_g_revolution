@ Unmatched ROM 0x08060446..0x08060447
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0060446
gRomGap0060446:
	.incbin "baserom.gba", 0x60446, 0x2
