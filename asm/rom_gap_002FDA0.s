@ Unmatched ROM 0x0802FDA0..0x0803019B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002FDA0
gRomGap002FDA0:
	.global _0802FDA0
	.thumb_func
_0802FDA0:
	.incbin "baserom.gba", 0x2FDA0, 0xBC
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2FE60, 0x54
	.global _0802FEB4
	.thumb_func
_0802FEB4:
	.incbin "baserom.gba", 0x2FEB4, 0x80
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x2FF38, 0x5C
	.4byte gRom_0833C18C
	.4byte gRom_0833C194
	.4byte gRom_0833C1A4
	.4byte gRom_08077F44
	.4byte gRom_0833C1BC
	.4byte gRom_08077F24
	.incbin "baserom.gba", 0x2FFAC, 0x50
	.global _0802FFFC
	.thumb_func
_0802FFFC:
	.incbin "baserom.gba", 0x2FFFC, 0x4
	.global gRom_08030000
gRom_08030000:
	.incbin "baserom.gba", 0x30000, 0x4
	.global gRom_08030004
gRom_08030004:
	.incbin "baserom.gba", 0x30004, 0x50
	.global _08030054
	.thumb_func
_08030054:
	.incbin "baserom.gba", 0x30054, 0x44
	.4byte gRom_0833C1D8
	.4byte gRom_0833C1F4
	.4byte gRom_0833C220
	.global gRom_080300A4
gRom_080300A4:
	.incbin "baserom.gba", 0x300A4, 0xC
	.global gRom_080300B0
gRom_080300B0:
	.incbin "baserom.gba", 0x300B0, 0x10
	.global gRom_080300C0
gRom_080300C0:
	.incbin "baserom.gba", 0x300C0, 0xC
	.global gRom_080300CC
gRom_080300CC:
	.incbin "baserom.gba", 0x300CC, 0x24
	.global gRom_080300F0
gRom_080300F0:
	.incbin "baserom.gba", 0x300F0, 0x4
	.global gRom_080300F4
gRom_080300F4:
	.4byte gRom_080300F8
	.global gRom_080300F8
gRom_080300F8:
	.incbin "baserom.gba", 0x300F8, 0x4
	.global gRom_080300FC
gRom_080300FC:
	.4byte gRom_08030168
	.incbin "baserom.gba", 0x30100, 0x4
	.4byte gRom_08030124
	.incbin "baserom.gba", 0x30108, 0x4
	.4byte gRom_08030114
	.incbin "baserom.gba", 0x30110, 0x4
	.global gRom_08030114
gRom_08030114:
	.incbin "baserom.gba", 0x30114, 0x10
	.global gRom_08030124
gRom_08030124:
	.incbin "baserom.gba", 0x30124, 0x44
	.global gRom_08030168
gRom_08030168:
	.incbin "baserom.gba", 0x30168, 0x34
