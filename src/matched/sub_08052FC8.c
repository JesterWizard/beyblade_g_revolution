#include "global.h"

// @ 0x08052fc8

void InputUpdate(void);

// @ 0x08052fc8
void sub_08052FC8(void)
{
    struct MainWork **wp;

    TimerAdvance();
    wp = gMainWorkPtrLoc;
    SceneObjUpdate((u8 *)*wp + 0x36C);
    sub_08067CE8((struct AnimObj *)((u8 *)*wp + 0x36C), 0);
    sub_0805D1AC();
    _0802D9A8();
    _08073C40(*(void **)0x080BB888);
    VBlankIntrWait();
    InputUpdate();
    SparklesUpdate();
}

