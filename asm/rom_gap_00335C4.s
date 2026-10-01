@ Unmatched ROM 0x080335C4..0x0803370B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00335C4
gRomGap00335C4:
	.incbin "baserom.gba", 0x335C4, 0x138
	.4byte gData_0810B4E0
	.incbin "baserom.gba", 0x33700, 0xC
