@ Unmatched ROM 0x0806BC80..0x0806BDA7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006BC80
gRomGap006BC80:
	.incbin "baserom.gba", 0x6BC80, 0xFC
	.4byte gData_080BB8C0
	.4byte gData_083D1D3C
	.incbin "baserom.gba", 0x6BD84, 0x24
