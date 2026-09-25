#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802fa94
void sub_0802FA94(void) {
    TextGetAreaWidth();
    BtlObjTableAdd(0x10);
}

