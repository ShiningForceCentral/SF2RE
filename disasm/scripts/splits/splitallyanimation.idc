#include <idc.idc>
static main(void) {

auto i,j,index,path;
auto addr,dref,jdref,action,file;

i = 0;
addr = 0x1AAC3A;
action=1;

file = fopen("splitallyanimations.txt","w");

while(addr!=0x1AAD96&&action==1){
	Jump(addr);
	
	dref = Dfirst(addr);
	
	Jump(dref);
	
	j = dref+1;
	Message(form("dref %s, j %s\n",ltoa(dref,16),ltoa(j,16)));
	while(DfirstB(j)==-1){
	j++;
	}
	MakeData(dref,FF_BYTE,j-dref,1);
	
	index = ltoa(i,10);
	if(strlen(index)==1)index=form("00%s",index);
	if(strlen(index)==2)index=form("0%s",index);
	
	MakeNameEx(dref,form("AllyAnimation%s",index),0);
	SetManualInsn   (dref, form("incbin \"battles/animations/allies/allyanimation%s.bin\"",index));
	
	writestr(file,form("#split\t0x%s,0x%s,battles/animations/allies/allyanimation%s.bin\n",ltoa(dref,16),ltoa(j,16),index));
	
	addr=addr+4;
	i++;
	
	//action = AskYN(1,"Ok ?");
}

fclose(file);

}

