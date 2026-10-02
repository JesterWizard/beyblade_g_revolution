#!/usr/bin/env python3
"""Apply a mod's hooks.txt to a linked ROM (called by `make MOD=<name>`).

usage: apply_hooks.py <elf> <rom> <hooks.txt>

hooks.txt, one directive per line (`#` starts a comment):

    <target> <replacement>      redirect a retail Thumb function to mod code
    call <addr> <orig> <repl>   retarget one Thumb `bl` inside a retail function
    pointer <addr> <orig> <repl>
                                retarget one Thumb function pointer stored in ROM data
                                (a jump or script-opcode table entry)
    patch <addr> <hex bytes> [expect <hex bytes>]
                                overwrite raw ROM bytes (tables, constants); with
                                `expect` the original bytes are verified first

<target> is a symbol or a 0x08xxxxxx address; use the `sub_XXXXXXXX` identity,
not a friendly name (names are aliases and the ELF only carries identities).
<replacement> is a symbol from the mod's own code.

`call` keeps the surrounding retail function intact. <addr> must hold a `bl`
whose current target is <orig> (checked, so a stale address is an error); it is
rewritten to call <repl>, which should call <orig> itself if the original
behaviour is still wanted. <repl> must be within +/-4 MB of <addr>, so keep
mod code small or use a hook to a veneer.

A hook overwrites the first 16 bytes of the target (18 when the target is not
4-aligned) with a LynJump stub: Thumb `bx pc`, then ARM `ldr ip, [pc]; bx ip`,
then the replacement address. It clobbers only r12, so all four argument
registers survive. The original function body is gone, so the replacement
must reimplement it.
"""

from __future__ import annotations

import struct
import subprocess
import sys
from pathlib import Path

ROM_BASE = 0x08000000
STUB = struct.pack("<HHII", 0x4778, 0x46C0, 0xE59FC000, 0xE12FFF1C)  # + POIN
NOP = struct.pack("<H", 0x46C0)


def load_symbols(elf: Path) -> dict[str, tuple[int, int | None]]:
    out = subprocess.check_output(["arm-none-eabi-nm", "-S", str(elf)], text=True)
    syms: dict[str, tuple[int, int | None]] = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 3:
            addr, kind, name = parts
            size = None
        elif len(parts) == 4:
            addr, size_s, kind, name = parts
            size = int(size_s, 16)
        else:
            continue
        syms[name] = (int(addr, 16), size)
    return syms


def resolve(token: str, syms: dict, *, thumb: bool, where: str) -> tuple[int, int | None]:
    if token.lower().startswith("0x"):
        return int(token, 16) | (1 if thumb else 0), None
    if token not in syms:
        # Retail code the decomp has not named yet is labelled _XXXXXXXX.
        alt = "_" + token[4:] if token.startswith("sub_") else None
        if alt in syms:
            token = alt
        else:
            sys.exit(f"{where}: unknown symbol '{token}' (hooks use sub_XXXXXXXX identities)")
    addr, size = syms[token]
    return (addr | 1 if thumb else addr), size


def decode_bl(rom: bytes, addr: int) -> int | None:
    """Target of the Thumb `bl` pair at addr, or None if it is not one."""
    off = addr - ROM_BASE
    hi, lo = struct.unpack_from("<HH", rom, off)
    if hi & 0xF800 != 0xF000 or lo & 0xF800 != 0xF800:
        return None
    imm = ((hi & 0x7FF) << 12) | ((lo & 0x7FF) << 1)
    if imm & 0x400000:
        imm -= 0x800000
    return addr + 4 + imm


def encode_bl(addr: int, target: int) -> bytes:
    imm = (target & ~1) - (addr + 4)
    if not -0x400000 <= imm < 0x400000:
        raise ValueError("out of bl range")
    return struct.pack("<HH", 0xF000 | ((imm >> 12) & 0x7FF), 0xF800 | ((imm >> 1) & 0x7FF))


