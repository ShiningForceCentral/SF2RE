static main()
{
    // Trap0_SoundCommand
    SetFunctionCmt(0x45c, 
        "if xxxx = $FFFF, then get d0.w", 1);

    // Trap6_TriggerAndExecuteMapScript
    SetFunctionCmt(0x57a, 
        "execute map script at a0", 1);

    // ApplyVIntCramDMA
    SetFunctionCmt(0xc80, 
        "VDP CRAM", 1);

    // sub_CC4
    SetFunctionCmt(0xcc4, 
        "Unused palette copy", 1);

    // sub_E7C
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

    // ApplyImmediateVramDMA
    SetFunctionCmt(0x10dc, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // ApplyVIntVramDMA
    SetFunctionCmt(0x119e, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // sub_1234
    SetFunctionCmt(0x1234, 
        "unused", 1);

    // UpdateVDPVScrollData
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

    // ApplyImmediateVramDMAOnCompressedTiles
    SetFunctionCmt(0x1382, 
        "A0=Source, A1=Destination, D0=Length, D1=Auto-increment", 1);

    // sub_13C0
    SetFunctionCmt(0x13c0, 
        "unused DMA code", 1);

    // sub_13E4
    SetFunctionCmt(0x13e4, 
        "unused DMA code", 1);

    // DMAandWait
    SetFunctionCmt(0x1408, 
        "unused", 1);

    // ApplyVramDMAFill
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
        "In: D6=Value range, Out: D7=Random value", 1);

    // GetRandomOrDebugValue
    SetFunctionCmt(0x1674, 
        "input D0=value range\n\
output D0=random value\n\
debug mode allows values 0-3 depending on player direction", 1);

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

    // MoveWindowWithSFX
    SetFunctionCmt(0x48f4, 
        "D0=Windows index, D1=Destination, D2=Anim max", 1);

    // MoveWindow
    SetFunctionCmt(0x48f8, 
        "D0=Windows index, D1=Destination, D2=Anim max", 1);

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

    // GetMapPixelCoordRAMOffset
    SetFunctionCmt(0x61fc, 
        "In: D0 = x pixel coord\n\
    D1 = y pixel coord\n\
Out: D2 = RAM offset from start of map VDP tile data", 1);

    // DisplayText
    SetFunctionCmt(0x6260, 
        "d0 : string index", 1);

    // CopyASCIIBytesForDialogueString
    SetFunctionCmt(0x6654, 
        "copy ASCII string of length D7 at A0 to RAM for dialogue textbox", 1);

    // CopyLineOfVDPTileOrderForDialogueWindowToRAM
    SetFunctionCmt(0x6860, 
        "In: A1 - address in RAM to copy VDP tile idxes\n\
    D0 - VDP tile idx for left border of line\n\
    D1 - VDP tile idx for first inner box tile of line\n\
    D2 - VDP tile idx for right border of line\n\
    D3 - amount to add to D1 each time a tile is copied (0 for top and bottom border lines, 1 for inner box)", 1);

    // HideTextBox
    SetFunctionCmt(0x6a38, 
        "related to text box", 1);

    // CopyBytesToSRAM
    SetFunctionCmt(0x7004, 
        "a0 = source address\n\
a1 = destination address\n\
d7 = number of bytes to copy", 1);

    // CopyBytesFromSRAM
    SetFunctionCmt(0x701c, 
        "and calculate checksum", 1);

    // WitchSuspend
    SetFunctionCmt(0x7034, 
        "witch suspend screen", 1);

    // MainLoop
    SetFunctionCmt(0x75c4, 
        "In: D0 = map idx\n\
    D1 = player X coord\n\
    D2 = player Y coord\n\
    D3 = player facing\n\
    D4 = ???\n\
    D7 = battle idx (FFFF for none)\n\
...more", 1);

    // GetSavePointForMap
    SetFunctionCmt(0x75ec, 
        "In: D0 = from map idx\n\
Out: D0 = to map idx\n\
     D1 = X\n\
     D2 = Y\n\
     D3 = facing", 1);

    // CheckMapSwitch
    SetFunctionCmt(0x7956, 
        "Alters map index if certain flags are set (Granseal, Pacalon, etc)\n\
In: D0 = map idx\n\
Out: D0 = new map idx", 1);

    // CheckBattle
    SetFunctionCmt(0x799c, 
        "In: D0 = map idx (if not supplied, will be pulled from CURRENT_MAP)\n\
    D1 = player X coord to check\n\
    D2 = player Y coord to check\n\
Out: D7 = battle idx to trigger (FFFF if none)\n\
...more", 1);

    // UpdateWitchLayoutZone
    SetFunctionCmt(0x7d28, 
        "D1=Width/Height", 1);

    // j_GetClass
    SetFunctionCmt(0x8004, 
        "get entity's class index ?", 1);

    // j_GetCharacterWord34
    SetFunctionCmt(0x8064, 
        "related to AI control on 0x0004 ?", 1);

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

    // GetCharName
    SetFunctionCmt(0x82d0, 
        "In: D0 = char idx\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetEnemyAISetting36
    SetFunctionCmt(0x84b0, 
        "In: D0 = char idx\n\
Out: D1 = high 4 bits\n\
     D2 = low 4 bits", 1);

    // SetKills
    SetFunctionCmt(0x86e6, 
        "actually seems to only be used for monster AI, not kills", 1);

    // SetDefeats
    SetFunctionCmt(0x86fe, 
        "actually seems to only be used for monster AI, not kills", 1);

    // FindName
    SetFunctionCmt(0x8976, 
        "In: A0 = address of names list\n\
    D1 = name idx\n\
Out: A0 = address of entry in names list\n\
     D7 = length of name", 1);

    // ApplyMagicOnStats
    SetFunctionCmt(0x8a26, 
        "In: D0 = char index\n\
    D3 = status bitfield", 1);

    // ApplyItemOnStats
    SetFunctionCmt(0x8a90, 
        "In: A2 = address in RAM of char's prowess\n\
    D0 = char idx\n\
    D1 = item idx", 1);

    // FindItemName
    SetFunctionCmt(0x8bd0, 
        "In: D1 = item entry\n\
Out: A0 = address of name\n\
     D7 = length of name", 1);

    // GetItemDefAddress
    SetFunctionCmt(0x8be4, 
        "In: D1 = item idx\n\
Out: A0 = item definition address in ROM", 1);

    // GetCharItemAtSlotAndNumberOfItems
    SetFunctionCmt(0x8bfa, 
        "In: D0 = char entry idx\n\
    D1 = item slot idx\n\
Out: D1 = item idx\n\
     D2 = number of items held", 1);

    // GetItemType
    SetFunctionCmt(0x8c28, 
        "In: D1 = item idx\n\
Out: D2 = item type (0 = item, 1 = weapon, FFFF = ring)", 1);

    // AddItem
    SetFunctionCmt(0x8ca2, 
        "In: D0 = char idx\n\
    D1 = item entry\n\
OUT : D2 = set if not slot available", 1);

    // BreakItem
    SetFunctionCmt(0x8cd4, 
        "In: D0 = char idx\n\
    D1 = item slot", 1);

    // EquipItemBySlot
    SetFunctionCmt(0x8d34, 
        "In: D0 = char entry idx\n\
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
Out: A0 = address of char entry item slot idx in RAM\n\
     D2 = 0 = equipped and cursed, 1 = not equipped, 2 = equipped, 3 = nothing", 1);

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

    // IsItemEquippable
    SetFunctionCmt(0x8f60, 
        "In: D1 = item idx\n\
    D2 = item type bitmask (for ANDing the item type bitfield)\n\
    D3 = class equip bitmask (for ANDing the item equip bitfield)", 1);

    // GetCharATKandDEFWithSpecificWeapon
    SetFunctionCmt(0x8fee, 
        "In: A0 = char entry address\n\
    D1 = item idx\n\
Out: D2 = char ATK with item equipped\n\
     D3 = char DEF with item equipped", 1);

    // IsItemUsableInBattle
    SetFunctionCmt(0x90cc, 
        "carry set : YES", 1);

    // IsItemUsableWeaponInBattle
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

    // LearnSpell
    SetFunctionCmt(0x9226, 
        "In: D0 = char idx\n\
    D1 = spell idx\n\
Out: D2 = result (0 = learned new spell, 1 = upgraded spell, 2 = no room)", 1);

    // GetSpellCost
    SetFunctionCmt(0x927e, 
        "    Get MP cost of spell.\n\
    In: D1 = spell index\n\
    Out: D1 = spell MP cost", 1);

    // GetCharEntryAddress
    SetFunctionCmt(0x928e, 
        "In: D0 = char idx\n\
Out: A0 = char RAM address", 1);

    // GetCharacterByte
    SetFunctionCmt(0x92f8, 
        "In: D0 = char idx\n\
    D7 = char byte offset\n\
Out: D1 = byte", 1);

    // GetCharacterWord
    SetFunctionCmt(0x9302, 
        "In: D0 = char idx\n\
    D7 = char byte offset\n\
Out: D1 = word", 1);

    // IncreaseAndClampByte
    SetFunctionCmt(0x9312, 
        "clamp byte # D7 of entity D0's information + D1 between D5 and D6", 1);

    // DecreaseAndClampByte
    SetFunctionCmt(0x936c, 
        "clamp byte # D7 of entity D0's information - D1 between D5 and D6", 1);

    // GetDistanceBetweenEntities
    SetFunctionCmt(0x941e, 
        "Gets distance between two entities (simple X and Y calculation, no obstructions)\n\
In: D0 = from entity\n\
    D1 = to entity\n\
Out: D2 = distance", 1);

    // CalculateStatGain
    SetFunctionCmt(0x96ba, 
        "In: D1 = current stat value\n\
    D2 = growth curve ID\n\
    D3 = starting value\n\
    D4 = projected value\n\
    D5 = current level\n\
Out: D1 = stat gain value", 1);

    // InitGameSettings
    SetFunctionCmt(0x9844, 
        "Clear all flags and important game variables.", 1);

    // GetFlag
    SetFunctionCmt(0x98e8, 
        "flag bit check pattern based on bit number D1 -> D0", 1);

    // UpdateForce
    SetFunctionCmt(0x9900, 
        "determine who is in the force or not based on flags and update RAM lists", 1);

    // GetDealsItemAmount
    SetFunctionCmt(0x99de, 
        "In: D1 = item idx\n\
Out: D2 = number of item idx in deals", 1);

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

    // InitSkirmishProperties
    SetFunctionCmt(0x9f28, 
        "In: A2 = battle scene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of attacker idx\n\
    A5 = address in RAM of target idx", 1);

    // CreateBattleSceneText
    SetFunctionCmt(0xa05c, 
        "Loads proper battle scene text script depending on attack action.\n\
In: A3 = RAM index containing action type\n\
    A4 = RAM index containing attacker index\n\
HARDCODED enemy and text indexes", 1);

    // CreateBattleSceneAnimation
    SetFunctionCmt(0xa200, 
        "    Loads proper battle scene sprite/magic animation properties.\n\
    In: A3 = ", 1);

    // WriteSkirmishScript_DoAction
    SetFunctionCmt(0xa3f4, 
        "In: A2 = battle scene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of attacker idx\n\
    A5 = address in RAM of target idx", 1);

    // GetEffectGraphicsIdx
    SetFunctionCmt(0xa54e, 
        "In: A2 = cutscene stack\n\
    A3 = battle action in RAM\n\
Out: D4 = effect idx\n\
HARDCODED class, enemy and weapon indexes", 1);

    // WriteSkirmishScript_AnimateSprite
    SetFunctionCmt(0xa6e8, 
        "    Loads proper battle scene sprite animation properties.\n\
    In: D4 = projectile\n\
        D5 = special script idx", 1);

    // GetAmountOfEXPForEncounter
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

    // WriteSkirmishScript_InflictDamage
    SetFunctionCmt(0xacea, 
        "In: D6 = damage", 1);

    // WriteSkirmishScript_UseSpell
    SetFunctionCmt(0xb0a8, 
        "In: A2 = battle scene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of attacker idx\n\
    A5 = address in RAM of target idx", 1);

    // spell07_Muddle
    SetFunctionCmt(0xb488, 
        "muddle", 1);

    // GetSpellPowerAdjustedForClass
    SetFunctionCmt(0xbb56, 
        "    Miscellaneous hacks to alter spell damage. (125% if promoted, damage divided if SORC spells)\n\
    In: D6 = original damage\n\
    Out: D6 = altered damage", 1);

    // GetItemBreakMessage
    SetFunctionCmt(0xbc9a, 
        "In: A2 = skirmish properties stack\n\
    D0 = whether item is already damaged (0=no, 1=yes)\n\
Out: D3 = message idx", 1);

    // WriteSkirmishScript_EnemyDropItem
    SetFunctionCmt(0xbd24, 
        "In: A2 = battle scene stack\n\
    A3 = address in RAM of scene action type\n\
    A4 = address in RAM of attacker idx\n\
    A5 = address in RAM of target idx", 1);

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

    // SetMovableAtCoord
    SetFunctionCmt(0xc204, 
        "    Set coord to movable in movable grid.\n\
    In: D1 = X coord\n\
        D2 = Y coord", 1);

    // GetResistanceToSpell
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

    // CreateSpellRangeGrid
    SetFunctionCmt(0xc478, 
        "    Clear and update target/movable grids based on spell properties.\n\
    In: D0 = spell user\n\
        D1 = spell idx", 1);

    // ApplyRelativeCoordListToGrids
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

    // GetSpellPowerAdjustedForResistance
    SetFunctionCmt(0xcc54, 
        "In: D0 = target combatant idx\n\
    D1 = spell idx\n\
Out: D6 = adjusted power", 1);

    // sub_CD68
    SetFunctionCmt(0xcd68, 
        "In: D0 = heal target char idx\n\
    D4 = heal spell idx", 1);

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

    // j_sub_DEFC_0
    SetFunctionCmt(0xdefc, 
        "In: D0 = char idx", 1);

    // sub_EBA4
    SetFunctionCmt(0xeba4, 
        "In: D0 = char idx", 1);

    // j_EndKiss
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

    // sub_107EA
    SetFunctionCmt(0x107ea, 
        "related to menu choice", 1);

    // LoadIHighlightableSpellIcon
    SetFunctionCmt(0x10940, 
        "    Copy spell icon to RAM.\n\
    In: A1 = dest in RAM\n\
        D0 = spell idx\n\
    Out: A1 = end of affected section after copy", 1);

    // sub_10CB0
    SetFunctionCmt(0x10cb0, 
        "related to menu choice", 1);

    // sub_11862
    SetFunctionCmt(0x11862, 
        "write one column of HP/MP bar pixels into A1", 1);

    // AdjustStringLengthForSpecialChars
    SetFunctionCmt(0x11898, 
        "check ASCII name at A0 for two special chars ???\n\
", 1);

    // WriteStatValue
    SetFunctionCmt(0x11aae, 
        "display d0 stat value or \"??\" if above 99", 1);

    // CopyFighterMinistatusWindowTileColumn
    SetFunctionCmt(0x11ac6, 
        "draw tiles from A0 into A1 (one column)", 1);

    // BuildMemberStatsScreen
    SetFunctionCmt(0x11c2a, 
        "Create and display member stats screen\n\
\n\
In: D0 = character idx", 1);

    // AddStatusEffectTileIndexesToVDPTileOrder
    SetFunctionCmt(0x11eea, 
        "In: A1 = address of VDP tile order in RAM", 1);

    // GetPortraitIdx
    SetFunctionCmt(0x1263a, 
        "    Get index of portrait based on char index for any character.\n\
    In: D0 = char idx\n\
    Out: D0 = adjusted portrait idx", 1);

    // LoadCharPortrait
    SetFunctionCmt(0x13394, 
        "    In: D0 = char idx", 1);

    // GetSelectedMember
    SetFunctionCmt(0x13462, 
        "    Get index of currently selected force member (in menus).\n\
    Out: D0 = selected index (capped to 255)", 1);

    // sub_14074
    SetFunctionCmt(0x14074, 
        "related to menu choice", 1);

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

    // sub_14CB2
    SetFunctionCmt(0x14cb2, 
        "copy item # D1 icon pixels to A0 in RAM", 1);

    // sub_14CEC
    SetFunctionCmt(0x14cec, 
        "get current item idx in shop/caravan (from index list) -> D0", 1);

    // sub_15422
    SetFunctionCmt(0x15422, 
        "d0 = FFAFE7, related to DMA", 1);

    // ClosePortraitEyes
    SetFunctionCmt(0x154f6, 
        "Close princess Ellis' eyes when unconscious.", 1);

    // UpdatePortrait
    SetFunctionCmt(0x155c4, 
        "d1 = alternate/original, d7 = tile number", 1);

    // LoadPortrait
    SetFunctionCmt(0x1562a, 
        "    In: D0 = portrait idx", 1);

    // GetCharPortraitIdx
    SetFunctionCmt(0x15736, 
        "    Get index of portrait based on char index for force members.\n\
    In: D0 = char idx\n\
    Out: D0 = adjusted portrait idx", 1);

    // sub_1586E
    SetFunctionCmt(0x1586e, 
        "related to battlefield options", 1);

    // NumberPrompt
    SetFunctionCmt(0x16282, 
        "In: D0 = default num\n\
    D1 = min num\n\
    D2 = max num\n\
Out: D0 = chosen num", 1);

    // ModifyPromptNumber
    SetFunctionCmt(0x16398, 
        "In: A6 = prompt stack", 1);

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

    // MakeActorIdle
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

    // InitializeBattleScenePalettes
    SetFunctionCmt(0x19884, 
        "clears plt 1-2 and 1-2bis, sets plt 3bis", 1);

    // LoadPaletteForBattleScene
    SetFunctionCmt(0x199de, 
        "load palette D1 of battle sprite D0", 1);

    // LoadAllyBattleSpriteFrame
    SetFunctionCmt(0x19a0c, 
        "D0=Battlesprite idx, D1=Frame idx", 1);

    // VIntLoadAllyBattleSpriteFrame
    SetFunctionCmt(0x19a2a, 
        "D0=Battlesprite idx, D1=Frame idx", 1);

    // LoadWeaponSprite
    SetFunctionCmt(0x19a5c, 
        "D0=Weapon sprite idx", 1);

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
        "get battle sprite # and palette # for character related to entity D0 -> D1 (sprite), D2 (palette)", 1);

    // GetWeaponSpriteAndPalette
    SetFunctionCmt(0x19db0, 
        "get battle sprite # and palette # for entity D0's equipped weapon -> D2 (sprite), D3 (palette)", 1);

    // sub_19E96
    SetFunctionCmt(0x19e96, 
        "Get a boolean depending on background id", 1);

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

    // DoesCurrentShopContainItem
    SetFunctionCmt(0x20834, 
        "In: D1 = item idx\n\
Out: Z = 0 = yes, 1 = no", 1);

    // FindPromotionSection
    SetFunctionCmt(0x2110c, 
        "In: D2 = section type (regpre, regpost, specpre, specpost, specitem)\n\
Out: A0 = address", 1);

    // ReplaceSpellsWithSORCDefaults
    SetFunctionCmt(0x2112c, 
        "In: A6 = church actions stack", 1);

    // sub_219EC
    SetFunctionCmt(0x219ec, 
        "copy available targets list ?", 1);

    // DisplaySpecialCaravanDescription
    SetFunctionCmt(0x22864, 
        "only used for chirrup sandals", 1);

    // sub_22926
    SetFunctionCmt(0x22926, 
        "copy item idxes of caravan items to index list", 1);

    // sub_2294C
    SetFunctionCmt(0x2294c, 
        "get whether character D0's item at slot D1 is cursed -> carry", 1);

    // UseFieldItem
    SetFunctionCmt(0x229ec, 
        "check specific item index + code offset to run when used in field", 1);

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

    // GetEntityNumberOfCombatant
    SetFunctionCmt(0x22f30, 
        "    Convert combatant number to entity number.\n\
    In: D0 = combatant number\n\
    Out: D0 = entity number", 1);

    // GetEntityEventIdx
    SetFunctionCmt(0x22f4a, 
        "In: D0 = entity idx\n\
Out: D0 = entity event idx", 1);

    // SetUnitCursorDestinationToNextCombatant
    SetFunctionCmt(0x232ac, 
        "In: D0 = entity idx\n\
Out: D2 = entity X\n\
     D3 = entity Y", 1);

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

    // CheckArea
    SetFunctionCmt(0x23862, 
        "Get item or area description", 1);

    // GetChestGoldAmount
    SetFunctionCmt(0x2399c, 
        "get amount of gold (D2 - 0x80) as an offset from the gold table (see constants)", 1);

    // BattleLoop
    SetFunctionCmt(0x23a84, 
        "In: D0 = map idx\n\
    D1 = battle idx", 1);

    // GetRemainingFighters
    SetFunctionCmt(0x23c58, 
        "number of force members living, number of enemies living -> D2, D3", 1);

    // sub_23D98
    SetFunctionCmt(0x23d98, 
        "battlefield spell/item use", 1);

    // GetEgressPositionForBattle
    SetFunctionCmt(0x23e50, 
        "HARDCODED battle->map relationship ?", 1);

    // sub_23EB0
    SetFunctionCmt(0x23eb0, 
        "In: D0 = combatant idx", 1);

    // HandleAfterTurnEffects
    SetFunctionCmt(0x24242, 
        "handle after-turn effects (status effects, HP/MP regen/degen, etc)", 1);

    // UpdateTargetListForCombatant
    SetFunctionCmt(0x24642, 
        "In: D0 = combatant idx", 1);

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

    // GetEntityPositionAfterApplyingFacing
    SetFunctionCmt(0x256b2, 
        "In: D0 = combatant idx\n\
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
        "Out: D4 = map sprite ID", 1);

    // GetCombatantMapSprite
    SetFunctionCmt(0x44a7c, 
        "In: A6 = battle vars stack ???\n\
Out: D4 = map sprite ID", 1);

    // WaitForEntityToStopMoving
    SetFunctionCmt(0x44da4, 
        "In: D0 = entity idx", 1);

    // GetEntityRAMAddress
    SetFunctionCmt(0x44dd8, 
        "location in memory of entity # D0 -> A0", 1);

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

    // GetEntityPortraitAndSpeechSfx
    SetFunctionCmt(0x45638, 
        "In: D0 = entity idx\n\
Out: D1 = portrait idx\n\
     D2 = speech sound idx", 1);

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

    // GetEntityAddressFromPlayableCharacterIdx
    SetFunctionCmt(0x4704a, 
        "    Get address of entity information. Could be a force member or an opponent\n\
    In: D0 = playable character from FFB140\n\
    Out: A5 = entity info address in RAM", 1);

    // AdjustScriptPointerByCharAliveStatus
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
        "In: D0 = entity event idx", 1);

    // LoadAndDisplayCurrentPortrait
    SetFunctionCmt(0x476e8, 
        "    Get index of current portrait for textbox and load it.", 1);

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
        "In: D0 = char idx\n\
    D4 = char idx (same as D0)\n\
Out: D0 = 0000 if activated and dead, FFFF if not", 1);

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
        "In: D0 = char idx\n\
    D1 = char word 34 (AI stuff)\n\
Out: carry = 0 if respawn, 1 if not", 1);

    // InitEnemyStats
    SetFunctionCmt(0x1b140a, 
        "In: A0 = address of current combatant from battle def", 1);

    // InitEnemyItems
    SetFunctionCmt(0x1b1504, 
        "handle custom item idx of monster list entry starting at A0 -> ???", 1);

    // GetEnemyOriginalPosOccupied
    SetFunctionCmt(0x1b1554, 
        "In: D3 = enemy starting tile x (from battle def)\n\
    D4 = enemy starting tile y (from battle def)\n\
Out: carry = if anyone is on D3/D4", 1);

    // SetEnemyBaseATK
    SetFunctionCmt(0x1b15aa, 
        "sets Enemy ATK according to difficulty", 1);

    // GetEnemyAITargetPos
    SetFunctionCmt(0x1b15f8, 
        "coords of anchor point used in AI byte D0 -> D1, D2", 1);

    // GetBattleSpriteSetSubsection
    SetFunctionCmt(0x1b1630, 
        "Get current battle subsection d1 -> A0\n\
Subsection size -> d1", 1);

    // GetCombatantStartPos
    SetFunctionCmt(0x1b169e, 
        "Starting X and Y of entity d0 -> d1, d2", 1);

    // sub_1B16FE
    SetFunctionCmt(0x1b16fe, 
        "Battle-related", 1);

    // DoesBattleUpgrade
    SetFunctionCmt(0x1b1780, 
        "Check if current battle can be upgraded (0x0000=no, 0xffff=yes) -> D1", 1);

    // UpgradeBattle
    SetFunctionCmt(0x1b17bc, 
        "Strange use case where \"Battle completed\" flag is set for battle 4 in spite of being alreeady set earlier.", 1);

    // ShouldBattleUpgrade
    SetFunctionCmt(0x1b17fe, 
        "check if battle should be upgraded based on index in RAM:f712 and if normal battle was done (0=no, 1=yes) -> D1", 1);

    // UpgradeUnitIdx
    SetFunctionCmt(0x1b184c, 
        "In: D1 = original unit idx\n\
Out: D1 = upgraded unit idx", 1);

}
