#include "global.h"
#include "data_symbols.h"
/* match-compiler: old_agbcc */
void sub_08060D58(struct Unk0798 *state, u32 x_arg, u32 y_arg, u32 w_arg, u32 h_arg, u32 tile_arg)
{
    u32 x = (u8)x_arg;
    u32 y = (u8)y_arg;
    u32 width = (u8)w_arg;
    u32 height = (u8)h_arg;
    u32 tilePacked = tile_arg << 16;
    u32 tileId = 0;
    u16 baseTile;
    u32 vramBase;
    u8 *vram;
    void **cpuLoc;
    u32 row, col, rowNext;
    u32 widthShifted, widthU;
    u16 *cell;
    u8 bank;

    tileId = 0;
    baseTile = state->unk96;
    bank = state->unk5C;
    vramBase = bank << 11;
    vramBase += 0xC0 << 19;
    vram = (u8 *)vramBase;
    cpuLoc = (void **)gData_080BB8BC;
    _08073C4C((void *)((tilePacked >> 16) | tilePacked | baseTile), vram, 0x80 << 4, *cpuLoc);
    vram += ((y << 5) + x) << 1;
    row = 0;
    if (0 < height) {
        widthShifted = width << 16;
        widthU = widthShifted >> 16;
        do {
            col = 0;
            rowNext = row + 1;
            if (0 < widthU) {
                do {
                    cell = (u16 *)(vram + (((row << 5) + col) << 1));
                    *cell = (u16)(tileId | baseTile);
                    tileId = (u16)(tileId + 1);
                    col = (u16)(col + 1);
                } while (col < (widthShifted >> 16));
            }
            row = (u16)rowNext;
        } while (row < height);
    }
    state->unk98 = (u16)(width << 3);
    state->unk9A = (u16)(height << 3);
    state->unkA4 = (u16)x;
    state->unkA6 = (u16)y;
}
