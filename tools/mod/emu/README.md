# Headless emulator harness

Runs a ROM in mGBA without a window: press keys, read and write memory, take
screenshots, save states, and call game functions directly. It is how the debug
menu was checked (no display needed).

```
tools/mod/emu/build.sh                 # builds mGBA 0.10.2 + helper into build/emu/ (once)
```

```python
import sys; sys.path.insert(0, "tools/mod/emu")
from emu import Emu

e = Emu("beyblade_g_revolution_debug_menu.gba", "work.sav")   # .sav is optional
e.frames(300)                      # run frames
e.press("L", hold=3, wait=40)      # buttons: A B SELECT START UP DOWN LEFT RIGHT L R, "A+B" combines
e.r32(0x03000198)                  # peek (also r8, r16; w8, w16, w32 poke)
e.shot("out.png", scale=2)
e.save("x.state"); e.load("x.state")
e.call(0x08042BE8, 4000)           # call a Thumb function, returns r0
e.until(addr, r0, r1, r2, r3, [t1, t2])   # run until the pc reaches one of the targets
```

Notes:
- One emulator per process (the helper keeps a single core).
- `call` and `until` switch to system mode with IRQs off and restore every
  register afterwards. Good for pure functions and branch checks; do not use
  them on code that waits for VBlank.
- mGBA prints its log to stdout; `emu.py` redirects it to /dev/null and gives you
  a clean `sys.stdout`.
