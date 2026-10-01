@ Unmatched ROM 0x0802BC84..0x0802BF03
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002BC84
gRomGap002BC84:
	.global _0802BC84
	.thumb_func
_0802BC84:
	.incbin "baserom.gba", 0x2BC84, 0x34
	.global _0802BCB8
	.thumb_func
_0802BCB8:
	.incbin "baserom.gba", 0x2BCB8, 0xC0
	.4byte gData_08096B5C
	.incbin "baserom.gba", 0x2BD7C, 0x4
	.4byte gRom_0802BD84
	.global gRom_0802BD84
gRom_0802BD84:
	.4byte gRom_0802BE48
	.4byte gRom_0802BDA8
	.4byte gRom_0802BDD4
	.4byte gRom_0802BE00
	.4byte gRom_0802BE48
	.4byte gRom_0802BE48
	.4byte gRom_0802BE48
	.4byte gRom_0802BE48
	.4byte gRom_0802BE48
	.global gRom_0802BDA8
gRom_0802BDA8:
	.incbin "baserom.gba", 0x2BDA8, 0x20
	.4byte gRom_08096CEC
	.incbin "baserom.gba", 0x2BDCC, 0x4
	.4byte gRom_082F9D90
	.global gRom_0802BDD4
gRom_0802BDD4:
	.incbin "baserom.gba", 0x2BDD4, 0x20
	.4byte gRom_08096DF0
	.incbin "baserom.gba", 0x2BDF8, 0x4
	.4byte gRom_082F9B38
	.global gRom_0802BE00
gRom_0802BE00:
	.incbin "baserom.gba", 0x2BE00, 0x48
	.global gRom_0802BE48
gRom_0802BE48:
	.incbin "baserom.gba", 0x2BE48, 0x30
	.4byte gRom_08096E04
	.incbin "baserom.gba", 0x2BE7C, 0x4
	.4byte gRom_082F9A68
	.incbin "baserom.gba", 0x2BE84, 0x80
