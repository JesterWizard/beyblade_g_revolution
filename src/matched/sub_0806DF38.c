#include "global.h"
#include "ram_map.h"
#include "battle.h"

// @ 0x0806df38
// Collect up to maxCount (track, key) hits for `key` across a's keyframe
// tracks, skipping track `skip`. Each hit records the track, key index, track
// index and the 16-byte frames either side of the key. Returns the hit count.
u16 KeyframeFindHits(struct UnkDEC8 *a, struct UnkDF38Entry *out, void *skip, u16 maxCount, u32 key)
{
    u16 count;
    s32 idx;
    struct Unk6E31CTrack *track;
    u8 *frames;
    s32 i;
    u32 *keys;

    count = 0;
    for (idx = 0; idx < a->unk00->unk04; idx++)
    {
        track = (struct Unk6E31CTrack *)ChunkListAt(a, idx);
        if (track == NULL)
            break;
        if (track == skip)
            continue;
        frames = (u8 *)track->unk20 + track->unk00 * 4;
        keys = track->unk20;
        for (i = 0; i < track->unk00; i++)
        {
            if (key == keys[i])
            {
                out[count].unk00 = (s32 *)track;
                out[count].unk04 = i;
                out[count].unk08 = idx;
                out[count].unk0C = i > 0 ? frames + (i - 1) * 16 : NULL;
                if (i < track->unk00 - 1)
                    out[count].unk10 = frames + i * 16;
                else
                    out[count].unk10 = NULL;
                count++;
                if (count >= maxCount)
                    return count;
            }
        }
    }
    return count;
}

