#include "global.h"

// @ 0x08041c8c
// Find the battle object with unkD4 == a and unkD8 == b in the gUnk_03000480
// pool (count at gUnk_03000504); if found and its unkC8/unkC8->unk10 are set,
// record c on that node and copy the two payload words of c into the node's
// unk30 record (byte at +0, byte at +4, halfword at +6).
// PARKED: structure lines up instruction-for-instruction with retail, but agbcc
// keeps the count address in a rematerialised literal and the pool base in ip,
// while retail pushes r6/r7 for r8 = &count and r9 = pool (142 vs 136 bytes).
// Permuter (150s) did not close the gap. Needs a source shape that raises
// register pressure across the loop.
void sub_08041C8C(u32 a, u32 b, u32 c)
{


    struct Unk68574 **pool;
    s16 i;
    s16 count;
    struct Unk68574 *p;
    struct Unk41E14Node *node;
    u32 *src;
    struct Unk41C8CDst *dst;

    i = 0;
    count = *(s16 *)gUnk_03000504;
    if (count > 0 && i < count)
    {
        pool = (struct Unk68574 **)gUnk_03000480;
        do
        {
            p = pool[i];
            if (p != 0 && p->unkD4 == (void *)a && p->unkD8 == (void *)b)
            {
                node = p->unkC8;
                if (node == 0)
                    break;
                if (node->unk10 == 0)
                    break;
                src = (u32 *)c;
                node->unk10->unk10 = (struct Unk41E14Node *)c;
                dst = node->unk30;
                dst->unk00 = (u8)src[0];
                dst->unk06 = (u16)src[1];
                dst->unk04 = 0;
                break;
            }
            i++;
        } while (i < *(s16 *)gUnk_03000504);
    }

}
