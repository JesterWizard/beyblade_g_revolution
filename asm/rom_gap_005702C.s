@ Unmatched ROM 0x0805702C..0x08057233
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap005702C
gRomGap005702C:
	.incbin "baserom.gba", 0x5702C, 0x18
	.4byte _08057050 + 1
	.4byte _080570F8 + 1
	.4byte _08057208 + 1
	.global _08057050
	.thumb_func
_08057050:
	.incbin "baserom.gba", 0x57050, 0xA8
	.global _080570F8
	.thumb_func
_080570F8:
	.incbin "baserom.gba", 0x570F8, 0x34
	.4byte gRom_08057130
	.global gRom_08057130
gRom_08057130:
	.4byte gRom_08057150
	.incbin "baserom.gba", 0x57134, 0x4
	.4byte gRom_080571FC
	.4byte gRom_080571FC
	.incbin "baserom.gba", 0x57140, 0x4
	.4byte gRom_080571A4
	.4byte gRom_080571FC
	.4byte gRom_080571E8
	.global gRom_08057150
gRom_08057150:
	.incbin "baserom.gba", 0x57150, 0x54
	.global gRom_080571A4
gRom_080571A4:
	.incbin "baserom.gba", 0x571A4, 0x44
	.global gRom_080571E8
gRom_080571E8:
	.incbin "baserom.gba", 0x571E8, 0x14
	.global gRom_080571FC
gRom_080571FC:
	.incbin "baserom.gba", 0x571FC, 0xC
	.global _08057208
	.thumb_func
_08057208:
	.incbin "baserom.gba", 0x57208, 0x2C
