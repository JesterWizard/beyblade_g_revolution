---
name: gba-decomp-ecosystem
description: >-
  External GBA matching-decompilation guides and tools (pret/pokeemerald, m2c,
  decomp-permuter, agbcc). Use when learning decomp methodology, looking up
  matching standards, starting a new GBA decomp project, or choosing between
  m2c, permuter, and hand matching.
---

# GBA decomp ecosystem (guides & tools)

This repo follows the **pret matching-decomp** model: agbcc oracle, byte-identical `make compare`, C89 semantic code.

## Essential reading (methodology)

| Resource | URL | Use for |
|----------|-----|---------|
| pokeemerald decomp standards | https://mintlify.wiki/pret/pokeemerald/contributing/decompilation-standards | C89, matching mindset, `make compare` gate |
| pokeemerald building | https://mintlify.wiki/pret/pokeemerald/building | Build + verify workflow |
| pokeemerald docs index | https://pret-pokeemerald.mintlify.app/ | Full pret doc tree |
| pret/agbcc | https://github.com/pret/agbcc | Matching compiler install |

## Core tools (used in matching pipelines)

| Tool | URL | Role |
|------|-----|------|
| **m2c** | https://github.com/matt-kempster/m2c | Asm → seed C (`--target gba`) |
| **decomp-permuter** | https://github.com/simonlindholm/decomp-permuter | Search C permutations for byte match |
| **decomp-permuter-agbcc** | https://github.com/WhenGryphonsFly/decomp-permuter-agbcc | agbcc/ARMv4T notes |
| **asm-differ** | https://github.com/simonlindholm/asm-differ | Visual asm diff (optional) |

m2c flags worth knowing:

- `--target gba` — APCS Thumb (this project)
- `--valid-syntax` — uglier C, better for permuter input
- `-f FunctionName` — single function

## GBA decomp projects (reference implementations)

| Project | Notes |
|---------|--------|
| [pret/pokeemerald](https://github.com/pret/pokeemerald) | Canonical pret layout; largest community |
| [laqieer/fireemblem8j](https://github.com/laqieer/fireemblem8j) | Documented m2c wrapper + decomp loop (`scripts/tools/m2c/`) |
| **This repo** | agbcc + permuter + battle queue + semantic batch tooling |

## Typical workflow (any pret-style GBA decomp)

```
disassemble / split → asm stub per function
       ↓
m2c seed C → hand types + globals
       ↓
match_function / objdiff / make compare  (oracle)
       ↓
DIFF? → register pin → permuter → readable asm + document blocker
       ↓
MATCH → integrate → shrink ROM .incbin → commit
```

## Matching vs modern build

- **Matching path:** agbcc, C89, `HACKS=0`, SHA1 compare — required for decomp %
- **Modern path:** `arm-none-eabi-gcc`, `HACKS=1` — hacks/porting only; breaks compare

Do not mix modern C constructs into matching paths.

## Permuter philosophy (upstream README)

- Permuter **complements** hand matching, not replaces it
- Use `PERM_GENERAL(a, b)` / `PERM_ONCE` when you know two valid C shapes (e.g. ternary vs if)
- Score 0 ≠ guaranteed MATCH — always re-run project oracle (`match_function.py` here)

## When stuck

1. Read pret decomp standards (C89, no mid-block decls)
2. Read this repo’s [docs/decomp-patterns.md](docs/decomp-patterns.md)
3. Search near-miss log in [docs/decomp-status.md](docs/decomp-status.md)
4. Check [docs/decomp-queue.toml](docs/decomp-queue.toml) for known blocks
5. Ask in pret Discord / decomp forums with **function name + DIFF sizes** (not “it doesn’t compile”)

## This repo’s docs (prefer over generic guides)

| Doc | Content |
|-----|---------|
| [docs/decomp-mission.md](docs/decomp-mission.md) | Autonomous loop, fork policy |
| [docs/decomp-patterns.md](docs/decomp-patterns.md) | Project-specific patterns |
| [docs/decomp-roadmap.md](docs/decomp-roadmap.md) | Phases 1–5 |
| [architecture.md](architecture.md) | Directory layout |
| [AGENTS.md](AGENTS.md) | Tool map |

Use **gba-decomp-session** + **gba-decomp-improve** skills for day-to-day work on this tree.
