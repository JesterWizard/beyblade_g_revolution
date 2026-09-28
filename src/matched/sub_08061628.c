#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08061628
/* match-compiler: old_agbcc */
// Fill the window's BG map (screenblock unk5C) with the fill tile, then lay
// out a w x h block of consecutive tiles at (x, y) and record its pixel size
// and position.
void TextWindowLayout(u32 xArg, u32 yArg, u32 wArg, u32 hArg, u32 fillArg)
{
    u8 x = xArg;
    u8 y = yArg;
    u8 w = wArg;
    u8 h = hArg;
    u32 fill = fillArg << 16;
    u16 tile;
    u16 base;
    u16 *map;
    u16 row, col;

    tile = 0;
    base = gData_03000798->unk96;
    map = (u16 *)(gData_03000798->unk5C * 0x800 + 0x06000000);
    ((void (*)(u32, void *, u32))gData_080BB8BC[0])((fill >> 16) | fill | base, map, 0x800);
    map += y * 32 + x;
    for (row = 0; row < h; row++)
    {
        for (col = 0; col < w; col++)
        {
            map[row * 32 + col] = tile | base;
            tile++;
        }
    }
    gData_03000798->unk98 = w << 3;
    gData_03000798->unk9A = h << 3;
    gData_03000798->unkA4 = x;
    gData_03000798->unkA6 = y;
}

