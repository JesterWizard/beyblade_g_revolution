#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/serialize.h>
#include <mgba/gba/core.h>
#include <mgba/internal/arm/arm.h>
#include <mgba-util/vfs.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct mCore *core;
static uint32_t *vbuf;

int emu_load(const char *rom, const char *sav) {
    core = mCoreFind(rom);
    if (!core) return -1;
    core->init(core);
    mCoreInitConfig(core, NULL);
    vbuf = calloc(256 * 256, 4);
    core->setVideoBuffer(core, (color_t *)vbuf, 256);
    if (!mCoreLoadFile(core, rom)) return -2;
    if (sav) {
        struct VFile *v = VFileOpen(sav, O_RDWR | O_CREAT);
        if (v) core->loadSave(core, v);
    }
    core->reset(core);
    return 0;
}
void emu_frame(unsigned keys, int n) {
    core->setKeys(core, keys);
    for (int i = 0; i < n; i++) core->runFrame(core);
}
unsigned emu_r8(unsigned a)  { return core->busRead8(core, a); }
unsigned emu_r16(unsigned a) { return core->busRead16(core, a); }
unsigned emu_r32(unsigned a) { return core->busRead32(core, a); }
void emu_w8(unsigned a, unsigned v)  { core->busWrite8(core, a, v); }
void emu_w16(unsigned a, unsigned v) { core->busWrite16(core, a, v); }
void emu_w32(unsigned a, unsigned v) { core->busWrite32(core, a, v); }
/* RGBA bytes 240x160 */
void emu_shot(unsigned char *out) {
    for (int y = 0; y < 160; y++) for (int x = 0; x < 240; x++) {
        uint32_t c = vbuf[y * 256 + x];
        unsigned char *o = out + (y * 240 + x) * 4;
        o[0] = c & 0xFF; o[1] = (c >> 8) & 0xFF; o[2] = (c >> 16) & 0xFF; o[3] = 255;
    }
}
int emu_savestate(const char *path) {
    struct VFile *v = VFileOpen(path, O_CREAT | O_TRUNC | O_RDWR);
    if (!v) return -1; int r = mCoreSaveStateNamed(core, v, SAVESTATE_ALL); v->close(v); return r;
}
int emu_loadstate(const char *path) {
    struct VFile *v = VFileOpen(path, O_RDONLY);
    if (!v) return -1; int r = mCoreLoadStateNamed(core, v, SAVESTATE_ALL); v->close(v); return r;
}

/* Call a game function (Thumb) from the host. Returns r0, or 0xDEAD0000 on timeout. */
unsigned emu_call(unsigned fn, unsigned a0, unsigned a1, unsigned a2, unsigned a3, int maxsteps) {
    unsigned saved[16], cpsr, v, i;
    char name[8];
    const unsigned RET = 0x08000000 + 0xC0; /* inside the ROM header: never fetched as code */
    for (i = 0; i < 16; i++) { snprintf(name, 8, "r%d", i); core->readRegister(core, name, &saved[i]); }
    core->readRegister(core, "cpsr", &cpsr);
    v = 0x1F | 0x20 | 0x80; core->writeRegister(core, "cpsr", &v);   /* system, thumb, irq off */
    core->readRegister(core, "sp", &v); v = (v - 0x100) & ~7u; core->writeRegister(core, "sp", &v);
    v = RET | 1; core->writeRegister(core, "lr", &v);
    core->writeRegister(core, "r0", &a0); core->writeRegister(core, "r1", &a1);
    core->writeRegister(core, "r2", &a2); core->writeRegister(core, "r3", &a3);
    v = fn & ~1u; core->writeRegister(core, "pc", &v);
    unsigned r0 = 0xDEAD0000;
    for (int n = 0; n < maxsteps; n++) {
        core->step(core);
        unsigned pc; core->readRegister(core, "pc", &pc);
        if (pc >= RET && pc <= RET + 6) { core->readRegister(core, "r0", &r0); break; }
    }
    for (i = 0; i < 16; i++) { snprintf(name, 8, "r%d", i); core->writeRegister(core, name, &saved[i]); }
    core->writeRegister(core, "cpsr", &cpsr);
    return r0;
}

