# Decompilation queue

_Auto-generated. Edit pins/blockers in [`decomp-queue.toml`](decomp-queue.toml); refresh with `make queue` or `python3 tools/decomp/next_queue.py --write`._

_Updated: 2026-09-29T18:32:06Z_

## Summary

| Metric | Count |
|--------|------:|
| Semantic C done | 606 |
| Still need semantic C | **27** |
| Readable Thumb remaining | 27 |
| Opcode embeds remaining | 0 |
| Battle pending | 7 (151 already semantic) |
| Blocked (documented) | 20 |
| WIP (resume these first) | 24 |

Ranking: **battle** · showing top **40**

Park unmatched C in [`src/decompiled/`](../src/decompiled/README.md) — see [`decomp-wip.md`](decomp-wip.md).

## Resume (WIP)

_Parked C — do not start these from disasm. Read `notes`, then `match_function.py` the `seed`._

| Function | Bytes | Score | Seed | Status | Next |
|----------|------:|-------|------|--------|------|
| `sub_08035624` | 114 | 20/114 | `src/decompiled/sub_08035624.c` | two attempts: 20/114 bytes, 112B candidate both times; logic and fields match, but agbcc omits retail's pushed r5/type-copy register and changes the prologue | Force a genuinely live selector copy in r5 or use a targeted source/permuter register search; preserve signed-byte delta and Unk705DC +0x22 |
| `sub_08038D68` | 112 | 37/112 | `src/decompiled/sub_08038D68.c` | two attempts: direct semantic seed 15/112 (108B); pinned base/table registers 37/112 but expanded to 120B. Data flow and both Unk705DC output writes are correct; register pressure/order remains | Use the direct field algorithm with a targeted r5 base/r2 table search; avoid the current over-constraining dual register pins and preserve the 112-byte retail size |
| `sub_08035054` | 432 | 80/432 | `src/decompiled/sub_08035054.c` | Rewritten seed (old_agbcc, u16 id local, data symbols) is structurally exact; only register allocation differs: retail src=r7, pos=r8, ours pos=r7, src=r8, which costs 8B (mov via r8). Permuter best 301 (376/432 same-size) only by dropping the src=NULL init. | Find the source shape that gives src higher global-alloc priority than pos (decl/init order sweeps, u8 params and else-NULL all failed). |
| `sub_08038438` | 240 | 45/240 | `src/decompiled/sub_08038438.c` | for-loop seed with slots=&gData_030003CC + _call_via_r3 fn-pointer call is same-size (old_agbcc 45/240). Retail keeps both loops' found-blocks inline (no loop-exit block motion), so *slots reloads every pass; agbcc/old_agbcc move the found blocks out of the loops. | Find a loop shape that stops loop.c moving the exit blocks (break + flag, goto-free) while keeping the hoisted r7/r8/r5 in loop 2. |
| `sub_08045C5C` | 136 | 127/136 | `src/decompiled/sub_08045C5C.c` | Rewritten with the gData_03003F60 / gData_03000198 data symbols (plain reads, no local pointers): 93/136 -> 127/136, same size. Only the prologue differs: retail loads the 0xFC00 sentinel before copying the mask address into r4 and does the ldrh through r4. | Find the shape that puts `movs r1,#0xFC; lsls` between the address load and the copy (sentinel local, comparison order and volatile views tried). Permuter 480s: best 220. |
| `sub_08069270` | 244 | 24/244 | `src/decompiled/sub_08069270.c` | Logic mapped (horizontal wrap split into two blits; fn = 0x0806945D or gData_080BB8A4[0]; wrap-off path uses gData_080BB8A8[0]). Separate e1/e2/h1/h2 copies reproduce retail's stack spills; remaining diff is register choice: retail keeps d in r3 and end in r5, ours copies d to r6 (+2B). Permuter (2 rounds) reached 25 only via uninitialised-variable tricks. | Find a source shape that leaves d in its argument register (d is only read by the first blit); try the permuter from this seed with a longer budget. |
| `sub_0806960C` | 600 | 226/600 | `src/decompiled/sub_0806960C.c` | BG map streaming (scroll by dx/dy, stream a column/row of tiles through sub_08069270 when the view crosses the loaded rect, wrap on unk7C bits). Logic complete, same size. Retail spills tile/edge/source/start values to 8 consecutive stack words (sp0C..sp28) and keeps the constant 1 in r10; a local Unk688C8Rect + start[2] gets closest. | Find the local aggregate shape that yields the sp0C..sp28 layout while keeping CSE of the stored values; one = 1 local helps the prologue. |
| `sub_08043DB4` | 1352 | 1031/1352 | `src/decompiled/sub_08043DB4.c` | Fixed REG_BLDY -> REG_BLDALPHA (retail stores 0 to 0x04000052). Remaining: retail keeps the -1 compared against unk18B4 in a stack slot (sp+0x18). local-alloc's update_equiv_regs moves a set-once/used-once constant next to its use, so any `none = -1` local is rematerialised. | The -1 needs a pseudo with a second, different set (no REG_EQUIV) that still gets no hard register. A volatile local gives the right 0x1C frame but the wrong slot order (sp10 instead of sp18). |
| `sub_08044A8C` | 672 | 613/672 | `src/decompiled/sub_08044A8C.c` | Same size. `hdr = unk1688; hdr += i;` fixed the base-before-index order at both header reads (602 -> 613). Left: buf/retry register swap at the top (retail buf=r7, retry=r5) and the unk1688 base register (retail r4) in the per-slot checks. | Retail copies *hdrBlock into r3 and only later into r7: find the statement shape that creates that copy. Permuter 480s from this seed: best 425. |
| `sub_08040680` | 308 | one-insn diff (304 vs 308 B) | `src/decompiled/sub_08040680.c` | logic exact; one diff: BtlObjTableAdd result copied to r1 before the unk834 store in retail (ours stores from r0) | local-alloc shape for the buffer store; permuter 5 min found nothing |
| `sub_0803E0CC` | 296 | 170/296 | `src/decompiled/sub_0803E0CC.c` | Data symbol gData_03000198 plus `unk1C |= (s8)0xFF` (keeps the ldrb/orr/strb instead of folding to strb -1): 56 -> 170/296. Still 4 bytes short: retail hoists the unk1C offset into r10, ours keeps it in r3 and caller-saves it to the stack. | Get the loop-invariant 0x8EC offset into a callee-saved register (r10); old_agbcc is required. |
| `sub_0804BD38` | 328 | 56 asm diff lines | `src/decompiled/sub_0804BD38.c` | logic mapped (5-row menu redraw); retail makes i*16 a giv in r9 and keeps a on the stack, ours hoists &gData_03000674 instead | find the loop shape that makes the row-y giv; try permuter |
| `sub_080737C0` | 336 | 61/336 | `src/decompiled/sub_080737C0.c` | logic mapped (word wrap into <=count lines); retail keeps the done flag in a stack slot and tests count from the stack | while(!done) shape is closest (81 diff lines); find what spills done |
| `sub_08044648` | 364 | 135/364 | `src/decompiled/sub_08044648.c` | New semantic draft from scratch (the old one was a junk stub); roster is gData_08075AB8 (struct BeybladeDef[]). Same size, logic exact. Left: retail loads the table base before computing id*28 (ours computes the offset first), which swaps r6/r7; a `s16 key` local for the two GetIndexedRecordWord calls duplicates the loop test. | Same table-base-first problem as sub_080447E8. A local table pointer gets hoisted out of the loop by loop.c; look for a shape that keeps the symbol load inside the if and before the multiply. |
| `sub_080447E8` | 372 | 232/372 | `src/decompiled/sub_080447E8.c` | New semantic draft (sibling of sub_08044648, table gData_0807BE04, Unk7BE04 fields named). Logic exact, 4 bytes long; retail loads the table symbol before id*28 and keeps it in r8. | Solve the table-base-first order (see sub_08044648), then the loop-test duplication. |
| `sub_0804C8BC` | 372 | 74/372 | `src/decompiled/sub_0804C8BC.c` | New semantic draft (the old one was a junk stub): five list rows from gData_080989F0 (struct Unk4C8BCRow). Logic exact, 4 bytes long. Retail has five loop givs (palette pointer, i*4, two row givs, i*16) and copies the i*16 giv into a stack local for the sprite y; every shape tried either drops the i*16 giv or adds a (y+0x38)<<8 giv. | Find the source form of the sprite y ((i*16 + 0x38) << 8) that reuses the i*16 giv through a copy. |
| `sub_08070930` | 420 | 199/420 | `src/decompiled/sub_08070930.c` | New semantic draft: append glyphs to a text sprite group (Unk7069C, now with the unk14 Unk700CCHdr chain). old_agbcc. Early exits must fall off the end (no return, retail returns the zero in r0). 8 bytes short: retail keeps the two affine-size checks as separate code paths on two copies of the affine pointer (r1 and r8), and the glyph loop test is duplicated at the top. | Find why retail has two pseudos for the affine pointer; that also un-merges the loop tests. |
| `sub_080618EC` | 428 | 108/428 | `src/decompiled/sub_080618EC.c` | New semantic draft: typewriter text tick (struct Unk618EC). Logic mapped; size mismatch. Retail tests the u8 state with ldrb straight into r3 and later ORs 0xFF into that same register; our shapes either copy the load or fold state|0xFF to 0xFF. | Get the state load to keep its value for the later `|= 0xFF` without cse knowing it equals 1; then fix the switch/control-code tail. |
| `sub_0806314C` | 404 | 175/404 | `src/decompiled/sub_0806314C.c` | palette fade step, 400/404 | offset i*2 spilled at sp+8 in retail |
| `sub_08060E48` | 532 | 92/532 | `src/decompiled/sub_08060E48.c` | text glyph blit 528/532; regalloc: retail spills 9 address pseudos | gw in r9, rows/yt next-iter in sp24/28; permuter |
| `sub_0806EC20` | 516 | ?/516 | `src/decompiled/sub_0806EC20.c` | BG setup 500/516; param copy order matches | a in r5,b in r8 (ours r7/r10); i<<24 copy r6 |
| `sub_0806E060` | 492 | 89/492 | `src/decompiled/sub_0806E060.c` | bezier keyframe sampler 468/492 | idx in r10, f in r12, p0/p1 in sp0/sp4; 0x180 not folded |
| `sub_0806B764` | 0 | 509/588 | `src/decompiled/sub_0806B764.c` | TextLayerInit same-size 509/588, old_agbcc | a reload gets r4 not r7; 0x80 test operand order |
| `sub_08067CE8` | 548 | 258/548 | `src/decompiled/sub_08067CE8.c` | AnimObjDraw same-size 548, structure matches; only regalloc (a=r5,px=r4,py=r7,slot=r6 in retail) | raise px priority over a; m3 mask var, pin vars, out[3] all matter |

