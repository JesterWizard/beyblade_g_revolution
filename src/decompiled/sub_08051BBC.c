#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08051bbc
void sub_08051BBC(void) {
    void *temp_r1;

    temp_r1 = gMainWorkPtr;
    temp_r1->unk17F0 = 0x10;
    temp_r1->unk17F2 = 0;
}

