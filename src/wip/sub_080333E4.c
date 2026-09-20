#include "global.h"

u32 sub_08038438(void *a);
void sub_08067BB8(
    void *a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void sub_08068584(void *a, s32 b, s32 c);

void sub_080333E4(void *arg, s32 x, s32 y, u32 mode)
{
    void *arg_reg;
    s32 x_reg;
    s32 y_reg;
    u32 mode_reg;
    struct BattleWork *work;
    u32 resource_id;
    void *resource;

    arg_reg = arg;
    x_reg = x;
    y_reg = y;
    mode_reg = (u8)mode;
    if (mode_reg > 4)
        return;
    work = gBattleWork;
    if (work->unk2088 == 1 &&
        (s8)work->unk2089 != (s8)mode_reg)
        sub_08033574();
    work = gBattleWork;
    if (work->unk2088 == 0)
    {
        resource = ((void **)0x08078108)[mode_reg];
        resource_id = (u16)sub_08038438(resource);
        sub_08067BB8(
            &work->unk1FAC, resource, 0, (s32)arg_reg,
            x_reg, y_reg, -1);
        sub_08068584(&work->unk1FAC, 0x20, 0x20);
        work->unk201C = sub_08067FC8(&work->unk1FAC, 0);
        work->unk1FE6 =
            (work->unk1FE6 & 1) | ((u8)(resource_id << 1));
        work->unk2088 = 1;
    }
    else if ((s8)work->unk2089 == (s8)mode_reg)
    {
        work->unk201C += sub_08067FC8(&work->unk1FAC, 0);
    }
}
