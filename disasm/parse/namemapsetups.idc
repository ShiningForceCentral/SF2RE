




#include <idc.idc>


static main(void){

	Message("\nNAMING MAP SETUPS...\n");
	nameMapSetups();	
	Message("END OF NAMING.\n");	


}


static nameMapSetups(){

	auto ea,i,j,action,start,mapId,isDef,flag;
	action = 1;
	start = 0x4F6E2;
	isDef = 1;
	
	ea = start;
	
	for(j=start;j<0x64000;j++){
		if(strstr(GetTrueName(j),"ms_map")!=-1){
			MakeNameEx(j,"",0);
		}	
	}
	
	while(action==1&&Word(ea)!=0xFFFF){
	
		//Jump(ea);
	
		while(Word(ea)!=0xFFFD){
		
			if(isDef == 1){
				mapId = ltoa(Word(ea),10);
				MakeNameExC(Dword(ea+2),form("ms_map%s",mapId),0);
				nameMapSetup(Dword(ea+2),form("ms_map%s",mapId));
				isDef = 0;
				ea = ea + 6;
			}
			else{
				flag = Word(ea);
				MakeRptCmt(ea,getFlagDesc(flag));
				MakeNameExC(Dword(ea+2),form("ms_map%s_flag%s",mapId,ltoa(flag,16)),0);
				nameMapSetup(Dword(ea+2),form("ms_map%s_flag%s",mapId,ltoa(flag,16)));		
				ea = ea + 6;
			}
		}
		//action = AskYN(1,"Continue ?");
		isDef = 1;
		ea = ea + 2;
	}

}

static nameMapSetup(ea,baseName){

	auto j;

	parseMapSetupEntities(Dword(ea),baseName);

	parseMapSetupSection2(Dword(ea+4),baseName);

	parseMapSetupSection3(Dword(ea+8),baseName);

	parseMapSetupSection4(Dword(ea+12),baseName);

	parseMapSetupSection5(Dword(ea+16),baseName);

	parseMapSetupInitFunction(Dword(ea+0x14),baseName);
	
	

}

static parseMapSetupEntities(ea,baseName){
	auto j;
	MakeNameExC(ea,form("%s_Entities",baseName),0);
}


static parseMapSetupSection2(ea,baseName){
	auto base;
	MakeNameExC(ea,form("%s_EntityEvents",baseName),0);
}


static parseMapSetupSection3(ea,baseName){
	auto base;
	MakeNameExC(ea,form("%s_ZoneEvents",baseName),0);
}

static parseMapSetupSection4(ea,baseName){
	MakeNameExC(ea,form("%s_AreaDescriptions",baseName),0);
	/* TODO
	 * parse base line index
	 * and comment each area with corresponding line !
	 */
}

static parseMapSetupSection5(ea,baseName){
	auto base;
	base = ea;
	if(Word(ea)==0x4E75){
		return;
	}
	MakeNameExC(ea,form("%s_Section5",baseName),0);
}

static parseMapSetupInitFunction(ea,baseName){
	MakeNameExC(ea,form("%s_InitFunction",baseName),0);
}

static MakeNameExC(addr,name,flags){

	auto current;
	current = GetTrueName(addr);
	if(current=="" || strstr(current,"unk_")!=-1 || strstr(current,"byte_")!=-1 || strstr(current,"word_")!=-1 || strstr(current,"dword_")!=-1 || strstr(current,"off_")!=-1 || strstr(current,"sub_")!=-1){
		MakeNameEx(addr,name,flags);
	}

}

/* 
 *	Makes sure byte at addr is
 *	clean for new formatting
 */
static undefineByte(addr){
		auto from;
		from = DfirstB(addr);
		while(from!=BADADDR){
			//Message(form("Removed DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
		}		
		from = RfirstB(addr);
		while(from!=BADADDR){
			//Message(form("Removed Code XRref at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
		}				
		MakeUnkn(addr,DOUNK_DELNAMES);
		MakeNameEx(addr,"",0);
		SetManualInsn(addr,"");
}

static getFlagDesc(flag){

			auto flagmapFile, lineNumber, currentLine, flagDesc;
			flag = ltoa(flag,16);
			while(strlen(flag)<4){
				flag=form("0%s",flag);
			}
			lineNumber = 0;
			flagmapFile = fopen("flagmap.txt","r");
			while(flagDesc==""){
				lineNumber = lineNumber + 1;
				currentLine = readstr(flagmapFile);
				/* if(lineNumber % 100 == 0) {
				 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
				} */
				if(currentLine==-1){
					Message(form("\nCould not find dialog line for current parameter 0x%s",flag));
					break;
				}
				if(strlen(currentLine)>=4 && substr(currentLine,0,4)==flag){
					flagDesc = form("%s",substr(currentLine,5,strlen(currentLine)-1));
				}
			}
			fclose(flagmapFile);
			
			return flagDesc;

}