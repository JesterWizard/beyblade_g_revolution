#!/usr/bin/env python3
"""Repair matched C whose definition signature disagrees with its prototype.

`src/matched/*.c` is never linked (the Makefile's C_SRCS is empty), so a file can
be recorded as byte-matching, and stay that way, while not compiling from source
at all. agbcc then reports "conflicting types".

The defect is a definition whose return type and/or parameter list disagrees with
the prototype in `include/unknown-functions.h`. The repair copies the prototype's
signature into the definition.

Deliberately narrow: this only rewrites a definition that is anchored either by a
`__attribute__((naked))` line or by being the file's own top-level definition of
its own stem. Anything else is left alone and reported, because a loose regex
over `src/matched/*.c` matches call sites and forward declarations too.

Because a signature change *can* change code generation for an ordinary
function, `--apply` re-runs match_function.py on every touched file and reverts
any whose match regresses.

Usage:
    python3 tools/decomp/repair_naked_signatures.py --check
    python3 tools/decomp/repair_naked_signatures.py --apply
"""

import argparse
import concurrent.futures as cf
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"
HEADER = ROOT / "include" / "unknown-functions.h"

_DEFINE = re.compile(r"^\s*#define\s+(\w+)\s+sub_([0-9A-Fa-f]{8})\s*$", re.M)
_RET = r"(?:void|u8|u16|u32|s8|s16|s32|_Bool|int|struct\s+\w+|union\s+\w+|\w+)"

# A prototype in the header; the parameter list may wrap onto several lines.
_PROTO = re.compile(
    rf"(?P<ret>{_RET}\s*\**)\s*(?P<name>sub_[0-9A-Fa-f]{{8}})\s*"
    r"\((?P<params>[^;{}]*?)\)\s*;",
    re.S,
)

# A definition anchored by the naked attribute line.
_NAKED_DEF = re.compile(
    rf"__attribute__\s*\(\(\s*naked\s*\)\)\s*\n"
    rf"(?P<indent>[ \t]*)(?P<ret>{_RET}\s*\**)\s*(?P<name>sub_[0-9A-Fa-f]{{8}}|[A-Za-z_]\w*)\s*"
    r"\((?P<params>[^;{}()]*?)\)\s*\n",
)

# A plain top-level definition of the file's own stem.
_PLAIN_DEF = re.compile(
    rf"^(?P<ret>{_RET}\s*\**)\s*(?P<name>sub_[0-9A-Fa-f]{{8}}|[A-Za-z_]\w*)\s*"
    r"\((?P<params>[^;{}()]*?)\)\s*\n",
    re.M,
)


def protos() -> dict[str, tuple[str, str]]:
    """sub_XXXXXXXX -> (return type, parameter list), from unknown-functions.h."""
    out: dict[str, tuple[str, str]] = {}
    text = "\n".join(
        ln for ln in HEADER.read_text(errors="replace").splitlines()
        if not ln.lstrip().startswith("#")
    )
    for m in _PROTO.finditer(text):
        out[m.group("name")] = (
            " ".join(m.group("ret").split()),
            " ".join(m.group("params").split()),
        )
    return out


def aliases() -> dict[str, str]:
    """readable name -> sub_XXXXXXXX, from the generated symbols.h."""
    path = ROOT / "include" / "symbols.h"
    if not path.is_file():
        return {}
    return {a: l for a, l in _DEFINE.findall(path.read_text(errors="replace"))}


