@ Unmatched ROM 0x080505AC..0x080507B7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00505AC
gRomGap00505AC:
	.global _080505AC
	.thumb_func
_080505AC:
	.incbin "baserom.gba", 0x505AC, 0x24
	.4byte gRom_080505D4
	.global gRom_080505D4
gRom_080505D4:
	.4byte gRom_080505E8
	.incbin "baserom.gba", 0x505D8, 0x8
	.4byte gRom_0805060C
	.4byte gRom_0805061C
	.global gRom_080505E8
gRom_080505E8:
	.incbin "baserom.gba", 0x505E8, 0x24
	.global gRom_0805060C
gRom_0805060C:
	.incbin "baserom.gba", 0x5060C, 0x10
	.global gRom_0805061C
gRom_0805061C:
	.incbin "baserom.gba", 0x5061C, 0x10
	.global _0805062C
	.thumb_func
_0805062C:
	.incbin "baserom.gba", 0x5062C, 0x74
	.global _080506A0
	.thumb_func
_080506A0:
	.incbin "baserom.gba", 0x506A0, 0x84
	.global _08050724
	.thumb_func
_08050724:
	.incbin "baserom.gba", 0x50724, 0x48
	.global _0805076C
	.thumb_func
_0805076C:
	.incbin "baserom.gba", 0x5076C, 0x4C
