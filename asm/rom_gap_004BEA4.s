@ Unmatched ROM 0x0804BEA4..0x0804C27B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap004BEA4
gRomGap004BEA4:
	.global _0804BEA4
	.thumb_func
_0804BEA4:
	.incbin "baserom.gba", 0x4BEA4, 0xB0
	.4byte gRom_082BB648
	.4byte gData_080B7258
	.global _0804BF5C
	.thumb_func
_0804BF5C:
	.incbin "baserom.gba", 0x4BF5C, 0x70
	.global _0804BFCC
	.thumb_func
_0804BFCC:
	.incbin "baserom.gba", 0x4BFCC, 0xB0
	.global _0804C07C
	.thumb_func
_0804C07C:
	.incbin "baserom.gba", 0x4C07C, 0x90
	.4byte gRom_083A7DAC
	.global _0804C110
	.thumb_func
_0804C110:
	.incbin "baserom.gba", 0x4C110, 0x38
	.global _0804C148
	.thumb_func
_0804C148:
	.incbin "baserom.gba", 0x4C148, 0x34
	.global _0804C17C
	.thumb_func
_0804C17C:
	.incbin "baserom.gba", 0x4C17C, 0xF0
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7DC8
	.4byte gRom_083A7DE0
