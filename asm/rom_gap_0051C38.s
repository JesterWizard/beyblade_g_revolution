@ Unmatched ROM 0x08051C38..0x080523A3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0051C38
gRomGap0051C38:
	.global _08051C38
	.thumb_func
_08051C38:
	.incbin "baserom.gba", 0x51C38, 0x27C
	.4byte gRom_08111CB4
	.incbin "baserom.gba", 0x51EB8, 0x28
	.4byte gRom_0811B378
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gData_08096B5C
	.incbin "baserom.gba", 0x51EF0, 0x4
	.4byte gRom_080978E0
	.4byte gData_080BB8C0
	.4byte gRom_082C5960
	.incbin "baserom.gba", 0x51F00, 0x4
	.global _08051F04
	.thumb_func
_08051F04:
	.incbin "baserom.gba", 0x51F04, 0x13C
	.4byte gRom_0811B4C0
	.4byte gRom_0811D5A4
	.4byte gData_080BB8C0
	.4byte gRom_0811F688
	.incbin "baserom.gba", 0x52050, 0x58
	.global _080520A8
	.thumb_func
_080520A8:
	.incbin "baserom.gba", 0x520A8, 0x8C
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x52138, 0x100
	.global _08052238
	.thumb_func
_08052238:
	.incbin "baserom.gba", 0x52238, 0x38
	.global _08052270
	.thumb_func
_08052270:
	.incbin "baserom.gba", 0x52270, 0x44
	.global _080522B4
	.thumb_func
_080522B4:
	.incbin "baserom.gba", 0x522B4, 0x34
	.global _080522E8
	.thumb_func
_080522E8:
	.incbin "baserom.gba", 0x522E8, 0x18
	.global gRom_08052300
gRom_08052300:
	.incbin "baserom.gba", 0x52300, 0x1C
	.global _0805231C
	.thumb_func
_0805231C:
	.incbin "baserom.gba", 0x5231C, 0x34
	.4byte gData_080995AC
	.incbin "baserom.gba", 0x52354, 0x4
	.global _08052358
	.thumb_func
_08052358:
	.incbin "baserom.gba", 0x52358, 0x34
	.4byte gData_080995AC
	.incbin "baserom.gba", 0x52390, 0x14
