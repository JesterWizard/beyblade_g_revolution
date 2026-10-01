@ Unmatched ROM 0x08041808..0x08041857
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0041808
gRomGap0041808:
	.incbin "baserom.gba", 0x41808, 0x2C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x41838, 0x20
