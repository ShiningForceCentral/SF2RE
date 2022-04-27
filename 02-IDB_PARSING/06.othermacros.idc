


#include <idc.idc>


static main(void){

    Message("\nINITIALIZING ARRAYS...\n");
    initializeArrays();
    
    Message("PARSING DATA STRUCTURES INTO MACROS ...\n");
    parseFlaggedSwitchedMaps();
    parseBattleMapCoords();    
    parseSavePointMapCoords();
    parseRaftResetMapCoords();
    parseClassTypes();
    parseHalvedEXPearnedBattles();
    parseCriticalHitSettings();
    parseItemBreakMessages();
    parseEnemyItemDrops();
    //parseEnemyGold();
    parseSpellElements();
    parseLandEffectSettingsAndMoveCosts();
    parseAiCommandsets();
    parseSwarmBattles();
    parseSpellNames();
    parseAllyNames();
    parseEnemyNames();
    parseSpellLevelHighlightVdpSprites();
    parseDiamondMenuLayout();
    parseMagicMenuLayout();
    parseItemMenuLayout();
    parseSpellLevelTilesLayouts();
    parseBattleEquipWindowLayout();
    parsePortraitWindowLayout();
    parseAllyKillDefeatWindowLayout();
    parseGoldWindowLayout();
    parseMemberListTextHighlightVdpSprite();
    parseUnknownWindowLayout_13EDE();
    parseItemListTextHighlightVdpSprites();
    parseShopInventoryWindowLayout();
    parseYesNoPromptMenuLayout();
    parseBattleConfigVdpSprites();
    parseBattleConfigWindowLayout();
    parseFighterMiniStatusWindowLayout();
    parseAlphabetWindowLayout();
    parseNameEntryWindowLayout();
    parseTimerWindowLayout();
    parseMemberStatsWindowLayout();
    parseItemDefs();
    parseSpellDefs();
    parseItemNames();
    parseClassNames();
    parseTerrainBackgrounds();
    parseUnknownVdpSprites_1F128();
    parseBattlesceneAllyVdpSprites();
    parseBattlesceneWeaponVdpSprites();
    parseBattlesceneGroundVdpSprites();
    parseAllyBattleSprites();
    parseEnemyBattleSprites();
    parseWeaponSprites();
    parseCustomBackgrounds();
    parseAllyBattleSpriteIdleAnimate();
    parseEnemyBattleSpriteIdleAnimate();
    parseBackgroundLayout();
    parseShopInventories();
    parsePromotions();
    parseBlacksmithEligibleClassesList();
    parseMithrilWeaponClassLists();
    parseMithrilWeaponLists();
    parseSpecialCaravanDescriptions();
    parseUsableOutsideBattleItems();
    parseUnknownVdpSprites_2358C();   // unknown sprite definitions at 0x2358C
    parseConfigurationModeInputs();
    parseDebugModeInputs();
    parseFollowers();
    parseAllyMapSprites();
    parseEnemyMapSprites();
    parseSpriteDialogProperties();
    //parseEnemyLeaderPresence();
    parseEnemyDefs();
    parseRandomBattles();
    parseEnemyUpgradeDefs();
    parseStatGrowthCurves();
    parseAllyStats();
    parseAllyStartDefs();
    parseClassDefs();
    parseMapData();

    Message("DELETING ARRAYS...\n");
    deleteArrays();
      
    Message("END OF PARSING.\n");  

    // Check if script running in batch mode, and exit once done
    if (Batch(1) == 1) {
        Exit(0);                              // exit to OS, error code 0 - success		
    }
    else {
        Batch(0);
    }
}

static parseFlaggedSwitchedMaps(){
    auto addr, j, map, flag, newMap;
    auto flagmapFile, currentLine, lineNumber;
    auto parameter;
    auto flagDescription;
    addr = 0x7988;
    lineNumber = 0;
    while(Word(addr)!=0xFFFF){
        flagDescription = "";
        for(j=addr;j<addr+6;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,6,1);
        map = Word(addr);
        flag = Word(addr+2);
        newMap = Word(addr+4);
        flagDescription = getFlagDesc(flag);   
        MakeRptCmt(addr,flagDescription);
        SetManualInsn(addr, form("flagSwitchedMap %s, %s, %s", getMap(map), ltoa(flag,10), getMap(newMap)));
        addr = addr+6;
    }
    for(j=addr;j<addr+1;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "flagSwitchedMapsEnd");
}



static parseBattleMapCoords(){
    auto addr, j, map, x, y, width, height, triggerX, triggerY;
    auto parameter;
    addr = 0x7A36;
    while(addr<0x7B71){
        for(j=addr;j<addr+7;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,7,1);
        map = Byte(addr);
        x = Byte(addr+1);
        y = Byte(addr+2);
        width = Byte(addr+3);
        height = Byte(addr+4);
        triggerX = Byte(addr+5);
        triggerY = Byte(addr+6);
        SetManualInsn(addr, form("battleMapCoords %d, %d, %d, %d, %d, %d, %d", map, x, y, width, height, triggerX, triggerY));
        addr = addr+7;
    }
}


static parseSavePointMapCoords(){
    auto addr, j, map, x, y, facing;
    auto parameter;
    addr = 0x7B71;
    while(addr<0x7BCD){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,4,1);
        map = Byte(addr);
        x = Byte(addr+1);
        y = Byte(addr+2);
        facing = Byte(addr+3);
        SetManualInsn(addr, form("savePointMapCoords %s, %d, %d, %s", getMap(map), x, y, getDirection(facing)));
        addr = addr+4;
    }
}


static parseRaftResetMapCoords(){
    auto addr, j, map, raftMap, x, y;
    auto parameter;
    addr = 0x7BCE;
    while(addr<0x7BDE){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,4,1);
        map = Byte(addr);
        raftMap = Byte(addr+1);
        x = Byte(addr+2);
        y = Byte(addr+3);
        SetManualInsn(addr, form("raftResetMapCoords %s, %s, %d, %d", getMap(map), getMap(raftMap), x, y));
        addr = addr+4;
    }
}


static parseClassTypes(){
    auto addr, classType, index, className;
    addr = 0x853A;
    while(addr<0x855A){
        undefineByte(addr);
        MakeByte(addr);
        classType = getClassTypeShorthand(Byte(addr));
        SetManualInsn(addr, form("classType %s", classType));
        
        /* Provide class name and index as a comment */
        className = getClassName(index);
        MakeRptCmt(addr, form("%d: %s", index, className));
        index++;
        addr++;
    }
}

static parseHalvedEXPearnedBattles(){
    auto addr, battle;
    addr = 0xA870;
    while(addr<0xA871){
        undefineByte(addr);
        MakeByte(addr);
        battle = getBattleShorthand(Byte(addr));
        SetManualInsn(addr, form("battle %s", battle));
        addr++;
    }
    
    /* Terminator byte at address 0xA871 */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
}

static parseCriticalHitSettings(){
    auto addr, j, chance, damage;
    addr = 0xACCA;
    while(addr<0xACEA){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,2,1);
        chance = Byte(addr);
        damage = Byte(addr+1);
        SetManualInsn(addr, form("dc.b %d, %d", chance, damage));
        addr = addr+2;
    }
}

static parseItemBreakMessages(){
    auto addr, j, item, msgOffset;
    addr = 0xBCF0;
    while(addr<0xBD22){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,2,1);
        item = getItemShorthand(Byte(addr));
        msgOffset = Byte(addr+1);
        SetManualInsn(addr, form("itemBreakMessage %s, %d", item, msgOffset));
        addr = addr+2;
    }
    
    /* Terminator word at address 0xBD22 */
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "tableEnd");
}

static parseEnemyItemDrops(){
    auto addr, j, battle, enemyEntity, itemDrop, dropFlag;
    addr = 0xBE52;
    while(addr<0xBECA){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        
        /* Battle */
        MakeByte(addr);
        battle = getBattleShorthand(Byte(addr));
        SetManualInsn(addr, form("battle      %s", battle));
        
        /* Enemy entity */
        MakeByte(addr+1);
        enemyEntity = Byte(addr+1)-128;
        SetManualInsn(addr+1, form("enemyEntity %d", enemyEntity));
        
        /* Item */
        MakeByte(addr+2);
        itemDrop = getItemShorthand(Byte(addr+2));
        SetManualInsn(addr+2, form("itemIndex   %s", itemDrop));
        
        /* Drpped flag */
        MakeByte(addr+3);
        dropFlag = Byte(addr+3);
        SetManualInsn(addr+3, form("droppedFlag %d\n", dropFlag));
        
        addr = addr+4;
    }
    
    /* Terminator word at address 0xBECA */
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "tableEnd");
}

