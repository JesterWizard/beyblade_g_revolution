#!/usr/bin/env python3
"""Bounded permuter run for one function; land score 0 automatically.

This is the cheap fork for a same-size DIFF. The permuter grinds locally for
free, so the agent does not have to hand-edit C through repeated model turns
(the previous habit: ~1000 scratch.c edits per session).

Pipeline per invocation:

  1. import (fresh)                    -> nonmatchings/<fn>/{base.c,target.s,matchflags}
  2. score the base seed               -> permuter.py --debug  (fast, one compile)
     - base score 0 => the seed already matches; skip the search entirely
  3. otherwise permute bounded         -> permuter.py -j N --stop-on-zero
  4. on score 0: verify + integrate    -> match_function.py, then integrate_c.py

  python3 tools/decomp/permuter/auto.py sub_0806FEFC
  python3 tools/decomp/permuter/auto.py sub_0806FEFC --seconds 300 --jobs 8
  python3 tools/decomp/permuter/auto.py sub_0806FEFC --no-integrate

Exit codes: 0 = matched, 1 = no score 0 within budget, 2 = setup error.
"""

from __future__ import annotations

import argparse
import os
import re
import signal
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PERM = ROOT / "tools" / "decomp-permuter"
WORKROOT = ROOT / "nonmatchings"
IMPORT = ROOT / "tools" / "decomp" / "permuter" / "import_function.py"
MATCH_SCRIPT = ROOT / "tools" / "decomp" / "match_function.py"
INTEGRATE = ROOT / "tools" / "decomp" / "integrate_c.py"

_BASE_SCORE_RE = re.compile(r"base score = (\d+)")
_OUT_DIR_RE = re.compile(r"^output-(\d+)-\d+$")


def workdir_for(name: str) -> Path:
    return WORKROOT / name


def clean_output_dirs(workdir: Path) -> int:
    """Remove stale permuter output-* dirs so scores reflect this run only."""
    removed = 0
    if not workdir.is_dir():
        return removed
    for child in workdir.iterdir():
        if _OUT_DIR_RE.match(child.name) and child.is_dir():
            import shutil

            shutil.rmtree(child, ignore_errors=True)
            removed += 1
    if removed:
        print(f"cleared {removed} stale output dir(s) in {workdir.relative_to(ROOT)}")
    return removed


def byte_match_summary(name: str) -> str | None:
    """Best-effort byte-match line from the decompiled seed."""
    seed = ROOT / "src" / "decompiled" / f"{name}.c"
    if not seed.is_file():
        return None
    result = subprocess.run(
        [sys.executable, str(MATCH_SCRIPT), name, str(seed)],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
    )
    for line in reversed((result.stdout or "").splitlines()):
        line = line.strip()
        if line and ("bytes matched" in line or "MATCH" in line):
            return line
    return None


def ensure_import(name: str, *, force: bool) -> int:
    workdir = workdir_for(name)
    if force and workdir.is_dir():
        clean_output_dirs(workdir)
    if workdir.is_dir() and not force:
        return 0
    result = subprocess.run(
        [sys.executable, str(IMPORT), name],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
    )
    for line in (result.stdout or "").splitlines():
        if line.startswith(
            ("imported ", "match-flags:", "match-compiler:", "removed stale")
        ):
            print(line)
    if result.returncode != 0:
        sys.stderr.write(result.stdout or "")
        sys.stderr.write(result.stderr or "")
        return result.returncode
    return 0


def base_score(workdir: Path) -> int | None:
    """Compile + score the imported seed once. None if it does not compile."""
    result = subprocess.run(
        [sys.executable, str(PERM / "permuter.py"), str(workdir), "--debug"],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
        timeout=600,
    )
    # `--debug` writes these into the cwd (the repo root); clean them up.
    for leftover in ("debug_source.c", "debug_compiled_object.o"):
        (ROOT / leftover).unlink(missing_ok=True)
    for match in _BASE_SCORE_RE.finditer(result.stdout or ""):
        return int(match.group(1))
    return None


def output_dirs(workdir: Path) -> list[tuple[int, Path]]:
    rows: list[tuple[int, Path]] = []
    if not workdir.is_dir():
        return rows
    for child in workdir.iterdir():
        m = _OUT_DIR_RE.match(child.name)
        if m and child.is_dir():
            rows.append((int(m.group(1)), child))
    return sorted(rows)


