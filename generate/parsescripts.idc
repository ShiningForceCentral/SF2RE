

#include <idc.idc>


static main(void){

	if(AskYN(1,"Parse cutscene at current cursor position ?")!=1){
		parseAll();
	}
	else{
		parseSingleCS(ScreenEA());
	}
	


}

static parseAll(){

	Message("\nPARSING...\n");
	Message("Entity Actscripts...");
	parseActscripts();
	Message(" DONE.\nCutscenes ...");	
	parseCutscenes();
	Message(" DONE.\n");		
	Message("END OF PARSING.\n");	

}

static parseActscripts(){
	// ACTSCRIPTS
	
	parseEAS(0x4497A,0x449C6);
	parseEAS(0x44DE2,0x45204);
	parseEAS(0x452A4,0x45322);	
	parseEAS(0x45360,0x453C6);
	parseEAS(0x4540C,0x4543F);
	parseEAS(0x45488,0x4549C);		
	parseEAS(0x45556,0x455AC);	
	parseEAS(0x455DC,0x45634);				
	parseEAS(0x45E44,0x46506);
				
	parseEAS(0x493A2,0x493CE);	
	
	parseEAS(0x51840,0x51912);
	
	parseEAS(0x5E2C4,0x5E320);
	parseEAS(0x5EF46,0x5EF60);	
	parseEAS(0x5FFC4,0x60024);	
	
	
}

static parseSingleCS(ea){

	auto file;
	
	file = fopen("parsecommands.txt","a");
	writestr(file,form("\n\tparseCS(0x%s,-1);",ltoa(ea,16)));
	parseCS(ea,0x64000);


	file = fclose(file);

}

