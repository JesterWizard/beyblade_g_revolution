#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

/* fn: sub_080611A4 */
// @ 0x080611a4

// @ 0x080611a4
void VramSlotsInit(void)
{
    u32 *slotA;
    struct Unk0758 **slotB;
    void *p;

    slotA = (u32 *)gUnk_03000790;
    *slotA = 0;
    slotB = gUnk_03000798Loc;
    *slotB = 0;
    gUnk_03000794 = 0;
    p = HeapAlloc(0xAC);
    *slotA = (u32)p;
    if (p != 0)
    {
        *slotB = *(struct Unk0758 **)p;
        _08073C4C(0, *slotB, 0xAC, (void *)gData_080BB8BC[0]);
    }
    else
    {
        TextWindowClose();
    }
}

/* fn: sub_08061AB8 */
// @ 0x08061ab8
// ROM copy routine at gData_080BB8C0 (reached via _call_via_r3).
typedef void (*CopyFunc)(const void *src, void *dst, u32 size);

// Allocates the next of the 4 VRAM slots (gData_03000794 counts them) for the
// current graphic (gData_03000798): copies unk94 tiles from its VRAM block into a
// heap buffer and records the buffer and the graphic's unk90/unk92.
void VramSlotLoad(void)
{
    void **buffer;
    struct Unk0770 *slot;
    struct TextWindow *work;
    u32 n;
    void *vram;
    struct Unk0770 *table;

    if (gData_03000794[0] == 4)
        return;
    buffer = HeapAlloc(gData_03000798->tileCount << 5);
    table = (struct Unk0770 *)gData_03000770;
    table[gData_03000794[0]].unk00 = buffer;
    if (buffer == NULL)
        return;
    work = gData_03000798;
    vram = (void *)(VRAM + (work->charBlock << 14));
    ((CopyFunc)gData_080BB8C0[0])(vram, *buffer, work->tileCount << 5);
    n = gData_03000794[0];
    slot = &table[n];
    slot->unk04 = gData_03000798->penX;
    slot->unk06 = gData_03000798->penY;
    gData_03000794[0] = n + 1;
}

/* fn: sub_08061BAC */
// @ 0x08061bac

// @ 0x08061bac
void VramSlotsRelease(void)
{
    struct Unk0770 *p;
    s32 n;
    void *z;

    p = (struct Unk0770 *)gUnk_03000770;
    z = 0;
    n = 3;
    do
    {
        if (p->unk00 != 0)
        {
            HeapFree(p->unk00);
            p->unk00 = z;
        }
        p++;
        n--;
    } while (n >= 0);
    gUnk_03000794 = 0;
}

/* fn: sub_08061C48 */
// @ 0x08061c48

void VramSlotReleaseLast(void)
{
    s32 i;
    struct Unk0770 *base;

    i = gData_03000794[0] - 1;
    if (i < 0)
        return;
    gData_03000794[0] = i;
    base = (struct Unk0770 *)gData_03000770;
    if (base[i].unk00 != 0)
    {
        HeapFree(base[i].unk00);
        base[gData_03000794[0]].unk00 = 0;
    }
}

/* fn: sub_08069DBC */
// @ 0x08069dbc

/* match-compiler: old_agbcc */
// @ 0x08069dbc
// Copy `count` halfwords from a source map into VRAM with row/column strides.
void VramCopyStrided(struct Unk69DBC *state, u32 unused, u32 count_arg, u32 destination_arg, u32 shift_arg, u32 source_arg)
{
    u8 count;
    s32 source_index;
    u32 stride;
    u16 *source;
    u16 *destination;
    u8 *shift_ptr;
    u32 off;
    u32 source_step;
    u32 two;

    count = (u8)count_arg;
    source_index = (s32)source_arg;
    destination = (u16 *)(state->unk70 + ((source_index & 0x1F) << 1));
    source = destination;
    source_index >>= 5;
    stride = state->unk00;
    source = (u16 *)((u8 *)source + ((stride << 2) * source_index));
    off = state->unk5C << 11;
    off += 0x6000000;
    off += ((shift_arg << state->unk5F) + destination_arg) << 1;
    destination = (u16 *)off;
    if (count != 0)
    {
        source_step = stride << 1;
        shift_ptr = &state->unk5F;
        two = 2;
        do
        {
            *destination = *source;
            source = (u16 *)((u8 *)source + source_step);
            destination = (u16 *)((u8 *)destination + (two << *shift_ptr));
            count--;
        } while (count != 0);
    }
}

/* fn: sub_0806B5B8 */
// @ 0x0806b5b8
s32 TileAddrFromIndex(s32 arg0, s32 arg1) {
    return arg0 + ((0x3FF & arg1) << 5);
}

/* fn: sub_0806FBF8 */
// @ 0x0806fbf8
/* match-compiler: old_agbcc */
// Return the span [start, start + size) to the sorted free list at
// gData_03004088: grow a neighbouring span when it touches one, otherwise link
// in a node taken from the spare list gData_03004098. Then coalesce adjacent
// spans, returning the absorbed nodes to the spare list.
void VramSpanFree(s32 start, s32 size)
{
    struct Unk6FBF8Span *cur;
    struct Unk6FBF8Span *spare;
    struct Unk6FBF8Span *prev;
    struct Unk6FBF8Span *next;
    s32 end;

    cur = gData_03004088;
    spare = gData_03004098;
    prev = NULL;
    end = start + size;
    while (cur != NULL)
    {
        if (end == cur->start)
        {
            cur->start -= size;
            cur->size += size;
            break;
        }
        if (start == cur->start + cur->size)
        {
            cur->size += size;
            break;
        }
        if (cur->start > start)
        {
            if (spare == NULL)
            {
                DebugPrint((void *)0x083D2184);
                return;
            }
            gData_03004098 = spare->next;
            if (prev != NULL)
                prev->next = spare;
            else
                gData_03004088 = spare;
            spare->next = cur;
            spare->start = start;
            spare->size = size;
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    cur = gData_03004088->next;
    prev = gData_03004088;
    while (cur != NULL)
    {
        if (cur->start == prev->start + prev->size)
        {
            next = cur->next;
            prev->size = cur->size + prev->size;
            prev->next = next;
            cur->next = gData_03004098;
            gData_03004098 = cur;
            cur = next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}
