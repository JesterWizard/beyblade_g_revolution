@ Unmatched ROM 0x08043980..0x08043ADB
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0043980
gRomGap0043980:
	.incbin "baserom.gba", 0x43980, 0x9C
	.4byte gRom_08094BFC
	.incbin "baserom.gba", 0x43A20, 0xA4
	.4byte gData_080BB8C0
	.4byte gRom_080D7174
	.incbin "baserom.gba", 0x43ACC, 0x8
	.4byte gRom_08118FBC
	.incbin "baserom.gba", 0x43AD8, 0x4
