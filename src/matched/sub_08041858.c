#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08041858
// Release the slot held at 0x03000508 (via sub_0806A434) and zero the two
// battle-state words. gData_* symbols keep the 0x03000508/0x03000534/0x03000504
// pool literals distinct (raw literals get folded into base+offset).
void sub_08041858(void)
{
    void *v;

    sub_08041980();
    v = gData_03000508[0];
    if (v != 0)
    {
        sub_0806A434(v);
        gData_03000508[0] = 0;
    }
    gData_03000534[0] = 0;
    gData_03000504[0] = 0;
}

