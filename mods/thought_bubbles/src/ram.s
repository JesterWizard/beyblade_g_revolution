@ The bubble's state block: the top 4 KB of EWRAM. The heap is shrunk to
@ end at 0x02020800 (hooks.txt patches HeapAlloc), so nothing else touches it.
@ debug_menu keeps its state at the start of the same page (gDebug, 0x0203F000).
	.global gBubble
	.set gBubble, 0x0203F800
