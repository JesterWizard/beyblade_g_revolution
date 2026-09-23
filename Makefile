# GBA ROM header (from Beyblade G Revolution USA/Europe; verify against your baserom)
TITLE      := BEYBLADEGREV
GAME_CODE  := BB2E
MAKER_CODE := 70
REVISION   := 0

FILE_NAME  := beyblade_g_revolution
BUILD_DIR  := build
OBJ_DIR    := $(BUILD_DIR)/bbgr

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

MODERN  ?= 0
COMPARE ?= 0
# Set HACKS=1 to link append ROM (runtime + src_custom). Breaks make compare.
HACKS   ?= 0

ifeq (compare,$(MAKECMDGOALS))
  COMPARE := 1
  HACKS := 0
  MODERN := 1
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

.PHONY: all rom modern compare clean tidy tools check-baserom
.PHONY: analyze symbols tier document status audit repair-signatures audit-drafts repair-drafts prune-drafts signatures fix-stub-arities sync-verified check-verified
all: rom

C_SUBDIR = src
CUSTOM_C_SUBDIR = src_custom
CONFIG_SUBDIR = configs
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data

C_BUILDDIR = $(OBJ_DIR)/$(C_SUBDIR)
CUSTOM_C_BUILDDIR = $(OBJ_DIR)/$(CUSTOM_C_SUBDIR)
CONFIG_BUILDDIR = $(OBJ_DIR)/$(CONFIG_SUBDIR)
ASM_BUILDDIR = $(OBJ_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(OBJ_DIR)/$(DATA_ASM_SUBDIR)

C_SRCS :=
ifeq ($(HACKS),1)
CUSTOM_C_SRCS := \
	$(CUSTOM_C_SUBDIR)/nocash.c
CONFIG_SRCS := $(CONFIG_SUBDIR)/runtime.c
else
CUSTOM_C_SRCS :=
CONFIG_SRCS :=
endif
RAM_MAP_FRAGMENTS := \
	$(ASM_SUBDIR)/ram_map_iwram.s \
	$(ASM_SUBDIR)/ram_map_ewram.s \
	$(ASM_SUBDIR)/ram_map_sram.s \
	$(ASM_SUBDIR)/ram_map_iwram_pool.inc \
	$(ASM_SUBDIR)/ram_map_ewram_pool.inc \
	$(ASM_SUBDIR)/data_symbols.s
ASM_MATCHINGS := $(wildcard $(ASM_SUBDIR)/matchings/*.s)
ASM_ROM_GAPS := $(wildcard $(ASM_SUBDIR)/rom_gap_*.s)
ASM_SRCS := \
	$(ASM_SUBDIR)/rom.s \
	$(ASM_SUBDIR)/rom_tail.s \
	$(ASM_ROM_GAPS) \
	$(ASM_MATCHINGS) \
	$(ASM_SUBDIR)/ram_map.s
DATA_ASM_SRCS :=

C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))
CUSTOM_C_OBJS := $(patsubst $(CUSTOM_C_SUBDIR)/%.c,$(CUSTOM_C_BUILDDIR)/%.o,$(CUSTOM_C_SRCS))
CONFIG_OBJS := $(patsubst $(CONFIG_SUBDIR)/%.c,$(CONFIG_BUILDDIR)/%.o,$(CONFIG_SRCS))
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))

OBJS := $(C_OBJS) $(CUSTOM_C_OBJS) $(CONFIG_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS)
OBJS_REL := $(patsubst $(OBJ_DIR)/%,%,$(OBJS))

LYNJUMP_EVENT := $(CUSTOM_C_SUBDIR)/LynJump.event
APPLY_LYNJUMP := $(TOOLS_DIR)/apply_lynjump.py

SUBDIRS := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(SUBDIRS))

modern: all
compare: all

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

analyze:
	python3 tools/decomp/analyze.py

symbols:
	python3 tools/decomp/symbols.py generate

tier:
	python3 tools/decomp/tier.py

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

rom: check-baserom $(ROM)
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

clean: tidy
	@$(MAKE) clean -C tools

tidy:
	rm -f $(ROM) $(ELF) $(MAP)
	rm -rf $(BUILD_DIR)

$(ASM_BUILDDIR)/ram_map.o: $(RAM_MAP_FRAGMENTS)

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I . -o $@ $<

$(ASM_BUILDDIR)/matchings/%.o: $(ASM_SUBDIR)/matchings/%.s
	@mkdir -p $(ASM_BUILDDIR)/matchings
	$(AS) $(ASFLAGS) -I . -o $@ $<

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I . -o $@ $<

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c
ifeq ($(MODERN),0)
	@test -x $(CC1) || { echo "error: agbcc missing. See INSTALL.md"; exit 1; }
endif
	@$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) -o $@ $(C_BUILDDIR)/$*.s

$(CUSTOM_C_BUILDDIR)/%.o: $(CUSTOM_C_SUBDIR)/%.c
ifeq ($(MODERN),0)
	@test -x $(CC1) || { echo "error: agbcc missing. See INSTALL.md"; exit 1; }
endif
	@$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) -o $(CUSTOM_C_BUILDDIR)/$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(CUSTOM_C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) -o $@ $(CUSTOM_C_BUILDDIR)/$*.s

# runtime.c uses C99 designated initializers (ygodm8-style); compile with modern gcc.
$(CONFIG_BUILDDIR)/%.o: $(CONFIG_SUBDIR)/%.c
	$(PREFIX)gcc -c -mcpu=arm7tdmi -mthumb -mthumb-interwork -O2 \
		-fno-toplevel-reorder -iquote include -I include \
		-o $@ $<

LD_SCRIPT := ld_script.ld
LDFLAGS = -Map ../../$(MAP) -L ../../asm

$(ELF): $(LD_SCRIPT) $(OBJS)
	cd $(OBJ_DIR) && $(LD) $(LDFLAGS) -T ../../$(LD_SCRIPT) -o ../../$@ $(OBJS_REL) $(LIB)
ifneq ($(wildcard $(FIX)),)
	$(FIX) $@ -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent
endif

$(ROM): $(ELF) $(LYNJUMP_EVENT) $(APPLY_LYNJUMP)
	$(OBJCOPY) -O binary --gap-fill 0xFF $< $@
ifneq ($(wildcard $(FIX)),)
	$(FIX) $@ -p --silent
endif
	python3 $(APPLY_LYNJUMP) $(ELF) $@
	@# Pad only through append end. Must be >4MB so 0x08400000 is not a
	@# mirror of 0x08000000; do not force a full 8MB image.
	@end=$$(arm-none-eabi-nm $(ELF) | awk '/__append_end$$/{print $$1}'); \
	 size=$$((0x$$end - 0x08000000)); \
	 truncate -s $$size $@
ifneq ($(wildcard $(FIX)),)
	$(FIX) $@ -p --silent
endif
