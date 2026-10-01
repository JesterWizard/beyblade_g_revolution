@ Unmatched ROM 0x08047B3C..0x08048167
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0047B3C
gRomGap0047B3C:
	.global _08047B3C
	.thumb_func
_08047B3C:
	.incbin "baserom.gba", 0x47B3C, 0xB0
	.4byte gData_082BCD00
	.4byte gData_080B738E
	.global _08047BF4
	.thumb_func
_08047BF4:
	.incbin "baserom.gba", 0x47BF4, 0x58
	.4byte gData_080BB8C0
	.4byte gRom_082C5960
	.incbin "baserom.gba", 0x47C54, 0x74
	.4byte gRom_08097CBC
	.incbin "baserom.gba", 0x47CCC, 0x74
	.4byte gRom_08097CBC
	.incbin "baserom.gba", 0x47D44, 0x8
	.global _08047D4C
	.thumb_func
_08047D4C:
	.incbin "baserom.gba", 0x47D4C, 0xD0
	.global _08047E1C
	.thumb_func
_08047E1C:
	.incbin "baserom.gba", 0x47E1C, 0x64
	.global _08047E80
	.thumb_func
_08047E80:
	.incbin "baserom.gba", 0x47E80, 0x48
	.global _08047EC8
	.thumb_func
_08047EC8:
	.incbin "baserom.gba", 0x47EC8, 0x70
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x47F3C, 0x19C
	.4byte gData_080D79CC
	.4byte gData_080B7429
	.4byte gRom_083A7240
	.4byte gRom_083A725C
	.4byte gRom_083A7278
	.incbin "baserom.gba", 0x480EC, 0x4
	.4byte gRom_083A7294
	.4byte gData_080969CC
	.incbin "baserom.gba", 0x480F8, 0x8
	.4byte gData_080969E0
	.4byte gRom_083A72A0
	.global _08048108
	.thumb_func
_08048108:
	.incbin "baserom.gba", 0x48108, 0x30
	.global _08048138
	.thumb_func
_08048138:
	.incbin "baserom.gba", 0x48138, 0x30
