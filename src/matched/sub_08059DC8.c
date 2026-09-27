#include "global.h"
#include "ram_map.h"
#include "battle.h"

typedef u32 *(*ScriptCmdFunc)(u32 *cmd, u32 *a, u32 *b, u32 *done);

// @ 0x08059dc8
// Runs a script: dispatches each command through the handler table until one
// sets `done`.
void sub_08059DC8(u32 arg0, void *script)
{
    u32 *cmd;
    u32 a;
    u32 b;
    u32 done;
    ScriptCmdFunc *table;

    cmd = script;
    a = 1;
    done = 0;
    b = 0;
    if (cmd == 0)
        return;
    gData_03000734 = arg0;
    table = (ScriptCmdFunc *)gData_08099710;
    while (done == 0)
        cmd = table[*cmd](cmd, &a, &b, &done);
}

