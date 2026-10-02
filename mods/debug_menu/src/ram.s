@ The debug menu's state block: the top 4 KB of EWRAM. The retail heap ends
@ 0x1000 earlier (hooks.txt patches HeapAlloc), so nothing else touches it.
	.global gDebug
	.set gDebug, 0x0203F000
