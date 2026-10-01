@ Unmatched ROM 0x0802D9A8..0x0802DCDB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002D9A8
gRomGap002D9A8:
	.global _0802D9A8
	.thumb_func
_0802D9A8:
	.incbin "baserom.gba", 0x2D9A8, 0x30
	.4byte gRom_0802D9DC
	.global gRom_0802D9DC
gRom_0802D9DC:
	.4byte gRom_0802D9F0
	.4byte gRom_0802DBAC
	.4byte gRom_0802DBC4
	.4byte gRom_0802DBE4
	.4byte gRom_0802DC3C
	.global gRom_0802D9F0
gRom_0802D9F0:
	.incbin "baserom.gba", 0x2D9F0, 0x1B0
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x2DBA4, 0x8
	.global gRom_0802DBAC
gRom_0802DBAC:
	.incbin "baserom.gba", 0x2DBAC, 0x18
	.global gRom_0802DBC4
gRom_0802DBC4:
	.incbin "baserom.gba", 0x2DBC4, 0x20
	.global gRom_0802DBE4
gRom_0802DBE4:
	.incbin "baserom.gba", 0x2DBE4, 0x58
	.global gRom_0802DC3C
gRom_0802DC3C:
	.incbin "baserom.gba", 0x2DC3C, 0xA0
