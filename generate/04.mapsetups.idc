


#include <idc.idc>


static main(void){

	Message("\nPARSING MAP SETUP Sections ...\n");
	parseAllMapSetupsSections();	
	Message("END OF PARSING.\n");	


}

static parseAllMapSetupsSections(){
	auto addr,j,firstMs, map, flag;
	addr = 0x4F6E2;
	while(Word(addr)!=0xFFFF){
		firstMs = 1;
		map = Word(addr);
		while(Word(addr)!=0xFFFD){
			if(firstMs){
				flag = 0;
				for(j=addr;j<addr+6;j++){undefineByte(j);}
				MakeData(addr,FF_BYTE,6,1);
				SetManualInsn   (addr, form("msMap %d, %s",Word(addr),GetTrueName(Dword(addr+2))));
				firstMs = 0;
			}else{
				flag = Word(addr);
				for(j=addr;j<addr+6;j++){undefineByte(j);}
				MakeData(addr,FF_BYTE,6,1);
				SetManualInsn   (addr, form("msFlag %d, %s",Word(addr),GetTrueName(Dword(addr+2))));
			}
			parseMapSetupSection1(Dword(Dword(addr+2)),map,flag);
			parseMapSetupSection2(Dword(Dword(addr+2)+4),map,flag);
			parseMapSetupSection3(Dword(Dword(addr+2)+4+4),map,flag);
			parseMapSetupSection4(Dword(Dword(addr+2)+4+4+4),map,flag);
			parseMapSetupSection5(Dword(Dword(addr+2)+4+4+4+4),map,flag);
			addr = addr+6;
		}
		for(j=addr;j<addr+1;j++){undefineByte(addr);}
		MakeWord(addr);
		SetManualInsn   (addr, "msMapEnd");
		addr = addr+2;	
	}
	for(j=addr;j<addr+1;j++){undefineByte(addr);}
	MakeWord(addr);
	SetManualInsn   (addr, "msEnd");
	addr = addr+2;	
}


static parseMapSetupSection1(ea,map,flag){
	auto j, x, y, facing, sprite, scriptName, walkX, walkY, walkDist;

	while(Word(ea)!=0xFFFF){
	
		for(j=ea;j<ea+8;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,8,1);
		x = Byte(ea);
		y = Byte(ea+1);
		facing = getDirection(Byte(ea+2));
		sprite = getMapspriteOrAlly(Byte(ea+3));
		if(Byte(ea+4)==0xFF){
			walkX = Byte(ea+5);
			walkY = Byte(ea+6);
			walkDist = Byte(ea+7);
			SetManualInsn   (ea, form("msWalkingEntity %d, %d, %s, %s, %d, %d, %d",x, y, facing, sprite, walkX, walkY, walkDist));
		}else if(Byte(ea+4)==0xFE){
			MakeNameEx(Dword(ea+4)-0xFE000000,form("ems_%s",ltoa(Dword(ea+4)-0xFE000000,16)),0);
			scriptName = GetTrueName(Dword(ea+4)-0xFE000000);
			SetManualInsn   (ea, form("msSequencedEntity %d, %d, %s, %s, %s",x, y, facing, sprite, scriptName));
			parseEntityMoveSequence(Dword(ea+4)-0xFE000000);
		}else{
			if(GetTrueName(Dword(ea+4))==""){MakeNameEx(Dword(ea+4),"",SN_AUTO);}
			scriptName = GetTrueName(Dword(ea+4));
			SetManualInsn   (ea, form("msFixedEntity %d, %d, %s, %s, %s",x, y, facing, sprite, scriptName));
		}
		ea = ea+8;
	}
	for(j=ea;j<ea+1;j++){undefineByte(j);}
	MakeWord(ea);
	SetManualInsn   (ea, "msEntitiesEnd");
}

static parseEntityMoveSequence(addr){

	while(Word(addr)!=0xFFFF){
		undefineByte(addr);
		MakeByte(addr);
		SetManualInsn   (addr, form("dc.b %s",getDirection(Byte(addr))));
		addr++;
	}
	undefineByte(addr);
	MakeWord(addr);
	SetManualInsn   (addr, "emsEnd");
}

