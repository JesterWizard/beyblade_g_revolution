#include "global.h"

/* Custom voices. voices.txt lists audio files; tools/gen_voices.py turns each into one chunk
 * of the sound engine's own ADPCM format (voices_data.s). A chunk is played once with
 * SoundPlay(chunk, 0); the mixer stops the channel at its end. See mods/custom_music for the
 * format. */

struct Voice {
    const void *chunk;
    u8 launch;  /* plays when the player's blade is launched */
    u8 replace; /* retail sound effect it plays instead of, 255 for none */
    u8 pad[2];
};

extern const u32 gVoiceCount;
extern const struct Voice gVoices[];

/* Plays a voice at the sound effect volume. Returns the channel handle, or -1. */
static s32 PlayVoice(const struct Voice *v)
{
    s32 handle = (s32)SoundPlay((void *)v->chunk, 0);

    if (handle != -1)
        SoundSetVolume(handle, gMainWorkPtr->sfxVolume);
    return handle;
}

/* The player's blade has been released (called by the hook in launch.s). */
void VoiceOnLaunch(void)
{
    u32 i, n = 0, pick = 0;

    for (i = 0; i < gVoiceCount; i++)
        n += gVoices[i].launch;
    if (n == 0)
        return;
    if (n > 1)
        pick = RandRange(n);
    for (i = 0; i < gVoiceCount; i++)
        if (gVoices[i].launch) {
            if (pick == 0) {
                PlayVoice(&gVoices[i]);
                return;
            }
            pick--;
        }
}

/* Replaces SfxPlayInSlot (sub_080601C4): effect `a` at note `b`, in the effect's own handle
 * slot so that SfxStopSlot still stops it. Retail body otherwise. */
void SfxPlayInSlot__Voices(u32 a, u32 b)
{
    struct MainWork *work = gMainWorkPtr;
    const struct Voice *v = 0;
    u32 i;

    for (i = 0; i < gVoiceCount; i++)
        if (gVoices[i].replace == a)
            v = &gVoices[i];

    if (work->sfxHandles[a] != -1)
        SoundStop(work->sfxHandles[a]);

    if (v) {
        work->sfxHandles[a] = PlayVoice(v);
    } else {
        work->sfxHandles[a] = (s32)SoundPlayIndexed(a, b);
        SoundSetVolume(work->sfxHandles[a], work->sfxVolume);
    }
}
