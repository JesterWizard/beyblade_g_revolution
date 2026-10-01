@ Unmatched ROM 0x08057344..0x080593A3
	.section .rodata,"a",%progbits
	.balign 2
	.global gRomGap0057344
gRomGap0057344:
	.incbin "baserom.gba", 0x57344, 0x150
	.global _08057494
	.thumb_func
_08057494:
	.incbin "baserom.gba", 0x57494, 0x2C
	.4byte gData_080BB8BC
	.incbin "baserom.gba", 0x574C4, 0xC
	.global _080574D0
	.thumb_func
_080574D0:
	.incbin "baserom.gba", 0x574D0, 0x44
	.4byte gRom_08057518
	.global gRom_08057518
gRom_08057518:
	.4byte gRom_0805904C
	.4byte gRom_080575DC
	.4byte gRom_08057628
	.4byte gRom_080576A0
	.4byte gRom_0805773C
	.4byte gRom_08057820
	.4byte gRom_080578D8
	.4byte gRom_08057960
	.4byte gRom_080579DC
	.4byte gRom_08057A50
	.4byte gRom_08057AC8
	.4byte gRom_08057B38
	.4byte gRom_08057BEC
	.incbin "baserom.gba", 0x5754C, 0x4
	.4byte gRom_08057C2C
	.4byte gRom_08057E8C
	.4byte gRom_08057F40
	.4byte gRom_08057F8C
	.4byte gRom_08057FCC
	.4byte gRom_08058028
	.4byte gRom_0805808C
	.4byte gRom_080580FC
	.4byte gRom_08058158
	.4byte gRom_080581B4
	.4byte gRom_080581DC
	.incbin "baserom.gba", 0x5757C, 0x4
	.4byte gRom_080582A0
	.4byte gRom_080582C4
	.incbin "baserom.gba", 0x57588, 0x4
	.4byte gRom_08058400
	.4byte gRom_08058498
	.4byte gRom_08058604
	.4byte gRom_080586B4
	.4byte gRom_08058730
	.4byte gRom_080587E0
	.4byte gRom_0805883C
	.4byte gRom_08058864
	.4byte gRom_0805888C
	.4byte gRom_08058E10
	.4byte gRom_080588EC
	.incbin "baserom.gba", 0x575B8, 0x4
	.4byte gRom_08058B24
	.4byte gRom_08058B84
	.incbin "baserom.gba", 0x575C4, 0x4
	.4byte gRom_08058BCC
	.4byte gRom_08058CF8
	.4byte gRom_08058D84
	.4byte gRom_08058E10
	.4byte gRom_08058EB4
	.global gRom_080575DC
gRom_080575DC:
	.incbin "baserom.gba", 0x575DC, 0x3C
	.4byte gRom_0810B69C
	.4byte gData_080BB8C0
	.4byte gRom_08123470
	.incbin "baserom.gba", 0x57624, 0x4
	.global gRom_08057628
gRom_08057628:
	.incbin "baserom.gba", 0x57628, 0x68
	.4byte gRom_08123670
	.incbin "baserom.gba", 0x57694, 0x8
	.4byte _0805919C + 1
	.global gRom_080576A0
gRom_080576A0:
	.incbin "baserom.gba", 0x576A0, 0x8C
	.4byte gRom_0810B86C
	.incbin "baserom.gba", 0x57730, 0x8
	.4byte gRom_0810BF18
	.global gRom_0805773C
gRom_0805773C:
	.incbin "baserom.gba", 0x5773C, 0xD0
	.4byte _080591D8 + 1
	.incbin "baserom.gba", 0x57810, 0x4
	.4byte gRom_08123D50
	.4byte gRom_080996D8
	.4byte gRom_08124128
	.global gRom_08057820
gRom_08057820:
	.incbin "baserom.gba", 0x57820, 0xA0
	.4byte gRom_08124594
	.incbin "baserom.gba", 0x578C4, 0x4
	.4byte gData_080BB8C0
	.4byte gRom_081247A4
	.incbin "baserom.gba", 0x578D0, 0x8
	.global gRom_080578D8
