@ Unmatched ROM 0x080471E4..0x0804737B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00471E4
gRomGap00471E4:
	.incbin "baserom.gba", 0x471E4, 0xDC
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x472C4, 0x24
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x472EC, 0x90
