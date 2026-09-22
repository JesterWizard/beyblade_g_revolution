#!/usr/bin/env python3
"""Audit that prototypes, definitions and call sites agree on arity.

`make compare` proves the **ROM**, never the C: matched C is not linked, so a
function can be declared with one shape, defined with another, and called with a
third, and every gate stays green. `sub_080674B4` shipped exactly that way -- the
header left it unprototyped, the definition claimed `(const void *src, void *dest)`
(a memory-copy shape), and all 38 call sites passed no arguments. It was actually
BIOS VBlankIntrWait, so the most-called function in the ROM carried the most
misleading signature in the tree.

`audit_c_compiles.py` cannot see this (each file compiles fine in isolation), and
`repair_naked_signatures.py` only fires once compilation has already failed. This
tool cross-checks the sources of truth against each other:

  1. prototypes  `include/unknown-functions.h`
  2. definitions `src/matched/*.c`
  3. call sites  `src/matched/*.c` + `src/decompiled/*.c`

Readable names from `include/symbols.h` are folded back to their `sub_` label, so
renamed functions stay checkable. `fix_stub_arities.py` consumes `analyse()` to
repair the readable-Thumb stubs this reports.

Usage:
    python3 tools/decomp/audit_signatures.py [--dirs matched,decompiled] [--json]
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
HEADER = ROOT / "include" / "unknown-functions.h"
SYMBOLS_H = ROOT / "include" / "symbols.h"

LABEL_RE = re.compile(r"\bsub_[0-9A-Fa-f]{5,8}\b")
DEFINE_RE = re.compile(r"#define\s+([A-Za-z_]\w*)\s+(sub_[0-9A-Fa-f]{5,8})\b")

# `...` is genuinely variadic and `()` is K&R; neither constrains call sites.
UNSPECIFIED = object()

CALL_ISH = set("=!&|<>,?+-/%^~(")
STATEMENT_KEYWORDS = (
    "if", "while", "for", "switch", "return", "else", "do", "sizeof", "case", "goto",
)
TYPE_PREFIX_RE = re.compile(r"^[A-Za-z0-9_\s*\[\]]+$")

# weight > 0 means "this source is making a real claim about the arity";
# 0 means "this is a placeholder signature, believe the callers instead".
WEIGHT_HEADER = 3
WEIGHT_PROTOTYPE = 2
WEIGHT_DEFINITION = 2
WEIGHT_STUB_DEFINITION = 0
WEIGHT_CALL = 1


@dataclasses.dataclass(frozen=True)
class Signature:
    arity: int | object
    params: str
    file: str
    line: int

    @property
    def specified(self) -> bool:
        return self.arity is not UNSPECIFIED


@dataclasses.dataclass
class Report:
    dirs: list[str]
    declarations: dict[str, Signature]
    definitions: dict[str, Signature]
    local_prototypes: dict[str, Signature]
    calls: list[tuple[str, int, str, int]]
    conflicts: list[dict[str, object]]
    bad_calls: list[dict[str, object]]
    expected: dict[str, int]


def strip_noise(text: str) -> str:
    """Blank out comments, string/char literals and preprocessor lines.

    `asm("bl sub_080674B4\\n")` is not a C call and a `','` char literal is not an
    argument separator. Preprocessor lines go too, so an `#include` above the first
    declaration is not mistaken for call context. Replacements preserve character
    count, so line numbers derived from offsets stay correct.
    """
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        ch = text[i]
        if ch == "#" and (i == 0 or text[i - 1] == "\n"):
            while i < n and text[i] != "\n":
                out[i] = " "
                i += 1
        elif ch == "/" and i + 1 < n and text[i + 1] == "/":
            while i < n and text[i] != "\n":
                out[i] = " "
                i += 1
        elif ch == "/" and i + 1 < n and text[i + 1] == "*":
            while i < n and not (text[i] == "*" and i + 1 < n and text[i + 1] == "/"):
                out[i] = " "
                i += 1
            for _ in range(2):
                if i < n:
                    out[i] = " "
                    i += 1
        elif ch in "\"'":
            quote = ch
            out[i] = " "
            i += 1
            while i < n and text[i] != quote:
                if text[i] == "\\" and i + 1 < n:
                    out[i] = " "
                    i += 1
                out[i] = " "
                i += 1
            if i < n:
                out[i] = " "
                i += 1
        else:
            i += 1
    return "".join(out)


def split_args(text: str) -> list[str]:
    """Split on top-level commas, respecting nesting."""
    args: list[str] = []
    depth = 0
    current: list[str] = []
    for ch in text:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            args.append("".join(current).strip())
            current = []
        else:
            current.append(ch)
    tail = "".join(current).strip()
    if tail or args:
        args.append(tail)
    return [a for a in args if a]


def match_call(text: str, start: int) -> tuple[str, int] | None:
    """From `start` (a `(`), return the parenthesised body and the index after it."""
    if start >= len(text) or text[start] != "(":
        return None
    depth, i = 0, start
    while i < len(text):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return text[start + 1 : i], i + 1
        i += 1
    return None


def count_params(params: str) -> int | object:
    stripped = params.strip()
    if stripped in ("", "...") or stripped.endswith(", ..."):
        return UNSPECIFIED
    if stripped == "void":
        return 0
    return len(split_args(stripped))


def line_of(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def statement_prefix(text: str, offset: int) -> str:
    """Text between the name and the start of its statement."""
    start = max(text.rfind(";", 0, offset), text.rfind("{", 0, offset), text.rfind("}", 0, offset))
    return text[start + 1 : offset]


def looks_like_declaration(prefix: str) -> bool:
    """Whether a prefix reads as a return type rather than a call's lead-in.

    A bare `sub_080674B4();` statement has an empty prefix and is a call; so is
    anything containing an operator, an opening paren (`if (`, a nested call).
    """
    p = prefix.strip()
    if not p or any(c in CALL_ISH for c in p):
        return False
    if not TYPE_PREFIX_RE.match(p):
        return False
    first = re.split(r"[^A-Za-z0-9_]", p)[0]
    return first not in STATEMENT_KEYWORDS


def read_aliases() -> dict[str, str]:
    """readable name -> sub_XXXX, from the generated symbols.h."""
    if not SYMBOLS_H.is_file():
        return {}
    return {a: l for a, l in DEFINE_RE.findall(SYMBOLS_H.read_text(errors="replace"))}


def resolve(word: str, aliases: dict[str, str]) -> str | None:
    label = word if word.startswith("sub_") else aliases.get(word)
    if label is not None and re.fullmatch(r"sub_[0-9A-Fa-f]{5,8}", label):
        return label
    return None


def scan(path: pathlib.Path, aliases: dict[str, str]) -> tuple[
    dict[str, Signature], dict[str, Signature], list[tuple[str, int, int]]
]:
    """Return (prototypes, definitions, calls) found in one .c file."""
    clean = strip_noise(path.read_text(errors="replace"))
    rel = str(path.relative_to(ROOT))
    protos: dict[str, Signature] = {}
    defs: dict[str, Signature] = {}
    calls: list[tuple[str, int, int]] = []

    for m in re.finditer(r"\b(" + LABEL_RE.pattern + r"|[A-Za-z_]\w*)\s*\(", clean):
        label = resolve(m.group(1), aliases)
        if label is None:
            continue
        body = match_call(clean, m.end() - 1)
        if body is None:
            continue
        params, after = body
        line = line_of(clean, m.start())
        sig = Signature(count_params(params), params, rel, line)

        if clean[after:].lstrip()[:1] == "{":
            defs.setdefault(label, sig)
        elif looks_like_declaration(statement_prefix(clean, m.start())):
            protos.setdefault(label, sig)
        else:
            calls.append((label, len(split_args(params)), rel, line))

    return protos, defs, calls


def is_semantic_stub_free(raw: str) -> bool:
    """Whether a file's definition is real C rather than a readable-Thumb body."""
    return "__attribute__((naked))" not in raw


