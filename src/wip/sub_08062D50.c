#include "global.h"

void sub_08062D50(u8 arg0, struct Unk62D50 *arg1)
{
    *(u16 *)(0x05000000 + (arg0 << 1)) =
        (arg1->unk00 & 0x1F) | ((arg1->unk01 & 0x1F) << 5) | ((arg1->unk02 & 0x1F) << 0xA);
}
