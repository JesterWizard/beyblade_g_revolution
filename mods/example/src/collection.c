#include "global.h"

/* Example mod: the collection never reports full. Reimplements
 * CollectionIsFull (sub_0802BC14); the retail body is overwritten by the hook. */
s32 CollectionIsFull__Replacement(s16 a)
{
    return 0;
}
