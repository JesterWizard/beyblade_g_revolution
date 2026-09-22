#!/usr/bin/env python3
"""Align readable-Thumb stub signatures with the arity their callers use.

A readable-Thumb stub in `src/matched/` is a raw asm body, so its C signature is
pure documentation — and a stub that says `(void)` while its callers pass seven
arguments is worse than no signature at all. `audit_signatures.py` reports those
conflicts; this repairs them by taking the parameter list from the most
authoritative prototype available and rewriting the stub to agree.

Because the body is asm, the parameters are never read, so a correct repair
cannot change the emitted bytes. That is still checked per file with
`match_function.py`, and anything that stops matching is reverted.

Usage:
    python3 tools/decomp/fix_stub_arities.py [--apply] [--dirs matched]
"""

from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))

from audit_signatures import (  # noqa: E402
    ROOT,
    UNSPECIFIED,
    analyse,
    is_semantic_stub_free,
    read_aliases,
    split_args,
)

TYPE_WORDS = {
    "void", "char", "short", "int", "long", "float", "double", "unsigned", "signed",
    "const", "volatile", "static", "s8", "s16", "s32", "s64", "u8", "u16", "u32", "u64",
    "struct", "union", "enum", "bool",
}


def has_name(param: str) -> bool:
    """Whether a parameter already carries an identifier."""
    tokens = [t for t in re.split(r"[\s*\[\]]+", param.strip()) if t]
    if len(tokens) < 2:
        return False
    return tokens[-1] not in TYPE_WORDS


def named_params(params: str) -> str:
    """Copy a prototype's parameter list, naming any that are anonymous.

    A definition must name its parameters, but a prototype need not, so
    `(void *)` has to become `(void *a)`.
    """
    out: list[str] = []
    for i, param in enumerate(split_args(params)):
        text = param.strip()
        if not has_name(text):
            name = "abcdefghijklmnopqrstuvwxyz"[i] if i < 26 else f"p{i}"
            text = f"{text} {name}".replace("  ", " ")
        out.append(text)
    return ", ".join(out)


def best_params(label: str, report) -> list[tuple[str, str]]:
    """Candidate parameter lists, best first: (params, source).

    Ordering matters because a stub is a separate translation unit: a type named
    only in some *caller's* local prototype is not visible where the stub is
    compiled, so copying that text can fail to compile. Candidates are tried in
    order and the first that still matches is kept, so a precise type is used
    where it is visible and opaque pointers are the fallback.
    """
    want = report.expected.get(label)
    if want is None:
        return []
    candidates: list[tuple[str, str]] = []
    for table, source in (
        (report.declarations, "include/unknown-functions.h"),
        (report.local_prototypes, "local prototype"),
    ):
        sig = table.get(label)
        if sig is not None and sig.specified and sig.arity == want:
            candidates.append((named_params(sig.params), f"{source} ({sig.file}:{sig.line})"))
    candidates.append(
        (", ".join(f"void *{name}" for name in "abcdefghijklmnopqrstuvwxyz"[:want]), "opaque pointers")
    )
    return candidates


def rewrite(text: str, names: list[str], params: str) -> str | None:
    """Replace the parameter list of the definition in `text`."""
    for name in names:
        pattern = re.compile(r"(\b" + re.escape(name) + r"\s*\()([^()]*)(\)\s*\{)", re.S)
        match = pattern.search(text)
        if match:
            return text[: match.start(2)] + params + text[match.end(2) :]
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--apply", action="store_true", help="write the repairs")
    ap.add_argument(
        "--dirs", default="matched,decompiled",
        help="src/ subdirs to gather evidence from; repairs are limited to asm stubs",
    )
    args = ap.parse_args()
    dirs = [d.strip() for d in args.dirs.split(",") if d.strip()]

    report = analyse(dirs)
    aliases = read_aliases()
    reverse: dict[str, list[str]] = {}
    for readable, label in aliases.items():
        reverse.setdefault(label, []).append(readable)

    targets = []
    for row in report.conflicts:
        label = str(row["name"])
        sig = report.definitions.get(label)
        if sig is None:
            continue  # no C definition to repair
        if is_semantic_stub_free((ROOT / sig.file).read_text(errors="replace")):
            continue  # real C body: its signature is a claim, not a placeholder
        candidates = best_params(label, report)
        if candidates:
            targets.append((label, sig, candidates))

    print("=== stub arity repair ===")
    print(f"  conflicting arity          : {len(report.conflicts)}")
    print(f"  repairable asm stubs       : {len(targets)}")

    if not args.apply:
        for label, sig, candidates in targets:
            params, source = candidates[0]
            print(
                f"    {label}  {sig.file}  ({sig.arity} -> {report.expected[label]} arg(s))"
                f"  from {source}"
            )
        print(f"\n  would repair: {len(targets)} file(s)  (re-run with --apply)")
        return 0

    kept, reverted = 0, []
    for label, sig, candidates in targets:
        path = ROOT / sig.file
        original = path.read_text(errors="replace")
        names = [label, *reverse.get(label, [])]
        applied = False
        for params, source in candidates:
            fixed = rewrite(original, names, params)
            if fixed is None or fixed == original:
                continue
            path.write_text(fixed)
            result = subprocess.run(
                ["python3", "tools/decomp/match_function.py", label, str(path.relative_to(ROOT))],
                capture_output=True, text=True, cwd=ROOT, timeout=600,
            )
            if result.stdout.startswith("MATCH"):
                kept += 1
                applied = True
                print(f"    OK     {label}  {path.name}  ({source})")
                break
        if not applied:
            path.write_text(original)
            reverted.append(label)
            print(f"    REVERT {label} — no candidate signature matched")

    print(f"\n  kept    : {kept}")
    print(f"  reverted: {len(reverted)}")
    for label in reverted:
        print(f"    {label}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
