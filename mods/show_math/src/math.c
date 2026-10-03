#include "global.h"
#include "ram_map.h"
#include "battle.h"

/* Show the numbers behind a blade's stars on the detail panel (the workshop's
 * blade screen, DetailPanelDraw). The retail formulas are in docs/mechanics.md:
 *
 *   attack  = ring + disk + base (byte 0 of the part rows) + exp / 100
 *   defense = same with byte 1
 *
 * where exp is what the battle setup (sub_08031728) uses as the launch base for
 * the player: the character's experience (MainWork.expPoints) plus the blade's
 * bit beast experience. An attack (or a defense) is worth its sum times 1, 2 or 3 depending on how much
 * charge it had when released, so all three are shown. The launch RPM is
 * sub_0803CECC with the power meter at 100 and the boost at 0:
 *
 *   quot = (exp << 16) / 25600
 *   rpm  = (quot * (100 << 8)) >> 16 + strength * 100 */

#define LAUNCH_POWER 100
#define LAUNCH_BOOST 0
#define EXP_MAX 32767

/* The panel's text window starts 8 px right of the screen's left edge; the
 * tile columns of TextRowSetPaletteBank are screen columns. */
#define TEXT_ORIGIN_X 8
#define BAR_FIRST_COL 0x0A
#define BAR_LAST_COL 0x18
#define BANK_NORMAL 0x0F
#define BANK_SELECTED 0x0E

#define ATT_X 70
#define ATT_Y 71
#define DEF_Y 79
#define END_Y 87

extern void sub_080507B8(u8 *panel);

static char *PutInt(char *p, s32 v)
{
    char tmp[12];
    s32 n = 0;

    if (v < 0)
        v = 0;
    do {
        tmp[n++] = '0' + DivRemainder(v, 10);
        v = Div(v, 10);
    } while (v > 0);
    while (n > 0)
        *p++ = tmp[--n];
    return p;
}

/* Screen x just past the widest number (`end` is the widest so far). Nothing is
 * kept between calls: a mod `static` lands in .bss at 0x03000000, on top of vanilla
 * IWRAM (see asm/ram_map_iwram.s), so ShowMathBar measures the numbers again instead
 * of remembering where ShowMathPanel put them. */
static u32 Place(u32 x, u32 y, const char *s, u32 draw, u32 end)
{
    u32 right;

    if (draw) {
        TextSetCursor(x, y);
        TextDrawAlign((void *)s, x, 2);
    }
    right = TEXT_ORIGIN_X + x + TextMeasureWidth((const u8 *)s, (const u8 *)gUnk_03000798->widthTable,
        gUnk_03000798->glyphWidth, gUnk_03000798->spacing);
    return right > end ? right : end;
}

static u32 PlaceTriple(u32 y, s32 v, u32 draw, u32 end)
{
    char buf[24];
    char *p = buf;

    p = PutInt(p, v);
    *p++ = '/';
    p = PutInt(p, v * 2);
    *p++ = '/';
    p = PutInt(p, v * 3);
    *p = 0;
    return Place(ATT_X, y, buf, draw, end);
}

/* Draws the numbers (draw != 0) or only measures them; returns the screen x just
 * past the widest one, 0 when there is nothing to show. */
static u32 Layout(struct BeybladeBuild *rec, u32 draw)
{
    s32 exp;
    s32 bonus;
    s32 attack;
    s32 defense;
    s32 quot;
    s32 rpm;
    char buf[24];
    char *p;
    u32 end = 0;

    if (rec == NULL || rec->beybladeId == -1)
        return 0;
    exp = rec->unk26 + gMainWorkPtr->expPoints;
    if (exp < 0)
        exp = 0;
    if (exp > EXP_MAX)
        exp = EXP_MAX;
    bonus = Div(exp, 100);

    attack = gData_0807BDB8[rec->weightDisk * 4] + gData_0807BB80[(s8)rec->bladeBase * 4]
        + gData_0807B6F0[rec->attackRing * 4] + bonus;
    defense = gData_0807BDB8[rec->weightDisk * 4 + 1] + gData_0807BB80[(s8)rec->bladeBase * 4 + 1]
        + gData_0807B6F0[rec->attackRing * 4 + 1] + bonus;

    quot = Div(exp << 16, 25600);
    rpm = ((quot * (LAUNCH_POWER << 8)) >> 16) + ((quot * (LAUNCH_BOOST << 8)) >> 16)
        + gMainWorkPtr->strength * (LAUNCH_POWER + LAUNCH_BOOST);

    end = PlaceTriple(ATT_Y, attack, draw, end);
    end = PlaceTriple(DEF_Y, defense, draw, end);
    p = buf;
    *p++ = 'R';
    *p++ = 'P';
    *p++ = 'M';
    *p++ = ' ';
    p = PutInt(p, rpm);
    *p = 0;
    return Place(ATT_X, END_Y, buf, draw, end);
}

static struct BeybladeBuild *PanelEntry(void)
{
    struct Unk4FFCCRow *row = &gData_030006BC[gData_030006AC + gData_030006B0];

    return row->unk0C >= 0 ? CollectionFindEntry(row->unk0C, row->unk0E) : NULL;
}

/* Commits the row palettes (retail sub_080507B8), then narrows the selected part's
 * bar. Also hooked where the panel's key handlers move the selection. While a part
 * is being picked, the retail code lights the selected part row from column 0x0A to
 * 0x18, which runs across the numbers. The bar starts after them instead (the part
 * names are right aligned and start further right). */
void ShowMathBar(u8 *panel)
{
    u32 numbersEnd;

    sub_080507B8(panel);
    numbersEnd = gUnk_030006B8 != 0 ? Layout(PanelEntry(), 0) : 0;
    if (numbersEnd != 0) {
        u32 selRow = (u32)(((s32)(s8)panel[0x2D5] << 1) + 6);
        u32 first = (numbersEnd + 7) >> 3;

        if (first < BAR_FIRST_COL)
            first = BAR_FIRST_COL;
        if (first <= BAR_LAST_COL) {
            TextRowSetPaletteBank(selRow, BANK_NORMAL, BAR_FIRST_COL, BAR_LAST_COL);
            TextRowSetPaletteBank(selRow, BANK_SELECTED, first, BAR_LAST_COL);
        }
    }
}

void ShowMathPanel(u8 *panel)
{
    Layout(PanelEntry(), 1);
    ShowMathBar(panel);
}
