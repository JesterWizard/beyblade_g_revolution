#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// Hack toggles live in configs/runtime.c (see include/runtime.h).

// Comment out to enable AGBPrint / mGBA printf debugging.
#define NDEBUG

#ifndef NDEBUG

#define PRETTY_PRINT_MINI_PRINTF (0)
#define PRETTY_PRINT_LIBC (1)

#define LOG_HANDLER_AGB_PRINT (0)
#define LOG_HANDLER_NOCASH_PRINT (1)
#define LOG_HANDLER_MGBA_PRINT (2)

#define PRETTY_PRINT_HANDLER (PRETTY_PRINT_MINI_PRINTF)
#define LOG_HANDLER (LOG_HANDLER_MGBA_PRINT)

#endif

#endif // GUARD_CONFIG_H
