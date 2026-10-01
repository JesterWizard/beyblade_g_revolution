@ Unmatched ROM 0x0804054C..0x080405A7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004054C
gRomGap004054C:
	.incbin "baserom.gba", 0x4054C, 0x3C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x4058C, 0x1C
