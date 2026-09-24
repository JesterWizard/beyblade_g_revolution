"""Live permuter state for the dashboard."""

from __future__ import annotations

import json
import re
import threading
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[4]

def _strip_ansi(text: str) -> str:
    return re.sub(r"\033\[[0-9;]*m", "", text)


_BASE_SCORE_RE = re.compile(r"base score = (\d+)")
_PERM_COUNT_RE = re.compile(r"Will run for (\d+) iterations\.")
_PERM_BASES_RE = re.compile(r"Will try (\d+) different base sources\.")
_ITERATION_RE = re.compile(
    r"iteration (\d+), (\d+) errors(?:, (\d+) permuter failures)?, score = (\d+|inf)"
)
_BEST_SCORE_RE = re.compile(
    r"found (?:new best|a better|tied best) score! \((\d+) vs (\d+)\)"
)
_WROTE_RE = re.compile(r"wrote to (.+)$")
_ROUND_RE = re.compile(r"permuting for up to (\d+)s on (\d+) jobs \(round (\d+)\)")
_OUT_DIR_RE = re.compile(r"^output-(\d+)-(\d+)$")


def score_pct(base_score: int, score: int) -> float:
    """Progress from base score toward zero (100% = score 0)."""
    if base_score <= 0:
        return 100.0 if score == 0 else 0.0
    if score <= 0:
        return 100.0
    if score >= base_score:
        return 0.0
    return round(100.0 * (base_score - score) / base_score, 1)


@dataclass
class Attempt:
    ts: float
    iteration: int
    score: int
    pct: float
    message: str
    is_best: bool = False
    output_dir: str = ""


@dataclass
class Candidate:
    score: int
    pct: float
    path: str
    ts: float
    index: int = 0


