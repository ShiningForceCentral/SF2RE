


#include <idc.idc>


static main(void){

	Message("\nPARSING MAP SETUP Section 4...\n");
	parseMapSetupSection4(ScreenEA());	
	Message("END OF PARSING.\n");	


}


static parseMapSetupSection4(ea){
	auto base;
	base = ea;

	while(Byte(ea)!=0xFD){
		MakeWord(ea);
		MakeByte(ea+2);
		MakeByte(ea+3);	
		if(Byte(ea+3)==0){
			MakeByte(ea+4);
			MakeByte(ea+5);	
		}
		else{
			if(Word(ea+4) > 0x8000) {
				OpOffEx(ea+4, -1, REF_LOW16, base + (Word(ea+4)+0xFFFF0000), base, 0);
				MakeCode(base+Word(ea+4)-0x10000);
			}
			else{
				OpOffEx(ea+4, -1, REF_OFF32, -1, base, 0);
				MakeCode(base+Word(ea+4));
			}
		}		
		ea = ea + 6;	
	}
	MakeWord(ea);
}