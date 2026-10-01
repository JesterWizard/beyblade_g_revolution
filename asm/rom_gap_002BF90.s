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
	.incbin "baserom.gba", 0x2C070, 0x38
	.global gRom_0802C0A8
gRom_0802C0A8:
	.incbin "baserom.gba", 0x2C0A8, 0x4C
	.4byte gData_08075AB8
	.global gRom_0802C0F8
gRom_0802C0F8:
	.incbin "baserom.gba", 0x2C0F8, 0x34
	.global gRom_0802C12C
gRom_0802C12C:
	.incbin "baserom.gba", 0x2C12C, 0x34
	.global gRom_0802C160
gRom_0802C160:
	.incbin "baserom.gba", 0x2C160, 0x34
	.global gRom_0802C194
gRom_0802C194:
	.incbin "baserom.gba", 0x2C194, 0x34
	.global gRom_0802C1C8
gRom_0802C1C8:
	.incbin "baserom.gba", 0x2C1C8, 0x34
	.global gRom_0802C1FC
gRom_0802C1FC:
	.incbin "baserom.gba", 0x2C1FC, 0x34
	.global gRom_0802C230
gRom_0802C230:
	.incbin "baserom.gba", 0x2C230, 0x80
