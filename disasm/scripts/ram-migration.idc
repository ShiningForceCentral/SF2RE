/*
 * This script was written to unify both RAM and RAMFF segments into a single RAM segment.
 * This way, RAM offsets always point to the same segment with no doubles.
 * 
 * The script changes references to the old RAMFF segment so that they now point to the RAM segment adequately.
 *
 * This script should not need to be executed again.
 * If a RAM offset reference has to be changed, do it manually with the "manual operand" command (Atl-F1).
 * Example : ((byte_FFF7A8-$1000000)).w
 *
 */

#include <idc.idc>
static main(void) {

auto addr,dref,next,action,opnd,before,after;

Message(form("addr %d",addr));


	for(addr=ScreenEA();addr!=BADADDR;addr=addr+1){
		
		if(addr<0xFFFF8000)addr=0xFFFF8000;
		
		Jump(addr);
		Message(form("\naddr %s",ltoa(addr,16)));
		
		for(dref=DfirstB(addr);dref!=-1;dref=DnextB(addr,dref)){
		
			Jump(dref);
		
			Message(form("\naddr %s, dref %s, ",ltoa(addr,16), ltoa(dref,16)));
			
			//action = AskYN(1,form("addr %s, dref %s, ",ltoa(addr,16), ltoa(dref,16)));
			action = 1;
			//if (action==-1) break;
			if (action==1){
			
				opnd = GetOperandValue(dref,0);
				if(opnd==addr){
					before = GetOpnd(dref,0);
					OpOffEx(ScreenEA(),0,REF_OFF32,GetOperandValue(ScreenEA(),0)-0xFF000000,0x0,0xFF000000);
					add_dref(ScreenEA(),GetOperandValue(ScreenEA(),0)-0xFF000000,fl_F | XREF_USER);
					after = GetOpnd(dref,0);
					Message(form("from %s to %s",before,after));
					//action = AskYN(1,"Ok ?");
					//if (action!=1) break;
				}
				else{
					opnd = GetOperandValue(dref,1);
					if(opnd==addr){
						before = GetOpnd(dref,1);
						OpOffEx(ScreenEA(),1,REF_OFF32,GetOperandValue(ScreenEA(),1)-0xFF000000,0x0,0xFF000000);
						add_dref(ScreenEA(),GetOperandValue(ScreenEA(),1)-0xFF000000,fl_F | XREF_USER);
						after = GetOpnd(dref,1);	
						Message(form("from %s to %s",before,after));	
						//action = AskYN(1,"Ok ?");
						//if (action!=1) break;			
					}
					else{
						Message(form("opnd not found ?"));
						action = AskYN(1,form("addr %s, dref %s",ltoa(addr,16), ltoa(dref,16)));
						if (action==-1) break;
					}
				}
			}
			else{
				Message("passed");
			}
		}
		
		//if (action==-1) break;
		
	}

}

