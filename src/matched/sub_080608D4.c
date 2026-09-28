#include "global.h"

// @ 0x080608d4
void WindowRegsClear(void)
{
    u16 *p;
    u16 z;

    p = (u16 *)0x04000040;
    z = 0;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
    p++;
    *p = z;
}

