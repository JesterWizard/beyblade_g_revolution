#!/usr/bin/env python3
"""One-screen context packet for a remaining readable-Thumb function.

Scripts try patterns + cleaned m2c first. The agent should only see this
packet — not mission/roadmap dumps or full objdump hex.

  python3 tools/decomp/agent_packet.py --next
  python3 tools/decomp/agent_packet.py sub_08030938
  python3 tools/decomp/agent_packet.py --next --battle
  python3 tools/decomp/agent_packet.py --next --wip
"""

from __future__ import annotations

import argparse
import os
import re
import signal
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MATCHED = ROOT / "src" / "matched"
WIP = ROOT / "src" / "decompiled"
HEADERS = ROOT / "include" / "unknown-functions.h"
sys.path.insert(0, str(ROOT / "tools" / "decomp"))

from classify_semantic_targets import (  # noqa: E402
    CALL_RE,
    asm_body,
    classify,
    declared_symbols,
)
from match_function import (  # noqa: E402
    format_compact_diff,
    format_score,
    try_compile_and_score,
    write_single_function_c,
)
from next_queue import collect  # noqa: E402
from opcode_stubs import list_readable_asm  # noqa: E402
from progress import function_size  # noqa: E402
from try_convert import asm_lines, candidates  # noqa: E402
from unknown_types import fields_of_struct, struct_from_function  # noqa: E402

_OFF = re.compile(r"\[r\d+,\s*#(0x[0-9A-Fa-f]+|\d+)\]")
_RAM = re.compile(r"0x0[23][0-9A-Fa-f]{6,7}")
_MAX_THUMB = 50
_MAX_SEED = 80
# One hand-written attempt per function. A same-size DIFF goes to the local
# permuter (free) — not to another model turn.
_MAX_ATTEMPTS = 1
_AUTO_PERMUTE_SECONDS = 60


def _bucket_of(name: str, buckets: dict[str, list[str]]) -> str:
    for key, names in buckets.items():
        if name in names:
            return key
    return "unknown"


def _blocked_names(data: dict) -> set[str]:
    return {r["name"] for r in data.get("blocked") or [] if r.get("name")}


def _exhausted_names() -> set[str]:
    """WIP entries parked as `retry = false` (documented as unreachable).

    Reading this from the queue instead of the prose in
    `src/decompiled/<name>.md` matters: the notes said "do not re-attempt" for
    `sub_08031300` while its queue block still said "rewrite without register
    asm", because park_wip.py used to skip names it had already seen. The picker
    read the stale half and offered a function the previous session had already
    proved unreachable — the packet then told the agent not to re-attempt the
    thing the packet had just asked for.
    """
    try:
        sys.path.insert(0, str(Path(__file__).resolve().parent))
        from queue_toml import read_blocks
    except ImportError:
        return set()
    return {
        b["name"]
        for b in read_blocks()
        if b.get("name") and str(b.get("retry", "")).lower() == "false"
    }


def _row_for(name: str, data: dict) -> dict:
    for key in ("recommended", "backlog", "wip", "blocked"):
        for row in data.get(key) or []:
            if row.get("name") == name:
                return row
    return {}


def _pick_next(*, battle: bool, resume_wip: bool, force_exhausted: bool = False) -> str | None:
    remaining = set(list_readable_asm())
    buckets, _missing, _cse = classify()
    skip = set(buckets.get("naked_only") or [])
    data = collect()
    blocked = _blocked_names(data)
    wip_names = {p.stem for p in WIP.glob("sub_*.c")}
    if not force_exhausted:
        skip |= _exhausted_names()

    if battle:
        for row in data.get("recommended") or []:
            name = row.get("name")
            if name and _pickable(name, remaining, skip, blocked, wip_names, resume_wip):
                return name

    # Bucket order is the *primary* key: it is the difficulty ranking from
    # classify_semantic_targets.py, and a parked small seed is far cheaper to
    # finish than a fresh 1.5 KB high_reg_pressure function. WIP-ness is only a
    # tiebreak inside a bucket, so a parked small_clean seed beats a fresh
    # high_reg_pressure one. (`leaf_branch` was previously absent here, so those
    # targets were unreachable from --next.)
    order = (
        "unblock_first",
        "small_clean",
        "leaf_branch",
        "large",
        "high_reg_pressure",
    )
    for key in order:
        candidates = [
            n
            for n in buckets.get(key) or []
            if n in remaining and n not in skip and n not in blocked
        ]
        if not candidates:
            continue
        landed = [n for n in candidates if n in wip_names]
        fresh = [n for n in candidates if n not in wip_names]
        if resume_wip:
            if landed:
                return landed[0]
        else:
            if fresh:
                return fresh[0]
            if landed:
                return landed[0]

    leftover = sorted(remaining - skip - blocked)
    landed = [n for n in leftover if n in wip_names]
    fresh = [n for n in leftover if n not in wip_names]
    pool = landed if resume_wip else (fresh or landed)
    return pool[0] if pool else None


