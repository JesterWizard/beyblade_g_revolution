#include "global.h"

// @ 0x080674b4
/* `swi 5` with the caller's r0/r1 forwarded untouched and r2 = 0: the parameters keep
 * r0/r1 live, the third asm operand materialises the zero in r2. */
void sub_080674B4(const void *src, void *dest)
{
    asm("swi 5" : : "r"(src), "r"(dest), "r"(0));
}
