@ Unmatched ROM 0x080505AC..0x080507B7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00505AC
gRomGap00505AC:
	.incbin "baserom.gba", 0x505AC, 0x20C
