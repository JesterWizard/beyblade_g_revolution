#include "global.h"

/*
 * Retail sub_080302E0. Launch RPM is a full word (battle+0x13C). This step
 * does (rpm << 16) / 0x900 with a signed divide. 32768 << 16 is negative, so
 * once experience pushes the launch RPM that high the blade steps backward
 * and the fight treats it as already stopped.
 *
 * The same overflow happens one step earlier, inside sub_0803CECC, when the
 * summed experience word at 0x030002A0+8 is itself >= 32768. That leaves a
 * negative word in +0x13C. Rebuild that word with an unsigned shift before
 * stepping.
 */
#define RPM_SHIFT_DEN 25600u
#define STEP_DEN 0x900u

static s32 ScaledShift(u32 quot, u32 scaled)
{
    return (s32)(((quot >> 16) * scaled) + (((quot & 0xFFFFu) * scaled) >> 16));
}

static s32 LaunchRpm(s32 base, s32 power, s32 boost, s32 strength)
{
    u32 quot;
    s32 rpm;

    if (base < 0)
        base = 0;
    quot = ((u32)base << 16) / RPM_SHIFT_DEN;
    rpm = ScaledShift(quot, (u32)power << 8);
    rpm += ScaledShift(quot, (u32)boost << 8);
    rpm += strength * (power + boost);
    if (power > 94 && boost > 94)
        rpm += rpm >> 2;
    if (rpm < 1)
        rpm = 1;
    return rpm;
}

APPEND_TEXT void SpinStep__Replacement(struct Unk346C0 *a)
{
    struct BattleWork *battle;
    u8 index;
    s32 value;
    s32 offset;
    s32 delta;
    s32 frame;
    u8 *obj;
    u8 *extra;
    s32 *rpms;
    s32 *phase;

    battle = gBattleWork;
    index = a->unk30C;
    rpms = (s32 *)((u8 *)battle + 0x13C);
    phase = (s32 *)((u8 *)battle + 0xAE8);
    value = rpms[index];
    offset = phase[index];
    if (gRuntimeConfig.fixHighExpRpm != FALSE && index == 0 && value <= 0)
    {
        value = LaunchRpm(
            *(s32 *)(0x030002A0 + 8),
            *(s16 *)((u8 *)battle + 0x1F74),
            *(s16 *)((u8 *)battle + 0x1F76),
            gMainWorkPtr->strength);
        rpms[0] = value;
        *(s32 *)((u8 *)battle + 0xBB4) = value;
        *(s32 *)((u8 *)battle + 0x144) = value;
        *(s32 *)(0x030002A0 + 12) = value;
    }
    if (gRuntimeConfig.fixHighExpRpm != FALSE && value >= 0)
        delta = (s32)(((u32)value << 16) / STEP_DEN);
    else
        delta = ((s32 (*)(s32, s32))(0x080740B0 | 1))((s32)((u32)value << 16), (s32)STEP_DEN);
    if (a->unk04->unk28->unk1F & 0x40)
        offset -= delta;
    else
        offset += delta;
    phase[index] = offset;
    offset = (offset >> 8) & 0xFF;
    obj = (u8 *)a->unk00->unk00;
    if (obj == NULL)
        return;
    if ((delta >> 8) > 0x1F)
        frame = (s32)sub_080628B4(2);
    else
        frame = 2;
    *(u16 *)(obj + 0x18) = (u16)frame;
    extra = *(u8 **)(obj + 0x30);
    if (extra == NULL)
        return;
    sub_08070354(
        (struct Unk70354 *)obj,
        *(u16 *)(extra + 0x14),
        *(u16 *)(extra + 0x16),
        (u8)offset);
}
