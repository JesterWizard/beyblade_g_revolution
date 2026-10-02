#!/usr/bin/env python3
"""Rename struct tags and struct members across include/ and src/.

Struct and member names never reach the ROM: they only decide how the C reads.
That makes renaming them safe *if* every use is found. A tag is a unique global
identifier, so a whole-word replace is enough. A member name is not: `unk14`
exists in dozens of structs, so a text replace would rename the wrong fields.
Member renames are therefore driven by the compiler:

  1. rename the member in the struct definition;
  2. compile every C file that mentions `->old` / `.old`;
  3. agbcc reports `structure has no member named `old'` at exactly the
     accesses that belong to this struct; rename `old` on those lines only;
  4. when a line also touches `.old` of another struct (the rename then trips
     `no member named `new'`), resolve that line one occurrence at a time;
  5. repeat until no file reports either name.

Files that do not compile for unrelated reasons (broken drafts) are reported
and left alone. Always re-verify the bytes afterwards
(`matched_rescore.py --kind semantic`): a correct rename changes nothing.

    python3 tools/decomp/rename_struct.py tag Unk6EE48 CameraState
    python3 tools/decomp/rename_struct.py field CameraState unk224 target
    python3 tools/decomp/rename_struct.py batch renames.txt

A batch file holds one `tag OLD NEW` or `field STRUCT OLD NEW` per line
(`#` comments allowed).
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import re
import subprocess
import sys
from pathlib import Path

import groups

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "include"
SRC_DIRS = [ROOT / "src" / "matched", ROOT / "src" / "decompiled"]
AGBCC = ROOT / "tools" / "agbcc" / "bin" / "agbcc"
CPPFLAGS = ["-Iinclude", "-Itools/agbcc/include", "-Itools/agbcc"]
CFLAGS = ["-mthumb-interwork", "-Wimplicit", "-Wparentheses", "-Werror", "-O2", "-g", "-fhex-asm"]
GENERATED = {INCLUDE / "symbols.h"}

_FLAGS = re.compile(r"/\*\s*match-flags:\s*([^*]*)\*/")
_COMPILER = re.compile(r"/\*\s*match-compiler:\s*([A-Za-z0-9_]+)\s*\*/")
_IDENT = re.compile(r"^[A-Za-z_]\w*$")


def c_files() -> list[Path]:
    files: list[Path] = []
    for d in SRC_DIRS:
        files += sorted(p for p in d.rglob("*.c") if ".audit" not in p.name)
    return files + groups.group_files()  # shared src/<group>.c files


def header_files() -> list[Path]:
    return sorted(p for p in INCLUDE.rglob("*.h") if p not in GENERATED)


# --- compiling ----------------------------------------------------------------


def compile_errors(path: Path) -> list[tuple[str, int, str]]:
    """(file, line, message) for every agbcc diagnostic of one C file."""
    text = path.read_text(errors="replace")
    extra: list[str] = []
    m = _FLAGS.search(text)
    if m:
        extra += m.group(1).split()
    binary = AGBCC
    mc = _COMPILER.search(text)
    if mc and mc.group(1) == "old_agbcc":
        binary = AGBCC.parent / "old_agbcc"
    i_path = path.with_suffix(".rename.i")
    s_path = path.with_suffix(".rename.s")
    try:
        pp = subprocess.run(["arm-none-eabi-gcc", "-E", *CPPFLAGS, str(path), "-o", str(i_path)],
                            capture_output=True, text=True, cwd=ROOT)
        if pp.returncode != 0:
            return [(str(path), 0, "preprocess: " + pp.stderr.strip()[-200:])]
        cc = subprocess.run([str(binary), str(i_path), "-o", str(s_path), *CFLAGS, *extra],
                            capture_output=True, text=True, cwd=ROOT)
        out: list[tuple[str, int, str]] = []
        for line in cc.stderr.splitlines():
            mm = re.match(r"^(.*?):(\d+): (.*)$", line)
            if mm:
                out.append((mm.group(1), int(mm.group(2)), mm.group(3)))
        if cc.returncode != 0 and not out:
            out.append((str(path), 0, cc.stderr.strip()[-200:] or "failed"))
        return out
    finally:
        i_path.unlink(missing_ok=True)
        s_path.unlink(missing_ok=True)


def compile_many(paths: list[Path]) -> dict[Path, list[tuple[str, int, str]]]:
    with cf.ThreadPoolExecutor(max_workers=8) as ex:
        return dict(zip(paths, ex.map(compile_errors, paths)))


# --- literal-aware scanning -------------------------------------------------------


def code_spans(text: str) -> list[tuple[int, int]]:
    """Spans of `text` that are code (not comments, strings or chars)."""
    spans: list[tuple[int, int]] = []
    i, n, start = 0, len(text), 0
    while i < n:
        two = text[i:i + 2]
        if two in ("//", "/*") or text[i] in "\"'":
            spans.append((start, i))
            if two == "//":
                j = text.find("\n", i)
                i = n if j == -1 else j
            elif two == "/*":
                j = text.find("*/", i + 2)
                i = n if j == -1 else j + 2
            else:
                q, j = text[i], i + 1
                while j < n and text[j] != q:
                    j += 2 if text[j] == "\\" else 1
                i = j + 1
            start = i
            continue
        i += 1
    spans.append((start, n))
    return spans


def member_hits(line: str, name: str) -> list[tuple[int, int]]:
    """Positions of `name` used as a member (`.name` / `->name`) in code."""
    hits = []
    for a, b in code_spans(line):
        for m in re.finditer(r"(?:\.|->)\s*(" + re.escape(name) + r")\b", line[a:b]):
            hits.append((a + m.start(1), a + m.end(1)))
    return hits


def replace_at(line: str, spans: list[tuple[int, int]], new: str) -> str:
    for a, b in sorted(spans, reverse=True):
        line = line[:a] + new + line[b:]
    return line


# --- struct definitions ----------------------------------------------------------


def find_struct(tag: str) -> tuple[Path, int, int] | None:
    """(file, start, end) character span of `struct tag { ... };`."""
    pat = re.compile(r"^\s*struct\s+" + re.escape(tag) + r"\b[^;{]*\{", re.M)
    for path in header_files() + c_files():
        text = path.read_text(errors="replace")
        m = pat.search(text)
        if not m:
            continue
        depth, i = 0, m.end() - 1
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    return path, m.start(), i
            i += 1
    return None


def rename_member_decl(tag: str, old: str, new: str) -> Path:
    found = find_struct(tag)
    if not found:
        raise SystemExit(f"struct {tag} not found")
    path, a, b = found
    text = path.read_text()
    body = text[a:b]
    # the declarator: `old;`, `old[..];` or `old:bits;` at statement level
    pat = re.compile(r"(?<![\w.>])" + re.escape(old) + r"(?=\s*(?:\[[^\]]*\]\s*)*(?::\s*\d+\s*)?[;,])")
    spans = [s for s in code_spans(body)]
    hits = [m for s0, s1 in spans for m in pat.finditer(body, s0, s1)]
    if len(hits) != 1:
        raise SystemExit(f"struct {tag}: expected one member `{old}`, found {len(hits)}")
    m = hits[0]
    code = "".join(body[s0:s1] for s0, s1 in spans)
    if re.search(r"(?<![\w.>])" + re.escape(new) + r"(?=\s*(?:\[[^\]]*\]\s*)*(?::\s*\d+\s*)?[;,])", code):
        raise SystemExit(f"struct {tag} already has a member `{new}`")
    body = body[:m.start()] + new + body[m.end():]
    path.write_text(text[:a] + body + text[b:])
    return path


# --- commands --------------------------------------------------------------------


def rename_tag(old: str, new: str) -> int:
    if not (_IDENT.match(old) and _IDENT.match(new)):
        raise SystemExit("tags must be identifiers")
    word = re.compile(r"\b" + re.escape(old) + r"\b")
    clash = re.compile(r"\b(?:struct|union)\s+" + re.escape(new) + r"\b")
    changed = 0
    for path in header_files() + c_files():
        text = path.read_text(errors="replace")
        if clash.search(text):
            raise SystemExit(f"{new} already exists ({path.relative_to(ROOT)})")
    for path in header_files() + c_files():
        text = path.read_text(errors="replace")
        new_text, n = word.subn(new, text)
        if n:
            path.write_text(new_text)
            changed += 1
    print(f"tag {old} -> {new}: {changed} file(s)")
    return 0


def rename_field(tag: str, old: str, new: str) -> int:
    if not (_IDENT.match(old) and _IDENT.match(new)):
        raise SystemExit("members must be identifiers")
    decl = rename_member_decl(tag, old, new)
    needle = re.compile(r"(?:\.|->)\s*" + re.escape(old) + r"\b")
    candidates = [p for p in c_files() if needle.search(p.read_text(errors="replace"))]
    # headers can hold inline users too (macros); they are handled via the C files
    no_old = re.compile(r"no member named `" + re.escape(old) + r"'")
    no_new = re.compile(r"no member named `" + re.escape(new) + r"'")
    edited_lines: dict[tuple[Path, int], str] = {}
    broken: dict[Path, str] = {}
    pending = candidates
    rounds = 0
    total = 0
    while pending and rounds < 20:
        rounds += 1
        results = compile_many(pending)
        next_round: set[Path] = set()
        for cfile, errs in results.items():
            hits = {}
            bad_new = set()
            other = None
            for f, ln, msg in errs:
                fp = (ROOT / f).resolve() if not Path(f).is_absolute() else Path(f)
                if no_old.search(msg):
                    hits.setdefault(fp, set()).add(ln)
                elif no_new.search(msg):
                    bad_new.add((fp, ln))
                elif other is None:
                    other = f"{f}:{ln}: {msg}"
            if not hits and not bad_new:
                if other:
                    broken[cfile] = other
                continue
            progress = False
            macro_files = set()
            for fp, lines in hits.items():
                src = fp.read_text().split("\n")
                for ln in sorted(lines):
                    spans = member_hits(src[ln - 1], old)
                    if len(spans) > 1:
                        fp.write_text("\n".join(src))
                        resolve_line(fp, ln, old, new, cfile, no_old, no_new)
                        src = fp.read_text().split("\n")
                        total += 1
                        progress = True
                    elif spans:
                        src[ln - 1] = replace_at(src[ln - 1], spans, new)
                        edited_lines[(fp, ln)] = "all"
                        total += len(spans)
                        progress = True
                    else:
                        macro_files.add(fp)
                fp.write_text("\n".join(src))
            for fp, ln in bad_new:
                resolve_line(fp, ln, old, new, cfile, no_old, no_new)
                progress = True
            for fp in macro_files:
                n = resolve_macros(fp, old, new, cfile, no_old, no_new)
                total += n
                progress = progress or n > 0
            if progress:
                next_round.add(cfile)
            else:
                broken[cfile] = f"could not place {len(hits)} access(es) (macro or unusual syntax)"
        pending = sorted(next_round)
    print(f"field {tag}.{old} -> {new}: decl in {decl.relative_to(ROOT)}, "
          f"{total} access(es) renamed in {rounds} round(s)")
    for f, why in sorted(broken.items()):
        if needle.search(f.read_text(errors="replace")):
            print(f"  skipped (does not compile): {f.relative_to(ROOT)}: {why}")
    return 0


def resolve_line(fp: Path, ln: int, old: str, new: str, cfile: Path, no_old, no_new) -> None:
    """A line mixes this struct's `old` with other structs' members of the same
    name (e.g. `st->unk08->unk08`). Try every subset of the occurrences and keep
    the one that leaves no `old`/`new` member error on the line."""
    from itertools import combinations

    src = fp.read_text().split("\n")
    line = src[ln - 1]
    # put every new-name member access on this line back to the old name,
    # except those that were already `new` before we touched the file
    base = replace_at(line, member_hits(line, new), old)
    spans = member_hits(base, old)
    best = None
    for k in range(len(spans), -1, -1):
        for subset in combinations(spans, k):
            src[ln - 1] = replace_at(base, list(subset), new)
            fp.write_text("\n".join(src))
            errs = compile_errors(cfile)
            if not any(l == ln and (no_old.search(m) or no_new.search(m)) for _, l, m in errs):
                best = list(subset)
                break
        if best is not None:
            break
    src[ln - 1] = replace_at(base, best or [], new)
    fp.write_text("\n".join(src))


def macro_lines(src: list[str]) -> list[int]:
    """1-based numbers of the lines that belong to a #define body."""
    out, inside = [], False
    for i, line in enumerate(src, 1):
        if inside or line.lstrip().startswith("#define"):
            out.append(i)
            inside = line.rstrip().endswith("\\")
        else:
            inside = False
    return out


