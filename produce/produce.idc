
/*
 *	Attempt at producing ASM file from IDC script 
 *	instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

	Message("PRODUCING ASM...\n");

	//produceMacros();
	produceEnums();
	produceConst();
	produceMain();
	
	Message("\nEND OF ASM PRODUCTION.\n");

}

/*
static produceMacros(){
	auto file;
	Message("\nWriting Macros to sf2macros.asm ...");	
	file = fopen("disasm\\sf2macros.asm","w");
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
*/

static produceEnums(){
	auto i,j,enumQty,id,enumName,enumSize,constant,constId,output,file;
	file = fopen("disasm\\sf2enums.asm","w");
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
	file = fopen("disasm\\sf2const.asm","w");
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
	file = fopen("disasm\\sf2.asm","w");
	writeHeader(file);

	produceLayoutFile();

	fclose(file);
	Message("\nDONE.");	
}

static produceLayoutFile(){

	auto file;
	file = fopen("disasm\\layout\\sf2-00-romlayout.asm","w");
	
	writestr(file,"\n; ROM LAYOUT FILE\n;\n; Original ROM layout results in a 2MB ROM.\n; Sections can be moved to get more free space by changing declaration order and by using align directives to pad section ends until desired end offset.");
	writestr(file,"\n; (beware : ROMs over 2MB imply to manage SRAM bankswitching first)");
	writestr(file,"\n\n");

	produceSpecificSectionOne(file,		"01",	0x0,		0x8000,		90,	"0x000000..0x008000 : Technical Layer, Low Level Game Engine, Map/Exploration Engine, Entity Script Commands, Witch Functions");
	produceSpecificSectionTwo(file,		"02",	0x8000,		0x10000,	121,	"0x008000..0x010000 : Character Stats Engine, Battle engine, Item Effects Engine, Enemy AI Engine");
	produceSpecificSectionThree(file,	"03",	0x10000,	0x18000,	38,	"0x010000..0x018000 : Menu Engine");
	produceSpecificSectionFour(file,	"04",	0x18000,	0x20000,	532,	"0x018000..0x020000 : BattleScene Engine");
	produceSpecificSectionFive(file,	"05",	0x20000,	0x28000,	626,	"0x020000..0x028000 : Battle Engine, Special Sprites, Shop/Church/Blacksmith/Caravan engine, Battle Engine, Exploration Engine, Special Sprites");
	produceSpecificSectionSix(file,		"06",	0x28000,	0x44000,	6681,	"0x028000..0x044000 : Fonts, Menu Tiles, Text Decoding Functions, SEGA Logo, Game Staff, Conf/Debug modes, End Kiss Sequence, Text Huffman Trees, Textbanks");
	produceSpecificSectionSeven(file,	"07",	0x44000,	0x64000,	2931,	"0x044000..0x064000 : Entity ActScripts, CutScene Scripts, Battle CutScenes, Intro cutscene, End cutscene, Map Setups");
	produceSpecificSectionEight(file,	"08",	0x64000,	0xC8000,	953 ,	"0x064000..0x0C8000 : Map Tiles, Map Palettes, Map Data");
	produceSpecificSectionNine(file,	"09",	0xC8000,	0x100000,	1315,	"0x0C8000..0x100000 : Entity Sprites");
	produceSpecificSectionTen(file,		"10",	0x100000,	0x130000,	432,	"0x100000..0x130000 : Backgrounds, invocation sprites, title screen");
	produceSpecificSectionEleven(file,	"11",	0x130000,	0x180000,	429,	"0x130000..0x180000 : Enemy battle sprites");
	produceSpecificSectionTwelve(file,	"12",	0x180000,	0x1AC000,	871,	"0x180000..0x1AC000 : Ally battle sprites, status anim tiles, battlescene transition tiles, bolt graphics, ally and enemy animations");
	produceSpecificSectionThirteen(file,	"13",	0x1AC000,	0x1B8000,	133,	"0x1AC000..0x1B8000 : Battle setup functions, battle terrains, battle entity setups, end kiss graphics");
	produceSpecificSectionFourteen(file,	"14",	0x1B8000,	0x1C8000,	474,	"0x1B8000..0x1C8000 : Battlescene grounds, weapons, spell graphics, witch screens");
	produceSpecificSectionFifteen(file,	"15",	0x1C8000,	0x1D8000,	1467,	"0x1C8000..0x1D8000 : Portraits");
	produceSection(file,			"16",	0x1D8000,	0x1E0000,	126,	"0x1D8000..0x1E0000 : Icons");
	produceSpecificSectionSeventeen(file,	"17",	0x1E0000,	0x1F0000,	462,	"0x1E0000..0x1F0000 : PCM Banks, YM Instruments, sound driver, char stats, witch screens");
	produceSection(file,			"18",	0x1F0000,	0x200000,	1038,	"0x1F0000..0x200000 : Music banks 1 and 0");
	writestr(file,"\t\tconditionalRomExpand\t\t\t\t; if EXPANDED_ROM = 1, then include next layout file to fill the ROM up to 0x3FFFFF");

	fclose(file);

}


static produceSpecificSectionOne(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x00000%s-0x00%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	
	
	produceAsmScript(file,"code\\romheader",0x0,0x200,"ROM Header");
	produceAsmScript(file,"code\\gameflow\\start\\systeminit",0x200,0x2DE,"System init functions");
	produceAsmScript(file,"code\\gameflow\\start\\gamestart",0x2DE,0x45A,"Start function");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\trap0_soundcommand",0x45A,0x490,"Trap 0 - Sound Command");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\errors",0x490,0x556,"Error interrupts");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\trap5_textbox",0x556,0x57A,"Trap 5 - Text Box");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\trap6_mapscript",0x57A,0x592,"Trap 6 - Map Script");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\hint",0x592,0x594,"Horizontal Interrupt - Triggered at each line display");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\vintengine",0x594,0x14A6,"Vertical Interrupt Engine - Main Technical Engine - Triggered at each frame display");
	produceAsmScript(file,"code\\common\\scripting\\text\\asciinumber",0x14A6,0x150E,"ASCII number function");
	produceAsmScript(file,"code\\common\\tech\\input",0x150E,0x1600,"Input functions");
	produceAsmScript(file,"code\\common\\tech\\randomnumbergenerator",0x1600,0x16BE,"RNG functions");
	produceAsmScript(file,"code\\common\\tech\\sound\\music",0x16BE,0x16D6,"Sound function");
	produceAsmScript(file,"code\\common\\tech\\bytecopy",0x16D6,0x1700,"Byte-copy function");
	produceAsmScript(file,"code\\common\\tech\\interrupts\\trap1-4_flags",0x1700,0x1770,"Trap 1-4 - Flag Functions");
	produceAsmScript(file,"code\\common\\tech\\graphics\\graphics",0x1770,0x20E6,"Graphics functions");
	produceAsmScript(file,"code\\common\\maps\\mapload",0x20E6,0x2F6A,"Map loading functions");
	produceAsmScript(file,"code\\common\\tech\\graphics\\display",0x2F6A,0x31CC,"Display function");
	produceAsmScript(file,"code\\gameflow\\exploration\\exploration",0x31CC,0x4544,"Exploration functions");
	produceAsmScript(file,"code\\gameflow\\battle\\battlemusic",0x4544,0x458E,"Battle music function");
	produceAsmScript(file,"code\\common\\scripting\\map\\bbcs_11_function",0x458E,0x45C2,"Specific to before battle 11 cutscene function");
	produceAsmScript(file,"code\\common\\maps\\camerafunctions",0x45C2,0x4728,"Camera function");
	produceAsmScript(file,"code\\common\\maps\\animations",0x4728,0x47C6,"Map animation function");
	produceAsmScript(file,"code\\common\\windows\\windowengine",0x47C6,0x4C68,"Window engine");
	produceAsmScript(file,"code\\common\\scripting\\entity\\entityscriptengine",0x4C68,0x6260,"Entity script engine");
	produceAsmScript(file,"code\\common\\scripting\\text\\textfunctions",0x6260,0x6E94,"Text functions");
	produceAsmScript(file,"code\\common\\tech\\sram\\sramfunctions",0x6E94,0x7034,"SRAM functions");
	produceAsmScript(file,"code\\specialscreens\\suspend\\witchsuspend",0x7034,0x7094,"Witch suspend function");	
	produceAsmScript(file,"code\\specialscreens\\witchend\\witchendinit",0x7094,0x70D2,"Witch end function");
	produceAsmScript(file,"code\\gameflow\\start\\gameinit",0x70D2,0x7186,"Game init");	
	produceAsmScript(file,"data\\maps\\global\\debugmodemaps",0x7186,0x71C0,"Debug mode maps");	
	produceAsmScript(file,"code\\gameflow\\start\\gameintro",0x71C0,0x7406,"Game intro");	
	produceAsmScript(file,"code\\specialscreens\\witch\\witchactions",0x7406,0x75C4,"Witch actions");	
	produceAsmScript(file,"code\\gameflow\\mainloop",0x75C4,0x75EC,"Main loop");	
	produceAsmScript(file,"code\\common\\maps\\egressinit",0x75EC,0x764E,"Egress map init function");	
	produceAsmScript(file,"code\\gameflow\\start\\basetiles",0x764E,0x769C,"Base tiles loading");	
	produceAsmScript(file,"code\\gameflow\\special\\battletest",0x769C,0x7956,"Battle test functions");	
	produceAsmScript(file,"code\\common\\maps\\mapinit_0",0x7956,0x7988,"Map init functions");	
	produceAsmScript(file,"data\\maps\\global\\flagswitchedmaps",0x7988,0x799C,"Flag-switched maps");	
	produceAsmScript(file,"code\\common\\maps\\getbattle",0x799C,0x7A36,"GetNextBattleOnMap function");	
	produceAsmScriptWithConditionalInclude(file,"code\\common\\maps\\mapcoords",0x7A36,0x7BDE,"Map coords data",1);	
	produceAsmScript(file,"code\\specialscreens\\witch\\witchfunctions",0x7BDE,0x7E3A,"Witch functions");	
	produceAsmScript(file,"code\\gameflow\\special\\configurationmode",0x7E3A,0x7EC6,"Configuration mode function");	
	produceAsmScript(file,"code\\gameflow\\start\\regioncheck",0x7EC6,0x7FA4,"Region check function");	
	produceAsmSectionNoPretty(file,0x7FA4,0x8000);

	fclose(file);
	Message("DONE.\n");	
}	


