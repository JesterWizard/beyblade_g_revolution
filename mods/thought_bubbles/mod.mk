# Thought bubble art -> ROM data. tools/gen_bubbles.py turns bubbles.txt and
# assets/*.png into bubble_data.s, linked like any other mod object.
# (BUBBLE_* are this mod's own copies: a recipe runs after every mod.mk is read.)
BUBBLE_DIR   := $(MOD_DIR)
BUBBLE_BUILD := $(MOD_BUILDDIR)
BUBBLE_PNGS  := $(wildcard $(BUBBLE_DIR)/assets/*.png)
MOD_OBJS     += $(BUBBLE_BUILD)/bubble_data.o

$(BUBBLE_BUILD)/bubble_data.s: $(BUBBLE_DIR)/tools/gen_bubbles.py $(BUBBLE_DIR)/bubbles.txt $(BUBBLE_PNGS)
	@mkdir -p $(dir $@)
	python3 $< $(BUBBLE_DIR) $(BUBBLE_BUILD)

$(BUBBLE_BUILD)/bubble_data.o: $(BUBBLE_BUILD)/bubble_data.s
	$(AS) $(ASFLAGS) -mthumb -o $@ $<
