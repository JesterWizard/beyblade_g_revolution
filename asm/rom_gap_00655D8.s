@ Unmatched ROM 0x080655D8..0x08065CCF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00655D8
gRomGap00655D8:
	.incbin "baserom.gba", 0x655D8, 0xEC
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
	.incbin "baserom.gba", 0x65944, 0x38C
