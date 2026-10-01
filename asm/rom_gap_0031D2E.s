@ Unmatched ROM 0x08031D2E..0x080320CB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0031D2E
gRomGap0031D2E:
	.incbin "baserom.gba", 0x31D2E, 0x2
	.global _08031D30
	.thumb_func
_08031D30:
	.incbin "baserom.gba", 0x31D30, 0x39C
