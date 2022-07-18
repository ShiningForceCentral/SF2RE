static main()
{
    // Trap0_SoundCommand
    SetFunctionCmt(0x45c, 
        "if xxxx = $FFFF, then get d0.w", 1);

    // Trap6_TriggerAndExecuteMapScript
    SetFunctionCmt(0x57a, 
        "execute map script at a0", 1);

    // HInt
    SetFunctionCmt(0x592, 
        "Horizontal interrupt", 1);

    // VInt
    SetFunctionCmt(0x594, 
        "Vertical interrupt", 1);

    // GetVdpRegStatus
    SetFunctionCmt(0xbac, 
        "VDP Reg Status -> d0.w", 1);

    // ApplyVIntCramDma
    SetFunctionCmt(0xc80, 
        "VDP CRAM", 1);

    // SetBasePalette1
    SetFunctionCmt(0xcc4, 
        "Unused palette copy", 1);

    // Sleep
    SetFunctionCmt(0xf04, 
        "Wait for d0.w VInts/Frames.", 1);

    // sub_F3A
    SetFunctionCmt(0xf3a, 
        "unused", 1);

    // sub_F76
    SetFunctionCmt(0xf76, 
        "unused", 1);

    // sub_F90
    SetFunctionCmt(0xf90, 
        "unused", 1);

    // sub_1014
    SetFunctionCmt(0x1014, 
        "unused", 1);

    // ApplyImmediateVramDma
    SetFunctionCmt(0x10dc, 
        "In: a0 = Source, a1 = Destination, d0.w = Length, d1.l = Auto-increment", 1);

    // ApplyVIntVramDma
    SetFunctionCmt(0x119e, 
        "In: a0 = Source, a1 = Destination, d0.w = Length, d1.l = Auto-increment", 1);

    // sub_1234
    SetFunctionCmt(0x1234, 
        "unused", 1);

    // UpdateVdpVScrollData
    SetFunctionCmt(0x12d2, 
        "VDP Vertical Scroll Data", 1);

    // sub_134A
    SetFunctionCmt(0x134a, 
        "unused", 1);

    // sub_135A
    SetFunctionCmt(0x135a, 
        "unused", 1);

    // sub_1372
    SetFunctionCmt(0x1372, 
        "unused", 1);

    // ApplyImmediateVramDmaOnCompressedTiles
    SetFunctionCmt(0x1382, 
        "In: a0 = Source, a1 = Destination, d0.w = Length, d1.l = Auto-increment", 1);

    // sub_13C0
    SetFunctionCmt(0x13c0, 
        "unused DMA code", 1);

    // sub_13E4
    SetFunctionCmt(0x13e4, 
        "unused DMA code", 1);

    // DmaAndWait
    SetFunctionCmt(0x1408, 
        "unused", 1);

    // ApplyVramDmaFill
    SetFunctionCmt(0x140e, 
        "d0.w = Destination, d1.w = Length, d2.w = Filler value", 1);

    // UpdatePlayerInputs
    SetFunctionCmt(0x150e, 
        "Convert data ports 1/2 information into P1/2 inputs State A/B.", 1);

    // sub_15A4
    SetFunctionCmt(0x15a4, 
        "unused", 1);

    // GenerateRandomNumber
    SetFunctionCmt(0x1600, 
        "In: d6.w = Value range, Out: d7.w = Random value", 1);

    // GenerateRandomOrDebugNumber
    SetFunctionCmt(0x1674, 
        "Debug mode allows values 0-3 depending on player direction.\n\
\n\
  In: d0.w = Value range, Out: d0.w = Random or debug value", 1);

    // PlayMusicAfterCurrentOne
    SetFunctionCmt(0x16be, 
        "In: d0.w = music index, or previous music if value $FB", 1);

    // CopyBytes
    SetFunctionCmt(0x16d6, 
        "In: a0 = Source, a1 = Destination, d7.w = Length", 1);

    // InitSprites
    SetFunctionCmt(0x1770, 
        "In: d0.w = Number of sprites to initialize", 1);

    // sub_179C
    SetFunctionCmt(0x179c, 
        "related to spell animations", 1);

    // sub_1942
    SetFunctionCmt(0x1942, 
        "something with clearing/resetting sprite info when transitioning to battlescene?", 1);

    // sub_19C8
    SetFunctionCmt(0x19c8, 
        "palette copies to figure out", 1);

    // sub_19F8
    SetFunctionCmt(0x19f8, 
        "related to palette updating, maybe unused", 1);

    // LoadSpriteData
    SetFunctionCmt(0x1a84, 
        "Basic tile decompression : a0 = Source, a1 = Destination", 1);

    // LoadCompressedData
    SetFunctionCmt(0x1e48, 
        "Stack decompression : a0 = Source, a1 = Destination", 1);

    // LoadMapLayoutData
    SetFunctionCmt(0x20e6, 
        "In: a0 = Source, a1 = Destination", 1);

    // ReadMapLayoutBarrelForBlockFlags
    SetFunctionCmt(0x2296, 
        "Reads next part of barrel to determine flags for next block\n\
barrel = 00\n\
\n\
  In: d0.w = Barrel, Out: d1.w = Block flag word", 1);

    // LoadMapBlocks
    SetFunctionCmt(0x2372, 
        "a0 : input ROM block data\n\
a1 : output RAM data", 1);

    // LoadMapTilesets
    SetFunctionCmt(0x29e2, 
        "In: d1.w = Map index", 1);

    // LoadMap
    SetFunctionCmt(0x2a8c, 
        "Load all map properties (map coords, entities, etc.)\n\
\n\
  In: d1.b = Map index, or -1 to indicate current map", 1);

    // LoadMapArea
    SetFunctionCmt(0x2dec, 
        "In: d0.w, d1.w, d2.w, d3.w = start X, start Y, end X, end Y", 1);

    // OpenDoor
    SetFunctionCmt(0x3e40, 
        "uses door open SFX", 1);

    // ToggleRoofOnMapLoad
    SetFunctionCmt(0x3f2c, 
        "Display (or don't) map roof depending on player's start location.", 1);

    // GetChestItem
    SetFunctionCmt(0x4232, 
        "In: d0.w, d1.w = Candidate coordinates\n\
\n\
Out: a2 = Map layout offset\n\
     d0.w = Layout block offset\n\
     d1.w = Item flag\n\
     d2.w = Item index", 1);

    // IsMapScrollingToViewTarget
    SetFunctionCmt(0x4728, 
        "Out: Z = is scrolling", 1);

    // CreateWindow
    SetFunctionCmt(0x4802, 
        "In: d0.w = width/height, d1.w = X/Y position\n\
Out: a1 = window tiles end, d0.w = window slot (-1 if no free slot available)", 1);

    // SetWindowDestination
    SetFunctionCmt(0x4866, 
        "In DO=Windows index, D1=Value ($8080->X/Y), Out A0=Window properties", 1);

    // MoveWindowWithSfx
    SetFunctionCmt(0x48f4, 
        "In: D0 = window slot\n\
    D1 = destination\n\
    D2 = animation length", 1);

    // MoveWindow
    SetFunctionCmt(0x48f8, 
        "In: D0 = window slot\n\
    D1 = destination\n\
    D2 = animation length", 1);

    // GetWindowInfo
    SetFunctionCmt(0x4c38, 
        "In D0=Window index, Out A0=Address", 1);

    // GetWindowTileAddress
    SetFunctionCmt(0x4c44, 
        "In D0=Windows index, D1=Tile coords, Out A1=Address", 1);

    // sub_4EC6
    SetFunctionCmt(0x4ec6, 
        "related to sprite updates during VInt", 1);

    // esc00_wait
    SetFunctionCmt(0x4fbc, 
        "clear timer and parse next command", 1);

    // esc01_waitUntilDestination
    SetFunctionCmt(0x4fd4, 
        "wait until entity has reached its destination", 1);

    // esc02_controlCharacter
    SetFunctionCmt(0x4ff8, 
        "update next entity", 1);

    // esc04_moveToRelativeDest
    SetFunctionCmt(0x53fe, 
        "related to moving an entity", 1);

    // HasSameDestinationAsOtherEntity
    SetFunctionCmt(0x5610, 
        "Check if another entity has the same destination as current entity.\n\
\n\
Out: CCR zero-bit set if true", 1);

    // esc07_controlRaft
    SetFunctionCmt(0x5668, 
        "related to controlling raft", 1);

    // esc08_controlCaravan
    SetFunctionCmt(0x57ea, 
        "related to controlling caravan", 1);

    // esc0C_setPosition
    SetFunctionCmt(0x5a3c, 
        "set new pos/dest, clear offset", 1);

    // esc0D_clonePosition
    SetFunctionCmt(0x5a64, 
        "set same X pos, dest, offset and facing as other entity", 1);

    // esc10_setSpeed
    SetFunctionCmt(0x5ac8, 
        "set entity 1A-1B values with xxxx", 1);

    // esc11_setAccelerationFactors
    SetFunctionCmt(0x5ad4, 
        "set entity 18-19 values with xxxx", 1);

    // esc12_activateAcceleration
    SetFunctionCmt(0x5ae0, 
        "set or clear entity value 1C bits 0-1 according to xxxx", 1);

    // esc13_activateDeceleration
    SetFunctionCmt(0x5b0e, 
        "set or clear entity value 1C bits 2-3 according to xxxx", 1);

    // esc18_setEntityObstructable
    SetFunctionCmt(0x5b88, 
        "set or clear entity value 1C bit 7 according to xxxx", 1);

    // esc1F_setResizable
    SetFunctionCmt(0x5c3c, 
        "set entity bit 3 of byte $1D", 1);

    // esc21_set1Cbit4
    SetFunctionCmt(0x5c70, 
        "unused command", 1);

    // esc30_branch
    SetFunctionCmt(0x5ca6, 
        "parse from current offset + xxxx", 1);

    // esc41_pass
    SetFunctionCmt(0x5d48, 
        "directly go to next command 4 bytes forward", 1);

    // esc_clearTimerGoToNextEntity
    SetFunctionCmt(0x5d5a, 
        "clear timer and update next entity", 1);

    // UpdateEntityProperties
    SetFunctionCmt(0x6052, 
        "In: d0.b = entity index\n\
    d1.w = new facing direction\n\
    d2.b = new B flags (keep current if = $FF)\n\
    d3.b = new map sprite index (keep current if = $FF)", 1);

    // ChangeEntitySprite
    SetFunctionCmt(0x60a8, 
        "In: a0 = pointer to entity data\n\
    d6.b = facing direction", 1);

    // GetMapPixelCoordRamOffset
    SetFunctionCmt(0x61fc, 
        "In: D0 = x pixel coord\n\
    D1 = y pixel coord\n\
Out: D2 = RAM offset from start of map VDP tile data", 1);

    // DisplayText
    SetFunctionCmt(0x6260, 
        "d0 : string index", 1);

    // CopyAsciiBytesForDialogueString
    SetFunctionCmt(0x6654, 
        "Copy ASCII string of length D7 at A0 to RAM for dialogue textbox", 1);

    // CopyLineOfVdpTileOrderForDialogueWindowToRam
    SetFunctionCmt(0x6860, 
        "In: A1 = address in RAM to copy VDP tile indexes\n\
    D0 = VDP tile index for left border of line\n\
    D1 = VDP tile index for first inner box tile of line\n\
    D2 = VDP tile index for right border of line\n\
    D3 = amount to add to D1 each time a tile is copied (0 for top and bottom border lines, 1 for inner box)", 1);

    // CheckSram
    SetFunctionCmt(0x6ea6, 
        "Out: d0.w, d1.w = -1 if slot 1 or slot 2 failed checksum, respectively.", 1);

    // CopyBytesToSram
    SetFunctionCmt(0x7004, 
        "In: A0 = source address\n\
    A1 = destination address\n\
    D7 = number of bytes to copy", 1);

    // CopyBytesFromSram
    SetFunctionCmt(0x701c, 
        "and calculate checksum", 1);

    // MainLoop
    SetFunctionCmt(0x75c4, 
        "In: D0 = map index\n\
    D1 = player X coord\n\
    D2 = player Y coord\n\
    D3 = player facing\n\
    D4 = ???\n\
    D7 = battle index ($FFFF for none)\n\
...more", 1);

    // GetSavePointForMap
    SetFunctionCmt(0x75ec, 
        "In: D0 = from map index\n\
Out: D0 = to map index\n\
     D1 = X\n\
     D2 = Y\n\
     D3 = facing", 1);

    // CheckMapSwitch
    SetFunctionCmt(0x7956, 
        "Alter map index if certain flags are set (Granseal, Pacalon, etc)\n\
\n\
      In: D0 = map index\n\
\n\
      Out: D0 = new map index", 1);

    // CheckBattle
    SetFunctionCmt(0x799c, 
        "In: D0 = map index (if not supplied, will be pulled from CURRENT_MAP)\n\
    D1 = player X coord to check\n\
    D2 = player Y coord to check\n\
Out: D7 = battle index to trigger ($FFFF if none)\n\
...more", 1);

    // UpdateWitchLayoutZone
    SetFunctionCmt(0x7d28, 
        "D1=Width/Height", 1);

    // SoundTest
    SetFunctionCmt(0x7fa4, 
        "Function is missing in US version.", 1);

    // j_GetMoveInfo
    SetFunctionCmt(0x82bc, 
        "entity D0's current MOV*2, X, Y -> D0, D3, D4", 1);

    // GetCombatantName
    SetFunctionCmt(0x82d0, 
        "In: D0 = combatant index\n\
\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetClass
    SetFunctionCmt(0x8306, 
        "Get combatant D0's class index -> D1", 1);

    // GetCurrentLevel
    SetFunctionCmt(0x8316, 
        "Get combatant D0's current level -> D1", 1);

    // GetMoveType
    SetFunctionCmt(0x846a, 
        "Get combatant D0's move type, shifted into lower nibble position -> D1", 1);

    // GetAiCommandset
    SetFunctionCmt(0x8480, 
        "Get combatant D0's AI commandset -> D1", 1);

    // GetAiSpecialMoveOrders
    SetFunctionCmt(0x8494, 
        "Out: D1 = combatant index to follow\n\
     D2 = second AI point", 1);

    // GetAiRegion
    SetFunctionCmt(0x84b0, 
        "In: D0 = combatant index\n\
\n\
Out: D1 = AI activation region index 1\n\
     D2 = AI activation region index 2", 1);

    // GetEnemyIndex
    SetFunctionCmt(0x84dc, 
        "In: d0.b = combatant index\n\
Out: d1.w = enemy index, or -1 if not an enemy", 1);

    // GetCombatantType
    SetFunctionCmt(0x851a, 
        "Get combatant d0.w type -> d1.w\n\
\n\
If combatant is an ally, type is equal to combatant index plus allies number\n\
 times class type (0, 1, or 2 for base, promoted, and special, respectively),\n\
 and the most significant bit is set. However, this feature is unused.\n\
\n\
Otherwise, if an enemy, return the enemy index.", 1);

    // LoadAllyName
    SetFunctionCmt(0x855a, 
        "In: a0 = pointer to temporarily loaded name in RAM", 1);

    // FindName
    SetFunctionCmt(0x8976, 
        "In: A0 = address of names list\n\
    D1 = name index\n\
\n\
Out: A0 = address of entry in names list\n\
     D7 = length of name", 1);

    // ApplyStatusEffectsAndItemsOnStats
    SetFunctionCmt(0x89ce, 
        "Update all current stats", 1);

    // ApplyStatusEffectsOnStats
    SetFunctionCmt(0x8a26, 
        "In: D0 = combatant index\n\
    D3 = status effects bitfield", 1);

    // ApplyItemOnStats
    SetFunctionCmt(0x8a90, 
        "In: A2 = address in RAM of combatant's prowess\n\
    D0 = combatant index\n\
    D1 = item index", 1);

    // FindItemName
    SetFunctionCmt(0x8bd0, 
        "In: D1 = item entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetItemDefAddress
    SetFunctionCmt(0x8be4, 
        "Out: A0 = pointer to definition for item D1", 1);

    // GetItemAndNumberHeld
    SetFunctionCmt(0x8bfa, 
        "In: D0 = combatant index, D1 = item slot\n\
Out: D1 = item entry, D2 = number of items held", 1);

    // GetEquipmentType
    SetFunctionCmt(0x8c28, 
        "In: D1 = item index\n\
\n\
Out: D2 = equipment type (0 = item, 1 = weapon, $FFFF = ring)", 1);

    // GetEquippedWeapon
    SetFunctionCmt(0x8c4c, 
        "Get combatant D0's equipped weapon and slot indexes -> D1 and D2 ($FFFF if nothing equipped)", 1);

    // GetEquippedRing
    SetFunctionCmt(0x8c56, 
        "Get combatant D0's equipped ring and slot indexes -> D1 and D2 ($FFFF if nothing equipped)", 1);

    // AddItem
    SetFunctionCmt(0x8ca2, 
        "In: D0 = combatant index\n\
    D1 = item index\n\
\n\
Out: D2 = 0 if item successfully added, 1 if no empty slot available", 1);

    // BreakItemBySlot
    SetFunctionCmt(0x8cd4, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D2 = 3 if item slot is empty", 1);

    // EquipItemBySlot
    SetFunctionCmt(0x8d34, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D2 = 0 if equipped, 1 if not, 2 if equipped and cursed, 3 if item is nothing", 1);

    // IsItemEquippableAndCursed
    SetFunctionCmt(0x8d6a, 
        "Is item equippable, and is it cursed ?\n\
\n\
      In: D0 = ally index\n\
          D1 = item index\n\
\n\
      Out: D2 = 0 if equippable, 1 if not, 2 if equippable and cursed", 1);

    // UnequipItemBySlotIfNotCursed
    SetFunctionCmt(0x8d9e, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D2 = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if nothing", 1);

    // IsItemInSlotEquippedOrCursed
    SetFunctionCmt(0x8db6, 
        "Is item in slot equipped, and if so, is it cursed ?\n\
\n\
      In: D0 = ally index\n\
          D1 = item slot\n\
\n\
      Out: A0 = pointer to item entry\n\
           D2 = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if neither", 1);

    // UnequipItemBySlot
    SetFunctionCmt(0x8dfe, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D2 = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if nothing", 1);

    // DropItemBySlot
    SetFunctionCmt(0x8e12, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D2 = 2 if not dropped, 3 if dropped or nothing", 1);

    // RemoveAndArrangeItems
    SetFunctionCmt(0x8e5c, 
        "In: A0 = char entry address + offset to items\n\
    D0 = item slot", 1);

    // RemoveItemBySlot
    SetFunctionCmt(0x8e76, 
        "In: D0 = combatant index\n\
    D1 = item slot", 1);

    // GetEquippableWeapons
    SetFunctionCmt(0x8eee, 
        "Out: A0 = pointer to equippable items list\n\
     D1 = equippable weapons count", 1);

    // GetEquippableRings
    SetFunctionCmt(0x8ef8, 
        "Out: A0 = pointer to equippable items list\n\
     D1 = equippable rings count", 1);

    // IsItemEquippable
    SetFunctionCmt(0x8f60, 
        "In: D1 = item index\n\
    D2 = item type bitmask (for ANDing the item type bitfield)\n\
    D3 = class equip bitmask (for ANDing the item equip bitfield)", 1);

    // GetNewATTandDEFwithItemEquipped
    SetFunctionCmt(0x8fee, 
        "In: A0 = combatant entry address\n\
    D1 = item index\n\
    D2 = item type (weapon or ring)\n\
\n\
Out: D2 = current ATT with item equipped\n\
     D3 = current DEF with item equipped", 1);

    // IsItemCursed
    SetFunctionCmt(0x90b2, 
        "Is item D1 cursed ? CCR carry-bit set if true", 1);

    // IsItemUsableInBattle
    SetFunctionCmt(0x90cc, 
        "carry set : YES", 1);

    // IsItemUsableWeaponInBattle
    SetFunctionCmt(0x90e6, 
        "carry set : NO", 1);

    // UnequipAllItemsIfNotCursed
    SetFunctionCmt(0x9106, 
        "In: D0 = combatant index", 1);

    // GetItemSlotContainingIndex
    SetFunctionCmt(0x9194, 
        "In: D0 = entity index\n\
    D1 = item index\n\
\n\
Out: D2 = item slot ($FFFF if not held)", 1);

    // FindSpellName
    SetFunctionCmt(0x91c6, 
        "In: D1 = spell index\n\
\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // FindSpellDefAddress
    SetFunctionCmt(0x91da, 
        "Find pointer to definition entry for spell D1 -> A0", 1);

    // GetSpellAndNumberOfSpells
    SetFunctionCmt(0x91fa, 
        "In: D0 = combatant index\n\
    D1 = spell slot\n\
\n\
Out: D1 = first spell entry\n\
     D2 = number of spells learned", 1);

    // LearnSpell
    SetFunctionCmt(0x9226, 
        "In: D0 = ally index\n\
    D1 = spell entry\n\
\n\
Out: D2 = result (0 = success, 1 = failure : same or higher level known, 2 = failure : no room)", 1);

    // GetSpellCost
    SetFunctionCmt(0x927e, 
        "Get spell D1's MP cost -> D1", 1);

    // GetCombatantEntryAddress
    SetFunctionCmt(0x928e, 
        "Get pointer to combatant D0's entry in RAM -> A0", 1);

    // SetCombatantByte
    SetFunctionCmt(0x92e0, 
        "In: D0 = combatant index\n\
    D1 = byte\n\
    D7 = offset", 1);

    // SetCombatantWord
    SetFunctionCmt(0x92e8, 
        "In: D0 = combatant index\n\
    D1 = word\n\
    D7 = offset", 1);

    // GetCombatantByte
    SetFunctionCmt(0x92f8, 
        "In: D0 = combatant index\n\
    D7 = combatant byte offset\n\
\n\
Out: D1 = byte", 1);

    // GetCombatantWord
    SetFunctionCmt(0x9302, 
        "In: D0 = combatant index\n\
    D7 = combatant word offset\n\
\n\
Out: D1 = word", 1);

    // IncreaseAndClampByte
    SetFunctionCmt(0x9312, 
        "clamp byte D7 of entity D0's information + D1 between D5 and D6", 1);

    // DecreaseAndClampByte
    SetFunctionCmt(0x936c, 
        "clamp byte D7 of entity D0's information - D1 between D5 and D6", 1);

    // GetDistanceBetweenEntities
    SetFunctionCmt(0x941e, 
        "Get distance between two combatants (simple X and Y calculation, no obstructions)\n\
\n\
      In: D0 = from combatant\n\
          D1 = to combatant\n\
\n\
      Out: D2 = distance", 1);

    // LevelUp
    SetFunctionCmt(0x9484, 
        "In: D0 = ally index", 1);

    // InitAllyStats
    SetFunctionCmt(0x95c6, 
        "In: d0.w = ally index\n\
    d1.w = starting level", 1);

    // CalculateStatGain
    SetFunctionCmt(0x96ba, 
        "In: d1.w = current stat value\n\
    d2.w = growth curve index\n\
    d3.w = starting value\n\
    d4.w = projected value\n\
    d5.w = current level\n\
\n\
Out: d1.w = stat gain value", 1);

    // InitAllyCombatantEntry
    SetFunctionCmt(0x975e, 
        "In: D0 = ally index", 1);

    // LoadAllyClassData
    SetFunctionCmt(0x97f8, 
        "In: D0 = ally index\n\
    D1 = class index", 1);

    // InitGameSettings
    SetFunctionCmt(0x9844, 
        "Clear all flags and important game variables.", 1);

    // GetFlag
    SetFunctionCmt(0x98e8, 
        "flag bit check pattern based on bit number D1 -> D0", 1);

    // UpdateForce
    SetFunctionCmt(0x9900, 
        "Determine who is in the force or not based on flags and update RAM lists.", 1);

    // JoinForce
    SetFunctionCmt(0x9956, 
        "In: D0 = ally index", 1);

    // LeaveForce
    SetFunctionCmt(0x9976, 
        "In: D0 = ally index", 1);

    // IsInBattleParty
    SetFunctionCmt(0x9994, 
        "In: D0 = ally index", 1);

    // JoinBattleParty
    SetFunctionCmt(0x99ac, 
        "In: D0 = ally index", 1);

    // LeaveBattleParty
    SetFunctionCmt(0x99c0, 
        "In: D0 = ally index", 1);

    // GetDealsItemAmount
    SetFunctionCmt(0x99de, 
        "In: D1 = item index\n\
\n\
Out: D2 = number of item index in deals", 1);

    // AddItemToDeals
    SetFunctionCmt(0x99ec, 
        "In: D1 = item index", 1);

    // RemoveItemFromDeals
    SetFunctionCmt(0x9a02, 
        "In: D1 = item index", 1);

    // GetDealsItemInfo
    SetFunctionCmt(0x9a16, 
        "In: D1 = item index\n\
\n\
Out: A0 = RAM address of deals slot\n\
     D0 = amount to add to deals slot (0x10 or 0x01)\n\
     D2 = number of item index in deals", 1);

    // AddItemToCaravan
    SetFunctionCmt(0x9a3c, 
        "In: d1.w = item index (only the actual index is used, the status bits are cut out)", 1);

    // RemoveItemFromCaravan
    SetFunctionCmt(0x9a62, 
        "In: d1.w = inventory slot", 1);

    // DebugModeSelectHits
    SetFunctionCmt(0x9b58, 
        "In: A2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript
    SetFunctionCmt(0x9b92, 
        "In: d0.w = actor index", 1);

    // DetermineTargetsByAction
    SetFunctionCmt(0x9dd6, 
        "In: A3 = action data", 1);

    // InitBattlesceneDisplayedCombatants
    SetFunctionCmt(0x9e60, 
        "In: A2 = battlescene script stack frame\n\
    A3 = pointer to action type in RAM\n\
    A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // DetermineIneffectiveAttack
    SetFunctionCmt(0x9ec4, 
        "In: A2 = battlescene script stack frame", 1);

    // InitBattlesceneProperties
    SetFunctionCmt(0x9f28, 
        "In: A2 = battlescene script stack frame\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of actor index\n\
    A5 = address in RAM of target index", 1);

    // CreateBattlesceneMessage
    SetFunctionCmt(0xa05c, 
        "Load proper battlescene message script depending on action.\n\
\n\
      In: a3 = action type index in RAM\n\
          a4 = actor index in RAM\n\
\n\
<HARDCODED> enemy and message indexes", 1);

    // CreateBattlesceneAnimation
    SetFunctionCmt(0xa200, 
        "Load proper battlescene sprite/magic animation properties.\n\
\n\
      In: a2 = battlescene script stack frame\n\
          a3 = pointer to action data in RAM\n\
          a4 = battlescene actor index in RAM", 1);

    // WriteBattlesceneScript_End
    SetFunctionCmt(0xa34e, 
        "In: A2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript_DoAction
    SetFunctionCmt(0xa3f4, 
        "In: A2 = battlescene script stack frame\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of actor index\n\
    A5 = address in RAM of target index", 1);

    // FinalDoubleAttackCheck
    SetFunctionCmt(0xa45e, 
        "In: A2 = battlescene script stack frame", 1);

    // IsAbleToCounterAttack
    SetFunctionCmt(0xa49c, 
        "In: a2 = battlescene script stack frame\n\
Out: -12(a2) = 0 if false, otherwise true", 1);

    // GetSpellAnimation
    SetFunctionCmt(0xa54e, 
        "In: a2 = battlescene script stack frame\n\
    a3 = pointer to battleaction in RAM\n\
    a4 = pointer to battlescene actor index in RAM\n\
\n\
Out: d4 = spell animation index\n\
\n\
  HARDCODED class, enemy and weapon indexes", 1);

    // WriteBattlesceneScript_AnimateAction
    SetFunctionCmt(0xa6e8, 
        "Load proper battlescene sprite and spell animations properties\n\
\n\
    In: D4 = spell/item/projectile animation index, set $80 to come from enemy\n\
        D5 = animation type index (0 = attack, 1 = dodge, 2 = spell/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)", 1);

    // WriteBattlesceneScript_SwitchTargets
    SetFunctionCmt(0xa702, 
        "In: A2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript_EXPandGold
    SetFunctionCmt(0xa7f8, 
        "In: A2 = battlescene script stack frame", 1);

    // GetAmountOfEXPforEncounter
    SetFunctionCmt(0xa968, 
        "Get amount of EXP gained from encounter based on level difference between actor and target\n\
\n\
      In: A4 = pointer to actor index in RAM\n\
          A5 = pointer to target index in RAM\n\
\n\
      Out: D5 = amount of EXP", 1);

    // WriteBattlesceneScript_Attack
    SetFunctionCmt(0xaab6, 
        "In: A2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript_DodgeAttack
    SetFunctionCmt(0xaafc, 
        "In: A2 = battlescene script stack frame\n\
    A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // CalculateDamage
    SetFunctionCmt(0xabbe, 
        "In: A4 = attacker index in RAM\n\
    A5 = defender index in RAM\n\
\n\
Out: D6 = damage", 1);

    // DetermineCriticalHit
    SetFunctionCmt(0xac4e, 
        "In: A2 = battlescene script stack frame\n\
    D6 = damage", 1);

    // WriteBattlesceneScript_InflictDamage
    SetFunctionCmt(0xacea, 
        "In: A2 = battlescene script stack frame\n\
    A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM\n\
    D6 = damage", 1);

    // WriteBattlesceneScript_InflictAilment
    SetFunctionCmt(0xae32, 
        "In: A2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript_InflictCurseDamage
    SetFunctionCmt(0xaf70, 
        "In: A2 = battlescene script stack frame\n\
    D6 = damage", 1);

    // DetermineDoubleAndCounter
    SetFunctionCmt(0xb00e, 
        "In: A2 = battlescene script stack frame\n\
    A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // WriteBattlesceneScript_CastSpell
    SetFunctionCmt(0xb0a8, 
        "In: A2 = battlescene stack\n\
    A3 = scene action type in RAM\n\
    A4 = actor index in RAM\n\
    A5 = target index in RAM", 1);

    // SpellEffect_Desoul
    SetFunctionCmt(0xb516, 
        "In: A2 = battlescene script stack frame", 1);

    // ApplyRandomEffectiveness
    SetFunctionCmt(0xba98, 
        "In: A2 = battlescene script stack frame", 1);

    // CalculateDamage_Spell
    SetFunctionCmt(0xbb02, 
        "In: A2 = battlescene script stack frame\n\
    D2 = resistance setting (0=none, 1=minor, 2=major, 3=weakness)\n\
    D3 = chance to critical hit", 1);

    // AdjustSpellPower
    SetFunctionCmt(0xbb56, 
        "Miscellaneous hacks to alter spell power (125% if promoted, damage divided if SORC spells)\n\
\n\
      In: A3 = pointer to action type index in RAM\n\
          A4 = pointer to caster's index in RAM\n\
          D6 = original spell power\n\
\n\
      Out: D6 = altered spell power", 1);

    // GetItemBreakMessage
    SetFunctionCmt(0xbc9a, 
        "In: A2 = battlescene script stack frame\n\
    D0 = whether item is already damaged (0=no, 1=yes)\n\
\n\
Out: D3 = message index", 1);

    // WriteBattlesceneScript_EnemyDropItem
    SetFunctionCmt(0xbd24, 
        "In: A2 = battlescene script stack frame\n\
    A3 = scene action type in RAM\n\
    A4 = actor index in RAM\n\
    A5 = target index in RAM", 1);

    // GetEnemyDestination
    SetFunctionCmt(0xc024, 
        "In: d0.b = combatant index\n\
Out: d1.w, d2.w = X,Y coordinates", 1);

    // ConvertCoordToOffset
    SetFunctionCmt(0xc09a, 
        "    Convert coordinate to offset and add to address argument.\n\
    In: A0 = start of grid\n\
        D1 = X coord\n\
        D2 = Y coord\n\
    Out: A0 = start of grid + offset", 1);

    // ClearTargetGrid
    SetFunctionCmt(0xc0a8, 
        "    Clear valid target index grid at RAM:5600.", 1);

    // ClearMovableGrid
    SetFunctionCmt(0xc0c4, 
        "    Clear moveable tile data at RAM:4400 and RAM:4d00.", 1);

    // GetTargetAtCoordOffset
    SetFunctionCmt(0xc0e8, 
        "    Get value at converted coordinate offset.\n\
    In: D1 = X coord\n\
        D2 = Y coord\n\
    Out: D0 = terrain at offset", 1);

    // GetMoveCostToEntity
    SetFunctionCmt(0xc0fc, 
        "get distance from current unit to entity D0 -> D0", 1);

    // GetDestinationMoveCost
    SetFunctionCmt(0xc118, 
        "get movecost to get to tile D1,D2 -> D0", 1);

    // GetCurrentTerrainType
    SetFunctionCmt(0xc144, 
        "get terrain type of tile under entity D0 -> D0", 1);

    // GetTerrain
    SetFunctionCmt(0xc160, 
        "    Get obstruction at converted coordinate offset.\n\
    In: D1 = X coord\n\
        D2 = Y coord\n\
    Out: D0 = target at offset", 1);

    // MemorizePath
    SetFunctionCmt(0xc18c, 
        "Populate move costs list for currently moving entity", 1);

    // GetLandEffectSetting
    SetFunctionCmt(0xc1da, 
        "In:  d0.b = combatant index\n\
Out: d1.b = land effect setting (0 = 0%, 1 = 15%, 2 = 30%)", 1);

    // SetMovableAtCoord
    SetFunctionCmt(0xc204, 
        "Set coord to movable in movable grid\n\
\n\
      In: D1 = X coord\n\
          D2 = Y coord", 1);

    // GetResistanceToSpell
    SetFunctionCmt(0xc22a, 
        "Get combatant D0's resistance setting to spell D1 -> D2", 1);

    // DetermineMuddleBattleaction
    SetFunctionCmt(0xc27a, 
        "Check for muddle 2'd units to control whether or not they take an action,\n\
 and to prevent them from killing Bowie or bosses.\n\
\n\
In:  d0 = character index of attacker\n\
     d1 = character index of defender\n\
Out: d3 = 0 or 1\n\
\n\
If d3=1 upon return, then no action is taken by the attacker.\n\
\n\
Return 1 if...\n\
        ally attacker and defender is Bowie\n\
        enemy attacker attacking the first enemy (usually the boss)\n\
        50/50 odds to return 1 if attacker targets itself\n\
Return 0 otherwise.", 1);

    // GetMoveInfo
    SetFunctionCmt(0xc2c8, 
        "Get combatant D0's current MOV*2, X, Y -> D0, D3, D4", 1);

    // GetAttackRange
    SetFunctionCmt(0xc306, 
        "Get max/min attack range for combatant d0.b -> d3.w, d4.w", 1);

    // GetSpellRange
    SetFunctionCmt(0xc380, 
        "In: D1 = spell index\n\
Out: D3 = max range, D4 = min range", 1);

    // GetItemRange
    SetFunctionCmt(0xc398, 
        "In: D1 = item index\n\
Out: D3 = max range, D4 = min range", 1);

    // CheckMuddled2
    SetFunctionCmt(0xc3b0, 
        "In: D0 = combatant index\n\
Out: D1 = whether combatant is inflicted with MUDDLE 2 (0=no, 1=yes)", 1);

    // CreateItemRangeGrid
    SetFunctionCmt(0xc44c, 
        "In: D0 = user combatant index\n\
    D1 = item index", 1);

    // CreateSpellRangeGrid
    SetFunctionCmt(0xc478, 
        "Clear and update target/movable grids based on spell properties\n\
\n\
      In: D0 = caster combatant index\n\
          D1 = spell index", 1);

    // ApplyRelativeCoordListToGrids
    SetFunctionCmt(0xc510, 
        "Apply coord list at A0 and add any targets to target list\n\
\n\
      In: A0 = address of relative coord list\n\
          D0 = current entity index\n\
          D1 = starting X coord\n\
          D2 = starting Y coord", 1);

    // CreateTargetGrid
    SetFunctionCmt(0xc62e, 
        "In: D1 = spell entry", 1);

    // GetClosestAttackPosition
    SetFunctionCmt(0xc71a, 
        "In: D1 = X pos, D2 = Y pos, D3 = max range, D4 = min range\n\
\n\
Out: D1 = chosen X pos, return $FF if no attack position is available\n\
     D2 = chosen Y pos", 1);

    // MakeTargetsList_Allies
    SetFunctionCmt(0xc7fa, 
        "Clear target grid, then add allies", 1);

    // MakeTargetsList_Everybody
    SetFunctionCmt(0xc81c, 
        "Populate a list of all combatants on the battlefield", 1);

    // PrioritizeReachableTargets
    SetFunctionCmt(0xc958, 
        "Populate lists of targets reachable by item, spell, and regular attack,\n\
 then give each target a priority value.\n\
\n\
To allow AI to cast more than one spell, this must be adjusted.\n\
\n\
      In: D0, D7 = character index\n\
          D1, D6 = extra AI variable (values of 0-3)", 1);

    // CalculateAttackTargetPriority
    SetFunctionCmt(0xcaea, 
        "In: A0 = list of reachable targets\n\
    A1 = movement to each reachable target\n\
    A2 = \n\
    D0 = caster index\n\
    D1 = spell index\n\
    D2 = target of the spell\n\
\n\
Out: D6 = target priority (higher is better)", 1);

    // AdjustAttackTargetPriorityForDifficulty
    SetFunctionCmt(0xcb18, 
        "This first calculates expected max damage from a physical attack\n\
 and places that value into d6.\n\
\n\
This then calls one of the difficulty-based subroutines,\n\
 which sets d6 = target priority value instead (using the\n\
 \"remaining HP of target\" as a key part of the target priority).\n\
\n\
      In:  D0 = attacker, D1 = defender\n\
      Out: D6 = target priority (higher number = better target)", 1);

    // AdjustSpellTargetPriorityForDifficulty
    SetFunctionCmt(0xcba2, 
        "This first calculates expected spell damage and then calls one of the\n\
 difficulty-based subroutines to calculate target priority.\n\
\n\
It then sums these priority values for each enemy in the AOE and returns the result.\n\
\n\
      In:  d0 = attacker, d1 = spell index\n\
      Out: d6 = sum of target priority of all targets in the AOE", 1);

    // CalculatePotentialDamage
    SetFunctionCmt(0xcc0c, 
        "In: D0 = attacker, D1 = defender\n\
Out: D6 = max potential physical damage value, adjusted for land effect", 1);

    // GetSpellPowerAdjustedForResistance
    SetFunctionCmt(0xcc54, 
        "In: D0 = target combatant index\n\
    D1 = spell index\n\
\n\
Out: D6 = adjusted power", 1);

    // CalculatePotentialRemainingHP
    SetFunctionCmt(0xcc8a, 
        "In: D0 = target index, D6 = potential damage\n\
Out: D1 = target's potential remaining HP", 1);

    // TargetPriorityScript1
    SetFunctionCmt(0xcca0, 
        "+1 base priority\n\
+15 if target is expected to die\n\
+2 if target is the same as last turn's target", 1);

    // TargetPriorityScript2
    SetFunctionCmt(0xccd4, 
        "+1 base priority\n\
+15 if target is expected to die\n\
+1 if target loses more than 2/3 of remaining health\n\
+1 if target is brought under 20% health\n\
+2 if target is the same as last turn's target", 1);

    // TargetPriorityScript3
    SetFunctionCmt(0xcd18, 
        "+1 base priority\n\
1/3rd of the time, +15 priority if target is expected to die\n\
2/3rd of the time, +18 minus 2x +1 the move required to attack target (prioritize closer targets)", 1);

    // TargetPriorityScript4
    SetFunctionCmt(0xcd4c, 
        "+1 base priority\n\
+15 if target is expected to die\n\
+1 if target is brought under 20% health", 1);

    // DetermineHealingSpellLevel
    SetFunctionCmt(0xcd68, 
        "Decide which level of spell to use based upon the HP missing from target\n\
 and the MP available to the caster.\n\
\n\
  In: d0.b = heal target character index\n\
      d1.b = combatant index of the spell caster\n\
      d4.b = spell entry\n\
\n\
  Out: d2.w = spell level to cast (if -1, then no spell is cast)", 1);

    // CalculateHealTargetPriority
    SetFunctionCmt(0xcdea, 
        "If the target for healing uses AI #14 or #15, then return the maximum\n\
 priority of 13.\n\
\n\
If not, then return a priority based upon the movetype for the enemy,\n\
 which approximately goes highest to lowest priority of\n\
 healer, mage, archer, flyer, melee, aquatic.\n\
\n\
Specific decending priority for each move type is in tbl_MovetypesHealTargetPriority.\n\
\n\
The first byte in that table is $FF to ensure there is never a movetype\n\
 match and therefore nothing has a priority higher than AI #14 or AI #15.\n\
\n\
      In: D0 = target index\n\
      Out: D6 = target priority", 1);

    // AdjustTargetPriorityForAlly
    SetFunctionCmt(0xce36, 
        "Extra adjustments on target priority if the attacker is an ally \n\
 (does not apply to enemies.)\n\
\n\
In: D0 = defender index\n\
    D1 = defenders remaining HP after taking theoretical max damage from an attack (prior routines)\n\
    D4 = attacker index (the one attacking or casting the offensive spell)\n\
    D7 = who the enemy targeted last\n\
\n\
Out: D6 = priority of the action (basically the total max damage output of the action plus adjustments)", 1);

    // GetHighestUsableSpellLevel
    SetFunctionCmt(0xced2, 
        "Get highest usable level of spell D1, considering current MP and highest known level\n\
\n\
      In: D0 = caster index\n\
          D1 = highest known level spell entry\n\
\n\
      Out: D1 = highest usuable level spell entry", 1);

    // GetSlotContainingSpell
    SetFunctionCmt(0xcf0e, 
        "In: D0 = combatant index\n\
    D1 = spell index\n\
\n\
Out: D1 = spell index\n\
     D2 = slot", 1);

    // GetSlotContainingItem
    SetFunctionCmt(0xcf40, 
        "In: D0 = combatant index\n\
    D1 = item index\n\
\n\
Out: D1 = item index\n\
     D2 = slot", 1);

    // GetNextUsableAttackSpell
    SetFunctionCmt(0xcf74, 
        "Get next attack spell usable by the caster.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot", 1);

    // GetNextHealingSpell
    SetFunctionCmt(0xd018, 
        "Get next healing spell known by the combatant.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot", 1);

    // GetNextSupportSpell
    SetFunctionCmt(0xd062, 
        "Get next support spell known by the combatant.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot", 1);

    // GetNextUsableAttackItem
    SetFunctionCmt(0xd0ac, 
        "Get the next item in combatant's inventory that can be used to cast\n\
 BLAZE/FREEZE/BOLT/BLAST. <HARDCODED>\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot", 1);

    // GetNextUsableHealingItem
    SetFunctionCmt(0xd160, 
        "Get the next item in combatant's inventory that can be used to cast\n\
 a healing spell. <HARDCODED>\n\
\n\
This only looks for Healing Rain as a valid healing item,\n\
 unless the AI is set to use the item the in battle data.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot", 1);

    // IsCombatantAtLessThanHalfHP
    SetFunctionCmt(0xd296, 
        "In: D0 = combatant index\n\
Out: carry clear if true", 1);

    // sub_D2F8
    SetFunctionCmt(0xd2f8, 
        "In: D0 = defender index\n\
    D1 = defenders theoretical remaining HP after attack\n\
\n\
Set the carry flag if less than 2/3rds of defenders remaining HP\n\
 is expected to be taken by the attack.", 1);

    // sub_D310
    SetFunctionCmt(0xd310, 
        "unused", 1);

    // sub_D326
    SetFunctionCmt(0xd326, 
        "unused", 1);

    // sub_D336
    SetFunctionCmt(0xd336, 
        "unused", 1);

    // sub_D34C
    SetFunctionCmt(0xd34c, 
        "unused", 1);

    // sub_D362
    SetFunctionCmt(0xd362, 
        "In: D0 = defender index\n\
    D1 = defenders theoretical remaining HP after attack\n\
\n\
Set the carry flag if the defender is expected to have more than 20%\n\
 of max HP remain after attack.", 1);

    // DoesCombatantRequireHealing
    SetFunctionCmt(0xd38a, 
        "Is combatant d0 at 2/3 or less of max HP? Return carry clear if true.", 1);

    // GetDifficulty
    SetFunctionCmt(0xd408, 
        "Out: D1 = 0 if normal, 1 if hard, 2 if super, 3 if ouch", 1);

    // MakePrioritiesListForSpell_Attack
    SetFunctionCmt(0xd460, 
        "AI: cast ATTACK spell", 1);

    // MakePrioritiesListForSpell_Boost2
    SetFunctionCmt(0xd4e0, 
        "AI: cast BOOST 2 spell", 1);

    // MakePrioritiesListForSpell_Dispel
    SetFunctionCmt(0xd560, 
        "AI: cast DISPEL spell", 1);

    // MakePrioritiesListForSpell_Muddle2
    SetFunctionCmt(0xd62c, 
        "AI: cast MUDDLE 2 spell", 1);

    // CalculateDispelSpellTargetPriority
    SetFunctionCmt(0xd6f2, 
        "Returns priority for the AI to cast DISPEL.\n\
+1 point for each target within the area of effect that knows at least\n\
 one attack or healing spell.\n\
\n\
Out: d1.w = target priority", 1);

    // CalculateBoostSpellTargetPriority
    SetFunctionCmt(0xd742, 
        "Returns priority for the AI to cast BOOST.\n\
\n\
Out: d1.w = target priority", 1);

    // CalculateAttackSpellTargetPriority
    SetFunctionCmt(0xd7aa, 
        "Returns priority for the AI to cast ATTACK.\n\
\n\
Out: d1.w = target priority", 1);

    // MakeAiMoveString
    SetFunctionCmt(0xdd10, 
        "In: A2 = loading space\n\
    A3 = loading space\n\
    D0 = destination X\n\
    D1 = destination Y", 1);

    // AddAllToStack
    SetFunctionCmt(0xdd60, 
        "unused", 1);

    // MakeEnemyMoveOrder
    SetFunctionCmt(0xdd78, 
        "create enemy move order from movecost lists", 1);

    // ExecuteAiControl
    SetFunctionCmt(0xdefc, 
        "related to AI controlled unit (enemy, auto-control cheat, MUDDLEd force member)\n\
\n\
    In: D0 = AI controlled combatant index", 1);

    // CountDefeatedEnemies
    SetFunctionCmt(0xe0b6, 
        "Out: d1.w = defeated enemies count", 1);

    // HandleAiCommand
    SetFunctionCmt(0xe294, 
        "In: d0.b = combatant index\n\
    d1.b = command code (like Heal, Attack, etc.)", 1);

    // ExecuteAiCommand_Heal
    SetFunctionCmt(0xe3ee, 
        "In: d0.b = caster index\n\
    d1.w = command parameter (values of 0-2), unused\n\
\n\
Out: d1.w = $FFFF if command failed", 1);

    // ExecuteAiCommand_Attack
    SetFunctionCmt(0xe78c, 
        "In: D0 = character index (attacker)\n\
    D1 = extra AI variable (values of 0-3)", 1);

    // ExecuteAiCommand_SpecialMove
    SetFunctionCmt(0xe98c, 
        "Move scripts (move to point, follow ally, follow force member)", 1);

    // ExecuteAiCommand_Support
    SetFunctionCmt(0xeba4, 
        "Supoort spells AI (Muddle 2, Dispel 1)\n\
\n\
      In: D0 = caster index", 1);

    // DetermineAiBattleaction
    SetFunctionCmt(0xedd6, 
        "AI randomly chooses whether to attack, cast a spell, or use an item.\n\
\n\
Then, AI will always target the highest priority option based upon\n\
 the chosen action, unless there are multiple options with equal priority.\n\
\n\
      In: D0 = character index of attacker\n\
      Out: D0 = target index, D1 = priority (max of 15), D2 = battle action\n\
\n\
If no targets in range then D0 = $FFFF, D1 = 0, D2 = 3", 1);

    // ExecuteAiCommand_Move
    SetFunctionCmt(0xf1d4, 
        "In: D0 = character index (mover)\n\
    D1 = extra AI variable (values of 0-2)", 1);

    // j_PlayEndKiss
    SetFunctionCmt(0x100b4, 
        "related to end kiss", 1);

    // WriteTilesFromAsciiWithOrangeFont
    SetFunctionCmt(0x100c8, 
        "Write tiles from ASCII using the orange font", 1);

    // WriteTilesFromNumber
    SetFunctionCmt(0x100d4, 
        "write tiles from number in D0 into A1 D7 letters, window width D1", 1);

    // WriteTilesFromAsciiWithRegularFont
    SetFunctionCmt(0x100e2, 
        "Write tiles from ASCII from A0 into A1 D7 letters, window width D1\n\
", 1);

    // sub_1018E
    SetFunctionCmt(0x1018e, 
        "draw box tiles into A1, dimensions in D0, including borders (xxyy)", 1);

    // ExecuteMenu
    SetFunctionCmt(0x101f6, 
        "In: A0 = special subroutine address to handle menu, default handling if not supplied (unused functionality)\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // LoadDiamenuWindowVdpTileData
    SetFunctionCmt(0x103b8, 
        "In: -12(A6) = window slot index", 1);

    // ExecuteItemMenu
    SetFunctionCmt(0x10586, 
        "In: A0 = special subroutine address to handle menu, default handling if not supplied\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // sub_107EA
    SetFunctionCmt(0x107ea, 
        "related to menu choice", 1);

    // LoadHighlightableSpellIcon
    SetFunctionCmt(0x10940, 
        "Copy spell icon to RAM\n\
\n\
      In: A1 = destination in RAM\n\
          D0 = spell index\n\
\n\
      Out: A1 = end of affected section after copy", 1);

    // ExecuteMagicMenu
    SetFunctionCmt(0x10a4a, 
        "In: A0 = special subroutine address to handle menu, default handling if not supplied\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // sub_10CB0
    SetFunctionCmt(0x10cb0, 
        "related to menu choice", 1);

    // sub_10CC6
    SetFunctionCmt(0x10cc6, 
        "In: D0 = displayed spell icon", 1);

    // CreateBattlefieldMiniStatusWindow
    SetFunctionCmt(0x11572, 
        "In: d0.w = combatant index", 1);

    // ShowAllyBattlesceneWindow
    SetFunctionCmt(0x11638, 
        "In: d0.b = ally index\n\
    d1.w = ?", 1);

    // ShowEnemyBattlesceneWindow
    SetFunctionCmt(0x116b8, 
        "In: d0.b = enemy index\n\
    d1.w = ?", 1);

    // DrawColoredStatBar
    SetFunctionCmt(0x1173a, 
        "Draw colored stat bars into ministatus window layout at A1\n\
\n\
In: A0 = loading space address\n\
    D0 = current HP/MP value\n\
    D1 = max HP/MP value\n\
    D2 = VDP tile index", 1);

    // WriteStatBarColumn
    SetFunctionCmt(0x11862, 
        "Write one column of HP/MP bar pixels into A0\n\
\n\
    In: D4 = stat bar column index\n\
        D7 = drawn columns count", 1);

    // AdjustStringLengthForSpecialCharacters
    SetFunctionCmt(0x11898, 
        "Check ASCII name at A0 for two special characters", 1);

    // BuildMiniStatusWindow
    SetFunctionCmt(0x118be, 
        "In: a1 = window tiles address, d0.w = combatant index", 1);

    // WriteStatValue
    SetFunctionCmt(0x11aae, 
        "Write stat value d0.w or '??' if above 99", 1);

    // CopyMiniStatusWindowTileColumn
    SetFunctionCmt(0x11ac6, 
        "Draw tiles from a0 into a1 (one column)", 1);

    // BuildMemberScreen
    SetFunctionCmt(0x11c2a, 
        "Create and display member screen\n\
\n\
      In: D0 = member index", 1);

    // AddStatusEffectTileIndexesToVdpTileOrder
    SetFunctionCmt(0x11eea, 
        "In: A1 = address of VDP tile order in RAM", 1);

    // BuildMemberStatusWindow
    SetFunctionCmt(0x11ff0, 
        "In: a1 = window tile adress, d0.w = combatant index", 1);

    // sub_12606
    SetFunctionCmt(0x12606, 
        "Unused function", 1);

    // GetCombatantPortrait
    SetFunctionCmt(0x1263a, 
        "Get portrait index for combatant d0.w -> d0.w", 1);

    // LoadCombatantPortrait
    SetFunctionCmt(0x13394, 
        "In: D0 = combatant index", 1);

    // GetSelectedMember
    SetFunctionCmt(0x13462, 
        "    Get index of currently selected force member (in menus).\n\
    Out: D0 = selected index (capped to 255)", 1);

    // WriteMemberListText
    SetFunctionCmt(0x135a6, 
        "In: a1 = window tiles address, d0.w = selected member index", 1);

    // sub_14074
    SetFunctionCmt(0x14074, 
        "related to menu choice", 1);

    // sub_14108
    SetFunctionCmt(0x14108, 
        "related to equip menu", 1);

    // BuildEquippingWindow
    SetFunctionCmt(0x141ce, 
        "In: D1 = old equipped item index\n\
    D2 = old equipped item slot\n\
    D3 = equippable items count", 1);

    // sub_1445A
    SetFunctionCmt(0x1445a, 
        "Handle out of battle MAGIC menu", 1);

    // LoadMiniStatusTextHighlightSprites
    SetFunctionCmt(0x146ae, 
        "In: D1 = blinking frame timer", 1);

    // EquipNewItem
    SetFunctionCmt(0x1477e, 
        "Try to unequip current item, and equip new one if successful\n\
\n\
     In: D1 = old item index\n\
         D2 = old item slot\n\
         D4 = new item slot", 1);

    // sub_14B28
    SetFunctionCmt(0x14b28, 
        "related to gold display", 1);

    // sub_14BB0
    SetFunctionCmt(0x14bb0, 
        "copy item icon tiles into RAM based on index list at RAM:b0ae", 1);

    // sub_14C56
    SetFunctionCmt(0x14c56, 
        "copy shop price tag pixels to A0 in RAM", 1);

    // CopyIconPixels
    SetFunctionCmt(0x14cb2, 
        "Copy item D1 icon pixels to A0 in RAM", 1);

    // GetSelectedItem
    SetFunctionCmt(0x14cec, 
        "Get index of currently selected item in shop/caravan (from index list) -> D0", 1);

    // sub_15422
    SetFunctionCmt(0x15422, 
        "d0 = FFAFE7, related to DMA", 1);

    // ClosePortraitEyes
    SetFunctionCmt(0x154f6, 
        "Close princess Elis's eyes when unconscious", 1);

    // UpdatePortrait
    SetFunctionCmt(0x155c4, 
        "d1 = alternate/original, d7 = tile number", 1);

    // LoadPortrait
    SetFunctionCmt(0x1562a, 
        "In: D0 = portrait index", 1);

    // sub_156A8
    SetFunctionCmt(0x156a8, 
        "Unused window function", 1);

    // sub_156BC
    SetFunctionCmt(0x156bc, 
        "Unused window function", 1);

    // sub_156CE
    SetFunctionCmt(0x156ce, 
        "Unused window function", 1);

    // GetAllyPortrait
    SetFunctionCmt(0x15736, 
        "In: D0 = ally or portrait index (depending on caller function)\n\
\n\
Out: D0 = portrait index adjusted for class", 1);

    // sub_1586E
    SetFunctionCmt(0x1586e, 
        "related to battlefield options", 1);

    // NameAlly
    SetFunctionCmt(0x15bb0, 
        "In: D0 = ally index", 1);

    // NumberPrompt
    SetFunctionCmt(0x16282, 
        "In: D0 = default number\n\
    D1 = min number\n\
    D2 = max number\n\
\n\
Out: D0 = chosen number", 1);

    // WritePromptNumberTiles
    SetFunctionCmt(0x16376, 
        "In: A6 = number prompt window stack", 1);

    // ModifyPromptNumber
    SetFunctionCmt(0x16398, 
        "In: A6 = number prompt window stack", 1);

    // InitializeBattlescene
    SetFunctionCmt(0x18012, 
        "In: d0.w = enemy index\n\
    d1.w = ally index", 1);

    // bsc00_animateEnemyAction
    SetFunctionCmt(0x183f4, 
        "xx      animation type index (0000 for attack, 0001 for dodge, 0002 for magic/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)\n\
yy      magic/item/projectile animation index, set $0080 to come from enemy", 1);

    // bsc01_animateAllyAction
    SetFunctionCmt(0x184e8, 
        "xx      animation type index (0000 for attack, 0001 for dodge, 0002 for magic/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)\n\
yy      magic/item/projectile animation index, set $0080 to come from enemy", 1);

    // bsc03_moveAllyBattleSprite
    SetFunctionCmt(0x185c8, 
        "like previous bsc but for battlescene ally", 1);

    // bsc02_moveEnemyBattleSprite
    SetFunctionCmt(0x185de, 
        "set a long value at FFB3F6, related to battlescene enemy", 1);

    // bsc05_makeAllyIdle
    SetFunctionCmt(0x185f4, 
        "related to battlescene ally", 1);

    // bsc04_makeEnemyIdle
    SetFunctionCmt(0x1869a, 
        "related to battlescene enemy", 1);

    // bsc07_switchAllies
    SetFunctionCmt(0x186da, 
        "xx      Combatant index\n\
yy      0000 for right side, 0001 for left side", 1);

    // bsc06_switchEnemies
    SetFunctionCmt(0x1893e, 
        "xx      Combatant index\n\
yy      0000 for right side, 0001 for left side", 1);

    // bsc08_switchToEnemyAlone
    SetFunctionCmt(0x18d5a, 
        "xx enemy index", 1);

    // bsc09_switchToAllyAlone
    SetFunctionCmt(0x18d8c, 
        "xx ally index", 1);

    // bsc0B_executeAllyReaction
    SetFunctionCmt(0x18dbe, 
        "same parameters as previous command", 1);

    // bsc0A_executeEnemyReaction
    SetFunctionCmt(0x18f4e, 
        "Byte 00-01      HP change, signed.\n\
Byte 02-03      MP change, signed.\n\
Byte 04-05      Set status bytes.\n\
Byte 06-07      Flags - 0x0001 enemy flash/sound", 1);

    // bsc0F_giveEXP
    SetFunctionCmt(0x190dc, 
        "Byte 00-01      Amount of EXP.", 1);

    // bsc10_displayMessage
    SetFunctionCmt(0x191e0, 
        "        Byte 00-01      Main string index.\n\
        Byte 02-03      Character name index.\n\
        Byte 04-05      Magic/item index.\n\
        Byte 06-09      Number.", 1);

    // bsc11_displayMessageWithNoWait
    SetFunctionCmt(0x1922a, 
        "same params as previous command", 1);

    // sub_193B2
    SetFunctionCmt(0x193b2, 
        "related to battlescene ally and weapon VDP sprites", 1);

    // sub_193C4
    SetFunctionCmt(0x193c4, 
        "related to battlescene ally VDP sprites", 1);

    // sub_19504
    SetFunctionCmt(0x19504, 
        "related to battlescene ground VDP sprites", 1);

    // sub_19564
    SetFunctionCmt(0x19564, 
        "related to battlescene weapon VDP sprites", 1);

    // MakeActorIdle
    SetFunctionCmt(0x195e2, 
        "make actor idle", 1);

    // AddEnemyToDeadList
    SetFunctionCmt(0x197a6, 
        "Add enemy to dead combatants list.", 1);

    // GetAllyAnimation
    SetFunctionCmt(0x197c8, 
        "In: D1 = animation type, Out: A0 = animation pointer", 1);

    // GetEnemyAnimation
    SetFunctionCmt(0x19838, 
        "In: D1 = animation type, Out: A0 = animation pointer", 1);

    // GetAllyBattleSpriteIdleAnimate
    SetFunctionCmt(0x19860, 
        "Return whether or not ally battle sprite should animate when idle\n\
\n\
      In: D0 = ally battle sprite index\n\
\n\
      Out: D1 = 0 if animates, 1 if not", 1);

    // GetEnemyBattleSpriteIdleAnimate
    SetFunctionCmt(0x1986a, 
        "Return whether or not enemy battle sprite should animate when idle\n\
\n\
      In: D0 = enemy battle sprite index\n\
\n\
      Out: D1 = 0 if animates, 1 if not", 1);

    // InitializeBattlescenePalettes
    SetFunctionCmt(0x19884, 
        "Clear palettes 1-2 and 1-2bis, and load battlescene UI and ground palette to 3bis.", 1);

    // LoadEnemyBattleSpritePropertiesAndPalette
    SetFunctionCmt(0x19970, 
        "In: d0.w = enemy battle sprite index\n\
    d1.w = palette index", 1);

    // LoadEnemyBattleSpriteFrameToVram
    SetFunctionCmt(0x1999e, 
        "In: d0.w = enemy battle sprite index\n\
    d1.w = frame index", 1);

    // LoadEnemyBattleSpriteFrameAndWaitForDma
    SetFunctionCmt(0x199bc, 
        "In: d0.w = enemy battle sprite index\n\
    d1.w = frame index", 1);

    // LoadAllyBattleSpritePropertiesAndPalette
    SetFunctionCmt(0x199de, 
        "In: d0.w = ally battle sprite index\n\
    d1.w = palette index", 1);

    // LoadAllyBattleSpriteFrameToVram
    SetFunctionCmt(0x19a0c, 
        "In: d0.w = ally battle sprite index\n\
    d1.w = frame index", 1);

    // LoadAllyBattleSpriteFrameAndWaitForDma
    SetFunctionCmt(0x19a2a, 
        "In: d0.w = ally battle sprite index\n\
    d1.w = frame index", 1);

    // LoadWeaponPalette
    SetFunctionCmt(0x19a4c, 
        "In: d0.w = weapon palette index", 1);

    // LoadWeaponSprite
    SetFunctionCmt(0x19a5c, 
        "In: d0.w = weapon sprite index", 1);

    // LoadAllyBattleSpriteFrame
    SetFunctionCmt(0x19ab0, 
        "In: d0.w = ally battle sprite index\n\
    d1.w = frame index", 1);

    // LoadEnemyBattleSpriteFrame
    SetFunctionCmt(0x19b24, 
        "In: d0.w = enemy battle sprite index\n\
    d1.w = frame index", 1);

    // LoadNewEnemyBattleSprite
    SetFunctionCmt(0x19b44, 
        "In: d0.w = enemy battle sprite index", 1);

    // LoadBattlesceneBackground
    SetFunctionCmt(0x19b80, 
        "In: d0.w = battlescene background index", 1);

    // LoadBattlesceneGround
    SetFunctionCmt(0x19bcc, 
        "In: d0.w = battlescene ground index", 1);

    // LoadInvocationSpellTilesToVram
    SetFunctionCmt(0x19bf2, 
        "In: d0.w = invocation sprite index", 1);

    // LoadSpellGraphics
    SetFunctionCmt(0x19ca4, 
        "In: d0.w = spell animation tiles index", 1);

    // LoadSpellGraphicsForInvocation
    SetFunctionCmt(0x19ce8, 
        "Loads spell graphics for Apollo and Neptun invocations.\n\
\n\
In: d0.w = spell animation tiles index", 1);

    // GetBattleSpriteAndPalette
    SetFunctionCmt(0x19d3e, 
        "Get battle sprite and palette indexes for combatant D0 -> D1 (sprite), D2 (palette)", 1);

    // GetWeaponSpriteAndPalette
    SetFunctionCmt(0x19db0, 
        "Get battlescene weapon sprite and palette indexes for equipped weapon.\n\
\n\
In: d0.w = combatant index\n\
Out: d2.w = weapon sprite index, d3.w = palette index", 1);

    // GetBattlesceneBackground
    SetFunctionCmt(0x19dfe, 
        "In: d0.w = combatant index\n\
Out: d1.w = battlescene background index", 1);

    // GetBattlesceneGround
    SetFunctionCmt(0x19e6e, 
        "In: d0.w = combatant index\n\
Out: d1.w = battlescene ground index", 1);

    // sub_19E96
    SetFunctionCmt(0x19e96, 
        "Get a boolean depending on background index", 1);

    // ExecuteSpellAnimation
    SetFunctionCmt(0x19ee6, 
        "Execute spell animation D0", 1);

    // sub_19FAA
    SetFunctionCmt(0x19faa, 
        "In: a0 = pointer to spell animation data", 1);

    // sub_1A0E2
    SetFunctionCmt(0x1a0e2, 
        "restore some colors", 1);

    // sub_1A100
    SetFunctionCmt(0x1a100, 
        "Lower brightness of most elements on the screen to 50%", 1);

    // sub_1A122
    SetFunctionCmt(0x1a122, 
        "Lower the brightness of most elements on the screen to 75%", 1);

    // sub_1A14A
    SetFunctionCmt(0x1a14a, 
        "Apply a greyscale palette to most elements on the screen", 1);

    // sub_1A19E
    SetFunctionCmt(0x1a19e, 
        "Tint the screen blue", 1);

    // sub_1A1CA
    SetFunctionCmt(0x1a1ca, 
        "Tint the screen green", 1);

    // sub_1A1F6
    SetFunctionCmt(0x1a1f6, 
        "Tint the screen red", 1);

    // Tint_Apollo
    SetFunctionCmt(0x1a222, 
        "Tint parts of the screen red", 1);

    // ExecSpellAnimationFlash
    SetFunctionCmt(0x1a2a6, 
        "    In: D0 = color to flash", 1);

    // ClearSpellAnimationProperties
    SetFunctionCmt(0x1a2d4, 
        "    Clears a portion at RAM:b406 and RAM:b532 for spell properties.", 1);

    // LoadInvocationSpell
    SetFunctionCmt(0x1a32c, 
        "code for invocations", 1);

    // sa1F_OddEyeBeam
    SetFunctionCmt(0x1b716, 
        "and maybe Zynk's beam too ?", 1);

    // DetermineDealsItemsNotInCurrentShop
    SetFunctionCmt(0x207fe, 
        "Create list of deals items not normally sold in current shop", 1);

    // DoesCurrentShopContainItem
    SetFunctionCmt(0x20834, 
        "In: D1 = item index\n\
\n\
Out: Zero-bit clear = yes, set = no", 1);

    // GetShopInventoryAddress
    SetFunctionCmt(0x20852, 
        "Get shop inventory address -> A0", 1);

    // GetPromotionData
    SetFunctionCmt(0x210d0, 
        "Get promotion data for class d1.b, given section type d2.w\n\
\n\
      Out: -32(a6) = promotion section offset\n\
           -34(a6) = promotion section length\n\
           -36(a6) = cannot promote flag (1 if no matching promotion data found)", 1);

    // FindPromotionSection
    SetFunctionCmt(0x2110c, 
        "In: D2 = section type (regpre, regpost, specpre, specpost, specitem)\n\
Out: A0 = address", 1);

    // ReplaceSpellsWithSORCdefaults
    SetFunctionCmt(0x2112c, 
        "In: A6 = church actions stack", 1);

    // Church_GetCurrentForceMemberInfo
    SetFunctionCmt(0x21156, 
        "Out: D7 = force members counter", 1);

    // sub_219EC
    SetFunctionCmt(0x219ec, 
        "copy available targets list ?", 1);

    // DisplaySpecialCaravanDescription
    SetFunctionCmt(0x22864, 
        "only used for chirrup sandals", 1);

    // CopyCaravanItems
    SetFunctionCmt(0x22926, 
        "Copy caravan item indexes to generic list space", 1);

    // IsItemInSlotEquippedAndCursed
    SetFunctionCmt(0x2294c, 
        "Is character D0's item in slot D1 equipped and cursed ? CCR carry-bit set if true", 1);

    // FindUsableOutsideBattleItem
    SetFunctionCmt(0x229ca, 
        "Out: D2 = 0 if true, $FFFFFFFF if false", 1);

    // UseFieldItem
    SetFunctionCmt(0x229ec, 
        "Find specific item index + code offset to run when used in field\n\
\n\
      In: D1 = item entry", 1);

    // GetCurrentPosition
    SetFunctionCmt(0x22c60, 
        "get first entity's X, Y and facing", 1);

    // ControlBattleEntity
    SetFunctionCmt(0x22e1a, 
        "Out: d2.b = chosen X\n\
     d3.b = chosen Y\n\
     d4.w = copied P1 input state bitfield", 1);

    // GetEntityIndexForCombatant_0
    SetFunctionCmt(0x22f2a, 
        "Pointless wrapper (should instead directly branch to subroutine below)", 1);

    // GetEntityIndexForCombatant
    SetFunctionCmt(0x22f30, 
        "Get entity index for combatant D0 -> D0", 1);

    // GetEntityEventIndex
    SetFunctionCmt(0x22f4a, 
        "In: D0 = entity index\n\
Out: D0 = entity event index", 1);

    // SetUnitCursorDestinationToNextCombatant
    SetFunctionCmt(0x232ac, 
        "In: d0.w = combatant index", 1);

    // SetUnitCursorDestinationToNextBattleEntity
    SetFunctionCmt(0x232bc, 
        "In: d2.w, d3.w = entity X,Y coordinates", 1);

    // UpdateBattleEntitySprite
    SetFunctionCmt(0x234c8, 
        "In: a1 = pointer to entity data\n\
    d6.b = facing direction", 1);

    // SetEntityPosition
    SetFunctionCmt(0x2376a, 
        "In: D0 = entity index\n\
    D1 = x pos\n\
    D2 = y pos", 1);

    // GetActivatedEntity
    SetFunctionCmt(0x2379a, 
        "Out: D0 = activated entity index\n\
     D1 = activated entity's facing\n\
     D2 = player entity's facing", 1);

    // CheckIfEntityIsFollower
    SetFunctionCmt(0x23846, 
        "In: D0 = entity index\n\
Out: Z = entity is NOT follower", 1);

    // CheckArea
    SetFunctionCmt(0x23862, 
        "Get item or area description", 1);

    // GetChestGoldAmount
    SetFunctionCmt(0x2399c, 
        "get amount of gold (D2 - 0x80) as an offset from the gold table (see constants)", 1);

    // BattleLoop
    SetFunctionCmt(0x23a84, 
        "In: D0 = map index\n\
    D1 = battle index", 1);

    // GetRemainingCombatants
    SetFunctionCmt(0x23c58, 
        "Get number of allies living, number of enemies living -> D2, D3", 1);

    // GetEgressPositionForBattle
    SetFunctionCmt(0x23e50, 
        "HARDCODED special cases", 1);

    // ExecuteIndividualTurn
    SetFunctionCmt(0x23eb0, 
        "In: d0.w = combatant index", 1);

    // HandleAfterTurnEffects
    SetFunctionCmt(0x24242, 
        "Handle after-turn effects (status effects, HP/MP regen/degen, etc.)\n\
\n\
      In: d0.w = combatant index", 1);

    // SpawnEnemy
    SetFunctionCmt(0x24490, 
        "In: D0 = combatant", 1);

    // UpdateTargetsListForCombatant
    SetFunctionCmt(0x24642, 
        "In: D0 = combatant index", 1);

    // sub_24662
    SetFunctionCmt(0x24662, 
        "Handle player input when controlling battle entity.", 1);

    // sub_24966
    SetFunctionCmt(0x24966, 
        "    createSpellRangeGridMaster ?", 1);

    // sub_24C4E
    SetFunctionCmt(0x24c4e, 
        "In: A0 = pointer to equippable items list\n\
    D1 = old item index\n\
    D2 = old item slot\n\
    D3 = equippable items count", 1);

    // EquipNewItemInBattle
    SetFunctionCmt(0x24c94, 
        "In: D2 = old item slot\n\
    D4 = new item slot", 1);

    // sub_252FA
    SetFunctionCmt(0x252fa, 
        "related to AI controlled unit (enemy, auto-control cheat, MUDDLEd force member)", 1);

    // UpdateAllEnemiesAi
    SetFunctionCmt(0x2550c, 
        "<BUG> A Goddess Staff is added to the deals section in shops whenever a DEF-CON switch \n\
      is activated, and if one of the following items is also present :\n\
      - Quick Ring\n\
      - Protect Ring\n\
      - White Ring\n\
      - Running Ring\n\
\n\
End function with a RTS intruction to fix", 1);

    // AddCombatantAndRandomizedAGItoTurnOrder
    SetFunctionCmt(0x255a4, 
        "In: a0 = pointer to turn order entry\n\
    d0.w = combatant index", 1);

    // LoadBattle
    SetFunctionCmt(0x25610, 
        "load all battle properties", 1);

    // GetEntityPositionAfterApplyingFacing
    SetFunctionCmt(0x256b2, 
        "In: D0 = combatant index\n\
Out: D0 = new X\n\
     D1 = new Y", 1);

    // PrintActivatedDefCon
    SetFunctionCmt(0x25772, 
        "if flag D1 is set, AI region active, display def-con textbox", 1);

    // sub_258A8
    SetFunctionCmt(0x258a8, 
        "update main entity properties", 1);

    // WaitForEvent
    SetFunctionCmt(0x2591c, 
        "Wait for event OR player action (A/C button)", 1);

    // ProcessPlayerAction
    SetFunctionCmt(0x25ad6, 
        "Manage debug actions, entity events, item finds, area descriptions, caravan or main menu", 1);

    // LoadSpecialSprite
    SetFunctionCmt(0x25c24, 
        "In: d1.w = special map sprite index", 1);

    // DisplaySegaLogo
    SetFunctionCmt(0x2804c, 
        "Out: D0 = $FFFFFFFF if pressing start, 0 if not", 1);

    // InitDecoder
    SetFunctionCmt(0x2e10e, 
        "Initialise Huffman decoder\n\
- clear Huffman (script) data\n\
- set starting tree", 1);

    // j_RunMapSetupItemEvent
    SetFunctionCmt(0x44088, 
        "triggers a map setup function according to up to 4 criterias in d1-d4", 1);

    // j_MapEventType2
    SetFunctionCmt(0x44098, 
        "related to followers maybe", 1);

    // IsOverworldMap
    SetFunctionCmt(0x44268, 
        "Out: ccr zero-bit clear if true", 1);

    // GetAllyMapSprite
    SetFunctionCmt(0x449c6, 
        "Get mapsprite index for combatant d0.w -> d4.w", 1);

    // GetCombatantMapSprite
    SetFunctionCmt(0x44a7c, 
        "In: a6 = battle vars stack\n\
Out: d4.w = map sprite index", 1);

    // SetEntityActscript
    SetFunctionCmt(0x44b4a, 
        "In: d0.w = entity index", 1);

    // SetControlledEntityActScript
    SetFunctionCmt(0x44b5c, 
        "In: d0.w = entity index", 1);

    // SetUnitCursorSpeedx2
    SetFunctionCmt(0x44b94, 
        "In: d0.w = entity index", 1);

    // SetUnitCursorActscript
    SetFunctionCmt(0x44baa, 
        "In: d0.w = entity index", 1);

    // sub_44BC0
    SetFunctionCmt(0x44bc0, 
        "In: d0.w = entity index", 1);

    // sub_44BD6
    SetFunctionCmt(0x44bd6, 
        "In: d0.w = entity index", 1);

    // MakeEntityIdle
    SetFunctionCmt(0x44bec, 
        "In: d0.w = entity index", 1);

    // ApplyInitActscript
    SetFunctionCmt(0x44c02, 
        "In: d0.w = entity index", 1);

    // SetEntityMovescriptToIdle
    SetFunctionCmt(0x44c18, 
        "In: d0.w = entity index", 1);

    // AddFollower
    SetFunctionCmt(0x44c2e, 
        "In: d0.w = entity index", 1);

    // HideEntity
    SetFunctionCmt(0x44c84, 
        "In: d0.w = entity index", 1);

    // SetWalkingActscript
    SetFunctionCmt(0x44cd0, 
        "In: d0.w = entity index", 1);

    // sub_44D0E
    SetFunctionCmt(0x44d0e, 
        "In: d0.w = entity index", 1);

    // WaitForEntityToStopMoving
    SetFunctionCmt(0x44da4, 
        "In: d0.w = entity index", 1);

    // GetEntityEntryAddress
    SetFunctionCmt(0x44dd8, 
        "Get RAM address of entity d0.w -> a0", 1);

    // WaitForFollowersStopped
    SetFunctionCmt(0x45204, 
        "still to confirm", 1);

    // WaitForHeroAndFollowersStopped
    SetFunctionCmt(0x4520e, 
        "to confirm", 1);

    // WaitForPartyEntitiesIdle
    SetFunctionCmt(0x45218, 
        "to confirm", 1);

    // ApplyActscriptToHeroAndFollowers
    SetFunctionCmt(0x4524c, 
        "might be related to followers", 1);

    // ApplyActscriptToFollowers
    SetFunctionCmt(0x45254, 
        "to confirm", 1);

    // MapEventType2
    SetFunctionCmt(0x45268, 
        "Control Caravan", 1);

    // MapEventType3
    SetFunctionCmt(0x453c6, 
        "Control Raft", 1);

    // GetEntityPortaitAndSpeechSfx
    SetFunctionCmt(0x45638, 
        "Get portrait and speech sfx for character d0.w -> d1.w, d2.w", 1);

    // csc35_setBlocksVar
    SetFunctionCmt(0x46582, 
        "similar to setBlocks", 1);

    // csc36_resetMap
    SetFunctionCmt(0x4658e, 
        "related to loading a map", 1);

    // csc15_setEntityActscript
    SetFunctionCmt(0x46978, 
        "x y zzzz : actscript read timer, wait for entity idle or not, actscript", 1);

    // csc16_waitUntilEntityIdle
    SetFunctionCmt(0x4699a, 
        "xxxx", 1);

    // csc17_setEntityPosAndFacingWithFlash
    SetFunctionCmt(0x469ac, 
        "make entity flash progressively faster, and set new pos-dest-facing", 1);

    // csc19_setEntityPosAndFacing
    SetFunctionCmt(0x46a12, 
        "use xxxxxxxx if alive or yyyyyyyy if dead", 1);

    // csc20_updateDefeatedAllies
    SetFunctionCmt(0x46af0, 
        "if X Pos == -1, then dead", 1);

    // csc22_animateEntityFadeInOrOut
    SetFunctionCmt(0x46b42, 
        "0/1 = scan down/up, 2/3 = wipe out/in, 4/5 = slide out/in, 6/7 = mosaic out/in", 1);

    // csc24_setCameraTargetEntity
    SetFunctionCmt(0x46c38, 
        "set playable entity 00xx or something like that", 1);

    // csc2F_fly
    SetFunctionCmt(0x46ea8, 
        "specific entity behaviour for skreech join cutscene", 1);

    // GetEntityAddressFromCharacter
    SetFunctionCmt(0x4704a, 
        "    Get address of entity information. Could be a force member or an opponent\n\
    In: D0 = playable character from FFB140\n\
    Out: A5 = entity info address in RAM", 1);

    // AdjustScriptPointerByCharacterAliveStatus
    SetFunctionCmt(0x47080, 
        "move script pointer d7 forward if character dead", 1);

    // sub_4709E
    SetFunctionCmt(0x4709e, 
        "Launches DMA\n\
\n\
    In: A5 = entity data pointer", 1);

    // ExecuteMapScript
    SetFunctionCmt(0x4712c, 
        "In: A0 = script address", 1);

    // csc08_joinForce
    SetFunctionCmt(0x47398, 
        "make 00xx character join force with bit 15 set for sad join music", 1);

    // csc0C_jumpIfFlagSet
    SetFunctionCmt(0x47418, 
        "xxxx yyyyyyyy", 1);

    // csc0D_jumpIfFlagClear
    SetFunctionCmt(0x4742c, 
        "xxxx yyyyyyyy", 1);

    // csc0F_jumpIfCharacterDead
    SetFunctionCmt(0x47464, 
        "xxxx yyyyyyyy", 1);

    // csc10_setOrClearFlag
    SetFunctionCmt(0x4747a, 
        "xxxx yyyy", 1);

    // csc13_setStoryFlag
    SetFunctionCmt(0x474e0, 
        "xxxx", 1);

    // RunMapSetupEntityEvent
    SetFunctionCmt(0x4761a, 
        "In: D0 = entity event index", 1);

    // LoadAndDisplayCurrentPortrait
    SetFunctionCmt(0x476e8, 
        "Get index of current portrait for dialogue window and load it", 1);

    // GetMapSetupEntityList
    SetFunctionCmt(0x47790, 
        "returns entity list of map setup in a0", 1);

    // GetCurrentMapSetup
    SetFunctionCmt(0x4779e, 
        "returns map setup address in a0", 1);

    // sub_4781A
    SetFunctionCmt(0x4781a, 
        "reset entity flags and sprite", 1);

    // sub_47832
    SetFunctionCmt(0x47832, 
        "reset entity flags and sprite and facing ?", 1);

    // ExecuteBattleCutscene_Intro
    SetFunctionCmt(0x47a50, 
        "cutscene before the battle begins", 1);

    // ExecuteBattleCutscene_Start
    SetFunctionCmt(0x47aee, 
        "cutscene at the start of battle (after units are placed and battle officially begins)\n\
\n\
only seems to happen in first \"above Pacalon\" battle", 1);

    // ApplyPositionsAfterEnemyLeaderDies
    SetFunctionCmt(0x47d9e, 
        "After-battlescene listener used to prepare entity positions for end cutscene before the enemy leader dies.\n\
Only used in battle 5.", 1);

    // ExecuteBattleRegionCutscene
    SetFunctionCmt(0x47e82, 
        "executes cutscenes activated by regions", 1);

    // csub_4CD56
    SetFunctionCmt(0x4cd56, 
        "Jaro joins the Force", 1);

    // DiscardItem
    SetFunctionCmt(0x4f570, 
        "In: D1 = item slot\n\
    D2 = item index", 1);

    // Map8_DescFunc6
    SetFunctionCmt(0x562ba, 
        "set after you open the tree in Ribble with the wooden plank", 1);

    // sub_6051E
    SetFunctionCmt(0x6051e, 
        "unused descriptions which look similar to the default ones for map 5", 1);

    // WaitForPlayer1InputStart
    SetFunctionCmt(0x100204, 
        "wait for max d0 frames", 1);

    // sub_1AC024
    SetFunctionCmt(0x1ac024, 
        "AI-related", 1);

    // sub_1AC028
    SetFunctionCmt(0x1ac028, 
        "AI-related", 1);

    // sub_1AC030
    SetFunctionCmt(0x1ac030, 
        "AI-related", 1);

    // sub_1AC038
    SetFunctionCmt(0x1ac038, 
        "AI-related", 1);

    // sub_1AC054
    SetFunctionCmt(0x1ac054, 
        "Battle-related", 1);

    // j_GetLaserFacing
    SetFunctionCmt(0x1ac05c, 
        "AI-related", 1);

    // LoadEndCreditsFont
    SetFunctionCmt(0x1ac29c, 
        "Generates font from basetile font.\n\
Stretches characters from 1 tile to 2 tiles vertically.\n\
Also creates a shadow effect using palette index 2.", 1);

    // sub_1AC38E
    SetFunctionCmt(0x1ac38e, 
        "AI-related", 1);

    // sub_1AC4F0
    SetFunctionCmt(0x1ac4f0, 
        "something with targetting grid or ???", 1);

    // sub_1AC5AA
    SetFunctionCmt(0x1ac5aa, 
        "AI-related", 1);

    // ClearTerrainListObstructions
    SetFunctionCmt(0x1ac654, 
        "clear upper two bits from all tiles in terrain list", 1);

    // sub_1AC69A
    SetFunctionCmt(0x1ac69a, 
        "AI-related", 1);

    // sub_1AC728
    SetFunctionCmt(0x1ac728, 
        "AI-related", 1);

    // sub_1AC7FE
    SetFunctionCmt(0x1ac7fe, 
        "AI-related", 1);

    // GetLaserFacing
    SetFunctionCmt(0x1ac8a0, 
        "AI-related", 1);

    // sub_1AC9FC
    SetFunctionCmt(0x1ac9fc, 
        "AI-related\n\
\n\
In: d0.b = \n\
Out: d1.w = ", 1);

    // sub_1ACA72
    SetFunctionCmt(0x1aca72, 
        "AI-related", 1);

    // sub_1ACAD6
    SetFunctionCmt(0x1acad6, 
        "AI-related", 1);

    // CheckTriggerRegionFlag
    SetFunctionCmt(0x1ace32, 
        "In: d0.b = region index", 1);

    // UpdateTriggeredRegionsAndAi
    SetFunctionCmt(0x1ace4a, 
        "In: d0.w = combatant index", 1);

    // GetListOfSpawningEnemies
    SetFunctionCmt(0x1acf30, 
        "adds respawning enemy #s to target list in RAM", 1);

    // UpdateEnemyActivationIfDead
    SetFunctionCmt(0x1ad002, 
        "In: D0 = character index\n\
    D4 = character index (same as D0)\n\
\n\
Out: D0 = 0000 if activated and dead, $FFFF if not", 1);

    // BattleDebugFunction1B120A
    SetFunctionCmt(0x1b120a, 
        "Never called, probably what remains of some debugging code ?", 1);

    // InitEnemyBattlePosition
    SetFunctionCmt(0x1b130c, 
        "In: d0.b = combatant index", 1);

    // UpdateEnemyStatsForRespawn
    SetFunctionCmt(0x1b13a0, 
        "In: D0 = character index\n\
    D1 = character word 34 (AI stuff)\n\
\n\
Out: carry = 0 if respawn, 1 if not", 1);

    // InitEnemyStats
    SetFunctionCmt(0x1b140a, 
        "In: a0 = pointer to battle entity definition\n\
    d0.b = combatant index", 1);

    // IsEnemyStartingPositionOccupied
    SetFunctionCmt(0x1b1554, 
        "In: d3.w = enemy starting tile x (from battle def)\n\
    d4.w = enemy starting tile y (from battle def)\n\
\n\
Out: CCR carry-bit set if true", 1);

    // SetEnemyBaseATT
    SetFunctionCmt(0x1b15aa, 
        "Set enemy base ATT according to difficulty", 1);

    // GetEnemyAiTargetPosition
    SetFunctionCmt(0x1b15f8, 
        "coords of anchor point used in AI byte D0 -> D1, D2", 1);

    // GetBattleSpritesetSubsection
    SetFunctionCmt(0x1b1630, 
        "In: d1.w = subsection index\n\
Out: a0 = subsection address, d1.w = subsection size", 1);

    // GetCombatantStartingPositions
    SetFunctionCmt(0x1b169e, 
        "Get starting X and Y of combatant D0 -> D1, D2", 1);

    // sub_1B16FE
    SetFunctionCmt(0x1b16fe, 
        "Battle-related\n\
\n\
      In: D1 = \n\
          D2 = ", 1);

    // DoesBattleUpgrade
    SetFunctionCmt(0x1b1780, 
        "Check if current battle can be upgraded (0x0000=no, 0xffff=yes) -> D1", 1);

    // UpgradeBattle
    SetFunctionCmt(0x1b17bc, 
        "Strange use case where \"Battle completed\" flag is set for battle 4 in spite of being alreeady set earlier.", 1);

    // ShouldBattleUpgrade
    SetFunctionCmt(0x1b17fe, 
        "check if battle should be upgraded based on index in RAM:f712 and if normal battle was done (0=no, 1=yes) -> D1", 1);

    // UpgradeEnemyIndex
    SetFunctionCmt(0x1b184c, 
        "Upgrade enemy index d1.w -> d1.w", 1);

    // HasJaroJoinedTheForce
    SetFunctionCmt(0x1b1a28, 
        "Check if Jaro has joined the Force\n\
\n\
      Out: D1 = 0 if false, 1 if true", 1);

}
