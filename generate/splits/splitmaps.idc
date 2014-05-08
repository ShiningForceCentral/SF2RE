#include <idc.idc>
static main(void) {

auto i,j,x,s,index,path;
auto addr,dref,section,action,file;

i = 0;
addr = 0x94B8A;
action=1;

file = fopen("splitmaps.txt","w");

while(addr!=0x94CC6&&action==1){
	Jump(addr);
	
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
	
		section = Dfirst(dref+6+4*s);
		x = section+1;
		Message(form("\nsection%s, x%s ",ltoa(section,16),ltoa(x,16)));
		while(DfirstB(x)==-1){
			x++;
			//Message(form("x%s;",ltoa(x,16)));
		}
		MakeData(section,FF_BYTE,x-section,1);
		MakeNameEx(section,form("Map%sSection%d",index,s),0);
		SetManualInsn   (section, form("incbin \"maps/map%s/section%d.bin\"",index,s));
		writestr(file,form("#split\t0x%s,0x%s,maps/map%s/section%d.bin\n",ltoa(section,16),ltoa(x,16),index,s));
		
	}
		
	addr=addr+4;
	i++;
	
	action = AskYN(1,"Ok ?");
}

fclose(file);

}

