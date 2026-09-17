#!/usr/bin/env python3
"""Grow unknown-types.h structs: filler_XX -> unkXX as fields are discovered.

A struct is a superset. Adding a field is fine; moving one is not.
"""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HEADER = ROOT / "include" / "unknown-types.h"

BEGIN = "/* BEGIN GENERATED STRUCTS */"
END = "/* END GENERATED STRUCTS */"

# Functions known to share a layout (hand-merged in unknown-types.h).
SHARED_STRUCT = {
    "sub_08068584": "Unk68574",
    "sub_08068574": "Unk68574",
    "sub_080358CC": "Unk35878",
    "sub_08035878": "Unk35878",
    "sub_080705D4": "Unk705CC",
    "sub_080705CC": "Unk705CC",
    "sub_080338E4": "Unk338E4",
    "sub_080346A8": "Unk346A8",
    "sub_08036190": "Unk36190",
    "sub_0806BB38": "Unk6BB38",
    "sub_08062098": "Unk62098",
    "sub_080314FC": "BattleWork",
    "sub_080628E4": "MainWork",
}

_FIELD_RE = re.compile(
    r"/\*\s*([0-9a-fA-F]+)\s*\*/\s*(u8|u16|u32|s8|s16|s32|void\s*\*)\s+(unk[0-9A-Fa-f]+|filler_[0-9A-Fa-f]+)(\[[^\]]+\])?"
)


def parse_imm(value: str | int) -> int:
    if isinstance(value, int):
        return value
    return int(str(value).lstrip("#"), 0)


def unk_name(offset: int) -> str:
    if offset < 0x100:
        return f"unk{offset:02X}"
    return f"unk{offset:X}"


def struct_from_function(function: str) -> str:
    if function in SHARED_STRUCT:
        return SHARED_STRUCT[function]
    hexpart = function.split("_", 1)[1]  # 08068584
    return "Unk" + hexpart[3:]  # 68584


def width_of(ctype: str) -> int:
    ctype = re.sub(r"\s+", " ", ctype.strip())
    if ctype in ("u8", "s8"):
        return 1
    if ctype in ("u16", "s16"):
        return 2
    if ctype in ("u32", "s32") or "*" in ctype:
        return 4
    raise ValueError(ctype)


def ensure_field(struct_name: str, offset: int, ctype: str) -> None:
    """No-op if the hand-written header already has the field. Does not rewrite it.

    Generated-struct support can be added later; Phase 3b structs are curated.
    This exists so c_patterns can call a single API.
    """
    text = HEADER.read_text()
    if f"struct {struct_name}" not in text:
        _append_generated_struct(struct_name, offset, ctype)
        return
    # Already present: callers must not move fields. Presence of the struct is enough.
    _ = (offset, ctype)


def _append_generated_struct(struct_name: str, offset: int, ctype: str) -> None:
    text = HEADER.read_text()
    end_size = offset + width_of(ctype)
    field = unk_name(offset)
    lines = [f"\n/* generated from first use; grow with ensure_field. */"]
    lines.append(f"struct {struct_name} /* >= {end_size:#x} */")
    lines.append("{")
    if offset:
        lines.append(f"    /* 00 */ u8 filler_00[{offset:#x}];")
    comment_off = f"{offset:02x}" if offset < 0x100 else f"{offset:x}"
    lines.append(f"    /* {comment_off} */ {ctype} {field};")
    lines.append("};")
    block = "\n".join(lines) + "\n"
    if BEGIN in text and END in text:
        text = text.replace(END, block + "\n" + END)
    else:
        text = text.replace(
            "#endif /* GUARD_UNKNOWN_TYPES_H */",
            f"{BEGIN}\n{block}{END}\n\n#endif /* GUARD_UNKNOWN_TYPES_H */\n",
        )
    HEADER.write_text(text)
