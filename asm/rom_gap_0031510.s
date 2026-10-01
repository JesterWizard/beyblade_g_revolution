@ Unmatched ROM 0x08031510..0x08031C97
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0031510
gRomGap0031510:
	.incbin "baserom.gba", 0x31510, 0xD4
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x315E8, 0xC4
	.global _080316AC
	.thumb_func
_080316AC:
	.incbin "baserom.gba", 0x316AC, 0x50
	.global _080316FC
	.thumb_func
_080316FC:
	.incbin "baserom.gba", 0x316FC, 0xC4
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x317C4, 0x2C8
	.4byte gData_0807BDB8
	.4byte gData_0807BB80
	.4byte gData_0807B6F0
	.4byte gRom_0833C444
	.4byte gRom_0833C454
	.4byte gRom_0833C464
	.4byte gRom_0833C474
	.4byte gRom_0833C484
	.4byte gRom_0833C494
	.4byte gRom_0833C4A4
	.incbin "baserom.gba", 0x31AB4, 0x1B8
	.4byte gData_0807BDB8
	.4byte gData_0807BB80
	.4byte gData_0807B6F0
	.4byte gRom_0833C4B4
	.4byte gRom_0833C454
	.4byte gRom_0833C464
	.4byte gRom_0833C474
	.4byte gRom_0833C484
	.incbin "baserom.gba", 0x31C8C, 0x8
	.4byte gRom_0833C4C0