/*
static parseEnemyGold(){
    auto addr, i, j, gold;
    addr = 0xBECC;
    while(addr<0xC024){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        gold = Word(addr);
        //SetManualInsn(addr, form("enemyGold %d", gold));
        SetManualInsn(addr, "");
        // Provide enemy's name as a comment
        if(i<103){MakeRptCmt(addr, form("%s", findName(0xFB8A,i)));}
        i++;
        addr = addr+2;
    }
}
*/

static parseSpellElements(){
    auto addr, spellElement, index, spellName;
    addr = 0xC24E;
    while(addr<0xC27A){
        undefineByte(addr);
        MakeByte(addr);
        spellElement = getSpellElementShorthand(Byte(addr));
        SetManualInsn(addr, form("spellElement %s", spellElement));
        
        /* Provide spell name as a comment */
        spellName = getSpellName(index);
        MakeRptCmt(addr, form("%d: %s", index, spellName));
        index++;
        addr++;
    }
}

static parseLandEffectSettingsAndMoveCosts(){
    auto addr, landEffect, landEffectSettingAndMoveCost;
    addr = 0xD824;
    while(addr<0xD8F4){
        undefineByte(addr);
        MakeByte(addr);
        if(Byte(addr)==0xFF){
            landEffectSettingAndMoveCost = getLandEffectSettingObstructedShorthand(Byte(addr));
        }else{
            landEffect = getLandEffectSettingShorthand(Byte(addr)&0xF0);
            landEffectSettingAndMoveCost = form("%s|%d", landEffect, Byte(addr)&0xF);
        }
        SetManualInsn(addr, form("landEffectAndMoveCost %s", landEffectSettingAndMoveCost));
        addr++;
    }
}

static parseAiCommandsets(){
    auto addr, j, len, aiCommandset, next;
    addr = 0xE1EC;
    while(addr<0xE249){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        aiCommandset = "";
        for(j=addr+1;j<addr+len;j++){
            next = getAiCommandShorthand(Byte(j));
            if(aiCommandset==""){
                aiCommandset = next;
            }else{
                aiCommandset = form("%s, &\n             %s", aiCommandset, next);
            }
        }
        SetManualInsn(addr, form("aiCommandset %s", aiCommandset));
        addr = addr+len;
    }
}

static parseSwarmBattles(){
    auto addr, j, len, battles, next;
    addr = 0xE25B;
    while(addr<0xE25F){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        battles = "";
        for(j=addr+1;j<addr+len;j++){
            next = getBattleShorthand(Byte(j));
            if(battles==""){
                battles = next;
            }else{
                battles = form("%s, %s", battles, next);
            }
        }
        SetManualInsn(addr, form("battles %s", battles));
        addr = addr+len;
    }
    
    /* Word align at address 0xE25F */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, form("wordAlign"));
}

static parseSpellNames(){
    auto addr, j, size, name;
    addr = 0xF9C4;
    while(addr<0xFAD6){
        size = Byte(addr)+1;
        name = Str(addr,size);
        for(j=addr;j<addr+size;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,size,1);
        SetManualInsn(addr, form("spellName \"%s\"", name));
        addr = addr+size;
    }
}

static parseAllyNames(){
    auto addr, j, size, name;
    addr = 0xFAD6;
    while(addr<0xFB8A){
        size = Byte(addr)+1;
        name = Str(addr,size);
        for(j=addr;j<addr+size;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,size,1);
        SetManualInsn(addr, form("allyName \"%s\"", name));
        addr = addr+size;
    }
}

static parseEnemyNames(){
    auto addr, j, size, name;
    addr = 0xFB8A;
    while(addr<0xFF87){
        size = Byte(addr)+1;
        name = Str(addr,size);
        for(j=addr;j<addr+size;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,size,1);
        SetManualInsn(addr, form("enemyName \"%s\"", name));
        addr = addr+size;
    }
    
    /* Set Jaro's entry manually */
    SetManualInsn(0xFF5E, form("enemyName \"JAR\", 0"));
}

static parseSpellLevelHighlightVdpSprites(){
    parseVdpSprites(0x10DD2,0x10DE2);
}

