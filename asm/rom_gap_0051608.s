@ Unmatched ROM 0x08051608..0x08051BBB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0051608
gRomGap0051608:
	.global _08051608
	.thumb_func
_08051608:
	.incbin "baserom.gba", 0x51608, 0x54
	.global _0805165C
	.thumb_func
_0805165C:
	.incbin "baserom.gba", 0x5165C, 0x4
	.global _08051660
	.thumb_func
_08051660:
	.incbin "baserom.gba", 0x51660, 0x4
	.global _08051664
	.thumb_func
_08051664:
	.incbin "baserom.gba", 0x51664, 0x4
	.global _08051668
	.thumb_func
_08051668:
	.incbin "baserom.gba", 0x51668, 0x4
	.global _0805166C
	.thumb_func
_0805166C:
	.incbin "baserom.gba", 0x5166C, 0x4
	.global _08051670
	.thumb_func
_08051670:
	.incbin "baserom.gba", 0x51670, 0xF0
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A85B0
	.4byte gRom_083A85C0
	.4byte gRom_083A85D0
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x5177C, 0x4
	.global _08051780
	.thumb_func
_08051780:
	.incbin "baserom.gba", 0x51780, 0xEC
	.global _0805186C
	.thumb_func
_0805186C:
	.incbin "baserom.gba", 0x5186C, 0x4C
	.global _080518B8
	.thumb_func
_080518B8:
	.incbin "baserom.gba", 0x518B8, 0x94
	.global _0805194C
	.thumb_func
_0805194C:
	.incbin "baserom.gba", 0x5194C, 0x44
	.global _08051990
	.thumb_func
_08051990:
	.incbin "baserom.gba", 0x51990, 0x110
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A85E0
	.4byte gRom_083A85FC
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096A58
	.incbin "baserom.gba", 0x51ABC, 0x8
	.4byte gRom_083A8618
	.incbin "baserom.gba", 0x51AC8, 0xCC
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A85E0
	.4byte gRom_083A85FC
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096A6C
	.incbin "baserom.gba", 0x51BB0, 0x8
	.4byte gRom_083A8618
