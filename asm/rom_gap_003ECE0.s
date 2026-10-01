@ Unmatched ROM 0x0803ECE0..0x0803EDC7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003ECE0
gRomGap003ECE0:
	.incbin "baserom.gba", 0x3ECE0, 0x20
	.4byte gData_0807BDB8
	.4byte gRom_0803ED08
	.global gRom_0803ED08
gRom_0803ED08:
	.4byte gRom_0803ED2C
	.4byte gRom_0803ED2C
	.4byte gRom_0803ED2C
	.4byte gRom_0803ED30
	.4byte gRom_0803ED30
	.4byte gRom_0803ED30
	.4byte gRom_0803ED34
	.4byte gRom_0803ED34
	.4byte gRom_0803ED34
	.global gRom_0803ED2C
gRom_0803ED2C:
	.incbin "baserom.gba", 0x3ED2C, 0x4
	.global gRom_0803ED30
gRom_0803ED30:
	.incbin "baserom.gba", 0x3ED30, 0x4
	.global gRom_0803ED34
gRom_0803ED34:
	.incbin "baserom.gba", 0x3ED34, 0x90
	.4byte gData_0807BE04
