@ Unmatched ROM head 0x08000000..0x0802B8BB
	.section .rodata,"a",%progbits
	.balign 2
	.global gBaserom
gBaserom:
	.global gRom_08000000
gRom_08000000:
	.incbin "baserom.gba", 0x0, 0x8
	.global gRom_08000008
gRom_08000008:
	.incbin "baserom.gba", 0x8, 0x28
	.global gRom_08000030
gRom_08000030:
	.incbin "baserom.gba", 0x30, 0x50
	.global gRom_08000080
gRom_08000080:
	.incbin "baserom.gba", 0x80, 0x80
	.global gRom_08000100
gRom_08000100:
	.incbin "baserom.gba", 0x100, 0x10
	.global _08000110
	.thumb_func
_08000110:
	.incbin "baserom.gba", 0x110, 0x28
	.global gRom_08000138
gRom_08000138:
	.incbin "baserom.gba", 0x138, 0xC
	.global gRom_08000144
gRom_08000144:
	.incbin "baserom.gba", 0x144, 0x10
	.global _08000154
	.thumb_func
_08000154:
	.incbin "baserom.gba", 0x154, 0xAC
	.global _08000200
	.thumb_func
_08000200:
	.incbin "baserom.gba", 0x200, 0x44
	.global gRom_08000244
gRom_08000244:
	.incbin "baserom.gba", 0x244, 0x8
	.global gRom_0800024C
gRom_0800024C:
	.incbin "baserom.gba", 0x24C, 0xC
	.4byte gRom_083D3384
	.4byte _08045AF8 + 1
	.incbin "baserom.gba", 0x260, 0x4
	.global gRom_08000264
gRom_08000264:
	.incbin "baserom.gba", 0x264, 0x10
	.4byte gRom_08000298
	.incbin "baserom.gba", 0x278, 0x14
	.4byte gRom_080002A8
	.incbin "baserom.gba", 0x290, 0x8
	.global gRom_08000298
gRom_08000298:
	.incbin "baserom.gba", 0x298, 0x10
	.global gRom_080002A8
gRom_080002A8:
	.incbin "baserom.gba", 0x2A8, 0x24
	.4byte gRom_080002F0
	.incbin "baserom.gba", 0x2D0, 0x14
	.4byte gRom_08000300
	.incbin "baserom.gba", 0x2E8, 0x8
	.global gRom_080002F0
gRom_080002F0:
	.incbin "baserom.gba", 0x2F0, 0xC
	.global _080002FC
	.thumb_func
_080002FC:
	.incbin "baserom.gba", 0x2FC, 0x4
	.global gRom_08000300
gRom_08000300:
	.incbin "baserom.gba", 0x300, 0x14
	.global gRom_08000314
gRom_08000314:
	.incbin "baserom.gba", 0x314, 0x10
	.4byte gRom_08000348
	.incbin "baserom.gba", 0x328, 0x14
	.4byte gRom_08000358
	.incbin "baserom.gba", 0x340, 0x8
	.global gRom_08000348
gRom_08000348:
	.incbin "baserom.gba", 0x348, 0x10
	.global gRom_08000358
gRom_08000358:
	.incbin "baserom.gba", 0x358, 0x14
	.global gRom_0800036C
gRom_0800036C:
	.incbin "baserom.gba", 0x36C, 0x10
	.4byte gRom_080003A0
	.incbin "baserom.gba", 0x380, 0x14
	.4byte gRom_080003B0
	.incbin "baserom.gba", 0x398, 0x8
	.global gRom_080003A0
gRom_080003A0:
	.incbin "baserom.gba", 0x3A0, 0x10
	.global gRom_080003B0
gRom_080003B0:
	.incbin "baserom.gba", 0x3B0, 0x24
	.4byte gRom_080003F8
	.incbin "baserom.gba", 0x3D8, 0x14
	.4byte gRom_08000408
	.incbin "baserom.gba", 0x3F0, 0x8
	.global gRom_080003F8
gRom_080003F8:
	.incbin "baserom.gba", 0x3F8, 0x8
	.global gRom_08000400
gRom_08000400:
	.incbin "baserom.gba", 0x400, 0x8
	.global gRom_08000408
gRom_08000408:
	.incbin "baserom.gba", 0x408, 0x8
	.global _08000410
	.thumb_func
_08000410:
	.incbin "baserom.gba", 0x410, 0xC
	.global gRom_0800041C
gRom_0800041C:
	.incbin "baserom.gba", 0x41C, 0xC
	.4byte gRom_08000490
	.incbin "baserom.gba", 0x42C, 0x8
	.4byte gRom_080004A0
	.incbin "baserom.gba", 0x438, 0x8
	.4byte gRom_080004B0
	.incbin "baserom.gba", 0x444, 0x18
	.global _0800045C
	.thumb_func
_0800045C:
	.incbin "baserom.gba", 0x45C, 0x30
	.4byte gRom_080004C0
	.global gRom_08000490
gRom_08000490:
	.incbin "baserom.gba", 0x490, 0x10
	.global gRom_080004A0
gRom_080004A0:
	.incbin "baserom.gba", 0x4A0, 0x10
	.global gRom_080004B0
gRom_080004B0:
	.incbin "baserom.gba", 0x4B0, 0x10
	.global gRom_080004C0
gRom_080004C0:
	.incbin "baserom.gba", 0x4C0, 0x10
	.global gRom_080004D0
gRom_080004D0:
	.4byte gRom_08000534
	.incbin "baserom.gba", 0x4D4, 0x38
	.global gRom_0800050C
gRom_0800050C:
	.incbin "baserom.gba", 0x50C, 0x24
	.4byte gRom_08000544
	.global gRom_08000534
gRom_08000534:
	.incbin "baserom.gba", 0x534, 0x10
	.global gRom_08000544
gRom_08000544:
	.incbin "baserom.gba", 0x544, 0x14
	.global gRom_08000558
gRom_08000558:
	.4byte gRom_080005FC
	.4byte gRom_0800060C
	.4byte gRom_0800061C
	.4byte gRom_0800062C
	.incbin "baserom.gba", 0x568, 0x20
	.global gRom_08000588
gRom_08000588:
	.incbin "baserom.gba", 0x588, 0x10
	.global _08000598
	.thumb_func
_08000598:
	.incbin "baserom.gba", 0x598, 0x34
	.global gRom_080005CC
gRom_080005CC:
	.incbin "baserom.gba", 0x5CC, 0x10
	.global _080005DC
	.thumb_func
_080005DC:
	.incbin "baserom.gba", 0x5DC, 0x18
	.4byte gRom_0800063C
	.4byte gRom_0800064C
	.global gRom_080005FC
gRom_080005FC:
	.incbin "baserom.gba", 0x5FC, 0x4
	.global gRom_08000600
gRom_08000600:
	.incbin "baserom.gba", 0x600, 0x4
	.global _08000604
	.thumb_func
_08000604:
	.incbin "baserom.gba", 0x604, 0x8
	.global gRom_0800060C
gRom_0800060C:
	.incbin "baserom.gba", 0x60C, 0x4
	.global gRom_08000610
gRom_08000610:
	.incbin "baserom.gba", 0x610, 0xC
	.global gRom_0800061C
gRom_0800061C:
	.incbin "baserom.gba", 0x61C, 0x10
	.global gRom_0800062C
gRom_0800062C:
	.incbin "baserom.gba", 0x62C, 0x4
	.global gRom_08000630
gRom_08000630:
	.incbin "baserom.gba", 0x630, 0xC
	.global gRom_0800063C
gRom_0800063C:
	.incbin "baserom.gba", 0x63C, 0x10
	.global gRom_0800064C
gRom_0800064C:
	.incbin "baserom.gba", 0x64C, 0x4
	.global gRom_08000650
gRom_08000650:
	.incbin "baserom.gba", 0x650, 0xC
	.global gRom_0800065C
gRom_0800065C:
	.4byte gRom_080006DC
	.4byte gRom_080006EC
	.4byte gRom_080006FC
	.4byte gRom_0800070C
	.global _0800066C
	.thumb_func
_0800066C:
	.incbin "baserom.gba", 0x66C, 0x2C
	.global _08000698
	.thumb_func
_08000698:
	.incbin "baserom.gba", 0x698, 0x34
	.global _080006CC
	.thumb_func
_080006CC:
	.incbin "baserom.gba", 0x6CC, 0x8
	.4byte gRom_0800071C
	.4byte gRom_0800072C
	.global gRom_080006DC
gRom_080006DC:
	.incbin "baserom.gba", 0x6DC, 0x10
	.global gRom_080006EC
gRom_080006EC:
	.incbin "baserom.gba", 0x6EC, 0x10
	.global gRom_080006FC
gRom_080006FC:
	.incbin "baserom.gba", 0x6FC, 0x4
	.global gRom_08000700
gRom_08000700:
	.incbin "baserom.gba", 0x700, 0xC
	.global gRom_0800070C
gRom_0800070C:
	.incbin "baserom.gba", 0x70C, 0x4
	.global gRom_08000710
gRom_08000710:
	.incbin "baserom.gba", 0x710, 0xC
	.global gRom_0800071C
gRom_0800071C:
	.incbin "baserom.gba", 0x71C, 0x4
	.global gRom_08000720
gRom_08000720:
	.incbin "baserom.gba", 0x720, 0xC
	.global gRom_0800072C
gRom_0800072C:
	.incbin "baserom.gba", 0x72C, 0x10
	.global gRom_0800073C
gRom_0800073C:
	.4byte gRom_080007C8
	.global gRom_08000740
gRom_08000740:
	.4byte gRom_080007D8
	.4byte gRom_080007E8
	.4byte gRom_080007F8
	.incbin "baserom.gba", 0x74C, 0x4C
	.global _08000798
	.thumb_func
_08000798:
	.incbin "baserom.gba", 0x798, 0x28
	.4byte gRom_08000808
	.4byte gRom_08000818
	.global gRom_080007C8
gRom_080007C8:
	.incbin "baserom.gba", 0x7C8, 0x4
	.global gRom_080007CC
gRom_080007CC:
	.incbin "baserom.gba", 0x7CC, 0x4
	.global gRom_080007D0
gRom_080007D0:
	.incbin "baserom.gba", 0x7D0, 0x8
	.global gRom_080007D8
gRom_080007D8:
	.incbin "baserom.gba", 0x7D8, 0x10
	.global gRom_080007E8
gRom_080007E8:
	.incbin "baserom.gba", 0x7E8, 0x10
	.global gRom_080007F8
gRom_080007F8:
	.incbin "baserom.gba", 0x7F8, 0x8
	.global _08000800
	.thumb_func
_08000800:
	.incbin "baserom.gba", 0x800, 0x8
	.global gRom_08000808
gRom_08000808:
	.incbin "baserom.gba", 0x808, 0x10
	.global gRom_08000818
gRom_08000818:
	.incbin "baserom.gba", 0x818, 0x10
	.global gRom_08000828
gRom_08000828:
	.4byte gRom_080008A0
	.4byte gRom_080008B0
	.4byte gRom_080008C0
	.4byte gRom_080008D0
	.incbin "baserom.gba", 0x838, 0x1C
	.global gRom_08000854
gRom_08000854:
	.incbin "baserom.gba", 0x854, 0x44
	.4byte gRom_080008E0
	.4byte gRom_080008F0
	.global gRom_080008A0
gRom_080008A0:
	.incbin "baserom.gba", 0x8A0, 0x10
	.global gRom_080008B0
gRom_080008B0:
	.incbin "baserom.gba", 0x8B0, 0x10
	.global gRom_080008C0
gRom_080008C0:
	.incbin "baserom.gba", 0x8C0, 0x10
	.global gRom_080008D0
gRom_080008D0:
	.incbin "baserom.gba", 0x8D0, 0x10
	.global gRom_080008E0
gRom_080008E0:
	.incbin "baserom.gba", 0x8E0, 0x10
	.global gRom_080008F0
gRom_080008F0:
	.incbin "baserom.gba", 0x8F0, 0x10
	.global gRom_08000900
gRom_08000900:
	.4byte gRom_08000970
	.4byte gRom_08000980
	.global gRom_08000908
gRom_08000908:
	.4byte gRom_08000990
	.4byte gRom_080009A0
	.incbin "baserom.gba", 0x910, 0x34
	.global gRom_08000944
gRom_08000944:
	.incbin "baserom.gba", 0x944, 0x24
	.4byte gRom_080009B0
	.4byte gRom_080009C0
	.global gRom_08000970
gRom_08000970:
	.incbin "baserom.gba", 0x970, 0x10
	.global gRom_08000980
gRom_08000980:
	.incbin "baserom.gba", 0x980, 0x10
	.global gRom_08000990
gRom_08000990:
	.incbin "baserom.gba", 0x990, 0x10
	.global gRom_080009A0
gRom_080009A0:
	.incbin "baserom.gba", 0x9A0, 0x10
	.global gRom_080009B0
gRom_080009B0:
	.incbin "baserom.gba", 0x9B0, 0x10
	.global gRom_080009C0
