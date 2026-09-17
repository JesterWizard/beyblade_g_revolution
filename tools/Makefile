# Builds pret-style GBA decomp tools used by this project.
# Sources are cloned from pokeemerald on first run.
#
# Usage (from repo root): make tools

TOOLS := gbafix scaninc preproc ramscrgen gbagfx
POKEEMERALD_TOOLS := https://github.com/pret/pokeemerald.git

.PHONY: all clean $(TOOLS)

all: $(TOOLS)

src:
	@if [ ! -d src/.git ]; then \
	  echo "Cloning pokeemerald (sparse: tools/)..."; \
	  git clone --depth 1 --filter=blob:none --sparse $(POKEEMERALD_TOOLS) src; \
	  cd src && git sparse-checkout set tools; \
	fi

define BUILD_TOOL
$(1): src
	@mkdir -p $(1)
	@cp -a src/tools/$(1)/. $(1)/
	@$(MAKE) -C $(1)
endef

$(foreach t,$(TOOLS),$(eval $(call BUILD_TOOL,$(t))))

clean:
	rm -rf $(TOOLS) src
