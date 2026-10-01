@ Unmatched ROM 0x08072CD8..0x08072F93
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0072CD8
gRomGap0072CD8:
	.incbin "baserom.gba", 0x72CD8, 0x48
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x72D24, 0x64
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x72D8C, 0x208