def count_errors(cfile: Path, pat) -> int:
    return sum(1 for _, _, m in compile_errors(cfile) if pat.search(m))


def resolve_macros(fp: Path, old: str, new: str, cfile: Path, no_old, no_new) -> int:
    """Errors reported at a macro call: try each `->old` in the file's macro bodies."""
    renamed = 0
    for ln in macro_lines(fp.read_text().split("\n")):
        while True:
            src = fp.read_text().split("\n")
            spans = member_hits(src[ln - 1], old)
            done = False
            for span in spans:
                before_old = count_errors(cfile, no_old)
                before_new = count_errors(cfile, no_new)
                trial = list(src)
                trial[ln - 1] = replace_at(src[ln - 1], [span], new)
                fp.write_text("\n".join(trial))
                if count_errors(cfile, no_old) < before_old and count_errors(cfile, no_new) <= before_new:
                    renamed += 1
                    done = True
                    break
                fp.write_text("\n".join(src))
            if not done:
                break
    return renamed


def run_batch(path: Path) -> int:
    for raw in path.read_text().splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split()
        if parts[0] == "tag" and len(parts) == 3:
            rename_tag(parts[1], parts[2])
        elif parts[0] == "field" and len(parts) == 4:
            rename_field(parts[1], parts[2], parts[3])
        else:
            raise SystemExit(f"bad batch line: {raw}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    t = sub.add_parser("tag")
    t.add_argument("old")
    t.add_argument("new")
    f = sub.add_parser("field")
    f.add_argument("struct")
    f.add_argument("old")
    f.add_argument("new")
    b = sub.add_parser("batch")
    b.add_argument("file", type=Path)
    args = ap.parse_args()
    if args.cmd == "tag":
        return rename_tag(args.old, args.new)
    if args.cmd == "field":
        return rename_field(args.struct, args.old, args.new)
    return run_batch(args.file)


if __name__ == "__main__":
    sys.exit(main())
