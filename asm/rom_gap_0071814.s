@ Unmatched ROM 0x08071814..0x08071B4B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0071814
gRomGap0071814:
	.incbin "baserom.gba", 0x71814, 0x2A4
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x71ABC, 0x90
