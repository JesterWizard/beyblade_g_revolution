@ The BgmPlay (sub_0805FED4) hook at 0x0805FEF4.
@
@ Retail, after BgmStop, sub_080674B4 and `bgmTrack = r4; bgmHandle = -1`:
@
@     0805FEF4  cmp  r4, #0x10
@     0805FEF6  bls  0x0805FEFA
@     0805FEF8  b    0x0806011E              @ epilogue: pop {r4}; pop {r0}; bx r0
@     0805FEFA  lsls r0, r4, #2              @ jump table at 0x0805FF10
@     0805FEFC  ldr  r1, [pc, #0xC]
@     0805FEFE  adds r0, r0, r1
@     0805FF00  ldr  r0, [r0]
@     0805FF02  mov  pc, r0
@
@ The hook replaces those 16 bytes, so this code runs them itself. r4 is the
@ track, the stack holds BgmPlay's {r4, lr}.
@
@  - track >= 17: a custom track; start it, return.
@  - a retail track tracks.txt replaces: let the retail case run (it sets up the
@    timers and state that go with the track), but return into CustomBgmAfter
@    through a stacked copy of the epilogue frame; that swaps in the custom track.
@  - anything else: the retail code, unchanged.

	.syntax unified
	.thumb
	.align 2
	.global CustomBgmDispatch
	.thumb_func
CustomBgmDispatch:
	adds r0, r4, #0
	bl CustomBgmFind
	cmp r0, #0
	blt .Lretail
	cmp r4, #17
	bhs .Lcustom
	ldr r0, .LAfter
	push {r0}
	push {r4}
	b .Ltable

.Lcustom:
	adds r0, r4, #0
	bl CustomBgmStart
	b .Lepilogue

.Lretail:
	cmp r4, #0x10
	bhi .Lepilogue
.Ltable:
	lsls r0, r4, #2
	ldr r1, .Lcases
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0

.Lepilogue:
	ldr r0, .Lepi
	bx r0

	.align 2
.Lcases:
	.4byte 0x0805FF10
.Lepi:
	.4byte 0x0806011F
.LAfter:
	.4byte CustomBgmAfter

@ The retail case has finished and its epilogue popped the frame pushed above:
@ r4 is the track again and the stack holds BgmPlay's own {r4, lr}.
	.thumb_func
CustomBgmAfter:
	adds r0, r4, #0
	bl CustomBgmStart
	b .Lepilogue
