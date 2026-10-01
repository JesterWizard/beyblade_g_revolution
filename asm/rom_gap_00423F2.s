@ Unmatched ROM 0x080423F2..0x0804245B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00423F2
gRomGap00423F2:
	.incbin "baserom.gba", 0x423F2, 0x3E
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x42434, 0x28
