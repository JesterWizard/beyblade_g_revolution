# Function scores

_Auto-generated. Do not edit. Refresh with `python3 tools/decomp/function_scores.py --write` or `make progress`._

_Updated: 2026-09-21T15:09:48Z_

## Legend

| Status | Meaning | Counted as decompiled? |
|--------|---------|------------------------|
| **matched** | Semantic C, `match_function.py` MATCH, integrated | yes |
| **byte-identical DIFF** | Same size as retail; remaining diffs are only unresolved pool/reloc words | **no** |
| **same-size DIFF** | Same size, instruction bytes differ | no |
| **size DIFF** | Compiled length ≠ retail | no |
| **not started** | Readable Thumb, no C attempt recorded | no |
| **WIP (parked C)** | Unmatched draft in [`src/wip/`](../src/wip/README.md) — resume, do not restart | no |
| **blocked** | Documented in [`decomp-queue.toml`](decomp-queue.toml) | no |

Score is **matched bytes / retail bytes** (e.g. `68/70`). Completion % is that ratio. A function that compiles to the same bytes *except* a literal-pool address is **byte-identical DIFF**, not matched.

## Summary

| Status | Count |
|--------|------:|
| matched | 360 |
| byte-identical DIFF | 0 |
| same-size DIFF | 1 |
| size DIFF | 2 |
| WIP (parked C) | 152 |
| not started | 108 |
| blocked | 10 |
| **total** | **633** |

## Close / attempted

