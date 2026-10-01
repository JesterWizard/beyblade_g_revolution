@ Unmatched ROM 0x08061B30..0x08061BAB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0061B30
gRomGap0061B30:
	.incbin "baserom.gba", 0x61B30, 0x78
	.4byte gData_080BB8C0
