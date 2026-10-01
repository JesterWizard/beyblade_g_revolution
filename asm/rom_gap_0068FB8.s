@ Unmatched ROM 0x08068FB8..0x080691E3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0068FB8
gRomGap0068FB8:
	.incbin "baserom.gba", 0x68FB8, 0x34
	.4byte gRom_083A9508
	.incbin "baserom.gba", 0x68FF0, 0x1A0
	.4byte gData_080BB8A4
	.incbin "baserom.gba", 0x69194, 0x50
