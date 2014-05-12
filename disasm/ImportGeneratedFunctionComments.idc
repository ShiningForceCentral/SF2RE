static main()
{
    // Trap0_SoundCommand
    SetFunctionCmt(0x45c, 
        "if xxxx = $FFFF, then get d0.w", 1);

    // Trap6_TriggerAndExecuteMapScript
    SetFunctionCmt(0x57a, 
        "execute map script at a0", 1);

    // relatedToBits031_sub_674
    SetFunctionCmt(0x674, 
        "related to bit0, bit3 and bit1", 1);

    // relatedToBit0_sub_67C
    SetFunctionCmt(0x67c, 
        "executes if bit0 set", 1);

    // relatedToBit4_sub_700
    SetFunctionCmt(0x700, 
        "related to bit4", 1);

    // relatedToBits31_sub_740
    SetFunctionCmt(0x740, 
        "executes if bit3 set or bit1 clear", 1);

    // ParseFadingFX
    SetFunctionCmt(0xaba, 
        "fade subroutine to comment again ;_;", 1);

    // WaitForDMAFree
    SetFunctionCmt(0xb96, 
        "waits for 0xc00004 (VDP DMA register) to be cleared", 1);

    // getVdpRegStatus
    SetFunctionCmt(0xbac, 
        "d0 : vdp reg number", 1);

    // setVdpReg
    SetFunctionCmt(0xbc2, 
        "d0 : vdp reg command", 1);

    // setFFDE94bit1
    SetFunctionCmt(0xc58, 
        "used to execute sub_740", 1);

    // copyPaletteIncomplete
    SetFunctionCmt(0xcc4, 
        "looks like this piece of code is incomplete and useless", 1);

    // WaitForVInt
    SetFunctionCmt(0xeee, 
        "wait until VInt func is called, which clears RAM:def7", 1);

    // Sleep
    SetFunctionCmt(0xf04, 
        "wait for D0 Vints", 1);

    // set_FFDE94_bit0
    SetFunctionCmt(0xf1a, 
        "used to execute sub_67C", 1);

    // setFFDE94b0andWait
    SetFunctionCmt(0xf24, 
        "execute sub_67C", 1);

    // set_FFDE94_bit3
    SetFunctionCmt(0xf2a, 
        "used to execute sub_740", 1);

    // setFFDE94b3andWait
    SetFunctionCmt(0xf34, 
        "set bit 3 of 0xFFDE94 and wait next Vint to execute sub_740", 1);

    // bwahDMAstuffAgainbis
    SetFunctionCmt(0x119e, 
        "d0 = DMA destination ?", 1);

    // sub_134A
    SetFunctionCmt(0x134a, 
        "beforeBwahDMAstuffAgain", 1);

    // DmaVramFill
    SetFunctionCmt(0x140e, 
        "d0:DMA destination - d1:DMA length - d2:sent to VDP Data", 1);

    // WriteAsciiNumber
    SetFunctionCmt(0x14a6, 
        "write D0 into RAM:de80 to D7 places", 1);

    // UpdatePlayerInputs
    SetFunctionCmt(0x150e, 
        "converts data ports 1/2 information into P1/2 inputs State A/B", 1);

    // UpdateRandomSeed
    SetFunctionCmt(0x1600, 
        "randomize a few bits in D7 based on RAM:dea4", 1);

    // GetRandomOrDebugValue
    SetFunctionCmt(0x1674, 
        "another random function taking debug mode into account", 1);

    // playMusicAfterCurrentOne
    SetFunctionCmt(0x16be, 
        "d0 : music index, or previous music if value $FB", 1);

    // copyBytes
    SetFunctionCmt(0x16d6, 
        "    Copy D7 bytes from A0 to A1.\n\
    In: A0 = src address\n\
        A1 = dest address\n\
        D7 = number of bytes to copy", 1);

    // InitSprites
    SetFunctionCmt(0x1770, 
        "In: D0 = number of sprites\n\
\n\
set default values in sprite table", 1);

    // sub_19C8
    SetFunctionCmt(0x19c8, 
        "moves palettes, no idea why", 1);

    // sub_19F8
    SetFunctionCmt(0x19f8, 
        "related to palette updating", 1);

    // loadSpriteData
    SetFunctionCmt(0x1a84, 
        "Basic tile decompression\n\
\n\
    In: A0 = address of compressed data\n\
        A1 = dest address in RAM\n\
", 1);

    // loadTileData
    SetFunctionCmt(0x1e48, 
        "Stack tile decompression\n\
\n\
    In: A0 = address of compressed data\n\
        A1 = dest address in RAM", 1);

    // LoadMapLayoutData
    SetFunctionCmt(0x20e6, 
        "In: A0 = compressed map layout data (block indexes)\n\
    A1 = RAM address to put map layout data", 1);

    // ReadMapLayoutBarrelForBlockFlags
    SetFunctionCmt(0x2296, 
        "Reads next part of barrel to determine flags for next block\n\
barrel = 00\n\
\n\
In: D0 = barrel\n\
Out: D1 = block flag word", 1);

    // sub_2670
    SetFunctionCmt(0x2670, 
        "related to 4 choices apparently", 1);

    // LoadMapTilesets
    SetFunctionCmt(0x29e2, 
        "In: D1 = map index", 1);

    // LoadMap
    SetFunctionCmt(0x2a8c, 
        "loads all map properties (map coords, entities, etc.)", 1);

    // displayBlackScreen
    SetFunctionCmt(0x3022, 
        "or something like that ?", 1);

    // ToggleRoofOnMapLoad
    SetFunctionCmt(0x3f2c, 
        "display (or don't) map roof depending on player's start location", 1);

    // LoadBattleMapMusic
    SetFunctionCmt(0x4544, 
        "overrides music index if we're in a battle", 1);

    // waitForScrollingStop
    SetFunctionCmt(0x4708, 
        "wait for end of scrolling ?", 1);

    // testIfMapScrollingDueToWalking
    SetFunctionCmt(0x4728, 
        "8 = foreground x, 4 = foreground y, 2 = background x, 1 = background y", 1);

    // createWindow
    SetFunctionCmt(0x4802, 
        "d0 = width height, d1 = X Y pos\n\
returns a1 = window tiles end, d0 = window slot", 1);

    // setWindowDestination
    SetFunctionCmt(0x4866, 
        "    startWindowTransition ???\n\
    In: D0 = window number\n\
    Cross: getAddressOfWindowInfo", 1);

    // MoveWindowWithSFX
    SetFunctionCmt(0x48f4, 
        "set window D0's dest to D1 (xxyy) and play window switching sound", 1);

    // MoveWindowWithoutSFX
    SetFunctionCmt(0x48f8, 
        "set window D0's dest to D1 (xxyy)", 1);

    // GetWindowInfo
    SetFunctionCmt(0x4c38, 
        "    Get address in RAM of window info, starting at RAM:a87e.\n\
    In: D0 = window idx\n\
    Out: A0 = address of window info", 1);

    // GetAddressOfWindowTileDataStartingAtCoord
    SetFunctionCmt(0x4c44, 
        "    Get address of specific tile based on coord for a window.\n\
    In: D0 = window idx\n\
        D1 = X/Y coord, stacked into a word\n\
    Out: A1 = address of window coord", 1);

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

    // checkIfSameDestForOtherEntity
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

    // esc0A_
    SetFunctionCmt(0x5a18, 
        "force entity sprite update ?", 1);

    // esc0B_
    SetFunctionCmt(0x5a30, 
        "update FFAF44", 1);

    // esc0C_
    SetFunctionCmt(0x5a3c, 
        "set new pos/dest, clear offset", 1);

    // esc0D_
    SetFunctionCmt(0x5a64, 
        "set same X pos, dest, offset and facing as other entity", 1);

    // scriptCommand_0010
    SetFunctionCmt(0x5ac8, 
        "set entity 1A-1B values with xxxx", 1);

    // sub_5AD4
    SetFunctionCmt(0x5ad4, 
        "set entity 18-19 values with xxxx", 1);

    // sub_5AE0
    SetFunctionCmt(0x5ae0, 
        "set or clear entity value 1C bits 0-1 according to xxxx", 1);

    // sub_5B0E
    SetFunctionCmt(0x5b0e, 
        "set or clear entity value 1C bits 2-3 according to xxxx", 1);

    // esc18_
    SetFunctionCmt(0x5b88, 
        "set or clear entity value 1C bit 7 according to xxxx", 1);

    // esc19_
    SetFunctionCmt(0x5ba2, 
        "set or clear entity value 1C bit 6 according to xxxx", 1);

    // scriptCommand_001A
    SetFunctionCmt(0x5bbc, 
        "set or clear entity value 1C bit 5 according to xxxx", 1);

    // sub_5C3C
    SetFunctionCmt(0x5c3c, 
        "set entity bit 3 of byte $1D", 1);

    // sub_5C56
    SetFunctionCmt(0x5c56, 
        "set entity bit 5 of byte $1D", 1);

    // sub_5C70
    SetFunctionCmt(0x5c70, 
        "set entity bit 4 of byte $1C", 1);

    // esc22_setEntityFacing
    SetFunctionCmt(0x5c8a, 
        "maybe more than just that ?", 1);

    // esc30_branch
    SetFunctionCmt(0x5ca6, 
        "parse from current offset + xxxx", 1);

    // esc41_Pass
    SetFunctionCmt(0x5d48, 
        "directly go to next command 4 bytes forward", 1);

    // esc_clearTimerGoToNextEntity
    SetFunctionCmt(0x5d5a, 
        "clear timer and update next entity", 1);

    // LoadMapEntitySprites
    SetFunctionCmt(0x6024, 
        "load all entities for the current map", 1);

    // changeEntitySprite
    SetFunctionCmt(0x60a8, 
        "a0 : entity address\n\
d6 : facing", 1);

    // GetMapPixelCoordRAMOffset
    SetFunctionCmt(0x61fc, 
        "In: D0 = x pixel coord\n\
    D1 = y pixel coord\n\
Out: D2 = RAM offset from start of map VDP tile data", 1);

    // DisplayText
    SetFunctionCmt(0x6260, 
        "d0 : string index", 1);

    // copyName
    SetFunctionCmt(0x6654, 
        "copy ASCII string of length D7 at A0 to slot for textbox", 1);

    // hideTextBox
    SetFunctionCmt(0x6a38, 
        "related to text box", 1);

    // checkSRAM
    SetFunctionCmt(0x6ea6, 
        "check saves ?", 1);

    // CopyBytesToSRAM
    SetFunctionCmt(0x7004, 
        "a0 = source address\n\
a1 = destination address\n\
d7 = number of bytes to copy", 1);

    // CopyBytesFromSRAM
    SetFunctionCmt(0x701c, 
        "and calculate checksum", 1);

    // sub_7034
    SetFunctionCmt(0x7034, 
        "witch suspend screen ?", 1);

    // MainBattleAndMapLoop
    SetFunctionCmt(0x75c4, 
        "In: D0 = map idx\n\
    D1 = player X coord\n\
    D2 = player Y coord\n\
    D3 = player facing\n\
    D4 = ???\n\
    D7 = battle idx (FFFF for none)\n\
...more", 1);

    // AlterMapIndexIfChanged
    SetFunctionCmt(0x7956, 
        "Alters map index if certain flags are set (Granseal, Pacalon, etc)\n\
In: D0 = map idx\n\
Out: D0 = new map idx", 1);

    // GetNextBattleOnMap
    SetFunctionCmt(0x799c, 
        "In: D0 = map idx (if not supplied, will be pulled from CURRENT_MAP)\n\
    D1 = player X coord to check\n\
    D2 = player Y coord to check\n\
Out: D7 = battle idx to trigger (FFFF if none)\n\
...more", 1);

    // j_GetClass
    SetFunctionCmt(0x8004, 
        "get entity's class index ?", 1);

    // j_IsInBattleParty
    SetFunctionCmt(0x827c, 
        "In: D0 = character idx", 1);

    // j_JoinBattleParty
    SetFunctionCmt(0x8280, 
        "In: D0 = character idx", 1);

    // j_LeaveBattleParty
    SetFunctionCmt(0x8284, 
        "In: D0 = character idx", 1);

    // j_GetMoveInfo
    SetFunctionCmt(0x82bc, 
        "entity D0's current MOV*2, X, Y -> D0, D3, D4", 1);

    // FindCombatantName
    SetFunctionCmt(0x82d0, 
        "In: D0 = combatant entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetEnemyAISetting36
    SetFunctionCmt(0x84b0, 
        "In: D0 = char idx\n\
Out: D1 = high 4 bits\n\
     D2 = low 4 bits", 1);

    // FindName
    SetFunctionCmt(0x8976, 
        "In: A0 = address of names list\n\
    D1 = name idx\n\
Out: A0 = address of entry in names list\n\
     D7 = length of name", 1);

    // FindItemName
    SetFunctionCmt(0x8bd0, 
        "In: D1 = item entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetItemDefAddress
    SetFunctionCmt(0x8be4, 
        "In: D1 = item idx\n\
Out: A0 = item address", 1);

    // GetItemAndNumberOfItems
    SetFunctionCmt(0x8bfa, 
        "In: D0 = entity idx\n\
    D1 = item slot\n\
Out: D1 = item idx\n\
     D2 = number of items held", 1);

    // GetItemType
    SetFunctionCmt(0x8c28, 
        "In: D1 = item idx\n\
Out: D2 = item type (0 = item, 1 = weapon, FFFF = ring)", 1);

    // AddItem
    SetFunctionCmt(0x8ca2, 
        "In: D0 = char idx\n\
    D1 = item entry", 1);

    // BreakItem
    SetFunctionCmt(0x8cd4, 
        "In: D0 = char idx\n\
    D1 = item slot", 1);

    // EquipItemBySlot
    SetFunctionCmt(0x8d34, 
        "In: D0 = char idx\n\
    D1 = item slot idx\n\
Out: D2 = 0 if equipped, 1 if not, 2 if equipped and cursed, 3 if item is nothing", 1);

    // IsItemEquippableAndCursed
    SetFunctionCmt(0x8d6a, 
        "Checks if item is equippable by char D0's class, and whether or not it's a cursed item.\n\
In: D0 = char idx\n\
Out: D2 = 0 if equippable, 1 if not, 2 if equippable and cursed", 1);

    // UnequipItemBySlotIfNotCursed
    SetFunctionCmt(0x8d9e, 
        "In: D0 = char idx\n\
    D1 = item slot idx", 1);

    // IsItemInSlotEquippedAndCursed
    SetFunctionCmt(0x8db6, 
        "In: D0 = char idx\n\
    D1 = item slot idx\n\
Out: D2 = 0 = equipped and cursed, 1 = not equipped, 2 = equipped, 3 = nothing", 1);

    // UnequipItemBySlot
    SetFunctionCmt(0x8dfe, 
        "In: D0 = char idx\n\
    D1 = item slot idx", 1);

    // DropItemBySlot
    SetFunctionCmt(0x8e12, 
        "In: D0 = char idx\n\
    D1 = item slot\n\
Out: D2 = 2 if not dropped, 3 if dropped or nothing", 1);

    // RemoveAndArrangeItems
    SetFunctionCmt(0x8e5c, 
        "In: A0 = char entry address + offset to items\n\
    D0 = item slot", 1);

    // RemoveItemBySlot
    SetFunctionCmt(0x8e76, 
        "In: D0 = char idx\n\
    D1 = item slot", 1);

    // isItemUsableInBattle
    SetFunctionCmt(0x90cc, 
        "carry set : YES", 1);

    // isItemUsableWeaponInBattle
    SetFunctionCmt(0x90e6, 
        "carry set : NO", 1);

    // UnequipAllItemsIfNotCursed
    SetFunctionCmt(0x9106, 
        "In: D0 = char idx", 1);

    // GetItemSlotContainingIndex
    SetFunctionCmt(0x9194, 
        "In: D0 = entity idx\n\
    D1 = item idx\n\
Out: D2 = item slot (FFFF if not held)", 1);

    // FindSpellName
    SetFunctionCmt(0x91c6, 
        "In: D1 = spell entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetSpellDefAddress
    SetFunctionCmt(0x91da, 
        "    Get address of entry in spell definition table.\n\
    In: D1 = spell index\n\
    Out: A0 = address of spell #D1 definition", 1);

    // GetSpellAndNumberOfSpells
    SetFunctionCmt(0x91fa, 
        "In: D0 = entity #\n\
    D1 = spell slot\n\
Out: D1 = spell idx\n\
     D2 = number of spells", 1);

    // getSpellCost
    SetFunctionCmt(0x927e, 
        "    Get MP cost of spell.\n\
    In: D1 = spell index\n\
    Out: D1 = spell MP cost", 1);

    // GetCharEntryAddress
    SetFunctionCmt(0x928e, 
        "In: D0 = char idx\n\
Out: A0 = char RAM address", 1);

    // ClampByteIncreasing
    SetFunctionCmt(0x9312, 
        "clamp byte # D7 of entity D0's information + D1 between D5 and D6", 1);

    // getDistanceBetweenEntities
    SetFunctionCmt(0x941e, 
        "Gets distance between two entities (simple X and Y calculation, no obstructions)\n\
In: D0 = from entity\n\
    D1 = to entity\n\
Out: D2 = distance", 1);

    // initGameSettings
    SetFunctionCmt(0x9844, 
        "Clear all flags and important game variables.", 1);

    // GetFlag
    SetFunctionCmt(0x98e8, 
        "flag bit check pattern based on bit number D1 -> D0", 1);

    // UpdateForce
    SetFunctionCmt(0x9900, 
        "determine who is in the force or not based on flags and update RAM lists", 1);

    // AddItemToDeals
    SetFunctionCmt(0x99ec, 
        "In: D1 = item idx", 1);

    // RemoveItemFromDeals
    SetFunctionCmt(0x9a02, 
        "In: D1 = item idx", 1);

    // GetDealsItemInfo
    SetFunctionCmt(0x9a16, 
        "In: D1 = item idx\n\
Out: A0 = RAM address of deals slot\n\
     D0 = amt to add to deals slot (0x10 or 0x01)\n\
     D2 = number of item idx in deals", 1);

    // AddItemToCaravan
    SetFunctionCmt(0x9a3c, 
        "In: D1 = item idx (only the actual item idx is used, the status bits are cut out)", 1);

    // WriteSkirmishScript
    SetFunctionCmt(0x9b92, 
        "In: D0 = attacker idx", 1);

    // DetermineTargetsByAction
    SetFunctionCmt(0x9dd6, 
        "In: A3 = action data", 1);

    // createBattleSceneText
    SetFunctionCmt(0xa05c, 
        "Loads proper battle scene text script depending on attack action.\n\
In: A3 = RAM index containing action type\n\
    A4 = RAM index containing attacker index", 1);

    // createBattleSceneAnimation
    SetFunctionCmt(0xa200, 
        "    Loads proper battle scene sprite/magic animation properties.\n\
    In: A3 = ", 1);

    // GetEffectGraphicsIdx
    SetFunctionCmt(0xa54e, 
        "In: A2 = cutscene stack\n\
    A3 = battle action in RAM\n\
Out: D4 = effect idx", 1);

    // WriteSkirmishScript_AnimateSprite
    SetFunctionCmt(0xa6e8, 
        "    Loads proper battle scene sprite animation properties.\n\
    In: D4 = projectile\n\
        D5 = special script idx", 1);

    // getAmountOfEXPForEncounter
    SetFunctionCmt(0xa968, 
        "Gets amount of EXP gained from encounter based on attacker level and target level.\n\
In: A4 = address of attacker byte in RAM\n\
    A5 = address of target byte in RAM\n\
Out: D5 = amount of EXP", 1);

    // CalculateDamage
    SetFunctionCmt(0xabbe, 
        "In: A4 = attacker index in RAM\n\
    A5 = defender index in RAM\n\
Out: D6 = damage", 1);

    // alterSpellPotency
    SetFunctionCmt(0xbb56, 
        "    Miscellaneous hacks to alter spell damage. (125% if promoted, damage divided if SORC spells)\n\
    In: D6 = original damage\n\
    Out: D6 = altered damage", 1);

    // GetItemBreakMessage
    SetFunctionCmt(0xbc9a, 
        "In: A2 = skirmish properties stack\n\
    D0 = whether item is already damaged (0=no, 1=yes)\n\
Out: D3 = message idx", 1);

    // convertCoordToOffset
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

    // getTargetAtCoordOffset
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

    // getTerrainAtCoordOffset
    SetFunctionCmt(0xc160, 
        "    Get obstruction at converted coordinate offset.\n\
    In: D1 = X coord\n\
        D2 = Y coord\n\
    Out: D0 = target at offset", 1);

    // setMovableAtCoord
    SetFunctionCmt(0xc204, 
        "    Set coord to movable in movable grid.\n\
    In: D1 = X coord\n\
        D2 = Y coord", 1);

    // getResistanceToSpell
    SetFunctionCmt(0xc22a, 
        "    Get resistance to spell of combatant.\n\
    In: D0 = combatant idx\n\
        D1 = spell idx\n\
    Out: D2 = resistance bitmask", 1);

    // GetMoveInfo
    SetFunctionCmt(0xc2c8, 
        "entity D0's current MOV*2, X, Y -> D0, D3, D4", 1);

    // GetWeaponRange
    SetFunctionCmt(0xc306, 
        "get index and max/min range of current character's current weapon (D1,D3,D4)", 1);

    // CheckMuddled2
    SetFunctionCmt(0xc3b0, 
        "In: D0 = combatant entry\n\
Out: D1 = whether combatant is inflicted with MUDDLE 2", 1);

    // CreateItemRangeGrid
    SetFunctionCmt(0xc44c, 
        "In: D0 = item user\n\
    D1 = item idx", 1);

    // createSpellRangeGrid
    SetFunctionCmt(0xc478, 
        "    Clear and update target/movable grids based on spell properties.\n\
    In: D0 = spell user\n\
        D1 = spell idx", 1);

    // applyRelativeCoordListToGrids
    SetFunctionCmt(0xc510, 
        "    Apply coord list at A0 and add any targets to target list.\n\
    In: A0 = address of relative coord list\n\
        D0 = current entity idx\n\
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
        "    Clear target grid, then add allies.", 1);

    // GetHighestUsableSpellLevel
    SetFunctionCmt(0xced2, 
        "Get highest usable level of spell D1, considering current MP and highest known level.\n\
In: D0 = combatant idx\n\
    D1 = spell idx\n\
Out: D1 = spell idx", 1);

    // GetSlotContainingSpell
    SetFunctionCmt(0xcf0e, 
        "In: D0 = combatant idx\n\
    D1 = spell idx\n\
Out: D1 = spell idx\n\
     D2 = slot", 1);

    // GetSlotContainingItem
    SetFunctionCmt(0xcf40, 
        "In: D0 = combatant idx\n\
    D1 = item idx\n\
Out: D1 = item idx\n\
     D2 = slot", 1);

    // GetNextHealingSpell
    SetFunctionCmt(0xd018, 
        "Get next healing spell known by combatant.\n\
In: D0 = entity #\n\
    D3 = starting spell slot\n\
Out: D1 = spell idx\n\
     D2 = spell slot", 1);

    // GetNextUsableAttackItem
    SetFunctionCmt(0xd0ac, 
        "Get the next item in combatant's inventory that can be used to cast BLAZE/FREEZE/BOLT/BLAST.\n\
<HARDCODED>\n\
In: D0 = combatant idx\n\
    D3 = starting item slot\n\
Out: D1 = item idx\n\
     D2 = item slot", 1);

    // GetNextUsableHealingItem
    SetFunctionCmt(0xd160, 
        "Get the next item in combatant's inventory that can be used to cast a healing spell.\n\
<HARDCODED>\n\
In: D0 = combatant idx\n\
    D3 = starting item slot\n\
Out: D1 = item idx\n\
     D2 = item slot", 1);

    // AddAllToStack
    SetFunctionCmt(0xdd60, 
        "unused, pointless", 1);

    // MakeEnemyMoveOrder
    SetFunctionCmt(0xdd78, 
        "create enemy move order from movecost lists", 1);

    // sub_100B4
    SetFunctionCmt(0x100b4, 
        "related to end kiss", 1);

    // sub_100C8
    SetFunctionCmt(0x100c8, 
        "write from ascii but with FFFF value instead of 0, hmm ...", 1);

    // WriteTilesFromNumber
    SetFunctionCmt(0x100d4, 
        "write tiles from number in D0 into A1 D7 letters, window width D1", 1);

    // WriteTilesFromASCII
    SetFunctionCmt(0x100e2, 
        "write tiles from ASCII from A0 into A1 D7 letters, window width D1\n\
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
    D2 = menu idx to use (just affects icons and text)", 1);

    // LoadDiamenuWindowVDPTileData
    SetFunctionCmt(0x103b8, 
        "In: -$C(A6) = window slot idx", 1);

    // loadIHighlightableSpellIcon
    SetFunctionCmt(0x10940, 
        "    Copy spell icon to RAM.\n\
    In: A1 = dest in RAM\n\
        D0 = spell idx\n\
    Out: A1 = end of affected section after copy", 1);

    // sub_11862
    SetFunctionCmt(0x11862, 
        "write one column of HP/MP bar pixels into A1", 1);

    // adjustStringLengthForSpecialChars
    SetFunctionCmt(0x11898, 
        "check ASCII name at A0 for two special chars ???\n\
", 1);

    // WriteStatValue
    SetFunctionCmt(0x11aae, 
        "display d0 stat value or \"??\" if above 99", 1);

    // copyFighterMinistatusWindowTileColumn
    SetFunctionCmt(0x11ac6, 
        "draw tiles from A0 into A1 (one column)", 1);

    // memberStatsScreen
    SetFunctionCmt(0x11c2a, 
        "Create and display member stats screen\n\
\n\
In: D0 = character idx", 1);

    // AddStatusEffectTileIndexesToVDPTileOrder
    SetFunctionCmt(0x11eea, 
        "In: A1 = address of VDP tile order in RAM", 1);

    // getPortraitIdx
    SetFunctionCmt(0x1263a, 
        "    Get index of portrait based on char index for any character.\n\
    In: D0 = char idx\n\
    Out: D0 = adjusted portrait idx", 1);

    // sub_12DEC
    SetFunctionCmt(0x12dec, 
        "related to end kiss", 1);

    // loadCharPortrait
    SetFunctionCmt(0x13394, 
        "    In: D0 = char idx", 1);

    // getSelectedMember
    SetFunctionCmt(0x13462, 
        "    Get index of currently selected force member (in menus).\n\
    Out: D0 = selected index (capped to 255)", 1);

    // sub_14BB0
    SetFunctionCmt(0x14bb0, 
        "copy item icon tiles into RAM based on index list at RAM:b0ae", 1);

    // sub_14C56
    SetFunctionCmt(0x14c56, 
        "copy shop price tag pixels to A0 in RAM", 1);

    // sub_14CB2
    SetFunctionCmt(0x14cb2, 
        "copy item # D1 icon pixels to A0 in RAM", 1);

    // sub_14CEC
    SetFunctionCmt(0x14cec, 
        "get current item idx in shop/caravan (from index list) -> D0", 1);

    // sub_15422
    SetFunctionCmt(0x15422, 
        "d0 = FFAFE7, related to DMA", 1);

    // VInt_HandlePortraitBlinking
    SetFunctionCmt(0x15534, 
        "must be related to portrait display", 1);

    // updatePortrait
    SetFunctionCmt(0x155c4, 
        "d1 = alternate/original, d7 = tile number", 1);

    // loadPortrait
    SetFunctionCmt(0x1562a, 
        "    In: D0 = portrait idx", 1);

    // getCharPortraitIdx
    SetFunctionCmt(0x15736, 
        "    Get index of portrait based on char index for force members.\n\
    In: D0 = char idx\n\
    Out: D0 = adjusted portrait idx", 1);

    // executeBattlesceneScript
    SetFunctionCmt(0x18398, 
        "battlescene scripting ?", 1);

    // bsc00_animateEnemyAction
    SetFunctionCmt(0x183f4, 
        "xx      animation type index (0000 for attack, 0001 for dodge, 0002 for magic/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)\n\
yy      magic/item/projectile animation idx, set 0x0080 to come from enemy", 1);

    // bsc01_animateAllyAction
    SetFunctionCmt(0x184e8, 
        "xx      animation type index (0000 for attack, 0001 for dodge, 0002 for magic/item -- others (i.e. MMNK crit, RBT laser, BRGN flashing)\n\
yy      magic/item/projectile animation idx, set 0x0080 to come from enemy", 1);

    // bsc03_moveAllyBSprite
    SetFunctionCmt(0x185c8, 
        "like previous bsc but for battlescene ally", 1);

    // bsc02_moveEnemyBSprite
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
        "xx      Character index.\n\
yy      0000 for right side, 0001 for left side", 1);

    // bsc06_switchEnemies
    SetFunctionCmt(0x1893e, 
        "xx      Character index.\n\
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

    // makeActorIdle
    SetFunctionCmt(0x195e2, 
        "make actor idle", 1);

    // AddEnemyToDeadList
    SetFunctionCmt(0x197a6, 
        "add enemy to dead combatant list", 1);

    // GetAllyBattleSpriteIdleAnimate
    SetFunctionCmt(0x19860, 
        "Returns whether or not ally bsprite should animate when idle.\n\
In: D0 = ally bsprite idx\n\
Out: D1 = 0 if animates, 1 if not", 1);

    // GetEnemyBattleSpriteIdleAnimate
    SetFunctionCmt(0x1986a, 
        "Returns whether or not enemy bsprite should animate when idle.\n\
In: D0 = enemy bsprite idx\n\
Out: D1 = 0 if animates, 1 if not", 1);

    // sub_19884
    SetFunctionCmt(0x19884, 
        "clears plt 1-2 and 1-2bis, sets plt 3bis", 1);

    // LoadPaletteForBattleScene
    SetFunctionCmt(0x199de, 
        "load palette D1 of battle sprite D0", 1);

    // loadBattleSpriteData
    SetFunctionCmt(0x19a0c, 
        "    In: D0 = battle sprite idx\n\
        D1 = frame idx", 1);

    // sub_19A5C
    SetFunctionCmt(0x19a5c, 
        "???\n\
In: D0 = weapon sprite idx", 1);

    // loadEnemyBattleSprite
    SetFunctionCmt(0x19b44, 
        "d0 : battle sprite index", 1);

    // loadSpellAnimationGraphics
    SetFunctionCmt(0x19ca4, 
        "    Loads spell animation tiles.\n\
    In: D0 = spell animation tileset index", 1);

    // getBattleSpriteAndPalette
    SetFunctionCmt(0x19d3e, 
        "get battle sprite # and palette # for character related to entity D0 -> D1 (sprite), D2 (palette)", 1);

    // getWeaponSpriteAndPalette
    SetFunctionCmt(0x19db0, 
        "get battle sprite # and palette # for entity D0's equipped weapon -> D2 (sprite), D3 (palette)", 1);

    // executeSpellAnimation
    SetFunctionCmt(0x19ee6, 
        "spell animation subroutine", 1);

    // execSpellAnimationFlash
    SetFunctionCmt(0x1a2a6, 
        "    In: D0 = color to flash", 1);

    // clearSpellAnimationProperties
    SetFunctionCmt(0x1a2d4, 
        "    Clears a portion at RAM:b406 and RAM:b532 for spell properties.", 1);

    // sub_1A32C
    SetFunctionCmt(0x1a32c, 
        "code for invocations", 1);

    // boltAnimation
    SetFunctionCmt(0x1ce50, 
        "looks related to BOLT", 1);

    // j_CaravanActions
    SetFunctionCmt(0x20010, 
        "seems related to caravan", 1);

    // FindPromotionSection
    SetFunctionCmt(0x2110c, 
        "In: D2 = section type (regpre, regpost, specpre, specpost, specitem)\n\
Out: A0 = address", 1);

    // sub_219EC
    SetFunctionCmt(0x219ec, 
        "copy available targets list ?", 1);

    // CaravanActions
    SetFunctionCmt(0x21fd2, 
        "seems related to caravan", 1);

    // sub_228A8
    SetFunctionCmt(0x228a8, 
        "textbox?", 1);

    // sub_22926
    SetFunctionCmt(0x22926, 
        "copy item idxes of caravan items to index list", 1);

    // sub_2294C
    SetFunctionCmt(0x2294c, 
        "get whether character D0's item at slot D1 is cursed -> carry", 1);

    // sub_229EC
    SetFunctionCmt(0x229ec, 
        "initiates the level up process ?", 1);

    // sub_22AAE
    SetFunctionCmt(0x22aae, 
        "boost attack ?", 1);

    // sub_22AD6
    SetFunctionCmt(0x22ad6, 
        "boost def ?", 1);

    // sub_22AFE
    SetFunctionCmt(0x22afe, 
        "boost agi ?", 1);

    // sub_22B26
    SetFunctionCmt(0x22b26, 
        "boost mov ?", 1);

    // sub_22C60
    SetFunctionCmt(0x22c60, 
        "get first entity's X, Y and facing", 1);

    // CreateMoveableRangeForUnit
    SetFunctionCmt(0x22c84, 
        "    Update some map stuff ???", 1);

    // ControlBattleUnit
    SetFunctionCmt(0x22e1a, 
        "Out: D4 = copied P1 input state bitfield", 1);

    // getCombatantNumberOfEntity
    SetFunctionCmt(0x22f30, 
        "    Convert entity number to combatant number.\n\
    In: D0 = entity number\n\
    Out: D0 = combatant number", 1);

    // GetEntityEventIdx
    SetFunctionCmt(0x22f4a, 
        "In: D0 = entity idx\n\
Out: D0 = entity event idx", 1);

    // SetEntityVspeedBit7
    SetFunctionCmt(0x2345a, 
        "is it vertical speed ?", 1);

    // ClearEntityVspeedBit7
    SetFunctionCmt(0x23474, 
        "is it vertical speed ?", 1);

    // SetEntityPosition
    SetFunctionCmt(0x2376a, 
        "In: D0 = entity idx\n\
    D1 = x pos\n\
    D2 = y pos", 1);

    // GetActivatedEntity
    SetFunctionCmt(0x2379a, 
        "Out: D0 = activated entity idx\n\
     D1 = activated entity's facing\n\
     D2 = player entity's facing", 1);

    // CheckIfEntityIsFollower
    SetFunctionCmt(0x23846, 
        "In: D0 = entity idx\n\
Out: Z = entity is NOT follower", 1);

    // getGoldAmount
    SetFunctionCmt(0x2399c, 
        "get amount of gold (D2 - 0x80) as an offset from the gold table (see constants)", 1);

    // ExecuteBattleLoop
    SetFunctionCmt(0x23a84, 
        "In: D0 = map idx\n\
    D1 = battle idx", 1);

    // GetRemainingFighters
    SetFunctionCmt(0x23c58, 
        "number of force members living, number of enemies living -> D2, D3", 1);

    // sub_23EB0
    SetFunctionCmt(0x23eb0, 
        "In: D0 = char idx", 1);

    // HandleAfterTurnEffects
    SetFunctionCmt(0x24242, 
        "handle after-turn effects (status effects, HP/MP regen/degen, etc)", 1);

    // SpawnEnemySkipCamera
    SetFunctionCmt(0x2448a, 
        "?", 1);

    // sub_24966
    SetFunctionCmt(0x24966, 
        "    createSpellRangeGridMaster???", 1);

    // AddRandomizedAGIToTurnOrder
    SetFunctionCmt(0x255a4, 
        "In: A0 = turn order in RAM\n\
    D0 = char idx    ", 1);

    // LoadBattle
    SetFunctionCmt(0x25610, 
        "load all battle properties", 1);

    // PrintActivatedDefCon
    SetFunctionCmt(0x25772, 
        "if flag D1 is set, display def-con textbox", 1);

    // sub_2594A
    SetFunctionCmt(0x2594a, 
        "deal with \"system\" event (RAM:a84a)", 1);

    // SetBattleVIntFuncs
    SetFunctionCmt(0x25a94, 
        "init vint contextual functions", 1);

    // endGame
    SetFunctionCmt(0x279d8, 
        "need to verify", 1);

    // sub_4401C
    SetFunctionCmt(0x4401c, 
        "set entity D0's movescript to 0x460ce (default? don't move?)", 1);

    // sub_44098
    SetFunctionCmt(0x44098, 
        "related to followers maybe", 1);

    // clearEntities
    SetFunctionCmt(0x4465a, 
        "clear entities in memory", 1);

    // getCharacterSpriteIdx
    SetFunctionCmt(0x449c6, 
        "In: D0 = char idx\n\
Out: D4 = sprite idx\n\
\n\
wtf I need to figure out that implementation, many strange exceptions", 1);

    // GetCombatantSpriteIdx
    SetFunctionCmt(0x44a7c, 
        "In: A6 = battle vars stack ???\n\
Out: D4 = sprite idx", 1);

    // sub_44C02
    SetFunctionCmt(0x44c02, 
        "set entity D0's movescript to 0x460ce (default? don't move?)", 1);

    // getEntityAddress
    SetFunctionCmt(0x44dd8, 
        "location in memory of entity # D0 -> A0", 1);

    // waitForFollowersStopped
    SetFunctionCmt(0x45204, 
        "still to confirm", 1);

    // waitForHeroAndFollowersStopped
    SetFunctionCmt(0x4520e, 
        "to confirm", 1);

    // waitForPartyEntitiesIdle
    SetFunctionCmt(0x45218, 
        "to confirm", 1);

    // applyActscriptToHeroAndFollowers
    SetFunctionCmt(0x4524c, 
        "might be related to followers", 1);

    // applyActscriptToFollowers
    SetFunctionCmt(0x45254, 
        "to confirm", 1);

    // GetEntityPortraitAndSpeechSound
    SetFunctionCmt(0x45638, 
        "In: D0 = entity idx\n\
Out: D1 = portrait idx\n\
     D2 = speech sound idx", 1);

    // sub_4658E
    SetFunctionCmt(0x4658e, 
        "related to loading a map", 1);

    // csc45_
    SetFunctionCmt(0x46700, 
        "related to camera adjust to lpayer", 1);

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
        "if character xxxx dead, then do it to entity yyyy ?!", 1);

    // csc1C_stopEntityAnim
    SetFunctionCmt(0x46a82, 
        "if character xxxx dead, then do it to entity yyyy ?!", 1);

    // csc1F_addForceMemberToList
    SetFunctionCmt(0x46ade, 
        "set some value in RAM", 1);

    // csc20_addForceMembersOnMapToList
    SetFunctionCmt(0x46af0, 
        "related to same ram values", 1);

    // csc21_removeForceMemberFromList
    SetFunctionCmt(0x46b1a, 
        "related to same ram values", 1);

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

    // sub_47008
    SetFunctionCmt(0x47008, 
        "xx character", 1);

    // getEntityAddressFromPlayableCharacterIdx
    SetFunctionCmt(0x4704a, 
        "    Get address of entity information. Could be a force member or an opponent\n\
    In: D0 = playable character from FFB140\n\
    Out: A5 = entity info address in RAM", 1);

    // adjustScriptPointerByCharAliveStatus
    SetFunctionCmt(0x47080, 
        "move script pointer d7 forward if character dead", 1);

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

    // csc0F_jumpIfCharacterDead
    SetFunctionCmt(0x47464, 
        "xxxx yyyyyyyy", 1);

    // csc10_setOrClearFlag
    SetFunctionCmt(0x4747a, 
        "xxxx yyyy", 1);

    // csc13_setStoryFlag
    SetFunctionCmt(0x474e0, 
        "xxxx", 1);

    // ExecuteEntityEvent
    SetFunctionCmt(0x4761a, 
        "In: D0 = entity event idx", 1);

    // LoadAndDisplayCurrentPortrait
    SetFunctionCmt(0x476e8, 
        "    Get index of current portrait for textbox and load it.", 1);

    // getMapSetupEntityList
    SetFunctionCmt(0x47790, 
        "returns entity list of map setup in a0", 1);

    // getCurrentMapSetup
    SetFunctionCmt(0x4779e, 
        "returns map setup address in a0", 1);

    // j_ExecuteBattleCutscene_Intro_0
    SetFunctionCmt(0x47a50, 
        "cutscene before the battle begins", 1);

    // ExecuteBattleCutscene_Start
    SetFunctionCmt(0x47aee, 
        "cutscene at the start of battle (after units are placed and battle officially begins)\n\
\n\
only seems to happen in first \"above Pacalon\" battle", 1);

    // ExecuteBattleCutscene_Region
    SetFunctionCmt(0x47e82, 
        "executes cutscenes activated by regions", 1);

    // WaitForPlayer1InputStart
    SetFunctionCmt(0x100204, 
        "wait during d0 frames", 1);

    // sub_1AC4F0
    SetFunctionCmt(0x1ac4f0, 
        "something with targetting grid or ???", 1);

    // clearTerrainListObstructions
    SetFunctionCmt(0x1ac654, 
        "clear upper two bits from all tiles in terrain list", 1);

    // CheckTriggerRegionFlag
    SetFunctionCmt(0x1ace32, 
        "In: D1 = region #", 1);

    // GetListOfSpawningEnemies
    SetFunctionCmt(0x1acf30, 
        "adds respawning enemy #s to target list in RAM", 1);

    // UpdateEnemyActivationIfDead
    SetFunctionCmt(0x1ad002, 
        "In: D0 = char idx\n\
    D4 = char idx (same as D0)\n\
Out: D0 = 0000 if activated and dead, FFFF if not", 1);

    // LoadBattleTerrainData
    SetFunctionCmt(0x1ad0dc, 
        "loads terrain data for current battle", 1);

    // InitEnemyBattlePosition
    SetFunctionCmt(0x1b130c, 
        "(also checks for Jaro)", 1);

    // UpdateEnemyStatsForRespawn
    SetFunctionCmt(0x1b13a0, 
        "In: D0 = char idx\n\
    D1 = char word 34 (AI stuff)\n\
Out: carry = 0 if respawn, 1 if not", 1);

    // InitEnemyStats
    SetFunctionCmt(0x1b140a, 
        "In: A0 = address of current combatant from battle def", 1);

    // sub_1B1504
    SetFunctionCmt(0x1b1504, 
        "handle custom item idx of monster list entry starting at A0 -> ???", 1);

    // GetEnemyOriginalPosOccupied
    SetFunctionCmt(0x1b1554, 
        "In: D3 = enemy starting tile x (from battle def)\n\
    D4 = enemy starting tile y (from battle def)\n\
Out: carry = if anyone is on D3/D4", 1);

    // setEnemyBaseATK
    SetFunctionCmt(0x1b15aa, 
        "sets Enemy ATK according to difficulty", 1);

    // getEnemyAITargetPos
    SetFunctionCmt(0x1b15f8, 
        "coords of anchor point used in AI byte D0 -> D1, D2", 1);

    // getAddrOfBattleDataSection
    SetFunctionCmt(0x1b1630, 
        "get address of subsection D1 (list sizes, force defs, enemy defs, region defs, point defs) of current battle -> A0\n\
      \n\
                    if D1 = 2, size of monster list -> D1", 1);

    // GetMonsterStartPos
    SetFunctionCmt(0x1b169e, 
        "starting X and Y of monster (D0 - 0x80) -> D1, D2", 1);

    // DoesBattleUpgrade
    SetFunctionCmt(0x1b1780, 
        "check if battle can be upgraded based on index in RAM:f712 (0x0000=no, 0xffff=yes) -> D1", 1);

    // ShouldBattleUpgrade
    SetFunctionCmt(0x1b17fe, 
        "check if battle should be upgraded based on index in RAM:f712 and if normal battle was done (0=no, 1=yes) -> D1", 1);

    // UpgradeUnitIdx
    SetFunctionCmt(0x1b184c, 
        "In: D1 = original unit idx\n\
Out: D1 = upgraded unit idx", 1);

}
