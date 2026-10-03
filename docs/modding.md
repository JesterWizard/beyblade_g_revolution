# Modding

A mod is a directory under `mods/` that sits on top of the decomp. The decomp
itself (`src/`, `asm/`, `include/`) is never edited for a mod, so upstream
changes merge cleanly and `make compare` keeps passing.

```
make                    # builds every default mod together into beyblade_g_revolution.gba
make NO_MODS=1          # the vanilla decomp: beyblade_g_revolution.gba
make MOD=example        # only that mod, still beyblade_g_revolution.gba
make MOD="a b"          # several mods in one ROM
make compare            # always vanilla; checks rom.sha1 (rebuilds the mod ROM afterwards)
make check-vanilla      # vanilla matches AND no mod object was linked (rebuilds the mod ROM afterwards)
```

The default mods are the `#define MOD_<NAME> 1` gates in [`mods/mods.h`](../mods/mods.h) (`<NAME>` is the directory name in upper case); set a gate to 0 to leave a mod out, and add a line there for a new mod. One that does not exist
in a fork is skipped, and if none exist plain `make` is vanilla. `MOD=` with nothing
after it also means no mod.

Mods built together must not touch the same bytes: every `call`, `pointer`, hook and
`patch` has to be at a different place. The one exception is an identical `patch`
(same address, same bytes), which is applied once, so two mods can both shrink the
heap for their state page. Give each mod its own variable names in `mod.mk` (a
recipe runs after every `mod.mk` has been read) and, in the shared EWRAM page
`0x0203F000`, its own part of it (`debug_menu` the first 2 KB, `thought_bubbles` the
rest).

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
# pointer <addr> <orig> <repl>   retarget a function pointer stored in ROM data
pointer 0x08099784 sub_0805A304 DebugPortraitOp
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
- **`pointer`** rewrites a Thumb function pointer held in ROM data (a script
  opcode or jump table entry). The word must currently be `<orig>|1`. Use it to
  wrap a handler that is only ever called through a table.
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
heap spans all of EWRAM (`0x02000800`–`0x02040000`, sized `0xFE << 10` at
`0x0806A3DE` and `0x0806A622`). The mods shrink it to `0x80 << 10` (128 KB, a
play-through peaks near 67 KB; check with `tools/ram_survey.py`), so
`0x02020800`–`0x02040000` is free: that is `FreeEwramSpaceTop`..`Bottom` in
`asm/ram_map_ewram.s`. `mods/debug_menu` puts its state at `0x0203F000`
(`src/ram.s`); `mods/bitbeast_bars` keeps a picture, tile and OAM backup at
`0x02038000` (`gBitBeastBarsBuf` in the RAM map). If you need more, lower the byte in the `patch` (both sites). Initialise it behind a magic number, since
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
