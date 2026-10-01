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

    /* Retail ROM image: incbin peels + matched C .text at fixed VMAs. */
    INCLUDE rom_layout.ld

    /* Sections not placed by rom_layout.ld land after the retail image.
     * Nothing does today, so __append_end is the end of the retail ROM. */
    __append_start = .;

    .append_text :
    {
        *(.text);
        *(.text.*);
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
