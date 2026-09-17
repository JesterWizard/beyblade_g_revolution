/* asm prelude prepended to target.s by decomp-permuter import.py. */

.macro glabel label
	.global \label
	.type \label, %function
	.thumb_func
\label:
.endm

.syntax unified
.text
.thumb
