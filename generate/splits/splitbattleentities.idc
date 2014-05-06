#include <idc.idc>
static main(void) {

auto i,j,index,path;
auto addr,dref,jdref,action,file;

i = 0;
addr = 0x1B30EE;
action=1;

file = fopen("splitbattleentities.txt","w");

while(addr!=0x1B31A2&&action==1){
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
	if(strlen(index)==1)index=form("0%s",index);
	
	MakeNameEx(dref,form("BattleEntitySetup%s",index),0);
	SetManualInsn   (dref, form("incbin \"battles/entitysetups/battleentitysetup%s.bin\"",index));
	
	writestr(file,form("#split\t0x%s,0x%s,battles/entitysetups/battleentitysetup%s.bin\n",ltoa(dref,16),ltoa(j,16),index));
	
	addr=addr+4;
	i++;
	
	//action = AskYN(1,"Ok ?");
}

fclose(file);

}

