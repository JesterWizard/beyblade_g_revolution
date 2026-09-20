#include "global.h"

void sub_0804188C(void)
{
    register s32 i asm("r7");
    register s32 fixed asm("r4");
    register struct Unk68574 **entries asm("r6");
    register struct Unk68574 *obj asm("r5");
    s32 value;
    s32 shifted;
    u32 normalized;
    u16 color;

    i = 0;
    if (*(s16 *)gUnk_03000504 <= 0)
        return;
    sub_08062B9C(3, 0x0F);
    if (i >= *(s16 *)gUnk_03000504)
        return;
    entries = (struct Unk68574 **)gUnk_03000480;
    while (i < *(s16 *)gUnk_03000504)
    {
        fixed = i << 16;
        obj = entries[i];
        sub_08068418(obj);
        if (obj->unkB8 != 0)
        {
            if (obj->unkD8 == (void *)1)
            {
                obj->unkBC = 0xFFFF;
                sub_08070468(obj->unkB8, obj->unkBC);
            }
            else
            {
                obj->unkBC = ~(obj->unk08 >> 8);
                sub_08070468(obj->unkB8, obj->unkBC);
            }
            if (obj->unkD8 == 0)
                value = sub_08062AF8((void *)0x080775CC, obj->unkD4);
            else
                value = sub_08062AF8((void *)0x080779A8, obj->unkD4);
            normalized = (value << 24) >> 8;
            color = normalized >> 16;
            obj->unk3A = (color << 1) | 1;
        }
        sub_08067CE8(obj, 0);
        i = (fixed + 0x10000) >> 16;
    }
}
