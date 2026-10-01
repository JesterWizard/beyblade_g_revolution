@ Unmatched ROM 0x08054DA8..0x080553B7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0054DA8
gRomGap0054DA8:
	.incbin "baserom.gba", 0x54DA8, 0xC
	.global _08054DB4
	.thumb_func
_08054DB4:
	.incbin "baserom.gba", 0x54DB4, 0x164
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x54F2C, 0x4
	.global _08054F30
	.thumb_func
_08054F30:
	.incbin "baserom.gba", 0x54F30, 0xD0
	.global _08055000
	.thumb_func
_08055000:
	.incbin "baserom.gba", 0x55000, 0x70
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x55074, 0xC0
	.global _08055134
	.thumb_func
_08055134:
	.incbin "baserom.gba", 0x55134, 0x38
	.global _0805516C
	.thumb_func
_0805516C:
	.incbin "baserom.gba", 0x5516C, 0x44
	.global _080551B0
	.thumb_func
_080551B0:
	.incbin "baserom.gba", 0x551B0, 0x2C
	.global _080551DC
	.thumb_func
_080551DC:
	.incbin "baserom.gba", 0x551DC, 0x1A8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8864
	.4byte gRom_083A8878
	.4byte gRom_083A888C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08097480
	.incbin "baserom.gba", 0x553A4, 0x8
	.4byte gRom_08097494
	.4byte gRom_080974A8
	.4byte gRom_080974BC