def _kill_group(proc: subprocess.Popen) -> None:
    """Kill a permuter run and its worker pool.

    decomp-permuter forks worker processes that inherit our stdout pipe. Killing
    only the parent leaves them alive, which both burns CPU forever and blocks
    the caller's pipe read, so signal the whole process group.
    """
    try:
        os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
    except (ProcessLookupError, PermissionError, OSError):
        proc.kill()
    try:
        proc.wait(timeout=15)
    except subprocess.TimeoutExpired:
        pass


def _ancestors(start: int | None = None) -> set[int]:
    """Pids from `start` (default: us) up to pid 1."""
    chain: set[int] = set()
    pid = start if start is not None else os.getpid()
    for _ in range(64):
        if pid <= 1:
            break
        chain.add(pid)
        try:
            with open(f"/proc/{pid}/stat", "rb") as fh:
                pid = int(fh.read().rsplit(b")", 1)[1].split()[1])
        except (OSError, IndexError, ValueError):
            break
    return chain


def reap_stale_permuters() -> int:
    """Kill permuter processes from an earlier, already-dead batch.

    A batch killed by the caller's timeout cannot run its own cleanup: we spawn
    permuter.py with `start_new_session=True` (so `_kill_group` can reach the
    worker pool), which also detaches it from the signal the caller got. The
    survivors keep every core busy, and because they hold the inherited stdout
    pipe the next piped invocation hangs on read instead of finishing.

    Only processes that are unmistakably ours are touched: a permuter.py under
    this repo whose parent is not in our ancestor chain. Returns how many were
    killed.
    """
    marker = str(PERM / "permuter.py")
    mine = _ancestors()
    killed = 0
    for entry in os.listdir("/proc"):
        if not entry.isdigit():
            continue
        pid = int(entry)
        try:
            with open(f"/proc/{pid}/cmdline", "rb") as fh:
                argv = fh.read().split(b"\0")
            with open(f"/proc/{pid}/stat", "rb") as fh:
                ppid = int(fh.read().rsplit(b")", 1)[1].split()[1])
        except (OSError, IndexError, ValueError):
            continue
        if marker not in (arg.decode(errors="ignore") for arg in argv if arg):
            continue
        if ppid in mine:
            continue
        try:
            os.killpg(os.getpgid(pid), signal.SIGKILL)
        except (ProcessLookupError, PermissionError, OSError):
            try:
                os.kill(pid, signal.SIGKILL)
            except OSError:
                continue
        killed += 1
    if killed:
        print(f"reaped {killed} stale permuter process(es) from an earlier batch")
    return killed


def kill_permuter_tree(workdir: Path, proc: subprocess.Popen | None = None) -> None:
    """Stop a permuter and any worker processes for this workdir."""
    if proc is not None and proc.poll() is None:
        try:
            os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
        except (ProcessLookupError, PermissionError, OSError):
            proc.kill()
    marker = f"permuter.py.*{workdir.name}"
    subprocess.run(
        ["pkill", "-9", "-f", marker],
        cwd=str(ROOT),
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
        check=False,
    )


def promote_best_to_base(workdir: Path, name: str) -> int | None:
    """Replace base.c with the best permuter output if it improved the seed."""
    rows = output_dirs(workdir)
    if not rows:
        return None
    best_score, best_dir = rows[0]
    current = base_score(workdir)
    if current is not None and best_score >= current:
        return None
    source = best_dir / "source.c"
    base_path = workdir / "base.c"
    if not source.is_file() or not base_path.is_file():
        return None
    new_fn = extract_function(source.read_text(), name)
    old_fn = extract_function(base_path.read_text(), name)
    if not new_fn or not old_fn:
        return None
    base_path.write_text(base_path.read_text().replace(old_fn, new_fn, 1))
    promoted = base_score(workdir)
    if promoted is not None:
        print(
            f"promoted output-{best_score}-* to base.c (score {current} -> {promoted})",
            flush=True,
        )
    return promoted


