@ Unmatched ROM 0x0803D64C..0x0803DBCF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003D64C
gRomGap003D64C:
	.incbin "baserom.gba", 0x3D64C, 0x64
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3D6B8, 0x40
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3D700, 0x98
	.global _0803D798
	.thumb_func
_0803D798:
	.incbin "baserom.gba", 0x3D798, 0x8
	.global _0803D7A0
	.thumb_func
_0803D7A0:
	.incbin "baserom.gba", 0x3D7A0, 0x50
	.global _0803D7F0
	.thumb_func
_0803D7F0:
	.incbin "baserom.gba", 0x3D7F0, 0x4C
	.global _0803D83C
	.thumb_func
_0803D83C:
	.incbin "baserom.gba", 0x3D83C, 0x60
	.global _0803D89C
	.thumb_func
_0803D89C:
	.incbin "baserom.gba", 0x3D89C, 0x30
	.global _0803D8CC
	.thumb_func
_0803D8CC:
	.incbin "baserom.gba", 0x3D8CC, 0x50
	.4byte gData_08099710
	.incbin "baserom.gba", 0x3D920, 0xC
	.global _0803D92C
	.thumb_func
_0803D92C:
	.incbin "baserom.gba", 0x3D92C, 0x34
	.global _0803D960
	.thumb_func
_0803D960:
	.incbin "baserom.gba", 0x3D960, 0x1C
	.global _0803D97C
	.thumb_func
_0803D97C:
	.incbin "baserom.gba", 0x3D97C, 0x50
	.global _0803D9CC
	.thumb_func
_0803D9CC:
	.incbin "baserom.gba", 0x3D9CC, 0x54
	.global _0803DA20
	.thumb_func
_0803DA20:
	.incbin "baserom.gba", 0x3DA20, 0x188
	.4byte gData_0807A1F4
	.incbin "baserom.gba", 0x3DBAC, 0x1C
	.4byte gData_0807A1F4
	.incbin "baserom.gba", 0x3DBCC, 0x4
