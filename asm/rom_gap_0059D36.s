@ Unmatched ROM 0x08059D36..0x08059DC7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0059D36
gRomGap0059D36:
	.incbin "baserom.gba", 0x59D36, 0x4A
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x59D84, 0x44
