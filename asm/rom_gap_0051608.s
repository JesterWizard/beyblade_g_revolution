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
	.incbin "baserom.gba", 0x51660, 0x100
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
	.incbin "baserom.gba", 0x518B8, 0x1E8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A85E0
	.4byte gRom_083A85FC
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096A58
	.incbin "baserom.gba", 0x51ABC, 0xD8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A85E0
	.4byte gRom_083A85FC
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096A6C
	.incbin "baserom.gba", 0x51BB0, 0xC
