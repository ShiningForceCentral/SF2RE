


#include <idc.idc>


static main(void){
	Message("\nPARSING DATA STRUCTURES INTO MACROS ...\n");
	parseFlaggedSwitchedMaps();
	parseBattleMapCoords();	
	parseSavePointMapCoords();
	parseRaftResetMapCoords();
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
	parseShopItems();
	parseAllyMapSprites();
	parseEnemyMapSprites();
	parseEnemyDefs();
	parseAllyStartDefs();
	parseClassDefs();
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
		SetManualInsn(addr, form("flagSwitchedMap %d, $%s, %d", map, ltoa(flag,16), newMap));
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
		SetManualInsn(addr, form("savePointMapCoords %d, %d, %d, %d", map, x, y, facing));
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
		SetManualInsn(addr, form("raftResetMapCoords %d, %d, %d, %d", map, raftMap, x, y));
		addr = addr+4;
	}
}

static parseSpellElements(){
	auto addr, i, j, element, spellName;
	addr = 0xC24E;
	while(addr<0xC27A){
		for(j=addr;j<addr+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,1,1);
		element = Byte(addr);
		SetManualInsn(addr, form("spellElement %d", element));
		// Provide spell name as a comment
		spellName = findName(0xF9C4,i);
		MakeRptCmt(addr, form("%s", spellName));
		i++;
		addr = addr+1;
	}
}

static parseSpellNames(){
	auto addr, j, len, name;
	addr = 0xF9C4;
	while(addr<0xFAD6){
		len = Byte(addr);
		name = Str(addr+1,len);
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		SetManualInsn(addr, form("dc.b %d, '%s'", len, name));
		addr = addr+len+1;
	}
}

static parseAllyNames(){
	auto addr, j, len, name;
	addr = 0xFAD6;
	while(addr<0xFB8A){
		len = Byte(addr);
		name = Str(addr+1,len);
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		SetManualInsn(addr, form("dc.b %d, '%s'", len, name));
		addr = addr+len+1;
	}
}

static parseEnemyNames(){
	auto addr, j, len, name;
	addr = 0xFB8A;
	while(addr<0xFF87){
		len = Byte(addr);
		name = Str(addr+1,len);
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		SetManualInsn(addr, form("dc.b %d, '%s'", len, name));
		addr = addr+len+1;
	}
	// Manual fix for Jaro's bugged entry
	SetManualInsn(0xFF5E, form("dc.b 4, 'JAR', 0"));
	MakeRptCmt(0xFF5E,"here is the cause of the infamous JAR bug, an innocent typo :)");
}

static parseItemDefs(){
	auto addr, i, j, eqBitfield, maxRange, minRange, price, flags, useEffect, eqEffectOne, eqValueOne, eqEffectTwo, eqValueTwo, eqEffectThree, eqValueThree, itemName;
	addr = 0x16EA6;
	while(addr<0x176A6){
		for(j=addr;j<addr+16;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,16,1);
		eqBitfield = Dword(addr);
		maxRange = Byte(addr+4);
		minRange = Byte(addr+5);
		price = Word(addr+6);
		flags = Byte(addr+8);
		useEffect = Byte(addr+9);
		eqEffectOne = Byte(addr+10);
		eqValueOne = Byte(addr+11);
		eqEffectTwo = Byte(addr+12);
		eqValueTwo = Byte(addr+13);
		eqEffectThree = Byte(addr+14);
		eqValueThree = Byte(addr+15);
		SetManualInsn(addr, form("itemDef %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", eqBitfield, maxRange, minRange, price, flags, useEffect, eqEffectOne, eqValueOne, eqEffectTwo, eqValueTwo, eqEffectThree, eqValueThree));
		// Provide item name as a comment
		itemName = findNameWithoutSpecialChar(0x1796E,i);
		MakeRptCmt(addr, form("%s", itemName));
		i++;
		addr = addr+16;
	}
}

