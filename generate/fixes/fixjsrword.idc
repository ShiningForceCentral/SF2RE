/*
 * 	It is known that IDA's mc68 module doesn't
 *	properly output certain instructions with 
 *	specific addressing modes. 
 *
 *	This script helps to fix one of these 
 *	instructions : 
 *	jsr (loc).w were displayed as jsr loc. 
 *
 *	It finds jsr (loc).w instructions 
 *	from current address and asks for each one
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

	auto addr; // current location
	
	auto opnd; // operand found at current location
	
	auto action; // action asked to user
	
	auto rep; // proper representation of instruction
	
	auto pattern; // byte pattern to find
	
	pattern = "4E B8"; // opcode for jsr (loc).w
	
	// Start search from current address on screen
	for(addr=FindBinary(ScreenEA(),7,pattern);addr!=BADADDR;addr=FindBinary(addr+1,7,pattern)){
		
		opnd = GetOpnd(addr,0);
		
		if (opnd!=""){
		
			rep = form("jsr     (%s).w",opnd);
			
			Jump(addr);
		
			//action = AskYN(1,form("Change representation from jsr %s to jsr (%s).w ?",opnd, opnd));
			action = 1;
		
			if (action==-1) break;
			if (action==1){
				Message(form("\n0x%d : jsr %s changed to jsr (%s).w",addr,opnd, opnd));
				SetManualInsn(addr,rep);
			}
			else{
				Message(form("\n0x%d : jsr %s NOT changed to jsr (%s).w",addr,opnd, opnd));
			}
		
		}

		
	}


}