class Rom:
    def __init__(self, data: bytearray) -> None:
        self.data = data
        self.owner: dict[int, str] = {}

    def write(self, addr: int, blob: bytes, who: str) -> None:
        off = addr - ROM_BASE
        if off < 0 or off + len(blob) > len(self.data):
            sys.exit(f"{who}: 0x{addr:08X}+{len(blob)} is outside the ROM")
        for i in range(off, off + len(blob)):
            if i in self.owner:
                sys.exit(f"{who}: overlaps bytes already written by {self.owner[i]}")
            self.owner[i] = who
        self.data[off : off + len(blob)] = blob


def main() -> int:
    if len(sys.argv) != 4:
        print(__doc__)
        return 2
    elf, rom_path, hooks = (Path(a) for a in sys.argv[1:])
    syms = load_symbols(elf)
    rom = Rom(bytearray(rom_path.read_bytes()))
    count = 0

    for n, raw in enumerate(hooks.read_text().splitlines(), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        where = f"{hooks}:{n}"
        words = line.split()

        if words[0] == "patch":
            if len(words) < 3:
                sys.exit(f"{where}: patch <addr> <hex bytes>")
            addr = int(words[1], 16)
            try:
                if "expect" in words:
                    k = words.index("expect")
                    blob = bytes(int(b, 16) for b in words[2:k])
                    want = bytes(int(b, 16) for b in words[k + 1 :])
                else:
                    blob, want = bytes(int(b, 16) for b in words[2:]), None
            except ValueError:
                sys.exit(f"{where}: bad hex byte list")
            if want is not None:
                have = bytes(rom.data[addr - ROM_BASE : addr - ROM_BASE + len(want)])
                if have != want or len(blob) != len(want):
                    sys.exit(f"{where}: 0x{addr:08X} holds {have.hex()}, expected {want.hex()}")
            rom.write(addr, blob, line)
        elif words[0] == "call":
            if len(words) != 4:
                sys.exit(f"{where}: call <addr> <orig> <repl>")
            addr = int(words[1], 16)
            orig, _ = resolve(words[2], syms, thumb=False, where=where)
            repl, _ = resolve(words[3], syms, thumb=True, where=where)
            found = decode_bl(rom.data, addr)
            if found is None:
                sys.exit(f"{where}: 0x{addr:08X} is not a Thumb bl")
            if found != (orig & ~1):
                sys.exit(f"{where}: bl at 0x{addr:08X} calls 0x{found:08X}, not {words[2]} (0x{orig & ~1:08X})")
            try:
                blob = encode_bl(addr, repl)
            except ValueError:
                sys.exit(f"{where}: '{words[3]}' is more than 4 MB from 0x{addr:08X}")
            rom.write(addr, blob, line)
        elif words[0] == "pointer":
            if len(words) != 4:
                sys.exit(f"{where}: pointer <addr> <orig> <repl>")
            addr = int(words[1], 16)
            orig, _ = resolve(words[2], syms, thumb=False, where=where)
            repl, _ = resolve(words[3], syms, thumb=True, where=where)
            have = struct.unpack_from("<I", rom.data, addr - ROM_BASE)[0]
            if have != (orig | 1):
                sys.exit(f"{where}: 0x{addr:08X} holds 0x{have:08X}, not a pointer to {words[2]} (0x{orig | 1:08X})")
            rom.write(addr, struct.pack("<I", repl | 1), line)
        elif len(words) == 2:
            target, size = resolve(words[0], syms, thumb=False, where=where)
            repl, _ = resolve(words[1], syms, thumb=True, where=where)
            if repl - 1 < ROM_BASE + 0x400000:
                sys.exit(f"{where}: '{words[1]}' is retail code, not mod code")
            lead = NOP if target % 4 == 2 else b""
            blob = lead + STUB + struct.pack("<I", repl)
            if size is not None and size < len(blob):
                print(f"warning: {where}: {words[0]} is {size} bytes, stub needs {len(blob)}")
            rom.write(target, blob, line)
        else:
            sys.exit(f"{where}: expected '<target> <replacement>', 'call ...', 'pointer ...' or 'patch ...'")
        count += 1

    rom_path.write_bytes(rom.data)
    print(f"applied {count} hook(s) from {hooks}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
