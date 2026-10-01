@ Unmatched ROM 0x080526AC..0x08052933
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00526AC
gRomGap00526AC:
	.incbin "baserom.gba", 0x526AC, 0x1DC
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A8694
	.4byte gRom_083A86B0
	.4byte gRom_083A86CC
	.4byte gRom_083A86E8
	.global _080528A0
	.thumb_func
_080528A0:
	.incbin "baserom.gba", 0x528A0, 0x18
	.global _080528B8
	.thumb_func
_080528B8:
	.incbin "baserom.gba", 0x528B8, 0x38
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.incbin "baserom.gba", 0x528F8, 0x3C