static parseDiamondMenuLayout(){
    auto addr, j, vdpTile;
    addr = 0x10E1C;
    while(addr<0x10EF4){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseMagicMenuLayout(){
    auto addr, j, vdpTile;
    addr = 0x10EF4;
    while(addr<0x10FCC){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseItemMenuLayout(){
    auto addr, j, vdpTile;
    addr = 0x10FCC;
    while(addr<0x110A4){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseSpellLevelTilesLayouts(){
    auto addr, j, vdpTile;
    addr = 0x110E4;
    while(addr<0x1115C){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseBattleEquipWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x114BE;
    while(addr<0x11572){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseFighterMiniStatusWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x11AEC;
    while(addr<0x11B46){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parsePortraitWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x126EE;
    while(addr<0x1278E){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseAllyKillDefeatWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x1278E;
    while(addr<0x1284E){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseGoldWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x1284E;
    while(addr<0x1288E){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseMemberListTextHighlightVdpSprite(){
    parseVdpSprites(0x13452,0x13462);
}

static parseUnknownWindowLayout_13EDE(){
    auto addr, j, vdpTile;
    addr = 0x13EDE;
    while(addr<0x13F14){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseItemListTextHighlightVdpSprites(){
    parseVdpSprites(0x14724,0x1474C);
}

static parseShopInventoryWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x1505C;
    while(addr<0x151D6){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseYesNoPromptMenuLayout(){
    auto addr, j, vdpTile;
    addr = 0x154A2;
    while(addr<0x154F6){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseBattleConfigVdpSprites(){
    parseVdpSprites(0x15A00,0x15A20);
}

static parseBattleConfigWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x15A5A;
    while(addr<0x15BB0){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseAlphabetWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x1607C;
    while(addr<0x16204){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseNameEntryWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x16204;
    while(addr<0x1623A){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseTimerWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x16618;
    while(addr<0x16658){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseMemberStatsWindowLayout(){
    auto addr, j, vdpTile;
    addr = 0x16A62;
    while(addr<0x16EA6){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr)&0x1FFF);
        SetManualInsn(addr, form("vdpBaseTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseItemDefs(){
    auto addr, j, equipFlags, maxRange, minRange, price, itemType, useSpell, equipEffects, next, index, itemName;
    addr = 0x16EA6;
    while(addr<0x176A6){
        for(j=addr;j<addr+16;j++){undefineByte(j);}
        
        /* Equip flags */
        MakeDword(addr);
        if(Dword(addr)==0){
            //equipFlags = getEquipFlagsOtherShorthand(Dword(addr));
            equipFlags = "NONE";
        }else if(Dword(addr)==-1){
            equipFlags = "ALL";
        }else{
            equipFlags = getEquipFlagsShorthand(Dword(addr));
        }
        SetManualInsn(addr, form("equipFlags   %s", equipFlags));
        
        /* Range */
        MakeData(addr+4,FF_BYTE,2,1);
        maxRange = Byte(addr+4);
        minRange = Byte(addr+5);
        SetManualInsn(addr+4, form("range        %d, %d", minRange, maxRange));
        
        /* Price */
        MakeWord(addr+6);
        price = Word(addr+6);
        SetManualInsn(addr+6, form("price        %d", price));
        
        /* Item type */
        MakeByte(addr+8);
        if(Byte(addr+8)==0){
            itemType = getItemTypeNoneShorthand(Byte(addr+8));
        }else{
            itemType = getItemTypeShorthand(Byte(addr+8));
        }
        SetManualInsn(addr+8, form("itemType     %s", itemType));
        
        /* Use spell */
        MakeByte(addr+9);
        useSpell = getSpellShorthand(Byte(addr+9));
        SetManualInsn(addr+9, form("useSpell     %s", useSpell));
        
        /* Equip effects */
        MakeData(addr+10,FF_BYTE,6,1);
        equipEffects = "";
        for(j=addr+10;j<addr+16;j=j+2){
            next = getEquipEffectShorthand(Byte(j));
            if(equipEffects==""){
                equipEffects = form("%s, %d", next, Byte(j+1));
            }else{
                equipEffects = form("%s, &\n             %s, %d", equipEffects, next, Byte(j+1));
            }
        }
        SetManualInsn(addr+10, form("equipEffects %s\n", equipEffects));
        
        /* Provide item name as a comment */
        if(index!=0){
            itemName = getItemName(index);
            ExtLinA(addr, 0, form("                ; %d: %s", index, itemName));
        }

        index++;
        addr = addr+16;
    }
}

static parseSpellDefs(){
    auto addr, j, entry, mpCost, animation, properties, maxRange, minRange, radius, power, index, count, spellName;
    addr = 0x176A6;
    while(addr<0x1796E){
        for(j=addr;j<addr+8;j++){undefineByte(j);}
        
        /* Spell entry */
        MakeByte(addr);
        entry = getSpellShorthand(Byte(addr));
        SetManualInsn(addr, form("entry      %s", entry));
        
        /* MP cost */
        MakeByte(addr+1);
        mpCost = Byte(addr+1);
        SetManualInsn(addr+1, form("mpCost     %d", mpCost));
        
        /* Animation index */
        MakeByte(addr+2);
        animation = getSpellAnimationShorthand(Byte(addr+2));
        SetManualInsn(addr+2, form("animation  %s", animation));
        
        /* Spell properties */
        MakeByte(addr+3);
        properties = getSpellPropertiesShorthand(Byte(addr+3));
        SetManualInsn(addr+3, form("properties %s", properties));
        
        /* Range */
        MakeData(addr+4,FF_BYTE,2,1);
        maxRange = Byte(addr+4);
        minRange = Byte(addr+5);
        SetManualInsn(addr+4, form("range      %d, %d", minRange, maxRange));
        
        /* Radius */
        MakeByte(addr+6);
        radius = Byte(addr+6);
        SetManualInsn(addr+6, form("radius     %d", radius));
        
        /* Power */
        MakeByte(addr+7);
        power = Byte(addr+7);
        SetManualInsn(addr+7, form("power      %d\n", power));
        
        /* Provide spell name as a comment */
        index = Byte(addr);
        count = 1;
        while(index>=64){
            index = index-64;
            count++;
        }
        spellName = getSpellName(index);
        MakeRptCmt(addr, form("%s %d", spellName, count));
        addr = addr+8;
    }
}

static parseItemNames(){
    auto addr, size, subSize, specialChar, nextChar, j, nameOne, nameTwo;
    addr = 0x1796E;
    while(addr<0x17F3D){
        size = Byte(addr)+1;
        
        /* Get name properties : special character, substring entry size */
        subSize = 1;
        specialChar = 0;
        for(j=addr+1;j<addr+size-1;j++){
            nextChar = Byte(j);
            if(nextChar==11||nextChar==13){
                specialChar = nextChar;
                break;
            }
            subSize++;
        }
        
        for(j=addr;j<addr+size;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,size,1);
        if(specialChar!=0){
            nameOne = Str(addr,subSize);
            nameTwo = Str(addr+subSize,size-subSize);
            SetManualInsn(addr, form("itemName \"%s\", %d, \"%s\"", nameOne, specialChar, nameTwo));
        }else{
            SetManualInsn(addr, form("itemName \"%s\"", Str(addr,size)));
        }
        addr = addr+size;
    }
    
    /* Word align at address 0x17F3D */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, form("wordAlign"));
}

static parseClassNames(){
    auto addr, j, size, name;
    addr = 0x17F3E;
    while(addr<0x17FDA){
        size = Byte(addr)+1;
        name = Str(addr,size);
        for(j=addr;j<addr+size;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,size,1);
        SetManualInsn(addr, form("className \"%s\"", name));
        addr = addr+size;
    }
}

static parseTerrainBackgrounds(){
    auto addr, battleBackground;
    addr = 0x19E5E;
    while(addr<0x19E6E){
        undefineByte(addr);
        MakeByte(addr);
        battleBackground = getBattleBackgroundShorthand(Byte(addr));
        SetManualInsn(addr, form("background %s", battleBackground));
        addr++;
    }
}

static parseUnknownVdpSprites_1F128(){
    parseVdpSprites(0x1F128,0x1F140);
}

static parseBattlesceneAllyVdpSprites(){
    parseVdpSprites(0x1F576,0x1F606);
}

static parseBattlesceneWeaponVdpSprites(){
    parseVdpSprites(0x1F606,0x1F686);
}

static parseBattlesceneGroundVdpSprites(){
    parseVdpSprites(0x1F686,0x1F6B6);
}

static parseAllyBattleSprites(){
    auto addr, i, j, forClass, sprite, palette, allyName;
    addr = 0x1F806;
    while(addr<0x1F914){
        for(j=addr;j<addr+9;j++){undefineByte(j);}
        
        /* For base class */
        MakeData(addr,FF_BYTE,3,1);
        forClass = getClassShorthand(Byte(addr));
        sprite = getAllyBattlespriteShorthand(Byte(addr+1));
        palette = Byte(addr+2);
        SetManualInsn(addr, form("allyBattleSprAndPlt %s, %s, %d", forClass, sprite, palette));
        
        /* For regular promo */
        MakeData(addr+3,FF_BYTE,3,1);
        forClass = getClassShorthand(Byte(addr+3));
        sprite = getAllyBattlespriteShorthand(Byte(addr+4));
        palette = Byte(addr+5);
        SetManualInsn(addr+3, form("allyBattleSprAndPlt %s, %s, %d", forClass, sprite, palette));
        
        /* For special promo */
        MakeData(addr+6,FF_BYTE,3,1);
        forClass = getClassShorthand(Byte(addr+6));
        sprite = getAllyBattlespriteShorthand(Byte(addr+7));
        palette = Byte(addr+8);
        SetManualInsn(addr+6, form("allyBattleSprAndPlt %s, %s, %d", forClass, sprite, palette));
        
        addr = addr+9;
    }
}

static parseEnemyBattleSprites(){
    auto addr, j, sprite, palette, index, enemyName;
    addr = 0x1F914;
    while(addr<0x1F9E2){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,2,1);
        sprite = getEnemyBattlespriteShorthand(Byte(addr));
        palette = Byte(addr+1);
        SetManualInsn(addr, form("enemyBattleSprAndPlt %s, %d", sprite, palette));
        
        /* Provide enemy's name as a comment */
        enemyName = getEnemyName(index);
        MakeRptCmt(addr, form("%d: %s", index, enemyName));
        index++;
        addr = addr+2;
    }
}

static parseWeaponSprites(){
    auto addr, j, sprite, palette, index, itemName;
    index = 26;
    addr = 0x1F9E2;
    while(addr<0x1FA8A){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        sprite = getWeaponSpriteShorthand(Byte(addr));
        palette = getWeaponPaletteShorthand(Byte(addr+1));
        SetManualInsn(addr, form("weaponGraphics %s, %s", sprite, palette));
        
        /* Provide item name as a comment */
        itemName = getItemName(index);
        MakeRptCmt(addr, form("%d: %s", index, itemName));
        index++;
        addr = addr+2;
    }
}

static parseCustomBackgrounds(){
    auto addr, battleBackground;
    addr = 0x1FA8A;
    while(addr<0x1FAB7){
        undefineByte(addr);
        MakeByte(addr);
        battleBackground = getBattleBackgroundShorthand(Byte(addr));
        SetManualInsn(addr, form("background %s", battleBackground));
        addr++;
    }
    
    /* Word align at address 0x1FAB7 */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, form("wordAlign"));
}

static parseAllyBattleSpriteIdleAnimate(){
    auto addr, allyBattleSprite;
    addr = 0x1FAD6;
    while(addr<0x1FADC){
        undefineByte(addr);
        MakeByte(addr);
        allyBattleSprite = getAllyBattlespriteShorthand(Byte(addr));
        SetManualInsn(addr, form("allyBattleSprite %s", allyBattleSprite));
        addr++;
    }
    
    /* Terminator byte at address 0x1FADD */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
}

static parseEnemyBattleSpriteIdleAnimate(){
    auto addr, enemyBattleSprite;
    addr = 0x1FADD;
    while(addr<0x1FAE9){
        undefineByte(addr);
        MakeByte(addr);
        enemyBattleSprite = getEnemyBattlespriteShorthand(Byte(addr));
        SetManualInsn(addr, form("enemyBattleSprite %s", enemyBattleSprite));
        addr++;
    }
    
    /* Terminator byte at address 0x1FAEA */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
}

static parseBackgroundLayout(){
    auto addr, j, vdpTile;
    addr = 0x1FAEA;
    while(addr<0x1FDEA){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeWord(addr);
        vdpTile = getVdpTileShorthand(Word(addr));
        SetManualInsn(addr, form("vdpTile %s", vdpTile));
        addr = addr+2;
    }
}

static parseShopInventories(){
    auto addr, i, j, len, shopInventory, next;
    i = 1;
    addr = 0x20878;
    while(addr<0x20981){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        shopInventory = "";
        for(j=addr+1;j<addr+len;j++){
            next = getItemShorthand(Byte(j));
            if(shopInventory==""){
                shopInventory = form("    %s", next);
            }else{
                shopInventory = form("%s, &\n    %s", shopInventory, next);
            }
        }
        SetManualInsn(addr, form("shopInventory &\n%s\n", shopInventory));
        
        /* Comments */
        if(i<=15){
            MakeRptCmt(addr, form("Weapon shop %d", i));
        }else if(i>15&&i<31){
            MakeRptCmt(addr, form("Item shop %d", i-15));
        }else{
            MakeRptCmt(addr, "Debug shop");
        }
        i++;
        addr = addr+len;
    }
}

static parsePromotions(){
    auto addr, i, j, len, promotionSection, next;
    addr = 0x21046;
    i = 0;
    while(addr<0x21072){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        promotionSection = "";
        for(j=addr+1;j<addr+len;j++){
            if(i!=4){
                next = getClassShorthand(Byte(j));
            }else{
                next = getItemShorthand(Byte(j));
            }
            if(promotionSection==""){
                promotionSection = form("    %s", next);
            }else{
                promotionSection = form("%s, %s", promotionSection, next);
            }
        }
        if(i!=4){SetManualInsn(addr, form("promotionSection &\n%s\n", promotionSection));}
        else{SetManualInsn(addr, form("promotionItems &\n%s", promotionSection));}
        
        /* Comments */
        if(i==0){
            MakeRptCmt(addr, "Regular base classes");
        }else if(i==1){
            MakeRptCmt(addr, "Regular promoted classes");
        }else if(i==2){
            MakeRptCmt(addr, "Special base classes");
        }else if(i==3){
            MakeRptCmt(addr, "Special promoted classes");
        }else{
            MakeRptCmt(addr, "Special promotion items");
        }
        i++;
        addr = addr+len;
    }
}

static parseBlacksmithEligibleClassesList(){
    auto addr, j, len, blacksmithClasses, next;
    addr = 0x21EB6;
    while(addr<0x21ED6){
        len = Word(addr)*2+2;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_WORD,len,1);
        blacksmithClasses = "";
        for(j=addr+2;j<addr+len;j=j+2){
            next = getClassShorthand(Word(j));
            if(blacksmithClasses==""){
                blacksmithClasses = next;
            }else{
                blacksmithClasses = form("%s, &\n    %s", blacksmithClasses, next);
            }
        }
        SetManualInsn(addr, form("blacksmithClasses %s\n", blacksmithClasses));
        addr = addr+len;
    }
}

static parseMithrilWeaponClassLists(){
    auto addr, j, len, weaponClass, next;
    addr = 0x21F62;
    while(addr<0x21F92){
        len = Word(addr)*2+2;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_WORD,len,1);
        weaponClass = "";
        for(j=addr+2;j<addr+len;j=j+2){
            next = getClassShorthand(Word(j));
            if(weaponClass==""){
                weaponClass = next;
            }else{
                weaponClass = form("%s, %s", weaponClass, next);
            }
        }
        SetManualInsn(addr, form("mithrilWeaponClass %s", weaponClass));
        addr = addr+len;
    }
}

static parseMithrilWeaponLists(){
    auto addr, j, mithrilWeapons, next;
    addr = 0x21F92;
    while(addr<0x21FD2){
        for(j=addr;j<addr+8;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,8,1);
        mithrilWeapons = "";
        for(j=addr;j<addr+8;j=j+2){
            next = form("%d, %s", Byte(j), getItemShorthand(Byte(j+1)));
            if(mithrilWeapons==""){
                mithrilWeapons = form("    %s", next);
            }else{
                mithrilWeapons = form("%s, &\n    %s", mithrilWeapons, next);
            }
        }
        SetManualInsn(addr, form("mithrilWeapons &\n%s\n", mithrilWeapons));
        addr = addr+8;
    }
}

static parseSpecialCaravanDescriptions(){
    auto addr, j, item, linesNum, message;
    addr = 0x228A2;
    while(addr<0x228A6){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,4,1);
        item = getItemShorthand(Byte(addr));
        linesNum = Byte(addr+1);
        message = getCaravanDescriptionShorthand(Word(addr+2));
        SetManualInsn(addr, form("specialCaravanDescription %s, %d, %s", item, linesNum, message));
        addr = addr+4;
    }
    
    /* Terminator word at address 0x228A6 */
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "tableEnd");
}

static parseUsableOutsideBattleItems(){
    auto addr, j, item;
    addr = 0x229E2;
    while(addr<0x229EB){
        undefineByte(addr);
        MakeByte(addr);
        item = getItemShorthand(Byte(addr));
        SetManualInsn(addr, form("itemIndex %s", item));
        addr++;
    }
    
    /* Terminator byte at address 0x229EB */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
}

static parseUnknownVdpSprites_2358C(){
    parseVdpSprites(0x2358C,0x2364C);
}

static parseConfigurationModeInputs(){
    auto addr, input;
    addr = 0x28FBC;
    while(addr<0x28FCA){
        undefineByte(addr);
        MakeByte(addr);
        input = getInputShorthand(Byte(addr));
        SetManualInsn(addr, form("input %s", input));
        addr++;
    }
    
    /* Terminator byte at address 0x28FCA */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
    
    /* Word alignment byte at address 0x28FCB */
    undefineByte(addr+1);
    MakeByte(addr+1);
    SetManualInsn(addr+1, "wordAlign");
}

static parseDebugModeInputs(){
    auto addr, input;
    addr = 0x28FF0;
    while(addr<0x29000){
        undefineByte(addr);
        MakeByte(addr);
        input = getInputShorthand(Byte(addr));
        SetManualInsn(addr, form("input %s", input));
        addr++;
    }
    
    /* Terminator byte at address 0x29000 */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "tableEnd.b");
    
    /* Word alignment byte at address 0x29001 */
    undefineByte(addr+1);
    MakeByte(addr+1);
    SetManualInsn(addr+1, "wordAlign");
}

static parseFollowers(){
    auto addr, i, j, flag, entity, sprite;
    addr = 0x44338;
    while(addr<0x44388){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,4,1);
        flag = form("%s", ltoa(Byte(addr),10));
        if(Byte(addr+1)<0x1E){
            entity = GetConstName(GetConst(GetEnum("Allies"),Byte(addr+1),-1));
        }else{
            entity = GetConstName(GetConst(GetEnum("Followers"),Byte(addr+1),-1));
        }
        if(Byte(addr+2)!=0xFF){
            sprite = GetConstName(GetConst(GetEnum("Mapsprites"),Byte(addr+2),-1));
        }else{
            sprite = form("$%s", ltoa(Byte(addr+2),16));
        }
        SetManualInsn(addr, form("follower %s, %s, %s, %s", flag, entity, sprite, ltoa(Byte(addr+3),10)));
        addr = addr+4;
    }
    
    /* Terminator word at address 0x44388 */
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "tableEnd");
}

static parseAllyMapSprites(){
    auto addr, sprite, index, allyName;
    addr = 0x44A5E;
    while(addr<0x44A7C){
        undefineByte(addr);
        MakeByte(addr);
        sprite = getMapspriteShorthand(Byte(addr));
        SetManualInsn(addr, form("mapSprite %s", sprite));
        
        /* Provide ally's name as a comment */
        allyName = getAllyName(index);
        MakeRptCmt(addr, form("%d: %s", index, allyName));
        index++;
        addr++;
    }
}

static parseEnemyMapSprites(){
    auto addr, sprite, index, enemyName;
    addr = 0x44AA4;
    while(addr<0x44B4A){
        undefineByte(addr);
        MakeByte(addr);
        sprite = getMapspriteShorthand(Byte(addr));
        SetManualInsn(addr, form("mapSprite %s", sprite));
        
        /* Provide enemy's name as a comment */
        if(index<103){
            enemyName = getEnemyName(index);
            MakeRptCmt(addr, form("%d: %s", index, enemyName));
        }
        index++;
        addr++;
    }
}

static parseSpriteDialogProperties(){
    auto addr, j, sprite, portrait, sfx;
    addr = 0x4567A;
    while(addr<0x45856){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        
        /* Map sprite */
        MakeByte(addr);
        sprite = getMapspriteShorthand(Byte(addr));
        SetManualInsn(addr, form("mapSprite %s", sprite));
        
        /* Portrait */
        MakeByte(addr+1);
        portrait = getPortraitShorthand(Byte(addr+1));
        SetManualInsn(addr+1, form("portrait  %s", portrait));
        
        /* Speech sfx */
        MakeData(addr+2,FF_BYTE,2,1);
        sfx = getSfxShorthand(Byte(addr+2));
        SetManualInsn(addr+2, form("speechSfx %s\n", sfx));
        
        addr = addr+4;
    }
    
    /* Terminator word at address 0x45856 */
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "tableEnd");
}

/*
static parseEnemyLeaderPresence(){
    auto addr, i, j;
    addr = 0x47C8E;
    while(addr<0x47CBC){
        undefineByte(addr);
        MakeByte(addr);
        OpDecimal(addr,0);
        // Provide battle index as a comment
        MakeRptCmt(addr, form("Battle %s", ltoa(i,10)));
        i++;
        addr++;
    }
}
*/

static parseEnemyDefs(){
    auto addr, j, unknownByte, spellPower, level, maxHp, maxMp, baseAtt, baseDef, baseAgi, baseMov;
    auto baseResistance, baseProwess, items, spells, initialStatus, moveType, unknownWord, next, index, enemyName;
    addr = 0x1B1A66;
    while(addr<0x1B30EE){
        for(j=addr;j<addr+56;j++){undefineByte(j);}
        
        /* Unknown byte */
        MakeData(addr,FF_BYTE,10,1);
        unknownByte = Byte(addr);
        SetManualInsn(addr, form("unknownByte %d", unknownByte));
        
        /* Spell power */
        MakeByte(addr+10);
        spellPower = getSpellPowerShorthand(Byte(addr+10));
        SetManualInsn(addr+10, form("spellPower %s", spellPower));
        
        /* Level */
        MakeByte(addr+11);
        level = Byte(addr+11);
        SetManualInsn(addr+11, form("level    %d", level));
        
        /* Max HP */
        MakeData(addr+12,FF_WORD,4,1);
        maxHp = Word(addr+12);
        SetManualInsn(addr+12, form("maxHp    %d", maxHp));
        
        /* Max MP */
        MakeData(addr+16,FF_BYTE,2,1);
        maxMp = Byte(addr+16);
        SetManualInsn(addr+16, form("maxMp    %d", maxMp));
        
        /* Base ATT */
        MakeData(addr+18,FF_BYTE,2,1);
        baseAtt = Byte(addr+18);
        SetManualInsn(addr+18, form("baseAtt  %d", baseAtt));
        
        /* Base DEF */
        MakeData(addr+20,FF_BYTE,2,1);
        baseDef = Byte(addr+20);
        SetManualInsn(addr+20, form("baseDef  %d", baseDef));
        
        /* Base AGI */
        MakeData(addr+22,FF_BYTE,2,1);
        baseAgi = Byte(addr+22);
        SetManualInsn(addr+22, form("baseAgi  %d", baseAgi));
        
        /* Base MOV */
        MakeData(addr+24,FF_BYTE,2,1);
        baseMov = Byte(addr+24);
        SetManualInsn(addr+24, form("baseMov  %d", baseMov));
        
        /* Base resistance */
        MakeData(addr+26,FF_WORD,4,1);
        if(Word(addr+26)==0){
            baseResistance = getResistanceNoneShorthand(Word(addr+26));
        }else{
            baseResistance = getResistanceShorthand(Word(addr+26));
        }
        SetManualInsn(addr+26, form("baseResistance %s", baseResistance));
        
        /* Base prowess */
        MakeData(addr+30,FF_BYTE,2,1);
        baseProwess = getProwessShorthand(Byte(addr+30));
        SetManualInsn(addr+30, form("baseProwess    %s", baseProwess));
        
        /* Items */
        MakeData(addr+32,FF_WORD,8,1);
        items = "";
        for(j=addr+32;j<addr+40;j=j+2){
            next = getItemShorthand(Word(j));
            if(items==""){
                items = form("    %s", next);
            }else{
                items = form("%s, &\n    %s", items, next);
            }
        }
        SetManualInsn(addr+32, form("items &\n%s", items));
        
        /* Spells */
        MakeData(addr+40,FF_BYTE,4,1);
        spells = "";
        for(j=addr+40;j<addr+44;j++){
            next = getSpellShorthand(Byte(j));
            if(spells==""){
                spells = form("    %s", next);
            }else{
                spells = form("%s, &\n    %s", spells, next);
            }
        }
        SetManualInsn(addr+40, form("spells &\n%s", spells));
        
        /* Initial status effects */
        MakeData(addr+44,FF_BYTE,5,1);
        if(Word(addr+44)==0){
            initialStatus = getStatusEffectNoneShorthand(Word(addr+44));
        }else{
            initialStatus = getStatusEffectsShorthand(Word(addr+44));
        }
        SetManualInsn(addr+44, form("initialStatus %s", initialStatus));
        
        /* Move type */
        MakeByte(addr+49);
        moveType = getMoveTypeShorthand(Byte(addr+49));
        SetManualInsn(addr+49, form("moveType      %s", moveType));
        
        /* Unknown word */
        MakeData(addr+50,FF_BYTE,6,1);
        unknownWord = Word(addr+52);
        SetManualInsn(addr+50, form("unknownWord   %d\n", unknownWord));
        
        /* Provide enemy's name as a comment */
        enemyName = getEnemyName(index);
        MakeRptCmt(addr, form("%d: %s", index, enemyName));
        index++;
        addr = addr+56;
    }
}

static parseRandomBattles(){
    auto addr, j, len, battles, next;
    addr = 0x1B6DB0;
    while(addr<0x1B6DBC){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        battles = "";
        for(j=addr+1;j<addr+len;j++){
            next = getBattleShorthand(Byte(j));
            if(battles==""){
                battles = form("%s", next);
            }else{
                battles = form("%s, &\n        %s", battles, next);
            }
        }
        SetManualInsn(addr, form("battles %s", battles));
        addr = addr+len;
    }
}

static parseEnemyUpgradeDefs(){
    auto addr, j, len, range, firstEnemy, lastEnemy, excludedEnemies, next;
    addr = 0x1B6DBC;
    while(addr<0x1B6DDA){
        for(j=addr;j<addr+3;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,3,1);
        range = Byte(addr);
        firstEnemy = getEnemyShorthand(Byte(addr+1));
        lastEnemy = getEnemyShorthand(Byte(addr+2));
        SetManualInsn(addr, form("upgradeRange    %d, %s, %s", range, firstEnemy, lastEnemy));
        
        /* Excluded enemies list */
        len = Byte(addr+3)+1;
        for(j=addr+3;j<addr+len+3;j++){undefineByte(j);}
        MakeData(addr+3,FF_BYTE,len,1);
        excludedEnemies = "";
        for(j=addr+4;j<addr+len+3;j++){
            next = getEnemyShorthand(Byte(j));
            if(excludedEnemies==""){
                excludedEnemies = form("%s", next);
            }else{
                excludedEnemies = form("%s, %s", excludedEnemies, next);
            }
        }
        SetManualInsn(addr+3, form("excludedEnemies %s", excludedEnemies));
        addr = addr+len+3;
    }
}

static parseStatGrowthCurves(){
    auto addr, i, j, curveParams, next;
    addr = 0x1EE02C;
    while(addr<0x1EE270){
        for(j=addr;j<addr+116;j++){undefineByte(j);}
        i = 2;
        for(j=addr;j<addr+116;j=j+4){
            MakeData(j,FF_WORD,4,1);
            curveParams = form("%d, %d", Word(j), Word(j+2));
            if(i!=30){
                SetManualInsn(j, form("dc.w %s", curveParams));
            }else{
                SetManualInsn(j, form("dc.w %s\n", curveParams));
            }
            
            /* Comments */
            MakeRptCmt(j, form(" level %d", i));
            i++;
        }
        addr = addr+116;
    }
}

static parseAllyStats(){
    auto addr, j, forClass, curve, start, proj, offset, next, count, spellList, allyName;
    addr = 0x1EE2F0;
    while(addr<0x1EE7CF){
        for(j=addr;j<addr+16;j++){undefineByte(j);}
        
        /* For class */
        MakeByte(addr);
        forClass = getClassShorthand(Byte(addr));
        SetManualInsn(addr, form("forClass  %s", forClass));
        
        /* HP growth */
        MakeData(addr+1,FF_BYTE,3,1);
        curve = getGrowthCurveShorthand(Byte(addr+1));
        start = Byte(addr+2);
        proj = Byte(addr+3);
        SetManualInsn(addr+1, form("hpGrowth  %d, %d, %s", start, proj, curve));
        
        /* MP growth */
        MakeData(addr+4,FF_BYTE,3,1);
        curve = getGrowthCurveShorthand(Byte(addr+4));
        start = Byte(addr+5);
        proj = Byte(addr+6);
        SetManualInsn(addr+4, form("mpGrowth  %d, %d, %s", start, proj, curve));
        
        /* ATT growth */
        MakeData(addr+7,FF_BYTE,3,1);
        curve = getGrowthCurveShorthand(Byte(addr+7));
        start = Byte(addr+8);
        proj = Byte(addr+9);
        SetManualInsn(addr+7, form("attGrowth %d, %d, %s", start, proj, curve));
        
        /* DEF growth */
        MakeData(addr+10,FF_BYTE,3,1);
        curve = getGrowthCurveShorthand(Byte(addr+10));
        start = Byte(addr+11);
        proj = Byte(addr+12);
        SetManualInsn(addr+10, form("defGrowth %d, %d, %s", start, proj, curve));
        
        /* AGI growth */
        MakeData(addr+13,FF_BYTE,3,1);
        curve = getGrowthCurveShorthand(Byte(addr+13));
        start = Byte(addr+14);
        proj = Byte(addr+15);
        SetManualInsn(addr+13, form("agiGrowth %d, %d, %s", start, proj, curve));
        
        /* Count spell list bytes */
        offset = 16;
        next = Byte(addr+offset);
        count = 1;
        while(next!=254&&next!=255){
            offset++;
            next = Byte(addr+offset);
            count++;
        }
        
        /* Spell list */
        offset++;
        if(Byte(addr+16)==254){
            undefineByte(addr+16);
            MakeByte(addr+16);
            SetManualInsn(addr+16, "useFirstSpellList\n");
        }else{
            for(j=addr+16;j<addr+offset;j++){undefineByte(j);}
            MakeData(addr+16,FF_BYTE,count,1);
            spellList = "";
            for(j=addr+16;j<addr+offset;j=j+2){
                if(Byte(j)!=254&&Byte(j)!=255){
                    next = getSpellShorthand(Byte(j+1));
                    if(spellList==""){
                        spellList = form("    %d, %s", Byte(j), next);
                    }else{
                        spellList = form("%s, &\n    %d, %s", spellList, Byte(j), next);
                    }
                }
            }
            if(spellList!=""){
                SetManualInsn(addr+16, form("spellList &\n%s\n", spellList));
            }else{
                SetManualInsn(addr+16, form("spellList %s\n", spellList));
            }
        }
        addr = addr+offset;
    }
    
    /* Word align at address 0x1EE7CF */
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "wordAlign");
}

static parseAllyStartDefs(){
    auto addr, j, startClass, startLevel, startItems, next, index, allyName;
    addr = 0x1EE7D0;
    while(addr<0x1EE890){
        for(j=addr;j<addr+6;j++){undefineByte(j);}
        
        /* Starting class */
        MakeByte(addr);
        startClass = getClassShorthand(Byte(addr));
        SetManualInsn(addr, form("startClass %s", startClass));
        
        /* Starting level */
        MakeByte(addr+1);
        startLevel = Byte(addr+1);
        SetManualInsn(addr+1, form("startLevel %d", startLevel));
        
        /* Starting items */
        MakeData(addr+2,FF_BYTE,4,1);
        startItems = "";
        for(j=addr+2;j<addr+6;j++){
            next = getItemShorthand(Byte(j));
            if(startItems==""){
                startItems = form("    %s", next);
            }else{
                startItems = form("%s, &\n    %s", startItems, next);
            }
        }
        SetManualInsn(addr+2, form("startItems &\n%s\n", startItems));
        
        /* Provide ally's name as a comment */
        if(index<30){
            allyName = getAllyName(index);
            MakeRptCmt(addr, form("%d: %s", index, allyName));
        }
        index++;
        addr = addr+6;
    }
}

static parseClassDefs(){
    auto addr, j, mov, resistance, moveType, prowess, index, className;
    addr = 0x1EE890;
    while(addr<0x1EE930){
        for(j=addr;j<addr+5;j++){undefineByte(j);}
        
        /* MOV */
        MakeByte(addr);
        mov = Byte(addr);
        SetManualInsn(addr, form("mov %d", mov));
        
        /* Resistance */
        MakeWord(addr+1);
        if(Word(addr+1)==0){
            resistance = getResistanceNoneShorthand(Word(addr+1));
        }else{
            resistance = getResistanceShorthand(Word(addr+1));
        }
        SetManualInsn(addr+1, form("resistance %s", resistance));
        
        /* Move type */
        MakeByte(addr+3);
        moveType = getMoveTypeShorthand(Byte(addr+3));
        SetManualInsn(addr+3, form("moveType   %s", moveType));
        
        /* Prowess */
        MakeByte(addr+4);
        prowess = getProwessShorthand(Byte(addr+4));
        SetManualInsn(addr+4, form("prowess    %s\n", prowess));
        
        /* Provide class name as a comment */
        className = getClassName(index);
        MakeRptCmt(addr, form("%d: %s", index, className));
        index++;
        addr = addr+5;
    }
}


static parseMapData(){
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,sc,flag,flagDescription,parameter,flagmapFile,lineNumber,currentLine,entry;
    i = 0;
    start = 0x94B8A;
    end = 0x94CC6;
    addr = start;
    lastEntryDataEnd = 0xC7ECC;
    chunkEnd = 0xC8000;
    i = 0;
    action = 1;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);    
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        
        /* tileset data */
        MakeByte(dref);
        SetManualInsn(dref, form("mapPalette  %d", Byte(dref)));
        MakeByte(dref+1);
        SetManualInsn(dref+1, form("mapTileset1 %d", Byte(dref+1)));
        MakeByte(dref+2);
        SetManualInsn(dref+2, form("mapTileset2 %d", Byte(dref+2)));
        MakeByte(dref+3);
        SetManualInsn(dref+3, form("mapTileset3 %d", Byte(dref+3)));
        MakeByte(dref+4);
        SetManualInsn(dref+4, form("mapTileset4 %d", Byte(dref+4)));
        MakeByte(dref+5);
        SetManualInsn(dref+5, form("mapTileset5 %d", Byte(dref+5)));

        /* Areas */
        section = Dfirst(dref+6+4*2);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+30;j++){undefineByte(j);}
                MakeWord(sc);
                MakeWord(sc+2);
                SetManualInsn(sc, form("; Area %d",entry));
                SetManualInsn(sc+2, form("    mainLayerStart      %d, %d", Word(sc), Word(sc+2)));
                MakeDword(sc+4);
                SetManualInsn(sc+4, form("    mainLayerEnd        %d, %d", Word(sc+4), Word(sc+6)));
                MakeDword(sc+8);
                SetManualInsn(sc+8, form("    scndLayerFgndStart  %d, %d", Word(sc+8), Word(sc+10)));
                MakeDword(sc+12);
                SetManualInsn(sc+12, form("    scndLayerBgndStart  %d, %d", Word(sc+12), Word(sc+14)));
                MakeDword(sc+16);
                SetManualInsn(sc+16, form("    mainLayerParallax   %d, %d", Word(sc+16), Word(sc+18)));
                MakeDword(sc+20);
                SetManualInsn(sc+20, form("    scndLayerParallax   %d, %d", Word(sc+20), Word(sc+22)));
                MakeWord(sc+24);
                SetManualInsn(sc+24, form("    mainLayerAutoscroll %d, %d", Byte(sc+24), Byte(sc+25)));
                MakeWord(sc+26);
                SetManualInsn(sc+26, form("    scndLayerAutoscroll %d, %d", Byte(sc+26), Byte(sc+27)));
                MakeByte(sc+28);
                SetManualInsn(sc+28, form("    mainLayerType    %d", Byte(sc+28)));
                MakeByte(sc+29);
                SetManualInsn(sc+29, form("    areaDefaultMusic %d", Byte(sc+29)));
                sc = sc+30;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }
        
        /* Flag block copies */
        section = Dfirst(dref+6+4*3);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+8;j++){undefineByte(j);}
                MakeWord(sc);
                flagDescription = "";
                flag = Word(sc);  
                flagDescription = getFlagDesc(flag);  
                MakeRptCmt(sc,flagDescription);
                SetManualInsn(sc, form("fbcFlag %s", ltoa(Word(sc),10)));
                MakeWord(sc+2);
                SetManualInsn(sc+2, form("  fbcSource %d, %d", Byte(sc+2), Byte(sc+3)));
                MakeWord(sc+4);
                SetManualInsn(sc+4, form("  fbcSize   %d, %d", Byte(sc+4), Byte(sc+5)));
                MakeWord(sc+6);
                SetManualInsn(sc+6, form("  fbcDest   %d, %d", Byte(sc+6), Byte(sc+7)));
                sc = sc+8;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Step block copies */
        section = Dfirst(dref+6+4*4);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+8;j++){undefineByte(j);}
                MakeWord(sc);
                SetManualInsn(sc, form("sbc %d, %d", Byte(sc), Byte(sc+1)));
                MakeWord(sc+2);
                SetManualInsn(sc+2, form("  sbcSource %d, %d", Byte(sc+2), Byte(sc+3)));
                MakeWord(sc+4);
                SetManualInsn(sc+4, form("  sbcSize   %d, %d", Byte(sc+4), Byte(sc+5)));
                MakeWord(sc+6);
                SetManualInsn(sc+6, form("  sbcDest   %d, %d", Byte(sc+6), Byte(sc+7)));
                sc = sc+8;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Layer 2 block copies */
        section = Dfirst(dref+6+4*5);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+8;j++){undefineByte(j);}
                MakeWord(sc);
                SetManualInsn(sc, form("slbc %d, %d", Byte(sc), Byte(sc+1)));
                MakeWord(sc+2);
                SetManualInsn(sc+2, form("  slbcSource %d, %d", Byte(sc+2), Byte(sc+3)));
                MakeWord(sc+4);
                SetManualInsn(sc+4, form("  slbcSize   %d, %d", Byte(sc+4), Byte(sc+5)));
                MakeWord(sc+6);
                SetManualInsn(sc+6, form("  slbcDest   %d, %d", Byte(sc+6), Byte(sc+7)));
                sc = sc+8;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Warps */
        section = Dfirst(dref+6+4*6);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+8;j++){undefineByte(j);}
                MakeWord(sc);
                SetManualInsn(sc, form("mWarp %d, %d", Byte(sc), Byte(sc+1)));
                MakeByte(sc+2);
                if(Byte(sc+2)!=0){
                    SetManualInsn(sc+2, form("  warpScroll %s", getDirection(Byte(sc+2)&0xF)));
                }else{
                    SetManualInsn(sc+2, "  warpNoScroll");
                }
                MakeByte(sc+3);
                SetManualInsn(sc+3, form("  warpMap    %s", getMap(Byte(sc+3))));
                MakeWord(sc+4);
                SetManualInsn(sc+4, form("  warpDest   %d, %d", Byte(sc+4), Byte(sc+5)));
                MakeWord(sc+6);
                SetManualInsn(sc+6, form("  warpFacing %s", getDirection(Byte(sc+6))));
                sc = sc+8;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Chest Items */
        section = Dfirst(dref+6+4*7);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+4;j++){undefineByte(j);}
                MakeDword(sc);                
                flagDescription = "";
                flag = Word(sc);
                flagDescription = getFlagDesc(flag);   
                MakeRptCmt(sc,flagDescription);
                SetManualInsn(sc, form("mapItem %d, %d, %s, %s", Byte(sc), Byte(sc+1), ltoa(Byte(sc+2),10),getItemShorthand(Byte(sc+3))));
                sc = sc+4;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Non-Chest Items */
        section = Dfirst(dref+6+4*8);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+4;j++){undefineByte(j);}
                MakeDword(sc);                
                flagDescription = "";
                flag = Word(sc);  
                flagDescription = getFlagDesc(flag);  
                MakeRptCmt(sc,flagDescription);
                SetManualInsn(sc, form("mapItem %d, %d, %s, %s", Byte(sc), Byte(sc+1), ltoa(Byte(sc+2),10),getItemShorthand(Byte(sc+3))));
                sc = sc+4;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }

        /* Animations */
        section = Dfirst(dref+6+4*9);
        if(section!=BADADDR){
            dataEnd = 0;
            j = section+1;
            while(dataEnd==0){
                from = DfirstB(j);
                while(from!=BADADDR){
                    if(from>=start&&from<chunkEnd){
                        dataEnd = j;
                    }
              from=DnextB(addr,from);      
                }
                j++;
                if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
            }
            sc = section;
            entry = 0;
            if(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+4;j++){undefineByte(j);}
                MakeDword(sc);
                SetManualInsn(sc, form("mapAnimation %d, %d", Word(sc), Word(sc+2)));
                sc = sc+4;
            }
            while(Word(sc)!=0xFFFF){
                for(j=sc;j<sc+8;j++){undefineByte(j);}
                MakeData(sc,FF_BYTE,8,1);
                SetManualInsn(sc, form("  mapAnimEntry %d, %d, $%s, %d", Word(sc), Word(sc+2), ltoa(Word(sc+4),16), Word(sc+6)));
                sc = sc+8;
                entry++;
            }
            for(j=sc;j<sc+1;j++){undefineByte(j);}
            MakeWord(sc);
            SetManualInsn(sc, "endWord");
        }
        
        addr=addr+4;
        i++;
    }
    
}



