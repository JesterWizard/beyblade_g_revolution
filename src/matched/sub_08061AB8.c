#include "global.h"
#include "ram_map.h"
#include "battle.h"

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

