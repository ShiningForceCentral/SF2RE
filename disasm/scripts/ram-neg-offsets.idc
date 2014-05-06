/*
 * This script was written to replace negative RAM references (i.e., trying to move 0xFFFFDEF2 into a word)
 * with manual definitions to existing RAM labels minus $1000000 (NEG_RAM_OFFSET)
 * This way, RAM offsets always point to the same segment with no doubles.

 * If a RAM offset reference has to be changed, do it manually with the "manual operand" command (Atl-F1).
 * Example : ((byte_FFF7A8-$1000000)).w
 *
 */

#include <idc.idc>

static ReplaceNegRamOffset(ea, n)
{
	auto optype, opvalue, addrname, sizetype;
	
	optype = GetOpType(ea, n);
	
	if (optype == 2)
	{
		opvalue = GetOperandValue(ea, n);
		sizetype = "w";
		
		if (opvalue < 0)
		//	sizetype = "w";
		{	
			Message("EA %x, Operand %d = %s (value %x) (type %d) (flags %x) (sizetype %s)\n", ea, n, GetOpnd(ea, n), opvalue, GetOpType(ea, n), GetFlags(ea), sizetype);
			opvalue = opvalue & 0x00ffffff;
			addrname = Name(opvalue);
			if (addrname != "")
				OpAlt(ea, n, form("((%s + %s)).%s", addrname, "NRO", sizetype));
			else
				Message("Skipped because no name defined\n");
			//OpOff(ea, n, opvalue);
			//OpSign(ea, n);
			//OpOffEx(ea, n, REF_OFF32, -1, opvalue, -2);
			//OpOffEx(addr, 1, 0x0100, 10, 20, 30);
		}
	}
	
	return;
}

static main(void) 
{

	auto addr, dref, next, action, opnd, before, after;
	auto optype0, optype1;
	auto opvalue0, opvalue1;
	auto addrname;
	
	//Jump(0x21e);
	
	addr = ScreenEA();
	
	Message("\n-------------------------\n");
	Message("Running ram-neg-offsets.idc starting at address ROM:%x\n", addr);
	//Message(form("addr %d\n",addr));

	//addr_lbl = LocByName("FADING_COUNTER_MAX");
	
	Message("%s\n", Name(0x00ffdef2)); // prints "FADING_COUNTER_MAX"
	
	ReplaceNegRamOffset(addr, 0);
	ReplaceNegRamOffset(addr, 1);

	
	/*for (addr = addr; addr != BADADDR; addr=addr+1)
	{
		
		if(addr < 0xFFFF8000)
			addr = 0xFFFF8000;
		
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
		
	}*/

	Message("End of execution\n");
	Message("-------------------------\n\n");
	
}

