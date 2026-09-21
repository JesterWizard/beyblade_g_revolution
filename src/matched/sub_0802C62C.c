#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802c62c
// Count the 4-byte entries of gMainWorkPtr->unk1694 (128 of them) whose signed +3 byte
// equals `a`, sign-extended. Twin of sub_0802C5DC (which sets unk01 and returns at the
// first hit). `val` must be initialised before `count`: retail truncates the argument
// (`a << 24 >> 24`, then `<< 24 >> 24` signed) ahead of the `movs r3,#0` that zeroes the
// counter; with `s32 count = 0;` declared first the mov lands first and the function
// floors at 59/64.
s32 sub_0802C62C(s8 a)
{
    s32 i;
    s32 count;
    s8 val;

    val = (s8)a;
    count = 0;
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if (gMainWorkPtr->unk1694[i].unk03 == val)
                count++;
        }
    }
    return count;
}

