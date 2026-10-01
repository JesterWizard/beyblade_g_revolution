@ Unmatched ROM 0x08041E86..0x08041F87
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0041E86
gRomGap0041E86:
	.incbin "baserom.gba", 0x41E86, 0x2
	.global _08041E88
	.thumb_func
_08041E88:
	.incbin "baserom.gba", 0x41E88, 0x24
	.4byte gRom_08041EB0
	.global gRom_08041EB0
gRom_08041EB0:
	.4byte gRom_08041EF4
	.incbin "baserom.gba", 0x41EB4, 0x4
	.4byte gRom_08041F14
	.4byte gRom_08041F7C
	.4byte gRom_08041F2C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F44
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F7C
	.4byte gRom_08041F6C
	.global gRom_08041EF4
gRom_08041EF4:
	.incbin "baserom.gba", 0x41EF4, 0x20
	.global gRom_08041F14
gRom_08041F14:
	.incbin "baserom.gba", 0x41F14, 0x18
	.global gRom_08041F2C
gRom_08041F2C:
	.incbin "baserom.gba", 0x41F2C, 0x18
	.global gRom_08041F44
gRom_08041F44:
	.incbin "baserom.gba", 0x41F44, 0x28
	.global gRom_08041F6C
gRom_08041F6C:
	.incbin "baserom.gba", 0x41F6C, 0x10
	.global gRom_08041F7C
gRom_08041F7C:
	.incbin "baserom.gba", 0x41F7C, 0xC
