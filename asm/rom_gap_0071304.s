@ Unmatched ROM 0x08071304..0x0807179B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0071304
gRomGap0071304:
	.incbin "baserom.gba", 0x71304, 0xF0
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x713F8, 0x40
	.4byte gRom_0807143C
	.global gRom_0807143C
gRom_0807143C:
	.incbin "baserom.gba", 0x7143C, 0x78
	.4byte gRom_0807158C
	.incbin "baserom.gba", 0x714B8, 0x7C
	.4byte gRom_0807158C
	.incbin "baserom.gba", 0x71538, 0x44
	.4byte gRom_080715F8
	.incbin "baserom.gba", 0x71580, 0xC
	.global gRom_0807158C
gRom_0807158C:
	.incbin "baserom.gba", 0x7158C, 0x6C
	.global gRom_080715F8
gRom_080715F8:
	.incbin "baserom.gba", 0x715F8, 0x94
	.4byte gRom_08071690
	.global gRom_08071690
gRom_08071690:
	.4byte gRom_080716EC
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_080716F4
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.4byte gRom_08071710
	.incbin "baserom.gba", 0x716C4, 0x28
	.global gRom_080716EC
gRom_080716EC:
	.incbin "baserom.gba", 0x716EC, 0x8
	.global gRom_080716F4
gRom_080716F4:
	.incbin "baserom.gba", 0x716F4, 0x1C
	.global gRom_08071710
gRom_08071710:
	.incbin "baserom.gba", 0x71710, 0x8C
