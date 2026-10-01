@ Unmatched ROM 0x0806645C..0x08066AD3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap006645C
gRomGap006645C:
	.global _0806645C
	.thumb_func
_0806645C:
	.incbin "baserom.gba", 0x6645C, 0x1D4
	.4byte gRom_080BAF18
	.incbin "baserom.gba", 0x66634, 0x4
	.4byte gRom_082A478C
	.4byte gRom_08126D9C
	.4byte gRom_080BAFE4
	.incbin "baserom.gba", 0x66644, 0x4
	.4byte gData_082BCD00
	.4byte gRom_080BAE54
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x66654, 0x10
	.global _08066664
	.thumb_func
_08066664:
	.incbin "baserom.gba", 0x66664, 0x188
	.global _080667EC
	.thumb_func
_080667EC:
	.incbin "baserom.gba", 0x667EC, 0xDC
	.global _080668C8
	.thumb_func
_080668C8:
	.incbin "baserom.gba", 0x668C8, 0xBC
	.global _08066984
	.thumb_func
_08066984:
	.incbin "baserom.gba", 0x66984, 0x70
	.global _080669F4
	.thumb_func
_080669F4:
	.incbin "baserom.gba", 0x669F4, 0x38
	.global _08066A2C
	.thumb_func
_08066A2C:
	.incbin "baserom.gba", 0x66A2C, 0x38
	.global _08066A64
	.thumb_func
_08066A64:
	.incbin "baserom.gba", 0x66A64, 0x38
	.global _08066A9C
	.thumb_func
_08066A9C:
	.incbin "baserom.gba", 0x66A9C, 0x38
