# Cursor skills — GBA matching decomp

Agent skills for this repo and future pret-style GBA decomp projects.

| Skill | When to use |
|-------|-------------|
| [gba-decomp-session](gba-decomp-session/SKILL.md) | Start/resume a decomp session; triage, integrate, batch |
| [gba-decomp-matching](gba-decomp-matching/SKILL.md) | `match_function.py` DIFF; near-misses; register/pool fixes |
| [gba-decomp-improve](gba-decomp-improve/SKILL.md) | After each batch: seeds, patterns, queue, metrics, template |
| [gba-decomp-ecosystem](gba-decomp-ecosystem/SKILL.md) | External guides (pret, m2c, permuter); new-repo bootstrap |

## Self-improvement loop (short)

1. **Session** → pick queue targets → convert → `make compare`
2. **Matching** → fix DIFF or block + document
3. **Improve** → add seeds/patterns → refresh queue → update status → commit
4. **Ecosystem** → consult when methodology or tooling choice is unclear

Copy `.cursor/skills/` into a new decomp repo when using this project as a scaffold.
