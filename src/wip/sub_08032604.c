#include "global.h"

s32 _08032458(void);
void sub_08069894(void);
void *sub_08065E0C(void *a, u32 b, void *c, u32 d, u32 e);

struct Unk32604Table
{
    void *unk00;
    void *unk04;
    void *unk08;
};

void sub_08032604(void)
{
    register struct BattleWork **main_loc;
    register struct Unk32604Table *table;
    register u32 transfer_size;
    s8 index;

    index = (s8)_08032458();
    sub_08069894();
    main_loc = gBattleWorkPtrLoc;
    table = (struct Unk32604Table *)0x0807800C;
    transfer_size = 0x8000;
    (*main_loc)->unk00 = sub_08065E0C(
        (*main_loc)->filler_0008, 2, table[index].unk00,
        transfer_size, 0);
    (*main_loc)->unk04 = sub_08065E0C(
        (*main_loc)->unk090, 3, table[index].unk04,
        transfer_size, 0);
    sub_080679A4(table[index].unk08);
    sub_08069B78(1, 2, 3, 0);
    *(u16 *)0x04000000 = 0x1C42;
    (*main_loc)->unk054 = 0x10000;
    (*main_loc)->unk058 = 0x10000;
    (*main_loc)->unk050 = 0x3C;
    (*main_loc)->unk052 = 0x3C;
    (*main_loc)->unkDC = 0x10000;
    (*main_loc)->unkE0 = 0x10000;
    (*main_loc)->unkD8 = 0x3C;
    (*main_loc)->unkDA = 0x3C;
}
