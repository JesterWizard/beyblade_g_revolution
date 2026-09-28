#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08062988
// ROM copy/fill routines at gData_080BB8BC/C0 (reached via _call_via_r3).
typedef void (*BlockFunc)(const void *src, void *dst, u32 size);

/* match-compiler: old_agbcc */
// Loads a 0x2000-byte block into the buffer at gUnk_030007A4: LZ77-decompresses
// it when the header says so (mode 1, variant 1 or 2, non-zero group), otherwise
// runs the ROM block routine at gData_080BB8BC with a NULL source and then copies
// `a` with the one at gData_080BB8C0; then hands the buffer to sub_0806BC0C.
void sub_08062988(struct Unk62988 *a)
{
    u32 flags = a->unk00;
    u32 group = flags >> 8;
    u32 mode = (flags >> 4) & 0x0F;
    u32 variant = a->unk04 & 3;

    if (gUnk_030007A0 == 0)
        return;
    if (mode == 1 && (u8)(variant - 1) <= 1 /* variant 1 or 2 */ && group != 0)
    {
        VBlankIntrWait();
        LZ77UnCompWram(a, gUnk_030007A4);
    }
    else
    {
        ((BlockFunc)gData_080BB8BC[0])(NULL, gUnk_030007A4, 0x2000);
        ((BlockFunc)gData_080BB8C0[0])(a, gUnk_030007A4, 0x2000);
    }
    ResourceBind(gUnk_030007B0, gUnk_030007A4);
}

