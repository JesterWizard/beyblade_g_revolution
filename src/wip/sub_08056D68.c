#include "global.h"

void sub_08056D68(struct Unk56D68 *event)
{
    switch (event->unk04)
    {
    case 0x3D73:
        gMainWorkPtr->unk17F7 = event->unk08;
        gMainWorkPtr->unk17F6 = event->unk0C;
        gMainWorkPtr->unk1834 = 1;
        break;
    case 0x47EE:
        gMainWorkPtr->unk1828 = event->unk08;
        break;
    case 0x5989:
        gMainWorkPtr->unk182C = event->unk08;
        break;
    case 0x6A74:
        gMainWorkPtr->unk1828 = event->unk08;
        break;
    case 0x9E3B:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        event = (struct Unk56D68 *)((u8 *)event + 8);
        gMainWorkPtr->unk181D = 0;
        gMainWorkPtr->unk16C8 = event;
        sub_0802D52C(0, 1);
        break;
    case 0xBEE4:
        if (gMainWorkPtr->unk03AC != 0 || gMainWorkPtr->unk03B0 != 0)
            break;
        event = (struct Unk56D68 *)((u8 *)event + 8);
        gMainWorkPtr->unk181D = 1;
        gMainWorkPtr->unk16C8 = event;
        sub_0802D52C(1, 1);
        {
            struct Unk2B95C *result;

            result = (struct Unk2B95C *)sub_0802B95C(gMainWorkPtr->unk16C8);
            if (result != 0)
                gMainWorkPtr->unk1794 = result->unk00;
            else
                gMainWorkPtr->unk1794 = -1;
        }
        break;
    case 0xCE50:
        event = (struct Unk56D68 *)((u8 *)event + 8);
        gMainWorkPtr->unk16C8 = event;
        sub_08056F84();
        break;
    case 0xD791:
        event = (struct Unk56D68 *)((u8 *)event + 8);
        gMainWorkPtr->unk181D = 3;
        gMainWorkPtr->unk16C8 = event;
        sub_0802D52C(3, 1);
        break;
    case 0xE319:
        event = (struct Unk56D68 *)((u8 *)event + 8);
        gMainWorkPtr->unk16C8 = event;
        sub_08059DC8(0, sub_08043BDC());
        break;
    }
}
