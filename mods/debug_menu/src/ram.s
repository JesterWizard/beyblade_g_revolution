@ The debug menu's state block: the top 4 KB of EWRAM. The heap is shrunk to
@ end at 0x02020800 (hooks.txt patches HeapAlloc), so nothing else touches it.
	.global gDebug
	.set gDebug, 0x0203F000