static produceSpecificSectionTwo(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x00%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmScript(file,"code\\common\\stats\\statsengine",0x8000,0x9A9A,"Character stats engine");	
	produceAsmScript(file,"code\\gameflow\\special\\debugmodebattleactions",0x9A9A,0x9B92,"Debug mode battle actions");	
	produceAsmScript(file,"code\\gameflow\\battle\\battleactionsengine",0x9B92,0xC09A,"Battle actions engine");	
	produceAsmScript(file,"code\\gameflow\\battle\\battlefieldengine",0xC09A,0xDEFC,"Battlefield engine");	
	produceAsmScript(file,"code\\gameflow\\battle\\aiengine",0xDEFC,0xF9C4,"AI engine");	
	produceAsmSection(file,0xF9C4,0x10000);

	fclose(file);
	Message("DONE.\n");	
}	


static produceSpecificSectionThree(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmScript(file,"code\\common\\menus\\menuengine",0x10000,0x16EA6,"Menu engine");	
	produceAsmSection(file,0x16EA6,0x18000);

	fclose(file);
	Message("DONE.\n");	
}	


static produceSpecificSectionFour(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\battlesceneengine",0x18000,0x1FDEB,"Battlescene engine");	
	produceAsmSection(file,0x1FDEB,0x20000);

	fclose(file);
	Message("DONE.\n");	
}	


