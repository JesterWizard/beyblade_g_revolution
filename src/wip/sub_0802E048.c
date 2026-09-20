#include "global.h"

/*
 * WIP — not byte-matched (82.5%, 188/228 bytes, same_size DIFF).
 * Logic is verified correct (asm-wrapper equivalent semantics), but agbcc
 * assigns registers r4 (0x0300026C address temp) / r5 (rec) opposite of
 * retail regardless of local declaration order, C variable type, or
 * splitting into separate p/rec locals. Tried: swapping declaration order,
 * caching gUnk_0300026C in a named local (made it worse: extra spill),
 * struct Unk705DC* vs void* for p. All produced identical 188/228 or worse.
 * Likely same class of quirk as the documented dead-end list
 * (systemic agbcc leaf-function register-allocation issue).
 * @ 0x0802e048
 */
void sub_0802E048(void)
{
    struct Unk705DC *rec;
    void *p;

    p = gUnk_0300026C->unk0C;
    if (p != 0)
    {
        sub_0806FE84(p);
        gUnk_0300026C->unk0C = 0;
    }

    rec = sub_0806FDD0(0);
    gUnk_0300026C->unk0C = rec;

    if (gMainWorkPtr->unk1808 & 0x80000000)
        sub_0806FF58(rec, (void *)0x08266FE0, 0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);
    else
        sub_0806FF58(rec, (void *)0x08266DAC, 0xFFFFC000, 0xFFFFC000, 0, 1, 0, 0);

    sub_080705DC(gUnk_0300026C->unk0C, 2);

    rec = gUnk_0300026C->unk0C;
    rec->unk08 = 0;
    rec->unk0C = 0;

    rec = gUnk_0300026C->unk10;
    rec->unk08 = 0x3B00;
    rec->unk0C = 0;

    rec = gUnk_0300026C->unk14;
    rec->unk08 = 0x4B00;
    rec->unk0C = 0x1500;

    rec = gUnk_0300026C->unk18;
    rec->unk08 = 0x5000;
    rec->unk0C = 0x1500;

    rec = gUnk_0300026C->unk1C;
    rec->unk08 = 0x4B00;
    rec->unk0C = 0x300;

    rec = gUnk_0300026C->unk20;
    rec->unk08 = 0x5000;
    rec->unk0C = 0x300;

    rec = gUnk_0300026C->unk24;
    rec->unk08 = 0x4B00;
    rec->unk0C = 0xC00;
}
