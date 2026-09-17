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
void sub_08071FC8(s32 a);
u32 sub_08074264(u32 a, u32 b);

#endif /* GUARD_UNKNOWN_FUNCTIONS_H */
