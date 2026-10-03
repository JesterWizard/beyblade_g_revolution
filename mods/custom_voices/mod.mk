# Voice clips -> ROM data. tools/gen_voices.py turns voices.txt and voices/* into voices_data.s,
# linked like any other mod object. (VOICE_* are this mod's own copies: a recipe runs
# after every mod.mk is read.)
VOICE_DIR   := $(MOD_DIR)
VOICE_BUILD := $(MOD_BUILDDIR)
VOICE_FILES := $(filter-out %/SIZES.md,$(wildcard $(VOICE_DIR)/voices/*))
MOD_OBJS    += $(VOICE_BUILD)/voices_data.o

$(VOICE_BUILD)/voices_data.s: $(VOICE_DIR)/tools/gen_voices.py tools/mod/gba_adpcm.py $(VOICE_DIR)/voices.txt baserom.gba $(VOICE_FILES)
	@mkdir -p $(dir $@)
	python3 $< $(VOICE_DIR) $(VOICE_BUILD)

$(VOICE_BUILD)/voices_data.o: $(VOICE_BUILD)/voices_data.s
	$(AS) $(ASFLAGS) -mthumb -o $@ $<
