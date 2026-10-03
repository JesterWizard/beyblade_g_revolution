# opponents.json -> ROM data. tools/gen_opponents.py turns it (and the ROM's own start
# values for anything it leaves out) into opponent_data.s, linked like any other mod
# object. (OPP_* are this mod's own copies: a recipe runs after every mod.mk is read.)
OPP_DIR   := $(MOD_DIR)
OPP_BUILD := $(MOD_BUILDDIR)
MOD_OBJS  += $(OPP_BUILD)/opponent_data.o

$(OPP_BUILD)/opponent_data.s: $(OPP_DIR)/tools/gen_opponents.py $(OPP_DIR)/opponents.json baserom.gba
	@mkdir -p $(dir $@)
	python3 $< $(OPP_DIR) $(OPP_BUILD)

$(OPP_BUILD)/opponent_data.o: $(OPP_BUILD)/opponent_data.s
	$(AS) $(ASFLAGS) -mthumb -o $@ $<
