@ Unmatched ROM 0x08072FA8..0x08073077
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0072FA8
gRomGap0072FA8:
	.incbin "baserom.gba", 0x72FA8, 0x48
	.4byte gRom_083D2628
	.incbin "baserom.gba", 0x72FF4, 0x2C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x73024, 0x18
	.4byte gRom_083D2660
	.incbin "baserom.gba", 0x73040, 0x38