static parseCutscenes(){
	// INTRO CUTSCENE
	parseCS(0x47F7E,0x48340);
	parseCS(0x48380,0x48510);
	parseCS(0x48540,0x48A50);
	parseCS(0x48A78,0x48FAA);
	
	
	// END CUTSCENE
	parseCS(0x49058,0x492CC);	
	
	parseCS(0x4931C,0x4933E);									
	parseCS(0x4933E,0x49358);
	parseCS(0x49358,0x49384);
	parseCS(0x49384,0x493A2);		
	
	// unused broken cutscenes ? 	parseCS(0x493CE,0x493EC);
	//														parseCS(0x493FA,0x494AC);	
		
	
	parseCS(0x494BC,0x49694);
	parseCS(0x496DC,0x4980E);		
	parseCS(0x4980E,0x49816);		
	parseCS(0x4981E,0x498EE);		
	parseCS(0x498EE,0x49AB2);		
	parseCS(0x49AB2,0x49B48);		
	parseCS(0x49B48,0x49BCA);
	parseCS(0x49BCA,0x49CE2);
	parseCS(0x49CE2,0x49F7E);
	parseCS(0x49F7E,0x4A952);
	parseCS(0x4A952,0x4A994);	
	parseCS(0x4A994,0x4AA74);	
	parseCS(0x4AA74,0x4AAB6);	
	parseCS(0x4AAB6,0x4ABFE);		
	parseCS(0x4ABFE,0x4ACC8);	
	parseCS(0x4ACC8,0x4ACEC);
	parseCS(0x4ACEC,0x4ACF8);
	parseCS(0x4ACF8,0x4ADA6);
	parseCS(0x4ADA6,0x4AE72);
	parseCS(0x4AE72,0x4AFBE);
	parseCS(0x4AFBE,0x4B1BC);
	parseCS(0x4B1BC,0x4B1CA);
	parseCS(0x4B1D8,0x4B2F2);
	parseCS(0x4B2F2,0x4B6CE);
	parseCS(0x4B6CE,0x4B790);
	parseCS(0x4B790,0x4B88C);
	parseCS(0x4B88C,0x4B958);		
	parseCS(0x4B958,0x4BCAA);	
	parseCS(0x4BCAA,0x4BE6A);	
	parseCS(0x4BE6A,0x4BE8C);	
	parseCS(0x4BE8C,0x4C07C);	
	parseCS(0x4C07C,0x4C3DC);	
	parseCS(0x4C3DC,0x4C5E6);	
	parseCS(0x4C5E6,0x4C6A8);	
	parseCS(0x4C6A8,0x4C994);	
	parseCS(0x4C994,0x4CBE2);	
	parseCS(0x4CBE2,0x4CD10);	
	parseCS(0x4CD10,0x4CD56);	
	parseCS(0x4CDB4,0x4CF0C);	
	parseCS(0x4CF0C,0x4D09A);	
	parseCS(0x4D09A,0x4D342);	
	parseCS(0x4D342,0x4D4B6);	
	parseCS(0x4D4B6,0x4D6CE);	
	parseCS(0x4D6CE,0x4D88A);	
	parseCS(0x4D88A,0x4D9A4);	
	parseCS(0x4D9A4,0x4DA66);	
	parseCS(0x4DA66,0x4DB94);	
	parseCS(0x4DB94,0x4DDA4);	
	parseCS(0x4DDA4,0x4DE8C);	
	parseCS(0x4DE8C,0x4E3D2);	
	parseCS(0x4E3D2,0x4E4DC);	
	parseCS(0x4E4DC,0x4E8A8);
	parseCS(0x4E8A8,0x4E9B2);
	parseCS(0x4E9B2,0x4EA94);			
	parseCS(0x4EA94,0x4ED0E);	
	parseCS(0x4ED0E,0x4ED8E);	
	parseCS(0x4ED8E,0x4EF04);	
	parseCS(0x4EF04,0x4F358);	
	parseCS(0x4F358,0x4F35E);	
	parseCS(0x4F35E,0x4F47A);	
	parseCS(0x4F47A,0x4F48A);	
	


	parseCS(0x4FB64,-1);
	parseCS(0x4FC32,-1);
	parseCS(0x4FF42,-1);
	parseCS(0x4FF5A,-1);
	parseCS(0x4FFDA,-1);
	parseCS(0x5023E,-1);
	parseCS(0x503A6,-1);
	parseCS(0x50806,-1);
	parseCS(0x50ABE,-1);
	parseCS(0x512BA,-1);
	parseCS(0x51374,-1);
	parseCS(0x5137A,-1);
	parseCS(0x513A0,-1);
	parseCS(0x513BA,-1);
	parseCS(0x513CE,-1);
	parseCS(0x513D6,-1);
	parseCS(0x513E2,-1);
	parseCS(0x51444,-1);
	parseCS(0x5144C,-1);
	parseCS(0x51454,-1);
	parseCS(0x5145C,-1);
	parseCS(0x5148C,-1);
	parseCS(0x5149A,-1);
	parseCS(0x51652,-1);
	parseCS(0x516A8,-1);
	parseCS(0x51742,-1);
	parseCS(0x51750,-1);
	parseCS(0x51B14,-1);
	parseCS(0x51F88,-1);
	parseCS(0x521BA,-1);
	parseCS(0x5247C,-1);
	parseCS(0x5249E,-1);
	parseCS(0x52530,-1);
	parseCS(0x528CA,-1);
	parseCS(0x528D4,-1);
	parseCS(0x52938,-1);
	parseCS(0x52A3C,-1);
	parseCS(0x52F0C,-1);
	parseCS(0x52F24,-1);
	parseCS(0x52F40,-1);
	parseCS(0x53104,-1);
	parseCS(0x53176,-1);
	parseCS(0x534D2,-1);
	parseCS(0x535FA,-1);
	parseCS(0x53620,-1);
	parseCS(0x5362A,-1);
	parseCS(0x53816,-1);
	parseCS(0x53996,-1);
	parseCS(0x53B66,-1);
	parseCS(0x53EF4,-1);
	parseCS(0x53F2A,-1);
	parseCS(0x53FD8,-1);
	parseCS(0x53FE0,-1);
	parseCS(0x540C0,-1);
	parseCS(0x54570,-1);
	parseCS(0x54578,-1);
	parseCS(0x54CC6,-1);
	parseCS(0x54E70,-1);
	parseCS(0x54E78,-1);
	parseCS(0x54E86,-1);
	parseCS(0x54F26,-1);
	parseCS(0x55242,-1);
	parseCS(0x55288,-1);
	parseCS(0x55832,-1);
	parseCS(0x55A36,-1);
	parseCS(0x55BEE,-1);
	parseCS(0x56146,-1);
	parseCS(0x56172,-1);
	parseCS(0x56314,-1);
	parseCS(0x563B2,-1);
	parseCS(0x56422,-1);
	parseCS(0x568F6,-1);
	parseCS(0x569BC,-1);
	parseCS(0x56AE6,-1);
	parseCS(0x570B0,-1);
	parseCS(0x573EC,-1);
	parseCS(0x574A6,-1);
	parseCS(0x5766C,-1);
	parseCS(0x5779C,-1);
	parseCS(0x5797A,-1);
	parseCS(0x57AAA,-1);
	parseCS(0x57D22,-1);
	parseCS(0x58116,-1);
	parseCS(0x58310,-1);
	parseCS(0x58330,-1);
	parseCS(0x58512,-1);
	parseCS(0x585FE,-1);
	parseCS(0x58856,-1);
	parseCS(0x58AE2,-1);
	parseCS(0x58B7A,-1);
	parseCS(0x58E5C,-1);
	parseCS(0x58F5C,-1);
	parseCS(0x58F7E,-1);
	parseCS(0x58FA4,-1);
	parseCS(0x59656,-1);
	parseCS(0x5994E,-1);
	parseCS(0x5996E,-1);
	parseCS(0x599A4,-1);
	parseCS(0x599B2,-1);
	parseCS(0x59C9E,-1);
	parseCS(0x59CAA,-1);
	parseCS(0x59E04,-1);
	parseCS(0x59F20,-1);
	parseCS(0x59FB8,-1);
	parseCS(0x5A256,-1);
	parseCS(0x5A30C,-1);
	parseCS(0x5A31E,-1);
	parseCS(0x5A33A,-1);
	parseCS(0x5A4FE,-1);
	parseCS(0x5A828,-1);
	parseCS(0x5A8CA,-1);
	parseCS(0x5A8E6,-1);
	parseCS(0x5A90E,-1);
	parseCS(0x5A92A,-1);
	parseCS(0x5A93A,-1);
	parseCS(0x5A956,-1);
	parseCS(0x5A97E,-1);
	parseCS(0x5A99A,-1);
	parseCS(0x5A9AA,-1);
	parseCS(0x5A9C6,-1);
	parseCS(0x5A9EE,-1);
	parseCS(0x5AA0A,-1);
	parseCS(0x5AA1A,-1);
	parseCS(0x5AA36,-1);
	parseCS(0x5AA5E,-1);
	parseCS(0x5AA7A,-1);
	parseCS(0x5ABA8,-1);
	parseCS(0x5ABCC,-1);
	parseCS(0x5ABE6,-1);
	parseCS(0x5AC04,-1);
	parseCS(0x5AC1C,-1);
	parseCS(0x5AC34,-1);
	parseCS(0x5AC4C,-1);
	parseCS(0x5AC58,-1);
	parseCS(0x5AF36,-1);
	parseCS(0x5B016,-1);
	parseCS(0x5B466,-1);
	parseCS(0x5B6C0,-1);
	parseCS(0x5C312,-1);
	parseCS(0x5C3AA,-1);
	parseCS(0x5C3D8,-1);
	parseCS(0x5C4EE,-1);
	parseCS(0x5C622,-1);
	parseCS(0x5C6CA,-1);
	parseCS(0x5C876,-1);
	parseCS(0x5C8D4,-1);
	parseCS(0x5C8FE,-1);
	parseCS(0x5C914,-1);
	parseCS(0x5CA5E,-1);
	parseCS(0x5CA6E,-1);
	parseCS(0x5CB34,-1);
	parseCS(0x5CBB4,-1);
	parseCS(0x5CC26,-1);
	parseCS(0x5CCF6,-1);
	parseCS(0x5D04E,-1);
	parseCS(0x5D3AA,-1);
	parseCS(0x5D3B8,-1);
	parseCS(0x5D63C,-1);
	parseCS(0x5D644,-1);
	parseCS(0x5D652,-1);
	parseCS(0x5D712,-1);
	parseCS(0x5D724,-1);
	parseCS(0x5D732,-1);
	parseCS(0x5DA28,-1);
	parseCS(0x5DA7A,-1);
	parseCS(0x5DD8E,-1);
	parseCS(0x5DD9C,-1);
	parseCS(0x5DE22,-1);
	parseCS(0x5DE76,-1);
	parseCS(0x5E0EE,-1);
	parseCS(0x5E0F8,-1);
	parseCS(0x5E20A,-1);
	parseCS(0x5E27C,-1);	
	parseCS(0x5E320,-1);
	parseCS(0x5E346,-1);
	parseCS(0x5E3C2,-1);
	parseCS(0x5E772,-1);
	parseCS(0x5EB26,-1);
	parseCS(0x5EB44,-1);
	parseCS(0x5EBFC,-1);
	parseCS(0x5ED06,-1);
	parseCS(0x5EDB8,-1);	
	parseCS(0x5EF60,-1);
	parseCS(0x5F3A2,-1);
	parseCS(0x5F3C4,-1);
	parseCS(0x5F4AE,-1);
	parseCS(0x5F4B8,-1);
	parseCS(0x5F594,-1);
	parseCS(0x5FA9C,-1);
	parseCS(0x5FABC,-1);
	parseCS(0x5FB30,-1);
	parseCS(0x5FB6A,-1);
	parseCS(0x5FE9A,-1);
	parseCS(0x5FF06,-1);	
	parseCS(0x600B2,-1);
	parseCS(0x600CE,-1);
	parseCS(0x6060E,-1);
	parseCS(0x60656,-1);
	parseCS(0x606AC,-1);
	parseCS(0x606E0,-1);
	parseCS(0x606EA,-1);
	parseCS(0x60708,-1);
	parseCS(0x607DE,-1);
	parseCS(0x6093A,-1);
	parseCS(0x60B10,-1);
	parseCS(0x60BA6,-1);
	parseCS(0x60C42,-1);
	parseCS(0x60CA4,-1);
	parseCS(0x60EB2,-1);
	parseCS(0x60F18,-1);
	parseCS(0x60F64,-1);
	parseCS(0x60FA4,-1);
	parseCS(0x612BE,-1);
	parseCS(0x6143C,-1);
	parseCS(0x6150A,-1);
	parseCS(0x615E6,-1);
	parseCS(0x6283E,-1);
	parseCS(0x628C8,-1);
	parseCS(0x6290C,-1);
	parseCS(0x62D06,-1);
	parseCS(0x62D0E,-1);
	parseCS(0x632EA,-1);
	parseCS(0x6335E,-1);
	parseCS(0x633B2,-1);
	parseCS(0x633C4,-1);																																																											

}


