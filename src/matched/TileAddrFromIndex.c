#include "global.h"

// @ 0x0806b5b8
s32 TileAddrFromIndex(s32 arg0, s32 arg1) {
    return arg0 + ((0x3FF & arg1) << 5);
}
