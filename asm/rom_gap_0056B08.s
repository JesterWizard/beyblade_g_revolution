@ Unmatched ROM 0x08056B08..0x08056BA3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0056B08
gRomGap0056B08:
	.incbin "baserom.gba", 0x56B08, 0x4
	.global _08056B0C
	.thumb_func
_08056B0C:
	.incbin "baserom.gba", 0x56B0C, 0x4
	.global _08056B10
	.thumb_func
_08056B10:
	.incbin "baserom.gba", 0x56B10, 0x94
