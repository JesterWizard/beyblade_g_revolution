    .rom_head 0x08000000 : {
        asm/rom.o(.rodata)
    } > ROM
    .rom_sub_08033A94 0x08033A94 : {
        asm/matchings/sub_08033A94.o(.text)
    } > ROM
    .rom_gap_000 0x08033A98 : {
        asm/rom_gap_000.o(.rodata)
    } > ROM
    .rom_sub_08062098 0x08062098 : {
        asm/matchings/sub_08062098.o(.text)
    } > ROM
    .rom_gap_001 0x0806209C : {
        asm/rom_gap_001.o(.rodata)
    } > ROM
    .rom_sub_08062A14 0x08062A14 : {
        asm/matchings/sub_08062A14.o(.text)
    } > ROM
    .rom_gap_002 0x08062A1C : {
        asm/rom_gap_002.o(.rodata)
    } > ROM
    .rom_sub_080674A0 0x080674A0 : {
        asm/matchings/sub_080674A0.o(.text)
    } > ROM
    .rom_sub_080674A4 0x080674A4 : {
        asm/matchings/sub_080674A4.o(.text)
    } > ROM
    .rom_gap_003 0x080674AA : {
        asm/rom_gap_003.o(.rodata)
    } > ROM
    .rom_sub_080674AC 0x080674AC : {
        asm/matchings/sub_080674AC.o(.text)
    } > ROM
    .rom_sub_080674B0 0x080674B0 : {
        asm/matchings/sub_080674B0.o(.text)
    } > ROM
    .rom_sub_080674B4 0x080674B4 : {
        asm/matchings/sub_080674B4.o(.text)
    } > ROM
    .rom_gap_004 0x080674BA : {
        asm/rom_gap_004.o(.rodata)
    } > ROM
    .rom_sub_08067A9C 0x08067A9C : {
        asm/matchings/sub_08067A9C.o(.text)
    } > ROM
    .rom_gap_005 0x08067A9E : {
        asm/rom_gap_005.o(.rodata)
    } > ROM
    .rom_sub_0806EEC4 0x0806EEC4 : {
        asm/matchings/sub_0806EEC4.o(.text)
    } > ROM
    .rom_gap_006 0x0806EEC6 : {
        asm/rom_gap_006.o(.rodata)
    } > ROM
    .rom_sub_08074144 0x08074144 : {
        asm/matchings/sub_08074144.o(.text)
    } > ROM
    .rom_tail 0x08074146 : {
        asm/rom_tail.o(.rodata)
    } > ROM