Per-function notes: `src/decompiled/<fn>.md`.

## Recommended next

| Function | Address | Bytes | Battle refs | Pool | Kind | Notes |
|----------|---------|------:|------------:|:----:|------|-------|
| `sub_080706B0` | `0x080706B0` | 626 | 0 | pool | asm | |
| `sub_0806C7D4` | `0x0806C7D4` | 1302 | 0 |      | asm | |

## Blocked

| Function | Address | Bytes | Reason |
|----------|---------|------:|--------|
| `sub_0802C62C` | `0x0802C62C` | 0 | counts gMainWorkPtr->unk1694[0..0x7F] entries with unk03==(s8)a — same-size DIFF (64B=64B!) across every declaration-order variant tried, purely a r2/r3/r4 register-choice swap (which var lands in the return register); 7000+ permuter iterations floor at score 95, never zero; needs permuter |
| `sub_08030938` | `0x08030938` | 0 | computes a->unk2D8/unk2D4/unk00->unk30/unk00->unk34/nested sub_080674A0 fixed-point calls, then sub_080346C0(a, unk30, unk34, unk2D8, 0xB4-nested) with 5th arg on stack — logic correct across several forms but push-set (r4-r7 vs r4-r6) and stack-arg store ordering differ; needs permuter |
| `sub_08033530` | `0x08033530` | 0 | battle state branch — subs r2 #0x6C vs direct unk201C pool (same-size DIFF) |
| `sub_08034894` | `0x08034894` | 0 | docs/battle.md: readable Thumb — agbcc prologue / pool ordering (no struct yet for param @ +0x30C flag / +0x300,0x302,0x304 fields) |
| `sub_08038314` | `0x08038314` | 0 | battle countdown gate: a->unk304-- then flush-condition on gBtlKeysHeld&3, else store v to a->unk2FC and sub_08062044 x4 on gBattleWork->unk19C[0..3] — logic reconstructed correctly (same-size DIFF, 5/108 bytes), several source shapes (inline expr, cached local, array-index cast) all land agbcc on the same reordering (mask loaded+ANDed before vs after the #3 immediate load); needs permuter (base score 70, 20k+ iterations without a zero) |
| `sub_080428C4` | `0x080428C4` | 0 | docs/battle.md: readable Thumb — C adds push {lr} (same extra-prologue quirk as sub_0806FEFC family) |
| `sub_08045C5C` | `0x08045C5C` | 136 | gMainWorkPtr->unk1710[25..26] input-repeat debouncer keyed on gBtlInputMask==0xFC00 — logic reconstructed correctly but agbcc drops r7 from the push set (r4-r6+lr, 140B) vs retail's r4-r7+lr (136B); tried inline/cached-local/branch-order variants, all land on the same 4B-over shape; needs permuter |
| `sub_080473E4` | `0x080473E4` | 0 | dual IWRAM zero — agbcc pool order / CSE of 0x634 and 0x63C (permuter best ~5) |
| `sub_08049F98` | `0x08049F98` | 0 | sound/anim trigger sequencer: sub_080617C4 x2, sub_080615EC x3 with idx<<4+8/+0x10 offsets, sub_0806171C x3 with sub_08061784()<<16>>17 — m2c fails to reconstruct (r8 stack-saved 3rd param); multiple hand-written + register-pinned C forms all land 8 bytes over; needs permuter |
| `sub_0804E17C` | `0x0804E17C` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A83F4); same blocker |
| `sub_08051578` | `0x08051578` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A85A4); same blocker |
| `sub_08053218` | `0x08053218` | 0 | byte-identical to sub_08049F98 (different embedded const 0x083A8724); same blocker |
| `sub_080601C4` | `0x080601C4` | 0 | r8 pool pin — permuter best score ~100 |
| `sub_080604C8` | `0x080604C8` | 0 | byte-swaps 6 u8 pairs from *gUnk_03000750 into u16 fields, writes them to REG_BG palette-ish IO regs 0x04000040-0x0400004A — logic correct; real remaining gap is a 4-byte tail-fold (agbcc collapses the last out=out+2;*out=val into strh [r0,#2] when out isn't used again, unlike retail which keeps the explicit adds+strh[0]); several dependency-shape rewrites (loop, pre-increment, reordering) all land 4B short; needs permuter |
| `sub_08062728` | `0x08062728` | 0 | u32 zero-fill loop (a->unk04[i]=0 for i<a->unk08) — retail uses stm r0!,{r3} leaf loop (18B), agbcc compiles any equivalent C to a push/pop-framed indexed loop (32B); needs permuter or specific idiom to trigger stm codegen |
| `sub_08062C80` | `0x08062C80` | 0 | calls _08073C4C(0, dst, size, src) at raw address 0x08073C4C twice (VRAM/PLTT clear via CpuFastSet-style primitive) — that callee has no C symbol/prototype anywhere in the codebase yet (only referenced via bl _08073C4C from naked asm in many other unconverted functions); needs the callee named/prototyped first |
| `sub_08062CF4` | `0x08062CF4` | 0 | BGR555 color pack (inverse of sub_08062CC8/sub_08062D24): rgb[0..2] -> u16 @ PLTT 0x05000200+idx*2 — logic reconstructed correctly (same-size DIFF, ~1 instruction reordered) across many register-pinned variants; retail keeps r6 live (push {r4,r5,r6,lr}) but my C never needed r6 pressure, changing push set; needs permuter |
| `sub_0806A6F8` | `0x0806A6F8` | 436 | docs/battle.md: readable Thumb — large input hub (436B, 6 IWRAM refs) |
| `sub_08073114` | `0x08073114` | 0 | BtlObjTable scan+remove (loop over gBtlObjTable[0..gBtlObjTableCount) matching entry->key==obj, calls sub_0806A434/sub_08067B98) — logic reconstructed correctly (same-size DIFF on every variant tried) but agbcc compiles the do-while as pre-test loop + different table-pointer register placement than retail; needs permuter or deeper agbcc loop-codegen trick |
| `sub_08074144` | `0x08074144` | 2 | single instruction 'mov pc, lr' (2B) — semantically identical to bx lr but a different opcode; agbcc never emits mov pc,lr for an empty C function (only bx lr), so this must stay naked asm |

## Commands

```bash
make queue                              # refresh this file
python3 tools/decomp/next_queue.py -n 10
python3 tools/decomp/park_wip.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c --status "…" --next "…"
python3 tools/decomp/match_function.py sub_XXXXXXXX src/decompiled/sub_XXXXXXXX.c
python3 tools/decomp/try_convert.py sub_XXXXXXXX --integrate
python3 tools/decomp/function_scores.py --close
python3 tools/decomp/script_first.py
python3 tools/decomp/agent_packet.py --next
python3 tools/decomp/cluster_shapes.py
python3 tools/decomp/c_patterns.py --list
python3 tools/decomp/battle_scan.py -n 20
```

Full ranked backlog (2 functions): [`decomp-queue.json`](decomp-queue.json)

Patterns: [`decomp-patterns.md`](decomp-patterns.md)
