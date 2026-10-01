@ Unmatched ROM 0x080679DC..0x08067A9B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00679DC
gRomGap00679DC:
	.incbin "baserom.gba", 0x679DC, 0xBC
	.global _08067A98
	.thumb_func
_08067A98:
	.incbin "baserom.gba", 0x67A98, 0x4
