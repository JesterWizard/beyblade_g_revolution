@ Unmatched ROM 0x08039344..0x08039BD3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0039344
gRomGap0039344:
	.global _08039344
	.thumb_func
_08039344:
	.incbin "baserom.gba", 0x39344, 0x1D4
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x3952C, 0xC
	.global _08039538
	.thumb_func
_08039538:
	.incbin "baserom.gba", 0x39538, 0xD0
	.global _08039608
	.thumb_func
_08039608:
	.incbin "baserom.gba", 0x39608, 0x74
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x39680, 0x7C
	.global _080396FC
	.thumb_func
_080396FC:
	.incbin "baserom.gba", 0x396FC, 0x1DC
	.global _080398D8
	.thumb_func
_080398D8:
	.incbin "baserom.gba", 0x398D8, 0x74
	.global _0803994C
	.thumb_func
_0803994C:
	.incbin "baserom.gba", 0x3994C, 0x64
	.global _080399B0
	.thumb_func
_080399B0:
	.incbin "baserom.gba", 0x399B0, 0x1E8
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833C688
	.4byte gRom_0833C6A0
	.4byte gRom_0833C6B8
	.incbin "baserom.gba", 0x39BAC, 0x8
	.4byte gRom_0833C6D0
	.4byte gRom_0833C6EC
	.4byte gRom_0833C708
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.4byte gRom_08096F44
	.incbin "baserom.gba", 0x39BCC, 0x8
