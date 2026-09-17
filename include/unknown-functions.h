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

#endif /* GUARD_UNKNOWN_FUNCTIONS_H */
