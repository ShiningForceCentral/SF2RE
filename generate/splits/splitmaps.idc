#include <idc.idc>
static main(void) {

	auto i,j,x,s,index,path;
	auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,file;
	
	i = 0;
	start = 0x94B8A;
	end = 0x94CC6;
	addr = start;
	lastEntryDataEnd = 0xC7ECC;
	chunkEnd = 0xC8000;
	
	action=1;
	
	file = fopen("splitmaps.txt","w");
	
	for(j=start;j<chunkEnd;j++){undefineByte(j);}
	
	MakeNameEx(addr,"pt_MapData",0);
	
	while(addr<end&&action==1){
		
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);		
		Jump(dref);
		
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("0%s",index);
		
		MakeNameEx(dref,form("Map%s",index),0);
		writestr(file,form("#dir\tmaps/map%s\n",index));
		MakeData(dref, FF_BYTE, 0x1, 0);
		MakeData(dref+1, FF_BYTE, 0x1, 0);
		MakeData(dref+2, FF_BYTE, 0x1, 0);
		MakeData(dref+3, FF_BYTE, 0x1, 0);
		MakeData(dref+4, FF_BYTE, 0x1, 0);
		MakeData(dref+5, FF_BYTE, 0x1, 0);
		
		for(s=0;s!=10;s++){
			from = dref+6+4*s;
			MakeDword(from);
			section = Dword(from);
			add_dref(from,section,dr_O);
			MakeNameEx(section,form("Map%sSection%d",index,s),0);
		} 
		
		addr=addr+4;
		i++;
	
	}


	i = 0;
	addr = start;
	while(addr!=end&&action==1){
		
		dref = Dfirst(addr);		
		Jump(dref); 
			
		for(s=0;s!=10;s++){
		
			section = Dfirst(dref+6+4*s);
			
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
				
				index = ltoa(i,10);
				if(strlen(index)==1)index=form("0%s",index);
				
				Message(form("section %s, dataEnd %s\n",ltoa(section,16),ltoa(dataEnd,16)));
				
				MakeData(section,FF_BYTE,dataEnd-section,1);
				SetManualInsn   (section, form("incbin \"maps/map%s/section%d.bin\"",index,s));
				writestr(file,form("#split\t0x%s,0x%s,maps/map%s/section%d.bin\n",ltoa(section,16),ltoa(dataEnd,16),index,s));
			
			}
		
		}
			
		addr=addr+4;
		i++;
		
		//action = AskYN(1,"Ok ?");
	}

	MakeAlign(lastEntryDataEnd, chunkEnd-lastEntryDataEnd,15);
	fclose(file);

}



static undefineByte(addr){
		auto from;
		from = DfirstB(addr);
		while(from!=BADADDR){
			Message(form("addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
		}		
		from = RfirstB(addr);
		while(from!=BADADDR){
			Message(form("addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
		}				
		MakeUnkn(addr,DOUNK_DELNAMES);
		MakeNameEx(addr,"",0);
		SetManualInsn(addr,"");
}