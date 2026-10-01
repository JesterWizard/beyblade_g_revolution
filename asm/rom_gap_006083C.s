@ Unmatched ROM 0x0806083C..0x080608D3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006083C
gRomGap006083C:
	.incbin "baserom.gba", 0x6083C, 0x90
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x608D0, 0x4
