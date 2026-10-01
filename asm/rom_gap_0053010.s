@ Unmatched ROM 0x08053010..0x08053217
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0053010
gRomGap0053010:
	.incbin "baserom.gba", 0x53010, 0xF8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A86FC
	.4byte gRom_08099620
	.incbin "baserom.gba", 0x53118, 0xE8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A86FC
	.4byte gRom_08099620
	.incbin "baserom.gba", 0x53210, 0x8
