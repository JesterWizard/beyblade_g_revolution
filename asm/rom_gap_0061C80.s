@ Unmatched ROM 0x08061C80..0x08061CFF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0061C80
gRomGap0061C80:
	.incbin "baserom.gba", 0x61C80, 0x7C
	.4byte gData_080BB8C0
