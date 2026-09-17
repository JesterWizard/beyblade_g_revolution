#include "global.h"

// @ 0x080628e4
#include "global.h"
#include "battle.h"
#include "ram_map.h"

// @ 0x080628E4
// Stores into main work arena slot used by battle setup paths.
void sub_080628E4(u32 value)
{
    u32 *mainWork;

    mainWork = *(u32 **)gMainWorkPtr;
    *(u32 *)((u8 *)mainWork + BTL_MAIN_WORK_FIELD_1800) = value;
}

