

#include <idc.idc>


static main(void){

		parseAll();

}

static parseAll(){

	Message("\nPARSING...\n");
	Message(" Music bank ...");
	createEnums();	
	parseMusicBank();	
	Message("\n DONE.\n");		
	Message("END OF PARSING.\n");	

}

static createEnums(){
	createNotes();
}

static createNotes(){
	auto enumid,octave,code;
	enumid = AddEnum(-1,"NOTES",0);
	for(octave=0;octave<9;octave++){
		code=AddConstEx(enumid,form("C%d",octave),12*octave+0,-1);
		AddConstEx(enumid,form("Cs%d",octave),12*octave+1,-1);
		AddConstEx(enumid,form("D%d",octave),12*octave+2,-1);
		AddConstEx(enumid,form("Ds%d",octave),12*octave+3,-1);
		AddConstEx(enumid,form("E%d",octave),12*octave+4,-1);
		AddConstEx(enumid,form("F%d",octave),12*octave+5,-1);
		AddConstEx(enumid,form("Fs%d",octave),12*octave+6,-1);
		AddConstEx(enumid,form("G%d",octave),12*octave+7,-1);
		AddConstEx(enumid,form("Gs%d",octave),12*octave+8,-1);
		AddConstEx(enumid,form("A%d",octave),12*octave+9,-1);
		AddConstEx(enumid,form("As%d",octave),12*octave+10,-1);
		AddConstEx(enumid,form("B%d",octave),12*octave+11,-1);
	}
}

static parseMusicBank(){
	auto i;
	auto addr,target;
	undefineByte(0);
	for(i=1;i<=32;i++){
		addr = 0x8000+(i-1)*2;
		MakeWord(addr);
		target = Word(addr);
		MakeNameEx(target,form("Music_%s",ltoa(i,10)),0);
		OpOff(addr,0,0);
		Message(form("\n  Music %d at 0x%s...",i,ltoa(target,16)));	
		parseMusic(target,target+0x1000,i);
		Message(" DONE.\n");
		/*if(AskYN(1,"Next Music ?")!=1){
			break;
		}*/	
	}	
	MakeArray(0xFE37,457);		
	SetManualInsn(0xFE37,"align 8000h");
}


