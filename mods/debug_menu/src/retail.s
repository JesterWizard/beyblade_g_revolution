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

@ The battle code the abilities wrap (abilities.c). Most of it still sits in
@ asm gaps; sub_08030638 and sub_080348E8 are decomp functions, aliased here so
@ the mod can declare its own prototypes for them.
	.weak _08034BE0
	.thumb_set _08034BE0, 0x08034BE0
	.weak _0802FFAC
	.thumb_set _0802FFAC, 0x0802FFAC
	.weak _080300D4
	.thumb_set _080300D4, 0x080300D4
	.weak _08032A88
	.thumb_set _08032A88, 0x08032A88
	.weak _08030638
	.thumb_set _08030638, 0x08030638
	.weak _080348E8
	.thumb_set _080348E8, 0x080348E8