gRom_080578D8:
	.incbin "baserom.gba", 0x578D8, 0x7C
	.4byte _08059274 + 1
	.incbin "baserom.gba", 0x57958, 0x4
	.4byte gRom_081249A4
	.global gRom_08057960
gRom_08057960:
	.incbin "baserom.gba", 0x57960, 0x68
	.4byte gRom_08124DBC
	.4byte gData_080BB8C0
	.4byte gRom_08125334
	.incbin "baserom.gba", 0x579D4, 0x8
	.global gRom_080579DC
gRom_080579DC:
	.incbin "baserom.gba", 0x579DC, 0x74
	.global gRom_08057A50
gRom_08057A50:
	.incbin "baserom.gba", 0x57A50, 0x78
	.global gRom_08057AC8
gRom_08057AC8:
	.incbin "baserom.gba", 0x57AC8, 0x5C
	.4byte gRom_08124DBC
	.incbin "baserom.gba", 0x57B28, 0x8
	.4byte _08059300 + 1
	.incbin "baserom.gba", 0x57B34, 0x4
	.global gRom_08057B38
gRom_08057B38:
	.incbin "baserom.gba", 0x57B38, 0xB0
	.4byte gRom_08124DBC
	.global gRom_08057BEC
gRom_08057BEC:
	.incbin "baserom.gba", 0x57BEC, 0x34
	.4byte _08059300 + 1
	.incbin "baserom.gba", 0x57C24, 0x8
	.global gRom_08057C2C
gRom_08057C2C:
	.incbin "baserom.gba", 0x57C2C, 0x200
	.4byte gRom_08125534
	.incbin "baserom.gba", 0x57E30, 0x4
	.4byte gData_080BB8C0
	.4byte gRom_08125B08
	.incbin "baserom.gba", 0x57E3C, 0x8
	.4byte gRom_08125D08
	.incbin "baserom.gba", 0x57E48, 0x8
	.4byte _080594A4 + 1
	.incbin "baserom.gba", 0x57E54, 0x38
	.global gRom_08057E8C
gRom_08057E8C:
	.incbin "baserom.gba", 0x57E8C, 0x98
	.4byte gRom_0810B69C
	.4byte gRom_0810B86C
	.incbin "baserom.gba", 0x57F2C, 0x8
	.4byte gRom_0810BF18
	.incbin "baserom.gba", 0x57F38, 0x8
	.global gRom_08057F40
gRom_08057F40:
	.incbin "baserom.gba", 0x57F40, 0x4C
	.global gRom_08057F8C
gRom_08057F8C:
	.incbin "baserom.gba", 0x57F8C, 0x3C
	.4byte gRom_08124DBC
	.global gRom_08057FCC
gRom_08057FCC:
	.incbin "baserom.gba", 0x57FCC, 0x5C
	.global gRom_08058028
gRom_08058028:
	.incbin "baserom.gba", 0x58028, 0x64
	.global gRom_0805808C
gRom_0805808C:
	.incbin "baserom.gba", 0x5808C, 0x5C
	.4byte gRom_08124DBC
	.incbin "baserom.gba", 0x580EC, 0x8
	.4byte _08059300 + 1
	.incbin "baserom.gba", 0x580F8, 0x4
	.global gRom_080580FC
gRom_080580FC:
	.incbin "baserom.gba", 0x580FC, 0x5C
	.global gRom_08058158
gRom_08058158:
	.incbin "baserom.gba", 0x58158, 0x50
	.4byte gRom_08124DBC
	.incbin "baserom.gba", 0x581AC, 0x8
	.global gRom_080581B4
gRom_080581B4:
	.incbin "baserom.gba", 0x581B4, 0x20
	.4byte _08059300 + 1
	.incbin "baserom.gba", 0x581D8, 0x4
	.global gRom_080581DC
gRom_080581DC:
	.incbin "baserom.gba", 0x581DC, 0xB0
	.4byte gRom_08124DBC
	.incbin "baserom.gba", 0x58290, 0x8
	.4byte _08059300 + 1
	.incbin "baserom.gba", 0x5829C, 0x4
	.global gRom_080582A0
gRom_080582A0:
	.incbin "baserom.gba", 0x582A0, 0x24
	.global gRom_080582C4
gRom_080582C4:
	.incbin "baserom.gba", 0x582C4, 0x13C
	.global gRom_08058400
