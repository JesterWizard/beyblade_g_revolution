OUTPUT_ARCH(arm)
ENTRY(gBaserom)

MEMORY {
    EWRAM (rwx) : ORIGIN = 0x02000000, LENGTH = 256K
    IWRAM (rwx) : ORIGIN = 0x03000000, LENGTH = 32K
    /* 8M address space so append past the 4MB retail image is allowed; output
     * ROM is trimmed to __append_end (not a full 8MB file). */
    ROM   (rx)  : ORIGIN = 0x08000000, LENGTH = 8M
}

/* Absolute RAM symbols live in asm/ram_map.s (and region fragments). */

SECTIONS {
    ewram (NOLOAD) : ALIGN(4)
    {
        __ewram_start = .;
        *(ewram_data)
        . = ALIGN(4);
        __ewram_end = .;
    } > EWRAM

    iwram (NOLOAD) : ALIGN(4)
    {
        __iwram_start = .;
        *(.bss)
        *(COMMON)
        *(iwram_data)
        . = ALIGN(4);
        __iwram_end = .;
    } > IWRAM

    /* Mod C must not have .bss/COMMON: it would be linked here, on top of vanilla
     * IWRAM (0x03000000 holds live game variables). Keep mod state in the EWRAM
     * state page (mods/<name>/src/ram.s) or in a struct that lives there. */
    ASSERT(__iwram_end == __iwram_start, "mod .bss/COMMON linked at 0x03000000, on vanilla IWRAM; move the static into the mod's EWRAM state")

    /* Optional insert after .rom_head: `ld --defsym=__rom_shift_bytes=0x1000`. */
PROVIDE(__rom_shift_bytes = 0);
    INCLUDE rom_layout.ld

    /* Extra code for mods. Do not scoop leftover `.text` here: matched C is
     * already listed in rom_layout.ld, and libgcc veneers are peel labels. */
    __append_start = .;

    .append_text :
    {
        /* `make MOD=<name>` objects (empty in a vanilla build). */
        mod/*.o(.text .text.*)
        *(.append_text);
    } > ROM = 0xFF

    .append_rodata :
    {
        *(.rodata);
        *(.rodata.*);
        *(.append_rodata);
    } > ROM = 0xFF

    .append_data :
    {
        *(.data);
        *(.append_data);
    } > ROM = 0xFF

    . = ALIGN(4);
    __append_end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
        *(.ARM.attributes)
    }
}
