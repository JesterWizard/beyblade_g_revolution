#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* fn: sub_0802B95C */
// @ 0x0802b95c
void *FindEntryByString(void *a)
{
    struct Unk2B95C *p;
    struct Unk2B95C *q;

    p = sub_0802B994();
    if (p != 0)
        goto check;
    return 0;
found:
    return q;
check:
    if (p->unk04 == 0)
        return 0;
    q = p;
    do
    {
        if (StringCompare(q->unk04, a) == 0)
            goto found;
        q++;
    } while (q->unk04 != 0);
    return 0;
}

/* fn: sub_0806105C */
// @ 0x0806105c
void TextWindowPutString(void *a, u8 *s)
{
  u8 *sp;
  s32 i;
  u8 c;
 do { sp = s; if ((sp == 0) || (a == 0)) { return; } c = sp[0]; i = 1; } while (0);
  if (c == 0)
  {
    return;
  }
  do
  {
    TextWindowPutChar(a, c);
    c = sp[i];
    i++;
  }
  while (c != 0);
}

/* fn: sub_0806AC68 */
// @ 0x0806ac68
/* match-flags: -fprologue-bugfix */

u32 StringCountNonSpace(u8 *s)
{
    u32 r2;
    u32 r1;
    u8 *r0;

    r2 = 0;
    goto test;
loop:
    r0++;
    if (r1 != 0x20)
        r2++;
test:
    r1 = *r0;
    if (r1 != 0)
        goto loop;
    r0 = (u8 *)r2;
    return (u32)r0;
}

/* fn: sub_08070930 */
// @ 0x08070930
/* match-compiler: old_agbcc */
#define TextGroupAppendString sub_08070930_x
#undef TextGroupAppendString
// Appends the glyphs of a string to a text sprite group at x = unk0A, growing
// the sprite chain and advancing x by each glyph width (space: unk28).

u8 TextGroupAppendString(struct TextGroup *a, u8 *s, u8 pal)
{
    u32 count;
    struct Sprite *first;
    u32 len;
    u8 defWidth;
    u8 *widths;
    u16 x;
    u16 flip;
    u8 mode;
    struct Sprite *node;
    struct AffineObj *aff;
    u32 bits;
    u8 c;
    u16 w;

    len = StringCountNonSpace(s);
    defWidth = a->font->unk04;
    widths = a->widthTable;
    count = a->glyphs.count;
    x = a->penX;
    flip = 0;
    mode = (a->flags & 0x180) >> 7;
    if (s != NULL && *s != 0)
    {
        node = (struct Sprite *)a->glyphs.tail;
        first = (struct Sprite *)BtlObjPoolResizeChain(&a->glyphs, len + count, a->unk2B);
        if (first == NULL)
        {
            DebugPrint((void *)0x083D22D4, s);
            return 0;
        }
        if (node != NULL)
            first = node->next;
        node = first;
        aff = a->affine;
        if (aff != NULL)
        {
            bits = ((aff->unk08 & 0x3E0) << 20) | 0x100;
            if (!(a->flags & 8))
            {
                if (aff->angle != 0)
                {
                    if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)
                        bits |= 0x200;
                }
                else if (aff->scaleX > 0xB0 || aff->scaleY > 0xB0)
                    bits |= 0x200;
            }
        }
        while ((c = *s++) != 0)
        {
            w = defWidth;
            if (c == ' ')
            {
                w = a->spaceWidth;
                flip = 0x8000;
            }
            else
            {
                c = gData_080BB748[c];
                SpriteInitFromTemplate(node, a->font, 0, 0, 0, mode, 0, c);
                TextEntrySetPaletteBank(node, pal);
                SpriteSetObjMode(node, a->objMode);
                if (widths != NULL)
                    w = w - widths[c];
                w = w + a->letterSpacing;
                node->unk1E = x | flip;
                flip = 0;
                if (aff != NULL)
                {
                    node->unk10 = (node->unk10 & 0xC1FFFCFF) | bits;
                    node->affine = (struct Sprite *)aff;
                }
                node = node->next;
            }
            x += w;
        }
        sub_080706B0((struct Unk70C98 *)a);
        a->penX = x;
        return 1;
    }
}

/* fn: sub_08070AD4 */
// @ 0x08070ad4
u8 TextGroupSetString(struct TextGroup *a, void *b, u8 c)
{
    TextGroupClear(a);
    return TextGroupAppendString(a, b, c);
}

/* fn: sub_08073078 */
// @ 0x08073078
/* match-compiler: old_agbcc */
s32 StringLength(u8 *s)
{
    s32 n = 0;

    if (s == 0)
        return -1;
    while (s[n] != 0)
        n++;
    return n;
}

