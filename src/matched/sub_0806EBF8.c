#include "global.h"

// @ 0x0806ebf8
void sub_0806EBF8(void *a, u32 b, u16 c, u32 d, u32 e)
{
    struct MapOrigins origins;

    origins.layer[0].x = d;
    origins.layer[0].y = e;
    origins.layer[1].x = d;
    origins.layer[1].y = e;
    origins.layer[2].x = d;
    origins.layer[2].y = e;
    origins.layer[3].x = d;
    origins.layer[3].y = e;
    sub_0806EC20(a, (void *)b, c, &origins);
}