static parseVdpSprites(start,end){
    auto addr, i, j, ypos, size, sizeAndLink, vdpTile, xpos;
    addr = start;
    while(addr<end){
        for(j=addr;j<addr+8;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,8,1);
        ypos = ltoa(Word(addr),10);
        size = getVdpSpriteSizeShorthand(Word(addr+2)&0xFF00);
        sizeAndLink = form("%s|%s", size, ltoa(Word(addr+2)&0xFF,10));
        vdpTile = form("%s|%s", ltoa(Word(addr+4)&0x7FF,10), getVdpTileShorthand(Word(addr+4)&0xF800));
        xpos = ltoa(Word(addr+6),10);
        SetManualInsn(addr, form("vdpSprite %s, %s, %s, %s", ypos, sizeAndLink, vdpTile, xpos));
        addr = addr+8;
    }
}



static getAiCommandShorthand(cmd){
    return getShorthand(cmd,"AiCommands","AICOMMAND_");
}

static getAllyShorthand(cmd){
    return getShorthand(cmd,"Allies","ALLY_");
}

static getAllyBattlespriteShorthand(cmd){
    return getShorthand(cmd,"AllyBattleSprites","ALLYBATTLESPRITE_");
}

static getBattleBackgroundShorthand(cmd){
    return getShorthand(cmd,"BattleBackgrounds","BATTLEBACKGROUND_");
}

