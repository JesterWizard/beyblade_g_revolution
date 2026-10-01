@ Unmatched ROM 0x080407B4..0x080408C3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00407B4
gRomGap00407B4:
	.global _080407B4
	.thumb_func
_080407B4:
	.incbin "baserom.gba", 0x407B4, 0x38
	.global _080407EC
	.thumb_func
_080407EC:
	.incbin "baserom.gba", 0x407EC, 0x1C
	.global gRom_08040808
gRom_08040808:
	.incbin "baserom.gba", 0x40808, 0x3C
	.global _08040844
	.thumb_func
_08040844:
	.incbin "baserom.gba", 0x40844, 0x1C
	.global _08040860
	.thumb_func
_08040860:
	.incbin "baserom.gba", 0x40860, 0x18
	.global _08040878
	.thumb_func
_08040878:
	.incbin "baserom.gba", 0x40878, 0x8
	.global gRom_08040880
gRom_08040880:
	.incbin "baserom.gba", 0x40880, 0x24
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x408AC, 0x10
	.global gRom_080408BC
gRom_080408BC:
	.incbin "baserom.gba", 0x408BC, 0x8
