#!/usr/bin/env python3
"""Turns settings.txt into the `patch` lines for the charge_levels mod.

    gen_settings.py <mod dir> <output hooks file>

The retail attack release (sub_08030388) stores the recovery after an attack,
in frames, with a `movs r0, #n` per charge level; the patch rewrites the
immediate of each one.
"""

import sys

# name -> (address of the movs, retail value)
RECOVERY = {
    "recovery_light": (0x0803055C, 75),
    "recovery_medium": (0x0803058C, 90),
    "recovery_heavy": (0x080305FA, 120),
}


def main():
    mod_dir, out = sys.argv[1], sys.argv[2]
    values = {}
    with open(f"{mod_dir}/settings.txt") as f:
        for n, line in enumerate(f, 1):
            line = line.split("#")[0].strip()
            if not line:
                continue
            key, _, val = line.partition("=")
            key = key.strip()
            if key not in RECOVERY:
                sys.exit(f"settings.txt:{n}: unknown setting '{key}'")
            try:
                values[key] = int(val.strip())
            except ValueError:
                sys.exit(f"settings.txt:{n}: '{val.strip()}' is not a number")
    lines = ["# Generated from settings.txt by tools/gen_settings.py. Do not edit."]
    for key, (addr, retail) in RECOVERY.items():
        v = values.get(key, retail)
        if not 1 <= v <= 255:
            sys.exit(f"settings.txt: {key} must be 1..255 frames, not {v}")
        lines.append(f"patch 0x{addr:08X} {v:02X} expect {retail:02X}")
    with open(out, "w") as f:
        f.write("\n".join(lines) + "\n")


main()
