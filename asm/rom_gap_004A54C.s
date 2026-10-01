@ Unmatched ROM 0x0804A54C..0x0804AAEF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004A54C
gRomGap004A54C:
	.global _0804A54C
	.thumb_func
_0804A54C:
	.incbin "baserom.gba", 0x4A54C, 0x120
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x4A670, 0xC
	.global _0804A67C
	.thumb_func
_0804A67C:
	.incbin "baserom.gba", 0x4A67C, 0xBC
	.global _0804A738
	.thumb_func
_0804A738:
	.incbin "baserom.gba", 0x4A738, 0x98
	.global _0804A7D0
	.thumb_func
_0804A7D0:
	.incbin "baserom.gba", 0x4A7D0, 0x4
	.global _0804A7D4
	.thumb_func
_0804A7D4:
	.incbin "baserom.gba", 0x4A7D4, 0x38
	.global _0804A80C
	.thumb_func
_0804A80C:
	.incbin "baserom.gba", 0x4A80C, 0x34
	.global _0804A840
	.thumb_func
_0804A840:
	.incbin "baserom.gba", 0x4A840, 0x34
	.global _0804A874
	.thumb_func
_0804A874:
	.incbin "baserom.gba", 0x4A874, 0x30
	.4byte gRom_08097FE4
	.incbin "baserom.gba", 0x4A8A8, 0x4
	.global _0804A8AC
	.thumb_func
_0804A8AC:
	.incbin "baserom.gba", 0x4A8AC, 0x30
	.4byte gRom_08097FE4
	.incbin "baserom.gba", 0x4A8E0, 0x1D4
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A741C
	.4byte gRom_083A7438
	.4byte gRom_083A7454
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.4byte gRom_083A7470
	.4byte gRom_083A747C
	.4byte gRom_083A7488
	.4byte gRom_083A7494
	.4byte gRom_083A74A4
	.4byte gRom_083A74B0
	.4byte gRom_083A74BC
	.4byte gRom_083A74C8
