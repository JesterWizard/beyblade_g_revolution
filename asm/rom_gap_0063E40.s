@ Unmatched ROM 0x08063E40..0x0806555F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0063E40
gRomGap0063E40:
	.global _08063E40
	.thumb_func
_08063E40:
	.incbin "baserom.gba", 0x63E40, 0x74
	.global _08063EB4
	.thumb_func
_08063EB4:
	.incbin "baserom.gba", 0x63EB4, 0x28
	.global _08063EDC
	.thumb_func
_08063EDC:
	.incbin "baserom.gba", 0x63EDC, 0xCC
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x63FAC, 0x4
	.global _08063FB0
	.thumb_func
_08063FB0:
	.incbin "baserom.gba", 0x63FB0, 0x40
	.global _08063FF0
	.thumb_func
_08063FF0:
	.incbin "baserom.gba", 0x63FF0, 0x38
	.global _08064028
	.thumb_func
_08064028:
	.incbin "baserom.gba", 0x64028, 0x44
	.global _0806406C
	.thumb_func
_0806406C:
	.incbin "baserom.gba", 0x6406C, 0x18
	.global _08064084
	.thumb_func
_08064084:
	.incbin "baserom.gba", 0x64084, 0x6C
	.global _080640F0
	.thumb_func
_080640F0:
	.incbin "baserom.gba", 0x640F0, 0xA0
	.4byte gRom_080B8FD0
	.4byte gRom_082AB6B0
	.global _08064198
	.thumb_func
_08064198:
	.incbin "baserom.gba", 0x64198, 0xC8
	.global _08064260
	.thumb_func
_08064260:
	.incbin "baserom.gba", 0x64260, 0x74
	.global _080642D4
	.thumb_func
_080642D4:
	.incbin "baserom.gba", 0x642D4, 0x70
	.global _08064344
	.thumb_func
_08064344:
	.incbin "baserom.gba", 0x64344, 0xF4
	.4byte gRom_0806443C
	.global gRom_0806443C
gRom_0806443C:
	.4byte gRom_08064450
	.4byte gRom_08064458
	.4byte gRom_08064460
	.4byte gRom_08064468
	.4byte gRom_08064470
	.global gRom_08064450
gRom_08064450:
	.incbin "baserom.gba", 0x64450, 0x4
	.4byte gRom_080BAF48
	.global gRom_08064458
gRom_08064458:
	.incbin "baserom.gba", 0x64458, 0x4
	.4byte _080BAF4C + 1
	.global gRom_08064460
gRom_08064460:
	.incbin "baserom.gba", 0x64460, 0x8
	.global gRom_08064468
gRom_08064468:
	.incbin "baserom.gba", 0x64468, 0x8
	.global gRom_08064470
gRom_08064470:
	.incbin "baserom.gba", 0x64470, 0x3C
	.4byte gRom_080BAF5C
	.4byte gRom_080BAED8
	.global _080644B4
	.thumb_func
_080644B4:
	.incbin "baserom.gba", 0x644B4, 0x8C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096BAC
	.incbin "baserom.gba", 0x6454C, 0xC
	.global _08064558
	.thumb_func
_08064558:
	.incbin "baserom.gba", 0x64558, 0xB4
	.4byte gRom_08096BAC
	.incbin "baserom.gba", 0x64610, 0xC
	.global _0806461C
	.thumb_func
_0806461C:
	.incbin "baserom.gba", 0x6461C, 0x44
	.global _08064660
	.thumb_func
_08064660:
	.incbin "baserom.gba", 0x64660, 0x338
	.4byte gRom_080BAF18
	.incbin "baserom.gba", 0x6499C, 0x4
	.4byte gRom_082A478C
	.4byte gRom_082AB778
	.4byte gRom_082ADA14
	.4byte gRom_082AB6B0
	.incbin "baserom.gba", 0x649B0, 0x4
	.4byte gRom_080BADF4
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x649C0, 0x4
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_0809697C
	.4byte gData_08096B5C
	.4byte gRom_080978E0
	.4byte gRom_082AFCB0
	.global _080649DC
	.thumb_func
_080649DC:
	.incbin "baserom.gba", 0x649DC, 0x140
	.global _08064B1C
	.thumb_func
_08064B1C:
	.incbin "baserom.gba", 0x64B1C, 0x90
	.global _08064BAC
	.thumb_func
_08064BAC:
	.incbin "baserom.gba", 0x64BAC, 0x1C
	.global _08064BC8
	.thumb_func
_08064BC8:
	.incbin "baserom.gba", 0x64BC8, 0x38
	.global _08064C00
	.thumb_func
_08064C00:
	.incbin "baserom.gba", 0x64C00, 0xCC
	.4byte gRom_083A8E1C
	.incbin "baserom.gba", 0x64CD0, 0x8
	.global _08064CD8
	.thumb_func
_08064CD8:
	.incbin "baserom.gba", 0x64CD8, 0xCC
	.4byte gRom_083A8E1C
	.incbin "baserom.gba", 0x64DA8, 0x8
	.global _08064DB0
	.thumb_func
_08064DB0:
	.incbin "baserom.gba", 0x64DB0, 0x60
	.global _08064E10
	.thumb_func
_08064E10:
	.incbin "baserom.gba", 0x64E10, 0x120
	.4byte gData_082BCD00
	.global _08064F34
	.thumb_func
_08064F34:
	.4byte gData_080B738E
	.4byte gRom_08096A80
	.incbin "baserom.gba", 0x64F3C, 0x8
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_080978CC
	.4byte gRom_080978E0
	.4byte gRom_080BA284
	.incbin "baserom.gba", 0x64F58, 0x38
	.4byte gRom_080BA648
	.incbin "baserom.gba", 0x64F94, 0x128
	.4byte gRom_082AFF2C
	.4byte gRom_082AB6B0
	.4byte gRom_082AFCB0
	.incbin "baserom.gba", 0x650C8, 0x4
	.global _080650CC
	.thumb_func
_080650CC:
	.incbin "baserom.gba", 0x650CC, 0x98
	.4byte gRom_080BA284
	.incbin "baserom.gba", 0x65168, 0xC0
	.global _08065228
	.thumb_func
_08065228:
	.incbin "baserom.gba", 0x65228, 0x120
	.global _08065348
	.thumb_func
_08065348:
	.incbin "baserom.gba", 0x65348, 0x68
	.4byte gRom_080BA284
	.incbin "baserom.gba", 0x653B4, 0x90
	.global _08065444
	.thumb_func
_08065444:
	.incbin "baserom.gba", 0x65444, 0x74
	.global _080654B8
	.thumb_func
_080654B8:
	.incbin "baserom.gba", 0x654B8, 0x98
	.4byte gRom_080B8FF4
	.incbin "baserom.gba", 0x65554, 0xC
