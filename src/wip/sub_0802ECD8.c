#include "global.h"

struct Unk2ECD8Record
{
    u8 filler_00[4];
    void *unk04;
    u8 filler_08[4];
    s8 unk0C;
    s8 unk0D;
    s8 unk0E;
    u8 filler_0F;
};

struct Unk2ECD8Root
{
    u8 filler_00[0x0C];
    struct Unk2ECD8Record *records;
    u8 filler_10[0xE8];
    u8 unkF8;
    u8 filler_F9[0x37];
    s32 unk130;
    s32 unk134;
    s32 unk138;
};

s32 sub_0803E1F4(s8 a, s8 b);
s32 sub_0802E2F8(s8 a, s8 b, s32 multiplier);

void sub_0802ECD8(void)
{
    struct Unk2ECD8Record *record;
    struct Unk2C314 out;
    register void *buffer asm("r7");
    register s32 i asm("r6");
    register struct Unk2ECD8Root **root_loc asm("r8");
    register u32 x asm("r9");
    register u32 y asm("r10");
    s32 mode;
    s32 result;
    s32 amount;
    s32 base;

    sub_08061784();
    buffer = sub_0807309C(0x10);
    i = 0;
    root_loc = (struct Unk2ECD8Root **)gUnk_03000278;
    y = 0xD000;
    x = 0xC000;
    do
    {
        base = (*root_loc)->unk134 + i;
        record = (*root_loc)->records + base;
        if (record->unk0C >= 0)
        {
            sub_080615EC(0, (i << 4) + 0x40);
            if (i == (*root_loc)->unk138)
            {
                result = _080563A8(record->unk0D, record->unk0C);
                if (result != 0)
                    sub_08070AD4(
                        (struct Unk7069C *)&(*root_loc)->unkF8,
                        (void *)result, 0x0F);
                else
                    sub_08070AD4(
                        (struct Unk7069C *)&(*root_loc)->unkF8,
                        record->unk04, 0x0F);
                sub_08061610(0x0E);
                sub_08061D68(x >> 16, 0x0E, 2, 0x1B);
                sub_08061D68(y >> 16, 0x0E, 2, 0x1B);
            }
            else
            {
                sub_08061610(0x0F);
                sub_08061D68(x >> 16, 0x0F, 2, 0x1B);
                sub_08061D68(y >> 16, 0x0F, 2, 0x1B);
            }
            if (base < (*root_loc)->unk130 - 1)
            {
                sub_080731F4((u8 *)buffer);
                record = (*root_loc)->records + base;
                if (record->unk0D == 1)
                {
                    amount = sub_0803E1F4(record->unk0C, record->unk0E);
                    amount = *(s8 *)((u8 *)amount + 0x24);
                    result = sub_0802E2F8(
                        record->unk0D, record->unk0C, 100 - amount);
                }
                else
                {
                    sub_0802C4A4(
                        record->unk0D, record->unk0C, &out);
                    mode = (s8)out.unk02;
                    result = sub_0802E2F8(
                        record->unk0D, record->unk0C, mode);
                }
                sub_080735DC(result, buffer, 0x10);
                sub_0806171C(buffer, 0xD4, 1);
            }
        }
        record = (*root_loc)->records + base;
        sub_0806171C(record->unk04, 0x0C, 2);
        x += 0x800;
        y += 0x800;
        i++;
    } while (i <= 2);
    sub_08073114(buffer);
}
