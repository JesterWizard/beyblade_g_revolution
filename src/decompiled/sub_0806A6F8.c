#include "global.h"

// Poll keys (or play/record a u16 queue), then refresh per-button hold slots.
void sub_0806A6F8(void)
{
    u16 *state;
    u16 queueCount;
    u16 *cursor;
    u16 keys;
    u16 prev;
    u16 i;
    s32 bit;
    s32 held;
    struct Unk6A954 *slots;
    struct Unk6A954 *slot;

    state = (u16 *)gBtlState;
    if (*state == 2)
    {
        queueCount = *(u16 *)gBtlKeyQueueCount;
        if (queueCount == 0)
        {
            *state = queueCount;
        }
        else
        {
            cursor = *(u16 **)gBtlKeyQueuePtr;
            keys = *cursor;
            cursor++;
            *(u16 **)gBtlKeyQueuePtr = cursor;
            *(u16 *)gBtlKeyQueueCount = queueCount - 1;
        }
        *(u32 *)gUnk_03004068 = gData_03000180.unk00;
    }

    if (*state != 2)
    {
        keys = ~REG_KEYINPUT;
        if ((keys & 0x3FF) != 0)
            *(u32 *)gUnk_03004068 = gData_03000180.unk00;

        if (*state == 1)
        {
            queueCount = *(u16 *)gBtlKeyQueueCount;
            if (queueCount != 0)
            {
                cursor = *(u16 **)gBtlKeyQueuePtr;
                *cursor = keys;
                cursor++;
                *(u16 **)gBtlKeyQueuePtr = cursor;
                *(u16 *)gBtlKeyQueueCount = queueCount - 1;
            }
        }
    }

    prev = *(u16 *)gBtlInputMask;
    gData_03004060 = keys & ~prev;
    gData_0300406C = 0;
    gData_03004064 = prev;
    *(u16 *)gBtlInputMask = keys;

    slots = (struct Unk6A954 *)gUnk_03003F70;
    for (i = 0; i <= 9; i++)
    {
        bit = 1 << i;
        slot = &slots[i];
        if ((s32)(gData_03004060 & bit) > 0)
        {
            if (gData_03000180.unk00 > slot->unk04 + slot->unk0C)
                slot->unk10 = 1;
            else
                slot->unk10++;
            slot->unk14 = slot->unk00;
            slot->unk00 = gData_03000180.unk00;
        }

        held = *(u16 *)gBtlInputMask;
        if ((s32)(held & bit) > 0)
            slot->unk08 = gData_03000180.unk00 - slot->unk00;

        if (((held >> i) & 1) == 0)
        {
            if ((s32)(gData_03004064 & bit) > 0)
            {
                slot->unk04 = gData_03000180.unk00;
                slot->unk08 = gData_03000180.unk00 - slot->unk00;
                gData_0300406C |= bit;
            }
        }
    }
}
