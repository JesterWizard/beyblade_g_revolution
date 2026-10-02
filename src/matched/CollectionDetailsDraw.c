#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0804aaf0
/* match-compiler: old_agbcc */
// Select the record at the browser cursor and print its detail lines.
void CollectionDetailsDraw(void *a)
{
    void *buffer;

    buffer = StringAlloc(0x10);
    gUnk_03000660 = gData_03000658[gData_03000654];
    TextSetCursor(0, 0x18);
    TextDrawAlign((void *)sub_0803EBB0(gUnk_03000660->attackRing), 0xC4, 1);
    TextSetCursor(0, 0x20);
    TextDrawAlign((void *)sub_0803ECB8(gUnk_03000660->weightDisk), 0xC4, 1);
    TextSetCursor(0, 0x28);
    TextDrawAlign((void *)sub_0803EC34((s8)gUnk_03000660->bladeBase), 0xC4, 1);
    if (gUnk_03000660->coreFlags & 0x40)
    {
        TextSetCursor(0, 0x30);
        TextDrawAlign((void *)0x083A74F0, 0xC4, 1);
    }
    else
    {
        TextSetCursor(0, 0x30);
        TextDrawAlign((void *)0x083A74FC, 0xC4, 1);
    }
    TextSetCursor(0, 0x38);
    if (gUnk_03000660->beybladeId == -1)
        TextDrawAlign((void *)0x083A7508, 0xC4, 1);
    else
        TextDrawAlign((void *)BeybladeNameGet(gUnk_03000660->beybladeId), 0xC4, 1);
    TextFormatInt(gUnk_03000660->unk26, buffer, 0x10);
    TextSetCursor(0, 0x40);
    TextDrawAlign(buffer, 0xC4, 1);
    TextSetCursor(0, 0x48);
    TextDrawAlign((void *)sub_0803DD60(gUnk_03000660->coreFlags & 3), 0xC4, 1);
    StringFree(buffer);
}