gRom_080009C0:
	.incbin "baserom.gba", 0x9C0, 0x10
	.global gRom_080009D0
gRom_080009D0:
	.incbin "baserom.gba", 0x9D0, 0x10
	.4byte gRom_08000A40
	.4byte gRom_08000A50
	.4byte gRom_08000A60
	.4byte gRom_08000A70
	.incbin "baserom.gba", 0x9F0, 0x48
	.4byte gRom_08000A80
	.4byte gRom_08000A90
	.global gRom_08000A40
gRom_08000A40:
	.incbin "baserom.gba", 0xA40, 0x10
	.global gRom_08000A50
gRom_08000A50:
	.incbin "baserom.gba", 0xA50, 0x10
	.global gRom_08000A60
gRom_08000A60:
	.incbin "baserom.gba", 0xA60, 0x10
	.global gRom_08000A70
gRom_08000A70:
	.incbin "baserom.gba", 0xA70, 0x10
	.global gRom_08000A80
gRom_08000A80:
	.incbin "baserom.gba", 0xA80, 0x10
	.global gRom_08000A90
gRom_08000A90:
	.incbin "baserom.gba", 0xA90, 0x10
	.global gRom_08000AA0
gRom_08000AA0:
	.4byte gRom_08000AC8
	.4byte gRom_08000AD8
	.4byte gRom_08000AE8
	.4byte gRom_08000AF8
	.4byte gRom_08000B08
	.4byte gRom_08000B18
	.4byte gRom_08000B28
	.4byte gRom_08000B38
	.4byte gRom_08000B48
	.4byte gRom_08000B58
	.global gRom_08000AC8
gRom_08000AC8:
	.incbin "baserom.gba", 0xAC8, 0x10
	.global gRom_08000AD8
gRom_08000AD8:
	.incbin "baserom.gba", 0xAD8, 0x10
	.global gRom_08000AE8
gRom_08000AE8:
	.incbin "baserom.gba", 0xAE8, 0x10
	.global gRom_08000AF8
gRom_08000AF8:
	.incbin "baserom.gba", 0xAF8, 0x8
	.global gRom_08000B00
gRom_08000B00:
	.incbin "baserom.gba", 0xB00, 0x8
	.global gRom_08000B08
gRom_08000B08:
	.incbin "baserom.gba", 0xB08, 0x10
	.global gRom_08000B18
gRom_08000B18:
	.incbin "baserom.gba", 0xB18, 0x10
	.global gRom_08000B28
gRom_08000B28:
	.incbin "baserom.gba", 0xB28, 0x10
	.global gRom_08000B38
gRom_08000B38:
	.incbin "baserom.gba", 0xB38, 0x10
	.global gRom_08000B48
gRom_08000B48:
	.incbin "baserom.gba", 0xB48, 0x8
	.global gRom_08000B50
gRom_08000B50:
	.incbin "baserom.gba", 0xB50, 0x8
	.global gRom_08000B58
gRom_08000B58:
	.incbin "baserom.gba", 0xB58, 0x10
	.global gRom_08000B68
gRom_08000B68:
	.incbin "baserom.gba", 0xB68, 0x18
	.4byte gRom_08000BB8
	.incbin "baserom.gba", 0xB84, 0x18
	.4byte gRom_08000BC8
	.incbin "baserom.gba", 0xBA0, 0x18
	.global gRom_08000BB8
gRom_08000BB8:
	.incbin "baserom.gba", 0xBB8, 0x10
	.global gRom_08000BC8
gRom_08000BC8:
	.incbin "baserom.gba", 0xBC8, 0x10
	.global gRom_08000BD8
gRom_08000BD8:
	.incbin "baserom.gba", 0xBD8, 0x4
	.global _08000BDC
	.thumb_func
_08000BDC:
	.incbin "baserom.gba", 0xBDC, 0x10
	.4byte gRom_08000C08
	.incbin "baserom.gba", 0xBF0, 0x8
	.4byte gRom_08000C18
	.incbin "baserom.gba", 0xBFC, 0x4
	.global gRom_08000C00
gRom_08000C00:
	.incbin "baserom.gba", 0xC00, 0x4
	.4byte gRom_08000C28
	.global gRom_08000C08
gRom_08000C08:
	.incbin "baserom.gba", 0xC08, 0x8
	.global _08000C10
	.thumb_func
_08000C10:
	.incbin "baserom.gba", 0xC10, 0x8
	.global gRom_08000C18
gRom_08000C18:
	.incbin "baserom.gba", 0xC18, 0x10
	.global gRom_08000C28
gRom_08000C28:
	.incbin "baserom.gba", 0xC28, 0xC
	.global gRom_08000C34
gRom_08000C34:
	.incbin "baserom.gba", 0xC34, 0x8
	.global gRom_08000C3C
gRom_08000C3C:
	.incbin "baserom.gba", 0xC3C, 0x14
	.4byte gRom_08000C74
	.incbin "baserom.gba", 0xC54, 0x20
	.global gRom_08000C74
gRom_08000C74:
	.incbin "baserom.gba", 0xC74, 0x10
	.global gRom_08000C84
gRom_08000C84:
	.incbin "baserom.gba", 0xC84, 0x18
	.4byte gRom_08000CE8
	.incbin "baserom.gba", 0xCA0, 0x8
	.4byte gRom_08000CF8
	.4byte gRom_08000D08
	.incbin "baserom.gba", 0xCB0, 0x4
	.4byte gRom_08000D18
	.incbin "baserom.gba", 0xCB8, 0x24
	.4byte gRom_08000D28
	.incbin "baserom.gba", 0xCE0, 0x4
	.4byte gRom_08000D38
	.global gRom_08000CE8
gRom_08000CE8:
	.incbin "baserom.gba", 0xCE8, 0x10
	.global gRom_08000CF8
gRom_08000CF8:
	.incbin "baserom.gba", 0xCF8, 0x10
	.global gRom_08000D08
gRom_08000D08:
	.incbin "baserom.gba", 0xD08, 0x10
	.global gRom_08000D18
gRom_08000D18:
	.incbin "baserom.gba", 0xD18, 0x10
	.global gRom_08000D28
gRom_08000D28:
	.incbin "baserom.gba", 0xD28, 0x10
	.global gRom_08000D38
gRom_08000D38:
	.incbin "baserom.gba", 0xD38, 0x14
	.global gRom_08000D4C
gRom_08000D4C:
	.incbin "baserom.gba", 0xD4C, 0x8
	.4byte gRom_08000D9C
	.incbin "baserom.gba", 0xD58, 0x2C
	.4byte gRom_08000DAC
	.incbin "baserom.gba", 0xD88, 0x10
	.4byte gRom_08000DBC
	.global gRom_08000D9C
gRom_08000D9C:
	.incbin "baserom.gba", 0xD9C, 0x10
	.global gRom_08000DAC
gRom_08000DAC:
	.incbin "baserom.gba", 0xDAC, 0x10
	.global gRom_08000DBC
gRom_08000DBC:
	.incbin "baserom.gba", 0xDBC, 0x14
	.global gRom_08000DD0
gRom_08000DD0:
	.incbin "baserom.gba", 0xDD0, 0x28
	.4byte gRom_08000E58
	.incbin "baserom.gba", 0xDFC, 0x8
	.4byte gRom_08000E68
	.incbin "baserom.gba", 0xE08, 0x8
	.global gRom_08000E10
gRom_08000E10:
	.incbin "baserom.gba", 0xE10, 0x3C
	.4byte gRom_08000E78
	.4byte gRom_08000E94
	.incbin "baserom.gba", 0xE54, 0x4
	.global gRom_08000E58
gRom_08000E58:
	.incbin "baserom.gba", 0xE58, 0x8
	.global gRom_08000E60
gRom_08000E60:
	.incbin "baserom.gba", 0xE60, 0x8
	.global gRom_08000E68
gRom_08000E68:
	.incbin "baserom.gba", 0xE68, 0x10
	.global gRom_08000E78
gRom_08000E78:
	.incbin "baserom.gba", 0xE78, 0x1C
	.global gRom_08000E94
gRom_08000E94:
	.incbin "baserom.gba", 0xE94, 0x1C
	.global gRom_08000EB0
gRom_08000EB0:
	.incbin "baserom.gba", 0xEB0, 0x4
	.global gRom_08000EB4
gRom_08000EB4:
	.incbin "baserom.gba", 0xEB4, 0x28
	.4byte gRom_08000F0C
	.incbin "baserom.gba", 0xEE0, 0x10
	.4byte gRom_08000F1C
	.4byte gRom_08000F34
	.incbin "baserom.gba", 0xEF8, 0x14
	.global gRom_08000F0C
gRom_08000F0C:
	.incbin "baserom.gba", 0xF0C, 0x10
	.global gRom_08000F1C
gRom_08000F1C:
	.incbin "baserom.gba", 0xF1C, 0x18
	.global gRom_08000F34
gRom_08000F34:
	.incbin "baserom.gba", 0xF34, 0x18
	.global gRom_08000F4C
gRom_08000F4C:
	.incbin "baserom.gba", 0xF4C, 0x4
	.global gRom_08000F50
gRom_08000F50:
	.incbin "baserom.gba", 0xF50, 0x18
	.4byte gRom_08000F70
	.4byte gRom_08000F80
	.global gRom_08000F70
gRom_08000F70:
	.incbin "baserom.gba", 0xF70, 0x10
	.global gRom_08000F80
gRom_08000F80:
	.incbin "baserom.gba", 0xF80, 0x10
	.global gRom_08000F90
gRom_08000F90:
	.incbin "baserom.gba", 0xF90, 0x14
	.4byte gRom_08000FC0
	.incbin "baserom.gba", 0xFA8, 0x8
	.4byte gRom_08000FD0
	.incbin "baserom.gba", 0xFB4, 0x4
	.4byte gRom_08000FE0
	.incbin "baserom.gba", 0xFBC, 0x4
	.global gRom_08000FC0
gRom_08000FC0:
	.incbin "baserom.gba", 0xFC0, 0x10
	.global gRom_08000FD0
gRom_08000FD0:
	.incbin "baserom.gba", 0xFD0, 0xC
	.global _08000FDC
	.thumb_func
_08000FDC:
	.incbin "baserom.gba", 0xFDC, 0x4
	.global gRom_08000FE0
gRom_08000FE0:
	.incbin "baserom.gba", 0xFE0, 0x14
	.global gRom_08000FF4
gRom_08000FF4:
	.incbin "baserom.gba", 0xFF4, 0x14
	.4byte gRom_08001034
	.global _0800100C
	.thumb_func
_0800100C:
	.incbin "baserom.gba", 0x100C, 0x28
	.global gRom_08001034
gRom_08001034:
	.incbin "baserom.gba", 0x1034, 0x10
	.global gRom_08001044
gRom_08001044:
	.incbin "baserom.gba", 0x1044, 0x18
	.4byte gRom_080010A8
	.incbin "baserom.gba", 0x1060, 0x8
	.4byte gRom_080010B8
	.4byte gRom_080010C8
	.incbin "baserom.gba", 0x1070, 0x4
	.4byte gRom_080010D8
	.incbin "baserom.gba", 0x1078, 0x24
	.4byte gRom_080010E8
	.incbin "baserom.gba", 0x10A0, 0x4
	.4byte gRom_080010F8
	.global gRom_080010A8
gRom_080010A8:
	.incbin "baserom.gba", 0x10A8, 0x10
	.global gRom_080010B8
gRom_080010B8:
	.incbin "baserom.gba", 0x10B8, 0x10
	.global gRom_080010C8
gRom_080010C8:
	.incbin "baserom.gba", 0x10C8, 0x10
	.global gRom_080010D8
gRom_080010D8:
	.incbin "baserom.gba", 0x10D8, 0x10
	.global gRom_080010E8
gRom_080010E8:
	.incbin "baserom.gba", 0x10E8, 0x10
	.global gRom_080010F8
gRom_080010F8:
	.incbin "baserom.gba", 0x10F8, 0x14
	.global gRom_0800110C
gRom_0800110C:
	.incbin "baserom.gba", 0x110C, 0x4
	.global _08001110
	.thumb_func
_08001110:
	.incbin "baserom.gba", 0x1110, 0x2C
	.4byte gRom_0800115C
	.incbin "baserom.gba", 0x1140, 0x8
	.4byte gRom_0800116C
	.incbin "baserom.gba", 0x114C, 0xC
	.4byte gRom_0800117C
	.global gRom_0800115C
gRom_0800115C:
	.incbin "baserom.gba", 0x115C, 0x4
	.global gRom_08001160
gRom_08001160:
	.incbin "baserom.gba", 0x1160, 0xC
	.global gRom_0800116C
gRom_0800116C:
	.incbin "baserom.gba", 0x116C, 0x10
	.global gRom_0800117C
gRom_0800117C:
	.incbin "baserom.gba", 0x117C, 0x14
	.global gRom_08001190
