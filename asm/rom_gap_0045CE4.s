@ Unmatched ROM 0x08045CE4..0x08045D3B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0045CE4
gRomGap0045CE4:
	.incbin "baserom.gba", 0x45CE4, 0x54
	.4byte gRom_083A5E38
