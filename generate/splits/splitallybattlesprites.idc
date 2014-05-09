

#include <idc.idc>


static main(void) {

	auto i,j,index,path;
	auto start,end,lastEntryDataEnd,addr,dref,dataEnd,jdref,action,file;
	
	i = 0;
	start = 0x18001C;
	end = 0x18009C;
	lastEntryDataEnd = 0x1AA16E;
	addr = start;
	action=1;
	
	file = fopen("splitallybattlesprites.txt","w");
	
	while(addr!=end&&action==1){
	
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);
		Jump(dref);
		
		if((addr+4)!=end){dataEnd = Dword(addr+4);}
		else{dataEnd = lastEntryDataEnd;}
		
		for(j=dref+1;j<dataEnd;j++){undefineByte(j);}
		
		Message(form("dref %s, dataEnd %s\n",ltoa(dref,16),ltoa(dataEnd,16)));
		MakeData(dref,FF_BYTE,dataEnd-dref,1);
		
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("0%s",index);
		MakeNameEx(dref,form("AllyBattleSprite%s",index),0);
		SetManualInsn   (dref, form("incbin \"sprites/battlesprites/allies/allybattlesprite%s.bin\"",index));
		writestr(file,form("#split\t0x%s,0x%s,sprites/battlesprites/allies/allybattlesprite%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
		
		addr=addr+4;
		i++;
	}
	
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