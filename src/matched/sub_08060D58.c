#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08060d58
/* match-compiler: old_agbcc */
// Fill the BG screen block with the fill pattern, then lay a width x height
// run of consecutive tile ids (| baseTile) at (x, y) and record the window.
void TextWindowFillMap(struct TextWindow *state, u32 x_arg, u32 y_arg, u32 w_arg, u32 h_arg, u32 tile_arg)
{
    u8 x = x_arg;
    u8 y = y_arg;
    u8 width = w_arg;
    u8 height = h_arg;
    u16 tile = tile_arg;
    u16 tileId;
    u16 baseTile;
    u16 *vram;
    u16 row;
    u16 col;
    u32 *fillSrc;

    tileId = 0;
    baseTile = state->baseTile;
    vram = (u16 *)(VRAM + (state->screenBlock << 11));
    fillSrc = gData_080BB8BC;
    _08073C4C((void *)(tile | (tile << 16) | baseTile), vram, 0x800, (void *)*fillSrc);
    vram += (y << 5) + x;
    for (row = 0; row < height; row++)
    {
        for (col = 0; col < width; col++)
        {
            vram[row * 32 + col] = tileId | baseTile;
            tileId++;
        }
    }
    state->width = width << 3;
    state->height = height << 3;
    state->unkA4 = x;
    state->unkA6 = y;
}

