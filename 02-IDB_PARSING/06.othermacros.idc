


#include <idc.idc>


static main(void){
    Message("\nPARSING DATA STRUCTURES INTO MACROS ...\n");
    parseFlaggedSwitchedMaps();
    parseBattleMapCoords();    
    parseSavePointMapCoords();
    parseRaftResetMapCoords();
    parseClassTypes();
    parseCriticalHitSettings();
    parseItemBreakMessages();
    parseEnemyItemDrops();
    //parseEnemyGold();
    parseSpellElements();
    parseSpellNames();
    parseAllyNames();
    parseEnemyNames();
    parseItemDefs();
    parseSpellDefs();
    parseItemNames();
    parseClassNames();
    parseAllyBattleSprites();
    parseEnemyBattleSprites();
    parseWeaponSprites();
    parseShopDefs();
    parsePromotions();
    parseMithrilWeaponClassLists();
    parseMithrilWeaponLists();
    parseSpecialCaravanDescriptions();
    parseUsableOutsideBattleItems();
    parseFollowers();
    parseAllyMapSprites();
    parseEnemyMapSprites();
    parseSpriteDialogProperties();
    //parseEnemyLeaderPresence();
    parseEnemyDefs();
    parseRandomBattles();
    parseStatGrowthCurves();
    parseAllyStats();
    parseAllyStartDefs();
    parseClassDefs();
    parseMapData();
    Message("END OF PARSING.\n");    
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
        parameter = ltoa(flag,16);
        while(strlen(parameter)<4){
            parameter=form("0%s",parameter);
        }
        flagmapFile = fopen("flagmap.txt","r");
        while(flagDescription==""){
        lineNumber = lineNumber + 1;
            currentLine = readstr(flagmapFile);
            if(currentLine==-1){
                break;
            }
            if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
                flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
            }
        }
        fclose(flagmapFile);    
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
    auto addr, i, j, classType, className;
    addr = 0x853A;
    while(addr<0x855A){
        undefineByte(addr);
        MakeByte(addr);
        classType = substr(GetConstName(GetConst(GetEnum("ClassTypes"),Byte(addr),-1)),strlen("CLASSTYPE_"),-1);
        SetManualInsn(addr, form("classType %s", classType));
        // Provide class name as a comment
        className = findName(0x17F3E,i);
        MakeRptCmt(addr, form("%s", className));
        i++;
        addr++;
    }
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
        item = GetBitfieldConstNames(GetEnum("Items"),Byte(addr),strlen("ITEM_"),0);
        msgOffset = Byte(addr+1);
        SetManualInsn(addr, form("itemBreakMessage %s, %d", item, msgOffset));
        addr = addr+2;
    }
    // Terminator word at address 0xBD22
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "\ntableEnd");
}

static parseEnemyItemDrops(){
    auto addr, i, j, battle, enemyEntity, itemDrop, dropFlag;
    addr = 0xBE52;
    while(addr<0xBECA){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        // Battle
        MakeByte(addr);
        battle = substr(GetConstName(GetConst(GetEnum("Battles"),Byte(addr),-1)),strlen("BATTLE_"),-1);
        SetManualInsn(addr, form("battle      %s", battle));
        // Enemy entity
        MakeByte(addr+1);
        enemyEntity = Byte(addr+1)-128;
        SetManualInsn(addr+1, form("enemyEntity %d", enemyEntity));
        // Item drop
        MakeByte(addr+2);
        itemDrop = GetBitfieldConstNames(GetEnum("Items"),Byte(addr+2),strlen("ITEM_"),0);
        SetManualInsn(addr+2, form("itemDrop    %s", itemDrop));
        // Drop flag
        MakeByte(addr+3);
        dropFlag = Byte(addr+3);
        SetManualInsn(addr+3, form("dropFlag    %d\n", dropFlag));
        addr = addr+4;
    }
    // Terminator word at address 0xBECA
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
    auto addr, i, j, spellElement, spellName;
    addr = 0xC24E;
    while(addr<0xC27A){
        undefineByte(addr);
        MakeByte(addr);
        spellElement = substr(GetConstName(GetConst(GetEnum("SpellElements"),Byte(addr),-1)),strlen("SPELLELEMENT_"),-1);
        SetManualInsn(addr, form("spellElement %s", spellElement));
        // Provide spell name as a comment
        spellName = findName(0xF9C4,i);
        MakeRptCmt(addr, form("%s", spellName));
        i++;
        addr++;
    }
}

static parseSpellNames(){
    auto addr, j, len, name;
    addr = 0xF9C4;
    while(addr<0xFAD6){
        len = Byte(addr)+1;
        name = Str(addr+1,len-1);
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        SetManualInsn(addr, form("spellName \"%s\"", name));
        addr = addr+len;
    }
}

