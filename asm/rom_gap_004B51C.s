@ Unmatched ROM 0x0804B51C..0x0804BD37
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004B51C
gRomGap004B51C:
	.incbin "baserom.gba", 0x4B51C, 0x84
	.4byte gRom_083A75C0
	.4byte gRom_083A75C8
	.incbin "baserom.gba", 0x4B5A8, 0x4
	.4byte gRom_0804B5B0
	.global gRom_0804B5B0
gRom_0804B5B0:
	.4byte gRom_0804B5C8
	.4byte gRom_0804B628
	.4byte gRom_0804B5F8
	.4byte gRom_0804B688
	.4byte gRom_0804B658
	.4byte gRom_0804B6C0
	.global gRom_0804B5C8
gRom_0804B5C8:
	.incbin "baserom.gba", 0x4B5C8, 0x24
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B5F0, 0x8
	.global gRom_0804B5F8
gRom_0804B5F8:
	.incbin "baserom.gba", 0x4B5F8, 0x24
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B620, 0x8
	.global gRom_0804B628
gRom_0804B628:
	.incbin "baserom.gba", 0x4B628, 0x24
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B650, 0x8
	.global gRom_0804B658
gRom_0804B658:
	.incbin "baserom.gba", 0x4B658, 0x24
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B680, 0x8
	.global gRom_0804B688
gRom_0804B688:
	.incbin "baserom.gba", 0x4B688, 0x2C
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B6B8, 0x8
	.global gRom_0804B6C0
gRom_0804B6C0:
	.incbin "baserom.gba", 0x4B6C0, 0x30
	.4byte gRom_083A75CC
	.incbin "baserom.gba", 0x4B6F4, 0x20
	.4byte gRom_083A75D0
	.global _0804B718
	.thumb_func
_0804B718:
	.incbin "baserom.gba", 0x4B718, 0x34
	.global _0804B74C
	.thumb_func
_0804B74C:
	.incbin "baserom.gba", 0x4B74C, 0xB8
	.4byte gData_080BB8BC
	.global _0804B808
	.thumb_func
_0804B808:
	.incbin "baserom.gba", 0x4B808, 0xC4
	.4byte gRom_08098000
	.incbin "baserom.gba", 0x4B8D0, 0x1C
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _0804B8F4
	.thumb_func
_0804B8F4:
	.incbin "baserom.gba", 0x4B8F4, 0x70
	.global _0804B964
	.thumb_func
_0804B964:
	.incbin "baserom.gba", 0x4B964, 0x114
	.global _0804BA78
	.thumb_func
_0804BA78:
	.incbin "baserom.gba", 0x4BA78, 0x90
	.4byte gRom_083A7D40
	.4byte gRom_08098000
	.incbin "baserom.gba", 0x4BB10, 0xC
	.global _0804BB1C
	.thumb_func
_0804BB1C:
	.incbin "baserom.gba", 0x4BB1C, 0x38
	.global _0804BB54
	.thumb_func
_0804BB54:
	.incbin "baserom.gba", 0x4BB54, 0x4C
	.global _0804BBA0
	.thumb_func
_0804BBA0:
	.incbin "baserom.gba", 0x4BBA0, 0x17C
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7D58
	.4byte gRom_083A7D74
	.4byte gRom_083A7D90
	.4byte gData_082BCD00
	.4byte gData_080B738E
