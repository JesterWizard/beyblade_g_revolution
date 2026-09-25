@ sub_08041E88 copies its speed argument to MainWork+0x17B0, then
@ switches on the direction in r0. The overworld frame passes 0x100, or
@ 0x200 while B is held. The first 16 bytes are this stub. Retail resumes
@ at 0x08041E98 with r2 still the direction and the cmp r2, #16 flags set.
@ overworldSpeed is RuntimeConfig offset 14. 1 leaves the step unchanged.

.equ OVERWORLD_SPEED_FIELD, 14

.syntax unified
.section .append_text, "ax"
.thumb
.align 2
.global OverworldSpeed__Replacement
.thumb_func
OverworldSpeed__Replacement:
	push {lr}
	adds r2, r0, #0
	ldr r0, .Lconfig
	ldrb r0, [r0, #OVERWORLD_SPEED_FIELD]
	muls r1, r0
	ldr r0, .Lmain
	ldr r0, [r0]
	ldr r3, .Lspeed
	adds r0, r0, r3
	str r1, [r0]
	cmp r2, #16
	ldr r3, .Lresume
	bx r3

.align 2
.Lconfig:
	.word gRuntimeConfigRom
.Lmain:
	.word 0x03000198
.Lspeed:
	.word 0x000017B0
.Lresume:
	.word 0x08041E99