def _one_round(
    workdir: Path,
    *,
    jobs: int,
    seconds: int,
    strict_branches: bool,
    round_no: int,
    dashboard: bool = False,
    only_if_below: int | None = None,
    dash_state=None,
) -> bool:
    """Run one bounded permuter pass. Returns True if the user interrupted."""
    cmd = [
        sys.executable,
        str(PERM / "permuter.py"),
        str(workdir),
        "-j",
        str(jobs),
        "--stop-on-zero",
        "--no-context-output",
    ]
    if not dashboard:
        cmd.append("--quiet")
    if strict_branches:
        # The permuter ignores branch targets by default, which can produce a
        # "score 0" that is not byte-identical (see docs/decomp-patterns.md).
        cmd.append("--no-ignore-branch-targets")
    if only_if_below is not None:
        cmd.extend(["--only-if-below", str(only_if_below)])
        cmd.append("--better-only")
    print(
        f"permuting for up to {seconds}s on {jobs} jobs (round {round_no}) ...",
        flush=True,
    )
    if dashboard:
        if str(ROOT) not in sys.path:
            sys.path.insert(0, str(ROOT))
        from tools.decomp.permuter.dashboard.runner import run_round_with_dashboard

        round_result = run_round_with_dashboard(
            workdir=workdir,
            cmd=cmd,
            seconds=seconds,
            jobs=jobs,
            round_no=round_no,
            state=dash_state,
        )
        return round_result.interrupted
    proc = subprocess.Popen(cmd, cwd=str(ROOT), start_new_session=True)
    # The caller owns its own timeout (`timeout 600` in a batch script, or a
    # killed session). `start_new_session=True` means its signal never reaches
    # the worker pool, so forward it.
    prev = {}

    def _forward(signum, _frame):
        kill_permuter_tree(workdir, proc)
        handler = prev.get(signum)
        if callable(handler):
            handler(signum, _frame)
        else:
            signal.signal(signum, signal.SIG_DFL)
            os.kill(os.getpid(), signum)

    for sig in (signal.SIGTERM, signal.SIGINT, signal.SIGHUP):
        prev[sig] = signal.getsignal(sig)
        signal.signal(sig, _forward)
    try:
        proc.wait(timeout=seconds)
    except subprocess.TimeoutExpired:
        print(f"budget of {seconds}s reached")
        kill_permuter_tree(workdir, proc)
    finally:
        for sig, handler in prev.items():
            signal.signal(sig, handler)
    return False


#: A round that gets the best score down to at most this fraction of where the
#: round started is making real progress and earns another round.
ESCALATE_RATIO = 0.6

#: Upper bound on rounds, so an unlucky sequence of improvements cannot spin.
MAX_ROUNDS = 4


def run_permuter(
    workdir: Path,
    *,
    jobs: int,
    seconds: int,
    seed_score: int,
    strict_branches: bool,
    escalate: bool = True,
    dashboard: bool = False,
    dash_state=None,
    function_name: str = "",
) -> tuple[int, bool]:
    """Run the permuter until score 0 or timeout. Returns the best score seen.

    A single fixed budget cannot serve both failure modes. Most seeds are dead
    ends — `randomization` (no perm macros in a hand-written seed) either finds
    something in the first minute or never does — and spending 4 minutes on each
    of those starves the queue. But some seeds are one round from a match:
    `sub_08061C48` went 210 -> 10 inside its first 120s and was parked on the
    timer. So probe once, then keep going only while the score is still
    collapsing.
    """
    best = seed_score
    rounds = MAX_ROUNDS if escalate else 1
    interrupted = False
    for round_no in range(1, rounds + 1):
        reap_stale_permuters()
        only_if_below = best if round_no > 1 and best < seed_score else None
        if round_no > 1 and function_name and only_if_below is not None:
            promoted = promote_best_to_base(workdir, function_name)
            if promoted is not None:
                best = min(best, promoted)
                only_if_below = best
        interrupted = _one_round(
            workdir,
            jobs=jobs,
            seconds=seconds,
            strict_branches=strict_branches,
            round_no=round_no,
            dashboard=dashboard,
            only_if_below=only_if_below,
            dash_state=dash_state,
        )
        scores = [score for score, _ in output_dirs(workdir)]
        round_best = min(scores + [seed_score])
        improved = round_best < best
        best = round_best
        if interrupted:
            break
        if best == 0 or round_no == rounds:
            break
        if not (improved and best <= seed_score * ESCALATE_RATIO):
            break
        print(f"score {best} is still collapsing — granting another round", flush=True)
    return best, interrupted


