/* match-compiler: old_agbcc */
#include "global.h"

void sub_0806114C(
    struct Unk6114C *state,
    u32 tile,
    u32 palette,
    u32 first,
    u32 last)
{
    u32 temp;
    u16 *screen;

    tile &= 0x1F;
    first &= 0x1F;
    last &= 0x1F;
    if (last < first)
    {
        temp = first;
        first = last;
        last = temp;
    }
    screen = (u16 *)(VRAM + (state->unk5C << 11) + (tile << 6));
    palette = (palette & 0x0F) << 12;
    for (; first <= last; first++)
    {
        *screen = (*screen & 0x03FF) | palette;
        screen++;
    }
}
