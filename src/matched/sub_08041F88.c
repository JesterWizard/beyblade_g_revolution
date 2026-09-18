#include "global.h"

// @ 0x08041f88
void sub_08041F88(void)
{
    gMainWorkPtr->unk03AC = 0;
    gMainWorkPtr->unk03B0 = 0;
    gMainWorkPtr->unk180C = 0;
    sub_08057274();
    gMainWorkPtr->unk0868 = gMainWorkPtr->unk0370;
    gMainWorkPtr->unk086C = gMainWorkPtr->unk0374;
}
