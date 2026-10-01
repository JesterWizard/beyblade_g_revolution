@ Unmatched ROM 0x0803B144..0x0803C4FF
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap003B144
gRomGap003B144:
	.incbin "baserom.gba", 0x3B144, 0x4
	.global _0803B148
	.thumb_func
_0803B148:
	.incbin "baserom.gba", 0x3B148, 0x24C
	.4byte gData_080BB888
	.incbin "baserom.gba", 0x3B398, 0x4
	.global _0803B39C
	.thumb_func
_0803B39C:
	.incbin "baserom.gba", 0x3B39C, 0x270
	.global _0803B60C
	.thumb_func
_0803B60C:
	.incbin "baserom.gba", 0x3B60C, 0x30
	.4byte gRom_0803B640
	.global gRom_0803B640
gRom_0803B640:
	.4byte gRom_0803B658
	.4byte gRom_0803B71C
	.4byte gRom_0803B93C
	.4byte gRom_0803BB50
	.4byte gRom_0803C0CC
	.4byte gRom_0803C268
	.global gRom_0803B658
gRom_0803B658:
	.incbin "baserom.gba", 0x3B658, 0x84
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3B6E4, 0x38
	.global gRom_0803B71C
gRom_0803B71C:
	.incbin "baserom.gba", 0x3B71C, 0x198
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3B8BC, 0x80
	.global gRom_0803B93C
gRom_0803B93C:
	.incbin "baserom.gba", 0x3B93C, 0x190
	.4byte gData_082BF600
	.4byte gData_080B72F3
	.incbin "baserom.gba", 0x3BAD4, 0x7C
	.global gRom_0803BB50
gRom_0803BB50:
	.incbin "baserom.gba", 0x3BB50, 0x2A0
	.4byte gRom_0803BDF4
	.global gRom_0803BDF4
gRom_0803BDF4:
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEB8
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BEA0
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE88
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.4byte gRom_0803BE70
	.global gRom_0803BE70
gRom_0803BE70:
	.incbin "baserom.gba", 0x3BE70, 0x18
	.global gRom_0803BE88
gRom_0803BE88:
	.incbin "baserom.gba", 0x3BE88, 0x18
	.global gRom_0803BEA0
gRom_0803BEA0:
	.incbin "baserom.gba", 0x3BEA0, 0x18
	.global gRom_0803BEB8
gRom_0803BEB8:
	.incbin "baserom.gba", 0x3BEB8, 0x214
	.global gRom_0803C0CC
gRom_0803C0CC:
	.incbin "baserom.gba", 0x3C0CC, 0x19C
	.global gRom_0803C268
gRom_0803C268:
	.incbin "baserom.gba", 0x3C268, 0x298
