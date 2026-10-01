@ Unmatched ROM 0x08038DD8..0x08038F2F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0038DD8
gRomGap0038DD8:
	.incbin "baserom.gba", 0x38DD8, 0x9C
	.4byte gRom_08079648
	.incbin "baserom.gba", 0x38E78, 0x4
	.4byte gRom_08079688
	.incbin "baserom.gba", 0x38E80, 0x1C
	.4byte gRom_08079658
	.incbin "baserom.gba", 0x38EA0, 0x4
	.4byte gRom_0807968C
	.incbin "baserom.gba", 0x38EA8, 0x1C
	.4byte gRom_08079668
	.incbin "baserom.gba", 0x38EC8, 0x4
	.4byte gRom_08079690
	.incbin "baserom.gba", 0x38ED0, 0x44
	.4byte gRom_08079678
	.incbin "baserom.gba", 0x38F18, 0x4
	.4byte gRom_08079694
	.incbin "baserom.gba", 0x38F20, 0x10
