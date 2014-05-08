#include <idc.idc>
static main(void) {

auto i,j,x,s,index,path;
auto start,base,addr,end,dref,section,action,file;

i = 1;
start = 0x1B8028;
end = 0x1B80A0;
addr = start;
action=1;

file = fopen("splitbattlescenegrounds.txt","w");

while(addr!=end&&action==1){
	Jump(addr);

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
	
	Message(form("dref %s, base %s\n",ltoa(dref,16),ltoa(base,16)));
	dref = base + Word(base);
	Jump(dref);
	Message(form("dref %s\n",ltoa(dref,16)));
	
	
	j = dref+1;
	Message(form("dref %s, j %s\n",ltoa(dref,16),ltoa(j,16)));
	while(DfirstB(j)==-1){
		j++;
	}
	Message(form("dref %s, j %s\n",ltoa(dref,16),ltoa(j,16)));
	MakeData(dref,FF_BYTE,j-dref,1); 
	
	MakeNameEx(dref,"",0);
	MakeNameEx(dref,form("groundTiles%s",index),0);
	SetManualInsn   (dref, form("incbin \"battles/grounds/ground%s.bin\"",index));
	writestr(file,form("#split\t0x%s,0x%s,battles/grounds/ground%s.bin\n",ltoa(dref,16),ltoa(j,16),index));
	
	addr=addr+4;
	i++;
	action = AskYN(1,"Ok ?");
}

fclose(file);

}