static parseAllyNames(){
    auto addr, j, len, name;
    addr = 0xFAD6;
    while(addr<0xFB8A){
        len = Byte(addr)+1;
        name = Str(addr+1,len-1);
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        SetManualInsn(addr, form("allyName \"%s\"", name));
        addr = addr+len;
    }
}

static parseEnemyNames(){
    auto addr, j, len, name;
    addr = 0xFB8A;
    while(addr<0xFF87){
        len = Byte(addr)+1;
        name = Str(addr+1,len-1);
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        SetManualInsn(addr, form("enemyName \"%s\"", name));
        addr = addr+len;
    }
    // Manual fix for Jaro's bugged entry
    SetManualInsn(0xFF5E, form("enemyName \"JAR\", 0"));
    MakeRptCmt(0xFF5E,"here is the cause of the infamous JAR bug, an innocent typo :)");
}

static parseItemDefs(){
    auto addr, i, j, equipFlags, maxRange, minRange, price, itemType, useSpell, equipEffects, next, itemName;
    addr = 0x16EA6;
    while(addr<0x176A6){
        for(j=addr;j<addr+16;j++){undefineByte(j);}
        // Equip flags
        MakeDword(addr);
        if(Dword(addr)==0||Dword(addr)==-1){
            equipFlags = substr(GetConstName(GetConst(GetEnum("EquipFlags_Other"),Dword(addr),-1)),strlen("EQUIPFLAG_"),-1);
            SetManualInsn(addr, form("equipFlags %s", equipFlags));
        }
        else{
            equipFlags = GetBitfieldConstNames(GetEnum("EquipFlags"),Dword(addr),strlen("EQUIPFLAG_"),0);
            SetManualInsn(addr, form("equipFlags &\n%s", equipFlags));
        }
        // Range
        MakeData(addr+4,FF_BYTE,2,1);
        maxRange = Byte(addr+4);
        minRange = Byte(addr+5);
        SetManualInsn(addr+4, form("range %d, %d", minRange, maxRange));
        // Price
        MakeWord(addr+6);
        price = Word(addr+6);
        SetManualInsn(addr+6, form("price %d", price));
        // Item type
        MakeByte(addr+8);
        if(Byte(addr+8)!=0){
            itemType = GetBitfieldConstNames(GetEnum("ItemType"),Byte(addr+8),strlen("ITEMTYPE_"),0);
        }
        else{
            itemType = substr(GetConstName(GetConst(GetEnum("ItemType_None"),Byte(addr+8),-1)),strlen("ITEMTYPE_"),-1);
        }
        SetManualInsn(addr+8, form("itemType %s", itemType));
        // Use spell
        MakeByte(addr+9);
        useSpell = GetBitfieldConstNames(GetEnum("Spells"),Byte(addr+9),strlen("SPELL_"),0);
        SetManualInsn(addr+9, form("useSpell %s", useSpell));
        // Equip effects
        MakeData(addr+10,FF_BYTE,6,1);
        equipEffects = "";
        for(j=addr+10;j<addr+16;j=j+2){
            next = substr(GetConstName(GetConst(GetEnum("EquipEffects"),Byte(j),-1)),strlen("EQUIPEFFECT_"),-1);
            if(equipEffects==""){equipEffects = form("%s, %d", next, Byte(j+1));}
            else{equipEffects = form("%s, &\n%s, %d", equipEffects, next, Byte(j+1));}
        }
        SetManualInsn(addr+10, form("equipEffects &\n%s\n", equipEffects));
        // Provide item name as a comment
        itemName = findNameWithoutSpecialChar(0x1796E,i,1);
        MakeRptCmt(addr, form("%s", itemName));
        i++;
        addr = addr+16;
    }
}