static parseSpellDefs(){
	auto addr, j, spellCode, mpCost, animation, type, maxRange, minRange, area, damage, count, spellName;
	addr = 0x176A6;
	while(addr<0x1796E){
		for(j=addr;j<addr+8;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,8,1);
		spellCode = Byte(addr);
		mpCost = Byte(addr+1);
		animation = Byte(addr+2);
		type = Byte(addr+3);
		maxRange = Byte(addr+4);
		minRange = Byte(addr+5);
		area = Byte(addr+6);
		damage = Byte(addr+7);
		SetManualInsn(addr, form("spellDef %d, %d, %d, %d, %d, %d, %d, %d", spellCode, mpCost, animation, type, maxRange, minRange, area, damage));
		// Provide spell name as a comment
		count = 1;
		while(spellCode>63){
			spellCode = spellCode-64;
			count++;
		}
		spellName = findName(0xF9C4,spellCode);
		MakeRptCmt(addr, form("%s %s", spellName, ltoa(count,10)));
		addr = addr+8;
	}
}

static parseItemNames(){
	auto addr, j, len, specialChar, subLen, nameOne, nameTwo;
	addr = 0x1796E;
	while(addr<0x17F3D){
		len = Byte(addr);
		specialChar = specialChar(addr+1,len);
		if(specialChar != 0){
			subLen = subLen(addr+1,len);
			nameOne = Str(addr+1,subLen-1);
			nameTwo = Str(addr+subLen+1,len-subLen);
		}
		else{
			nameOne = Str(addr+1,len);
		}
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		if(specialChar != 0){
			SetManualInsn(addr, form("dc.b %d, '%s', %d, '%s'", len, nameOne, specialChar, nameTwo));
		}
		else{
			SetManualInsn(addr, form("dc.b %d, '%s'", len, nameOne));
		}
		addr = addr+len+1;
	}
	// Manual fix for Thieve's Dagger
	SetManualInsn(0x17E46, form("dc.b 15, 'Thieve', 39, 's', 13, 'Dagger'"));
	// Padding byte
	MakeData(0x17F3D,FF_BYTE,1,1);
	SetManualInsn(0x17F3D, form("align 2"));
	MakeRptCmt(0x17F3D,"make sure end of variable length table is word-aligned");
}

static parseClassNames(){
	auto addr, j, len, name;
	addr = 0x17F3E;
	while(addr<0x17FDA){
		len = Byte(addr);
		name = Str(addr+1,len);
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		SetManualInsn(addr, form("dc.b %d, '%s'", len, name));
		addr = addr+len+1;
	}
}

static parseAllyBattleSprites(){
	auto addr, i, j, baseClass, sprite, palette, promotedClass, promotedSprite, promotedPalette, specialClass, specialSprite, specialPalette, allyName;
	auto parameter;
	addr = 0x1F806;
	while(addr<0x1F914){
		for(j=addr;j<addr+9;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,9,1);
		baseClass = Byte(addr);
		sprite = Byte(addr+1);
		palette = Byte(addr+2);
		promotedClass = Byte(addr+3);
		promotedSprite = Byte(addr+4);
		promotedPalette = Byte(addr+5);
		specialClass = Byte(addr+6);
		specialSprite = Byte(addr+7);
		specialPalette = Byte(addr+8);
		SetManualInsn(addr, form("allyBattleSprites %d, %d, %d, %d, %d, %d, %d, %d, %d", baseClass, sprite, palette, promotedClass, promotedSprite, promotedPalette, specialClass, specialSprite, specialPalette));
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
		sprite = Byte(addr);
		palette = Byte(addr+1);
		SetManualInsn(addr, form("enemyBattleSprite %d, %d", sprite, palette));
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
		MakeData(addr,FF_BYTE,2,1);
		sprite = Byte(addr);
		palette = Byte(addr+1);
		SetManualInsn(addr, form("weaponSprite %d, %d", sprite, palette));
		// Provide item name as a comment
		itemName = findNameWithoutSpecialChar(0x1796E,i);
		MakeRptCmt(addr, form("%s", itemName));
		i++;
		addr = addr+2;
	}
}

