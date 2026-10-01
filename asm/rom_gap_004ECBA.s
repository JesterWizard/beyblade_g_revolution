@ Unmatched ROM 0x0804ECBA..0x0804ED8F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004ECBA
gRomGap004ECBA:
	.incbin "baserom.gba", 0x4ECBA, 0x2
	.global _0804ECBC
	.thumb_func
_0804ECBC:
	.incbin "baserom.gba", 0x4ECBC, 0x64
	.global _0804ED20
	.thumb_func
_0804ED20:
	.incbin "baserom.gba", 0x4ED20, 0x70
