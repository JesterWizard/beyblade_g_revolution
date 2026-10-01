@ Unmatched ROM 0x08030986..0x08030D4B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0030986
gRomGap0030986:
	.incbin "baserom.gba", 0x30986, 0x35E
	.4byte gRom_080D7D40
	.incbin "baserom.gba", 0x30CE8, 0x2C
	.4byte gRom_080F27D4
	.incbin "baserom.gba", 0x30D18, 0x4
	.4byte gRom_080F2864
	.incbin "baserom.gba", 0x30D20, 0x4
	.4byte gRom_080F3C9C
	.incbin "baserom.gba", 0x30D28, 0x4
	.4byte gRom_083184A8
	.incbin "baserom.gba", 0x30D30, 0x14
	.4byte gRom_0833C318
	.4byte gRom_0833C320
