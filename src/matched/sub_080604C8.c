#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x080604c8
/* match-compiler: old_agbcc */
void WindowRegsApply(void)
{
    struct WindowRegs *p = *(struct WindowRegs **)gUnk_03000750;
    u32 w;

    w = p->win0Left;
    w <<= 8;
    w |= p->win0Right;
    p->win0H = w;
    p->win1H = (p->win1Left << 8) | p->win1Right;
    p->win0V = (p->win0Top << 8) | p->win0Bottom;
    if (1)
    {
        if (p)
        {
            p->win1V = (p->win1Top << 8) | p->win1Bottom;
            p->winIn = (p->win1In << 8) | p->win0In;
            p->winOut = (p->objWinIn << 8) | p->outside;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->win1H;
            w += 2;
            *(u16 *)w = p->win0V;
            w += 2;
            *(u16 *)w = p->win1V;
            w += 2;
            *(u16 *)w = p->winIn;
            w += 2;
        }
        else
        {
            p->win1V = (p->win1Top << 8) | p->win1Bottom;
            p->winIn = (p->win1In << 8) | p->win0In;
            p->winOut = (p->objWinIn << 8) | p->outside;
            *(vu16 *)gData_04000040 = (u16)w;
            w = (u32)gData_04000042;
            *(u16 *)w = p->win1H;
            w += 2;
            *(u16 *)w = p->win0V;
            w += 2;
            *(u16 *)w = p->win1V;
            w += 2;
            *(u16 *)w = p->winIn;
            w += 2;
        }
    }
    *(u16 *)w = p->winOut;
}

