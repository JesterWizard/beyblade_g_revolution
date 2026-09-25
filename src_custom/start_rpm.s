@ sub_0803CECC writes 9216 to BattleWork+0xBC4/+0xBC8, then computes
@ player[0].rpm into Unk002A0+0x0C and copies it to +0x13C, +0x144, and +0xBB4.
@ Live spin climbs in +0xBBC and is clamped to +0xBC4. The first 16 bytes are
@ the LynJump stub; execution resumes at 0x0803CEDC with r5/r1/r2/r0 set.
@ setRPMTo is the word at RuntimeConfig offset 4. 0 leaves retail RPM.
@ 1..99999 replaces player 0's launch RPM and the spin cap.

.equ SET_RPM_FIELD, 4

.syntax unified
.section .append_text, "ax"
.thumb
.align 2
.global StartRpm__Replacement
.thumb_func
StartRpm__Replacement:
	ldr r0, .Lconfig
	ldr r0, [r0, #SET_RPM_FIELD]
	cmp r0, #0
	beq .Lframe
	push {lr}
	ldr r0, .Lfinish
	movs r1, #1
	orrs r0, r0, r1
	mov lr, r0
.Lframe:
	push {r4, r5, r6, r7, lr}
	ldr r5, .Lbattle
	ldr r1, [r5]
	movs r2, #144
	lsls r2, r2, #6
	ldr r3, .Lbc4
	adds r0, r1, r3
	str r2, [r0]
	ldr r0, .Lcont
	bx r0

.align 2
.Lconfig:
	.word gRuntimeConfigRom
.Lfinish:
	.word StartRpm_Finish
.Lbattle:
	.word 0x03000290
.Lbc4:
	.word 0x00000BC4
.Lcont:
	.word 0x0803CEDD

.thumb_func
StartRpm_Finish:
	ldr r0, .Lconfig2
	ldr r1, [r0, #SET_RPM_FIELD]
	ldr r2, .Lcap
	cmp r1, r2
	bls .Luse
	adds r1, r2, #0
.Luse:
	ldr r0, .Lbattle2
	ldr r0, [r0]
	ldr r2, .Lbb4
	adds r3, r0, r2
	str r1, [r3]
	ldr r2, .Lbbc
	adds r3, r0, r2
	str r1, [r3]
	ldr r2, .Lbc4b
	adds r3, r0, r2
	str r1, [r3]
	ldr r2, .L13c
	adds r3, r0, r2
	str r1, [r3]
	ldr r2, .L144
	adds r3, r0, r2
	str r1, [r3]
	ldr r0, .Lslot
	str r1, [r0, #12]
	pop {r0}
	bx r0

.align 2
.Lconfig2:
	.word gRuntimeConfigRom
.Lcap:
	.word 99999
.Lbattle2:
	.word 0x03000290
.Lbb4:
	.word 0x00000BB4
.Lbbc:
	.word 0x00000BBC
.Lbc4b:
	.word 0x00000BC4
.L13c:
	.word 0x0000013C
.L144:
	.word 0x00000144
.Lslot:
	.word 0x030002A0