static parseSpellDefs(){
    auto addr, j, index, mpCost, animation, properties, maxRange, minRange, radius, power, count, spellName;
    addr = 0x176A6;
    while(addr<0x1796E){
        for(j=addr;j<addr+8;j++){undefineByte(j);}
        // Spell ID
        MakeByte(addr);
        index = GetBitfieldConstNames(GetEnum("Spells"),Byte(addr),strlen("SPELL_"),0);
        SetManualInsn(addr, form("index %s", index));
        // MP cost
        MakeByte(addr+1);
        mpCost = Byte(addr+1);
        SetManualInsn(addr+1, form("mpCost %d", mpCost));
        // Animation ID
        MakeByte(addr+2);
        animation = GetBitfieldConstNames(GetEnum("SpellAnimations"),Byte(addr+2),strlen("SPELLANIMATION_"),0);
        SetManualInsn(addr+2, form("animation %s", animation));
        // Spell properties
        MakeByte(addr+3);
        properties = GetBitfieldConstNames(GetEnum("SpellProps"),Byte(addr+3),strlen("SPELLPROPS_"),0);
        SetManualInsn(addr+3, form("properties %s", properties));
        // Range
        MakeData(addr+4,FF_BYTE,2,1);
        maxRange = Byte(addr+4);
        minRange = Byte(addr+5);
        SetManualInsn(addr+4, form("range %d, %d", minRange, maxRange));
        // Radius
        MakeByte(addr+6);
        radius = Byte(addr+6);
        SetManualInsn(addr+6, form("radius %d", radius));
        // Power
        MakeByte(addr+7);
        power = Byte(addr+7);
        SetManualInsn(addr+7, form("power %d\n", power));
        // Provide spell name as a comment
        index = Byte(addr);
        count = 1;
        while(index>=64){
            index = index-64;
            count++;
        }
        spellName = findName(0xF9C4,index);
        MakeRptCmt(addr, form("%s %s", spellName, ltoa(count,10)));
        addr = addr+8;
    }
}

static parseItemNames(){
    auto addr, j, len, cc, subLen, next, nameOne, nameTwo;
    addr = 0x1796E;
    while(addr<0x17F3D){
        len = Byte(addr)+1;
        // Get name properties
        cc = 0;
        subLen = 1;
        for(j=addr+1;j<addr+len-1;j++){
            next = Byte(j);
            if(next==11||next==13){
                cc = next;
                break;
            }
            subLen = subLen+1;
        }
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        if(cc!=0){
            nameOne = Str(addr+1,subLen-1);
            nameTwo = Str(addr+subLen+1,len-subLen-1);
            SetManualInsn(addr, form("itemName \"%s\", %d, \"%s\"", nameOne, cc, nameTwo));
        }
        else{
            nameOne = Str(addr+1,len-1);
            SetManualInsn(addr, form("itemName \"%s\"", nameOne));
        }
        addr = addr+len;
    }
    // Word align at address 0x17F3D
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, form("wordAlign"));
}

static parseClassNames(){
    auto addr, j, len, name;
    addr = 0x17F3E;
    while(addr<0x17FDA){
        len = Byte(addr)+1;
        name = Str(addr+1,len-1);
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        SetManualInsn(addr, form("className \"%s\"", name));
        addr = addr+len;
    }
}

static parseAllyBattleSprites(){
    auto addr, i, j, forClass, sprite, palette, allyName;
    addr = 0x1F806;
    while(addr<0x1F914){
        for(j=addr;j<addr+9;j++){undefineByte(j);}
        // For base class
        MakeByte(addr);
        forClass = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(addr),-1)),strlen("CLASS_"),-1);
        SetManualInsn(addr, form("forClass %s", forClass));
        MakeData(addr+1,FF_BYTE,2,1);
        sprite = substr(GetConstName(GetConst(GetEnum("AllyBattleSprites"),Byte(addr+1),-1)),strlen("ALLYBATTLESPRITE_"),-1);
        palette = Byte(addr+2);
        SetManualInsn(addr+1, form("allyBattleSprite %s, %d", sprite, palette));
        // For regular promo
        MakeByte(addr+3);
        forClass = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(addr+3),-1)),strlen("CLASS_"),-1);
        SetManualInsn(addr+3, form("forClass %s", forClass));
        MakeData(addr+4,FF_BYTE,2,1);
        sprite = substr(GetConstName(GetConst(GetEnum("AllyBattleSprites"),Byte(addr+4),-1)),strlen("ALLYBATTLESPRITE_"),-1);
        palette = Byte(addr+5);
        SetManualInsn(addr+4, form("allyBattleSprite %s, %d", sprite, palette));
        // For special promo
        MakeByte(addr+6);
        forClass = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(addr+6),-1)),strlen("CLASS_"),-1);
        SetManualInsn(addr+6, form("forClass %s", forClass));
        MakeData(addr+7,FF_BYTE,2,1);
        sprite = substr(GetConstName(GetConst(GetEnum("AllyBattleSprites"),Byte(addr+7),-1)),strlen("ALLYBATTLESPRITE_"),-1);
        palette = Byte(addr+8);
        SetManualInsn(addr+7, form("allyBattleSprite %s, %d\n", sprite, palette));
        // Provide ally's name as a comment
        allyName = findName(0xFAD6,i);
        MakeRptCmt(addr, form("%s", allyName));
        i++;
        addr = addr+9;
    }
}

