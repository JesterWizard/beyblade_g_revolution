#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08040f4c
/* match-compiler: old_agbcc */
// Menu main loop: clear + set up the stack state, then per frame run the blend
// fade and dispatch on the mode byte until mode 3 ends the loop.
void MenuDispatchLoop(void)
{
    struct Unk40F4C state;
    s32 done;

    done = 0;
    {
        u32 *src = gData_080BB8BC;
        _08073C4C(0, &state, sizeof(state), (void *)*src);
    }
    sub_0804109C(&state, sub_0806639C());
    WindowEffectCreate();
    sub_08060758();
    do
    {
        WindowEffectApply();
        BlendFadeTick();
        VBlankIntrWait();
        sub_0806A6F8();
        if (!(state.unk324 & 1))
            _08073C40((void *)gData_080BB888[0]);
        if (state.unk2D7 == 1)
        {
            switch (state.unk322)
            {
            case 1:
                state.unk31C -= state.unk31E;
                if ((s16)state.unk31C < 0)
                {
                    state.unk31C = 0;
                    state.unk2D7 = 0;
                }
                break;
            case 2:
                state.unk31C += state.unk31E;
                if ((s16)state.unk31C > 0x1F)
                {
                    state.unk31C = 0x1F;
                    state.unk2D7 = 0;
                }
                break;
            }
            REG_BLDCNT = state.unk320;
            REG_BLDY = state.unk31C;
        }
        switch (state.unk2D4)
        {
        case 0:
            if (state.unk24C)
                _08073C44(&state, state.unk24C);
            break;
        case 1:
            if (state.unk250)
                _08073C44(&state, state.unk250);
            sub_080411EC(&state);
            break;
        case 2:
            if (state.unk254)
                _08073C44(&state, state.unk254);
            break;
        case 3:
            done = 1;
            break;
        }
        if (state.unk258)
            _08073C44(&state, state.unk258);
    } while (!done);
    sub_08041394((struct Unk41394 *)&state);
    WindowEffectDestroy();
    sub_08060798();
}

