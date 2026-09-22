#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08051444

void sub_08051578(u32 a, s32 b, u32 c);
void sub_08051504(void *a);

void sub_08051444(void *a, void *b)
{
    struct Unk617C4 *gfx;
    u32 pal;

    sub_080674B4();
    TextSetCursor(0, 0);
    gfx = (struct Unk617C4 *)gData_080D79CC;
    pal = (u32)gData_080B7429;
    sub_080617C4(gfx, pal);
    TextDrawAlign((void *)gData_083A858C, TextGetAreaWidth() >> 1, 0);
    sub_08051578((u32)a, 0, gData_080969CC[gMainWorkPtr->unk1818]);
    sub_08051578((u32)a, 1, gData_080969E0[gMainWorkPtr->unk1818]);
    sub_080617C4(gfx, pal);
    TextSetCursor(0, 0x28);
    TextDrawAlign((void *)gData_083A8598, TextGetAreaWidth() >> 1, 0);
    sub_08051504(a);
}