static parseMusic(start,end,index){

	auto ea,channelsPointerTable,channel,channelStart,ymChannel,psgChannel,addr,target,cmd,cmdLength,cmdName,cmdComment,i,action;
	auto textIndex,flag;
	auto dac;
	
	cmdLength = 1;
	ea = start;
	
	action = 1;
	
	Message(form("\Music starting from 0x%s ...",ltoa(ea,16)));
	
	/*if(end!=-1&&(end-start)<0x1000){
		for(i=start;i<end;i++){
			MakeRptCmt(i,"");
		}	
	}*/
	
	MakeByte(ea);
	SetManualInsn(ea,"");
	MakeByte(ea+1);
	SetManualInsn(ea+1,"");
	MakeByte(ea+2);
	SetManualInsn(ea+2,"");
	MakeByte(ea+3);
	SetManualInsn(ea+3,"");
	
	dac = Byte(ea+1);
	
	ea = ea+4;
	
	channelsPointerTable = ea;
	
	for(channel=0;channel<10;channel++){
		addr = ea+channel*2;
		target = Word(addr);
		MakeUnknown(addr,2,DOUNK_SIMPLE);
		MakeWord(addr);
		SetManualInsn(addr,"");
		MakeNameEx(target,form("Music_%d_Channel_%d",index,channel),0);
		OpOff(addr,0,0);
		Message(form("\n  Music %d channel %d at 0x%s",index,channel,ltoa(target,16)));
	}
	
	for(ymChannel=0;ymChannel<6;ymChannel++){
		channelStart = Word(channelsPointerTable+ymChannel*2);
		ea = channelStart;
		while(action==1){
			//Jump(ea);
			cmd = Byte(ea);
			if(strstr(GetTrueName(ea),form("Music_%d_Channel_%d",index,ymChannel))==-1 && strstr(GetTrueName(ea),"Music")!=-1){
				break;
			}
			if(cmd==0xFF){
				cmdLength = 3;
				if(Word(ea+1)==0){
					MakeData(ea,FF_BYTE,cmdLength,1);
					SetManualInsn(ea,"channel_end");
					break;
				}else{
					if(Byte(ea+2)==0){
						MakeData(ea,FF_BYTE,cmdLength,1);
						SetManualInsn(ea,form("newSoundCommand 0%sh",ltoa(Byte(ea+1),16)));
						Jump(ea);
						AskYN(1,"Found a newSoundCommand command !");
						break;						
					}else{
						MakeData(ea,FF_BYTE,cmdLength,1);			
						if(GetTrueName(Word(ea+1))==""){
							MakeNameEx(Word(ea+1),form("jump_%s",ltoa(Word(ea+1),16)),0);
						}
						SetManualInsn(ea,form("jump $%s",GetTrueName(Word(ea+1))));
						Jump(ea);
						AskYN(1,"Found a jump command !");
						break;
					}
				}
			}else if(cmd==0xFE){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  inst %s",ltoa(Byte(ea+1),10)));
			}else if(cmd==0xFD){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  vol 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xFC){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				if(Byte(ea+1)<0x80){
					SetManualInsn(ea,form("  setRelease 0%sh",ltoa(Byte(ea+1),16)));
				}else if(Byte(ea+1)==0x80){
					SetManualInsn(ea,"  sustain");
				}else if(Byte(ea+1)<0xFF){
					SetManualInsn(ea,form("  setSlide 0%sh",ltoa(Byte(ea+1)-0x80,16)));
				}else {
					SetManualInsn(ea,"  noSlide");
				}
			}else if(cmd==0xFB){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  vibrato 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xFA){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  stereo 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xF9){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  shifting 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xF8){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				if(Byte(ea+1)==0x00){
					SetManualInsn(ea,"mainLoopStart");
				}else if(Byte(ea+1)==0xA1){
					SetManualInsn(ea,"mainLoopEnd");
				}else if(Byte(ea+1)==0x20){
					SetManualInsn(ea,"repeatStart");
				}else if(Byte(ea+1)==0xA0){
					SetManualInsn(ea,"repeatEnd");
				}else if(Byte(ea+1)==0x40){
					SetManualInsn(ea,"repeatSection1Start");
				}else if(Byte(ea+1)==0x60){
					SetManualInsn(ea,"repeatSection2Start");
				}else if(Byte(ea+1)==0x80){
					SetManualInsn(ea,"repeatSection3Start");
				}else if(Byte(ea+1)==0xE0){
					SetManualInsn(ea,"countedLoopEnd");
				}else{
					SetManualInsn(ea,form("countedLoopStart %s",ltoa(Byte(ea+1)-0xC0,10)));
				}				
			}else if(cmd==0xF0){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("        waitL %s",ltoa(Byte(ea+1),10)));
			}else if(cmd==0x70){
				cmdLength = 1;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,"        wait");
			}else if(cmd>=0x80){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				if(ymChannel==5 && dac==0){
					SetManualInsn(ea,form("        sampleL %s,%s",ltoa(Byte(ea)-0x80,10),ltoa(Byte(ea+1),10)));
				}else{
					SetManualInsn(ea,form("        noteL %s,%s",getYmNote(Byte(ea)-0x80),ltoa(Byte(ea+1),10)));
				}
			}else {
				cmdLength = 1;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				if(ymChannel==5 && dac==0){
					SetManualInsn(ea,form("        sample  %s",ltoa(Byte(ea),10)));
				}else{
					SetManualInsn(ea,form("        note  %s",getYmNote(Byte(ea))));
				}
			}
		
		
		
			//action = AskYN(1,"Continue ?");
			ea = ea + cmdLength;
		}
	}	
	
	for(psgChannel=0;psgChannel<4;psgChannel++){
		channelStart = Word(channelsPointerTable+6*2+psgChannel*2);
		ea = channelStart;
		Message(form("\nChannel 0x%s",ltoa(channelStart,16)));
		while(action==1){
			//Jump(ea);
			cmd = Byte(ea);
			if(strstr(GetTrueName(ea),form("Music_%d_Channel_%d",index,psgChannel+6))==-1 && strstr(GetTrueName(ea),"Music")!=-1){
				break;
			}
			if(cmd==0xFF){
				cmdLength = 3;
				if(Word(ea+1)==0){
					MakeData(ea,FF_BYTE,cmdLength,1);
					SetManualInsn(ea,"channel_end");
					break;
				}else{
					if(Byte(ea+2)==0){
						MakeData(ea,FF_BYTE,cmdLength,1);
						SetManualInsn(ea,form("newSoundCommand 0%sh",ltoa(Byte(ea+1),16)));
						Jump(ea);
						AskYN(1,"Found a newSoundCommand command !");
						break;						
					}else{
						MakeData(ea,FF_BYTE,cmdLength,1);			
						if(GetTrueName(Word(ea+1))==""){
							MakeNameEx(Word(ea+1),form("jump_%s",ltoa(Word(ea+1),16)),0);
						}
						SetManualInsn(ea,form("jump $%s",GetTrueName(Word(ea+1))));
						Jump(ea);
						AskYN(1,"Found a jump command !");
						break;
					}
				}
			}else if(cmd==0xFD){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  psgInst 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xFC){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  setRelease 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xFB){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  vibrato 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xFA){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  ymTimer 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xF9){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("  shifting 0%sh",ltoa(Byte(ea+1),16)));
			}else if(cmd==0xF8){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				if(Byte(ea+1)==0x00){
					SetManualInsn(ea,"mainLoopStart");
				}else if(Byte(ea+1)==0xA1){
					SetManualInsn(ea,"mainLoopEnd");
				}else if(Byte(ea+1)==0x20){
					SetManualInsn(ea,"repeatStart");
				}else if(Byte(ea+1)==0xA0){
					SetManualInsn(ea,"repeatEnd");
				}else if(Byte(ea+1)==0x40){
					SetManualInsn(ea,"repeatSection1Start");
				}else if(Byte(ea+1)==0x60){
					SetManualInsn(ea,"repeatSection2Start");
				}else if(Byte(ea+1)==0x80){
					SetManualInsn(ea,"repeatSection3Start");
				}else if(Byte(ea+1)==0xE0){
					SetManualInsn(ea,"countedLoopEnd");
				}else{
					SetManualInsn(ea,form("countedLoopStart %s",ltoa(Byte(ea+1)-0xC0,10)));
				}	
			}else if(cmd==0xF0){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("        waitL    %s",ltoa(Byte(ea+1),10)));
			}else if(cmd==0x70){
				cmdLength = 1;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,"        wait");
			}else if(cmd>=0x80){
				cmdLength = 2;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("        psgNoteL %s,%s",getPsgNote(Byte(ea)-0x80),ltoa(Byte(ea+1),10)));
			}else {
				cmdLength = 1;
				MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
				MakeData(ea,FF_BYTE,cmdLength,1);
				SetManualInsn(ea,form("        psgNote  %s",getPsgNote(Byte(ea))));
			}
		
		
		
			//action = AskYN(1,"Continue ?");
			ea = ea + cmdLength;
		}
	}

	//Message(form("\n%a : END OF MUSIC PARSING",ea));

}

