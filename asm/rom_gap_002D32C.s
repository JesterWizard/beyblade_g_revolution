@ Unmatched ROM 0x0802D32C..0x0802D3EF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002D32C
gRomGap002D32C:
	.incbin "baserom.gba", 0x2D32C, 0x34
	.4byte gData_0807741C
	.incbin "baserom.gba", 0x2D364, 0x40
	.4byte gData_0807741C
	.incbin "baserom.gba", 0x2D3A8, 0x44
	.4byte gData_080BB8BC