gRom_08001190:
	.incbin "baserom.gba", 0x1190, 0x28
	.4byte gRom_0800121C
	.incbin "baserom.gba", 0x11BC, 0x8
	.4byte gRom_0800122C
	.incbin "baserom.gba", 0x11C8, 0x44
	.4byte gRom_0800123C
	.4byte gRom_08001258
	.incbin "baserom.gba", 0x1214, 0x8
	.global gRom_0800121C
gRom_0800121C:
	.incbin "baserom.gba", 0x121C, 0x10
	.global gRom_0800122C
gRom_0800122C:
	.incbin "baserom.gba", 0x122C, 0x10
	.global gRom_0800123C
gRom_0800123C:
	.incbin "baserom.gba", 0x123C, 0x1C
	.global gRom_08001258
gRom_08001258:
	.incbin "baserom.gba", 0x1258, 0x1C
	.global gRom_08001274
gRom_08001274:
	.incbin "baserom.gba", 0x1274, 0x4
	.global gRom_08001278
gRom_08001278:
	.incbin "baserom.gba", 0x1278, 0x28
	.4byte gRom_080012D0
	.incbin "baserom.gba", 0x12A4, 0x10
	.4byte gRom_080012E0
	.4byte gRom_080012F8
	.incbin "baserom.gba", 0x12BC, 0x14
	.global gRom_080012D0
gRom_080012D0:
	.incbin "baserom.gba", 0x12D0, 0x10
	.global gRom_080012E0
gRom_080012E0:
	.incbin "baserom.gba", 0x12E0, 0x18
	.global gRom_080012F8
gRom_080012F8:
	.incbin "baserom.gba", 0x12F8, 0x18
	.global gRom_08001310
gRom_08001310:
	.incbin "baserom.gba", 0x1310, 0x4
	.global gRom_08001314
gRom_08001314:
	.4byte gRom_08001344
	.incbin "baserom.gba", 0x1318, 0x8
	.4byte gRom_08001354
	.incbin "baserom.gba", 0x1324, 0xC
	.global _08001330
	.thumb_func
_08001330:
	.incbin "baserom.gba", 0x1330, 0x10
	.4byte gRom_08001364
	.global gRom_08001344
gRom_08001344:
	.incbin "baserom.gba", 0x1344, 0x10
	.global gRom_08001354
gRom_08001354:
	.incbin "baserom.gba", 0x1354, 0x10
	.global gRom_08001364
gRom_08001364:
	.incbin "baserom.gba", 0x1364, 0x14
	.global gRom_08001378
gRom_08001378:
	.incbin "baserom.gba", 0x1378, 0x14
	.4byte gRom_080013B0
	.incbin "baserom.gba", 0x1390, 0x20
	.global gRom_080013B0
gRom_080013B0:
	.incbin "baserom.gba", 0x13B0, 0x10
	.global gRom_080013C0
gRom_080013C0:
	.incbin "baserom.gba", 0x13C0, 0x14
	.4byte gRom_08001424
	.incbin "baserom.gba", 0x13D8, 0x34
	.4byte gRom_08001434
	.4byte gRom_08001444
	.4byte gRom_08001454
	.4byte gRom_08001464
	.incbin "baserom.gba", 0x141C, 0x4
	.4byte gRom_08001474
	.global gRom_08001424
gRom_08001424:
	.incbin "baserom.gba", 0x1424, 0x10
	.global gRom_08001434
gRom_08001434:
	.incbin "baserom.gba", 0x1434, 0x10
	.global gRom_08001444
gRom_08001444:
	.incbin "baserom.gba", 0x1444, 0x10
	.global gRom_08001454
gRom_08001454:
	.incbin "baserom.gba", 0x1454, 0x10
	.global gRom_08001464
gRom_08001464:
	.incbin "baserom.gba", 0x1464, 0x10
	.global gRom_08001474
gRom_08001474:
	.incbin "baserom.gba", 0x1474, 0x14
	.global gRom_08001488
gRom_08001488:
	.incbin "baserom.gba", 0x1488, 0x14
	.4byte gRom_080014E4
	.incbin "baserom.gba", 0x14A0, 0x18
	.4byte gRom_080014F4
	.incbin "baserom.gba", 0x14BC, 0x24
	.4byte gRom_08001504
	.global gRom_080014E4
gRom_080014E4:
	.incbin "baserom.gba", 0x14E4, 0x10
	.global gRom_080014F4
gRom_080014F4:
	.incbin "baserom.gba", 0x14F4, 0x10
	.global gRom_08001504
gRom_08001504:
	.incbin "baserom.gba", 0x1504, 0x14
	.global gRom_08001518
gRom_08001518:
	.incbin "baserom.gba", 0x1518, 0x28
	.4byte gRom_080015A0
	.incbin "baserom.gba", 0x1544, 0x8
	.4byte gRom_080015B0
	.incbin "baserom.gba", 0x1550, 0x44
	.4byte gRom_080015C0
	.4byte gRom_080015DC
	.incbin "baserom.gba", 0x159C, 0x4
	.global gRom_080015A0
gRom_080015A0:
	.incbin "baserom.gba", 0x15A0, 0x10
	.global gRom_080015B0
gRom_080015B0:
	.incbin "baserom.gba", 0x15B0, 0x10
	.global gRom_080015C0
gRom_080015C0:
	.incbin "baserom.gba", 0x15C0, 0x1C
	.global gRom_080015DC
gRom_080015DC:
	.incbin "baserom.gba", 0x15DC, 0x1C
	.global gRom_080015F8
gRom_080015F8:
	.incbin "baserom.gba", 0x15F8, 0x28
	.4byte gRom_0800164C
	.4byte gRom_0800165C
	.incbin "baserom.gba", 0x1628, 0x24
	.global gRom_0800164C
gRom_0800164C:
	.incbin "baserom.gba", 0x164C, 0x10
	.global gRom_0800165C
gRom_0800165C:
	.incbin "baserom.gba", 0x165C, 0x10
	.global gRom_0800166C
gRom_0800166C:
	.incbin "baserom.gba", 0x166C, 0x28
	.4byte gRom_080016C4
	.incbin "baserom.gba", 0x1698, 0x20
	.4byte gRom_080016D4
	.incbin "baserom.gba", 0x16BC, 0x4
	.4byte gRom_080016EC
	.global gRom_080016C4
gRom_080016C4:
	.incbin "baserom.gba", 0x16C4, 0x10
	.global gRom_080016D4
gRom_080016D4:
	.incbin "baserom.gba", 0x16D4, 0x18
	.global gRom_080016EC
gRom_080016EC:
	.incbin "baserom.gba", 0x16EC, 0x18
	.global gRom_08001704
gRom_08001704:
	.4byte gRom_08001708
	.global gRom_08001708
gRom_08001708:
	.incbin "baserom.gba", 0x1708, 0x10
	.global gRom_08001718
gRom_08001718:
	.incbin "baserom.gba", 0x1718, 0x4
	.global gRom_0800171C
gRom_0800171C:
	.incbin "baserom.gba", 0x171C, 0x10
	.4byte gRom_08001748
	.4byte gRom_08001758
	.incbin "baserom.gba", 0x1734, 0x14
	.global gRom_08001748
gRom_08001748:
	.incbin "baserom.gba", 0x1748, 0x10
	.global gRom_08001758
gRom_08001758:
	.incbin "baserom.gba", 0x1758, 0x10
	.global gRom_08001768
gRom_08001768:
	.4byte gRom_08001798
	.incbin "baserom.gba", 0x176C, 0x8
	.4byte gRom_080017A8
	.incbin "baserom.gba", 0x1778, 0x1C
	.4byte gRom_080017B8
	.global gRom_08001798
gRom_08001798:
	.incbin "baserom.gba", 0x1798, 0x10
	.global gRom_080017A8
gRom_080017A8:
	.incbin "baserom.gba", 0x17A8, 0x10
	.global gRom_080017B8
gRom_080017B8:
	.incbin "baserom.gba", 0x17B8, 0x14
	.global gRom_080017CC
gRom_080017CC:
	.incbin "baserom.gba", 0x17CC, 0x14
	.4byte gRom_08001804
	.incbin "baserom.gba", 0x17E4, 0x20
	.global gRom_08001804
gRom_08001804:
	.incbin "baserom.gba", 0x1804, 0x10
	.global gRom_08001814
gRom_08001814:
	.incbin "baserom.gba", 0x1814, 0x14
	.4byte gRom_08001878
	.incbin "baserom.gba", 0x182C, 0x34
	.4byte gRom_08001888
	.4byte gRom_08001898
	.4byte gRom_080018A8
	.4byte gRom_080018B8
	.incbin "baserom.gba", 0x1870, 0x4
	.4byte gRom_080018C8
	.global gRom_08001878
gRom_08001878:
	.incbin "baserom.gba", 0x1878, 0x10
	.global gRom_08001888
gRom_08001888:
	.incbin "baserom.gba", 0x1888, 0x10
	.global gRom_08001898
gRom_08001898:
	.incbin "baserom.gba", 0x1898, 0x10
	.global gRom_080018A8
gRom_080018A8:
	.incbin "baserom.gba", 0x18A8, 0x10
	.global gRom_080018B8
gRom_080018B8:
	.incbin "baserom.gba", 0x18B8, 0x10
	.global gRom_080018C8
gRom_080018C8:
	.incbin "baserom.gba", 0x18C8, 0x14
	.global gRom_080018DC
gRom_080018DC:
	.incbin "baserom.gba", 0x18DC, 0x18
	.4byte gRom_08001930
	.incbin "baserom.gba", 0x18F8, 0x30
	.4byte gRom_08001940
	.4byte gRom_08001950
	.global gRom_08001930
gRom_08001930:
	.incbin "baserom.gba", 0x1930, 0x10
	.global gRom_08001940
gRom_08001940:
	.incbin "baserom.gba", 0x1940, 0x10
	.global gRom_08001950
gRom_08001950:
	.incbin "baserom.gba", 0x1950, 0x14
	.global gRom_08001964
gRom_08001964:
	.incbin "baserom.gba", 0x1964, 0x28
	.4byte gRom_080019EC
	.incbin "baserom.gba", 0x1990, 0x8
	.4byte gRom_080019FC
	.incbin "baserom.gba", 0x199C, 0x40
	.4byte gRom_08001A0C
	.4byte gRom_08001A28
	.incbin "baserom.gba", 0x19E4, 0x8
	.global gRom_080019EC
gRom_080019EC:
	.incbin "baserom.gba", 0x19EC, 0x10
	.global gRom_080019FC
gRom_080019FC:
	.incbin "baserom.gba", 0x19FC, 0x10
	.global gRom_08001A0C
gRom_08001A0C:
	.incbin "baserom.gba", 0x1A0C, 0x1C
	.global gRom_08001A28
gRom_08001A28:
	.incbin "baserom.gba", 0x1A28, 0x1C
	.global gRom_08001A44
gRom_08001A44:
	.incbin "baserom.gba", 0x1A44, 0x4
	.global gRom_08001A48
gRom_08001A48:
	.incbin "baserom.gba", 0x1A48, 0x4
	.global gRom_08001A4C
gRom_08001A4C:
	.incbin "baserom.gba", 0x1A4C, 0x28
	.4byte gRom_08001AA4
	.incbin "baserom.gba", 0x1A78, 0x10
	.4byte gRom_08001AB4
	.4byte gRom_08001ACC
	.incbin "baserom.gba", 0x1A90, 0x14
	.global gRom_08001AA4
gRom_08001AA4:
	.incbin "baserom.gba", 0x1AA4, 0x10
	.global gRom_08001AB4
gRom_08001AB4:
	.incbin "baserom.gba", 0x1AB4, 0x18
	.global gRom_08001ACC
gRom_08001ACC:
	.incbin "baserom.gba", 0x1ACC, 0x18
	.global gRom_08001AE4
gRom_08001AE4:
	.incbin "baserom.gba", 0x1AE4, 0x4
	.global gRom_08001AE8
gRom_08001AE8:
	.incbin "baserom.gba", 0x1AE8, 0x10
	.4byte gRom_08001B24
	.4byte gRom_08001B34
	.incbin "baserom.gba", 0x1B00, 0xC
	.4byte gRom_08001B44
	.incbin "baserom.gba", 0x1B10, 0xC
	.4byte gRom_08001B58
	.incbin "baserom.gba", 0x1B20, 0x4
	.global gRom_08001B24
gRom_08001B24:
	.incbin "baserom.gba", 0x1B24, 0x10
	.global gRom_08001B34
gRom_08001B34:
	.incbin "baserom.gba", 0x1B34, 0x10
	.global gRom_08001B44
gRom_08001B44:
	.incbin "baserom.gba", 0x1B44, 0x14
	.global gRom_08001B58
gRom_08001B58:
	.incbin "baserom.gba", 0x1B58, 0x10
	.global gRom_08001B68
gRom_08001B68:
	.incbin "baserom.gba", 0x1B68, 0x10
	.4byte gRom_08001BA8
	.incbin "baserom.gba", 0x1B7C, 0x10
	.4byte gRom_08001BB8
	.4byte gRom_08001BCC
	.4byte gRom_08001BE4
	.incbin "baserom.gba", 0x1B98, 0x10
	.global gRom_08001BA8
