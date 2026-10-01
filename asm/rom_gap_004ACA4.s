@ Unmatched ROM 0x0804ACA4..0x0804AE93
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004ACA4
gRomGap004ACA4:
	.global _0804ACA4
	.thumb_func
_0804ACA4:
	.incbin "baserom.gba", 0x4ACA4, 0x48
	.global _0804ACEC
	.thumb_func
_0804ACEC:
	.incbin "baserom.gba", 0x4ACEC, 0x54
	.global _0804AD40
	.thumb_func
_0804AD40:
	.incbin "baserom.gba", 0x4AD40, 0x48
	.global _0804AD88
	.thumb_func
_0804AD88:
	.incbin "baserom.gba", 0x4AD88, 0x58
	.global _0804ADE0
	.thumb_func
_0804ADE0:
	.incbin "baserom.gba", 0x4ADE0, 0x64
	.global _0804AE44
	.thumb_func
_0804AE44:
	.incbin "baserom.gba", 0x4AE44, 0x50
