# Decompilation status

_Agent-maintained log. Updated after each batch run._

## Progress

| Metric | Value |
|--------|-------|
| Non-matching asm | 633 |
| Matching asm (linked) | 71 |
| `src/*.c` files | 1 |
| `pct_asm_matched` | 10.1% |
| Phase | 1 (ASM match loop) |

## Batch log

### 2026-09-17 — batch 3 (20 functions)

Integrated 20 asm-verified functions including literal-pool loaders (`sub_0802B90C`, `sub_080429C0`, …), IWRAM accessors, and field setters. `make compare`: **OK**.

### 2026-09-17 — linker integration + batch 2

11 functions linked via ROM peel tooling.

### 2026-09-17 — bootstrap + batch 1

First 4 functions + `src/stubs.c`.

## Tooling

| Script | Purpose |
|--------|---------|
| `scripts/decomp/cursor_batch.sh` | Triage + m2c seeds |
| `scripts/decomp/integrate_match.py` | Link match into ROM peel |
| `scripts/decomp/match_function.py` | Verify scratch C vs asm (now runs CPP) |
| `scripts/decomp/gen_rom_layout.py` | Regenerate `asm/rom_layout.ld` |

## Next

- Replace asm matchings with byte-matched C (`match_function.py` + `src/`)
- Add IWRAM symbols to `asm/ram_map*.s` instead of hardcoded `0x03…` in C
- Continue integrating score-5 triage candidates

## Blockers

- None (`make compare` green with 31 peeled functions)

### 2026-09-17 — match_batch (+10, 41/633 linked)
- Functions: `sub_080473E4`, `sub_08061BDC`, `sub_08062634`, `sub_08062A1C`, `sub_0806644C`, `sub_08068584`, `sub_08072F94`, `sub_0802B8BC`, `sub_0803EDC8`, `sub_080400C0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 51/633 linked)
- Functions: `sub_080628E4`, `sub_08067890`, `sub_080314FC`, `sub_0803EDF0`, `sub_08068574`, `sub_0806BB38`, `sub_0802D598`, `sub_0802D8C4`, `sub_08062728`, `sub_0806639C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 61/633 linked)
- Functions: `sub_080717F0`, `sub_08033958`, `sub_08061610`, `sub_08061E40`, `sub_08062684`, `sub_0806DEF4`, `sub_0806AC68`, `sub_080705A4`, `sub_080705DC`, `sub_08033F30`
- make compare: OK

### 2026-09-17 — match_batch (+10, 71/633 linked)
- Functions: `sub_08036190`, `sub_08042E78`, `sub_08068884`, `sub_08069F00`, `sub_0806A954`, `sub_0806BE08`, `sub_080346C0`, `sub_0803DD60`, `sub_0803EBB0`, `sub_0803EC34`
- make compare: OK

### 2026-09-17 — match_batch (+10, 81/633 linked)
- Functions: `sub_08033F24`, `sub_08034414`, `sub_08032DB8`, `sub_080686D8`, `sub_080602C0`, `sub_08060394`, `sub_08060428`, `sub_08060438`, `sub_08060448`, `sub_08060458`
- make compare: OK

### 2026-09-17 — match_batch (+10, 91/633 linked)
- Functions: `sub_080312EC`, `sub_08060254`, `sub_08067634`, `sub_080679C0`, `sub_08069C14`, `sub_0807069C`, `sub_08071F84`, `sub_08071F98`, `sub_08034FDC`, `sub_0803ECB8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 101/633 linked)
- Functions: `sub_08040530`, `sub_08042B00`, `sub_080447B4`, `sub_080679A4`, `sub_0806BDA8`, `sub_08031294`, `sub_080312D8`, `sub_0803DD88`, `sub_0803DDB0`, `sub_0803DDD8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 111/633 linked)
- Functions: `sub_080433F4`, `sub_080608D4`, `sub_08068558`, `sub_0806FDB4`, `sub_08072CC0`, `sub_0802E1EC`, `sub_08044D8C`, `sub_080475C4`, `sub_080475F4`, `sub_08071FAC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 121/633 linked)
- Functions: `sub_08033C1C`, `sub_0803484C`, `sub_08034FF8`, `sub_080361A8`, `sub_080428C4`, `sub_080604A4`, `sub_08060798`, `sub_080615EC`, `sub_0806EE24`, `sub_08033E3C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 131/633 linked)
- Functions: `sub_08034360`, `sub_08034FBC`, `sub_080447CC`, `sub_08062960`, `sub_08070C98`, `sub_08071FC8`, `sub_08073078`, `sub_0807339C`, `sub_0802D898`, `sub_08035908`
- make compare: OK

