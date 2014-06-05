
/*
 *	Attempt at producing ASM file from IDC script 
 *	instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

	Message("PRODUCING ASM...\n");

	produceMacros();
	produceEnums();
	produceConst();
	produceMain();
	
	Message("\nEND OF ASM PRODUCTION.\n");

}

static produceMacros(){
	auto file;
	Message("\nWriting Macros to sf2macros.asm ...");	
	file = fopen("sf2macros.asm","w");
	writestr(file,"; ---------------------------------------------------------------------------\n");
	writestr(file,"; Align and pad\n");
	writestr(file,"; input: length to align to, value to use as padding (default is $FF)\n");
	writestr(file,"; ---------------------------------------------------------------------------\n");
	writestr(file,"\n");
	writestr(file,"align:	macro\n");
	writestr(file,"	if (narg=1)\n");
	writestr(file,"	dcb.b \\1-(*%\\1),$FF\n");
	writestr(file,"	else\n");
	writestr(file,"	dcb.b \\1-(*%\\1),\\2\n");
	writestr(file,"	endc\n");
	writestr(file,"	endm\n");
	writestr(file,"\n");
	fclose(file);	
	Message("DONE.");	
}

static produceEnums(){
	auto i,j,enumQty,id,enumName,enumSize,constant,constId,output,file;
	file = fopen("sf2enums.asm","w");
	Message("\nWriting Enums to sf2enums.asm ...");
	enumQty = GetEnumQty();
	for(i=0;i<enumQty;i++){
		id = GetnEnum(i);
		enumName = GetEnumName(id);
		//Message("\n\n; ---------------------------------------------------------------------------\n");
		writestr(file,"\n\n; ---------------------------------------------------------------------------\n");
		//Message(form("\n; enum %s",enumName));
		writestr(file,form("\n; enum %s",enumName));
		enumSize = GetEnumSize(id);
		constant = GetFirstConst(id,-1);
		while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				output = form("\n%s: equ $%s",GetConstName(constId),ltoa(constant,16));
				//Message(output);
				writestr(file,output);
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
		}
	}
	fclose(file);
	Message("DONE.");
}


static produceConst(void) {
	auto seg,end,ea,segName,name,file;
	Message("\nWriting offset constants to sf2const.asm ...");
	file = fopen("sf2const.asm","w");
	writestr(file,"; SF2CONST.ASM INCLUDED AT START OF SF2.ASM\n\n");
	seg = FirstSeg();
	seg = NextSeg(seg);
	while(seg != BADADDR){
		end = SegEnd(seg);
		segName = SegName(seg);
		writestr(file,form("; START OF SEGMENT %s OFFSETS FROM %a TO %a\n",segName, seg, end));
		ea = seg;
		while(ea<end){
			name = GetTrueName(ea);
			if(name!=""){
				writestr(file,form("%s: equ $%s\n",name,ltoa(ea,16)));
			}
			ea = ea + ItemSize(ea);
		}
		writestr(file,form("; END OF SEGMENT %s OFFSETS FROM %a TO %a\n\n",segName, seg, end));
		seg = NextSeg(seg);
	}
	fclose(file);
	Message("DONE.\n");
}


static produceMain(){

	auto seg,end,ea,itemSize,action,currentLine,previousLine,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	Message("Writing main assembly file to sf2.asm ...");	
	action = 1;
	file = fopen("sf2.asm","w");
	writeHeader(file);

	produceSection(file,"01",0x0,			0x8000,			90,		"Technical Layer, Low Level Game Engine, Map/Exploration Engine, Entity Script Commands, Witch Functions");
	produceSection(file,"02",0x8000,	0x10000,		121,	"Character Stats Engine, Item Effects Engine");
	produceSection(file,"03",0x10000,	0x18000,		38,		"Menu Engine");
	produceSection(file,"04",0x18000,	0x20000,		532,	"BattleScene Engine");
	produceSection(file,"05",0x20000,	0x28000,		626,	"Battle Engine, Special Sprites, Shop/Church/Blacksmith/Caravan engine");
	produceSection(file,"06",0x28000,	0x44000,		6681,	"Fonts, Menu Tiles, Text Decoding Functions, SEGA Logo, Game Staff, Conf/Debug modes, End Kiss Sequence, Script Huffman Trees, Scriptbanks");
	produceSpecificSectionSeven(file,"07",0x44000,	0x64000,		2931,	"Entity ActScripts, CutScene Scripts, Battle CutScenes, Intro cutscene, End cutscene, Map Setups");
	produceSection(file,"08",0x64000,	0xC8000,		953 ,	"Map Tiles, Map Palettes, Map Data");
	produceSection(file,"09",0xC8000,	0x100000,		1315,"Entity Sprites");
	produceSection(file,"10",0x100000,0x130000,		432,	"Backgrounds, invocation sprites, title screen");
	produceSection(file,"11",0x130000,0x180000,		429,	"Enemy battle sprites");
	produceSection(file,"12",0x180000,0x1AC000,		871,	"Ally battle sprites, status anim tiles, battlescene transition tiles, bolt graphics, ally and enemy animations");
	produceSection(file,"13",0x1AC000,0x1B8000,		133,	"Battle setup functions, battle terrains, battle entity setups, end kiss graphics");
	produceSection(file,"14",0x1B8000,0x1C8000,		474,	"Battlescene grounds, weapons, spell graphics, witch screens");
	produceSection(file,"15",0x1C8000,0x1D8000,		1467,	"Portraits");
	produceSection(file,"16",0x1D8000,0x1E0000,		126,	"Icons");
	produceSection(file,"17",0x1E0000,0x1F0000,		462,	"PCM Banks, YM Instruments, sound driver, char stats, witch screens");
	produceSection(file,"18",0x1F0000,0x200000,		1038,	"Music banks 1 and 0");

	fclose(file);
	Message("\nDONE.");	
}

static produceSection(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("sf2-%s.asm",sectionName);
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("   include \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(fileName,"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("\n; FREE SPACE : %d bytes.\n\n\n",fs));	
	ea = start;
	while(ea<end){
		itemSize = ItemSize(ea);
		if(GetFunctionAttr(ea,FUNCATTR_START)==ea){	
			writeFunctionHeader(file,ea);
		}
		else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){	
			writeFChunkHeader(file,ea);
		}		
		writeItem(file,ea);
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea);
		}		
		else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFChunkFooter(file,ea);
		}				
		ea = ea + itemSize;
	}
	fclose(file);
	Message("DONE.\n");	

}

static produceSpecificSectionSeven(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("sf2-%s.asm",sectionName);
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("   include \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(fileName,"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("\n; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x44000,0x448C4);
	produceAsmScript(file,"battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies");
	produceAsmScript(file,"eas_battleneutralentities",0x4497A,0x449C6,"Entity actscripts for battle entities which are not force members or enemies");
	produceAsmSection(file,0x449C6,0x44DE2);
	produceAsmScript(file,"eas_main",0x44DE2,0x45202,"Main entity actscripts");
	produceAsmSection(file,0x45202,0x45284);
	produceAsmScript(file,"ms_caravanin",0x45284,0x45322,"Mapscript for getting into Caravan ?");
	produceAsmSection(file,0x45322,0x45348);
	produceAsmScript(file,"ms_caravanout",0x45348,0x453C6,"Mapscript for getting out of Caravan ?");
	produceAsmSection(file,0x453C6,0x453F2);
	produceAsmScript(file,"ms_raftin",0x453F2,0x45440,"Mapscript for getting into Raft ?");
	produceAsmSection(file,0x45440,0x45470);
	produceAsmScript(file,"ms_raftout",0x45470,0x454AC,"Mapscript for getting out of Raft ?");
	produceAsmSection(file,0x454AC,0x45546);
	produceAsmScript(file,"ms_shrinkin",0x45546,0x455AC,"Mapscript for shrinking in ?");
	produceAsmSection(file,0x455AC,0x455D2);
	produceAsmScript(file,"ms_growout",0x455D2,0x45634,"Mapscript for growing out ?");
	produceAsmSection(file,0x45634,0x45E44);
	produceAsmScript(file,"eas_actions",0x45E44,0x46506,"Entity scripts for cutscene actions");
	produceAsmSection(file,0x46506,0x47A88);
	produceAsmScript(file,"battlecutscenes\\cs_beforebattle",0x47A88,0x47AE8,"Before battle cutscenes");
	produceAsmSection(file,0x47AE8,0x47B2C);
	produceAsmScript(file,"battlecutscenes\\cs_battlestart",0x47B2C,0x47B8C,"Battle start cutscenes");
	produceAsmSection(file,0x47B8C,0x47BE8);
	produceAsmScript(file,"battlecutscenes\\cs_enemydefeated",0x47BE8,0x47C48,"Enemy defeated cutscenes");
	produceAsmSection(file,0x47C48,0x47CF4);
	produceAsmScript(file,"battlecutscenes\\cs_afterbattle",0x47CF4,0x47D54,"After battle cutscenes");
	produceAsmSection(file,0x47D54,0x47EC8);	
	produceAsmScript(file,"battlecutscenes\\cs_regionactivated",0x47EC8,0x47EEA,"Region-activated cutscenes");
	produceAsmSection(file,0x47EEA,0x47EF8);
	produceAsmScript(file,"cs_introendroutine",0x47EF8,0x47F7E,"Subroutine launching intro and end cutscenes");
	produceAsmScript(file,"cs_intro1",0x47F7E,0x48380,"Intro cutscene 1");
	produceAsmScript(file,"cs_intro2",0x48380,0x48540,"Intro cutscene 2");
	produceAsmScript(file,"cs_intro3",0x48540,0x48A78,"Intro cutscene 3");
	produceAsmScript(file,"cs_intro4",0x48A78,0x48FE2,"Intro cutscene 4");
	produceAsmSection(file,0x48FE2,0x49058);
	produceAsmScript(file,"cs_end",0x49058,0x493EC,"End cutscene");
	produceAsmSection(file,0x493EC,0x494BC);

	produceAsmScript(file,"battlecutscenes\\battle01\\bbcs",0x494BC,0x496DC,"Cutscene before battle 1");
	produceAsmScript(file,"battlecutscenes\\battle01\\abcs",0x496DC,0x4980E,"Cutscene after battle 1");
	produceAsmScript(file,"battlecutscenes\\battle03\\bbcs",0x4980E,0x4981E,"Cutscene before battle 3");
	produceAsmScript(file,"battlecutscenes\\battle04\\bbcs",0x4981E,0x498EE,"Cutscene before battle 4");
	produceAsmScript(file,"battlecutscenes\\battle04\\abcs",0x498EE,0x49AB2,"Cutscene after battle 4");
	produceAsmScript(file,"battlecutscenes\\battle05\\edcs",0x49AB2,0x49B48,"Enemy defeated cutscene for battle 5");
	produceAsmScript(file,"battlecutscenes\\battle05\\abcs",0x49B48,0x49BCA,"Cutscene after battle 5");
	produceAsmScript(file,"battlecutscenes\\battle06\\bbcs",0x49BCA,0x49CE2,"Cutscene before battle 6");
	produceAsmScript(file,"battlecutscenes\\battle07\\bbcs",0x49CE2,0x49F7E,"Cutscene before battle 7");
	produceAsmScript(file,"battlecutscenes\\battle07\\abcs",0x49F7E,0x4A952,"Cutscene after battle 7");
	produceAsmScript(file,"battlecutscenes\\battle08\\bbcs",0x4A952,0x4AA74,"Cutscene before battle 8");
	produceAsmScript(file,"battlecutscenes\\battle08\\abcs",0x4AA74,0x4ABFE,"Cutscene after battle 8");
	produceAsmScript(file,"battlecutscenes\\battle11\\bbcs",0x4ABFE,0x4ACC8,"Cutscene before battle 11");
	produceAsmScript(file,"battlecutscenes\\battle12\\edcs",0x4ACC8,0x4ACEC,"Enemy defeated cutscene for battle 12");
	produceAsmScript(file,"battlecutscenes\\battle12\\abcs",0x4ACEC,0x4ACF8,"Cutscene after battle 12");
	produceAsmScript(file,"battlecutscenes\\battle13\\abcs",0x4ACF8,0x4ADA6,"Cutscene after battle 13");
	produceAsmScript(file,"battlecutscenes\\battle15\\bbcs",0x4ADA6,0x4AE72,"Cutscene before battle 15");
	produceAsmScript(file,"battlecutscenes\\battle15\\abcs",0x4AE72,0x4AFBE,"Cutscene after battle 15");
	produceAsmScript(file,"battlecutscenes\\battle16\\bbcs",0x4AFBE,0x4B1BC,"Cutscene before battle 16");
	produceAsmScript(file,"battlecutscenes\\battle16\\abcs",0x4B1BC,0x4B1D8,"Cutscene after battle 16");
	produceAsmScript(file,"battlecutscenes\\battle18\\bbcs",0x4B1D8,0x4B2F2,"Cutscene before battle 18");
	produceAsmScript(file,"battlecutscenes\\battle18\\abcs",0x4B2F2,0x4B6CE,"Cutscene after battle 18");
	produceAsmScript(file,"battlecutscenes\\battle20\\abcs",0x4B6CE,0x4B790,"Cutscene after battle 20");
	produceAsmScript(file,"battlecutscenes\\battle21\\bbcs",0x4B790,0x4B88C,"Cutscene before battle 21");
	produceAsmScript(file,"battlecutscenes\\battle21\\abcs",0x4B88C,0x4B958,"Cutscene after battle 21");
	produceAsmScript(file,"battlecutscenes\\battle26\\bbcs",0x4B958,0x4BCAA,"Cutscene before battle 26");
	produceAsmScript(file,"battlecutscenes\\battle26\\abcs",0x4BCAA,0x4BE6A,"Cutscene after battle 26");
	produceAsmScript(file,"battlecutscenes\\battle27\\bscs",0x4BE6A,0x4BE8C,"Start cutscene for battle 27");
	produceAsmScript(file,"battlecutscenes\\battle28\\bbcs",0x4BE8C,0x4C07C,"Cutscene before battle 28");
	produceAsmScript(file,"battlecutscenes\\battle28\\abcs",0x4C07C,0x4C3DC,"Cutscene after battle 28");
	produceAsmScript(file,"battlecutscenes\\battle29\\bbcs",0x4C3DC,0x4C5E6,"Cutscene before battle 29");
	produceAsmScript(file,"battlecutscenes\\battle30\\bbcs",0x4C5E6,0x4C6A8,"Cutscene before battle 30");
	produceAsmScript(file,"battlecutscenes\\battle30\\abcs",0x4C6A8,0x4C994,"Cutscene after battle 30");
	produceAsmScript(file,"battlecutscenes\\battle31\\bbcs",0x4C994,0x4CBE2,"Cutscene before battle 31");
	produceAsmScript(file,"battlecutscenes\\battle32\\bbcs",0x4CBE2,0x4CD10,"Cutscene before battle 32");
	produceAsmScript(file,"battlecutscenes\\battle32\\rbcs_1",0x4CD10,0x4CDB4,"Region-activated cutscene for battle 32");
	produceAsmScript(file,"battlecutscenes\\battle32\\abcs",0x4CDB4,0x4CF0C,"Cutscene after battle 32");
	produceAsmScript(file,"battlecutscenes\\battle33\\bbcs",0x4CF0C,0x4D09A,"Cutscene before battle 33");
	produceAsmScript(file,"battlecutscenes\\battle33\\abcs",0x4D09A,0x4D342,"Cutscene after battle 33");
	produceAsmScript(file,"battlecutscenes\\battle34\\bbcs",0x4D342,0x4D4B6,"Cutscene before battle 34");
	produceAsmScript(file,"battlecutscenes\\battle34\\abcs",0x4D4B6,0x4D6CE,"Cutscene after battle 34");
	produceAsmScript(file,"battlecutscenes\\battle35\\bbcs",0x4D6CE,0x4D88A,"Cutscene before battle 35");
	produceAsmScript(file,"battlecutscenes\\battle36\\bbcs",0x4D88A,0x4D9A4,"Cutscene before battle 36");
	produceAsmScript(file,"battlecutscenes\\battle36\\abcs",0x4D9A4,0x4DA66,"Cutscene after battle 36");
	produceAsmScript(file,"battlecutscenes\\battle37\\bbcs",0x4DA66,0x4DB94,"Cutscene before battle 37");
	produceAsmScript(file,"battlecutscenes\\battle37\\abcs",0x4DB94,0x4DDA4,"Cutscene after battle 37");
	produceAsmScript(file,"battlecutscenes\\battle38\\bbcs",0x4DDA4,0x4DE8C,"Cutscene before battle 38");
	produceAsmScript(file,"battlecutscenes\\battle38\\abcs",0x4DE8C,0x4E3D2,"Cutscene after battle 38");
	produceAsmScript(file,"battlecutscenes\\battle39\\bbcs",0x4E3D2,0x4E4DC,"Cutscene before battle 39");
	produceAsmScript(file,"battlecutscenes\\battle40\\bbcs",0x4E4DC,0x4E8A8,"Cutscene before battle 40");
	produceAsmScript(file,"battlecutscenes\\battle40\\rbcs_1",0x4E8A8,0x4E9B2,"Region-activated cutscene 1 for battle 40");
	produceAsmScript(file,"battlecutscenes\\battle40\\rbcs_2",0x4E9B2,0x4EA94,"Region-activated cutscene 2 for battle 40");
	produceAsmScript(file,"battlecutscenes\\battle40\\abcs",0x4EA94,0x4ED0E,"Cutscene after battle 40");
	produceAsmScript(file,"battlecutscenes\\battle41\\bbcs",0x4ED0E,0x4ED8E,"Cutscene before battle 41");
	produceAsmScript(file,"battlecutscenes\\battle42\\bbcs",0x4ED8E,0x4EF04,"Cutscene before battle 42");
	produceAsmScript(file,"battlecutscenes\\battle42\\abcs",0x4EF04,0x4F358,"Cutscene after battle 42");
	produceAsmScript(file,"battlecutscenes\\battle43\\edcs",0x4F358,0x4F35E,"Enemy defeated cutscene for battle 43");
	produceAsmScript(file,"battlecutscenes\\battle43\\abcs",0x4F35E,0x4F47A,"Cutscene after battle 43");
	produceAsmScript(file,"battlecutscenes\\battle00\\abcs",0x4F47A,0x4F48A,"Cutscene after battle 0");
	
	produceAsmSection(file,0x4F48A,0x4F6E2);
	
	produceAsmScript(file,"mapsetups\\mapsetupstable",0x4F6E2,0x4FA70,"Map setups table");
	produceAsmScript(file,"mapsetups\\mapsetups",0x4FA70,0x6348C,"Map setups to be split later");
	produceAsmSection(file,0x6348C,0x64000);

	fclose(file);
	Message("DONE.\n");	
}

static produceAsmScript(mainFile,sectionName,start,end,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("asmscripts\\%s.asm",sectionName);
	Message(form("Writing assembly script section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("   include \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(fileName,"w");
	writestr(file,form("\n; SCRIPT SECTION %s :\n; %s\n",sectionName,sectionComment));	
	produceAsmSection(file,start,end);
	fclose(file);
	Message("DONE.\n");	

}

static produceAsmSection(file,start,end){
	auto ea,itemSize;
	ea = start;
	while(ea<end){
		itemSize = ItemSize(ea);
		if(GetFunctionAttr(ea,FUNCATTR_START)==ea){	
			writeFunctionHeader(file,ea);
		}
		else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){	
			writeFChunkHeader(file,ea);
		}		
		writeItem(file,ea);
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea);
		}		
		else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFChunkFooter(file,ea);
		}				
		ea = ea + itemSize;
	}
}

static writeHeader(file){
	writestr(file,"\n");
	writestr(file,"   include \"sf2macros.asm\"\n");	
	writestr(file,"   include \"sf2enums.asm\"\n");
	writestr(file,"   include \"sf2const.asm\"\n");
	writestr(file,"\n");
}

static writeFooter(file){
	writestr(file,"		END");
}

static writeFunctionHeader(file, ea){
	auto funcCmt;
	writestr(file,"\n; =============== S U B R O U T I N E =======================================\n\n");
	funcCmt = GetFunctionCmt(ea,0);
	if(funcCmt!=""){
		writestr(file,form("; %s\n\n",funcCmt));
	}
	else{
		funcCmt = GetFunctionCmt(ea,1);
		if(funcCmt!=""){
			funcCmt = formatFuncRptCmt(funcCmt);
			writestr(file,form("; %s\n\n",funcCmt));
		}
	}
	undefineLocalVars(file,ea);
}

static undefineLocalVars(file,ea){
	auto id, i, firstM, lastM, mName, mSize, mFlag;
	id = GetFrame(ea);
	firstM = GetFirstMember(id);
	lastM = GetLastMember(id);
	i=firstM;
	while(i<=lastM){
		if(i!=-1&&GetMemberName(id,i)!=""&&GetMemberName(id,i)!=" r"&&GetMemberName(id,i)!=" s"){
			mName = GetMemberName(id,i); // Get the name
			mSize = GetMemberSize(id, i); // Get the size (in byte)
			mFlag = GetMemberFlag(id, i); // Get the flag
			Message("\n%a : undefined %s %d %x", ea, mName, mSize, mFlag);
			DelStrucMember(id,i);		
			i = i+mSize;
		}
		else{
			i++;
		}	
	}
}

static undefineMultipleLineArray(ea){
	auto type;
			type = GuessType(ea);
			if(strstr(type,"char[")!=-1&&(strstr(GetDisasm(ea),"incbin")==-1)){
					Message(form("\n%a : %s \t\t<== UNDEFINE if on multiple lines.",ea,GuessType(ea)));
			}	
}

static writeFunctionFooter(file, ea){
	auto funcName;
	funcName = GetFunctionName(ea);
	writestr(file,form("\n	; End of function %s\n\n",funcName));
}

static writeItem(file,ea){
	auto name,tabLength,indent,disasm,cmtIdx,commentIndent,comment,commentEx,i,line,lineA,lineB,type,output;
	tabLength = 2;
	indent = "\t\t\t\t\t\t\t\t\t\t";
	commentIndent = "\t\t\t\t\t\t\t\t\t\t\t\t";
	name = GetTrueName(ea);
	if(name==""){
		name = Name(ea);
	}
	if(name!=""){
		name=form("%s:",name);
		if(GetFunctionAttr(ea,FUNCATTR_START)!=-1){
			name = form("%s\n%s",name,indent);
		}
		else{
			while(strlen(name)<(strlen(indent)*tabLength)){
				name = form("%s ",name);
			}		
			undefineMultipleLineArray(ea);
		}
	}
	else {
		name = indent;
	}
	commentEx = CommentEx(ea,0);
	if(commentEx!=""){
		comment = commentEx;
	}
	else{
		commentEx = CommentEx(ea,1);
		if(commentEx!=""){
			comment = formatRptCmt(commentEx);
		}
	}
	disasm = GetDisasm(ea);
	cmtIdx = strstr(disasm,";");
	if(cmtIdx!=-1){
		disasm = substr(disasm,0,cmtIdx);
	}
	if(comment!=""){
		comment = form("; %s",comment);
	}
	if(strlen(name)>(strlen(indent)*tabLength)){
		name = form("%s\n%s",name,indent);
	}
	if(strlen(disasm)>(strlen(commentIndent)*tabLength)&&comment!=""){
		disasm = form("%s\n%s%s",disasm,indent,commentIndent);
	}
	output = form("%s%s%s%s\n%s",lineA,name,disasm,comment,lineB);
	writestr(file,output);
}

static writeFChunkHeader(file,ea){
	auto text,functionName;
	text = "; START OF FUNCTION CHUNK FOR ";
	functionName = GetFunctionName(ea);
	writestr(file,form("\n%s%s\n\n",text,functionName));
}

static writeFChunkFooter(file,ea){
	auto text,functionName;
	text = "; END OF FUNCTION CHUNK FOR ";
	functionName = GetFunctionName(ea);
	writestr(file,form("\n%s%s\n\n",text,functionName));
}

static formatFuncRptCmt(cmt){
	auto index, before, after, result;
	index = strstr(cmt,"\n");
	if(index!=-1){
		before = substr(cmt,0,index+1);
		after = substr(cmt,index+1,strlen(cmt));
		result = form("%s; %s",before,formatFuncRptCmt(after));
		return result;
	}
	else{
		return cmt;
	}
}

static formatRptCmt(cmt){
	auto index, before, after, result;
	index = strstr(cmt,"\n");
	if(index!=-1){
		before = substr(cmt,0,index+1);
		after = substr(cmt,index+1,strlen(cmt));
		result = form("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t; %s",before,formatRptCmt(after));
		return result;
	}
	else{
		return cmt;
	}
}




	/* useless
	i=0;
	line = LineA(ea,i);
	while(line!=""){
		lineA = form("%s\n%s",lineA,line);
		i++;
		line = LineA(ea,i);
	}
	if(lineA!=""){
		lineA = form("%s\n",lineA);
	}
	
	i=0;
	line = LineB(ea,i);
	while(line!=""){
		lineA = form("%s\n%s",lineB,line);
		i++;
		line = LineB(ea,i);		
	}
	if(lineB!=""){
		lineB = form("%s\n",lineB);
	}
	*/