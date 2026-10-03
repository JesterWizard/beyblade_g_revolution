@ The launch hook at 0x0803C234.
@
@ In the battle code (sub_0803C...) the player's launch ends with
@
@     0803C230  bl   _0803CECC              @ launch RPM (debug_menu hooks this bl)
@     0803C234  ldr  r0, [r5]
@     0803C236  movs r5, #0x96
@     0803C238  lsls r5, r5, #1             @ 0x12C
@     0803C23A  adds r0, r0, r5
@     0803C23C  movs r1, #5
@     0803C23E  strb r1, [r0]               @ state = 5, the blade is released
@     0803C240  b    0x0803C47C
@     0803C242  (padding)
@
@ The hook replaces the 16 bytes 0x0803C234..0x0803C243, so this code runs the displaced
@ instructions itself. Nothing else branches into that range. VoiceOnLaunch is C and
@ keeps r4-r7.

	.syntax unified
	.thumb
	.align 2
	.global VoiceLaunchHook
	.thumb_func
VoiceLaunchHook:
	bl VoiceOnLaunch
	ldr r0, [r5]
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r0, r5
	movs r1, #5
	strb r1, [r0]
	ldr r0, .Lback
	bx r0

	.align 2
.Lback:
	.4byte 0x0803C47D