gRom_08001BA8:
	.incbin "baserom.gba", 0x1BA8, 0x10
	.global gRom_08001BB8
gRom_08001BB8:
	.incbin "baserom.gba", 0x1BB8, 0x14
	.global gRom_08001BCC
gRom_08001BCC:
	.incbin "baserom.gba", 0x1BCC, 0x18
	.global gRom_08001BE4
gRom_08001BE4:
	.incbin "baserom.gba", 0x1BE4, 0x14
	.global gRom_08001BF8
gRom_08001BF8:
	.incbin "baserom.gba", 0x1BF8, 0x18
	.4byte gRom_08001C34
	.incbin "baserom.gba", 0x1C14, 0x4
	.4byte gRom_08001C54
	.4byte gRom_08001C78
	.4byte gRom_08001C9C
	.incbin "baserom.gba", 0x1C24, 0x4
	.4byte gRom_08001CB0
	.4byte gRom_08001CC4
	.4byte gRom_08001CD8
	.global gRom_08001C34
gRom_08001C34:
	.incbin "baserom.gba", 0x1C34, 0x20
	.global gRom_08001C54
gRom_08001C54:
	.incbin "baserom.gba", 0x1C54, 0x24
	.global gRom_08001C78
gRom_08001C78:
	.incbin "baserom.gba", 0x1C78, 0x24
	.global gRom_08001C9C
gRom_08001C9C:
	.incbin "baserom.gba", 0x1C9C, 0x14
	.global gRom_08001CB0
gRom_08001CB0:
	.incbin "baserom.gba", 0x1CB0, 0x14
	.global gRom_08001CC4
gRom_08001CC4:
	.incbin "baserom.gba", 0x1CC4, 0x14
	.global gRom_08001CD8
gRom_08001CD8:
	.incbin "baserom.gba", 0x1CD8, 0x14
	.global gRom_08001CEC
gRom_08001CEC:
	.incbin "baserom.gba", 0x1CEC, 0x10
	.4byte gRom_08001D20
	.4byte gRom_08001D30
	.incbin "baserom.gba", 0x1D04, 0x8
	.4byte gRom_08001D40
	.4byte gRom_08001D58
	.4byte gRom_08001D6C
	.incbin "baserom.gba", 0x1D18, 0x4
	.4byte gRom_08001D80
	.global gRom_08001D20
gRom_08001D20:
	.incbin "baserom.gba", 0x1D20, 0x10
	.global gRom_08001D30
gRom_08001D30:
	.incbin "baserom.gba", 0x1D30, 0x10
	.global gRom_08001D40
gRom_08001D40:
	.incbin "baserom.gba", 0x1D40, 0x18
	.global gRom_08001D58
gRom_08001D58:
	.incbin "baserom.gba", 0x1D58, 0x14
	.global gRom_08001D6C
gRom_08001D6C:
	.incbin "baserom.gba", 0x1D6C, 0x14
	.global gRom_08001D80
gRom_08001D80:
	.incbin "baserom.gba", 0x1D80, 0x24
	.4byte gRom_08001DB8
	.4byte gRom_08001DC8
	.4byte gRom_08001DEC
	.incbin "baserom.gba", 0x1DB0, 0x4
	.4byte gRom_08001E00
	.global gRom_08001DB8
gRom_08001DB8:
	.incbin "baserom.gba", 0x1DB8, 0x10
	.global gRom_08001DC8
gRom_08001DC8:
	.incbin "baserom.gba", 0x1DC8, 0x24
	.global gRom_08001DEC
gRom_08001DEC:
	.incbin "baserom.gba", 0x1DEC, 0x14
	.global gRom_08001E00
gRom_08001E00:
	.incbin "baserom.gba", 0x1E00, 0x14
	.global gRom_08001E14
gRom_08001E14:
	.incbin "baserom.gba", 0x1E14, 0x4
	.4byte gRom_08001E50
	.incbin "baserom.gba", 0x1E1C, 0x14
	.4byte gRom_08001E64
	.4byte gRom_08001E74
	.4byte gRom_08001E88
	.4byte gRom_08001EAC
	.4byte gRom_08001ED0
	.4byte gRom_08001EE4
	.4byte gRom_08001EF8
	.4byte gRom_08001F0C
	.global gRom_08001E50
gRom_08001E50:
	.incbin "baserom.gba", 0x1E50, 0x14
	.global gRom_08001E64
gRom_08001E64:
	.incbin "baserom.gba", 0x1E64, 0x10
	.global gRom_08001E74
gRom_08001E74:
	.incbin "baserom.gba", 0x1E74, 0x14
	.global gRom_08001E88
gRom_08001E88:
	.incbin "baserom.gba", 0x1E88, 0x24
	.global gRom_08001EAC
gRom_08001EAC:
	.incbin "baserom.gba", 0x1EAC, 0x24
	.global gRom_08001ED0
gRom_08001ED0:
	.incbin "baserom.gba", 0x1ED0, 0x14
	.global gRom_08001EE4
gRom_08001EE4:
	.incbin "baserom.gba", 0x1EE4, 0x14
	.global gRom_08001EF8
gRom_08001EF8:
	.incbin "baserom.gba", 0x1EF8, 0x14
	.global gRom_08001F0C
gRom_08001F0C:
	.incbin "baserom.gba", 0x1F0C, 0x14
	.global gRom_08001F20
gRom_08001F20:
	.incbin "baserom.gba", 0x1F20, 0x10
	.4byte gRom_0800210C
	.4byte gRom_08002120
	.incbin "baserom.gba", 0x1F38, 0x140
	.4byte gRom_08002134
	.4byte gRom_08002144
	.4byte gRom_08002158
	.4byte gRom_0800216C
	.4byte gRom_08002180
	.incbin "baserom.gba", 0x208C, 0x80
	.global gRom_0800210C
gRom_0800210C:
	.incbin "baserom.gba", 0x210C, 0x14
	.global gRom_08002120
gRom_08002120:
	.incbin "baserom.gba", 0x2120, 0x14
	.global gRom_08002134
gRom_08002134:
	.incbin "baserom.gba", 0x2134, 0x10
	.global gRom_08002144
gRom_08002144:
	.incbin "baserom.gba", 0x2144, 0x14
	.global gRom_08002158
gRom_08002158:
	.incbin "baserom.gba", 0x2158, 0x14
	.global gRom_0800216C
gRom_0800216C:
	.incbin "baserom.gba", 0x216C, 0x14
	.global gRom_08002180
gRom_08002180:
	.incbin "baserom.gba", 0x2180, 0x10
	.global gRom_08002190
gRom_08002190:
	.incbin "baserom.gba", 0x2190, 0x40
	.4byte gRom_08002228
	.4byte gRom_0800224C
	.4byte gRom_0800225C
	.incbin "baserom.gba", 0x21DC, 0xC
	.4byte gRom_08002270
	.4byte gRom_08002284
	.4byte gRom_08002298
	.4byte gRom_080022B0
	.4byte gRom_080022C4
	.4byte gRom_080022D8
	.4byte gRom_080022F0
	.incbin "baserom.gba", 0x2204, 0x4
	.global gRom_08002208
gRom_08002208:
	.incbin "baserom.gba", 0x2208, 0x20
	.global gRom_08002228
gRom_08002228:
	.incbin "baserom.gba", 0x2228, 0x4
	.global _0800222C
	.thumb_func
_0800222C:
	.incbin "baserom.gba", 0x222C, 0x20
	.global gRom_0800224C
gRom_0800224C:
	.incbin "baserom.gba", 0x224C, 0x10
	.global gRom_0800225C
gRom_0800225C:
	.incbin "baserom.gba", 0x225C, 0x14
	.global gRom_08002270
gRom_08002270:
	.incbin "baserom.gba", 0x2270, 0x14
	.global gRom_08002284
gRom_08002284:
	.incbin "baserom.gba", 0x2284, 0x14
	.global gRom_08002298
gRom_08002298:
	.incbin "baserom.gba", 0x2298, 0x18
	.global gRom_080022B0
gRom_080022B0:
	.incbin "baserom.gba", 0x22B0, 0x14
	.global gRom_080022C4
gRom_080022C4:
	.incbin "baserom.gba", 0x22C4, 0x14
	.global gRom_080022D8
gRom_080022D8:
	.incbin "baserom.gba", 0x22D8, 0x18
	.global gRom_080022F0
gRom_080022F0:
	.incbin "baserom.gba", 0x22F0, 0x18
	.global gRom_08002308
gRom_08002308:
	.incbin "baserom.gba", 0x2308, 0x1C
	.4byte gRom_08002358
	.4byte gRom_0800236C
	.4byte gRom_08002380
	.4byte gRom_08002394
	.4byte gRom_080023A8
	.4byte gRom_080023BC
	.4byte gRom_080023D0
	.incbin "baserom.gba", 0x2340, 0x4
	.4byte gRom_080023E4
	.incbin "baserom.gba", 0x2348, 0x4
	.4byte gRom_080023F4
	.incbin "baserom.gba", 0x2350, 0x4
	.4byte gRom_08002404
	.global gRom_08002358
gRom_08002358:
	.incbin "baserom.gba", 0x2358, 0x14
	.global gRom_0800236C
gRom_0800236C:
	.incbin "baserom.gba", 0x236C, 0x14
	.global gRom_08002380
gRom_08002380:
	.incbin "baserom.gba", 0x2380, 0x14
	.global gRom_08002394
gRom_08002394:
	.incbin "baserom.gba", 0x2394, 0x14
	.global gRom_080023A8
gRom_080023A8:
	.incbin "baserom.gba", 0x23A8, 0x14
	.global gRom_080023BC
gRom_080023BC:
	.incbin "baserom.gba", 0x23BC, 0x14
	.global gRom_080023D0
gRom_080023D0:
	.incbin "baserom.gba", 0x23D0, 0x14
	.global gRom_080023E4
gRom_080023E4:
	.incbin "baserom.gba", 0x23E4, 0x10
	.global gRom_080023F4
gRom_080023F4:
	.incbin "baserom.gba", 0x23F4, 0x10
	.global gRom_08002404
gRom_08002404:
	.incbin "baserom.gba", 0x2404, 0x14
	.global gRom_08002418
gRom_08002418:
	.incbin "baserom.gba", 0x2418, 0x8
	.4byte gRom_0800250C
	.4byte gRom_08002520
	.4byte gRom_08002544
	.4byte gRom_08002558
	.4byte gRom_0800256C
	.4byte gRom_08002580
	.4byte gRom_08002594
	.4byte gRom_080025A8
	.4byte gRom_080025BC
	.4byte gRom_080025D0
	.4byte gRom_080025E4
	.4byte gRom_080025F4
	.4byte gRom_08002608
	.incbin "baserom.gba", 0x2454, 0x20
	.4byte gRom_0800261C
	.incbin "baserom.gba", 0x2478, 0x88
	.global gRom_08002500
gRom_08002500:
	.incbin "baserom.gba", 0x2500, 0x4
	.4byte gRom_08002640
	.incbin "baserom.gba", 0x2508, 0x4
	.global gRom_0800250C
gRom_0800250C:
	.incbin "baserom.gba", 0x250C, 0x14
	.global gRom_08002520
gRom_08002520:
	.incbin "baserom.gba", 0x2520, 0x24
	.global gRom_08002544
gRom_08002544:
	.incbin "baserom.gba", 0x2544, 0x14
	.global gRom_08002558
gRom_08002558:
	.incbin "baserom.gba", 0x2558, 0x14
	.global gRom_0800256C
gRom_0800256C:
	.incbin "baserom.gba", 0x256C, 0x14
	.global gRom_08002580
gRom_08002580:
	.incbin "baserom.gba", 0x2580, 0x14
	.global gRom_08002594
gRom_08002594:
	.incbin "baserom.gba", 0x2594, 0x14
	.global gRom_080025A8
gRom_080025A8:
	.incbin "baserom.gba", 0x25A8, 0x14
	.global gRom_080025BC
gRom_080025BC:
	.incbin "baserom.gba", 0x25BC, 0x14
	.global gRom_080025D0
gRom_080025D0:
	.incbin "baserom.gba", 0x25D0, 0x14
	.global gRom_080025E4
gRom_080025E4:
	.incbin "baserom.gba", 0x25E4, 0x10
	.global gRom_080025F4
gRom_080025F4:
	.incbin "baserom.gba", 0x25F4, 0x14
	.global gRom_08002608
gRom_08002608:
	.incbin "baserom.gba", 0x2608, 0x14
	.global gRom_0800261C
gRom_0800261C:
	.incbin "baserom.gba", 0x261C, 0x14
	.global gRom_08002630
gRom_08002630:
	.incbin "baserom.gba", 0x2630, 0x10
	.global gRom_08002640
gRom_08002640:
	.incbin "baserom.gba", 0x2640, 0x14
	.global gRom_08002654
