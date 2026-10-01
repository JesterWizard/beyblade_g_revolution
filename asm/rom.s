@ Unmatched ROM head 0x08000000..0x0802B8BB
	.section .rodata,"a",%progbits
	.balign 2
	.global gBaserom
gBaserom:
	.incbin "baserom.gba", 0x0, 0x4D0
	.global gRom_080004D0
gRom_080004D0:
	.incbin "baserom.gba", 0x4D0, 0x88
	.4byte gRom_080005FC
	.4byte gRom_0800060C
	.4byte gRom_0800061C
	.4byte gRom_0800062C
	.incbin "baserom.gba", 0x568, 0x94
	.global gRom_080005FC
gRom_080005FC:
	.incbin "baserom.gba", 0x5FC, 0x10
	.global gRom_0800060C
gRom_0800060C:
	.incbin "baserom.gba", 0x60C, 0x10
	.global gRom_0800061C
gRom_0800061C:
	.incbin "baserom.gba", 0x61C, 0x10
	.global gRom_0800062C
gRom_0800062C:
	.incbin "baserom.gba", 0x62C, 0x30
	.4byte gRom_080006DC
	.4byte gRom_080006EC
	.4byte gRom_080006FC
	.4byte gRom_0800070C
	.incbin "baserom.gba", 0x66C, 0x70
	.global gRom_080006DC
gRom_080006DC:
	.incbin "baserom.gba", 0x6DC, 0x10
	.global gRom_080006EC
gRom_080006EC:
	.incbin "baserom.gba", 0x6EC, 0x10
	.global gRom_080006FC
gRom_080006FC:
	.incbin "baserom.gba", 0x6FC, 0x10
	.global gRom_0800070C
gRom_0800070C:
	.incbin "baserom.gba", 0x70C, 0x14
	.global gRom_08000720
gRom_08000720:
	.incbin "baserom.gba", 0x720, 0x1C
	.4byte gRom_080007C8
	.4byte gRom_080007D8
	.4byte gRom_080007E8
	.4byte gRom_080007F8
	.incbin "baserom.gba", 0x74C, 0x7C
	.global gRom_080007C8
gRom_080007C8:
	.incbin "baserom.gba", 0x7C8, 0x10
	.global gRom_080007D8
gRom_080007D8:
	.incbin "baserom.gba", 0x7D8, 0x10
	.global gRom_080007E8
gRom_080007E8:
	.incbin "baserom.gba", 0x7E8, 0x10
	.global gRom_080007F8
gRom_080007F8:
	.incbin "baserom.gba", 0x7F8, 0x30
	.4byte gRom_080008A0
	.4byte gRom_080008B0
	.4byte gRom_080008C0
	.4byte gRom_080008D0
	.incbin "baserom.gba", 0x838, 0x68
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
	.incbin "baserom.gba", 0x8D0, 0x30
	.4byte gRom_08000970
	.4byte gRom_08000980
	.4byte gRom_08000990
	.4byte gRom_080009A0
	.incbin "baserom.gba", 0x910, 0x60
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
	.incbin "baserom.gba", 0x9A0, 0x40
	.4byte gRom_08000A40
	.4byte gRom_08000A50
	.4byte gRom_08000A60
	.4byte gRom_08000A70
	.incbin "baserom.gba", 0x9F0, 0x50
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
	.incbin "baserom.gba", 0xA70, 0x30
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
	.incbin "baserom.gba", 0xAF8, 0x10
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
	.incbin "baserom.gba", 0xB48, 0x10
	.global gRom_08000B58
gRom_08000B58:
	.incbin "baserom.gba", 0xB58, 0x8B4
	.4byte gRom_08001434
	.4byte gRom_08001444
	.4byte gRom_08001454
	.4byte gRom_08001464
	.incbin "baserom.gba", 0x141C, 0x18
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
	.incbin "baserom.gba", 0x1464, 0x3FC
	.4byte gRom_08001888
	.4byte gRom_08001898
	.4byte gRom_080018A8
	.4byte gRom_080018B8
	.incbin "baserom.gba", 0x1870, 0x18
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
	.incbin "baserom.gba", 0x18B8, 0x2D4
	.4byte gRom_08001BB8
	.4byte gRom_08001BCC
	.4byte gRom_08001BE4
	.incbin "baserom.gba", 0x1B98, 0x20
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
	.incbin "baserom.gba", 0x1BF8, 0x20
	.4byte gRom_08001C54
	.4byte gRom_08001C78
	.4byte gRom_08001C9C
	.incbin "baserom.gba", 0x1C24, 0x4
	.4byte gRom_08001CB0
	.4byte gRom_08001CC4
	.4byte gRom_08001CD8
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
	.incbin "baserom.gba", 0x1CEC, 0x20
	.4byte gRom_08001D40
	.4byte gRom_08001D58
	.4byte gRom_08001D6C
	.incbin "baserom.gba", 0x1D18, 0x28
	.global gRom_08001D40
