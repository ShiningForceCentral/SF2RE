


#include <idc.idc>


static main(void){

	Message("\nPARSING MAP SETUP Section 1 : Entities ...\n");
	parseAllMapSetupsSection1();	
	Message("END OF PARSING.\n");	


}

static parseAllMapSetupsSection1(){
	auto addr,j,firstMs;
	addr = 0x4F6E2;
	while(Word(addr)!=0xFFFF){
		firstMs = 1;
		while(Word(addr)!=0xFFFD){
			if(firstMs){
				for(j=addr;j<addr+6;j++){undefineByte(j);}
				MakeData(addr,FF_BYTE,6,1);
				SetManualInsn   (addr, form("msMap %d, %s",Word(addr),GetTrueName(Dword(addr+2))));
				firstMs = 0;
			}else{
				for(j=addr;j<addr+6;j++){undefineByte(j);}
				MakeData(addr,FF_BYTE,6,1);
				SetManualInsn   (addr, form("msFlag %d, %s",Word(addr),GetTrueName(Dword(addr+2))));
			}
			parseMapSetupSection1(Dword(Dword(addr+2)));
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


static parseMapSetupSection1(ea){
	auto j, x, y, facing, sprite, scriptName, walkX, walkY, walkDist;

	while(Word(ea)!=0xFFFF){
	
		for(j=ea;j<ea+8;j++){undefineByte(j);}
		MakeData(ea,FF_BYTE,8,1);
		x = Byte(ea);
		y = Byte(ea+1);
		facing = getDirection(Byte(ea+2));
		sprite = Byte(ea+3);
		if(Byte(ea+4)==0xFF){
			walkX = Byte(ea+5);
			walkY = Byte(ea+6);
			walkDist = Byte(ea+7);
			SetManualInsn   (ea, form("msWalkingEntity %d, %d, %s, %d, %d, %d, %d",x, y, facing, sprite, walkX, walkY, walkDist));
		}else if(Byte(ea+4)==0xFE){
			MakeNameEx(Dword(ea+4)-0xFE000000,form("ems_%s",ltoa(Dword(ea+4)-0xFE000000,16)),0);
			scriptName = GetTrueName(Dword(ea+4)-0xFE000000);
			SetManualInsn   (ea, form("msSequencedEntity %d, %d, %s, %d, %s",x, y, facing, sprite, scriptName));
			parseEntityMoveSequence(Dword(ea+4)-0xFE000000);
		}else{
			if(GetTrueName(Dword(ea+4))==""){MakeNameEx(Dword(ea+4),"",SN_AUTO);}
			scriptName = GetTrueName(Dword(ea+4));
			SetManualInsn   (ea, form("msFixedEntity %d, %d, %s, %d, %s",x, y, facing, sprite, scriptName));
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