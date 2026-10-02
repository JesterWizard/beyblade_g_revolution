@ =============================================================================
@ Save storage map (the cartridge's "SRAM" window)
@ =============================================================================
@ This game has NO SRAM or flash: nothing in the ROM touches the 0x0E000000 bus
@ (no literal-pool reference, no ARM/Thumb load). Saves go to a serial EEPROM
@ ("EEPROM_V124" library, ROM 0x08067504..) through DMA3 on 0x0D000000.
@
@   EepromSetType(0x40) selects the 64 Kbit part: config at 0x083A93D4
@     size 0x2000 B, 0x400 blocks of 8 B, 14 address bits, WAITCNT field 3
@   (the 4 Kbit config at 0x083A93C8 is 0x200 B / 0x40 blocks / 6 bits, unused)
@
@ EEPROM is not memory mapped, so the values below are CHIP BYTE OFFSETS
@ (block * 8), not CPU addresses. They match the .sav file byte for byte.
@ Format: SET_ARRAY name, offset, size   @ eeprom: evidence
@ Read by tools/ram_coverage.py (docs/ram-coverage.md).
@ =============================================================================

@ -- Chip --------------------------------------------------------------------
SET_DATA gEepromSize, 0x2000
SET_DATA gEepromBlockSize, 8

@ -- Save header: blocks 0-2 --------------------------------------------------
@ SaveDataVerify (sub_08044A8C family, src/save.c) reads 3 blocks into a 0x18 B
@ buffer; SaveSlotWriteDefault writes blocks idx*3 .. idx*3+2 from 0x08096938.
@   +0x00 magic 0xFEEDFACE   +0x04 SaveDataChecksum of the slot
@   +0x10 0x00370053         +0x14 0x00F6009C   (fixed validation words)
SET_ARRAY gSaveHeader, 0x0000, 0x18                          @ eeprom: SaveDataVerify

@ -- Save slot 0: blocks 3-0x3EE ----------------------------------------------
@ LoadGameSave reads blocks index*0x3EC + 3 .. +0x3EF, struct Unk45198Save
@ (0x1F60 B). Only slot 0 exists: every loop is `i < 1`, and a second slot would run
@ past the chip. Sub-regions are slot offsets + 0x18; sources are SaveDataWrite.
SET_ARRAY gSaveSlot0,           0x0018, 0x1F60               @ eeprom: LoadGameSave
SET_ARRAY gSaveSlotHdr,         0x0018, 0x08                 @ eeprom: +0000 unk0000, +0004 size 0x1F60
SET_ARRAY gSaveSlotScalars,     0x0044, 0x28                 @ eeprom: +002C..+0054 volumes, flags (MainWork 0x1798..0x1857)
SET_ARRAY gSaveSlotUnk16B0,     0x0070, 0x18                 @ eeprom: +0058 2 x Unk45198Rec from MainWork.unk16B0
SET_ARRAY gSaveSlotUnk1694,     0x0098, 0x200                @ eeprom: +0080 copy of MainWork.unk1694
SET_ARRAY gSaveSlotStats,       0x0298, 0x14                 @ eeprom: +0280 exp / strength (MainWork 0x868..0x87B)
SET_ARRAY gSaveSlotUnk87C,      0x02AC, 0x53                 @ eeprom: +0294 MainWork.unk087C[0x53]
SET_ARRAY gSaveSlotRecords,     0x0300, 0x3E4                @ eeprom: +02E8 0x53 x 12 B from MainWork.unk08D0
SET_ARRAY gSaveSlotBlob2B90C,   0x06E4, 0xF8                 @ eeprom: +06CC sub_0802B90C data
SET_ARRAY gSaveSlotBlob3EDC8,   0x07DC, 0xB88                @ eeprom: +07C4 sub_0803EDC8(0) data
SET_ARRAY gSaveSlotCollection,  0x1364, 0xA50                @ eeprom: +134C BeybladeCollectionEntry(0), 0xA50 B
SET_ARRAY gSaveSlotCursorHist,  0x1DB4, 0x144                @ eeprom: +1D9C CursorHistoryGet
SET_ARRAY gSaveSlotUnk15C8,     0x1EF8, 0x14                 @ eeprom: +1EE0 MainWork.unk15C8
SET_ARRAY gSaveSlotBlob43974,   0x1F0C, 0x18                 @ eeprom: +1EF4 sub_08043974
SET_ARRAY gSaveSlotUnk1861,     0x1F24, 0x53                 @ eeprom: +1F0C MainWork.unk1861[0x53]

@ 0x1F78 - 0x2000 (0x88 B, 17 blocks) is never read or written: a .sav from play
@ ends at 0x1F77. Free for a mod save extension, with no collision with the game.