gRom_08001D40:
	.incbin "baserom.gba", 0x1D40, 0x18
	.global gRom_08001D58
gRom_08001D58:
	.incbin "baserom.gba", 0x1D58, 0x14
	.global gRom_08001D6C
gRom_08001D6C:
	.incbin "baserom.gba", 0x1D6C, 0x38
	.4byte gRom_08001DB8
	.4byte gRom_08001DC8
	.4byte gRom_08001DEC
	.incbin "baserom.gba", 0x1DB0, 0x8
	.global gRom_08001DB8
gRom_08001DB8:
	.incbin "baserom.gba", 0x1DB8, 0x10
	.global gRom_08001DC8
gRom_08001DC8:
	.incbin "baserom.gba", 0x1DC8, 0x24
	.global gRom_08001DEC
gRom_08001DEC:
	.incbin "baserom.gba", 0x1DEC, 0x44
	.4byte gRom_08001E64
	.4byte gRom_08001E74
	.4byte gRom_08001E88
	.4byte gRom_08001EAC
	.4byte gRom_08001ED0
	.4byte gRom_08001EE4
	.4byte gRom_08001EF8
	.4byte gRom_08001F0C
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
	.incbin "baserom.gba", 0x1F20, 0x158
	.4byte gRom_08002134
	.4byte gRom_08002144
	.4byte gRom_08002158
	.4byte gRom_0800216C
	.4byte gRom_08002180
	.incbin "baserom.gba", 0x208C, 0xA8
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
	.incbin "baserom.gba", 0x2204, 0x24
	.global gRom_08002228
gRom_08002228:
	.incbin "baserom.gba", 0x2228, 0x24
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
	.incbin "baserom.gba", 0x2340, 0x18
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
	.incbin "baserom.gba", 0x23D0, 0x48
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
	.incbin "baserom.gba", 0x2454, 0xB8
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
	.incbin "baserom.gba", 0x2608, 0x14C
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
	.incbin "baserom.gba", 0x2780, 0x20
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
	.incbin "baserom.gba", 0x2814, 0x14
	.global gRom_08002828
gRom_08002828:
	.incbin "baserom.gba", 0x2828, 0x14
	.global gRom_0800283C
gRom_0800283C:
	.incbin "baserom.gba", 0x283C, 0xAC
	.4byte gRom_08002968
	.4byte gRom_0800297C
	.4byte gRom_08002990
	.4byte gRom_080029A8
	.incbin "baserom.gba", 0x28F8, 0x70
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
	.incbin "baserom.gba", 0x29A8, 0x24
	.4byte gRom_080029FC
	.4byte gRom_08002A0C
	.4byte gRom_08002A30
	.incbin "baserom.gba", 0x29D8, 0x24
	.global gRom_080029FC
gRom_080029FC:
	.incbin "baserom.gba", 0x29FC, 0x10
	.global gRom_08002A0C
gRom_08002A0C:
	.incbin "baserom.gba", 0x2A0C, 0x24
	.global gRom_08002A30
gRom_08002A30:
	.incbin "baserom.gba", 0x2A30, 0xB8
	.global gRom_08002AE8
gRom_08002AE8:
	.incbin "baserom.gba", 0x2AE8, 0x5C
	.global gRom_08002B44
gRom_08002B44:
	.incbin "baserom.gba", 0x2B44, 0x134
	.4byte gRom_08002C94
	.4byte gRom_08002CA4
	.4byte gRom_08002CB4
	.incbin "baserom.gba", 0x2C84, 0x10
	.global gRom_08002C94
gRom_08002C94:
	.incbin "baserom.gba", 0x2C94, 0x10
	.global gRom_08002CA4
gRom_08002CA4:
	.incbin "baserom.gba", 0x2CA4, 0x10
	.global gRom_08002CB4
gRom_08002CB4:
	.incbin "baserom.gba", 0x2CB4, 0x60
	.global gRom_08002D14
gRom_08002D14:
	.incbin "baserom.gba", 0x2D14, 0x18
	.4byte gRom_08002D68
	.4byte gRom_08002D78
	.4byte gRom_08002D88
	.incbin "baserom.gba", 0x2D38, 0x30
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
	.incbin "baserom.gba", 0x2D9C, 0x44
	.4byte gRom_08002E30
	.4byte gRom_08002E48
	.4byte gRom_08002E58
	.incbin "baserom.gba", 0x2DEC, 0x44
	.global gRom_08002E30
