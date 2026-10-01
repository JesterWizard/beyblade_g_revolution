@ Unmatched ROM 0x08043980..0x08043ADB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0043980
gRomGap0043980:
	.incbin "baserom.gba", 0x43980, 0x15C
