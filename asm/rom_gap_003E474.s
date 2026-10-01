@ Unmatched ROM 0x0803E474..0x0803E847
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003E474
gRomGap003E474:
	.global _0803E474
	.thumb_func
_0803E474:
	.incbin "baserom.gba", 0x3E474, 0xB0
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.4byte gRom_0833D378
	.global _0803E530
	.thumb_func
_0803E530:
	.incbin "baserom.gba", 0x3E530, 0xC8
	.global _0803E5F8
	.thumb_func
_0803E5F8:
	.incbin "baserom.gba", 0x3E5F8, 0x90
	.global _0803E688
	.thumb_func
_0803E688:
	.incbin "baserom.gba", 0x3E688, 0x4
	.global _0803E68C
	.thumb_func
_0803E68C:
	.incbin "baserom.gba", 0x3E68C, 0x38
	.global _0803E6C4
	.thumb_func
_0803E6C4:
	.incbin "baserom.gba", 0x3E6C4, 0x34
	.global _0803E6F8
	.thumb_func
_0803E6F8:
	.incbin "baserom.gba", 0x3E6F8, 0x124
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833D3A0
	.4byte gRom_0833D3B8
	.4byte gRom_0833D3C4
	.4byte gRom_0833D3CC
	.4byte gRom_0833D3D8
	.4byte gRom_0833D3E0
	.4byte gRom_0833D3E8
	.4byte gRom_0833D3F0
	.incbin "baserom.gba", 0x3E844, 0x4