gRom_08002E30:
	.incbin "baserom.gba", 0x2E30, 0x18
	.global gRom_08002E48
gRom_08002E48:
	.incbin "baserom.gba", 0x2E48, 0x10
	.global gRom_08002E58
gRom_08002E58:
	.incbin "baserom.gba", 0x2E58, 0x7C
	.4byte gRom_08002F90
	.4byte gRom_08002FA4
	.4byte gRom_08002FB8
	.incbin "baserom.gba", 0x2EE0, 0xB0
	.global gRom_08002F90
gRom_08002F90:
	.incbin "baserom.gba", 0x2F90, 0x14
	.global gRom_08002FA4
gRom_08002FA4:
	.incbin "baserom.gba", 0x2FA4, 0x14
	.global gRom_08002FB8
gRom_08002FB8:
	.incbin "baserom.gba", 0x2FB8, 0x90
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
	.incbin "baserom.gba", 0x308C, 0x38
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
	.incbin "baserom.gba", 0x328C, 0x34
	.4byte gRom_08003304
	.4byte gRom_08003314
	.4byte gRom_08003324
	.4byte gRom_08003334
	.incbin "baserom.gba", 0x32D0, 0x34
	.global gRom_08003304
gRom_08003304:
	.incbin "baserom.gba", 0x3304, 0x10
	.global gRom_08003314
gRom_08003314:
	.incbin "baserom.gba", 0x3314, 0x10
	.global gRom_08003324
gRom_08003324:
	.incbin "baserom.gba", 0x3324, 0x10
	.global gRom_08003334
gRom_08003334:
	.incbin "baserom.gba", 0x3334, 0xD8
	.4byte gRom_0800346C
	.4byte gRom_08003484
	.4byte gRom_080034A0
	.4byte gRom_080034B4
	.4byte gRom_080034C4
	.4byte gRom_080034D8
	.incbin "baserom.gba", 0x3424, 0x48
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
	.incbin "baserom.gba", 0x34EC, 0x48
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
	.incbin "baserom.gba", 0x3570, 0x68
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
	.incbin "baserom.gba", 0x3704, 0x24
	.global gRom_08003728
gRom_08003728:
	.incbin "baserom.gba", 0x3728, 0x10
	.global gRom_08003738
gRom_08003738:
	.incbin "baserom.gba", 0x3738, 0x24
	.global gRom_0800375C
gRom_0800375C:
	.incbin "baserom.gba", 0x375C, 0x610
	.global gRom_08003D6C
gRom_08003D6C:
	.incbin "baserom.gba", 0x3D6C, 0x2478
	.global gRom_080061E4
gRom_080061E4:
	.incbin "baserom.gba", 0x61E4, 0x1D80
	.global gRom_08007F64
gRom_08007F64:
	.incbin "baserom.gba", 0x7F64, 0x3430
	.global gRom_0800B394
gRom_0800B394:
	.incbin "baserom.gba", 0xB394, 0xAF0
	.global gRom_0800BE84
gRom_0800BE84:
	.incbin "baserom.gba", 0xBE84, 0xD64
	.global gRom_0800CBE8
gRom_0800CBE8:
	.incbin "baserom.gba", 0xCBE8, 0x2B10
	.global gRom_0800F6F8
gRom_0800F6F8:
	.incbin "baserom.gba", 0xF6F8, 0x705C
	.global gRom_08016754
gRom_08016754:
	.incbin "baserom.gba", 0x16754, 0x235C
	.global gRom_08018AB0
gRom_08018AB0:
	.incbin "baserom.gba", 0x18AB0, 0x6114
	.global gRom_0801EBC4
gRom_0801EBC4:
	.incbin "baserom.gba", 0x1EBC4, 0x2AC8
	.global gRom_0802168C
gRom_0802168C:
	.incbin "baserom.gba", 0x2168C, 0x1E18
	.global gRom_080234A4
gRom_080234A4:
	.incbin "baserom.gba", 0x234A4, 0x37F0
	.global gRom_08026C94
gRom_08026C94:
	.incbin "baserom.gba", 0x26C94, 0x2DD0
	.global gRom_08029A64
gRom_08029A64:
	.incbin "baserom.gba", 0x29A64, 0xB04
	.global gRom_0802A568
gRom_0802A568:
	.incbin "baserom.gba", 0x2A568, 0xDB0
	.global gRom_0802B318
gRom_0802B318:
	.incbin "baserom.gba", 0x2B318, 0x4D0
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
