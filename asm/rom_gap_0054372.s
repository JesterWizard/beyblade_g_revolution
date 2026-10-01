@ Unmatched ROM 0x08054372..0x08054453
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0054372
gRomGap0054372:
	.incbin "baserom.gba", 0x54372, 0x2
	.global _08054374
	.thumb_func
_08054374:
	.incbin "baserom.gba", 0x54374, 0xA4
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x5441C, 0x38
