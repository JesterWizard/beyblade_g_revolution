@ Unmatched ROM 0x08030744..0x08030937
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0030744
gRomGap0030744:
	.incbin "baserom.gba", 0x30744, 0x7C
	.4byte gRom_0833C2DC
	.incbin "baserom.gba", 0x307C4, 0x5C
	.4byte gRom_08078A38
	.incbin "baserom.gba", 0x30824, 0x2C
	.4byte gRom_08078AA8
	.incbin "baserom.gba", 0x30854, 0x34
	.global gRom_08030888
gRom_08030888:
	.incbin "baserom.gba", 0x30888, 0x10
	.4byte gRom_08078B18
	.incbin "baserom.gba", 0x3089C, 0x24
	.4byte gRom_0833C2F0
	.incbin "baserom.gba", 0x308C4, 0x60
	.4byte gRom_0833C304
	.incbin "baserom.gba", 0x30928, 0x10
