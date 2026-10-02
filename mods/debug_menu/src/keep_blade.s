@ "Infinite BeyBlade Health": do not lose the equipped beyblade after a loss.
@
@ Hooks sub_08037F98 (battle result) at 0x080380E0, where r2 is BattleWork+0x138
@ and r0 is +0x139. The hook replaces these 16 retail bytes:
@     cmp  r2, r0
@     bcs  0x0803814C                 @ equal or higher: draw / win
@     ldr  r0, =0x030002A0 ; ldr r0, [r0, #0x2C]
@     cmp  r0, #11 ; beq 0x08038144   @ battle mode 11: spare the blade
@     cmp  r0, #8  ; beq 0x08038144   @ battle mode 8: spare the blade
@ and resumes at 0x080380F0 (modes 7, 10, 9 and the last-blade check).
@ Below is a loss; with the entry on it takes the same "spare" exit as mode 8/11.

	.syntax unified
	.thumb
	.align 2
	.global KeepBladeOnLoss__Hook
	.thumb_func
KeepBladeOnLoss__Hook:
	cmp r2, r0
	bcs .Ldraw
	ldr r1, .Lflag
	ldrb r1, [r1]
	cmp r1, #0
	bne .Lspare
	ldr r0, .Lbattle
	ldr r0, [r0, #0x2c]
	cmp r0, #11
	beq .Lspare
	cmp r0, #8
	beq .Lspare
	ldr r1, .Lresume
	bx r1
.Ldraw:
	ldr r1, .LdrawAddr
	bx r1
.Lspare:
	ldr r1, .LspareAddr
	bx r1

	.align 2
@ gDebug.value[DBG_INF_BEYBLADE_HEALTH]: 4 bytes of magic, then the entry index.
.Lflag:
	.word gDebug + 4 + 10
.Lbattle:
	.word 0x030002A0
.Lresume:
	.word 0x080380F1
.LdrawAddr:
	.word 0x0803814D
.LspareAddr:
	.word 0x08038145
