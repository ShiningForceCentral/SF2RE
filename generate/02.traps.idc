
/*
 *	PARSETRAP0 SCRIPT 
 *	This script will scan "TRAP 0" instructions 
 *  and parse the following word to add corresponding sound command 
 *  as a constant from an Enum, for easier code readability.
 * 
 */

#include <idc.idc>



static main(void) {

	Message("SCANNING TRAPS...\n");
	
	parseSoundTrap();
	parseFlagTraps();
	parseTextTrap();
	parseScriptTrap();
	
	Message("END OF TRAPS SCAN.\n");
	Batch(0);

}

static parseSoundTrap(void) {

	Message("SCANNING TRAP 0...\n");
	
	scanTrap0();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 0 SCAN.\n");

}



/* SOUND */


static scanTrap0(){

	auto addr; // current location
	auto parameter; // parameter found after TRAP 0
	auto action; 
	auto cont; // script continuation asked to user
	auto param;
	action = 0;
	cont = 1;
	addr=0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,"4E 40");addr!=BADADDR;addr=FindBinary(addr+1,7,"4E 40")){

		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
		
			parameter = Word(addr+2);

			//Message(form("\nBinary value 0x4E40 with parameter value 0x%s at address 0x%s in code.",ltoa(parameter,16),ltoa(addr,16)));
			
			if(parameter == 0x20
					|| (parameter >= 0xF0 &&  parameter <= 0xFFFF)){
					OpEnumEx(addr+2,0,GetEnum("SoundCommands"),0);
					param = GetConstName(GetConstEx(GetEnum("SoundCommands"),parameter,0,0));
			}
			else if(parameter >= 0 && parameter <= 0x29){
					OpEnumEx(addr+2,0,GetEnum("Music"),0);
					param = GetConstName(GetConstEx(GetEnum("Music"),parameter,0,0));
			}
			else if(parameter >= 0x41 && parameter <= 0x78){
					OpEnumEx(addr+2,0,GetEnum("Sfx"),0);
					param = GetConstName(GetConstEx(GetEnum("Sfx"),parameter,0,0));
			}	
			else{
				param = form("$%s",ltoa(addr+2,16));
				Message(form("%s: could not process trap 0 value %d",ltoa(addr,16),parameter));
			}					
			
			/* Macro formatting */
			if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr+2,DOUNK_DELNAMES);
				MakeUnkn(addr+3,DOUNK_DELNAMES);
				MakeData(addr,FF_BYTE,4,1);
				SetManualInsn(addr, form("sndCom  %s", param));
			}else{
				SetManualInsn(addr, " ");
				SetManualInsn(addr+2, form("sndCom  %s", param));
			}
			
			//cont = AskYN(1,"Continue ?");
			//if (cont==-1 || cont==0) return;	
		}
		else{
			Message(form("\n0x%s: Binary value 0x4E40 with parameter value 0x%s not in code",ltoa(addr,16),ltoa(Word(addr+2),16)));
		}
	}
	
}






/* FLAGS */


static parseFlagTraps(void) {

	Message("SCANNING TRAP 1...\n");
	scanTrap1();
	Message("\nDONE. SCANNING TRAP 2...\n");
	scanTrap2();
	Message("\nDONE. SCANNING TRAP 3...\n");
	scanTrap3();
	Message("\nDONE. SCANNING TRAP 4...\n");
	scanTrap4();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 1/2/3/4 SCAN.\n");

}


