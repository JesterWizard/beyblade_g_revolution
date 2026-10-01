@ Unmatched ROM 0x08065E68..0x08066223
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0065E68
gRomGap0065E68:
	.incbin "baserom.gba", 0x65E68, 0x12C
	.4byte gRom_083A8E30
	.incbin "baserom.gba", 0x65F98, 0x4
	.4byte gData_083C9544
	.incbin "baserom.gba", 0x65FA0, 0x178
	.4byte gData_083C9544
	.incbin "baserom.gba", 0x6611C, 0x108