def extract_function(text: str, name: str) -> str | None:
    """Pull a single function definition out of permuter output/base source."""
    for match in re.finditer(rf"\b{re.escape(name)}\s*\(", text):
        line_start = text.rfind("\n", 0, match.start()) + 1
        head = text[line_start : match.start()]
        if head.strip().startswith("#") or ";" in head:
            continue
        brace = text.find("{", match.end())
        if brace == -1 or ";" in text[match.end() : brace]:
            continue
        depth = 0
        for i in range(brace, len(text)):
            char = text[i]
            if char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
                if depth == 0:
                    return text[line_start : i + 1].strip()
    return None


def prepend_match_flags(candidate: str, workdir: Path) -> str:
    """Re-attach the `/* match-flags: ... */` comment to an extracted body.

    Permuter output (and any function we extract) loses the comment, but
    match_function.py and the permuter both need it — without it the candidate
    recompiles with a `push {lr}` prologue that retail does not have.
    """
    flags_path = workdir / "matchflags"
    if not flags_path.is_file() or "match-flags" in candidate:
        return candidate
    flags = flags_path.read_text().split()
    if not flags:
        return candidate
    return f"/* match-flags: {' '.join(flags)} */\n{candidate}"


def prepend_compiler(candidate: str, workdir: Path) -> str:
    """Re-attach `/* match-compiler: ... */` to an extracted body.

    Same reason as prepend_match_flags: the permuter's `base.c`/`source.c` are
    preprocessed, so the comment is gone. Without it the candidate is verified
    (and landed) with the default agbcc, which cannot reproduce the bytes it was
    searched for with old_agbcc.
    """
    compiler_path = workdir / "compiler"
    if not compiler_path.is_file() or "match-compiler" in candidate:
        return candidate
    compiler = compiler_path.read_text().strip()
    if not compiler or compiler == "agbcc":
        return candidate
    return f"/* match-compiler: {compiler} */\n{candidate}"


def verify(name: str, body: str, scratch: Path) -> bool:
    sys.path.insert(0, str(ROOT / "tools" / "decomp"))
    from match_function import write_single_function_c  # noqa: WPS433

    write_single_function_c(name, body, scratch)
    result = subprocess.run(
        [sys.executable, str(MATCH_SCRIPT), name, str(scratch)],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
    )
    if result.returncode == 0:
        return True
    sys.stderr.write(result.stdout or "")
    return False


def integrate(name: str, body: str, note: str, *, skip_compare: bool = False) -> int:
    # Pass the raw function definition: integrate_c.py re-wraps it with the
    # project headers and re-verifies before writing src/matched/.
    cmd = [
        sys.executable,
        str(INTEGRATE),
        name,
        body,
        "--kind",
        "semantic",
        "--note",
        note,
    ]
    if skip_compare:
        cmd.append("--skip-compare")
    return subprocess.run(cmd, cwd=str(ROOT), check=False).returncode


