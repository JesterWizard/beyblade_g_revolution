@ Unmatched ROM 0x08041A5C..0x08041B73
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0041A5C
gRomGap0041A5C:
	.incbin "baserom.gba", 0x41A5C, 0x68
	.global _08041AC4
	.thumb_func
_08041AC4:
	.incbin "baserom.gba", 0x41AC4, 0xB0
