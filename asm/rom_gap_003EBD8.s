@ Unmatched ROM 0x0803EBD8..0x0803EC33
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003EBD8
gRomGap003EBD8:
	.incbin "baserom.gba", 0x3EBD8, 0x20
	.4byte gData_0807B6F0
	.4byte gRom_0803EC00
	.global gRom_0803EC00
gRom_0803EC00:
	.4byte gRom_0803EC24
	.4byte gRom_0803EC24
	.4byte gRom_0803EC24
	.4byte gRom_0803EC28
	.4byte gRom_0803EC28
	.4byte gRom_0803EC28
	.4byte gRom_0803EC2C
	.4byte gRom_0803EC2C
	.4byte gRom_0803EC2C
	.global gRom_0803EC24
gRom_0803EC24:
	.incbin "baserom.gba", 0x3EC24, 0x4
	.global gRom_0803EC28
gRom_0803EC28:
	.incbin "baserom.gba", 0x3EC28, 0x4
	.global gRom_0803EC2C
gRom_0803EC2C:
	.incbin "baserom.gba", 0x3EC2C, 0x8
