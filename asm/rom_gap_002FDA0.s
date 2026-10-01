@ Unmatched ROM 0x0802FDA0..0x0803019B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002FDA0
gRomGap002FDA0:
	.incbin "baserom.gba", 0x2FDA0, 0xBC
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2FE60, 0xD4
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2FF38, 0x5C
	.4byte gRom_0833C18C
	.4byte gRom_0833C194
	.4byte gRom_0833C1A4
	.4byte gRom_08077F44
	.4byte gRom_0833C1BC
	.4byte gRom_08077F24
	.incbin "baserom.gba", 0x2FFAC, 0xEC
	.4byte gRom_0833C1D8
	.4byte gRom_0833C1F4
	.4byte gRom_0833C220
	.incbin "baserom.gba", 0x300A4, 0x50
	.4byte gRom_080300F8
	.global gRom_080300F8
gRom_080300F8:
	.incbin "baserom.gba", 0x300F8, 0x4
	.4byte gRom_08030168
	.incbin "baserom.gba", 0x30100, 0x4
	.4byte gRom_08030124
	.incbin "baserom.gba", 0x30108, 0x4
	.4byte gRom_08030114
	.incbin "baserom.gba", 0x30110, 0x4
	.global gRom_08030114
gRom_08030114:
	.incbin "baserom.gba", 0x30114, 0x10
	.global gRom_08030124
gRom_08030124:
	.incbin "baserom.gba", 0x30124, 0x44
	.global gRom_08030168
gRom_08030168:
	.incbin "baserom.gba", 0x30168, 0x34
