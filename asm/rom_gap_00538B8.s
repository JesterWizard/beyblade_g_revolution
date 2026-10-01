@ Unmatched ROM 0x080538B8..0x08054107
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00538B8
gRomGap00538B8:
	.incbin "baserom.gba", 0x538B8, 0x8
	.global _080538C0
	.thumb_func
_080538C0:
	.incbin "baserom.gba", 0x538C0, 0x20C
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x53AE0, 0x8
	.global _08053AE8
	.thumb_func
_08053AE8:
	.incbin "baserom.gba", 0x53AE8, 0xD0
	.global _08053BB8
	.thumb_func
_08053BB8:
	.incbin "baserom.gba", 0x53BB8, 0x74
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x53C30, 0x88
	.global _08053CB8
	.thumb_func
_08053CB8:
	.incbin "baserom.gba", 0x53CB8, 0x154
	.global _08053E0C
	.thumb_func
_08053E0C:
	.incbin "baserom.gba", 0x53E0C, 0x74
	.global _08053E80
	.thumb_func
_08053E80:
	.incbin "baserom.gba", 0x53E80, 0x64
	.global _08053EE4
	.thumb_func
_08053EE4:
	.incbin "baserom.gba", 0x53EE4, 0x70
	.global gRom_08053F54
gRom_08053F54:
	.incbin "baserom.gba", 0x53F54, 0x178
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A878C
	.4byte gRom_083A87A4
	.4byte gRom_083A87BC
	.incbin "baserom.gba", 0x540E0, 0x8
	.4byte gRom_083A87D4
	.4byte gRom_083A87F0
	.4byte gRom_083A880C
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.4byte gRom_08096F44
	.incbin "baserom.gba", 0x54100, 0x4
	.4byte gRom_080978F4
