#include "global.h"

/*
 * Retail sub_08044E54. The save commit clears the whole profile, then the
 * unpacker copies that profile onto the live blade table. Every other field
 * the unpacker cares about is copied back from live RAM afterwards, so the
 * blade rows are the ones that stay zero and get programmed to EEPROM.
 *
 * Scratch sits in the free EWRAM pool (ram_map_ewram.s). The user stack is
 * only 0x500 bytes, and the table is 0xA50.
 */
#define PROFILE_SIZE 0x1F60
#define BLADE_OFF 0x134C
#define BLADE_SIZE 0xA50
#define BLADE_BACKUP ((u8 *)0x02030000)

extern u32 sub_08044D8C(u32 *record);

static void CopyBytes(u8 *dst, u8 *src, u32 n)
{
    volatile u8 *out;
    u32 i;

    out = dst;
    for (i = 0; i < n; i++)
        out[i] = src[i];
}

static void ClearBytes(u8 *dst, u32 n)
{
    volatile u8 *out;
    u32 i;

    out = dst;
    for (i = 0; i < n; i++)
        out[i] = 0;
}

APPEND_TEXT void SavePrepare__Replacement(u32 slot)
{
    u8 *record;
    u8 *live;
    u32 *sum;

    record = (u8 *)gMainWorkPtr->unk168C + slot * PROFILE_SIZE;
    live = NULL;
    if (gRuntimeConfig.keepBitBeastExp != FALSE)
    {
        live = sub_08042E78(0);
        if (live != NULL)
            CopyBytes(BLADE_BACKUP, live, BLADE_SIZE);
    }

    ClearBytes(record, PROFILE_SIZE);
    sub_08045198(record, 0);
    if (live != NULL)
    {
        CopyBytes(live, BLADE_BACKUP, BLADE_SIZE);
        CopyBytes(record + BLADE_OFF, BLADE_BACKUP, BLADE_SIZE);
    }
    sum = (u32 *)record;
    *sum = sub_08044D8C(sum);
}
