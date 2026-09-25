@ sub_08037F98, at file offset $380E0. r2 is BattleWork+0x138 and r0 is
@ +0x139. Reaching here means r2 <= r0. Equal is a draw (branch to $3814C).
@ Less is a loss: retail then exempts battle modes 7, 8, 9, 10 and 11, and a
@ last remaining blade. keepBeybladeOnLoss takes that same spare path.
@ The LynJump stub occupies the first 16 bytes; flag-off resumes at $380F0
@ with r0 holding the mode word from 0x030002A0+0x2C.
@ keepBeybladeOnLoss is RuntimeConfig offset 11.

.equ KEEP_BLADE_FIELD, 11

.syntax unified
.section .append_text, "ax"
.thumb
.align 2
.global KeepBladeOnLoss__Replacement
.thumb_func
KeepBladeOnLoss__Replacement:
	cmp r2, r0
	bcs .Ldraw
	ldr r1, .Lconfig
	ldrb r1, [r1, #KEEP_BLADE_FIELD]
	cmp r1, #0
	bne .Lspare
	ldr r0, .Lwork
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
.Lconfig:
	.word gRuntimeConfigRom
.Lwork:
	.word 0x030002A0
.Lresume:
	.word 0x080380F1
.LdrawAddr:
	.word 0x0803814D
.LspareAddr:
	.word 0x08038145
