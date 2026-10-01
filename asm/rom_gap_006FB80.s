@ Unmatched ROM 0x0806FB80..0x0806FBF7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006FB80
gRomGap006FB80:
	.global _0806FB80
	.thumb_func
_0806FB80:
	.incbin "baserom.gba", 0x6FB80, 0x78
