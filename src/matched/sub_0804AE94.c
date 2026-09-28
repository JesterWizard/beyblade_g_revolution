#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804ae94
// Builds the browser caption for the record at the cursor: "<index><sep>
// <name><sep><title>" (indices above 0x36 use a fixed suffix instead of the
// title) and shows it with sub_08054558.
void CollectionCaptionDraw(void)
{
    u8 *line;
    u8 *num;

    line = StringAlloc(0x80);
    num = StringAlloc(0x80);
    gData_03000660 = gData_03000658[gData_03000654];
    if (gData_03000654 <= 0x36)
    {
        TextFormatInt(gData_03000654, num, 0x80);
        StringCopy((u8 *)0x083A7510, line, 0x80);
        StringAppend(num, line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)GetBeybladeNameWithIndex(gData_03000660->unk1C), line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend(BeybladeGetName(gData_03000654), line, 0x80);
        sub_08054558(line);
    }
    else
    {
        TextFormatInt(gData_03000654, num, 0x80);
        StringCopy((u8 *)0x083A7510, line, 0x80);
        StringAppend(num, line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)GetBeybladeNameWithIndex(gData_03000660->unk1C), line, 0x80);
        StringAppend((const u8 *)0x083A7518, line, 0x80);
        StringAppend((const u8 *)0x083A751C, line, 0x80);
        sub_08054558(line);
    }
    StringFree(line);
    StringFree(num);
}

