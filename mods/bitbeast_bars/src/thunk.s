@ Retail calls `bl _080740B0` (gauge, 12) with the fighter in r4. C cannot see
@ r4, so pass it as the third argument and tail-call the real function.
	.syntax unified
	.thumb
	.align 2
	.global BitBeastBarsThunk
	.thumb_func
BitBeastBarsThunk:
	adds r2, r4, #0
	ldr r3, .Lbars
	bx r3
	.align 2
.Lbars:
	.word BitBeastBars
