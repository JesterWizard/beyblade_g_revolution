@ Unmatched ROM 0x08042C74..0x08042E77
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0042C74
gRomGap0042C74:
	.incbin "baserom.gba", 0x42C74, 0x84
	.4byte gRom_080911CC
	.4byte gRom_08042D00
	.global gRom_08042D00
gRom_08042D00:
	.4byte gRom_08042D20
	.4byte gRom_08042D14
	.4byte gRom_08042D18
	.4byte gRom_08042D1C
	.4byte gRom_08042D20
	.global gRom_08042D14
gRom_08042D14:
	.incbin "baserom.gba", 0x42D14, 0x4
	.global gRom_08042D18
gRom_08042D18:
	.incbin "baserom.gba", 0x42D18, 0x4
	.global gRom_08042D1C
gRom_08042D1C:
	.incbin "baserom.gba", 0x42D1C, 0x4
	.global gRom_08042D20
gRom_08042D20:
	.incbin "baserom.gba", 0x42D20, 0x130
	.4byte gRom_080909C4
	.incbin "baserom.gba", 0x42E54, 0x24
