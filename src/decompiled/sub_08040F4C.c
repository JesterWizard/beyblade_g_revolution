#include "global.h"

// @ 0x08040f4c
void sub_08040F4C(void)
{
    struct Unk40F4C state;
    s32 done;
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;

    done = 0;
    r0 = 0x080BB8BC;
    r2 = 0xCA;
    r2 <<= 2;
    r3 = *(u32 *)r0;
    r0 = 0;
    r1 = (u32)&state;
    _08073C4C((void *)r0, (void *)r1, r2, (void *)r3);
    r0 = (u32)sub_0806639C();
    r1 = r0;
    r0 = (u32)&state;
    sub_0804109C((struct Unk40F4C *)r0, (struct Unk4109CInput *)r1);
    sub_08060468();
    sub_08060758();
loop:
    sub_080604C8();
    sub_080607BC();
    sub_080674B4();
    sub_0806A6F8();
    r0 = (u32)&state.unk324;
    r0 = *(u32 *)r0;
    r1 = 1;
    r0 &= r1;
    if (r0 != 0)
        goto after_vblank;
    r0 = 0x080BB888;
    r0 = *(u32 *)r0;
    _08073C40((void *)r0);
after_vblank:
    r2 = 0x2D7;
    r2 += (u32)&state;
    r0 = *(u8 *)r2;
    if (r0 != 1)
        goto after_blend;
    r0 = 0x322;
    r0 += (u32)&state;
    r0 = *(u16 *)r0;
    if (r0 == 1)
        goto blend1;
    if (r0 == 2)
        goto blend2;
    goto blend_hw;
blend1:
    r1 = (u32)&state.unk31C;
    r0 = 0x31E;
    r0 += (u32)&state;
    r3 = *(u16 *)r1;
    r0 = *(u16 *)r0;
    r0 = r3 - r0;
    r4 = 0;
    r3 = 0;
    *(u16 *)r1 = (u16)r0;
    r0 <<= 16;
    if ((s32)r0 >= 0)
        goto blend_hw;
    *(u16 *)r1 = (u16)r3;
    *(u8 *)r2 = (u8)r4;
    goto blend_hw;
blend2:
    r1 = (u32)&state.unk31C;
    r0 = 0x31E;
    r0 += (u32)&state;
    r3 = *(u16 *)r1;
    r0 = *(u16 *)r0;
    r0 = r3 + r0;
    r3 = 0;
    *(u16 *)r1 = (u16)r0;
    r0 <<= 16;
    r0 = (u32)((s32)r0 >> 16);
    if ((s32)r0 <= 0x1F)
        goto blend_hw;
    r0 = 0x1F;
    *(u16 *)r1 = (u16)r0;
    *(u8 *)r2 = (u8)r3;
blend_hw:
    r1 = REG_ADDR_BLDCNT;
    r0 = (u32)&state.unk320;
    r0 = *(u16 *)r0;
    *(vu16 *)r1 = (u16)r0;
    r1 += 4;
    r0 = (u32)&state.unk31C;
    r0 = *(u16 *)r0;
    *(vu16 *)r1 = (u16)r0;
after_blend:
    r0 = (u32)&state.unk2D4;
    r0 = *(u8 *)r0;
    if (r0 == 1)
        goto mode1;
    if ((s32)r0 > 1)
        goto mode_high;
    if (r0 == 0)
        goto mode0;
    goto after_mode;
mode_high:
    if (r0 == 2)
        goto mode2;
    if (r0 == 3)
        goto mode3;
    goto after_mode;
mode0:
    r0 = (u32)&state.unk24C;
    goto mode_shared;
mode1:
    r0 = (u32)&state.unk250;
    r1 = *(u32 *)r0;
    if (r1 == 0)
        goto mode1_update;
    r0 = (u32)&state;
    _08073C44((void *)r0, (void *)r1);
mode1_update:
    r0 = (u32)&state;
    sub_080411EC((void *)r0);
    goto after_mode;
mode2:
    r0 = (u32)&state.unk254;
mode_shared:
    r1 = *(u32 *)r0;
    if (r1 == 0)
        goto after_mode;
    r0 = (u32)&state;
    _08073C44((void *)r0, (void *)r1);
    goto after_mode;
mode3:
    done = 1;
after_mode:
    r0 = (u32)&state.unk258;
    r1 = *(u32 *)r0;
    if (r1 == 0)
        goto check_done;
    r0 = (u32)&state;
    _08073C44((void *)r0, (void *)r1);
check_done:
    if (done != 0)
        goto exit_loop;
    goto loop;
exit_loop:
    r0 = (u32)&state;
    sub_08041394((struct Unk41394 *)r0);
    sub_080604A4();
    sub_08060798();
}

