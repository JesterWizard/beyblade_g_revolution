#include "global.h"

/* 67/76 same size (was 54/76). Walks MainWork.unk16E0 (8-byte records) until
 * sub_08073440(node->unk00, unk16C8) returns 0, then returns node->unk04.
 * Null list returns -1.
 *
 * Remaining 9-byte delta is the loop-exit epilogue: retail falls out of the
 * head test (`ldr r0,[r4]; cmp r0,#0; bne body`) into `pop {r4}; pop {r1}` with
 * r0 already 0, so the early-out return yields the *tested* value rather than a
 * materialised 0. `return (s32)node->unk00;` makes agbcc reload (extra
 * `ldr r0,[r4]`), `return 0;` makes it emit `movs r0,#0`, and caching the field
 * in a local (`v`) makes agbcc keep the *call argument* in that register, adding
 * `adds r0,r2,#0`. Retail has neither: the head-test value is reused for the
 * return while the call argument is a fresh load. Revisit via permuter. */
s32 sub_08043B90(void)
{
    struct Unk16E0 *node = gMainWorkPtr->unk16E0;

    if (node == 0)
        return -1;
    while (node->unk00 != 0)
    {
        if (sub_08073440(node->unk00, gMainWorkPtr->unk16C8) == 0)
            return node->unk04;
        node++;
    }
    return 0;
}
