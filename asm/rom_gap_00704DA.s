@ Unmatched ROM 0x080704DA..0x080705A3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00704DA
gRomGap00704DA:
	.incbin "baserom.gba", 0x704DA, 0x2A
	.global gRom_08070504
gRom_08070504:
	.incbin "baserom.gba", 0x70504, 0x7C
	.4byte gRom_080BB858
	.incbin "baserom.gba", 0x70584, 0x1C
	.4byte gRom_080BB858
