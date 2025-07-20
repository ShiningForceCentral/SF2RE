static main()
{
    // InitializeVdpData
    SetFunctionCmt(0x244, 
        "Clear WRAM data tables reserved by the program for VDP control.", 1);

    // Trap0_SoundCommand
    SetFunctionCmt(0x45c, 
        "If interrupt parameter word = -1, then get d0.w", 1);

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
        "unused\n\
\n\
VDP Reg Status -> d0.w", 1);

    // ActivateVIntDmaQueueProcessing
    SetFunctionCmt(0xc4e, 
        "unused", 1);

    // DeactivateVIntDmaQueueProcessing
    SetFunctionCmt(0xc58, 
        "unused", 1);

    // ApplyVIntCramDma
    SetFunctionCmt(0xc80, 
        "VDP CRAM", 1);

    // SetBasePalette1
    SetFunctionCmt(0xcc4, 
        "unused palette copy", 1);

    // ApplyCurrentColorFadingValue
    SetFunctionCmt(0xd1e, 
        "In: d0.w = fading data value, d1.w = palette bitfield", 1);

    // ClearCram
    SetFunctionCmt(0xe7c, 
        "unused", 1);

    // Sleep
    SetFunctionCmt(0xf04, 
        "Wait for d0.w VInts/Frames.", 1);

    // RequestVdpCommandQueueProcessing
    SetFunctionCmt(0xf1a, 
        "unused", 1);

    // WaitForVdpCommandQueueProcessing
    SetFunctionCmt(0xf24, 
        "unused", 1);

    // sub_F3A
    SetFunctionCmt(0xf3a, 
        "unused", 1);

    // sub_F76
    SetFunctionCmt(0xf76, 
        "unused", 1);

    // sub_F90
    SetFunctionCmt(0xf90, 
        "unused", 1);

    // SwapA6
    SetFunctionCmt(0x1004, 
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

    // WaitForPlayer1NewInput
    SetFunctionCmt(0x1586, 
        "unused", 1);

    // sub_15A4
    SetFunctionCmt(0x15a4, 
        "unused", 1);

    // WaitForInputFor1Second
    SetFunctionCmt(0x15d8, 
        "unused", 1);

    // WaitForInputFor3Seconds
    SetFunctionCmt(0x15f4, 
        "unused", 1);

    // GenerateRandomNumber
    SetFunctionCmt(0x1600, 
        "In: d6.w = Value range, Out: d7.w = Random value", 1);

    // WaitForRandomValueToMatch
    SetFunctionCmt(0x1628, 
        "unused", 1);

    // GenerateRandomValueUnsigned
    SetFunctionCmt(0x1652, 
        "unused", 1);

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

    // InitializeSprites
    SetFunctionCmt(0x1770, 
        "In: d0.w = Number of sprites to initialize", 1);

    // sub_179C
    SetFunctionCmt(0x179c, 
        "related to spellanimations", 1);

    // sub_17EC
    SetFunctionCmt(0x17ec, 
        "related to spellanimations", 1);

    // sub_1812
    SetFunctionCmt(0x1812, 
        "related to spellanimations", 1);

    // sub_18EE
    SetFunctionCmt(0x18ee, 
        "unused", 1);

    // sub_1942
    SetFunctionCmt(0x1942, 
        "something with clearing/resetting sprite info when transitioning to battlescene?", 1);

    // sub_196C
    SetFunctionCmt(0x196c, 
        "related to the battlescene", 1);

    // sub_198C
    SetFunctionCmt(0x198c, 
        "related to the battlescene", 1);

    // sub_19B0
    SetFunctionCmt(0x19b0, 
        "clear table related to sprites", 1);

    // LoadBasicCompressedData
    SetFunctionCmt(0x1a84, 
        "Basic tile decompression.  In: a0 = Source, a1 = Destination", 1);

    // LoadStackCompressedData
    SetFunctionCmt(0x1e48, 
        "Stack decompression.  In: a0 = Source, a1 = Destination", 1);

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

    // sub_2EC0
    SetFunctionCmt(0x2ec0, 
        "unused", 1);

    // sub_2F24
    SetFunctionCmt(0x2f24, 
        "unused", 1);

    // sub_30BE
    SetFunctionCmt(0x30be, 
        "unused", 1);

    // sub_36B2
    SetFunctionCmt(0x36b2, 
        "unused", 1);

    // sub_3D96
    SetFunctionCmt(0x3d96, 
        "unused", 1);

    // OpenDoor
    SetFunctionCmt(0x3e40, 
        "uses door open SFX", 1);

    // ToggleRoofOnMapLoad
    SetFunctionCmt(0x3f2c, 
        "Display (or don't) map roof depending on player's start location.", 1);

    // OpenChest
    SetFunctionCmt(0x4156, 
        "In: d0.w, d1.w = Candidate coordinates", 1);

    // CloseChest
    SetFunctionCmt(0x4194, 
        "In: d0.w, d1.w = Candidate coordinates", 1);

    // CheckChestItem
    SetFunctionCmt(0x41c6, 
        "In: d0.w, d1.w = Candidate coordinates", 1);

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
Out: a1 = window layout end address, d0.w = window slot (-1 if no free slot available)", 1);

    // SetWindowDestination
    SetFunctionCmt(0x4866, 
        "In: d0.w = Windows index, d1.w = Value ($8080->X/Y)\n\
Out: a0 = Window properties", 1);

    // sub_48BE
    SetFunctionCmt(0x48be, 
        "unused", 1);

    // MoveWindowWithSfx
    SetFunctionCmt(0x48f4, 
        "In: d0.w = window slot\n\
    d1.w = destination\n\
    d2.b = animation length", 1);

    // MoveWindow
    SetFunctionCmt(0x48f8, 
        "In: d0.w = window slot\n\
    d1.w = destination\n\
    d2.b = animation length", 1);

    // GetWindowEntryAddress
    SetFunctionCmt(0x4c38, 
        "Get entry address for window d0.w -> a0", 1);

    // GetWindowTileAddress
    SetFunctionCmt(0x4c44, 
        "Get pointer to tile at coordinates d1.w in layout for window d0.w -> a1", 1);

    // sub_4E86
    SetFunctionCmt(0x4e86, 
        "unused", 1);

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

    // esc18_setEntityObstructable
    SetFunctionCmt(0x5b88, 
        "set or clear entity value 1C bit 7 according to xxxx", 1);

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
    d2.b = new B flags (keep current if = -1)\n\
    d3.b = new map sprite index (keep current if = -1)", 1);

    // ChangeEntityMapsprite
    SetFunctionCmt(0x60a8, 
        "In: a0 = pointer to entity data\n\
    d6.b = facing direction", 1);

    // ConvertMapPixelCoordinatesToOffset
    SetFunctionCmt(0x61fc, 
        "In: d0.w, d1.w = X, Y pixel coordinates\n\
Out: d2.w = offset from start of map VDP tile layout", 1);

    // DisplayText
    SetFunctionCmt(0x6260, 
        "In: d0.w = string index", 1);

    // GetCurrentDialogueNameIndex
    SetFunctionCmt(0x6648, 
        "Out: d1.w", 1);

    // CopyAsciiBytesForDialogueString
    SetFunctionCmt(0x6654, 
        "Copy ASCII string of length D7 at A0 to RAM for dialogue textbox", 1);

    // LoadOneDialogueWindowLayoutLine
    SetFunctionCmt(0x6860, 
        "In: a1 = destination\n\
    d0.w = VDP tile index for left border of line\n\
    d1.w = VDP tile index for first inner box tile of line\n\
    d2.w = VDP tile index for right border of line\n\
    d3.w = amount to add to D1 each time a tile is copied (0 for top and bottom border lines, 1 for inner box)", 1);

    // CheckSram
    SetFunctionCmt(0x6ea6, 
        "Out: d0.w, d1.w = -1 if slot 1 or slot 2 failed checksum, respectively.", 1);

    // CopyBytesToSram
    SetFunctionCmt(0x7004, 
        "In: a0 = source address, a1 = destination address, d7.w = number of bytes to copy\n\
Out: d0.b = checksum", 1);

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
    D7 = battle index (-1 for none)\n\
...more", 1);

    // GetSavepointForMap
    SetFunctionCmt(0x75ec, 
        "In: d0.b = From map index\n\
Out: d0.b = To map index, d1.b = X, d2.b = Y, d3.b = Facing", 1);

    // SwitchMap
    SetFunctionCmt(0x7956, 
        "Alter map index if certain flags are set (Granseal, Pacalon, etc.)\n\
\n\
In: d0.w = original map index, Out: d0.w = new map index", 1);

    // CheckBattle
    SetFunctionCmt(0x799c, 
        "In: D0 = map index (if not supplied, will be pulled from CURRENT_MAP)\n\
    D1 = player X coord to check\n\
    D2 = player Y coord to check\n\
Out: D7 = battle index to trigger (-1 if none)\n\
...more", 1);

    // UpdateWitchLayoutZone
    SetFunctionCmt(0x7d28, 
        "In: d1.w = Width/Height", 1);

    // j_SoundTest
    SetFunctionCmt(0x7fa4, 
        "Function is missing in US version.", 1);

    // j_GetCurrentProwess
    SetFunctionCmt(0x8020, 
        "unused", 1);

    // j_GetBaseProwess
    SetFunctionCmt(0x8024, 
        "unused", 1);

    // j_GetBaseResistance
    SetFunctionCmt(0x8030, 
        "unused", 1);

    // j_GetCurrentResistance
    SetFunctionCmt(0x8054, 
        "unused", 1);

    // j_GetCombatantType
    SetFunctionCmt(0x8070, 
        "; unused", 1);

    // j_SetMaxMp
    SetFunctionCmt(0x8084, 
        "unused", 1);

    // j_SetBaseMov
    SetFunctionCmt(0x80a0, 
        "unused", 1);

    // j_SetBaseResistance
    SetFunctionCmt(0x80a8, 
        "unused", 1);

    // j_SetCurrentMov
    SetFunctionCmt(0x80b4, 
        "unused", 1);

    // j_SetCurrentResistance
    SetFunctionCmt(0x80d0, 
        "unused", 1);

    // j_IncreaseLevel
    SetFunctionCmt(0x810c, 
        "unused", 1);

    // j_DecreaseBaseMov
    SetFunctionCmt(0x812c, 
        "unused", 1);

    // j_DecreaseBaseDef
    SetFunctionCmt(0x8130, 
        "unused", 1);

    // j_DecreaseBaseAgi
    SetFunctionCmt(0x8134, 
        "unused", 1);

    // j_DecreaseCurrentMov
    SetFunctionCmt(0x8138, 
        "unused", 1);

    // j_DecreaseCurrentDef
    SetFunctionCmt(0x8144, 
        "unused", 1);

    // j_DecreaseCurrentAtt
    SetFunctionCmt(0x8148, 
        "unused", 1);

    // j_DecreaseCurrentAgi
    SetFunctionCmt(0x814c, 
        "unused", 1);

    // j_ApplyItemOnStats
    SetFunctionCmt(0x8168, 
        "unused", 1);

    // j_BreakItemBySlot
    SetFunctionCmt(0x8184, 
        "unused", 1);

    // j_GetItemSlotContainingIndex
    SetFunctionCmt(0x81d4, 
        "unused", 1);

    // j_GetDistanceBetweenCombatants
    SetFunctionCmt(0x81f0, 
        "unused", 1);

    // j_nullsub_9482
    SetFunctionCmt(0x81f4, 
        "unused", 1);

    // j_PopulateTargetableGrid_UseItem
    SetFunctionCmt(0x8220, 
        "unused", 1);

    // j_sub_C5FA
    SetFunctionCmt(0x8224, 
        "unused", 1);

    // j_PopulateTargetableGrid_CastSpell
    SetFunctionCmt(0x8228, 
        "unused", 1);

    // j_PopulateTargetableGrid
    SetFunctionCmt(0x822c, 
        "unused", 1);

    // j_PopulateTargetsArrayWithOpponents
    SetFunctionCmt(0x8230, 
        "unused", 1);

    // j_PopulateTargetsArrayWithAllies
    SetFunctionCmt(0x8234, 
        "unused", 1);

    // j_PopulateTargetsArrayWithEnemies
    SetFunctionCmt(0x8238, 
        "unused", 1);

    // j_PopulateTargetsArrayWithAllCombatants
    SetFunctionCmt(0x823c, 
        "unused", 1);

    // j_ClearTargetsArray
    SetFunctionCmt(0x8250, 
        "unused", 1);

    // j_LeaveForce
    SetFunctionCmt(0x8278, 
        "unused", 1);

    // j_AddAllToStack
    SetFunctionCmt(0x829c, 
        "unused", 1);

    // GetCombatantName
    SetFunctionCmt(0x82d0, 
        "In: d0.b = combatant index\n\
\n\
Out: a0 = address of name\n\
     d7.w = length of name", 1);

    // GetClass
    SetFunctionCmt(0x8306, 
        "Get class index for combatant d0.b -> d1.w", 1);

    // GetLevel
    SetFunctionCmt(0x8316, 
        "Get current level for combatant d0.b -> d1.w", 1);

    // GetMoveType
    SetFunctionCmt(0x846a, 
        "Get movetype for combatant d0.w, shifted to the lower nibble position -> d1.w", 1);

    // GetAiCommandset
    SetFunctionCmt(0x8480, 
        "Get AI commandset for combatant d0.w -> d1.w", 1);

    // GetAiSpecialMoveOrders
    SetFunctionCmt(0x8494, 
        "Out: d1.w = combatant index to follow, or first AI point if bit 6 is set\n\
     d2.w = second AI point", 1);

    // GetAiRegion
    SetFunctionCmt(0x84b0, 
        "In: d0.w = combatant index\n\
Out: d1.w, d2.w = AI activation regions 1 and 2 indexes", 1);

    // GetEnemy
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
        "Load ally name into combatant data block.\n\
\n\
In: a0 = pointer to temporarily loaded name in RAM", 1);

    // SetMoveTypeAndAiCommandset
    SetFunctionCmt(0x86d6, 
        "Set combined movetype and ai commandset when initializing an enemy.", 1);

    // DecreaseBaseDef
    SetFunctionCmt(0x88ec, 
        "unused", 1);

    // DecreaseBaseAgi
    SetFunctionCmt(0x8918, 
        "unused", 1);

    // DecreaseBaseMov
    SetFunctionCmt(0x8944, 
        "unused", 1);

    // FindName
    SetFunctionCmt(0x8976, 
        "In: a0 = names list pointer, d1.w = name index\n\
Out: a0 = pointer to name entry, d7.w = name length", 1);

    // UpdateCombatantStats
    SetFunctionCmt(0x89ce, 
        "Update all current stats", 1);

    // ApplyStatusEffectsOnStats
    SetFunctionCmt(0x8a26, 
        "In: d0.w = combatant index\n\
    d3.w = status effects bitfield", 1);

    // ApplyItemOnStats
    SetFunctionCmt(0x8a90, 
        "In: a2 = prowess entry pointer\n\
    d0.w = combatant index\n\
    d1.w = item entry", 1);

    // GetItemName
    SetFunctionCmt(0x8bd0, 
        "In: D1 = item entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetItemDefinitionAddress
    SetFunctionCmt(0x8be4, 
        "Out: a0 = pointer to definition for item d1", 1);

    // GetItemBySlotAndHeldItemsNumber
    SetFunctionCmt(0x8bfa, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d1.w = item entry, d2.l = number of items held", 1);

    // GetEquipmentType
    SetFunctionCmt(0x8c28, 
        "Get equipment type for item d1.w -> d2.w (0 = none, 1 = weapon, -1 = ring)", 1);

    // GetEquippedWeapon
    SetFunctionCmt(0x8c4c, 
        "Get equipped weapon and slot indexes for combatant d0.b -> d1.w, d2.w (-1 if nothing equipped)", 1);

    // GetEquippedRing
    SetFunctionCmt(0x8c56, 
        "Get equipped ring and slot indexes for combatant d0.b -> d1.w, d2.w (-1 if nothing equipped)", 1);

    // AddItem
    SetFunctionCmt(0x8ca2, 
        "In: d0.b = combatant index, d1.w = item entry\n\
Out: d2.w = 0 if item successfully added, 1 if no empty slot available", 1);

    // BreakItemBySlot
    SetFunctionCmt(0x8cd4, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2 = -1 if item slot was empty", 1);

    // RepairItemBySlot
    SetFunctionCmt(0x8d00, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2 = 1 if item was not broken, -1 if item slot was empty", 1);

    // EquipItemBySlot
    SetFunctionCmt(0x8d34, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2.w = 0 if equipped, 1 if not, 2 if equipped and cursed, 3 if item is nothing", 1);

    // IsItemEquippableAndCursed
    SetFunctionCmt(0x8d6a, 
        "Is item d1.w equippable by ally d0.b and if so, is it cursed?\n\
\n\
  Out: d2.w = 0 if equippable, 1 if not, 2 if equippable and cursed", 1);

    // UnequipItemBySlotIfNotCursed
    SetFunctionCmt(0x8d9e, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2.w = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if nothing", 1);

    // IsItemInSlotEquippedOrCursed
    SetFunctionCmt(0x8db6, 
        "Is item in slot d1.w equipped by combatant d0.b, and if so, is it cursed?\n\
\n\
  In: d0.b = combatant index, d1.w = item slot\n\
\n\
  Out: a0 = pointer to item entry\n\
       d2.w = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if neither", 1);

    // UnequipItemBySlot
    SetFunctionCmt(0x8dfe, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2.w = 0 if equipped, 1 if not equipped, 2 if equipped and cursed, 3 if nothing", 1);

    // DropItemBySlot
    SetFunctionCmt(0x8e12, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2.w = 2 if not dropped, 3 if dropped or nothing", 1);

    // RemoveAndArrangeItems
    SetFunctionCmt(0x8e5c, 
        "In: a0 = combatant items address\n\
    d0.w = item slot\n\
\n\
Out: d2.w = 0", 1);

    // RemoveItemBySlot
    SetFunctionCmt(0x8e76, 
        "In: d0.b = combatant index, d1.w = item slot\n\
Out: d2.w = 3 if nothing to remove, 0 otherwise", 1);

    // GetEquippableWeapons
    SetFunctionCmt(0x8eee, 
        "Out: a0 = pointer to equippable items list\n\
     d1.w = equippable weapons count", 1);

    // GetEquippableRings
    SetFunctionCmt(0x8ef8, 
        "Out: a0 = pointer to equippable items list\n\
     d1.w = equippable rings count", 1);

    // IsItemEquippable
    SetFunctionCmt(0x8f60, 
        "In: d1.w = item index\n\
    d2.w = item type bitmask (for ANDing the item type bitfield)\n\
    d3.l = class equip bitmask (for ANDing the item equip bitfield)\n\
\n\
Out: CCR carry-bit set if true", 1);

    // IsWeaponOrRingEquippable
    SetFunctionCmt(0x8f80, 
        "Is weapon or ring d1.w equippable by combatant d0.w?\n\
Return CCR carry-bit set if true.", 1);

    // GetEquipNewAttAndDef
    SetFunctionCmt(0x8f9c, 
        "In: d1.w = index of new item being equipped\n\
Out: d2.w, d3.w = new ATT and DEF", 1);

    // GetNewAttAndDefWithItemEquipped
    SetFunctionCmt(0x8fee, 
        "In: a0 = combatant entry address\n\
    d1.w = new item index\n\
    d2.w = new item type (weapon or ring)\n\
\n\
Out: d2.w = current ATT with new item equipped\n\
     d3.w = current DEF with new item equipped", 1);

    // IsItemCursed
    SetFunctionCmt(0x90b2, 
        "Is item d1.w cursed? Return CCR carry-bit set if true.", 1);

    // IsItemUsableInBattle
    SetFunctionCmt(0x90cc, 
        "Is item d1.w usable in battle? Return CCR carry-bit set if true.", 1);

    // IsItemUsableByCombatant
    SetFunctionCmt(0x90e6, 
        "Is item d1.w allowed to be used in battle by combatant d0.w?\n\
Return CCR carry-bit set if true.", 1);

    // UnequipAllItemsIfNotCursed
    SetFunctionCmt(0x9106, 
        "In: d0.w = combatant index", 1);

    // GetItemInventoryLocation
    SetFunctionCmt(0x9146, 
        "In: d1.w = item\n\
Out: d0.b = character, d1.w = item slot", 1);

    // GetItemSlotContainingIndex
    SetFunctionCmt(0x9194, 
        "In: d0.b = combatant index, d1.w = item index\n\
Out: d2.w = item slot (-1 if not found)", 1);

    // GetSpellName
    SetFunctionCmt(0x91c6, 
        "In: D1 = spell index\n\
\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetSpellDefAddress
    SetFunctionCmt(0x91da, 
        "Find pointer to definition entry for spell d1.b -> a0", 1);

    // GetSpellAndNumberOfSpells
    SetFunctionCmt(0x91fa, 
        "In: d0.b = combatant index, d1.w = spell slot\n\
\n\
Out: d1.b = first spell entry, d2.w = number of spells learned", 1);

    // LearnSpell
    SetFunctionCmt(0x9226, 
        "In: d0.b = ally index, d1.w = spell entry\n\
\n\
Out: d2 = result (0 = success, 1 = failure : same or higher level known, 2 = failure : no room)", 1);

    // GetSpellCost
    SetFunctionCmt(0x927e, 
        "Get spell d1.b's MP cost -> d1.w", 1);

    // GetCombatantEntryAddress
    SetFunctionCmt(0x928e, 
        "Get pointer to combatant d0.b's entry in RAM -> a0", 1);

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
        "Clamp d7.b of combatant d0's data + d1.b between d5.b and d6.b", 1);

    // DecreaseAndClampByte
    SetFunctionCmt(0x936c, 
        "Clamp d7.b of combatant d0's data - d1.b between d5.b and d6.b", 1);

    // IncreaseAndClampLong
    SetFunctionCmt(0x93da, 
        "unused", 1);

    // DecreaseAndClampLong
    SetFunctionCmt(0x93f8, 
        "unused", 1);

    // GetDistanceBetweenCombatants
    SetFunctionCmt(0x941e, 
        "Get distance between two combatants on the battlefield (simple X and Y calculation, no obstructions.)\n\
\n\
      In: d0.w = actor combatant\n\
          d1.w = target combatant\n\
\n\
      Out: d2.w = distance in map blocks, or -1 if either combatant is positioned out of the battlefield", 1);

    // LevelUp
    SetFunctionCmt(0x9484, 
        "In: d0.w = ally index", 1);

    // InitializeAllyStats
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

    // InitializeAllyCombatantEntry
    SetFunctionCmt(0x975e, 
        "In: D0 = ally index", 1);

    // LoadAllyClassData
    SetFunctionCmt(0x97f8, 
        "In: d0.w = ally index\n\
    d1.w = class index", 1);

    // InitializeGameSettings
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
        "In: d0.b = ally index", 1);

    // LeaveForce
    SetFunctionCmt(0x9976, 
        "In: d0.b = ally index", 1);

    // IsInBattleParty
    SetFunctionCmt(0x9994, 
        "Is ally d0.b currently in battle party? Return CCR zero-bit set if true.", 1);

    // JoinBattleParty
    SetFunctionCmt(0x99ac, 
        "In: d0.b = ally index", 1);

    // LeaveBattleParty
    SetFunctionCmt(0x99c0, 
        "In: d0.b = ally index", 1);

    // GetDealsItemAmount
    SetFunctionCmt(0x99de, 
        "In: d1.w = item index, Out: d2.b = number of item index in deals", 1);

    // AddItemToDeals
    SetFunctionCmt(0x99ec, 
        "In: d1.w = item index", 1);

    // RemoveItemFromDeals
    SetFunctionCmt(0x9a02, 
        "In: d1.w = item index", 1);

    // GetDealsItemInfo
    SetFunctionCmt(0x9a16, 
        "In: d1.w = item index\n\
\n\
Out: a0 = RAM address of deals slot\n\
     d0 = amount to add to deals slot (0x10 or 0x01)\n\
     d2.b = number of item index in deals", 1);

    // AddItemToCaravan
    SetFunctionCmt(0x9a3c, 
        "In: d1.w = item index (only the actual index is used, the status bits are cut out)", 1);

    // RemoveItemFromCaravan
    SetFunctionCmt(0x9a62, 
        "In: d1.w = inventory slot", 1);

    // DebugModeSelectHits
    SetFunctionCmt(0x9b58, 
        "In: a2 = battlescene script stack frame", 1);

    // WriteBattlesceneScript
    SetFunctionCmt(0x9b92, 
        "In: d0.w = actor index", 1);

    // battlesceneScript_DetermineTargetsByAction
    SetFunctionCmt(0x9dd6, 
        "In: a3 = battleaction data pointer", 1);

    // battlesceneScript_InitializeActors
    SetFunctionCmt(0x9e60, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction data pointer\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // battlesceneScript_DetermineIneffectiveAttack
    SetFunctionCmt(0x9ec4, 
        "In: a2 = battlescene script stack frame", 1);

    // battlesceneScript_InitializeBattlesceneProperties
    SetFunctionCmt(0x9f28, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction data pointer\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // battlesceneScript_DisplayActionMessage
    SetFunctionCmt(0xa05c, 
        "Load display message command depending on action.\n\
\n\
      In: a3 = battleaction data pointer\n\
          a4 = actor index pointer\n\
\n\
HARDCODED enemy and message indexes", 1);

    // battlesceneScript_PerformAnimation
    SetFunctionCmt(0xa200, 
        "Load battlescene sprite and spellanimation properties.\n\
\n\
      In: a2 = battlescene script stack frame\n\
          a3 = battleaction data pointer\n\
          a4 = actor index pointer", 1);

    // battlesceneScript_End
    SetFunctionCmt(0xa34e, 
        "In: a2 = battlescene script stack frame", 1);

    // battlesceneScript_ApplyActionEffect
    SetFunctionCmt(0xa3f4, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction type pointer\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // battlesceneScript_ValidateDoubleAttack
    SetFunctionCmt(0xa45e, 
        "In: a2 = battlescene script stack frame", 1);

    // battlesceneScript_ValidateCounterAttack
    SetFunctionCmt(0xa49c, 
        "In: a2 = battlescene script stack frame\n\
    a4 = pointer to target index\n\
    a5 = pointer to actor index\n\
\n\
Out: -12(a2) = 0 if false, otherwise true", 1);

    // battlesceneScript_GetSpellanimation
    SetFunctionCmt(0xa54e, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction data pointer\n\
    a4 = actor index pointer\n\
\n\
Out: d4.b = spellanimation index\n\
\n\
HARDCODED class, enemy and weapon indexes", 1);

    // battlesceneScript_AnimateAction
    SetFunctionCmt(0xa6e8, 
        "Load battlescene sprite and spellanimation properties.\n\
\n\
In: d4.w = spell/item/projectile animation index, set $80 to come from enemy\n\
    d5.w = animation type index (0 = attack, 1 = dodge, 2 = spell/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)", 1);

    // battlesceneScript_SwitchTargets
    SetFunctionCmt(0xa702, 
        "In: a2 = battlescene script stack frame\n\
    d6.w = direction (0 = right, 1 = left)", 1);

    // battlesceneScript_GiveExpAndGold
    SetFunctionCmt(0xa7f8, 
        "In: a2 = battlescene script stack frame", 1);

    // battlesceneScript_GetKillExp
    SetFunctionCmt(0xa968, 
        "Get EXP gained for a kill based on level difference between actor and target.\n\
\n\
  In: a4, a5 = pointers to actor and target indexes\n\
  Out: d5.l = EXP amount", 1);

    // OneSecondSleep
    SetFunctionCmt(0xaa98, 
        "unused", 1);

    // NopOnce
    SetFunctionCmt(0xaaa4, 
        "unused", 1);

    // NopTwice
    SetFunctionCmt(0xaaa8, 
        "unused", 1);

    // NopThrice
    SetFunctionCmt(0xaaae, 
        "unused", 1);

    // battlesceneScript_Attack
    SetFunctionCmt(0xaab6, 
        "In: a2 = battlescene script stack frame\n\
    a4 = pointer to attacker index in RAM\n\
    a5 = pointer to target index in RAM", 1);

    // battlesceneScript_DetermineDodge
    SetFunctionCmt(0xaafc, 
        "In: a2 = battlescene script stack frame\n\
    a4 = attacker index pointer\n\
    a5 = target index pointer", 1);

    // battlesceneScript_CalculateDamage
    SetFunctionCmt(0xabbe, 
        "In: a4 = attacker index pointer\n\
    a5 = target index pointer\n\
\n\
Out: d6.w = damage", 1);

    // battlesceneScript_DetermineCriticalHit
    SetFunctionCmt(0xac4e, 
        "In: a2 = battlescene script stack frame\n\
    d6.w = damage", 1);

    // battlesceneScript_InflictDamage
    SetFunctionCmt(0xacea, 
        "In: a2 = battlescene script stack frame\n\
    a4 = actor index pointer\n\
    a5 = target index pointer\n\
    d6.w = damage value", 1);

    // battlesceneScript_InflictAilment
    SetFunctionCmt(0xae32, 
        "In: a2 = battlescene script stack frame", 1);

    // battlesceneScript_InflictCurseDamage
    SetFunctionCmt(0xaf70, 
        "In: a2 = battlescene script stack frame\n\
    d6.w = final damage", 1);

    // battlesceneScript_DetermineDoubleAndCounter
    SetFunctionCmt(0xb00e, 
        "In: a2 = battlescene script stack frame\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // battlesceneScript_CastSpell
    SetFunctionCmt(0xb0a8, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction data pointer\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // spellEffect_Slow
    SetFunctionCmt(0xb30e, 
        "In: d2.w = target's resistance setting", 1);

    // spellEffect_Dispel
    SetFunctionCmt(0xb41a, 
        "In: d2.w = target's resistance setting", 1);

    // spellEffect_Muddle
    SetFunctionCmt(0xb488, 
        "In: d2.w = target's resistance setting", 1);

    // spellEffect_Desoul
    SetFunctionCmt(0xb516, 
        "In: a2 = battlescene script stack frame\n\
    d2.w = target's resistance setting", 1);

    // spellEffect_Sleep
    SetFunctionCmt(0xb57e, 
        "In: d2.w = target's resistance setting", 1);

    // battlesceneScript_DetermineSpellEffectiveness
    SetFunctionCmt(0xba98, 
        "In: a2 = battlescene script stack frame\n\
    d2.w = resistance setting (0=none, 1=minor, 2=major, 3=immunity)", 1);

    // battlesceneScript_CalculateSpellDamage
    SetFunctionCmt(0xbb02, 
        "In: a2 = battlescene script stack frame\n\
    d2.w = resistance setting (0 = none, 1 = minor, 2 = major, 3 = weakness)\n\
    d3.l = chance to critical hit", 1);

    // AdjustSpellPower
    SetFunctionCmt(0xbb56, 
        "Miscellaneous hacks to alter spell power (125% if promoted, damage divided if SORC spells.)\n\
\n\
  In: a3 = pointer to action type index in RAM\n\
      a4 = pointer to caster's index in RAM\n\
      d6.w = original spell power\n\
\n\
  Out: d6.w = altered spell power", 1);

    // battlesceneScript_GetItemBreakMessage
    SetFunctionCmt(0xbc9a, 
        "In: a2 = battlescene script stack frame\n\
    d0.b = whether item is already damaged (0=no, 1=yes)\n\
\n\
Out: d3.w = message index", 1);

    // battlesceneScript_DropEnemyItem
    SetFunctionCmt(0xbd24, 
        "In: a2 = battlescene script stack frame\n\
    a3 = battleaction type pointer\n\
    a4 = actor index pointer\n\
    a5 = target index pointer", 1);

    // GetEnemyDestination
    SetFunctionCmt(0xc024, 
        "In: d0.b = combatant index\n\
Out: d1.w, d2.w = X,Y coordinates", 1);

    // ConvertCoordinatesToAddress
    SetFunctionCmt(0xc09a, 
        "Convert coordinates to offset and add to address argument.\n\
\n\
  In: a0 = start of grid address, d1.w,d2.w = X,Y coordinates\n\
  Out: a0 = start of grid address + offset", 1);

    // GetCombatantOccupyingSpace
    SetFunctionCmt(0xc0e8, 
        "Get index of combatant occupying position d1.w,d2.w -> d0.b", 1);

    // GetMoveCostToEntity
    SetFunctionCmt(0xc0fc, 
        "Get movecost to reach entity d0.b -> d0.b", 1);

    // GetMoveCostToDestination
    SetFunctionCmt(0xc118, 
        "Get movecost to reach space at coordinates d1.w,d2.w -> d0.b", 1);

    // GetCurrentTerrainType
    SetFunctionCmt(0xc144, 
        "Get terrain type of space occupied by battle entity d0.b -> d0.b", 1);

    // GetTerrain
    SetFunctionCmt(0xc160, 
        "Get terrain entry at coordinates d1.w,d2.w -> d0.b", 1);

    // SetTerrain
    SetFunctionCmt(0xc176, 
        "Set terrain entry d0.b at coordinates d1.w,d2.w", 1);

    // PopulateMovecostsTable
    SetFunctionCmt(0xc18c, 
        "Populate movecosts table for moving battle entity d0.b", 1);

    // sub_C1BE
    SetFunctionCmt(0xc1be, 
        "unused", 1);

    // GetLandEffectSetting
    SetFunctionCmt(0xc1da, 
        "In:  d0.b = combatant index\n\
Out: d1.w = land effect setting (0 = 0%, 1 = 15%, 2 = 30%)", 1);

    // SetMovableSpace
    SetFunctionCmt(0xc204, 
        "Set space at position d1.w,d2.w as movable and clear movecost.", 1);

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

    // InitializeMovementArrays
    SetFunctionCmt(0xc2c8, 
        "Out: a2, a3 = pointers to total movecosts and movable grid arrays\n\
     a4 = pointer to battle terrain array\n\
     a5 = pointer to move costs table\n\
     d0.w = move value (MOV*2)\n\
     d3.w, d4.w = moving combatant X, Y\n\
       ", 1);

    // GetAttackRange
    SetFunctionCmt(0xc306, 
        "Get max, min attack range for combatant d0.b -> d3.w, d4.w", 1);

    // GetSpellRange
    SetFunctionCmt(0xc380, 
        "In: D1 = spell index\n\
Out: D3 = max range, D4 = min range", 1);

    // GetItemRange
    SetFunctionCmt(0xc398, 
        "In: D1 = item index\n\
Out: D3 = max range, D4 = min range", 1);

    // IsConfused
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

    // ApplyRelativeCoordinatesListToGrid
    SetFunctionCmt(0xc510, 
        "Apply relative coordinates list to movable grid and add any targets to target list.\n\
\n\
  In: a0 = address of relative coordinates list\n\
      d0.b = battle entity index\n\
      d5.b = ignore obstructed terrain if = 0", 1);

    // PopulateTargetableGrid_UseItem
    SetFunctionCmt(0xc5d6, 
        "In: d0.w = actor combatant index\n\
    d1.w = item index", 1);

    // sub_C5FA
    SetFunctionCmt(0xc5fa, 
        "unused", 1);

    // PopulateTargetableGrid_CastSpell
    SetFunctionCmt(0xc61e, 
        "In: d0.w = actor combatant index\n\
    d1.w = spell index", 1);

    // PopulateTargetableGrid
    SetFunctionCmt(0xc62e, 
        "In: d1.b = spell entry", 1);

    // GetClosestAttackPosition
    SetFunctionCmt(0xc71a, 
        "In: d1.b,d2.b = current X,Y\n\
    d3.b,d4.b = max,min range\n\
\n\
Out: d1.b,d2.b = destination X,Y (-1 if no position is available)", 1);

    // PopulateTargetsArrayWithOpponents
    SetFunctionCmt(0xc7f2, 
        "Populate array of targets with alignment opposite to d0.w\n\
(Note: enemy bit is flipped prior to calling this routine.)", 1);

    // PopulateTargetsArrayWithAllCombatants
    SetFunctionCmt(0xc81c, 
        "Populate an array containing all combatants present on the battlefield.", 1);

    // UpdateBattleTerrainOccupiedByOpponents
    SetFunctionCmt(0xc87a, 
        "In: d0.w = combatant\n\
    d3.w = 0 to clear flag, set otherwise", 1);

    // UpdateBattleTerrainOccupiedFlag
    SetFunctionCmt(0xc898, 
        "In: d3.w = 0 to clear flag, set otherwise", 1);

    // UpdateMovableGridArray
    SetFunctionCmt(0xc900, 
        "In: d3.w = clear bit 7 if = 0, set otherwise", 1);

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

    // CalculatePotentialRemainingHp
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
Specific decending priority for each move type is in table_HealPriorityMoveTypes.\n\
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
        "Get highest usable level of spell D1, considering current MP and highest known level.\n\
\n\
  In: d0.w = caster index, d1.w = highest known level spell entry, d4.w = spell index\n\
  Out: d1.w = highest usuable level spell entry", 1);

    // GetSlotContainingSpell
    SetFunctionCmt(0xcf0e, 
        "unused\n\
\n\
  In: d0.b = combatant index, d1.b = spell index\n\
  Out: d1.w = spell index, d2.w = slot", 1);

    // GetSlotContainingItem
    SetFunctionCmt(0xcf40, 
        "unused\n\
\n\
  In: d0.b = combatant index, d1.b = item index\n\
  Out: d1.w = item index, d2.w = slot", 1);

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
 BLAZE/FREEZE/BOLT/BLAST.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell entry, d2.w = item slot\n\
\n\
HARDCODED spell indexes", 1);

    // GetNextUsableHealingItem
    SetFunctionCmt(0xd160, 
        "Get the next item in combatant's inventory that can be used to cast\n\
 a healing spell.\n\
\n\
This only looks for Healing Rain as a valid healing item,\n\
 unless the AI is set to use the item the in battle data.\n\
\n\
      In: d0.w = caster index, d3.w = starting spell slot\n\
      Out: d1.w = spell index, d2.w = spell slot\n\
\n\
HARDCODED item and spell indexes", 1);

    // IsCombatantAtLessThanHalfHp
    SetFunctionCmt(0xd296, 
        "Is combatant d0.w at less than half HP? Return CCR carry-bit clear if true.", 1);

    // sub_D2D2
    SetFunctionCmt(0xd2d2, 
        "unused", 1);

    // sub_D2F8
    SetFunctionCmt(0xd2f8, 
        "Set the carry flag if less than 2/3rds of defenders remaining HP\n\
  is expected to be taken by the attack.\n\
\n\
  In: d0.w = defender index, d1.w = defenders theoretical remaining HP after attack", 1);

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
        "Is combatant d0.w at 2/3 or less of max HP? Return CCR carry-bit clear if true.", 1);

    // sub_D3CA
    SetFunctionCmt(0xd3ca, 
        "Unused in the US version.", 1);

    // sub_D3E0
    SetFunctionCmt(0xd3e0, 
        "unused", 1);

    // sub_D3F0
    SetFunctionCmt(0xd3f0, 
        "unused", 1);

    // GetDifficulty
    SetFunctionCmt(0xd408, 
        "Out: D1 = 0 if normal, 1 if hard, 2 if super, 3 if ouch", 1);

    // PopulatePrioritiesListForSpell_Attack
    SetFunctionCmt(0xd460, 
        "AI: cast ATTACK spell", 1);

    // PopulatePrioritiesListForSpell_Boost2
    SetFunctionCmt(0xd4e0, 
        "AI: cast BOOST 2 spell", 1);

    // PopulatePrioritiesListForSpell_Dispel
    SetFunctionCmt(0xd560, 
        "AI: cast DISPEL spell", 1);

    // PopulatePrioritiesListForSpell_Muddle2
    SetFunctionCmt(0xd62c, 
        "AI: cast MUDDLE 2 spell", 1);

    // CalculateTargetPriorityForSpell_Dispel
    SetFunctionCmt(0xd6f2, 
        "Returns priority for the AI to cast DISPEL.\n\
+1 point for each target within the area of effect that knows at least\n\
 one attack or healing spell.\n\
\n\
Out: d1.w = target priority", 1);

    // CalculateTargetPriorityForSpell_Boost
    SetFunctionCmt(0xd742, 
        "Returns priority for the AI to cast BOOST.\n\
\n\
Out: d1.w = target priority", 1);

    // CalculateTargetPriorityForSpell_Attack
    SetFunctionCmt(0xd7aa, 
        "Returns priority for the AI to cast ATTACK.\n\
\n\
Out: d1.w = target priority", 1);

    // PopulateMovementArrays
    SetFunctionCmt(0xda82, 
        "In: a2, a3 = pointers to total movecosts and movable grid arrays\n\
    d0.w = move value (MOV*2)\n\
    d3.b, d4.b = moving combatant X, Y", 1);

    // sub_DB48
    SetFunctionCmt(0xdb48, 
        "In: a2, a3 = movecost arrays\n\
    a4 = pointer to battle terrain array\n\
    a5 = pointer to move costs table\n\
    d0.w = move value (MOV*2)\n\
    d5.w = coordinates offset\n\
    d6.w = move count", 1);

    // BuildCancelMoveString
    SetFunctionCmt(0xdb9a, 
        "In: a2, a3 = pointers to total movecosts and movable grid arrays\n\
    d0.b, d1.b = X, Y", 1);

    // alt_BuildCancelMoveString
    SetFunctionCmt(0xdba8, 
        "Alternate entry point", 1);

    // BuildAiMoveString
    SetFunctionCmt(0xdd10, 
        "In: a2, a3 = pointers to total movecosts and movable grid arrays\n\
    d0.b, d1.b = destination X,Y", 1);

    // AddAllToStack
    SetFunctionCmt(0xdd60, 
        "unused", 1);

    // BuildMoveString
    SetFunctionCmt(0xdd6a, 
        "In: a2, a3 = pointers to total movecosts and movable grid arrays\n\
    d0.w, d1.w = starting X, Y\n\
    d3.w = move value (MOV*2)", 1);

    // alt_BuildMoveString
    SetFunctionCmt(0xdd78, 
        "Alternate entry point", 1);

    // StartAiControl
    SetFunctionCmt(0xdefc, 
        "Starting point for the AI control process.\n\
\n\
  In: d0.w = combatant index", 1);

    // CountDefeatedEnemies
    SetFunctionCmt(0xe0b6, 
        "Out: d1.w = defeated enemies count", 1);

    // ProcessLineAttackerAi
    SetFunctionCmt(0xe0ee, 
        "In: d0.w = attacker index", 1);

    // ProcessExploderAi
    SetFunctionCmt(0xe144, 
        "In: d0.w = attacker index", 1);

    // ExecuteAiCommand
    SetFunctionCmt(0xe294, 
        "In: d0.b = combatant index\n\
    d1.b = command code (like Heal, Attack, etc.)", 1);

    // ExecuteAiCommand_Heal
    SetFunctionCmt(0xe3ee, 
        "In: d0.b = caster index\n\
    d1.w = command parameter (values of 0-2), unused\n\
\n\
Out: d1.w = -1 if command failed", 1);

    // ExecuteAiCommand_Attack
    SetFunctionCmt(0xe78c, 
        "In: D0 = character index (attacker)\n\
    D1 = extra AI variable (values of 0-3)", 1);

    // ExecuteAiCommand_SpecialMove
    SetFunctionCmt(0xe98c, 
        "Move scripts (move to point, follow ally, follow force member)\n\
\n\
Out: d1.b = -1 if command failed to execute", 1);

    // ExecuteAiCommand_Support
    SetFunctionCmt(0xeba4, 
        "Support spells AI (Muddle 2, Dispel 1)\n\
\n\
In: d0.w = caster index\n\
Out: d1.b = -1 if command failed to execute", 1);

    // DetermineAiBattleaction
    SetFunctionCmt(0xedd6, 
        "AI randomly chooses whether to attack, cast a spell, or use an item.\n\
\n\
Then, AI will always target the highest priority option based upon\n\
 the chosen action, unless there are multiple options with equal priority.\n\
\n\
      In: d0.b = character index of attacker\n\
      Out: d0.w = target index, d1.w = priority (max of 15), d2.b = battle action\n\
\n\
If no targets in range then d0.w = -1, d1.w = 0, d2.b = 3", 1);

    // ExecuteAiCommand_Move
    SetFunctionCmt(0xf1d4, 
        "In: D0 = character index (mover)\n\
    D1 = extra AI variable (values of 0-2)", 1);

    // DetermineStandbyAiMovement
    SetFunctionCmt(0xf522, 
        "Randomly move an AI controlled combatant around a designated position when not activated.\n\
\n\
In: d0.w = attacker combatant", 1);

    // sub_F7A0
    SetFunctionCmt(0xf7a0, 
        "In: d0.b = moving combatant index\n\
    d1.b = teammate to follow combatant index", 1);

    // sub_F8EA
    SetFunctionCmt(0xf8ea, 
        "Out: d1.w = 0 if allowed to move\n\
     d2.w != 0 if combatant is set to perform a special move order", 1);

    // WriteTilesFromAsciiWithOrangeFont
    SetFunctionCmt(0x100c8, 
        "Write tiles from ASCII using the orange font", 1);

    // WriteTilesFromNumber
    SetFunctionCmt(0x100d4, 
        "write tiles from number in D0 into A1 D7 letters, window width D1", 1);

    // WriteTilesFromAsciiWithRegularFont
    SetFunctionCmt(0x100e2, 
        "Write tiles from ASCII from A0 into A1 D7 letters, window width D1", 1);

    // WriteWindowTiles
    SetFunctionCmt(0x1018e, 
        "Write window tiles onto layout a1, dimensions d0.w including borders (xxyy).", 1);

    // ExecuteDiamondMenu
    SetFunctionCmt(0x101f6, 
        "In: a0 = special subroutine address to handle menu, default handling if not supplied (unused functionality)\n\
    d0.b = initial choice (0 = up, 1 = left, 2 = right, 3 = down)\n\
    d1.w = animate-in direction (0 = from bottom, other = from right)\n\
    d2.w = menu index to use (only affects icons and text)", 1);

    // LoadDiamondMenuWindowLayout
    SetFunctionCmt(0x103b8, 
        "In: -12(a6) = window slot index", 1);

    // DmaDiamondMenuIcons
    SetFunctionCmt(0x103fe, 
        "In: d6.w = frame counter", 1);

    // dmaDiamondMenuIcon_Up
    SetFunctionCmt(0x10410, 
        "In: d6.w = frame counter", 1);

    // dmaDiamondMenuIcon_Left
    SetFunctionCmt(0x10430, 
        "In: d6.w = frame counter", 1);

    // dmaDiamondMenuIcon_Right
    SetFunctionCmt(0x1045a, 
        "In: d6.w = frame counter", 1);

    // dmaDiamondMenuIcon_Down
    SetFunctionCmt(0x10548, 
        "In: d6.w = frame counter", 1);

    // LoadMainMenuIcon
    SetFunctionCmt(0x10568, 
        "In: d0.b = menu icon index", 1);

    // ExecuteBattlefieldItemMenu
    SetFunctionCmt(0x10586, 
        "In: A0 = special subroutine address to handle menu, default handling if not supplied\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // DmaSelectedIcon
    SetFunctionCmt(0x107ea, 
        "In: d6.w = frame counter", 1);

    // dmaSelectedIcon_Up
    SetFunctionCmt(0x10800, 
        "In: d6.w = frame counter", 1);

    // dmaSelectedIcon_Left
    SetFunctionCmt(0x10820, 
        "In: d6.w = frame counter", 1);

    // dmaSelectedIcon_Right
    SetFunctionCmt(0x1084a, 
        "In: d6.w = frame counter", 1);

    // dmaSelectedIcon_Down
    SetFunctionCmt(0x10920, 
        "In: d6.w = frame counter", 1);

    // LoadHighlightableSpellIcon
    SetFunctionCmt(0x10940, 
        "Load spell icon with red border overlay.\n\
\n\
      In: a1 = destination in RAM\n\
          d0.w = spell index\n\
\n\
      Out: a1 = end of affected section after copy", 1);

    // LoadHighlightableItemIcon
    SetFunctionCmt(0x10958, 
        "Same as above, but for items.", 1);

    // ExecuteBattlefieldMagicMenu
    SetFunctionCmt(0x10a4a, 
        "In: A0 = special subroutine address to handle menu, default handling if not supplied\n\
    D0 = initial choice (00=up, 01=left, 02=right, 03=down)\n\
    D1 = animate-in direction (00=from bottom, other=from right)\n\
    D2 = menu index to use (just affects icons and text)", 1);

    // DmaSelectedIcon_0
    SetFunctionCmt(0x10cb0, 
        "related to menu choice", 1);

    // SelectSpellLevel
    SetFunctionCmt(0x10cc6, 
        "In: d0.w = displayed spell icon. Out: d0.w = selection (-1 if pressed B)", 1);

    // LoadSpellLevelHighlightSprites
    SetFunctionCmt(0x10de2, 
        "In: d6.w = blinking frame timer", 1);

    // OpenBattlefieldMiniStatusWindow
    SetFunctionCmt(0x11572, 
        "In: d0.w = combatant index", 1);

    // CloseBattlefieldMiniStatusWindow
    SetFunctionCmt(0x115e0, 
        "Move window off screen, then clear it from memory.", 1);

    // OpenAllyBattlesceneMiniStatusWindow
    SetFunctionCmt(0x11638, 
        "In: d0.b = ally index\n\
    d1.w = ?", 1);

    // OpenEnemyBattlesceneMiniStatusWindow
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
        "Check ASCII name at a0 for two special characters.\n\
\n\
In: d7.w = name length", 1);

    // BuildMiniStatusWindow
    SetFunctionCmt(0x118be, 
        "In: a1 = window tiles address, d0.w = combatant index", 1);

    // WriteStatValue
    SetFunctionCmt(0x11aae, 
        "Write stat value d0.w or '??' if above 99", 1);

    // WriteOneMiniStatusWindowTileColumn
    SetFunctionCmt(0x11ac6, 
        "Draw tiles from a0 into a1 (one column)", 1);

    // ClosePortraitWindow
    SetFunctionCmt(0x11be2, 
        "Move window offscreen, then clear it from memory.", 1);

    // BuildMemberScreen
    SetFunctionCmt(0x11c2a, 
        "Create and display member screen.\n\
\n\
  In: d0.w = member index", 1);

    // WriteStatusEffectTiles
    SetFunctionCmt(0x11eea, 
        "In: a1 = current cursor position in the layout\n\
    d0.l = VDP tile entries", 1);

    // BuildMemberStatusWindow
    SetFunctionCmt(0x11ff0, 
        "In: a1 = window tile adress, d0.w = combatant index", 1);

    // sub_12606
    SetFunctionCmt(0x12606, 
        "unused", 1);

    // GetCombatantPortrait
    SetFunctionCmt(0x1263a, 
        "Get portrait index for combatant d0.w -> d0.w", 1);

    // ValidateMembersListScreenConfirmationInput
    SetFunctionCmt(0x132bc, 
        "Out: CCR zero-bit set if confirmation input is valid", 1);

    // LoadMembersListScreenPortrait
    SetFunctionCmt(0x13394, 
        "In: D0 = combatant index", 1);

    // LoadMembersListHighlightSprites
    SetFunctionCmt(0x133a0, 
        "Load VDP sprite data for the red box used to highlight text in the\n\
members list window.\n\
\n\
In: d1.w = blinking frame timer", 1);

    // GetSelectedMember
    SetFunctionCmt(0x13462, 
        "    Get index of currently selected force member (in menus).\n\
    Out: D0 = selected index (capped to 255)", 1);

    // CopyWords
    SetFunctionCmt(0x134a0, 
        "unused", 1);

    // BuildMembersListWindow
    SetFunctionCmt(0x135a6, 
        "In: a1 = window tiles address, d0.w = selected member index", 1);

    // LoadIcon
    SetFunctionCmt(0x13b82, 
        "In: a1 = loading space address, d1.w = item or spell index", 1);

    // DmaMembersListIcon
    SetFunctionCmt(0x14074, 
        "In: d0.w = current diamond-menu choice", 1);

    // PerformEquipItemSubmenuAction
    SetFunctionCmt(0x14108, 
        "Call ExecuteEquipMenu and equip new items accordingly.", 1);

    // ExecuteEquipMenu
    SetFunctionCmt(0x141ce, 
        "In: D1 = old equipped item index\n\
    D2 = old equipped item slot\n\
    D3 = equippable items count", 1);

    // LoadMemberSummaryHighlightSprites
    SetFunctionCmt(0x146ae, 
        "Load VDP sprite data for the red box used to highlight text in the\n\
members list screen summary (i.e., top-right) window.\n\
\n\
In: d1.w = blinking frame timer", 1);

    // WriteSpellLevel
    SetFunctionCmt(0x1474c, 
        "In: d3.w  = selected spell level", 1);

    // EquipNewItem
    SetFunctionCmt(0x1477e, 
        "Try to unequip current item, and equip new one if successful\n\
\n\
     In: d1.w = old item index (-1 if nothing equipped)\n\
         d2.w = old item slot\n\
         d4.w = new item slot", 1);

    // ExecuteShopScreen
    SetFunctionCmt(0x147fa, 
        "Out: d0.w = selected item index, or -1 if canceled out of the screen", 1);

    // LoadShopInventoryHighlightSprites
    SetFunctionCmt(0x14a82, 
        "In: d1.w = blinking frame timer", 1);

    // WriteGoldAmount
    SetFunctionCmt(0x14b28, 
        "related to gold display", 1);

    // LoadItemIconsAndPriceTagTiles
    SetFunctionCmt(0x14bb0, 
        "Load item icons and price tag tiles based on generic index list.", 1);

    // LoadPriceTagTiles
    SetFunctionCmt(0x14c56, 
        "Load shop price tag pixels into space at a0.", 1);

    // LoadItemIconInShopScreen
    SetFunctionCmt(0x14cb2, 
        "Load icon pixels for item d0.w to loading space in a0.", 1);

    // GetCurrentShopSelection
    SetFunctionCmt(0x14cec, 
        "Get index of currently selected item in shop/caravan (from index list) -> d0.w", 1);

    // sub_14EC0
    SetFunctionCmt(0x14ec0, 
        "Set item name and price window destination off-screen.", 1);

    // sub_15268
    SetFunctionCmt(0x15268, 
        "unused", 1);

    // sub_15422
    SetFunctionCmt(0x15422, 
        "related to DMA\n\
\n\
In: d0.b = current diamond menu choice", 1);

    // ClosePortraitEyes
    SetFunctionCmt(0x154f6, 
        "Close princess Elis's eyes when unconscious", 1);

    // UpdatePortrait
    SetFunctionCmt(0x155c4, 
        "In: d1.w = 0 to use original tiles, 1 to use alternate tiles\n\
    d7.w = tiles number", 1);

    // LoadPortrait
    SetFunctionCmt(0x1562a, 
        "In: d0.w = portrait index", 1);

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

    // BuildBattlefieldSettingsScreen
    SetFunctionCmt(0x1586e, 
        "related to battlefield options", 1);

    // GetCurrentBattlefieldSettingValue
    SetFunctionCmt(0x15a20, 
        "In: d4.w = 0 to get message speed, or 1 to get no battle messages toggle\n\
Out: d3.w", 1);

    // NameAlly
    SetFunctionCmt(0x15bb0, 
        "In: D0 = ally index", 1);

    // LoadAlphabetHighlightSprites
    SetFunctionCmt(0x15f24, 
        "In: d1.w = blinking frame timer", 1);

    // NumberPrompt
    SetFunctionCmt(0x16282, 
        "In: d0.w = default number, d1.w = min number, d2.w = max number\n\
Out: d0.w = chosen number", 1);

    // WriteNumberPromptDigits
    SetFunctionCmt(0x16376, 
        "In: a6 = number prompt window stack", 1);

    // UpdatePromptNumber
    SetFunctionCmt(0x16398, 
        "In: a6 = number prompt window stack", 1);

    // ExecuteWitchMainMenu
    SetFunctionCmt(0x16658, 
        "In: d0.w = window slot\n\
    d1.w = \n\
    d2.w = \n\
\n\
Out: d0.w = -1 if pressed B", 1);

    // CloseNameUnderPortraitWindow
    SetFunctionCmt(0x16a30, 
        "Move window offscreen, then clear it from memory.", 1);

    // nullsub_18010
    SetFunctionCmt(0x18010, 
        "unused", 1);

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

    // bsc03_moveAllyBattlesprite
    SetFunctionCmt(0x185c8, 
        "like previous bsc but for battlescene ally", 1);

    // bsc02_moveEnemyBattlesprite
    SetFunctionCmt(0x185de, 
        "set a long value at FFB3F6, related to battlescene enemy", 1);

    // bsc04_makeEnemyIdle
    SetFunctionCmt(0x1869a, 
        "related to battlescene enemy", 1);

    // bsc07_switchAllies
    SetFunctionCmt(0x186da, 
        "xx      Combatant index\n\
yy      0000 for right side, 0001 for left side", 1);

    // SwitchAllyBattlesprite
    SetFunctionCmt(0x188d4, 
        "In: d1.w = ", 1);

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

    // bsc0F_giveExp
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
        "same parameters as previous command", 1);

    // LoadBattlesceneAllyAndWeaponVdpSprites
    SetFunctionCmt(0x193b2, 
        "related to battlescene ally and weapon VDP sprites", 1);

    // LoadBattlesceneAllyVdpSprites
    SetFunctionCmt(0x193c4, 
        "related to battlescene ally VDP sprites", 1);

    // sub_1942C
    SetFunctionCmt(0x1942c, 
        "In: d0.w = frame index", 1);

    // LoadBattlesceneGroundVdpSprites
    SetFunctionCmt(0x19504, 
        "related to battlescene ground VDP sprites", 1);

    // MakeActorIdle
    SetFunctionCmt(0x195e2, 
        "make actor idle", 1);

    // sub_19632
    SetFunctionCmt(0x19632, 
        "In: d0.w, d1.w", 1);

    // AddEnemyToDeadList
    SetFunctionCmt(0x197a6, 
        "Add enemy to dead combatants list.", 1);

    // GetAllyAnimation
    SetFunctionCmt(0x197c8, 
        "In: d1.w = animation type, Out: a0 = animation pointer", 1);

    // GetEnemyAnimation
    SetFunctionCmt(0x19838, 
        "In: D1 = animation type, Out: A0 = animation pointer", 1);

    // GetAllyBattlespriteIdleAnimate
    SetFunctionCmt(0x19860, 
        "Return whether or not ally battlesprite d0.b should animate when idle.\n\
\n\
      Out: d1.l = 0 if it animates, 1 if not", 1);

    // GetEnemyBattlespriteIdleAnimate
    SetFunctionCmt(0x1986a, 
        "Return whether or not enemy battlesprite d0.b should animate when idle.\n\
\n\
      Out: d1.l = 0 if it animates, 1 if not", 1);

    // InitializeBattlescenePalettes
    SetFunctionCmt(0x19884, 
        "Clear palettes 1-2 and 1-2bis, and load battlescene UI and ground palette to 3bis.", 1);

    // LoadEnemyBattlespritePropertiesAndPalette
    SetFunctionCmt(0x19970, 
        "In: d0.w = enemy battlesprite index\n\
    d1.w = palette index", 1);

    // LoadEnemyBattlespriteFrameToVram
    SetFunctionCmt(0x1999e, 
        "In: d0.w = enemy battlesprite index\n\
    d1.w = frame index", 1);

    // LoadEnemyBattlespriteFrameAndWaitForDma
    SetFunctionCmt(0x199bc, 
        "In: d0.w = enemy battlesprite index\n\
    d1.w = frame index", 1);

    // LoadAllyBattlespritePropertiesAndPalette
    SetFunctionCmt(0x199de, 
        "In: d0.w = ally battlesprite index\n\
    d1.w = palette index", 1);

    // LoadAllyBattlespriteFrameToVram
    SetFunctionCmt(0x19a0c, 
        "In: d0.w = ally battlesprite index\n\
    d1.w = frame index", 1);

    // LoadAllyBattlespriteFrameAndWaitForDma
    SetFunctionCmt(0x19a2a, 
        "In: a1 = frame location in VRAM\n\
    d0.w = ally battlesprite index\n\
    d1.w = frame index", 1);

    // LoadWeaponPalette
    SetFunctionCmt(0x19a4c, 
        "In: d0.w = weapon palette index", 1);

    // LoadWeaponsprite
    SetFunctionCmt(0x19a5c, 
        "In: d0.w = weaponsprite index", 1);

    // LoadAllyBattlespriteFrame
    SetFunctionCmt(0x19ab0, 
        "In: d0.w = ally battlesprite index\n\
    d1.w = frame index", 1);

    // LoadEnemyBattlespriteFrame
    SetFunctionCmt(0x19b24, 
        "In: d0.w = enemy battlesprite index\n\
    d1.w = frame index", 1);

    // LoadNewEnemyBattlesprite
    SetFunctionCmt(0x19b44, 
        "In: d0.w = enemy battlesprite index", 1);

    // LoadBattlesceneBackground
    SetFunctionCmt(0x19b80, 
        "In: d0.w = battlescene background index", 1);

    // LoadBattlesceneGround
    SetFunctionCmt(0x19bcc, 
        "In: d0.w = battlescene ground index", 1);

    // LoadInvocationSpriteFrameToVram
    SetFunctionCmt(0x19bf2, 
        "In: d0.w = invocation sprite index\n\
    d1.w = frame number", 1);

    // LoadSpellGraphics
    SetFunctionCmt(0x19ca4, 
        "In: d0.w = spellanimation graphics data index", 1);

    // LoadSpellGraphicsForInvocation
    SetFunctionCmt(0x19ce8, 
        "Loads spell graphics for Apollo and Neptun invocations.\n\
\n\
In: d0.w = spellanimation graphics data index", 1);

    // GetBattlespriteAndPalette
    SetFunctionCmt(0x19d3e, 
        "Get battlesprite and palette indexes for combatant d0.w -> d1.w, d2.w", 1);

    // GetWeaponspriteAndPalette
    SetFunctionCmt(0x19db0, 
        "Get battlescene weaponsprite and palette indexes for equipped weapon.\n\
\n\
In: d0.w = combatant index\n\
Out: d2.w = weaponsprite index, d3.w = palette index (-1 if skipped)", 1);

    // GetBattlesceneBackground
    SetFunctionCmt(0x19dfe, 
        "In: d0.w = combatant index\n\
Out: d1.w = battlescene background index", 1);

    // GetBattlesceneGround
    SetFunctionCmt(0x19e6e, 
        "In: d0.w = combatant index\n\
Out: d1.w = battlescene ground index (-1 if skipped)", 1);

    // sub_19E96
    SetFunctionCmt(0x19e96, 
        "Get a boolean depending on background index", 1);

    // SetupSpellanimation
    SetFunctionCmt(0x19ee6, 
        "In: d0.w = spellanimation entry", 1);

    // sub_19FAA
    SetFunctionCmt(0x19faa, 
        "In: a0 = pointer to spellanimation data", 1);

    // sub_1A0C4
    SetFunctionCmt(0x1a0c4, 
        "unused duplicate of the function below", 1);

    // PreserveBasePaletteEntries
    SetFunctionCmt(0x1a0e2, 
        "Preserve UI palette entries #9, #13, and #14 when tinting the screen.", 1);

    // ProduceDarkenedPalettes
    SetFunctionCmt(0x1a100, 
        "Lower brightness of most elements on the screen to 50%.", 1);

    // ProduceDimmedPalettes
    SetFunctionCmt(0x1a122, 
        "Lower the brightness of most elements on the screen to 75%.", 1);

    // ProduceGreyscalePalettes
    SetFunctionCmt(0x1a14a, 
        "Produce a greyscale palette for most elements on the screen.", 1);

    // ProduceBlueMonochromePalettes
    SetFunctionCmt(0x1a19e, 
        "Tint the screen blue.", 1);

    // tint_Blue
    SetFunctionCmt(0x1a1c4, 
        "unused", 1);

    // ProduceGreenMonochromePalettes
    SetFunctionCmt(0x1a1ca, 
        "Tint the screen green.", 1);

    // tint_Green
    SetFunctionCmt(0x1a1f0, 
        "unused", 1);

    // ProduceRedMonochromePalettes
    SetFunctionCmt(0x1a1f6, 
        "Tint the screen red.", 1);

    // tint_Apollo
    SetFunctionCmt(0x1a222, 
        "Tint parts of the screen red when invocating Apollo.", 1);

    // ExecuteSpellcastFlashEffect
    SetFunctionCmt(0x1a2a6, 
        "In: d0.w = color to flash", 1);

    // ClearSpellanimationProperties
    SetFunctionCmt(0x1a2d4, 
        "    Clears a portion at RAM:b406 and RAM:b532 for spell properties.", 1);

    // sub_1A2F6
    SetFunctionCmt(0x1a2f6, 
        "Out: d0.w", 1);

    // LoadInvocationSpell
    SetFunctionCmt(0x1a32c, 
        "code for invocations", 1);

    // spellanimationSetup_OddEyeBeam
    SetFunctionCmt(0x1b716, 
        "and maybe Zynk's beam too ?", 1);

    // sub_1B90C
    SetFunctionCmt(0x1b90c, 
        "related to spellanimations", 1);

    // j_BattleLoop_0
    SetFunctionCmt(0x20038, 
        "unused", 1);

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

    // ReplaceSpellsWithSorcDefaults
    SetFunctionCmt(0x2112c, 
        "In: a6 = church actions stack", 1);

    // Church_GetCurrentForceMemberInfo
    SetFunctionCmt(0x21156, 
        "Out: D7 = force members counter", 1);

    // sub_21A1C
    SetFunctionCmt(0x21a1c, 
        "unused", 1);

    // CountPendingAndReadyToFulfillOrders
    SetFunctionCmt(0x21e48, 
        "Determine whether blacksmith is ready to fulfill orders,\n\
 and count existing orders as either \"ready\" or \"pending\" accordingly.", 1);

    // IsClassBlacksmithEligible
    SetFunctionCmt(0x21e8e, 
        "Is character belonging to class d1.w eligible to place a blacksmith order?\n\
Return d0.w = 0 if true.", 1);

    // DisplaySpecialCaravanDescription
    SetFunctionCmt(0x22864, 
        "Return CCR zero-bit set if special description was found.\n\
(Only used for Chirrup Sandals.)", 1);

    // DisplayCaravanMessageWithPortrait
    SetFunctionCmt(0x228a8, 
        "In: d1.w = message index", 1);

    // CopyCaravanItems
    SetFunctionCmt(0x22926, 
        "Copy caravan item indexes to generic list space", 1);

    // IsItemInSlotEquippedAndCursed
    SetFunctionCmt(0x2294c, 
        "Is item in slot d1.w cursed and equipped by combatant d0.b?\n\
Return CCR carry-bit set if true.", 1);

    // IsItemUnsellable
    SetFunctionCmt(0x2299e, 
        "Is item d1.w unsellable? Return CCR carry-bit set if true.", 1);

    // IsItemUsableOnField
    SetFunctionCmt(0x229ca, 
        "Is item d1.b usable on field? Return d2.l = 0 if true.", 1);

    // UseItemOnField
    SetFunctionCmt(0x229ec, 
        "Find specific item index + code offset to run when used in field.\n\
\n\
      In: d1.w = item entry", 1);

    // GetPlayerEntityPosition
    SetFunctionCmt(0x22c60, 
        "Get first entity's X, Y and facing -> d1.l, d2.l, d3.w", 1);

    // GetBattleMapProperties
    SetFunctionCmt(0x22ce8, 
        "Out: a0 = pointer to movable grid array\n\
     a1 = pointer to start of battle map vdptile layout\n\
     d6.w, d7.w = width, height of battle map", 1);

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
        "Get entity index for combatant d0.w -> d0.w", 1);

    // GetEntityEventIndex
    SetFunctionCmt(0x22f4a, 
        "In: D0 = entity index\n\
Out: D0 = entity event index", 1);

    // sub_23256
    SetFunctionCmt(0x23256, 
        "related to cursor entity", 1);

    // SetCursorDestinationToNextCombatant
    SetFunctionCmt(0x232ac, 
        "In: d0.w = combatant index", 1);

    // SetCursorDestinationToNextBattleEntity
    SetFunctionCmt(0x232bc, 
        "In: d2.w, d3.w = entity X,Y coordinates", 1);

    // UpdateBattleEntityMapsprite
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

    // IsFollowerEntity
    SetFunctionCmt(0x23846, 
        "Is entity d0.b a follower? Return CCR zero-bit set if true.", 1);

    // CheckArea
    SetFunctionCmt(0x23862, 
        "Get item or area description", 1);

    // GetChestGoldAmount
    SetFunctionCmt(0x2399c, 
        "Get amount of gold (d2.w - offset) -> d1.l", 1);

    // BattleLoop
    SetFunctionCmt(0x23a84, 
        "In: d0.b = map index\n\
    d1.b = battle index", 1);

    // CountRemainingCombatants
    SetFunctionCmt(0x23c58, 
        "Count number of allies living, number of enemies living -> d2.w, d3.w", 1);

    // GetEgressPositionForBattle
    SetFunctionCmt(0x23e50, 
        "HARDCODED special cases", 1);

    // ExecuteIndividualTurn
    SetFunctionCmt(0x23eb0, 
        "In: d0.w = combatant index", 1);

    // ProcessAfterTurnEffects
    SetFunctionCmt(0x24242, 
        "Handle after-turn effects (status effects, HP/MP regen/degen, etc.)\n\
\n\
      In: d0.w = combatant index", 1);

    // SpawnEnemyWithCamera
    SetFunctionCmt(0x24490, 
        "In: d0.w = combatant", 1);

    // UpdateTargetsListForCombatant
    SetFunctionCmt(0x24642, 
        "In: d0.w = combatant index", 1);

    // ProcessBattleEntityControlPlayerInput
    SetFunctionCmt(0x24662, 
        "Handle player input when controlling battle entity.", 1);

    // sub_24C4E
    SetFunctionCmt(0x24c4e, 
        "In: A0 = pointer to equippable items list\n\
    D1 = old item index\n\
    D2 = old item slot\n\
    D3 = equippable items count", 1);

    // EquipNewItemInBattle
    SetFunctionCmt(0x24c94, 
        "In: d2.w = old item slot, d4.w = new item slot", 1);

    // PerformAiTargetingVisualAct
    SetFunctionCmt(0x2548e, 
        "- Make actor mapsprite face target\n\
- Move unit cursor from actor to target\n\
- Display mini status windows and play the validation SFX", 1);

    // UpdateAllRegionActivatedEnemiesAi
    SetFunctionCmt(0x2550c, 
        "BUG -- A Goddess Staff is added to the deals section in shops whenever a DEF-CON switch \n\
      is activated, and if one of the following items is also present :\n\
      - Quick Ring\n\
      - Protect Ring\n\
      - White Ring\n\
      - Running Ring\n\
\n\
End function with a RTS intruction to fix", 1);

    // AddCombatantAndRandomizedAgiToTurnOrder
    SetFunctionCmt(0x255a4, 
        "In: a0 = pointer to turn order entry\n\
    d0.w = combatant index", 1);

    // LoadBattle
    SetFunctionCmt(0x25610, 
        "Load all battle properties.\n\
\n\
In: d0.w = combatant index", 1);

    // GetEntityPositionAfterApplyingFacing
    SetFunctionCmt(0x256b2, 
        "In: d0.w = combatant index\n\
Out: d0.w, d1.w = new X, Y", 1);

    // PrintActivatedDefCon
    SetFunctionCmt(0x25772, 
        "if flag D1 is set, AI region active, display def-con textbox", 1);

    // WaitForEvent
    SetFunctionCmt(0x2591c, 
        "Wait for event OR player action (A/C button)", 1);

    // ProcessPlayerAction
    SetFunctionCmt(0x25ad6, 
        "Manage debug actions, entity events, item finds, area descriptions, caravan or main menu", 1);

    // LoadSpecialSprite
    SetFunctionCmt(0x25c24, 
        "In: d1.w = entity mapsprite index", 1);

    // AnimateSpecialSprite
    SetFunctionCmt(0x25cb6, 
        "In: d0.w = 0. Evil Spirit, 1. Evil Spirit (alt.), 2. Zeon", 1);

    // UpdateSpecialSprite
    SetFunctionCmt(0x25cfa, 
        "In: a0 = entity data pointer", 1);

    // DisplaySegaLogo
    SetFunctionCmt(0x2804c, 
        "Out: d0.w = -1 if pressing start, 0 if not", 1);

    // InitializeHuffmanDecoder
    SetFunctionCmt(0x2e10e, 
        "Initialize Huffman decoder.\n\
- clear Huffman (script) data\n\
- set starting tree", 1);

    // j_MapEventType2
    SetFunctionCmt(0x44098, 
        "related to followers maybe", 1);

    // sub_440D4
    SetFunctionCmt(0x440d4, 
        "unused InitializeMapEntities entry point", 1);

    // IsOverworldMap
    SetFunctionCmt(0x44268, 
        "Out: ccr zero-bit clear if true", 1);

    // InitializeFollowerEntities
    SetFunctionCmt(0x44298, 
        "In: a1 = pointer to entity event indexes list in RAM\n\
    a3 = pointer to followers list in RAM\n\
    d0.l = 1", 1);

    // GetEntityEvent
    SetFunctionCmt(0x44536, 
        "In: d0.w = battle entity", 1);

    // DeclareNewEntity
    SetFunctionCmt(0x445ca, 
        "In: d0.w = index\n\
    d1.w = initial X\n\
    d2.w = initial Y\n\
    d3.b = initial facing\n\
    d4.b = mapsprite\n\
    d5.l = actscript address\n\
    d6.w = entity index (lower byte), layer (upper byte)", 1);

    // GetAllyMapsprite
    SetFunctionCmt(0x449c6, 
        "Get mapsprite index for combatant d0.w -> d4.w", 1);

    // GetCombatantMapsprite
    SetFunctionCmt(0x44a7c, 
        "In: a6 = battle vars stack\n\
Out: d4.w = map sprite index", 1);

    // SetEntityActscript
    SetFunctionCmt(0x44b4a, 
        "In: d0.w = entity index", 1);

    // SetControlledEntityActScript
    SetFunctionCmt(0x44b5c, 
        "In: d0.w = entity index", 1);

    // SetCursorEntitySpeedx2
    SetFunctionCmt(0x44b94, 
        "In: d0.w = entity index", 1);

    // SetCursorEntityActscript
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
        "In: d0.w = entity index, d1.w, d2.w, d3.w", 1);

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
        "Get portrait and speech sfx for character entity d0.w -> d1.w, d2.w", 1);

    // OrientSpriteLeft
    SetFunctionCmt(0x45858, 
        "In: a0, a1 = pointer to mapsprite decompressed pixel data in RAM", 1);

    // OrientSpriteRight
    SetFunctionCmt(0x45974, 
        "In: a0, a1 = pointer to mapsprite decompressed pixel data in RAM", 1);

    // ApplySpriteGhostEffect
    SetFunctionCmt(0x45b84, 
        "In: a0, a1 = pointer to mapsprite decompressed pixel data in RAM", 1);

    // ResizeSprite
    SetFunctionCmt(0x45bbe, 
        "In: a0, a1 = pointer to mapsprite decompressed pixel data in RAM", 1);

    // ApplySpriteImmersedEffect
    SetFunctionCmt(0x45c82, 
        "In: a0, a1 = pointer to mapsprite decompressed pixel data in RAM", 1);

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

    // csc51_joinBattleParty
    SetFunctionCmt(0x46f02, 
        "force join to active party", 1);

    // GetEntityAddressFromCharacter
    SetFunctionCmt(0x4704a, 
        "    Get address of entity information. Could be a force member or an opponent\n\
    In: D0 = playable character from FFB140\n\
    Out: A5 = entity info address in RAM", 1);

    // AdjustScriptPointerByCharacterAliveStatus
    SetFunctionCmt(0x47080, 
        "Move script pointer d7.w bytes forward if character is dead.", 1);

    // DmaMapsprite
    SetFunctionCmt(0x4709e, 
        "In: a5 = entity data pointer", 1);

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

    // csc10_toggleFlag
    SetFunctionCmt(0x4747a, 
        "xxxx yyyy", 1);

    // csc13_setStoryFlag
    SetFunctionCmt(0x474e0, 
        "xxxx", 1);

    // sub_474EE
    SetFunctionCmt(0x474ee, 
        "unused", 1);

    // RunMapSetupItemEvent
    SetFunctionCmt(0x47586, 
        "Trigger a map setup function according to up to 4 criterias in d1-d4.\n\
\n\
 In: d1.w, d2.w, d3.w = first entity's X, Y and facing\n\
     d4.w, d5.w = item index, item slot", 1);

    // RunMapSetupEntityEvent
    SetFunctionCmt(0x4761a, 
        "In: D0 = entity event index", 1);

    // sub_476DC
    SetFunctionCmt(0x476dc, 
        "unused", 1);

    // DisplayCurrentPortrait
    SetFunctionCmt(0x476e8, 
        "Get index of current portrait for dialogue window and display it.", 1);

    // GetMapSetupEntityList
    SetFunctionCmt(0x47790, 
        "Returns entity list of map setup in a0.", 1);

    // GetCurrentMapSetup
    SetFunctionCmt(0x4779e, 
        "Returns map setup address in a0.", 1);

    // sub_4781A
    SetFunctionCmt(0x4781a, 
        "reset entity flags and sprite", 1);

    // sub_47832
    SetFunctionCmt(0x47832, 
        "reset entity flags and sprite and facing ?", 1);

    // CheckRandomBattle
    SetFunctionCmt(0x47856, 
        "In: d0.w = battle index", 1);

    // ExecuteBeforeBattleCutscene
    SetFunctionCmt(0x47a50, 
        "cutscene before the battle begins", 1);

    // ExecuteBattleStartCutscene
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
        "Execute cutscenes activated by regions.", 1);

    // csub_JaroJoinForce
    SetFunctionCmt(0x4cd56, 
        "Jaro joins the Force", 1);

    // ReceiveMandatoryItem
    SetFunctionCmt(0x4f48a, 
        "In: d0.w = item index\n\
    d1.w = whether an item must be discarded if inventory is full (0 if false)\n\
\n\
Out: d0.w = 0 if item was received, 1 if there was no room, or 2 if another item was discarded", 1);

    // RemoveItemFromInventory
    SetFunctionCmt(0x4f542, 
        "Out: d0.w = -1 if item was not found", 1);

    // DiscardItem
    SetFunctionCmt(0x4f570, 
        "In: d1.w = item slot, d2.w = item index", 1);

    // Map8_DescFunc6
    SetFunctionCmt(0x562ba, 
        "set after you open the tree in Ribble with the wooden plank", 1);

    // sub_6051E
    SetFunctionCmt(0x6051e, 
        "unused descriptions which look similar to the default ones for map 5", 1);

    // WaitForPlayer1InputStart
    SetFunctionCmt(0x100204, 
        "Wait for max d0.w frames", 1);

    // EndTitleScreen
    SetFunctionCmt(0x10029e, 
        "End title screen if player pressed Start.", 1);

    // sub_1AC024
    SetFunctionCmt(0x1ac024, 
        "AI-related", 1);

    // sub_1AC028
    SetFunctionCmt(0x1ac028, 
        "AI-related", 1);

    // j_IsRegionTriggered
    SetFunctionCmt(0x1ac038, 
        "AI-related", 1);

    // j_GetLaserFacing
    SetFunctionCmt(0x1ac05c, 
        "AI-related", 1);

    // GenerateEndingCreditsFont
    SetFunctionCmt(0x1ac29c, 
        "Generates font from basetile font.\n\
Stretches characters from 1 tile to 2 tiles vertically.\n\
Also creates a shadow effect using palette index 2.", 1);

    // sub_1AC38E
    SetFunctionCmt(0x1ac38e, 
        "AI-related\n\
\n\
Out: d1.b", 1);

    // AdjustObstructionFlagsForAiWithSecondaryCharacteristic1
    SetFunctionCmt(0x1ac43c, 
        "In: d0.w = combatant index", 1);

    // AdjustObstructionFlagsForAiWithSecondaryCharacteristic2
    SetFunctionCmt(0x1ac4f0, 
        "In: d0.w = combatant index", 1);

    // AdjustObstructionFlagsForAiTetheredToLastTarget
    SetFunctionCmt(0x1ac5aa, 
        "In: d0.w = combatant index", 1);

    // ClearBattleTerrainArrayObstructionFlags
    SetFunctionCmt(0x1ac654, 
        "Clear upper two bits from all entries in terrain array.", 1);

    // sub_1AC69A
    SetFunctionCmt(0x1ac69a, 
        "related to AI command : Special Move", 1);

    // sub_1AC728
    SetFunctionCmt(0x1ac728, 
        "AI-related", 1);

    // sub_1AC7FE
    SetFunctionCmt(0x1ac7fe, 
        "AI-related\n\
\n\
  In: a0 = pointer to relative coordinates list\n\
      d5.w,d6.w = X,Y", 1);

    // GetLaserFacing
    SetFunctionCmt(0x1ac8a0, 
        "AI-related", 1);

    // IsRegionTriggered
    SetFunctionCmt(0x1ac9fc, 
        "Is AI region indicated by bit d0.b triggered?\n\
\n\
In: d0.b = region index\n\
Out: d1.w = -1 if true", 1);

    // AreAnyAlliesPositionedWithinRegion
    SetFunctionCmt(0x1aca72, 
        "In: d2.w, d3.w, d4.w = region delimiter coordinates\n\
Out: d6.w = -1 if true", 1);

    // IsAllyPositionedWithinRegion
    SetFunctionCmt(0x1acad6, 
        "In: d2.w, d3.w, d4.w = region delimiter coordinates\n\
    d5.w = combatant coordinates\n\
\n\
Out: d6.w = 0 if true", 1);

    // IsPositionWithinRegion
    SetFunctionCmt(0x1acc26, 
        "In: d1.b-d6.b = coordinates 1, 2, and 3\n\
Out: d0.w = %00 = true, %10 = false", 1);

    // CheckTriggerRegionFlag
    SetFunctionCmt(0x1ace32, 
        "In: d0.b = region index", 1);

    // TriggerRegionsAndActivateEnemies
    SetFunctionCmt(0x1ace4a, 
        "In: d0.w = combatant index", 1);

    // UpdateEnemyActivationIfDead
    SetFunctionCmt(0x1ad002, 
        "In: d0.w = character index\n\
    d4.w = copy character index\n\
\n\
Out: d0.w = 0 if activated and dead, -1 if not", 1);

    // GenerateRandomValueSigned
    SetFunctionCmt(0x1ad090, 
        "Modify the lower byte of RANDOM_SEED_COPY.\n\
\n\
Out: d7.w", 1);

    // GenerateRandomNumberUnderD6
    SetFunctionCmt(0x1ad0b4, 
        "Return 0, or a random number in the range 2, d6.w-1\n\
\n\
Execution takes a variable amount of time, simulating \"thinking\" by the AI.\n\
A copy of RANDOM_SEED is updated during text symbol parsing and diamond menu execution.", 1);

    // BattleDebugFunction1B120A
    SetFunctionCmt(0x1b120a, 
        "Never called, probably what remains of some debugging code ?", 1);

    // InitializeEnemyBattlePosition
    SetFunctionCmt(0x1b130c, 
        "In: d0.b = combatant index", 1);

    // ResetSpawningEnemyStats
    SetFunctionCmt(0x1b13a0, 
        "In: d0.w = combatant index\n\
    d1.w = AI activation bitfield\n\
\n\
Out: CCR carry-bit set if spawn position is occupied", 1);

    // InitializeEnemyStats
    SetFunctionCmt(0x1b140a, 
        "In: a0 = pointer to battle entity definition\n\
    d0.b = combatant index", 1);

    // IsEnemyStartingPositionOccupied
    SetFunctionCmt(0x1b1554, 
        "Is enemy starting position d3.w,d4.w curently occupied?\n\
Return CCR carry-bit set if true.", 1);

    // AdjustEnemyBaseAttForDifficulty
    SetFunctionCmt(0x1b15aa, 
        "Adjust enemy base ATT according to difficulty.\n\
\n\
  In: d0.b = combatant index", 1);

    // GetAiSpecialMoveOrderCoordinates
    SetFunctionCmt(0x1b15f8, 
        "Get coordinates for AI special move order d0.w -> d1.w, d2.w", 1);

    // GetBattleSpritesetSubsection
    SetFunctionCmt(0x1b1630, 
        "In: d1.w = subsection index\n\
Out: a0 = subsection address, d1.w = subsection size", 1);

    // GetCombatantStartingPosition
    SetFunctionCmt(0x1b169e, 
        "Get starting X, Y for combatant d0.b -> d1.w, d2.w", 1);

    // RegionTriggeredSpawn
    SetFunctionCmt(0x1b16fe, 
        "related to player controlled movement on the battlefield\n\
\n\
In: d1.w, d2.w = x, y", 1);

    // IsBattleUpgradable
    SetFunctionCmt(0x1b1780, 
        "Is current battle upgradable? Return d1.w = -1 if true.", 1);

    // UpgradeBattle
    SetFunctionCmt(0x1b17bc, 
        "Strange use case where \"Battle completed\" flag is set for battle 4 in spite of being alreeady set earlier.", 1);

    // DetermineBattleUpgrade
    SetFunctionCmt(0x1b17fe, 
        "Should random battle enemies be upgraded? Return d1.w = 1 if so.", 1);

    // UpgradeRandomBattleEnemies
    SetFunctionCmt(0x1b184c, 
        "Upgrade enemy index d1.w -> d1.w", 1);

    // HasJaroJoinedTheForce
    SetFunctionCmt(0x1b1a28, 
        "Has Jaro joined the Force? Return d1.w = 1 if true.", 1);

}
