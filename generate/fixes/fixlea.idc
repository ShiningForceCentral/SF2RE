/*
 * 	It is known that IDA's mc68 module doesn't
 *	properly output certain instructions with 
 *	specific addressing modes. 
 *
 *	This script helps to fix these 
 *	instructions :  
 *	lea loc(pc),a0 were displayed as lea loc, a0.
 *	lea loc(pc),a1 were displayed as lea loc, a1. 
 *	lea loc(pc),a2 were displayed as lea loc, a2. 
 *	lea loc(pc),a3 were displayed as lea loc, a3. 
 *	lea loc(pc),a4 were displayed as lea loc, a4. 
 *	lea loc(pc),a5 were displayed as lea loc, a5. 
 *	lea loc(pc),a6 were displayed as lea loc, a6. 
 *	lea loc(pc),a7 were displayed as lea loc, a7. 
 *
 *
 *	It finds every instructions 
 *	in formatted code and asks for each one
 *	of them if you want it to be properly formatted.
 *
 *	"No" skips the instruction.
 *	"Cancel" stops the script.
 *
 *	Be aware that it will only find instructions if they have been formatted as code. 
 *	They won't be identified if they are still known as pure data. 
 *
 */


#include <idc.idc>

static main(void) {

auto batch;

batch = AskYN(1,"Batch mode ?");
Batch(batch);



fix("41 FA","lea     %s(pc), a0","lea loc, a0","lea loc(pc),a0");
fix("43 FA","lea     %s(pc), a1","lea loc, a1","lea loc(pc),a1");
fix("45 FA","lea     %s(pc), a2","lea loc, a2","lea loc(pc),a2");
fix("47 FA","lea     %s(pc), a3","lea loc, a3","lea loc(pc),a3");
fix("49 FA","lea     %s(pc), a4","lea loc, a4","lea loc(pc),a4");
fix("4B FA","lea     %s(pc), a5","lea loc, a5","lea loc(pc),a5");
fix("4D FA","lea     %s(pc), a6","lea loc, a6","lea loc(pc),a6");
fix("4F FA","lea     %s(pc), a7","lea loc, a7","lea loc(pc),a7");

}



static fix(pattern, manualInstruction, wrongInstString, newInstString){

	auto addr; // current location
	
	auto opnd; // operand found at current location
	
	auto action; // action asked to user
	
	auto rep; // proper representation of instruction
	
	action = 1;
	
	// Start search from current address on screen
	for(addr=0;addr!=BADADDR;addr=FindBinary(addr+1,7,pattern)){
		
		opnd = GetOpnd(addr,0);
		
		if (opnd!=""){
		
			rep = form(manualInstruction,opnd);
		
			Jump(addr);
		
			action = AskYN(1,form("Change representation from %s to %s ?",wrongInstString, newInstString));
		
			if (action==-1) break;
			if (action==1){
				Message(form("\n0x%d : %s changed to %s",addr,wrongInstString, newInstString));
				SetManualInsn(addr,rep);
			}
			else{
				Message(form("\n0x%d : %s NOT changed to %s",addr,wrongInstString, newInstString));
			}
		
		}

		
	}

}