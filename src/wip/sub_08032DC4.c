#include "global.h"

void sub_080338E4(void *dst, void *src);
void sub_08032D5C(struct Unk346C0 *a, struct Unk346C0 *b);
void sub_08033188(void);
void sub_0803370C(void);
void sub_08033084(void *a, u32 b);
void sub_080302E0(void *a);
void sub_08035D68(void *a, void *b);
void sub_0803531C(void *a);
void sub_080353A0(void *a);
void sub_08030F38(void);
void sub_08033DD4(void);
u8 sub_08033A94(void *a);
void sub_080338F0(struct Unk33958 *a, u16 b);
void sub_08033978(struct Unk33A5C *a, struct Unk346C0 *b, struct Unk346C0 *c, u8 d);
void sub_080333E4(s32 a, s32 b, s32 c, s32 d);
void sub_08032DB8(struct Unk346C0 *a);
void sub_080361A8(void *a);
void sub_08068EC0(void *a);
void sub_08030F00(struct Unk30F00 *a, struct Unk30F00Src *b);

void sub_08032DC4(
    s32 frame_arg, struct Unk346C0 *state_a_arg,
    struct Unk346C0 *state_b_arg)
{
    register s32 frame;
    register struct Unk346C0 *state_a;
    register struct Unk346C0 *state_b;
    struct Unk33958 temp_a;
    struct Unk33958 temp_b;
    struct Unk33958 temp_c;
    u32 i;

    state_a = state_a_arg;
    state_b = state_b_arg;
    frame = frame_arg;
    gBattleWork->unkAC4 = sub_080628B4(0x100) << 8;
    sub_080338E4(&temp_a, (void *)0x0807811C);
    sub_080338E4(&temp_b, (void *)0x08078130);
    sub_080338E4(&temp_c, (void *)0x08078144);
    sub_08032D5C(state_a, state_b);
    if (frame >= 0)
    {
        do
        {
            sub_080674B4();
            sub_08067890();
            sub_0806A6F8();
            if ((*(u16 *)gBtlKeysHeld & 8) != 0)
                sub_08033188();
            sub_080361CC(
                (struct Unk36190 *)&gBattleWork->unkAA8,
                (struct Unk361CCDst *)gBattleWork->filler_0008);
            sub_080361CC(
                (struct Unk36190 *)&gBattleWork->unkAA8,
                (struct Unk361CCDst *)gBattleWork->unk090);
            sub_08068EC0(gBattleWork->filler_0008);
            sub_08068EC0(gBattleWork->unk090);
            sub_08035D68(
                (void *)((u8 *)gBattleWork + 0x328),
                (void *)((u8 *)gBattleWork + 0xAA8));
            sub_08035D68(
                (void *)((u8 *)gBattleWork + 0x37C),
                (void *)((u8 *)gBattleWork + 0xAA8));
            sub_080302A8(
                (struct Unk302A8 *)((u8 *)gBattleWork + 0x328),
                (struct Unk302A8Src *)((u8 *)gBattleWork + 0xAA8),
                (struct Unk302A8 *)gBattleWork->unk0AD8[0]);
            sub_080302A8(
                (struct Unk302A8 *)((u8 *)gBattleWork + 0x37C),
                (struct Unk302A8Src *)((u8 *)gBattleWork + 0xAA8),
                (struct Unk302A8 *)gBattleWork->unk0AD8[1]);
            sub_0803531C(state_a);
            sub_0803531C(state_b);
            sub_080353A0(state_a);
            sub_080353A0(state_b);
            sub_08030F38();
            sub_08030F00(
                (struct Unk30F00 *)gBattleWork->unk0AE8.fields.unkB50,
                (struct Unk30F00Src *)((u8 *)gBattleWork + 0x478));
            sub_08033530();
            sub_0803370C();
            sub_08033084(
                (void *)((u8 *)gBattleWork + 0x1F7C),
                gBattleWork->unk1F98);
            sub_080302E0(state_a);
            sub_080302E0(state_b);
            sub_08031300((struct Unk312EC *)gBattleWork->unkB84);
            sub_08031300((struct Unk312EC *)gBattleWork->unkB94);
            _08073C40(*(void **)0x080BB888);
            sub_08036264(
                (struct Unk36264 *)((u8 *)gBattleWork + 0xAA8),
                (struct Unk360BC *)((u8 *)gBattleWork + 0x328),
                (struct Unk360BC *)((u8 *)gBattleWork + 0x37C), 0x66);
            sub_080361A8((u8 *)gBattleWork + 0xAA8);
            sub_08034894(state_a);
            if (state_a->unk30C == 1)
                sub_08033DD4();
            if (sub_08033A94(gBattleWork->unk2094) == 0)
            {
                sub_080338F0(&temp_a, state_a->unk300);
                sub_080338F0(&temp_b, state_a->unk300);
                sub_080338F0(&temp_c, state_a->unk300);
                if (sub_08033958(&temp_a) != 0)
                {
                    sub_08033978(
                        gBattleWork->unk2094, state_a, state_b, 0);
                    sub_080333E4(0x78, 0x50, 0, 3);
                }
                if (sub_08033958(&temp_b) != 0)
                {
                    sub_08033978(
                        gBattleWork->unk2094, state_a, state_b, 1);
                    sub_080333E4(0x78, 0x50, 0, 3);
                }
                if (sub_08033958(&temp_c) != 0)
                {
                    sub_08033978(
                        gBattleWork->unk2094, state_a, state_b, 2);
                    sub_080333E4(0x78, 0x50, 0, 3);
                }
            }
            frame--;
        } while (frame >= 0);
    }
    sub_08032DB8(state_a);
}
