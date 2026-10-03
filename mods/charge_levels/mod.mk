# settings.txt -> `patch` lines, applied together with hooks.txt. (CHL_* are this mod's
# own copies: a recipe runs after every mod.mk is read.)
CHL_DIR   := $(MOD_DIR)
CHL_BUILD := $(MOD_BUILDDIR)
MOD_HOOKS += $(CHL_BUILD)/settings_hooks.txt

$(CHL_BUILD)/settings_hooks.txt: $(CHL_DIR)/tools/gen_settings.py $(CHL_DIR)/settings.txt
	@mkdir -p $(dir $@)
	python3 $< $(CHL_DIR) $@
