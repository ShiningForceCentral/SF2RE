#include <idc.idc>
static main(void) {

auto i,j,index,path;
auto addr,dref,jdref,action,file;

i = 0;
addr = 0x1B9A9A;
action=1;

file = fopen("splitweaponsprites.txt","w");

while(addr!=0x1B9AF6&&action==1){
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
	
	MakeNameEx(dref,form("WeaponSprite%s",index),0);
	SetManualInsn   (dref, form("incbin \"sprites/weapons/weaponsprite%s.bin\"",index));
	
	writestr(file,form("#split\t0x%s,0x%s,sprites/weapons/weaponsprite%s.bin\n",ltoa(dref,16),ltoa(j,16),index));
	
	addr=addr+4;
	i++;
	
	//action = AskYN(1,"Ok ?");
}

fclose(file);

}

