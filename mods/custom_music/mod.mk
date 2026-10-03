# BGM audio -> ROM data. tools/gen_music.py turns tracks.txt and music/* into music_data.s,
# linked like any other mod object. (MUSIC_* are this mod's own copies: a recipe runs
# after every mod.mk is read.)
MUSIC_DIR   := $(MOD_DIR)
MUSIC_BUILD := $(MOD_BUILDDIR)
MUSIC_FILES := $(filter-out %/SIZES.md,$(wildcard $(MUSIC_DIR)/music/*))
MOD_OBJS    += $(MUSIC_BUILD)/music_data.o

$(MUSIC_BUILD)/music_data.s: $(MUSIC_DIR)/tools/gen_music.py $(MUSIC_DIR)/tracks.txt include/bgm.h baserom.gba $(MUSIC_FILES)
	@mkdir -p $(dir $@)
	python3 $< $(MUSIC_DIR) $(MUSIC_BUILD)

$(MUSIC_BUILD)/music_data.o: $(MUSIC_BUILD)/music_data.s
	$(AS) $(ASFLAGS) -mthumb -o $@ $<
