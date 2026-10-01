@ Unmatched ROM 0x08061338..0x08061563
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0061338
gRomGap0061338:
	.incbin "baserom.gba", 0x61338, 0x224
	.4byte gData_080BB748
	.incbin "baserom.gba", 0x61560, 0x4
