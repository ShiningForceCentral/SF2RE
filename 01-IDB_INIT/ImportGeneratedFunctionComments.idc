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
        "VDP Reg Status -> D0", 1);

    // ApplyVIntCramDma
    SetFunctionCmt(0xc80, 
        "VDP CRAM", 1);

    // SetBasePalette1
    SetFunctionCmt(0xcc4, 
        "Unused palette copy", 1);

    // ClearCram
    SetFunctionCmt(0xe7c, 
        "unused DMA", 1);

    // Sleep
    SetFunctionCmt(0xf04, 
        "Wait for D0 VInts/Frames", 1);

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
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // ApplyVIntVramDma
    SetFunctionCmt(0x119e, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

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
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

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
        "D0=Destination, D1=Length, D2=Filler value", 1);

    // UpdatePlayerInputs
    SetFunctionCmt(0x150e, 
        "converts data ports 1/2 information into P1/2 inputs State A/B", 1);

    // sub_15A4
    SetFunctionCmt(0x15a4, 
        "unused", 1);

    // GenerateRandomNumber
    SetFunctionCmt(0x1600, 
        "In: D6 = Value range, Out: D7 = Random value", 1);

    // GetRandomOrDebugValue
    SetFunctionCmt(0x1674, 
        "Get random value in range D0 -> D0\n\
\n\
Debug mode allows values 0-3 depending on player direction", 1);

    // PlayMusicAfterCurrentOne
    SetFunctionCmt(0x16be, 
        "d0 : music index, or previous music if value $FB", 1);

    // CopyBytes
    SetFunctionCmt(0x16d6, 
        "A0=Source, A1=Destination, D7=Length", 1);

    // InitSprites
    SetFunctionCmt(0x1770, 
        "D0 = Number of sprites to initialize", 1);

    // sub_179C
    SetFunctionCmt(0x179c, 
        "related to spell animations", 1);

    // sub_1942
    SetFunctionCmt(0x1942, 
        "something with clearing/resetting sprite info when transitioning to battle scene?", 1);

    // sub_19C8
    SetFunctionCmt(0x19c8, 
        "Palette copies to figure out", 1);

    // sub_19F8
    SetFunctionCmt(0x19f8, 
        "related to palette updating, maybe unused", 1);

    // LoadSpriteData
    SetFunctionCmt(0x1a84, 
        "Basic tile decompression : A0=Source, A1=Destination", 1);

    // LoadCompressedData
    SetFunctionCmt(0x1e48, 
        "Stack decompression : A0=Source, A1=Destination", 1);

    // LoadMapLayoutData
    SetFunctionCmt(0x20e6, 
        "A0=Source, A1=Destination", 1);

    // ReadMapLayoutBarrelForBlockFlags
    SetFunctionCmt(0x2296, 
        "Reads next part of barrel to determine flags for next block\n\
barrel = 00\n\
\n\
In: D0 = barrel\n\
Out: D1 = block flag word", 1);

    // LoadMapBlocks
    SetFunctionCmt(0x2372, 
        "decompress map blocks ?\n\
a0 : input ROM block data\n\
a1 : output RAM data", 1);

    // LoadMapTilesets
    SetFunctionCmt(0x29e2, 
        "In: D1 = map index", 1);

    // LoadMap
    SetFunctionCmt(0x2a8c, 
        "loads all map properties (map coords, entities, etc.)", 1);

    // OpenDoor
    SetFunctionCmt(0x3e40, 
        "uses door open SFX", 1);

    // ToggleRoofOnMapLoad
    SetFunctionCmt(0x3f2c, 
        "display (or don't) map roof depending on player's start location", 1);

    // GetChestItem
    SetFunctionCmt(0x4232, 
        "IN : \n\
- d0d1 : candidate coordinates\n\
OUT :\n\
- d0 : layout block offset\n\
- d1 : item flag\n\
- d2 : item index\n\
- a2 : map layout offset", 1);

    // UpdateVdpPlaneA
    SetFunctionCmt(0x4344, 
        "Updates plane A", 1);

    // UpdateVdpPlaneB
    SetFunctionCmt(0x43a4, 
        "Updates plane B", 1);

    // IsMapScrollingToViewTarget
    SetFunctionCmt(0x4728, 
        "Out: Z = is scrolling", 1);

    // CreateWindow
    SetFunctionCmt(0x4802, 
        "d0 = width height, d1 = X Y pos\n\
returns a1 = window tiles end, d0 = window slot", 1);

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

    // esc02_
    SetFunctionCmt(0x4ff8, 
        "update next entity", 1);

    // esc04_moveToRelativeDest
    SetFunctionCmt(0x53fe, 
        "related to moving an entity", 1);

    // CheckIfSameDestForOtherEntity
    SetFunctionCmt(0x5610, 
        "check if another entity has the same destination as current entity\n\
Z=1 if that's the case", 1);

    // esc07_
    SetFunctionCmt(0x5668, 
        "related to controlling raft", 1);

    // esc08_
    SetFunctionCmt(0x57ea, 
        "related to controlling caravan", 1);

    // esc09_
    SetFunctionCmt(0x596c, 
        "related to facing", 1);

    // esc0E_
    SetFunctionCmt(0x59cc, 
        "same facing as other entity ?", 1);

    // esc0A_updateEntitySprite
    SetFunctionCmt(0x5a18, 
        "force entity sprite update ?", 1);

    // esc0B_setSpriteSize
    SetFunctionCmt(0x5a30, 
        "update FFAF44", 1);

    // esc0C_setPosition
    SetFunctionCmt(0x5a3c, 
        "set new pos/dest, clear offset", 1);

    // esc0D_clonePosition
    SetFunctionCmt(0x5a64, 
        "set same X pos, dest, offset and facing as other entity", 1);

    // esc10_setSpeed
    SetFunctionCmt(0x5ac8, 
        "set entity 1A-1B values with xxxx", 1);

    // esc11_
    SetFunctionCmt(0x5ad4, 
        "set entity 18-19 values with xxxx", 1);

    // esc12_
    SetFunctionCmt(0x5ae0, 
        "set or clear entity value 1C bits 0-1 according to xxxx", 1);

    // esc13_
    SetFunctionCmt(0x5b0e, 
        "set or clear entity value 1C bits 2-3 according to xxxx", 1);

    // esc18_set1Cbit7
    SetFunctionCmt(0x5b88, 
        "set or clear entity value 1C bit 7 according to xxxx", 1);

    // esc19_set1Cbit6
    SetFunctionCmt(0x5ba2, 
        "set or clear entity value 1C bit 6 according to xxxx", 1);

    // esc1A_set1Cbit5
    SetFunctionCmt(0x5bbc, 
        "set or clear entity value 1C bit 5 according to xxxx", 1);

    // esc1F_set1Dbit3
    SetFunctionCmt(0x5c3c, 
        "set entity bit 3 of byte $1D", 1);

    // esc20_setEntityInWater
    SetFunctionCmt(0x5c56, 
        "set entity bit 5 of byte $1D", 1);

    // esc21_set1Cbit4
    SetFunctionCmt(0x5c70, 
        "set entity bit 4 of byte $1C", 1);

    // esc30_branch
    SetFunctionCmt(0x5ca6, 
        "parse from current offset + xxxx", 1);

    // esc41_Pass
    SetFunctionCmt(0x5d48, 
        "directly go to next command 4 bytes forward", 1);

    // esc_clearTimerGoToNextEntity
    SetFunctionCmt(0x5d5a, 
        "clear timer and update next entity", 1);

    // UpdateEntityProperties
    SetFunctionCmt(0x6052, 
        "In D0=Entity index", 1);

    // ChangeEntitySprite
    SetFunctionCmt(0x60a8, 
        "A0=Entity address, D6=Facing", 1);

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

    // HideTextBox
    SetFunctionCmt(0x6a38, 
        "related to text box", 1);

    // CheckSram
    SetFunctionCmt(0x6ea6, 
        "Out: D0, D1 = -1 if slot 1, or slot 2 failed checksum", 1);

    // CopyBytesToSram
    SetFunctionCmt(0x7004, 
        "In: A0 = source address\n\
    A1 = destination address\n\
    D7 = number of bytes to copy", 1);

    // CopyBytesFromSram
    SetFunctionCmt(0x701c, 
        "and calculate checksum", 1);

    // WitchSuspend
    SetFunctionCmt(0x7034, 
        "witch suspend screen", 1);

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

    // j_GetCharacterWord34
    SetFunctionCmt(0x8064, 
        "related to AI control on 0x0004 ?", 1);

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

    // GetUpperMoveType
    SetFunctionCmt(0x846a, 
        "Get combatant D0's upper move type, shifted into lower nibble position -> D1", 1);

    // GetEnemyAISetting36
    SetFunctionCmt(0x84b0, 
        "In: D0 = combatant index\n\
\n\
Out: D1 = high 4 bits\n\
     D2 = low 4 bits", 1);

    // GetEnemyIndex
    SetFunctionCmt(0x84dc, 
        "In: D0 = combatant index\n\
\n\
Out: D1 = enemy index ($FFFF if not an enemy)", 1);

    // GetSomethingClassType
    SetFunctionCmt(0x851a, 
        "In: D0 = combatant index\n\
\n\
Out: D1 = something class type ??", 1);

    // CopyCharacterNameToRam
    SetFunctionCmt(0x855a, 
        "In: A0 = temporary space used when naming characters", 1);

    // SetKills
    SetFunctionCmt(0x86e6, 
        "actually seems to only be used for enemy AI, not kills", 1);

    // SetDefeats
    SetFunctionCmt(0x86fe, 
        "actually seems to only be used for enemy AI, not kills", 1);

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
        "Get pointer to item D1's definition in ROM -> A0", 1);

    // GetItemAndNumberOfItems
    SetFunctionCmt(0x8bfa, 
        "In: D0 = combatant index\n\
    D1 = item slot\n\
\n\
Out: D1 = item index\n\
     D2 = number of items held", 1);

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
        "In: D0 = character index\n\
    D1 = item index\n\
\n\
Out: D2 = 0 if item successfully added, 1 if no empty slot available", 1);

    // BreakItem
    SetFunctionCmt(0x8cd4, 
        "In: D0 = character index\n\
    D1 = item slot", 1);

    // EquipItemBySlot
    SetFunctionCmt(0x8d34, 
        "In: D0 = character index\n\
    D1 = item slot index\n\
\n\
Out: D2 = 0 if equipped, 1 if not, 2 if equipped and cursed, 3 if item is nothing", 1);

    // IsItemEquippableAndCursed
    SetFunctionCmt(0x8d6a, 
        "Is item D1 equippable by character D0's class, and is it cursed ?\n\
\n\
Out: D2 = 0 if equippable, 1 if not, 2 if equippable and cursed", 1);

    // UnequipItemBySlotIfNotCursed
    SetFunctionCmt(0x8d9e, 
        "In: D0 = character index\n\
    D1 = item slot index", 1);

    // IsItemInSlotEquippedAndCursed
    SetFunctionCmt(0x8db6, 
        "Is character D0's item in slot D1 equipped, and if so, is it cursed ?\n\
\n\
Out: A0 = pointer to character's item slot in RAM\n\
     D2 = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if nothing", 1);

    // UnequipItemBySlot
    SetFunctionCmt(0x8dfe, 
        "In: D0 = character index\n\
    D1 = item slot index", 1);

    // DropItemBySlot
    SetFunctionCmt(0x8e12, 
        "In: D0 = character index\n\
    D1 = item slot\n\
\n\
Out: D2 = 2 if not dropped, 3 if dropped or nothing", 1);

    // RemoveAndArrangeItems
    SetFunctionCmt(0x8e5c, 
        "In: A0 = char entry address + offset to items\n\
    D0 = item slot", 1);

    // RemoveItemBySlot
    SetFunctionCmt(0x8e76, 
        "In: D0 = character index\n\
    D1 = item slot", 1);

    // IsItemEquippable
    SetFunctionCmt(0x8f60, 
        "In: D1 = item index\n\
    D2 = item type bitmask (for ANDing the item type bitfield)\n\
    D3 = class equip bitmask (for ANDing the item equip bitfield)", 1);

    // GetCurrentATTandDEFwithSpecificItem
    SetFunctionCmt(0x8fee, 
        "In: A0 = character entry address\n\
    D1 = item index\n\
    D2 = item type (weapon or ring)\n\
\n\
Out: D2 = current ATT with item equipped\n\
     D3 = current DEF with item equipped", 1);

    // IsItemUsableInBattle
    SetFunctionCmt(0x90cc, 
        "carry set : YES", 1);

    // IsItemUsableWeaponInBattle
    SetFunctionCmt(0x90e6, 
        "carry set : NO", 1);

    // UnequipAllItemsIfNotCursed
    SetFunctionCmt(0x9106, 
        "In: D0 = character index", 1);

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
Out: D1 = spell index\n\
     D2 = number of spells learned", 1);

    // LearnSpell
    SetFunctionCmt(0x9226, 
        "In: D0 = character index\n\
    D1 = spell index\n\
\n\
Out: D2 = result (0 = learned new spell, 1 = upgraded spell, 2 = no room)", 1);

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
        "Gets distance between two entities (simple X and Y calculation, no obstructions)\n\
In: D0 = from entity\n\
    D1 = to entity\n\
Out: D2 = distance", 1);

    // InitCharacterStats
    SetFunctionCmt(0x95c6, 
        "In: D0 = ally index\n\
    D1 = starting level", 1);

    // CalculateStatGain
    SetFunctionCmt(0x96ba, 
        "In: D1 = current stat value\n\
    D2 = growth curve index\n\
    D3 = starting value\n\
    D4 = projected value\n\
    D5 = current level\n\
\n\
Out: D1 = stat gain value", 1);

    // InitCharacterCombatantEntry
    SetFunctionCmt(0x975e, 
        "In: D0 = ally index", 1);

    // SetCharacterClassData
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
        "determine who is in the force or not based on flags and update RAM lists", 1);

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
        "In: D1 = item index (only the actual index is used, the status bits are cut out)", 1);

    // WriteBattlesceneScript
    SetFunctionCmt(0x9b92, 
        "In: D0 = actor index", 1);

    // DetermineTargetsByAction
    SetFunctionCmt(0x9dd6, 
        "In: A3 = action data", 1);

    // InitBattlesceneDisplayedCombatants
    SetFunctionCmt(0x9e60, 
        "In: A2 = battle scene stack\n\
    A3 = pointer to action type in RAM\n\
    A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // InitBattlesceneProperties
    SetFunctionCmt(0x9f28, 
        "In: A2 = battle scene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of attacker index\n\
    A5 = address in RAM of target index", 1);

    // CreateBattlesceneMessage
    SetFunctionCmt(0xa05c, 
        "Load proper battlescene message script depending on action\n\
\n\
In: A3 = action type index in RAM\n\
    A4 = actor index in RAM\n\
\n\
<HARDCODED> enemy and message indexes", 1);

    // CreateBattlesceneAnimation
    SetFunctionCmt(0xa200, 
        "Load proper battle scene sprite/magic animation properties\n\
\n\
      In: A3 = pointer to action data in RAM\n\
          A4 = battle scene attacker index in RAM", 1);

    // WriteBattlesceneScript_DoAction
    SetFunctionCmt(0xa3f4, 
        "In: A2 = battlescene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of actor index\n\
    A5 = address in RAM of target index", 1);

    // GetSpellAnimation
    SetFunctionCmt(0xa54e, 
        "In: A2 = cutscene stack\n\
    A3 = battle action in RAM\n\
    A4 = battle scene attacker index in RAM\n\
\n\
Out: D4 = spell animation index\n\
\n\
<HARDCODED> class, enemy and weapon indexes", 1);

    // WriteBattlesceneScript_AnimateAction
    SetFunctionCmt(0xa6e8, 
        "Load proper battlescene sprite and spell animations properties\n\
\n\
    In: D4 = spell/item/projectile animation index, set $80 to come from enemy\n\
        D5 = animation type index (0 = attack, 1 = dodge, 2 = spell/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)", 1);

    // GetAmountOfEXPforEncounter
    SetFunctionCmt(0xa968, 
        "Get amount of EXP gained from encounter based on attacker level and target level\n\
\n\
In: A4 = address of attacker byte in RAM\n\
    A5 = address of target byte in RAM\n\
\n\
Out: D5 = amount of EXP", 1);

    // WriteBattlesceneScript_DodgeAttack
    SetFunctionCmt(0xaafc, 
        "In: A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // CalculateDamage
    SetFunctionCmt(0xabbe, 
        "In: A4 = attacker index in RAM\n\
    A5 = defender index in RAM\n\
\n\
Out: D6 = damage", 1);

    // CalculateCriticalHit
    SetFunctionCmt(0xac4e, 
        "In: D6 = damage", 1);

    // WriteBattlesceneScript_InflictDamage
    SetFunctionCmt(0xacea, 
        "In: A4 = pointer to actor index in RAM\n\
    A5 = pointer to target index in RAM\n\
    D6 = damage", 1);

    // WriteBattlesceneScript_InflictCurseDamage
    SetFunctionCmt(0xaf70, 
        "In: D6 = damage", 1);

    // DetermineDoubleAndCounter
    SetFunctionCmt(0xb00e, 
        "In: A4 = pointer to attacker index in RAM\n\
    A5 = pointer to target index in RAM", 1);

    // WriteBattlesceneScript_CastSpell
    SetFunctionCmt(0xb0a8, 
        "In: A2 = battlescene stack\n\
    A3 = scene action type in RAM\n\
    A4 = actor index in RAM\n\
    A5 = target index in RAM", 1);

    // CalculateDamage_Spell
    SetFunctionCmt(0xbb02, 
        "In: D2 = resistance setting (0=none, 1=minor, 2=major, 3=weakness)\n\
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
        "In: A2 = battlescene stack\n\
    D0 = whether item is already damaged (0=no, 1=yes)\n\
\n\
Out: D3 = message index", 1);

    // WriteBattlesceneScript_EnemyDropItem
    SetFunctionCmt(0xbd24, 
        "In: A2 = battlescene stack\n\
    A3 = scene action type in RAM\n\
    A4 = actor index in RAM\n\
    A5 = target index in RAM", 1);

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

    // GetLandEffectSetting
    SetFunctionCmt(0xc1da, 
        "In: D0 = combatant index\n\
\n\
Out: D1 = land effect setting (0=0%, 1=15%, 2=30%)", 1);

    // SetMovableAtCoord
    SetFunctionCmt(0xc204, 
        "Set coord to movable in movable grid\n\
\n\
      In: D1 = X coord\n\
          D2 = Y coord", 1);

    // GetResistanceToSpell
    SetFunctionCmt(0xc22a, 
        "Get combatant D0's resistance setting to spell D1 -> D2", 1);

    // GetMoveInfo
    SetFunctionCmt(0xc2c8, 
        "entity D0's current MOV*2, X, Y -> D0, D3, D4", 1);

    // GetWeaponRange
    SetFunctionCmt(0xc306, 
        "get index and max/min range of current character's current weapon (D1,D3,D4)", 1);

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

    // GetClosestAttackPosition
    SetFunctionCmt(0xc71a, 
        "something with terrain lists and checking, look into it ???\n\
In: D1 = x pos\n\
    D2 = y pos\n\
    D3 = max range\n\
    D4 = min range\n\
Out: D1 = chosen x pos\n\
     D2 = chosen y pos", 1);

    // MakeTargetListAllies
    SetFunctionCmt(0xc7fa, 
        "Clear target grid, then add allies", 1);

    // EvaluateDamage
    SetFunctionCmt(0xcc0c, 
        "Calculate max potential damage value, adjusted for land effect\n\
\n\
      Out: D6 = potential damage", 1);

    // GetSpellPowerAdjustedForResistance
    SetFunctionCmt(0xcc54, 
        "In: D0 = target combatant index\n\
    D1 = spell index\n\
\n\
Out: D6 = adjusted power", 1);

    // EvaluateTargetRemainingHP
    SetFunctionCmt(0xcc8a, 
        "In: D6 = potential damage\n\
\n\
Out: D1 = target's remaining HP", 1);

    // sub_CD68
    SetFunctionCmt(0xcd68, 
        "In: D0 = heal target character index\n\
    D4 = heal spell index", 1);

    // GetHighestUsableSpellLevel
    SetFunctionCmt(0xced2, 
        "Get highest usable level of spell D1, considering current MP and highest known level\n\
\n\
      In: D0 = combatant index\n\
          D1 = spell index\n\
\n\
      Out: D1 = spell index", 1);

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

    // GetNextHealingSpell
    SetFunctionCmt(0xd018, 
        "Get next healing spell known by combatant\n\
\n\
      In: D0 = entity index\n\
          D3 = starting spell slot\n\
\n\
      Out: D1 = spell index\n\
           D2 = spell slot", 1);

    // GetNextUsableAttackItem
    SetFunctionCmt(0xd0ac, 
        "Get the next item in combatant's inventory that can be used to cast BLAZE/FREEZE/BOLT/BLAST\n\
<HARDCODED>\n\
\n\
      In: D0 = combatant index\n\
          D3 = starting item slot\n\
\n\
      Out: D1 = item index\n\
           D2 = item slot", 1);

    // GetNextUsableHealingItem
    SetFunctionCmt(0xd160, 
        "Get the next item in combatant's inventory that can be used to cast a healing spell\n\
<HARDCODED>\n\
\n\
      In: D0 = combatant index\n\
          D3 = starting item slot\n\
\n\
      Out: D1 = item index\n\
           D2 = item slot", 1);

    // IsCombatantAtLessThanHalfHP
    SetFunctionCmt(0xd296, 
        "In: D0 = combatant index\n\
\n\
Out: carry clear if true", 1);

    // GetDifficulty
    SetFunctionCmt(0xd408, 
        "Out: D1 = 0 if normal, 1 if hard, 2 if super, 3 if ouch", 1);

    // AddAllToStack
    SetFunctionCmt(0xdd60, 
        "unused, pointless", 1);

    // MakeEnemyMoveOrder
    SetFunctionCmt(0xdd78, 
        "create enemy move order from movecost lists", 1);

    // sub_DEFC
    SetFunctionCmt(0xdefc, 
        "related to AI controlled unit (enemy, auto-control cheat, MUDDLEd force member)\n\
\n\
    In: D0 = character index", 1);

    // sub_EBA4
    SetFunctionCmt(0xeba4, 
        "In: D0 = character index", 1);

    // j_EndKiss
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
        "related to menus\n\
\n\
In: A0 = special subroutine address to handle menu, default handling if not supplied (unused functionality)\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // LoadDiamenuWindowVdpTileData
    SetFunctionCmt(0x103b8, 
        "In: -$C(A6) = window slot index", 1);

    // sub_10586
    SetFunctionCmt(0x10586, 
        "In: D0 = current diamenu choice\n\
    D1 = \n\
    D2 = \n\
    A0 = ", 1);

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

    // sub_10A4A
    SetFunctionCmt(0x10a4a, 
        "In: D1 = \n\
    D2 = \n\
    A0 = ", 1);

    // sub_10CB0
    SetFunctionCmt(0x10cb0, 
        "related to menu choice", 1);

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

    // BuildFighterMiniStatusWindow
    SetFunctionCmt(0x118be, 
        "In: A1 = window tiles address\n\
    D0 = combatant index", 1);

    // WriteStatValue
    SetFunctionCmt(0x11aae, 
        "Write stat value D0 or '??' if above 99", 1);

    // CopyFighterMinistatusWindowTileColumn
    SetFunctionCmt(0x11ac6, 
        "draw tiles from A0 into A1 (one column)", 1);

    // BuildMemberStatsScreen
    SetFunctionCmt(0x11c2a, 
        "Create and display member stats screen\n\
\n\
      In: D0 = character index", 1);

    // AddStatusEffectTileIndexesToVdpTileOrder
    SetFunctionCmt(0x11eea, 
        "In: A1 = address of VDP tile order in RAM", 1);

    // BuildMemberStatsWindow
    SetFunctionCmt(0x11ff0, 
        "In: D0 = character index\n\
    A1 = window tile adress", 1);

    // GetCombatantPortrait
    SetFunctionCmt(0x1263a, 
        "Get portrait index for combatant D0 -> D0", 1);

    // LoadCombatantPortrait
    SetFunctionCmt(0x13394, 
        "In: D0 = combatant index", 1);

    // GetSelectedMember
    SetFunctionCmt(0x13462, 
        "    Get index of currently selected force member (in menus).\n\
    Out: D0 = selected index (capped to 255)", 1);

    // sub_14074
    SetFunctionCmt(0x14074, 
        "related to menu choice", 1);

    // sub_1445A
    SetFunctionCmt(0x1445a, 
        "Handle out of battle MAGIC menu", 1);

    // LoadMiniStatusTextHighlightSprites
    SetFunctionCmt(0x146ae, 
        "In: D1 = blinking frame timer", 1);

    // sub_1477E
    SetFunctionCmt(0x1477e, 
        "related to item unequip and cursed items", 1);

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

    // GetAllyPortrait
    SetFunctionCmt(0x15736, 
        "In: D0 = ally or portrait index (depending on caller function)\n\
\n\
Out: D0 = portrait index adjusted for class", 1);

    // sub_1586E
    SetFunctionCmt(0x1586e, 
        "related to battlefield options", 1);

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

    // MakeActorIdle
    SetFunctionCmt(0x195e2, 
        "make actor idle", 1);

    // AddEnemyToDeadList
    SetFunctionCmt(0x197a6, 
        "add enemy to dead combatant list", 1);

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
        "clears plt 1-2 and 1-2bis, sets plt 3bis", 1);

    // LoadPaletteForBattlescene
    SetFunctionCmt(0x199de, 
        "load palette D1 of battle sprite D0", 1);

    // LoadAllyBattleSpriteFrame
    SetFunctionCmt(0x19a0c, 
        "In: D0 = battle sprite index\n\
    D1 = frame index", 1);

    // VInt_LoadAllyBattleSpriteFrame
    SetFunctionCmt(0x19a2a, 
        "In: D0 = battle sprite index\n\
    D1 = frame index", 1);

    // LoadWeaponSprite
    SetFunctionCmt(0x19a5c, 
        "In: D0 = weapon sprite index", 1);

    // LoadEnemyBattleSprite
    SetFunctionCmt(0x19b44, 
        "d0 : battle sprite index", 1);

    // LoadSpellGraphics
    SetFunctionCmt(0x19ca4, 
        "    Loads spell animation tiles.\n\
    In: D0 = spell animation tileset index", 1);

    // sub_19CE8
    SetFunctionCmt(0x19ce8, 
        "loads spell graphics", 1);

    // GetBattleSpriteAndPalette
    SetFunctionCmt(0x19d3e, 
        "Get battle sprite and palette indexes for combatant D0 -> D1 (sprite), D2 (palette)", 1);

    // GetWeaponSpriteAndPalette
    SetFunctionCmt(0x19db0, 
        "Get battle sprite and palette indexes for combatant D0's equipped weapon -> D2 (sprite), D3 (palette)", 1);

    // sub_19E96
    SetFunctionCmt(0x19e96, 
        "Get a boolean depending on background index", 1);

    // ExecuteSpellAnimation
    SetFunctionCmt(0x19ee6, 
        "spell animation subroutine", 1);

    // ExecSpellAnimationFlash
    SetFunctionCmt(0x1a2a6, 
        "    In: D0 = color to flash", 1);

    // ClearSpellAnimationProperties
    SetFunctionCmt(0x1a2d4, 
        "    Clears a portion at RAM:b406 and RAM:b532 for spell properties.", 1);

    // LoadInvocationSpell
    SetFunctionCmt(0x1a32c, 
        "code for invocations", 1);

    // sa1F_OddeyeBeam
    SetFunctionCmt(0x1b716, 
        "and maybe Zynk's beam too ?", 1);

    // sub_1B93C
    SetFunctionCmt(0x1b93c, 
        "desoul ?", 1);

    // VInt_UpdateBattlesceneGraphics
    SetFunctionCmt(0x1ee2c, 
        "and other stuff ?", 1);

    // DetermineDealsItemsNotInCurrentShop
    SetFunctionCmt(0x207fe, 
        "Create list of deals items not normally sold in current shop", 1);

    // DoesCurrentShopContainItem
    SetFunctionCmt(0x20834, 
        "In: D1 = item index\n\
\n\
Out: Zero-bit clear = yes, set = no", 1);

    // GetCurrentShopDefAddress
    SetFunctionCmt(0x20852, 
        "Get current shop definition address -> A0", 1);

    // FindPromotionSection
    SetFunctionCmt(0x2110c, 
        "In: D2 = section type (regpre, regpost, specpre, specpost, specitem)\n\
Out: A0 = address", 1);

    // ReplaceSpellsWithSORCdefaults
    SetFunctionCmt(0x2112c, 
        "In: A6 = church actions stack", 1);

    // sub_219EC
    SetFunctionCmt(0x219ec, 
        "copy available targets list ?", 1);

    // DisplaySpecialCaravanDescription
    SetFunctionCmt(0x22864, 
        "only used for chirrup sandals", 1);

    // CopyCaravanItems
    SetFunctionCmt(0x22926, 
        "Copy caravan item indexes to generic list space", 1);

    // sub_2294C
    SetFunctionCmt(0x2294c, 
        "get whether character D0's item at slot D1 is cursed -> carry", 1);

    // FindUsableOutsideBattleItem
    SetFunctionCmt(0x229ca, 
        "Out: D2 = 0 if true, $FFFFFFFF if false", 1);

    // UseFieldItem
    SetFunctionCmt(0x229ec, 
        "Find specific item index + code offset to run when used in field", 1);

    // sub_22C60
    SetFunctionCmt(0x22c60, 
        "get first entity's X, Y and facing", 1);

    // CreateMoveableRangeForUnit
    SetFunctionCmt(0x22c84, 
        "    Update some map stuff ???", 1);

    // ControlBattleUnit
    SetFunctionCmt(0x22e1a, 
        "Out: D2 = chosen X\n\
     D3 = chosen Y\n\
     D4 = copied P1 input state bitfield", 1);

    // GetEntityIndexForCombatant
    SetFunctionCmt(0x22f30, 
        "Get entity index for combatant D0 -> D0", 1);

    // GetEntityEventIndex
    SetFunctionCmt(0x22f4a, 
        "In: D0 = entity index\n\
Out: D0 = entity event index", 1);

    // SetUnitCursorDestinationToNextCombatant
    SetFunctionCmt(0x232ac, 
        "In: D0 = entity index\n\
Out: D2 = entity X\n\
     D3 = entity Y", 1);

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

    // sub_23D98
    SetFunctionCmt(0x23d98, 
        "battlefield spell/item use", 1);

    // GetEgressPositionForBattle
    SetFunctionCmt(0x23e50, 
        "HARDCODED battle->map relationship ?", 1);

    // sub_23EB0
    SetFunctionCmt(0x23eb0, 
        "In: D0 = combatant index", 1);

    // HandleAfterTurnEffects
    SetFunctionCmt(0x24242, 
        "Handle after-turn effects (status effects, HP/MP regen/degen, etc)", 1);

    // UpdateTargetListForCombatant
    SetFunctionCmt(0x24642, 
        "In: D0 = combatant index", 1);

    // sub_24966
    SetFunctionCmt(0x24966, 
        "    createSpellRangeGridMaster???", 1);

    // sub_252FA
    SetFunctionCmt(0x252fa, 
        "related to AI controlled unit (enemy, auto-control cheat, MUDDLEd force member)", 1);

    // UpdateAllEnemiesAI
    SetFunctionCmt(0x2550c, 
        "<BUG> A Goddess Staff is added to the deals section in shops whenever a DEF-CON switch \n\
      is activated, and if one of the following items is also present :\n\
      - Quick Ring\n\
      - Protect Ring\n\
      - White Ring\n\
      - Running Ring\n\
\n\
End function with a RTS intruction to fix", 1);

    // AddRandomizedAGItoTurnOrder
    SetFunctionCmt(0x255a4, 
        "In: A0 = turn order in RAM\n\
    D0 = combatant index", 1);

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
        "if flag D1 is set, display def-con textbox", 1);

    // sub_258A8
    SetFunctionCmt(0x258a8, 
        "update main entity properties", 1);

    // WaitForEvent
    SetFunctionCmt(0x2591c, 
        "Wait for event OR player action (A/C button)", 1);

    // ProcessPlayerAction
    SetFunctionCmt(0x25ad6, 
        "Manage debug actions, entity events, item finds, area descriptions, caravan or main menu", 1);

    // DisplaySegaLogo
    SetFunctionCmt(0x2804c, 
        "Out: D0 = $FFFFFFFF if pressing start, 0 if not", 1);

    // CalculateRomChecksum
    SetFunctionCmt(0x28f62, 
        "Checksum", 1);

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

    // DeclareNewEntity
    SetFunctionCmt(0x445ca, 
        "declare new entity ?", 1);

    // ClearEntities
    SetFunctionCmt(0x4465a, 
        "clear entities in memory", 1);

    // GetAllyMapSprite
    SetFunctionCmt(0x449c6, 
        "In: D0 = combatant index\n\
\n\
Out: D4 = map sprite index", 1);

    // GetCombatantMapSprite
    SetFunctionCmt(0x44a7c, 
        "In: A6 = battle vars stack ???\n\
\n\
Out: D4 = map sprite index", 1);

    // WaitForEntityToStopMoving
    SetFunctionCmt(0x44da4, 
        "In: D0 = entity index", 1);

    // GetEntityEntryAddress
    SetFunctionCmt(0x44dd8, 
        "Get RAM address of entity D0 -> A0", 1);

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

    // GetEntityPortaitAndSpeechSound
    SetFunctionCmt(0x45638, 
        "In: D0 = character index\n\
\n\
Out: D1 = portrait index\n\
     D2 = speech sound index", 1);

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

    // csc1B_startEntityAnim
    SetFunctionCmt(0x46a6c, 
        "if character dead, then get new character index from next word ? This doesn't make sense.", 1);

    // csc1C_stopEntityAnim
    SetFunctionCmt(0x46a82, 
        "if character xxxx dead, then do it to entity yyyy ?!", 1);

    // csc20_updateDefeatedAllies
    SetFunctionCmt(0x46af0, 
        "if X Pos == -1, then dead", 1);

    // csc22_animateEntityFadeInOrOut
    SetFunctionCmt(0x46b42, 
        "0/1 = scan down/up, 2/3 = wipe out/in, 4/5 = slide out/in, 6/7 = mosaic out/in", 1);

    // csc23_setEntityFacing
    SetFunctionCmt(0x46c20, 
        "set entity yyyy facing zzzz according to character's xxxx alive status ?!", 1);

    // csc24_setCameraTargetEntity
    SetFunctionCmt(0x46c38, 
        "set playable entity 00xx or something like that", 1);

    // csc25_cloneEntity
    SetFunctionCmt(0x46c5a, 
        "wtf, copy entity number of entity 00xx into entity number of entity 00yy ?!", 1);

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
        "Launches DMA", 1);

    // ExecuteMapScript
    SetFunctionCmt(0x4712c, 
        "In: A0 = script address", 1);

    // csc04_setTextIndex
    SetFunctionCmt(0x47372, 
        "set cutscene dialogue index", 1);

    // csc05_playSound
    SetFunctionCmt(0x47378, 
        "play sound of index 00xx", 1);

    // csc08_joinForce
    SetFunctionCmt(0x47398, 
        "make 00xx character join force with bit F set for sad join music", 1);

    // csc09_hideTextBoxAndPortrait
    SetFunctionCmt(0x473fe, 
        "related to portrait window", 1);

    // csc0C_jumpIfFlagSet
    SetFunctionCmt(0x47418, 
        "xxxx yyyyyyyy", 1);

    // csc0D_jumpIfFlagClear
    SetFunctionCmt(0x4742c, 
        "xxxx yyyyyyyy", 1);

    // csc0E_jumpIfForceMemberInList
    SetFunctionCmt(0x47440, 
        "branch if something", 1);

    // csc0F_jumpIfCharacterAlive
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

    // j_ExecuteBattleCutscene_Intro_0
    SetFunctionCmt(0x47a50, 
        "cutscene before the battle begins", 1);

    // ExecuteBattleCutscene_Start
    SetFunctionCmt(0x47aee, 
        "cutscene at the start of battle (after units are placed and battle officially begins)\n\
\n\
only seems to happen in first \"above Pacalon\" battle", 1);

    // ApplyPositionsAfterEnemyLeaderDies
    SetFunctionCmt(0x47d9e, 
        "After-battlescene listener used to prepare entity positions for end cutscene before the enemy leader dies. Only used in battle 5.", 1);

    // ExecuteBattleRegionCutscene
    SetFunctionCmt(0x47e82, 
        "executes cutscenes activated by regions", 1);

    // csub_4CD56
    SetFunctionCmt(0x4cd56, 
        "Jaro joins the Force", 1);

    // Map8_DescFunc6
    SetFunctionCmt(0x562ba, 
        "set after you open the tree in Ribble with the wooden plank", 1);

    // sub_5FD7C
    SetFunctionCmt(0x5fd7c, 
        "unused", 1);

    // sub_5FD92
    SetFunctionCmt(0x5fd92, 
        "unused", 1);

    // sub_6051E
    SetFunctionCmt(0x6051e, 
        "unused descriptions which look similar to the default ones for map 5", 1);

    // WaitForPlayer1InputStart
    SetFunctionCmt(0x100204, 
        "wait during d0 frames", 1);

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

    // sub_1AC05C
    SetFunctionCmt(0x1ac05c, 
        "AI-related", 1);

    // LoadEndCreditsFont
    SetFunctionCmt(0x1ac29c, 
        "Load base tiles and ...  generate font from basetile font !\n\
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

    // sub_1AC8A0
    SetFunctionCmt(0x1ac8a0, 
        "AI-related", 1);

    // sub_1AC9FC
    SetFunctionCmt(0x1ac9fc, 
        "AI-related", 1);

    // sub_1ACA72
    SetFunctionCmt(0x1aca72, 
        "AI-related", 1);

    // sub_1ACAD6
    SetFunctionCmt(0x1acad6, 
        "AI-related", 1);

    // CheckTriggerRegionFlag
    SetFunctionCmt(0x1ace32, 
        "In: D1 = region #", 1);

    // GetListOfSpawningEnemies
    SetFunctionCmt(0x1acf30, 
        "adds respawning enemy #s to target list in RAM", 1);

    // UpdateEnemyActivationIfDead
    SetFunctionCmt(0x1ad002, 
        "In: D0 = character index\n\
    D4 = character index (same as D0)\n\
\n\
Out: D0 = 0000 if activated and dead, $FFFF if not", 1);

    // LoadBattleTerrainData
    SetFunctionCmt(0x1ad0dc, 
        "loads terrain data for current battle", 1);

    // BattleDebugFunction1B120A
    SetFunctionCmt(0x1b120a, 
        "Never called, probably what remains of some debugging code ?", 1);

    // InitEnemyBattlePosition
    SetFunctionCmt(0x1b130c, 
        "(also checks for Jaro)", 1);

    // UpdateEnemyStatsForRespawn
    SetFunctionCmt(0x1b13a0, 
        "In: D0 = character index\n\
    D1 = character word 34 (AI stuff)\n\
\n\
Out: carry = 0 if respawn, 1 if not", 1);

    // InitEnemyStats
    SetFunctionCmt(0x1b140a, 
        "In: A0 = address of current combatant from battle def", 1);

    // InitEnemyItems
    SetFunctionCmt(0x1b1504, 
        "Handle custom item index of enemy list entry starting at A0 -> ???", 1);

    // GetEnemyOriginalPosOccupied
    SetFunctionCmt(0x1b1554, 
        "In: D3 = enemy starting tile x (from battle def)\n\
    D4 = enemy starting tile y (from battle def)\n\
Out: carry = if anyone is on D3/D4", 1);

    // SetEnemyBaseATT
    SetFunctionCmt(0x1b15aa, 
        "Set enemy base ATT according to difficulty", 1);

    // GetEnemyAITargetPosition
    SetFunctionCmt(0x1b15f8, 
        "coords of anchor point used in AI byte D0 -> D1, D2", 1);

    // GetBattleSpriteSetSubsection
    SetFunctionCmt(0x1b1630, 
        "Get address and size of subsection D1 for current battle\n\
\n\
      In: D1 = subsection index\n\
\n\
      Out: A0 = subsection address\n\
           D1 = subsection size", 1);

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
        "In: D1 = original enemy index\n\
\n\
Out: D1 = upgraded enemy index", 1);

    // HasJaroJoinedTheForce
    SetFunctionCmt(0x1b1a28, 
        "Check if Jaro has joined the Force\n\
\n\
      Out: D1 = 0 if false, 1 if true", 1);

}
