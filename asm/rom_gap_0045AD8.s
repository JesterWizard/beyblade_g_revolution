@ Unmatched ROM 0x08045AD8..0x08045C5B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0045AD8
gRomGap0045AD8:
	.incbin "baserom.gba", 0x45AD8, 0x20
	.global _08045AF8
	.thumb_func
_08045AF8:
	.incbin "baserom.gba", 0x45AF8, 0xC4
	.4byte gRom_0802B7E0
	.incbin "baserom.gba", 0x45BC0, 0x8
	.global _08045BC8
	.thumb_func
_08045BC8:
	.incbin "baserom.gba", 0x45BC8, 0x4C
	.global _08045C14
	.thumb_func
_08045C14:
	.incbin "baserom.gba", 0x45C14, 0x4
	.global _08045C18
	.thumb_func
_08045C18:
	.incbin "baserom.gba", 0x45C18, 0x44
