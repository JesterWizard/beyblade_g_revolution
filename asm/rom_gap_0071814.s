@ Unmatched ROM 0x08071814..0x08071B4B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0071814
gRomGap0071814:
	.incbin "baserom.gba", 0x71814, 0xF0
	.4byte gRom_083D230C
	.incbin "baserom.gba", 0x71908, 0x18C
	.4byte gRom_083D250C
	.incbin "baserom.gba", 0x71A98, 0x8
	.4byte gRom_083D2540
	.incbin "baserom.gba", 0x71AA4, 0x14
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x71ABC, 0x90
