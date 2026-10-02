#include "global.h"
#include "ram_map.h"

/* A 128x64 picture drawn over the overworld and the world map, chosen by the
 * latest story event flag (bubbles.txt), toggled with L. The picture is two
 * 64x64 OBJ sprites: the last two OAM entries, the top 128 tiles of OBJ VRAM
 * and OBJ palette slot 12. The engine hands those out last (its sprite slots
 * and VRAM spans are first-fit, and the overworld uses well under half), so it
 * does not know about them. */

#define KEY_L 0x200

#define BUBBLE_MAGIC 0x7B0BB1E5
#define NO_FLAG 0xFFFF
#define PAL_SLOT 12
#define FIRST_TILE 0x380 /* 2 x 64 tiles, up to the end of OBJ VRAM (0x400) */
#define TILE_WORDS (2 * 64 * 32 / 4)
#define OBJ_VRAM ((u32 *)(0x06010000 + FIRST_TILE * 32))
#define OAM_FIRST 126
#define OAM_ENTRY(i) ((vu16 *)(0x07000000 + (i) * 8))
/* The pictures' tail ends at (68, 56); that point goes just above the head. */
#define TAIL_X 68
#define TAIL_Y 56
#define HEAD_GAP -10 /* the player sprite has about 12 px of empty space above the head */
#define OAM_HIDE 0x0200 /* attribute 0: disabled */
#define OAM_SIZE_64 0xC000 /* attribute 1: 64x64 */

struct BubbleImage {
    const u32 *tiles; /* 4 KB, the two halves */
    const u16 *palette; /* 16 colours */
};

struct BubbleFlag {
    u16 flag;
    u16 image;
};

extern const struct BubbleImage gBubbleImages[];
extern const struct BubbleFlag gBubbleFlags[]; /* ends at flag NO_FLAG */

/* All of it lives in RAM at gBubble (ram.s); EWRAM is not cleared at boot, so
 * it is only trusted behind the magic number. */
struct BubbleState {
    u32 magic;
    u32 flags[8]; /* the event flags as of the last frame */
    u16 latest; /* index into gBubbleFlags of the latest flag, NO_FLAG for none */
    u8 shown; /* L toggle */
    u8 drawn; /* the OAM entries are live */
};

extern struct BubbleState gBubble;

static bool32 FlagSet(const u32 *flags, u32 flag)
{
    return (flags[flag >> 5] >> (flag & 31)) & 1;
}

/* The latest flag is the newest one the table lists that became set since the
 * last frame; several at once (a save was loaded) leave the one listed last.
 * It drops out when the game clears it, falling back to the last listed flag
 * that is still set, so a loaded save shows the bubble for where it stands. */
static void TrackFlags(void)
{
    const struct BubbleFlag *e;
    u32 now[8];
    u32 i;

    for (i = 0; i < 8; i++)
        now[i] = gData_03000610.words[i];
    for (e = gBubbleFlags, i = 0; e->flag != NO_FLAG; e++, i++) {
        if (FlagSet(now, e->flag) && !FlagSet(gBubble.flags, e->flag))
            gBubble.latest = i;
    }
    if (gBubble.latest != NO_FLAG && !FlagSet(now, gBubbleFlags[gBubble.latest].flag)) {
        gBubble.latest = NO_FLAG;
        for (e = gBubbleFlags, i = 0; e->flag != NO_FLAG; e++, i++) {
            if (FlagSet(now, e->flag))
                gBubble.latest = i;
        }
    }
    for (i = 0; i < 8; i++)
        gBubble.flags[i] = now[i];
}

static void InitState(void)
{
    u8 *p = (u8 *)&gBubble;
    u32 i;

    for (i = 0; i < sizeof(gBubble); i++)
        p[i] = 0;
    gBubble.magic = BUBBLE_MAGIC;
    gBubble.latest = NO_FLAG;
}

/* True when the picture is still where it was put. The engine can wipe OBJ
 * VRAM and the palette slots when a map loads, so sample a few words. */
static bool32 GfxIntact(const struct BubbleImage *img)
{
    u32 i;

    for (i = 0; i < TILE_WORDS; i += 61) {
        if (OBJ_VRAM[i] != img->tiles[i])
            return FALSE;
    }
    return OBJ_VRAM[TILE_WORDS - 1] == img->tiles[TILE_WORDS - 1];
}

static void LoadGfx(const struct BubbleImage *img)
{
    u32 i;

    if (!GfxIntact(img)) {
        VBlankIntrWait();
        for (i = 0; i < TILE_WORDS; i++)
            OBJ_VRAM[i] = img->tiles[i];
    }
    /* ObjPalLoadSlot also registers the slot for palette fades; the table is
     * emptied when a map loads, which is the cue to load again. */
    if (gUnk_030008D0 != NULL && gUnk_030008D0->unk00[PAL_SLOT] != img->palette)
        ObjPalLoadSlot(PAL_SLOT, (void *)img->palette);
}

/* Top-left of the picture on screen: the player's sprite position (world
 * position minus the camera, both 24.8) with the tail on its head, kept on
 * screen. Recomputed every frame so it follows the walk and the scrolling. */
static void BubbleOrigin(s32 *x, s32 *y)
{
    struct MainWork *work = gMainWorkPtr;
    struct MapLayer *camera = &((struct MapView *)work)->layers[0];
    struct Actor *player = (struct Actor *)&work->unk036C;
    s32 head = ((work->unk0370 - camera->offsetX) >> 8) + (player->width >> 1);
    s32 top = ((work->unk0374 - camera->offsetY) >> 8) - HEAD_GAP;

    *x = head - TAIL_X;
    *y = top - TAIL_Y;
    if (*x < 0)
        *x = 0;
    else if (*x > 240 - 128)
        *x = 240 - 128;
    if (*y < 0)
        *y = 0;
    else if (*y > 160 - 64)
        *y = 160 - 64;
}

static void SetOam(bool32 visible)
{
    s32 x, y;
    u32 half;

    BubbleOrigin(&x, &y);

    for (half = 0; half < 2; half++) {
        vu16 *oam = OAM_ENTRY(OAM_FIRST + half);

        if (visible) {
            oam[0] = y;
            oam[1] = (x + half * 64) | OAM_SIZE_64;
            oam[2] = (FIRST_TILE + half * 64) | (PAL_SLOT << 12); /* priority 0: in front */
        } else {
            oam[0] = OAM_HIDE;
        }
    }
    gBubble.drawn = visible;
}

/* Called in place of CursorHistoryReplayStep, once per overworld frame (town
 * and world map alike). */
void BubbleFieldTick(void)
{
    struct MainWork *work;
    bool32 idle;

    CursorHistoryReplayStep();
    if (gBubble.magic != BUBBLE_MAGIC)
        InitState();
    TrackFlags();

    work = gMainWorkPtr;
    idle = work->unk180C == 0 && work->unk185A == 1;
    if (idle && (gData_03004060 & KEY_L))
        gBubble.shown ^= 1;

    if (gBubble.shown && idle) {
        u32 image = gBubble.latest == NO_FLAG ? 0 : gBubbleFlags[gBubble.latest].image;

        LoadGfx(&gBubbleImages[image]);
        SetOam(TRUE);
    } else if (gBubble.drawn) {
        SetOam(FALSE);
    }
}
