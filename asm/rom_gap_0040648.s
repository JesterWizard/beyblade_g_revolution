@ Unmatched ROM 0x08040648..0x0804067F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0040648
gRomGap0040648:
	.incbin "baserom.gba", 0x40648, 0x1C
	.global _08040664
	.thumb_func
_08040664:
	.incbin "baserom.gba", 0x40664, 0x1C
