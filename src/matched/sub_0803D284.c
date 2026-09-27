#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0803d284
/* match-compiler: old_agbcc */
// Lay out `str` as a centred row of glyph sprites in BattleWork.unk0BCC:
// hide all 48 entries, then give each non-space character its own entry
// (spaces just advance x by 4). Glyphs map through gData_080BB748 and
// advance by 0x10 minus that glyph's entry in `widths`.
void sub_0803D284(const u8 *str, s32 b, const u8 *widths, s32 y)
{
    s32 i;
    s32 x;
    s32 n;

    for (i = 0; i <= 0x2F; i++)
    {
        gBattleWork->unk0BCC[i].unk24 = -0x4000;
        gBattleWork->unk0BCC[i].unk28 = -0x4000;
        sub_08062238(&gBattleWork->unk0BCC[i]);
    }
    x = 0x76 - (sub_08073988(str, widths, 0x10, 4) >> 1);
    for (n = 0, i = 0; str[i] != 0; i++)
    {
        if (str[i] != ' ')
        {
            sub_0806211C(&gBattleWork->unk0BCC[n], 0, b, x, y, 0, 0x28, 0, gData_080BB748[str[i]]);
            x += 0x10 - widths[gData_080BB748[str[i]]];
            sub_08062634(&gBattleWork->unk0BCC[n], -1, n * 2, 0x0803D27D);
            sub_080705DC(gBattleWork->unk0BCC[n].unk08, 0);
            sub_08070468((struct Unk6FDB4 *)gBattleWork->unk0BCC[n].unk08, 40000 - n);
            n++;
        }
        else
            x += 4;
    }
}

