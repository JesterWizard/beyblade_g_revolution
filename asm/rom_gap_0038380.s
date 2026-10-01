@ Unmatched ROM 0x08038380..0x08038437
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0038380
gRomGap0038380:
	.incbin "baserom.gba", 0x38380, 0x8C
	.4byte gRom_0833B768
	.incbin "baserom.gba", 0x38410, 0x28
