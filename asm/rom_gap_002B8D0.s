@ Unmatched ROM 0x0802B8D0..0x0802B90B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002B8D0
gRomGap002B8D0:
	.global _0802B8D0
	.thumb_func
_0802B8D0:
	.incbin "baserom.gba", 0x2B8D0, 0x3C