gRom_08002654:
	.incbin "baserom.gba", 0x2654, 0x14
	.4byte gRom_080026B4
	.incbin "baserom.gba", 0x266C, 0x3C
	.4byte gRom_080026D8
	.incbin "baserom.gba", 0x26AC, 0x4
	.4byte gRom_080026F0
	.global gRom_080026B4
gRom_080026B4:
	.incbin "baserom.gba", 0x26B4, 0x24
	.global gRom_080026D8
gRom_080026D8:
	.incbin "baserom.gba", 0x26D8, 0x18
	.global gRom_080026F0
gRom_080026F0:
	.incbin "baserom.gba", 0x26F0, 0x18
	.global gRom_08002708
gRom_08002708:
	.incbin "baserom.gba", 0x2708, 0x18
	.4byte gRom_08002790
	.incbin "baserom.gba", 0x2724, 0x30
	.4byte gRom_080027A0
	.4byte gRom_080027B4
	.4byte gRom_080027C8
	.4byte gRom_080027DC
	.4byte gRom_080027F0
	.4byte gRom_08002804
	.incbin "baserom.gba", 0x276C, 0x8
	.4byte gRom_08002814
	.4byte gRom_08002828
	.4byte gRom_0800283C
	.incbin "baserom.gba", 0x2780, 0x4
	.4byte gRom_08002850
	.incbin "baserom.gba", 0x2788, 0x8
	.global gRom_08002790
gRom_08002790:
	.incbin "baserom.gba", 0x2790, 0x10
	.global gRom_080027A0
gRom_080027A0:
	.incbin "baserom.gba", 0x27A0, 0x14
	.global gRom_080027B4
gRom_080027B4:
	.incbin "baserom.gba", 0x27B4, 0x14
	.global gRom_080027C8
gRom_080027C8:
	.incbin "baserom.gba", 0x27C8, 0x14
	.global gRom_080027DC
gRom_080027DC:
	.incbin "baserom.gba", 0x27DC, 0x14
	.global gRom_080027F0
gRom_080027F0:
	.incbin "baserom.gba", 0x27F0, 0x14
	.global gRom_08002804
gRom_08002804:
	.incbin "baserom.gba", 0x2804, 0x10
	.global gRom_08002814
gRom_08002814:
	.incbin "baserom.gba", 0x2814, 0xC
	.global gRom_08002820
gRom_08002820:
	.incbin "baserom.gba", 0x2820, 0x8
	.global gRom_08002828
gRom_08002828:
	.incbin "baserom.gba", 0x2828, 0x14
	.global gRom_0800283C
gRom_0800283C:
	.incbin "baserom.gba", 0x283C, 0x14
	.global gRom_08002850
gRom_08002850:
	.incbin "baserom.gba", 0x2850, 0x14
	.global gRom_08002864
gRom_08002864:
	.incbin "baserom.gba", 0x2864, 0x14
	.4byte gRom_08002894
	.incbin "baserom.gba", 0x287C, 0x18
	.global gRom_08002894
gRom_08002894:
	.incbin "baserom.gba", 0x2894, 0x10
	.global gRom_080028A4
gRom_080028A4:
	.incbin "baserom.gba", 0x28A4, 0x24
	.4byte gRom_080028F8
	.4byte gRom_08002908
	.incbin "baserom.gba", 0x28D0, 0x4
	.4byte gRom_0800292C
	.4byte gRom_08002950
	.incbin "baserom.gba", 0x28DC, 0xC
	.4byte gRom_08002968
	.4byte gRom_0800297C
	.4byte gRom_08002990
	.4byte gRom_080029A8
	.global gRom_080028F8
gRom_080028F8:
	.incbin "baserom.gba", 0x28F8, 0x8
	.global gRom_08002900
gRom_08002900:
	.incbin "baserom.gba", 0x2900, 0x8
	.global gRom_08002908
gRom_08002908:
	.incbin "baserom.gba", 0x2908, 0x24
	.global gRom_0800292C
gRom_0800292C:
	.incbin "baserom.gba", 0x292C, 0x24
	.global gRom_08002950
gRom_08002950:
	.incbin "baserom.gba", 0x2950, 0x18
	.global gRom_08002968
gRom_08002968:
	.incbin "baserom.gba", 0x2968, 0x14
	.global gRom_0800297C
gRom_0800297C:
	.incbin "baserom.gba", 0x297C, 0x14
	.global gRom_08002990
gRom_08002990:
	.incbin "baserom.gba", 0x2990, 0x18
	.global gRom_080029A8
gRom_080029A8:
	.incbin "baserom.gba", 0x29A8, 0x18
	.global gRom_080029C0
gRom_080029C0:
	.incbin "baserom.gba", 0x29C0, 0xC
	.4byte gRom_080029FC
	.4byte gRom_08002A0C
	.4byte gRom_08002A30
	.incbin "baserom.gba", 0x29D8, 0xC
	.4byte gRom_08002A54
	.incbin "baserom.gba", 0x29E8, 0x4
	.4byte gRom_08002A6C
	.incbin "baserom.gba", 0x29F0, 0xC
	.global gRom_080029FC
gRom_080029FC:
	.incbin "baserom.gba", 0x29FC, 0x10
	.global gRom_08002A0C
gRom_08002A0C:
	.incbin "baserom.gba", 0x2A0C, 0x24
	.global gRom_08002A30
gRom_08002A30:
	.incbin "baserom.gba", 0x2A30, 0x24
	.global gRom_08002A54
gRom_08002A54:
	.incbin "baserom.gba", 0x2A54, 0x18
	.global gRom_08002A6C
gRom_08002A6C:
	.incbin "baserom.gba", 0x2A6C, 0x18
	.global gRom_08002A84
gRom_08002A84:
	.incbin "baserom.gba", 0x2A84, 0x14
	.4byte gRom_08002AB0
	.4byte gRom_08002AC0
	.incbin "baserom.gba", 0x2AA0, 0x4
	.4byte gRom_08002AD4
	.incbin "baserom.gba", 0x2AA8, 0x8
	.global gRom_08002AB0
gRom_08002AB0:
	.incbin "baserom.gba", 0x2AB0, 0x10
	.global gRom_08002AC0
gRom_08002AC0:
	.incbin "baserom.gba", 0x2AC0, 0x14
	.global gRom_08002AD4
gRom_08002AD4:
	.incbin "baserom.gba", 0x2AD4, 0x14
	.global gRom_08002AE8
gRom_08002AE8:
	.incbin "baserom.gba", 0x2AE8, 0x10
	.4byte gRom_08002B34
	.incbin "baserom.gba", 0x2AFC, 0x38
	.global gRom_08002B34
gRom_08002B34:
	.incbin "baserom.gba", 0x2B34, 0x10
	.global gRom_08002B44
gRom_08002B44:
	.incbin "baserom.gba", 0x2B44, 0x14
	.4byte gRom_08002B7C
	.incbin "baserom.gba", 0x2B5C, 0x8
	.4byte gRom_08002B8C
	.incbin "baserom.gba", 0x2B68, 0x4
	.4byte gRom_08002BA0
	.incbin "baserom.gba", 0x2B70, 0x8
	.4byte gRom_08002BB4
	.global gRom_08002B7C
gRom_08002B7C:
	.incbin "baserom.gba", 0x2B7C, 0x10
	.global gRom_08002B8C
gRom_08002B8C:
	.incbin "baserom.gba", 0x2B8C, 0x14
	.global gRom_08002BA0
gRom_08002BA0:
	.incbin "baserom.gba", 0x2BA0, 0x14
	.global gRom_08002BB4
gRom_08002BB4:
	.incbin "baserom.gba", 0x2BB4, 0x24
	.4byte gRom_08002C00
	.incbin "baserom.gba", 0x2BDC, 0x8
	.4byte gRom_08002C10
	.incbin "baserom.gba", 0x2BE8, 0x4
	.4byte gRom_08002C20
	.4byte gRom_08002C30
	.incbin "baserom.gba", 0x2BF4, 0x4
	.4byte gRom_08002C44
	.incbin "baserom.gba", 0x2BFC, 0x4
	.global gRom_08002C00
gRom_08002C00:
	.incbin "baserom.gba", 0x2C00, 0x10
	.global gRom_08002C10
gRom_08002C10:
	.incbin "baserom.gba", 0x2C10, 0x10
	.global gRom_08002C20
gRom_08002C20:
	.incbin "baserom.gba", 0x2C20, 0x10
	.global gRom_08002C30
gRom_08002C30:
	.incbin "baserom.gba", 0x2C30, 0x14
	.global gRom_08002C44
gRom_08002C44:
	.incbin "baserom.gba", 0x2C44, 0x34
	.4byte gRom_08002C94
	.4byte gRom_08002CA4
	.4byte gRom_08002CB4
	.incbin "baserom.gba", 0x2C84, 0x4
	.4byte gRom_08002CD0
	.4byte gRom_08002CF0
	.incbin "baserom.gba", 0x2C90, 0x4
	.global gRom_08002C94
gRom_08002C94:
	.incbin "baserom.gba", 0x2C94, 0x10
	.global gRom_08002CA4
gRom_08002CA4:
	.incbin "baserom.gba", 0x2CA4, 0x10
	.global gRom_08002CB4
gRom_08002CB4:
	.incbin "baserom.gba", 0x2CB4, 0x1C
	.global gRom_08002CD0
gRom_08002CD0:
	.incbin "baserom.gba", 0x2CD0, 0x20
	.global gRom_08002CF0
gRom_08002CF0:
	.incbin "baserom.gba", 0x2CF0, 0x24
	.global gRom_08002D14
gRom_08002D14:
	.incbin "baserom.gba", 0x2D14, 0x8
	.4byte gRom_08002D44
	.incbin "baserom.gba", 0x2D20, 0x4
	.4byte gRom_08002D58
	.incbin "baserom.gba", 0x2D28, 0x4
	.4byte gRom_08002D68
	.4byte gRom_08002D78
	.4byte gRom_08002D88
	.incbin "baserom.gba", 0x2D38, 0xC
	.global gRom_08002D44
gRom_08002D44:
	.incbin "baserom.gba", 0x2D44, 0x14
	.global gRom_08002D58
gRom_08002D58:
	.incbin "baserom.gba", 0x2D58, 0x10
	.global gRom_08002D68
gRom_08002D68:
	.incbin "baserom.gba", 0x2D68, 0x10
	.global gRom_08002D78
gRom_08002D78:
	.incbin "baserom.gba", 0x2D78, 0x10
	.global gRom_08002D88
gRom_08002D88:
	.incbin "baserom.gba", 0x2D88, 0x14
	.global gRom_08002D9C
gRom_08002D9C:
	.incbin "baserom.gba", 0x2D9C, 0x1C
	.4byte gRom_08002DFC
	.4byte gRom_08002E0C
	.incbin "baserom.gba", 0x2DC0, 0x14
	.4byte gRom_08002E1C
	.incbin "baserom.gba", 0x2DD8, 0x8
	.4byte gRom_08002E30
	.4byte gRom_08002E48
	.4byte gRom_08002E58
	.incbin "baserom.gba", 0x2DEC, 0x4
	.4byte gRom_08002E6C
	.incbin "baserom.gba", 0x2DF4, 0x4
	.4byte gRom_08002E80
	.global gRom_08002DFC
gRom_08002DFC:
	.incbin "baserom.gba", 0x2DFC, 0x10
	.global gRom_08002E0C
gRom_08002E0C:
	.incbin "baserom.gba", 0x2E0C, 0x10
	.global gRom_08002E1C
gRom_08002E1C:
	.incbin "baserom.gba", 0x2E1C, 0x14
	.global gRom_08002E30
gRom_08002E30:
	.incbin "baserom.gba", 0x2E30, 0x18
	.global gRom_08002E48
gRom_08002E48:
	.incbin "baserom.gba", 0x2E48, 0x10
	.global gRom_08002E58
gRom_08002E58:
	.incbin "baserom.gba", 0x2E58, 0x14
	.global gRom_08002E6C
gRom_08002E6C:
	.incbin "baserom.gba", 0x2E6C, 0x14
	.global gRom_08002E80
gRom_08002E80:
	.incbin "baserom.gba", 0x2E80, 0x2C
	.4byte gRom_08002EE0
	.incbin "baserom.gba", 0x2EB0, 0x4
	.4byte gRom_08002F04
	.4byte gRom_08002F40
	.incbin "baserom.gba", 0x2EBC, 0x8
	.4byte gRom_08002F60
	.4byte gRom_08002F7C
	.incbin "baserom.gba", 0x2ECC, 0x8
	.4byte gRom_08002F90
	.4byte gRom_08002FA4
	.4byte gRom_08002FB8
	.global gRom_08002EE0
gRom_08002EE0:
	.incbin "baserom.gba", 0x2EE0, 0x24
	.global gRom_08002F04
gRom_08002F04:
	.incbin "baserom.gba", 0x2F04, 0x3C
	.global gRom_08002F40
gRom_08002F40:
	.incbin "baserom.gba", 0x2F40, 0x20
	.global gRom_08002F60
gRom_08002F60:
	.incbin "baserom.gba", 0x2F60, 0x1C
	.global gRom_08002F7C