static parseEnemyBattleSprites(){
    auto addr, i, j, sprite, palette, enemyName;
    auto parameter;
    addr = 0x1F914;
    while(addr<0x1F9E2){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,2,1);
        sprite = substr(GetConstName(GetConst(GetEnum("EnemyBattleSprites"),Byte(addr),-1)),strlen("ENEMYBATTLESPRITE_"),-1);
        palette = Byte(addr+1);
        SetManualInsn(addr, form("enemyBattleSprite %s, %d", sprite, palette));
        // Provide enemy's name as a comment
        enemyName = findName(0xFB8A,i);
        MakeRptCmt(addr, form("%s", enemyName));
        i++;
        addr = addr+2;
    }
}

static parseWeaponSprites(){
    auto addr, i, j, sprite, palette, itemName;
    auto parameter;
    i = 26;
    addr = 0x1F9E2;
    while(addr<0x1FA8A){
        for(j=addr;j<addr+2;j++){undefineByte(j);}
        // Weapon sprite
        MakeByte(addr);
        sprite = substr(GetConstName(GetConst(GetEnum("WeaponSprites"),Byte(addr),-1)),strlen("WEAPONSPRITE_"),-1);
        SetManualInsn(addr, form("weaponSprite %s", sprite));
        // Weapon palette
        MakeByte(addr+1);
        palette = substr(GetConstName(GetConst(GetEnum("WeaponPalettes"),Byte(addr+1),-1)),strlen("WEAPONPALETTE_"),-1);
        SetManualInsn(addr+1, form("weaponPalette %s\n", palette));
        // Provide item name as a comment
        itemName = findNameWithoutSpecialChar(0x1796E,i,1);
        MakeRptCmt(addr, form("%s", itemName));
        i++;
        addr = addr+2;
    }
}

static parseShopDefs(){
    auto addr, i, j, len, shopDef, next;
    i = 1;
    addr = 0x20878;
    while(addr<0x20981){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        shopDef = "";
        for(j=addr+1;j<addr+len;j++){
            //next = GetBitfieldConstNames(GetEnum("Items"),Byte(j),0);
            next = GetBitfieldConstNames(GetEnum("Items"),Byte(j),strlen("ITEM_"),0);
            if(shopDef==""){shopDef = next;}
            else{shopDef = form("%s, &\n%s", shopDef, next);}
        }
        SetManualInsn(addr, form("shopDef &\n%s\n", shopDef));
        // Comments
        if(i<=15){
            MakeRptCmt(addr, form("Weapon shop %d", i));
        }
        else if(i>15&&i<31){
            MakeRptCmt(addr, form("Item shop %d", i-15));
        }
        else{
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
            if(i!=4){next = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(j),-1)),strlen("CLASS_"),-1);}
            else{next = GetBitfieldConstNames(GetEnum("Items"),Byte(j),strlen("ITEM_"),0);}
            if(promotionSection==""){promotionSection = next;}
            else{promotionSection = form("%s, %s", promotionSection, next);}
        }
        if(i!=4){SetManualInsn(addr, form("promotionSection &\n%s\n", promotionSection));}
        else{SetManualInsn(addr, form("promotionItems &\n%s", promotionSection));}
        // Comments
        if(i==0){
            MakeRptCmt(addr, "Regular base classes");
        }
        else if(i==1){
            MakeRptCmt(addr, "Regular promoted classes");
        }
        else if(i==2){
            MakeRptCmt(addr, "Special base classes");
        }
        else if(i==3){
            MakeRptCmt(addr, "Special promoted classes");
        }
        else{
            MakeRptCmt(addr, "Special promotion items");
        }
        i++;
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
            next = substr(GetConstName(GetConst(GetEnum("Classes"),Word(j),-1)),strlen("CLASS_"),-1);
            if(weaponClass==""){weaponClass = next;}
            else{weaponClass = form("%s, %s", weaponClass, next);}
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
            next = form("%d, %s", Byte(j), GetBitfieldConstNames(GetEnum("Items"),Byte(j+1),strlen("ITEM_"),0));
            if(mithrilWeapons==""){mithrilWeapons = next;}
            else{mithrilWeapons = form("%s, &\n%s", mithrilWeapons, next);}
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
        //item = GetBitfieldConstNames(GetEnum("Items"),Byte(addr),0);
        item = GetBitfieldConstNames(GetEnum("Items"),Byte(addr),strlen("ITEM_"),0);
        linesNum = Byte(addr+1);
        message = Word(addr+2);
        SetManualInsn(addr, form("specialCaravanDescription %s, %d, %d", item, linesNum, message));
        addr = addr+4;
    }
    // Terminator word at address 0x228A6
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "\ntableEnd");
}

