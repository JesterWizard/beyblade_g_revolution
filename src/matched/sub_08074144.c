#include "global.h"

// @ 0x08074144
/* match-fixup: mov-pc-lr */
// Empty leaf. agbcc always returns with `bx lr`; retail uses `mov pc, lr`, so
// match_function.py rewrites the return (see apply_match_fixups).
void sub_08074144(void)
{
}
