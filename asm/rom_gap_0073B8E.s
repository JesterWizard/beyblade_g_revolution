@ Unmatched ROM 0x08073B8E..0x08074143
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0073B8E
gRomGap0073B8E:
	.incbin "baserom.gba", 0x73B8E, 0xB2
	.global _call_via_r0
	.thumb_func
_call_via_r0:
	.global _08073C40
	.thumb_func
_08073C40:
	.incbin "baserom.gba", 0x73C40, 0x4
	.global _call_via_r1
	.thumb_func
_call_via_r1:
	.global _08073C44
	.thumb_func
_08073C44:
	.incbin "baserom.gba", 0x73C44, 0x4
	.global _call_via_r2
	.thumb_func
_call_via_r2:
	.global _08073C48
	.thumb_func
_08073C48:
	.incbin "baserom.gba", 0x73C48, 0x4
	.global _call_via_r3
	.thumb_func
_call_via_r3:
	.global _08073C4C
	.thumb_func
_08073C4C:
	.incbin "baserom.gba", 0x73C4C, 0x4
	.global _call_via_r4
	.thumb_func
_call_via_r4:
	.global _08073C50
	.thumb_func
_08073C50:
	.global sub_08073C50
	.thumb_func
sub_08073C50:
	.incbin "baserom.gba", 0x73C50, 0x4
	.global _call_via_r5
	.thumb_func
_call_via_r5:
	.incbin "baserom.gba", 0x73C54, 0x4
	.global _call_via_r6
	.thumb_func
_call_via_r6:
	.incbin "baserom.gba", 0x73C58, 0x4
	.global _call_via_r7
	.thumb_func
_call_via_r7:
	.incbin "baserom.gba", 0x73C5C, 0x4
	.global _call_via_r8
	.thumb_func
_call_via_r8:
	.incbin "baserom.gba", 0x73C60, 0x4
	.global _call_via_r9
	.thumb_func
_call_via_r9:
	.global _08073C64
	.thumb_func
_08073C64:
	.incbin "baserom.gba", 0x73C64, 0x4
	.global _call_via_sl
	.thumb_func
_call_via_sl:
	.incbin "baserom.gba", 0x73C68, 0x4
	.global _call_via_fp
	.thumb_func
_call_via_fp:
	.incbin "baserom.gba", 0x73C6C, 0x4
	.global _call_via_ip
	.thumb_func
_call_via_ip:
	.incbin "baserom.gba", 0x73C70, 0x4
	.global _call_via_sp
	.thumb_func
_call_via_sp:
	.incbin "baserom.gba", 0x73C74, 0x4
	.global _call_via_lr
	.thumb_func
_call_via_lr:
	.incbin "baserom.gba", 0x73C78, 0x130
	.4byte gRom_083D3284
	.incbin "baserom.gba", 0x73DAC, 0x54
	.4byte gRom_083D3284
	.incbin "baserom.gba", 0x73E04, 0x174
	.4byte gRom_083D3284
	.incbin "baserom.gba", 0x73F7C, 0x134
	.global __divsi3
	.thumb_func
__divsi3:
	.global _080740B0
	.thumb_func
_080740B0:
	.incbin "baserom.gba", 0x740B0, 0x94
