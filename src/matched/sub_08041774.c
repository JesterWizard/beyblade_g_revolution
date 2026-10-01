#include "global.h"

// @ 0x08041774
void sub_08041774(void *a_arg, void *b_arg, s8 c)
{
    struct MenuState *a;
    struct Unk4109CInput *b;

    a = a_arg;
    b = b_arg;
    a->unk248 = b;
    a->unk2D4 = c;
    a->unk24C = (void *)b->unk00;
    a->unk250 = (void *)b->unk04;
    a->unk254 = (void *)b->unk08;
    a->unk258 = (void *)b->unk0C;
    a->unk240 = (void *)b->unk10;
    a->unk244 = (void *)b->unk14;
    a->onLeft = (void *)b->unk18;
    a->onRight = (void *)b->unk1C;
    a->onUp = (void *)b->unk20;
    a->onDown = (void *)b->unk24;
    a->onButtonA = (void *)b->unk28;
    a->onButtonB = (void *)b->unk2C;
    a->unk2D9 = b->unk4E;
}