static getBattleShorthand(cmd){
    return getShorthand(cmd,"Battles","BATTLE_");
}

static getCaravanDescriptionShorthand(cmd){
    return getShorthand(cmd,"Messages","MESSAGE_CARAVANDESC_");
}

static getClassShorthand(cmd){
    return getShorthand(cmd,"Classes","CLASS_");
}

static getClassTypeShorthand(cmd){
    return getShorthand(cmd,"ClassTypes","CLASSTYPE_");
}

static getEnemyBattlespriteShorthand(cmd){
    return getShorthand(cmd,"EnemyBattleSprites","ENEMYBATTLESPRITE_");
}

static getEnemyShorthand(cmd){
    return getShorthand(cmd,"Enemies","ENEMY_");
}

static getEquipEffectShorthand(cmd){
    return getShorthand(cmd,"EquipEffects","EQUIPEFFECT_");
}

static getEquipFlagsShorthand(cmd){
    return getBitfieldShorthands(cmd,"EquipFlags","EQUIPFLAG_");
}

static getEquipFlagsOtherShorthand(cmd){
    return getShorthand(cmd,"EquipFlags_Other","EQUIPFLAG_");
}

static getFollowerShorthand(cmd){
    return getShorthand(cmd,"Followers","FOLLOWER_");
}

