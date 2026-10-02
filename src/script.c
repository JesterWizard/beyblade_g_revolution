#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_08045D3C */
// @ 0x08045d3c
// Event-flag operations on the 256-bit set gData_03000610 (flag `id`):
// 0 clear all, 1 clear, 2 set, 3 toggle, 4 test into *out; 0x3EA/0x3EB save
// to / load from the current save slot, 0x3EC/0x3ED to / from unk18B8.
void EventFlagOp(u8 id, u32 op, u32 *out)
{
    u32 group;
    u8 bit;
    struct Unk45D3CEntry *entry;
    u32 *live;
    u32 *saved;
    s32 i;

    group = id >> 5;
    bit = id & 0x1F;
    switch (op)
    {
    case 0:
        gData_03000610.words[0] = 0;
        gData_03000610.words[1] = 0;
        gData_03000610.words[2] = 0;
        gData_03000610.words[3] = 0;
        gData_03000610.words[4] = 0;
        gData_03000610.words[5] = 0;
        gData_03000610.words[6] = 0;
        gData_03000610.words[7] = 0;
        break;
    case 1:
        gData_03000610.words[group] &= ~(1 << bit);
        break;
    case 2:
        gData_03000610.words[group] |= 1 << bit;
        break;
    case 3:
        gData_03000610.words[group] ^= 1 << bit;
        break;
    case 4:
        *out = gData_03000610.words[group] & (1 << bit);
        break;
    case 0x3EA:
        entry = &gMainWorkPtr->unk168C[SaveSlotGet()];
        live = gData_03000610.words;
        saved = entry->words;
        for (i = 7; i >= 0; i--)
            *saved++ = *live++;
        break;
    case 0x3EB:
        entry = &gMainWorkPtr->unk168C[SaveSlotGet()];
        saved = entry->words;
        live = gData_03000610.words;
        for (i = 7; i >= 0; i--)
            *live++ = *saved++;
        break;
    case 0x3EC:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            live = gData_03000610.words;
            saved = entry->words;
            for (i = 7; i >= 0; i--)
                *saved++ = *live++;
        }
        break;
    case 0x3ED:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            saved = entry->words;
            live = gData_03000610.words;
            for (i = 7; i >= 0; i--)
                *live++ = *saved++;
        }
        break;
    }
}

/* fn: sub_08045EF0 */
// @ 0x08045ef0
/* match-compiler: old_agbcc */
// Byte-variable operations on the 16 script bytes gData_03000600 (`index`):
// 11 set, 5 clear all, 6/7 increment/decrement, 8/9/10 compare ==, <, > into
// *out; 0x3E8/0x3E9 save to / load from the current save slot, 0x3EE/0x3EF
// load from / save to unk18B8.
void EventByteVarOp(u8 index, u8 value, u32 op, u32 *out)
{
    struct Unk45D3CEntry *entry;
    s8 i;

    switch (op)
    {
    case 11:
        gData_03000600.bytes[(s8)index] = value;
        break;
    case 5:
        for (i = 0; i < 16; i++)
            gData_03000600.bytes[i] = 0;
        break;
    case 6:
        gData_03000600.bytes[(s8)index]++;
        break;
    case 7:
        gData_03000600.bytes[(s8)index]--;
        break;
    case 8:
        *out = gData_03000600.bytes[(s8)index] == value;
        break;
    case 9:
        *out = (s8)gData_03000600.bytes[(s8)index] < (s8)value;
        break;
    case 10:
        *out = (s8)gData_03000600.bytes[(s8)index] > (s8)value;
        break;
    case 0x3E8:
        entry = &gMainWorkPtr->unk168C[SaveSlotGet()];
        for (i = 0; i < 16; i++)
            entry->bytes_70[i] = gData_03000600.bytes[i];
        break;
    case 0x3E9:
        entry = &gMainWorkPtr->unk168C[SaveSlotGet()];
        for (i = 0; i < 16; i++)
            gData_03000600.bytes[i] = entry->bytes_70[i];
        break;
    case 0x3EE:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            for (i = 0; i < 16; i++)
                gData_03000600.bytes[i] = entry->bytes_70[i];
        }
        break;
    case 0x3EF:
        entry = gMainWorkPtr->unk18B8.unk04;
        if (entry != NULL)
        {
            for (i = 0; i < 16; i++)
                entry->bytes_70[i] = gData_03000600.bytes[i];
        }
        break;
    }
}

/* fn: sub_08056D68 */
// @ 0x08056d68
// Dispatches a script event by its 16-bit key; the event's arguments start at
// unk08. Key 0x47EE is recognised but ignored.
void ScriptDispatchEvent(struct ScriptEvent *event)
{
    s16 *entry;
    u32 *args;

    switch (event->key)
    {
    case 0x9E3B:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        args = &event->args;
        gMainWorkPtr->unk181D = 0;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(0, 1);
        break;
    case 0xBEE4:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        args = &event->args;
        gMainWorkPtr->unk181D = 1;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(1, 1);
        entry = FindEntryByString(gMainWorkPtr->unk16C8);
        if (entry != NULL)
            gMainWorkPtr->unk1794 = *entry;
        else
            gMainWorkPtr->unk1794 = -1;
        break;
    case 0xCE50:
        args = &event->args;
        gMainWorkPtr->unk16C8 = args;
        sub_08056F84();
        break;
    case 0xE319:
        args = &event->args;
        gMainWorkPtr->unk16C8 = args;
        ScriptRun(0, BtlFindUnk16E4());
        break;
    case 0x6A74:
        gMainWorkPtr->unk1828 = event->args;
        break;
    case 0x5989:
        gMainWorkPtr->unk182C = event->args;
        break;
    case 0x3D73:
        gMainWorkPtr->unk17F7 = event->args;
        gMainWorkPtr->unk17F6 = event->unk0C;
        gMainWorkPtr->unk1834 = 1;
        break;
    case 0xD791:
        args = &event->args;
        gMainWorkPtr->unk181D = 3;
        gMainWorkPtr->unk16C8 = args;
        sub_0802D52C(3, 1);
        break;
    case 0x47EE:
        break;
    }
}

/* fn: sub_08059DC8 */
typedef u32 *(*ScriptCmdFunc)(u32 *cmd, u32 *a, u32 *b, u32 *done);

// @ 0x08059dc8
// Runs a script: dispatches each command through the handler table until one
// sets `done`.
void ScriptRun(u32 arg0, void *script)
{
    u32 *cmd;
    u32 a;
    u32 b;
    u32 done;
    ScriptCmdFunc *table;

    cmd = script;
    a = 1;
    done = 0;
    b = 0;
    if (cmd == 0)
        return;
    gData_03000734 = arg0;
    table = (ScriptCmdFunc *)gData_08099710;
    while (done == 0)
        cmd = table[*cmd](cmd, &a, &b, &done);
}

/* fn: sub_08066440 */
// @ 0x08066440
void sub_08066440(u8 v)
{
    u32 tmp[2];

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    *(u8 *)tmp[0] = v;
}

/* fn: sub_0806644C */
// @ 0x0806644c
s8 sub_0806644C(void)
{
    u32 tmp[2];
    s32 val;

    tmp[0] = (u32)gUnk_03000970;
    tmp[0] += 0x35;
    val = *(u8 *)tmp[0];
    val <<= 24;
    val >>= 24;
    return (s8)val;
}
