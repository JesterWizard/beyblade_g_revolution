@ Unmatched ROM 0x080476D2..0x08047A93
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00476D2
gRomGap00476D2:
	.incbin "baserom.gba", 0x476D2, 0x36
	.global _08047708
	.thumb_func
_08047708:
	.incbin "baserom.gba", 0x47708, 0x5C
	.global _08047764
	.thumb_func
_08047764:
	.incbin "baserom.gba", 0x47764, 0x50
	.global _080477B4
	.thumb_func
_080477B4:
	.incbin "baserom.gba", 0x477B4, 0xC0
	.global _08047874
	.thumb_func
_08047874:
	.incbin "baserom.gba", 0x47874, 0x18
	.global _0804788C
	.thumb_func
_0804788C:
	.incbin "baserom.gba", 0x4788C, 0x174
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A6BD0
	.4byte gData_083A6BE0
	.4byte gRom_083A6BF0
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_08096AD0
	.incbin "baserom.gba", 0x47A20, 0x74
