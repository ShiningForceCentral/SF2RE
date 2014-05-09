

#include <idc.idc>


static main(void) {

	auto i,j,index,path;
	auto start,end,lastEntryDataEnd,chunkEnd,addr,from,dref,dataEnd,jdref,action,file;
	
	i = 0;
	start = 0xC8000;
	end = 0xC8B40;
	lastEntryDataEnd = 0xFFC48;
	chunkEnd = 0x100000;
	addr = start;
	action=1;
	
	file = fopen("splitentitysprites.txt","w");
	
	
	while(addr!=end&&action==1){
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		addr=addr+4;
		i++;
	}
	
	i = 0;
	addr = start;

	while(addr<end&&action==1){
	
		dref = Dfirst(addr);
		Jump(dref);
		
		dataEnd = 0;
		
		if((addr+4)<end){
			j = dref+1;
			while(dataEnd==0){
				from = DfirstB(j);
				while(from!=BADADDR){
					if(from>=start&&from<end){
						dataEnd = j;
					}
		      from=DnextB(addr,from);      
				}
				j++;
				if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
			}
		}
		else{dataEnd = lastEntryDataEnd;}
		
		for(j=dref+1;j<dataEnd;j++){undefineByte(j);}
		
		Message(form("dref %s, dataEnd %s\n",ltoa(dref,16),ltoa(dataEnd,16)));
		MakeData(dref,FF_BYTE,dataEnd-dref,1);
		
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("00%s",index);
		if(strlen(index)==2)index=form("0%s",index);
		MakeNameEx(dref,form("EntitySprite%s",index),0);
		SetManualInsn   (dref, form("incbin \"sprites/entities/entitysprite%s.bin\"",index));
		writestr(file,form("#split\t0x%s,0x%s,sprites/entities/entitysprite%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
		
		addr=addr+4;
		i++;
	}
	
	Message("end");
	
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
}