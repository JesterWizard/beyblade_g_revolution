@ Unmatched ROM 0x0804E59C..0x0804EBEF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004E59C
gRomGap004E59C:
	.global _0804E59C
	.thumb_func
_0804E59C:
	.incbin "baserom.gba", 0x4E59C, 0x44
	.global _0804E5E0
	.thumb_func
_0804E5E0:
	.incbin "baserom.gba", 0x4E5E0, 0x44
	.global _0804E624
	.thumb_func
_0804E624:
	.incbin "baserom.gba", 0x4E624, 0xF0
	.4byte gRom_0804E718
	.global gRom_0804E718
gRom_0804E718:
	.4byte gRom_0804E75C
	.4byte gRom_0804E73C
	.4byte gRom_0804E74C
	.4byte gRom_0804E72C
	.4byte gRom_0804E784
	.global gRom_0804E72C
gRom_0804E72C:
	.incbin "baserom.gba", 0x4E72C, 0xC
	.4byte gRom_082FA21C
	.global gRom_0804E73C
gRom_0804E73C:
	.incbin "baserom.gba", 0x4E73C, 0xC
	.4byte gRom_082FA8AC
	.global gRom_0804E74C
gRom_0804E74C:
	.incbin "baserom.gba", 0x4E74C, 0xC
	.4byte gRom_082F9FE8
	.global gRom_0804E75C
gRom_0804E75C:
	.incbin "baserom.gba", 0x4E75C, 0x24
	.4byte gRom_082FA388
	.global gRom_0804E784
gRom_0804E784:
	.incbin "baserom.gba", 0x4E784, 0x3C
	.4byte gRom_082FAA18
	.global _0804E7C4
	.thumb_func
_0804E7C4:
	.incbin "baserom.gba", 0x4E7C4, 0x4
	.global _0804E7C8
	.thumb_func
_0804E7C8:
	.incbin "baserom.gba", 0x4E7C8, 0x2B8
	.4byte gRom_082FA21C
	.4byte gRom_082FA8AC
	.4byte gRom_082F9FE8
	.4byte gRom_082FAA18
	.4byte gRom_082FA388
	.incbin "baserom.gba", 0x4EA94, 0x4
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8434
	.incbin "baserom.gba", 0x4EAA4, 0x12C
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8448
	.4byte gRom_083A845C
	.4byte gRom_083A8470
	.4byte gRom_083A8484
	.4byte gRom_082C44A8
	.4byte gData_080B7258
