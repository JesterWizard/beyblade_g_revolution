@ Unmatched ROM 0x080655D8..0x08065CCF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00655D8
gRomGap00655D8:
	.incbin "baserom.gba", 0x655D8, 0xE0
	.4byte gRom_080BA284
	.4byte gRom_080BA288
	.incbin "baserom.gba", 0x656C0, 0x4
	.global _080656C4
	.thumb_func
_080656C4:
	.incbin "baserom.gba", 0x656C4, 0x124
	.4byte gRom_080BAF18
	.incbin "baserom.gba", 0x657EC, 0x4
	.4byte gRom_082A478C
	.4byte gRom_080BAE24
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_082AB6B0
	.global _08065804
	.thumb_func
_08065804:
	.incbin "baserom.gba", 0x65804, 0x140
	.global _08065944
	.thumb_func
_08065944:
	.incbin "baserom.gba", 0x65944, 0x94
	.global _080659D8
	.thumb_func
_080659D8:
	.incbin "baserom.gba", 0x659D8, 0x44
	.global _08065A1C
	.thumb_func
_08065A1C:
	.incbin "baserom.gba", 0x65A1C, 0x28
	.global _08065A44
	.thumb_func
_08065A44:
	.incbin "baserom.gba", 0x65A44, 0x4
	.global _08065A48
	.thumb_func
_08065A48:
	.incbin "baserom.gba", 0x65A48, 0x120
	.4byte gRom_080BAE24
	.incbin "baserom.gba", 0x65B6C, 0xC0
	.4byte gRom_083A8E2C
	.incbin "baserom.gba", 0x65C30, 0x48
	.4byte gRom_083A8E2C
	.incbin "baserom.gba", 0x65C7C, 0x50
	.4byte gRom_080B9000
