@ Unmatched ROM 0x0806B6DA..0x0806B723
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006B6DA
gRomGap006B6DA:
	.incbin "baserom.gba", 0x6B6DA, 0x46
	.4byte gData_080BB8BC