def candidate_from(workdir: Path, name: str) -> tuple[str, str] | None:
    """First candidate that survives match_function.py.

    Tries the imported seed, then every score-0 permuter output (newest first).
    The permuter's score alone is not proof: it ignores branch targets, so a
    "score 0" can still differ by a branch offset. Everything here is verified
    with match_function.py before it is reported.
    """
    scratch = ROOT / "build" / "permuter-import" / f"{name}.candidate.c"
    scratch.parent.mkdir(parents=True, exist_ok=True)
    sources: list[Path] = []
    if (workdir / "base.c").is_file():
        sources.append(workdir / "base.c")
    sources += sorted(
        (d / "source.c" for score, d in output_dirs(workdir) if score == 0 and (d / "source.c").is_file()),
        reverse=True,
    )
    for source in sources:
        body = extract_function(source.read_text(), name)
        if not body:
            continue
        body = prepend_match_flags(body, workdir)
        body = prepend_compiler(body, workdir)
        if verify(name, body, scratch):
            return body, f"permuter/{source.relative_to(ROOT)}"
    return None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function", help="sub_080XXXXXX")
    parser.add_argument("--seconds", type=int, default=180, help="permuter budget (default 180)")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    parser.add_argument(
        "--reuse",
        action="store_true",
        help="reuse an existing nonmatchings/<fn> workdir instead of a fresh import",
    )
    parser.add_argument(
        "--no-integrate",
        action="store_true",
        help="verify but do not land the result in src/matched/",
    )
    parser.add_argument(
        "--skip-compare",
        action="store_true",
        help="do not run make compare after integrating (batch runners verify once)",
    )
    parser.add_argument(
        "--strict-branches",
        action="store_true",
        help="score branch targets too (slower, but no false score 0)",
    )
    parser.add_argument(
        "--no-strict-branches",
        action="store_true",
        help="do not score branch targets (default unless seed is >=90%% byte match)",
    )
    parser.add_argument(
        "--no-escalate",
        action="store_true",
        help="single round, even if the score is still collapsing",
    )
    parser.add_argument(
        "--dashboard",
        action="store_true",
        help="open a live web dashboard at http://127.0.0.1:8765/ while permuting",
    )
    parser.add_argument(
        "--no-browser",
        action="store_true",
        help="with --dashboard, do not auto-open the browser",
    )
    args = parser.parse_args()
    name = args.function

    if not PERM.is_dir():
        print("run tools/decomp/permuter/setup.sh first", file=sys.stderr)
        return 2

    rc = ensure_import(name, force=not args.reuse)
    if rc != 0:
        return 2
    workdir = workdir_for(name)

    byte_line = byte_match_summary(name)
    if byte_line:
        print(f"{name}: {byte_line}")

    strict_branches = args.strict_branches
    if not strict_branches and not args.no_strict_branches and byte_line:
        m = re.search(r"(\d+(?:\.\d+)?)%", byte_line)
        if m and float(m.group(1)) >= 90.0:
            strict_branches = True
            print(f"{name}: auto-enabling --strict-branches (seed >= 90% byte match)")

    seed_score = base_score(workdir)
    if seed_score is None:
        print(f"{name}: seed does not compile — fix the seed first", file=sys.stderr)
        return 2
    print(f"{name}: base score {seed_score}")

    if seed_score == 0:
        found = candidate_from(workdir, name)
        if found:
            print("base seed already matches — skipping the search")
        else:
            # Base scores 0 but the extracted body does not verify.
            print(f"{name}: base scores 0 but verification failed", file=sys.stderr)
            return 1
    else:
        if args.dashboard:
            if str(ROOT) not in sys.path:
                sys.path.insert(0, str(ROOT))
            from tools.decomp.permuter.dashboard.runner import (
                finalize_dashboard_state,
                start_dashboard_server,
            )

            dash, dash_state = start_dashboard_server(
                function=name,
                workdir=workdir,
                budget_sec=args.seconds,
                jobs=args.jobs,
                open_browser=not args.no_browser,
            )
        else:
            dash = None
            dash_state = None
        best, interrupted = run_permuter(
            workdir,
            jobs=args.jobs,
            seconds=args.seconds,
            seed_score=seed_score,
            strict_branches=strict_branches,
            escalate=not args.no_escalate,
            dashboard=args.dashboard,
            dash_state=dash_state,
            function_name=name,
        )
        if dash is not None and dash_state is not None:
            finalize_dashboard_state(dash_state, interrupted=interrupted)
            dash.stop()
        if interrupted:
            print(f"{name}: interrupted — best score {best}")
            return 130
        found = candidate_from(workdir, name)
        if not found:
            zeros = [d for score, d in output_dirs(workdir) if score == 0]
            if zeros:
                print(
                    f"{name}: permuter reported score 0 but no candidate verifies "
                    "(branch-target false zero) — retry with --strict-branches",
                    file=sys.stderr,
                )
            else:
                print(f"{name}: no score 0 within budget, best {best}")
                print("park the seed and move on — do not hand-tune this one")
            return 1

    candidate, origin = found
    print(f"{name}: MATCH ({origin})")

    if args.no_integrate:
        scratch = ROOT / "build" / "permuter-import" / f"{name}.candidate.c"
        print(f"candidate kept at {scratch.relative_to(ROOT)}")
        return 0
    return integrate(name, candidate, origin, skip_compare=args.skip_compare)


if __name__ == "__main__":
    raise SystemExit(main())
