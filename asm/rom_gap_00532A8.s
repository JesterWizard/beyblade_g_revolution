@ Unmatched ROM 0x080532A8..0x0805368F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00532A8
gRomGap00532A8:
	.global _080532A8
	.thumb_func
_080532A8:
	.incbin "baserom.gba", 0x532A8, 0xC8
	.4byte gRom_0811F888
	.global _08053374
	.thumb_func
_08053374:
	.incbin "baserom.gba", 0x53374, 0x48
	.global _080533BC
	.thumb_func
_080533BC:
	.incbin "baserom.gba", 0x533BC, 0x74
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x53434, 0x34
	.global _08053468
	.thumb_func
_08053468:
	.incbin "baserom.gba", 0x53468, 0x4
	.global _0805346C
	.thumb_func
_0805346C:
	.incbin "baserom.gba", 0x5346C, 0x44
	.global _080534B0
	.thumb_func
_080534B0:
	.incbin "baserom.gba", 0x534B0, 0x64
	.global _08053514
	.thumb_func
_08053514:
	.incbin "baserom.gba", 0x53514, 0x160
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8738
	.4byte gRom_083A8754
	.4byte gRom_083A8770
	.4byte gData_082BCD00
	.4byte gData_080B738E
