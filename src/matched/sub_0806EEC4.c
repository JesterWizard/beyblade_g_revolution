#include "global.h"

// @ 0x0806eec4
// Returns the first motion slot of `state`, the one the camera follows.
struct Unk68E54 *CameraGetActive(struct Unk6EE48 *state)
{
    return state->motion;
}
