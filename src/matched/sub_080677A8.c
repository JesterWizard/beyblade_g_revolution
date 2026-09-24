#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080677a8
#include "global.h"
#include "ram_map.h"

u32 sub_080677A8(u32 a, void *b)
{
    u16 *arg1;
    u16 x;
    u16 buf[4];
    u16 *p;
    u8 i;
    u32 result;
    u16 va;
    u16 vb;

    arg1 = (u16 *)b;
    x = (u16)a;
    result = 0;
    if (x >= gUnk_030009B0->unk04)
        return 0x80FF;

    sub_08067584(x, buf);
    p = buf;
    i = 0;
    goto compare;
matched:
    i = (u8)(i + 1);
    if (i > 3)
        goto done;
compare:
    va = *arg1;
    vb = *p;
    p++;
    arg1++;
    if (va == vb)
        goto matched;
    result = 0x80;
    result <<= 8;
done:
    return result;
}

