@ Unmatched ROM 0x0803E8E8..0x0803E933
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003E8E8
gRomGap003E8E8:
	.global _0803E8E8
	.thumb_func
_0803E8E8:
	.incbin "baserom.gba", 0x3E8E8, 0x28
	.global _0803E910
	.thumb_func
_0803E910:
	.incbin "baserom.gba", 0x3E910, 0x24
