#include "global.h"

// @ 0x08038314
void sub_08038314(struct Unk38314 *a, u32 b)
{
    s32 *c;

    c = &a->unk304;
    if (--*c > 0 && (gBtlKeysHeldU16 & 3) != 0)
        return;
    a->unk2FC = b;
    sub_08062044((struct Unk62044 *)((u8 *)gBattleWork + 0x19C));
    sub_08062044((struct Unk62044 *)((u8 *)gBattleWork + 0x1C4));
    sub_08062044((struct Unk62044 *)((u8 *)gBattleWork + 0x1EC));
    sub_08062044((struct Unk62044 *)((u8 *)gBattleWork + 0x214));
}
