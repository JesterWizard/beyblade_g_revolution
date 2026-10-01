@ Unmatched ROM 0x0804AFC0..0x0804B40B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004AFC0
gRomGap004AFC0:
	.global _0804AFC0
	.thumb_func
_0804AFC0:
	.incbin "baserom.gba", 0x4AFC0, 0x68
	.global _0804B028
	.thumb_func
_0804B028:
	.incbin "baserom.gba", 0x4B028, 0xB0
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x4B0DC, 0x4
	.global _0804B0E0
	.thumb_func
_0804B0E0:
	.incbin "baserom.gba", 0x4B0E0, 0x48
	.global _0804B128
	.thumb_func
_0804B128:
	.incbin "baserom.gba", 0x4B128, 0x84
	.4byte gRom_0804B1B0
	.global gRom_0804B1B0
gRom_0804B1B0:
	.4byte gRom_0804B1C8
	.4byte gRom_0804B1CC
	.4byte gRom_0804B1D0
	.4byte gRom_0804B1D4
	.4byte gRom_0804B1D8
	.4byte gRom_0804B1EC
	.global gRom_0804B1C8
gRom_0804B1C8:
	.incbin "baserom.gba", 0x4B1C8, 0x4
	.global gRom_0804B1CC
gRom_0804B1CC:
	.incbin "baserom.gba", 0x4B1CC, 0x4
	.global gRom_0804B1D0
gRom_0804B1D0:
	.incbin "baserom.gba", 0x4B1D0, 0x4
	.global gRom_0804B1D4
gRom_0804B1D4:
	.incbin "baserom.gba", 0x4B1D4, 0x4
	.global gRom_0804B1D8
gRom_0804B1D8:
	.incbin "baserom.gba", 0x4B1D8, 0x14
	.global gRom_0804B1EC
gRom_0804B1EC:
	.incbin "baserom.gba", 0x4B1EC, 0x40
	.global _0804B22C
	.thumb_func
_0804B22C:
	.incbin "baserom.gba", 0x4B22C, 0x58
	.global _0804B284
	.thumb_func
_0804B284:
	.incbin "baserom.gba", 0x4B284, 0x44
	.global _0804B2C8
	.thumb_func
_0804B2C8:
	.incbin "baserom.gba", 0x4B2C8, 0x34
	.global _0804B2FC
	.thumb_func
_0804B2FC:
	.incbin "baserom.gba", 0x4B2FC, 0xE8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7524
	.4byte gRom_083A753C
	.4byte gRom_083A754C
	.4byte gRom_083A755C
	.4byte gRom_083A7568
	.4byte gRom_083A7578
	.4byte gRom_083A7584
	.4byte gRom_083A7590
