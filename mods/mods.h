/*
 * Build-time gates for the mods in mods/<name>/.
 *
 * `make` builds every mod set to 1 here, together, into beyblade_g_revolution.gba.
 * Set a line to 0 to leave that mod out. The Makefile reads this file with sed,
 * so keep one `#define MOD_<NAME> <0|1>` per line (<NAME> is the directory name
 * in upper case). A new mod needs a line here; `make MOD=<name>` and
 * `make NO_MODS=1` still override the file from the command line.
 */
#ifndef MODS_H
#define MODS_H

#define MOD_DEBUG_MENU      1
#define MOD_THOUGHT_BUBBLES 1
#define MOD_FAST_SAVE       1
#define MOD_BITBEAST_BARS   1
#define MOD_SHOW_MATH       1
#define MOD_SINGLE_MATCH    1
#define MOD_CUSTOM_MUSIC    1
#define MOD_CUSTOM_VOICES   1
#define MOD_SKIP_INTRO      1

#endif /* MODS_H */
