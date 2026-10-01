@ Unmatched ROM 0x08030388..0x08030637
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0030388
gRomGap0030388:
	.incbin "baserom.gba", 0x30388, 0x88
	.4byte gRom_0833C230
	.incbin "baserom.gba", 0x30414, 0x70
	.4byte gRom_0833C244
	.4byte gRom_0833C274
	.incbin "baserom.gba", 0x3048C, 0x50
	.4byte gRom_0833C288
	.incbin "baserom.gba", 0x304E0, 0x84
	.4byte gRom_0833C298
	.4byte gRom_08078618
	.incbin "baserom.gba", 0x3056C, 0x44
	.4byte gRom_080786B8
	.4byte gRom_0833C2AC
	.incbin "baserom.gba", 0x305B8, 0x58
	.4byte gRom_0833C2C4
	.4byte gRom_08078788
	.incbin "baserom.gba", 0x30618, 0x20
