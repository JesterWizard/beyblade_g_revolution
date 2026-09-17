@ Unmatched ROM image (full baserom until peels begin).
@ As functions/data are decompiled, shrink this .incbin and move ranges into
@ real asm/C objects listed in ld_script.ld.

	.section .rodata
	.align 2
	.global gBaserom
gBaserom:
	.incbin "baserom.gba"