static parseEntityMoveSequence(addr){

	while(Word(addr)!=0xFFFF){
		undefineByte(addr);
		MakeByte(addr);
		SetManualInsn   (addr, form("dc.b %s",getDirection(Byte(addr))));
		addr++;
	}
	undefineByte(addr);
	MakeWord(addr);
	SetManualInsn   (addr, "emsEnd");
}

static parseMapSetupSection2(ea,map,flag){
	auto base, j, entity, facing, offset, target, functionName, index, flagName, functionRef;
	base = ea;
	index = 0;
	if(Word(ea)==0x4E75){
		//map 52 bug
		MakeWord(ea);
	}
	else{
		if(flag!=0){
			flagName = form("_%s",ltoa(flag,16));
		}else{
			flagName = "";
		}
		while(Byte(ea)!=0xFD){
			for(j=ea;j<ea+4;j++){undefineByte(j);}
			MakeData(ea,FF_BYTE,4,1);
			entity = Byte(ea);
			facing = getDirection(Byte(ea+1));
			offset = Word(ea+2);
			functionName = form("Map%s%s_EntityEvent%s",ltoa(map,10),flagName,ltoa(index,10));
			if(offset>0x7FFF){
				target = base+offset-0x10000;
			}else{
				target = base+offset;
			}
			if(substr(GetTrueName(target),0,3)!="Map"){
				MakeNameEx(target,functionName,0);
			}else{
				functionName = GetTrueName(target);
			}		
			if(offset>0x7FFF){
				functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
			}else{
				functionRef = form("%s-%s",functionName,GetTrueName(base));
			}
			SetManualInsn   (ea, form("msEntityEvent %d, %s, %s", entity, facing, functionRef));	
			ea = ea+4;
			index = index+1;
		}
		for(j=ea;j<ea+4;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,4,1);
		entity = Byte(ea);
		facing = getDirection(Byte(ea+1));
		offset = Word(ea+2);
			functionName = form("Map%s%s_DefaultEntityEvent",ltoa(map,10),flagName);
			if(offset>0x7FFF){
				target = base+offset-0x10000;
			}else{
				target = base+offset;
			}
			if(substr(GetTrueName(target),0,3)!="Map"){
				MakeNameEx(target,functionName,0);
			}else{
				functionName = GetTrueName(target);
			}		
			if(offset>0x7FFF){
				functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
			}else{
				functionRef = form("%s-%s",functionName,GetTrueName(base));
			}
			if(Byte(ea+1)==0){
				SetManualInsn   (ea, form("msDefaultEntityEvent %s", functionRef));
			}else{
				SetManualInsn   (ea, form("msDftEntityEvent %d, %s", Byte(ea+1), functionRef));
			}
	}
}

static parseMapSetupSection3(ea,map,flag){
	auto base, j, x, y, offset, target, functionName, index, flagName, functionRef;
	base = ea;
	index = 0;
	if(flag!=0){
		flagName = form("_%s",ltoa(flag,16));
	}else{
		flagName = "";
	}
	while(Byte(ea)!=0xFD){
		for(j=ea;j<ea+4;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,4,1);
		x = Byte(ea);
		y = Byte(ea+1);
		offset = Word(ea+2);
		functionName = form("Map%s%s_ZoneEvent%s",ltoa(map,10),flagName,ltoa(index,10));
		if(offset>0x7FFF){
			target = base+offset-0x10000;
		}else{
			target = base+offset;
		}
		if(substr(GetTrueName(target),0,3)!="Map"){
			MakeNameEx(target,functionName,0);
		}else{
			functionName = GetTrueName(target);
		}		
		if(offset>0x7FFF){
			functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
		}else{
			functionRef = form("%s-%s",functionName,GetTrueName(base));
		}
		SetManualInsn   (ea, form("msZoneEvent %d, %d, %s", x, y, functionRef));	
		ea = ea+4;
		index = index+1;
	}
	// Map 44 bug
	if(ea!=0x54458){
		for(j=ea;j<ea+4;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,4,1);
		offset = Word(ea+2);
		functionName = form("Map%s%s_DefaultZoneEvent",ltoa(map,10),flagName);
		if(offset>0x7FFF){
			target = base+offset-0x10000;
		}else{
			target = base+offset;
		}
		if(substr(GetTrueName(target),0,3)!="Map"){
			MakeNameEx(target,functionName,0);
		}else{
			functionName = GetTrueName(target);
		}		
		if(offset>0x7FFF){
			functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
		}else{
			functionRef = form("%s-%s",functionName,GetTrueName(base));
		}
		if(Byte(ea+1)==0){
			SetManualInsn   (ea, form("msDefaultZoneEvent %s", functionRef));
		}else{
			SetManualInsn   (ea, form("msDftZoneEvent %d, %s", Byte(ea+1), functionRef));
		}
	}
}

