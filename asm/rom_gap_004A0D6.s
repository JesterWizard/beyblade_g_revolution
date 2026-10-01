@ Unmatched ROM 0x0804A0D6..0x0804A437
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004A0D6
gRomGap004A0D6:
	.incbin "baserom.gba", 0x4A0D6, 0x2
	.global _0804A0D8
	.thumb_func
_0804A0D8:
	.incbin "baserom.gba", 0x4A0D8, 0x68
	.global _0804A140
	.thumb_func
_0804A140:
	.incbin "baserom.gba", 0x4A140, 0x48
	.global _0804A188
	.thumb_func
_0804A188:
	.incbin "baserom.gba", 0x4A188, 0x74
	.4byte gRom_0804A200
	.global gRom_0804A200
gRom_0804A200:
	.4byte gRom_0804A21C
	.4byte gRom_0804A220
	.4byte gRom_0804A224
	.4byte gRom_0804A228
	.4byte gRom_0804A22C
	.4byte gRom_0804A230
	.4byte gRom_0804A244
	.global gRom_0804A21C
gRom_0804A21C:
	.incbin "baserom.gba", 0x4A21C, 0x4
	.global gRom_0804A220
gRom_0804A220:
	.incbin "baserom.gba", 0x4A220, 0x4
	.global gRom_0804A224
gRom_0804A224:
	.incbin "baserom.gba", 0x4A224, 0x4
	.global gRom_0804A228
gRom_0804A228:
	.incbin "baserom.gba", 0x4A228, 0x4
	.global gRom_0804A22C
gRom_0804A22C:
	.incbin "baserom.gba", 0x4A22C, 0x4
	.global gRom_0804A230
gRom_0804A230:
	.incbin "baserom.gba", 0x4A230, 0x14
	.global gRom_0804A244
gRom_0804A244:
	.incbin "baserom.gba", 0x4A244, 0x28
	.global _0804A26C
	.thumb_func
_0804A26C:
	.incbin "baserom.gba", 0x4A26C, 0x38
	.global _0804A2A4
	.thumb_func
_0804A2A4:
	.incbin "baserom.gba", 0x4A2A4, 0x44
	.global _0804A2E8
	.thumb_func
_0804A2E8:
	.incbin "baserom.gba", 0x4A2E8, 0x34
	.global _0804A31C
	.thumb_func
_0804A31C:
	.incbin "baserom.gba", 0x4A31C, 0xF4
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A736C
	.4byte gRom_083A7384
	.4byte gRom_083A7394
	.4byte gRom_083A73A8
	.4byte gRom_083A73B8
	.4byte gRom_083A73C8
	.4byte gRom_083A73DC
	.4byte gRom_083A73EC
