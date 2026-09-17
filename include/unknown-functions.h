#ifndef GUARD_UNKNOWN_FUNCTIONS_H
#define GUARD_UNKNOWN_FUNCTIONS_H

/*
 * Declarations for still-unnamed functions, so every TU agrees on signatures.
 * Add a prototype here when semantic C needs to call another sub_*.
 * Named replacements belong in [renames] (Phase 4), then this entry drops.
 */

s8 sub_08042BE8(s16 a);
void sub_0806A434(void *a);
void sub_08071F84(s32 a);
void sub_08071FC8(s32 a, u32 b);
u32 sub_08074264(u32 a, u32 b);
void sub_080601C4(u32 a, u32 b);
void sub_080717F0(u32 a);
u16 sub_08071808(void);
s32 sub_08073440(void *a, void *b);
void sub_08033574(void);
void sub_080686D8(void *a);
void sub_08068418(void *a);
void sub_08072CC0(void);
void sub_08063104(void);
void sub_08035258(u32 a, u32 b);
void sub_08067CE8(void *a, u32 b);
struct Unk71F84 *sub_08071F44(s32 a);
void sub_08071FAC(s32 a);
void sub_080312D8(struct Unk312EC *a);
void sub_080312EC(struct Unk312EC *a);
void sub_08031294(void *a);
void sub_080705DC(void *a, u8 b);
void sub_080700CC(void *a);
void *sub_08069988(u8 a);
u32 sub_08069C14(struct Unk69C14 *a);
void *sub_08068014(struct Unk68014 **slot, u32 i);
void sub_080400C0(u32 v);
void sub_08067890(void);
u16 sub_08061784(void);
u16 sub_080617B4(void);
u32 sub_08061A98(void);
u16 sub_08061AA8(void);

#endif /* GUARD_UNKNOWN_FUNCTIONS_H */
