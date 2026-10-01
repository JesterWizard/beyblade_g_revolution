@ Unmatched ROM 0x0806F1DA..0x0806F42F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006F1DA
gRomGap006F1DA:
	.incbin "baserom.gba", 0x6F1DA, 0x1EA
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x6F3C8, 0x68