static parseUsableOutsideBattleItems(){
    auto addr, j, item;
    addr = 0x229E2;
    while(addr<0x229EB){
        undefineByte(addr);
        MakeByte(addr);
        item = GetBitfieldConstNames(GetEnum("Items"),Byte(addr),strlen("ITEM_"),0);
        SetManualInsn(addr, form("usableOutsideBattleItem %s", item));
        addr++;
    }
    // Terminator byte at address 0x229EB
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "\ntableEnd.b");
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
    // Terminator word at address 0x44388
    for(j=addr;j<addr+2;j++){undefineByte(j);}
    MakeWord(addr);
    SetManualInsn(addr, "\ntableEnd");
}

static parseAllyMapSprites(){
    auto addr, i, j, sprite, allyName;
    addr = 0x44A5E;
    while(addr<0x44A7C){
        undefineByte(addr);
        MakeByte(addr);
        sprite = substr(GetConstName(GetConst(GetEnum("Mapsprites"),Byte(addr),-1)),strlen("MAPSPRITE_"),-1);
        SetManualInsn(addr, form("mapSprite %s", sprite));
        // Provide ally's name as a comment
        allyName = findName(0xFAD6,i);
        MakeRptCmt(addr, form("%s", allyName));
        i++;
        addr++;
    }
}

static parseEnemyMapSprites(){
    auto addr, i, j, sprite, enemyName;
    addr = 0x44AA4;
    while(addr<0x44B4A){
        undefineByte(addr);
        MakeByte(addr);
        sprite = substr(GetConstName(GetConst(GetEnum("Mapsprites"),Byte(addr),-1)),strlen("MAPSPRITE_"),-1);
        SetManualInsn(addr, form("mapSprite %s", sprite));
        // Provide enemy's name as a comment
        if(i<103){
            enemyName = findName(0xFB8A,i);
            MakeRptCmt(addr, form("%s", enemyName));
        }
        i++;
        addr++;
    }
}

static parseSpriteDialogProperties(){
    auto addr, j, sprite, portrait, sfx;
    addr = 0x4567A;
    while(addr<0x45856){
        for(j=addr;j<addr+4;j++){undefineByte(j);}
        // Map sprite
        MakeByte(addr);
        sprite = substr(GetConstName(GetConst(GetEnum("Mapsprites"),Byte(addr),-1)),strlen("MAPSPRITE_"),-1);
        SetManualInsn(addr, form("mapSprite %s", sprite));
        // Portrait
        MakeByte(addr+1);
        portrait = substr(GetConstName(GetConst(GetEnum("Portraits"),Byte(addr+1),-1)),strlen("PORTRAIT_"),-1);
        SetManualInsn(addr+1, form("portrait %s", portrait));
        // Speech sound
        MakeData(addr+2,FF_BYTE,2,1);
        sfx = substr(GetConstName(GetConst(GetEnum("Sfx"),Byte(addr+2),-1)),strlen("SFX_"),-1);
        SetManualInsn(addr+2, form("speechSound %s\n", sfx));
        addr = addr+4;
    }
    // Terminator word at address 0x45856
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
        // Provide battle ID as a comment
        MakeRptCmt(addr, form("Battle %s", ltoa(i,10)));
        i++;
        addr++;
    }
}
*/

