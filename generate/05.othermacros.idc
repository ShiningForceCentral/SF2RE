


#include <idc.idc>


static main(void){
	Message("\nPARSING DATA STRUCTURES INTO MACROS ...\n");
	parseFlaggedSwitchedMaps();
	parseBattleMapCoords();	
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
