#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804ae94
// Builds the browser caption for the record at the cursor: "<index><sep>
// <name><sep><title>" (indices above 0x36 use a fixed suffix instead of the
// title) and shows it with sub_08054558.
void sub_0804AE94(void)
{
    u8 *line;
    u8 *num;

    line = BtlObjTableAdd(0x80);
    num = BtlObjTableAdd(0x80);
    gData_03000660 = gData_03000658[gData_03000654];
    if (gData_03000654 <= 0x36)
    {
        TextFormatInt(gData_03000654, num, 0x80);
        sub_08073218((u8 *)0x083A7510, line, 0x80);
        StringAppend(num, line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)sub_0803DD88(gData_03000660->unk1C), line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend(sub_08042B00(gData_03000654), line, 0x80);
        sub_08054558(line);
    }
    else
    {
        TextFormatInt(gData_03000654, num, 0x80);
        sub_08073218((u8 *)0x083A7510, line, 0x80);
        StringAppend(num, line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)sub_0803DD88(gData_03000660->unk1C), line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)0x083A751C, line, 0x80);
        sub_08054558(line);
    }
    BtlObjTableRemove(line);
    BtlObjTableRemove(num);
}

