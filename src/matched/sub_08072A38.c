#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x08072a38
/* match-compiler: old_agbcc */
// Palette fade over job->unk08 rows: each colour fades toward (d, e, f) if
// its rough luminance is below c, else toward (g, h, i); the fade amount
// starts at 0 and grows by (4 * b / rows) / 1024 per row.
void sub_08072A38(struct Unk72A38 *job, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i)
{
    s32 step;
    s32 t;
    s32 row;
    s32 col;
    u16 *src;
    u16 *dst;
    s32 r, gr, bl;
    s32 lum;
    u16 color;

    step = b;
    step = ((step << 10) >> 8) / job->unk08;
    t = 0;
    dst = job->unk0C;
    for (row = 0; row < job->unk08; row++)
    {
        src = &job->unk00[job->unk04];
        for (col = 0; col < job->unk06; col++)
        {
            color = *src;
            r = 0x1F;
            r &= color;
            gr = (color & 0x3E0) >> 5;
            bl = (color & 0x7C00) >> 10;
            lum = (r >> 2) + (gr >> 1) + (bl >> 1);
            if (lum > 31)
                lum = 31;
            if (lum < (s32)c)
            {
                r += ((s32)(d - r) * t) >> 10;
                gr += ((s32)(e - gr) * t) >> 10;
                bl += ((s32)(f - bl) * t) >> 10;
            }
            else
            {
                r += ((s32)(g - r) * t) >> 10;
                gr += ((s32)(h - gr) * t) >> 10;
                bl += ((s32)(i - bl) * t) >> 10;
            }
            if (r > 31)
                r = 31;
            if (gr > 31)
                gr = 31;
            if (bl > 31)
                bl = 31;
            *dst++ = r + (gr << 5) + (bl << 10);
            src++;
        }
        t += step;
    }
}