static parseCS(start,end){

	auto ea,cmd,cmdLength,cmdName,cmdComment,i,action;
	
	cmdLength = 2;
	ea = start;
	
	action = 1;
	
	//Message(form("\n%a : START OF CS PARSING",ea));
	
	if(end!=-1&&(end-start)<0x1000){
		for(i=start;i<end;i++){
			MakeRptCmt(i,"");
		}	
	}
	
	while(action==1){
	
		//Jump(ea);
		
		if(Word(ea)==0xFFFF){
			MakeWord(ea);
			MakeRptCmt(ea,"END OF CUTSCENE SCRIPT");
			break;
		}		

		cmd = Byte(ea+1);
		
		if(Word(ea)>0x7FFF){
			cmdName = "WAIT";
			cmdComment = form("%s %s",cmdName,ltoa(Byte(ea+1),16));
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeByte(ea);
			MakeByte(ea+1);						
		}
		else if(cmd==0x0000){
			cmdName = "0000 DISPLAY SINGLE TEXTBOX";
			cmdComment = form("%s %s",cmdName, ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}
		else if(cmd==	0x0001){
			cmdName = "0001 DISPLAY SINGLE TEXT BOX WITH VARS";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0002){
			cmdName = "0002 DISPLAY TEXT BOX";
			cmdComment = form("%s %s",cmdName, ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
		}
		else if(cmd==	0x0003){
			cmdName = "0003 DISPLAY TEXTBOX WITH VARS";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(cmd==	0x0004){
			cmdName = "0004 SET TEXT INDEX";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);					
		}
		else if(cmd==	0x0005){
			cmdName = "0005 PLAY SOUND";
			cmdComment = form("%s %s",cmdName,getSoundName(Word(ea+2)));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0006){
			cmdName = "0006 DO NOTHING";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		else if(cmd==	0x0007){
			cmdName = "0007 EXECUTE MAP SYSTEM EVENT";
			cmdComment = form("%s %s",cmdName, ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeDword(ea+2);
		}
		else if(cmd==	0x0008){
			cmdName = "0008 JOIN FORCE";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);		
		}
		else if(cmd==	0x0009){
			cmdName = "0009 HIDE TEXTBOX AND PORTRAIT";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}				
		else if(cmd==	0x000A){
			cmdName = "000A EXECUTE SUBROUTINE";
			cmdComment = form("%s %s",cmdName,ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			OpOff(ea+2,0,0);	
			MakeCode(Dword(ea+2));
		}
		else if(cmd==	0x000B){
			cmdName = "000B JUMP";
			cmdComment = form("%s %s",cmdName,ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			OpOff(ea+2,0,0);			
		}
		else if(cmd==	0x000C){
			cmdName = "000C JUMP IF SET FLAG";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Dword(ea+4),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			OpOff(ea+4,0,0);	
		}
		else if(cmd==	0x000D){
			cmdName = "000D JUMP IF CLEAR FLAG";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Dword(ea+4),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			OpOff(ea+4,0,0);				
		}
		else if(cmd==	0x000E){
			cmdName = "000E JUMP IF CHARACTER DEAD";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Dword(ea+4),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			OpOff(ea+4,0,0);					
		}
		else if(cmd==	0x000F){
			cmdName = "000F JUMP IF CHARACTER ALIVE";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Dword(ea+4),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			OpOff(ea+4,0,0);			
		}
		else if(cmd==	0x0010){
			cmdName = "0010 SET FLAG";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
			MakeWord(ea+4);
		}
		else if(cmd==	0x0011){
			cmdName = "0011 STORY YESNO PROMPT";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		else if(cmd==	0x0012){
			cmdName = "0012 EXECUTE CONTEXTUAL MENU";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0013){
			cmdName = "0013 SET STORY FLAG";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);					
		}
		else if(cmd==	0x0014){
			cmdName = "0014 SET MANUAL ACTSCRIPT";
			cmdComment = form("%s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16),ltoa(Dword(ea+4),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);	
			MakeByte(ea+3);							
			cmdLength = parseEAS(ea+4,0xFFFFFF) + 2 - ea;
			MakeWord(ea+cmdLength-2);
			MakeRptCmt(ea+cmdLength-2,"0014 END OF MANUAL ACTSCRIPT");
		}
		else if(cmd==	0x0015){
			cmdName = "0015 SET ACTSCRIPT";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16),ltoa(Dword(ea+4),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);	
			MakeByte(ea+3);							
			MakeDword(ea+4);			
		}
		else if(cmd==	0x0016){
			cmdName = "0016 WAIT UNTIL IDLE ENTITY";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0017){
			cmdName = "0017 SET ENTITY POS AND FACING WITH FLASH";
			cmdComment = form("%s %s %s %s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16),ltoa(Byte(ea+4),16),ltoa(Byte(ea+5),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);	
			MakeByte(ea+3);		
			MakeByte(ea+4);	
			MakeByte(ea+5);							
		}
		else if(cmd==	0x0018){
			cmdName = "0018 FLASH ENTITY WHITE";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);				
		}
		else if(cmd==	0x0019){
			cmdName = "0019 SET ENTITY POS AND FACING";
			cmdComment = form("%s %s %s %s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16),ltoa(Byte(ea+4),16),ltoa(Byte(ea+5),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);
			MakeByte(ea+3);
			MakeByte(ea+4);
			MakeByte(ea+5);																
		}
		else if(cmd==	0x001A){
			cmdName = "001A SET ENTITY SPRITE";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
			MakeWord(ea+4);							
		}
		else if(cmd==	0x001B){
			cmdName = "001B START ENTITY ANIM";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x001C){
			cmdName = "001C STOP ENTITY ANIM";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
		}
		else if(cmd==	0x001D){
			cmdName = "001D SHOW PORTRAIT";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
		}
		else if(cmd==	0x001E){
			cmdName = "001E HIDE PORTRAIT";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(cmd==	0x001F){
			cmdName = "001F DECLARE FORCE MEMBER DEAD";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0020){
			cmdName = "0020 DECLARE FORCE MEMBERS ON MAP DEAD";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(cmd==	0x0021){
			cmdName = "0021 REVIVE FORCE MEMBER";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0022){
			cmdName = "0022 ANIMATE ENTITY FADE INOUT";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
			MakeWord(ea+4);							
		}
		else if(cmd==	0x0023){
			cmdName = "0023 SET ENTITY FACING";
			cmdComment = form("%s %s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);	
			MakeByte(ea+3);							
		}
		else if(cmd==	0x0024){
			cmdName = "0024 SET ENTITY FOLLOWED BY CAMERA";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}
		else if(cmd==	0x0025){
			cmdName = "0025 CLONE ENTITY";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);		
		}
		else if(cmd==	0x0026){
			cmdName = "0026 MAKE ENTITY NOD";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}
		else if(cmd==	0x0027){
			cmdName = "0027 MAKE ENTITY SHAKE HEAD";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);
		}
		else if(cmd==	0x0028){
			cmdName = "0028 MOVE ENTITY NEXT TO PLAYER";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0029){
			cmdName = "0029 SET ENTITY DEST";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(cmd==	0x002A){
			cmdName = "002A MAKE ENTITY SHIVER";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);		
		}
		else if(cmd==	0x002B){
			cmdName = "002B ";
			cmdComment = form("%s %s %s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Byte(ea+4),16),ltoa(Byte(ea+5),16),ltoa(Byte(ea+6),16),ltoa(Byte(ea+7),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeByte(ea+4);
			MakeByte(ea+5);
			MakeByte(ea+6);
			MakeByte(ea+7);		
		}
		else if(cmd==	0x002C){
			cmdName = "002C FOLLOW ENTITY";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(cmd==	0x002D){
			cmdName = "002D MOVE ENTITY";
			cmdComment = form("%s %s %s %s %s",cmdName,ltoa(Byte(ea+2),16),ltoa(Byte(ea+3),16),ltoa(Byte(ea+4),16),ltoa(Byte(ea+5),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeByte(ea+2);
			MakeByte(ea+3);
			cmdLength = cmdLength + parseCSC19Data(ea+4);
		}
		else if(cmd==	0x002E){
			cmdName = "002E HIDE ENTITY";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}
		else if(cmd==	0x002F){
			cmdName = "002F ";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0030){
			cmdName = "0030 REMOVE ENTITY SHADOW";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}																										
		else if(cmd==	0x0031){
			cmdName = "0031 MOVE ENTITY ABOVE ENTITY";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);				
		}
		else if(cmd==	0x0032){
			cmdName = "0032 SET CAMERA DEST";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);				
		}
		else if(cmd==	0x0033){
			cmdName = "0033 SET QUAKE AMOUNT";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
		}
		else if(cmd==	0x0034){
			cmdName = "0034 SET BLOCKS";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);				
		}
		else if(cmd==	0x0035){
			cmdName = "0035 SIMILAR TO SET BLOCKS";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);		
		}
		else if(cmd==	0x0036){
			cmdName = "0036 RELATED TO LOADING A MAP";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x0037){
			cmdName = "0037 LOAD MAP AND FADE IN";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(cmd==	0x0039){
			cmdName = "0039 FADE IN FROM BLACK";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x003A){
			cmdName = "003A FADE OUT TO BLACK";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		else if(cmd==	0x003B){
			cmdName = "003B SLOW FADE IN FROM BLACK";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x003C){
			cmdName = "003C SLOW FADE OUT TO BLACK";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		else if(cmd==	0x003D){
			cmdName = "003D TINT MAP";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x003E){
			cmdName = "003E SIMILAR TO TINT MAP";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x003F){
			cmdName = "003F FADE MAP OUT TO WHITE";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x0040){
			cmdName = "0040 FADE MAP IN FROM WHITE";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}																						
		else if(cmd==	0x0041){
			cmdName = "0041 FLASH SCREEN WHITE";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
		}
		else if(cmd==	0x0042){
			cmdName = "0042 RELATED TO LOADING MAP ENTITIES";
			cmdComment = form("%s %s",cmdName,ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			OpOff(ea+2,0,0);
			parseCSC42Struct(Dword(ea+2));		
		}
		else if(cmd==	0x0043){
			cmdName = "0043 RELATED TO BLOCK COPY";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0044){
			cmdName = "0044 ";
			cmdComment = form("%s %s",cmdName,ltoa(Dword(ea+2),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			OpOff(ea+2,0,0);	
		}
		else if(cmd==	0x0045){
			cmdName = "0045 RELATED TO CAMERA ADJUST TO PLAYER";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);	
		}
		else if(cmd==	0x0046){
			cmdName = "0046 ";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0047){
			cmdName = "0047 ";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0048){
			cmdName = "0048 LOAD MAP";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}		
		else if(cmd==	0x0049){
			cmdName = "0049 ";
			cmdComment = form("%s %s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16),ltoa(Word(ea+6),16));
			cmdLength = 8;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
			MakeWord(ea+6);	
		}
		else if(cmd==	0x004A){
			cmdName = "004A FADE IN FROM BLACK HALF";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(cmd==	0x004B){
			cmdName = "004B FADE OUT TO BLACK HALF";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
		}
		else if(cmd==	0x0050){
			cmdName = "0050 SET ENTITY SIZE";
			cmdComment = form("%s %s %s ",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0051){
			cmdName = "0051 ";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);		
		}
		else if(cmd==	0x0052){
			cmdName = "0052 RELATED TO TWO ENTITIES";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0053){
			cmdName = "0053 ";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);		
		}
		else if(cmd==	0x0054){
			cmdName = "0054 ";
			cmdComment = form("%s %s %s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);			
			MakeWord(ea+4);	
		}
		else if(cmd==	0x0055){
			cmdName = "0055 RESET FORCE BATTLE STATS";
			cmdComment = form("%s",cmdName);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
		}
		else if(cmd==	0x0056){
			cmdName = "0056 SOMETHING WITH AN ENTITY";
			cmdComment = form("%s %s",cmdName,ltoa(Word(ea+2),16));
			cmdLength = 4;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);		
		}																																	
		else{
			cmdComment = form("Unkown command : %s",ltoa(Word(ea),16));
			Message(form("\n%a: %s",ea,cmdComment));
			MakeRptCmt(ea,cmdComment);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		
		MakeRptCmt(ea,cmdComment);
		//Message(form("\n%a : %s",ea,cmdComment));
		

		
		//action = AskYN(1,"Continue ?");
	
		ea = ea + cmdLength;
	}



	//Message(form("\n%a : END OF CS PARSING",ea));

}


static getSoundName(cmd){
	auto id,enumSize,constant,j,constId,output;
	id = GetEnum("Music");
	enumSize = GetEnumSize(id);
	constant = GetFirstConst(id,-1);	
	while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				if(constant==cmd){
					return GetConstName(constId);
				}
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
	}
	id = GetEnum("Sfx");
	enumSize = GetEnumSize(id);
	constant = GetFirstConst(id,-1);	
	while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				if(constant==cmd){
					return GetConstName(constId);
				}
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
	}
}

static parseCSC19Data(addr){
	auto length;
	length = 2;
	while(Word(addr)<0x8000){
		MakeByte(addr);
		MakeByte(addr+1);
		addr = addr + 2;
		length = length + 2;
	}
	MakeWord(addr);
	return length;
}

static parseCSC42Struct(addr){
	MakeWord(addr);
	MakeWord(addr+2);
	MakeWord(addr+4);
	addr = addr + 6;
	while(Word(addr)!=0xFFFF){
		MakeByte(addr);
		MakeByte(addr+1);
		MakeByte(addr+2);
		MakeByte(addr+3);
		MakeDword(addr+4);		
		OpOff(addr+4,0,0);
		addr = addr + 8;
	}
	MakeWord(addr);
}


/* 
 *	Makes sure byte at addr is
 *	clean for new formatting
 */
static undefineByte(addr){
		auto from;
		from = DfirstB(addr);
		while(from!=BADADDR){
			//Message(form("Removed DATA XRef at addr %a, from %a\n",addr, from));
      del_dref(from,addr);
      from=DnextB(addr,from);
		}		
		from = RfirstB(addr);
		while(from!=BADADDR){
			//Message(form("Removed Code XRref at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
		}				
		MakeUnkn(addr,DOUNK_DELNAMES);
		MakeNameEx(addr,"",0);
		SetManualInsn(addr,"");
}

/**********************************************
 *																						*
 *																						*
 *			      ENTITY ACTSCRIPTS								*
 *																						*
 *																						*
 **********************************************/


static parseEAS(start,end){

	auto ea,cmdLength,cmdName,cmdComment,tab,action;
	
	cmdLength = 2;
	ea = start;
	action = 1;
	
	if(end==0xFFFFFF){
		tab = "  ";
	}
	
	//Message(form("\n%a : START OF EAS PARSING",ea));

	while(ea<end && Word(ea)!=0x8080 && action==1){

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
			makeRelativeOffsetFromCmd(ea+2);			
		}
		else if(Word(ea)==0x0031){
			cmdName = "0031 BRANCH IF SET FLAG";
			cmdComment = form("%s %s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);			
			MakeWord(ea+2);		
			makeRelativeOffsetFromCmd(ea+2);	
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0032){
			cmdName = "0032 BRANCH IF CLEARED FLAG";
			cmdComment = form("%s %s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+2),16),ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);
			MakeWord(ea+2);				
			makeRelativeOffsetFromCmd(ea+2);					
			MakeWord(ea+4);				
		}
		else if(Word(ea)==0x0033){
			cmdName = "0033 RANDOM BRANCH";
			cmdComment = form("%s TO CURRENT ADDR. + $%s",cmdName,ltoa(Word(ea+4),16));
			cmdLength = 6;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);		
			MakeWord(ea+2);			
			makeRelativeOffsetFromCmd(ea+2);				
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
			Message(form("\n%s%s",tab,cmdComment));
			MakeRptCmt(ea,cmdComment);
			cmdLength = 2;
			MakeUnknown(ea,cmdLength,DOUNK_DELNAMES);
			MakeWord(ea);	
		}
		
		MakeRptCmt(ea,form("%s%s",tab,cmdComment));
		//Message(form("\n%a : %s",ea,cmdComment));
		ea = ea + cmdLength;

		
		//action = AskYN(1,"Continue ?");
	
	
		
	}

	//Message(form("\n%a : END OF EAS PARSING",ea));
	
	return ea;

}


static makeRelativeOffsetFromCmd(addr){

		if(Word(addr) > 0x8000) {
			OpOffEx(addr, -1, REF_OFF32, addr - 2 + Word(addr) - 0x10000, addr-2, 0x10000);
		}
		else{
			OpOffEx(addr, -1, REF_OFF32, -1, addr-2, 0);
		}

}