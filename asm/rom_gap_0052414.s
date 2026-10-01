@ Unmatched ROM 0x08052414..0x0805264B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0052414
gRomGap0052414:
	.global _08052414
	.thumb_func
_08052414:
	.incbin "baserom.gba", 0x52414, 0x3C
	.global _08052450
	.thumb_func
_08052450:
	.incbin "baserom.gba", 0x52450, 0x4C
	.global _0805249C
	.thumb_func
_0805249C:
	.incbin "baserom.gba", 0x5249C, 0x34
	.global _080524D0
	.thumb_func
_080524D0:
	.incbin "baserom.gba", 0x524D0, 0x34
	.global _08052504
	.thumb_func
_08052504:
	.incbin "baserom.gba", 0x52504, 0x30
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x5253C, 0x58
	.global _08052594
	.thumb_func
_08052594:
	.incbin "baserom.gba", 0x52594, 0x30
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.incbin "baserom.gba", 0x525CC, 0x8
	.4byte gRom_080525D8
	.global gRom_080525D8
gRom_080525D8:
	.4byte gRom_080525F8
	.4byte gRom_08052600
	.4byte gRom_08052608
	.4byte gRom_08052610
	.4byte gRom_08052618
	.4byte gRom_08052620
	.4byte gRom_08052628
	.4byte gRom_08052638
	.global gRom_080525F8
gRom_080525F8:
	.incbin "baserom.gba", 0x525F8, 0x8
	.global gRom_08052600
gRom_08052600:
	.incbin "baserom.gba", 0x52600, 0x8
	.global gRom_08052608
gRom_08052608:
	.incbin "baserom.gba", 0x52608, 0x8
	.global gRom_08052610
gRom_08052610:
	.incbin "baserom.gba", 0x52610, 0x8
	.global gRom_08052618
gRom_08052618:
	.incbin "baserom.gba", 0x52618, 0x8
	.global gRom_08052620
gRom_08052620:
	.incbin "baserom.gba", 0x52620, 0x8
	.global gRom_08052628
gRom_08052628:
	.incbin "baserom.gba", 0x52628, 0x10
	.global gRom_08052638
gRom_08052638:
	.incbin "baserom.gba", 0x52638, 0x14