static getGrowthCurveShorthand(cmd){
    return getShorthand(cmd,"GrowthCurves","GROWTHCURVE_");
}

static getInputShorthand(cmd){
    return getBitfieldShorthands(cmd,"Controller_Input","INPUT_");
}

static getItemShorthand(cmd){
    return getBitfieldShorthands(cmd,"Items","ITEM_");
}

static getItemTypeShorthand(cmd){
    return getBitfieldShorthands(cmd,"ItemType","ITEMTYPE_");
}

static getItemTypeNoneShorthand(cmd){
    return getShorthand(cmd,"ItemType_None","ITEMTYPE_");
}

static getLandEffectSettingShorthand(cmd){
    return getBitfieldShorthands(cmd,"LandEffectSettings","LANDEFFECTSETTING_");
}

static getLandEffectSettingObstructedShorthand(cmd){
    return getShorthand(cmd,"LandEffectSetting_Obstructed","LANDEFFECTSETTING_");
}

static getMapspriteShorthand(cmd){
    return getShorthand(cmd,"Mapsprites","MAPSPRITE_");
}

static getMoveTypeShorthand(cmd){
    return getBitfieldShorthands(cmd,"MoveType","MOVETYPE_UPPER_");
}

static getPortraitShorthand(cmd){
    return getShorthand(cmd,"Portraits","PORTRAIT_");
}