static parseMapSetupSection4(ea,map,flag){
	auto base, j, x, y, parameter, textbanksFile, dialogLine, lineNumber, currentLine, baseInvestigationLineIndex, baseDescriptionLineIndex, investigationLineIndex, descriptionLineIndex, investigationLine, descriptionLine, offset, target, functionName, index, flagName, functionRef;
	index = 0;
	if(flag!=0){
		flagName = form("_%s",ltoa(flag,16));
	}else{
		flagName = "";
	}
	baseInvestigationLineIndex = 0x1A7;
	if(Word(ea)!=0x4E75){	
		// parse text start index
		baseDescriptionLineIndex = Word(ea+2);
		parameter = ltoa(baseDescriptionLineIndex,16);
		while(strlen(parameter)<4){
			parameter=form("0%s",parameter);
		}
		textbanksFile = fopen("textbanks.txt","r");
		while(dialogLine==""){
			lineNumber = lineNumber + 1;
			currentLine = readstr(textbanksFile);
			if(currentLine==-1){
				Message(form("\n%s: Could not find dialog line for current parameter 0x%s",ea,parameter));
				break;
			}
			if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
				dialogLine = form("\"%s\"",substr(currentLine,6,strlen(currentLine)-1));
			}
		}
		fclose(textbanksFile);
		//Message(form("\n%s",dialogLine));
		MakeRptCmt(ea,"");
		SetFunctionCmt(ea,"",1);
		MakeComm(ea,dialogLine);
		
		// get entry table address
		ea = ea+6+Word(ea+6);
		base = ea;
		
		// parse table
		while(Byte(ea)!=0xFD){
			for(j=ea;j<ea+6;j++){undefineByte(j);}
			MakeData(ea,FF_BYTE,6,1);
			x = Byte(ea);
			y = Byte(ea+1);
			if(Word(ea+2)==0){
				investigationLineIndex = Byte(ea+4);
				parameter = ltoa(baseInvestigationLineIndex+investigationLineIndex,16);
				while(strlen(parameter)<4){
					parameter=form("0%s",parameter);
				}
				textbanksFile = fopen("textbanks.txt","r");
				while(investigationLine==""){
					lineNumber = lineNumber + 1;
					currentLine = readstr(textbanksFile);
					if(currentLine==-1){
						Message(form("\n%s: Could not find dialog line for current parameter 0x%s",ea,parameter));
						break;
					}
					if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
						investigationLine = form("\"%s\"",substr(currentLine,6,strlen(currentLine)-1));
					}
				}
				fclose(textbanksFile);
				descriptionLineIndex = Byte(ea+5);
				parameter = ltoa(baseDescriptionLineIndex+descriptionLineIndex,16);
				while(strlen(parameter)<4){
					parameter=form("0%s",parameter);
				}
				textbanksFile = fopen("textbanks.txt","r");
				while(descriptionLine==""){
					lineNumber = lineNumber + 1;
					currentLine = readstr(textbanksFile);
					if(currentLine==-1){
						Message(form("\n%s: Could not find dialog line for current parameter 0x%s",ea,parameter));
						break;
					}
					if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
						descriptionLine = form("\"%s\"",substr(currentLine,6,strlen(currentLine)-1));
					}
				}
				fclose(textbanksFile);
				SetManualInsn   (ea, form("msDesc %d, %d, %d, %d", x, y, investigationLineIndex, descriptionLineIndex));
				MakeRptCmt(ea, form("%s\n%s",investigationLine,descriptionLine));
				investigationLine = "";
				descriptionLine = "";
			}else{
				offset = Word(ea+4);
				functionName = form("Map%s%s_DescFunc%s",ltoa(map,10),flagName,ltoa(index,10));
				if(offset>0x7FFF){
					target = base+offset-0x10000;
				}else{
					target = base+offset;
				}
				if(substr(GetTrueName(target),0,3)!="Map"){
					MakeNameEx(target,functionName,0);
				}else{
					functionName = GetTrueName(target);
				}		
				if(offset>0x7FFF){
					functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
				}else{
					functionRef = form("%s-%s",functionName,GetTrueName(base));
				}
				if(Byte(ea+2)==0){
					SetManualInsn   (ea, form("msDescFunction %d, %d, %s", x, y, functionRef));	
				}else{
					SetManualInsn   (ea, form("msDescFunctionD6 %d, %d, $%s, %s", x, y, ltoa(Byte(ea+2),16), functionRef));	
				}
				index = index + 1;
			}
			ea = ea+6;
		}
		for(j=ea;j<ea+2;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,2,1);
		SetManualInsn   (ea, "msDescEnd");	
	
	}

}


