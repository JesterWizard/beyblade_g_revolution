@ Unmatched ROM 0x0806A970..0x0806AC67
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006A970
gRomGap006A970:
	.incbin "baserom.gba", 0x6A970, 0x178
	.4byte gRom_083D1C78
	.incbin "baserom.gba", 0x6AAEC, 0x100
	.4byte gRom_083D1CA8
	.4byte gRom_083D1CB0
	.incbin "baserom.gba", 0x6ABF4, 0x74
