@ Unmatched ROM 0x08036B58..0x0803715B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0036B58
gRomGap0036B58:
	.incbin "baserom.gba", 0x36B58, 0x84
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36BE4, 0x94
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36C80, 0x94
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36D1C, 0xE0
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36E04, 0xE0
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36EEC, 0xE0
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x36FD4, 0xBC
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.incbin "baserom.gba", 0x37098, 0xA0
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_08096FA8
	.incbin "baserom.gba", 0x37144, 0x18
