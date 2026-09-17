# Installation

## Dependencies (Debian/Ubuntu/WSL)

```bash
sudo apt update
sudo apt install -y build-essential git python3 libpng-dev binutils-arm-none-eabi gcc-arm-none-eabi
```

Optional: install [devkitPro](https://devkitpro.org/wiki/Getting_Started) `gba-dev` and ensure `DEVKITARM` is set. The Makefile prefers `arm-none-eabi-*` on `PATH`.

## Baserom

Place a clean **Beyblade G Revolution (USA/Europe)** dump in the repo root as:

```text
baserom.gba
```

Confirm header fields (and update the Makefile if needed):

```bash
python3 tools/decomp/print_header.py
```

Expected SHA1 for the target ROM:

```text
a89f7b4eb77dc986022201db51a676451ba7c5e4
```

## Build tools (optional at scaffold stage)

```bash
make tools
```

This sparse-clones [pret/pokeemerald](https://github.com/pret/pokeemerald) and builds `gbafix`, `scaninc`, `preproc`, `ramscrgen`, and `gbagfx`.

## Install agbcc (needed once you compile matching C with `make`)

```bash
git clone https://github.com/pret/agbcc ../agbcc
cd ../agbcc
./build.sh
./install.sh ../beyblade_g_revolution
cd ../beyblade_g_revolution
```

For append/hack C only (`src_custom/`, `configs/`), `make modern` uses `arm-none-eabi-gcc` and does not require agbcc.

## Build / compare

```bash
make compare     # builds and checks rom.sha1 (vanilla rebuild)
make HACKS=1 modern   # append ROM with runtime + src_custom
```

## AI decompilation toolchain

```bash
bash build_tools.sh
export ANTHROPIC_API_KEY=sk-...   # required for Mizuchi Claude Runner
tools/decomp/run_batch.sh 10
```

See [AGENTS.md](AGENTS.md) and [docs/decomp-agent.md](docs/decomp-agent.md).

## decomp-permuter (agbcc matching)

For functions whose C is the right logic but agbcc emits a different literal-pool or instruction order:

```bash
tools/decomp/permuter/setup.sh
tools/decomp/permuter/permute.sh import sub_08072F94
tools/decomp/permuter/permute.sh run nonmatchings/sub_08072F94 -j 4 --stop-on-zero
```

On score 0, copy the winning `output-0-*.c` over `src/matched/sub_XXXXXXXX.c` and `python3 tools/decomp/match_function.py` + `integrate_c.py --kind semantic`.
