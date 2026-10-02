# GBA ROM header (from Beyblade G Revolution USA/Europe; verify against your baserom)
TITLE      := BEYBLADEGREV
GAME_CODE  := BB2E
MAKER_CODE := 70
REVISION   := 0

FILE_NAME  := beyblade_g_revolution
BUILD_DIR  := build
null  :=
space := $(null) $(null)
OBJ_DIR    := $(BUILD_DIR)/bbgr

# Mods (mods/<name>/, see docs/modding.md) are built in by default: plain
# `make` produces beyblade_g_revolution_<mods joined with +>.gba, with every mod
# in DEFAULT_MOD built together.
#   make NO_MODS=1      the vanilla decomp, beyblade_g_revolution.gba
#   make MOD=<name>     one mod, or several: make MOD="a b" (MOD= means none)
#   make compare        always vanilla, it checks rom.sha1
DEFAULT_MOD := debug_menu thought_bubbles
ifeq ($(NO_MODS),1)
  override MOD :=
else ifeq ($(origin MOD),undefined)
  MOD := $(foreach m,$(DEFAULT_MOD),$(if $(wildcard mods/$(m)),$(m)))
endif
ifneq (,$(filter compare check-vanilla,$(MAKECMDGOALS)))
  override MOD :=
endif
ifneq ($(MOD),)
  $(foreach m,$(MOD),$(if $(wildcard mods/$(m)),,$(error mods/$(m) not found. See docs/modding.md)))
  FILE_NAME := beyblade_g_revolution_$(subst $(space),+,$(strip $(MOD)))
endif

ROM  := $(FILE_NAME).gba
ELF  := $(FILE_NAME).elf
MAP  := $(FILE_NAME).map

# Toolchain (devkitARM or system arm-none-eabi-*)
TOOLCHAIN := $(DEVKITARM)
ifneq (,$(TOOLCHAIN))
  ifneq ($(wildcard $(TOOLCHAIN)/bin),)
    export PATH := $(TOOLCHAIN)/bin:$(PATH)
  endif
endif

PREFIX  := arm-none-eabi-
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump
AS      := $(PREFIX)as
LD      := $(PREFIX)ld
CPP     := $(CC) -E

EXE :=
ifeq ($(OS),Windows_NT)
  EXE := .exe
endif

# Compile functions in parallel unless -j was given.
ifeq (,$(filter -j% --jobs%,$(MAKEFLAGS)))
  MAKEFLAGS += --jobs=$(shell nproc 2>/dev/null || echo 4)
endif

MODERN  ?= 0
COMPARE ?= 0

ifeq (compare,$(MAKECMDGOALS))
  COMPARE := 1
endif
ifeq (modern,$(MAKECMDGOALS))
  MODERN := 1
endif

ASFLAGS   := -mcpu=arm7tdmi -I asm --defsym MODERN=$(MODERN)
INCLUDE_DIRS := include
CPPFLAGS  := $(INCLUDE_DIRS:%=-iquote %) -Wno-trigraphs -DMODERN=$(MODERN)

O_LEVEL ?= 2

# Libraries are only needed once C objects are linked.
LIB :=
ifeq ($(MODERN),0)
  CPPFLAGS += -I tools/agbcc/include -I tools/agbcc -nostdinc -undef -std=gnu89
  CC1 := tools/agbcc/bin/agbcc$(EXE)
  override CFLAGS += -mthumb-interwork -Wimplicit -Wparentheses -Werror -O$(O_LEVEL) -fhex-asm
  LIBPATH := -L ../../tools/agbcc/lib
  LIB := $(LIBPATH) -lgcc
else
  MODERNCC := $(PREFIX)gcc
  PATH_MODERNCC := PATH="$(PATH)" $(MODERNCC)
  CC1 := $(shell $(PATH_MODERNCC) --print-prog-name=cc1) -quiet
  override CFLAGS += -mthumb -mthumb-interwork -O$(O_LEVEL) -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -fno-toplevel-reorder
  LIBPATH := -L "$(dir $(shell $(PATH_MODERNCC) -mthumb -print-file-name=libgcc.a))"
  LIB := $(LIBPATH) -lgcc
