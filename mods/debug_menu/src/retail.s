@ Retail functions the mod calls that the decomp has not given a symbol yet.
@ Weak, so a real label of the same name wins once the decomp adds one.
	.syntax unified
	.thumb

	.weak _0803CECC
	.thumb_set _0803CECC, 0x0803CECC

@ Retail data the mod reads. The world map's node table: 16 pointers to the
@ spot records that sub_08042F9C seeds the saved map flags from.
	.weak gMapNodes
	.set gMapNodes, 0x08094B68

@ Script opcode 29 (dialogue portrait), wrapped through the opcode table.
	.weak _0805A304
	.thumb_set _0805A304, 0x0805A304

@ The save commit's data-block writer (sub_08044DAC calls it).
	.weak sub_08044F14
	.thumb_set sub_08044F14, 0x08044F14
