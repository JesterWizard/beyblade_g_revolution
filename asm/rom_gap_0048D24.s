@ Unmatched ROM 0x08048D24..0x08048DB7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0048D24
gRomGap0048D24:
	.global _08048D24
	.thumb_func
_08048D24:
	.incbin "baserom.gba", 0x48D24, 0x38
	.global _08048D5C
	.thumb_func
_08048D5C:
	.incbin "baserom.gba", 0x48D5C, 0x5C
