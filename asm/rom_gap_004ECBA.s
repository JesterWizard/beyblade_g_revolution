@ Unmatched ROM 0x0804ECBA..0x0804ED8F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004ECBA
gRomGap004ECBA:
	.incbin "baserom.gba", 0x4ECBA, 0xD6
