#include "global.h"
#include "data_symbols.h"

extern s32 BtlApplyClampedScore(u8 a, u8 b);

/* One row of opponents.json, resolved by tools/gen_opponents.py (opponent_data.s). */
struct OpponentRow
{
    u16 exp;
    u8 strength;
    u8 hasBeast; /* beastExp is only written when the file sets it */
    u16 beastExp;
    u16 pad;
};

extern const struct OpponentRow gOpponentRows[55];

/* Replaces the two script opcodes' call of sub_08042F4C(exp, strength, row, bonus),
 * which set the blader row to the player's (or a rival's) experience and
 * strength plus 100 * bonus / bonus. The row gets the values from
 * opponents.json instead, so the opponent's launch RPM no longer follows the
 * player. Row layout: s16 experience at +0, strength at +3, and the blade's bit
 * beast experience at +0x2E (the blade record starts at +8, its counter at +0x26). */
void FixedOpponentRow(s32 exp, s32 strength, s32 row, s32 bonus)
{
    u8 *p = sub_08042E78(row);
    const struct OpponentRow *o;

    if (p == 0)
        return;
    o = &gOpponentRows[row];
    *(u16 *)p = o->exp;
    p[3] = o->strength;
    if (o->hasBeast)
        *(u16 *)(p + 0x2E) = o->beastExp;
}

/* Replaces the call of sub_08042F08(amount), which adds amount experience to
 * every blader row past its first stage. */
void FixedOpponentNoGrowth(s32 amount)
{
}

/* Wraps BtlApplyClampedScore (sub_0803715C), which awards experience after a
 * bout. Opponents (slots 1..3) get a share of it too: their row experience
 * (unk24->unk00) and their blade's bit beast experience (unk28->unk26). Those
 * are put back, so only the player's side grows. */
s32 FixedOpponentScore(u8 a, u8 b)
{
    s16 exp[4];
    u16 beast[4];
    s32 i;
    s32 score;

    for (i = 1; i < 4; i++)
    {
        exp[i] = gData_030002A0[i].unk24 != NULL ? gData_030002A0[i].unk24->unk00 : 0;
        beast[i] = gData_030002A0[i].unk28 != NULL ? gData_030002A0[i].unk28->unk26 : 0;
    }
    score = BtlApplyClampedScore(a, b);
    for (i = 1; i < 4; i++)
    {
        if (gData_030002A0[i].unk24 != NULL)
            gData_030002A0[i].unk24->unk00 = exp[i];
        if (gData_030002A0[i].unk28 != NULL)
            gData_030002A0[i].unk28->unk26 = beast[i];
    }
    return score;
}