gRom_08002F7C:
	.incbin "baserom.gba", 0x2F7C, 0x14
	.global gRom_08002F90
gRom_08002F90:
	.incbin "baserom.gba", 0x2F90, 0x14
	.global gRom_08002FA4
gRom_08002FA4:
	.incbin "baserom.gba", 0x2FA4, 0x14
	.global gRom_08002FB8
gRom_08002FB8:
	.incbin "baserom.gba", 0x2FB8, 0x14
	.global gRom_08002FCC
gRom_08002FCC:
	.incbin "baserom.gba", 0x2FCC, 0x18
	.4byte gRom_08003004
	.4byte gRom_08003014
	.incbin "baserom.gba", 0x2FEC, 0x18
	.global gRom_08003004
gRom_08003004:
	.incbin "baserom.gba", 0x3004, 0x10
	.global gRom_08003014
gRom_08003014:
	.incbin "baserom.gba", 0x3014, 0x10
	.global gRom_08003024
gRom_08003024:
	.incbin "baserom.gba", 0x3024, 0x18
	.4byte gRom_080030A0
	.4byte gRom_080030B0
	.incbin "baserom.gba", 0x3044, 0x4
	.4byte gRom_080030C4
	.4byte gRom_080030D8
	.4byte gRom_080030EC
	.4byte gRom_08003100
	.4byte gRom_08003114
	.4byte gRom_08003128
	.4byte gRom_08003140
	.4byte gRom_08003158
	.incbin "baserom.gba", 0x3068, 0xC
	.4byte gRom_08003170
	.4byte gRom_08003184
	.4byte gRom_08003198
	.4byte gRom_080031AC
	.4byte gRom_080031C0
	.4byte gRom_080031D4
	.incbin "baserom.gba", 0x308C, 0x14
	.global gRom_080030A0
gRom_080030A0:
	.incbin "baserom.gba", 0x30A0, 0x10
	.global gRom_080030B0
gRom_080030B0:
	.incbin "baserom.gba", 0x30B0, 0x14
	.global gRom_080030C4
gRom_080030C4:
	.incbin "baserom.gba", 0x30C4, 0x14
	.global gRom_080030D8
gRom_080030D8:
	.incbin "baserom.gba", 0x30D8, 0x14
	.global gRom_080030EC
gRom_080030EC:
	.incbin "baserom.gba", 0x30EC, 0x14
	.global gRom_08003100
gRom_08003100:
	.incbin "baserom.gba", 0x3100, 0x14
	.global gRom_08003114
gRom_08003114:
	.incbin "baserom.gba", 0x3114, 0x14
	.global gRom_08003128
gRom_08003128:
	.incbin "baserom.gba", 0x3128, 0x18
	.global gRom_08003140
gRom_08003140:
	.incbin "baserom.gba", 0x3140, 0x18
	.global gRom_08003158
gRom_08003158:
	.incbin "baserom.gba", 0x3158, 0x18
	.global gRom_08003170
gRom_08003170:
	.incbin "baserom.gba", 0x3170, 0x14
	.global gRom_08003184
gRom_08003184:
	.incbin "baserom.gba", 0x3184, 0x14
	.global gRom_08003198
gRom_08003198:
	.incbin "baserom.gba", 0x3198, 0x14
	.global gRom_080031AC
gRom_080031AC:
	.incbin "baserom.gba", 0x31AC, 0x14
	.global gRom_080031C0
gRom_080031C0:
	.incbin "baserom.gba", 0x31C0, 0x14
	.global gRom_080031D4
gRom_080031D4:
	.incbin "baserom.gba", 0x31D4, 0x14
	.global gRom_080031E8
gRom_080031E8:
	.incbin "baserom.gba", 0x31E8, 0xC
	.4byte gRom_08003204
	.4byte gRom_08003214
	.4byte gRom_08003250
	.global _08003200
	.thumb_func
_08003200:
	.4byte gRom_0800328C
	.global gRom_08003204
gRom_08003204:
	.incbin "baserom.gba", 0x3204, 0x10
	.global gRom_08003214
gRom_08003214:
	.incbin "baserom.gba", 0x3214, 0x3C
	.global gRom_08003250
gRom_08003250:
	.incbin "baserom.gba", 0x3250, 0x3C
	.global gRom_0800328C
gRom_0800328C:
	.incbin "baserom.gba", 0x328C, 0x14
	.global gRom_080032A0
gRom_080032A0:
	.incbin "baserom.gba", 0x32A0, 0x20
	.4byte gRom_08003304
	.4byte gRom_08003314
	.4byte gRom_08003324
	.4byte gRom_08003334
	.incbin "baserom.gba", 0x32D0, 0x2C
	.4byte gRom_08003344
	.4byte gRom_08003354
	.global gRom_08003304
gRom_08003304:
	.incbin "baserom.gba", 0x3304, 0x4
	.global gRom_08003308
gRom_08003308:
	.incbin "baserom.gba", 0x3308, 0xC
	.global gRom_08003314
gRom_08003314:
	.incbin "baserom.gba", 0x3314, 0x10
	.global gRom_08003324
gRom_08003324:
	.incbin "baserom.gba", 0x3324, 0x10
	.global gRom_08003334
gRom_08003334:
	.incbin "baserom.gba", 0x3334, 0x10
	.global gRom_08003344
gRom_08003344:
	.incbin "baserom.gba", 0x3344, 0x10
	.global gRom_08003354
gRom_08003354:
	.incbin "baserom.gba", 0x3354, 0x14
	.global gRom_08003368
gRom_08003368:
	.incbin "baserom.gba", 0x3368, 0x10
	.4byte gRom_080033AC
	.incbin "baserom.gba", 0x337C, 0x2C
	.4byte gRom_080033BC
	.global gRom_080033AC
gRom_080033AC:
	.incbin "baserom.gba", 0x33AC, 0x10
	.global gRom_080033BC
gRom_080033BC:
	.incbin "baserom.gba", 0x33BC, 0x28
	.4byte gRom_08003424
	.incbin "baserom.gba", 0x33E8, 0x4
	.4byte gRom_08003448
	.incbin "baserom.gba", 0x33F0, 0xC
	.4byte gRom_08003458
	.incbin "baserom.gba", 0x3400, 0xC
	.4byte gRom_0800346C
	.4byte gRom_08003484
	.4byte gRom_080034A0
	.4byte gRom_080034B4
	.4byte gRom_080034C4
	.4byte gRom_080034D8
	.global gRom_08003424
gRom_08003424:
	.incbin "baserom.gba", 0x3424, 0x24
	.global gRom_08003448
gRom_08003448:
	.incbin "baserom.gba", 0x3448, 0x10
	.global gRom_08003458
gRom_08003458:
	.incbin "baserom.gba", 0x3458, 0x14
	.global gRom_0800346C
gRom_0800346C:
	.incbin "baserom.gba", 0x346C, 0x18
	.global gRom_08003484
gRom_08003484:
	.incbin "baserom.gba", 0x3484, 0x1C
	.global gRom_080034A0
gRom_080034A0:
	.incbin "baserom.gba", 0x34A0, 0x14
	.global gRom_080034B4
gRom_080034B4:
	.incbin "baserom.gba", 0x34B4, 0x10
	.global gRom_080034C4
gRom_080034C4:
	.incbin "baserom.gba", 0x34C4, 0x14
	.global gRom_080034D8
gRom_080034D8:
	.incbin "baserom.gba", 0x34D8, 0x14
	.global gRom_080034EC
gRom_080034EC:
	.incbin "baserom.gba", 0x34EC, 0x10
	.4byte gRom_08003590
	.4byte gRom_080035A4
	.incbin "baserom.gba", 0x3504, 0x30
	.4byte gRom_080035D8
	.4byte gRom_080035EC
	.4byte gRom_08003600
	.4byte gRom_08003610
	.4byte gRom_08003624
	.4byte gRom_08003634
	.4byte gRom_08003648
	.incbin "baserom.gba", 0x3550, 0x14
	.4byte gRom_08003684
	.4byte gRom_08003698
	.4byte gRom_080036AC
	.incbin "baserom.gba", 0x3570, 0x20
	.global gRom_08003590
gRom_08003590:
	.incbin "baserom.gba", 0x3590, 0x14
	.global gRom_080035A4
gRom_080035A4:
	.incbin "baserom.gba", 0x35A4, 0x34
	.global gRom_080035D8
gRom_080035D8:
	.incbin "baserom.gba", 0x35D8, 0x14
	.global gRom_080035EC
gRom_080035EC:
	.incbin "baserom.gba", 0x35EC, 0x14
	.global gRom_08003600
gRom_08003600:
	.incbin "baserom.gba", 0x3600, 0x10
	.global gRom_08003610
gRom_08003610:
	.incbin "baserom.gba", 0x3610, 0x14
	.global gRom_08003624
gRom_08003624:
	.incbin "baserom.gba", 0x3624, 0x10
	.global gRom_08003634
gRom_08003634:
	.incbin "baserom.gba", 0x3634, 0x14
	.global gRom_08003648
gRom_08003648:
	.incbin "baserom.gba", 0x3648, 0x3C
	.global gRom_08003684
gRom_08003684:
	.incbin "baserom.gba", 0x3684, 0x14
	.global gRom_08003698
gRom_08003698:
	.incbin "baserom.gba", 0x3698, 0x14
	.global gRom_080036AC
gRom_080036AC:
	.incbin "baserom.gba", 0x36AC, 0x28
	.global gRom_080036D4
gRom_080036D4:
	.incbin "baserom.gba", 0x36D4, 0x24
	.4byte gRom_08003728
	.4byte gRom_08003738
	.4byte gRom_0800375C
	.incbin "baserom.gba", 0x3704, 0xC
	.4byte gRom_08003780
	.incbin "baserom.gba", 0x3714, 0x10
	.4byte gRom_080037A4
	.global gRom_08003728
gRom_08003728:
	.incbin "baserom.gba", 0x3728, 0x10
	.global gRom_08003738
gRom_08003738:
	.incbin "baserom.gba", 0x3738, 0x24
	.global gRom_0800375C
gRom_0800375C:
	.incbin "baserom.gba", 0x375C, 0x24
	.global gRom_08003780
gRom_08003780:
	.incbin "baserom.gba", 0x3780, 0x24
	.global gRom_080037A4
gRom_080037A4:
	.incbin "baserom.gba", 0x37A4, 0x14
	.global gRom_080037B8
gRom_080037B8:
	.incbin "baserom.gba", 0x37B8, 0x4
	.global gRom_080037BC
gRom_080037BC:
	.incbin "baserom.gba", 0x37BC, 0x28
	.4byte gRom_0800389C
	.incbin "baserom.gba", 0x37E8, 0x8
	.4byte gRom_080038AC
	.incbin "baserom.gba", 0x37F4, 0x30
	.4byte gRom_080038BC
	.incbin "baserom.gba", 0x3828, 0x28
	.4byte gRom_080038CC
	.incbin "baserom.gba", 0x3854, 0x48
	.global gRom_0800389C
gRom_0800389C:
	.incbin "baserom.gba", 0x389C, 0x10
	.global gRom_080038AC
gRom_080038AC:
	.incbin "baserom.gba", 0x38AC, 0x10
	.global gRom_080038BC
gRom_080038BC:
	.incbin "baserom.gba", 0x38BC, 0x10
	.global gRom_080038CC
gRom_080038CC:
	.incbin "baserom.gba", 0x38CC, 0x18
	.global gRom_080038E4
gRom_080038E4:
	.incbin "baserom.gba", 0x38E4, 0x14
	.4byte gRom_08003918
	.incbin "baserom.gba", 0x38FC, 0x8
	.4byte gRom_08003928
	.incbin "baserom.gba", 0x3908, 0x4
	.4byte gRom_08003938
	.incbin "baserom.gba", 0x3910, 0x8
	.global gRom_08003918
gRom_08003918:
	.incbin "baserom.gba", 0x3918, 0x10
	.global gRom_08003928
gRom_08003928:
	.incbin "baserom.gba", 0x3928, 0x10
	.global gRom_08003938
gRom_08003938:
	.incbin "baserom.gba", 0x3938, 0x14
	.global gRom_0800394C
gRom_0800394C:
	.incbin "baserom.gba", 0x394C, 0x2C
	.4byte gRom_08003994
	.incbin "baserom.gba", 0x397C, 0x4
	.4byte gRom_080039A4
	.incbin "baserom.gba", 0x3984, 0x10
	.global gRom_08003994
gRom_08003994:
	.incbin "baserom.gba", 0x3994, 0x10
	.global gRom_080039A4
gRom_080039A4:
	.incbin "baserom.gba", 0x39A4, 0x10
	.global gRom_080039B4
gRom_080039B4:
	.incbin "baserom.gba", 0x39B4, 0x4
	.global gRom_080039B8
gRom_080039B8:
	.incbin "baserom.gba", 0x39B8, 0x14
	.4byte gRom_080039F0
	.incbin "baserom.gba", 0x39D0, 0x20
	.global gRom_080039F0
