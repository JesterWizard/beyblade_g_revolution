# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-20T11:43:53Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 272 |
| Still need semantic C | **361** |
| Readable Thumb remaining | 361 |
| Opcode embeds remaining | 0 |
| Battle pending | 101 (46 already semantic) |
| Blocked (documented) | 34 |
| WIP (resume these first) | 18 |

Ranking: **battle** · showing top **40**

Park unmatched C in [`src/wip/`](../src/wip/README.md) — see [`decomp-wip.md`](decomp-wip.md).

## Resume (WIP)

_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._

| Function | Bytes | Score | Seed | Status | Next |
|----------|------:|-------|------|--------|------|
| `sub_08046278` | 92 | 11/92 | `src/wip/sub_08046278.c` | logic OK; 11/92 (56B vs 92B); extra r8/r9 leaf spill | independent per-field addressing like sub_08046230; force r8/r9 live |
| `sub_0802E048` | 228 | 188/228 | `src/wip/sub_0802E048.c` | same-size DIFF, 188/228 bytes (82.5%) | try decomp-permuter register-order search; likely same agbcc leaf-fn reg-alloc quirk as dead-end list |
| `sub_080338F0` | 104 | 20/104 | `src/wip/sub_080338F0.c` | same_size DIFF, 20/104 bytes (19.2%) — structural rewrite needed, indexing bug noted in file | fix table indexing to byte-offset (see note), re-add Unk338F0Table struct + Unk33958 retype, then re-run match_function.py |
| `sub_0802D2C0` | 108 | 46/108 | `src/wip/sub_0802D2C0.c` | DIFF; corrected retail branch semantics, but best current compile is 46/108 and 104 bytes due pool/register layout | permuter run targeting corrected branch shape and literal-pool/register order |
| `sub_0802BC14` | 112 | 58/112 | `src/wip/sub_0802BC14.c` | same-size DIFF (58/112, 51.8%) after signed-call and r0-pointer hints; remaining pool/register layout differs | leave readable Thumb; revisit with a verified signed-argument prototype or targeted pool/register permutation |
| `sub_0802BF04` | 140 | 55/140 | `src/wip/sub_0802BF04.c` | best 55/140 size-mismatch; s16 comparison and explicit r8 zero-register hints did not recover retail setup/order | leave readable Thumb; revisit with targeted constant/pointer reuse or permuter |
| `sub_08035C64` | 182 | 85/182 | `src/wip/sub_08035C64.c` | same_size DIFF 85/182 (46.7%); logic fully correct (repulsion physics on Unk346C0Inner, dx/dy/distSq/threshold gate) but agbcc always emits the early-return (zero) block first regardless of if/else source order — branch layout inverted vs retail which keeps compute as fallthrough and zero-block at function end | try computing zero-branch via explicit goto label placed after compute code, or split into two functions/permuter branch-order search |
| `sub_08034568` | 0 | 156/176 | `src/wip/sub_08034568.c` | size_mismatch 156/176 (88.6%, compiled 168B vs retail 176B); all field init logic correct (Unk346C0 tail-region zero/const init, 8 byte writes + 3 halfword + several u32); agbcc picks r1-chain instead of r4-chain for final unk2C4 store, dropping one add-chain step vs retail | try alternate field write order or split into two helper calls matching retail's r1/r4 chain split; permuter candidate (small, near miss) |
| `sub_08049F98` | 144 | unscored | `src/wip/sub_08049F98.c` | same-size DIFF 36/144 (25%); logic confirmed correct (2x sub_080617C4 header calls, sub_080615EC coord set via idx<<4 chain, sub_08061784 return, sub_0806171C draw); agbcc keeps out-param in r8 across 3 calls in retail (push r8 at entry) but my C only uses out at final call so agbcc doesn't preallocate r8 early — retail's r8 usage implies out is referenced earlier in source or a dummy read keeps it live | try touching 'out' earlier (e.g. volatile read) or reorder params so out is 2nd arg; also try casting idx shift result through s16 (retail uses lsrs #17 = arithmetic sign truncate to s15 for the return-value cast, suggesting val type may be s16 not u16 -- already tried, needs recheck combined with r8 fix). Twin clones sub_0804E17C/sub_08051578 share same structure - crack this one first, then just re-run match_function.py with same seed |
| `sub_080385DC` | 80 | 18/80 | `src/wip/sub_080385DC.c` | same_size DIFF 18/80; shared masks and r12/r6/r1 pointer/register hints did not improve the baseline | leave readable Thumb; revisit with targeted pointer-cache/permuter technique |
| `sub_080733E4` | 90 | 14/90 | `src/wip/sub_080733E4.c` | size_mismatch 14/90 baseline; explicit-goto and r2/r5-pinned variants did not reproduce retail loop allocation | leave readable Thumb; revisit with permuter over skip/main-loop source shape |
| `sub_08069B78` | 154 | 62/154 | `src/wip/sub_08069B78.c` | same-size DIFF 62/154 (40.3%); shared mask/inverse and r10/r5 hints did not improve post-call register scheduling | leave readable Thumb; revisit with targeted post-call register scheduling or permuter |
| `sub_0806E7BC` | 152 | 42/152 | `src/wip/sub_0806E7BC.c` | size_mismatch 42/152 (27.6%), compiled 148B vs retail 152B; attempted as line-segment intersection test (2D cross-product sign comparison, 8 s32 params ax,ay,bx,by,cx,cy,dx,dy) returning 0/1/2; logic direction plausible (first 8 bytes match: prologue) but overall structure/expression grouping doesn't match agbcc's register scheduling - needs more careful param/expr-order derivation from raw asm (subs order matters: check if retail computes abx=ax-bx or bx-ax first, etc) | re-derive param roles more carefully from asm (r12=a0 orig, r6=a1, r5=a2, r4=a3; stack args sp0x18/1C/20/24) - do NOT assume signature guessed here is correct; trace each subs/muls instruction to exact source expr before writing C |
| `sub_08041858` | 52 | 47/52 | `src/wip/sub_08041858.c` | 90% DIFF size mismatch (48 vs 52); volatile/r0-pinned p2 variants and short permuter run did not break the pool-address fold | leave readable Thumb; revisit with a genuine call-boundary or pool-symbol technique |
| `sub_08043944` | 48 | 37/48 | `src/wip/sub_08043944.c` | best 77.1% (37/48) same-size DIFF after r3/r4 hints; input-normalization order still differs | leave readable Thumb; revisit with a source shape that forces idx normalization before flags normalization |
| `sub_080726E0` | 52 | 50/52 | `src/wip/sub_080726E0.c` | 96.2% (50/52) same-size DIFF; r4 register hint and short decomp-permuter run did not improve the result | leave readable Thumb; revisit with a new way to force r4 reuse for the final halfword offset |
| `sub_08044F64` | 74 | 69/74 | `src/wip/sub_08044F64.c` | 93.2% (69/74) same-size DIFF; idx-as-loop and r1 multiplier hints did not improve the register-order drift | leave readable Thumb; revisit with a source shape that preserves the parameter register through the multiply |
| `sub_08031300` | 78 | 65/78 | `src/wip/sub_08031300.c` | 83.3% (65/78) same-size DIFF; logic correct; decomp-permuter ran about 10,000 iterations and reached best score 1295 without zero | leave readable Thumb; revisit with a new register-allocation technique or a verified compiler/source-shape insight |

Per-function notes: `src/wip/<fn>.md`.

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_08033188` | `0x08033188` | 604 | 5 | pool | asm | (gMainWorkPtr, gBattleWork, gBtlInputMask, gBattl) |
| `sub_080436B0` | `0x080436B0` | 658 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08046E7C` | `0x08046E7C` | 872 | 3 | pool | asm | (gMainWorkPtr, gBtlInputMask, gBattlerArena/gBtlK) |
| `sub_08037430` | `0x08037430` | 216 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803C5DC` | `0x0803C5DC` | 220 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803C500` | `0x0803C500` | 220 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08036A68` | `0x08036A68` | 240 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0803D51C` | `0x0803D51C` | 304 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08038F30` | `0x08038F30` | 316 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08032908` | `0x08032908` | 384 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_08037508` | `0x08037508` | 452 | 2 | pool | asm | (gMainWorkPtr, gBattleWork) |
| `sub_0806F910` | `0x0806F910` | 624 | 2 | pool | asm | (gBtlObjListHead, gBtlObjListTail) |
| `sub_08032DC4` | `0x08032DC4` | 660 | 2 | pool | asm | (gBattleWork, gBattlerArena/gBtlKeysHeld) |
| `sub_08043B58` | `0x08043B58` | 54 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08043B90` | `0x08043B90` | 76 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033574` | `0x08033574` | 80 | 1 | pool | asm | (gBattleWork) |
| `sub_08052934` | `0x08052934` | 84 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08040EF4` | `0x08040EF4` | 88 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0803D4C4` | `0x0803D4C4` | 88 | 1 | pool | asm | (gBattleWork) |
| `sub_080449C4` | `0x080449C4` | 92 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042390` | `0x08042390` | 98 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08033084` | `0x08033084` | 100 | 1 | pool | asm | (gBattleWork) |
| `sub_08042784` | `0x08042784` | 100 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C2B0` | `0x0802C2B0` | 100 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042718` | `0x08042718` | 108 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08042630` | `0x08042630` | 116 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080426A4` | `0x080426A4` | 116 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080392D0` | `0x080392D0` | 116 | 1 | pool | asm | (gBattleWork) |
| `sub_08042540` | `0x08042540` | 120 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080425B8` | `0x080425B8` | 120 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08051BBC` | `0x08051BBC` | 124 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0802C55C` | `0x0802C55C` | 128 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080462D4` | `0x080462D4` | 130 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_0804245C` | `0x0804245C` | 140 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08031204` | `0x08031204` | 144 | 1 | pool | asm | (gBattleWork) |
| `sub_080442FC` | `0x080442FC` | 144 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08031C98` | `0x08031C98` | 150 | 1 | pool | asm | (gBattleWork) |
| `sub_08044FB0` | `0x08044FB0` | 156 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_080428F0` | `0x080428F0` | 160 | 1 | pool | asm | (gMainWorkPtr) |
| `sub_08062AF8` | `0x08062AF8` | 162 | 1 | pool | asm | (gMainWorkPtr) |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802B994` | `0x0802B994` | 58 | Unk7709C ROM table lookup keyed on *gMainWorkPtr->unk1690 — logic reconstructed correctly (same-size DIFF, 2/58 bytes short from a missing 2B) but every do/while/goto shape tried lands agbcc on push{lr}...pop{r1};bx r1 leaf framing that retail doesn't have (bx lr direct); same agbcc-extra-push-on-leaf class as sub_0802D8C4/sub_08061BDC; needs permuter |
| `sub_0802C62C` | `0x0802C62C` | 0 | counts gMainWorkPtr->unk1694[0..0x7F] entries with unk03==(s8)a — same-size DIFF (64B=64B!) across every declaration-order variant tried, purely a r2/r3/r4 register-choice swap (which var lands in the return register); 7000+ permuter iterations floor at score 95, never zero; needs permuter |
| `sub_0802D8C4` | `0x0802D8C4` | 24 | agbcc extra push {lr} on branch leaves |
| `sub_08030938` | `0x08030938` | 78 | computes a->unk2D8/unk2D4/unk00->unk30/unk00->unk34/nested sub_080674A0 fixed-point calls, then sub_080346C0(a, unk30, unk34, unk2D8, 0xB4-nested) with 5th arg on stack — logic correct across several forms but push-set (r4-r7 vs r4-r6) and stack-arg store ordering differ; needs permuter |
| `sub_08033530` | `0x08033530` | 0 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_08034894` | `0x08034894` | 84 | docs/battle.md: readable Thumb — agbcc prologue / pool ordering (no struct yet for param @ +0x30C flag / +0x300,0x302,0x304 fields) |
| `sub_08038314` | `0x08038314` | 0 | battle countdown gate: a->unk304-- then flush-condition on gBtlKeysHeld&3, else store v to a->unk2FC and sub_08062044 x4 on gBattleWork->unk19C[0..3] — logic reconstructed correctly (same-size DIFF, 5/108 bytes), several source shapes (inline expr, cached local, array-index cast) all land agbcc on the same reordering (mask loaded+ANDed before vs after the #3 immediate load); needs permuter (base score 70, 20k+ iterations without a zero) |
| `sub_0803DBD0` | `0x0803DBD0` | 80 | 2D ROM table lookup (gUnk_080796DC[a][gMainWorkPtr->unk1818] / gUnk_08097458[unk1818] fallback) — retail leaf is bx lr with no push at all; every C shape tried (both branch orders) needs push{lr}/pop{r1} for one extra temp register (80B retail vs 84B compiled); same agbcc-extra-push-on-leaf class; needs permuter |
| `sub_080428C4` | `0x080428C4` | 44 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_0804495C` | `0x0804495C` | 60 | 32-halfword table copy (gUnk_08094E00[gMainWorkPtr->unk181F] -> PLTT 0x050001C0) — void(void) leaf, same agbcc-extra-push-on-leaf framing as sub_0802B994 (60B retail vs 64B compiled, same shape every C form tried); needs permuter |
| `sub_08045128` | `0x08045128` | 80 | reads gMainWorkPtr->unk1688[idx].unk08 into unk1788, computes base = gMainWorkPtr->unk168C + idx*8032 (retail's literal shift/sub chain), calls sub_08045590(base,0) — logic correct (same-size DIFF, ~14/80 bytes differ) across many pointer-arithmetic orderings tried; needs permuter for the base-pointer scheduling |
| `sub_08045C5C` | `0x08045C5C` | 136 | gMainWorkPtr->unk1710[25..26] input-repeat debouncer keyed on gBtlInputMask==0xFC00 — logic reconstructed correctly but agbcc drops r7 from the push set (r4-r6+lr, 140B) vs retail's r4-r7+lr (136B); tried inline/cached-local/branch-order variants, all land on the same 4B-over shape; needs permuter |
| `sub_080473E4` | `0x080473E4` | 20 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_080475C4` | `0x080475C4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_080475F4` | `0x080475F4` | 48 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_08049F98` | `0x08049F98` | 144 | sound/anim trigger sequencer: sub_080617C4 x2, sub_080615EC x3 with idx<<4+8/+0x10 offsets, sub_0806171C x3 with sub_08061784()<<16>>17 — m2c fails to reconstruct (r8 stack-saved 3rd param); multiple hand-written + register-pinned C forms all land 8 bytes over; needs permuter |
| `sub_0804E17C` | `0x0804E17C` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A83F4); same blocker |
| `sub_08051578` | `0x08051578` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A85A4); same blocker |
| `sub_080523A4` | `0x080523A4` | 112 | calls sub_08061BE8, sub_0805264C(a,0..5), then a->unk288->unk0C = a->unk28C->unk0C = (a->unk2D5<<12)+0x2C00 — logic correct (same-size DIFF, ~15/112 bytes) across several pointer/base-register orderings; needs permuter |
| `sub_08053218` | `0x08053218` | 144 | byte-identical to sub_08049F98 (different embedded const 0x083A8724); same blocker |
| `sub_080601C4` | `0x080601C4` | 0 | r8 pool pin — permuter best score ~100 |
| `sub_080604C8` | `0x080604C8` | 112 | byte-swaps 6 u8 pairs from *gUnk_03000750 into u16 fields, writes them to REG_BG palette-ish IO regs 0x04000040-0x0400004A — logic correct; real remaining gap is a 4-byte tail-fold (agbcc collapses the last out=out+2;*out=val into strh [r0,#2] when out isn't used again, unlike retail which keeps the explicit adds+strh[0]); several dependency-shape rewrites (loop, pre-increment, reordering) all land 4B short; needs permuter |
| `sub_080615EC` | `0x080615EC` | 36 | branchy asm — agbcc compile fail |
| `sub_08061BDC` | `0x08061BDC` | 12 | agbcc extra push {lr} on null-check leaf |
| `sub_08061E40` | `0x08061E40` | 20 | agbcc extra push {lr} on null-check leaf |
| `sub_08062634` | `0x08062634` | 12 | agbcc extra push {lr} on null-check leaf |
| `sub_08062728` | `0x08062728` | 18 | u32 zero-fill loop (a->unk04[i]=0 for i<a->unk08) — retail uses stm r0!,{r3} leaf loop (18B), agbcc compiles any equivalent C to a push/pop-framed indexed loop (32B); needs permuter or specific idiom to trigger stm codegen |
| `sub_08062C80` | `0x08062C80` | 0 | calls _08073C4C(0, dst, size, src) at raw address 0x08073C4C twice (VRAM/PLTT clear via CpuFastSet-style primitive) — that callee has no C symbol/prototype anywhere in the codebase yet (only referenced via bl _08073C4C from naked asm in many other unconverted functions); needs the callee named/prototyped first |
| `sub_08062CF4` | `0x08062CF4` | 48 | BGR555 color pack (inverse of sub_08062CC8/sub_08062D24): rgb[0..2] -> u16 @ PLTT 0x05000200+idx*2 — logic reconstructed correctly (same-size DIFF, ~1 instruction reordered) across many register-pinned variants; retail keeps r6 live (push {r4,r5,r6,lr}) but my C never needed r6 pressure, changing push set; needs permuter |
| `sub_0806A6F8` | `0x0806A6F8` | 436 | docs/battle.md: readable Thumb — large input hub (436B, 6 IWRAM refs) |
| `sub_0806FEFC` | `0x0806FEFC` | 44 | BtlObjNode move-to-tail (gBtlObjListHead/Tail) — agbcc inserts extra push {lr}/pop{r1}+bx r1 frame on this null-check leaf like sub_0802D8C4/sub_08061BDC; same-size DIFF on direct-return form, +12B with early-return form; needs permuter |
| `sub_0806FF28` | `0x0806FF28` | 48 | BtlObj unlink+push-to-head (obj->unk19 early return) — same agbcc extra push{lr} frame quirk as sub_0806FEFC; +4B DIFF; needs permuter |
| `sub_08073114` | `0x08073114` | 112 | BtlObjTable scan+remove (loop over gBtlObjTable[0..gBtlObjTableCount) matching entry->key==obj, calls sub_0806A434/sub_08067B98) — logic reconstructed correctly (same-size DIFF on every variant tried) but agbcc compiles the do-while as pre-test loop + different table-pointer register placement than retail; needs permuter or deeper agbcc loop-codegen trick |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c --status "…" --next "…"
python3 tools/decomp/match_function.py sub_XXXXXXXX src/wip/sub_XXXXXXXX.c
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/function_scores.py --close
python3 tools/decomp/script_first.py
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/cluster_shapes.py
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
```

Full ranked backlog (316 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
