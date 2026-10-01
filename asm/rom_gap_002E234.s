@ Unmatched ROM 0x0802E234..0x0802E2F7
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap002E234
gRomGap002E234:
	.incbin "baserom.gba", 0x2E234, 0x40
	.4byte gData_08077AC0
	.incbin "baserom.gba", 0x2E278, 0x30
	.4byte gData_08077AC0
	.incbin "baserom.gba", 0x2E2AC, 0x40
	.4byte gData_08096B5C
	.incbin "baserom.gba", 0x2E2F0, 0x8
