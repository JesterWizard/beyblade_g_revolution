#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060c30
/* match-compiler: old_agbcc */
// Window setup on an explicit window (cf. sub_0806121C for gData_03000798):
// clear it, record source and count, then lay out (sub_08060D58) and finish
// (sub_08060D28).
void TextWindowOpenEx(void *winArg, void *srcArg, void *c, u16 count, u16 y, u16 h, u16 x, u16 w, u16 i, u8 mode)
{
    struct Unk0798 *win = winArg;
    struct Unk617C4 *src = srcArg;
    u16 attr = i << 12;

    ((void (*)(u32, void *, u32))gData_080BB8BC[0])(0, win, 0xAC);
    win->unk88 = src;
    win->unk8C = (u32)c;
    win->unk94 = count;
    win->unk96 = attr;
    win->unkA0 = src->unk04;
    win->unkA2 = src->unk05;
    win->unk90 = 0;
    win->unk92 = 0;
    win->unk9C = win->unkA0 >> 2;
    win->unkA4 = 0;
    win->unkA6 = 0;
    sub_08068BD4((struct Unk68E54 *)win, mode, count, 0);
    sub_08060D58(win, (u8)x, (u8)w, (u8)y, (u8)h, (u16)(count - 1));
    sub_08060D28(win);
}

