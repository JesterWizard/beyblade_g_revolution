# example

Smallest possible mod: `CollectionIsFull` always returns 0.

    make MOD=example      # -> beyblade_g_revolution_example.gba

- `src/*.c`, `src/*.s`: new code, compiled with agbcc and linked after the retail image.
- `include/`: mod-private headers.
- `hooks.txt`: which retail functions jump into your code.
