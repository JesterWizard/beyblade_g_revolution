#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0802BAD4 */
// @ 0x0802bad4
// This caller was built against an older (s8, s8, u8) prototype of
// sub_0803DEC8; its definition takes (u16, u8, u8).
#define BeybladeRecordClaimS8(a, b, c) ((void (*)(s8, s8, u8))BeybladeRecordClaim)(a, b, c)

// Claims the first free CollectionEntry slot (word 0xFF0000FF) for (kind, group, c, d),
// if the group still has room. Group 1 first registers the entry through
// sub_0802C3DC/sub_0803DEC8 (logging and skipping the slot on failure). Retail
// has a separate copy of the slot writes in each branch. Returns 1 once a free
// slot was found, else 0.
s32 CollectionAddItem(u8 kind, u8 group, u8 c, u8 d)
{
    s32 i;
    s32 err;

    if (gMainWorkPtr->unk1694 == NULL)
        return 0;
    if (CollectionCountByKind(group) >= _0802BA7C(group))
        return 0;
    for (i = 0; i <= 0x7F; i++)
    {
        if (((u32 *)gMainWorkPtr->unk1694)[i] == 0xFF0000FF)
        {
            if ((s8)group == 1)
            {
                err = CollectionFindByGroupKind(1, kind, NULL);
                if (err == 0)
                {
                    BeybladeRecordClaimS8(kind, d, i);
                    gMainWorkPtr->unk1694[i].value = err;
                    gMainWorkPtr->unk1694[i].kind = kind;
                    gMainWorkPtr->unk1694[i].group = group;
                    gMainWorkPtr->unk1694[i].slot = c;
                    gMainWorkPtr->unk1694[i].value = d;
                }
                else
                    DebugPrint((void *)0x0833BE1C, (s8)kind);
            }
            else
            {
                gMainWorkPtr->unk1694[i].kind = kind;
                gMainWorkPtr->unk1694[i].group = group;
                gMainWorkPtr->unk1694[i].slot = c;
                gMainWorkPtr->unk1694[i].value = d;
            }
            return 1;
        }
    }
    return 0;
}

/* fn: sub_0802BC14 */
// @ 0x0802bc14
/* A free CollectionEntry slot reads as the word 0xFF0000FF (unk00 = unk03 = 0xFF). */
s32 CollectionIsFull(s16 a)
{
    s32 count;
    s32 limit;
    s32 i;

    count = CollectionCountByKind((s8)a);
    limit = _0802BA7C((s8)a);
    DebugPrint((void *)0x0833BE30, (s16)a, count, limit);
    if (count < limit)
    {
        if (gMainWorkPtr->unk1694 != NULL)
        {
            for (i = 0; i <= 0x7F; i++)
            {
                if (((u32 *)gMainWorkPtr->unk1694)[i] == 0xFF0000FF)
                    return 0;
            }
        }
    }
    return 1;
}

/* fn: sub_0802C314 */
// @ 0x0802c314
/* match-compiler: old_agbcc */

s32 CollectionFindByGroupSlot(s8 a, u8 b, struct CollectionLookup *out)
{
    s32 i;

    if (out != NULL)
    {
        out->index = -1;
        out->kind |= 0xFF;
        out->group |= 0xFF;
        out->value = 0;
        out->slot = 0;
        out->entry = NULL;
    }
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].group == a && gMainWorkPtr->unk1694[i].slot == (s8)b)
            {
                if (out != NULL)
                {
                    out->index = i;
                    out->kind = gMainWorkPtr->unk1694[i].kind;
                    out->group = gMainWorkPtr->unk1694[i].group;
                    out->value = gMainWorkPtr->unk1694[i].value;
                    out->slot = gMainWorkPtr->unk1694[i].slot;
                    out->entry = &gMainWorkPtr->unk1694[i];
                }
                return 1;
            }
        }
    }
    return 0;
}

/* fn: sub_0802C3DC */
// @ 0x0802c3dc
/* match-compiler: old_agbcc */

