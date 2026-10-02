#include "global.h"

extern u32 sub_080677A8(u32 address, void *data);
extern u16 sub_08067634(u32 address, u32 data);

/* Replaces the EepromWriteBlock call in the save loops. EepromVerifyBlock
 * returns 0 only when the chip already holds exactly these 8 bytes, so the
 * slow EEPROM program cycle is skipped for every unchanged block. Anything
 * else (a differing block, a read failure, an out of range address) still
 * goes through the retail write, and the caller's verify and retry logic
 * runs unchanged afterwards. */
u16 FastSaveWriteBlock(u32 address, u32 data)
{
    if (sub_080677A8(address, (void *)data) == 0)
        return 0;
    return sub_08067634(address, data);
}
