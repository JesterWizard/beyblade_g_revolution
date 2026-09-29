/* match-compiler: old_agbcc */
#include "global.h"
#include "ram_map.h"

#define SAVE_FAIL(slot)                            \
    {                                              \
        BtlClearUnk1688Entry(slot);                \
        SaveSlotWriteDefault(slot);                        \
        gData_03000198->unk185B = 1;               \
        gData_03000198->unk185C = 0;               \
    }

s8 SaveDataVerify(void)
{
    u32 *buf;
    u32 **hdrBlock;
    struct Unk45D3CEntry **slotBlock;
    u16 i;
    u16 retry;
    u32 n;
    u8 invalid;
    struct Unk1688Words *hdr;

    n = 3;
    gData_03000198->unk185B = i = 0;
    gData_03000198->unk185C = 1;
    hdrBlock = HeapAlloc(0x18);
    slotBlock = HeapAlloc(0x1F60);
    gData_03000198->unk1688 = (struct Unk1688Entry *)(buf = *hdrBlock);
    gData_03000198->unk168C = *slotBlock;
    EepromSetType(0x40);
    VBlankIntrWait();
    SoundHwStop();
    REG_IME = 0;
    invalid = 0;
    for (i = 0; i < n; i++)
    {
        retry = 0;
        do
        {
            if (EepromReadBlock(i, buf) != 0)
                retry++;
            else
                retry = 0;
            if (retry == 8)
            {
                SoundHwStart();
                REG_IME = 1;
                for (i = 0; i < 1; i++)
                {
                    BtlClearUnk1688Entry(i);
                    SaveSlotWriteDefault(i);
                }
                gData_03000198->unk185B = 1;
                gData_03000198->unk185C = invalid;
                return 0;
            }
        } while (retry != 0);
        buf += 2;
    }
    for (i = 0; i < 1; i++)
        LoadGameSave(i);
    for (i = 0; i < 1; i++)
    {
        SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]);
        if (SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]) == 0)
            gData_03000198->unk185C = 0;
        hdr = (struct Unk1688Words *)gData_03000198->unk1688;
        hdr += i;
        if (hdr->unk04 != SaveDataChecksum((u32 *)&gData_03000198->unk168C[i]))
            SAVE_FAIL(i);
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk00 != 0xFEEDFACE)
            SAVE_FAIL(i);
        if (((struct Unk1688Words *)&gData_03000198->unk1688[i])->unk00 == 0xFEEDFACE
            && ((u32 *)&gData_03000198->unk168C[i])[1] != 0x1F60)
            SAVE_FAIL(i);
        hdr = (struct Unk1688Words *)gData_03000198->unk1688;
        hdr += i;
        if (hdr->unk10 != 0x00370053 || hdr->unk14 != 0x00F6009C)
        {
            DebugPrint((void *)0x083A2E04);
            SAVE_FAIL(i);
        }
    }
    SoundHwStart();
    REG_IME = 1;
    return gData_03000198->unk185B;
}
