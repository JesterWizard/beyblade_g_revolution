@ Unmatched ROM 0x08046356..0x08046E7B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0046356
gRomGap0046356:
	.incbin "baserom.gba", 0x46356, 0x306
	.4byte gRom_08315B88
	.4byte gData_080BB8C0
	.4byte gRom_083006E0
	.incbin "baserom.gba", 0x46668, 0x10
	.4byte gData_08091208
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x46684, 0xA0
	.4byte gRom_08046728
	.global gRom_08046728
gRom_08046728:
	.4byte gRom_08046750
	.4byte gRom_0804676C
	.incbin "baserom.gba", 0x46730, 0x4
	.4byte gRom_08046788
	.4byte gRom_0804677C
	.4byte gRom_08046788
	.4byte gRom_08046788
	.4byte gRom_08046788
	.4byte gRom_08046788
	.incbin "baserom.gba", 0x4674C, 0x4
	.global gRom_08046750
gRom_08046750:
	.incbin "baserom.gba", 0x46750, 0x1C
	.global gRom_0804676C
gRom_0804676C:
	.incbin "baserom.gba", 0x4676C, 0x10
	.global gRom_0804677C
gRom_0804677C:
	.incbin "baserom.gba", 0x4677C, 0xC
	.global gRom_08046788
gRom_08046788:
	.incbin "baserom.gba", 0x46788, 0x508
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x46C94, 0x1E8