def _pickable(
    name: str,
    remaining: set[str],
    skip: set[str],
    blocked: set[str],
    wip_names: set[str],
    resume_wip: bool,
) -> bool:
    if name not in remaining or name in skip or name in blocked:
        return False
    if resume_wip:
        return name in wip_names
    return name not in wip_names


def _thumb_excerpt(name: str) -> str:
    body = asm_body(name)
    lines = []
    for raw in body.splitlines():
        s = raw.strip()
        if not s or s.startswith(("@", ".")):
            continue
        lines.append(s)
    if len(lines) <= _MAX_THUMB:
        return "\n".join(lines)
    hidden = len(lines) - _MAX_THUMB
    return "\n".join(lines[:40] + [f"... ({hidden} lines omitted) ..."] + lines[-10:])


def _offsets(name: str) -> list[int]:
    body = asm_body(name)
    seen: set[int] = set()
    for m in _OFF.finditer(body):
        seen.add(int(m.group(1), 0))
    return sorted(seen)


def _ram_lits(name: str) -> list[str]:
    body = asm_body(name)
    return sorted(set(_RAM.findall(body)))


def _callees(name: str) -> list[str]:
    body = asm_body(name)
    found = CALL_RE.findall(body)
    # preserve order, unique
    out: list[str] = []
    for c in found:
        if c not in out:
            out.append(c)
    return out


def _proto_line(sym: str, header: str) -> str | None:
    m = re.search(rf"^.*\b{re.escape(sym)}\s*\([^;]*\);", header, re.M)
    return m.group(0).strip() if m else None


def _wip_excerpt(name: str) -> str | None:
    c_path = WIP / f"{name}.c"
    if not c_path.is_file():
        return None
    lines = c_path.read_text().splitlines()
    md = WIP / f"{name}.md"
    nxt = ""
    if md.is_file():
        text = md.read_text()
        m = re.search(r"^## Next\n+(.+)", text, re.M | re.S)
        if m:
            nxt = m.group(1).strip().split("\n", 1)[0]
    body = "\n".join(lines[:_MAX_SEED])
    if len(lines) > _MAX_SEED:
        body += f"\n... ({len(lines) - _MAX_SEED} lines omitted)"
    extra = f"\nnext: {nxt}" if nxt else ""
    return f"{c_path.relative_to(ROOT)}{extra}\n{body}"


def _try_candidates(name: str) -> tuple[list[str], str | None, str | None]:
    """Return (status lines, MATCH body or None, best DIFF blob)."""
    asm = asm_lines(name)
    if asm is None:
        return ["no asm"], None, None
    lines: list[str] = []
    best_diff: str | None = None
    best_pct = -1.0
    match_body: str | None = None
    for src, note, body in candidates(name, asm):
        with tempfile.TemporaryDirectory() as tmp:
            scratch = Path(tmp) / "scratch.c"
            write_single_function_c(name, body, scratch)
            scored = try_compile_and_score(name, scratch)
            if scored is None:
                lines.append(f"[FAIL] {src}: compile error")
                continue
            got, want, info = scored
        if got == want:
            lines.append(f"[MATCH] {src}: {note}")
            match_body = body
            break
        lines.append(f"[FAIL ] {src}: {format_score(info)}")
        if info["pct"] > best_pct:
            best_pct = info["pct"]
            best_diff = format_compact_diff(got, want, info)
    return lines, match_body, best_diff


