@ Unmatched ROM 0x080362D4..0x08036A67
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00362D4
gRomGap00362D4:
	.global _080362D4
	.thumb_func
_080362D4:
	.incbin "baserom.gba", 0x362D4, 0xE0
	.global _080363B4
	.thumb_func
_080363B4:
	.incbin "baserom.gba", 0x363B4, 0x44
	.4byte gRom_080363FC
	.global gRom_080363FC
gRom_080363FC:
	.4byte gRom_08036428
	.4byte gRom_08036454
	.4byte gRom_080364D0
	.4byte gRom_080364E8
	.4byte gRom_0803658C
	.4byte gRom_08036514
	.incbin "baserom.gba", 0x36414, 0x4
	.4byte gRom_08036540
	.4byte gRom_08036578
	.4byte gRom_080365A0
	.incbin "baserom.gba", 0x36424, 0x4
	.global gRom_08036428
gRom_08036428:
	.incbin "baserom.gba", 0x36428, 0x2C
	.global gRom_08036454
gRom_08036454:
	.incbin "baserom.gba", 0x36454, 0x7C
	.global gRom_080364D0
gRom_080364D0:
	.incbin "baserom.gba", 0x364D0, 0x18
	.global gRom_080364E8
gRom_080364E8:
	.incbin "baserom.gba", 0x364E8, 0x2C
	.global gRom_08036514
gRom_08036514:
	.incbin "baserom.gba", 0x36514, 0x2C
	.global gRom_08036540
gRom_08036540:
	.incbin "baserom.gba", 0x36540, 0x38
	.global gRom_08036578
gRom_08036578:
	.incbin "baserom.gba", 0x36578, 0x14
	.global gRom_0803658C
gRom_0803658C:
	.incbin "baserom.gba", 0x3658C, 0x14
	.global gRom_080365A0
gRom_080365A0:
	.incbin "baserom.gba", 0x365A0, 0x40
	.global _080365E0
	.thumb_func
_080365E0:
	.incbin "baserom.gba", 0x365E0, 0x138
	.4byte gRom_082A478C
	.4byte gRom_080BAF18
	.incbin "baserom.gba", 0x36720, 0x4
	.4byte gRom_08036728
	.global gRom_08036728
gRom_08036728:
	.4byte gRom_08036750
	.incbin "baserom.gba", 0x3672C, 0x4
	.4byte gRom_0803676C
	.incbin "baserom.gba", 0x36734, 0xC
	.4byte gRom_08036798
	.4byte gRom_080367A8
	.4byte gRom_080367B0
	.4byte gRom_080367D4
	.global gRom_08036750
gRom_08036750:
	.incbin "baserom.gba", 0x36750, 0x1C
	.global gRom_0803676C
gRom_0803676C:
	.incbin "baserom.gba", 0x3676C, 0x2C
	.global gRom_08036798
gRom_08036798:
	.incbin "baserom.gba", 0x36798, 0x10
	.global gRom_080367A8
gRom_080367A8:
	.incbin "baserom.gba", 0x367A8, 0x8
	.global gRom_080367B0
gRom_080367B0:
	.incbin "baserom.gba", 0x367B0, 0x24
	.global gRom_080367D4
gRom_080367D4:
	.incbin "baserom.gba", 0x367D4, 0x270
	.4byte gData_080B72F3
	.4byte gData_082BF600
	.4byte gRom_080972B4
	.incbin "baserom.gba", 0x36A50, 0x18
