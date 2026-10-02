@ Retail functions the mod calls that the decomp has not given a symbol yet.
@ Weak, so a real label of the same name wins once the decomp adds one.
	.syntax unified
	.thumb

@ Starts the bit beast summon sequence: (sequence object, fighter, opponent).
	.weak _08034090
	.thumb_set _08034090, 0x08034090
