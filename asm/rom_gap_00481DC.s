@ Unmatched ROM 0x080481DC..0x08048D0B
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap00481DC
gRomGap00481DC:
	.global _080481DC
	.thumb_func
_080481DC:
	.incbin "baserom.gba", 0x481DC, 0x38
	.global _08048214
	.thumb_func
_08048214:
	.incbin "baserom.gba", 0x48214, 0x148
	.4byte gRom_08097638
	.incbin "baserom.gba", 0x48360, 0x58
	.4byte gRom_0809764C
	.incbin "baserom.gba", 0x483BC, 0x4
	.4byte gRom_08097908
	.incbin "baserom.gba", 0x483C4, 0xE8
	.4byte gRom_08097660
	.incbin "baserom.gba", 0x484B0, 0x4
	.4byte gRom_08097908
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.incbin "baserom.gba", 0x484C0, 0x2B4
	.global _08048774
	.thumb_func
_08048774:
	.incbin "baserom.gba", 0x48774, 0x10C
	.global gRom_08048880
gRom_08048880:
	.incbin "baserom.gba", 0x48880, 0x94
	.4byte gRom_08113D80
	.4byte gRom_081145D4
	.4byte gRom_0811465C
	.4byte gData_080BB8C0
	.4byte gRom_082FACE0
	.incbin "baserom.gba", 0x48928, 0x8
	.global _08048930
	.thumb_func
_08048930:
	.incbin "baserom.gba", 0x48930, 0xD0
	.global _08048A00
	.thumb_func
_08048A00:
	.incbin "baserom.gba", 0x48A00, 0x74
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x48A78, 0x1DC
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A72AC
	.4byte gRom_083A72C0
	.4byte gRom_083A72D4
	.4byte gRom_082C44A8
	.4byte gData_080B7258
	.4byte gRom_08096C10
	.incbin "baserom.gba", 0x48C74, 0x8
	.4byte gRom_0809755C
	.4byte gRom_08097584
	.4byte gRom_08097570
	.global _08048C88
	.thumb_func
_08048C88:
	.incbin "baserom.gba", 0x48C88, 0x40
	.global _08048CC8
	.thumb_func
_08048CC8:
	.incbin "baserom.gba", 0x48CC8, 0x44
