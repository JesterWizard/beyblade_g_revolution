#include "global.h"
#include "bgm.h"

/* Custom BGM. tracks.txt lists audio files; tools/gen_music.py turns each into
 * chunks of the engine's own ADPCM format (music_data.s). Track 17 + i is
 * gCustomBgm[i]. The sound engine is the retail one:
 *  - a chunk is {type 0, byte length, 0, 0} + 4-bit ADPCM; the mixer decodes it
 *    (IWRAM 0x03004B74) and, when a chunk ends, steps along the channel's list;
 *  - SoundPlayFromList(list, index) plays list[index[0]] and, at its end, the
 *    next entry of index, -1 meaning "back to index[0]"; so index {0, -1} on a
 *    one-entry list repeats that chunk forever;
 *  - SoundPlay(chunk, n) plays one chunk once and stops it at the end.
 * An intro is a chunk that the channel is started on after the loop chunk was
 * set up as the list. */

struct CustomBgm {
    const void *const *list; /* [0] = the chunk that plays (and repeats) */
    const void *intro;       /* played once before the list, or 0 */
    const char *name;
    u8 replace;              /* retail track this one plays instead of, 255 for none */
    u8 overworld;            /* joins the overworld's random draw */
    u8 loop;                 /* repeats; otherwise plays once */
    u8 pad;
};

extern const u32 gCustomBgmCount;
extern const struct CustomBgm gCustomBgm[];

static const s16 sLoopIndex[2] = { 0, -1 };

u32 CustomBgmCount(void)
{
    return gCustomBgmCount;
}

const char *CustomBgmName(u32 i)
{
    return i < gCustomBgmCount ? gCustomBgm[i].name : "?";
}

/* The custom track that plays for BGM number `track`, or -1 if retail does. */
s32 CustomBgmFind(u32 track)
{
    u32 i;

    if (track >= BGM_TRACKS)
        return track - BGM_TRACKS < gCustomBgmCount ? (s32)(track - BGM_TRACKS) : -1;
    for (i = 0; i < gCustomBgmCount; i++)
        if (gCustomBgm[i].replace == track)
            return i;
    return -1;
}

/* Called by the BgmPlay hook once the retail code has done its part (for a
 * replaced track that includes playing the retail one, which is stopped here). */
void CustomBgmStart(u32 track)
{
    const struct CustomBgm *t;
    struct MainWork *work = gMainWorkPtr;
    struct SoundChannel *ch;
    s32 i = CustomBgmFind(track);
    s32 handle;

    if (i < 0)
        return;
    t = &gCustomBgm[i];

    if (work->bgmHandle != -1)
        SoundStop(work->bgmHandle);

    if (!t->loop) {
        handle = (s32)SoundPlay((void *)t->list[0], 0);
    } else {
        /* Started on the loop chunk; the mixer must not run between the start
         * and the switch to the intro. */
        REG_IME = 0;
        handle = (s32)SoundPlayFromList((void *)t->list, (u32)sLoopIndex);
        if (handle != -1 && t->intro) {
            ch = SoundFindChannel(handle);
            ch->data = (s32)t->intro;
            ch->cursor = (s32)t->intro + 0x10;
        }
        REG_IME = 1;
    }
    work->bgmHandle = handle;
    if (handle != -1)
        SoundSetVolume(handle, work->bgmVolume);
}

/* RandRange(6) in the three places that pick the overworld track. */
u32 CustomBgmRand(u32 n)
{
    u32 i, k, r, pool = 0;

    if (n == BGM_A_NEW_DAY + 1) {
        for (i = 0; i < gCustomBgmCount; i++)
            pool += gCustomBgm[i].overworld;
    }
    r = RandRange(n + pool);
    if (r < n)
        return r;
    /* r - n selects the (r - n)th overworld custom track */
    k = r - n;
    for (i = 0; i < gCustomBgmCount; i++)
        if (gCustomBgm[i].overworld) {
            if (k == 0)
                return BGM_TRACKS + i;
            k--;
        }
    return 0;
}
