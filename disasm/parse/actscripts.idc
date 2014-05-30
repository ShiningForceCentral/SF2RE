

#include <idc.idc>


static main(void){


	parseEAS(0x4497A,0x449C6);
	parseEAS(0x44DE2,0x45204);
	parseEAS(0x452A4,0x45322);	
	parseEAS(0x45360,0x453C6);
	parseEAS(0x4540C,0x4543F);
	parseEAS(0x45488,0x4549C);		
	parseEAS(0x45556,0x455AC);	
	parseEAS(0x455DC,0x45634);				
	parseEAS(0x45E44,0x46506);


}



static parseEAS(start,end){

	auto ea,cmdLength,cmdName,cmdComment,action;
	
	cmdLength = 2;
	ea = start;
	action = 1;
	
	Message(form("\n%a : START OF EAS PARSING",ea));

	while(ea<end&&action==1){

		MakeWord(ea);
		
		if(Word(ea)==0x0000){
			cmdName = "0000 WAIT";
			cmdComment = form("%s value $%s",cmdName, ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
		}
		else if(Word(ea)==0x0001){
			cmdName = "0001 WAIT UNTIL DESTINATION";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		else if(Word(ea)==0x0002){
			cmdName = "0002 BIG ONE RELATED TO CAMERA";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(Word(ea)==0x0003){
			cmdName = "0003 ";
			cmdComment = form("%s $%s $%s $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(Word(ea)==0x0004){
			cmdName = "0004 MOVE TO RELATIVE DEST";
			cmdComment = form("%s X=X+$%s Y=Y+$%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0005){
			cmdName = "0005 MOVE TO ABSOLUTE DEST";
			cmdComment = form("%s X=$%s Y=$%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0006){
			cmdName = "0006 ";
			cmdComment = form("%s $%s $%s $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);				
		}
		else if(Word(ea)==0x0007){
			cmdName = "0007 CONTROLLING RAFT";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(Word(ea)==0x0008){
			cmdName = "0008 CONTROLLING CARAVAN";
			cmdComment = form("%s ",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(Word(ea)==0x0009){
			cmdName = "0009 ";
			cmdComment = form("%s $%s $%s",cmdName, ltoa(Word(ea+2),16), ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
			MakeWord(ea+4);			
		}		
		else if(Word(ea)==0x000A){
			cmdName = "000A UPDATE SPRITE";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);			
		}
		else if(Word(ea)==0x000B){
			cmdName = "000B SET SPRITE SIZE";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x000C){
			cmdName = "000C SET POSITION";
			cmdComment = form("%s X=$%s Y=$%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);			
		}
		else if(Word(ea)==0x000D){
			cmdName = "000D CLONE POSITION";
			cmdComment = form("%s FROM ENTITY $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x000E){
			cmdName = "000E ";
			cmdComment = form("%s $%s $%s $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);				
		}
		else if(Word(ea)==0x000F){
			cmdName = "000F WAIT UNTIL DES REACHED BY ENTITY";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0010){
			cmdName = "0010 SET SPEED";
			cmdComment = form("%s X=$%s Y=$%s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);				
			MakeByte(ea+3);
		}
		else if(Word(ea)==0x0011){
			cmdName = "0011 ";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0012){
			cmdName = "0012 ";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0013){
			cmdName = "0013 ";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);					
		}
		else if(Word(ea)==0x0014){
			cmdName = "0014 SET ANIM COUNTER";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0015){
			cmdName = "0015 SET ABILITY TO CHANGE FACING";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0016){
			cmdName = "0016 SET ENTITY NUMBER";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0017){
			cmdName = "0017 SET ENTITY SPRITE";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0018){
			cmdName = "0018 SET 1C BIT 7";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0019){
			cmdName = "0019 SET 1C BIT 6";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001A){
			cmdName = "001A SET 1C BIT 5";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001B){
			cmdName = "001B SET FLIPPING";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001C){
			cmdName = "001C SET TRANSPARENCY";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001D){
			cmdName = "001D SET GHOST";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001E){
			cmdName = "001E SET ANIM SPEED X2";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x001F){
			cmdName = "001F SET 1D BIT 3";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0020){
			cmdName = "0020 SET ENTITY IN WATER";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0021){
			cmdName = "0021 SET 1C BIT 4";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0022){
			cmdName = "0022 SET FACING";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0023){
			cmdName = "0023 SEND SOUND COMMAND";
			cmdComment = form("%s $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(Word(ea)==0x0030){
			cmdName = "0030 BRANCH";
			cmdComment = form("%s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
			makeRelativeOffset(ea+2);			
		}
		else if(Word(ea)==0x0031){
			cmdName = "0031 BRANCH IF SET FLAG";
			cmdComment = form("%s %s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);			
			MakeWord(ea+2);		
			makeRelativeOffset(ea+2);	
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0032){
			cmdName = "0032 BRANCH IF CLEARED FLAG";
			cmdComment = form("%s %s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
			makeRelativeOffset(ea+2);					
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0033){
			cmdName = "0033 RANDOM BRANCH";
			cmdComment = form("%s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
			MakeWord(ea+2);			
			makeRelativeOffset(ea+2);				
			MakeWord(ea+4);			
		}
		else if(Word(ea)==0x0034){
			cmdName = "0034 JUMP";
			cmdComment = form("%s TO ABSOLUTE ADDR. 0x%s",cmdName,ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			OpOff(ea+2,0,0);				
		}
		else if(Word(ea)==0x0040){
			cmdName = "0040 ";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(Word(ea)==0x0041){
			cmdName = "0041 PASS";
			cmdComment = form("%s",cmdName);
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else{
			cmdComment = form("Unkown command : %s",ltoa(Word(ea),16));
			Message(form("\n%s",cmdComment));
			MakeRptCmt(ea,cmdComment);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		
		MakeRptCmt(ea,cmdComment);
		//Message(form("\n%a : %s",ea,cmdComment));
		ea = ea + cmdLength;

		
		//action = AskYN(1,"Continue ?");
	
	
		
	}



	Message(form("\n%a : END OF EAS PARSING",ea));

}


static makeRelativeOffset(addr){

		if(Word(addr) > 0x8000) {
			OpOffEx(addr, -1, REF_OFF32, addr - 2 + Word(addr) - 0x10000, addr-2, 0x10000);
		}
		else{
			OpOffEx(addr, -1, REF_OFF32, -1, addr-2, 0);
		}

}


