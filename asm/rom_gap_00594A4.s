@ Unmatched ROM 0x080594A4..0x08059ADF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00594A4
gRomGap00594A4:
	.incbin "baserom.gba", 0x594A4, 0xA4
	.4byte gRom_0805954C
	.global gRom_0805954C
gRom_0805954C:
	.4byte gRom_08059568
	.4byte gRom_080595C0
	.4byte gRom_08059604
	.4byte gRom_08059628
	.4byte gRom_08059648
	.4byte gRom_08059664
	.4byte gRom_08059678
	.global gRom_08059568
gRom_08059568:
	.incbin "baserom.gba", 0x59568, 0x4C
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x595B8, 0x8
	.global gRom_080595C0
gRom_080595C0:
	.incbin "baserom.gba", 0x595C0, 0x44
	.global gRom_08059604
gRom_08059604:
	.incbin "baserom.gba", 0x59604, 0x24
	.global gRom_08059628
gRom_08059628:
	.incbin "baserom.gba", 0x59628, 0x20
	.global gRom_08059648
gRom_08059648:
	.incbin "baserom.gba", 0x59648, 0x1C
	.global gRom_08059664
gRom_08059664:
	.incbin "baserom.gba", 0x59664, 0x14
	.global gRom_08059678
gRom_08059678:
	.incbin "baserom.gba", 0x59678, 0x64
	.4byte gRom_080596E0
	.global gRom_080596E0
gRom_080596E0:
	.4byte gRom_08059704
	.4byte gRom_080597B8
	.4byte gRom_08059840
	.incbin "baserom.gba", 0x596EC, 0x4
	.4byte gRom_080598E8
	.4byte gRom_08059918
	.incbin "baserom.gba", 0x596F8, 0x4
	.4byte gRom_080599B8
	.4byte gRom_08059A04
	.global gRom_08059704
gRom_08059704:
	.incbin "baserom.gba", 0x59704, 0x9C
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x597A4, 0x14
	.global gRom_080597B8
gRom_080597B8:
	.incbin "baserom.gba", 0x597B8, 0x88
	.global gRom_08059840
gRom_08059840:
	.incbin "baserom.gba", 0x59840, 0xA8
	.global gRom_080598E8
gRom_080598E8:
	.incbin "baserom.gba", 0x598E8, 0x30
	.global gRom_08059918
gRom_08059918:
	.incbin "baserom.gba", 0x59918, 0xA0
	.global gRom_080599B8
gRom_080599B8:
	.incbin "baserom.gba", 0x599B8, 0x4C
	.global gRom_08059A04
gRom_08059A04:
	.incbin "baserom.gba", 0x59A04, 0xD8
	.4byte gData_080BB8BC