static scanTrap1(){
	auto trapHexString;
	auto addr; // current location
	auto parameter; // parameter found after TRAP
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto flagDescription;
	auto newComment; // comment to add
	auto flagmapFile, currentLine, lineNumber;
	trapHexString = "4E 41";
	action = 0;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
		flagDescription = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1 && addr%2==0){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
		
			parameter = ltoa(Word(addr+2),16);
			while(strlen(parameter)<4){
				parameter=form("0%s",parameter);
			}
			//Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s in code : searching for flag description.",trapHexString, ltoa(Word(addr+2),16),ltoa(addr,16)));
			
			flagmapFile = fopen("flagmap.txt","r");
			while(flagDescription==""){
			lineNumber = lineNumber + 1;
				currentLine = readstr(flagmapFile);
				/* if(lineNumber % 100 == 0) {
				 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
				} */
				if(currentLine==-1){
					//Message(form("\nCould not find flag description for current parameter 0x%s",parameter));
					break;
				}
				if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
					flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
				}
			}
			fclose(flagmapFile);
			
			/* Macro formatting */
			if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr+2,DOUNK_DELNAMES);
				MakeUnkn(addr+3,DOUNK_DELNAMES);
				MakeData(addr,FF_BYTE,4,1);
				SetManualInsn(addr, form("chkFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,flagDescription);
			}else{
				SetManualInsn(addr, " ");
				SetManualInsn(addr+2, form("chkFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,"");
				MakeRptCmt(addr+2,flagDescription);
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



static scanTrap2(){
	auto trapHexString;
	auto addr; // current location
	auto parameter; // parameter found after TRAP
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto flagDescription;
	auto newComment; // comment to add
	auto flagmapFile, currentLine, lineNumber;
	trapHexString = "4E 42";
	action = 0;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
		flagDescription = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1 && addr%2==0){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
		
			parameter = ltoa(Word(addr+2),16);
			while(strlen(parameter)<4){
				parameter=form("0%s",parameter);
			}
			//Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s in code : searching for flag description.",trapHexString, ltoa(Word(addr+2),16),ltoa(addr,16)));
			
			flagmapFile = fopen("flagmap.txt","r");
			while(flagDescription==""){
			lineNumber = lineNumber + 1;
				currentLine = readstr(flagmapFile);
				/* if(lineNumber % 100 == 0) {
				 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
				} */
				if(currentLine==-1){
					//Message(form("\nCould not find flag description for current parameter 0x%s",parameter));
					break;
				}
				if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
					flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
				}
			}
			fclose(flagmapFile);
			
			/* Macro formatting */
			if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr+2,DOUNK_DELNAMES);
				MakeUnkn(addr+3,DOUNK_DELNAMES);
				MakeData(addr,FF_BYTE,4,1);
				SetManualInsn(addr, form("setFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,flagDescription);
			}else{
				SetManualInsn(addr, " ");
				SetManualInsn(addr+2, form("setFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,"");
				MakeRptCmt(addr+2,flagDescription);
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



static scanTrap3(){
	auto trapHexString;
	auto addr; // current location
	auto parameter; // parameter found after TRAP
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto flagDescription;
	auto newComment; // comment to add
	auto flagmapFile, currentLine, lineNumber;
	trapHexString = "4E 43";
	action = 0;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
		flagDescription = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1 && addr%2==0){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
		
			parameter = ltoa(Word(addr+2),16);
			while(strlen(parameter)<4){
				parameter=form("0%s",parameter);
			}
			//Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s in code : searching for flag description.",trapHexString, ltoa(Word(addr+2),16),ltoa(addr,16)));
			
			flagmapFile = fopen("flagmap.txt","r");
			while(flagDescription==""){
			lineNumber = lineNumber + 1;
				currentLine = readstr(flagmapFile);
				/* if(lineNumber % 100 == 0) {
				 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
				} */
				if(currentLine==-1){
					//Message(form("\nCould not find flag description for current parameter 0x%s",parameter));
					break;
				}
				if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
					flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
				}
			}
			fclose(flagmapFile);
			
			/* Macro formatting */
			if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr+2,DOUNK_DELNAMES);
				MakeUnkn(addr+3,DOUNK_DELNAMES);
				MakeData(addr,FF_BYTE,4,1);
				SetManualInsn(addr, form("clrFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,flagDescription);
			}else{
				SetManualInsn(addr, " ");
				SetManualInsn(addr+2, form("clrFlg  $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,"");
				MakeRptCmt(addr+2,flagDescription);
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



static scanTrap4(){
	auto trapHexString;
	auto addr; // current location
	auto parameter; // parameter found after TRAP
	auto action; // comment update confirmation asked to user
	auto cont; // script continuation asked to user
	auto flagDescription;
	auto newComment; // comment to add
	auto flagmapFile, currentLine, lineNumber;
	trapHexString = "4E 44";
	action = 0;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
	if (action==-1) return;
	if (action==1){
		addr = ScreenEA();
	}
	Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
	
	for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
		flagDescription = "";
		//Jump(addr);
		if(GetFunctionAttr(addr, FUNCATTR_START)!=-1 && addr%2==0){
		
			OpEnumEx(addr,0,GetEnum("Traps"),0);
			MakeWord(addr+2);
		
			parameter = ltoa(Word(addr+2),16);
			while(strlen(parameter)<4){
				parameter=form("0%s",parameter);
			}
			//Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s in code : searching for flag description.",trapHexString, ltoa(Word(addr+2),16),ltoa(addr,16)));
			
			flagmapFile = fopen("flagmap.txt","r");
			while(flagDescription==""){
			lineNumber = lineNumber + 1;
				currentLine = readstr(flagmapFile);
				/* if(lineNumber % 100 == 0) {
				 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
				} */
				if(currentLine==-1){
					//Message(form("\nCould not find flag description for current parameter 0x%s",parameter));
					break;
				}
				if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
					flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
				}
			}
			fclose(flagmapFile);
			
			/* Macro formatting */
			if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
				MakeUnkn(addr,DOUNK_DELNAMES);
				MakeUnkn(addr+1,DOUNK_DELNAMES);
				MakeUnkn(addr+2,DOUNK_DELNAMES);
				MakeUnkn(addr+3,DOUNK_DELNAMES);
				MakeData(addr,FF_BYTE,4,1);
				SetManualInsn(addr, form("checkFlg $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,flagDescription);
			}else{
				SetManualInsn(addr, " ");
				SetManualInsn(addr+2, form("checkFlg $%s", ltoa(Word(addr+2),16)));
				MakeRptCmt(addr,"");
				MakeRptCmt(addr+2,flagDescription);
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




/* TEXT */


static parseTextTrap(void) {

	Message("SCANNING TRAP 5...\n");
	
	scanTrap5();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 5 SCAN.\n");

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
					SetManualInsn(addr, form("txt     $%s", ltoa(Word(addr+2),16)));
					MakeRptCmt(addr,dialogLine);
				}else{
					SetManualInsn(addr, " ");
					SetManualInsn(addr+2, form("txt     $%s", ltoa(Word(addr+2),16)));
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



/* SCRIPTS */

static parseScriptTrap(void) {

	Message("SCANNING TRAP 6...\n");
	scanTrap6();
	Message("\nDONE.\n");
	
	Message("END OF TRAP 6 SCAN.\n");

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
	action = 0;
	cont = 1;
	addr=0;
	lineNumber = 0;
	//action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
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