endif

TOOLS_DIR := tools
SCANINC   := $(TOOLS_DIR)/scaninc/scaninc$(EXE)
PREPROC   := $(TOOLS_DIR)/preproc/preproc$(EXE)
FIX       := $(TOOLS_DIR)/gbafix/gbafix$(EXE)
RAMSCRGEN := $(TOOLS_DIR)/ramscrgen/ramscrgen$(EXE)

SHA1 := $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c

SHELL := bash -o pipefail

.SUFFIXES:
.SECONDARY:
.DELETE_ON_ERROR:

.PHONY: all rom modern compare clean clean-tools clean-cache tidy tools check-baserom shift-test grow-test graphics clean-gfx
.PHONY: check-vanilla
.PHONY: split pack rename-files analyze symbols tier document status audit repair-signatures audit-drafts repair-drafts prune-drafts signatures fix-stub-arities sync-verified check-verified
all: rom

C_SUBDIR = src
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data

C_BUILDDIR = $(OBJ_DIR)/$(C_SUBDIR)
ASM_BUILDDIR = $(OBJ_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(OBJ_DIR)/$(DATA_ASM_SUBDIR)

# Matched C is authored in grouped files (src/<group>.c) plus the src/matched/
# inbox. groups.py splits both into one file per function under build/split/,
# which is what gets compiled, so asm/rom_layout.ld keeps one object per function.
SPLIT_DIR := build/split
SPLIT_RAN := $(shell python3 tools/decomp/groups.py split)
C_SRCS := $(patsubst $(SPLIT_DIR)/%.c,$(C_SUBDIR)/matched/%.c,$(wildcard $(SPLIT_DIR)/*.c))
RAM_MAP_FRAGMENTS := \
	$(ASM_SUBDIR)/ram_map_iwram.s \
	$(ASM_SUBDIR)/ram_map_ewram.s \
	$(ASM_SUBDIR)/ram_map_sram.s \
	$(ASM_SUBDIR)/ram_map_iwram_pool.inc \
	$(ASM_SUBDIR)/ram_map_ewram_pool.inc \
	$(ASM_SUBDIR)/data_symbols.s
ASM_ROM_GAPS := $(wildcard $(ASM_SUBDIR)/rom_gap_*.s)
ASM_SRCS := \
	$(ASM_SUBDIR)/rom.s \
	$(ASM_SUBDIR)/rom_tail.s \
	$(ASM_ROM_GAPS) \
	$(ASM_SUBDIR)/ram_map.s
DATA_ASM_SRCS :=

C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))

# Mod objects (MOD=<name>... only). Linked into .append_text past the retail image.
# Each mod's own mod.mk sees MOD_DIR / MOD_BUILDDIR and must copy them into
# variables of its own for use in rules (a recipe expands after the last mod
# has been read).
MOD_HOOKS    :=
MOD_OBJS     :=
define MOD_SETUP
MOD_DIR      := mods/$(1)
MOD_BUILDDIR := $(OBJ_DIR)/mod/$(1)
MOD_HOOKS    += $$(wildcard $$(MOD_DIR)/hooks.txt)
MOD_OBJS     += $$(patsubst $$(MOD_DIR)/src/%.c,$$(MOD_BUILDDIR)/%.o,$$(wildcard $$(MOD_DIR)/src/*.c)) \
                $$(patsubst $$(MOD_DIR)/src/%.s,$$(MOD_BUILDDIR)/%.o,$$(wildcard $$(MOD_DIR)/src/*.s))
-include $$(MOD_DIR)/mod.mk
endef
$(foreach m,$(MOD),$(eval $(call MOD_SETUP,$(m))))

OBJS := $(C_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(MOD_OBJS)
OBJS_REL := $(patsubst $(OBJ_DIR)/%,%,$(OBJS))


SUBDIRS := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(SUBDIRS))

modern: all
compare: all

shift-test:
	python3 tools/decomp/test_shift.py

grow-test:
	python3 tools/decomp/test_grow.py

progress:
	python3 tools/decomp/progress.py --write --top 15

queue:
	python3 tools/decomp/next_queue.py --write

scores:
	python3 tools/decomp/function_scores.py --write

patterns:
	python3 tools/decomp/c_patterns.py --list

packet:
	python3 tools/decomp/agent_packet.py --next

cluster:
	python3 tools/decomp/cluster_shapes.py

script-first:
	python3 tools/decomp/script_first.py

rename-files:
	python3 tools/decomp/fnfiles.py sync --apply

analyze:
	python3 tools/decomp/analyze.py

symbols:
	python3 tools/decomp/symbols.py generate

tier:
	python3 tools/decomp/tier.py

split:
	python3 tools/decomp/groups.py split

pack:
	python3 tools/decomp/groups.py pack --apply

document:
	python3 tools/decomp/document.py

status:
	python3 tools/decomp/cli.py status

audit:
	python3 tools/decomp/audit_c_compiles.py --dirs matched

audit-drafts:
	python3 tools/decomp/audit_c_compiles.py --dirs decompiled

prune-drafts:
	python3 tools/decomp/prune_drafts.py --apply

sync-verified:
	python3 tools/decomp/sync_verified.py --apply

check-verified:
	python3 tools/decomp/sync_verified.py --check

repair-signatures:
	python3 tools/decomp/repair_naked_signatures.py --dirs matched --apply

repair-drafts:
	python3 tools/decomp/repair_naked_signatures.py --dirs decompiled --apply

signatures:
	python3 tools/decomp/audit_signatures.py

fix-stub-arities:
	python3 tools/decomp/fix_stub_arities.py --apply

# Graphics are extracted from baserom.gba on the first build (and again whenever
# the ROM, the manifest or the extractor changes). The stamp is not a dependency
# of $(ROM): a graphics problem never changes the ROM bytes or `make compare`.
GFX_STAMP := graphics/.extracted
GFX_SRCS  := $(wildcard tools/gfx/*.py) tools/gfx/assets.json

$(GFX_STAMP): baserom.gba $(GFX_SRCS)
	python3 tools/gfx/extract.py
	@touch $@

graphics: check-baserom
	python3 tools/gfx/extract.py -v
	@touch $(GFX_STAMP)

rom: check-baserom $(GFX_STAMP) $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1) rom.sha1
endif

check-baserom:
	@test -f baserom.gba || { \
	  echo "error: baserom.gba not found."; \
	  echo "Place a clean Beyblade G Revolution (USA/Europe) ROM named baserom.gba in the repo root."; \
	  exit 1; \
	}

tools:
	@$(MAKE) -C tools

# Build outputs only. The tools under tools/ (gbafix, scaninc, ...) and the
# object cache survive; `make clean-tools` / `make clean-cache` remove those.
clean: tidy

clean-tools:
	@$(MAKE) clean -C tools

clean-cache:
	rm -rf .cache/objs

tidy:
	rm -f beyblade_g_revolution.gba beyblade_g_revolution.elf beyblade_g_revolution.map
	rm -f beyblade_g_revolution_*.gba beyblade_g_revolution_*.elf beyblade_g_revolution_*.map
	rm -rf $(BUILD_DIR)

# Extracted PNGs are regenerated from the ROM; `make tidy` leaves them alone.
clean-gfx:
	find graphics -name '*.png' -delete
	rm -f $(GFX_STAMP)

$(ASM_BUILDDIR)/ram_map.o: $(RAM_MAP_FRAGMENTS)

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I . -o $@ $<

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I . -o $@ $<

# Matched C is always agbcc (per-file compiler / flags / fixups). Do not use
# the generic cc1 recipe — it ignores match-compiler comments and pads .text.
GROW ?= 0
COMPILE_MATCHED_FLAGS :=
ifeq ($(GROW),1)
COMPILE_MATCHED_FLAGS += --grow
endif

# Objects are cached by content (tools/decomp/objcache.py), so `make clean`
# followed by `make` only recompiles functions whose source or toolchain changed.
OBJ_ENV := $(shell python3 tools/decomp/objcache.py --env)

$(C_BUILDDIR)/matched/%.o: $(SPLIT_DIR)/%.c tools/decomp/compile_matched.py tools/decomp/objcache.py
	@mkdir -p $(dir $@)
	python3 tools/decomp/objcache.py --env $(OBJ_ENV) $(COMPILE_MATCHED_FLAGS) $< $@

# Mod code: plain agbcc, no retail comparison. Mods must not edit src/.
define MOD_RULES
$(OBJ_DIR)/mod/$(1)/%.o: mods/$(1)/src/%.c
	@mkdir -p $$(dir $$@)
ifeq ($(MODERN),0)
	@test -x $(CC1) || { echo "error: agbcc missing. See INSTALL.md"; exit 1; }
endif
	@$(CPP) $(CPPFLAGS) -DMOD=1 -DMOD_NAME=\"$(1)\" -iquote mods/$(1)/include $$< | $(CC1) $(CFLAGS) -o $(OBJ_DIR)/mod/$(1)/$$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(OBJ_DIR)/mod/$(1)/$$*.s
	$(AS) $(ASFLAGS) -o $$@ $(OBJ_DIR)/mod/$(1)/$$*.s

$(OBJ_DIR)/mod/$(1)/%.o: mods/$(1)/src/%.s
	@mkdir -p $$(dir $$@)
	$(AS) $(ASFLAGS) -mthumb -I mods/$(1)/include -o $$@ $$<
endef
$(foreach m,$(MOD),$(eval $(call MOD_RULES,$(m))))

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c
ifeq ($(MODERN),0)
	@test -x $(CC1) || { echo "error: agbcc missing. See INSTALL.md"; exit 1; }
endif
	@$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) -o $@ $(C_BUILDDIR)/$*.s

LD_SCRIPT := ld_script.ld
SHIFT_BYTES ?= 0
GROW ?= 0
PAD_CART ?= 1
ifneq ($(SHIFT_BYTES),0)
PAD_CART := 0
endif
ifeq ($(GROW),1)
PAD_CART := 0
endif
ifneq ($(MOD),)
PAD_CART := 0
endif
LDFLAGS = -Map ../../$(MAP) -L ../../asm
ifneq ($(SHIFT_BYTES),0)
LDFLAGS += --defsym=__rom_shift_bytes=$(SHIFT_BYTES)
endif
EXTRA_OBJS ?=

$(ELF): $(LD_SCRIPT) asm/rom_layout.ld $(OBJS)
	cd $(OBJ_DIR) && $(LD) $(LDFLAGS) -T ../../$(LD_SCRIPT) -o ../../$@ $(OBJS_REL) $(EXTRA_OBJS) $(LIB)
ifneq ($(wildcard $(FIX)),)
	$(FIX) $@ -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent
endif

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --gap-fill 0xFF $< $@
ifneq ($(wildcard $(FIX)),)
ifeq ($(PAD_CART),1)
	$(FIX) $@ -p --silent
endif
endif
	@# Trim the image to __append_end (retail 4MB, or 4MB+shift/grow).
	@end=$$(arm-none-eabi-nm $(ELF) | awk '/__append_end$$/{print $$1}'); \
	 size=$$((0x$$end - 0x08000000)); \
	 truncate -s $$size $@
ifneq ($(MOD_HOOKS),)
	python3 tools/mod/apply_hooks.py $(ELF) $@ $(MOD_HOOKS)
endif
ifneq ($(wildcard $(FIX)),)
ifeq ($(PAD_CART),1)
	$(FIX) $@ -p --silent
endif
endif

# Prove a vanilla build is unaffected by mods/: byte-identical ROM, no mod objects linked.
check-vanilla:
	@$(MAKE) MOD= compare
	@! grep -qE '0x[0-9a-f]+ +0x[0-9a-f]+ +mod/' $(FILE_NAME).map || { echo "error: mod objects leaked into the vanilla link"; exit 1; }
	@echo "vanilla build OK (matches rom.sha1, no mod objects)"