static parseEnemyDefs(){
    auto addr, i, j, unknownByte, spellPower, level, maxHp, maxMp, baseAtk, baseDef, baseAgi, baseMov;
    auto baseResistance, baseProwess, items, spells, initialStatus, moveType, unknownWord, next, enemyName;
    addr = 0x1B1A66;
    while(addr<0x1B30EE){
        for(j=addr;j<addr+56;j++){undefineByte(j);}
        // Unknown byte
        MakeData(addr,FF_BYTE,10,1);
        unknownByte = Byte(addr);
        SetManualInsn(addr, form("unknownByte %d", unknownByte));
        // Spell power
        MakeByte(addr+10);
        spellPower = substr(GetConstName(GetConst(GetEnum("SpellPower"),Byte(addr+10),-1)),strlen("SPELLPOWER_"),-1);
        SetManualInsn(addr+10, form("spellPower %s", spellPower));
        // Level
        MakeByte(addr+11);
        level = Byte(addr+11);
        SetManualInsn(addr+11, form("level %d", level));
        // Max Hp
        MakeData(addr+12,FF_WORD,4,1);
        maxHp = Word(addr+12);
        SetManualInsn(addr+12, form("maxHp %d", maxHp));
        // Max Mp
        MakeData(addr+16,FF_BYTE,2,1);
        maxMp = Byte(addr+16);
        SetManualInsn(addr+16, form("maxMp %d", maxMp));
        // Base Atk
        MakeData(addr+18,FF_BYTE,2,1);
        baseAtk = Byte(addr+18);
        SetManualInsn(addr+18, form("baseAtk %d", baseAtk));
        // Base Def
        MakeData(addr+20,FF_BYTE,2,1);
        baseDef = Byte(addr+20);
        SetManualInsn(addr+20, form("baseDef %d", baseDef));
        // Base Agi
        MakeData(addr+22,FF_BYTE,2,1);
        baseAgi = Byte(addr+22);
        SetManualInsn(addr+22, form("baseAgi %d", baseAgi));
        // Base Mov
        MakeData(addr+24,FF_BYTE,2,1);
        baseMov = Byte(addr+24);
        SetManualInsn(addr+24, form("baseMov %d", baseMov));
        // Base resistance
        MakeData(addr+26,FF_WORD,4,1);
        if(Word(addr+26)!=0){
            baseResistance = GetBitfieldConstNames(GetEnum("Resistance"),Word(addr+26),strlen("RESISTANCE_"),0);
            SetManualInsn(addr+26, form("baseResistance &\n%s", baseResistance));
        }
        else{
            baseResistance = substr(GetConstName(GetConst(GetEnum("Resistance_None"),Word(addr+26),-1)),strlen("RESISTANCE_"),-1);
            SetManualInsn(addr+26, form("baseResistance %s", baseResistance));
        }
        // Base prowess
        MakeData(addr+30,FF_BYTE,2,1);
        baseProwess = GetBitfieldConstNames(GetEnum("Prowess"),Byte(addr+30),strlen("PROWESS_"),0);
        SetManualInsn(addr+30, form("baseProwess &\n%s", baseProwess));
        // Items
        MakeData(addr+32,FF_WORD,8,1);
        items = "";
        for(j=addr+32;j<addr+40;j=j+2){
            next = GetBitfieldConstNames(GetEnum("Items"),Word(j),strlen("ITEM_"),0);
            if(items==""){items = next;}
            else{items = form("%s, &\n%s", items, next);}
        }
        SetManualInsn(addr+32, form("items &\n%s", items));
        // Spells
        MakeData(addr+40,FF_BYTE,4,1);
        spells = "";
        for(j=addr+40;j<addr+44;j++){
            next = GetBitfieldConstNames(GetEnum("Spells"),Byte(j),strlen("SPELL_"),0);
            if(spells==""){spells = next;}
            else{spells = form("%s, &\n%s", spells, next);}
        }
        SetManualInsn(addr+40, form("spells &\n%s", spells));
        // Initial status
        MakeData(addr+44,FF_BYTE,5,1);
        initialStatus = Word(addr+44);
        SetManualInsn(addr+44, form("initialStatus %d", initialStatus));
        // Move type
        MakeByte(addr+49);
        moveType = GetBitfieldConstNames(GetEnum("MoveType"),Byte(addr+49),strlen("MOVETYPE_"),0);
        SetManualInsn(addr+49, form("moveType %s", moveType));
        // Unknown word
        MakeData(addr+50,FF_BYTE,6,1);
        unknownWord = Word(addr+52);
        SetManualInsn(addr+50, form("unknownWord %d\n", unknownWord));
        // Provide enemy's name as a comment
        enemyName = findName(0xFB8A,i);
        MakeRptCmt(addr, form("%s", enemyName));
        i++;
        addr = addr+56;
    }
}

