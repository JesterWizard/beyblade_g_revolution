#include "global.h"

// @ 0x08073114
// 104/112 same_size. Retail: a in r3, table value in r1 (ldr r0,=loc; ldr r1,[r0]),
// count via ldr r0,=; adds r2,r0. Score-45 permuter seed; early target=a gets r3
// but drops to 108B. Next: permuter with PERM macros on table/count loads.
void BtlObjTableRemove(void *a)
{
    struct BtlObj **table;
    u8 *count;
    u32 i;
    void *new_var;

    table = *((struct BtlObj ***)0x03004150);
    if (table == 0)
        return;
    i = 0;
    count = (u8 *)0x03004154;
    new_var = a;
    while (i < (*count))
    {
        if ((table[i] != 0) && (table[i]->next == new_var))
        {
            HeapFree(table[i]);
            table[i] = 0;
            (*((u8 *)0x03004158))--;
            break;
        }
        i++;
    }

    if (i == (*((u8 *)0x03004154)))
        DebugPrint((void *)0x083D2690);
}
