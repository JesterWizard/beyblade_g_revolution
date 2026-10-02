# Example Mod

---

## 📑 Index
- [Introduction](#-introduction)
- [How To Use](#️-how-to-use)
- [Code Locations](#️-code-locations)
- [TODO](#-todo)
- [Limitations & Bugs](#-limitations--bugs)

---

## 🧩 Introduction

The smallest possible mod, meant to be copied when starting a new one. It makes `CollectionIsFull` always return 0, so the collection never reports full.

The aim is to show the minimum a mod needs:

- A `src/*.c` file compiled with agbcc and linked past the retail image
- A `hooks.txt` line that sends a retail function to the new code
- `include/` for mod-private headers

---

## 🛠️ How To Use

```
make MOD=example      # only this mod
```

See [`docs/modding.md`](../../docs/modding.md) for the `hooks.txt` formats (`replace`, `call`, `pointer`, `patch`).

---

## 🗂️ Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| **Replacement** | `CollectionIsFull__Replacement` in [`collection.c`](src/collection.c) | Returns 0; the retail body is overwritten by the hook |
| **Hook** | `sub_0802BC14 CollectionIsFull__Replacement` in [`hooks.txt`](hooks.txt) | Replacement hook for `CollectionIsFull` |

---

## 📝 TODO

- None; kept deliberately minimal

---

## 🐛 Limitations & Bugs

Please report issues in the repository's **Issues** tab.

- Mods cannot combine with `make compare`; the SHA1 differs by design.

---
