@ Unmatched ROM 0x0804EEA4..0x0804FFCB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004EEA4
gRomGap004EEA4:
	.global _0804EEA4
	.thumb_func
_0804EEA4:
	.incbin "baserom.gba", 0x4EEA4, 0x38
	.global _0804EEDC
	.thumb_func
_0804EEDC:
	.incbin "baserom.gba", 0x4EEDC, 0x7C
	.4byte gRom_0804EF5C
	.global gRom_0804EF5C
gRom_0804EF5C:
	.4byte gRom_0804EFAC
	.4byte gRom_0804EF70
	.4byte gRom_0804F018
	.4byte gRom_0804F084
	.4byte gRom_0804F14C
	.global gRom_0804EF70
gRom_0804EF70:
	.incbin "baserom.gba", 0x4EF70, 0x3C
	.global gRom_0804EFAC
gRom_0804EFAC:
	.incbin "baserom.gba", 0x4EFAC, 0x6C
	.global gRom_0804F018
gRom_0804F018:
	.incbin "baserom.gba", 0x4F018, 0x6C
	.global gRom_0804F084
gRom_0804F084:
	.incbin "baserom.gba", 0x4F084, 0xC8
	.global gRom_0804F14C
gRom_0804F14C:
	.incbin "baserom.gba", 0x4F14C, 0x1AC
	.global gRom_0804F2F8
gRom_0804F2F8:
	.incbin "baserom.gba", 0x4F2F8, 0x148
	.4byte gRom_081146E4
	.4byte gRom_08114950
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8498
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.incbin "baserom.gba", 0x4F45C, 0x10
	.4byte gData_080976EC
	.incbin "baserom.gba", 0x4F470, 0xC
	.4byte gData_08097700
	.incbin "baserom.gba", 0x4F480, 0x24
	.4byte gData_08097714
	.incbin "baserom.gba", 0x4F4A8, 0x34
	.4byte gData_08097728
	.incbin "baserom.gba", 0x4F4E0, 0x50
	.4byte gRom_0804F534
	.global gRom_0804F534
gRom_0804F534:
	.incbin "baserom.gba", 0x4F534, 0x4
	.4byte gRom_0804F548
	.incbin "baserom.gba", 0x4F53C, 0x4
	.4byte gRom_0804F56C
	.4byte gRom_0804F57C
	.global gRom_0804F548
gRom_0804F548:
	.incbin "baserom.gba", 0x4F548, 0x24
	.global gRom_0804F56C
gRom_0804F56C:
	.incbin "baserom.gba", 0x4F56C, 0x10
	.global gRom_0804F57C
gRom_0804F57C:
	.incbin "baserom.gba", 0x4F57C, 0x50
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A84A4
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.global _0804F5E0
	.thumb_func
_0804F5E0:
	.incbin "baserom.gba", 0x4F5E0, 0x128
	.global _0804F708
	.thumb_func
_0804F708:
	.incbin "baserom.gba", 0x4F708, 0x1A8
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_080969A4
	.incbin "baserom.gba", 0x4F8BC, 0x8
	.4byte gRom_082FA21C
	.4byte gRom_082FA8AC
	.4byte gRom_082F9FE8
	.4byte gRom_082FAA18
	.4byte gRom_082FA388
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x4F8E0, 0x4
	.4byte gRom_082C5960
	.incbin "baserom.gba", 0x4F8E8, 0x4
	.4byte gRom_0811A764
	.global _0804F8F0
	.thumb_func
_0804F8F0:
	.incbin "baserom.gba", 0x4F8F0, 0x48
	.global _0804F938
	.thumb_func
_0804F938:
	.incbin "baserom.gba", 0x4F938, 0x8C
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x4F9C8, 0xE0
	.global _0804FAA8
	.thumb_func
_0804FAA8:
	.incbin "baserom.gba", 0x4FAA8, 0x16C
	.4byte gRom_0804FC18
	.global gRom_0804FC18
gRom_0804FC18:
	.4byte gRom_0804FC2C
	.4byte gRom_0804FC40
	.4byte gRom_0804FC54
	.4byte gRom_0804FC7C
	.4byte gRom_0804FC68
	.global gRom_0804FC2C
gRom_0804FC2C:
	.incbin "baserom.gba", 0x4FC2C, 0x14
	.global gRom_0804FC40
gRom_0804FC40:
	.incbin "baserom.gba", 0x4FC40, 0x14
	.global gRom_0804FC54
gRom_0804FC54:
	.incbin "baserom.gba", 0x4FC54, 0x14
	.global gRom_0804FC68
gRom_0804FC68:
	.incbin "baserom.gba", 0x4FC68, 0x14
	.global gRom_0804FC7C
gRom_0804FC7C:
	.incbin "baserom.gba", 0x4FC7C, 0x2C
	.global _0804FCA8
	.thumb_func
_0804FCA8:
	.incbin "baserom.gba", 0x4FCA8, 0x1B4
	.global gRom_0804FE5C
gRom_0804FE5C:
	.incbin "baserom.gba", 0x4FE5C, 0xA0
	.global _0804FEFC
	.thumb_func
_0804FEFC:
	.incbin "baserom.gba", 0x4FEFC, 0x74
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A84B4
	.4byte gRom_083A84D0
	.4byte gRom_083A84EC
	.4byte gRom_083A8508
	.4byte gRom_083A8520
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.4byte gRom_08096F08
	.incbin "baserom.gba", 0x4FF98, 0x8
	.4byte gRom_080975FC
	.4byte gRom_0809773C
	.4byte gRom_08097750
	.4byte gRom_08097764
	.4byte gRom_08097778
	.incbin "baserom.gba", 0x4FFB4, 0x18
