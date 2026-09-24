#include "global.h"

// @ 0x0806a4d8
void *sub_0806A4D8(void *minGap, void *regionStart, u32 allocSize, void *hdr, void *node, void *parentOut)
{
    struct Unk6A4D8Node *walk;
    struct Unk6A4D8Node *next;
    struct Unk6A4D8Node *hdrNode;
    struct Unk6A4D8Node *outNode;
    u32 gap;
    u32 regionEnd;
    u8 *insertAt;
    u32 tailRoom;

    hdrNode = hdr;
    outNode = node;
    gap = 0;
    if (hdrNode->unk00 != 0)
        gap = (u32)hdrNode->unk00 - (u32)regionStart;
    if (gap < (u32)minGap)
    {
        outNode->unk00 = (s32 *)regionStart;
        outNode->unk08 = 0;
        outNode->unk0C = hdrNode;
        outNode->unk04 = (u32)minGap;
        hdrNode->unk08 = outNode;
        *(struct Unk6A4D8Node **)parentOut = outNode;
        return outNode;
    }
    walk = hdrNode;
    insertAt = regionStart;
    tailRoom = allocSize;
    if (walk != 0)
    {
        regionEnd = (u32)regionStart + allocSize;
        for (;;)
        {
            next = walk->unk0C;
            if (next != 0)
            {
                if ((u32)next->unk00 - ((u32)walk->unk00 + walk->unk04) >= (u32)minGap)
                {
                    outNode->unk00 = walk->unk00;
                    outNode->unk08 = walk;
                    outNode->unk0C = walk->unk0C;
                    outNode->unk04 = (u32)minGap;
                    walk->unk0C->unk08 = outNode;
                    walk->unk0C = outNode;
                    return outNode;
                }
                walk = next;
            }
            else
            {
                if (walk->unk00 != 0)
                {
                    insertAt = (u8 *)walk->unk00 + walk->unk04;
                    tailRoom = regionEnd - (u32)insertAt;
                }
                else
                {
                    insertAt = regionStart;
                    tailRoom = allocSize;
                }
                break;
            }
        }
    }
    if (tailRoom < (u32)minGap)
        return 0;
    outNode->unk00 = (s32 *)insertAt;
    outNode->unk04 = (u32)minGap;
    outNode->unk0C = 0;
    if (outNode == hdrNode)
        outNode->unk08 = 0;
    else
    {
        outNode->unk08 = walk;
        walk->unk0C = outNode;
    }
    return outNode;
}
