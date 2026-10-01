@ Unmatched ROM 0x0803A20C..0x0803B077
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003A20C
gRomGap003A20C:
	.global _0803A20C
	.thumb_func
_0803A20C:
	.incbin "baserom.gba", 0x3A20C, 0x74
	.global _0803A280
	.thumb_func
_0803A280:
	.incbin "baserom.gba", 0x3A280, 0x74
	.global _0803A2F4
	.thumb_func
_0803A2F4:
	.incbin "baserom.gba", 0x3A2F4, 0x55C
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x3A864, 0x14
	.4byte gRom_081146E4
	.4byte gRom_080F3C9C
	.4byte gRom_08114950
	.4byte gRom_081155BC
	.incbin "baserom.gba", 0x3A888, 0x50
	.global _0803A8D8
	.thumb_func
_0803A8D8:
	.incbin "baserom.gba", 0x3A8D8, 0x84
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x3A960, 0xA4
	.global _0803AA04
	.thumb_func
_0803AA04:
	.incbin "baserom.gba", 0x3AA04, 0xC8
	.4byte gData_080BB8C0
	.incbin "baserom.gba", 0x3AAD0, 0x28
	.4byte gRom_0803AAFC
	.global gRom_0803AAFC
gRom_0803AAFC:
	.4byte gRom_0803AB10
	.4byte gRom_0803AB3C
	.4byte gRom_0803AB68
	.4byte gRom_0803AB94
	.4byte gRom_0803ABDC
	.global gRom_0803AB10
gRom_0803AB10:
	.incbin "baserom.gba", 0x3AB10, 0x2C
	.global gRom_0803AB3C
gRom_0803AB3C:
	.incbin "baserom.gba", 0x3AB3C, 0x2C
	.global gRom_0803AB68
gRom_0803AB68:
	.incbin "baserom.gba", 0x3AB68, 0x2C
	.global gRom_0803AB94
gRom_0803AB94:
	.incbin "baserom.gba", 0x3AB94, 0x48
	.global gRom_0803ABDC
gRom_0803ABDC:
	.incbin "baserom.gba", 0x3ABDC, 0xC4
	.global _0803ACA0
	.thumb_func
_0803ACA0:
	.incbin "baserom.gba", 0x3ACA0, 0xBC
	.global _0803AD5C
	.thumb_func
_0803AD5C:
	.incbin "baserom.gba", 0x3AD5C, 0x74
	.global _0803ADD0
	.thumb_func
_0803ADD0:
	.incbin "baserom.gba", 0x3ADD0, 0x228
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_0833C724
	.4byte gRom_0833C738
	.4byte gRom_0833C74C
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.4byte gRom_080796A8
	.incbin "baserom.gba", 0x3B018, 0x60
