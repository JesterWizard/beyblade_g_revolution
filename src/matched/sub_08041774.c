#include "global.h"

// @ 0x08041774
void sub_08041774(void *a_arg, void *b_arg, s8 c)
{
    struct Unk40F4C *a;
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
    a->unk25C = (void *)b->unk18;
    a->unk260 = (void *)b->unk1C;
    a->unk264 = (void *)b->unk20;
    a->unk268 = (void *)b->unk24;
    a->unk26C = (void *)b->unk28;
    a->unk270 = (void *)b->unk2C;
    a->unk2D9 = b->unk4E;
}