/* fn: sub_0807309C */
// @ 0x0807309c
void *StringAlloc(u32 size)
{
    void *buf = 0;
    struct BtlObj **table;
    struct BtlObj *obj;
    u32 i;

    if (gData_03004150 == 0)
        return 0;
    table = gData_03004150;

    for (i = 0; i < gData_03004154 && table[i] != 0; i++)
        ;
    if (i == gData_03004154)
        return 0;

    obj = HeapAlloc(size);
    table[i] = obj;
    if (obj == 0)
        return 0;

    buf = obj->next;
    MemClear(buf, size);
    gData_03004158++;
    return buf;
}

/* fn: sub_08073114 */
// @ 0x08073114
void StringFree(void *a)
{
    struct BtlObj **table;
    u32 i;

    table = gData_03004150;
    if (table == 0)
        return;
    for (i = 0; i < gData_03004154; i++)
    {
        if (table[i] != 0 && table[i]->next == a)
        {
            HeapFree(table[i]);
            table[i] = 0;
            gData_03004158--;
            break;
        }
    }
    if (i == gData_03004154)
        DebugPrint(gData_083D2690);
}

/* fn: sub_080731F4 */
// @ 0x080731f4
/* match-compiler: old_agbcc */
s32 StringClear(u8 *s)
{
    s32 n = 0;

    if (s == 0)
        return 0;
    while (*s != 0)
    {
        *s++ = 0;
        n++;
    }
    return n;
}

/* fn: sub_08073218 */
// @ 0x08073218
s32 StringCopy(u8 *src, u8 *dst, u32 n)
{
    u32 i = 0;

    if (src == 0 || dst == 0)
        return 0;

    for (;;)
    {
        u8 c;

        if (i < n)
            dst[i] = src[i];
        else
            dst[n - 1] = 0;

        c = src[i];
        i++;
        if (c == 0)
            break;
    }

    return i;
}

/* fn: sub_0807339C */
// @ 0x0807339c
void StringRemoveLast(u8 *s)
{
    s32 n;

    if (s != 0)
    {
        n = StringLength(s);
        if (n != 0)
            s[n - 1] = 0;
    }
}

/* fn: sub_080733BC */
// @ 0x080733bc
void StringAppendChar(u8 *s, u32 c, u32 cap)
{
    u8 ch;
    s32 n;

    ch = c;
    if (s == 0)
        return;
    n = StringLength(s);
    if ((u32)(n + 1) < cap)
    {
        s[n] = ch;
        s[n + 1] = 0;
    }
}

/* fn: sub_080733E4 */
// @ 0x080733e4
// Appends string src to the end of string dst, a buffer of `size` bytes. A '\n'
// in src is not copied (that byte of dst is left as it was); bytes past the
// buffer are dropped and the last byte is forced to 0. Returns strlen(src), or
// -1 for a NULL argument or an already-full buffer.
s32 StringAppend(const u8 *src, u8 *dst, s32 size)
{
    u8 ch;
    u32 i = 0;

    if (src == NULL || dst == NULL)
        return -1;
    while (*dst != 0)
    {
        size--;
        dst++;
    }
    if (size > 0)
    {
        do
        {
            if (i < size)
            {
                ch = src[i];
                if (ch != '\n')
                    dst[i] = ch;
            }
            else
                dst[size - 1] = 0;
        } while (src[i++] != 0);
    }
    i--;
    return i;
}

/* fn: sub_08073440 */
// @ 0x08073440
s32 StringCompare(void *a, void *b)
{
    u8 *pa = a;
    u8 *pb = b;
    s32 i = 0;
    bool8 done = FALSE;

    if (a == 0 || b == 0)
        return -2;

    while (!done)
    {
        if (pa[i] > pb[i])
            return 1;
        if (pa[i] < pb[i])
            return -1;
        if (pa[i] == 0 && pb[i] == 0)
            done = TRUE;
        i++;
    }

    return 0;
}

/* fn: sub_08073568 */
// @ 0x08073568

u8 StringArrayAlloc(void **out, u8 count, u32 size)
{
    u32 i;
    void **p;

    if (out == 0 || size == 0)
        return 0;

    i = 0;
    if (i < count)
    {
        p = out;
        do
        {
            *p = StringAlloc(size);
            if (*p == 0)
            {
                DebugPrint((void *)0x083D26C0);
                return i;
            }
            p++;
            i++;
        } while (i < count);
    }

    return i;
}

/* fn: sub_080735B0 */
// @ 0x080735b0
void StringArrayFree(void **a, u32 n)
{
    u32 i;

    n = (u8)n;
    if (a == 0)
        return;
    for (i = 0; i < n; i++)
    {
        if (a[i] != 0)
            StringFree(a[i]);
    }
}

