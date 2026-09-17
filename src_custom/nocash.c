#include "global.h"
#include "ram_map.h"
#include "nocash.h"

#include <stdarg.h>

/*
 * No$GBA debug string ports:
 *   0x4FFFA10  pret: auto newline (flaky on some builds)
 *   0x4FFFA14  pret: raw
 *   0x4FFFA18  Skill System DebugKit
 *
 * Must pass a pointer that stays valid after return — No$ may read the
 * string asynchronously. Do NOT use C `static` buffers: .bss is linked at
 * 0x03000000 and stomps vanilla IWRAM. Use gNoCashPrintBuf in the free pool.
 */
#define NOCASHGBAPRINTADDR ((volatile u32 *)0x04FFFA18)
#define NOCASH_BUF_CAP 0x100

APPEND_TEXT static void NoCashEmit(const char *pBuf)
{
    u32 i = 0;

    if (pBuf != gNoCashPrintBuf)
    {
        if (pBuf != NULL)
        {
            while (pBuf[i] != '\0' && i < (NOCASH_BUF_CAP - 2))
            {
                gNoCashPrintBuf[i] = pBuf[i];
                i++;
            }
        }
        if (i == 0 || gNoCashPrintBuf[i - 1] != '\n')
            gNoCashPrintBuf[i++] = '\n';
        gNoCashPrintBuf[i] = '\0';
    }
    else
    {
        while (gNoCashPrintBuf[i] != '\0' && i < (NOCASH_BUF_CAP - 2))
            i++;
        if (i == 0 || gNoCashPrintBuf[i - 1] != '\n')
        {
            gNoCashPrintBuf[i++] = '\n';
            gNoCashPrintBuf[i] = '\0';
        }
    }

    *NOCASHGBAPRINTADDR = (u32)gNoCashPrintBuf;
}

APPEND_TEXT void NoCashGBAPrint(const char *pBuf)
{
    NoCashEmit(pBuf);
}

APPEND_TEXT static void NoCashAppendChar(char *dst, u32 *pos, u32 cap, char c)
{
    if (*pos + 1 < cap)
        dst[(*pos)++] = c;
}

APPEND_TEXT static void NoCashAppendStr(char *dst, u32 *pos, u32 cap, const char *s)
{
    if (s == NULL)
        s = "(null)";
    while (*s != '\0' && *pos + 1 < cap)
        dst[(*pos)++] = *s++;
}

APPEND_TEXT static void NoCashAppendU32(char *dst, u32 *pos, u32 cap, u32 value, u32 base)
{
    char tmp[16];
    u32 n = 0;
    const char *digits = "0123456789ABCDEF";

    if (value == 0)
    {
        NoCashAppendChar(dst, pos, cap, '0');
        return;
    }

    while (value != 0 && n < sizeof(tmp))
    {
        tmp[n++] = digits[value % base];
        value /= base;
    }
    while (n > 0)
        NoCashAppendChar(dst, pos, cap, tmp[--n]);
}

/* Minimal %s / %u / %d / %x / %% — enough for crash probes. */
APPEND_TEXT void NoCashGBAPrintf(const char *fmt, ...)
{
    va_list ap;
    u32 pos = 0;
    u32 cap = NOCASH_BUF_CAP;

    if (fmt == NULL)
    {
        NoCashEmit("(null)");
        return;
    }

    va_start(ap, fmt);
    while (*fmt != '\0' && pos + 1 < cap)
    {
        if (*fmt != '%')
        {
            gNoCashPrintBuf[pos++] = *fmt++;
            continue;
        }
        fmt++;
        if (*fmt == '%')
        {
            gNoCashPrintBuf[pos++] = '%';
            fmt++;
            continue;
        }
        if (*fmt == 's')
        {
            NoCashAppendStr(gNoCashPrintBuf, &pos, cap, va_arg(ap, char *));
            fmt++;
            continue;
        }
        if (*fmt == 'u')
        {
            NoCashAppendU32(gNoCashPrintBuf, &pos, cap, va_arg(ap, u32), 10);
            fmt++;
            continue;
        }
        if (*fmt == 'd')
        {
            s32 v = va_arg(ap, s32);
            if (v < 0)
            {
                NoCashAppendChar(gNoCashPrintBuf, &pos, cap, '-');
                NoCashAppendU32(gNoCashPrintBuf, &pos, cap, (u32)(-v), 10);
            }
            else
            {
                NoCashAppendU32(gNoCashPrintBuf, &pos, cap, (u32)v, 10);
            }
            fmt++;
            continue;
        }
        if (*fmt == 'x' || *fmt == 'X')
        {
            NoCashAppendU32(gNoCashPrintBuf, &pos, cap, va_arg(ap, u32), 16);
            fmt++;
            continue;
        }
        NoCashAppendChar(gNoCashPrintBuf, &pos, cap, '%');
        if (*fmt != '\0')
            NoCashAppendChar(gNoCashPrintBuf, &pos, cap, *fmt++);
    }
    va_end(ap);
    gNoCashPrintBuf[pos] = '\0';
    NoCashEmit(gNoCashPrintBuf);
}