static parseRandomBattles(){
    auto addr, j, len, randomBattles, next;
    addr = 0x1B6DB0;
    while(addr<0x1B6DBC){
        len = Byte(addr)+1;
        for(j=addr;j<addr+len;j++){undefineByte(j);}
        MakeData(addr,FF_BYTE,len,1);
        randomBattles = "";
        for(j=addr+1;j<addr+len;j++){
            next = substr(GetConstName(GetConst(GetEnum("Battles"),Byte(j),-1)),strlen("BATTLE_"),-1);
            if(randomBattles==""){randomBattles = next;}
            else{randomBattles = form("%s, &\n%s", randomBattles, next);}
        }
        SetManualInsn(addr, form("randomBattles &\n%s", randomBattles));
        addr = addr+len;
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
            if(i!=30){SetManualInsn(j, form("dc.w %s", curveParams));}
            else{SetManualInsn(j, form("dc.w %s\n", curveParams));}
            // Comments
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
    //while(addr<0x1EE30B){
        for(j=addr;j<addr+16;j++){undefineByte(j);}
        // For class
        MakeByte(addr);
        forClass = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(addr),-1)),strlen("CLASS_"),-1);
        SetManualInsn(addr, form("forClass %s", forClass));
        // HP growth
        MakeData(addr+1,FF_BYTE,3,1);
        curve = substr(GetConstName(GetConst(GetEnum("GrowthCurves"),Byte(addr+1),-1)),strlen("GROWTHCURVE_"),-1);
        start = Byte(addr+2);
        proj = Byte(addr+3);
        SetManualInsn(addr+1, form("hpGrowth %d, %d, %s", start, proj, curve));
        // MP growth
        MakeData(addr+4,FF_BYTE,3,1);
        curve = substr(GetConstName(GetConst(GetEnum("GrowthCurves"),Byte(addr+4),-1)),strlen("GROWTHCURVE_"),-1);
        start = Byte(addr+5);
        proj = Byte(addr+6);
        SetManualInsn(addr+4, form("mpGrowth %d, %d, %s", start, proj, curve));
        // ATK growth
        MakeData(addr+7,FF_BYTE,3,1);
        curve = substr(GetConstName(GetConst(GetEnum("GrowthCurves"),Byte(addr+7),-1)),strlen("GROWTHCURVE_"),-1);
        start = Byte(addr+8);
        proj = Byte(addr+9);
        SetManualInsn(addr+7, form("atkGrowth %d, %d, %s", start, proj, curve));
        // DEF growth
        MakeData(addr+10,FF_BYTE,3,1);
        curve = substr(GetConstName(GetConst(GetEnum("GrowthCurves"),Byte(addr+10),-1)),strlen("GROWTHCURVE_"),-1);
        start = Byte(addr+11);
        proj = Byte(addr+12);
        SetManualInsn(addr+10, form("defGrowth %d, %d, %s", start, proj, curve));
        // AGI growth
        MakeData(addr+13,FF_BYTE,3,1);
        curve = substr(GetConstName(GetConst(GetEnum("GrowthCurves"),Byte(addr+13),-1)),strlen("GROWTHCURVE_"),-1);
        start = Byte(addr+14);
        proj = Byte(addr+15);
        SetManualInsn(addr+13, form("agiGrowth %d, %d, %s", start, proj, curve));
        // Count spell list bytes
        offset = 16;
        next = Byte(addr+offset);
        count = 1;
        while(next!=254&&next!=255){
            offset++;
            next = Byte(addr+offset);
            count++;
        }
        // Spell list
        offset++;
        if(Byte(addr+16)==254){
            undefineByte(addr+16);
            MakeByte(addr+16);
            SetManualInsn(addr+16, "useFirstSpellList\n");
        }
        else{
            for(j=addr+16;j<addr+offset;j++){undefineByte(j);}
            MakeData(addr+16,FF_BYTE,count,1);
            spellList = "";
            for(j=addr+16;j<addr+offset;j=j+2){
                if(Byte(j)!=254&&Byte(j)!=255){
                    next = GetBitfieldConstNames(GetEnum("Spells"),Byte(j+1),strlen("SPELL_"),0);
                    if(spellList==""){spellList = form("%d, %s", Byte(j), next);}
                    else{spellList = form("%s, &\n%d, %s", spellList, Byte(j), next);}
                }
            }
            if(spellList!=""){SetManualInsn(addr+16, form("spellList &\n%s\n", spellList));}
            else{SetManualInsn(addr+16, form("spellList %s\n", spellList));}
        }
        addr = addr+offset;
    }
    // Word align at address 0x1EE7CF
    undefineByte(addr);
    MakeByte(addr);
    SetManualInsn(addr, "wordAlign");
}

static parseAllyStartDefs(){
    auto addr, i, j, startClass, startLevel, startItems, next, allyName;
    addr = 0x1EE7D0;
    while(addr<0x1EE890){
        for(j=addr;j<addr+6;j++){undefineByte(j);}
        // Starting class
        MakeByte(addr);
        startClass = substr(GetConstName(GetConst(GetEnum("Classes"),Byte(addr),-1)),strlen("CLASS_"),-1);
        SetManualInsn(addr, form("startClass %s", startClass));
        // Starting level
        MakeByte(addr+1);
        startLevel = Byte(addr+1);
        SetManualInsn(addr+1, form("startLevel %d", startLevel));
        // Starting items
        MakeData(addr+2,FF_BYTE,4,1);
        startItems = "";
        for(j=addr+2;j<addr+6;j++){
            next = GetBitfieldConstNames(GetEnum("Items"),Byte(j),strlen("ITEM_"),0);
            if(startItems==""){startItems = next;}
            else{startItems = form("%s, &\n%s", startItems, next);}
        }
        SetManualInsn(addr+2, form("startItems &\n%s\n", startItems));
        // Provide ally's name as a comment
        if(i<30){
            allyName = findName(0xFAD6,i);
            MakeRptCmt(addr, form("%s", allyName));
        }
        i++;
        addr = addr+6;
    }
}

