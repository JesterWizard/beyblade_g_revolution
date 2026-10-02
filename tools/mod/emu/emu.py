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
    def save(s,p): return L.emu_savestate(p.encode())
    def load(s,p): return L.emu_loadstate(p.encode())
