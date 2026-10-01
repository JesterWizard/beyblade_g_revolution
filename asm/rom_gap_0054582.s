@ Unmatched ROM 0x08054582..0x08054CF3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0054582
gRomGap0054582:
	.incbin "baserom.gba", 0x54582, 0x62
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _080545EC
	.thumb_func
_080545EC:
	.incbin "baserom.gba", 0x545EC, 0x188
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x54788, 0x10
	.global _08054798
	.thumb_func
_08054798:
	.incbin "baserom.gba", 0x54798, 0x160
	.global _080548F8
	.thumb_func
_080548F8:
	.incbin "baserom.gba", 0x548F8, 0xA4
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x549A0, 0xD0
	.global _08054A70
	.thumb_func
_08054A70:
	.incbin "baserom.gba", 0x54A70, 0x44
	.global _08054AB4
	.thumb_func
_08054AB4:
	.incbin "baserom.gba", 0x54AB4, 0x38
	.global _08054AEC
	.thumb_func
_08054AEC:
	.incbin "baserom.gba", 0x54AEC, 0x2C
	.global _08054B18
	.thumb_func
_08054B18:
	.incbin "baserom.gba", 0x54B18, 0x1A8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8828
	.4byte gRom_083A883C
	.4byte gRom_083A8850
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_080973B8
	.incbin "baserom.gba", 0x54CE0, 0x8
	.4byte gRom_080973CC
	.4byte gRom_080973E0
	.4byte gRom_0809746C