static getProwessShorthand(cmd){
    return getBitfieldShorthands(cmd,"Prowess","PROWESS_");
}

static getResistanceShorthand(cmd){
    return getBitfieldShorthands(cmd,"Resistance","RESISTANCE_");
}

static getResistanceNoneShorthand(cmd){
    return getShorthand(cmd,"Resistance","RESISTANCE_");
}

static getSfxShorthand(cmd){
    return getShorthand(cmd,"Sfx","SFX_");
}

static getSpellAnimationShorthand(cmd){
    return getBitfieldShorthands(cmd,"SpellAnimations","SPELLANIMATION_");
}

static getSpellElementShorthand(cmd){
    return getShorthand(cmd,"SpellElements","SPELLELEMENT_");
}

static getSpellPowerShorthand(cmd){
    return getShorthand(cmd,"SpellPower","SPELLPOWER_");
}

static getSpellPropertiesShorthand(cmd){
    return getBitfieldShorthands(cmd,"SpellProps","SPELLPROPS_");
}

static getSpellShorthand(cmd){
    return getBitfieldShorthands(cmd,"Spells","SPELL_");
}

static getStatusEffectNoneShorthand(cmd){
    return getShorthand(cmd,"StatusEffect_None","STATUSEFFECT_");
}

static getStatusEffectsShorthand(cmd){
    return getBitfieldShorthands(cmd,"StatusEffects","STATUSEFFECT_");
}

