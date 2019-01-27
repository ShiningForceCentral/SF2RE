
/*
 *	PARSETRAP5 SCRIPT 
 *	This script will scan "TRAP 6" instructions 
 *  and parse the previous "lea" instruction to format them in a single mapscript macro,
 *  for easier code readability.
 * 
 */

#include <idc.idc>

static main(void) {

	Message("SCANNING TRAP 6...\n");
	scanTrap6();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 6 SCAN.\n");
	Batch(0);

}


static scanTrap6(){
	auto trapHexString;
	auto offset;
	auto scriptName;
	auto addr; // current location
	auto parameter; // parameter found after TRAP
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto flagDescription;
	auto newComment; // comment to add
	auto flagmapFile, currentLine, lineNumber;
	trapHexString = "4E 46";
	action = 1;
	cont = 1;
	addr=0;
	lineNumber = 0;
	action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
		flagDescription = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1 && addr%2==0 && Word(addr-4)==0x41FA){
			
			offset = Word(addr-2);
			if(offset>0x7FFF){
				scriptName = GetTrueName(addr-2+offset-0x10000);
			}else{
				scriptName = GetTrueName(addr-2+offset);
			}
			
			/* Macro formatting */
			if(addr-4!=GetFunctionAttr(addr-4,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr-4,DOUNK_DELNAMES);
				MakeUnkn(addr-3,DOUNK_DELNAMES);
				MakeUnkn(addr-2,DOUNK_DELNAMES);
				MakeUnkn(addr-1,DOUNK_DELNAMES);
				MakeData(addr-4,FF_BYTE,6,1);
				SetManualInsn(addr-4, form("script  %s", scriptName,16));
			}else{
				SetManualInsn(addr-4, " ");
				SetManualInsn(addr, form("script  %s", scriptName,16));
			}
			
			/*
			if (flagDescription!=""){
				newComment = form(flagDescription);
				action = AskYN(1,form("Update comment ? \nFrom %s\nTo : %s",CommentEx(addr+2,1), newComment));
				if (action==-1) return;
				if (action==1){
					Message(form("\n0x%s : %s changed to %s",ltoa(addr+2,16),CommentEx(addr+2,1), newComment));  
					MakeComm(addr+2,""); 
					MakeRptCmt(addr+2,newComment);
				}
				else{
					Message(form("\n0x%s : %s NOT changed to %s",ltoa(addr+2,16),CommentEx(addr+2,1), newComment));
				}
			}
			*/
			//cont = AskYN(1,"Continue ?");
			//if (cont==-1 || cont==0) return;	
		}
		else{
			Message(form("\n0x%s: Binary value \"%s\" with parameter value 0x%s not in code",ltoa(addr,16),trapHexString,ltoa(Word(addr+2),16)));
		}
	}
	
}