/* Run from fn until the pc reaches one of targets[] (halfword addresses); returns that target or 0. */
unsigned emu_until(unsigned fn, unsigned a0, unsigned a1, unsigned a2, unsigned a3, unsigned *targets, int nt, int maxsteps) {
    unsigned saved[16], cpsr, v, i;
    char name[8];
    for (i = 0; i < 16; i++) { snprintf(name, 8, "r%d", i); core->readRegister(core, name, &saved[i]); }
    core->readRegister(core, "cpsr", &cpsr);
    v = 0x1F | 0x20 | 0x80; core->writeRegister(core, "cpsr", &v);
    core->readRegister(core, "sp", &v); v = (v - 0x100) & ~7u; core->writeRegister(core, "sp", &v);
    core->writeRegister(core, "r0", &a0); core->writeRegister(core, "r1", &a1);
    core->writeRegister(core, "r2", &a2); core->writeRegister(core, "r3", &a3);
    v = fn & ~1u; core->writeRegister(core, "pc", &v);
    unsigned hit = 0;
    for (int n = 0; n < maxsteps && !hit; n++) {
        core->step(core);
        unsigned pc; core->readRegister(core, "pc", &pc);
        for (int k = 0; k < nt; k++) if (pc >= targets[k] && pc <= targets[k] + 6) { hit = targets[k]; break; }
    }
    for (i = 0; i < 16; i++) { snprintf(name, 8, "r%d", i); core->writeRegister(core, name, &saved[i]); }
    core->writeRegister(core, "cpsr", &cpsr);
    return hit;
}

/* Run n frames instruction by instruction and count how often the pc is at each
 * of targets[] (even addresses, Thumb or ARM). counts[k] gets the hits. */
static unsigned hist[512][5]; static int nhist;
int emu_hist_regs(unsigned i, unsigned *r1, unsigned *r2, unsigned *r3) { if (i >= (unsigned)nhist) return 0; *r1 = hist[i][2]; *r2 = hist[i][3]; *r3 = hist[i][4]; return 1; }
int emu_hist(unsigned i, unsigned *tgt, unsigned *r0) { if (i >= (unsigned)nhist) return 0; *tgt = hist[i][0]; *r0 = hist[i][1]; return 1; }
void emu_trace(unsigned keys, int nframes, unsigned *targets, int nt, unsigned *counts, unsigned *r0at) {
    struct ARMCore *cpu = (struct ARMCore *) core->cpu;
    nhist = 0;
    core->setKeys(core, keys);
    for (int k = 0; k < nt; k++) { counts[k] = 0; r0at[k] = 0; }
    uint32_t start = core->frameCounter(core);
    while (core->frameCounter(core) - start < (uint32_t) nframes) {
        core->step(core);
        unsigned pc = cpu->gprs[ARM_PC] - (cpu->executionMode == MODE_THUMB ? 4 : 8);
        for (int k = 0; k < nt; k++) if (pc == targets[k]) { counts[k]++; r0at[k] = cpu->gprs[0]; if (nhist < 512) { hist[nhist][0] = targets[k]; hist[nhist][1] = cpu->gprs[0]; hist[nhist][2] = cpu->gprs[1]; hist[nhist][3] = cpu->gprs[2]; hist[nhist][4] = cpu->gprs[4]; nhist++; } }
    }
}

/* Run up to nframes frames instruction by instruction until the word at addr changes.
 * Returns the pc of the instruction that changed it (0 if it did not); old/new in out[0..1], lr, r0-r3 in out[2..6]. */
unsigned emu_watch(unsigned keys, int nframes, unsigned addr, unsigned *out) {
    struct ARMCore *cpu = (struct ARMCore *) core->cpu;
    core->setKeys(core, keys);
    unsigned old = core->busRead32(core, addr);
    uint32_t start = core->frameCounter(core);
    unsigned last_pc = 0;
    while (core->frameCounter(core) - start < (uint32_t) nframes) {
        last_pc = cpu->gprs[ARM_PC] - (cpu->executionMode == MODE_THUMB ? 4 : 8);
        core->step(core);
        unsigned now = core->busRead32(core, addr);
        if (now != old) {
            out[0] = old; out[1] = now; out[2] = cpu->gprs[ARM_LR];
            for (int i = 0; i < 4; i++) out[3 + i] = cpu->gprs[i];
            return last_pc;
        }
    }
    return 0;
}
