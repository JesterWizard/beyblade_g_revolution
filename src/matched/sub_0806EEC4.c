#include "global.h"

// @ 0x0806eec4
// Returns the first motion slot of `state`, the one the camera follows.
struct MapLayer *CameraGetActive(struct MapView *state)
{
    return state->layers;
}
