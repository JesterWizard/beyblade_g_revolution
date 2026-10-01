@ Unmatched ROM 0x080626DC..0x08062727
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00626DC
gRomGap00626DC:
	.incbin "baserom.gba", 0x626DC, 0x38
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x62718, 0x10
