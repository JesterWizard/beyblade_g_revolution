@ Unmatched ROM 0x080602CE..0x08060393
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00602CE
gRomGap00602CE:
	.incbin "baserom.gba", 0x602CE, 0xC6
