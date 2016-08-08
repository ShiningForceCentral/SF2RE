
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
	produceSpecificSectionEight(file,"08",0x64000,	0xC8000,		953 ,	"Map Tiles, Map Palettes, Map Data");
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
	produceAsmScript(file,"battles\\global\\battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies");
	produceAsmScript(file,"battles\\global\\eas_battleneutralentities",0x4497A,0x449C6,"Entity actscripts for battle entities which are not force members or enemies");
	produceAsmSection(file,0x449C6,0x44DE2);
	produceAsmScript(file,"scripting\\entityactscripts\\eas_main",0x44DE2,0x45202,"Main entity actscripts");
	produceAsmSection(file,0x45202,0x45284);
	produceAsmScript(file,"scripting\\mapscripts\\ms_caravanin",0x45284,0x45322,"Mapscript for getting into Caravan ?");
	produceAsmSection(file,0x45322,0x45348);
	produceAsmScript(file,"scripting\\mapscripts\\ms_caravanout",0x45348,0x453C6,"Mapscript for getting out of Caravan ?");
	produceAsmSection(file,0x453C6,0x453F2);
	produceAsmScript(file,"scripting\\mapscripts\\ms_raftin",0x453F2,0x45440,"Mapscript for getting into Raft ?");
	produceAsmSection(file,0x45440,0x45470);
	produceAsmScript(file,"scripting\\mapscripts\\ms_raftout",0x45470,0x454AC,"Mapscript for getting out of Raft ?");
	produceAsmSection(file,0x454AC,0x45546);
	produceAsmScript(file,"scripting\\mapscripts\\ms_shrinkin",0x45546,0x455AC,"Mapscript for shrinking in ?");
	produceAsmSection(file,0x455AC,0x455D2);
	produceAsmScript(file,"scripting\\mapscripts\\ms_growout",0x455D2,0x45634,"Mapscript for growing out ?");
	produceAsmSection(file,0x45634,0x45E44);
	produceAsmScript(file,"scripting\\entityactscripts\\eas_actions",0x45E44,0x46506,"Entity scripts for cutscene actions");
	produceAsmSection(file,0x46506,0x47A88);
	produceAsmScript(file,"battles\\global\\beforebattlecutscenes",0x47A88,0x47AE8,"Before battle cutscenes");
	produceAsmSection(file,0x47AE8,0x47B2C);
	produceAsmScript(file,"battles\\global\\battlestartcutscenes",0x47B2C,0x47B8C,"Battle start cutscenes");
	produceAsmSection(file,0x47B8C,0x47BE8);
	produceAsmScript(file,"battles\\global\\battleendcutscenes",0x47BE8,0x47C48,"Enemy defeated cutscenes");
	produceAsmSection(file,0x47C48,0x47CF4);
	produceAsmScript(file,"battles\\global\\afterbattlecutscenes",0x47CF4,0x47D54,"After battle cutscenes");
	produceAsmSection(file,0x47D54,0x47EC8);	
	produceAsmScript(file,"battles\\global\\regionactivatedcutscenes",0x47EC8,0x47EEA,"Region-activated cutscenes");
	produceAsmSection(file,0x47EEA,0x47EF8);
	produceAsmScript(file,"scripting\\cutscenes\\cs_introendroutine",0x47EF8,0x47F7E,"Subroutine launching intro and end cutscenes");
	produceAsmScript(file,"scripting\\cutscenes\\cs_intro1",0x47F7E,0x48380,"Intro cutscene 1");
	produceAsmScript(file,"scripting\\cutscenes\\cs_intro2",0x48380,0x48540,"Intro cutscene 2");
	produceAsmScript(file,"scripting\\cutscenes\\cs_intro3",0x48540,0x48A78,"Intro cutscene 3");
	produceAsmScript(file,"scripting\\cutscenes\\cs_intro4",0x48A78,0x48FE2,"Intro cutscene 4");
	produceAsmSection(file,0x48FE2,0x49058);
	produceAsmScript(file,"scripting\\cutscenes\\cs_end",0x49058,0x493EC,"End cutscene");
	produceAsmSection(file,0x493EC,0x494BC);

	produceAsmScript(file,"battles\\entries\\battle01\\cs_beforebattle",0x494BC,0x496DC,"Cutscene before battle 1");
	produceAsmScript(file,"battles\\entries\\battle01\\cs_afterbattle",0x496DC,0x4980E,"Cutscene after battle 1");
	produceAsmScript(file,"battles\\entries\\battle03\\cs_beforebattle",0x4980E,0x4981E,"Cutscene before battle 3");
	produceAsmScript(file,"battles\\entries\\battle04\\cs_beforebattle",0x4981E,0x498EE,"Cutscene before battle 4");
	produceAsmScript(file,"battles\\entries\\battle04\\cs_afterbattle",0x498EE,0x49AB2,"Cutscene after battle 4");
	produceAsmScript(file,"battles\\entries\\battle05\\cs_battleend",0x49AB2,0x49B48,"Enemy defeated cutscene for battle 5");
	produceAsmScript(file,"battles\\entries\\battle05\\cs_afterbattle",0x49B48,0x49BCA,"Cutscene after battle 5");
	produceAsmScript(file,"battles\\entries\\battle06\\cs_beforebattle",0x49BCA,0x49CE2,"Cutscene before battle 6");
	produceAsmScript(file,"battles\\entries\\battle07\\cs_beforebattle",0x49CE2,0x49F7E,"Cutscene before battle 7");
	produceAsmScript(file,"battles\\entries\\battle07\\cs_afterbattle",0x49F7E,0x4A952,"Cutscene after battle 7");
	produceAsmScript(file,"battles\\entries\\battle08\\cs_beforebattle",0x4A952,0x4AA74,"Cutscene before battle 8");
	produceAsmScript(file,"battles\\entries\\battle08\\cs_afterbattle",0x4AA74,0x4ABFE,"Cutscene after battle 8");
	produceAsmScript(file,"battles\\entries\\battle11\\cs_beforebattle",0x4ABFE,0x4ACC8,"Cutscene before battle 11");
	produceAsmScript(file,"battles\\entries\\battle12\\cs_battleend",0x4ACC8,0x4ACEC,"Enemy defeated cutscene for battle 12");
	produceAsmScript(file,"battles\\entries\\battle12\\cs_afterbattle",0x4ACEC,0x4ACF8,"Cutscene after battle 12");
	produceAsmScript(file,"battles\\entries\\battle13\\cs_afterbattle",0x4ACF8,0x4ADA6,"Cutscene after battle 13");
	produceAsmScript(file,"battles\\entries\\battle15\\cs_beforebattle",0x4ADA6,0x4AE72,"Cutscene before battle 15");
	produceAsmScript(file,"battles\\entries\\battle15\\cs_afterbattle",0x4AE72,0x4AFBE,"Cutscene after battle 15");
	produceAsmScript(file,"battles\\entries\\battle16\\cs_beforebattle",0x4AFBE,0x4B1BC,"Cutscene before battle 16");
	produceAsmScript(file,"battles\\entries\\battle16\\cs_afterbattle",0x4B1BC,0x4B1D8,"Cutscene after battle 16");
	produceAsmScript(file,"battles\\entries\\battle18\\cs_beforebattle",0x4B1D8,0x4B2F2,"Cutscene before battle 18");
	produceAsmScript(file,"battles\\entries\\battle18\\cs_afterbattle",0x4B2F2,0x4B6CE,"Cutscene after battle 18");
	produceAsmScript(file,"battles\\entries\\battle20\\cs_afterbattle",0x4B6CE,0x4B790,"Cutscene after battle 20");
	produceAsmScript(file,"battles\\entries\\battle21\\cs_beforebattle",0x4B790,0x4B88C,"Cutscene before battle 21");
	produceAsmScript(file,"battles\\entries\\battle21\\cs_afterbattle",0x4B88C,0x4B958,"Cutscene after battle 21");
	produceAsmScript(file,"battles\\entries\\battle26\\cs_beforebattle",0x4B958,0x4BCAA,"Cutscene before battle 26");
	produceAsmScript(file,"battles\\entries\\battle26\\cs_afterbattle",0x4BCAA,0x4BE6A,"Cutscene after battle 26");
	produceAsmScript(file,"battles\\entries\\battle27\\cs_battlestart",0x4BE6A,0x4BE8C,"Start cutscene for battle 27");
	produceAsmScript(file,"battles\\entries\\battle28\\cs_beforebattle",0x4BE8C,0x4C07C,"Cutscene before battle 28");
	produceAsmScript(file,"battles\\entries\\battle28\\cs_afterbattle",0x4C07C,0x4C3DC,"Cutscene after battle 28");
	produceAsmScript(file,"battles\\entries\\battle29\\cs_beforebattle",0x4C3DC,0x4C5E6,"Cutscene before battle 29");
	produceAsmScript(file,"battles\\entries\\battle30\\cs_beforebattle",0x4C5E6,0x4C6A8,"Cutscene before battle 30");
	produceAsmScript(file,"battles\\entries\\battle30\\cs_afterbattle",0x4C6A8,0x4C994,"Cutscene after battle 30");
	produceAsmScript(file,"battles\\entries\\battle31\\cs_beforebattle",0x4C994,0x4CBE2,"Cutscene before battle 31");
	produceAsmScript(file,"battles\\entries\\battle32\\cs_beforebattle",0x4CBE2,0x4CD10,"Cutscene before battle 32");
	produceAsmScript(file,"battles\\entries\\battle32\\cs_regiontriggered_1",0x4CD10,0x4CDB4,"Region-activated cutscene for battle 32");
	produceAsmScript(file,"battles\\entries\\battle32\\cs_afterbattle",0x4CDB4,0x4CF0C,"Cutscene after battle 32");
	produceAsmScript(file,"battles\\entries\\battle33\\cs_beforebattle",0x4CF0C,0x4D09A,"Cutscene before battle 33");
	produceAsmScript(file,"battles\\entries\\battle33\\cs_afterbattle",0x4D09A,0x4D342,"Cutscene after battle 33");
	produceAsmScript(file,"battles\\entries\\battle34\\cs_beforebattle",0x4D342,0x4D4B6,"Cutscene before battle 34");
	produceAsmScript(file,"battles\\entries\\battle34\\cs_afterbattle",0x4D4B6,0x4D6CE,"Cutscene after battle 34");
	produceAsmScript(file,"battles\\entries\\battle35\\cs_beforebattle",0x4D6CE,0x4D88A,"Cutscene before battle 35");
	produceAsmScript(file,"battles\\entries\\battle36\\cs_beforebattle",0x4D88A,0x4D9A4,"Cutscene before battle 36");
	produceAsmScript(file,"battles\\entries\\battle36\\cs_afterbattle",0x4D9A4,0x4DA66,"Cutscene after battle 36");
	produceAsmScript(file,"battles\\entries\\battle37\\cs_beforebattle",0x4DA66,0x4DB94,"Cutscene before battle 37");
	produceAsmScript(file,"battles\\entries\\battle37\\cs_afterbattle",0x4DB94,0x4DDA4,"Cutscene after battle 37");
	produceAsmScript(file,"battles\\entries\\battle38\\cs_beforebattle",0x4DDA4,0x4DE8C,"Cutscene before battle 38");
	produceAsmScript(file,"battles\\entries\\battle38\\cs_afterbattle",0x4DE8C,0x4E3D2,"Cutscene after battle 38");
	produceAsmScript(file,"battles\\entries\\battle39\\cs_beforebattle",0x4E3D2,0x4E4DC,"Cutscene before battle 39");
	produceAsmScript(file,"battles\\entries\\battle40\\cs_beforebattle",0x4E4DC,0x4E8A8,"Cutscene before battle 40");
	produceAsmScript(file,"battles\\entries\\battle40\\cs_regiontriggered_1",0x4E8A8,0x4E9B2,"Region-activated cutscene 1 for battle 40");
	produceAsmScript(file,"battles\\entries\\battle40\\cs_regiontriggered_2",0x4E9B2,0x4EA94,"Region-activated cutscene 2 for battle 40");
	produceAsmScript(file,"battles\\entries\\battle40\\cs_afterbattle",0x4EA94,0x4ED0E,"Cutscene after battle 40");
	produceAsmScript(file,"battles\\entries\\battle41\\cs_beforebattle",0x4ED0E,0x4ED8E,"Cutscene before battle 41");
	produceAsmScript(file,"battles\\entries\\battle42\\cs_beforebattle",0x4ED8E,0x4EF04,"Cutscene before battle 42");
	produceAsmScript(file,"battles\\entries\\battle42\\cs_afterbattle",0x4EF04,0x4F358,"Cutscene after battle 42");
	produceAsmScript(file,"battles\\entries\\battle43\\cs_battleend",0x4F358,0x4F35E,"Enemy defeated cutscene for battle 43");
	produceAsmScript(file,"battles\\entries\\battle43\\cs_afterbattle",0x4F35E,0x4F47A,"Cutscene after battle 43");
	produceAsmScript(file,"battles\\entries\\battle00\\cs_afterbattle",0x4F47A,0x4F48A,"Cutscene after battle 0");
	
	produceAsmSection(file,0x4F48A,0x4F6E2);
	
	produceAsmScript(file,"maps\\global\\mapsetups",0x4F6E2,0x4FA70,"Map setups table");

	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\pt",0x4FA70,0x4FA88,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s1",0x4FA88,0x4FA8A,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s2",0x4FA8A,0x4FA90,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s3",0x4FA90,0x4FAE0,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s4",0x4FAE0,0x4FAE2,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s5",0x4FAE2,0x4FAEA,"");
	produceAsmScript(file,"maps\\entries\\map66\\mapsetups\\s6",0x4FAEA,0x4FAEC,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\pt",0x4FAEC,0x4FB04,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s1",0x4FB04,0x4FB06,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s2",0x4FB06,0x4FB0C,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s3",0x4FB0C,0x4FCCE,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s4",0x4FCCE,0x4FD42,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s5",0x4FD42,0x4FD4A,"");
	produceAsmScript(file,"maps\\entries\\map67\\mapsetups\\s6",0x4FD4A,0x4FD4C,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\pt",0x4FD4C,0x4FD64,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s1",0x4FD64,0x4FD66,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s2",0x4FD66,0x4FD6C,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s3",0x4FD6C,0x4FD7C,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s4",0x4FD7C,0x4FD7E,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s5",0x4FD7E,0x4FD86,"");
	produceAsmScript(file,"maps\\entries\\map68\\mapsetups\\s6",0x4FD86,0x4FD88,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\pt",0x4FD88,0x4FDA0,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s1",0x4FDA0,0x4FDA2,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s3",0x4FDA2,0x4FDD2,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s2",0x4FDD2,0x4FDD8,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s4",0x4FDD8,0x4FDDA,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s5",0x4FDDA,0x4FDE2,"");
	produceAsmScript(file,"maps\\entries\\map69\\mapsetups\\s6",0x4FDE2,0x4FDE4,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\pt",0x4FDE4,0x4FDFC,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s1",0x4FDFC,0x4FDFE,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s3",0x4FDFE,0x4FE32,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s2",0x4FE32,0x4FE38,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s4",0x4FE38,0x4FE3A,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s5",0x4FE3A,0x4FE42,"");
	produceAsmScript(file,"maps\\entries\\map70\\mapsetups\\s6",0x4FE42,0x4FE44,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\pt",0x4FE44,0x4FE5C,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s1",0x4FE5C,0x4FE5E,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s2",0x4FE5E,0x4FE64,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s3",0x4FE64,0x4FF24,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s4",0x4FF24,0x4FF26,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s5",0x4FF26,0x4FF2E,"");
	produceAsmScript(file,"maps\\entries\\map72\\mapsetups\\s6",0x4FF2E,0x50312,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\pt",0x50312,0x5032A,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s1",0x5032A,0x5032C,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s3",0x5032C,0x50332,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s2",0x50332,0x50338,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s4",0x50338,0x5033A,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s5",0x5033A,0x50342,"");
	produceAsmScript(file,"maps\\entries\\map73\\mapsetups\\s6",0x50342,0x5096A,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\pt",0x5096A,0x50982,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s1",0x50982,0x50984,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s3",0x50984,0x509C6,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s2",0x509C6,0x509CC,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s4",0x509CC,0x509CE,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s5",0x509CE,0x509D6,"");
	produceAsmScript(file,"maps\\entries\\map74\\mapsetups\\s6",0x509D6,0x509D8,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\pt",0x509D8,0x509F0,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s1",0x509F0,0x509F2,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s3",0x509F2,0x509F8,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s2",0x509F8,0x509FE,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s4",0x509FE,0x50A00,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s5",0x50A00,0x50A08,"");
	produceAsmScript(file,"maps\\entries\\map75\\mapsetups\\s6",0x50A08,0x50A0A,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\pt",0x50A0A,0x50A22,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s1",0x50A22,0x50A24,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s3",0x50A24,0x50A3E,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s2",0x50A3E,0x50A44,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s4",0x50A44,0x50A46,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s5",0x50A46,0x50A4E,"");
	produceAsmScript(file,"maps\\entries\\map76\\mapsetups\\s6",0x50A4E,0x50A50,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\pt",0x50A50,0x50A68,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s1",0x50A68,0x50A6A,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s3",0x50A6A,0x50A84,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s2",0x50A84,0x50A8A,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s4",0x50A8A,0x50A8C,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s5",0x50A8C,0x50AE6,"");
	produceAsmScript(file,"maps\\entries\\map77\\mapsetups\\s6",0x50AE6,0x50AE8,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\pt",0x50AE8,0x50B00,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\pt_261",0x50B00,0x50B18,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\pt_1FA",0x50B18,0x50B30,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s1",0x50B30,0x50BCA,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s1_261",0x50BCA,0x50CCA,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s1_1FA",0x50CCA,0x50D4C,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s3",0x50D4C,0x50EEA,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s3_261",0x50EEA,0x50F0C,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s3_1FA",0x50F0C,0x50F10,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s2",0x50F10,0x5105C,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s2_261",0x5105C,0x511CA,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s2_1FA",0x511CA,0x512E0,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s4",0x512E0,0x51358,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s5",0x51358,0x51360,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s6_1FA",0x51360,0x51382,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s6",0x51382,0x513C0,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s6_261",0x513C0,0x516CC,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\pt",0x516CC,0x516E4,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s1",0x516E4,0x516F6,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s3",0x516F6,0x516FC,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s2",0x516FC,0x51702,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s4",0x51702,0x51720,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s5",0x51720,0x51728,"");
	produceAsmScript(file,"maps\\entries\\map04\\mapsetups\\s6",0x51728,0x51912,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\pt",0x51912,0x5192A,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\pt_28A",0x5192A,0x51942,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s1",0x51942,0x519C4,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s1_28A",0x519C4,0x51A3E,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s2",0x51A3E,0x51A82,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s2_28A",0x51A82,0x51C22,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s3",0x51C22,0x51C28,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s4",0x51C28,0x51C54,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s5",0x51C54,0x51C5C,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s6",0x51C5C,0x51C5E,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\pt_297",0x51C5E,0x51C76,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\pt",0x51C76,0x51C8E,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s1_297",0x51C8E,0x51D30,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s1",0x51D30,0x51DE2,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s2_297",0x51DE2,0x51E32,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s2",0x51E32,0x51EE4,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s3",0x51EE4,0x51F2A,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s4",0x51F2A,0x51F6E,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s5",0x51F6E,0x51F76,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s6",0x51F76,0x52284,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\pt",0x52284,0x5229C,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\pt_1F9",0x5229C,0x522B4,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s1",0x522B4,0x522DC,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s1_1F9",0x522DC,0x5231C,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s2",0x5231C,0x523E4,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s3",0x523E4,0x52442,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s3_1F9",0x52442,0x52446,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s4",0x52446,0x52448,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s5",0x52448,0x52450,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s6",0x52450,0x52A80,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\pt",0x52A80,0x52A98,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s1",0x52A98,0x52ABA,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s2",0x52ABA,0x52B20,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s3",0x52B20,0x52B26,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s4",0x52B26,0x52B40,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s5",0x52B40,0x52B48,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s6",0x52B48,0x52B4A,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt",0x52B4A,0x52B62,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_1F5",0x52B62,0x52B7A,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_261",0x52B7A,0x52B92,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_1FA",0x52B92,0x52BAA,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_1FB",0x52BAA,0x52BC2,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1",0x52BC2,0x52C2C,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_1F5",0x52C2C,0x52C46,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_261",0x52C46,0x52CB0,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_1FA",0x52CB0,0x52D8A,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_1FB",0x52D8A,0x52D94,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s3",0x52D94,0x52D98,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s3_1FA",0x52D98,0x52DA4,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s3_1FB",0x52DA4,0x52E02,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2",0x52E02,0x52F60,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_1F5",0x52F60,0x52F90,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_261",0x52F90,0x5301C,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_1FA",0x5301C,0x530BA,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_1FB",0x530BA,0x530BE,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s4",0x530BE,0x530E2,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s5",0x530E2,0x530EA,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s6",0x530EA,0x5310C,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s6_261",0x5310C,0x5311E,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s6_1FA",0x5311E,0x53168,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s6_1FB",0x53168,0x53634,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\pt",0x53634,0x5364C,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\pt_1F5",0x5364C,0x53664,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\pt_261",0x53664,0x5367C,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\pt_1FA",0x5367C,0x53694,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s1",0x53694,0x536D6,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s1_1F5",0x536D6,0x53720,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s1_261",0x53720,0x53760,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s1_1FA",0x53760,0x53762,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s3",0x53762,0x53766,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s3_1F5",0x53766,0x537AC,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s2",0x537AC,0x53830,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s2_1F5",0x53830,0x538B4,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s2_261",0x538B4,0x53928,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s2_1FA",0x53928,0x5392C,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s4",0x5392C,0x5395E,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s5",0x5395E,0x53966,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s6",0x53966,0x53E18,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\pt",0x53E18,0x53E30,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\pt_1F5",0x53E30,0x53E48,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\pt_261",0x53E48,0x53E60,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\pt_1FA",0x53E60,0x53E78,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s1",0x53E78,0x53E82,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s1_261",0x53E82,0x53E8A,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s1_1FA",0x53E8A,0x53E8C,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s3",0x53E8C,0x53E92,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s2",0x53E92,0x53E9A,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s2_1F5",0x53E9A,0x53EA2,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s2_261",0x53EA2,0x53EAA,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s2_1FA",0x53EAA,0x53F06,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s4",0x53F06,0x53F08,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s5",0x53F08,0x53F10,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s6",0x53F10,0x53F48,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\pt_1FA",0x53F48,0x53F60,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\pt",0x53F60,0x53F78,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s1_1FA",0x53F78,0x53F90,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s1",0x53F90,0x53F92,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s2",0x53F92,0x53FBA,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s3",0x53FBA,0x53FC0,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s4",0x53FC0,0x53FC2,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s5",0x53FC2,0x53FCA,"");
	produceAsmScript(file,"maps\\entries\\map40\\mapsetups\\s6",0x53FCA,0x53FFE,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\pt",0x53FFE,0x54016,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\pt_264",0x54016,0x5402E,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s1",0x5402E,0x54046,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s1_264",0x54046,0x54048,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s3",0x54048,0x5404E,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s2",0x5404E,0x54054,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s5",0x54054,0x5405C,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s4",0x5405C,0x540A6,"");
	produceAsmScript(file,"maps\\entries\\map43\\mapsetups\\s6",0x540A6,0x54348,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\pt",0x54348,0x54360,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\pt_261",0x54360,0x54378,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\pt_1FA",0x54378,0x54390,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\pt_1FB",0x54390,0x543A8,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s1",0x543A8,0x543BA,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s1_261",0x543BA,0x543E4,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s1_1FA",0x543E4,0x543EE,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s1_1FB",0x543EE,0x54458,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s3",0x54458,0x5445E,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s2",0x5445E,0x5446A,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s2_261",0x5446A,0x54482,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s2_1FA",0x54482,0x5448A,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s2_1FB",0x5448A,0x5455E,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s5",0x5455E,0x54566,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s4",0x54566,0x54568,"");
	produceAsmScript(file,"maps\\entries\\map44\\mapsetups\\s6_1FB",0x54568,0x5473E,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\pt_2BE",0x5473E,0x54756,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\pt",0x54756,0x5476E,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\pt_2BD",0x5476E,0x54786,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s1_2BE",0x54786,0x547F8,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s1",0x547F8,0x5489A,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s1_2BD",0x5489A,0x5490C,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s2_2BE",0x5490C,0x54948,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s2",0x54948,0x54984,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s2_2BD",0x54984,0x54CD0,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s3",0x54CD0,0x54D3C,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s4_2BE",0x54D3C,0x54D8A,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s4",0x54D8A,0x54E4C,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s5",0x54E4C,0x54E54,"");
	produceAsmScript(file,"maps\\entries\\map06\\mapsetups\\s6",0x54E54,0x5537E,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\pt",0x5537E,0x55396,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\pt_2BD",0x55396,0x553AE,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\pt_325",0x553AE,0x553C6,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s1",0x553C6,0x55428,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s1_2BD",0x55428,0x554B2,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s1_325",0x554B2,0x5550C,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s2",0x5550C,0x55540,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s2_2BD",0x55540,0x55584,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s2_325",0x55584,0x5579E,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s3",0x5579E,0x557EE,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s4",0x557EE,0x5580E,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s5",0x5580E,0x55816,"");
	produceAsmScript(file,"maps\\entries\\map07\\mapsetups\\s6",0x55816,0x55F8E,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\pt_2C4",0x55F8E,0x55FA6,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\pt",0x55FA6,0x55FC4,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s1_2C4",0x55FC4,0x56036,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s1",0x56036,0x56048,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s2_2C4",0x56048,0x56084,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s2",0x56084,0x561AE,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s3",0x561AE,0x561EC,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s4",0x561EC,0x562E0,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s5",0x562E0,0x563A2,"");
	produceAsmScript(file,"maps\\entries\\map08\\mapsetups\\s6",0x563A2,0x56636,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\pt",0x56636,0x5664E,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\pt_206",0x5664E,0x56666,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s1",0x56666,0x566C0,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s1_206",0x566C0,0x56722,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s2",0x56722,0x56856,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s3",0x56856,0x5687A,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s4",0x5687A,0x568A4,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s5",0x568A4,0x568C4,"");
	produceAsmScript(file,"maps\\entries\\map09\\mapsetups\\s6",0x568C4,0x56B84,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\pt",0x56B84,0x56B9C,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\pt_2D2",0x56B9C,0x56BB4,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s1",0x56BB4,0x56CA6,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s1_2D2",0x56CA6,0x56D80,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s2",0x56D80,0x56E9C,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s2_2D2",0x56E9C,0x56F8A,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s3",0x56F8A,0x56FC0,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s3_2D2",0x56FC0,0x56FE0,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s4",0x56FE0,0x57028,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s5",0x57028,0x57030,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s6",0x57030,0x5708E,"");
	produceAsmScript(file,"maps\\entries\\map10\\mapsetups\\s6_2D2",0x5708E,0x579CA,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\pt",0x579CA,0x579E2,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s1",0x579E2,0x57A0C,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s2",0x57A0C,0x57A68,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s3",0x57A68,0x57A88,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s4",0x57A88,0x57AA0,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s5",0x57AA0,0x57AA8,"");
	produceAsmScript(file,"maps\\entries\\map11\\mapsetups\\s6",0x57AA8,0x57CCC,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\pt",0x57CCC,0x57CE4,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s1",0x57CE4,0x57CEE,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s2",0x57CEE,0x57CF4,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s3",0x57CF4,0x57CFA,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s4",0x57CFA,0x57CFC,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s5",0x57CFC,0x57D04,"");
	produceAsmScript(file,"maps\\entries\\map12\\mapsetups\\s6",0x57D04,0x57E36,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\pt",0x57E36,0x57E4E,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\pt_2C6",0x57E4E,0x57E66,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\pt_31F",0x57E66,0x57E7E,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\pt_201",0x57E7E,0x57E96,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s1",0x57E96,0x57F08,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s1_2C6",0x57F08,0x57F7A,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s1_31F",0x57F7A,0x57FB4,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s1_201",0x57FB4,0x5801E,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s2",0x5801E,0x5814C,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s2_201",0x5814C,0x5822A,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s3",0x5822A,0x582AC,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s4",0x582AC,0x582D8,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s5",0x582D8,0x582E0,"");
	produceAsmScript(file,"maps\\entries\\map13\\mapsetups\\s6",0x582E0,0x58E18,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\pt",0x58E18,0x58E30,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\pt_1CA",0x58E30,0x58E48,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s3",0x58E48,0x58EBA,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s2",0x58EBA,0x58F0E,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s1",0x58F0E,0x58F10,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s4",0x58F10,0x58F12,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s6",0x58F12,0x58F2A,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s1_1CA",0x58F2A,0x58F3C,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s2_1CA",0x58F3C,0x58F4C,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s3_1CA",0x58F4C,0x58F9A,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s6_1CA",0x58F9A,0x58F9C,"");
	produceAsmScript(file,"maps\\entries\\map14\\mapsetups\\s5",0x58F9C,0x592E0,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\pt",0x592E0,0x592F8,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\pt_20A",0x592F8,0x59310,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s1",0x59310,0x59402,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s1_20A",0x59402,0x59474,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s2",0x59474,0x595DE,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s3",0x595DE,0x59602,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s4",0x59602,0x59604,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s5",0x59604,0x5962E,"");
	produceAsmScript(file,"maps\\entries\\map22\\mapsetups\\s6",0x5962E,0x59AC0,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\pt",0x59AC0,0x59AD8,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\pt_2FA",0x59AD8,0x59AF0,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s1",0x59AF0,0x59B22,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s1_2FA",0x59B22,0x59B44,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s2",0x59B44,0x59BA8,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s2_2FA",0x59BA8,0x59BD2,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s3",0x59BD2,0x59BD8,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s4",0x59BD8,0x59BFC,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s5",0x59BFC,0x59C04,"");
	produceAsmScript(file,"maps\\entries\\map23\\mapsetups\\s6",0x59C04,0x59C06,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\pt",0x59C06,0x59C1E,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s1",0x59C1E,0x59C20,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s2",0x59C20,0x59C26,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s3",0x59C26,0x59C2C,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s4",0x59C2C,0x59C2E,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s5",0x59C2E,0x59C36,"");
	produceAsmScript(file,"maps\\entries\\map24\\mapsetups\\s6",0x59C36,0x59D08,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\pt",0x59D08,0x59D20,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s1",0x59D20,0x59D6A,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s2",0x59D6A,0x59DB6,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s3",0x59DB6,0x59DD2,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s4",0x59DD2,0x59DD4,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s5",0x59DD4,0x59DDC,"");
	produceAsmScript(file,"maps\\entries\\map26\\mapsetups\\s6",0x59DDC,0x59F42,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\pt",0x59F42,0x59F5A,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\pt_20B",0x59F5A,0x59F72,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s1",0x59F72,0x59F8A,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s1_20B",0x59F8A,0x59F8C,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s2",0x59F8C,0x59F92,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s3",0x59F92,0x59FAC,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s4",0x59FAC,0x59FAE,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s5",0x59FAE,0x59FB6,"");
	produceAsmScript(file,"maps\\entries\\map27\\mapsetups\\s6",0x59FB6,0x5A09E,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\pt",0x5A09E,0x5A0B6,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s1",0x5A0B6,0x5A0F0,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s2",0x5A0F0,0x5A14E,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s3",0x5A14E,0x5A154,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s4",0x5A154,0x5A16C,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s5",0x5A16C,0x5A174,"");
	produceAsmScript(file,"maps\\entries\\map29\\mapsetups\\s6",0x5A174,0x5A176,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\pt",0x5A176,0x5A18E,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\pt_311",0x5A18E,0x5A1A6,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\pt_2F9",0x5A1A6,0x5A1BE,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s1",0x5A1BE,0x5A1E0,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s1_311",0x5A1E0,0x5A20A,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s1_2F9",0x5A20A,0x5A20C,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s2",0x5A20C,0x5A2C2,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s3",0x5A2C2,0x5A2E8,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s4",0x5A2E8,0x5A2EA,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s5",0x5A2EA,0x5A2F2,"");
	produceAsmScript(file,"maps\\entries\\map30\\mapsetups\\s6",0x5A2F2,0x5A646,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\pt",0x5A646,0x5A65E,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\pt_20B",0x5A65E,0x5A676,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\pt_310",0x5A676,0x5A68E,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\pt_312",0x5A68E,0x5A6A6,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s1",0x5A6A6,0x5A6D8,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s1_20B",0x5A6D8,0x5A712,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s1_310",0x5A712,0x5A74C,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s1_312",0x5A74C,0x5A766,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s2",0x5A766,0x5AA8A,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s3",0x5AA8A,0x5AAD8,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s4",0x5AAD8,0x5AB74,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s5",0x5AB74,0x5AB7C,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s6",0x5AB7C,0x5AC56,"");
	produceAsmScript(file,"maps\\entries\\map33\\mapsetups\\s6_312",0x5AC56,0x5B5B6,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\pt",0x5B5B6,0x5B5CE,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\pt_310",0x5B5CE,0x5B5E6,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s1",0x5B5E6,0x5B68E,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s1_310",0x5B68E,0x5B690,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s2",0x5B690,0x5B696,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s3",0x5B696,0x5B6B4,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s4",0x5B6B4,0x5B6B6,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s5",0x5B6B6,0x5B6BE,"");
	produceAsmScript(file,"maps\\entries\\map34\\mapsetups\\s6",0x5B6BE,0x5BFEE,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\pt",0x5BFEE,0x5C006,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s1",0x5C006,0x5C0F8,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s2",0x5C0F8,0x5C264,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s3",0x5C264,0x5C26A,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s4",0x5C26A,0x5C26C,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s5",0x5C26C,0x5C274,"");
	produceAsmScript(file,"maps\\entries\\map46\\mapsetups\\s6",0x5C274,0x5C27C,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\pt",0x5C27C,0x5C294,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\pt_208",0x5C294,0x5C2AC,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s1",0x5C2AC,0x5C2CE,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s1_208",0x5C2CE,0x5C2D0,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s2",0x5C2D0,0x5C2D6,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s3",0x5C2D6,0x5C3C0,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s4",0x5C3C0,0x5C3C2,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s5",0x5C3C2,0x5C3CA,"");
	produceAsmScript(file,"maps\\entries\\map51\\mapsetups\\s6",0x5C3CA,0x5C454,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\pt",0x5C454,0x5C46C,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\pt_200",0x5C46C,0x5C484,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s1",0x5C484,0x5C4A6,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s1_200",0x5C4A6,0x5C4A8,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s2",0x5C4A8,0x5C4AA,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s3",0x5C4AA,0x5C4CC,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s4",0x5C4CC,0x5C4CE,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s5",0x5C4CE,0x5C4D6,"");
	produceAsmScript(file,"maps\\entries\\map52\\mapsetups\\s6",0x5C4D6,0x5C638,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\pt_2D9",0x5C638,0x5C650,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\pt",0x5C650,0x5C668,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s1",0x5C668,0x5C670,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s1_2D9",0x5C670,0x5C672,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s2",0x5C672,0x5C696,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s3",0x5C696,0x5C6BE,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s4",0x5C6BE,0x5C6C0,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s5",0x5C6C0,0x5C6C8,"");
	produceAsmScript(file,"maps\\entries\\map61\\mapsetups\\s6",0x5C6C8,0x5C76A,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\pt",0x5C76A,0x5C782,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\pt_4D",0x5C782,0x5C79A,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s1",0x5C79A,0x5C7AC,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s1_4D",0x5C7AC,0x5C7B6,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s2",0x5C7B6,0x5C820,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s3",0x5C820,0x5C86A,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s4",0x5C86A,0x5C86C,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s5",0x5C86C,0x5C874,"");
	produceAsmScript(file,"maps\\entries\\map62\\mapsetups\\s6",0x5C874,0x5C950,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\pt_1D",0x5C950,0x5C968,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\pt",0x5C968,0x5C980,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s1",0x5C980,0x5C988,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s1_1D",0x5C988,0x5C98A,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s2",0x5C98A,0x5C9E2,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s3",0x5C9E2,0x5CA24,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s4",0x5CA24,0x5CA26,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s5",0x5CA26,0x5CA50,"");
	produceAsmScript(file,"maps\\entries\\map63\\mapsetups\\s6",0x5CA50,0x5CDFE,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\pt",0x5CDFE,0x5CE16,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\pt_212",0x5CE16,0x5CE2E,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s1",0x5CE2E,0x5CE90,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s1_212",0x5CE90,0x5CEEA,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s2",0x5CEEA,0x5CF9E,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s2_212",0x5CF9E,0x5CFFA,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s3",0x5CFFA,0x5CFFE,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s3_212",0x5CFFE,0x5D020,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s4",0x5D020,0x5D044,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s5",0x5D044,0x5D04C,"");
	produceAsmScript(file,"maps\\entries\\map15\\mapsetups\\s6",0x5D04C,0x5D1CA,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\pt",0x5D1CA,0x5D1E2,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s1",0x5D1E2,0x5D224,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s2",0x5D224,0x5D33A,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s3",0x5D33A,0x5D340,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s4",0x5D340,0x5D394,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s5",0x5D394,0x5D39C,"");
	produceAsmScript(file,"maps\\entries\\map25\\mapsetups\\s6",0x5D39C,0x5D40E,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\pt",0x5D40E,0x5D426,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\pt_33E",0x5D426,0x5D43E,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s1",0x5D43E,0x5D440,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s1_33E",0x5D440,0x5D49A,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s2",0x5D49A,0x5D49E,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s2_33E",0x5D49E,0x5D552,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s3",0x5D552,0x5D556,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s3_33E",0x5D556,0x5D574,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s4",0x5D574,0x5D60E,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s5",0x5D60E,0x5D614,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s5_33E",0x5D614,0x5D61C,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s6",0x5D61C,0x5D61E,"");
	produceAsmScript(file,"maps\\entries\\map31\\mapsetups\\s6_33E",0x5D61E,0x5D756,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\pt",0x5D756,0x5D76E,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\pt_212",0x5D76E,0x5D786,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s1",0x5D786,0x5D7F0,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s1_212",0x5D7F0,0x5D84A,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s2",0x5D84A,0x5D924,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s2_212",0x5D924,0x5D9C0,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s3",0x5D9C0,0x5D9C6,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s4",0x5D9C6,0x5DA0E,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s5",0x5DA0E,0x5DA16,"");
	produceAsmScript(file,"maps\\entries\\map36\\mapsetups\\s6",0x5DA16,0x5DAE4,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\pt",0x5DAE4,0x5DAFC,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s1",0x5DAFC,0x5DB76,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s2",0x5DB76,0x5DCD0,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s3",0x5DCD0,0x5DD26,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s4",0x5DD26,0x5DD50,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s5",0x5DD50,0x5DD58,"");
	produceAsmScript(file,"maps\\entries\\map38\\mapsetups\\s6",0x5DD58,0x5DF84,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\pt",0x5DF84,0x5DF9C,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\pt_33E",0x5DF9C,0x5DFB4,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s1",0x5DFB4,0x5DFFE,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s1_33E",0x5DFFE,0x5E038,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s2",0x5E038,0x5E0B2,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s3",0x5E0B2,0x5E0CE,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s3_33E",0x5E0CE,0x5E0D4,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s4",0x5E0D4,0x5E0D6,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s5",0x5E0D6,0x5E0DE,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s6",0x5E0DE,0x5E0E0,"");
	produceAsmScript(file,"maps\\entries\\map39\\mapsetups\\s6_33E",0x5E0E0,0x5E22C,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\pt",0x5E22C,0x5E244,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s1",0x5E244,0x5E246,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s2",0x5E246,0x5E248,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s3",0x5E248,0x5E25E,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s4",0x5E25E,0x5E260,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s5",0x5E260,0x5E268,"");
	produceAsmScript(file,"maps\\entries\\map55\\mapsetups\\s6",0x5E268,0x5E37C,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\pt",0x5E37C,0x5E394,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s1",0x5E394,0x5E39E,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s2",0x5E39E,0x5E3A4,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s3",0x5E3A4,0x5E61E,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s4",0x5E61E,0x5E620,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s5",0x5E620,0x5E628,"");
	produceAsmScript(file,"maps\\entries\\map00\\mapsetups\\s6",0x5E628,0x5E62A,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\pt",0x5E62A,0x5E642,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s1",0x5E642,0x5E694,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s2",0x5E694,0x5E720,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s3",0x5E720,0x5E726,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s4",0x5E726,0x5E758,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s5",0x5E758,0x5E760,"");
	produceAsmScript(file,"maps\\entries\\map01\\mapsetups\\s6",0x5E760,0x5E86C,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\pt",0x5E86C,0x5E884,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\pt_212",0x5E884,0x5E89C,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s1",0x5E89C,0x5E8EE,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s1_212",0x5E8EE,0x5E938,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s2",0x5E938,0x5E9C8,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s2_212",0x5E9C8,0x5EA20,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s3",0x5EA20,0x5EA26,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s4",0x5EA26,0x5EA62,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s4_212",0x5EA62,0x5EA9E,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s5",0x5EA9E,0x5EAA6,"");
	produceAsmScript(file,"maps\\entries\\map02\\mapsetups\\s6",0x5EAA6,0x5EAA8,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\pt",0x5EAA8,0x5EAC0,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s1",0x5EAC0,0x5EAC2,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s2",0x5EAC2,0x5EAC8,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s3",0x5EAC8,0x5EACE,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s4",0x5EACE,0x5EAD0,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s5",0x5EAD0,0x5EAD8,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s6",0x5EAD8,0x5F34C,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\pt",0x5F34C,0x5F364,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s1",0x5F364,0x5F366,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s2",0x5F366,0x5F36C,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s3",0x5F36C,0x5F396,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s4",0x5F396,0x5F398,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s5",0x5F398,0x5F3A0,"");
	produceAsmScript(file,"maps\\entries\\map28\\mapsetups\\s6",0x5F3A0,0x5F3E8,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\pt",0x5F3E8,0x5F400,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s1",0x5F400,0x5F402,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s2",0x5F402,0x5F408,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s3",0x5F408,0x5F40E,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s4",0x5F40E,0x5F46C,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s5",0x5F46C,0x5F4A0,"");
	produceAsmScript(file,"maps\\entries\\map41\\mapsetups\\s6",0x5F4A0,0x5F630,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\pt",0x5F630,0x5F660,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\pt_3E7",0x5F660,0x5F678,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s1",0x5F678,0x5F772,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s1_3E7",0x5F772,0x5F86C,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s2",0x5F86C,0x5F9D2,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s2_3E7",0x5F9D2,0x5FA22,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s3",0x5FA22,0x5FA28,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s4",0x5FA28,0x5FA2A,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s5",0x5FA2A,0x5FA88,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s6",0x5FA88,0x5FAA4,"");
	produceAsmScript(file,"maps\\entries\\map37\\mapsetups\\s6_3E7",0x5FAA4,0x5FDE4,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\pt",0x5FDE4,0x5FDFC,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s1",0x5FDFC,0x5FDFE,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s2",0x5FDFE,0x5FE04,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s3",0x5FE04,0x5FE24,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s4",0x5FE24,0x5FE90,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s5",0x5FE90,0x5FE98,"");
	produceAsmScript(file,"maps\\entries\\map42\\mapsetups\\s6",0x5FE98,0x5FF62,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\pt",0x5FF62,0x5FF7A,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s1",0x5FF7A,0x60024,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s2",0x60024,0x60060,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s3",0x60060,0x60078,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s4",0x60078,0x60090,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s5",0x60090,0x60098,"");
	produceAsmScript(file,"maps\\entries\\map45\\mapsetups\\s6",0x60098,0x603AE,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\pt_212",0x603AE,0x603C6,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\pt_1C",0x603C6,0x603DE,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s1_212",0x603DE,0x60410,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s1_1C",0x60410,0x6043A,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s2_212",0x6043A,0x604C8,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s3_212",0x604C8,0x60548,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s4_212",0x60548,0x60606,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s5_212",0x60606,0x6061E,"");
	produceAsmScript(file,"maps\\entries\\map05\\mapsetups\\s6_212",0x6061E,0x60FAE,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\pt_212",0x60FAE,0x60FC6,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s1_212",0x60FC6,0x61058,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s2_212",0x61058,0x6114E,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s3_212",0x6114E,0x61154,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s4_212",0x61154,0x6119C,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s5_212",0x6119C,0x611A4,"");
	produceAsmScript(file,"maps\\entries\\map16\\mapsetups\\s6_212",0x611A4,0x611A6,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\pt_212",0x611A6,0x611BE,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s1_212",0x611BE,0x611E0,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s2_212",0x611E0,0x61208,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s3_212",0x61208,0x6120E,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s4_212",0x6120E,0x61210,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s5_212",0x61210,0x61218,"");
	produceAsmScript(file,"maps\\entries\\map17\\mapsetups\\s6_212",0x61218,0x6121A,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\pt_212",0x6121A,0x61232,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s1_212",0x61232,0x61254,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s2_212",0x61254,0x6125A,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s3_212",0x6125A,0x61278,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s4_212",0x61278,0x61290,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s5_212",0x61290,0x61298,"");
	produceAsmScript(file,"maps\\entries\\map18\\mapsetups\\s6_212",0x61298,0x61488,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\pt",0x61488,0x614A0,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s1",0x614A0,0x614AA,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s2",0x614AA,0x614D6,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s3",0x614D6,0x614FE,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s4",0x614FE,0x61500,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s5",0x61500,0x61508,"");
	produceAsmScript(file,"maps\\entries\\map56\\mapsetups\\s6",0x61508,0x6153E,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\pt_21F",0x6153E,0x61556,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s1_21F",0x61556,0x615B0,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s2_21F",0x615B0,0x615B6,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s3_21F",0x615B6,0x615CE,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s4_21F",0x615CE,0x615D0,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s5_21F",0x615D0,0x615D8,"");
	produceAsmScript(file,"maps\\entries\\map59\\mapsetups\\s6_21F",0x615D8,0x626A6,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\pt_21F",0x626A6,0x626BE,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s1_21F",0x626BE,0x62738,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s2_21F",0x62738,0x62820,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s3_21F",0x62820,0x62846,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s4_21F",0x62846,0x628BE,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s5_21F",0x628BE,0x628C6,"");
	produceAsmScript(file,"maps\\entries\\map03\\mapsetups\\s6_21F",0x628C6,0x6299A,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_21F",0x6299A,0x629B2,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\pt_3D6",0x629B2,0x629CA,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_21F",0x629CA,0x62A6C,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s1_3D6",0x62A6C,0x62AFE,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_21F",0x62AFE,0x62BCA,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s2_3D6",0x62BCA,0x62C6C,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s3_21F",0x62C6C,0x62C72,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s4_21F",0x62C72,0x62C96,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s5_21F",0x62C96,0x62C9E,"");
	produceAsmScript(file,"maps\\entries\\map19\\mapsetups\\s6_21F",0x62C9E,0x631EA,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\pt_21F",0x631EA,0x63202,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s1_21F",0x63202,0x63234,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s2_21F",0x63234,0x6329A,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s3_21F",0x6329A,0x63364,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s4_21F",0x63364,0x6339A,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s5_21F",0x6339A,0x633A2,"");
	produceAsmScript(file,"maps\\entries\\map20\\mapsetups\\s6_21F",0x633A2,0x6343C,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\pt_21F",0x6343C,0x63454,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s1_21F",0x63454,0x6345E,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s2_21F",0x6345E,0x63472,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s3_21F",0x63472,0x63478,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s4_21F",0x63478,0x6347A,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s5_21F",0x6347A,0x63482,"");
	produceAsmScript(file,"maps\\entries\\map21\\mapsetups\\s6_21F",0x63482,0x6348C,"");
	//produceAsmScript(file,"maps\\entries\\mapsetups",0x4FAEC,0x6348C,"Map setups to be split later");
	produceAsmSection(file,0x6348C,0x64000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionEight(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("sf2-%s.asm",sectionName);
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("   include \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(fileName,"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("\n; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x64000,0x6400C);
	produceAsmScript(file,"maps\\global\\maptilesets",0x6400C,0x9494A,"Map palettes table");	
	produceAsmScript(file,"maps\\global\\mappalettes",0x9494A,0x94B8A,"Map palettes table");
	produceAsmScript(file,"maps\\global\\mapentries",0x94B8A,0xC7ECC,"Map entries table");
	produceAsmSection(file,0xC7ECC,0xC8000);

	fclose(file);
	Message("DONE.\n");	
}


static produceAsmScript(mainFile,sectionName,start,end,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("%s.asm",sectionName);
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