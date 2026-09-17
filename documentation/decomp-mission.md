# Autonomous decompilation mission

**Copy-paste this block to start (or resume) a hands-off agent session:**

```text
Autonomous decomp mission — do not stop for approval between batches.

Read documentation/decomp-mission.md, AGENTS.md, and documentation/decomp-roadmap.md first.

Goal: byte-matching C for all 633 functions, self-documenting names, make compare always OK.

Each session until done:
1. python3 scripts/decomp/report_status.py && make compare
2. At every fork: follow the Fork policy below; verify with match_function.py / make compare
3. Work one subsystem batch (battle first: battle_scan.py), then the next subsystem
4. Every 3–5 batches: scripts/decomp/ram_map_pass.sh
5. Update documentation/decomp-status.md (+ subsystem docs, e.g. battle.md)
6. Commit after each green batch (see Commit policy)

Escalate only: baserom missing, agbcc broken, make compare fails after 3 fix attempts.

Do not stop until every function has src/matched/*.c OR is documented asm-only with reason,
and beyblade_g_revolution.toml [renames] covers all functions with self-documenting names.
```

---

## Definition of done

| Layer | Criterion | Current tooling |
|-------|-----------|-----------------|
| **ROM linked** | 633/633 functions in peel; `make compare` OK | `match_loop.sh`, `integrate_match.py` |
| **C decomp** | Every *convertible* function has verified C in `src/matched/` | `match_function.py`, `integrate_c.py`, `c_convert_batch.sh` |
| **RAM map** | Battle/menu IWRAM named; pool rescanned periodically | `ram_map_pass.sh`, `battle_scan.py` |
| **Names** | `[renames]` in `beyblade_g_revolution.toml`; C/asm use readable names | Phase 4 + `generate_asm.py --force` |
| **Shiftable** | No fixed-VMA per-function sections (Phase 5) | `check_shiftable.py` |

**Asm-only is acceptable** for functions that cannot byte-match in agbcc (literal-pool PC-relative loads, permuter-hard stubs). List them in `documentation/decomp-status.md` under **Asm-only (documented)** with the blocker reason.

---

## Session loop (current phase: 3 → 4)

Phase 1 (link all asm) is **complete**. Default loop:

```bash
# 1. Status gate
python3 scripts/decomp/report_status.py
make compare

# 2. Pick subsystem / triage
python3 scripts/decomp/battle_scan.py -n 20    # battle first
scripts/decomp/battle_convert_batch.sh 10
scripts/decomp/battle_cursor_batch.sh 5      # m2c seeds for hard battle fns
python3 scripts/decomp/triage_functions.py -n 10

# 3. Convert (try routes in Fork policy order)
scripts/decomp/c_convert_batch.sh 30
python3 scripts/decomp/match_function.py sub_XXXXXXXX src/matched/sub_XXXXXXXX.c
python3 scripts/decomp/integrate_c.py sub_XXXXXXXX @src/matched/sub_XXXXXXXX.c --note <subsystem>/<role>

# 4. Hard functions
scripts/decomp/cursor_batch.sh 10              # m2c seeds, no API key

# 5. RAM map (every 3–5 conversion batches)
scripts/decomp/ram_map_pass.sh

# 6. Phase 5 preflight (informational until migration)
python3 scripts/decomp/check_shiftable.py

# 7. Report + commit
python3 scripts/decomp/report_status.py
```

---

## Fork policy

When multiple approaches exist, try in this order. **Never break `make compare`.**

```
┌─ Trivial asm (c_patterns matches)?
│    YES → c_convert_batch.sh or integrate_c.py
│    NO  ↓
├─ m2c seed + hand-refined C?
│    match_function.py → MATCH → integrate_c.py
│    DIFF → try cursor_batch.sh / permuter; still DIFF ↓
├─ Literal-pool / agbcc ordering mismatch?
│    Keep asm matching; add to decomp-status.md asm-only list
│    Promote RAM symbols if tracing clarified globals
├─ Role understood while reading asm?
│    Promote gUnk_* → named SET_DATA in asm/ram_map_*.s; ram_map_pass.sh
│    Subsystem complete? → batch [renames] in beyblade_g_revolution.toml
└─ ≥80% in C + check_shiftable gates met?
     Begin Phase 5 shiftable ROM migration (see decomp-roadmap.md)
```

### Subsystem order (suggested)

1. **Battle** — `battle_scan.py`, `documentation/battle.md`, `include/battle.h`
2. **Menu / UI** — functions heavy on `gBattleWork`, `gMainWorkPtr`
3. **Save / SRAM** — after RAM map stable
4. **Audio (Gax)** — if distinct cluster appears in scans
5. **Remaining** — triage by size + call graph

Rename (`sub_*` → `BtlFoo`) only in **Phase 4**, after the function's role is understood — not at first conversion.

---

## Commit policy

Per [AGENTS.md](../AGENTS.md): **commit after every successful batch without asking the user.**

Pre-commit checklist:

- [ ] `make compare` → `beyblade_g_revolution.gba: OK`
- [ ] No `baserom.gba`, `*.gba`, or accidental `build/` artifacts staged

Message formats:

```
decomp: C batch (+N functions, M/633 in src/matched)

Battle: sub_080…, sub_080…
make compare: OK
```

```
decomp: battle RAM names + N C functions

make compare: OK
```

```
decomp: rename batch (subsystem Btl)

[renames] in beyblade_g_revolution.toml
make compare: OK
```

If the user explicitly says **do not commit** in the chat, skip commits and report at end of session instead.

---

## Escalation (ask the user)

- `baserom.gba` missing or wrong SHA1
- `scripts/setup.sh` / agbcc build fails after retry
- `make compare` still fails after **3** distinct fix attempts (attach log + diff)
- Need `ANTHROPIC_API_KEY` for Mizuchi and Cursor batch is insufficient

---

## Key paths

| What | Where |
|------|-------|
| Mission (this file) | `documentation/decomp-mission.md` |
| Master plan | `documentation/decomp-roadmap.md` |
| Live log | `documentation/decomp-status.md` |
| Battle notes | `documentation/battle.md` |
| Matched C | `src/matched/*.c` |
| Manifest | `build/matched.json` |
| Renames | `beyblade_g_revolution.toml` `[renames]` |

---

## Progress snapshot (update in decomp-status.md)

See `python3 scripts/decomp/report_status.py` for live counts:

- Linked in ROM: 633/633
- C in `src/matched/`: growing (trivial + battle)
- Renames: Phase 4 not started
- Shiftable: Phase 5 gated