static parseMapSetupSection5(ea,map,flag){
	auto base, j, x, y, facing, item, offset, target, functionName, index, flagName, functionRef;
	base = ea;
	index = 0;
	if(flag!=0){
		flagName = form("_%s",ltoa(flag,16));
	}else{
		flagName = "";
	}
	while(Byte(ea)!=0xFD){
		for(j=ea;j<ea+6;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,6,1);
		x = Byte(ea);
		y = Byte(ea+1);
		facing = Byte(ea+2);
		item = Byte(ea+3);
		offset = Word(ea+4);
		functionName = form("Map%s%s_ItemEvent%s",ltoa(map,10),flagName,ltoa(index,10));
		if(offset>0x7FFF){
			target = base+offset-0x10000;
		}else{
			target = base+offset;
		}
		if(substr(GetTrueName(target),0,3)!="Map"){
			MakeNameEx(target,functionName,0);
		}else{
			functionName = GetTrueName(target);
		}		
		if(offset>0x7FFF){
			functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
		}else{
			functionRef = form("%s-%s",functionName,GetTrueName(base));
		}
		SetManualInsn   (ea, form("msItemEvent %d, %d, %s, %d, %s", x, y, getDirection(facing), item, functionRef));
		//Message(form("0x%s: %s\n",ltoa(ea,16),functionName));	
		ea = ea+6;
		index = index+1;
	}
	for(j=ea;j<ea+6;j++){undefineByte(j);}
	MakeData(ea,FF_BYTE,6,1);
	offset = Word(ea+4);
		functionName = form("Map%s%s_DefaultItemEvent%s",ltoa(map,10),flagName,ltoa(index,10));
		if(offset>0x7FFF){
			target = base+offset-0x10000;
		}else{
			target = base+offset;
		}
		if(substr(GetTrueName(target),0,3)!="Map"){
			MakeNameEx(target,functionName,0);
		}else{
			functionName = GetTrueName(target);
		}		
		if(offset>0x7FFF){
			functionRef = form("(%s-%s) & $FFFF",functionName,GetTrueName(base));
		}else{
			functionRef = form("%s-%s",functionName,GetTrueName(base));
		}
		SetManualInsn   (ea, form("msDefaultItemEvent %s", functionRef));
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

static getDirectionAsMacro(cmd){
	auto id,enumSize,constant,j,constId,output;
	id = GetEnum("Direction");
	enumSize = GetEnumSize(id);
	constant = GetFirstConst(id,-1);	
	while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				if(constant==cmd){
					return substr(GetConstName(constId),0,1);
				}
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
	}
	return form("%s",ltoa(cmd,10));
}

static getMapsprite(cmd){
	auto id,enumSize,constant,j,constId,output;
	id = GetEnum("Mapsprites");
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

static getMapspriteOrAlly(cmd){
	auto id,enumSize,constant,j,constId,output;
	if(cmd<0x1E){
		id = GetEnum("Allies");
	}else{
		id = GetEnum("Mapsprites");
	}
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