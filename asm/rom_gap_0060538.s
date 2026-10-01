@ Unmatched ROM 0x08060538..0x08060757
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0060538
gRomGap0060538:
	.incbin "baserom.gba", 0x60538, 0xCC
	.global _08060604
	.thumb_func
_08060604:
	.incbin "baserom.gba", 0x60604, 0x154
