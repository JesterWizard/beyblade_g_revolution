@ Unmatched ROM 0x080663B8..0x08066433
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00663B8
gRomGap00663B8:
	.incbin "baserom.gba", 0x663B8, 0xC
	.4byte gRom_080BA1A8
	.incbin "baserom.gba", 0x663C8, 0x34
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x66400, 0x34