| Function | Status | % | Bytes | Note |
|----------|--------|--:|------:|------|
| `sub_08073988` | WIP (parked C) | 97.9% | 94/96 | 94/96; table constant lands in r2, retail materialises it in the free r0. Re-… |
| `sub_08040F4C` | WIP (parked C) | 94.9% | 319/336 | 319/336; done in r4 vs r5 |
| `sub_080442FC` | WIP (parked C) | 93.1% | 134/144 | 134/144; a in r4 vs r5 (gData symbols fixed pool fold) |
| `sub_08069894` | WIP (parked C) | 88.5% | 85/96 | 85/96; IWRAM stores preloaded vs sequential |
| `sub_08043B58` | WIP (parked C) | 87.0% | 47/54 | permuter 300 s + 900 s, no score 0 (45 → 20); 47/54 same-size |
| `sub_08071B4C` | WIP (parked C) | 86.9% | 73/84 | permuter 300 s + 900 s, no score 0 (335 → 5); 73/84 |
| `sub_08066224` | WIP (parked C) | 85.7% | 96/112 | permuter 300 s + 900 s, no score 0 (110 → 55); 96/112 |
| `sub_08034A68` | WIP (parked C) | 81.2% | 91/112 | permuter 300 s + 900 s, no score 0 (130 → 110); 91/112 |
| `sub_0806B3E8` | WIP (parked C) | 79.8% | 67/84 | permuter 300 s + 900 s, no score 0 (95 → 10); 67/84 |
| `sub_08070604` | WIP (parked C) | 79.3% | 73/92 | permuter 300 s, no score 0 (140 → 10); 73/92 |
| `sub_0803DDB0` | WIP (parked C) | 77.5% | 31/40 | 31/40 same-size (old_agbcc); idx_var form |
| `sub_0803DDD8` | WIP (parked C) | 77.5% | 31/40 | 31/40 same-size (old_agbcc); idx_var form |
| `sub_08035984` | WIP (parked C) | 66.7% | 232/348 | direct seed 232/348 (344B) retained. Loading both velocities before squaring … |
| `sub_08033C1C` | WIP (parked C) | 65.6% | 21/32 | matched only with GCC asm labels; stripped DIFF |
| `sub_080361A8` | WIP (parked C) | 63.9% | 23/36 | matched only with GCC asm labels; stripped DIFF |
| `sub_080523A4` | WIP (parked C) | 63.4% | 71/112 | matched only with GCC asm labels; stripped DIFF |
| `sub_08032DC4` | WIP (parked C) | 63.3% | 418/660 | 418/660 (656B); arg copies now state_a, state_b, frame. Remaining 4-byte shor… |
| `sub_08032908` | WIP (parked C) | 61.2% | 235/384 | three attempts: 151/384 (388B), 235/384 (388B) retained; loc-pin rewrite 114/… |
| `sub_08071E84` | WIP (parked C) | 60.4% | 58/96 | 58/96 same-size; gData symbols + while(count != -1); permuter 300s best 360 (… |
| `sub_08071EE4` | WIP (parked C) | 60.4% | 58/96 | 58/96 same-size; gData symbols + while(count != -1); permuter 300s best 360 (… |
| `sub_08052934` | WIP (parked C) | 58.3% | 49/84 | matched only with GCC asm labels; stripped DIFF |
| `sub_0804495C` | WIP (parked C) | 56.7% | 34/60 | matched only with GCC asm labels; stripped DIFF |
| `sub_080348E8` | WIP (parked C) | 54.2% | 208/384 | two semantic attempts: 208/384 same-size first draft; second fixed-register a… |
| `sub_0803E2AC` | WIP (parked C) | 54.0% | 67/124 then 72/124 | Two semantic attempts are same-size but differ in table literal/index schedul… |
| `sub_08061800` | WIP (parked C) | 53.9% | 41/76 | 41/76 bytes (53.9%), same size; correctly identified _08073C4C as a 'bx r3' t… |
| `sub_0803E374` | WIP (parked C) | 52.6% | 40/76 | 40/76 same-size DIFF; cloned signed table lookup matches size and most arithm… |
| `sub_0803E3C0` | WIP (parked C) | 52.6% | 40/76 | 40/76 same-size DIFF; clone table offsets +2 are correct, but agbcc retains t… |
| `sub_0802BC14` | WIP (parked C) | 51.8% | 58/112 | same-size DIFF (58/112, 51.8%) after signed-call and r0-pointer hints; remain… |
| `sub_08061DC0` | WIP (parked C) | 50.0% | 36/72 | 36/72 bytes (50%), same size; correct algorithm (bx-r3 trampoline _08073C4C c… |
| `sub_080473F8` | WIP (parked C) | 50.0% | 50/100 | 50/100 bytes (50%); semantically correct but agbcc emits 'subs r1,#8' peephol… |
| `sub_0802E048` | WIP (parked C) | 49.1% | 112/228 | matched only with GCC asm labels; stripped DIFF |
| `sub_08065560` | WIP (parked C) | 48.3% | 58/120 then 66/120 | Two attempts: semantic switch/loop 58/120 (116B), then r2/r1/r3/r4/r5 registe… |
| `sub_08043B90` | WIP (parked C) | 47.4% | 36/76 | matched only with GCC asm labels; stripped DIFF |
| `sub_08061D00` | WIP (parked C) | 47.1% | 49/104 then 23/104 | Two same-size attempts: direct semantic C 49/104, then r2/r4/r5 register anch… |
| `sub_08056F84` | WIP (parked C) | 47.0% | 79/168 then 76/168 | Two semantic attempts: direct fields 79/168 (172B), then saved main-location … |
| `sub_080610A8` | WIP (parked C) | 46.9% | 46/98 then 73/98 | Two semantic attempts: if-chain 46/98 (96B), then switch with unsigned half-s… |
| `sub_08062AF8` | WIP (parked C) | 46.9% | 76/162 then 27/162 | Two semantic attempts: indexed loops 76/162 (160B), then r2/r3/r4/r5 anchors … |
| `sub_08035C64` | WIP (parked C) | 46.7% | 85/182 | same_size DIFF 85/182 (46.7%); logic fully correct (repulsion physics on Unk3… |
| `sub_08035AE0` | WIP (parked C) | 46.1% | 179/388 | Collision/overlap response semantics reconstructed: squared separation thresh… |
| `sub_08047624` | WIP (parked C) | 46.0% | 80/174 | matched only with GCC asm labels; stripped DIFF |
| `sub_0802C55C` | WIP (parked C) | 45.3% | 58/128 | two attempts did not match; 58/128 bytes, final candidate 124B; semantics map… |
| `sub_0806EE48` | WIP (parked C) | 45.2% | 56/124 then 120/124 | Two semantic attempts: direct dispatcher 56/124 (132B), then flag_ptr pinned … |
| `sub_08042BE8` | WIP (parked C) | 45.1% | 37/82 | best 37/82 size-mismatch; explicit r4/r5/r6/r7/r3/r2 shaping reproduces the l… |
| `sub_08062B9C` | WIP (parked C) | 44.7% | 34/76 | 34/76 bytes (44.7%), same size; correct algorithm (clear bitmask bit + slot p… |
| `sub_0804AAF0` | WIP (parked C) | 43.7% | 145/332 then 151/332 | Two semantic attempts: initial 145/332 (324B), then early current-global addr… |
| `sub_0802D2C0` | WIP (parked C) | 42.6% | 46/108 | DIFF; corrected retail branch semantics, but best current compile is 46/108 a… |
| `sub_08042F4C` | WIP (parked C) | 41.2% | 33/80 | 33/80 size-mismatch; row update and six-argument notification logic are corre… |
| `sub_08069B78` | WIP (parked C) | 40.3% | 62/154 | same-size DIFF 62/154 (40.3%); shared mask/inverse and r10/r5 hints did not i… |
| `sub_0806BC0C` | WIP (parked C) | 39.7% | 46/116 then 43/116 | Two semantic attempts: direct bounded index loop 46/116 (104B), then an expli… |
| `sub_0802BF04` | WIP (parked C) | 39.3% | 55/140 | best 55/140 size-mismatch; s16 comparison and explicit r8 zero-register hints… |
| `sub_08037430` | WIP (parked C) | 38.9% | 84/216 | matched only with GCC asm labels; stripped DIFF |
| `sub_08040EF4` | WIP (parked C) | 38.6% | 34/88 | best 34/88 size-mismatch after raw offset and full register pins; baseline wa… |
| `sub_08057274` | WIP (parked C) | 38.5% | 80/208 then 81/208 | Two semantic attempts: direct MainWork switch 80/208 (204B), then r4 main-loc… |
| `sub_08069F00` | same-size DIFF | 37.5% | 9/24 |  |
| `sub_08059DC8` | WIP (parked C) | 37.5% | 27/72 | 27/72 bytes (37.5%); this is a state-machine dispatcher that calls a fixed bx… |
| `sub_08067504` | WIP (parked C) | 37.5% | 48/128 then 60/128 | Two semantic attempts: direct volatile-register C 48/128 (120B), then explici… |
| `sub_080302E0` | WIP (parked C) | 37.5% | 63/168 | two semantic attempts: 66/168 size_mismatch (148B), then 63/168 size_mismatch… |
| `sub_08067BB8` | WIP (parked C) | 37.2% | 113/304 then 44/304 | Two semantic constructor attempts: structured field initialization reached 11… |
| `sub_08068798` | WIP (parked C) | 36.4% | 40/110 then 70/110 | Two semantic attempts: initial queue model 40/110 (116B), then pinned offset/… |
| `sub_0803E848` | WIP (parked C) | 36.2% | 58/160 then 56/160 | Two semantic attempts remained size-mismatched: 58/160 (176B) and 56/160 (168… |
| `sub_08066FB8` | WIP (parked C) | 33.7% | 101/300 then 93/300 | Two semantic attempts: direct renderer 101/300 (304B), then r4/r5/r6 register… |
| `sub_080674A4` | WIP (parked C) | 33.3% | 2/6 | matched only with GCC asm labels; stripped DIFF |
| `sub_08062068` | WIP (parked C) | 33.3% | 16/48 | 16/48 bytes (28.6%), size mismatch (56 vs 48); correct algorithm (3-way selec… |
| `sub_08038D68` | WIP (parked C) | 33.0% | 37/112 | two attempts: direct semantic seed 15/112 (108B); pinned base/table registers… |
| `sub_08070468` | WIP (parked C) | 32.5% | 37/114 | Two attempts: the semantic sorted-list reposition candidate reached 37/114 (1… |
| `sub_08032604` | WIP (parked C) | 32.1% | 63/196 | Battle initialization semantics mapped (resource creation, display setup, tra… |
| `sub_080333E4` | WIP (parked C) | 30.9% | 84/272 | Mode resource initializer semantics reconstructed; second candidate reached e… |
| `sub_0804AC3C` | WIP (parked C) | 30.8% | 32/104 then 38/104 | Two attempts: semantic seed 32/104 (96B), then r6/r5/r4 register-pinned data/… |
| `sub_0805264C` | WIP (parked C) | 30.2% | 29/96 then 9/96 | Two semantic attempts after correcting the existing prototype: struct-table l… |
| `sub_08068988` | WIP (parked C) | 29.4% | 37/126 then 124/126 | Two semantic attempts: initial ABI call shape 37/126 (128B), then passed thro… |
| `sub_0803139C` | WIP (parked C) | 29.4% | 103/350 | Resource-list digit allocator/cleanup semantics reconstructed, reaching 103/3… |
| `sub_0803DBD0` | WIP (parked C) | 28.8% | 23/80 | matched only with GCC asm labels; stripped DIFF |
| `sub_08062D50` | WIP (parked C) | 28.3% | 13/46 | 13/46 bytes (28.3%), same size; correct algorithm (write a BGR555 palette ent… |
| `sub_08070354` | WIP (parked C) | 28.0% | 47/168 | Semantic object/flag updater reconstructed. Final verified attempt reached 47… |
| `sub_0806E7BC` | WIP (parked C) | 27.6% | 42/152 | size_mismatch 42/152 (27.6%), compiled 148B vs retail 152B; attempted as line… |
| `sub_0806FE84` | WIP (parked C) | 27.5% | 33/120 | Two attempts (the first run returned no status, then the retry) reached 33/12… |
| `sub_080429CC` | WIP (parked C) | 27.3% | 84/308 then 91/308 | Two attempts: local pointer seed 84/308 (288B), then r1/r2 pointer pins 91/30… |
| `sub_08071F44` | WIP (parked C) | 26.6% | 17/64 | sub_08071F44 |
| `sub_0806A314` | WIP (parked C) | 26.4% | 38/144 then 40/144 | Two semantic attempts: direct allocator/linked-list wrapper 38/144 (same size… |
| `sub_08038580` | WIP (parked C) | 26.1% | 24/92 | best 24/92 same-size DIFF; logic and size are correct, but baseline uses dst … |
| `sub_08069DBC` | WIP (parked C) | 26.0% | 25/96 then 63/96 | Two semantic attempts: direct tiled copy 25/96, then deferred shift load and … |
| `sub_0802C2B0` | WIP (parked C) | 26.0% | 26/100 | size mismatch; 26/100 bytes, compiled 92 vs retail 100; literal-pool/register… |
| `sub_080444BC` | WIP (parked C) | 24.7% | 98/396 then 90/396 | Two attempts: semantic resource setup seed 98/396 (368B), then r6 MainWork pi… |
| `sub_0802C3DC` | WIP (parked C) | 23.2% | 46/198 | size mismatch; 46/198 bytes, compiled 192 vs retail 198; sibling lookup logic… |
| `sub_08034420` | WIP (parked C) | 23.2% | 76/328 | 76/328 same-size; prologue matches (r6 out, r7 state_a, r8 unk2D0). Remaining… |
| `sub_0803DCFC` | WIP (parked C) | 22.9% | 11/48 | 11/48 same-size DIFF; index pinning and explicit goto preserved size, but ret… |
| `sub_080385DC` | WIP (parked C) | 22.5% | 18/80 | same_size DIFF 18/80; shared masks and r12/r6/r1 pointer/register hints did n… |
| `sub_0802DCDC` | WIP (parked C) | 22.1% | 100/452 | size mismatch; 100/452 bytes, compiled 428 vs retail 452; direct semantic con… |
| `sub_08041E14` | WIP (parked C) | 21.9% | 25/114 then 78/114 | Two semantic attempts: baseline 25/114 (104B), then retail register-pinned ar… |
| `sub_080617C4` | WIP (parked C) | 21.7% | 13/60 | matched only with GCC asm labels; stripped DIFF |
| `sub_08068118` | WIP (parked C) | 21.6% | 22/102 then 9/102 | Two semantic attempts: initial table/branch model 22/102 (116B), then correct… |
| `sub_08071BA0` | WIP (parked C) | 21.6% | 32/148 | matched only with GCC asm labels; stripped DIFF |
| `sub_0803D51C` | WIP (parked C) | 20.7% | 63/304 then 38/304 | Two same-size attempts did not match: direct semantic seed compiled 288/304 w… |
| `sub_0803559C` | WIP (parked C) | 20.4% | 22/108 | two attempts: 21/108 direct nested shape (104B), then 22/108 same-size with e… |
| `sub_080607BC` | WIP (parked C) | 20.3% | 26/128 then 36/128 | Two semantic attempts: direct typed state 26/128 (same size), then r2/r3/r4/r… |
| `sub_0802C314` | WIP (parked C) | 20.2% | 40/198 | size mismatch; 40/198 bytes, compiled 196 vs retail 198; lookup logic is mapp… |
| `sub_08051BBC` | WIP (parked C) | 19.4% | 24/124 then 26/124 | Two semantic attempts: direct field/volatile loop 24/124 (144B), then pinned … |
| `sub_080338F0` | WIP (parked C) | 19.2% | 20/104 | same_size DIFF, 20/104 bytes (19.2%) — structural rewrite needed, indexing bu… |
| `sub_080415FC` | WIP (parked C) | 19.0% | 38/200 then 127/200 | Two semantic attempts: cached-main/state seed 38/200 (180B), direct state-add… |
| `sub_0806A434` | WIP (parked C) | 18.9% | 31/164 then 29/164 | Two semantic attempts: register-pinned key version 31/164 (156B), then normal… |
| `sub_0804438C` | WIP (parked C) | 18.4% | 56/304 then 54/304 | Two semantic attempts: baseline 56/304 (292B), then signed value plus r5 DISP… |
| `sub_08043420` | WIP (parked C) | 18.0% | 79/438 then 79/438 | Two semantic attempts both 79/438 (448B): explicit state local and direct swi… |
| `sub_08038F30` | WIP (parked C) | 17.7% | 56/316 | two attempts: direct loop/if seed 32/316 (304B); goto plus r5/r6/r7 register … |
| `sub_0803DD88` | WIP (parked C) | 17.5% | 7/40 | matched only with GCC asm labels; stripped DIFF |
| `sub_08035624` | WIP (parked C) | 17.5% | 20/114 | two attempts: 20/114 bytes, 112B candidate both times; logic and fields match… |
| `sub_0806C78C` | WIP (parked C) | 17.1% | 12/70 | 12/70 bytes (17.1%), size mismatch (68 vs 70); partial model — calls sub_0806… |
| `sub_0806114C` | WIP (parked C) | 17.0% | 15/88 then 31/88 | Two attempts: explicit min/max locals 15/88 (100B), then direct parameter swa… |
| `sub_08035258` | WIP (parked C) | 16.8% | 33/196 | two semantic attempts: 21/196 bytes (192B) with a direct chain, then 33/196 b… |
| `sub_08062988` | WIP (parked C) | 16.4% | 23/140 then 32/140 | Two semantic attempts: unpinned field locals 23/140 (136B), then r1/r2/r3 reg… |
| `sub_080620D4` | WIP (parked C) | 15.8% | 12/72 | sub_080620D4 |
| `sub_08068E54` | WIP (parked C) | 15.7% | 17/108 then 70/108 | Two semantic attempts: direct motion model 17/108 (112B), then pinned state/x… |
| `sub_080733E4` | WIP (parked C) | 15.6% | 14/90 | size_mismatch 14/90 baseline; explicit-goto and r2/r5-pinned variants did not… |
| `sub_0802BAD4` | WIP (parked C) | 15.6% | 50/320 | Two semantic attempts. The final candidate reached 50/320 bytes (15.6%, 264B)… |
| `sub_0802DEA0` | WIP (parked C) | 15.6% | 66/424 | 66/424 bytes (15.6%), size mismatch (400 vs 424); correct algorithm fully der… |
| `sub_08030F38` | WIP (parked C) | 15.5% | 54/348 | Resource timer/update semantics reconstructed across the AF0/B00/B20/B40/B48 … |
| `sub_08061AB8` | WIP (parked C) | 15.0% | 18/120 then 50/120 | Two attempts: direct global C 18/120 same-size, then r4/r5/r6/r7 global ancho… |
| `sub_08061D68` | WIP (parked C) | 14.8% | 13/88 | 13/88 bytes (13.5%), size mismatch (96 vs 88); correct overall algorithm (mas… |
| `sub_0802C4A4` | WIP (parked C) | 14.8% | 27/182 | size mismatch; 27/182 bytes, compiled 152 vs retail 182; indexed lookup seman… |
| `sub_08067648` | WIP (parked C) | 14.2% | 50/352 then 50/352 | Two semantic attempts: approximate DMA/timing model 50/352 (260B), then enlar… |
| `sub_080677A8` | WIP (parked C) | 14.0% | 12/86 | 12/86 bytes (14%), size mismatch (80 vs 86); correct algorithm (bounds-check … |
| `sub_08056D68` | WIP (parked C) | 13.5% | 73/540 then 73/540 | Two semantic attempts (first after prototype correction, then after correctin… |
| `sub_08035468` | WIP (parked C) | 13.3% | 41/308 | Rotation/projection math reconstructed through both angle frames, depth corre… |
| `sub_0806D748` | WIP (parked C) | 13.0% | 6/46 | sub_0806D748 |
| `sub_08062F90` | WIP (parked C) | 12.8% | 19/148 then 33/148 | Two attempts: direct global C 19/148 (144B), then e0/d4 lifetime anchors 33/1… |
| `sub_08045EF0` | WIP (parked C) | 12.8% | 70/548 then 78/548 | Two attempts: semantic byte-state seed 70/548 (392B), then retail argument re… |
| `sub_080739E8` | size DIFF | 12.5% | 5/36 |  |
| `sub_08033978` | WIP (parked C) | 12.2% | 22/180 | matched only with GCC asm labels; stripped DIFF |
| `sub_08046278` | WIP (parked C) | 12.0% | 11/92 | logic OK; 11/92 (56B vs 92B); extra r8/r9 leaf spill |
| `sub_08030638` | WIP (parked C) | 11.6% | 31/268 | Semantic rotation transform reconstructed, but compiler shape is 244/268 afte… |
| `sub_080691E4` | WIP (parked C) | 10.9% | 15/138 then 20/138 | Two semantic attempts: direct mode switch 15/138 (128B), then exact two-step … |
| `sub_08031294` | WIP (parked C) | 10.7% | 3/28 | matched only with GCC asm labels; stripped DIFF |
| `sub_080411EC` | WIP (parked C) | 10.4% | 36/346 then 35/346 | Two semantic attempts failed to preserve the retail dispatcher shape: direct … |
| `sub_08033188` | WIP (parked C) | 10.4% | 63/604 | Input-transition routine semantics mapped (input snapshot/restore, two-frame … |
| `sub_080474AC` | WIP (parked C) | 10.3% | 24/232 then 25/232 | Two semantic attempts: local pool physics seed 24/232 (200B), then r3-pinned … |
| `sub_08031C98` | WIP (parked C) | 10.0% | 15/150 | two semantic attempts: 43/150 size_mismatch (148B), then 15/150 size_mismatch… |
| `sub_08066B10` | WIP (parked C) | 10.0% | 18/180 then 91/180 | Two attempts: u32 argument plus fixed registers 18/180 (192B), then u8 parame… |
| `sub_0802ECD8` | WIP (parked C) | 10.0% | 50/498 | two attempts did not match; 50/498 bytes, final compiled 416B; logic mapped b… |
| `sub_08045D3C` | WIP (parked C) | 9.9% | 43/436 then 81/436 | Two attempts: readable semantic seed 43/436 (332B), then switch plus r2/r4/r3… |
| `sub_08035D68` | WIP (parked C) | 9.7% | 19/196 | Rotation/projection helper semantics reconstructed: table sine/cosine lookup,… |
| `sub_08068598` | WIP (parked C) | 9.5% | 27/284 then 20/284 | Two semantic attempts: initial playback model 27/284 (288B), then explicit r2… |
| `sub_08035054` | WIP (parked C) | 9.5% | 41/432 | Resource mode dispatcher semantics mapped for kinds 0/1/2 (asset allocation, … |
| `sub_0802FA94` | WIP (parked C) | 8.7% | 65/748 | two attempts did not match; 65/748 bytes, final compiled 580B; loop semantics… |
| `sub_0804A028` | WIP (parked C) | 8.6% | 15/174 then 55/174 | Two semantic attempts: wrong-offset seed 15/174, corrected-offset render sequ… |
| `sub_08061564` | WIP (parked C) | 8.1% | 11/136 then 9/136 | Two semantic attempts: switch-based C 11/136 (144B), then explicit branch/got… |
| `sub_0804188C` | WIP (parked C) | 7.8% | 19/244 then 41/244 | Two semantic attempts failed to reproduce the fixed-point table walk: direct … |
| `sub_08031300` | WIP (parked C) | 7.7% | 6/78 | matched only with GCC asm labels; stripped DIFF |
| `sub_0803114C` | WIP (parked C) | 7.1% | 13/184 | Entry-position initialization semantics reconstructed with both direction bra… |
| `sub_0805E044` | WIP (parked C) | 7.0% | 16/228 then 15/228 | Two semantic attempts: typed table-pointer loop 16/228 (212B), then explicit … |
| `sub_080436B0` | WIP (parked C) | 7.0% | 46/658 then 85/658 | Two semantic attempts failed: structured local seed 46/658 (616B), then fixed… |
| `sub_0806A3A4` | WIP (parked C) | 6.9% | 10/144 | matched only with GCC asm labels; stripped DIFF |
| `sub_0806FDD0` | WIP (parked C) | 6.2% | 8/128 then 21/128 | Two semantic attempts: sorted-list insertion model 8/128 (120B), then correct… |
| `sub_08067584` | WIP (parked C) | 6.2% | 11/176 then 41/176 | Two semantic attempts: stack-array loops 11/176 (168B), then register anchors… |
| `sub_0803370C` | WIP (parked C) | 5.8% | 21/362 | Battle animation-position update semantics reconstructed (timer/counter, reso… |
| `sub_08033F30` | size DIFF | 3.6% | 1/24 |  |
| `sub_0802E2F8` | WIP (parked C) | 3.6% | 4/110 | two attempts did not match; 4/110 bytes, final pinned candidate 116B; table a… |

## All 633 functions

| Function | Address | Status | % | Bytes | Kind |
|----------|---------|--------|--:|------:|------|
| `sub_08073988` | `0x08073988` | WIP (parked C) | 97.9% | 94/96 | asm |
| `sub_08040F4C` | `0x08040F4C` | WIP (parked C) | 94.9% | 319/336 | asm |
| `sub_080442FC` | `0x080442FC` | WIP (parked C) | 93.1% | 134/144 | asm |
| `sub_08069894` | `0x08069894` | WIP (parked C) | 88.5% | 85/96 | asm |
| `sub_08043B58` | `0x08043B58` | WIP (parked C) | 87.0% | 47/54 | asm |
| `sub_08071B4C` | `0x08071B4C` | WIP (parked C) | 86.9% | 73/84 | asm |
| `sub_08066224` | `0x08066224` | WIP (parked C) | 85.7% | 96/112 | asm |
| `sub_08034A68` | `0x08034A68` | WIP (parked C) | 81.2% | 91/112 | asm |
| `sub_0806B3E8` | `0x0806B3E8` | WIP (parked C) | 79.8% | 67/84 | asm |
| `sub_08070604` | `0x08070604` | WIP (parked C) | 79.3% | 73/92 | asm |
| `sub_0803DDB0` | `0x0803DDB0` | WIP (parked C) | 77.5% | 31/40 | asm |
| `sub_0803DDD8` | `0x0803DDD8` | WIP (parked C) | 77.5% | 31/40 | asm |
| `sub_08035984` | `0x08035984` | WIP (parked C) | 66.7% | 232/348 | asm |
| `sub_08033C1C` | `0x08033C1C` | WIP (parked C) | 65.6% | 21/32 | asm |
| `sub_080361A8` | `0x080361A8` | WIP (parked C) | 63.9% | 23/36 | asm |
| `sub_080523A4` | `0x080523A4` | WIP (parked C) | 63.4% | 71/112 | asm |
| `sub_08032DC4` | `0x08032DC4` | WIP (parked C) | 63.3% | 418/660 | asm |
| `sub_08032908` | `0x08032908` | WIP (parked C) | 61.2% | 235/384 | asm |
| `sub_08071E84` | `0x08071E84` | WIP (parked C) | 60.4% | 58/96 | asm |
| `sub_08071EE4` | `0x08071EE4` | WIP (parked C) | 60.4% | 58/96 | asm |
| `sub_08052934` | `0x08052934` | WIP (parked C) | 58.3% | 49/84 | asm |
| `sub_0804495C` | `0x0804495C` | WIP (parked C) | 56.7% | 34/60 | asm |
| `sub_080348E8` | `0x080348E8` | WIP (parked C) | 54.2% | 208/384 | asm |
| `sub_0803E2AC` | `0x0803E2AC` | WIP (parked C) | 54.0% | 67/124 then 72/124 | asm |
| `sub_08061800` | `0x08061800` | WIP (parked C) | 53.9% | 41/76 | asm |
| `sub_0803E374` | `0x0803E374` | WIP (parked C) | 52.6% | 40/76 | asm |
| `sub_0803E3C0` | `0x0803E3C0` | WIP (parked C) | 52.6% | 40/76 | asm |
| `sub_0802BC14` | `0x0802BC14` | WIP (parked C) | 51.8% | 58/112 | asm |
| `sub_08061DC0` | `0x08061DC0` | WIP (parked C) | 50.0% | 36/72 | asm |
| `sub_080473F8` | `0x080473F8` | WIP (parked C) | 50.0% | 50/100 | asm |
| `sub_0802E048` | `0x0802E048` | WIP (parked C) | 49.1% | 112/228 | asm |
| `sub_08065560` | `0x08065560` | WIP (parked C) | 48.3% | 58/120 then 66/120 | asm |
| `sub_08043B90` | `0x08043B90` | WIP (parked C) | 47.4% | 36/76 | asm |
| `sub_08061D00` | `0x08061D00` | WIP (parked C) | 47.1% | 49/104 then 23/104 | asm |
| `sub_08056F84` | `0x08056F84` | WIP (parked C) | 47.0% | 79/168 then 76/168 | asm |
| `sub_080610A8` | `0x080610A8` | WIP (parked C) | 46.9% | 46/98 then 73/98 | asm |
| `sub_08062AF8` | `0x08062AF8` | WIP (parked C) | 46.9% | 76/162 then 27/162 | asm |
| `sub_08035C64` | `0x08035C64` | WIP (parked C) | 46.7% | 85/182 | asm |
| `sub_08035AE0` | `0x08035AE0` | WIP (parked C) | 46.1% | 179/388 | asm |
| `sub_08047624` | `0x08047624` | WIP (parked C) | 46.0% | 80/174 | asm |
| `sub_0802C55C` | `0x0802C55C` | WIP (parked C) | 45.3% | 58/128 | asm |
| `sub_0806EE48` | `0x0806EE48` | WIP (parked C) | 45.2% | 56/124 then 120/124 | asm |
| `sub_08042BE8` | `0x08042BE8` | WIP (parked C) | 45.1% | 37/82 | asm |
| `sub_08062B9C` | `0x08062B9C` | WIP (parked C) | 44.7% | 34/76 | asm |
| `sub_0804AAF0` | `0x0804AAF0` | WIP (parked C) | 43.7% | 145/332 then 151/332 | asm |
| `sub_0802D2C0` | `0x0802D2C0` | WIP (parked C) | 42.6% | 46/108 | asm |
| `sub_08042F4C` | `0x08042F4C` | WIP (parked C) | 41.2% | 33/80 | asm |
| `sub_08069B78` | `0x08069B78` | WIP (parked C) | 40.3% | 62/154 | asm |
| `sub_0806BC0C` | `0x0806BC0C` | WIP (parked C) | 39.7% | 46/116 then 43/116 | asm |
| `sub_0802BF04` | `0x0802BF04` | WIP (parked C) | 39.3% | 55/140 | asm |
| `sub_08037430` | `0x08037430` | WIP (parked C) | 38.9% | 84/216 | asm |
| `sub_08040EF4` | `0x08040EF4` | WIP (parked C) | 38.6% | 34/88 | asm |
| `sub_08057274` | `0x08057274` | WIP (parked C) | 38.5% | 80/208 then 81/208 | asm |
| `sub_08059DC8` | `0x08059DC8` | WIP (parked C) | 37.5% | 27/72 | asm |
| `sub_08067504` | `0x08067504` | WIP (parked C) | 37.5% | 48/128 then 60/128 | asm |
| `sub_080302E0` | `0x080302E0` | WIP (parked C) | 37.5% | 63/168 | asm |
| `sub_08067BB8` | `0x08067BB8` | WIP (parked C) | 37.2% | 113/304 then 44/304 | asm |
| `sub_08068798` | `0x08068798` | WIP (parked C) | 36.4% | 40/110 then 70/110 | asm |
| `sub_0803E848` | `0x0803E848` | WIP (parked C) | 36.2% | 58/160 then 56/160 | asm |
| `sub_08066FB8` | `0x08066FB8` | WIP (parked C) | 33.7% | 101/300 then 93/300 | asm |
| `sub_080674A4` | `0x080674A4` | WIP (parked C) | 33.3% | 2/6 | asm |
| `sub_08062068` | `0x08062068` | WIP (parked C) | 33.3% | 16/48 | asm |
| `sub_08038D68` | `0x08038D68` | WIP (parked C) | 33.0% | 37/112 | asm |
| `sub_08070468` | `0x08070468` | WIP (parked C) | 32.5% | 37/114 | asm |
| `sub_08032604` | `0x08032604` | WIP (parked C) | 32.1% | 63/196 | asm |
| `sub_080333E4` | `0x080333E4` | WIP (parked C) | 30.9% | 84/272 | asm |
| `sub_0804AC3C` | `0x0804AC3C` | WIP (parked C) | 30.8% | 32/104 then 38/104 | asm |
| `sub_0805264C` | `0x0805264C` | WIP (parked C) | 30.2% | 29/96 then 9/96 | asm |
| `sub_08068988` | `0x08068988` | WIP (parked C) | 29.4% | 37/126 then 124/126 | asm |
| `sub_0803139C` | `0x0803139C` | WIP (parked C) | 29.4% | 103/350 | asm |
| `sub_0803DBD0` | `0x0803DBD0` | WIP (parked C) | 28.8% | 23/80 | asm |
| `sub_08062D50` | `0x08062D50` | WIP (parked C) | 28.3% | 13/46 | asm |
| `sub_08070354` | `0x08070354` | WIP (parked C) | 28.0% | 47/168 | asm |
| `sub_0806E7BC` | `0x0806E7BC` | WIP (parked C) | 27.6% | 42/152 | asm |
| `sub_0806FE84` | `0x0806FE84` | WIP (parked C) | 27.5% | 33/120 | asm |
| `sub_080429CC` | `0x080429CC` | WIP (parked C) | 27.3% | 84/308 then 91/308 | asm |
| `sub_08071F44` | `0x08071F44` | WIP (parked C) | 26.6% | 17/64 | asm |
| `sub_0806A314` | `0x0806A314` | WIP (parked C) | 26.4% | 38/144 then 40/144 | asm |
| `sub_08038580` | `0x08038580` | WIP (parked C) | 26.1% | 24/92 | asm |
| `sub_08069DBC` | `0x08069DBC` | WIP (parked C) | 26.0% | 25/96 then 63/96 | asm |
| `sub_0802C2B0` | `0x0802C2B0` | WIP (parked C) | 26.0% | 26/100 | asm |
| `sub_080444BC` | `0x080444BC` | WIP (parked C) | 24.7% | 98/396 then 90/396 | asm |
| `sub_0802C3DC` | `0x0802C3DC` | WIP (parked C) | 23.2% | 46/198 | asm |
| `sub_08034420` | `0x08034420` | WIP (parked C) | 23.2% | 76/328 | asm |
| `sub_0803DCFC` | `0x0803DCFC` | WIP (parked C) | 22.9% | 11/48 | asm |
| `sub_080385DC` | `0x080385DC` | WIP (parked C) | 22.5% | 18/80 | asm |
| `sub_0802DCDC` | `0x0802DCDC` | WIP (parked C) | 22.1% | 100/452 | asm |
| `sub_08041E14` | `0x08041E14` | WIP (parked C) | 21.9% | 25/114 then 78/114 | asm |
| `sub_080617C4` | `0x080617C4` | WIP (parked C) | 21.7% | 13/60 | asm |
| `sub_08068118` | `0x08068118` | WIP (parked C) | 21.6% | 22/102 then 9/102 | asm |
| `sub_08071BA0` | `0x08071BA0` | WIP (parked C) | 21.6% | 32/148 | asm |
| `sub_0803D51C` | `0x0803D51C` | WIP (parked C) | 20.7% | 63/304 then 38/304 | asm |
| `sub_0803559C` | `0x0803559C` | WIP (parked C) | 20.4% | 22/108 | asm |
| `sub_080607BC` | `0x080607BC` | WIP (parked C) | 20.3% | 26/128 then 36/128 | asm |
| `sub_0802C314` | `0x0802C314` | WIP (parked C) | 20.2% | 40/198 | asm |
| `sub_08051BBC` | `0x08051BBC` | WIP (parked C) | 19.4% | 24/124 then 26/124 | asm |
| `sub_080338F0` | `0x080338F0` | WIP (parked C) | 19.2% | 20/104 | asm |
| `sub_080415FC` | `0x080415FC` | WIP (parked C) | 19.0% | 38/200 then 127/200 | asm |
| `sub_0806A434` | `0x0806A434` | WIP (parked C) | 18.9% | 31/164 then 29/164 | asm |
| `sub_0804438C` | `0x0804438C` | WIP (parked C) | 18.4% | 56/304 then 54/304 | asm |
| `sub_08043420` | `0x08043420` | WIP (parked C) | 18.0% | 79/438 then 79/438 | asm |
| `sub_08038F30` | `0x08038F30` | WIP (parked C) | 17.7% | 56/316 | asm |
| `sub_0803DD88` | `0x0803DD88` | WIP (parked C) | 17.5% | 7/40 | asm |
| `sub_08035624` | `0x08035624` | WIP (parked C) | 17.5% | 20/114 | asm |
| `sub_0806C78C` | `0x0806C78C` | WIP (parked C) | 17.1% | 12/70 | asm |
| `sub_0806114C` | `0x0806114C` | WIP (parked C) | 17.0% | 15/88 then 31/88 | asm |
| `sub_08035258` | `0x08035258` | WIP (parked C) | 16.8% | 33/196 | asm |
| `sub_08062988` | `0x08062988` | WIP (parked C) | 16.4% | 23/140 then 32/140 | asm |
| `sub_080620D4` | `0x080620D4` | WIP (parked C) | 15.8% | 12/72 | asm |
| `sub_08068E54` | `0x08068E54` | WIP (parked C) | 15.7% | 17/108 then 70/108 | asm |
| `sub_080733E4` | `0x080733E4` | WIP (parked C) | 15.6% | 14/90 | asm |
| `sub_0802BAD4` | `0x0802BAD4` | WIP (parked C) | 15.6% | 50/320 | asm |
| `sub_0802DEA0` | `0x0802DEA0` | WIP (parked C) | 15.6% | 66/424 | asm |
| `sub_08030F38` | `0x08030F38` | WIP (parked C) | 15.5% | 54/348 | asm |
| `sub_08061AB8` | `0x08061AB8` | WIP (parked C) | 15.0% | 18/120 then 50/120 | asm |
| `sub_08061D68` | `0x08061D68` | WIP (parked C) | 14.8% | 13/88 | asm |
| `sub_0802C4A4` | `0x0802C4A4` | WIP (parked C) | 14.8% | 27/182 | asm |
| `sub_08067648` | `0x08067648` | WIP (parked C) | 14.2% | 50/352 then 50/352 | asm |
| `sub_080677A8` | `0x080677A8` | WIP (parked C) | 14.0% | 12/86 | asm |
| `sub_08056D68` | `0x08056D68` | WIP (parked C) | 13.5% | 73/540 then 73/540 | asm |
| `sub_08035468` | `0x08035468` | WIP (parked C) | 13.3% | 41/308 | asm |
| `sub_0806D748` | `0x0806D748` | WIP (parked C) | 13.0% | 6/46 | asm |
| `sub_08062F90` | `0x08062F90` | WIP (parked C) | 12.8% | 19/148 then 33/148 | asm |
| `sub_08045EF0` | `0x08045EF0` | WIP (parked C) | 12.8% | 70/548 then 78/548 | asm |
| `sub_08033978` | `0x08033978` | WIP (parked C) | 12.2% | 22/180 | asm |
| `sub_08046278` | `0x08046278` | WIP (parked C) | 12.0% | 11/92 | asm |
| `sub_08030638` | `0x08030638` | WIP (parked C) | 11.6% | 31/268 | asm |
| `sub_080691E4` | `0x080691E4` | WIP (parked C) | 10.9% | 15/138 then 20/138 | asm |
| `sub_08031294` | `0x08031294` | WIP (parked C) | 10.7% | 3/28 | asm |
| `sub_080411EC` | `0x080411EC` | WIP (parked C) | 10.4% | 36/346 then 35/346 | asm |
| `sub_08033188` | `0x08033188` | WIP (parked C) | 10.4% | 63/604 | asm |
| `sub_080474AC` | `0x080474AC` | WIP (parked C) | 10.3% | 24/232 then 25/232 | asm |
| `sub_08031C98` | `0x08031C98` | WIP (parked C) | 10.0% | 15/150 | asm |
| `sub_08066B10` | `0x08066B10` | WIP (parked C) | 10.0% | 18/180 then 91/180 | asm |
| `sub_0802ECD8` | `0x0802ECD8` | WIP (parked C) | 10.0% | 50/498 | asm |
| `sub_08045D3C` | `0x08045D3C` | WIP (parked C) | 9.9% | 43/436 then 81/436 | asm |
| `sub_08035D68` | `0x08035D68` | WIP (parked C) | 9.7% | 19/196 | asm |
| `sub_08068598` | `0x08068598` | WIP (parked C) | 9.5% | 27/284 then 20/284 | asm |
| `sub_08035054` | `0x08035054` | WIP (parked C) | 9.5% | 41/432 | asm |
| `sub_0802FA94` | `0x0802FA94` | WIP (parked C) | 8.7% | 65/748 | asm |
| `sub_0804A028` | `0x0804A028` | WIP (parked C) | 8.6% | 15/174 then 55/174 | asm |
| `sub_08061564` | `0x08061564` | WIP (parked C) | 8.1% | 11/136 then 9/136 | asm |
| `sub_0804188C` | `0x0804188C` | WIP (parked C) | 7.8% | 19/244 then 41/244 | asm |
| `sub_08031300` | `0x08031300` | WIP (parked C) | 7.7% | 6/78 | asm |
| `sub_0803114C` | `0x0803114C` | WIP (parked C) | 7.1% | 13/184 | asm |
| `sub_0805E044` | `0x0805E044` | WIP (parked C) | 7.0% | 16/228 then 15/228 | asm |
| `sub_080436B0` | `0x080436B0` | WIP (parked C) | 7.0% | 46/658 then 85/658 | asm |
| `sub_0806A3A4` | `0x0806A3A4` | WIP (parked C) | 6.9% | 10/144 | asm |
| `sub_0806FDD0` | `0x0806FDD0` | WIP (parked C) | 6.2% | 8/128 then 21/128 | asm |
| `sub_08067584` | `0x08067584` | WIP (parked C) | 6.2% | 11/176 then 41/176 | asm |
| `sub_0803370C` | `0x0803370C` | WIP (parked C) | 5.8% | 21/362 | asm |
| `sub_0802E2F8` | `0x0802E2F8` | WIP (parked C) | 3.6% | 4/110 | asm |
| `sub_08069F00` | `0x08069F00` | same-size DIFF | 37.5% | 9/24 | asm |
| `sub_080739E8` | `0x080739E8` | size DIFF | 12.5% | 5/36 | asm |
| `sub_08033F30` | `0x08033F30` | size DIFF | 3.6% | 1/24 | asm |
| `sub_08035908` | `0x08035908` | not started | 0.0% | 0/36 | asm |
| `sub_0806BE20` | `0x0806BE20` | not started | 0.0% | 0/36 | asm |
| `sub_08033158` | `0x08033158` | not started | 0.0% | 0/46 | asm |
| `sub_080320CC` | `0x080320CC` | not started | 0.0% | 0/52 | asm |
| `sub_08035020` | `0x08035020` | not started | 0.0% | 0/52 | asm |
| `sub_08067FC8` | `0x08067FC8` | not started | 0.0% | 0/74 | asm |
| `sub_080699C8` | `0x080699C8` | not started | 0.0% | 0/80 | asm |
| `sub_08065E0C` | `0x08065E0C` | not started | 0.0% | 0/92 | asm |
| `sub_08067F3C` | `0x08067F3C` | not started | 0.0% | 0/92 | asm |
| `sub_08042784` | `0x08042784` | not started | 0.0% | 0/100 | asm |
| `sub_08061E8C` | `0x08061E8C` | not started | 0.0% | 0/108 | asm |
| `sub_08073910` | `0x08073910` | not started | 0.0% | 0/118 | asm |
| `sub_0806B064` | `0x0806B064` | not started | 0.0% | 0/122 | asm |
| `sub_080735DC` | `0x080735DC` | not started | 0.0% | 0/132 | asm |
| `sub_08041C8C` | `0x08041C8C` | not started | 0.0% | 0/142 | asm |
| `sub_0806E31C` | `0x0806E31C` | not started | 0.0% | 0/148 | asm |
| `sub_08044FB0` | `0x08044FB0` | not started | 0.0% | 0/156 | asm |
| `sub_0806833C` | `0x0806833C` | not started | 0.0% | 0/156 | asm |
| `sub_080428F0` | `0x080428F0` | not started | 0.0% | 0/160 | asm |
| `sub_08041B74` | `0x08041B74` | not started | 0.0% | 0/162 | asm |
| `sub_08073AEC` | `0x08073AEC` | not started | 0.0% | 0/162 | asm |
| `sub_080686F4` | `0x080686F4` | not started | 0.0% | 0/164 | asm |
| `sub_0806A4D8` | `0x0806A4D8` | not started | 0.0% | 0/168 | asm |
| `sub_080419B0` | `0x080419B0` | not started | 0.0% | 0/172 | asm |
| `sub_08068180` | `0x08068180` | not started | 0.0% | 0/174 | asm |
| `sub_080416C4` | `0x080416C4` | not started | 0.0% | 0/176 | asm |
| `sub_08070D44` | `0x08070D44` | not started | 0.0% | 0/176 | asm |
| `sub_0806E420` | `0x0806E420` | not started | 0.0% | 0/178 | asm |
| `sub_0806FF58` | `0x0806FF58` | not started | 0.0% | 0/180 | asm |
| `sub_080700CC` | `0x080700CC` | not started | 0.0% | 0/188 | asm |
| `sub_080688C8` | `0x080688C8` | not started | 0.0% | 0/190 | asm |
| `sub_08051444` | `0x08051444` | not started | 0.0% | 0/192 | asm |
| `sub_08062358` | `0x08062358` | not started | 0.0% | 0/192 | asm |
| `sub_0807000C` | `0x0807000C` | not started | 0.0% | 0/192 | asm |
| `sub_08054494` | `0x08054494` | not started | 0.0% | 0/196 | asm |
| `sub_0806FBF8` | `0x0806FBF8` | not started | 0.0% | 0/196 | asm |
| `sub_0804EBF0` | `0x0804EBF0` | not started | 0.0% | 0/202 | asm |
| `sub_0803FFB0` | `0x0803FFB0` | not started | 0.0% | 0/216 | asm |
| `sub_08063D68` | `0x08063D68` | not started | 0.0% | 0/216 | asm |
| `sub_0807027C` | `0x0807027C` | not started | 0.0% | 0/216 | asm |
| `sub_0803C500` | `0x0803C500` | not started | 0.0% | 0/220 | asm |
| `sub_0803C5DC` | `0x0803C5DC` | not started | 0.0% | 0/220 | asm |
| `sub_0806DF38` | `0x0806DF38` | not started | 0.0% | 0/228 | asm |
| `sub_0806121C` | `0x0806121C` | not started | 0.0% | 0/236 | asm |
| `sub_08062790` | `0x08062790` | not started | 0.0% | 0/236 | asm |
| `sub_08036A68` | `0x08036A68` | not started | 0.0% | 0/240 | asm |
| `sub_08038438` | `0x08038438` | not started | 0.0% | 0/240 | asm |
| `sub_08060D58` | `0x08060D58` | not started | 0.0% | 0/240 | asm |
| `sub_08061628` | `0x08061628` | not started | 0.0% | 0/244 | asm |
| `sub_08069270` | `0x08069270` | not started | 0.0% | 0/244 | asm |
| `sub_08070188` | `0x08070188` | not started | 0.0% | 0/244 | asm |
| `sub_08060C30` | `0x08060C30` | not started | 0.0% | 0/248 | asm |
| `sub_08068EC0` | `0x08068EC0` | not started | 0.0% | 0/248 | asm |
| `sub_0806B2F0` | `0x0806B2F0` | not started | 0.0% | 0/248 | asm |
| `sub_08072A38` | `0x08072A38` | not started | 0.0% | 0/250 | asm |
| `sub_080593A4` | `0x080593A4` | not started | 0.0% | 0/256 | asm |
| `sub_08062D80` | `0x08062D80` | not started | 0.0% | 0/264 | asm |
| `sub_08062E88` | `0x08062E88` | not started | 0.0% | 0/264 | asm |
| `sub_08068418` | `0x08068418` | not started | 0.0% | 0/272 | asm |
| `sub_0806B5C8` | `0x0806B5C8` | not started | 0.0% | 0/274 | asm |
| `sub_08069A60` | `0x08069A60` | not started | 0.0% | 0/280 | asm |
| `sub_0806F05C` | `0x0806F05C` | not started | 0.0% | 0/280 | asm |
| `sub_0806211C` | `0x0806211C` | not started | 0.0% | 0/284 | asm |
| `sub_0803E0CC` | `0x0803E0CC` | not started | 0.0% | 0/296 | asm |
| `sub_0803D284` | `0x0803D284` | not started | 0.0% | 0/298 | asm |
| `sub_0804AE94` | `0x0804AE94` | not started | 0.0% | 0/300 | asm |
| `sub_08056250` | `0x08056250` | not started | 0.0% | 0/302 | asm |
| `sub_08040680` | `0x08040680` | not started | 0.0% | 0/308 | asm |
| `sub_08065CD0` | `0x08065CD0` | not started | 0.0% | 0/316 | asm |
| `sub_08043C70` | `0x08043C70` | not started | 0.0% | 0/324 | asm |
| `sub_0804BD38` | `0x0804BD38` | not started | 0.0% | 0/328 | asm |
| `sub_08061EF8` | `0x08061EF8` | not started | 0.0% | 0/332 | asm |
| `sub_080737C0` | `0x080737C0` | not started | 0.0% | 0/336 | asm |
| `sub_0804D420` | `0x0804D420` | not started | 0.0% | 0/362 | asm |
| `sub_08044648` | `0x08044648` | not started | 0.0% | 0/364 | asm |
| `sub_080447E8` | `0x080447E8` | not started | 0.0% | 0/372 | asm |
| `sub_0804C8BC` | `0x0804C8BC` | not started | 0.0% | 0/372 | asm |
| `sub_0806314C` | `0x0806314C` | not started | 0.0% | 0/404 | asm |
| `sub_0806EEC8` | `0x0806EEC8` | not started | 0.0% | 0/404 | asm |
| `sub_08070AF8` | `0x08070AF8` | not started | 0.0% | 0/416 | asm |
| `sub_08068BD4` | `0x08068BD4` | not started | 0.0% | 0/420 | asm |
| `sub_08070930` | `0x08070930` | not started | 0.0% | 0/420 | asm |
| `sub_080618EC` | `0x080618EC` | not started | 0.0% | 0/428 | asm |
| `sub_08048DB8` | `0x08048DB8` | not started | 0.0% | 0/440 | asm |
| `sub_0803715C` | `0x0803715C` | not started | 0.0% | 0/444 | asm |
| `sub_08056BA4` | `0x08056BA4` | not started | 0.0% | 0/450 | asm |
| `sub_08068A08` | `0x08068A08` | not started | 0.0% | 0/460 | asm |
| `sub_0806E060` | `0x0806E060` | not started | 0.0% | 0/492 | asm |
| `sub_0803DEC8` | `0x0803DEC8` | not started | 0.0% | 0/514 | asm |
| `sub_0806EC20` | `0x0806EC20` | not started | 0.0% | 0/516 | asm |
| `sub_08053690` | `0x08053690` | not started | 0.0% | 0/528 | asm |
| `sub_08060E48` | `0x08060E48` | not started | 0.0% | 0/532 | asm |
| `sub_08067CE8` | `0x08067CE8` | not started | 0.0% | 0/548 | asm |
| `sub_0806B764` | `0x0806B764` | not started | 0.0% | 0/588 | asm |
| `sub_08054120` | `0x08054120` | not started | 0.0% | 0/594 | asm |
| `sub_0806960C` | `0x0806960C` | not started | 0.0% | 0/600 | asm |
| `sub_0806F910` | `0x0806F910` | not started | 0.0% | 0/624 | asm |
| `sub_080706B0` | `0x080706B0` | not started | 0.0% | 0/626 | asm |
| `sub_08044A8C` | `0x08044A8C` | not started | 0.0% | 0/672 | asm |
| `sub_0806C388` | `0x0806C388` | not started | 0.0% | 0/710 | asm |
| `sub_08046E7C` | `0x08046E7C` | not started | 0.0% | 0/872 | asm |
| `sub_0804DB28` | `0x0804DB28` | not started | 0.0% | 0/900 | asm |
| `sub_08045198` | `0x08045198` | not started | 0.0% | 0/1016 | asm |
| `sub_08045590` | `0x08045590` | not started | 0.0% | 0/1256 | asm |
| `sub_0806C7D4` | `0x0806C7D4` | not started | 0.0% | 0/1302 | asm |
| `sub_08043DB4` | `0x08043DB4` | not started | 0.0% | 0/1352 | asm |
| `sub_0804FFCC` | `0x0804FFCC` | not started | 0.0% | 0/1504 | asm |
| `sub_08039BD4` | `0x08039BD4` | not started | 0.0% | 0/1552 | asm |
| `sub_08074144` | `0x08074144` | blocked | 0.0% | 0/2 | asm |
| `sub_08062728` | `0x08062728` | blocked | 0.0% | 0/18 | asm |
| `sub_080428C4` | `0x080428C4` | blocked | 0.0% | 0/44 | asm |
| `sub_08062CF4` | `0x08062CF4` | blocked | 0.0% | 0/48 | asm |
| `sub_08030938` | `0x08030938` | blocked | 0.0% | 0/78 | asm |
| `sub_08034894` | `0x08034894` | blocked | 0.0% | 0/84 | asm |
| `sub_080604C8` | `0x080604C8` | blocked | 0.0% | 0/112 | asm |
| `sub_08073114` | `0x08073114` | blocked | 0.0% | 0/112 | asm |
| `sub_08045C5C` | `0x08045C5C` | blocked | 0.0% | 0/136 | asm |
| `sub_0806A6F8` | `0x0806A6F8` | blocked | 0.0% | 0/436 | asm |
| `sub_08067A9C` | `0x08067A9C` | matched | 100.0% | 2/2 | semantic |
| `sub_0806EEC4` | `0x0806EEC4` | matched | 100.0% | 2/2 | semantic |
| `sub_08033A94` | `0x08033A94` | matched | 100.0% | 4/4 | semantic |
| `sub_08062098` | `0x08062098` | matched | 100.0% | 4/4 | semantic |
| `sub_080674A0` | `0x080674A0` | matched | 100.0% | 4/4 | semantic |
| `sub_080674AC` | `0x080674AC` | matched | 100.0% | 4/4 | semantic |
| `sub_080674B0` | `0x080674B0` | matched | 100.0% | 4/4 | semantic |
| `sub_080674B4` | `0x080674B4` | matched | 100.0% | 6/6 | semantic |
| `sub_08067B98` | `0x08067B98` | matched | 100.0% | 6/6 | semantic |
| `sub_080705CC` | `0x080705CC` | matched | 100.0% | 6/6 | semantic |
| `sub_080705D4` | `0x080705D4` | matched | 100.0% | 6/6 | semantic |
| `sub_08062A14` | `0x08062A14` | matched | 100.0% | 8/8 | semantic |
| `sub_080338E4` | `0x080338E4` | matched | 100.0% | 10/10 | semantic |
| `sub_08033F24` | `0x08033F24` | matched | 100.0% | 10/10 | semantic |
| `sub_08034414` | `0x08034414` | matched | 100.0% | 10/10 | semantic |
| `sub_080346A8` | `0x080346A8` | matched | 100.0% | 10/10 | semantic |
| `sub_080358CC` | `0x080358CC` | matched | 100.0% | 10/10 | semantic |
| `sub_08068014` | `0x08068014` | matched | 100.0% | 10/10 | semantic |
| `sub_0802B90C` | `0x0802B90C` | matched | 100.0% | 12/12 | semantic |
| `sub_08032DB8` | `0x08032DB8` | matched | 100.0% | 12/12 | semantic |
| `sub_08035878` | `0x08035878` | matched | 100.0% | 12/12 | semantic |
| `sub_080429C0` | `0x080429C0` | matched | 100.0% | 12/12 | semantic |
| `sub_08043974` | `0x08043974` | matched | 100.0% | 12/12 | semantic |
| `sub_08061BDC` | `0x08061BDC` | matched | 100.0% | 12/12 | semantic |
| `sub_08062634` | `0x08062634` | matched | 100.0% | 12/12 | semantic |
| `sub_08066390` | `0x08066390` | matched | 100.0% | 12/12 | semantic |
| `sub_08066434` | `0x08066434` | matched | 100.0% | 12/12 | semantic |
| `sub_08066440` | `0x08066440` | matched | 100.0% | 12/12 | semantic |
| `sub_08068584` | `0x08068584` | matched | 100.0% | 12/12 | semantic |
| `sub_080686D8` | `0x080686D8` | matched | 100.0% | 12/12 | semantic |
| `sub_08071808` | `0x08071808` | matched | 100.0% | 12/12 | semantic |
| `sub_080602C0` | `0x080602C0` | matched | 100.0% | 14/14 | semantic |
| `sub_08060394` | `0x08060394` | matched | 100.0% | 14/14 | semantic |
| `sub_08060428` | `0x08060428` | matched | 100.0% | 14/14 | semantic |
| `sub_08060438` | `0x08060438` | matched | 100.0% | 14/14 | semantic |
| `sub_08060448` | `0x08060448` | matched | 100.0% | 14/14 | semantic |
| `sub_08060458` | `0x08060458` | matched | 100.0% | 14/14 | semantic |
| `sub_08061784` | `0x08061784` | matched | 100.0% | 16/16 | semantic |
| `sub_080617B4` | `0x080617B4` | matched | 100.0% | 16/16 | semantic |
| `sub_08061A98` | `0x08061A98` | matched | 100.0% | 16/16 | semantic |
| `sub_08061AA8` | `0x08061AA8` | matched | 100.0% | 16/16 | semantic |
| `sub_08062A1C` | `0x08062A1C` | matched | 100.0% | 16/16 | semantic |
| `sub_0806644C` | `0x0806644C` | matched | 100.0% | 16/16 | semantic |
| `sub_08068574` | `0x08068574` | matched | 100.0% | 16/16 | semantic |
| `sub_0806B5B8` | `0x0806B5B8` | matched | 100.0% | 16/16 | semantic |
| `sub_0806BB38` | `0x0806BB38` | matched | 100.0% | 16/16 | semantic |
| `sub_0802B8BC` | `0x0802B8BC` | matched | 100.0% | 20/20 | semantic |
| `sub_080312D8` | `0x080312D8` | matched | 100.0% | 20/20 | semantic |
| `sub_080312EC` | `0x080312EC` | matched | 100.0% | 20/20 | semantic |
| `sub_080314FC` | `0x080314FC` | matched | 100.0% | 20/20 | semantic |
| `sub_08033958` | `0x08033958` | matched | 100.0% | 20/20 | semantic |
| `sub_0803EDC8` | `0x0803EDC8` | matched | 100.0% | 20/20 | semantic |
| `sub_0803EDF0` | `0x0803EDF0` | matched | 100.0% | 20/20 | semantic |
| `sub_080400C0` | `0x080400C0` | matched | 100.0% | 20/20 | semantic |
| `sub_080473E4` | `0x080473E4` | matched | 100.0% | 20/20 | semantic |
| `sub_08061E40` | `0x08061E40` | matched | 100.0% | 20/20 | semantic |
| `sub_08062684` | `0x08062684` | matched | 100.0% | 20/20 | semantic |
| `sub_080628E4` | `0x080628E4` | matched | 100.0% | 20/20 | semantic |
| `sub_08067634` | `0x08067634` | matched | 100.0% | 20/20 | semantic |
| `sub_08067890` | `0x08067890` | matched | 100.0% | 20/20 | semantic |
| `sub_08069C14` | `0x08069C14` | matched | 100.0% | 20/20 | semantic |
| `sub_0806DEF4` | `0x0806DEF4` | matched | 100.0% | 20/20 | semantic |
| `sub_0807069C` | `0x0807069C` | matched | 100.0% | 20/20 | semantic |
| `sub_08071F84` | `0x08071F84` | matched | 100.0% | 20/20 | semantic |
| `sub_08071F98` | `0x08071F98` | matched | 100.0% | 20/20 | semantic |
| `sub_08072F94` | `0x08072F94` | matched | 100.0% | 20/20 | semantic |
| `sub_080447B4` | `0x080447B4` | matched | 100.0% | 22/22 | semantic |
| `sub_0806AC68` | `0x0806AC68` | matched | 100.0% | 22/22 | semantic |
| `sub_0802D8C4` | `0x0802D8C4` | matched | 100.0% | 24/24 | semantic |
| `sub_08036190` | `0x08036190` | matched | 100.0% | 24/24 | semantic |
| `sub_08048D0C` | `0x08048D0C` | matched | 100.0% | 24/24 | semantic |
| `sub_08050864` | `0x08050864` | matched | 100.0% | 24/24 | semantic |
| `sub_080538A0` | `0x080538A0` | matched | 100.0% | 24/24 | semantic |
| `sub_08054108` | `0x08054108` | matched | 100.0% | 24/24 | semantic |
| `sub_08056380` | `0x08056380` | matched | 100.0% | 24/24 | semantic |
| `sub_08056AF0` | `0x08056AF0` | matched | 100.0% | 24/24 | semantic |
| `sub_08060254` | `0x08060254` | matched | 100.0% | 24/24 | semantic |
| `sub_08061610` | `0x08061610` | matched | 100.0% | 24/24 | semantic |
| `sub_08068884` | `0x08068884` | matched | 100.0% | 24/24 | semantic |
| `sub_0806BE08` | `0x0806BE08` | matched | 100.0% | 24/24 | semantic |
| `sub_080717F0` | `0x080717F0` | matched | 100.0% | 24/24 | semantic |
| `sub_08072CC0` | `0x08072CC0` | matched | 100.0% | 24/24 | semantic |
| `sub_080346C0` | `0x080346C0` | matched | 100.0% | 26/26 | semantic |
| `sub_080447CC` | `0x080447CC` | matched | 100.0% | 26/26 | semantic |
| `sub_0806BDA8` | `0x0806BDA8` | matched | 100.0% | 26/26 | semantic |
| `sub_08071FAC` | `0x08071FAC` | matched | 100.0% | 26/26 | semantic |
| `sub_0802D598` | `0x0802D598` | matched | 100.0% | 28/28 | semantic |
| `sub_0803484C` | `0x0803484C` | matched | 100.0% | 28/28 | semantic |
| `sub_08034FDC` | `0x08034FDC` | matched | 100.0% | 28/28 | semantic |
| `sub_08034FF8` | `0x08034FF8` | matched | 100.0% | 28/28 | semantic |
| `sub_08040530` | `0x08040530` | matched | 100.0% | 28/28 | semantic |
| `sub_08042E78` | `0x08042E78` | matched | 100.0% | 28/28 | semantic |
| `sub_0806639C` | `0x0806639C` | matched | 100.0% | 28/28 | semantic |
| `sub_080679A4` | `0x080679A4` | matched | 100.0% | 28/28 | semantic |
| `sub_080679C0` | `0x080679C0` | matched | 100.0% | 28/28 | semantic |
| `sub_08068558` | `0x08068558` | matched | 100.0% | 28/28 | semantic |
| `sub_0806A954` | `0x0806A954` | matched | 100.0% | 28/28 | semantic |
| `sub_0806FDB4` | `0x0806FDB4` | matched | 100.0% | 28/28 | semantic |
| `sub_080705A4` | `0x080705A4` | matched | 100.0% | 28/28 | semantic |
| `sub_080705DC` | `0x080705DC` | matched | 100.0% | 28/28 | semantic |
| `sub_08033E3C` | `0x08033E3C` | matched | 100.0% | 30/30 | semantic |
| `sub_08034360` | `0x08034360` | matched | 100.0% | 30/30 | semantic |
| `sub_08034FBC` | `0x08034FBC` | matched | 100.0% | 30/30 | semantic |
| `sub_080400D4` | `0x080400D4` | matched | 100.0% | 30/30 | semantic |
| `sub_08044D8C` | `0x08044D8C` | matched | 100.0% | 30/30 | semantic |
| `sub_08070C98` | `0x08070C98` | matched | 100.0% | 30/30 | semantic |
| `sub_08071FC8` | `0x08071FC8` | matched | 100.0% | 30/30 | semantic |
| `sub_0807339C` | `0x0807339C` | matched | 100.0% | 30/30 | semantic |
| `sub_0802EECC` | `0x0802EECC` | matched | 100.0% | 32/32 | semantic |
| `sub_0802FD80` | `0x0802FD80` | matched | 100.0% | 32/32 | semantic |
| `sub_08035238` | `0x08035238` | matched | 100.0% | 32/32 | semantic |
| `sub_080408C4` | `0x080408C4` | matched | 100.0% | 32/32 | semantic |
| `sub_080608D4` | `0x080608D4` | matched | 100.0% | 32/32 | semantic |
| `sub_08045A84` | `0x08045A84` | matched | 100.0% | 34/34 | semantic |
| `sub_08062238` | `0x08062238` | matched | 100.0% | 34/34 | semantic |
| `sub_080703FC` | `0x080703FC` | matched | 100.0% | 34/34 | semantic |
| `sub_08070AD4` | `0x08070AD4` | matched | 100.0% | 34/34 | semantic |
| `sub_08070DF4` | `0x08070DF4` | matched | 100.0% | 34/34 | semantic |
| `sub_08073078` | `0x08073078` | matched | 100.0% | 34/34 | semantic |
| `sub_0802E1EC` | `0x0802E1EC` | matched | 100.0% | 36/36 | semantic |
| `sub_0802E210` | `0x0802E210` | matched | 100.0% | 36/36 | semantic |
| `sub_0804BE80` | `0x0804BE80` | matched | 100.0% | 36/36 | semantic |
| `sub_0804CA30` | `0x0804CA30` | matched | 100.0% | 36/36 | semantic |
| `sub_0804D58C` | `0x0804D58C` | matched | 100.0% | 36/36 | semantic |
| `sub_080604A4` | `0x080604A4` | matched | 100.0% | 36/36 | semantic |
| `sub_08060798` | `0x08060798` | matched | 100.0% | 36/36 | semantic |
| `sub_080615EC` | `0x080615EC` | matched | 100.0% | 36/36 | semantic |
| `sub_08062044` | `0x08062044` | matched | 100.0% | 36/36 | semantic |
| `sub_080626B8` | `0x080626B8` | matched | 100.0% | 36/36 | semantic |
| `sub_080686B4` | `0x080686B4` | matched | 100.0% | 36/36 | semantic |
| `sub_0806EE24` | `0x0806EE24` | matched | 100.0% | 36/36 | semantic |
| `sub_08070678` | `0x08070678` | matched | 100.0% | 36/36 | semantic |
| `sub_08073184` | `0x08073184` | matched | 100.0% | 36/36 | semantic |
| `sub_080731F4` | `0x080731F4` | matched | 100.0% | 36/36 | semantic |
| `sub_0802E18C` | `0x0802E18C` | matched | 100.0% | 38/38 | semantic |
| `sub_08031124` | `0x08031124` | matched | 100.0% | 38/38 | semantic |
| `sub_08041394` | `0x08041394` | matched | 100.0% | 38/38 | semantic |
| `sub_080312B0` | `0x080312B0` | matched | 100.0% | 40/40 | semantic |
| `sub_0803A1E4` | `0x0803A1E4` | matched | 100.0% | 40/40 | semantic |
| `sub_0803DD60` | `0x0803DD60` | matched | 100.0% | 40/40 | semantic |
| `sub_0803EBB0` | `0x0803EBB0` | matched | 100.0% | 40/40 | semantic |
| `sub_0803EC34` | `0x0803EC34` | matched | 100.0% | 40/40 | semantic |
| `sub_0803ECB8` | `0x0803ECB8` | matched | 100.0% | 40/40 | semantic |
| `sub_08042B00` | `0x08042B00` | matched | 100.0% | 40/40 | semantic |
| `sub_08042B28` | `0x08042B28` | matched | 100.0% | 40/40 | semantic |
| `sub_08042B50` | `0x08042B50` | matched | 100.0% | 40/40 | semantic |
| `sub_08062960` | `0x08062960` | matched | 100.0% | 40/40 | semantic |
| `sub_0806EBF8` | `0x0806EBF8` | matched | 100.0% | 40/40 | semantic |
| `sub_080720F0` | `0x080720F0` | matched | 100.0% | 40/40 | semantic |
| `sub_080733BC` | `0x080733BC` | matched | 100.0% | 40/40 | semantic |
| `sub_0802B930` | `0x0802B930` | matched | 100.0% | 42/42 | semantic |
| `sub_08054558` | `0x08054558` | matched | 100.0% | 42/42 | semantic |
| `sub_08062D24` | `0x08062D24` | matched | 100.0% | 42/42 | semantic |
| `sub_080735B0` | `0x080735B0` | matched | 100.0% | 42/42 | semantic |
| `sub_0802D898` | `0x0802D898` | matched | 100.0% | 44/44 | semantic |
| `sub_08034788` | `0x08034788` | matched | 100.0% | 44/44 | semantic |
| `sub_080347E4` | `0x080347E4` | matched | 100.0% | 44/44 | semantic |
| `sub_080361CC` | `0x080361CC` | matched | 100.0% | 44/44 | semantic |
| `sub_0803C6B8` | `0x0803C6B8` | matched | 100.0% | 44/44 | semantic |
| `sub_080433F4` | `0x080433F4` | matched | 100.0% | 44/44 | semantic |
| `sub_08044EE8` | `0x08044EE8` | matched | 100.0% | 44/44 | semantic |
| `sub_08059C6C` | `0x08059C6C` | matched | 100.0% | 44/44 | semantic |
| `sub_0806105C` | `0x0806105C` | matched | 100.0% | 44/44 | semantic |
| `sub_080611F0` | `0x080611F0` | matched | 100.0% | 44/44 | semantic |
| `sub_08062CC8` | `0x08062CC8` | matched | 100.0% | 44/44 | semantic |
| `sub_08066BC4` | `0x08066BC4` | matched | 100.0% | 44/44 | semantic |
| `sub_0806DEC8` | `0x0806DEC8` | matched | 100.0% | 44/44 | semantic |
| `sub_0806F174` | `0x0806F174` | matched | 100.0% | 44/44 | semantic |
| `sub_0806FEFC` | `0x0806FEFC` | matched | 100.0% | 44/44 | semantic |
| `sub_08059D08` | `0x08059D08` | matched | 100.0% | 46/46 | semantic |
| `sub_0802BA4C` | `0x0802BA4C` | matched | 100.0% | 48/48 | semantic |
| `sub_080405E8` | `0x080405E8` | matched | 100.0% | 48/48 | semantic |
| `sub_08040618` | `0x08040618` | matched | 100.0% | 48/48 | semantic |
| `sub_08041980` | `0x08041980` | matched | 100.0% | 48/48 | semantic |
| `sub_08043944` | `0x08043944` | matched | 100.0% | 48/48 | semantic |
| `sub_08045AA8` | `0x08045AA8` | matched | 100.0% | 48/48 | semantic |
| `sub_08047594` | `0x08047594` | matched | 100.0% | 48/48 | semantic |
| `sub_080475C4` | `0x080475C4` | matched | 100.0% | 48/48 | semantic |
| `sub_080475F4` | `0x080475F4` | matched | 100.0% | 48/48 | semantic |
| `sub_0805D1AC` | `0x0805D1AC` | matched | 100.0% | 48/48 | semantic |
| `sub_08060D28` | `0x08060D28` | matched | 100.0% | 48/48 | semantic |
| `sub_08061308` | `0x08061308` | matched | 100.0% | 48/48 | semantic |
| `sub_08061BAC` | `0x08061BAC` | matched | 100.0% | 48/48 | semantic |
| `sub_080628B4` | `0x080628B4` | matched | 100.0% | 48/48 | semantic |
| `sub_08067F98` | `0x08067F98` | matched | 100.0% | 48/48 | semantic |
| `sub_0806A580` | `0x0806A580` | matched | 100.0% | 48/48 | semantic |
| `sub_0806F430` | `0x0806F430` | matched | 100.0% | 48/48 | semantic |
| `sub_0806FF28` | `0x0806FF28` | matched | 100.0% | 48/48 | semantic |
| `sub_08031368` | `0x08031368` | matched | 100.0% | 50/50 | semantic |
| `sub_08035204` | `0x08035204` | matched | 100.0% | 50/50 | semantic |
| `sub_08068808` | `0x08068808` | matched | 100.0% | 50/50 | semantic |
| `sub_080310F0` | `0x080310F0` | matched | 100.0% | 52/52 | semantic |
| `sub_0803E440` | `0x0803E440` | matched | 100.0% | 52/52 | semantic |
| `sub_08041858` | `0x08041858` | matched | 100.0% | 52/52 | semantic |
| `sub_08060220` | `0x08060220` | matched | 100.0% | 52/52 | semantic |
| `sub_080726E0` | `0x080726E0` | matched | 100.0% | 52/52 | semantic |
| `sub_080302A8` | `0x080302A8` | matched | 100.0% | 54/54 | semantic |
| `sub_08033F48` | `0x08033F48` | matched | 100.0% | 54/54 | semantic |
| `sub_08062758` | `0x08062758` | matched | 100.0% | 54/54 | semantic |
| `sub_0802B95C` | `0x0802B95C` | matched | 100.0% | 56/56 | semantic |
| `sub_0802E1B4` | `0x0802E1B4` | matched | 100.0% | 56/56 | semantic |
| `sub_08030F00` | `0x08030F00` | matched | 100.0% | 56/56 | semantic |
| `sub_08033A5C` | `0x08033A5C` | matched | 100.0% | 56/56 | semantic |
| `sub_0803403C` | `0x0803403C` | matched | 100.0% | 56/56 | semantic |
| `sub_08040088` | `0x08040088` | matched | 100.0% | 56/56 | semantic |
| `sub_08042B78` | `0x08042B78` | matched | 100.0% | 56/56 | semantic |
| `sub_08042BB0` | `0x08042BB0` | matched | 100.0% | 56/56 | semantic |
| `sub_08042C3C` | `0x08042C3C` | matched | 100.0% | 56/56 | semantic |
| `sub_0805DA70` | `0x0805DA70` | matched | 100.0% | 56/56 | semantic |
| `sub_0806013C` | `0x0806013C` | matched | 100.0% | 56/56 | semantic |
| `sub_08061C48` | `0x08061C48` | matched | 100.0% | 56/56 | asm |
| `sub_0806209C` | `0x0806209C` | matched | 100.0% | 56/56 | semantic |
| `sub_08062AC0` | `0x08062AC0` | matched | 100.0% | 56/56 | semantic |
| `sub_080712CC` | `0x080712CC` | matched | 100.0% | 56/56 | semantic |
| `sub_0802B994` | `0x0802B994` | matched | 100.0% | 58/58 | semantic |
| `sub_0806F1A0` | `0x0806F1A0` | matched | 100.0% | 58/58 | semantic |
| `sub_080726A4` | `0x080726A4` | matched | 100.0% | 58/58 | semantic |
| `sub_08034810` | `0x08034810` | matched | 100.0% | 60/60 | semantic |
| `sub_080603A4` | `0x080603A4` | matched | 100.0% | 60/60 | semantic |
| `sub_08060468` | `0x08060468` | matched | 100.0% | 60/60 | semantic |
| `sub_08066AD4` | `0x08066AD4` | matched | 100.0% | 60/60 | semantic |
| `sub_08033EA4` | `0x08033EA4` | matched | 100.0% | 62/62 | semantic |
| `sub_08057234` | `0x08057234` | matched | 100.0% | 62/62 | semantic |
| `sub_0802C62C` | `0x0802C62C` | matched | 100.0% | 64/64 | asm |
| `sub_0803413C` | `0x0803413C` | matched | 100.0% | 64/64 | semantic |
| `sub_08038638` | `0x08038638` | matched | 100.0% | 64/64 | semantic |
| `sub_0803FDD0` | `0x0803FDD0` | matched | 100.0% | 64/64 | semantic |
| `sub_080405A8` | `0x080405A8` | matched | 100.0% | 64/64 | asm |
| `sub_08054454` | `0x08054454` | matched | 100.0% | 64/64 | semantic |
| `sub_08060758` | `0x08060758` | matched | 100.0% | 64/64 | semantic |
| `sub_08069908` | `0x08069908` | matched | 100.0% | 64/64 | semantic |
| `sub_08069948` | `0x08069948` | matched | 100.0% | 64/64 | semantic |
| `sub_08069988` | `0x08069988` | matched | 100.0% | 64/64 | semantic |
| `sub_0806B724` | `0x0806B724` | matched | 100.0% | 64/64 | semantic |
| `sub_0806D958` | `0x0806D958` | matched | 100.0% | 64/64 | semantic |
| `sub_08071E04` | `0x08071E04` | matched | 100.0% | 64/64 | semantic |
| `sub_08071E44` | `0x08071E44` | matched | 100.0% | 64/64 | semantic |
| `sub_08033D90` | `0x08033D90` | matched | 100.0% | 66/66 | semantic |
| `sub_080618A8` | `0x080618A8` | matched | 100.0% | 66/66 | semantic |
| `sub_08073218` | `0x08073218` | matched | 100.0% | 66/66 | semantic |
| `sub_08073A28` | `0x08073A28` | matched | 100.0% | 66/66 | semantic |
| `sub_08033530` | `0x08033530` | matched | 100.0% | 68/68 | semantic |
| `sub_08043ADC` | `0x08043ADC` | matched | 100.0% | 68/68 | semantic |
| `sub_08062640` | `0x08062640` | matched | 100.0% | 68/68 | semantic |
| `sub_08066BF0` | `0x08066BF0` | matched | 100.0% | 70/70 | semantic |
| `sub_08073568` | `0x08073568` | matched | 100.0% | 70/70 | semantic |
| `sub_080330F4` | `0x080330F4` | matched | 100.0% | 72/72 | semantic |
| `sub_08035884` | `0x08035884` | matched | 100.0% | 72/72 | semantic |
| `sub_0803593C` | `0x0803593C` | matched | 100.0% | 72/72 | semantic |
| `sub_08043C28` | `0x08043C28` | matched | 100.0% | 72/72 | semantic |
| `sub_08046230` | `0x08046230` | matched | 100.0% | 72/72 | semantic |
| `sub_08052FC8` | `0x08052FC8` | matched | 100.0% | 72/72 | semantic |
| `sub_080603E0` | `0x080603E0` | matched | 100.0% | 72/72 | semantic |
| `sub_08062BF0` | `0x08062BF0` | matched | 100.0% | 72/72 | semantic |
| `sub_08062C38` | `0x08062C38` | matched | 100.0% | 72/72 | semantic |
| `sub_08062C80` | `0x08062C80` | matched | 100.0% | 72/72 | semantic |
| `sub_08063104` | `0x08063104` | matched | 100.0% | 72/72 | semantic |
| `sub_080674BC` | `0x080674BC` | matched | 100.0% | 72/72 | semantic |
| `sub_08069A18` | `0x08069A18` | matched | 100.0% | 72/72 | semantic |
| `sub_08044F64` | `0x08044F64` | matched | 100.0% | 74/74 | semantic |
| `sub_080611A4` | `0x080611A4` | matched | 100.0% | 74/74 | semantic |
| `sub_08073440` | `0x08073440` | matched | 100.0% | 74/74 | semantic |
| `sub_08035D1C` | `0x08035D1C` | matched | 100.0% | 76/76 | semantic |
| `sub_0803E328` | `0x0803E328` | matched | 100.0% | 76/76 | semantic |
| `sub_08041348` | `0x08041348` | matched | 100.0% | 76/76 | semantic |
| `sub_08043BDC` | `0x08043BDC` | matched | 100.0% | 76/76 | semantic |
| `sub_08062A74` | `0x08062A74` | matched | 100.0% | 76/76 | semantic |
| `sub_080680CC` | `0x080680CC` | matched | 100.0% | 76/76 | semantic |
| `sub_0806F8C4` | `0x0806F8C4` | matched | 100.0% | 76/76 | semantic |
| `sub_0802C5DC` | `0x0802C5DC` | matched | 100.0% | 78/78 | semantic |
| `sub_08068020` | `0x08068020` | matched | 100.0% | 78/78 | semantic |
| `sub_08033574` | `0x08033574` | matched | 100.0% | 80/80 | semantic |
| `sub_08045128` | `0x08045128` | matched | 100.0% | 80/80 | semantic |
| `sub_0804745C` | `0x0804745C` | matched | 100.0% | 80/80 | semantic |
| `sub_0803E258` | `0x0803E258` | matched | 100.0% | 82/82 | semantic |
| `sub_0807179C` | `0x0807179C` | matched | 100.0% | 82/82 | semantic |
| `sub_08041F88` | `0x08041F88` | matched | 100.0% | 84/84 | semantic |
| `sub_0805D99C` | `0x0805D99C` | matched | 100.0% | 84/84 | semantic |
| `sub_08038D10` | `0x08038D10` | matched | 100.0% | 86/86 | semantic |
| `sub_0803D4C4` | `0x0803D4C4` | matched | 100.0% | 88/88 | semantic |
| `sub_080424E8` | `0x080424E8` | matched | 100.0% | 88/88 | semantic |
| `sub_08032D5C` | `0x08032D5C` | matched | 100.0% | 90/90 | semantic |
| `sub_0802F520` | `0x0802F520` | matched | 100.0% | 92/92 | semantic |
| `sub_08031094` | `0x08031094` | matched | 100.0% | 92/92 | semantic |
| `sub_080449C4` | `0x080449C4` | matched | 100.0% | 92/92 | semantic |
| `sub_080601C4` | `0x080601C4` | matched | 100.0% | 92/92 | semantic |
| `sub_0806184C` | `0x0806184C` | matched | 100.0% | 92/92 | semantic |
| `sub_08041DB4` | `0x08041DB4` | matched | 100.0% | 94/94 | semantic |
| `sub_0802C6AC` | `0x0802C6AC` | matched | 100.0% | 96/96 | semantic |
| `sub_080435D8` | `0x080435D8` | matched | 100.0% | 96/96 | semantic |
| `sub_08061BE8` | `0x08061BE8` | matched | 100.0% | 96/96 | semantic |
| `sub_0803E1F4` | `0x0803E1F4` | matched | 100.0% | 98/98 | semantic |
| `sub_08042390` | `0x08042390` | matched | 100.0% | 98/98 | semantic |
| `sub_08059B74` | `0x08059B74` | matched | 100.0% | 98/98 | semantic |
| `sub_08033084` | `0x08033084` | matched | 100.0% | 100/100 | semantic |
| `sub_08037318` | `0x08037318` | matched | 100.0% | 100/100 | semantic |
| `sub_08044A20` | `0x08044A20` | matched | 100.0% | 100/100 | semantic |
| `sub_08033DD4` | `0x08033DD4` | matched | 100.0% | 104/104 | semantic |
| `sub_080360BC` | `0x080360BC` | matched | 100.0% | 104/104 | semantic |
| `sub_0804737C` | `0x0804737C` | matched | 100.0% | 104/104 | semantic |
| `sub_0804B4B4` | `0x0804B4B4` | matched | 100.0% | 104/104 | semantic |
| `sub_0804C324` | `0x0804C324` | matched | 100.0% | 104/104 | semantic |
| `sub_0804CED4` | `0x0804CED4` | matched | 100.0% | 104/104 | semantic |
| `sub_08059AE0` | `0x08059AE0` | matched | 100.0% | 104/104 | semantic |
| `sub_0806171C` | `0x0806171C` | matched | 100.0% | 104/104 | semantic |
| `sub_0802D52C` | `0x0802D52C` | matched | 100.0% | 108/108 | semantic |
| `sub_08033878` | `0x08033878` | matched | 100.0% | 108/108 | semantic |
| `sub_08038314` | `0x08038314` | matched | 100.0% | 108/108 | semantic |
| `sub_08042718` | `0x08042718` | matched | 100.0% | 108/108 | semantic |
| `sub_0804A4E0` | `0x0804A4E0` | matched | 100.0% | 108/108 | semantic |
| `sub_08036264` | `0x08036264` | matched | 100.0% | 112/112 | semantic |
| `sub_0803E934` | `0x0803E934` | matched | 100.0% | 112/112 | semantic |
| `sub_08059C98` | `0x08059C98` | matched | 100.0% | 112/112 | semantic |
| `sub_080392D0` | `0x080392D0` | matched | 100.0% | 116/116 | semantic |
| `sub_08042630` | `0x08042630` | matched | 100.0% | 116/116 | semantic |
| `sub_080426A4` | `0x080426A4` | matched | 100.0% | 116/116 | semantic |
| `sub_08048168` | `0x08048168` | matched | 100.0% | 116/116 | semantic |
| `sub_08051504` | `0x08051504` | matched | 100.0% | 116/116 | semantic |
| `sub_08042540` | `0x08042540` | matched | 100.0% | 120/120 | semantic |
| `sub_080425B8` | `0x080425B8` | matched | 100.0% | 120/120 | semantic |
| `sub_08043638` | `0x08043638` | matched | 100.0% | 120/120 | semantic |
| `sub_0807309C` | `0x0807309C` | matched | 100.0% | 120/120 | semantic |
| `sub_080462D4` | `0x080462D4` | matched | 100.0% | 130/130 | semantic |
| `sub_0803531C` | `0x0803531C` | matched | 100.0% | 132/132 | semantic |
| `sub_0806C704` | `0x0806C704` | matched | 100.0% | 136/136 | semantic |
| `sub_0804245C` | `0x0804245C` | matched | 100.0% | 140/140 | semantic |
| `sub_08034618` | `0x08034618` | matched | 100.0% | 142/142 | semantic |
| `sub_08031204` | `0x08031204` | matched | 100.0% | 144/144 | semantic |
| `sub_08049F98` | `0x08049F98` | matched | 100.0% | 144/144 | semantic |
| `sub_0804E17C` | `0x0804E17C` | matched | 100.0% | 144/144 | semantic |
| `sub_08051578` | `0x08051578` | matched | 100.0% | 144/144 | semantic |
| `sub_08053218` | `0x08053218` | matched | 100.0% | 144/144 | semantic |
| `sub_08041774` | `0x08041774` | matched | 100.0% | 148/148 | semantic |
| `sub_08059BD8` | `0x08059BD8` | matched | 100.0% | 148/148 | semantic |
| `sub_0806306C` | `0x0806306C` | matched | 100.0% | 152/152 | semantic |
| `sub_0804E20C` | `0x0804E20C` | matched | 100.0% | 164/164 | semantic |
| `sub_08047A94` | `0x08047A94` | matched | 100.0% | 168/168 | semantic |
| `sub_0804A438` | `0x0804A438` | matched | 100.0% | 168/168 | semantic |
| `sub_0804B40C` | `0x0804B40C` | matched | 100.0% | 168/168 | semantic |
| `sub_0804C27C` | `0x0804C27C` | matched | 100.0% | 168/168 | semantic |
| `sub_0804CE2C` | `0x0804CE2C` | matched | 100.0% | 168/168 | semantic |
| `sub_0804E4F4` | `0x0804E4F4` | matched | 100.0% | 168/168 | semantic |
| `sub_080507B8` | `0x080507B8` | matched | 100.0% | 172/172 | semantic |
| `sub_08034568` | `0x08034568` | matched | 100.0% | 176/176 | semantic |
| `sub_08054CF4` | `0x08054CF4` | matched | 100.0% | 180/180 | semantic |
| `sub_080553B8` | `0x080553B8` | matched | 100.0% | 180/180 | semantic |
| `sub_080632F8` | `0x080632F8` | matched | 100.0% | 184/184 | semantic |
| `sub_08052F0C` | `0x08052F0C` | matched | 100.0% | 188/188 | semantic |
| `sub_0806225C` | `0x0806225C` | matched | 100.0% | 188/188 | semantic |
| `sub_080353A0` | `0x080353A0` | matched | 100.0% | 200/200 | semantic |
| `sub_0802D8DC` | `0x0802D8DC` | matched | 100.0% | 204/204 | semantic |
| `sub_0803B078` | `0x0803B078` | matched | 100.0% | 204/204 | semantic |
| `sub_080427E8` | `0x080427E8` | matched | 100.0% | 220/220 | semantic |
| `sub_0803019C` | `0x0803019C` | matched | 100.0% | 268/268 | semantic |
| `sub_0804ED90` | `0x0804ED90` | matched | 100.0% | 276/276 | semantic |
| `sub_0802D3F0` | `0x0802D3F0` | matched | 100.0% | 316/316 | semantic |
| `sub_0804109C` | `0x0804109C` | matched | 100.0% | 336/336 | semantic |
| `sub_08030D4C` | `0x08030D4C` | matched | 100.0% | 436/436 | semantic |
| `sub_0802D6D4` | `0x0802D6D4` | matched | 100.0% | 452/452 | semantic |
| `sub_08037508` | `0x08037508` | matched | 100.0% | 452/452 | semantic |