gRom_08058400:
	.incbin "baserom.gba", 0x58400, 0x70
	.4byte gRom_0810CADC
	.4byte gData_080BB8C0
	.4byte gRom_08112180
	.incbin "baserom.gba", 0x5847C, 0x4
	.4byte gRom_08113180
	.incbin "baserom.gba", 0x58484, 0x14
	.global gRom_08058498
gRom_08058498:
	.incbin "baserom.gba", 0x58498, 0x16C
	.global gRom_08058604
gRom_08058604:
	.incbin "baserom.gba", 0x58604, 0x94
	.4byte gRom_0810B69C
	.4byte gRom_0810B86C
	.incbin "baserom.gba", 0x586A0, 0x8
	.4byte gRom_0810BF18
	.incbin "baserom.gba", 0x586AC, 0x8
	.global gRom_080586B4
gRom_080586B4:
	.incbin "baserom.gba", 0x586B4, 0x7C
	.global gRom_08058730
gRom_08058730:
	.incbin "baserom.gba", 0x58730, 0x94
	.4byte gRom_0810B69C
	.4byte gRom_0810B86C
	.incbin "baserom.gba", 0x587CC, 0x8
	.4byte gRom_0810BF18
	.incbin "baserom.gba", 0x587D8, 0x8
	.global gRom_080587E0
gRom_080587E0:
	.incbin "baserom.gba", 0x587E0, 0x5C
	.global gRom_0805883C
gRom_0805883C:
	.incbin "baserom.gba", 0x5883C, 0x28
	.global gRom_08058864
gRom_08058864:
	.incbin "baserom.gba", 0x58864, 0x28
	.global gRom_0805888C
gRom_0805888C:
	.incbin "baserom.gba", 0x5888C, 0x60
	.global gRom_080588EC
gRom_080588EC:
	.incbin "baserom.gba", 0x588EC, 0x21C
	.4byte gRom_0810B69C
	.4byte gRom_0810B86C
	.incbin "baserom.gba", 0x58B10, 0x8
	.4byte gRom_0810BF18
	.incbin "baserom.gba", 0x58B1C, 0x8
	.global gRom_08058B24
gRom_08058B24:
	.incbin "baserom.gba", 0x58B24, 0x60
	.global gRom_08058B84
gRom_08058B84:
	.incbin "baserom.gba", 0x58B84, 0x48
	.global gRom_08058BCC
gRom_08058BCC:
	.incbin "baserom.gba", 0x58BCC, 0x12C
	.global gRom_08058CF8
gRom_08058CF8:
	.incbin "baserom.gba", 0x58CF8, 0x8C
	.global gRom_08058D84
gRom_08058D84:
	.incbin "baserom.gba", 0x58D84, 0x8C
	.global gRom_08058E10
gRom_08058E10:
	.incbin "baserom.gba", 0x58E10, 0x7C
	.4byte gRom_0810CADC
	.4byte gData_080BB8C0
	.4byte gRom_08112180
	.incbin "baserom.gba", 0x58E98, 0x4
	.4byte gRom_08113180
	.incbin "baserom.gba", 0x58EA0, 0x14
	.global gRom_08058EB4
gRom_08058EB4:
	.incbin "baserom.gba", 0x58EB4, 0x198
	.global gRom_0805904C
gRom_0805904C:
	.incbin "baserom.gba", 0x5904C, 0x14
	.global _08059060
	.thumb_func
_08059060:
	.incbin "baserom.gba", 0x59060, 0x13C
	.global _0805919C
	.thumb_func
_0805919C:
	.incbin "baserom.gba", 0x5919C, 0x3C
	.global _080591D8
	.thumb_func
_080591D8:
	.incbin "baserom.gba", 0x591D8, 0x6C
	.4byte gRom_080996D8
	.incbin "baserom.gba", 0x59248, 0x2C
	.global _08059274
	.thumb_func
_08059274:
	.incbin "baserom.gba", 0x59274, 0x8C
	.global _08059300
	.thumb_func
_08059300:
	.incbin "baserom.gba", 0x59300, 0x60
	.4byte gRom_080996EC
	.incbin "baserom.gba", 0x59364, 0x40
