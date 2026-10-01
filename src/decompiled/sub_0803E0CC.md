# sub_0803E0CC — WIP

| | |
|--|--|
| ROM | `0x0803E0CC` |
| Retail | |
| `src/matched` | readable Thumb |
| Seed | `src/decompiled/sub_0803E0CC.c` |
| Last `match_function.py` | 56/296
| Sibling / types | |

## Role

(one sentence)

## Process

- 2026-09-28 — parked. Status: logic mapped (release all slots with unk23 == id); s8 unk1C |= 0xFF folds to strb -1, retail keeps ldrb/orr; loop.c hoists different constants

## Current state

logic mapped (release all slots with unk23 == id); s8 unk1C |= 0xFF folds to strb -1, retail keeps ldrb/orr; loop.c hoists different constants

## Next

unk1C likely a u8 view / bitfield here; other users need s8

## Process (final sweep)

- 2026-09-28 (final sweep): Data symbol gData_03000198 plus `unk1C |= (s8)0xFF` (keeps the ldrb/orr/strb instead of folding to strb -1): 56 -> 170/296. Still 4 bytes short: retail hoists the unk1C offset into r10, ours keeps it in r3 and caller-saves it to the stack. Next: Get the loop-invariant 0x8EC offset into a callee-saved register (r10); old_agbcc is required.

- 2026-10-01 (allocation analysis, still unmatched; draft stays at 170/296 under old_agbcc):
  Retail keeps the two loop-invariant constants K23 (0x8F3 -> r8) and K1C (0x8EC -> r10) plus id (r9) in hi regs; ours gives K1C to r3 via caller-save (`str r3,[sp]`/`ldr r3,[sp]` around DebugPrint), which also forces B (the unk23 byte) out of its register (`mov r12,r0`). global.c only tries caller-save when no callee-saved lo reg is free *and* 4*calls < refs, and K1C/K23 have refs=5 in ours. Debug-compiler hacks (env REFADJ `pseudo:delta` in global.c, NOCS to disable caller-save) show that K23 refs<=4, K1C refs<=3 and B's priority below G's (B refs 2) reproduce retail's hi-reg order (r8=K23, r9=id, r10=K1C), G=r1, B=r2 and the all-r3 reload scratch -- but nothing in source found yet lowers the weights (do-while only raises them; for/while/do/goto loop forms, `continue`, nested ifs, decl order, compare operand order all give identical or worse allocation). `(s16)(u16)id` / swapped compare make ours fold the sign-extension out of the loop (wrong). Retail also reserves a 4-byte stack slot it never uses (caller-save slot of a pseudo later evicted by reload), so the real source probably has K1C allocated r3 first and evicted at the id copy; our reload evicts B instead because uses(B)=4 < uses(K1C)=5.

- 2026-10-01 — **MATCHED** (296/296, old_agbcc). The missing piece was a third DebugPrint argument: the format string at 0x0833D34C is `"(%s) : %d\n"`, so the call is `DebugPrint(fmt, "removeBladeFromTysonsCollection", slot.unk23)`. Retail passes the already-loaded unk23 byte in r2 with no move, which keeps it live up to the call. That gives it r2 and pushes G into r1, and it makes reload evict the caller-saved 0x8EC constant from r3 (to r10) instead of evicting the byte. The empty `add sp,#-4` slot left by that eviction was the clue. The prototype stays `s16` (caller sub_0802C55C needs it); `u16 id = a;` in the body gives retail's zero-extension.