static parseClassDefs(){
    auto addr, i, j, mov, resistance, moveType, prowess, className;
    addr = 0x1EE890;
    while(addr<0x1EE930){
        for(j=addr;j<addr+5;j++){undefineByte(j);}
        // MOV
        MakeByte(addr);
        mov = Byte(addr);
        SetManualInsn(addr, form("mov %d", mov));
        // Resistance
        MakeWord(addr+1);
        if(Word(addr+1)!=0){
            resistance = GetBitfieldConstNames(GetEnum("Resistance"),Word(addr+1),strlen("RESISTANCE_"),0);
            SetManualInsn(addr+1, form("resistance &\n%s", resistance));
        }
        else{
            resistance = substr(GetConstName(GetConst(GetEnum("Resistance_None"),Word(addr+1),-1)),strlen("RESISTANCE_"),-1);
            SetManualInsn(addr+1, form("resistance %s", resistance));
        }
        // Move type
        MakeByte(addr+3);
        moveType = GetBitfieldConstNames(GetEnum("MoveType"),Byte(addr+3),strlen("MOVETYPE_"),0);
        SetManualInsn(addr+3, form("moveType %s", moveType));
        // Prowess
        MakeByte(addr+4);
        prowess = GetBitfieldConstNames(GetEnum("Prowess"),Byte(addr+4),strlen("PROWESS_"),0);
        SetManualInsn(addr+4, form("prowess &\n%s\n", prowess));
        // Provide class name as a comment
        className = findName(0x17F3E,i);
        MakeRptCmt(addr, form("%s", className));
        i++;
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
                parameter = ltoa(flag,16);
                while(strlen(parameter)<4){
                    parameter=form("0%s",parameter);
                }
                flagmapFile = fopen("flagmap.txt","r");
                while(flagDescription==""){
                lineNumber = lineNumber + 1;
                    currentLine = readstr(flagmapFile);
                    if(currentLine==-1){
                        break;
                    }
                    if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
                        flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
                    }
                }
                fclose(flagmapFile);    
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
                parameter = ltoa(flag,16);
                while(strlen(parameter)<4){
                    parameter=form("0%s",parameter);
                }
                flagmapFile = fopen("flagmap.txt","r");
                while(flagDescription==""){
                lineNumber = lineNumber + 1;
                    currentLine = readstr(flagmapFile);
                    if(currentLine==-1){
                        break;
                    }
                    if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
                        flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
                    }
                }
                fclose(flagmapFile);    
                MakeRptCmt(sc,flagDescription);
                SetManualInsn(sc, form("mapItem %d, %d, %s, %s", Byte(sc), Byte(sc+1), ltoa(Byte(sc+2),10),GetBitfieldConstNames(GetEnum("Items"),Byte(sc+3),strlen("ITEM_"),0)));
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
                parameter = ltoa(flag,16);
                while(strlen(parameter)<4){
                    parameter=form("0%s",parameter);
                }
                flagmapFile = fopen("flagmap.txt","r");
                while(flagDescription==""){
                lineNumber = lineNumber + 1;
                    currentLine = readstr(flagmapFile);
                    if(currentLine==-1){
                        break;
                    }
                    if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
                        flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
                    }
                }
                fclose(flagmapFile);    
                MakeRptCmt(sc,flagDescription);
                SetManualInsn(sc, form("mapItem %d, %d, %s, %s", Byte(sc), Byte(sc+1), ltoa(Byte(sc+2),10),GetBitfieldConstNames(GetEnum("Items"),Byte(sc+3),strlen("ITEM_"),0)));
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






static GetBitfieldConstNames(enumIdx,value,strlen,param){
    auto bmask, names, mval, next;
    bmask = GetFirstBmask(enumIdx);
    names = "";
    while(bmask!=0){
        mval = value & bmask;
        next = substr(GetConstName(GetConst(enumIdx,mval,bmask)),strlen,-1);
        if(next!=""){
            if(names==""){names = next;}
            else if(param!=0){names = form("%s|&\n%s", names, next);}
            else{names = form("%s|%s", names, next);}
        }
        // Break out of loop after iterating last bitmask
        if(bmask==-1){break;}
        bmask = GetNextBmask(enumIdx,bmask);
    }
    return names;
}


static findName(addr,i){
    return findNameWithoutSpecialChar(addr,i,0);
}

static findNameWithoutSpecialChar(addr,i,param){
    auto len;
    while(i>0){
        len = Byte(addr);
        addr = addr+len+1;
        i--;
    }
    return StrWithoutSpecialChar(addr+1,Byte(addr),param);
}


/*
 *  Returns the string prefixed with length byte at addr
 */
static Str(addr,len){
    return StrWithoutSpecialChar(addr,len,0);
}

static StrWithoutSpecialChar(addr,len,param){
    auto j, str, next;
    str = "";
    for(j=addr;j<addr+len;j++){
        next = Byte(j);
        if(param!=0){
            if(next==11||next==13){next = 32;}
        }
        str = form("%s%c", str, next);
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
