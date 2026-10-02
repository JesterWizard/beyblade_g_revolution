# Modding

A mod is a directory under `mods/` that sits on top of the decomp. The decomp
itself (`src/`, `asm/`, `include/`) is never edited for a mod, so upstream
changes merge cleanly and `make compare` keeps passing.

```
make                    # builds in the default mod (debug_menu): beyblade_g_revolution_debug_menu.gba
make NO_MODS=1          # the vanilla decomp: beyblade_g_revolution.gba
make MOD=example        # a different mod -> beyblade_g_revolution_example.gba
make compare            # always vanilla; checks rom.sha1
make check-vanilla      # vanilla matches AND no mod object was linked
```

The default mod is `DEFAULT_MOD` in the Makefile. If `mods/<DEFAULT_MOD>` does not
exist (a fork without it), plain `make` is vanilla. `MOD=` with nothing after it also
means no mod. Only one mod is built at a time.

## Layout

```
mods/<name>/
  src/*.c, src/*.s      new code (agbcc / Thumb asm), linked past the retail image
  include/              mod-private headers  (-iquote mods/<name>/include)
  hooks.txt             retail functions that jump into the mod code
  mod.mk                optional extra make rules or variables
  README.md
```

Mod C is compiled with `-DMOD=1 -DMOD_NAME=\"<name>\"` and sees the normal
`include/` tree, so names from `symbols.h` and the RAM map work as in the decomp.
`mods/example/` is a complete, minimal mod.

## hooks.txt

```
# <target> <replacement>      replace a retail function with mod code
sub_0802BC14 CollectionIsFull__Replacement
# call <addr> <orig> <repl>   retarget one bl, keep the retail function around it
call 0x080470FC sub_0802D8DC DebugFieldTick
# patch <addr> <hex bytes> [expect <hex bytes>]
patch 0x0806A3DE FC 22 expect FE 22
```

- **Targets** are `sub_XXXXXXXX` identities or `0x08xxxxxx` addresses. Use the
  identity, not a friendly name: renames only change aliases in `symbols.h`,
  the linked symbol stays `sub_XXXXXXXX`, so hooks survive upstream renames.
  Retail code the decomp has not named is labelled `_XXXXXXXX`; `sub_` names
  fall back to that.
- **Replacement hook** (`<target> <replacement>`): overwrites the first 16 bytes
  of the target (18 if it is not 4-aligned) with a stub that jumps to the
  replacement, clobbering only r12. The retail body is gone, so the replacement
  reimplements the function. The target may also be an address in the middle of
  a function: then the replacement must run the displaced instructions itself
  and jump back (see `mods/debug_menu/src/keep_blade.s`).
- **`call`** is the gentle option and the one to prefer. `<addr>` must hold a
  Thumb `bl` whose current target is `<orig>` (checked, so a stale address is
  an error); it is rewritten to call `<repl>`, which calls `<orig>` itself when
  the retail behaviour is still wanted. The replacement must be within +/-4 MB
  of `<addr>`, which holds for the first ~270 KB of mod code.
- **`patch`** overwrites raw bytes. With `expect` the original bytes are
  verified first.
- Overlapping hooks or patches are rejected, as are replacements that point at
  retail code. Replacements are Thumb.

## Calling retail code

Mod C calls retail functions by their `sub_XXXXXXXX` / `_XXXXXXXX` symbol or
friendly alias, declared with an `extern` prototype. A function that has no
symbol yet (it sits inside an asm gap) gets a weak alias in the mod, so a real
label wins once the decomp adds one:

```
	.weak _0803CECC
	.thumb_set _0803CECC, 0x0803CECC      @ mods/debug_menu/src/retail.s
```

## Mod RAM

Mutable data must live in RAM and must not collide with the game. The retail
heap spans all of EWRAM and the `FreeEwramSpaceTop` pool in `asm/ram_map_ewram.s`
is not reserved. `mods/debug_menu` shows a safe way: shrink the heap by 4 KB with
a `patch` (`HeapAlloc` sizes it as `0xFE << 10` bytes at `0x0806A3DE`) and put the
state at `0x0203F000` (`src/ram.s`). Initialise it behind a magic number, since
EWRAM is not cleared at boot.

## Constraints

- Mod ROM data must be `const`: it is linked into ROM. Mutable state belongs in
  RAM, see "Mod RAM" above.
- The ROM grows past 4 MB (`__append_start` = `0x08400000`) and is not padded.
- Mods cannot combine with `compare`; the SHA1 will not match by design.

## Staying in sync with upstream

Keep your mod in `mods/<name>/` of your fork and merge upstream `main` as usual.
Nothing outside `mods/` changes, so there is nothing to untangle. A decomp
discovery (a rename, a struct) lands upstream and your mod picks it up on merge;
`make check-vanilla` confirms nothing leaked into the vanilla build.

Alternatively keep the mod in its own repo and add this one as a submodule at
the root, with `mods/<name>` symlinked or copied in.

## Testing without a display

`tools/mod/emu/` builds a headless mGBA you can script: press buttons, poke
memory, screenshot, save states and call game functions. See its README.
