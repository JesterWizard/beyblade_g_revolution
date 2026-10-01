@ Unmatched ROM 0x0803417C..0x0803435F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003417C
gRomGap003417C:
	.incbin "baserom.gba", 0x3417C, 0x100
	.4byte gRom_08078574
	.incbin "baserom.gba", 0x34280, 0x4
	.4byte gRom_08078584
	.incbin "baserom.gba", 0x34288, 0x38
	.4byte gRom_080785A0
	.4byte gRom_08078E58
	.incbin "baserom.gba", 0x342C8, 0x60
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x34330, 0x30
