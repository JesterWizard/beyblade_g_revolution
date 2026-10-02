#include "global.h"

// @ 0x080674ac
void LZ77UnCompWram(void *src, void *dest)
{
    asm("swi 17" : : "r"(src), "r"(dest));
}