gRom_080039F0:
	.incbin "baserom.gba", 0x39F0, 0x10
	.global gRom_08003A00
gRom_08003A00:
	.incbin "baserom.gba", 0x3A00, 0x18
	.4byte gRom_08003A64
	.incbin "baserom.gba", 0x3A1C, 0x8
	.4byte gRom_08003A74
	.4byte gRom_08003A84
	.incbin "baserom.gba", 0x3A2C, 0x4
	.4byte gRom_08003A94
	.incbin "baserom.gba", 0x3A34, 0x28
	.4byte gRom_08003AA4
	.4byte gRom_08003AB4
	.global gRom_08003A64
gRom_08003A64:
	.incbin "baserom.gba", 0x3A64, 0x10
	.global gRom_08003A74
gRom_08003A74:
	.incbin "baserom.gba", 0x3A74, 0x10
	.global gRom_08003A84
gRom_08003A84:
	.incbin "baserom.gba", 0x3A84, 0x10
	.global gRom_08003A94
gRom_08003A94:
	.incbin "baserom.gba", 0x3A94, 0x10
	.global gRom_08003AA4
gRom_08003AA4:
	.incbin "baserom.gba", 0x3AA4, 0x10
	.global gRom_08003AB4
gRom_08003AB4:
	.incbin "baserom.gba", 0x3AB4, 0x14
	.global gRom_08003AC8
gRom_08003AC8:
	.incbin "baserom.gba", 0x3AC8, 0x8
	.4byte gRom_08003B18
	.incbin "baserom.gba", 0x3AD4, 0x28
	.4byte gRom_08003B28
	.incbin "baserom.gba", 0x3B00, 0x14
	.4byte gRom_08003B38
	.global gRom_08003B18
gRom_08003B18:
	.incbin "baserom.gba", 0x3B18, 0x10
	.global gRom_08003B28
gRom_08003B28:
	.incbin "baserom.gba", 0x3B28, 0x10
	.global gRom_08003B38
gRom_08003B38:
	.incbin "baserom.gba", 0x3B38, 0x14
	.global gRom_08003B4C
gRom_08003B4C:
	.incbin "baserom.gba", 0x3B4C, 0x28
	.4byte gRom_08003BD8
	.incbin "baserom.gba", 0x3B78, 0x8
	.4byte gRom_08003BE8
	.incbin "baserom.gba", 0x3B84, 0xC
	.4byte gRom_08003BF8
	.incbin "baserom.gba", 0x3B94, 0x30
	.4byte gRom_08003C14
	.incbin "baserom.gba", 0x3BC8, 0x10
	.global gRom_08003BD8
gRom_08003BD8:
	.incbin "baserom.gba", 0x3BD8, 0x10
	.global gRom_08003BE8
gRom_08003BE8:
	.incbin "baserom.gba", 0x3BE8, 0x10
	.global gRom_08003BF8
gRom_08003BF8:
	.incbin "baserom.gba", 0x3BF8, 0x1C
	.global gRom_08003C14
gRom_08003C14:
	.incbin "baserom.gba", 0x3C14, 0xC
	.global gRom_08003C20
gRom_08003C20:
	.incbin "baserom.gba", 0x3C20, 0x10
	.global gRom_08003C30
gRom_08003C30:
	.incbin "baserom.gba", 0x3C30, 0x4
	.global gRom_08003C34
gRom_08003C34:
	.incbin "baserom.gba", 0x3C34, 0x4
	.global gRom_08003C38
gRom_08003C38:
	.incbin "baserom.gba", 0x3C38, 0x4
	.global gRom_08003C3C
gRom_08003C3C:
	.incbin "baserom.gba", 0x3C3C, 0x4
	.global gRom_08003C40
gRom_08003C40:
	.incbin "baserom.gba", 0x3C40, 0x10
	.4byte gRom_08003C74
	.incbin "baserom.gba", 0x3C54, 0x14
	.4byte gRom_08003C84
	.incbin "baserom.gba", 0x3C6C, 0x8
	.global gRom_08003C74
gRom_08003C74:
	.incbin "baserom.gba", 0x3C74, 0x10
	.global gRom_08003C84
gRom_08003C84:
	.incbin "baserom.gba", 0x3C84, 0x14
	.global gRom_08003C98
gRom_08003C98:
	.incbin "baserom.gba", 0x3C98, 0x4
	.global gRom_08003C9C
gRom_08003C9C:
	.incbin "baserom.gba", 0x3C9C, 0x18
	.4byte gRom_08003D10
	.incbin "baserom.gba", 0x3CB8, 0x28
	.4byte gRom_08003D20
	.4byte gRom_08003D38
	.incbin "baserom.gba", 0x3CE8, 0x28
	.global gRom_08003D10
gRom_08003D10:
	.incbin "baserom.gba", 0x3D10, 0x10
	.global gRom_08003D20
gRom_08003D20:
	.incbin "baserom.gba", 0x3D20, 0x18
	.global gRom_08003D38
gRom_08003D38:
	.incbin "baserom.gba", 0x3D38, 0x18
	.global gRom_08003D50
gRom_08003D50:
	.incbin "baserom.gba", 0x3D50, 0x4
	.global gRom_08003D54
gRom_08003D54:
	.incbin "baserom.gba", 0x3D54, 0x8
	.global gRom_08003D5C
gRom_08003D5C:
	.incbin "baserom.gba", 0x3D5C, 0x4
	.global gRom_08003D60
gRom_08003D60:
	.incbin "baserom.gba", 0x3D60, 0x8
	.global gRom_08003D68
gRom_08003D68:
	.incbin "baserom.gba", 0x3D68, 0x4
	.global gRom_08003D6C
gRom_08003D6C:
	.incbin "baserom.gba", 0x3D6C, 0x220
	.4byte _080C3CE4 + 1
	.incbin "baserom.gba", 0x3F90, 0x70
	.global gRom_08004000
gRom_08004000:
	.incbin "baserom.gba", 0x4000, 0x154
	.4byte gRom_082BEC24
	.incbin "baserom.gba", 0x4158, 0xB8
	.global _08004210
	.thumb_func
_08004210:
	.incbin "baserom.gba", 0x4210, 0x68
	.4byte gRom_081A8B4C
	.incbin "baserom.gba", 0x427C, 0x8C
	.global gRom_08004308
gRom_08004308:
	.incbin "baserom.gba", 0x4308, 0x118
	.global gRom_08004420
gRom_08004420:
	.incbin "baserom.gba", 0x4420, 0x1E8
	.global gRom_08004608
gRom_08004608:
	.incbin "baserom.gba", 0x4608, 0x70
	.global _08004678
	.thumb_func
_08004678:
	.incbin "baserom.gba", 0x4678, 0x5A8
	.global _08004C20
	.thumb_func
_08004C20:
	.incbin "baserom.gba", 0x4C20, 0x398
	.4byte gRom_0800F80C
	.incbin "baserom.gba", 0x4FBC, 0x598
	.global _08005554
	.thumb_func
_08005554:
	.incbin "baserom.gba", 0x5554, 0xC90
	.global gRom_080061E4
gRom_080061E4:
	.incbin "baserom.gba", 0x61E4, 0x3EC
	.global gRom_080065D0
gRom_080065D0:
	.incbin "baserom.gba", 0x65D0, 0xA8
	.global gRom_08006678
gRom_08006678:
	.incbin "baserom.gba", 0x6678, 0x8B8
	.global gRom_08006F30
gRom_08006F30:
	.incbin "baserom.gba", 0x6F30, 0x95C
	.global _0800788C
	.thumb_func
_0800788C:
	.incbin "baserom.gba", 0x788C, 0x6D8
	.global gRom_08007F64
gRom_08007F64:
	.incbin "baserom.gba", 0x7F64, 0x6C
	.4byte gRom_080420E0
	.incbin "baserom.gba", 0x7FD4, 0x30
	.global gRom_08008004
gRom_08008004:
	.incbin "baserom.gba", 0x8004, 0x17C
	.global _08008180
	.thumb_func
_08008180:
	.incbin "baserom.gba", 0x8180, 0x300
	.global gRom_08008480
gRom_08008480:
	.incbin "baserom.gba", 0x8480, 0x1E4
	.4byte _082B0CD8 + 1
	.incbin "baserom.gba", 0x8668, 0x4C8
	.global gRom_08008B30
gRom_08008B30:
	.incbin "baserom.gba", 0x8B30, 0x2AC
	.4byte gRom_0807F104
	.incbin "baserom.gba", 0x8DE0, 0x154
	.4byte _0801F600 + 1
	.incbin "baserom.gba", 0x8F38, 0x118
	.4byte gRom_0800FA04
	.incbin "baserom.gba", 0x9054, 0x8
	.4byte _0802F404 + 1
	.incbin "baserom.gba", 0x9060, 0xD0
	.4byte _0800F704 + 1
	.incbin "baserom.gba", 0x9134, 0x11C
	.4byte gRom_0802FA04
	.incbin "baserom.gba", 0x9254, 0x1878
	.global gRom_0800AACC
gRom_0800AACC:
	.incbin "baserom.gba", 0xAACC, 0x34
	.global gRom_0800AB00
gRom_0800AB00:
	.incbin "baserom.gba", 0xAB00, 0x3C
	.global gRom_0800AB3C
gRom_0800AB3C:
	.incbin "baserom.gba", 0xAB3C, 0x4
	.global _0800AB40
	.thumb_func
_0800AB40:
	.incbin "baserom.gba", 0xAB40, 0x4F0
	.global gRom_0800B030
gRom_0800B030:
	.incbin "baserom.gba", 0xB030, 0x1D0
	.global _0800B200
	.thumb_func
_0800B200:
	.incbin "baserom.gba", 0xB200, 0x194
	.global gRom_0800B394
gRom_0800B394:
	.incbin "baserom.gba", 0xB394, 0xBC
	.global gRom_0800B450
gRom_0800B450:
	.incbin "baserom.gba", 0xB450, 0x53C
	.4byte _08122534 + 1
	.incbin "baserom.gba", 0xB990, 0x14C
	.4byte _080A0804 + 1
	.incbin "baserom.gba", 0xBAE0, 0x128
	.global gRom_0800BC08
gRom_0800BC08:
	.incbin "baserom.gba", 0xBC08, 0x27C
	.global gRom_0800BE84
gRom_0800BE84:
	.incbin "baserom.gba", 0xBE84, 0x18
	.4byte gRom_08080708
	.incbin "baserom.gba", 0xBEA0, 0x1B4
	.4byte gRom_08190C28
	.incbin "baserom.gba", 0xC058, 0xA4
	.global gRom_0800C0FC
gRom_0800C0FC:
	.incbin "baserom.gba", 0xC0FC, 0x190
	.4byte gRom_0808FD04
	.incbin "baserom.gba", 0xC290, 0x218
	.4byte _08090808 + 1
	.incbin "baserom.gba", 0xC4AC, 0x1C
	.4byte gRom_08090708
	.incbin "baserom.gba", 0xC4CC, 0x298
	.global gRom_0800C764
gRom_0800C764:
	.incbin "baserom.gba", 0xC764, 0xA4
	.global gRom_0800C808
gRom_0800C808:
	.incbin "baserom.gba", 0xC808, 0x2C4
	.global gRom_0800CACC
gRom_0800CACC:
	.incbin "baserom.gba", 0xCACC, 0x11C
	.global gRom_0800CBE8
gRom_0800CBE8:
	.incbin "baserom.gba", 0xCBE8, 0x6C
	.global _0800CC54
	.thumb_func
_0800CC54:
	.incbin "baserom.gba", 0xCC54, 0x278
	.4byte _08080B0C + 1
	.incbin "baserom.gba", 0xCED0, 0x9C
	.4byte gRom_080A0600
	.incbin "baserom.gba", 0xCF70, 0xF0
	.4byte gRom_0800F700
	.incbin "baserom.gba", 0xD064, 0x10B0
	.4byte gRom_0808F000
	.incbin "baserom.gba", 0xE118, 0x2E8
	.global gRom_0800E400
gRom_0800E400:
	.incbin "baserom.gba", 0xE400, 0xA04
	.global _0800EE04
	.thumb_func
_0800EE04:
	.incbin "baserom.gba", 0xEE04, 0x510
	.global _0800F314
	.thumb_func
_0800F314:
	.incbin "baserom.gba", 0xF314, 0x3E4
	.global gRom_0800F6F8
gRom_0800F6F8:
	.incbin "baserom.gba", 0xF6F8, 0x8
	.global gRom_0800F700
gRom_0800F700:
	.incbin "baserom.gba", 0xF700, 0x4
	.global _0800F704
	.thumb_func
_0800F704:
	.incbin "baserom.gba", 0xF704, 0x108
	.global gRom_0800F80C
gRom_0800F80C:
	.incbin "baserom.gba", 0xF80C, 0x1F8
	.global gRom_0800FA04
gRom_0800FA04:
	.incbin "baserom.gba", 0xFA04, 0x1E8
	.global _0800FBEC
	.thumb_func
_0800FBEC:
	.incbin "baserom.gba", 0xFBEC, 0x404
	.global gRom_0800FFF0