### 2026-09-17 — match_batch (+10, 141/633 linked)
- Functions: `sub_08042B28`, `sub_08042B50`, `sub_08044EE8`, `sub_08048D0C`, `sub_08050864`, `sub_080538A0`, `sub_08054108`, `sub_08056380`, `sub_08056AF0`, `sub_080626B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 151/633 linked)
- Functions: `sub_0806BE20`, `sub_0806FEFC`, `sub_08073184`, `sub_080731F4`, `sub_080739E8`, `sub_0802B930`, `sub_0803DCFC`, `sub_080405E8`, `sub_08045A84`, `sub_080720F0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 161/633 linked)
- Functions: `sub_0802BA4C`, `sub_0802E210`, `sub_080312B0`, `sub_080408C4`, `sub_08047594`, `sub_080628B4`, `sub_08062CC8`, `sub_080686B4`, `sub_0806FF28`, `sub_0802EECC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 171/633 linked)
- Functions: `sub_0802FD80`, `sub_08031124`, `sub_0803E440`, `sub_080400D4`, `sub_08040618`, `sub_08041394`, `sub_08041980`, `sub_08043944`, `sub_08043B58`, `sub_0804495C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 181/633 linked)
- Functions: `sub_08059C6C`, `sub_080611F0`, `sub_08062238`, `sub_08062D24`, `sub_080703FC`, `sub_08070AD4`, `sub_08070DF4`, `sub_08034788`, `sub_080347E4`, `sub_08035238`
- make compare: OK

### 2026-09-17 — match_batch (+10, 191/633 linked)
- Functions: `sub_080361CC`, `sub_08054558`, `sub_08061308`, `sub_08061BAC`, `sub_08062044`, `sub_08062CF4`, `sub_0806DEC8`, `sub_0806EBF8`, `sub_0806F430`, `sub_080733BC`
- make compare: OK

### 2026-09-17 — match_batch (+10, 201/633 linked)
- Functions: `sub_0802B994`, `sub_0802E18C`, `sub_080320CC`, `sub_08033158`, `sub_08041858`, `sub_08060D28`, `sub_08062D50`, `sub_080674BC`, `sub_08069908`, `sub_08069948`
- make compare: OK

### 2026-09-17 — match_batch (+10, 211/633 linked)
- Functions: `sub_08069988`, `sub_080735B0`, `sub_080405A8`, `sub_0804BE80`, `sub_0804CA30`, `sub_0804D58C`, `sub_0805DA70`, `sub_08060220`, `sub_0806105C`, `sub_08062068`
- make compare: OK

### 2026-09-17 — match_batch (+10, 221/633 linked)
- Functions: `sub_08066BC4`, `sub_08067F98`, `sub_0806A580`, `sub_08070678`, `sub_08031368`, `sub_08042B78`, `sub_08042BB0`, `sub_08042C3C`, `sub_0806013C`, `sub_080603A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 231/633 linked)
- Functions: `sub_08061C48`, `sub_08062AC0`, `sub_0806D748`, `sub_080330F4`, `sub_08035020`, `sub_0805D1AC`, `sub_080699C8`, `sub_0806F174`, `sub_080726E0`, `sub_0802C62C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 241/633 linked)
- Functions: `sub_08030F00`, `sub_0803DBD0`, `sub_08059D08`, `sub_08060468`, `sub_080617C4`, `sub_080310F0`, `sub_0803A1E4`, `sub_08040088`, `sub_08066BF0`, `sub_08071F44`
- make compare: OK

### 2026-09-17 — match_batch (+10, 251/633 linked)
- Functions: `sub_080302A8`, `sub_08033F48`, `sub_08035204`, `sub_08060758`, `sub_08062758`, `sub_08068808`, `sub_0806B724`, `sub_0806F1A0`, `sub_08071E44`, `sub_0803C6B8`
- make compare: OK

### 2026-09-17 — match_batch (+10, 261/633 linked)
- Functions: `sub_08045AA8`, `sub_08046230`, `sub_0806209C`, `sub_08066AD4`, `sub_08069A18`, `sub_080712CC`, `sub_08071E04`, `sub_08038638`, `sub_08043BDC`, `sub_080603E0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 271/633 linked)
- Functions: `sub_080726A4`, `sub_0802B95C`, `sub_0803403C`, `sub_08034810`, `sub_08034894`, `sub_08033530`, `sub_0803E328`, `sub_0803E374`, `sub_0803E3C0`, `sub_08041348`
- make compare: OK

### 2026-09-17 — match_batch (+10, 281/633 linked)
- Functions: `sub_08043B90`, `sub_08045128`, `sub_08059DC8`, `sub_080618A8`, `sub_08061DC0`, `sub_08073218`, `sub_0803593C`, `sub_08043ADC`, `sub_08054454`, `sub_080611A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 291/633 linked)
- Functions: `sub_08062A74`, `sub_08063104`, `sub_0806D958`, `sub_08071B4C`, `sub_0802C5DC`, `sub_08033574`, `sub_08033EA4`, `sub_080385DC`, `sub_0803E258`, `sub_0803FDD0`
- make compare: OK

