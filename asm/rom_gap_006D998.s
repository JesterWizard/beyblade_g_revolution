@ Unmatched ROM 0x0806D998..0x0806DEC7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006D998
gRomGap006D998:
	.global _0806D998
	.thumb_func
_0806D998:
	.incbin "baserom.gba", 0x6D998, 0x530