s32 CollectionFindByGroupKind(s8 a, s8 b, struct CollectionLookup *out)
{
    s32 i;

    if (out != NULL)
    {
        out->index = -1;
        out->kind |= 0xFF;
        out->group |= 0xFF;
        out->value = 0;
        out->slot = 0;
        out->entry = NULL;
    }
    if (gMainWorkPtr->unk1694 != NULL)
    {
        for (i = 0; i <= 0x7F; i++)
        {
            if ((s8)gMainWorkPtr->unk1694[i].group == a && (s8)gMainWorkPtr->unk1694[i].kind == b)
            {
                if (out != NULL)
                {
                    out->index = i;
                    out->kind = gMainWorkPtr->unk1694[i].kind;
                    out->group = gMainWorkPtr->unk1694[i].group;
                    out->value = gMainWorkPtr->unk1694[i].value;
                    out->slot = gMainWorkPtr->unk1694[i].slot;
                    out->entry = &gMainWorkPtr->unk1694[i];
                }
                return 1;
            }
        }
    }
    return 0;
}

/* fn: sub_0802C55C */
// @ 0x0802c55c
/* match-compiler: old_agbcc */
// Free slot `i` of the MainWork.unk1694 table if it holds (a, b); a freed
// kind-1 slot also notifies sub_0803E0CC.
void CollectionFreeSlot(u16 a, u8 b, s16 i)
{
    s8 kind;

    if (i > 0x7F)
        return;
    if ((s8)gMainWorkPtr->unk1694[i].kind != (s16)a)
        return;
    kind = (s8)gMainWorkPtr->unk1694[i].group;
    if (kind != (s8)b)
        return;
    gMainWorkPtr->unk1694[i].kind |= 0xFF;
    gMainWorkPtr->unk1694[i].group |= 0xFF;
    gMainWorkPtr->unk1694[i].value = 0;
    gMainWorkPtr->unk1694[i].slot = 0;
    if (kind == 1)
        RemoveBladeFromTysonsCollection(i);
}

/* fn: sub_0802C62C */
// @ 0x0802c62c
// Count the 4-byte entries of gMainWorkPtr->unk1694 (128 of them) whose signed +3 byte
// equals `a`, sign-extended. Twin of sub_0802C5DC (which sets unk01 and returns at the
// first hit). `val` must be initialised before `count`: retail truncates the argument
// (`a << 24 >> 24`, then `<< 24 >> 24` signed) ahead of the `movs r3,#0` that zeroes the
// counter; with `s32 count = 0;` declared first the mov lands first and the function
// floors at 59/64.
s32 CollectionCountByKind(s8 a)
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
            if ((s8)gMainWorkPtr->unk1694[i].group == val)
                count++;
        }
    }
    return count;
}

/* fn: sub_0802FA94 */
// @ 0x0802fa94
// Draw the three visible rows of the gData_03000278 item list: name
// (highlighted row = cursor), a per-language category label for kinds 2/3
// (sub_0803DD88 name for kind 1) and the count; empty rows get the
// gData_08096B5C placeholder.