def _auto_permute(name: str, seconds: int) -> tuple[bool, str | None]:
    """Run the bounded local permuter. Returns (matched, note).

    A same-size DIFF is the permuter's job: it searches locally for free, so the
    agent only has to wake up for functions it cannot solve.
    """
    if seconds <= 0:
        return False, None
    script = ROOT / "tools/decomp/permuter/auto.py"
    if not script.is_file():
        return False, None
    proc = subprocess.Popen(
        [sys.executable, str(script), name, "--seconds", str(seconds)],
        cwd=str(ROOT),
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        start_new_session=True,
    )
    try:
        text, _ = proc.communicate(timeout=seconds + 120)
    except subprocess.TimeoutExpired:
        try:
            os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
        except (ProcessLookupError, PermissionError, OSError):
            proc.kill()
        text, _ = proc.communicate()
        return False, "permuter timed out"
    text = text or ""
    if proc.returncode == 0:
        return True, "permuter/auto.py — already verified and integrated"
    best = None
    for m in re.finditer(r"no score 0 within budget, best (\d+)", text):
        best = m.group(1)
    if best is None and "failed match_function" in text:
        return False, "permuter found 0 but the candidate failed verification"
    return False, f"permuter best {best}" if best else "permuter no score 0"


def build_packet(name: str, permute_seconds: int = _AUTO_PERMUTE_SECONDS) -> str:
    buckets, missing_by_symbol, cse_risk = classify()
    bucket = _bucket_of(name, buckets)
    try:
        size = function_size(name, MATCHED / f"{name}.c")
    except FileNotFoundError:
        size = 0
    data = collect()
    row = _row_for(name, data)
    battle = row.get("battle_refs") or 0
    st = struct_from_function(name)
    fields = fields_of_struct(st)
    header = HEADERS.read_text() if HEADERS.is_file() else ""
    declared = declared_symbols()

    out: list[str] = [
        f"=== PACKET {name} ===",
        f"bucket: {bucket}   bytes: {size}   battle_refs: {battle}",
        f"struct: {st}   cse_risk: {'yes' if name in cse_risk else 'no'}",
        f"wip: {'yes — resume, do not re-derive' if (WIP / f'{name}.c').is_file() else 'no'}",
        "",
    ]

    if bucket == "naked_only":
        out.append("STOP: naked_only — leave as readable Thumb.")
        return "\n".join(out) + "\n"

    wip = _wip_excerpt(name)
    auto: list[str] = []
    match_body: str | None = None
    best_diff: str | None = None
    permuted = False
    if wip:
        auto = ["(skipped — WIP seed exists; resume that, do not re-run m2c)"]
    else:
        auto, match_body, best_diff = _try_candidates(name)
    # Near-miss or parked seed: let the local permuter try before the agent does.
    # It costs no tokens, so this is the cheapest possible fork.
    if match_body is None and (wip or best_diff) and permute_seconds > 0:
        permuted, note = _auto_permute(name, permute_seconds)
        if note:
            auto.append(f"[PERM ] {note}")
    out.append("## Auto try (do not redo these)")
    out.extend(auto if auto else ["(no candidates)"])
    out.append("")

    if permuted:
        out.append("## MATCH — permuter already verified and integrated")
        out.append("Nothing to write. Run make compare once, then take the next function.")
        out.append("")
        return "\n".join(out) + "\n"

    if match_body:
        out.append("## MATCH — integrate, do not rewrite")
        out.append(f"python3 tools/decomp/try_convert.py {name} --integrate --note packet-auto")
        out.append("")
        out.append(match_body.rstrip())
        out.append("")
        out.append("Then: make compare")
        return "\n".join(out) + "\n"

    out.append("## Agent job")
    out.append(
        f"Write semantic C from the seed below. Max {_MAX_ATTEMPTS} "
        "match_function.py attempt, then park_wip.py."
    )
    out.append(f"python3 tools/decomp/match_function.py {name} scratch.c")
    out.append(
        f"python3 tools/decomp/integrate_c.py {name} @scratch.c "
        "--kind semantic --note <role>"
    )
    out.append(
        f"python3 tools/decomp/park_wip.py {name} scratch.c "
        '--status "…" --next "…" --score "N/M"'
    )
    out.append("")
    out.append(
        "If the result is a same-size DIFF, do NOT hand-edit to chase registers — "
        "run the local permuter and park if it fails:"
    )
    out.append(f"python3 tools/decomp/permuter/auto.py {name} --seconds 240")
    out.append("")

    if best_diff:
        out.append("## Best auto DIFF")
        out.append(best_diff.rstrip())
        out.append("")

    if wip:
        out.append("## WIP seed (resume here)")
        out.append(wip)
        out.append("")
        out.append("Do not re-read decomp-mission.md / roadmap. Park on DIFF, do not retry-loop.")
        return "\n".join(out) + "\n"

    out.append("## Thumb (stripped)")
    out.append(_thumb_excerpt(name))
    out.append("")

    out.append("## Offsets → " + st + "  (ldr/str [reg,#imm]; may be relative to a computed base)")
    offs = _offsets(name)
    if not offs:
        out.append("(none)")
    else:
        for off in offs:
            hit = fields.get(off)
            if hit:
                out.append(f"  +{off:#x}  {hit}")
            else:
                from unknown_types import unk_name  # noqa: WPS433

                out.append(f"  +{off:#x}  MISSING — add {unk_name(off)} (split filler)")
    ram = _ram_lits(name)
    if ram:
        out.append("RAM literals: " + ", ".join(ram))
    out.append("")

    out.append("## Callees")
    calls = _callees(name)
    if not calls:
        out.append("(none)")
    else:
        for sym in calls:
            proto = _proto_line(sym, header)
            if proto:
                out.append(f"  {proto}")
            elif sym in declared:
                out.append(f"  {sym}()  (declared)")
            else:
                out.append(f"  {sym}  UNDECLARED — unblock_symbols.py")
    missing_for = [sym for sym, callers in missing_by_symbol.items() if name in callers]
    if missing_for:
        out.append("blocked on: " + ", ".join(missing_for))
    out.append("")

    out.append("## Cleaned m2c seed")
    from m2c_cleanup import cleanup_function  # noqa: WPS433

    seed = cleanup_function(name)
    if not seed:
        seed = cleanup_function(name, valid_syntax=True)
    if seed:
        slines = seed.splitlines()
        if len(slines) > _MAX_SEED:
            seed = "\n".join(slines[:_MAX_SEED]) + f"\n... ({len(slines) - _MAX_SEED} lines omitted)"
        out.append(seed.rstrip())
    else:
        out.append("(m2c failed)")
    out.append("")
    out.append("Do not re-read decomp-mission.md / roadmap. Park on DIFF, do not retry-loop.")
    return "\n".join(out) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function", nargs="?", help="sub_080XXXXXX")
    parser.add_argument("--next", action="store_true", help="pick cheapest remaining target")
    parser.add_argument("--battle", action="store_true", help="prefer next_queue battle ranking")
    parser.add_argument("--wip", action="store_true", help="prefer parked src/decompiled/ seeds")
    parser.add_argument(
        "--force-exhausted",
        action="store_true",
        help="also pick functions parked with retry = false (documented as unreachable)",
    )
    parser.add_argument("--write", metavar="PATH", help="also write the packet to a file")
    parser.add_argument(
        "--permute-seconds",
        type=int,
        default=_AUTO_PERMUTE_SECONDS,
        help=(
            "local permuter budget for near-miss/WIP seeds before the agent is "
            "asked to write C (0 disables; default %(default)s)"
        ),
    )
    args = parser.parse_args()

    name = args.function
    if args.next or not name:
        name = _pick_next(
            battle=args.battle, resume_wip=args.wip, force_exhausted=args.force_exhausted
        )
        if not name:
            print("no remaining readable-Thumb targets")
            return 0
    if not name.startswith("sub_"):
        print("function must be sub_XXXXXXXX", file=sys.stderr)
        return 2

    packet = build_packet(name, permute_seconds=args.permute_seconds)
    print(packet, end="")
    if args.write:
        path = Path(args.write)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(packet)
        print(f"\nwrote {path}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
