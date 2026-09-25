#ifndef GUARD_RUNTIME_CONFIG_H
#define GUARD_RUNTIME_CONFIG_H

#include "gba/types.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/*
 * Build-time hack toggles (ROM const copy).
 * Edit configs/runtime.c, then rebuild.
 */
typedef struct {
    /* sub_0803EAC0 masks bit-beast experience with 0x3FFF after each ±16.
     * The pool word 0x00003FFF disassembles as `subs r7, #255`. */
    u8 uncapBitBeastExp;
    /* Three bytes so setRPMTo stays a 4-aligned word at offset 4. */
    u8 _padSetRpm[3];
    /* After sub_0803CECC, player 0's launch RPM and spin cap are replaced.
     * 0 leaves the retail formula. 1..99999 is the forced value. Above
     * 99999 is clamped to 99999. */
    u32 setRPMTo;
    /* sub_08031094 keeps player 0's bit-beast gauge at its full 0..36 reading. */
    u8 fullBitBeastGauge;
    /* sub_08044E54 zeros the save record before unpacking it. The blade table
     * is copied record -> live, so that wipe is what gets written to EEPROM. */
    u8 keepBitBeastExp;
    /* Launch RPM is stored as a full word, then sub_080302E0 shifts it << 16
     * and divides as signed. At 32768 and above the shift is negative, the
     * spin step runs backward, and the battle treats the blade as empty. */
    u8 fixHighExpRpm;
    /* sub_08037F98 compares the two result bytes at BattleWork+0x138/+0x139.
     * The lower one loses their equipped beyblade, unless it is the last blade
     * or the battle mode is one of 7, 8, 9, 10, 11. */
    u8 keepBeybladeOnLoss;
    /* Equipped ripcord (inventory type 2). sub_0803D51C subtracts the part id
     * plus strength from its health byte, which starts at 100. At 0 the part
     * breaks and the battle treats the blade as empty. */
    u8 infiniteRipcordHealth;
    /* Equipped launcher (inventory type 3). Same wear function as the ripcord. */
    u8 infiniteLauncherHealth;
    /* sub_08041E88 stores the overworld step at MainWork+0x17B0. Walking is
     * 0x100 per frame; holding B raises it to 0x200. This byte multiplies
     * that step. 1 is retail speed. 0 stores a zero step, so the character
     * stands still. */
    u8 overworldSpeed;
} RuntimeConfig;

extern const RuntimeConfig gRuntimeConfigRom;
#define gRuntimeConfig gRuntimeConfigRom

#define _maybe_unused __attribute__((unused))

#define LYN_REPLACE_CHECK(name) \
    extern __typeof__(name) name; \
    static const void *const _maybe_unused lyn_exists_check_##name = &name

#define APPEND_TEXT __attribute__((section(".append_text")))
#define APPEND_RODATA __attribute__((section(".append_rodata")))
#define APPEND_DATA __attribute__((section(".append_data")))

#endif /* GUARD_RUNTIME_CONFIG_H */
