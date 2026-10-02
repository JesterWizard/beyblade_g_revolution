import ctypes, os, sys
_real=os.dup(1); sys.stdout=os.fdopen(_real,'w',buffering=1); os.dup2(os.open(os.devnull,os.O_WRONLY),1)
from PIL import Image
H = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "build", "emu")
L = ctypes.CDLL(os.path.join(H, "libemuh.so"))
for f in ("emu_r8","emu_r16","emu_r32"): getattr(L,f).restype = ctypes.c_uint
KEYS = dict(A=1,B=2,SELECT=4,START=8,RIGHT=16,LEFT=32,UP=64,DOWN=128,R=256,L=512)
def keymask(name): return sum(KEYS[x] for x in name.split('+')) if name else 0
class Emu:
    def __init__(s, rom, sav=None):
        r = L.emu_load(rom.encode(), sav.encode() if sav else None)
        assert r == 0, r
    def frames(s, n, keys=0): L.emu_frame(keymask(keys) if isinstance(keys,str) else keys, n)
    def press(s, name, hold=4, wait=10): s.frames(hold, name); s.frames(wait, 0)
    def r8(s,a): return L.emu_r8(a)
    def r16(s,a): return L.emu_r16(a)
    def r32(s,a): return L.emu_r32(a)
    def w8(s,a,v): L.emu_w8(a,v)
    def w16(s,a,v): L.emu_w16(a,v)
    def w32(s,a,v): L.emu_w32(a,v)
    def shot(s, path, scale=2):
        buf = (ctypes.c_ubyte*(240*160*4))(); L.emu_shot(buf)
        im = Image.frombuffer("RGBA",(240,160),bytes(buf),"raw","RGBA",0,1).convert("RGB")
        im.resize((240*scale,160*scale), Image.NEAREST).save(path)
    def call(s, fn, a0=0,a1=0,a2=0,a3=0, steps=2000000):
        L.emu_call.restype=ctypes.c_uint
        return L.emu_call(ctypes.c_uint(fn),ctypes.c_uint(a0),ctypes.c_uint(a1),ctypes.c_uint(a2),ctypes.c_uint(a3),steps)
    def until(s, fn, a0, a1, a2, a3, targets, steps=200000):
        arr=(ctypes.c_uint*len(targets))(*targets)
        L.emu_until.restype=ctypes.c_uint
        return L.emu_until(ctypes.c_uint(fn),ctypes.c_uint(a0),ctypes.c_uint(a1),ctypes.c_uint(a2),ctypes.c_uint(a3),arr,len(targets),steps)
    def trace(s, keys, n, targets):
        """Run n frames stepping each instruction; returns how often the pc was at each target (r0 at the last hit in .last_r0)."""
        arr=(ctypes.c_uint*len(targets))(*targets); out=(ctypes.c_uint*len(targets))(); r0=(ctypes.c_uint*len(targets))()
        L.emu_trace(keymask(keys) if isinstance(keys,str) else keys, n, arr, len(targets), out, r0)
        s.last_r0 = list(r0)
        s.hist = []
        t=ctypes.c_uint(); v=ctypes.c_uint(); i=0
        while L.emu_hist(i, ctypes.byref(t), ctypes.byref(v)): s.hist.append((t.value, v.value)); i+=1
        s.regs = []; a=ctypes.c_uint(); c=ctypes.c_uint(); d=ctypes.c_uint(); i=0
        while L.emu_hist_regs(i, ctypes.byref(a), ctypes.byref(c), ctypes.byref(d)): s.regs.append((a.value, c.value, d.value)); i+=1  # r1, r2, r4 at each hit
        return list(out)
    def watch(s, keys, n, addr):
        """Step until the word at addr changes: returns (pc, old, new, lr, r0..r3) or None."""
        out=(ctypes.c_uint*7)()
        pc=L.emu_watch(keymask(keys) if isinstance(keys,str) else keys, n, addr, out)
        return (pc,)+tuple(out) if pc else None
    def save(s,p): return L.emu_savestate(p.encode())
    def load(s,p): return L.emu_loadstate(p.encode())
