@ Unmatched ROM 0x08072118..0x080726A3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0072118
gRomGap0072118:
	.incbin "baserom.gba", 0x72118, 0x58
	.4byte gRom_08072174
	.global gRom_08072174
gRom_08072174:
	.4byte gRom_0807218C
	.4byte gRom_080721D4
	.4byte gRom_08072334
	.incbin "baserom.gba", 0x72180, 0x4
	.4byte gRom_080722E8
	.4byte gRom_08072318
	.global gRom_0807218C
gRom_0807218C:
	.incbin "baserom.gba", 0x7218C, 0x48
	.global gRom_080721D4
gRom_080721D4:
	.incbin "baserom.gba", 0x721D4, 0x114
	.global gRom_080722E8
gRom_080722E8:
	.incbin "baserom.gba", 0x722E8, 0x30
	.global gRom_08072318
gRom_08072318:
	.incbin "baserom.gba", 0x72318, 0x1C
	.global gRom_08072334
gRom_08072334:
	.incbin "baserom.gba", 0x72334, 0x370
