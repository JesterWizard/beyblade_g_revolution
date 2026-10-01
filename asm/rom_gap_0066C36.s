@ Unmatched ROM 0x08066C36..0x08066FB7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0066C36
gRomGap0066C36:
	.incbin "baserom.gba", 0x66C36, 0x2
	.global _08066C38
	.thumb_func
_08066C38:
	.incbin "baserom.gba", 0x66C38, 0x6C
	.4byte gData_080BB110
	.incbin "baserom.gba", 0x66CA8, 0x14
	.global _08066CBC
	.thumb_func
_08066CBC:
	.incbin "baserom.gba", 0x66CBC, 0x48
	.global _08066D04
	.thumb_func
_08066D04:
	.incbin "baserom.gba", 0x66D04, 0x16C
	.4byte gData_080BB110
	.incbin "baserom.gba", 0x66E74, 0x28
	.global _08066E9C
	.thumb_func
_08066E9C:
	.incbin "baserom.gba", 0x66E9C, 0x44
	.global _08066EE0
	.thumb_func
_08066EE0:
	.incbin "baserom.gba", 0x66EE0, 0x44
	.global _08066F24
	.thumb_func
_08066F24:
	.incbin "baserom.gba", 0x66F24, 0x44
	.global _08066F68
	.thumb_func
_08066F68:
	.incbin "baserom.gba", 0x66F68, 0x50
