@ Unmatched ROM 0x0803737C..0x0803742F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003737C
gRomGap003737C:
	.incbin "baserom.gba", 0x3737C, 0x90
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_08096F94
	.incbin "baserom.gba", 0x37418, 0x18
