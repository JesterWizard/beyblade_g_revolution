@ Unmatched ROM 0x08063024..0x0806306B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0063024
gRomGap0063024:
	.incbin "baserom.gba", 0x63024, 0x44
	.4byte gData_080BB8C0
