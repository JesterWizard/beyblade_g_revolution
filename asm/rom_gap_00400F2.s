@ Unmatched ROM 0x080400F2..0x0804052F
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00400F2
gRomGap00400F2:
	.incbin "baserom.gba", 0x400F2, 0x2A
	.4byte gRom_08040120
	.global gRom_08040120
gRom_08040120:
	.4byte gRom_0804016C
	.4byte gRom_08040198
	.4byte gRom_080401BC
	.4byte gRom_08040258
	.4byte gRom_080401C0
	.4byte gRom_08040210
	.incbin "baserom.gba", 0x40138, 0x4
	.4byte gRom_080402BC
	.4byte gRom_080402F8
	.4byte gRom_08040334
	.4byte gRom_08040344
	.4byte gRom_08040354
	.4byte gRom_08040390
	.4byte gRom_080403C0
	.4byte gRom_080403FC
	.4byte gRom_0804046C
	.4byte gRom_080404B8
	.4byte gRom_080404B8
	.4byte gRom_080404B8
	.global gRom_0804016C
gRom_0804016C:
	.incbin "baserom.gba", 0x4016C, 0x2C
	.global gRom_08040198
gRom_08040198:
	.incbin "baserom.gba", 0x40198, 0x24
	.global gRom_080401BC
gRom_080401BC:
	.incbin "baserom.gba", 0x401BC, 0x4
	.global gRom_080401C0
gRom_080401C0:
	.incbin "baserom.gba", 0x401C0, 0x40
	.4byte _08050EA8 + 1
	.4byte sub_080400D4
	.incbin "baserom.gba", 0x40208, 0x8
	.global gRom_08040210
gRom_08040210:
	.incbin "baserom.gba", 0x40210, 0x40
	.4byte _0803D944 + 1
	.4byte sub_080400D4
	.global gRom_08040258
gRom_08040258:
	.incbin "baserom.gba", 0x40258, 0x54
	.4byte _080563A0 + 1
	.4byte sub_080400D4
	.incbin "baserom.gba", 0x402B4, 0x8
	.global gRom_080402BC
gRom_080402BC:
	.incbin "baserom.gba", 0x402BC, 0x34
	.4byte _0802E67C + 1
	.4byte sub_080400D4
	.global gRom_080402F8
gRom_080402F8:
	.incbin "baserom.gba", 0x402F8, 0x34
	.4byte _0802FDA0 + 1
	.4byte _0802FEB4 + 1
	.global gRom_08040334
gRom_08040334:
	.incbin "baserom.gba", 0x40334, 0x10
	.global gRom_08040344
gRom_08040344:
	.incbin "baserom.gba", 0x40344, 0x10
	.global gRom_08040354
gRom_08040354:
	.incbin "baserom.gba", 0x40354, 0x34
	.4byte _0802EEEC + 1
	.4byte _0802EFCC + 1
	.global gRom_08040390
gRom_08040390:
	.incbin "baserom.gba", 0x40390, 0x30
	.global gRom_080403C0
gRom_080403C0:
	.incbin "baserom.gba", 0x403C0, 0x34
	.4byte _08050E68 + 1
	.4byte _08050E80 + 1
	.global gRom_080403FC
gRom_080403FC:
	.incbin "baserom.gba", 0x403FC, 0x14
	.global gRom_08040410
gRom_08040410:
	.incbin "baserom.gba", 0x40410, 0x4
	.global gRom_08040414
gRom_08040414:
	.incbin "baserom.gba", 0x40414, 0x2C
	.global gRom_08040440
gRom_08040440:
	.incbin "baserom.gba", 0x40440, 0x1C
	.4byte _0805DEAC + 1
	.incbin "baserom.gba", 0x40460, 0x4
	.4byte _0805DF04 + 1
	.incbin "baserom.gba", 0x40468, 0x4
	.global gRom_0804046C
gRom_0804046C:
	.incbin "baserom.gba", 0x4046C, 0x1C
	.global gRom_08040488
gRom_08040488:
	.incbin "baserom.gba", 0x40488, 0x28
	.4byte _0804E59C + 1
	.4byte _0804E5E0 + 1
	.global gRom_080404B8
gRom_080404B8:
	.incbin "baserom.gba", 0x404B8, 0x64
	.4byte _0803DB44 + 1
	.incbin "baserom.gba", 0x40520, 0x8
	.4byte _0803DA68 + 1
	.4byte _0803DAD4 + 1
