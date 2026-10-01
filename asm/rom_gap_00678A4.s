@ Unmatched ROM 0x080678A4..0x080679A3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00678A4
gRomGap00678A4:
	.incbin "baserom.gba", 0x678A4, 0x30
	.4byte gRom_08000138
	.incbin "baserom.gba", 0x678D8, 0x4
	.4byte gRom_0800024C
	.incbin "baserom.gba", 0x678E0, 0x24
	.4byte gRom_083A9434
	.incbin "baserom.gba", 0x67908, 0x40
	.4byte gRom_083A93FC
	.incbin "baserom.gba", 0x6794C, 0x58