gRom_0800FFF0:
	.incbin "baserom.gba", 0xFFF0, 0x10
	.global gRom_08010000
gRom_08010000:
	.incbin "baserom.gba", 0x10000, 0x8
	.global gRom_08010008
gRom_08010008:
	.incbin "baserom.gba", 0x10008, 0x108
	.global gRom_08010110
gRom_08010110:
	.incbin "baserom.gba", 0x10110, 0x6F8
	.global gRom_08010808
gRom_08010808:
	.incbin "baserom.gba", 0x10808, 0x1DF8
	.global _08012600
	.thumb_func
_08012600:
	.incbin "baserom.gba", 0x12600, 0xAB0
	.global gRom_080130B0
gRom_080130B0:
	.incbin "baserom.gba", 0x130B0, 0x36A4
	.global gRom_08016754
gRom_08016754:
	.incbin "baserom.gba", 0x16754, 0x2DC
	.4byte _081D0900 + 1
	.incbin "baserom.gba", 0x16A34, 0x2B8
	.4byte gRom_082102F8
	.incbin "baserom.gba", 0x16CF0, 0x2D0
	.4byte gRom_080DE500
	.incbin "baserom.gba", 0x16FC4, 0xB8
	.4byte gRom_080CFBFC
	.incbin "baserom.gba", 0x17080, 0x174
	.4byte gRom_08021120
	.incbin "baserom.gba", 0x171F8, 0x148
	.4byte gRom_08000408
	.incbin "baserom.gba", 0x17344, 0x4
	.4byte _08230B14 + 1
	.incbin "baserom.gba", 0x1734C, 0x158
	.4byte gRom_0802071C
	.incbin "baserom.gba", 0x174A8, 0x170
	.4byte _080D1210 + 1
	.incbin "baserom.gba", 0x1761C, 0x20
	.4byte gRom_0804F2F8
	.incbin "baserom.gba", 0x17640, 0x8C
	.4byte _08000C10 + 1
	.incbin "baserom.gba", 0x176D0, 0x100
	.4byte gRom_08100020 + 1
	.incbin "baserom.gba", 0x177D4, 0xC8
	.4byte gRom_080C0E0C
	.incbin "baserom.gba", 0x178A0, 0x144
	.4byte _080F190C + 1
	.incbin "baserom.gba", 0x179E8, 0x2B8
	.4byte _080E14FC + 1
	.incbin "baserom.gba", 0x17CA4, 0x174
	.4byte gRom_080F0D00
	.incbin "baserom.gba", 0x17E1C, 0xF8
	.4byte gRom_080F1C24
	.incbin "baserom.gba", 0x17F18, 0x2DC
	.4byte gRom_080A0900
	.incbin "baserom.gba", 0x181F8, 0x120
	.4byte gRom_08040410
	.incbin "baserom.gba", 0x1831C, 0xF8
	.4byte gRom_08060000
	.incbin "baserom.gba", 0x18418, 0x1F0
	.global gRom_08018608
gRom_08018608:
	.incbin "baserom.gba", 0x18608, 0x1F8
	.global gRom_08018800
gRom_08018800:
	.incbin "baserom.gba", 0x18800, 0x8
	.global gRom_08018808
gRom_08018808:
	.incbin "baserom.gba", 0x18808, 0x180
	.global gRom_08018988
gRom_08018988:
	.incbin "baserom.gba", 0x18988, 0x128
	.global gRom_08018AB0
gRom_08018AB0:
	.incbin "baserom.gba", 0x18AB0, 0x7CC
	.4byte gRom_081C2428
	.incbin "baserom.gba", 0x19280, 0x794
	.4byte _0807FCF4 + 1
	.incbin "baserom.gba", 0x19A18, 0x288
	.4byte _080EFEF4 + 1
	.incbin "baserom.gba", 0x19CA4, 0x64
	.4byte gRom_080D1214
	.incbin "baserom.gba", 0x19D0C, 0x34C
	.4byte gRom_080C1014
	.incbin "baserom.gba", 0x1A05C, 0x78
	.4byte gRom_0808131C
	.incbin "baserom.gba", 0x1A0D8, 0x2A8
	.4byte gRom_0801FBF8
	.incbin "baserom.gba", 0x1A384, 0xD60
	.4byte _08121118 + 1
	.incbin "baserom.gba", 0x1B0E8, 0x15C
	.4byte gRom_0802F9F4
	.incbin "baserom.gba", 0x1B248, 0x9C
	.4byte _08181110 + 1
	.incbin "baserom.gba", 0x1B2E8, 0x390
	.4byte gRom_0805FAF4
	.incbin "baserom.gba", 0x1B67C, 0x61C
	.4byte _08101118 + 1
	.incbin "baserom.gba", 0x1BC9C, 0xB8
	.4byte gRom_0814EA04
	.incbin "baserom.gba", 0x1BD58, 0x39C
	.global _0801C0F4
	.thumb_func
_0801C0F4:
	.incbin "baserom.gba", 0x1C0F4, 0x190
	.4byte _080B111C + 1
	.incbin "baserom.gba", 0x1C288, 0x70
	.4byte _080F06FC + 1
	.incbin "baserom.gba", 0x1C2FC, 0x14
	.global gRom_0801C310
gRom_0801C310:
	.incbin "baserom.gba", 0x1C310, 0x614
	.4byte gRom_081A1910
	.incbin "baserom.gba", 0x1C928, 0x4B0
	.4byte _080C111C + 1
	.incbin "baserom.gba", 0x1CDDC, 0x630
	.4byte _080C151C + 1
	.incbin "baserom.gba", 0x1D410, 0xA4
	.4byte gRom_080D171C
	.incbin "baserom.gba", 0x1D4B8, 0x6E0
	.4byte _0800FBEC + 1
	.incbin "baserom.gba", 0x1DB9C, 0x290
	.4byte _0802FFFC + 1
	.incbin "baserom.gba", 0x1DE30, 0x250
	.4byte _080002FC + 1
	.incbin "baserom.gba", 0x1E084, 0x84
	.4byte gRom_080A0C10
	.incbin "baserom.gba", 0x1E10C, 0x48
	.4byte _080B0C0C + 1
	.incbin "baserom.gba", 0x1E158, 0xE0
	.4byte gRom_080A0B0C
	.incbin "baserom.gba", 0x1E23C, 0xF8
	.4byte gRom_080C0808
	.incbin "baserom.gba", 0x1E338, 0x78
	.4byte gRom_08080608
	.incbin "baserom.gba", 0x1E3B4, 0x90
	.4byte gRom_08090708
	.incbin "baserom.gba", 0x1E448, 0x2C
	.4byte gRom_08070504
	.incbin "baserom.gba", 0x1E478, 0x7C
	.4byte gRom_08080A08
	.incbin "baserom.gba", 0x1E4F8, 0x5C
	.4byte _08060604 + 1
	.incbin "baserom.gba", 0x1E558, 0x60
	.4byte _08080604 + 1
	.incbin "baserom.gba", 0x1E5BC, 0x14
	.4byte _08050604 + 1
	.incbin "baserom.gba", 0x1E5D4, 0x2C
	.4byte _080A0604 + 1
	.incbin "baserom.gba", 0x1E604, 0x5C0
	.global gRom_0801EBC4
gRom_0801EBC4:
	.incbin "baserom.gba", 0x1EBC4, 0x644
	.4byte _08112E2C + 1
	.incbin "baserom.gba", 0x1F20C, 0x2B0
	.4byte gRom_080C080C
	.incbin "baserom.gba", 0x1F4C0, 0xA8
	.4byte _0804F708 + 1
	.incbin "baserom.gba", 0x1F56C, 0x94
	.global _0801F600
	.thumb_func
_0801F600:
	.incbin "baserom.gba", 0x1F600, 0x10
	.global gRom_0801F610
gRom_0801F610:
	.incbin "baserom.gba", 0x1F610, 0x1F4
	.4byte _0803F804 + 1
	.incbin "baserom.gba", 0x1F808, 0x114
	.4byte gRom_0801F610
	.4byte _0804FEFC + 1
	.incbin "baserom.gba", 0x1F924, 0xE4
	.global _0801FA08
	.thumb_func
_0801FA08:
	.incbin "baserom.gba", 0x1FA08, 0x1F0
	.global gRom_0801FBF8
gRom_0801FBF8:
	.incbin "baserom.gba", 0x1FBF8, 0x408
	.global gRom_08020000
gRom_08020000:
	.incbin "baserom.gba", 0x20000, 0x10
	.global gRom_08020010
gRom_08020010:
	.incbin "baserom.gba", 0x20010, 0x54
	.global gRom_08020064
gRom_08020064:
	.incbin "baserom.gba", 0x20064, 0x1C
	.global gRom_08020080
gRom_08020080:
	.incbin "baserom.gba", 0x20080, 0x69C
	.global gRom_0802071C
gRom_0802071C:
	.incbin "baserom.gba", 0x2071C, 0xEC
	.global gRom_08020808
gRom_08020808:
	.incbin "baserom.gba", 0x20808, 0x8
	.global gRom_08020810
gRom_08020810:
	.incbin "baserom.gba", 0x20810, 0x910
	.global gRom_08021120
gRom_08021120:
	.incbin "baserom.gba", 0x21120, 0x56C
	.global gRom_0802168C
gRom_0802168C:
	.incbin "baserom.gba", 0x2168C, 0x520
	.4byte gRom_080713EC
	.incbin "baserom.gba", 0x21BB0, 0xB74
	.4byte _080A0304 + 1
	.incbin "baserom.gba", 0x22728, 0xD7C
	.global gRom_080234A4
gRom_080234A4:
	.incbin "baserom.gba", 0x234A4, 0x210
	.4byte _08080EF4 + 1
	.incbin "baserom.gba", 0x236B8, 0x10
	.4byte gRom_0806F204
	.incbin "baserom.gba", 0x236CC, 0x164
	.4byte gRom_0809F830
	.incbin "baserom.gba", 0x23834, 0x2DC
	.4byte gRom_0804FE5C
	.incbin "baserom.gba", 0x23B14, 0x93C
	.global _08024450
	.thumb_func
_08024450:
	.incbin "baserom.gba", 0x24450, 0x32C
	.4byte _08291040 + 1
	.incbin "baserom.gba", 0x24780, 0x114
	.4byte _0824EA30 + 1
	.incbin "baserom.gba", 0x24898, 0x1C
	.4byte _080CFAFC + 1
	.incbin "baserom.gba", 0x248B8, 0xCB0
	.4byte _08050704 + 1
	.incbin "baserom.gba", 0x2556C, 0x188
	.4byte _08000604 + 1
	.incbin "baserom.gba", 0x256F8, 0x159C
	.global gRom_08026C94
gRom_08026C94:
	.incbin "baserom.gba", 0x26C94, 0x204
	.4byte gRom_081AECF8
	.incbin "baserom.gba", 0x26E9C, 0xC78
	.4byte _0802F810 + 1
	.incbin "baserom.gba", 0x27B18, 0xF0
	.4byte _080AF300 + 1
	.incbin "baserom.gba", 0x27C0C, 0x160
	.4byte _0801FA08 + 1
	.incbin "baserom.gba", 0x27D70, 0xEC
	.4byte _0805FDF4 + 1
	.incbin "baserom.gba", 0x27E60, 0x1A0
	.global gRom_08028000
gRom_08028000:
	.incbin "baserom.gba", 0x28000, 0x8
	.global gRom_08028008
gRom_08028008:
	.incbin "baserom.gba", 0x28008, 0x688
	.4byte gRom_0803FD04
	.incbin "baserom.gba", 0x28694, 0x13D0
	.global gRom_08029A64
gRom_08029A64:
	.incbin "baserom.gba", 0x29A64, 0xB04
	.global gRom_0802A568
gRom_0802A568:
	.incbin "baserom.gba", 0x2A568, 0x280
	.4byte _08273734 + 1
	.incbin "baserom.gba", 0x2A7EC, 0xB2C
	.global gRom_0802B318
gRom_0802B318:
	.incbin "baserom.gba", 0x2B318, 0x4C8
	.global gRom_0802B7E0
gRom_0802B7E0:
	.incbin "baserom.gba", 0x2B7E0, 0x8
	.4byte gRom_0802B7F0
	.4byte gRom_0802B7F0
	.global gRom_0802B7F0
gRom_0802B7F0:
	.4byte gRom_08003D6C
	.4byte gRom_080061E4
	.4byte gRom_08007F64
	.4byte gRom_0800B394
	.4byte gRom_0800BE84
	.4byte gRom_0800CBE8
	.4byte gRom_0800F6F8
	.4byte gRom_08016754
	.4byte gRom_08018AB0
	.4byte gRom_0801EBC4
	.4byte gRom_0802168C
	.4byte gRom_080234A4
	.4byte gRom_08026C94
	.4byte gRom_08029A64
	.4byte gRom_0802A568
	.4byte gRom_0802B318
	.incbin "baserom.gba", 0x2B830, 0x88
	.4byte gData_08075AB8
