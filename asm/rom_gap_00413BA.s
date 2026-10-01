@ Unmatched ROM 0x080413BA..0x080415FB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00413BA
gRomGap00413BA:
	.incbin "baserom.gba", 0x413BA, 0xD6
	.4byte gData_080908B4
	.incbin "baserom.gba", 0x41494, 0x6C
	.4byte gRom_083A2AA4
	.incbin "baserom.gba", 0x41504, 0x34
	.4byte gRom_083A2AD0
	.incbin "baserom.gba", 0x4153C, 0x8C
	.4byte gData_080BB8C0
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x415D0, 0x2C
