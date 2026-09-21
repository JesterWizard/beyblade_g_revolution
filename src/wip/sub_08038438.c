s32 sub_08038438(u32 arg0)
{
    u16 i;
    u16 j;
    s16 k;
    u32 *p;
    struct Unk38438 *s;

    i = 0;
    p = (u32 *)gData_08079068[0];
    while (p != 0 && p != (u32 *)arg0) {
        i++;
        p = (u32 *)gData_08079068[i];
    }
    if (gData_030003CC[0] == 0)
        return -1;
    j = 0;
    k = (s16)i;
    do {
        s = (struct Unk38438 *)gData_030003CC[0];
        if (k == s->unk00[j]) {
            s->unk22[j]++;
            return (s8)j;
        }
        j++;
    } while ((s16)j <= 0x0F);
    j = 0;
    do {
        s = (struct Unk38438 *)gData_030003CC[0];
        if (((s->unk20 >> (s16)j) & 1) == 0) {
            s->unk00[j] = i;
            s->unk20 |= 1 << j;
            s->unk22[j] = 1;
            _08073C4C((void *)gData_08079358[i],
                      (void *)(gData_05000200 + ((s16)j << 5)), 0x20,
                      (void *)gData_080BB8C0[0]);
            return (s8)j;
        }
        j++;
    } while ((s16)j <= 0x0F);
    return -1;
}
