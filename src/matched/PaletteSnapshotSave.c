#include "global.h"
#include "ram_map.h"
#include "battle.h"
#include "data_symbols.h"

// @ 0x08062f90
typedef void (*CpuCopyFunc)(const void *, void *, u32);

// Snapshots BG and OBJ palette RAM into two freshly allocated 0x200-byte
// buffers, unless a snapshot is already held (see sub_0806306C).
void PaletteSnapshotSave(void)
{
    bool32 bgAllocated;

    if (gData_030008DC != NULL || gData_030008D8 != NULL
        || gData_030008E0 != NULL || gData_030008D4 != NULL)
        return;
    gData_030008E0 = HeapAlloc(0x200);
    gData_030008D4 = HeapAlloc(0x200);
    if ((bgAllocated = gData_030008E0 != NULL) || gData_030008D4 != NULL)
    {
        gData_030008DC = *gData_030008E0;
        gData_030008D8 = *gData_030008D4;
        ((CpuCopyFunc)gData_080BB8C0[0])((void *)0x05000000, gData_030008DC, 0x200);
        ((CpuCopyFunc)gData_080BB8C0[0])((void *)0x05000200, gData_030008D8, 0x200);
    }
}

