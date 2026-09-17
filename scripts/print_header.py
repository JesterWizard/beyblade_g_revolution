#!/usr/bin/env python3
"""Print GBA cartridge header fields from baserom.gba."""

from pathlib import Path
import sys

path = Path(sys.argv[1] if len(sys.argv) > 1 else "baserom.gba")
if not path.is_file():
    sys.exit(f"missing ROM: {path}")

data = path.read_bytes()
if len(data) < 0xC0:
    sys.exit("ROM too small for a GBA header")

title = data[0xA0:0xAC].decode("ascii", errors="replace")
game_code = data[0xAC:0xB0].decode("ascii", errors="replace")
maker = data[0xB0:0xB2].decode("ascii", errors="replace")
version = data[0xBC]

print(f"size:       {len(data)} ({len(data) // (1024 * 1024)} MiB)")
print(f"title:      {title!r}")
print(f"game_code:  {game_code!r}")
print(f"maker_code: {maker!r}")
print(f"revision:   {version}")
print()
print("Makefile values:")
print(f"TITLE      := {title.rstrip()}")
print(f"GAME_CODE  := {game_code}")
print(f"MAKER_CODE := {maker}")
print(f"REVISION   := {version}")