static parseShopItems(){
	auto addr, j, len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven, itemEight, itemNine, itemTen, itemEleven, itemTwelve;
	addr = 0x20878;
	while(addr<0x20981){
		len = Byte(addr);
		for(j=addr;j<addr+len+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,len+1,1);
		itemOne = Byte(addr+1);
		itemTwo = Byte(addr+2);
		itemThree = Byte(addr+3);
		itemFour = Byte(addr+4);
		itemFive = Byte(addr+5);
		itemSix = Byte(addr+6);
		itemSeven = Byte(addr+7);
		itemEight = Byte(addr+8);
		itemNine = Byte(addr+9);
		itemTen = Byte(addr+10);
		itemEleven = Byte(addr+11);
		itemTwelve = Byte(addr+12);
		if(len == 12){
			SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven, itemEight, itemNine, itemTen, itemEleven, itemTwelve));
		}
		else{
			if(len == 11){
				SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven, itemEight, itemNine, itemTen, itemEleven));
			}
			else{
				if(len == 10){
					SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven, itemEight, itemNine, itemTen));
				}
				else{
					if(len == 9){
						SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven, itemEight, itemNine));
					}
					else{
						if(len == 7){
							SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix, itemSeven));
						}
						else{
							if(len == 6){
								SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive, itemSix));
							}
							else{
								if(len == 5){
									SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour, itemFive));
								}
								else{
									SetManualInsn(addr, form("dc.b %d, %d, %d, %d, %d", len, itemOne, itemTwo, itemThree, itemFour));
								}
							}
						}
					}
				}
			}
		}
		addr = addr+len+1;
	}
}

static parseAllyMapSprites(){
	auto addr, i, j, sprite, palette, allyName;
	addr = 0x44A5E;
	while(addr<0x44A7C){
		for(j=addr;j<addr+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,1,1);
		sprite = Byte(addr);
		SetManualInsn(addr, form("allyMapSprite %d", sprite));
		// Provide ally's name as a comment
		allyName = findName(0xFAD6,i);
		MakeRptCmt(addr, form("%s", allyName));
		i++;
		addr = addr+1;
	}
}

static parseEnemyMapSprites(){
	auto addr, i, j, sprite, palette, enemyName;
	addr = 0x44AA4;
	while(addr<0x44B4A){
		for(j=addr;j<addr+1;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,1,1);
		sprite = Byte(addr);
		SetManualInsn(addr, form("enemyMapSprite %d", sprite));
		// Provide enemy's name as a comment
		if(i<103){
			enemyName = findName(0xFB8A,i);
			MakeRptCmt(addr, form("%s", enemyName));
		}
		i++;
		addr = addr+1;
	}
}

static parseEnemyDefs(){
	auto addr, i, j, index, spellPower, level, maxHP, maxMP, baseATK, baseDEF, baseAGI, baseMOV, baseResist, baseProwess, itemOne, itemTwo, itemThree, itemFour, spellOne, spellTwo, spellThree, spellFour, initStatus, moveType, unkVar, enemyName;
	addr = 0x1B1A66;
	while(addr<0x1B30EE){
		for(j=addr;j<addr+56;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,56,1);
		index = Byte(addr);
		spellPower = Byte(addr+10);
		level = Byte(addr+11);
		maxHP = Word(addr+12);
		maxMP = Byte(addr+16);
		baseATK = Byte(addr+18);
		baseDEF = Byte(addr+20);
		baseAGI = Byte(addr+22);
		baseMOV = Byte(addr+24);
		baseResist = Word(addr+26);
		baseProwess = Byte(addr+30);
		itemOne = Word(addr+32);
		itemTwo = Word(addr+34);
		itemThree = Word(addr+36);
		itemFour = Word(addr+38);
		spellOne = Byte(addr+40);
		spellTwo = Byte(addr+41);
		spellThree = Byte(addr+42);
		spellFour = Byte(addr+43);
		initStatus = Word(addr+44);
		moveType = Byte(addr+49);
		unkVar = Word(addr+52);
		SetManualInsn(addr, form("enemyDef %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", index, spellPower, level, maxHP, maxMP, baseATK, baseDEF, baseAGI, baseMOV, baseResist, baseProwess, itemOne, itemTwo, itemThree, itemFour, spellOne, spellTwo, spellThree, spellFour, initStatus, moveType, unkVar));
		// Provide enemy's name as a comment
		enemyName = findName(0xFB8A,i);
		MakeRptCmt(addr, form("%s", enemyName));
		i++;
		addr = addr+56;
	}
}

