


#include <idc.idc>


static main(void){
	Message("\nPARSING DATA STRUCTURES INTO MACROS ...\n");
	parseFlaggedSwitchedMaps();
	parseBattleMapCoords();	
	parseSavePointMapCoords();
	parseRaftResetMapCoords();
	parseAllyBattleSprites();
	parseEnemyBattleSprites();
	parseWeaponSprites();
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

static parseAllyBattleSprites(){
	auto addr, j, baseClass, sprite, palette, promotedClass, promotedSprite, promotedPalette, specialClass, specialSprite, specialPalette;
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
		addr = addr+9;
	}
}

static parseEnemyBattleSprites(){
	auto addr, j, sprite, palette;
	auto parameter;
	addr = 0x1F914;
	while(addr<0x1F9E2){
		for(j=addr;j<addr+2;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,2,1);
		sprite = Byte(addr);
		palette = Byte(addr+1);
		SetManualInsn(addr, form("enemyBattleSprite %d, %d", sprite, palette));
		addr = addr+2;
	}
}

static parseWeaponSprites(){
	auto addr, j, sprite, palette;
	auto parameter;
	addr = 0x1F9E2;
	while(addr<0x1FA8A){
		for(j=addr;j<addr+2;j++){undefineByte(j);}
		MakeData(addr,FF_BYTE,2,1);
		sprite = Byte(addr);
		palette = Byte(addr+1);
		SetManualInsn(addr, form("weaponSprite %d, %d", sprite, palette));
		addr = addr+2;
	}
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
