#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0802ecd8
void sub_0802ECD8(void) {
    TextGetAreaWidth();
    BtlObjTableAdd(0x10);
}