static getVdpSpriteSizeShorthand(cmd){
    return getBitfieldShorthands(cmd,"VdpSpriteSize","VDPSPRITESIZE_");
}

static getVdpTileShorthand(cmd){
    return getBitfieldShorthands(cmd,"VdpTiles","VDPTILE_");
}

static getWeaponPaletteShorthand(cmd){
    return getShorthand(cmd,"WeaponPalettes","WEAPONPALETTE_");
}

static getWeaponSpriteShorthand(cmd){
    return getShorthand(cmd,"WeaponSprites","WEAPONSPRITE_");
}



static getBitfieldShorthands(cmd,enumName,prefix){
    auto id, bitmask, output, value, next;
    id = GetEnum(enumName);
    bitmask = GetFirstBmask(id);
    output = "";
    while(bitmask!=-1){
        value = cmd & bitmask;
        next = getShorthandEx(value,enumName,prefix,bitmask);
        if(next!=""&&next!="0"){
            if(output==""){
                output = next;
            }else{
                output = form("%s|%s",output,next);
            }
        }
        bitmask = GetNextBmask(id,bitmask);
    }
    return output;
}

static getShorthand(cmd,enumName,prefix){
    return getShorthandEx(cmd,enumName,prefix,-1);
}

static getShorthandEx(cmd,enumName,prefix,bitmask){
    auto id, constant, j, constId;
    id = GetEnum(enumName);
    constant = GetFirstConst(id,bitmask);
    while(constant!=-1){
        j=0;
        constId = GetConstEx(id,constant,j,bitmask);
        while(constId!=-1){
            if(constant==cmd){
                return substr(GetConstName(constId),strlen(prefix),-1);
            }
            j++;
            constId = GetConstEx(id,constant,j,bitmask);
        }
        constant = GetNextConst(id,constant,bitmask);
    }
    return form("%d",cmd);
}



static getAllyName(index){
    return findName(0xFAD6,index);
}

static getClassName(index){
    return findName(0x17F3E,index);
}

static getEnemyName(index){
    return findName(0xFB8A,index);
}

static getItemName(index){
    return findNameWithoutSpecialChar(0x1796E,index);
}

static getSpellName(index){
    return findName(0xF9C4,index);
}



static findName(ea,index){
    return findNameEx(ea,index,0);
}

static findNameWithoutSpecialChar(ea,index){
    return findNameEx(ea,index,1);
}

/*
 *  Return name from table of strings prefixed with length
 *      ea            - start of table address
 *      index         - name index
 *      noSpecialChar - optionally convert special characters into spaces
 */ 
static findNameEx(ea,index,noSpecialChar){
    auto size;
    while(index>0){
        size = Byte(ea)+1;
        ea = ea+size;
        index--;
    }
    size = Byte(ea)+1;
    return StrEx(ea,size,noSpecialChar);
}



static Str(ea,size){
    return StrEx(ea,size,0);
}

static StrWithoutSpecialChar(ea,size){
    return StrEx(ea,size,1);
}

/*
 *  Return string prefixed with length at the specified address
 *      ea            - linear address
 *      noSpecialChar - optionally convert special characters into spaces
 */
static StrEx(ea,size,noSpecialChar){
    auto addr, len, str, j, nextChar;
    addr = ea+1;
    len = size-1;
    str = "";
    for(j=addr;j<addr+len;j++){
        nextChar = Byte(j);
        if(noSpecialChar!=0&&(nextChar==11||nextChar==13)){
            nextChar = 32;
        }
        str = form("%s%c",str,nextChar);
    }
    return str;
}

static getDirection(cmd){
    auto id,enumSize,constant,j,constId,output;
    id = GetEnum("Direction");
    enumSize = GetEnumSize(id);
    constant = GetFirstConst(id,-1);    
    while(constant!=-1){
            j=0;
            constId = GetConstEx(id,constant,j,-1);
            while(constId != -1){
                if(constant==cmd){
                    return GetConstName(constId);
                }
                j++;
                constId = GetConstEx(id,constant,j,-1);
            }
            constant = GetNextConst(id,constant,-1);
    }
    return form("%s",ltoa(cmd,10));
}

static getMap(cmd){
    auto id,enumSize,constant,j,constId,output;
    id = GetEnum("Maps");
    enumSize = GetEnumSize(id);
    constant = GetFirstConst(id,-1);    
    while(constant!=-1){
            j=0;
            constId = GetConstEx(id,constant,j,-1);
            while(constId != -1){
                if(constant==cmd){
                    return GetConstName(constId);
                }
                j++;
                constId = GetConstEx(id,constant,j,-1);
            }
            constant = GetNextConst(id,constant,-1);
    }
    return form("%s",ltoa(cmd,10));
}

/* 
 *  Makes sure byte at addr is
 *  clean for new formatting
 */
static undefineByte(addr){
        auto from;
        from = DfirstB(addr);
        /*
        while(from!=BADADDR){
            //Message(form("Removed DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
        }        
        from = RfirstB(addr);
        while(from!=BADADDR){
            //Message(form("Removed Code XRrf at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
        }    
        */            
        MakeUnkn(addr,DOUNK_DELNAMES);
        //MakeNameEx(addr,"",0);
        SetManualInsn(addr,"");
}



/* INITIALIZE ARRAYS OF STRINGS TO OPTIMIZE EXTERNAL FILE ACCESS */

static initializeArrays(){
    
    loadArray("flags.txt","Flags");
    loadArray("text.txt","Text");    
    
}

static loadArray(fileName, arrayName){

    auto file, arrayId, idx, str;
    
    file = fopen(fileName,"r");
    arrayId = CreateArray(arrayName);
    idx = 0;
    while(str!=-1){
        str = readstr(file);
        if(str!=-1){
            str = form("%s",substr(str,5,strlen(str)-1));
            SetArrayString(arrayId, idx, str);
        }
        idx++;
    }
    fclose(file);
    
}

/* DELETE ARRAYS FROM IDB AFTER USAGE */

static deleteArrays(){

    DeleteArray(GetArrayId("Flags")); 
    DeleteArray(GetArrayId("Text")); 
    
}

static getTextLine(index){

    auto dialogLine;
    
    dialogLine = GetArrayElement(AR_STR, GetArrayId("Text"), index);
    if(dialogLine==-1){
        dialogLine="";
    }else{
        dialogLine = form("\"%s\"",dialogLine);
    }
    
    return dialogLine;

}


static getFlagDesc(flag){

    auto flagDesc;     
            
    flagDesc = GetArrayElement(AR_STR, GetArrayId("Flags"), flag);
    if(flagDesc==-1){
        flagDesc="";
    }
    
    return flagDesc;

}