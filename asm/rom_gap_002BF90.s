@ Unmatched ROM 0x0802BF90..0x0802C2AF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002BF90
gRomGap002BF90:
	.incbin "baserom.gba", 0x2BF90, 0xB8
	.4byte gRom_0802C04C
	.global gRom_0802C04C
gRom_0802C04C:
	.4byte gRom_0802C0A8
	.4byte gRom_0802C070
	.4byte gRom_0802C0F8
	.4byte gRom_0802C12C
	.4byte gRom_0802C160
	.4byte gRom_0802C194
	.4byte gRom_0802C1C8
	.4byte gRom_0802C1FC
	.4byte gRom_0802C230
	.global gRom_0802C070
gRom_0802C070:
	.incbin "baserom.gba", 0x2C070, 0x34
	.4byte gRom_082F9D90
	.global gRom_0802C0A8
gRom_0802C0A8:
	.incbin "baserom.gba", 0x2C0A8, 0x4C
	.4byte gData_08075AB8
	.global gRom_0802C0F8
gRom_0802C0F8:
	.incbin "baserom.gba", 0x2C0F8, 0x24
	.4byte gRom_08096DF0
	.incbin "baserom.gba", 0x2C120, 0x8
	.4byte gRom_082F9B38
	.global gRom_0802C12C
gRom_0802C12C:
	.incbin "baserom.gba", 0x2C12C, 0x24
	.4byte gRom_08096E04
	.incbin "baserom.gba", 0x2C154, 0x8
	.4byte gRom_082F9A68
	.global gRom_0802C160
gRom_0802C160:
	.incbin "baserom.gba", 0x2C160, 0x24
	.4byte gRom_08096CB0
	.incbin "baserom.gba", 0x2C188, 0x8
	.4byte gRom_082FA388
	.global gRom_0802C194
gRom_0802C194:
	.incbin "baserom.gba", 0x2C194, 0x24
	.4byte gRom_08096C38
	.incbin "baserom.gba", 0x2C1BC, 0x8
	.4byte gRom_082FA8AC
	.global gRom_0802C1C8
gRom_0802C1C8:
	.incbin "baserom.gba", 0x2C1C8, 0x24
	.4byte gRom_08096C9C
	.incbin "baserom.gba", 0x2C1F0, 0x8
	.4byte gRom_082F9FE8
	.global gRom_0802C1FC
gRom_0802C1FC:
	.incbin "baserom.gba", 0x2C1FC, 0x24
	.4byte gRom_08096EF4
	.incbin "baserom.gba", 0x2C224, 0x8
	.4byte gRom_082FA21C
	.global gRom_0802C230
gRom_0802C230:
	.incbin "baserom.gba", 0x2C230, 0x6C
	.4byte gRom_08096CC4
	.incbin "baserom.gba", 0x2C2A0, 0x8
	.4byte gRom_082FAA18
	.incbin "baserom.gba", 0x2C2AC, 0x4