def repair(text: str, stem: str, table: dict[str, tuple[str, str]],
           alias: dict[str, str]) -> tuple[str, str]:
    """Return (new text, reason). Reason is "" when nothing needs changing."""
    want = table.get(stem)
    if not want:
        return text, ""
    want_ret, want_params = want

    def check(m: re.Match, anchored: bool) -> tuple[str, str] | None:
        name = m.group("name")
        if alias.get(name, name) != stem:
            return None
        got_ret = " ".join(m.group("ret").split())
        got_params = " ".join(m.group("params").split())
        if got_ret == want_ret and got_params == want_params:
            return None
        why = []
        if got_ret != want_ret:
            why.append(f"return {got_ret!r}->{want_ret!r}")
        if got_params != want_params:
            why.append(f"params ({got_params})->({want_params})")
        indent = m.group("indent") if anchored else ""
        repl = f"{indent}{want_ret} {name}({want_params})\n"
        start = m.start("ret") if anchored else m.start()
        end = m.end("params") + 1
        if anchored:
            end = text.index("\n", m.end("params")) + 1
        return text[:start] + repl + text[end:], "; ".join(why)

    for m in _NAKED_DEF.finditer(text):
        got = check(m, True)
        if got:
            return got
    for m in _PLAIN_DEF.finditer(text):
        got = check(m, False)
        if got:
            return got
    return text, ""


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--apply", action="store_true", help="write the repairs")
    ap.add_argument("--check", action="store_true", help="report only (default)")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument(
        "--dirs",
        default="matched",
        help=(
            "comma-separated src/ subdirs. `matched` repairs are verified against "
            "retail bytes and reverted on regression; `decompiled` drafts only have "
            "to compile, since they are not expected to match yet"
        ),
    )
    args = ap.parse_args()
    dirs = [d.strip() for d in args.dirs.split(",") if d.strip()]

    table = protos()
    if not table:
        print("no prototypes found in unknown-functions.h", file=sys.stderr)
        return 2
    alias = aliases()

    sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
    from audit_c_compiles import compile_one  # noqa: WPS433

    candidates = [
        path
        for d in dirs
        for path in sorted((ROOT / "src" / d).glob("sub_*.c"))
    ]
    failing: dict[str, str] = {}
    with cf.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for name, err in pool.map(compile_one, candidates):
            if err:
                failing[name] = err

    changes: list[tuple[pathlib.Path, str, str, str]] = []
    untouched: list[str] = []
    for path in candidates:
        if path.stem not in failing:
            # Compiles cleanly: a signature that only differs in parameter
            # *names* is not a defect worth rewriting verified source for.
            probe, why = repair(path.read_text(errors="replace"), path.stem, table, alias)
            if why:
                untouched.append(path.stem)
            continue
        original = path.read_text(errors="replace")
        fixed, why = repair(original, path.stem, table, alias)
        if fixed == original:
            continue
        changes.append((path, original, fixed, why))
        if not args.apply:
            print(f"    {path.stem}  {why}")

    print("=== signature repair ===")
    print(f"  dirs               : {', '.join(dirs)}")
    print(f"  failing to compile : {len(failing)}")
    print(f"  repairable         : {len(changes)}")
    print(f"  {'repaired' if args.apply else 'would repair'}: {len(changes)} file(s)")
    if untouched:
        print(f"  skipped (cosmetic): {len(untouched)} file(s) differ only in parameter names")

    unresolved = sorted(set(failing) - {p.stem for p, *_ in changes})
    if unresolved:
        print()
        print("  NOT auto-repairable — fix by hand:")
        for name in unresolved:
            print(f"    {name}  {failing[name][:120]}")

    if not args.apply:
        return 0

    reverted: list[str] = []
    for path, original, fixed, _why in changes:
        path.write_text(fixed)
        rel = str(path.relative_to(ROOT))
        if path.parent.name == "matched":
            # Matched source is verified code: a signature fix must not perturb
            # the bytes, so re-check and roll back if it does.
            r = subprocess.run(
                ["python3", "tools/decomp/match_function.py", path.stem, rel],
                capture_output=True, text=True, cwd=ROOT, timeout=600,
            )
            if r.stdout.startswith("MATCH"):
                print(f"    OK     {path.stem}")
                continue
            path.write_text(original)
            reverted.append(path.stem)
            print(f"    REVERT {path.stem} — match regressed")
            continue

        # Drafts are not expected to match; compiling is the bar.
        _name, err = compile_one(path)
        if err:
            path.write_text(original)
            reverted.append(path.stem)
            print(f"    REVERT {path.stem} — still does not compile")
        else:
            print(f"    OK     {path.stem}")

    print(f"\n  kept    : {len(changes) - len(reverted)}")
    print(f"  reverted: {len(reverted)}")
    for name in reverted:
        print(f"    {name} (needs hand fixing)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