@dataclass
class PermuterState:
    function: str = ""
    workdir: str = ""
    phase: str = "idle"  # idle | loading | running | done | error
    started_at: float = 0.0
    elapsed_sec: float = 0.0
    budget_sec: int = 0
    round_no: int = 0
    jobs: int = 1
    mode: str = "unknown"  # finite | randomization
    perm_total: int | None = None
    perm_remaining: int | None = None
    iteration: int = 0
    errors: int = 0
    internal_errors: int = 0
    base_score: int = 0
    best_score: int = 0
    best_pct: float = 0.0
    retail_bytes: int = 0
    rate_per_sec: float = 0.0
    eta_sec: int | None = None
    status_line: str = ""
    last_message: str = ""
    stop_reason: str = ""
    messages: list[str] = field(default_factory=list)
    recent_attempts: list[Attempt] = field(default_factory=list)
    top_candidates: list[Candidate] = field(default_factory=list)
    error: str = ""

    _lock: threading.Lock = field(default_factory=threading.Lock, repr=False)
    _seen_outputs: set[str] = field(default_factory=set, repr=False)
    _first_iteration_ts: float = field(default=0.0, repr=False)

    def snapshot(self) -> dict[str, Any]:
        with self._lock:
            skip = {"_lock", "_seen_outputs", "_first_iteration_ts"}
            data: dict[str, Any] = {}
            for key in self.__dataclass_fields__:
                if key in skip:
                    continue
                data[key] = getattr(self, key)
            if self.started_at:
                data["elapsed_sec"] = round(time.time() - self.started_at, 1)
            data["recent_attempts"] = [
                {
                    "ts": a.ts,
                    "iteration": a.iteration,
                    "score": a.score,
                    "pct": a.pct,
                    "message": a.message,
                    "is_best": a.is_best,
                    "output_dir": a.output_dir,
                }
                for a in self.recent_attempts
            ]
            data["top_candidates"] = [
                {
                    "score": c.score,
                    "pct": c.pct,
                    "path": c.path,
                    "ts": c.ts,
                    "index": c.index,
                }
                for c in self.top_candidates
            ]
            return data

    def write_json(self, path: Path) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(self.snapshot(), indent=2) + "\n")

    def begin(
        self,
        *,
        function: str,
        workdir: Path,
        budget_sec: int,
        jobs: int,
        retail_bytes: int = 0,
    ) -> None:
        with self._lock:
            self.function = function
            self.workdir = str(workdir.relative_to(ROOT))
            self.phase = "loading"
            self.started_at = time.time()
            self.budget_sec = budget_sec
            self.jobs = jobs
            self.retail_bytes = retail_bytes
            self.round_no = 0
            self.iteration = 0
            self.errors = 0
            self.internal_errors = 0
            self.base_score = 0
            self.best_score = 0
            self.best_pct = 0.0
            self.rate_per_sec = 0.0
            self.eta_sec = None
            self.status_line = ""
            self.last_message = ""
            self.stop_reason = ""
            self.messages = []
            self.recent_attempts = []
            self.top_candidates = []
            self.error = ""
            self._seen_outputs = set()
            self._first_iteration_ts = 0.0
            self.mode = "unknown"
            self.perm_total = None
            self.perm_remaining = None

    def set_phase(self, phase: str) -> None:
        with self._lock:
            self.phase = phase

    def set_error(self, message: str) -> None:
        with self._lock:
            self.phase = "error"
            self.error = message
            self._push_message(message)

    def _push_message(self, message: str) -> None:
        self.last_message = message
        self.messages.append(message)
        if len(self.messages) > 200:
            self.messages = self.messages[-200:]

    def _record_best(self, score: int) -> None:
        if self.best_score == 0 or score < self.best_score:
            self.best_score = score
            self.best_pct = score_pct(self.base_score, score)

    def _push_attempt(
        self,
        *,
        iteration: int,
        score: int,
        message: str,
        is_best: bool = False,
        output_dir: str = "",
    ) -> None:
        attempt = Attempt(
            ts=time.time(),
            iteration=iteration,
            score=score,
            pct=score_pct(self.base_score, score),
            message=message,
            is_best=is_best,
            output_dir=output_dir,
        )
        self.recent_attempts.append(attempt)
        if len(self.recent_attempts) > 100:
            self.recent_attempts = self.recent_attempts[-100:]

    def _refresh_top_candidates(self, workdir: Path) -> None:
        rows: list[Candidate] = []
        if workdir.is_dir():
            for child in workdir.iterdir():
                m = _OUT_DIR_RE.match(child.name)
                if m and child.is_dir():
                    score = int(m.group(1))
                    index = int(m.group(2))
                    rows.append(
                        Candidate(
                            score=score,
                            pct=score_pct(self.base_score, score),
                            path=str(child.relative_to(ROOT)),
                            ts=child.stat().st_mtime,
                            index=index,
                        )
                    )
        rows.sort(key=lambda c: (c.score, -c.ts))
        self.top_candidates = rows[:20]

    def _update_rates(self) -> None:
        if self.started_at <= 0:
            return
        elapsed = max(time.time() - self.started_at, 0.001)
        self.elapsed_sec = round(elapsed, 1)
        if self.iteration > 0:
            self.rate_per_sec = round(self.iteration / elapsed, 2)
        if self.budget_sec > 0:
            remaining = max(self.budget_sec - int(elapsed), 0)
            self.eta_sec = remaining
        elif self.perm_total and self.perm_remaining is not None and self.rate_per_sec > 0:
            self.eta_sec = int(self.perm_remaining / self.rate_per_sec)

    def ingest_line(self, line: str, *, workdir: Path) -> None:
        line = _strip_ansi(line.strip())
        if not line:
            return
        with self._lock:
            m = _ROUND_RE.search(line)
            if m:
                self.budget_sec = int(m.group(1))
                self.jobs = int(m.group(2))
                self.round_no = int(m.group(3))
                self.phase = "running"
                self._push_message(line)
                return

            m = _BASE_SCORE_RE.search(line)
            if m:
                self.base_score = int(m.group(1))
                self.best_score = self.base_score
                self.best_pct = score_pct(self.base_score, self.base_score)
                self._push_message(line)
                return

            m = _PERM_COUNT_RE.search(line)
            if m:
                self.mode = "finite"
                self.perm_total = int(m.group(1))
                self.perm_remaining = self.perm_total
                self._push_message(line)
                return

            m = _PERM_BASES_RE.search(line)
            if m:
                self.mode = "randomization"
                self.perm_total = int(m.group(1))
                self._push_message(line)
                return

            m = _BEST_SCORE_RE.search(line)
            if m:
                score = int(m.group(1))
                self._record_best(score)
                msg = line.split("] ", 1)[-1] if "] " in line else line
                self._push_message(msg)
                self._push_attempt(
                    iteration=self.iteration,
                    score=score,
                    message=msg,
                    is_best=True,
                )
                return

            m = _WROTE_RE.search(line)
            if m:
                out_path = m.group(1).strip()
                self._seen_outputs.add(out_path)
                m2 = _OUT_DIR_RE.search(Path(out_path).name)
                if m2:
                    score = int(m2.group(1))
                    self._record_best(score)
                    self._push_attempt(
                        iteration=self.iteration,
                        score=score,
                        message=f"saved candidate score {score}",
                        is_best=score == self.best_score,
                        output_dir=out_path,
                    )
                self._refresh_top_candidates(workdir)
                return

            m = _ITERATION_RE.search(line)
            if m:
                self.iteration = int(m.group(1))
                self.errors = int(m.group(2))
                if m.group(3):
                    self.internal_errors = int(m.group(3))
                score_raw = m.group(4)
                score = self.base_score if score_raw == "inf" else int(score_raw)
                self.status_line = line
                if self._first_iteration_ts == 0.0:
                    self._first_iteration_ts = time.time()
                if self.perm_total and self.mode == "finite":
                    self.perm_remaining = max(self.perm_total - self.iteration, 0)
                self._update_rates()
                return

            if "Found zero score" in line or "MATCH" in line:
                self.phase = "done"
                self._push_message(line)
                return

            if line.startswith("[") and (
                "found " in line or "tied " in line or "wrote to" in line
            ):
                self._push_message(line.split("] ", 1)[-1])

    def poll_workdir(self, workdir: Path) -> None:
        with self._lock:
            self._refresh_top_candidates(workdir)
            self._update_rates()

    def _resolve_best_score(self, best_score: int | None) -> int:
        if best_score is not None:
            return best_score
        if self.top_candidates:
            return min(c.score for c in self.top_candidates)
        return self.best_score

    def finalize(
        self,
        *,
        reason: str = "done",
        matched: bool = False,
        best_score: int | None = None,
    ) -> None:
        """Mark the run finished (done, interrupted, timeout, or error)."""
        with self._lock:
            self.phase = reason
            self.stop_reason = reason
            self.best_score = self._resolve_best_score(best_score)
            self.best_pct = score_pct(self.base_score, self.best_score)
            self._update_rates()
            self.eta_sec = 0
            if reason == "interrupted":
                self._push_message(
                    f"Stopped by user — best score {self.best_score} "
                    f"({self.best_pct:.1f}% toward 0)"
                )
            elif reason == "timeout":
                self._push_message(
                    f"Time budget reached — best score {self.best_score} "
                    f"({self.best_pct:.1f}% toward 0)"
                )
            elif matched or self.best_score == 0:
                self._push_message("Match found — permuter score 0")
            else:
                self._push_message(
                    f"Finished — best score {self.best_score} "
                    f"({self.best_pct:.1f}% toward 0)"
                )

    def finish(self, *, matched: bool, best_score: int | None = None) -> None:
        self.finalize(reason="done", matched=matched, best_score=best_score)


def retail_byte_count(function: str) -> int:
    """Best-effort retail .text size for byte-match context."""
    sys_path = ROOT / "tools" / "decomp"
    if str(sys_path) not in __import__("sys").path:
        __import__("sys").path.insert(0, str(sys_path))
    try:
        from asm_bytes import retail_bytes  # noqa: WPS433

        return len(retail_bytes(function))
    except Exception:
        return 0
