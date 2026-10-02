#include "global.h"

// @ 0x08067a9c
// K&R-style empty parameter list (not `...`): a variadic definition makes agbcc
// emit an 8-byte varargs prologue, while retail is a bare `bx lr`.
void DebugMessage()
{
}
