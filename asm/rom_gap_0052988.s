@ Unmatched ROM 0x08052988..0x08052F0B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0052988
gRomGap0052988:
	.global _08052988
	.thumb_func
_08052988:
	.incbin "baserom.gba", 0x52988, 0x24
	.global _080529AC
	.thumb_func
_080529AC:
	.incbin "baserom.gba", 0x529AC, 0x3C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x529F0, 0x8
	.4byte gRom_08097034
	.incbin "baserom.gba", 0x529FC, 0x20
	.4byte gRom_08097048
	.incbin "baserom.gba", 0x52A20, 0x4
	.global _08052A24
	.thumb_func
_08052A24:
	.incbin "baserom.gba", 0x52A24, 0x5C
	.global _08052A80
	.thumb_func
_08052A80:
	.incbin "baserom.gba", 0x52A80, 0x5C
	.global _08052ADC
	.thumb_func
_08052ADC:
	.incbin "baserom.gba", 0x52ADC, 0x5C
	.global _08052B38
	.thumb_func
_08052B38:
	.incbin "baserom.gba", 0x52B38, 0x5C
	.global _08052B94
	.thumb_func
_08052B94:
	.incbin "baserom.gba", 0x52B94, 0x70
	.global _08052C04
	.thumb_func
_08052C04:
	.incbin "baserom.gba", 0x52C04, 0x94
	.global _08052C98
	.thumb_func
_08052C98:
	.incbin "baserom.gba", 0x52C98, 0x7C
	.4byte gRom_08052D18
	.global gRom_08052D18
gRom_08052D18:
	.4byte gRom_08052D2C
	.4byte gRom_08052D84
	.4byte gRom_08052D94
	.4byte gRom_08052DAC
	.incbin "baserom.gba", 0x52D28, 0x4
	.global gRom_08052D2C
gRom_08052D2C:
	.incbin "baserom.gba", 0x52D2C, 0x58
	.global gRom_08052D84
gRom_08052D84:
	.incbin "baserom.gba", 0x52D84, 0xC
	.4byte gRom_08099634
	.global gRom_08052D94
gRom_08052D94:
	.incbin "baserom.gba", 0x52D94, 0x18
	.global gRom_08052DAC
gRom_08052DAC:
	.incbin "baserom.gba", 0x52DAC, 0x3C
	.global _08052DE8
	.thumb_func
_08052DE8:
	.incbin "baserom.gba", 0x52DE8, 0x54
	.global _08052E3C
	.thumb_func
_08052E3C:
	.incbin "baserom.gba", 0x52E3C, 0x54
	.global _08052E90
	.thumb_func
_08052E90:
	.incbin "baserom.gba", 0x52E90, 0x38
	.global _08052EC8
	.thumb_func
_08052EC8:
	.incbin "baserom.gba", 0x52EC8, 0x44
