

#include <idc.idc>
static main(void) {

	auto i,j,x,s,index,path;
	auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,file;
	
	i = 0;
	start = 0x1C8004;
	end = 0x1C80E4;
	addr = start;
	lastEntryDataEnd = 0x1D7E26;
	chunkEnd = 0x1D8000;
	
	action=1;
	
	file = fopen("splitportraits.txt","w");
	
	for(j=start;j<chunkEnd;j++){undefineByte(j);}
	
	MakeNameEx(addr,"pt_Portraits",0);
	
	while(addr<end&&action==1){
		
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);		
		Jump(dref);
		
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("0%s",index);
		
		MakeNameEx(dref,form("Portrait%s",index),0);
		
		addr=addr+4;
		i++;
	
	}


	i = 0;
	addr = start;
	while(addr!=end&&action==1){
		
		dref = Dfirst(addr);		
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
				SetManualInsn   (dref, form("incbin \"portraits/portrait%s.bin\"",index));
				writestr(file,form("#split\t0x%s,0x%s,portraits/portrait%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
			
		addr=addr+4;
		i++;
		
		//action = AskYN(1,"Ok ?");
	}

	MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,15);
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

