@ Unmatched ROM 0x08038678..0x08038D0F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0038678
gRomGap0038678:
	.global _08038678
	.thumb_func
_08038678:
	.incbin "baserom.gba", 0x38678, 0x64
	.global _080386DC
	.thumb_func
_080386DC:
	.incbin "baserom.gba", 0x386DC, 0x78
	.global _08038754
	.thumb_func
_08038754:
	.incbin "baserom.gba", 0x38754, 0xEC
	.global _08038840
	.thumb_func
_08038840:
	.incbin "baserom.gba", 0x38840, 0xC4
	.global _08038904
	.thumb_func
_08038904:
	.incbin "baserom.gba", 0x38904, 0x98
	.global _0803899C
	.thumb_func
_0803899C:
	.incbin "baserom.gba", 0x3899C, 0x1DC
	.4byte gRom_08110468
	.4byte gRom_0833C640
	.4byte gRom_0833C660
	.4byte gRom_08079698
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.incbin "baserom.gba", 0x38B90, 0x164
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x38CFC, 0x8
	.4byte gRom_08096FBC
	.incbin "baserom.gba", 0x38D08, 0x8