void ItemListDraw(void)
{
    s32 i;
    u8 *buf;
    s32 name;

    TextGetAreaWidth();
    buf = StringAlloc(0x10);
    for (i = 0; i <= 2; i++)
    {
        if (gData_03000278->items[gData_03000278->top + i].count > 0)
        {
            TextSetCursor(0, i * 16 + 0x40);
            if (i == gData_03000278->cursor)
            {
                name = _08056428(gData_03000278->items[gData_03000278->top + i].kind, gData_03000278->items[gData_03000278->top + i].id);
                if (name != 0)
                    TextGroupSetString((struct TextGroup *)gData_03000278->text, (void *)name, 15);
                else if (gData_03000278->items[gData_03000278->top + i].name != NULL)
                    TextGroupSetString((struct TextGroup *)gData_03000278->text, gData_03000278->items[gData_03000278->top + i].name, 15);
                TextSetPaletteBank(14);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 14, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 14, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(15);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 15, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 15, 2, 0x1B);
            }
            switch (gData_03000278->items[gData_03000278->top + i].kind)
            {
            case 2:
                switch (gData_03000278->items[gData_03000278->top + i].id)
                {
                case 4:
                    TextDrawAlign(gData_080970D4[gData_03000198->language], 0x0C, 2);
                    break;
                case 3:
                    TextDrawAlign(gData_080970E8[gData_03000198->language], 0x0C, 2);
                    break;
                case 2:
                    TextDrawAlign(gData_080970FC[gData_03000198->language], 0x0C, 2);
                    break;
                case 1:
                    TextDrawAlign(gData_08097110[gData_03000198->language], 0x0C, 2);
                    break;
                }
                break;
            case 3:
                switch (gData_03000278->items[gData_03000278->top + i].id)
                {
                case 4:
                    TextDrawAlign(gData_08097084[gData_03000198->language], 0x0C, 2);
                    break;
                case 3:
                    TextDrawAlign(gData_08097098[gData_03000198->language], 0x0C, 2);
                    break;
                case 2:
                    TextDrawAlign(gData_080970AC[gData_03000198->language], 0x0C, 2);
                    break;
                case 1:
                    TextDrawAlign(gData_080970C0[gData_03000198->language], 0x0C, 2);
                    break;
                }
                break;
            case 1:
                TextDrawAlign((void *)GetBeybladeNameWithIndex(gData_03000278->items[gData_03000278->top + i].id), 0x0C, 2);
                break;
            }
            if (gData_03000278->top + i < gData_03000278->count - 1)
            {
                StringClear(buf);
                TextFormatInt(gData_03000278->items[gData_03000278->top + i].count, buf, 0x10);
                TextDrawAlign(buf, 0xD4, 1);
            }
        }
        else
        {
            if (i == gData_03000278->cursor)
            {
                TextSetPaletteBank(14);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 14, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 14, 2, 0x1B);
            }
            else
            {
                TextSetPaletteBank(15);
                TextRowSetPaletteBank((u16)(i * 2 + 12), 15, 2, 0x1B);
                TextRowSetPaletteBank((u16)(i * 2 + 13), 15, 2, 0x1B);
            }
            TextSetCursor(0, i * 16 + 0x40);
            TextDrawAlign(gData_08096B5C[gData_03000198->language], 0x0C, 2);
        }
    }
    StringFree(buf);
}

/* fn: sub_0803E0CC */
// @ 0x0803e0cc
/* match-compiler: old_agbcc */
// Release every collection slot whose blade id (unk23) matches: log it, mark
// the slot's fields empty (0xFF / 0xFFFF), free the slot flag, drop the active
// count and bump the per-type counter indexed by the slot's (now -1) unk1C.
void RemoveBladeFromTysonsCollection(s16 a)
{
    u16 id = a;
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gData_03000198->unk08D0[i].unk23 == (s16)id && gData_03000198->unk087C[i] == 1)
        {
            DebugPrint((void *)0x0833D34C, (void *)0x0833D358, gData_03000198->unk08D0[i].unk23);
            gData_03000198->unk08D0[i].unk1D |= 0xFF;
            gData_03000198->unk08D0[i].unk21 |= 0xFF;
            gData_03000198->unk08D0[i].unk20 |= 0xFF;
            gData_03000198->unk08D0[i].unk26 = 0xFFFF;
            gData_03000198->unk08D0[i].unk1F |= 0xFF;
            gData_03000198->unk08D0[i].unk1C |= (s8)0xFF;
            gData_03000198->unk08D0[i].unk1E |= 0xFF;
            gData_03000198->unk08D0[i].unk23 |= 0xFF;
            gData_03000198->unk087C[i] = 0;
            gData_03000198->unk0877--;
            gData_03000198->unk1861[gData_03000198->unk08D0[i].unk1C]++;
        }
    }
}

/* fn: sub_0803E1F4 */
// @ 0x0803e1f4
void *CollectionFindEntry(s16 a, s16 b)
{
    s32 i;

    for (i = 0; i <= 0x52; i++)
    {
        if (gMainWorkPtr->unk08D0[i].unk23 == b
            && gMainWorkPtr->unk08D0[i].unk1C == a
            && gMainWorkPtr->unk087C[i] == 1)
        {
            return &gMainWorkPtr->unk08D0[i];
        }
    }

    return 0;
}

/* fn: sub_08042E78 */
// @ 0x08042e78
/* match-compiler: old_agbcc */
void *BeybladeCollectionEntry(u32 i)
{
    if (i > 0x36)
        return 0;
    return (u8 *)*(u32 *)gUnk_03000540 + i * 48;
}

/* fn: sub_0804AAF0 */
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

/* fn: sub_0804AE94 */
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