static parseAllyStartDefs(){
	auto addr, i, j, startingClass, startingLevel, itemOne, itemTwo, itemThree, itemFour, allyName;
	addr = 0x1EE7D0;
	while(addr<0x1EE890){
		for(j=addr;j<addr+6;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,6,1);
		startingClass = Byte(addr);
		startingLevel = Byte(addr+1);
		itemOne = Byte(addr+2);
		itemTwo = Byte(addr+3);
		itemThree = Byte(addr+4);
		itemFour = Byte(addr+5);
		SetManualInsn(addr, form("allyStartDef %d, %d, %d, %d, %d, %d", startingClass, startingLevel, itemOne, itemTwo, itemThree, itemFour));
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
	auto addr, i, j, moveStat, resistance, moveType, prowess, className;
	addr = 0x1EE890;
	while(addr<0x1EE930){
		for(j=addr;j<addr+5;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,5,1);
		moveStat = Byte(addr);
		resistance = Word(addr+1);
		moveType = Byte(addr+3);
		prowess = Byte(addr+4);
		SetManualInsn(addr, form("classDef %d, %d, %d, %d", moveStat, resistance, moveType, prowess));
		// Provide class name as a comment
		className = findName(0x17F3E,i);
		MakeRptCmt(addr, form("%s", className));
		i++;
		addr = addr+5;
	}
}








static specialChar(addr,len){
	auto j, specialChar, nextChar;
	specialChar = 0;
	for(j=addr;j<addr+len;j++){
		nextChar = Byte(j);
		if(nextChar == 11 || nextChar == 13){
			specialChar = nextChar;
			break;
		}
	}
	return specialChar;
}

static subLen(addr,len){
	auto j, subLen, nextChar;
	subLen = 1;
	for(j=addr;j<addr+len;j++){
		nextChar = Byte(j);
		if(nextChar == 11 || nextChar == 13){
			break;
		}
		subLen = subLen+1;
	}
	return subLen;
}

static findName(addr,i){
	auto len;
	while(i>0){
		len = Byte(addr);
		addr = addr+len+1;
		i--;
	}
	return Str(addr+1,Byte(addr));
}

static findNameWithoutSpecialChar(addr,i){
	auto len;
	while(i>0){
		len = Byte(addr);
		addr = addr+len+1;
		i--;
	}
	return StrWithoutSpecialChar(addr+1,Byte(addr));
}

/*
 *	Returns the string prefixed with length byte at addr
 */
static Str(addr,len){
	auto j, str, nextChar;
	str = "";
	for(j=addr;j<addr+len;j++){
		nextChar = Byte(j);
		str = form("%s%c", str, nextChar);
	}
	return str;
}

static StrWithoutSpecialChar(addr,len){
	auto j, str, nextChar;
	str = "";
	for(j=addr;j<addr+len;j++){
		nextChar = Byte(j);
		if(nextChar == 11 || nextChar == 13){
			nextChar = 32;
		}
		str = form("%s%c", str, nextChar);
	}
	return str;
}


/* 
 *	Makes sure byte at addr is
 *	clean for new formatting
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
