#include "global.h"

// @ 0x0806ff58
void sub_0806FF58(void *a, void *b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h)
{
    struct Unk705DC *dst;
    u8 *src;
    u32 attr;
    u32 attrHi;
    s8 pri;
    u8 shapeByte;

    dst = a;
    src = b;
    shapeByte = src[0x0C];
    pri = (s8)src[7];
    dst->unk2C = src;
    dst->unk1C = (u16)e;
    dst->unk08 = c;
    dst->unk0C = d;
    attr = (u32)(pri & 3) << 14;
    attr |= (u32)(~shapeByte & 1) << 13;
    attr |= (u32)(f & 3) << 10;
    attr |= 0x1000;
    attr |= (u32)(shapeByte & 0xC) << 28;
    attr |= (u32)(e & 3) << 28;
    dst->unk10 = attr;
    attrHi = (u32)((shapeByte >> 1) & 0xF) << 12;
    attrHi |= (u32)(g & 3) << 10;
    dst->unk14 = (u16)attrHi;
    if (src[0x1C] != 0)
        dst->unk28 = *(void **)(src + 0x1C);
    else
        dst->unk28 = *(void **)(src + 0x10);
    dst->unk16 = src[6];
    dst->unk18 = (u16)h;
    dst->unk1A = 0xFFFF;
    dst->unk1C = 0;
    dst->unk20 = 0;
    dst->unk24 = -1;
    dst->unk1E = 0;
}