### 2026-09-17 — match_batch (+10, 301/633 linked)
- Functions: `sub_08062C38`, `sub_08073A28`, `sub_0802E1B4`, `sub_08033A5C`, `sub_08041F88`, `sub_080424E8`, `sub_080435D8`, `sub_08061800`, `sub_080620D4`, `sub_08062B9C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 311/633 linked)
- Functions: `sub_08062BF0`, `sub_08033D90`, `sub_08040EF4`, `sub_080449C4`, `sub_08044A20`, `sub_0806F8C4`, `sub_08073440`, `sub_08073568`, `sub_0802C6AC`, `sub_08035884`
- make compare: OK

### 2026-09-17 — match_batch (+10, 321/633 linked)
- Functions: `sub_08035D1C`, `sub_08042BE8`, `sub_08044F64`, `sub_08046278`, `sub_08052934`, `sub_08062C80`, `sub_080680CC`, `sub_08057234`, `sub_0806C78C`, `sub_0803D4C4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 331/633 linked)
- Functions: `sub_08042F4C`, `sub_0804745C`, `sub_0805D99C`, `sub_08061D68`, `sub_08062640`, `sub_080677A8`, `sub_08043C28`, `sub_0806114C`, `sub_08067FC8`, `sub_08068020`
- make compare: OK

### 2026-09-17 — match_batch (+10, 341/633 linked)
- Functions: `sub_0806B3E8`, `sub_08038580`, `sub_08041DB4`, `sub_08061BE8`, `sub_08031300`, `sub_08033084`, `sub_08038D10`, `sub_0803E1F4`, `sub_0807179C`, `sub_0802D52C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 351/633 linked)
- Functions: `sub_0803413C`, `sub_08042784`, `sub_0806184C`, `sub_08071E84`, `sub_08071EE4`, `sub_0802C2B0`, `sub_08030938`, `sub_08033878`, `sub_080601C4`, `sub_080733E4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 361/633 linked)
- Functions: `sub_08042390`, `sub_08070604`, `sub_08073988`, `sub_08042718`, `sub_080473F8`, `sub_08067504`, `sub_0802D2C0`, `sub_08065560`, `sub_08069DBC`, `sub_08073114`
- make compare: OK

### 2026-09-17 — match_batch (+10, 371/633 linked)
- Functions: `sub_080338F0`, `sub_08042630`, `sub_08069894`, `sub_080426A4`, `sub_0805264C`, `sub_08052FC8`, `sub_080604C8`, `sub_08067F3C`, `sub_0802F520`, `sub_08042540`
- make compare: OK

### 2026-09-17 — match_batch (+10, 381/633 linked)
- Functions: `sub_080425B8`, `sub_08045C5C`, `sub_08059B74`, `sub_08061D00`, `sub_08031094`, `sub_08059AE0`, `sub_0802BC14`, `sub_08038D68`, `sub_080392D0`, `sub_08041E14`
- make compare: OK

### 2026-09-17 — match_batch (+10, 391/633 linked)
- Functions: `sub_08051BBC`, `sub_080610A8`, `sub_0806171C`, `sub_08071BA0`, `sub_08043638`, `sub_08065E0C`, `sub_08068798`, `sub_08070468`, `sub_0802E2F8`, `sub_08032D5C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 401/633 linked)
- Functions: `sub_0803E2AC`, `sub_0804737C`, `sub_080607BC`, `sub_08068118`, `sub_08036264`, `sub_080462D4`, `sub_08059C98`, `sub_08061AB8`, `sub_08038314`, `sub_0804B4B4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 411/633 linked)
- Functions: `sub_0804C324`, `sub_0804CED4`, `sub_08066224`, `sub_0806FDD0`, `sub_0807309C`, `sub_0803559C`, `sub_080360BC`, `sub_08061E8C`, `sub_08068E54`, `sub_08033DD4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 421/633 linked)
- Functions: `sub_08037318`, `sub_0806BC0C`, `sub_0806FE84`, `sub_08073910`, `sub_08034A68`, `sub_08035624`, `sub_0804A4E0`, `sub_0806A434`, `sub_0806B064`, `sub_0802C55C`
- make compare: OK

### 2026-09-17 — match_batch (+10, 431/633 linked)
- Functions: `sub_0804AC3C`, `sub_0803E934`, `sub_0806A314`, `sub_0802BF04`, `sub_08062988`, `sub_0806A3A4`, `sub_08041C8C`, `sub_08048168`, `sub_08051504`, `sub_080523A4`
- make compare: OK

### 2026-09-17 — match_batch (+10, 441/633 linked)
- Functions: `sub_0806EE48`, `sub_08061564`, `sub_08062F90`, `sub_080691E4`, `sub_08031204`, `sub_08031C98`, `sub_08041774`, `sub_0804245C`, `sub_08068988`, `sub_080442FC`
- make compare: OK
