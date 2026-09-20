# Autonomous decompilation mission

**Copy-paste this block to start (or resume) a hands-off agent session:**

```text
Autonomous decomp mission — do not stop for approval between batches.

Do not re-read decomp-mission.md / roadmap. Start with scripts.

Goal: byte-matching C for all 633 functions, self-documenting names, make compare always OK.

Each session until done:
1. python3 tools/decomp/report_status.py && make compare
2. python3 tools/decomp/script_first.py
3. python3 tools/decomp/agent_packet.py --next   # one leftover function; max 2 retries then park
4. Every 3–5 batches: tools/decomp/ram_map_pass.sh
5. Update docs/decomp-status.md
6. Commit after each green batch (see Commit policy)

Escalate only: baserom missing, agbcc broken, make compare fails after 3 fix attempts.

Do not stop until every function has src/matched/*.c OR is documented asm-only with reason,
and beyblade_g_revolution.toml [renames] covers all functions with self-documenting names.
```

---

## Definition of done

| Layer | Criterion | Current tooling |
|-------|-----------|-----------------|
| **ROM linked** | 633/633 functions in peel; `make compare` OK | `match_batch.sh`, `integrate_match.py` |
| **C decomp** | Every *convertible* function has verified C in `src/matched/` | `script_first.py`, `match_function.py`, `integrate_c.py` |
| **RAM map** | Battle/menu IWRAM named; pool rescanned periodically | `ram_map_pass.sh`, `battle_scan.py` |
| **Names** | `[renames]` in `beyblade_g_revolution.toml`; C/asm use readable names | Phase 4 + `generate_asm.py --force` |
| **Shiftable** | No fixed-VMA per-function sections (Phase 5) | `check_shiftable.py` |

**Asm-only is acceptable** for functions that cannot byte-match in agbcc (literal-pool PC-relative loads, permuter-hard stubs). List them in `docs/decomp-status.md` under **Asm-only (documented)** with the blocker reason.

---

## Session loop (current phase: 3b → 4)

Phase 1 (link all asm) is **complete**. Phase 3 placed byte-matched C for all 633 functions; **many are opcode embeds** (`asm(".byte …")`). **Phase 3b** replaces those with semantic C.

Default loop:

```bash
# 1. Status gate
python3 tools/decomp/report_status.py
make compare

# 2. Deterministic convert (patterns + cleaned m2c)
python3 tools/decomp/script_first.py

# 3. Remainder — one packet, not a doc dump
python3 tools/decomp/agent_packet.py --next
# Write C from that packet only. Max 2 match_function.py retries, then park_wip.py.

# 4. Grow zero-token path from clones
python3 tools/decomp/cluster_shapes.py

# 5. RAM map (every 3–5 conversion batches)
tools/decomp/ram_map_pass.sh

# 6. Report + commit
python3 tools/decomp/report_status.py
```

---

## Fork policy

When multiple approaches exist, try in this order. **Never break `make compare`.**

```
┌─ script_first.py / c_patterns MATCH?
│    YES → already integrated (or try_convert.py --integrate)
│    NO  ↓
├─ agent_packet.py seed + hand-refined C (max 2 retries)?
│    match_function.py → MATCH → integrate_c.py
│    DIFF → permuter (same-size); still DIFF ↓
├─ Literal-pool / agbcc ordering mismatch?
│    Keep asm matching in `src/matched/`; **park** unmatched C in `src/wip/`
│    (see docs/decomp-wip.md). Do not revert a reconstruction without a seed.
│    Promote RAM symbols if tracing clarified globals
├─ Clone family in cluster_shapes.py?
│    Add one matcher to c_patterns.py; re-run script_first.py
├─ Role understood while reading asm?
│    Promote gUnk_* → named SET_DATA in asm/ram_map_*.s; ram_map_pass.sh
│    Subsystem complete? → batch [renames] in beyblade_g_revolution.toml
└─ ≥80% in C + check_shiftable gates met?
     Begin Phase 5 shiftable ROM migration (see decomp-roadmap.md)
```

### Subsystem order (suggested)

1. **Battle** — `battle_scan.py`, `docs/battle.md`, `include/battle.h`
2. **Menu / UI** — functions heavy on `gBattleWork`, `gMainWorkPtr`
3. **Save / SRAM** — after RAM map stable
4. **Audio (Gax)** — if distinct cluster appears in scans
5. **Remaining** — triage by size + call graph

Rename (`sub_*` → `BtlFoo`) only in **Phase 4**, after the function's role is understood — not at first conversion.

---

## C style (default)

Follow the [aw2bhr](https://github.com/Mad-Man-Dan/aw2bhr) matching style. New semantic C must compile with agbcc and `match_function.py` → MATCH.

| Do | Don't |
|----|--------|
| `a->unkA0 = v` on a growing struct in `include/unknown-types.h` | `*(u16 *)((u8 *)a + 0xa0) = v` |
| `gMainWorkPtr->unk1800 = v` (typed macro in `ram_map.h`) | `*(u32 *)((u8 *)*(u32 **)0x03000198 + 0x1800) = v` |
| `filler_XX` for unread bytes; `unkXX` for accessed fields | Per-file `void *` + ad-hoc offsets |
| `register int r2 asm("r2") = 0; asm("swi 5" : : "r"(r2));` for BIOS | `asm volatile("movs r2, #0")` to force registers |
| Add a field to a struct (superset) | Move a field or change its type without re-matching every user |

- Structs are a **superset**: adding a field is fine; moving one is not. Offsets and sizeof are load-bearing.
- `volatile` on a store only when the ROM kept extra narrowing (`lsl #24; lsr #24` before `strb`).
- Naked `.byte` / unified `asm(...)` is for documented opcode stubs, not new C.
- `include/unknown-functions.h` gets prototypes when one `sub_*` needs to call another.
- Keep per-function `src/matched/*.c` until Phase 5 (do not pack consecutive functions into one file yet).

`c_patterns.py` emits member stores against `struct Unk*` names from `tools/decomp/unknown_types.py`. If a new offset appears, add the field (split a `filler_`) in `unknown-types.h` before integrating.

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
- `build_tools.sh` / agbcc build fails after retry
- `make compare` still fails after **3** distinct fix attempts (attach log + diff)

---

## Key paths

| What | Where |
|------|-------|
| End-to-end process | [README.md](../README.md) § Decompilation |
| Mission (this file) | `docs/decomp-mission.md` |
| Script-first batch | `tools/decomp/script_first.py` |
| Function packet | `tools/decomp/agent_packet.py` |
| Master plan | `docs/decomp-roadmap.md` |
| Live log | `docs/decomp-status.md` |
| Parked unmatched C | `docs/decomp-wip.md`, `src/wip/` |
| C-vs-original counter | `docs/decomp-progress.json` / `decomp-progress.svg` |
| Battle notes | `docs/battle.md` |
| Matched C | `src/matched/*.c` |
| Types | `include/unknown-types.h`, `include/unknown-functions.h` |
| Manifest | `build/matched.json` |
| Renames | `beyblade_g_revolution.toml` `[renames]` |

---

## Progress snapshot

Live counts: `python3 tools/decomp/report_status.py` (or `progress.py`).
Update `decomp-status.md` after each batch; don't hand-copy numbers here.
