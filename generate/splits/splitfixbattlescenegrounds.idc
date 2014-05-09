


#include <idc.idc>
static main(void) {

	auto i,j,x,s,index,path;
	auto start,end,lastEntryDataEnd,chunkEnd,addr,base,dataEnd,from,dref,section,action,file;
	
	i = 0;
	start = 0x1B8028;
	end = 0x1B80A0;
	addr = start;
	lastEntryDataEnd = 0x1B9A9A;
	chunkEnd = 0x1B9A9A;
	
	action=1;
	
	file = fopen("splitbattlescenegrounds.txt","w");
	
	for(j=start;j<chunkEnd;j++){undefineByte(j);}
	
	MakeNameEx(addr,"pt_BattleSceneGrounds",0);

	while(addr<end&&action==1){
		
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);		
		Jump(dref);
		
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("0%s",index);
		
		MakeNameEx(dref,form("battlesceneGround%s",index),0);
		
		MakeData(dref, FF_WORD, 0x2, 0);
		MakeData(dref+2, FF_WORD, 0x2, 0);
		MakeData(dref+4, FF_WORD, 0x2, 0);
		MakeData(dref+6, FF_WORD, 0x2, 0);
		MakeNameEx(dref+6,form("bsg%s_rpbase",index),0);
		
		base = dref+6;
		OpOffEx(base, -1, REF_OFF32, -1, base, 0);
		section = Word(base) + base;
		add_dref(base,section,dr_O);
		Message("base %a, section %a\n",base, section);
		MakeNameEx(section,form("groundTiles%s",index),0);
		
		addr=addr+4;
		i++;
	
	}


	i = 0;
	addr = start;
	while(addr!=end&&action==1){
		
		dref = Dfirst(addr);
		base = dref+6;
		dref = Word(base) + base;	
		Jump(dref); 
			
				dataEnd = 0;
				
				j = dref+1;
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
				
				index = ltoa(i,10);
				if(strlen(index)==1)index=form("0%s",index);
				
				Message(form("dref %s, dataEnd %s\n",ltoa(dref,16),ltoa(dataEnd,16)));
				
				MakeData(dref,FF_BYTE,dataEnd-dref,1);
				SetManualInsn   (dref, form("incbin \"battles/grounds/ground%s.bin\"",index));
				writestr(file,form("#split\t0x%s,0x%s,battles/grounds/ground%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
			
		addr=addr+4;
		i++;
		
		//action = AskYN(1,"Ok ?");
	}

	fclose(file);

}



static undefineByte(addr){
		auto from;
		from = DfirstB(addr);
		while(from!=BADADDR){
			Message(form("Removing DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
		}		
		from = RfirstB(addr);
		while(from!=BADADDR){
			Message(form("Removing CODE XRef at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
		}				
		MakeUnkn(addr,DOUNK_DELNAMES);
		MakeNameEx(addr,"",0);
		SetManualInsn(addr,"");
}