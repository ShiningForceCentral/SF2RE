
/*
 *	PARSETRAP5 SCRIPT 
 *	This script will scan "TRAP 5" instructions 
 *  and parse the following word to add corresponding dialog line in the comment,
 *  for easier code readability.
 *  Corresponding line is taken from the game's uncompressed scriptbanks,
 *  all compiled into one txt file thanks to BNC.
 *  
 *  Execution requirement : put textbanks.txt in IDB directory.
 * 
 */

#include <idc.idc>

static main(void) {

	Message("SCANNING TRAP 5...\n");
	
	scanTrap5();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 5 SCAN.\n");
	Batch(0);

}


static scanTrap5(){

	auto addr; // current location
	auto parameter; // parameter found after TRAP 5
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto dialogLine;
	auto newComment; // comment to add
	auto textbanksFile, currentLine, lineNumber; 
	action = 1;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	//if (action==-1) return;
	//if (action==1){
	//	addr = ScreenEA();
	//}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,"4E 45");addr!=BADADDR;addr=FindBinary(addr+1,7,"4E 45")){
		dialogLine = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
			//MakeUnkn(addr+1,DOUNK_DELNAMES);
			//MakeUnkn(addr+2,DOUNK_DELNAMES);
			//MakeUnkn(addr+3,DOUNK_DELNAMES);
			//MakeData(addr,FF_BYTE,4,1);
			parameter = ltoa(Word(addr+2),16);
			while(strlen(parameter)<4){
				parameter=form("0%s",parameter);
			}
			//Message(form("\nBinary value 0x4E45 with parameter value 0x%s at address 0x%s in code : searching for dialog line.",ltoa(Word(addr+2),16),ltoa(addr,16)));
			
			if(Word(addr+2)!=0xFFFF){
				textbanksFile = fopen("textbanks.txt","r");
				while(dialogLine==""){
					lineNumber = lineNumber + 1;
					currentLine = readstr(textbanksFile);
					/* if(lineNumber % 100 == 0) {
					 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
					} */
					if(currentLine==-1){
						Message(form("\n%s: Could not find dialog line for current parameter 0x%s",addr,parameter));
						break;
					}
					if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
						dialogLine = form("\"%s\"",substr(currentLine,6,strlen(currentLine)-1));
					}
				}
				fclose(textbanksFile);
				if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
					MakeUnkn(addr,DOUNK_DELNAMES);
					MakeUnkn(addr+1,DOUNK_DELNAMES);
					MakeUnkn(addr+2,DOUNK_DELNAMES);
					MakeUnkn(addr+3,DOUNK_DELNAMES);
					MakeData(addr,FF_BYTE,4,1);
					SetManualInsn(addr, form("txt $%s", ltoa(Word(addr+2),16)));
					MakeRptCmt(addr,dialogLine);
				}else{
					SetManualInsn(addr, " ");
					SetManualInsn(addr+2, form("txt $%s", ltoa(Word(addr+2),16)));
					MakeRptCmt(addr,"");
					MakeRptCmt(addr+2,dialogLine);
				}				
			}else{			
				if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
					MakeUnkn(addr,DOUNK_DELNAMES);
					MakeUnkn(addr+1,DOUNK_DELNAMES);
					MakeUnkn(addr+2,DOUNK_DELNAMES);
					MakeUnkn(addr+3,DOUNK_DELNAMES);
					MakeData(addr,FF_BYTE,4,1);
					SetManualInsn(addr, "clsTxt");
				}else{
					SetManualInsn(addr, " ");
					SetManualInsn(addr+2, "clsTxt");
				}
			}
			
			/*
			if (dialogLine!=""){
				//newComment = form(dialogLine);
				newComment = "";
				//action = AskYN(1,form("Update comment ? \nFrom %s\nTo : %s",CommentEx(addr+2,1), newComment));
				if (action==-1) return;
				if (action==1){
					//Message(form("\n0x%s : %s changed to %s",ltoa(addr+2,16),CommentEx(addr+2,1), newComment));  
					MakeComm(addr+2,""); 
					MakeRptCmt(addr+2,newComment);
				}
				else{
					Message(form("\n0x%s : %s NOT changed to %s",ltoa(addr+2,16),CommentEx(addr+2,1), newComment));
				}
			}
			*/
			//cont = AskYN(1,"Continue ?");
			if (cont==-1 || cont==0) return;	
		}
		else{
			Message(form("\n0x%s: Binary value 0x4E45 with parameter 0x%s not in code",ltoa(addr,16),ltoa(Word(addr+2),16)));
		}
	}
	
}