static produceSpecificSectionFive(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSectionNoPretty(file,0x20000,0x20064);
	produceAsmScript(file,"code\\common\\menus\\shop\\shopactions",0x20064,0x20A02,"Shop functions");	
	produceAsmScript(file,"code\\common\\menus\\church\\churchactions",0x20A02,0x2127E,"Church functions");	
	produceAsmScript(file,"code\\common\\menus\\main\\mainactions",0x2127E,0x21A3A,"Main menu functions");	
	produceAsmScript(file,"code\\common\\menus\\blacksmith\\blacksmithactions",0x21A3A,0x21FD2,"Blacksmith functions");	
	produceAsmScript(file,"code\\common\\menus\\caravan\\caravanactions",0x21FD2,0x229CA,"Caravan functions");	
	produceAsmScript(file,"code\\common\\stats\\items\\itemactions",0x229CA,0x22BC2,"Item functions");	
	produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions_0",0x22BC2,0x2379A,"Battle functions");
	produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_0",0x2379A,0x239AE,"Exploration functions");
	produceAsmScript(file,"data\\stats\\items\\chestgoldamounts",0x239AE,0x239C8,"Chest gold amounts");
	produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_1",0x239C8,0x23A84,"Exploration functions");
	produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions_1",0x23A84,0x257C0,"Battle functions");
	produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_2",0x257C0,0x25A94,"Exploration functions");
	produceAsmScript(file,"code\\gameflow\\battle\\battlevints",0x25A94,0x25AD6,"Battle VInt functions");
	produceAsmScript(file,"code\\gameflow\\exploration\\explorationvints",0x25AD6,0x25BFC,"Exploration VInt functions");
	produceAsmScript(file,"code\\common\\tech\\graphics\\specialsprites",0x25BFC,0x25DF6,"Special Sprites functions");
	produceAsmScriptWithConditionalInclude(file,"code\\common\\tech\\graphics\\specialspritesentries",0x25DF6,0x02784C,"Special Sprites Entries",1);
	produceAsmScript(file,"code\\common\\tech\\graphics\\specialspritesanims",0x02784C,0x2791C,"Special Sprites Animations");
	produceAsmScript(file,"code\\specialscreens\\suspend\\suspend",0x2791C,0x279D8,"Suspend functions");
	produceAsmScript(file,"code\\specialscreens\\witchend\\witchend",0x279D8,0x27D8C,"Witch end functions");
	produceAsmSection(file,0x27D8C,0x28000);

	fclose(file);
	Message("DONE.\n");	
}	
	
	
static produceSpecificSectionSix(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	
			
	produceAsmSectionNoPretty(file,0x28000,0x2804C);
	produceAsmScript(file,"code\\specialscreens\\segalogo\\segalogo",0x2804C,0x29002,"SEGA logo functions");	
	produceAsmSection(file,0x29002,0x2C576);
	produceAsmScript(file,"code\\specialscreens\\endkiss\\endkissfunctions_0",0x2C576,0x2C73C,"End kiss function");	
	produceAsmScript(file,"code\\specialscreens\\title\\loadfont",0x2C73C,0x2C7A0,"Title screen font loading function");	
	produceAsmSection(file,0x2C7A0,0x2E10E);
	produceAsmScript(file,"code\\common\\scripting\\text\\decoding",0x2E10E,0x2E196,"Text decoding functions");	
	produceAsmSection(file,0x2E196,0x2EB34);
	produceAsmScriptWithConditionalInclude(file,"data\\scripting\\text\\entries",0x2EB34,0x4201E,"Textbank entries",1);
	writestr(file,"\t\talignIfExpandedRom $30000\n");
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\grounds\\entries",0x1B8028,0x1B9A9A,"Grounds",2);	
	writestr(file,"\t\talignIfExpandedRom $38000\n");
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\weapons\\entries",0x1B9A9A,0x1BEE38,"Weapons",2);	
	produceAsmScriptWithConditionalInclude(file,"code\\specialscreens\\credits\\gamestaff",0x4201E,0x425ED,"Game Staff",1);
	writestr(file,"\t\talignIfExpandedRom $43800\n");
	produceAsmScriptWithConditionalInclude(file,"code\\common\\maps\\mapcoords",0x7A36,0x7BDE,"Map coords data",2);	
	writestr(file,"\t\talignIfExpandedRom $43C00\n");
	//produceAsmScriptWithConditionalInclude(file,"data\\battles\\global\\battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies",2);
	produceAsmSection(file,0x425ED,0x44000);	

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionSeven(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	auto battleCutscenesFile, mapSetupsFile;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSectionNoPretty(file,0x44000,0x440CC);
	produceAsmScript(file,"code\\common\\scripting\\map\\mapfunctions",0x440CC,0x4428A,"Map functions");
	produceAsmScript(file,"data\\maps\\global\\overworldmaps",0x4428A,0x44298,"Overworld maps");
	produceAsmScript(file,"code\\common\\scripting\\map\\followersfunctions_1",0x44298,0x44338,"Follower functions, part 1");
	produceAsmScript(file,"data\\scripting\\entity\\followers",0x44338,0x4438A,"Follower declarations");
	produceAsmScript(file,"code\\common\\scripting\\map\\followersfunctions_2",0x4438A,0x444A2,"Follower functions, part 2");
	produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_1",0x444A2,0x448C4,"Entity functions");
	//produceAsmScriptWithConditionalInclude(file,"data\\battles\\global\\battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies",1);
	produceAsmScript(file,"data\\battles\\global\\battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies");
	produceAsmScript(file,"data\\scripting\\entity\\eas_battleneutralentities",0x4497A,0x449C6,"Entity actscripts for battle entities which are not force members or enemies");
	produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_2",0x449C6,0x44DE2,"Entity functions");
	produceAsmScript(file,"data\\scripting\\entity\\eas_main",0x44DE2,0x45204,"Main entity actscripts");
	produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_3",0x45204,0x45268,"Entity functions");
	produceAsmScript(file,"code\\common\\scripting\\map\\vehiclefunctions",0x45268,0x45634,"Mapscripts and functions for Caravan and Raft");
	produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_4",0x45634,0x45E44,"Entity functions");
	produceAsmScript(file,"data\\scripting\\entity\\eas_actions",0x45E44,0x46506,"Entity scripts for cutscene actions");
	produceAsmScript(file,"code\\common\\scripting\\map\\mapscriptengine_1",0x46506,0x47102,"Mapscript engine, part 1");
	produceAsmScript(file,"code\\common\\scripting\\map\\debugmapscripts",0x47102,0x4712A,"Debug mapscript function");
	produceAsmScript(file,"code\\common\\scripting\\map\\nullsub_4712A",0x4712A,0x4712C,"Unused empty function");
	produceAsmScript(file,"code\\common\\scripting\\map\\mapscriptengine_2",0x4712C,0x474FC,"Mapscript engine, part 2");
	produceAsmScript(file,"code\\common\\scripting\\map\\mapsetupsfunctions_1",0x474FC,0x478C6,"Map setups functions");
	produceAsmScript(file,"code\\common\\scripting\\map\\resetalliesstats",0x478C6,0x4790E,"CSC 55 function");
	produceAsmScript(file,"code\\common\\scripting\\text\\headquartersquotes",0x4790E,0x47948,"Headquarters quote function");
	produceAsmScript(file,"data\\maps\\entries\\map37\\mapsetups\\s6_47948",0x47948,0x47992,"Map 37 init function");
	produceAsmScript(file,"data\\maps\\entries\\map46\\mapsetups\\s6_47992",0x47992,0x47A4E,"Map 46 init function");
	produceAsmScript(file,"code\\common\\scripting\\map\\ms_empty",0x47A4E,0x47A50,"Empty mapscript");
	produceAsmScript(file,"code\\gameflow\\battle\\beforebattlecutscenesstart",0x47A50,0x47A88,"Before battle cutscenes function start");
	produceAsmScript(file,"data\\battles\\beforebattlecutscenes",0x47A88,0x47AE8,"Before battle cutscenes");
	produceAsmScript(file,"code\\gameflow\\battle\\beforebattlecutscenesend",0x47AE8,0x47AEE,"Before battle cutscenes function end");
	produceAsmScript(file,"code\\gameflow\\battle\\battlestartcutscenesstart",0x47AEE,0x47B2C,"Battle start cutscenes function start");
	produceAsmScript(file,"data\\battles\\battlestartcutscenes",0x47B2C,0x47B8C,"Battle start cutscenes");
	produceAsmScript(file,"code\\gameflow\\battle\\battlestartcutscenesend",0x47B8C,0x47B92,"Battle start cutscenes function end");
	produceAsmScript(file,"code\\gameflow\\battle\\battleendcutscenesstart",0x47B92,0x47BE8,"Battle end cutscenes function start");
	produceAsmScript(file,"data\\battles\\battleendcutscenes",0x47BE8,0x47C48,"Enemy defeated cutscenes");
	produceAsmScript(file,"code\\gameflow\\battle\\battleendcutscenesend",0x47C48,0x47CBC,"Battle end cutscenes function end");
	produceAsmScript(file,"code\\gameflow\\battle\\afterbattlecutscenesstart",0x47CBC,0x47CF4,"After battle cutscenes function start");
	produceAsmScript(file,"data\\battles\\afterbattlecutscenes",0x47CF4,0x47D54,"After battle cutscenes");
	produceAsmScript(file,"code\\gameflow\\battle\\afterbattlecutscenesend",0x47D54,0x47D6A,"After battle cutscenes function end");
	produceAsmScript(file,"data\\battles\\global\\afterbattlejoins",0x47D6A,0x47D9E,"After battle joins (unused)");
	produceAsmScript(file,"code\\gameflow\\battle\\afterenemyleaderdeathpositions",0x47D9E,0x47E82,"After-battlescene listener used to prepare entity positions for end cutscene before the enemy leader dies. Only used in battle 5.");
	produceAsmScript(file,"code\\gameflow\\battle\\regionactivatedcutscenes",0x47E82,0x47EC8,"Region-activated cutscenes functions");
	produceAsmScript(file,"data\\battles\\global\\regionactivatedcutscenes",0x47EC8,0x47EEA,"Region-activated cutscenes data");
	produceAsmScript(file,"code\\common\\tech\\graphics\\flashwhite",0x47EEA,0x47EF8,"Flash white function and script");
	produceAsmScript(file,"data\\scripting\\map\\cs_introendroutine",0x47EF8,0x47F7E,"Subroutine launching intro and end cutscenes");
	produceAsmScript(file,"data\\scripting\\map\\cs_intro1",0x47F7E,0x48380,"Intro cutscene 1");
	produceAsmScript(file,"data\\scripting\\map\\cs_intro2",0x48380,0x48540,"Intro cutscene 2");
	produceAsmScript(file,"data\\scripting\\map\\cs_intro3",0x48540,0x48A78,"Intro cutscene 3");
	produceAsmScript(file,"data\\scripting\\map\\cs_intro4",0x48A78,0x48FE2,"Intro cutscene 4");
	produceAsmScript(file,"data\\scripting\\map\\cs_intro_stormeffect",0x48FE2,0x49058,"Storm Effect");
	produceAsmScript(file,"data\\scripting\\map\\cs_end",0x49058,0x494BC,"End cutscene");

	writestr(file,"\t\tinclude data\\battles\\entries\\battlecutscenesstorage.asm\n");
	battleCutscenesFile = fopen("disasm\\data\\battles\\entries\\battlecutscenesstorage.asm","w");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle01\\cs_beforebattle",0x494BC,0x496DC,"Cutscene before battle 1");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle01\\cs_afterbattle",0x496DC,0x4980E,"Cutscene after battle 1");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle03\\cs_beforebattle",0x4980E,0x4981E,"Cutscene before battle 3");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle04\\cs_beforebattle",0x4981E,0x498EE,"Cutscene before battle 4");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle04\\cs_afterbattle",0x498EE,0x49AB2,"Cutscene after battle 4");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle05\\cs_battleend",0x49AB2,0x49B48,"Enemy defeated cutscene for battle 5");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle05\\cs_afterbattle",0x49B48,0x49BCA,"Cutscene after battle 5");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle06\\cs_beforebattle",0x49BCA,0x49CE2,"Cutscene before battle 6");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle07\\cs_beforebattle",0x49CE2,0x49F7E,"Cutscene before battle 7");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle07\\cs_afterbattle",0x49F7E,0x4A952,"Cutscene after battle 7");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle08\\cs_beforebattle",0x4A952,0x4AA74,"Cutscene before battle 8");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle08\\cs_afterbattle",0x4AA74,0x4ABFE,"Cutscene after battle 8");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle11\\cs_beforebattle",0x4ABFE,0x4ACC8,"Cutscene before battle 11");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle12\\cs_battleend",0x4ACC8,0x4ACEC,"Enemy defeated cutscene for battle 12");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle12\\cs_afterbattle",0x4ACEC,0x4ACF8,"Cutscene after battle 12");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle13\\cs_afterbattle",0x4ACF8,0x4ADA6,"Cutscene after battle 13");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle15\\cs_beforebattle",0x4ADA6,0x4AE72,"Cutscene before battle 15");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle15\\cs_afterbattle",0x4AE72,0x4AFBE,"Cutscene after battle 15");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle16\\cs_beforebattle",0x4AFBE,0x4B1BC,"Cutscene before battle 16");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle16\\cs_afterbattle",0x4B1BC,0x4B1D8,"Cutscene after battle 16");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle18\\cs_beforebattle",0x4B1D8,0x4B2F2,"Cutscene before battle 18");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle18\\cs_afterbattle",0x4B2F2,0x4B6CE,"Cutscene after battle 18");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle20\\cs_afterbattle",0x4B6CE,0x4B790,"Cutscene after battle 20");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle21\\cs_beforebattle",0x4B790,0x4B88C,"Cutscene before battle 21");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle21\\cs_afterbattle",0x4B88C,0x4B958,"Cutscene after battle 21");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle26\\cs_beforebattle",0x4B958,0x4BCAA,"Cutscene before battle 26");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle26\\cs_afterbattle",0x4BCAA,0x4BE6A,"Cutscene after battle 26");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle27\\cs_battlestart",0x4BE6A,0x4BE8C,"Start cutscene for battle 27");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle28\\cs_beforebattle",0x4BE8C,0x4C07C,"Cutscene before battle 28");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle28\\cs_afterbattle",0x4C07C,0x4C3DC,"Cutscene after battle 28");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle29\\cs_beforebattle",0x4C3DC,0x4C5E6,"Cutscene before battle 29");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle30\\cs_beforebattle",0x4C5E6,0x4C6A8,"Cutscene before battle 30");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle30\\cs_afterbattle",0x4C6A8,0x4C994,"Cutscene after battle 30");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle31\\cs_beforebattle",0x4C994,0x4CBE2,"Cutscene before battle 31");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle32\\cs_beforebattle",0x4CBE2,0x4CD10,"Cutscene before battle 32");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle32\\cs_regiontriggered_1",0x4CD10,0x4CDB4,"Region-activated cutscene for battle 32");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle32\\cs_afterbattle",0x4CDB4,0x4CF0C,"Cutscene after battle 32");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle33\\cs_beforebattle",0x4CF0C,0x4D09A,"Cutscene before battle 33");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle33\\cs_afterbattle",0x4D09A,0x4D342,"Cutscene after battle 33");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle34\\cs_beforebattle",0x4D342,0x4D4B6,"Cutscene before battle 34");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle34\\cs_afterbattle",0x4D4B6,0x4D6CE,"Cutscene after battle 34");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle35\\cs_beforebattle",0x4D6CE,0x4D88A,"Cutscene before battle 35");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle36\\cs_beforebattle",0x4D88A,0x4D9A4,"Cutscene before battle 36");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle36\\cs_afterbattle",0x4D9A4,0x4DA66,"Cutscene after battle 36");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle37\\cs_beforebattle",0x4DA66,0x4DB94,"Cutscene before battle 37");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle37\\cs_afterbattle",0x4DB94,0x4DDA4,"Cutscene after battle 37");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle38\\cs_beforebattle",0x4DDA4,0x4DE8C,"Cutscene before battle 38");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle38\\cs_afterbattle",0x4DE8C,0x4E3D2,"Cutscene after battle 38");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle39\\cs_beforebattle",0x4E3D2,0x4E4DC,"Cutscene before battle 39");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle40\\cs_beforebattle",0x4E4DC,0x4E8A8,"Cutscene before battle 40");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle40\\cs_regiontriggered_1",0x4E8A8,0x4E9B2,"Region-activated cutscene 1 for battle 40");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle40\\cs_regiontriggered_2",0x4E9B2,0x4EA94,"Region-activated cutscene 2 for battle 40");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle40\\cs_afterbattle",0x4EA94,0x4ED0E,"Cutscene after battle 40");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle41\\cs_beforebattle",0x4ED0E,0x4ED8E,"Cutscene before battle 41");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle42\\cs_beforebattle",0x4ED8E,0x4EF04,"Cutscene before battle 42");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle42\\cs_afterbattle",0x4EF04,0x4F358,"Cutscene after battle 42");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle43\\cs_battleend",0x4F358,0x4F35E,"Enemy defeated cutscene for battle 43");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle43\\cs_afterbattle",0x4F35E,0x4F47A,"Cutscene after battle 43");
	produceAsmScript(battleCutscenesFile,"data\\battles\\entries\\battle00\\cs_afterbattle",0x4F47A,0x4F48A,"Cutscene after battle 0");
	fclose(battleCutscenesFile);
	
	produceAsmScript(file,"code\\common\\stats\\items\\itemfunctions_s7_0",0x4F48A,0x4F6E2,"Unidentified item functions");

	produceAsmScript(file,"data\\maps\\mapsetups",0x4F6E2,0x4FA70,"Map setups table");

	writestr(file,"\t\t;includeIfVanillaRom data\\maps\\mapsetupsstorage.asm\n");
	writestr(file,"\t\tinclude data\\maps\\mapsetupsstorage.asm\n");
	mapSetupsFile = fopen("disasm\\data\\maps\\mapsetupsstorage.asm","w");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\pt",0x4FA70,0x4FA88,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s1",0x4FA88,0x4FA8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s2",0x4FA8A,0x4FA90,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s3",0x4FA90,0x4FAE0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s4",0x4FAE0,0x4FAE2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s5",0x4FAE2,0x4FAEA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s6",0x4FAEA,0x4FAEC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\pt",0x4FAEC,0x4FB04,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s1",0x4FB04,0x4FB06,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s2",0x4FB06,0x4FB0C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s3",0x4FB0C,0x4FCCE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s4",0x4FCCE,0x4FD42,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s5",0x4FD42,0x4FD4A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s6",0x4FD4A,0x4FD4C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\pt",0x4FD4C,0x4FD64,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s1",0x4FD64,0x4FD66,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s2",0x4FD66,0x4FD6C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s3",0x4FD6C,0x4FD7C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s4",0x4FD7C,0x4FD7E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s5",0x4FD7E,0x4FD86,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s6",0x4FD86,0x4FD88,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\pt",0x4FD88,0x4FDA0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s1",0x4FDA0,0x4FDA2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s3",0x4FDA2,0x4FDD2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s2",0x4FDD2,0x4FDD8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s4",0x4FDD8,0x4FDDA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s5",0x4FDDA,0x4FDE2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s6",0x4FDE2,0x4FDE4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\pt",0x4FDE4,0x4FDFC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s1",0x4FDFC,0x4FDFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s3",0x4FDFE,0x4FE32,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s2",0x4FE32,0x4FE38,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s4",0x4FE38,0x4FE3A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s5",0x4FE3A,0x4FE42,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s6",0x4FE42,0x4FE44,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\pt",0x4FE44,0x4FE5C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s1",0x4FE5C,0x4FE5E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s2",0x4FE5E,0x4FE64,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s3",0x4FE64,0x4FF24,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s4",0x4FF24,0x4FF26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s5",0x4FF26,0x4FF2E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s6",0x4FF2E,0x50312,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\pt",0x50312,0x5032A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s1",0x5032A,0x5032C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s3",0x5032C,0x50332,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s2",0x50332,0x50338,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s4",0x50338,0x5033A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s5",0x5033A,0x50342,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s6",0x50342,0x5096A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\pt",0x5096A,0x50982,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s1",0x50982,0x50984,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s3",0x50984,0x509C6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s2",0x509C6,0x509CC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s4",0x509CC,0x509CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s5",0x509CE,0x509D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s6",0x509D6,0x509D8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\pt",0x509D8,0x509F0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s1",0x509F0,0x509F2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s3",0x509F2,0x509F8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s2",0x509F8,0x509FE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s4",0x509FE,0x50A00,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s5",0x50A00,0x50A08,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s6",0x50A08,0x50A0A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\pt",0x50A0A,0x50A22,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s1",0x50A22,0x50A24,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s3",0x50A24,0x50A3E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s2",0x50A3E,0x50A44,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s4",0x50A44,0x50A46,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s5",0x50A46,0x50A4E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s6",0x50A4E,0x50A50,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\pt",0x50A50,0x50A68,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s1",0x50A68,0x50A6A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s3",0x50A6A,0x50A84,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s2",0x50A84,0x50A8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s4",0x50A8A,0x50A8C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s5",0x50A8C,0x50AE6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s6",0x50AE6,0x50AE8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pt",0x50AE8,0x50B00,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pt_261",0x50B00,0x50B18,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pt_1FA",0x50B18,0x50B30,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1",0x50B30,0x50BCA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_261",0x50BCA,0x50CCA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_1FA",0x50CCA,0x50D4C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3",0x50D4C,0x50EEA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_261",0x50EEA,0x50F0C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_1FA",0x50F0C,0x50F10,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2",0x50F10,0x5105C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_261",0x5105C,0x511CA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_1FA",0x511CA,0x512E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s4",0x512E0,0x51358,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s5",0x51358,0x51360,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_1FA",0x51360,0x51382,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6",0x51382,0x513C0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_261",0x513C0,0x516CC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\pt",0x516CC,0x516E4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s1",0x516E4,0x516F6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s3",0x516F6,0x516FC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s2",0x516FC,0x51702,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s4",0x51702,0x51720,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s5",0x51720,0x51728,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s6",0x51728,0x51912,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pt",0x51912,0x5192A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pt_28A",0x5192A,0x51942,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1",0x51942,0x519C4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_28A",0x519C4,0x51A3E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2",0x51A3E,0x51A82,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2_28A",0x51A82,0x51C22,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s3",0x51C22,0x51C28,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s4",0x51C28,0x51C54,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s5",0x51C54,0x51C5C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s6",0x51C5C,0x51C5E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pt_297",0x51C5E,0x51C76,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pt",0x51C76,0x51C8E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1_297",0x51C8E,0x51D30,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1",0x51D30,0x51DE2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2_297",0x51DE2,0x51E32,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2",0x51E32,0x51EE4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s3",0x51EE4,0x51F2A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s4",0x51F2A,0x51F6E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s5",0x51F6E,0x51F76,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s6",0x51F76,0x52284,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pt",0x52284,0x5229C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pt_1F9",0x5229C,0x522B4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1",0x522B4,0x522DC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1_1F9",0x522DC,0x5231C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s2",0x5231C,0x523E4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3",0x523E4,0x52442,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3_1F9",0x52442,0x52446,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s4",0x52446,0x52448,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s5",0x52448,0x52450,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s6",0x52450,0x52A80,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\pt",0x52A80,0x52A98,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s1",0x52A98,0x52ABA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s2",0x52ABA,0x52B20,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s3",0x52B20,0x52B26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s4",0x52B26,0x52B40,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s5",0x52B40,0x52B48,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s6",0x52B48,0x52B4A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt",0x52B4A,0x52B62,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_1F5",0x52B62,0x52B7A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_261",0x52B7A,0x52B92,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_1FA",0x52B92,0x52BAA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_1FB",0x52BAA,0x52BC2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1",0x52BC2,0x52C2C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_1F5",0x52C2C,0x52C46,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_261",0x52C46,0x52CB0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_1FA",0x52CB0,0x52D8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_1FB",0x52D8A,0x52D94,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3",0x52D94,0x52D98,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_1FA",0x52D98,0x52DA4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_1FB",0x52DA4,0x52E02,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2",0x52E02,0x52F60,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_1F5",0x52F60,0x52F90,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_261",0x52F90,0x5301C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_1FA",0x5301C,0x530BA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_1FB",0x530BA,0x530BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s4",0x530BE,0x530E2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s5",0x530E2,0x530EA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6",0x530EA,0x5310C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_261",0x5310C,0x5311E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_1FA",0x5311E,0x53168,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_1FB",0x53168,0x53634,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pt",0x53634,0x5364C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pt_1F5",0x5364C,0x53664,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pt_261",0x53664,0x5367C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pt_1FA",0x5367C,0x53694,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1",0x53694,0x536D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_1F5",0x536D6,0x53720,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_261",0x53720,0x53760,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_1FA",0x53760,0x53762,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3",0x53762,0x53766,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3_1F5",0x53766,0x537AC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2",0x537AC,0x53830,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_1F5",0x53830,0x538B4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_261",0x538B4,0x53928,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_1FA",0x53928,0x5392C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s4",0x5392C,0x5395E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s5",0x5395E,0x53966,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s6",0x53966,0x53E18,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pt",0x53E18,0x53E30,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pt_1F5",0x53E30,0x53E48,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pt_261",0x53E48,0x53E60,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pt_1FA",0x53E60,0x53E78,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1",0x53E78,0x53E82,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_261",0x53E82,0x53E8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_1FA",0x53E8A,0x53E8C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s3",0x53E8C,0x53E92,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2",0x53E92,0x53E9A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_1F5",0x53E9A,0x53EA2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_261",0x53EA2,0x53EAA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_1FA",0x53EAA,0x53F06,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s4",0x53F06,0x53F08,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s5",0x53F08,0x53F10,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s6",0x53F10,0x53F48,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\pt_1FA",0x53F48,0x53F60,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\pt",0x53F60,0x53F78,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s1_1FA",0x53F78,0x53F90,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s1",0x53F90,0x53F92,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s2",0x53F92,0x53FBA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s3",0x53FBA,0x53FC0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s4",0x53FC0,0x53FC2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s5",0x53FC2,0x53FCA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s6",0x53FCA,0x53FFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\pt",0x53FFE,0x54016,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\pt_264",0x54016,0x5402E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s1",0x5402E,0x54046,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s1_264",0x54046,0x54048,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s3",0x54048,0x5404E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s2",0x5404E,0x54054,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s5",0x54054,0x5405C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s4",0x5405C,0x540A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s6",0x540A6,0x54348,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pt",0x54348,0x54360,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pt_261",0x54360,0x54378,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pt_1FA",0x54378,0x54390,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pt_1FB",0x54390,0x543A8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1",0x543A8,0x543BA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_261",0x543BA,0x543E4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_1FA",0x543E4,0x543EE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_1FB",0x543EE,0x54458,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s3",0x54458,0x5445E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2",0x5445E,0x5446A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_261",0x5446A,0x54482,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_1FA",0x54482,0x5448A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_1FB",0x5448A,0x5455E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s5",0x5455E,0x54566,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s4",0x54566,0x54568,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s6_1FB",0x54568,0x5473E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pt_2BE",0x5473E,0x54756,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pt",0x54756,0x5476E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pt_2BD",0x5476E,0x54786,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1_2BE",0x54786,0x547F8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1",0x547F8,0x5489A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1_2BD",0x5489A,0x5490C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2_2BE",0x5490C,0x54948,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2",0x54948,0x54984,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2_2BD",0x54984,0x54CD0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s3",0x54CD0,0x54D3C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s4_2BE",0x54D3C,0x54D8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s4",0x54D8A,0x54E4C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s5",0x54E4C,0x54E54,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s6",0x54E54,0x5537E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pt",0x5537E,0x55396,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pt_2BD",0x55396,0x553AE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pt_325",0x553AE,0x553C6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1",0x553C6,0x55428,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1_2BD",0x55428,0x554B2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1_325",0x554B2,0x5550C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2",0x5550C,0x55540,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2_2BD",0x55540,0x55584,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2_325",0x55584,0x5579E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s3",0x5579E,0x557EE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s4",0x557EE,0x5580E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s5",0x5580E,0x55816,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s6",0x55816,0x55F8E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\pt_2C4",0x55F8E,0x55FA6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\pt",0x55FA6,0x55FC4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s1_2C4",0x55FC4,0x56036,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s1",0x56036,0x56048,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s2_2C4",0x56048,0x56084,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s2",0x56084,0x561AE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s3",0x561AE,0x561EC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s4",0x561EC,0x562E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s5",0x562E0,0x563A2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s6",0x563A2,0x56636,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\pt",0x56636,0x5664E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\pt_206",0x5664E,0x56666,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s1",0x56666,0x566C0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s1_206",0x566C0,0x56722,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s2",0x56722,0x56856,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s3",0x56856,0x5687A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s4",0x5687A,0x568A4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s5",0x568A4,0x568C4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s6",0x568C4,0x56B84,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\pt",0x56B84,0x56B9C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\pt_2D2",0x56B9C,0x56BB4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s1",0x56BB4,0x56CA6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s1_2D2",0x56CA6,0x56D80,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s2",0x56D80,0x56E9C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s2_2D2",0x56E9C,0x56F8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s3",0x56F8A,0x56FC0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s3_2D2",0x56FC0,0x56FE0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s4",0x56FE0,0x57028,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s5",0x57028,0x57030,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s6",0x57030,0x5708E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s6_2D2",0x5708E,0x579CA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\pt",0x579CA,0x579E2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s1",0x579E2,0x57A0C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s2",0x57A0C,0x57A68,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s3",0x57A68,0x57A88,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s4",0x57A88,0x57AA0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s5",0x57AA0,0x57AA8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s6",0x57AA8,0x57CCC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\pt",0x57CCC,0x57CE4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s1",0x57CE4,0x57CEE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s2",0x57CEE,0x57CF4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s3",0x57CF4,0x57CFA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s4",0x57CFA,0x57CFC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s5",0x57CFC,0x57D04,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s6",0x57D04,0x57E36,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pt",0x57E36,0x57E4E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pt_2C6",0x57E4E,0x57E66,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pt_31F",0x57E66,0x57E7E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pt_201",0x57E7E,0x57E96,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1",0x57E96,0x57F08,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_2C6",0x57F08,0x57F7A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_31F",0x57F7A,0x57FB4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_201",0x57FB4,0x5801E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s2",0x5801E,0x5814C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s2_201",0x5814C,0x5822A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s3",0x5822A,0x582AC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s4",0x582AC,0x582D8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s5",0x582D8,0x582E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s6",0x582E0,0x58E18,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\pt",0x58E18,0x58E30,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\pt_1CA",0x58E30,0x58E48,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s3",0x58E48,0x58EBA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s2",0x58EBA,0x58F0E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s1",0x58F0E,0x58F10,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s4",0x58F10,0x58F12,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s6",0x58F12,0x58F2A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s1_1CA",0x58F2A,0x58F3C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s2_1CA",0x58F3C,0x58F4C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s3_1CA",0x58F4C,0x58F9A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s6_1CA",0x58F9A,0x58F9C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s5",0x58F9C,0x592E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\pt",0x592E0,0x592F8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\pt_20A",0x592F8,0x59310,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s1",0x59310,0x59402,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s1_20A",0x59402,0x59474,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s2",0x59474,0x595DE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s3",0x595DE,0x59602,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s4",0x59602,0x59604,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s5",0x59604,0x5962E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s6",0x5962E,0x59AC0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\pt",0x59AC0,0x59AD8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\pt_2FA",0x59AD8,0x59AF0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s1",0x59AF0,0x59B22,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s1_2FA",0x59B22,0x59B44,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s2",0x59B44,0x59BA8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s2_2FA",0x59BA8,0x59BD2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s3",0x59BD2,0x59BD8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s4",0x59BD8,0x59BFC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s5",0x59BFC,0x59C04,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s6",0x59C04,0x59C06,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\pt",0x59C06,0x59C1E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s1",0x59C1E,0x59C20,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s2",0x59C20,0x59C26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s3",0x59C26,0x59C2C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s4",0x59C2C,0x59C2E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s5",0x59C2E,0x59C36,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s6",0x59C36,0x59D08,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\pt",0x59D08,0x59D20,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s1",0x59D20,0x59D6A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s2",0x59D6A,0x59DB6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s3",0x59DB6,0x59DD2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s4",0x59DD2,0x59DD4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s5",0x59DD4,0x59DDC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s6",0x59DDC,0x59F42,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\pt",0x59F42,0x59F5A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\pt_20B",0x59F5A,0x59F72,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s1",0x59F72,0x59F8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s1_20B",0x59F8A,0x59F8C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s2",0x59F8C,0x59F92,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s3",0x59F92,0x59FAC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s4",0x59FAC,0x59FAE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s5",0x59FAE,0x59FB6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s6",0x59FB6,0x5A09E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\pt",0x5A09E,0x5A0B6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s1",0x5A0B6,0x5A0F0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s2",0x5A0F0,0x5A14E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s3",0x5A14E,0x5A154,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s4",0x5A154,0x5A16C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s5",0x5A16C,0x5A174,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s6",0x5A174,0x5A176,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pt",0x5A176,0x5A18E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pt_311",0x5A18E,0x5A1A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pt_2F9",0x5A1A6,0x5A1BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1",0x5A1BE,0x5A1E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1_311",0x5A1E0,0x5A20A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1_2F9",0x5A20A,0x5A20C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s2",0x5A20C,0x5A2C2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s3",0x5A2C2,0x5A2E8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s4",0x5A2E8,0x5A2EA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s5",0x5A2EA,0x5A2F2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s6",0x5A2F2,0x5A646,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pt",0x5A646,0x5A65E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pt_20B",0x5A65E,0x5A676,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pt_310",0x5A676,0x5A68E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pt_312",0x5A68E,0x5A6A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1",0x5A6A6,0x5A6D8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_20B",0x5A6D8,0x5A712,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_310",0x5A712,0x5A74C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_312",0x5A74C,0x5A766,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s2",0x5A766,0x5AA8A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s3",0x5AA8A,0x5AAD8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s4",0x5AAD8,0x5AB74,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s5",0x5AB74,0x5AB7C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s6",0x5AB7C,0x5AC56,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s6_312",0x5AC56,0x5B5B6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\pt",0x5B5B6,0x5B5CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\pt_310",0x5B5CE,0x5B5E6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s1",0x5B5E6,0x5B68E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s1_310",0x5B68E,0x5B690,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s2",0x5B690,0x5B696,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s3",0x5B696,0x5B6B4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s4",0x5B6B4,0x5B6B6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s5",0x5B6B6,0x5B6BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s6",0x5B6BE,0x5BFEE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\pt",0x5BFEE,0x5C006,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s1",0x5C006,0x5C0F8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s2",0x5C0F8,0x5C264,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s3",0x5C264,0x5C26A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s4",0x5C26A,0x5C26C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s5",0x5C26C,0x5C274,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s6",0x5C274,0x5C27C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\pt",0x5C27C,0x5C294,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\pt_208",0x5C294,0x5C2AC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s1",0x5C2AC,0x5C2CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s1_208",0x5C2CE,0x5C2D0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s2",0x5C2D0,0x5C2D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s3",0x5C2D6,0x5C3C0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s4",0x5C3C0,0x5C3C2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s5",0x5C3C2,0x5C3CA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s6",0x5C3CA,0x5C454,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\pt",0x5C454,0x5C46C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\pt_200",0x5C46C,0x5C484,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s1",0x5C484,0x5C4A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s1_200",0x5C4A6,0x5C4A8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s2",0x5C4A8,0x5C4AA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s3",0x5C4AA,0x5C4CC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s4",0x5C4CC,0x5C4CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s5",0x5C4CE,0x5C4D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s6",0x5C4D6,0x5C638,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\pt_2D9",0x5C638,0x5C650,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\pt",0x5C650,0x5C668,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s1",0x5C668,0x5C670,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s1_2D9",0x5C670,0x5C672,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s2",0x5C672,0x5C696,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s3",0x5C696,0x5C6BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s4",0x5C6BE,0x5C6C0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s5",0x5C6C0,0x5C6C8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s6",0x5C6C8,0x5C76A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\pt",0x5C76A,0x5C782,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\pt_4D",0x5C782,0x5C79A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s1",0x5C79A,0x5C7AC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s1_4D",0x5C7AC,0x5C7B6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s2",0x5C7B6,0x5C820,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s3",0x5C820,0x5C86A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s4",0x5C86A,0x5C86C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s5",0x5C86C,0x5C874,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s6",0x5C874,0x5C950,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\pt_1D",0x5C950,0x5C968,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\pt",0x5C968,0x5C980,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s1",0x5C980,0x5C988,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s1_1D",0x5C988,0x5C98A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s2",0x5C98A,0x5C9E2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s3",0x5C9E2,0x5CA24,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s4",0x5CA24,0x5CA26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s5",0x5CA26,0x5CA50,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s6",0x5CA50,0x5CDFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\pt",0x5CDFE,0x5CE16,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\pt_212",0x5CE16,0x5CE2E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s1",0x5CE2E,0x5CE90,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s1_212",0x5CE90,0x5CEEA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s2",0x5CEEA,0x5CF9E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s2_212",0x5CF9E,0x5CFFA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s3",0x5CFFA,0x5CFFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s3_212",0x5CFFE,0x5D020,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s4",0x5D020,0x5D044,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s5",0x5D044,0x5D04C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s6",0x5D04C,0x5D1CA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\pt",0x5D1CA,0x5D1E2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s1",0x5D1E2,0x5D224,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s2",0x5D224,0x5D33A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s3",0x5D33A,0x5D340,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s4",0x5D340,0x5D394,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s5",0x5D394,0x5D39C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s6",0x5D39C,0x5D40E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\pt",0x5D40E,0x5D426,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\pt_33E",0x5D426,0x5D43E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s1",0x5D43E,0x5D440,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s1_33E",0x5D440,0x5D49A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s2",0x5D49A,0x5D49E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s2_33E",0x5D49E,0x5D552,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s3",0x5D552,0x5D556,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s3_33E",0x5D556,0x5D574,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s4",0x5D574,0x5D60E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s5",0x5D60E,0x5D614,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s5_33E",0x5D614,0x5D61C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s6",0x5D61C,0x5D61E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s6_33E",0x5D61E,0x5D756,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\pt",0x5D756,0x5D76E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\pt_212",0x5D76E,0x5D786,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s1",0x5D786,0x5D7F0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s1_212",0x5D7F0,0x5D84A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s2",0x5D84A,0x5D924,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s2_212",0x5D924,0x5D9C0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s3",0x5D9C0,0x5D9C6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s4",0x5D9C6,0x5DA0E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s5",0x5DA0E,0x5DA16,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s6",0x5DA16,0x5DAE4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\pt",0x5DAE4,0x5DAFC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s1",0x5DAFC,0x5DB76,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s2",0x5DB76,0x5DCD0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s3",0x5DCD0,0x5DD26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s4",0x5DD26,0x5DD50,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s5",0x5DD50,0x5DD58,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s6",0x5DD58,0x5DF84,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\pt",0x5DF84,0x5DF9C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\pt_33E",0x5DF9C,0x5DFB4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s1",0x5DFB4,0x5DFFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s1_33E",0x5DFFE,0x5E038,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s2",0x5E038,0x5E0B2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s3",0x5E0B2,0x5E0CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s3_33E",0x5E0CE,0x5E0D4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s4",0x5E0D4,0x5E0D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s5",0x5E0D6,0x5E0DE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s6",0x5E0DE,0x5E0E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s6_33E",0x5E0E0,0x5E22C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\pt",0x5E22C,0x5E244,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s1",0x5E244,0x5E246,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s2",0x5E246,0x5E248,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s3",0x5E248,0x5E25E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s4",0x5E25E,0x5E260,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s5",0x5E260,0x5E268,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s6",0x5E268,0x5E37C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\pt",0x5E37C,0x5E394,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s1",0x5E394,0x5E39E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s2",0x5E39E,0x5E3A4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s3",0x5E3A4,0x5E61E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s4",0x5E61E,0x5E620,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s5",0x5E620,0x5E628,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s6",0x5E628,0x5E62A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\pt",0x5E62A,0x5E642,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s1",0x5E642,0x5E694,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s2",0x5E694,0x5E720,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s3",0x5E720,0x5E726,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s4",0x5E726,0x5E758,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s5",0x5E758,0x5E760,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s6",0x5E760,0x5E86C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\pt",0x5E86C,0x5E884,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\pt_212",0x5E884,0x5E89C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s1",0x5E89C,0x5E8EE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s1_212",0x5E8EE,0x5E938,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s2",0x5E938,0x5E9C8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s2_212",0x5E9C8,0x5EA20,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s3",0x5EA20,0x5EA26,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s4",0x5EA26,0x5EA62,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s4_212",0x5EA62,0x5EA9E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s5",0x5EA9E,0x5EAA6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s6",0x5EAA6,0x5EAA8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\pt",0x5EAA8,0x5EAC0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s1",0x5EAC0,0x5EAC2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s2",0x5EAC2,0x5EAC8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s3",0x5EAC8,0x5EACE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s4",0x5EACE,0x5EAD0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s5",0x5EAD0,0x5EAD8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s6",0x5EAD8,0x5F34C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\pt",0x5F34C,0x5F364,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s1",0x5F364,0x5F366,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s2",0x5F366,0x5F36C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s3",0x5F36C,0x5F396,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s4",0x5F396,0x5F398,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s5",0x5F398,0x5F3A0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s6",0x5F3A0,0x5F3E8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\pt",0x5F3E8,0x5F400,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s1",0x5F400,0x5F402,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s2",0x5F402,0x5F408,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s3",0x5F408,0x5F40E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s4",0x5F40E,0x5F46C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s5",0x5F46C,0x5F4A0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s6",0x5F4A0,0x5F630,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\pt",0x5F630,0x5F660,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\pt_3E7",0x5F660,0x5F678,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s1",0x5F678,0x5F772,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s1_3E7",0x5F772,0x5F86C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s2",0x5F86C,0x5F9D2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s2_3E7",0x5F9D2,0x5FA22,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s3",0x5FA22,0x5FA28,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s4",0x5FA28,0x5FA2A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s5",0x5FA2A,0x5FA88,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s6",0x5FA88,0x5FAA4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s6_3E7",0x5FAA4,0x5FDE4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\pt",0x5FDE4,0x5FDFC,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s1",0x5FDFC,0x5FDFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s2",0x5FDFE,0x5FE04,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s3",0x5FE04,0x5FE24,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s4",0x5FE24,0x5FE90,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s5",0x5FE90,0x5FE98,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s6",0x5FE98,0x5FF62,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\pt",0x5FF62,0x5FF7A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s1",0x5FF7A,0x60024,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s2",0x60024,0x60060,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s3",0x60060,0x60078,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s4",0x60078,0x60090,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s5",0x60090,0x60098,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s6",0x60098,0x603AE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pt_212",0x603AE,0x603C6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pt_1C",0x603C6,0x603DE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_212",0x603DE,0x60410,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_1C",0x60410,0x6043A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2_212",0x6043A,0x604C8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s3_212",0x604C8,0x60548,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s4_212",0x60548,0x60606,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s5_212",0x60606,0x6061E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s6_212",0x6061E,0x60FAE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pt_212",0x60FAE,0x60FC6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1_212",0x60FC6,0x61058,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2_212",0x61058,0x6114E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s3_212",0x6114E,0x61154,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s4_212",0x61154,0x6119C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s5_212",0x6119C,0x611A4,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s6_212",0x611A4,0x611A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pt_212",0x611A6,0x611BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1_212",0x611BE,0x611E0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s2_212",0x611E0,0x61208,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3_212",0x61208,0x6120E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s4_212",0x6120E,0x61210,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s5_212",0x61210,0x61218,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s6_212",0x61218,0x6121A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\pt_212",0x6121A,0x61232,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s1_212",0x61232,0x61254,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s2_212",0x61254,0x6125A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s3_212",0x6125A,0x61278,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s4_212",0x61278,0x61290,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s5_212",0x61290,0x61298,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s6_212",0x61298,0x61488,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\pt",0x61488,0x614A0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s1",0x614A0,0x614AA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s2",0x614AA,0x614D6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s3",0x614D6,0x614FE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s4",0x614FE,0x61500,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s5",0x61500,0x61508,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s6",0x61508,0x6153E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\pt_21F",0x6153E,0x61556,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s1_21F",0x61556,0x615B0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s2_21F",0x615B0,0x615B6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s3_21F",0x615B6,0x615CE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s4_21F",0x615CE,0x615D0,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s5_21F",0x615D0,0x615D8,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s6_21F",0x615D8,0x626A6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pt_21F",0x626A6,0x626BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_21F",0x626BE,0x62738,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_21F",0x62738,0x62820,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_21F",0x62820,0x62846,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s4_21F",0x62846,0x628BE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s5_21F",0x628BE,0x628C6,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_21F",0x628C6,0x6299A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_21F",0x6299A,0x629B2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pt_3D6",0x629B2,0x629CA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_21F",0x629CA,0x62A6C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_3D6",0x62A6C,0x62AFE,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_21F",0x62AFE,0x62BCA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_3D6",0x62BCA,0x62C6C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_21F",0x62C6C,0x62C72,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s4_21F",0x62C72,0x62C96,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s5_21F",0x62C96,0x62C9E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_21F",0x62C9E,0x631EA,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pt_21F",0x631EA,0x63202,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_21F",0x63202,0x63234,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_21F",0x63234,0x6329A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3_21F",0x6329A,0x63364,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s4_21F",0x63364,0x6339A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s5_21F",0x6339A,0x633A2,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s6_21F",0x633A2,0x6343C,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pt_21F",0x6343C,0x63454,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_21F",0x63454,0x6345E,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_21F",0x6345E,0x63472,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s3_21F",0x63472,0x63478,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s4_21F",0x63478,0x6347A,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s5_21F",0x6347A,0x63482,"");
	produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s6_21F",0x63482,0x6348C,"");
	fclose(mapSetupsFile);

	produceAsmSection(file,0x6348C,0x64000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionEight(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x64000,0x6400C);
	produceAsmScript(file,"data\\graphics\\maps\\maptilesets\\entries",0x6400C,0x9494A,"Map Tilesets");	
	writestr(file,"\t\talignIfExpandedRom $C7000\n");
	produceAsmScript(file,"data\\graphics\\maps\\mappalettes\\entries",0x9494A,0x94B8A,"Map palettes");
	produceAsmScriptWithConditionalInclude(file,"data\\maps\\entries",0x94B8A,0xC7ECC,"Map entries",1);
	produceAsmSection(file,0xC7ECC,0xC8000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionNine(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x0%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\mapsprites\\entries",0xC8000,0xFFC48,"Map sprites",1);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\spells\\entries",0x1BEEE0,0x1C46C2,"Spell Graphics",2);	
	writestr(file,"\t\talignIfExpandedRom $E0000\n");			
	produceAsmScriptWithConditionalInclude(file,"data\\battles\\terrainentries",0x1AD104,0x1B120A,"Battle terrain data",2);	
	produceAsmSection(file,0xFFC48,0x100000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionTen(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x100000,0x100008);
	produceAsmScript(file,"code\\specialscreens\\title\\title",0x100008,0x1002BE,"Title screen functions");	
	produceAsmScriptWithConditionalInclude(file,"code\\specialscreens\\title\\graphics",0x1002BE,0x101EE0,"Title Screen Graphics",1);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\backgrounds\\entries",0x101EE0,0x12A2F8,"Backgrounds",1);	
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\portraits\\entries",0x1C8004,0x1D7E26,"Portraits",2);	
	produceAsmScript(file,"data\\graphics\\battles\\spells\\invocations\\entries",0x12A2F8,0x12FADE,"Invocation sprites");	
	produceAsmSection(file,0x12FADE,0x130000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionEleven(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x130000,0x130004);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\battlesprites\\enemies\\entries",0x130004,0x17FE4F,"Enemy battle sprites",1);
	writestr(file,"\t\t;includeIfExpandedRom data\\maps\\mapsetupsstorage.asm\n");	
	produceAsmSection(file,0x17FE4F,0x180000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionTwelve(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x180000,0x18001C);
	produceAsmScriptWithConditionalInclude(file,"data\\scripting\\text\\entries",0x2EB34,0x4201E,"Textbank entries",2);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\battlesprites\\allies\\entries",0x18001C,0x1AA16E,"Ally battlesprites",1);	
	produceAsmSection(file,0x1AA16E,0x1AAC3A);		
	produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\allies\\animations\\entries",0x1AAC3A,0x1AB79E,"Ally animations");	
	produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\enemies\\animations\\entries",0x1AB79E,0x1ABE52,"Enemy animations");	
	produceAsmSection(file,0x1ABE52,0x1AC000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionThirteen(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_0",0x1AC000,0x1AC068,"Jump interface for section functions");	
	produceAsmScript(file,"code\\common\\scripting\\endcredits",0x1AC068,0x1AC29C,"Ending credits functions");
	produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_1",0x1AC29C,0x1AD104,"Battle init, terrain, AI stuff to split more properly");			
	produceAsmScriptWithConditionalInclude(file,"data\\battles\\terrainentries",0x1AD104,0x1B120A,"Battle terrain data",1);	
	produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_2",0x1B120A,0x1B1A66,"Battle init, terrain, AI stuff to split more properly");	
	produceAsmSection(file,0x1B1A66,0x1B30EE);		
	produceAsmScriptWithConditionalInclude(file,"data\\battles\\spritesetentries",0x1B30EE,0x1B6DB0,"Battle sprite sets",1);	
	produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_3",0x1B6DB0,0x1B6DDA,"Data related to UpgradeUnitIdx function");	
	produceAsmScriptWithConditionalInclude(file,"code\\specialscreens\\endkiss\\graphics",0x1B6DDA,0x1B7C9A,"End Kiss Graphics",1);
	produceAsmSection(file,0x1B7C9A,0x1B8000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionFourteen(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x1B8000,0x1B8028);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\grounds\\entries",0x1B8028,0x1B9A9A,"Grounds",1);	
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\weapons\\entries",0x1B9A9A,0x1BEE38,"Weapons",1);	
	produceAsmSection(file,0x1BEE38,0x1BEEE0);		
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\battles\\spells\\entries",0x1BEEE0,0x1C46C2,"Spell Graphics",1);
	produceAsmScript(file,"code\\specialscreens\\witch\\graphics",0x1C46C2,0x1C67C4,"Witch Screen");
	produceAsmScript(file,"code\\specialscreens\\witchend\\graphics",0x1C67C4,0x1C7F7C,"Witch End Screen");	
	produceAsmSection(file,0x1C7F7C,0x1C8000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionFifteen(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x1C8000,0x1C8004);
	produceAsmScriptWithConditionalInclude(file,"data\\graphics\\portraits\\entries",0x1C8004,0x1D7E26,"Portraits",1);	
	produceAsmSection(file,0x1D7E26,0x1D8000);

	fclose(file);
	Message("DONE.\n");	
}


static produceSpecificSectionSeventeen(mainFile,sectionName,start,end,fs,sectionComment){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	

	produceAsmSection(file,0x1E0000,0x1EE270);
	produceAsmScript(file,"data\\stats\\allies\\stats\\entries",0x1EE270,0x1EE7D0,"Ally stats");	
	produceAsmSection(file,0x1EE7D0,0x1EE930);
	produceAsmScriptWithConditionalInclude(file,"code\\specialscreens\\jewelend\\graphics",0x1EE930,0x1EF4BA,"Jewel End Graphics",1);	
	produceAsmScriptWithConditionalInclude(file,"code\\specialscreens\\suspend\\graphics",0x1EF4BA,0x1EF5A6,"Suspend String Graphics",1);	
	produceAsmSection(file,0x1EF5A6,0x1F0000);

	fclose(file);
	Message("DONE.\n");	
}

static produceSection(mainFile,sectionName,start,end,fs,sectionComment){
	produceSectionWithPrettyPrintParam(mainFile,sectionName,start,end,fs,sectionComment,1);
}


static produceSectionWithPrettyPrintParam(mainFile,sectionName,start,end,fs,sectionComment,prettyPrint){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
	Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	//form("0x%s..0x%s %s",ltoa(start,16),ltoa(end,16),sectionComment)
	action = 1;
	writestr(mainFile,form("\t\tinclude \"%s\"\t\t; %s\n",fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
	writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));	
	ea = start;
	while(ea<end){
		itemSize = ItemSize(ea);
		if(GetFunctionAttr(ea,FUNCATTR_START)==ea){	
			writeFunctionHeader(file,ea,prettyPrint);
		}
		else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){	
			writeFChunkHeader(file,ea,prettyPrint);
		}		
		writeItem(file,ea);
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea,prettyPrint);
		}		
		else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFChunkFooter(file,ea,prettyPrint);
		}				
		ea = ea + itemSize;
	}
	fclose(file);
	Message("DONE.\n");	

}

static produceAsmScript(mainFile,sectionName,start,end,sectionComment){
	
	produceAsmScriptWithConditionalInclude(mainFile,sectionName,start,end,sectionComment,0);

}


static produceAsmScriptWithConditionalInclude(mainFile,sectionName,start,end,sectionComment,conditionalIncludeType){
	auto ea,itemSize,action,currentLine,previousLine,fileName,file;
	auto output, include, name, indent, comment, commentEx, commentIndent, offsets;
	fileName = form("%s.asm",sectionName);
	Message(form("Writing assembly script section %s to %s (%s) ... ",sectionName,fileName,sectionComment));	
	//form("0x%s..0x%s %s",ltoa(start,16),ltoa(end,16),sectionComment)
	action = 1;
	if(conditionalIncludeType==1){
		include = "includeIfVanillaRom";
	}else if(conditionalIncludeType==2){
		include = "includeIfExpandedRom";
	}else{
		include = "include";
	}
	writestr(mainFile,form("\t\t%s \"%s\"\t\t; %s\n",include,fileName,sectionComment));
	file = fopen(form("disasm\\%s",fileName),"w");
	offsets = form("0x%s..0x%s",ltoa(start,16),ltoa(end,16));
	writestr(file,form("\n; ASM FILE %s.asm :\n; %s : %s\n",sectionName,offsets,sectionComment));
	produceAsmSection(file,start,end);
	fclose(file);
	Message("DONE.\n");	

}

static produceAsmSection(file,start,end){
	produceAsmSectionWithPrettyParam(file,start,end,1);
}

static produceAsmSectionNoPretty(file,start,end){
	produceAsmSectionWithPrettyParam(file,start,end,0);
}

static produceAsmSectionWithPrettyParam(file,start,end,prettyWriteFunctions){
	auto ea,itemSize;
	ea = start;
	while(ea<end){
		itemSize = ItemSize(ea);
		if(GetFunctionAttr(ea,FUNCATTR_START)==ea){	
			writeFunctionHeader(file,ea,prettyWriteFunctions);
		}
		else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){	
			writeFChunkHeader(file,ea,prettyWriteFunctions);
		}		
		writeItemWithPrettyPrintParam(file,ea,prettyWriteFunctions);
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea,prettyWriteFunctions);
		}		
		else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFChunkFooter(file,ea,prettyWriteFunctions);
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
	writestr(file,"   include \"layout\\sf2-00-romlayout.asm\"\n");
}

static writeFooter(file){
	writestr(file,"		END");
}

static writeFunctionHeader(file, ea, prettyWriteFunctions){
	auto funcCmt;
	if(prettyWriteFunctions!=0){
		writestr(file,"\n; =============== S U B R O U T I N E =======================================\n\n");
	}
	funcCmt = GetFunctionCmt(ea,0);
	if(funcCmt!=""){
		writestr(file,form("; %s\n",funcCmt));
		if(prettyWriteFunctions!=0){
			writestr(file,"\n");
		}
	}
	else{
		funcCmt = GetFunctionCmt(ea,1);
		if(funcCmt!=""){
			funcCmt = formatFuncRptCmt(funcCmt);
			writestr(file,form("; %s\n",funcCmt));
			if(prettyWriteFunctions!=0){
				writestr(file,"\n");
			}			
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

static writeFunctionFooter(file, ea,prettyWriteFunctions){
	auto funcName;
	funcName = GetFunctionName(ea);
	if(prettyWriteFunctions!=0){
		writestr(file,form("\n	; End of function %s\n\n",funcName));
	}
}

static writeItem(file,ea){
	writeItemWithPrettyPrintParam(file,ea,1);
}

static writeItemWithPrettyPrintParam(file,ea,prettyPrint){
	auto name,tabLength,ln,indent,disasm,cmtIdx,commentIndent,comment,commentEx,i,line,lineA,lineB,type,output;
	tabLength = 8;
	indent = "\t\t";
	commentIndent = "\t\t\t\t";
	name = GetTrueName(ea);
	if(name==""){
		name = Name(ea);
	}
	if(name!=""){
		name=form("%s:",name);
		if(GetFunctionAttr(ea,FUNCATTR_START)!=-1){
			if(prettyPrint!=0){
				ln = "\n";
			}else{
				ln = "";
			}
			name = form("%s%s%s",name,ln,indent);
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
	lineA = LineA(ea,0);
	disasm = GetDisasm(ea);
	cmtIdx = strstr(disasm,";");
	lineB = LineB(ea,0);
	if(lineA!=""){
		lineA = form("%s\n",lineA);
	}
	if(lineB!=""){
		lineB = form("%s\n",lineB);
	}	
	if(cmtIdx!=-1){
		disasm = substr(disasm,0,cmtIdx);
	}
	if(comment!=""){
		comment = form("; %s",comment);
	}
	if(strlen(name)>(strlen(indent)*tabLength)){
		name = form("%s\n%s",name,indent);
	}
	if(strstr(lineA,"\n")!=-1){
		lineA = form("%s%s",lineA,indent);
	}
	if(strlen(disasm)>(strlen(commentIndent)*tabLength)&&comment!=""){
		disasm = form("%s\n%s%s",disasm,indent,commentIndent);
	}
	//Message(form("\nname=%s,lineA=%s,disasm=%s,comment=%s,lineB=%s",name,lineA,disasm,comment,lineB));		
	output = form("%s%s%s%s\n%s",name,lineA,disasm,comment,lineB);
	writestr(file,output);
}

static writeFChunkHeader(file,ea,prettyWriteFunctions){
	auto text,functionName;
	text = "; START OF FUNCTION CHUNK FOR ";
	functionName = GetFunctionName(ea);
	writestr(file,form("\n%s%s\n\n",text,functionName));
}

static writeFChunkFooter(file,ea,prettyWriteFunctions){
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
		result = form("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t; %s",before,formatRptCmt(after));
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