/* fn: sub_080737C0 */
// @ 0x080737c0
/* match-compiler: old_agbcc */
s32 StringNextWord(const u8 *src, u8 *dst, s32 size);

// Word-wrap `text` into at most `count` line buffers of `lineSize` bytes, breaking
// before a word that would reach `maxWidth` (glyph metrics from `widths`) and
// after a word that ends in a newline. Returns the number of lines used, or -1.
s32 SplitStringIntoStringArray(void **lines, u8 *text, u8 count, u32 widths, u16 maxWidth, u16 glyph, u16 space, u32 lineSize)
{
    u32 x;
    u8 line;
    bool32 done;
    u8 *word;
    s32 used;
    s32 w;

    x = 0;
    line = 0;
    done = FALSE;
    if (lines == NULL || text == NULL || widths == 0 || *text == 0)
        return -1;
    if (count == 0)
        return -1;
    word = StringAlloc(0x40);
    if (word == NULL)
    {
        DebugPrint((void *)0x083D2720);
        return -1;
    }
    while (!done)
    {
        MemClear(word, 0x40);
        used = StringNextWord(text, word, 0x40);
        w = StringLength(word);
        if (used != 0 && w != 0)
        {
            text += used;
            w = TextMeasureWidth(word, (const u8 *)widths, glyph, space);
            if (x + w + space >= maxWidth)
            {
                x = 0;
                line++;
            }
            if (line < count)
            {
                if (x != 0)
                {
                    StringAppendChar(((u8 **)lines)[line], ' ', lineSize);
                    x += space;
                }
                if (TextHasNewline(word) == 1)
                {
                    StringAppend(word, ((u8 **)lines)[line], lineSize);
                    x = 0;
                    line++;
                }
                else
                {
                    StringAppend(word, ((u8 **)lines)[line], lineSize);
                    x += w;
                }
            }
            else
            {
                DebugPrint((void *)0x083D2760);
                break;
            }
        }
        else
        {
            done = TRUE;
        }
    }
    StringFree(word);
    return line + 1;
}

/* fn: sub_08073910 */
// @ 0x08073910
// Copy the next whitespace-delimited word of `src` into `dst` (at most `size`
// bytes incl. the terminator). Returns the index in `src` after the word.
s32 StringNextWord(const u8 *src, u8 *dst, s32 size_arg)
{
    u32 size = size_arg;
    u32 si;
    u32 di;
    u8 c;

    si = 0;
    di = 0;
    if (src == 0 || dst == 0)
        return 0;
    do
    {
        c = src[si];
        if (c == ' ')
            si++;
    } while (c == ' ');
    if (c == 0)
        return si;
    do
    {
        c = src[si];
        if (c != ' ' && c != 0)
        {
            if (di < size)
            {
                dst[di] = c;
                di++;
                si++;
            }
            else
                dst[size - 1] = 0;
        }
    } while (c != ' ' && c != 0 && c != '\n');
    if (di < size)
        dst[di] = 0;
    else
        dst[size - 1] = 0;
    return si;
}

/* fn: sub_08073A28 */
// @ 0x08073a28

void StringInsertChar(u8 *s, u8 c, u16 n)
{
    s32 len;
    s32 i;
    u16 orig;
    u8 *at;

    orig = n;
    if (s == 0)
        return;
    if (n == 0)
        return;
    len = StringLength(s);
    n = (u16)(n - 1);
    if ((s32)orig > len)
        return;
    i = len;
    at = s + n;
    if (i >= (s32)n)
    {
        do
        {
            s[i + 1] = s[i];
            i--;
        } while (i >= (s32)n);
    }
    *at = c;
}

/* fn: sub_08073AEC */
// @ 0x08073aec
// Copy NUL-terminated `src` into `dst`, expanding every `delim` byte into the
// string `repl`. At most `size` bytes are copied; past that each would-be
// write stores 0 at dst[size - 1] instead (and an overlong `repl` never
// advances, so it spins forever). Always NUL-terminates dst.
void StringExpandDelim(const u8 *src, u8 *dst, const u8 *repl, u8 delim, s32 size)
{
    s32 len;
    u8 ch;
    s32 j;

    len = 0;
    if (src == NULL || dst == NULL || repl == NULL || delim == 0)
        return;
    while (*src != 0)
    {
        ch = *src++;
        if (ch != delim)
        {
            if (len < size)
            {
                *dst++ = ch;
                len++;
            }
            else
            {
                dst[size - 1] = 0;
            }
        }
        else
        {
            for (j = 0; repl[j] != 0;)
            {
                if (len < size)
                {
                    *dst++ = repl[j++];
                    len++;
                }
                else
                {
                    dst[size - 1] = 0;
                }
            }
        }
    }
    *dst = 0;
}
