#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804db28
/* match-compiler: old_agbcc */
// Rebuild the object pool for scene gData_03000694: reset all nine
// objects, lay out eight in a 4x2 grid from the scene's gData_0807BE04 source,
// load their palette, pick each one's animation, and set up the optional ninth
// object when the scene has one (otherwise park it off-screen).
void sub_0804DB28(void)
{
    s32 i;

    for (i = 0; i < 9; i++)
        sub_08068808(&gData_03000698[i]);

    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[0], gData_0807BE04[gData_03000694].unk10, 0, 0x32, 0x34, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[1], gData_0807BE04[gData_03000694].unk10, 0, 0x5A, 0x34, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[2], gData_0807BE04[gData_03000694].unk10, 0, 0x82, 0x34, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[3], gData_0807BE04[gData_03000694].unk10, 0, 0xAA, 0x34, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[4], gData_0807BE04[gData_03000694].unk10, 0, 0x32, 0x6C, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[5], gData_0807BE04[gData_03000694].unk10, 0, 0x5A, 0x6C, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[6], gData_0807BE04[gData_03000694].unk10, 0, 0x82, 0x6C, 0, -1);
    sub_08067BB8((struct Unk67BB8 *)&gData_03000698[7], gData_0807BE04[gData_03000694].unk10, 0, 0xAA, 0x6C, 0, -1);

    gData_03000698[0].unk3A = 0x1F;
    gData_03000698[1].unk3A = 0x1F;
    gData_03000698[2].unk3A = 0x1F;
    gData_03000698[3].unk3A = 0x1F;
    gData_03000698[4].unk3A = 0x1F;
    gData_03000698[5].unk3A = 0x1F;
    gData_03000698[6].unk3A = 0x1F;
    gData_03000698[7].unk3A = 0x1F;

    _08073C4C(gData_080775CC[gData_03000694], (void *)0x050003E0, 0x20, (void *)gData_080BB8C0[0]);

    sub_080680CC((struct Unk680CC *)&gData_03000698[0], 5);
    gData_03000698[0].unk31 &= 2;
    sub_080680CC((struct Unk680CC *)&gData_03000698[1], 5);
    gData_03000698[1].unk31 |= 1;
    sub_080680CC((struct Unk680CC *)&gData_03000698[2], 6);
    gData_03000698[2].unk31 = 0;
    sub_080680CC((struct Unk680CC *)&gData_03000698[3], 7);
    gData_03000698[3].unk31 = 0;
    sub_080680CC((struct Unk680CC *)&gData_03000698[4], 8);
    gData_03000698[4].unk31 &= 2;
    sub_080680CC((struct Unk680CC *)&gData_03000698[5], 8);
    gData_03000698[5].unk31 |= 1;
    sub_080680CC((struct Unk680CC *)&gData_03000698[6], 10);
    gData_03000698[6].unk31 = 0;
    sub_080680CC((struct Unk680CC *)&gData_03000698[7], 11);
    gData_03000698[7].unk31 = 0;

    sub_08054558(gData_08098A20[gData_03000694]);

    if (gData_08098DF8[gData_03000694] != NULL && gData_080991D0[gData_03000694] != NULL)
    {
        sub_08067BB8((struct Unk67BB8 *)&gData_03000698[8], gData_080991D0[gData_03000694], 0, 0x8C, 3, 0, -1);
        _08073C4C(gData_08098DF8[gData_03000694], (void *)0x050003C0, 0x20, (void *)gData_080BB8C0[0]);
        gData_03000698[8].unk3A = 0x1D;
    }
    else
    {
        gData_03000698[8].unk04 = -0x4000;
        gData_03000698[8].unk08 = -0x4000;
    }

    for (i = 0; i <= 8; i++)
    {
        if (gData_03000698[i].unk00 != NULL)
        {
            sub_08068418(&gData_03000698[i]);
            sub_08067CE8(&gData_03000698[i], 0);
        }
    }
}

