@ Defaults for the two functions mods/custom_music defines (BGM tracks after the
@ retail 17). Weak, so the real ones win when that mod is built along with this one.
	.syntax unified
	.thumb
	.align 2
	.weak CustomBgmCount
	.thumb_func
CustomBgmCount:
	movs r0, #0
	bx lr

	.weak CustomBgmName
	.thumb_func
CustomBgmName:
	movs r0, #0
	bx lr
