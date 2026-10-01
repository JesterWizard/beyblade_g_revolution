@ Unmatched ROM 0x08033A98..0x08033C1B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0033A98
gRomGap0033A98:
	.global _08033A98
	.thumb_func
_08033A98:
	.incbin "baserom.gba", 0x33A98, 0x18
	.global _08033AB0
	.thumb_func
_08033AB0:
	.incbin "baserom.gba", 0x33AB0, 0x18
	.global _08033AC8
	.thumb_func
_08033AC8:
	.incbin "baserom.gba", 0x33AC8, 0x6C
	.4byte gRom_080784A4
	.4byte gRom_0833C530
	.incbin "baserom.gba", 0x33B3C, 0xC
	.4byte gRom_0807850C
	.4byte gRom_0833C544
	.incbin "baserom.gba", 0x33B50, 0xC
	.4byte gRom_080784D8
	.4byte gRom_0833C558
	.incbin "baserom.gba", 0x33B64, 0xC
	.4byte gRom_08078540
	.4byte gRom_0833C570
	.incbin "baserom.gba", 0x33B78, 0x3C
	.4byte gRom_080784A4
	.4byte gRom_0833C588
	.incbin "baserom.gba", 0x33BBC, 0x60