def analyse(dirs: list[str]) -> Report:
    aliases = read_aliases()

    declarations: dict[str, Signature] = {}
    if HEADER.is_file():
        clean = strip_noise(HEADER.read_text(errors="replace"))
        source = str(HEADER.relative_to(ROOT))
        for m in re.finditer(LABEL_RE.pattern + r"\s*\(", clean):
            label = m.group(0)[:-1].strip()
            body = match_call(clean, m.end() - 1)
            if body is None:
                continue
            declarations.setdefault(
                label, Signature(count_params(body[0]), body[0], source, line_of(clean, m.start()))
            )

    definitions: dict[str, Signature] = {}
    local_prototypes: dict[str, Signature] = {}
    calls: list[tuple[str, int, str, int]] = []
    for d in dirs:
        for path in sorted((ROOT / "src" / d).glob("*.c")):
            protos, file_defs, file_calls = scan(path, aliases)
            for name, sig in file_defs.items():
                definitions.setdefault(name, sig)
            for name, sig in protos.items():
                local_prototypes.setdefault(name, sig)
            calls.extend(file_calls)

    claims: dict[str, list[tuple[int, str, int]]] = {}
    open_signature: set[str] = set()

    def add(name: str, arity: int, source: str, weight: int) -> None:
        claims.setdefault(name, []).append((arity, source, weight))

    for name, sig in declarations.items():
        if sig.specified:
            add(name, sig.arity, "include/unknown-functions.h (prototype)", WEIGHT_HEADER)
        else:
            open_signature.add(name)
    for name, sig in local_prototypes.items():
        if sig.specified:
            add(name, sig.arity, f"{sig.file}:{sig.line} (local prototype)", WEIGHT_PROTOTYPE)
    for name, sig in definitions.items():
        if not sig.specified:
            open_signature.add(name)
            continue
        # A readable-Thumb stub declares `(void)` because its asm body ignores the
        # registers, so its signature is a placeholder: weight it below a caller.
        stub = not is_semantic_stub_free((ROOT / sig.file).read_text(errors="replace"))
        add(
            name,
            sig.arity,
            f"{sig.file} (definition{', asm stub' if stub else ''})",
            WEIGHT_STUB_DEFINITION if stub else WEIGHT_DEFINITION,
        )
    for name, arity, rel, line in calls:
        add(name, arity, f"{rel}:{line} (call)", WEIGHT_CALL)

    conflicts: list[dict[str, object]] = []
    expected: dict[str, int] = {}
    for name, entries in sorted(claims.items()):
        arities = {a for a, _s, _w in entries}
        if len(arities) == 1:
            expected[name] = arities.pop()
            continue
        if name in open_signature and all(w <= WEIGHT_CALL for _a, _s, w in entries):
            # A deliberately open signature (`void f();` or `f(...)`) whose only
            # concrete claims are call sites: varying arity is the point, not a bug.
            continue
        by_arity: dict[int, list[tuple[str, int]]] = {}
        for arity, source, weight in entries:
            by_arity.setdefault(arity, []).append((source, weight))
        # Highest-quality single source wins, then breadth of corroboration.
        best = max(by_arity, key=lambda a: (max(w for _s, w in by_arity[a]), len(by_arity[a])))
        expected[name] = best
        conflicts.append({
            "name": name,
            "claims": {
                str(arity): sorted(s for s, _w in value)
                for arity, value in sorted(by_arity.items(), key=lambda kv: -len(kv[1]))
            },
            "expected": best,
        })

    bad_calls: list[dict[str, object]] = []
    for name, arity, rel, line in calls:
        if name in expected and expected[name] != arity:
            bad_calls.append({
                "name": name, "file": rel, "line": line,
                "detail": f"called with {arity} arg(s), expected {expected[name]}",
            })

    return Report(dirs, declarations, definitions, local_prototypes, calls, conflicts, bad_calls, expected)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dirs", default="matched,decompiled", help="comma-separated src/ subdirs")
    ap.add_argument("--json", action="store_true", help="machine-readable output")
    args = ap.parse_args()
    dirs = [d.strip() for d in args.dirs.split(",") if d.strip()]

    report = analyse(dirs)

    if args.json:
        print(json.dumps(
            {"conflicts": report.conflicts, "call_sites": report.bad_calls}, indent=2
        ))
        return 0

    print("=== signature arity audit ===")
    print(f"  dirs                              : {', '.join(report.dirs)}")
    print(f"  prototypes in unknown-functions.h : {len(report.declarations)}")
    print(f"  definitions in C                  : {len(report.definitions)}")
    print(f"  call sites                        : {len(report.calls)}")
    print(f"  functions with conflicting arity  : {len(report.conflicts)}")
    print(f"  call sites on the wrong arity     : {len(report.bad_calls)}")

    if report.conflicts:
        print("\n  Functions whose sources disagree on arity:")
        for row in report.conflicts:
            print(f"    {row['name']}  -> expected {row['expected']} arg(s)")
            for arity, sources in row["claims"].items():
                shown = sources if len(sources) <= 3 else [*sources[:3], f"+{len(sources) - 3} more"]
                print(f"        {arity} arg(s) from {', '.join(shown)}")

    if report.bad_calls:
        print("\n  Call sites that disagree with the expected arity:")
        for row in report.bad_calls:
            print(f"    {row['name']}  {row['file']}:{row['line']}  {row['detail']}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