static getYmNote(cmd){
	auto id,enumSize,constant,j,constId,output;
	id = GetEnum("NOTES");
	enumSize = GetEnumSize(id);
	constant = GetFirstConst(id,-1);
	//Message(form("Getting Ym Note %d ...",cmd));	
	while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				if(constant==cmd+24){
					//Message(form(" Found Ym Note %s\n",GetConstName(constId)));
					return GetConstName(constId);
				}
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
	}
	Message(form("Ym Note %d not found !",cmd));
	return form("%s",ltoa(cmd,10));
}

static getPsgNote(cmd){
	auto id,enumSize,constant,j,constId,output;
	id = GetEnum("NOTES");
	enumSize = GetEnumSize(id);
	constant = GetFirstConst(id,-1);
	//Message(form("Getting Psg Note %d ...",cmd));	
	while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				if(constant==cmd){
					//Message(form(" Found Psg Note %s\n",GetConstName(constId)));
					return GetConstName(constId);
				}
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
	}
	Message(form("Psg Note %d not found !",cmd));
	return form("%s",ltoa(cmd,10));
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
		MakeUnkn(addr,DOUNK_SIMPLE);
		MakeNameEx(addr,"",0);
		SetManualInsn(addr,"");
}



static makeRelativeOffsetFromCmd(addr){

	auto type, target, base;
	
	base = addr-2;
	target = base + (Word(addr)+0xFFFF0000);

		if(Word(addr) > 0x8000) {
			OpOffEx(addr, -1, REF_LOW16, target, base, 0);
		}
		else{
			OpOffEx(addr, -1, REF_OFF32, -1, addr-2, 0);
		}

}

