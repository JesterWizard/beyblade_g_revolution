#include "global.h"

typedef u32 *(*ScriptCmdFunc)(u32 *cmd, u32 *a, u32 *b, u32 *done);

void sub_08059DC8(u32 arg0, void *script)
{
    u32 a;
    u32 b;
    u32 done;
    u32 *cmd;
    ScriptCmdFunc *table;

    a = 1;
    done = 0;
    b = 0;
    cmd = script;
    if (cmd == 0)
        return;
    *(u32 *)0x03000734 = arg0;
    table = (ScriptCmdFunc *)0x08099710;
    do
    {
        cmd = table[*cmd](cmd, &a, &b, &done);
    } while (done == 0);
}
