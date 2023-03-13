
/*
 *  Attempt at producing ASM file from IDC script 
 *  instead of IDA's function, for more flexibility.
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
    writestr(file,"align:    macro\n");
    writestr(file,"    if (narg=1)\n");
    writestr(file,"    dcb.b \\1-(*%\\1),$FF\n");
    writestr(file,"    else\n");
    writestr(file,"    dcb.b \\1-(*%\\1),\\2\n");
    writestr(file,"    endc\n");
    writestr(file,"    endm\n");
    writestr(file,"\n");
    fclose(file);    
    Message("DONE.");    
}
*/

static produceEnums(){
    auto i,j,enumQty,id,enumName,bmask,enumCount,constant,constId,output,file;
    file = fopen("disasm\\sf2enums.asm","w");
    Message("\nWriting Enums to sf2enums.asm ...");
    enumQty = GetEnumQty();
    for(i=0;i<enumQty;i++){
        id = GetnEnum(i);
        enumName = GetEnumName(id);
        //Message("\n\n; ---------------------------------------------------------------------------\n");
        writestr(file,"\n\n; ---------------------------------------------------------------------------\n");
        //Message(form("\n; enum %s",enumName));
        bmask = GetFirstBmask(id);
        if(bmask==-1){writestr(file,form("\n; enum %s",enumName));}
        else{writestr(file,form("\n; enum %s (bitfield)",enumName));}
        // Iterate bitmasks
        while(bmask!=0){
            enumCount = GetEnumSize(id);
            constant = GetFirstConst(id,bmask);
            // Iterate constants
            while(enumCount>0){
                j=0;
                constId = GetConstEx(id,constant,j,bmask);
                while(constId != -1){
                    //output = form("\n%s: equ $%s",GetConstName(constId),ltoa(constant,16));
                    output = conditionalEnumOutput(id,enumName,enumCount,constant,constId);
                    //Message(output);
                    writestr(file,output);
                    j++;
                    constId = GetConstEx(id,constant,j,bmask);
                }
                constant = GetNextConst(id,constant,bmask);
                enumCount--;
            }
            // Break out of loop after iterating last bitmask
            if(bmask==-1){break;}
            bmask = GetNextBmask(id,bmask);
        }
    }
    fclose(file);
    Message("DONE.");
}

static conditionalEnumOutput(id,enumName,enumCount,constant,constId){
    auto i,j,constName,constStr,enumMember,output;
    constName = GetConstName(constId);
    //constStr = ltoa(constant,16);
    
    output = form("\n%s", formEnumMemberWithHex(constName,ltoa(constant,16)));
    
    return output;
    
}

static formEnumMember(constName,constant) {
    auto enumMember;
    enumMember = formEnumMemberEx(constName,constant,0);
    return enumMember;
}

static formEnumMemberWithHex(constName,constant) {
    auto enumMember;
    enumMember = formEnumMemberEx(constName,constant,1);
    return enumMember;
}

static formEnumMemberEx(constName,constant,hex) {
    auto operand,enumMember;
    if(hex==1){operand = "$";}
    else{operand = "";}
    enumMember = form("%s: equ %s%s", constName, operand, constant);
    return enumMember;
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

    produceSpecificSectionOne(file,       "01", 0x0,      0x8000,   90,   "0x000000..0x008000 : Technical Layer, Low Level Game Engine, Map/Exploration Engine, Entity Script Commands, Witch Functions");
    produceSpecificSectionTwo(file,       "02", 0x8000,   0x10000,  121,  "0x008000..0x010000 : Character Stats Engine, Battle engine, Item Effects Engine, Enemy AI Engine");
    produceSpecificSectionThree(file,     "03", 0x10000,  0x18000,  38,   "0x010000..0x018000 : Menu Engine");
    produceSpecificSectionFour(file,      "04", 0x18000,  0x20000,  532,  "0x018000..0x020000 : BattleScene Engine");
    produceSpecificSectionFive(file,      "05", 0x20000,  0x28000,  626,  "0x020000..0x028000 : Battle Engine, Special Sprites, Shop/Church/Blacksmith/Caravan engine, Battle Engine, Exploration Engine, Special Sprites");
    produceSpecificSectionSix(file,       "06", 0x28000,  0x44000,  6681, "0x028000..0x044000 : Fonts, Menu Tiles, Text Decoding Functions, SEGA Logo, Game Staff, Conf/Debug modes, End Kiss Sequence, Text Huffman Trees, Textbanks");
    produceSpecificSectionSeven(file,     "07", 0x44000,  0x64000,  2931, "0x044000..0x064000 : Entity ActScripts, CutScene Scripts, Battle CutScenes, Intro cutscene, End cutscene, Map Setups");
    produceSpecificSectionEight(file,     "08", 0x64000,  0xC8000,  953 , "0x064000..0x0C8000 : Map Tiles, Map Palettes, Map Data");
    produceSpecificSectionNine(file,      "09", 0xC8000,  0x100000, 1315, "0x0C8000..0x100000 : Entity Sprites");
    produceSpecificSectionTen(file,       "10", 0x100000, 0x130000, 432,  "0x100000..0x130000 : Backgrounds, invocation sprites, title screen");
    produceSpecificSectionEleven(file,    "11", 0x130000, 0x180000, 429,  "0x130000..0x180000 : Enemy battlesprites");
    produceSpecificSectionTwelve(file,    "12", 0x180000, 0x1AC000, 871,  "0x180000..0x1AC000 : Ally battlesprites, status anim tiles, battlescene transition tiles, bolt graphics, ally and enemy animations");
    produceSpecificSectionThirteen(file,  "13", 0x1AC000, 0x1B8000, 133,  "0x1AC000..0x1B8000 : Battle setup functions, battle terrains, battle entity setups, end kiss graphics");
    produceSpecificSectionFourteen(file,  "14", 0x1B8000, 0x1C8000, 474,  "0x1B8000..0x1C8000 : Battlescene grounds, weapons, spell graphics, witch screens");
    produceSpecificSectionFifteen(file,   "15", 0x1C8000, 0x1D8000, 1467, "0x1C8000..0x1D8000 : Portraits");
    produceSpecificSectionSixteen(file,   "16", 0x1D8000, 0x1E0000, 126,  "0x1D8000..0x1E0000 : Icons");
    produceSpecificSectionSeventeen(file, "17", 0x1E0000, 0x1F0000, 462,  "0x1E0000..0x1F0000 : PCM Banks, YM Instruments, sound driver, char stats, witch screens");
    produceSection(file,                  "18", 0x1F0000, 0x200000, 1038, "0x1F0000..0x200000 : Music banks 1 and 0");

    fclose(file);

}


static produceSpecificSectionOne(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x00000%s-0x00%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
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
    produceAsmScript(file,"data\\battles\\global\\battlemapcoords",0x7A36,0x7B71,"Battle map coords");    
    produceAsmScript(file,"data\\maps\\global\\savepointmapcoords",0x7B71,0x7BCE,"Save point map coords");    
    produceAsmScript(file,"data\\maps\\global\\raftresetmapcoords",0x7BCE,0x7BDE,"Raft reset map coords");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\specialscreens\\witch\\witchfunctions",0x7BDE,0x7E3A,"Witch functions");    
    produceAsmScript(file,"code\\gameflow\\special\\configurationmode",0x7E3A,0x7EC6,"Configuration mode function");    
    produceAsmScript(file,"code\\gameflow\\start\\regioncheck",0x7EC6,0x7FA4,"Region check function");    
    produceAsmScript(file,"code\\specialscreens\\witch\\soundtest",0x7FA4,0x7FA6,"Sound Test function missing in US version");
    produceAsmSectionNoPretty(file,"",0x7FA6,0x8000);

    fclose(file);
    Message("DONE.\n");    
}    


static produceSpecificSectionTwo(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x00%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s02_jumpinterface",0x8000,0x82C4,"Game Section 02 Jump Interface");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s02_pointers",0x82C4,0x82D0,"Game Section 02 Pointers");
    writestr(file,"                \n");
    writestr(file,"                ; Stats engine\n");
    produceAsmScript(file,"code\\common\\stats\\statsengine_1",0x82D0,0x853A,"Character stats engine");
    produceAsmScript(file,"data\\stats\\allies\\classes\\classtypes",0x853A,0x855A,"Class types table");
    produceAsmScript(file,"code\\common\\stats\\statsengine_2",0x855A,0x9484,"Character stats engine");
    produceAsmScript(file,"code\\common\\stats\\levelup",0x9484,0x9736,"Level Up functions");
    produceAsmScript(file,"code\\common\\stats\\statsengine_3",0x9736,0x9A3C,"Character stats engine");
    produceAsmScript(file,"code\\common\\stats\\caravaninventoryfunctions",0x9A3C,0x9A9A,"Caravan inventory management functions");
    writestr(file,"                \n");
    writestr(file,"                ; Battleactions engine\n");
    produceAsmScript(file,"code\\gameflow\\special\\debugmodebattleactions",0x9A9A,0x9B92,"Debug mode battle actions");    
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_1",0x9B92,0x9EC4,"Battleactions engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\determineineffectiveattack",0x9EC4,0x9F28,"Determine ineffective attack function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\initbattlesceneproperties",0x9F28,0xA05C,"Init Battlescene Properties function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\createbattlescenemessage",0xA05C,0xA200,"Create Battlescene Message function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\createbattlesceneanimation",0xA200,0xA34E,"Create battlescene animation function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_2",0xA34E,0xA49C,"Battleactions engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\isabletocounterattack",0xA49C,0xA54E,"Is Able To Counter Attack function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\getspellanimation",0xA54E,0xA6E8,"Get spell animation function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_3",0xA6E8,0xA870,"Battleactions engine");
    produceAsmScript(file,"data\\battles\\global\\halvedexpearnedbattles",0xA870,0xA872,"Halved EXP earned battles table");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_4",0xA872,0xAAFC,"Battleactions engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\determinedodge",0xAAFC,0xABBE,"Determine dodge function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\calculatedamage",0xABBE,0xAC4E,"Calculate attack damage function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\determinecriticalhit",0xAC4E,0xACCA,"Determine critical hit function");
    produceAsmScript(file,"data\\stats\\allies\\classes\\criticalhitsettings",0xACCA,0xACEA,"Critical hit settings");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_5",0xACEA,0xB0A8,"Battleactions engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\castspell",0xB0A8,0xBB02,"Write Battlescene Script : Cast Spell");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\calculatespelldamage",0xBB02,0xBBB8,"Calculate Spell Damage function");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\useitem",0xBBB8,0xBBE4,"Write Battlescene Script : Use Item");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\nullsub_BBE4",0xBBE4,0xBBE6,"Unused nullsub");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\breakuseditem",0xBBE6,0xBCF0,"Write Battlescene Script : Break Used Item");
    produceAsmScript(file,"data\\stats\\items\\itembreakmessages",0xBCF0,0xBD24,"Item break messages");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\dropenemyitem",0xBD24,0xBE52,"Write Battlescene Command : Drop Enemy Item function");
    produceAsmScript(file,"data\\battles\\global\\enemyitemdrops",0xBE52,0xBECC,"Enemy item drops");
    produceAsmScript(file,"data\\stats\\enemies\\enemygold",0xBECC,0xC024,"Enemy gold amounts");
    produceAsmScript(file,"code\\gameflow\\battle\\battleactions\\battleactionsengine_6",0xC024,0xC09A,"Battleactions engine");
    writestr(file,"                \n");
    writestr(file,"                ; Battlefield engine\n");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_1",0xC09A,0xC24E,"Battlefield engine");
    produceAsmScript(file,"data\\stats\\spells\\spellelements",0xC24E,0xC27A,"Spell elements table");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_2",0xC27A,0xC306,"Battlefield engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\getattackrange",0xC306,0xC380,"Get Attack Range function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_3",0xC380,0xCD68,"Battlefield engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\determinehealingspelllevel",0xCD68,0xCDEA,"Determine healing spell level function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_4",0xCDEA,0xCF74,"Battlefield engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\useableaiactions",0xCF74,0xD1CC,"Usable AI actions getter functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_5",0xD1CC,0xD38A,"Battlefield engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\doescombatantrequirehealing",0xD38A,0xD3CA,"Does combatant require healing function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_6",0xD3CA,0xD824,"Battlefield engine");
    produceAsmScript(file,"data\\battles\\global\\landeffectsettingsandmovecosts",0xD824,0xD8F4,"Land effect settings and move costs table");
    produceAsmScript(file,"data\\battles\\global\\aipriority",0xD8F4,0xDA82,"AI priority data");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefield\\battlefieldengine_7",0xDA82,0xDEFC,"Battlefield engine");
    writestr(file,"                \n");
    writestr(file,"                ; AI engine\n");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aiengine_1",0xDEFC,0xE1AC,"AI engine");
    produceAsmScript(file,"data\\battles\\global\\aicommandsets",0xE1AC,0xE25B,"AI commands data");
    produceAsmScript(file,"data\\battles\\global\\swarmbattles",0xE25B,0xE294,"Parameters for battles implementing swarm AI");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\handleaicommand",0xE294,0xE3EE,"Handle AI Command function");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aicommandheal",0xE3EE,0xE78C,"AI command : Heal");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aicommandattack",0xE78C,0xE98C,"AI command : Attack");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aicommandspecialmove",0xE98C,0xEBA4,"AI command : Special Move");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aicommandsupport",0xEBA4,0xEDD6,"AI command : Support");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\determineaibattleaction",0xEDD6,0xF1D4,"Determine AI Battleaction function");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aicommandmove",0xF1D4,0xF522,"AI command : Move");
    produceAsmScript(file,"code\\gameflow\\battle\\ai\\aiengine_2",0xF522,0xF9B4,"AI engine");
    produceAsmScript(file,"data\\battles\\global\\krakenmovecosts",0xF9B4,0xF9C4,"Kraken move costs table");
    writestr(file,"                \n");
    produceAsmScript(file,"data\\stats\\spells\\spellnames",0xF9C4,0xFAD6,"Spell names");
    produceAsmScript(file,"data\\stats\\allies\\allynames",0xFAD6,0xFB8A,"Ally names");
    produceAsmScript(file,"data\\stats\\enemies\\enemynames",0xFB8A,0xFF87,"Enemy names");
    produceAsmSection(file,"",0xFF87,0x10000);

    fclose(file);
    Message("DONE.\n");    
}    


static produceSpecificSectionThree(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s03_jumpinterface_1",0x10000,0x10084,"Game Section 03 Jump Interface, part 1");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s03_pointers",0x10084,0x10094,"Game Section 03 Pointers");
    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s03_jumpinterface_2",0x10094,0x100C4,"Game Section 03 Jump Interface, part 2");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s03_memberstatuswindowlayoutpointer",0x100C4,0x100C8,"Game Section 03 Member Status Window Layout Pointer");
    produceAsmScript(file,"code\\common\\menus\\menuengine_01",0x100C8,0x10E1C,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\menus\\diamondmenulayout",0x10E1C,0x10EF4,"Diamond menu layout");
    produceAsmScript(file,"data\\graphics\\tech\\menus\\magicmenulayout",0x10EF4,0x10FCC,"Magic menu layout");
    produceAsmScript(file,"data\\graphics\\tech\\menus\\itemmenulayout",0x10FCC,0x110A4,"Item menu layout");
    produceAsmScript(file,"code\\common\\menus\\menuengine_02",0x110A4,0x114BE,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\battleequipwindowlayout",0x114BE,0x11572,"Battle equip window layout");
    produceAsmScript(file,"code\\common\\menus\\menuengine_03",0x11572,0x118BE,"Menu engine");
    produceAsmScript(file,"code\\common\\menus\\buildfighterministatuswindow",0x118BE,0x11AEC,"Build fighter mini status window function");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\fighterministatuswindowlayout",0x11AEC,0x11B46,"Fighter mini status window layout");
    produceAsmScript(file,"code\\common\\menus\\menuengine_04",0x11B46,0x11FF0,"Menu engine");
    produceAsmScript(file,"code\\common\\menus\\buildmemberstatswindow",0x11FF0,0x12606,"Build member stats window function");
    produceAsmScript(file,"code\\common\\menus\\unusedsub_12606",0x12606,0x1263A,"Unused function");
    produceAsmScript(file,"code\\common\\menus\\getcombatantportrait",0x1263A,0x1264E,"Get combatant portrait index function");
    produceAsmScript(file,"data\\graphics\\tech\\windowborder\\entries",0x1264E,0x126EE,"Windows border compressed tiles");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\portraitwindowlayout",0x126EE,0x1278E,"Member screen portrait window layout");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\allykilldefeatwindowlayout",0x1278E,0x1284E,"Member screen kills and defeat window layout");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\goldwindowlayout",0x1284E,0x1288E,"Member screen gold window layout");
    produceAsmScript(file,"code\\common\\menus\\menuengine_05",0x1288E,0x135A6,"Menu engine");
    produceAsmScript(file,"code\\common\\menus\\writememberlisttext",0x135A6,0x137AC,"Write member list text function");
    produceAsmScript(file,"code\\common\\menus\\menuengine_06",0x137AC,0x156A8,"Menu engine");
    produceAsmScript(file,"code\\common\\menus\\unusedsub_156A8",0x156A8,0x15736,"Unused window functions");
    produceAsmScript(file,"code\\common\\menus\\getallyportrait",0x15736,0x15772,"Get ally portrait index function");
    produceAsmScript(file,"code\\common\\menus\\menuengine_07",0x15772,0x15A5A,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\battleconfigwindowlayout",0x15A5A,0x15BB0,"Battle config window layout");
    produceAsmScript(file,"code\\common\\menus\\menuengine_08",0x15BB0,0x1607C,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\alphabetwindowlayout",0x1607C,0x16204,"Alphabet window layout");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\namecharacterentrywindowlayout",0x16204,0x1623A,"Name character entry window layout");
    produceAsmScript(file,"data\\graphics\\tech\\alphabethighlight\\entries",0x1623A,0x16282,"Alphabet Highlight Tiles");
    produceAsmScript(file,"code\\common\\menus\\menuengine_09",0x16282,0x16618,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\timerwindowlayout",0x16618,0x16658,"Timer window layout");
    produceAsmScript(file,"code\\specialscreens\\witch\\witchmainmenu",0x16658,0x169AE,"Witch main menu");
    produceAsmScript(file,"code\\common\\menus\\menuengine_10",0x169AE,0x16A62,"Menu engine");
    produceAsmScript(file,"data\\graphics\\tech\\windowlayouts\\memberstatswindowlayout",0x16A62,0x16EA6,"Member stats window layout");
    produceAsmScript(file,"data\\stats\\items\\itemdefs",0x16EA6,0x176A6,"Item definitions");
    produceAsmScript(file,"data\\stats\\spells\\spelldefs",0x176A6,0x1796E,"Spell definitions");
    produceAsmScript(file,"data\\stats\\items\\itemnames",0x1796E,0x17F3D,"Item names");
    produceAsmSection(file,"",0x17F3D,0x17F3E);
    produceAsmScript(file,"data\\stats\\allies\\classes\\classnames",0x17F3E,0x17FDA,"Class names");
    produceAsmSection(file,"",0x17FDA,0x18000);

    fclose(file);
    Message("DONE.\n");    
}    


static produceSpecificSectionFour(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s04_jumpinterface",0x18000,0x18010,"Game Section 04 Jump Interface");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\battlesceneengine_0",0x18010,0x197C8,"Battlescene engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\getallyanimation",0x197C8,0x19838,"Get ally battlescene animation function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\battlesceneengine_1",0x19838,0x19DB0,"Battlescene engine");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\getweaponspriteandpalette",0x19DB0,0x19DFE,"Weapon sprite and palette getter function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\getbattlescenebackground",0x19DFE,0x19E5E,"Get battlescene background function");
    produceAsmScript(file,"data\\battles\\global\\terrainbackgrounds",0x19E5E,0x19E6E,"Terrain backgrounds table");
    produceAsmScript(file,"code\\gameflow\\battle\\battlescenes\\battlesceneengine_2",0x19E6E,0x1F806,"Battlescene engine");
    produceAsmScript(file,"data\\stats\\allies\\allybattlesprites",0x1F806,0x1F914,"Ally battlesprites table");
    produceAsmScript(file,"data\\stats\\enemies\\enemybattlesprites",0x1F914,0x1F9E2,"Enemy battlesprites table");
    produceAsmScript(file,"data\\stats\\items\\weapongraphics",0x1F9E2,0x1FA8A,"Weapon graphics table");
    produceAsmScript(file,"data\\battles\\global\\custombackgrounds",0x1FA8A,0x1FAB7,"Battle custom backgrounds table");
    produceAsmSection(file,"",0x1FAB7,0x1FAB8);
    produceAsmScript(file,"data\\battles\\global\\backgroundenemyswitch",0x1FAB8,0x1FAD6,"Background enemy switch table");
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\allyidlebattlesprites",0x1FAD6,0x1FADD,"Ally Idle Battlesprites");
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\enemyidlebattlesprites",0x1FADD,0x1FAEA,"Enemy Idle Battlesprites");
    writestr(file,"                align\n");
    produceAsmScript(file,"data\\graphics\\tech\\backgroundlayout",0x1FAEA,0x1FDEA,"Battlescene Background Layout");
    produceAsmSection(file,"",0x1FDEA,0x20000);

    fclose(file);
    Message("DONE.\n");    
}    


static produceSpecificSectionFive(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s05_jumpinterface",0x20000,0x20064,"Game Section 05 Jump Interface");
    writestr(file,"                \n");
    writestr(file,"                ; Menu actions\n");
    produceAsmScript(file,"code\\common\\menus\\shop\\shopactions",0x20064,0x20878,"Shop functions");
    produceAsmScript(file,"data\\stats\\items\\shopinventories",0x20878,0x20981,"Shop inventories");
    produceAsmScript(file,"data\\stats\\items\\debugshop",0x20981,0x20A02,"Debug shop");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\common\\menus\\church\\churchactions_1",0x20A02,0x21046,"Church functions");
    produceAsmScript(file,"data\\stats\\allies\\classes\\promotions",0x21046,0x21072,"Promotions");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\common\\menus\\church\\churchactions_2",0x21072,0x2127E,"Church functions");
    produceAsmScript(file,"code\\common\\menus\\main\\mainactions",0x2127E,0x21A3A,"Main menu functions");    
    produceAsmScript(file,"code\\common\\menus\\blacksmith\\blacksmithactions",0x21A3A,0x21EB6,"Blacksmith functions");
    produceAsmScript(file,"data\\stats\\allies\\classes\\blacksmitheligibleclasses",0x21EB6,0x21ED6,"Blacksmith eligible classes list");
    produceAsmScript(file,"code\\common\\menus\\blacksmith\\pickmithrilweapon",0x21ED6,0x21F62,"Pick Mithril Weapon function");
    produceAsmScript(file,"data\\stats\\items\\mithrilweapons",0x21F62,0x21FD2,"Mithril weapons data");
    produceAsmScript(file,"code\\common\\menus\\caravan\\caravanactions_1",0x21FD2,0x228A2,"Caravan functions");
    produceAsmScript(file,"data\\stats\\items\\specialcaravandescriptions",0x228A2,0x228A8,"Special Caravan descriptions");
    produceAsmScript(file,"code\\common\\menus\\caravan\\choosecaravanportrait",0x228A8,0x228D8,"Choose Caravan Portrait function");
    produceAsmScript(file,"code\\common\\menus\\caravan\\caravanactions_2",0x228D8,0x229CA,"Caravan functions");
    produceAsmScript(file,"code\\common\\stats\\items\\itemactions_1",0x229CA,0x229E2,"Item functions");
    produceAsmScript(file,"data\\stats\\items\\usableoutsidebattleitems",0x229E2,0x229EC,"Usable outside battle items");
    produceAsmScript(file,"code\\common\\stats\\items\\itemactions_2",0x229EC,0x22BC2,"Item functions");
    writestr(file,"                \n");
    writestr(file,"                ; Battle functions\n");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\battlefunctions_0",0x22BC2,0x2379A,"Battle functions");
    produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_0",0x2379A,0x239AE,"Exploration functions");
    produceAsmScript(file,"data\\stats\\items\\chestgoldamounts",0x239AE,0x239C8,"Chest gold amounts");
    produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_1",0x239C8,0x23A84,"Exploration functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\battlefunctions_1",0x23A84,0x23E50,"Battle functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\getegresspositionforbattle",0x23E50,0x23EB0,"Get Egress Position For Battle function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\executeindividualturn",0x23EB0,0x24242,"Execute Individual Turn function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\handleafterturneffects",0x24242,0x2448A,"Handle After Turn Effects function");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\battlefunctions_2",0x2448A,0x2550C,"Battle functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\updateenemyaifunctions",0x2550C,0x25544,"Update Enemy AI functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\turnorderfunctions",0x25544,0x25610,"Battle turn order functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\battlefunctions_3",0x25610,0x25790,"Battle functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlefunctions\\setmovesfx",0x25790,0x257C0,"Set Move Sfx function");
    produceAsmScript(file,"code\\gameflow\\exploration\\explorationfunctions_2",0x257C0,0x25A94,"Exploration functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battlevints",0x25A94,0x25AD6,"Battle VInt functions");
    produceAsmScript(file,"code\\gameflow\\exploration\\explorationvints",0x25AD6,0x25BFC,"Exploration VInt functions");
    writestr(file,"                \n");
    produceAsmScript(file,"code\\common\\tech\\graphics\\specialsprites",0x25BFC,0x25DF6,"Special Sprites functions");
    produceAsmScript(file,"code\\common\\tech\\graphics\\specialspritesentries",0x25DF6,0x02784C,"Special Sprites Entries");
    produceAsmScript(file,"code\\common\\tech\\graphics\\specialspritesanims",0x02784C,0x2791C,"Special Sprites Animations");
    produceAsmScript(file,"code\\specialscreens\\suspend\\suspend",0x2791C,0x279D8,"Suspend functions");
    produceAsmScript(file,"code\\specialscreens\\witchend\\witchend",0x279D8,0x27D8E,"Witch end functions");
    produceAsmSection(file,"",0x27D8E,0x28000);

    fclose(file);
    Message("DONE.\n");    
}    
    
    
static produceSpecificSectionSix(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s06_textbankspointer",0x28000,0x28004,"Game Section 06 Text Banks Pointer");
    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s06_jumpinterface_1",0x28004,0x2800C,"Game Section 06 Jump Interface, part 1");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s06_pointers",0x2800C,0x2803C,"Game Section 06 Pointers");
    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s06_jumpinterface_2",0x2803C,0x28040,"Game Section 06 Jump Interface, part 2");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s06_gamestaffpointer",0x28040,0x28044,"Game Section 06 Game Staff Pointer");
    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s06_jumpinterface_3",0x28044,0x2804C,"Game Section 06 Jump Interface, part 3");
    produceAsmScript(file,"code\\specialscreens\\segalogo\\segalogo_0",0x2804C,0x28FBC,"SEGA logo functions");
    produceAsmScript(file,"data\\tech\\configurationmodeinputsequence",0x28FBC,0x28FCB,"Configuration mode input sequence");
    produceAsmSection(file,"",0x28FCB,0x28FCC);
    produceAsmScript(file,"code\\specialscreens\\segalogo\\segalogo_1",0x28FCC,0x28FF0,"SEGA logo functions");
    produceAsmScript(file,"data\\tech\\debugmodeinputsequence",0x28FF0,0x29001,"Debug mode input sequence");
    produceAsmSection(file,"",0x29001,0x2C576);
    produceAsmScript(file,"code\\specialscreens\\endkiss\\endkissfunctions_0",0x2C576,0x2C73C,"End kiss function");    
    produceAsmScript(file,"code\\specialscreens\\title\\loadfont",0x2C73C,0x2C7A0,"Title screen font loading function");    
    produceAsmSection(file,"",0x2C7A0,0x2E10E);
    produceAsmScript(file,"code\\common\\scripting\\text\\decoding",0x2E10E,0x2E196,"Text decoding functions");    
    produceAsmSection(file,"",0x2E196,0x2EB34);
    produceAsmScript(file,"data\\scripting\\text\\entries",0x2EB34,0x4201E,"Textbank entries");   
    produceAsmScript(file,"code\\specialscreens\\credits\\gamestaff",0x4201E,0x425ED,"Game Staff");
    writestr(file,"                align\n");
    produceAsmSection(file,"",0x425ED,0x44000);    

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
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s07_jumpinterface",0x44000,0x440CC,"Game Section 07 Jump Interface");
    produceAsmScript(file,"code\\common\\scripting\\map\\mapfunctions",0x440CC,0x4428A,"Map functions");
    produceAsmScript(file,"data\\maps\\global\\overworldmaps",0x4428A,0x44298,"Overworld maps");
    produceAsmScript(file,"code\\common\\scripting\\map\\followersfunctions_1",0x44298,0x44338,"Follower functions, part 1");
    produceAsmScript(file,"data\\scripting\\entity\\followers",0x44338,0x4438A,"Follower declarations");
    produceAsmScript(file,"code\\common\\scripting\\map\\followersfunctions_2",0x4438A,0x444A2,"Follower functions, part 2");
    produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_1",0x444A2,0x448C4,"Entity functions");
    produceAsmScript(file,"data\\battles\\global\\battleneutralentities",0x448C4,0x4497A,"Battle entities which are not force members or enemies");
    produceAsmScript(file,"data\\scripting\\entity\\eas_battleneutralentities",0x4497A,0x449C6,"Entity actscripts for battle entities which are not force members or enemies");
    produceAsmScript(file,"code\\common\\scripting\\entity\\getallymapsprite",0x449C6,0x44A5E,"Get ally map sprite index function");
    produceAsmScript(file,"data\\stats\\allies\\allymapsprites",0x44A5E,0x44A7C,"Ally map sprite indexes table");
    produceAsmScript(file,"code\\common\\scripting\\entity\\getcombatantmapsprite",0x44A7C,0x44AA4,"Get combatant map sprite index function");
    produceAsmScript(file,"data\\stats\\enemies\\enemymapsprites",0x44AA4,0x44B4A,"Enemy map sprite indexes table");
    writestr(file,"                align\n");
    produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_2",0x44B4A,0x44DE2,"Entity functions");
    produceAsmScript(file,"data\\scripting\\entity\\eas_main",0x44DE2,0x45204,"Main entity actscripts");
    produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_3",0x45204,0x45268,"Entity functions");
    produceAsmScript(file,"code\\common\\scripting\\map\\vehiclefunctions",0x45268,0x45638,"Mapscripts and functions for Caravan and Raft");
    produceAsmScript(file,"code\\common\\scripting\\entity\\getentityportaitandspeechsfx",0x45638,0x4567A,"Get entity portrait and speech sfx indexes function");
    produceAsmScript(file,"data\\spritedialogproperties",0x4567A,0x45858,"Sprite dialog properties");
    produceAsmScript(file,"code\\common\\scripting\\entity\\entityfunctions_4",0x45858,0x45E44,"Entity functions");
    produceAsmScript(file,"data\\scripting\\entity\\eas_actions",0x45E44,0x46506,"Entity scripts for cutscene actions");
    produceAsmScript(file,"code\\common\\scripting\\map\\mapscriptengine_1",0x46506,0x47102,"Mapscript engine, part 1");
    produceAsmScript(file,"code\\common\\scripting\\map\\debugmapscripts",0x47102,0x4712A,"Debug mapscript function");
    produceAsmScript(file,"code\\common\\scripting\\map\\nullsub_4712A",0x4712A,0x4712C,"Unused empty function");
    produceAsmScript(file,"code\\common\\scripting\\map\\mapscriptengine_2",0x4712C,0x474FC,"Mapscript engine, part 2");
    produceAsmScript(file,"code\\common\\scripting\\map\\mapsetupsfunctions_1",0x474FC,0x478C6,"Map setups functions");
    produceAsmScript(file,"code\\common\\scripting\\map\\resetalliesstats",0x478C6,0x4790E,"CSC 55 function");
    produceAsmScript(file,"code\\common\\scripting\\map\\headquartersfunctions",0x4790E,0x47A4E,"Headquarters functions");
    produceAsmScript(file,"code\\common\\scripting\\map\\ms_empty",0x47A4E,0x47A50,"Empty mapscript");
    produceAsmScript(file,"code\\gameflow\\battle\\beforebattlecutscenesstart",0x47A50,0x47A88,"Before battle cutscenes function start");
    produceAsmScript(file,"data\\battles\\beforebattlecutscenes",0x47A88,0x47AE8,"Before battle cutscenes");
    produceAsmScript(file,"code\\gameflow\\battle\\beforebattlecutscenesend",0x47AE8,0x47AEE,"Before battle cutscenes function end");
    produceAsmScript(file,"code\\gameflow\\battle\\battlestartcutscenesstart",0x47AEE,0x47B2C,"Battle start cutscenes function start");
    produceAsmScript(file,"data\\battles\\battlestartcutscenes",0x47B2C,0x47B8C,"Battle start cutscenes");
    produceAsmScript(file,"code\\gameflow\\battle\\battlestartcutscenesend",0x47B8C,0x47B92,"Battle start cutscenes function end");
    produceAsmScript(file,"code\\gameflow\\battle\\battleendcutscenesstart",0x47B92,0x47BE8,"Battle end cutscenes function start");
    produceAsmScript(file,"data\\battles\\battleendcutscenes",0x47BE8,0x47C48,"Enemy defeated cutscenes");
    produceAsmScript(file,"code\\gameflow\\battle\\battleendcutscenesend",0x47C48,0x47C8E,"Battle end cutscenes function end");
    produceAsmScript(file,"data\\battles\\global\\enemyleaderpresence",0x47C8E,0x47CBB,"Enemy leader presence table");
    produceAsmSection(file,"",0x47CBB,0x47CBC);
    produceAsmScript(file,"code\\gameflow\\battle\\afterbattlecutscenesstart",0x47CBC,0x47CF4,"After battle cutscenes function start");
    produceAsmScript(file,"data\\battles\\afterbattlecutscenes",0x47CF4,0x47D54,"After battle cutscenes");
    produceAsmScript(file,"code\\gameflow\\battle\\afterbattlecutscenesend",0x47D54,0x47D6A,"After battle cutscenes function end");
    produceAsmScript(file,"data\\battles\\global\\afterbattlejoins",0x47D6A,0x47D9E,"After battle joins (unused)");
    produceAsmScript(file,"code\\gameflow\\battle\\afterenemyleaderdeathpositions",0x47D9E,0x47E6C,"After-battlescene listener used to prepare entity positions for end cutscene before the enemy leader dies. Only used in battle 5.");
    produceAsmScript(file,"data\\battles\\afterbattlepositions",0x47E6C,0x47E82,"After battle positions");
    produceAsmScript(file,"code\\gameflow\\battle\\regionactivatedcutscenes",0x47E82,0x47EC8,"Region-activated cutscenes functions");
    produceAsmScript(file,"data\\battles\\global\\regionactivatedcutscenes",0x47EC8,0x47EEA,"Region-activated cutscenes data");
    produceAsmScript(file,"code\\common\\tech\\graphics\\flashwhite",0x47EEA,0x47EF8,"Flash white function and script");
    produceAsmScript(file,"data\\scripting\\map\\cs_introendroutine",0x47EF8,0x47F7E,"Subroutine launching intro and end cutscenes");
    produceAsmScript(file,"data\\scripting\\map\\cs_intro1",0x47F7E,0x48380,"Intro cutscene 1");
    produceAsmScript(file,"data\\scripting\\map\\cs_intro2",0x48380,0x48540,"Intro cutscene 2");
    produceAsmScript(file,"data\\scripting\\map\\cs_intro3",0x48540,0x48A78,"Intro cutscene 3");
    produceAsmScript(file,"data\\scripting\\map\\cs_intro4",0x48A78,0x48FE2,"Intro cutscene 4");
    produceAsmScript(file,"data\\scripting\\map\\cs_intro_stormeffect",0x48FE2,0x49058,"Storm Effect");
    produceAsmScript(file,"data\\scripting\\map\\cs_end",0x49058,0x4931C,"End cutscene");
    produceAsmScript(file,"data\\scripting\\map\\debugscripts",0x4931C,0x494BC,"Debugging scripts");

    writestr(file,"                include \"data\\battles\\entries\\battlecutscenesstorage.asm\"\n");
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

    writestr(file,"                include \"data\\maps\\mapsetupsstorage.asm\"\n");
    mapSetupsFile = fopen("disasm\\data\\maps\\mapsetupsstorage.asm","w");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\pointertable",0x4FA70,0x4FA88,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s1_entities",0x4FA88,0x4FA8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s2_entityevents",0x4FA8A,0x4FA90,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s3_zoneevents",0x4FA90,0x4FAE0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s4_descriptions",0x4FAE0,0x4FAE2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s5_itemevents",0x4FAE2,0x4FAEA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map66\\mapsetups\\s6_initfunction",0x4FAEA,0x4FAEC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\pointertable",0x4FAEC,0x4FB04,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s1_entities",0x4FB04,0x4FB06,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s2_entityevents",0x4FB06,0x4FB0C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s3_zoneevents",0x4FB0C,0x4FCCE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s4_descriptions",0x4FCCE,0x4FD42,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s5_itemevents",0x4FD42,0x4FD4A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map67\\mapsetups\\s6_initfunction",0x4FD4A,0x4FD4C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\pointertable",0x4FD4C,0x4FD64,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s1_entities",0x4FD64,0x4FD66,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s2_entityevents",0x4FD66,0x4FD6C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s3_zoneevents",0x4FD6C,0x4FD7C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s4_descriptions",0x4FD7C,0x4FD7E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s5_itemevents",0x4FD7E,0x4FD86,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map68\\mapsetups\\s6_initfunction",0x4FD86,0x4FD88,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\pointertable",0x4FD88,0x4FDA0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s1_entities",0x4FDA0,0x4FDA2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s3_zoneevents",0x4FDA2,0x4FDD2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s2_entityevents",0x4FDD2,0x4FDD8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s4_descriptions",0x4FDD8,0x4FDDA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s5_itemevents",0x4FDDA,0x4FDE2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map69\\mapsetups\\s6_initfunction",0x4FDE2,0x4FDE4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\pointertable",0x4FDE4,0x4FDFC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s1_entities",0x4FDFC,0x4FDFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s3_zoneevents",0x4FDFE,0x4FE32,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s2_entityevents",0x4FE32,0x4FE38,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s4_descriptions",0x4FE38,0x4FE3A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s5_itemevents",0x4FE3A,0x4FE42,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map70\\mapsetups\\s6_initfunction",0x4FE42,0x4FE44,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\pointertable",0x4FE44,0x4FE5C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s1_entities",0x4FE5C,0x4FE5E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s2_entityevents",0x4FE5E,0x4FE64,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s3_zoneevents",0x4FE64,0x4FF24,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s4_descriptions",0x4FF24,0x4FF26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s5_itemevents",0x4FF26,0x4FF2E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\s6_initfunction",0x4FF2E,0x4FFDA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map72\\mapsetups\\scripts",0x4FFDA,0x50312,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\pointertable",0x50312,0x5032A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s1_entities",0x5032A,0x5032C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s3_zoneevents",0x5032C,0x50332,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s2_entityevents",0x50332,0x50338,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s4_descriptions",0x50338,0x5033A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s5_itemevents",0x5033A,0x50342,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map73\\mapsetups\\s6_initfunction",0x50342,0x5096A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\pointertable",0x5096A,0x50982,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s1_entities",0x50982,0x50984,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s3_zoneevents",0x50984,0x509C6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s2_entityevents",0x509C6,0x509CC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s4_descriptions",0x509CC,0x509CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s5_itemevents",0x509CE,0x509D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map74\\mapsetups\\s6_initfunction",0x509D6,0x509D8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\pointertable",0x509D8,0x509F0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s1_entities",0x509F0,0x509F2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s3_zoneevents",0x509F2,0x509F8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s2_entityevents",0x509F8,0x509FE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s4_descriptions",0x509FE,0x50A00,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s5_itemevents",0x50A00,0x50A08,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map75\\mapsetups\\s6_initfunction",0x50A08,0x50A0A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\pointertable",0x50A0A,0x50A22,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s1_entities",0x50A22,0x50A24,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s3_zoneevents",0x50A24,0x50A3E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s2_entityevents",0x50A3E,0x50A44,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s4_descriptions",0x50A44,0x50A46,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s5_itemevents",0x50A46,0x50A4E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map76\\mapsetups\\s6_initfunction",0x50A4E,0x50A50,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\pointertable",0x50A50,0x50A68,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s1_entities",0x50A68,0x50A6A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s3_zoneevents",0x50A6A,0x50A84,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s2_entityevents",0x50A84,0x50A8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s4_descriptions",0x50A8A,0x50A8C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s5_itemevents",0x50A8C,0x50AE6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map77\\mapsetups\\s6_initfunction",0x50AE6,0x50AE8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pointertable",0x50AE8,0x50B00,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pointertable_609",0x50B00,0x50B18,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pointertable_506",0x50B18,0x50B30,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_entities",0x50B30,0x50BCA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_entities_609",0x50BCA,0x50CCA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_entities_506",0x50CCA,0x50D4C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_zoneevents",0x50D4C,0x50EEA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_zoneevents_609",0x50EEA,0x50F0C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_zoneevents_506",0x50F0C,0x50F10,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_entityevents",0x50F10,0x5105C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_entityevents_609",0x5105C,0x511CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_entityevents_506",0x511CA,0x512E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s4_descriptions",0x512E0,0x51358,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s5_itemevents",0x51358,0x51360,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_initfunction_506",0x51360,0x51382,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_initfunction",0x51382,0x513C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_initfunction_609",0x513C0,0x513D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\scripts_1",0x513D6,0x516CC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\pointertable",0x516CC,0x516E4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s1_entities",0x516E4,0x516F6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s3_zoneevents",0x516F6,0x516FC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s2_entityevents",0x516FC,0x51702,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s4_descriptions",0x51702,0x51720,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s5_itemevents",0x51720,0x51728,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\s6_initfunction",0x51728,0x51840,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map04\\mapsetups\\scripts",0x51840,0x51912,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pointertable",0x51912,0x5192A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pointertable_650",0x5192A,0x51942,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_entities",0x51942,0x519C4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_entities_650",0x519C4,0x51A3E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2_entityevents",0x51A3E,0x51A82,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2_entityevents_650",0x51A82,0x51C22,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s3_zoneevents",0x51C22,0x51C28,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s4_descriptions",0x51C28,0x51C54,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s5_itemevents",0x51C54,0x51C5C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s6_initfunction",0x51C5C,0x51C5E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pointertable_663",0x51C5E,0x51C76,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pointertable",0x51C76,0x51C8E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1_entities_663",0x51C8E,0x51D30,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1_entities",0x51D30,0x51DE2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2_entityevents_663",0x51DE2,0x51E32,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2_entityevents",0x51E32,0x51EE4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s3_zoneevents",0x51EE4,0x51F2A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s4_descriptions",0x51F2A,0x51F6E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s5_itemevents",0x51F6E,0x51F76,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s6_initfunction",0x51F76,0x51F88,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\scripts",0x51F88,0x52284,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pointertable",0x52284,0x5229C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pointertable_505",0x5229C,0x522B4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1_entities",0x522B4,0x522DC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1_entities_505",0x522DC,0x5231C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s2_entityevents",0x5231C,0x523E4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3_zoneevents",0x523E4,0x52442,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3_zoneevents_505",0x52442,0x52446,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s4_descriptions",0x52446,0x52448,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s5_itemevents",0x52448,0x52450,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s6_initfunction",0x52450,0x52530,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\scripts",0x52530,0x52A80,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\pointertable",0x52A80,0x52A98,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s1_entities",0x52A98,0x52ABA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s2_entityevents",0x52ABA,0x52B20,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s3_zoneevents",0x52B20,0x52B26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s4_descriptions",0x52B26,0x52B40,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s5_itemevents",0x52B40,0x52B48,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s6_initfunction",0x52B48,0x52B4A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable",0x52B4A,0x52B62,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_501",0x52B62,0x52B7A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_609",0x52B7A,0x52B92,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_506",0x52B92,0x52BAA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_507",0x52BAA,0x52BC2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities",0x52BC2,0x52C2C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_501",0x52C2C,0x52C46,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_609",0x52C46,0x52CB0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_506",0x52CB0,0x52D8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_507",0x52D8A,0x52D94,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_zoneevents",0x52D94,0x52D98,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_zoneevents_506",0x52D98,0x52DA4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_zoneevents_507",0x52DA4,0x52E02,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents",0x52E02,0x52F60,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_501",0x52F60,0x52F90,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_609",0x52F90,0x5301C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_506",0x5301C,0x530BA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_507",0x530BA,0x530BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s4_descriptions",0x530BE,0x530E2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s5_itemevents",0x530E2,0x530EA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_initfunction",0x530EA,0x5310C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_initfunction_609",0x5310C,0x5311E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_initfunction_506",0x5311E,0x53168,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_initfunction_507",0x53168,0x53176,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\scripts",0x53176,0x53634,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pointertable",0x53634,0x5364C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pointertable_501",0x5364C,0x53664,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pointertable_609",0x53664,0x5367C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pointertable_506",0x5367C,0x53694,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_entities",0x53694,0x536D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_entities_501",0x536D6,0x53720,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_entities_609",0x53720,0x53760,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_entities_506",0x53760,0x53762,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3_zoneevents",0x53762,0x53766,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3_zoneevents_501",0x53766,0x537AC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_entityevents",0x537AC,0x53830,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_entityevents_501",0x53830,0x538B4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_entityevents_609",0x538B4,0x53928,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_entityevents_506",0x53928,0x5392C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s4_descriptions",0x5392C,0x5395E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s5_itemevents",0x5395E,0x53966,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s6_initfunction",0x53966,0x53B66,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\scripts_1",0x53B66,0x53E18,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pointertable",0x53E18,0x53E30,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pointertable_501",0x53E30,0x53E48,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pointertable_609",0x53E48,0x53E60,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pointertable_506",0x53E60,0x53E78,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_entities",0x53E78,0x53E82,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_entities_609",0x53E82,0x53E8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_entities_506",0x53E8A,0x53E8C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s3_zoneevents",0x53E8C,0x53E92,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_entityevents",0x53E92,0x53E9A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_entityevents_501",0x53E9A,0x53EA2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_entityevents_609",0x53EA2,0x53EAA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_entityevents_506",0x53EAA,0x53F06,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s4_descriptions",0x53F06,0x53F08,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s5_itemevents",0x53F08,0x53F10,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s6_initfunction",0x53F10,0x53F48,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\pointertable_506",0x53F48,0x53F60,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\pointertable",0x53F60,0x53F78,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s1_entities_506",0x53F78,0x53F90,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s1_entities",0x53F90,0x53F92,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s2_entityevents",0x53F92,0x53FBA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s3_zoneevents",0x53FBA,0x53FC0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s4_descriptions",0x53FC0,0x53FC2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s5_itemevents",0x53FC2,0x53FCA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\s6_initfunction",0x53FCA,0x53FE0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map40\\mapsetups\\scripts",0x53FE0,0x53FFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\pointertable",0x53FFE,0x54016,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\pointertable_612",0x54016,0x5402E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s1_entities",0x5402E,0x54046,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s1_entities_612",0x54046,0x54048,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s3_zoneevents",0x54048,0x5404E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s2_entityevents",0x5404E,0x54054,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s5_itemevents",0x54054,0x5405C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s4_descriptions",0x5405C,0x540A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map43\\mapsetups\\s6_initfunction",0x540A6,0x54348,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pointertable",0x54348,0x54360,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pointertable_609",0x54360,0x54378,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pointertable_506",0x54378,0x54390,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\pointertable_507",0x54390,0x543A8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_entities",0x543A8,0x543BA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_entities_609",0x543BA,0x543E4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_entities_506",0x543E4,0x543EE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s1_entities_507",0x543EE,0x54458,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s3_zoneevents",0x54458,0x5445E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_entityevents",0x5445E,0x5446A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_entityevents_609",0x5446A,0x54482,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_entityevents_506",0x54482,0x5448A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s2_entityevents_507",0x5448A,0x5455E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s5_itemevents",0x5455E,0x54566,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s4_descriptions",0x54566,0x54568,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\s6_initfunction_507",0x54568,0x54578,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map44\\mapsetups\\scripts",0x54578,0x5473E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pointertable_702",0x5473E,0x54756,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pointertable",0x54756,0x5476E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\pointertable_701",0x5476E,0x54786,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1_entities_702",0x54786,0x547F8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1_entities",0x547F8,0x5489A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s1_entities_701",0x5489A,0x5490C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2_entityevents_702",0x5490C,0x54948,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2_entityevents",0x54948,0x54984,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s2_entityevents_701",0x54984,0x54CD0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s3_zoneevents",0x54CD0,0x54D3C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s4_descriptions_702",0x54D3C,0x54D8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s4_descriptions",0x54D8A,0x54E4C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s5_itemevents",0x54E4C,0x54E54,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\s6_initfunction",0x54E54,0x54E86,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map06\\mapsetups\\scripts",0x54E86,0x5537E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pointertable",0x5537E,0x55396,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pointertable_701",0x55396,0x553AE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\pointertable_805",0x553AE,0x553C6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1_entities",0x553C6,0x55428,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1_entities_701",0x55428,0x554B2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s1_entities_805",0x554B2,0x5550C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2_entityevents",0x5550C,0x55540,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2_entityevents_701",0x55540,0x55584,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s2_entityevents_805",0x55584,0x5579E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s3_zoneevents",0x5579E,0x557EE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s4_descriptions",0x557EE,0x5580E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s5_itemevents",0x5580E,0x55816,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\s6_initfunction",0x55816,0x55A36,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map07\\mapsetups\\scripts",0x55A36,0x55F8E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\pointertable_708",0x55F8E,0x55FA6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\pointertable",0x55FA6,0x55FC4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s1_entities_708",0x55FC4,0x56036,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s1_entities",0x56036,0x56048,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s2_entityevents_518",0x56048,0x56084,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s2_entityevents",0x56084,0x561AE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s3_zoneevents",0x561AE,0x561EC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s4_descriptions",0x561EC,0x562E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s5_itemevents",0x562E0,0x563A2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\s6_initfunction",0x563A2,0x563B2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map08\\mapsetups\\scripts",0x563B2,0x56636,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\pointertable",0x56636,0x5664E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\pointertable_518",0x5664E,0x56666,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s1_entities",0x56666,0x566C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s1_entities_518",0x566C0,0x56722,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s2_entityevents",0x56722,0x56856,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s3_zoneevents",0x56856,0x5687A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s4_descriptions",0x5687A,0x568A4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s5_itemevents",0x568A4,0x568C4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\s6_initfunction",0x568C4,0x568F6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map09\\mapsetups\\scripts",0x568F6,0x56B84,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\pointertable",0x56B84,0x56B9C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\pointertable_722",0x56B9C,0x56BB4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s1_entities",0x56BB4,0x56CA6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s1_entities_722",0x56CA6,0x56D80,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s2_entityevents",0x56D80,0x56E9C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s2_entityevents_722",0x56E9C,0x56F8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s3_zoneevents",0x56F8A,0x56FC0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s3_zoneevents_722",0x56FC0,0x56FE0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s4_descriptions",0x56FE0,0x57028,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s5_itemevents",0x57028,0x57030,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s6_initfunction",0x57030,0x5708E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\s6_initfunction_722",0x5708E,0x570B0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map10\\mapsetups\\scripts",0x570B0,0x579CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\pointertable",0x579CA,0x579E2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s1_entities",0x579E2,0x57A0C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s2_entityevents",0x57A0C,0x57A68,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s3_zoneevents",0x57A68,0x57A88,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s4_descriptions",0x57A88,0x57AA0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s5_itemevents",0x57AA0,0x57AA8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\s6_initfunction",0x57AA8,0x57AAA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map11\\mapsetups\\scripts",0x57AAA,0x57CCC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\pointertable",0x57CCC,0x57CE4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s1_entities",0x57CE4,0x57CEE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s2_entityevents",0x57CEE,0x57CF4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s3_zoneevents",0x57CF4,0x57CFA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s4_descriptions",0x57CFA,0x57CFC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s5_itemevents",0x57CFC,0x57D04,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map12\\mapsetups\\s6_initfunction",0x57D04,0x57E36,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pointertable",0x57E36,0x57E4E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pointertable_709",0x57E4E,0x57E66,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pointertable_799",0x57E66,0x57E7E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\pointertable_513",0x57E7E,0x57E96,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_entities",0x57E96,0x57F08,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_entities_709",0x57F08,0x57F7A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_entities_799",0x57F7A,0x57FB4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s1_entities_513",0x57FB4,0x5801E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s2_entityevents",0x5801E,0x5814C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s2_entityevents_513",0x5814C,0x5822A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s3_zoneevents",0x5822A,0x582AC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s4_descriptions",0x582AC,0x582D8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s5_itemevents",0x582D8,0x582E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\s6_initfunction",0x582E0,0x58330,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map13\\mapsetups\\scripts",0x58330,0x58E18,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\pointertable",0x58E18,0x58E30,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\pointertable_458",0x58E30,0x58E48,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s3_zoneevents",0x58E48,0x58EBA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s2_entityevents",0x58EBA,0x58F0E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s1_entities",0x58F0E,0x58F10,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s4_descriptions",0x58F10,0x58F12,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s6_initfunction",0x58F12,0x58F2A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s1_entities_458",0x58F2A,0x58F3C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s2_entityevents_458",0x58F3C,0x58F4C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s3_zoneevents_458",0x58F4C,0x58F5C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\scripts_1",0x58F5C,0x58F9A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s6_initfunction_458",0x58F9A,0x58F9C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\s5_itemevents",0x58F9C,0x58FA4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map14\\mapsetups\\scripts_2",0x58FA4,0x592E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\pointertable",0x592E0,0x592F8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\pointertable_522",0x592F8,0x59310,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s1_entities",0x59310,0x59402,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s1_entities_522",0x59402,0x59474,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s2_entityevents",0x59474,0x595DE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s3_zoneevents",0x595DE,0x59602,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s4_descriptions",0x59602,0x59604,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s5_itemevents",0x59604,0x5962E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\s6_initfunction",0x5962E,0x5994E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map22\\mapsetups\\scripts",0x5994E,0x59AC0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\pointertable",0x59AC0,0x59AD8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\pointertable_762",0x59AD8,0x59AF0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s1_entities",0x59AF0,0x59B22,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s1_entities_762",0x59B22,0x59B44,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s2_entityevents",0x59B44,0x59BA8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s2_entityevents_762",0x59BA8,0x59BD2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s3_zoneevents",0x59BD2,0x59BD8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s4_descriptions",0x59BD8,0x59BFC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s5_itemevents",0x59BFC,0x59C04,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map23\\mapsetups\\s6_initfunction",0x59C04,0x59C06,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\pointertable",0x59C06,0x59C1E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s1_entities",0x59C1E,0x59C20,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s2_entityevents",0x59C20,0x59C26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s3_zoneevents",0x59C26,0x59C2C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s4_descriptions",0x59C2C,0x59C2E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s5_itemevents",0x59C2E,0x59C36,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map24\\mapsetups\\s6_initfunction",0x59C36,0x59D08,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\pointertable",0x59D08,0x59D20,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s1_entities",0x59D20,0x59D6A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s2_entityevents",0x59D6A,0x59DB6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s3_zoneevents",0x59DB6,0x59DD2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s4_descriptions",0x59DD2,0x59DD4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s5_itemevents",0x59DD4,0x59DDC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\s6_initfunction",0x59DDC,0x59F20,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map26\\mapsetups\\scripts",0x59F20,0x59F42,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\pointertable",0x59F42,0x59F5A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\pointertable_523",0x59F5A,0x59F72,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s1_entities",0x59F72,0x59F8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s1_entities_523",0x59F8A,0x59F8C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s2_entityevents",0x59F8C,0x59F92,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s3_zoneevents",0x59F92,0x59FAC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s4_descriptions",0x59FAC,0x59FAE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s5_itemevents",0x59FAE,0x59FB6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\s6_initfunction",0x59FB6,0x59FB8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map27\\mapsetups\\scripts",0x59FB8,0x5A09E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\pointertable",0x5A09E,0x5A0B6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s1_entities",0x5A0B6,0x5A0F0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s2_entityevents",0x5A0F0,0x5A14E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s3_zoneevents",0x5A14E,0x5A154,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s4_descriptions",0x5A154,0x5A16C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s5_itemevents",0x5A16C,0x5A174,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map29\\mapsetups\\s6_initfunction",0x5A174,0x5A176,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pointertable",0x5A176,0x5A18E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pointertable_785",0x5A18E,0x5A1A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\pointertable_761",0x5A1A6,0x5A1BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1_entities",0x5A1BE,0x5A1E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1_entities_785",0x5A1E0,0x5A20A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s1_entities_761",0x5A20A,0x5A20C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s2_entityevents",0x5A20C,0x5A2C2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s3_zoneevents",0x5A2C2,0x5A2E8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s4_descriptions",0x5A2E8,0x5A2EA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s5_itemevents",0x5A2EA,0x5A2F2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\s6_initfunction",0x5A2F2,0x5A33A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map30\\mapsetups\\scripts",0x5A33A,0x5A646,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pointertable",0x5A646,0x5A65E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pointertable_523",0x5A65E,0x5A676,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pointertable_784",0x5A676,0x5A68E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\pointertable_786",0x5A68E,0x5A6A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_entities",0x5A6A6,0x5A6D8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_entities_523",0x5A6D8,0x5A712,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_entities_784",0x5A712,0x5A74C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s1_entities_786",0x5A74C,0x5A766,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s2_entityevents",0x5A766,0x5AA8A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s3_zoneevents",0x5AA8A,0x5AAD8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s4_descriptions",0x5AAD8,0x5AB74,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s5_itemevents",0x5AB74,0x5AB7C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s6_initfunction",0x5AB7C,0x5AC56,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\s6_initfunction_786",0x5AC56,0x5AC58,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map33\\mapsetups\\scripts",0x5AC58,0x5B5B6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\pointertable",0x5B5B6,0x5B5CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\pointertable_784",0x5B5CE,0x5B5E6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s1_entities",0x5B5E6,0x5B68E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s1_entities_784",0x5B68E,0x5B690,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s2_entityevents",0x5B690,0x5B696,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s3_zoneevents",0x5B696,0x5B6B4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s4_descriptions",0x5B6B4,0x5B6B6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s5_itemevents",0x5B6B6,0x5B6BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\s6_initfunction",0x5B6BE,0x5B6C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map34\\mapsetups\\scripts",0x5B6C0,0x5BFEE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\pointertable",0x5BFEE,0x5C006,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s1_entities",0x5C006,0x5C0F8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s2_entityevents",0x5C0F8,0x5C264,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s3_zoneevents",0x5C264,0x5C26A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s4_descriptions",0x5C26A,0x5C26C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s5_itemevents",0x5C26C,0x5C274,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map46\\mapsetups\\s6_initfunction",0x5C274,0x5C27C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\pointertable",0x5C27C,0x5C294,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\pointertable_520",0x5C294,0x5C2AC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s1_entities",0x5C2AC,0x5C2CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s1_entities_520",0x5C2CE,0x5C2D0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s2_entityevents",0x5C2D0,0x5C2D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s3_zoneevents",0x5C2D6,0x5C3C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s4_descriptions",0x5C3C0,0x5C3C2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s5_itemevents",0x5C3C2,0x5C3CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map51\\mapsetups\\s6_initfunction",0x5C3CA,0x5C454,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\pointertable",0x5C454,0x5C46C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\pointertable_512",0x5C46C,0x5C484,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s1_entities",0x5C484,0x5C4A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s1_entities_512",0x5C4A6,0x5C4A8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s2_entityevents",0x5C4A8,0x5C4AA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s3_zoneevents",0x5C4AA,0x5C4CC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s4_descriptions",0x5C4CC,0x5C4CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s5_itemevents",0x5C4CE,0x5C4D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\s6_initfunction",0x5C4D6,0x5C4EE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map52\\mapsetups\\scripts",0x5C4EE,0x5C638,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\pointertable_729",0x5C638,0x5C650,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\pointertable",0x5C650,0x5C668,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s1_entities",0x5C668,0x5C670,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s1_entities_729",0x5C670,0x5C672,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s2_entityevents",0x5C672,0x5C696,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s3_zoneevents",0x5C696,0x5C6BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s4_descriptions",0x5C6BE,0x5C6C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s5_itemevents",0x5C6C0,0x5C6C8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\s6_initfunction",0x5C6C8,0x5C6CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map61\\mapsetups\\scripts",0x5C6CA,0x5C76A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\pointertable",0x5C76A,0x5C782,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\pointertable_77",0x5C782,0x5C79A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s1_entities",0x5C79A,0x5C7AC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s1_entities_77",0x5C7AC,0x5C7B6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s2_entityevents",0x5C7B6,0x5C820,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s3_zoneevents",0x5C820,0x5C86A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s4_descriptions",0x5C86A,0x5C86C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s5_itemevents",0x5C86C,0x5C874,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\s6_initfunction",0x5C874,0x5C876,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map62\\mapsetups\\scripts",0x5C876,0x5C950,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\pointertable_29",0x5C950,0x5C968,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\pointertable",0x5C968,0x5C980,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s1_entities",0x5C980,0x5C988,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s1_entities_29",0x5C988,0x5C98A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s2_entityevents",0x5C98A,0x5C9E2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s3_zoneevents",0x5C9E2,0x5CA24,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s4_descriptions",0x5CA24,0x5CA26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s5_itemevents",0x5CA26,0x5CA50,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\s6_initfunction",0x5CA50,0x5CA6E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map63\\mapsetups\\scripts",0x5CA6E,0x5CDFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\pointertable",0x5CDFE,0x5CE16,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\pointertable_530",0x5CE16,0x5CE2E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s1_entities",0x5CE2E,0x5CE90,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s1_entities_530",0x5CE90,0x5CEEA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s2_entityevents",0x5CEEA,0x5CF9E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s2_entityevents_530",0x5CF9E,0x5CFFA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s3_zoneevents",0x5CFFA,0x5CFFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s3_zoneevents_530",0x5CFFE,0x5D020,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s4_descriptions",0x5D020,0x5D044,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s5_itemevents",0x5D044,0x5D04C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\s6_initfunction",0x5D04C,0x5D04E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map15\\mapsetups\\scripts",0x5D04E,0x5D1CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\pointertable",0x5D1CA,0x5D1E2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s1_entities",0x5D1E2,0x5D224,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s2_entityevents",0x5D224,0x5D33A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s3_zoneevents",0x5D33A,0x5D340,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s4_descriptions",0x5D340,0x5D394,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s5_itemevents",0x5D394,0x5D39C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\s6_initfunction",0x5D39C,0x5D3B8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map25\\mapsetups\\scripts",0x5D3B8,0x5D40E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\pointertable",0x5D40E,0x5D426,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\pointertable_830",0x5D426,0x5D43E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s1_entities",0x5D43E,0x5D440,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s1_entities_830",0x5D440,0x5D49A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s2_entityevents",0x5D49A,0x5D49E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s2_entityevents_830",0x5D49E,0x5D552,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s3_zoneevents",0x5D552,0x5D556,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s3_zoneevents_830",0x5D556,0x5D574,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s4_descriptions",0x5D574,0x5D60E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s5_itemevents",0x5D60E,0x5D614,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s5_itemevents_830",0x5D614,0x5D61C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s6_initfunction",0x5D61C,0x5D61E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\s6_initfunction_830",0x5D61E,0x5D644,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map31\\mapsetups\\scripts",0x5D644,0x5D756,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\pointertable",0x5D756,0x5D76E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\pointertable_530",0x5D76E,0x5D786,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s1_entities",0x5D786,0x5D7F0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s1_entities_530",0x5D7F0,0x5D84A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s2_entityevents",0x5D84A,0x5D924,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s2_entityevents_530",0x5D924,0x5D9C0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s3_zoneevents",0x5D9C0,0x5D9C6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s4_descriptions",0x5D9C6,0x5DA0E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s5_itemevents",0x5DA0E,0x5DA16,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\s6_initfunction",0x5DA16,0x5DA28,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map36\\mapsetups\\scripts",0x5DA28,0x5DAE4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\pointertable",0x5DAE4,0x5DAFC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s1_entities",0x5DAFC,0x5DB76,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s2_entityevents",0x5DB76,0x5DCD0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s3_zoneevents",0x5DCD0,0x5DD26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s4_descriptions",0x5DD26,0x5DD50,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s5_itemevents",0x5DD50,0x5DD58,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\s6_initfunction",0x5DD58,0x5DE2E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map38\\mapsetups\\scripts",0x5DE2E,0x5DF84,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\pointertable",0x5DF84,0x5DF9C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\pointertable_830",0x5DF9C,0x5DFB4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s1_entities",0x5DFB4,0x5DFFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s1_entities_830",0x5DFFE,0x5E038,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s2_entityevents",0x5E038,0x5E0B2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s3_zoneevents",0x5E0B2,0x5E0CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s3_zoneevents_830",0x5E0CE,0x5E0D4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s4_descriptions",0x5E0D4,0x5E0D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s5_itemevents",0x5E0D6,0x5E0DE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s6_initfunction",0x5E0DE,0x5E0E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\s6_initfunction_830",0x5E0E0,0x5E0F8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map39\\mapsetups\\scripts",0x5E0F8,0x5E22C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\pointertable",0x5E22C,0x5E244,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s1_entities",0x5E244,0x5E246,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s2_entityevents",0x5E246,0x5E248,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s3_zoneevents",0x5E248,0x5E25E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s4_descriptions",0x5E25E,0x5E260,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s5_itemevents",0x5E260,0x5E268,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\s6_initfunction",0x5E268,0x5E27C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map55\\mapsetups\\scripts",0x5E27C,0x5E37C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\pointertable",0x5E37C,0x5E394,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s1_entities",0x5E394,0x5E39E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s2_entityevents",0x5E39E,0x5E3A4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s3_zoneevents",0x5E3A4,0x5E61E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s4_descriptions",0x5E61E,0x5E620,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s5_itemevents",0x5E620,0x5E628,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map00\\mapsetups\\s6_initfunction",0x5E628,0x5E62A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\pointertable",0x5E62A,0x5E642,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s1_entities",0x5E642,0x5E694,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s2_entityevents",0x5E694,0x5E720,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s3_zoneevents",0x5E720,0x5E726,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s4_descriptions",0x5E726,0x5E758,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s5_itemevents",0x5E758,0x5E760,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\s6_initfunction",0x5E760,0x5E772,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map01\\mapsetups\\scripts",0x5E772,0x5E86C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\pointertable",0x5E86C,0x5E884,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\pointertable_530",0x5E884,0x5E89C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s1_entities",0x5E89C,0x5E8EE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s1_entities_530",0x5E8EE,0x5E938,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s2_entityevents",0x5E938,0x5E9C8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s2_entityevents_530",0x5E9C8,0x5EA20,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s3_zoneevents",0x5EA20,0x5EA26,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s4_descriptions",0x5EA26,0x5EA62,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s4_descriptions_530",0x5EA62,0x5EA9E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s5_itemevents",0x5EA9E,0x5EAA6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map02\\mapsetups\\s6_initfunction",0x5EAA6,0x5EAA8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\pointertable",0x5EAA8,0x5EAC0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s1_entities",0x5EAC0,0x5EAC2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s2_entityevents",0x5EAC2,0x5EAC8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s3_zoneevents",0x5EAC8,0x5EACE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s4_descriptions",0x5EACE,0x5EAD0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s5_itemevents",0x5EAD0,0x5EAD8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s6_initfunction",0x5EAD8,0x5F34C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\pointertable",0x5F34C,0x5F364,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s1_entities",0x5F364,0x5F366,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s2_entityevents",0x5F366,0x5F36C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s3_zoneevents",0x5F36C,0x5F396,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s4_descriptions",0x5F396,0x5F398,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s5_itemevents",0x5F398,0x5F3A0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\s6_initfunction",0x5F3A0,0x5F3A2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map28\\mapsetups\\scripts",0x5F3A2,0x5F3E8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\pointertable",0x5F3E8,0x5F400,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s1_entities",0x5F400,0x5F402,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s2_entityevents",0x5F402,0x5F408,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s3_zoneevents",0x5F408,0x5F40E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s4_descriptions",0x5F40E,0x5F46C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s5_itemevents",0x5F46C,0x5F4A0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\s6_initfunction",0x5F4A0,0x5F4B8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map41\\mapsetups\\scripts",0x5F4B8,0x5F630,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\pointertable",0x5F630,0x5F660,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\pointertable_999",0x5F660,0x5F678,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s1_entities",0x5F678,0x5F772,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s1_entities_999",0x5F772,0x5F86C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s2_entityevents",0x5F86C,0x5F9D2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s2_entityevents_999",0x5F9D2,0x5FA22,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s3_zoneevents",0x5FA22,0x5FA28,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s4_descriptions",0x5FA28,0x5FA2A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s5_itemevents",0x5FA2A,0x5FA88,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s6_initfunction",0x5FA88,0x5FAA4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\s6_initfunction_999",0x5FAA4,0x5FB30,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map37\\mapsetups\\scripts",0x5FB30,0x5FDE4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\pointertable",0x5FDE4,0x5FDFC,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s1_entities",0x5FDFC,0x5FDFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s2_entityevents",0x5FDFE,0x5FE04,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s3_zoneevents",0x5FE04,0x5FE24,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s4_descriptions",0x5FE24,0x5FE90,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s5_itemevents",0x5FE90,0x5FE98,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\s6_initfunction",0x5FE98,0x5FE9A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map42\\mapsetups\\scripts",0x5FE9A,0x5FF62,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\pointertable",0x5FF62,0x5FF7A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s1_entities",0x5FF7A,0x60024,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s2_entityevents",0x60024,0x60060,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s3_zoneevents",0x60060,0x60078,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s4_descriptions",0x60078,0x60090,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s5_itemevents",0x60090,0x60098,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\s6_initfunction",0x60098,0x600CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map45\\mapsetups\\scripts",0x600CE,0x603AE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pointertable_530",0x603AE,0x603C6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\pointertable_28",0x603C6,0x603DE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_entities_530",0x603DE,0x60410,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s1_entities_28",0x60410,0x6043A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s2_entityevents_530",0x6043A,0x604C8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s3_zoneevents_530",0x604C8,0x60548,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s4_descriptions_530",0x60548,0x60606,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s5_itemevents_530",0x60606,0x6060E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\scripts_2",0x6060E,0x6061E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\s6_initfunction_530",0x6061E,0x60708,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map05\\mapsetups\\scripts_1",0x60708,0x60FAE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\pointertable_530",0x60FAE,0x60FC6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s1_entities_530",0x60FC6,0x61058,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s2_entityevents_530",0x61058,0x6114E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s3_zoneevents_530",0x6114E,0x61154,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s4_descriptions_530",0x61154,0x6119C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s5_itemevents_530",0x6119C,0x611A4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map16\\mapsetups\\s6_initfunction_530",0x611A4,0x611A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\pointertable_530",0x611A6,0x611BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s1_entities_530",0x611BE,0x611E0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s2_entityevents_530",0x611E0,0x61208,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s3_zoneevents_530",0x61208,0x6120E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s4_descriptions_530",0x6120E,0x61210,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s5_itemevents_530",0x61210,0x61218,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map17\\mapsetups\\s6_initfunction_530",0x61218,0x6121A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\pointertable_530",0x6121A,0x61232,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s1_entities_530",0x61232,0x61254,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s2_entityevents_530",0x61254,0x6125A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s3_zoneevents_530",0x6125A,0x61278,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s4_descriptions_530",0x61278,0x61290,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s5_itemevents_530",0x61290,0x61298,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\s6_initfunction_530",0x61298,0x6143C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map18\\mapsetups\\scripts",0x6143C,0x61488,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\pointertable",0x61488,0x614A0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s1_entities",0x614A0,0x614AA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s2_entityevents",0x614AA,0x614D6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s3_zoneevents",0x614D6,0x614FE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s4_descriptions",0x614FE,0x61500,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s5_itemevents",0x61500,0x61508,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\s6_initfunction",0x61508,0x6150A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map56\\mapsetups\\scripts",0x6150A,0x6153E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\pointertable_543",0x6153E,0x61556,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s1_entities_543",0x61556,0x615B0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s2_entityevents_543",0x615B0,0x615B6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s3_zoneevents_543",0x615B6,0x615CE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s4_descriptions_543",0x615CE,0x615D0,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s5_itemevents_543",0x615D0,0x615D8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map59\\mapsetups\\s6_initfunction_543",0x615D8,0x626A6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\pointertable_543",0x626A6,0x626BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s1_entities_543",0x626BE,0x62738,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s2_entityevents_543",0x62738,0x62820,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s3_zoneevents_543",0x62820,0x62846,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s4_descriptions_543",0x62846,0x628BE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s5_itemevents_543",0x628BE,0x628C6,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\s6_initfunction_543",0x628C6,0x628C8,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map03\\mapsetups\\scripts_2",0x628C8,0x6299A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_543",0x6299A,0x629B2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\pointertable_982",0x629B2,0x629CA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_543",0x629CA,0x62A6C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s1_entities_982",0x62A6C,0x62AFE,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_543",0x62AFE,0x62BCA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s2_entityevents_982",0x62BCA,0x62C6C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s3_zoneevents_543",0x62C6C,0x62C72,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s4_descriptions_543",0x62C72,0x62C96,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s5_itemevents_543",0x62C96,0x62C9E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map19\\mapsetups\\s6_initfunction_543",0x62C9E,0x631EA,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\pointertable_543",0x631EA,0x63202,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s1_entities_543",0x63202,0x63234,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s2_entityevents_543",0x63234,0x6329A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s3_zoneevents_543",0x6329A,0x63364,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s4_descriptions_543",0x63364,0x6339A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s5_itemevents_543",0x6339A,0x633A2,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\s6_initfunction_543",0x633A2,0x633C4,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map20\\mapsetups\\scripts_2",0x633C4,0x6343C,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\pointertable_543",0x6343C,0x63454,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s1_entities_543",0x63454,0x6345E,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s2_entityevents_543",0x6345E,0x63472,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s3_zoneevents_543",0x63472,0x63478,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s4_descriptions_543",0x63478,0x6347A,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s5_itemevents_543",0x6347A,0x63482,"");
    produceAsmScript(mapSetupsFile,"data\\maps\\entries\\map21\\mapsetups\\s6_initfunction_543",0x63482,0x6348C,"");
    fclose(mapSetupsFile);

    produceAsmSection(file,"",0x6348C,0x64000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionEight(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x0%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s08_pointers",0x64000,0x6400C,"Game Section 08 Pointers");
    produceAsmScript(file,"data\\graphics\\maps\\maptilesets\\entries",0x6400C,0x9494A,"Map Tilesets");    
    produceAsmScript(file,"data\\graphics\\maps\\mappalettes\\entries",0x9494A,0x94B8A,"Map palettes");
    produceMapEntries(file,"data\\maps\\entries",0x94B8A,0xC7ECC,"Map entries");
    produceAsmSection(file,"",0xC7ECC,0xC8000);

    fclose(file);
    Message("DONE.\n");    
}

static produceMapEntries(mainFile,sectionName,start,end,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, include, name, indent, comment, commentEx, commentIndent, offsets;
    fileName = form("%s.asm",sectionName);
    Message(form("Writing assembly script section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    //form("0x%s..0x%s %s",ltoa(start,16),ltoa(end,16),sectionComment)
    action = 1;
    include = "include";
    writestr(mainFile,form("                %s \"%s\"    ; %s\n",include,fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    offsets = form("0x%s..0x%s",ltoa(start,16),ltoa(end,16));
    writestr(file,form("\n; ASM FILE %s.asm :\n; %s : %s\n",sectionName,offsets,sectionComment));
    
    
    //0x94B8A,0xC7ECC
    produceAsmSection(file,"",0x94B8A,0x94CC6);

    produceAsmScriptWithExtName(file,"Map00","data\\maps\\entries\\map00\\00-tilesets",0x94CC6,0x94CCC,"");
    produceAsmSection(file,"",0x94CCC,0x94CF4);
    produceAsmScriptWithExtName(file,"Map00s2_Areas","data\\maps\\entries\\map00\\2-areas",0x94CF4,0x94D14,"");
    produceAsmScriptWithExtName(file,"Map00s3_FlagEvents","data\\maps\\entries\\map00\\3-flag-events",0x94D14,0x94D1E,"");
    produceAsmScriptWithExtName(file,"Map00s4_StepEvents","data\\maps\\entries\\map00\\4-step-events",0x94D1E,0x94D20,"");
    produceAsmScriptWithExtName(file,"Map00s5_RoofEvents","data\\maps\\entries\\map00\\5-roof-events",0x94D20,0x94D22,"");
    produceAsmScriptWithExtName(file,"Map00s6_WarpEvents","data\\maps\\entries\\map00\\6-warp-events",0x94D22,0x94D44,"");
    produceAsmScriptWithExtName(file,"Map00s7_ChestItems","data\\maps\\entries\\map00\\7-chest-items",0x94D44,0x94D4A,"");
    produceAsmScriptWithExtName(file,"Map00s8_OtherItems","data\\maps\\entries\\map00\\8-other-items",0x94D4A,0x94D4C,"");
    produceAsmSection(file,"",0x94D4C,0x959B0);
    produceAsmSection(file,"",0x959B0,0x95E86);
    produceAsmScriptWithExtName(file,"Map00s9_Animations","data\\maps\\entries\\map00\\9-animations",0x95E86,0x95E9C,"");
    
    produceAsmScriptWithExtName(file,"Map01","data\\maps\\entries\\map01\\00-tilesets",0x95E9C,0x95EA2,"");
    produceAsmSection(file,"",0x95EA2,0x95ECA);
    produceAsmScriptWithExtName(file,"Map01s2_Areas","data\\maps\\entries\\map01\\2-areas",0x95ECA,0x95F26,"");
    produceAsmScriptWithExtName(file,"Map01s3_FlagEvents","data\\maps\\entries\\map01\\3-flag-events",0x95F26,0x95F38,"");
    produceAsmScriptWithExtName(file,"Map01s4_StepEvents","data\\maps\\entries\\map01\\4-step-events",0x95F38,0x95F4A,"");
    produceAsmScriptWithExtName(file,"Map01s5_RoofEvents","data\\maps\\entries\\map01\\5-roof-events",0x95F4A,0x95F4C,"");
    produceAsmScriptWithExtName(file,"Map01s6_WarpEvents","data\\maps\\entries\\map01\\6-warp-events",0x95F4C,0x95F7E,"");
    produceAsmScriptWithExtName(file,"Map01s7_ChestItems","data\\maps\\entries\\map01\\7-chest-items",0x95F7E,0x95F90,"");
    produceAsmScriptWithExtName(file,"Map01s8_OtherItems","data\\maps\\entries\\map01\\8-other-items",0x95F90,0x95F92,"");
    produceAsmSection(file,"",0x95F92,0x965E6);
    produceAsmSection(file,"",0x965E6,0x968C2);
    produceAsmScriptWithExtName(file,"Map01s9_Animations","data\\maps\\entries\\map01\\9-animations",0x968C2,0x968D8,"");
    
    produceAsmScriptWithExtName(file,"Map02","data\\maps\\entries\\map02\\00-tilesets",0x968D8,0x968DE,"");
    produceAsmSection(file,"",0x968DE,0x96906);
    produceAsmScriptWithExtName(file,"Map02s2_Areas","data\\maps\\entries\\map02\\2-areas",0x96906,0x96926,"");
    produceAsmScriptWithExtName(file,"Map02s3_FlagEvents","data\\maps\\entries\\map02\\3-flag-events",0x96926,0x969C8,"");
    produceAsmScriptWithExtName(file,"Map02s4_StepEvents","data\\maps\\entries\\map02\\4-step-events",0x969C8,0x96A12,"");
    produceAsmScriptWithExtName(file,"Map02s5_RoofEvents","data\\maps\\entries\\map02\\5-roof-events",0x96A12,0x96A5C,"");
    produceAsmScriptWithExtName(file,"Map02s6_WarpEvents","data\\maps\\entries\\map02\\6-warp-events",0x96A5C,0x96A7E,"");
    produceAsmScriptWithExtName(file,"Map02s7_ChestItems","data\\maps\\entries\\map02\\7-chest-items",0x96A7E,0x96A80,"");
    produceAsmScriptWithExtName(file,"Map02s8_OtherItems","data\\maps\\entries\\map02\\8-other-items",0x96A80,0x96A8A,"");
    produceAsmSection(file,"",0x96A8A,0x97458);
    produceAsmSection(file,"",0x97458,0x977D0);
    
    produceAsmScriptWithExtName(file,"Map03","data\\maps\\entries\\map03\\00-tilesets",0x977D0,0x977D6,"");
    produceAsmSection(file,"",0x977D6,0x977FE);
    produceAsmScriptWithExtName(file,"Map03s2_Areas","data\\maps\\entries\\map03\\2-areas",0x977FE,0x9785A,"");
    produceAsmScriptWithExtName(file,"Map03s3_FlagEvents","data\\maps\\entries\\map03\\3-flag-events",0x9785A,0x9786C,"");
    produceAsmScriptWithExtName(file,"Map03s4_StepEvents","data\\maps\\entries\\map03\\4-step-events",0x9786C,0x9789E,"");
    produceAsmScriptWithExtName(file,"Map03s5_RoofEvents","data\\maps\\entries\\map03\\5-roof-events",0x9789E,0x978F0,"");
    produceAsmScriptWithExtName(file,"Map03s6_WarpEvents","data\\maps\\entries\\map03\\6-warp-events",0x978F0,0x9793A,"");
    produceAsmScriptWithExtName(file,"Map03s7_ChestItems","data\\maps\\entries\\map03\\7-chest-items",0x9793A,0x97940,"");
    produceAsmScriptWithExtName(file,"Map03s8_OtherItems","data\\maps\\entries\\map03\\8-other-items",0x97940,0x97946,"");
    produceAsmSection(file,"",0x97946,0x984E8);
    produceAsmSection(file,"",0x984E8,0x9898A);
    produceAsmScriptWithExtName(file,"Map03s9_Animations","data\\maps\\entries\\map03\\9-animations",0x9898A,0x989A0,"");
    
    produceAsmScriptWithExtName(file,"Map04","data\\maps\\entries\\map04\\00-tilesets",0x989A0,0x989A6,"");
    produceAsmSection(file,"",0x989A6,0x989CE);
    produceAsmScriptWithExtName(file,"Map04s2_Areas","data\\maps\\entries\\map04\\2-areas",0x989CE,0x989EE,"");
    produceAsmScriptWithExtName(file,"Map04s3_FlagEvents","data\\maps\\entries\\map04\\3-flag-events",0x989EE,0x98A00,"");
    produceAsmScriptWithExtName(file,"Map04s4_StepEvents","data\\maps\\entries\\map04\\4-step-events",0x98A00,0x98A02,"");
    produceAsmScriptWithExtName(file,"Map04s5_RoofEvents","data\\maps\\entries\\map04\\5-roof-events",0x98A02,0x98A24,"");
    produceAsmScriptWithExtName(file,"Map04s6_WarpEvents","data\\maps\\entries\\map04\\6-warp-events",0x98A24,0x98A3E,"");
    produceAsmScriptWithExtName(file,"Map04s7_ChestItems","data\\maps\\entries\\map04\\7-chest-items",0x98A3E,0x98A40,"");
    produceAsmScriptWithExtName(file,"Map04s8_OtherItems","data\\maps\\entries\\map04\\8-other-items",0x98A40,0x98A46,"");
    produceAsmSection(file,"",0x98A46,0x993E0);
    produceAsmSection(file,"",0x993E0,0x9965A);
    //produceAsmScript(file,"data\\maps\\entries\\map04\\9-animations",0x9898A,0x989A0,"");
    
    produceAsmScriptWithExtName(file,"Map05","data\\maps\\entries\\map05\\00-tilesets",0x9965A,0x99660,"");
    produceAsmSection(file,"",0x99660,0x99688);
    produceAsmScriptWithExtName(file,"Map05s2_Areas","data\\maps\\entries\\map05\\2-areas",0x99688,0x996C6,"");
    produceAsmScriptWithExtName(file,"Map05s3_FlagEvents","data\\maps\\entries\\map05\\3-flag-events",0x996C6,0x996D0,"");
    produceAsmScriptWithExtName(file,"Map05s4_StepEvents","data\\maps\\entries\\map05\\4-step-events",0x996D0,0x996F2,"");
    produceAsmScriptWithExtName(file,"Map05s5_RoofEvents","data\\maps\\entries\\map05\\5-roof-events",0x996F2,0x99714,"");
    produceAsmScriptWithExtName(file,"Map05s6_WarpEvents","data\\maps\\entries\\map05\\6-warp-events",0x99714,0x99746,"");
    produceAsmScriptWithExtName(file,"Map05s7_ChestItems","data\\maps\\entries\\map05\\7-chest-items",0x99746,0x99750,"");
    produceAsmScriptWithExtName(file,"Map05s8_OtherItems","data\\maps\\entries\\map05\\8-other-items",0x99750,0x99758,"");
    produceAsmSection(file,"",0x99758,0x99F90);
    produceAsmSection(file,"",0x99F90,0x9A300);
    
    produceAsmScriptWithExtName(file,"Map06","data\\maps\\entries\\map06\\00-tilesets",0x9A300,0x9A306,"");
    produceAsmSection(file,"",0x9A306,0x9A32E);
    produceAsmScriptWithExtName(file,"Map06s2_Areas","data\\maps\\entries\\map06\\2-areas",0x9A32E,0x9A34E,"");
    produceAsmScriptWithExtName(file,"Map06s3_FlagEvents","data\\maps\\entries\\map06\\3-flag-events",0x9A34E,0x9A378,"");
    produceAsmScriptWithExtName(file,"Map06s4_StepEvents","data\\maps\\entries\\map06\\4-step-events",0x9A378,0x9A3B2,"");
    produceAsmScriptWithExtName(file,"Map06s5_RoofEvents","data\\maps\\entries\\map06\\5-roof-events",0x9A3B2,0x9A3F4,"");
    produceAsmScriptWithExtName(file,"Map06s6_WarpEvents","data\\maps\\entries\\map06\\6-warp-events",0x9A3F4,0x9A40E,"");
    produceAsmScriptWithExtName(file,"Map06s7_ChestItems","data\\maps\\entries\\map06\\7-chest-items",0x9A40E,0x9A418,"");
    produceAsmScriptWithExtName(file,"Map06s8_OtherItems","data\\maps\\entries\\map06\\8-other-items",0x9A418,0x9A422,"");
    produceAsmSection(file,"",0x9A422,0x9AB8A);
    produceAsmSection(file,"",0x9AB8A,0x9AF6C);
    produceAsmScriptWithExtName(file,"Map06s9_Animations","data\\maps\\entries\\map06\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map07","data\\maps\\entries\\map07\\00-tilesets",0x9AF82,0x9AF88,"");
    produceAsmSection(file,"",0x9AF88,0x9AFB0);
    produceAsmScriptWithExtName(file,"Map07s2_Areas","data\\maps\\entries\\map07\\2-areas",0x9AFB0,0x9AFD0,"");
    produceAsmScriptWithExtName(file,"Map07s3_FlagEvents","data\\maps\\entries\\map07\\3-flag-events",0x9AFD0,0x9AFD2,"");
    produceAsmScriptWithExtName(file,"Map07s4_StepEvents","data\\maps\\entries\\map07\\4-step-events",0x9AFD2,0x9AFDC,"");
    produceAsmScriptWithExtName(file,"Map07s5_RoofEvents","data\\maps\\entries\\map07\\5-roof-events",0x9AFDC,0x9AFF6,"");
    produceAsmScriptWithExtName(file,"Map07s6_WarpEvents","data\\maps\\entries\\map07\\6-warp-events",0x9AFF6,0x9B008,"");
    produceAsmScriptWithExtName(file,"Map07s7_ChestItems","data\\maps\\entries\\map07\\7-chest-items",0x9B008,0x9B00A,"");
    produceAsmScriptWithExtName(file,"Map07s8_OtherItems","data\\maps\\entries\\map07\\8-other-items",0x9B00A,0x9B014,"");
    produceAsmSection(file,"",0x9B014,0x9B7F8);
    produceAsmSection(file,"",0x9B7F8,0x9BAC2);
    //produceAsmScript(file,"data\\maps\\entries\\map07\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map08","data\\maps\\entries\\map08\\00-tilesets",0x9BAC2,0x9BAC8,"");
    produceAsmSection(file,"",0x9BAC8,0x9BAF0);
    produceAsmScriptWithExtName(file,"Map08s2_Areas","data\\maps\\entries\\map08\\2-areas",0x9BAF0,0x9BB2E,"");
    produceAsmScriptWithExtName(file,"Map08s3_FlagEvents","data\\maps\\entries\\map08\\3-flag-events",0x9BB2E,0x9BB58,"");
    produceAsmScriptWithExtName(file,"Map08s4_StepEvents","data\\maps\\entries\\map08\\4-step-events",0x9BB58,0x9BB8A,"");
    produceAsmScriptWithExtName(file,"Map08s5_RoofEvents","data\\maps\\entries\\map08\\5-roof-events",0x9BB8A,0x9BBBC,"");
    produceAsmScriptWithExtName(file,"Map08s6_WarpEvents","data\\maps\\entries\\map08\\6-warp-events",0x9BBBC,0x9BBDE,"");
    produceAsmScriptWithExtName(file,"Map08s7_ChestItems","data\\maps\\entries\\map08\\7-chest-items",0x9BBDE,0x9BBE0,"");
    produceAsmScriptWithExtName(file,"Map08s8_OtherItems","data\\maps\\entries\\map08\\8-other-items",0x9BBE0,0x9BBEA,"");
    produceAsmSection(file,"",0x9BBEA,0x9C454);
    produceAsmSection(file,"",0x9C454,0x9C742);
    
    produceAsmScriptWithExtName(file,"Map09","data\\maps\\entries\\map09\\00-tilesets",0x9C742,0x9C748,"");
    produceAsmSection(file,"",0x9C748,0x9C770);
    produceAsmScriptWithExtName(file,"Map09s2_Areas","data\\maps\\entries\\map09\\2-areas",0x9C770,0x9C7CC,"");
    produceAsmScriptWithExtName(file,"Map09s3_FlagEvents","data\\maps\\entries\\map09\\3-flag-events",0x9C7CC,0x9C7CE,"");
    produceAsmScriptWithExtName(file,"Map09s4_StepEvents","data\\maps\\entries\\map09\\4-step-events",0x9C7CE,0x9C7F8,"");
    produceAsmScriptWithExtName(file,"Map09s5_RoofEvents","data\\maps\\entries\\map09\\5-roof-events",0x9C7F8,0x9C83A,"");
    produceAsmScriptWithExtName(file,"Map09s6_WarpEvents","data\\maps\\entries\\map09\\6-warp-events",0x9C83A,0x9C864,"");
    produceAsmScriptWithExtName(file,"Map09s7_ChestItems","data\\maps\\entries\\map09\\7-chest-items",0x9C864,0x9C86A,"");
    produceAsmScriptWithExtName(file,"Map09s8_OtherItems","data\\maps\\entries\\map09\\8-other-items",0x9C86A,0x9C874,"");
    produceAsmSection(file,"",0x9C874,0x9D1F0);
    produceAsmSection(file,"",0x9D1F0,0x9D660);
    //produceAsmScript(file,"data\\maps\\entries\\map09\\9-animations",0xA2DD0,0xA2DE6,"");
    
    produceAsmScriptWithExtName(file,"Map10","data\\maps\\entries\\map10\\00-tilesets",0x9D660,0x9D666,"");
    produceAsmSection(file,"",0x9D666,0x9D68E);
    produceAsmScriptWithExtName(file,"Map10s2_Areas","data\\maps\\entries\\map10\\2-areas",0x9D68E,0x9D726,"");
    produceAsmScriptWithExtName(file,"Map10s3_FlagEvents","data\\maps\\entries\\map10\\3-flag-events",0x9D726,0x9D728,"");
    produceAsmScriptWithExtName(file,"Map10s4_StepEvents","data\\maps\\entries\\map10\\4-step-events",0x9D728,0x9D72A,"");
    produceAsmScriptWithExtName(file,"Map10s5_RoofEvents","data\\maps\\entries\\map10\\5-roof-events",0x9D72A,0x9D72C,"");
    produceAsmScriptWithExtName(file,"Map10s6_WarpEvents","data\\maps\\entries\\map10\\6-warp-events",0x9D72C,0x9D84E,"");
    produceAsmScriptWithExtName(file,"Map10s7_ChestItems","data\\maps\\entries\\map10\\7-chest-items",0x9D84E,0x9D850,"");
    produceAsmScriptWithExtName(file,"Map10s8_OtherItems","data\\maps\\entries\\map10\\8-other-items",0x9D850,0x9D858,"");
    produceAsmSection(file,"",0x9D858,0x9E0B0);
    produceAsmSection(file,"",0x9E0B0,0x9E45A);
    //produceAsmScript(file,"data\\maps\\entries\\map10\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map11","data\\maps\\entries\\map11\\00-tilesets",0x9E45A,0x9E460,"");
    produceAsmSection(file,"",0x9E460,0x9E488);
    produceAsmScriptWithExtName(file,"Map11s2_Areas","data\\maps\\entries\\map11\\2-areas",0x9E488,0x9E4C6,"");
    produceAsmScriptWithExtName(file,"Map11s3_FlagEvents","data\\maps\\entries\\map11\\3-flag-events",0x9E4C6,0x9E4C8,"");
    produceAsmScriptWithExtName(file,"Map11s4_StepEvents","data\\maps\\entries\\map11\\4-step-events",0x9E4C8,0x9E4CA,"");
    produceAsmScriptWithExtName(file,"Map11s5_RoofEvents","data\\maps\\entries\\map11\\5-roof-events",0x9E4CA,0x9E4CC,"");
    produceAsmScriptWithExtName(file,"Map11s6_WarpEvents","data\\maps\\entries\\map11\\6-warp-events",0x9E4CC,0x9E4E6,"");
    produceAsmScriptWithExtName(file,"Map11s7_ChestItems","data\\maps\\entries\\map11\\7-chest-items",0x9E4E6,0x9E4E8,"");
    produceAsmScriptWithExtName(file,"Map11s8_OtherItems","data\\maps\\entries\\map11\\8-other-items",0x9E4E8,0x9E4EA,"");
    produceAsmSection(file,"",0x9E4EA,0x9EB9E);
    produceAsmSection(file,"",0x9EB9E,0x9ED80);
    
    produceAsmScriptWithExtName(file,"Map12","data\\maps\\entries\\map12\\00-tilesets",0x9ED80,0x9ED86,"");
    produceAsmSection(file,"",0x9ED86,0x9EDAE);
    produceAsmScriptWithExtName(file,"Map12s2_Areas","data\\maps\\entries\\map12\\2-areas",0x9EDAE,0x9EDCE,"");
    produceAsmScriptWithExtName(file,"Map12s3_FlagEvents","data\\maps\\entries\\map12\\3-flag-events",0x9EDCE,0x9EDD0,"");
    produceAsmScriptWithExtName(file,"Map12s4_StepEvents","data\\maps\\entries\\map12\\4-step-events",0x9EDD0,0x9EDD2,"");
    produceAsmScriptWithExtName(file,"Map12s5_RoofEvents","data\\maps\\entries\\map12\\5-roof-events",0x9EDD2,0x9EDD4,"");
    produceAsmScriptWithExtName(file,"Map12s6_WarpEvents","data\\maps\\entries\\map12\\6-warp-events",0x9EDD4,0x9EDDE,"");
    produceAsmScriptWithExtName(file,"Map12s7_ChestItems","data\\maps\\entries\\map12\\7-chest-items",0x9EDDE,0x9EDE4,"");
    produceAsmScriptWithExtName(file,"Map12s8_OtherItems","data\\maps\\entries\\map12\\8-other-items",0x9EDE4,0x9EDE6,"");
    produceAsmSection(file,"",0x9EDE6,0x9EFF4);
    produceAsmSection(file,"",0x9EFF4,0x9F1AA);
    
    produceAsmScriptWithExtName(file,"Map13","data\\maps\\entries\\map13\\00-tilesets",0x9F1AA,0x9F1B0,"");
    produceAsmSection(file,"",0x9F1B0,0x9F1D8);
    produceAsmScriptWithExtName(file,"Map13s2_Areas","data\\maps\\entries\\map13\\2-areas",0x9F1D8,0x9F216,"");
    produceAsmScriptWithExtName(file,"Map13s3_FlagEvents","data\\maps\\entries\\map13\\3-flag-events",0x9F216,0x9F218,"");
    produceAsmScriptWithExtName(file,"Map13s4_StepEvents","data\\maps\\entries\\map13\\4-step-events",0x9F218,0x9F23A,"");
    produceAsmScriptWithExtName(file,"Map13s5_RoofEvents","data\\maps\\entries\\map13\\5-roof-events",0x9F23A,0x9F254,"");
    produceAsmScriptWithExtName(file,"Map13s6_WarpEvents","data\\maps\\entries\\map13\\6-warp-events",0x9F254,0x9F276,"");
    produceAsmScriptWithExtName(file,"Map13s7_ChestItems","data\\maps\\entries\\map13\\7-chest-items",0x9F276,0x9F278,"");
    produceAsmScriptWithExtName(file,"Map13s8_OtherItems","data\\maps\\entries\\map13\\8-other-items",0x9F278,0x9F27E,"");
    produceAsmSection(file,"",0x9F27E,0x9F882);
    produceAsmSection(file,"",0x9F882,0x9FB38);
    
    produceAsmScriptWithExtName(file,"Map14","data\\maps\\entries\\map14\\00-tilesets",0x9FB38,0x9FB3E,"");
    produceAsmSection(file,"",0x9FB3E,0x9FB66);
    produceAsmScriptWithExtName(file,"Map14s2_Areas","data\\maps\\entries\\map14\\2-areas",0x9FB66,0x9FBE0,"");
    produceAsmScriptWithExtName(file,"Map14s3_FlagEvents","data\\maps\\entries\\map14\\3-flag-events",0x9FBE0,0x9FBE2,"");
    produceAsmScriptWithExtName(file,"Map14s4_StepEvents","data\\maps\\entries\\map14\\4-step-events",0x9FBE2,0x9FBE4,"");
    produceAsmScriptWithExtName(file,"Map14s5_RoofEvents","data\\maps\\entries\\map14\\5-roof-events",0x9FBE4,0x9FBE6,"");
    produceAsmScriptWithExtName(file,"Map14s6_WarpEvents","data\\maps\\entries\\map14\\6-warp-events",0x9FBE6,0x9FC50,"");
    produceAsmScriptWithExtName(file,"Map14s7_ChestItems","data\\maps\\entries\\map14\\7-chest-items",0x9FC50,0x9FC52,"");
    produceAsmScriptWithExtName(file,"Map14s8_OtherItems","data\\maps\\entries\\map14\\8-other-items",0x9FC52,0x9FC5C,"");
    produceAsmSection(file,"",0x9FC5C,0xA02B4);
    produceAsmSection(file,"",0xA02B4,0xA057E);
    produceAsmScriptWithExtName(file,"Map14s9_Animations","data\\maps\\entries\\map14\\9-animations",0xA057E,0xA0594,"");
    
    produceAsmScriptWithExtName(file,"Map15","data\\maps\\entries\\map15\\00-tilesets",0xA0594,0xA059A,"");
    produceAsmSection(file,"",0xA059A,0xA05C2);
    produceAsmScriptWithExtName(file,"Map15s2_Areas","data\\maps\\entries\\map15\\2-areas",0xA05C2,0xA05E2,"");
    produceAsmScriptWithExtName(file,"Map15s3_FlagEvents","data\\maps\\entries\\map15\\3-flag-events",0xA05E2,0xA05E4,"");
    produceAsmScriptWithExtName(file,"Map15s4_StepEvents","data\\maps\\entries\\map15\\4-step-events",0xA05E4,0xA0606,"");
    produceAsmScriptWithExtName(file,"Map15s5_RoofEvents","data\\maps\\entries\\map15\\5-roof-events",0xA0606,0xA0628,"");
    produceAsmScriptWithExtName(file,"Map15s6_WarpEvents","data\\maps\\entries\\map15\\6-warp-events",0xA0628,0xA0652,"");
    produceAsmScriptWithExtName(file,"Map15s7_ChestItems","data\\maps\\entries\\map15\\7-chest-items",0xA0652,0xA0654,"");
    produceAsmScriptWithExtName(file,"Map15s8_OtherItems","data\\maps\\entries\\map15\\8-other-items",0xA0654,0xA0656,"");
    produceAsmSection(file,"",0xA0656,0xA11DA);
    produceAsmSection(file,"",0xA11DA,0xA1516);
    produceAsmScriptWithExtName(file,"Map15s9_Animations","data\\maps\\entries\\map15\\9-animations",0xA1516,0xA152C,"");
    
    produceAsmScriptWithExtName(file,"Map16","data\\maps\\entries\\map16\\00-tilesets",0xA152C,0xA1532,"");
    produceAsmSection(file,"",0xA1532,0xA155A);
    produceAsmScriptWithExtName(file,"Map16s2_Areas","data\\maps\\entries\\map16\\2-areas",0xA155A,0xA157A,"");
    produceAsmScriptWithExtName(file,"Map16s3_FlagEvents","data\\maps\\entries\\map16\\3-flag-events",0xA157A,0xA1594,"");
    produceAsmScriptWithExtName(file,"Map16s4_StepEvents","data\\maps\\entries\\map16\\4-step-events",0xA1594,0xA15CE,"");
    produceAsmScriptWithExtName(file,"Map16s5_RoofEvents","data\\maps\\entries\\map16\\5-roof-events",0xA15CE,0xA1618,"");
    produceAsmScriptWithExtName(file,"Map16s6_WarpEvents","data\\maps\\entries\\map16\\6-warp-events",0xA1618,0xA166A,"");
    produceAsmScriptWithExtName(file,"Map16s7_ChestItems","data\\maps\\entries\\map16\\7-chest-items",0xA166A,0xA167C,"");
    produceAsmScriptWithExtName(file,"Map16s8_OtherItems","data\\maps\\entries\\map16\\8-other-items",0xA167C,0xA1682,"");
    produceAsmSection(file,"",0xA1682,0xA280E);
    produceAsmSection(file,"",0xA280E,0xA2DD0);
    produceAsmScriptWithExtName(file,"Map16s9_Animations","data\\maps\\entries\\map16\\9-animations",0xA2DD0,0xA2DE6,"");
    
    produceAsmScriptWithExtName(file,"Map17","data\\maps\\entries\\map17\\00-tilesets",0xA2DE6,0xA2DEC,"");
    produceAsmSection(file,"",0xA2DEC,0xA2E14);
    produceAsmScriptWithExtName(file,"Map17s2_Areas","data\\maps\\entries\\map17\\2-areas",0xA2E14,0xA2EAC,"");
    produceAsmScriptWithExtName(file,"Map17s3_FlagEvents","data\\maps\\entries\\map17\\3-flag-events",0xA2EAC,0xA2EB6,"");
    produceAsmScriptWithExtName(file,"Map17s4_StepEvents","data\\maps\\entries\\map17\\4-step-events",0xA2EB6,0xA2EB8,"");
    produceAsmScriptWithExtName(file,"Map17s5_RoofEvents","data\\maps\\entries\\map17\\5-roof-events",0xA2EB8,0xA2EBA,"");
    produceAsmScriptWithExtName(file,"Map17s6_WarpEvents","data\\maps\\entries\\map17\\6-warp-events",0xA2EBA,0xA2F2C,"");
    produceAsmScriptWithExtName(file,"Map17s7_ChestItems","data\\maps\\entries\\map17\\7-chest-items",0xA2F2C,0xA2F2E,"");
    produceAsmScriptWithExtName(file,"Map17s8_OtherItems","data\\maps\\entries\\map17\\8-other-items",0xA2F2E,0xA2F38,"");
    produceAsmSection(file,"",0xA2F38,0xA36FC);
    produceAsmSection(file,"",0xA36FC,0xA3952);
    
    produceAsmScriptWithExtName(file,"Map18","data\\maps\\entries\\map18\\00-tilesets",0xA3952,0xA3958,"");
    produceAsmSection(file,"",0xA3958,0xA3980);
    produceAsmScriptWithExtName(file,"Map18s2_Areas","data\\maps\\entries\\map18\\2-areas",0xA3980,0xA39DC,"");
    produceAsmScriptWithExtName(file,"Map18s3_FlagEvents","data\\maps\\entries\\map18\\3-flag-events",0xA39DC,0xA39EE,"");
    produceAsmScriptWithExtName(file,"Map18s4_StepEvents","data\\maps\\entries\\map18\\4-step-events",0xA39EE,0xA39F0,"");
    produceAsmScriptWithExtName(file,"Map18s5_RoofEvents","data\\maps\\entries\\map18\\5-roof-events",0xA39F0,0xA3A0A,"");
    produceAsmScriptWithExtName(file,"Map18s6_WarpEvents","data\\maps\\entries\\map18\\6-warp-events",0xA3A0A,0xA3A2C,"");
    produceAsmScriptWithExtName(file,"Map18s7_ChestItems","data\\maps\\entries\\map18\\7-chest-items",0xA3A2C,0xA3A2E,"");
    produceAsmScriptWithExtName(file,"Map18s8_OtherItems","data\\maps\\entries\\map18\\8-other-items",0xA3A2E,0xA3A30,"");
    produceAsmSection(file,"",0xA3A30,0xA41AA);
    produceAsmSection(file,"",0xA41AA,0xA45B2);
    
    produceAsmScriptWithExtName(file,"Map19","data\\maps\\entries\\map19\\00-tilesets",0xA45B2,0xA45B8,"");
    produceAsmSection(file,"",0xA45B8,0xA45E0);
    produceAsmScriptWithExtName(file,"Map19s2_Areas","data\\maps\\entries\\map19\\2-areas",0xA45E0,0xA4600,"");
    produceAsmScriptWithExtName(file,"Map19s3_FlagEvents","data\\maps\\entries\\map19\\3-flag-events",0xA4600,0xA4602,"");
    produceAsmScriptWithExtName(file,"Map19s4_StepEvents","data\\maps\\entries\\map19\\4-step-events",0xA4602,0xA4614,"");
    produceAsmScriptWithExtName(file,"Map19s5_RoofEvents","data\\maps\\entries\\map19\\5-roof-events",0xA4614,0xA464E,"");
    produceAsmScriptWithExtName(file,"Map19s6_WarpEvents","data\\maps\\entries\\map19\\6-warp-events",0xA464E,0xA4688,"");
    produceAsmScriptWithExtName(file,"Map19s7_ChestItems","data\\maps\\entries\\map19\\7-chest-items",0xA4688,0xA4696,"");
    produceAsmScriptWithExtName(file,"Map19s8_OtherItems","data\\maps\\entries\\map19\\8-other-items",0xA4696,0xA4698,"");
    produceAsmSection(file,"",0xA4698,0xA5076);
    produceAsmSection(file,"",0xA5076,0xA534A);
    
    produceAsmScriptWithExtName(file,"Map20","data\\maps\\entries\\map20\\00-tilesets",0xA534A,0xA5350,"");
    produceAsmSection(file,"",0xA5350,0xA5378);
    produceAsmScriptWithExtName(file,"Map20s2_Areas","data\\maps\\entries\\map20\\2-areas",0xA5378,0xA53D4,"");
    produceAsmScriptWithExtName(file,"Map20s3_FlagEvents","data\\maps\\entries\\map20\\3-flag-events",0xA53D4,0xA53D6,"");
    produceAsmScriptWithExtName(file,"Map20s4_StepEvents","data\\maps\\entries\\map20\\4-step-events",0xA53D6,0xA53D8,"");
    produceAsmScriptWithExtName(file,"Map20s5_RoofEvents","data\\maps\\entries\\map20\\5-roof-events",0xA53D8,0xA53DA,"");
    produceAsmScriptWithExtName(file,"Map20s6_WarpEvents","data\\maps\\entries\\map20\\6-warp-events",0xA53DA,0xA5434,"");
    produceAsmScriptWithExtName(file,"Map20s7_ChestItems","data\\maps\\entries\\map20\\7-chest-items",0xA5434,0xA5436,"");
    produceAsmScriptWithExtName(file,"Map20s8_OtherItems","data\\maps\\entries\\map20\\8-other-items",0xA5436,0xA5438,"");
    produceAsmSection(file,"",0xA5438,0xA5E9C);
    produceAsmSection(file,"",0xA5E9C,0xA61A4);
    
    produceAsmScriptWithExtName(file,"Map21","data\\maps\\entries\\map21\\00-tilesets",0xA61A4,0xA61AA,"");
    produceAsmSection(file,"",0xA61AA,0xA61D2);
    produceAsmScriptWithExtName(file,"Map21s2_Areas","data\\maps\\entries\\map21\\2-areas",0xA61D2,0xA61F2,"");
    produceAsmScriptWithExtName(file,"Map21s3_FlagEvents","data\\maps\\entries\\map21\\3-flag-events",0xA61F2,0xA61F4,"");
    produceAsmScriptWithExtName(file,"Map21s4_StepEvents","data\\maps\\entries\\map21\\4-step-events",0xA61F4,0xA61F6,"");
    produceAsmScriptWithExtName(file,"Map21s5_RoofEvents","data\\maps\\entries\\map21\\5-roof-events",0xA61F6,0xA61F8,"");
    produceAsmScriptWithExtName(file,"Map21s6_WarpEvents","data\\maps\\entries\\map21\\6-warp-events",0xA61F8,0xA620A,"");
    produceAsmScriptWithExtName(file,"Map21s7_ChestItems","data\\maps\\entries\\map21\\7-chest-items",0xA620A,0xA620C,"");
    produceAsmScriptWithExtName(file,"Map21s8_OtherItems","data\\maps\\entries\\map21\\8-other-items",0xA620C,0xA620E,"");
    produceAsmSection(file,"",0xA620E,0xA63C4);
    produceAsmSection(file,"",0xA63C4,0xA6438);
    
    produceAsmScriptWithExtName(file,"Map22","data\\maps\\entries\\map22\\00-tilesets",0xA6438,0xA643E,"");
    produceAsmSection(file,"",0xA643E,0xA6466);
    produceAsmScriptWithExtName(file,"Map22s2_Areas","data\\maps\\entries\\map22\\2-areas",0xA6466,0xA6486,"");
    produceAsmScriptWithExtName(file,"Map22s3_FlagEvents","data\\maps\\entries\\map22\\3-flag-events",0xA6486,0xA6498,"");
    produceAsmScriptWithExtName(file,"Map22s4_StepEvents","data\\maps\\entries\\map22\\4-step-events",0xA6498,0xA649A,"");
    produceAsmScriptWithExtName(file,"Map22s5_RoofEvents","data\\maps\\entries\\map22\\5-roof-events",0xA649A,0xA649C,"");
    produceAsmScriptWithExtName(file,"Map22s6_WarpEvents","data\\maps\\entries\\map22\\6-warp-events",0xA649C,0xA649E,"");
    produceAsmScriptWithExtName(file,"Map22s7_ChestItems","data\\maps\\entries\\map22\\7-chest-items",0xA649E,0xA64A4,"");
    produceAsmScriptWithExtName(file,"Map22s8_OtherItems","data\\maps\\entries\\map22\\8-other-items",0xA64A4,0xA64A6,"");
    produceAsmSection(file,"",0xA64A6,0xA6B92);
    produceAsmSection(file,"",0xA6B92,0xA6E1A);
    
    produceAsmScriptWithExtName(file,"Map23","data\\maps\\entries\\map23\\00-tilesets",0xA6E1A,0xA6E20,"");
    produceAsmSection(file,"",0xA6E20,0xA6E48);
    produceAsmScriptWithExtName(file,"Map23s2_Areas","data\\maps\\entries\\map23\\2-areas",0xA6E48,0xA6E86,"");
    produceAsmScriptWithExtName(file,"Map23s3_FlagEvents","data\\maps\\entries\\map23\\3-flag-events",0xA6E86,0xA6E88,"");
    produceAsmScriptWithExtName(file,"Map23s4_StepEvents","data\\maps\\entries\\map23\\4-step-events",0xA6E88,0xA6EAA,"");
    produceAsmScriptWithExtName(file,"Map23s5_RoofEvents","data\\maps\\entries\\map23\\5-roof-events",0xA6EAA,0xA6ECC,"");
    produceAsmScriptWithExtName(file,"Map23s6_WarpEvents","data\\maps\\entries\\map23\\6-warp-events",0xA6ECC,0xA6EFE,"");
    produceAsmScriptWithExtName(file,"Map23s7_ChestItems","data\\maps\\entries\\map23\\7-chest-items",0xA6EFE,0xA6F08,"");
    produceAsmScriptWithExtName(file,"Map23s8_OtherItems","data\\maps\\entries\\map23\\8-other-items",0xA6F08,0xA6F12,"");
    produceAsmSection(file,"",0xA6F12,0xA7B26);
    produceAsmSection(file,"",0xA7B26,0xA81D4);
    //produceAsmScript(file,"data\\maps\\entries\\map23\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map24","data\\maps\\entries\\map24\\00-tilesets",0xA81D4,0xA81DA,"");
    produceAsmSection(file,"",0xA81DA,0xA8202);
    produceAsmScriptWithExtName(file,"Map24s2_Areas","data\\maps\\entries\\map24\\2-areas",0xA8202,0xA8222,"");
    produceAsmScriptWithExtName(file,"Map24s3_FlagEvents","data\\maps\\entries\\map24\\3-flag-events",0xA8222,0xA822C,"");
    produceAsmScriptWithExtName(file,"Map24s4_StepEvents","data\\maps\\entries\\map24\\4-step-events",0xA822C,0xA822E,"");
    produceAsmScriptWithExtName(file,"Map24s5_RoofEvents","data\\maps\\entries\\map24\\5-roof-events",0xA822E,0xA8230,"");
    produceAsmScriptWithExtName(file,"Map24s6_WarpEvents","data\\maps\\entries\\map24\\6-warp-events",0xA8230,0xA823A,"");
    produceAsmScriptWithExtName(file,"Map24s7_ChestItems","data\\maps\\entries\\map24\\7-chest-items",0xA823A,0xA8244,"");
    produceAsmScriptWithExtName(file,"Map24s8_OtherItems","data\\maps\\entries\\map24\\8-other-items",0xA8244,0xA8246,"");
    
    produceAsmScriptWithExtName(file,"Map25","data\\maps\\entries\\map25\\00-tilesets",0xA8246,0xA824C,"");
    produceAsmSection(file,"",0xA824C,0xA8274);
    produceAsmScriptWithExtName(file,"Map25s2_Areas","data\\maps\\entries\\map25\\2-areas",0xA8274,0xA82B2,"");
    produceAsmScriptWithExtName(file,"Map25s3_FlagEvents","data\\maps\\entries\\map25\\3-flag-events",0xA82B2,0xA82B4,"");
    produceAsmScriptWithExtName(file,"Map25s4_StepEvents","data\\maps\\entries\\map25\\4-step-events",0xA82B4,0xA82DE,"");
    produceAsmScriptWithExtName(file,"Map25s5_RoofEvents","data\\maps\\entries\\map25\\5-roof-events",0xA82DE,0xA8308,"");
    produceAsmScriptWithExtName(file,"Map25s6_WarpEvents","data\\maps\\entries\\map25\\6-warp-events",0xA8308,0xA8312,"");
    produceAsmScriptWithExtName(file,"Map25s7_ChestItems","data\\maps\\entries\\map25\\7-chest-items",0xA8312,0xA8314,"");
    produceAsmScriptWithExtName(file,"Map25s8_OtherItems","data\\maps\\entries\\map25\\8-other-items",0xA8314,0xA831E,"");
    produceAsmSection(file,"",0xA831E,0xA893C);
    produceAsmSection(file,"",0xA893C,0xA8C58);
    //produceAsmScript(file,"data\\maps\\entries\\map25\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map26","data\\maps\\entries\\map26\\00-tilesets",0xA8C58,0xA8C5E,"");
    produceAsmSection(file,"",0xA8C5E,0xA8C86);
    produceAsmScriptWithExtName(file,"Map26s2_Areas","data\\maps\\entries\\map26\\2-areas",0xA8C86,0xA8CC4,"");
    produceAsmScriptWithExtName(file,"Map26s3_FlagEvents","data\\maps\\entries\\map26\\3-flag-events",0xA8CC4,0xA8CC6,"");
    produceAsmScriptWithExtName(file,"Map26s4_StepEvents","data\\maps\\entries\\map26\\4-step-events",0xA8CC6,0xA8CD0,"");
    produceAsmScriptWithExtName(file,"Map26s5_RoofEvents","data\\maps\\entries\\map26\\5-roof-events",0xA8CD0,0xA8CD2,"");
    produceAsmScriptWithExtName(file,"Map26s6_WarpEvents","data\\maps\\entries\\map26\\6-warp-events",0xA8CD2,0xA8CEC,"");
    produceAsmScriptWithExtName(file,"Map26s7_ChestItems","data\\maps\\entries\\map26\\7-chest-items",0xA8CEC,0xA8CEE,"");
    produceAsmScriptWithExtName(file,"Map26s8_OtherItems","data\\maps\\entries\\map26\\8-other-items",0xA8CEE,0xA8CF0,"");
    produceAsmSection(file,"",0xA8CF0,0xA915E);
    produceAsmSection(file,"",0xA915E,0xA9384);
    
    produceAsmScriptWithExtName(file,"Map27","data\\maps\\entries\\map27\\00-tilesets",0xA9384,0xA938A,"");
    produceAsmSection(file,"",0xA938A,0xA93B2);
    produceAsmScriptWithExtName(file,"Map27s2_Areas","data\\maps\\entries\\map27\\2-areas",0xA93B2,0xA93F0,"");
    produceAsmScriptWithExtName(file,"Map27s3_FlagEvents","data\\maps\\entries\\map27\\3-flag-events",0xA93F0,0xA93F2,"");
    produceAsmScriptWithExtName(file,"Map27s4_StepEvents","data\\maps\\entries\\map27\\4-step-events",0xA93F2,0xA93F4,"");
    produceAsmScriptWithExtName(file,"Map27s5_RoofEvents","data\\maps\\entries\\map27\\5-roof-events",0xA93F4,0xA93F6,"");
    produceAsmScriptWithExtName(file,"Map27s6_WarpEvents","data\\maps\\entries\\map27\\6-warp-events",0xA93F6,0xA9438,"");
    produceAsmScriptWithExtName(file,"Map27s7_ChestItems","data\\maps\\entries\\map27\\7-chest-items",0xA9438,0xA943A,"");
    produceAsmScriptWithExtName(file,"Map27s8_OtherItems","data\\maps\\entries\\map27\\8-other-items",0xA943A,0xA943C,"");
    produceAsmSection(file,"",0xA943C,0xA995A);
    produceAsmSection(file,"",0xA995A,0xA9C00);
    
    produceAsmScriptWithExtName(file,"Map28","data\\maps\\entries\\map28\\00-tilesets",0xA9C00,0xA9C06,"");
    produceAsmSection(file,"",0xA9C06,0xA9C2E);
    produceAsmScriptWithExtName(file,"Map28s2_Areas","data\\maps\\entries\\map28\\2-areas",0xA9C2E,0xA9C4E,"");
    produceAsmScriptWithExtName(file,"Map28s3_FlagEvents","data\\maps\\entries\\map28\\3-flag-events",0xA9C4E,0xA9C58,"");
    produceAsmScriptWithExtName(file,"Map28s4_StepEvents","data\\maps\\entries\\map28\\4-step-events",0xA9C58,0xA9C6A,"");
    produceAsmScriptWithExtName(file,"Map28s5_RoofEvents","data\\maps\\entries\\map28\\5-roof-events",0xA9C6A,0xA9C6C,"");
    produceAsmScriptWithExtName(file,"Map28s6_WarpEvents","data\\maps\\entries\\map28\\6-warp-events",0xA9C6C,0xA9C7E,"");
    produceAsmScriptWithExtName(file,"Map28s7_ChestItems","data\\maps\\entries\\map28\\7-chest-items",0xA9C7E,0xA9C80,"");
    produceAsmScriptWithExtName(file,"Map28s8_OtherItems","data\\maps\\entries\\map28\\8-other-items",0xA9C80,0xA9C82,"");
    produceAsmSection(file,"",0xA9C82,0xAA3A2);
    produceAsmSection(file,"",0xAA3A2,0xAA898);
    produceAsmScriptWithExtName(file,"Map28s9_Animations","data\\maps\\entries\\map28\\9-animations",0xAA898,0xAA8BE,"");
    
    produceAsmScriptWithExtName(file,"Map29","data\\maps\\entries\\map29\\00-tilesets",0xAA8BE,0xAA8C4,"");
    produceAsmSection(file,"",0xAA8C4,0xAA8EC);
    produceAsmScriptWithExtName(file,"Map29s2_Areas","data\\maps\\entries\\map29\\2-areas",0xAA8EC,0xAA92A,"");
    produceAsmScriptWithExtName(file,"Map29s3_FlagEvents","data\\maps\\entries\\map29\\3-flag-events",0xAA92A,0xAA92C,"");
    produceAsmScriptWithExtName(file,"Map29s4_StepEvents","data\\maps\\entries\\map29\\4-step-events",0xAA92C,0xAA92E,"");
    produceAsmScriptWithExtName(file,"Map29s5_RoofEvents","data\\maps\\entries\\map29\\5-roof-events",0xAA92E,0xAA930,"");
    produceAsmScriptWithExtName(file,"Map29s6_WarpEvents","data\\maps\\entries\\map29\\6-warp-events",0xAA930,0xAA9C2,"");
    produceAsmScriptWithExtName(file,"Map29s7_ChestItems","data\\maps\\entries\\map29\\7-chest-items",0xAA9C2,0xAA9CC,"");
    produceAsmScriptWithExtName(file,"Map29s8_OtherItems","data\\maps\\entries\\map29\\8-other-items",0xAA9CC,0xAA9D2,"");
    produceAsmSection(file,"",0xAA9D2,0xAAF78);
    produceAsmSection(file,"",0xAAF78,0xAB332);
    produceAsmScriptWithExtName(file,"Map29s9_Animations","data\\maps\\entries\\map29\\9-animations",0xAB332,0xAB348,"");
    
    produceAsmScriptWithExtName(file,"Map30","data\\maps\\entries\\map30\\00-tilesets",0xAB348,0xAB34E,"");
    produceAsmSection(file,"",0xAB34E,0xAB376);
    produceAsmScriptWithExtName(file,"Map30s2_Areas","data\\maps\\entries\\map30\\2-areas",0xAB376,0xAB396,"");
    produceAsmScriptWithExtName(file,"Map30s3_FlagEvents","data\\maps\\entries\\map30\\3-flag-events",0xAB396,0xAB398,"");
    produceAsmScriptWithExtName(file,"Map30s4_StepEvents","data\\maps\\entries\\map30\\4-step-events",0xAB398,0xAB39A,"");
    produceAsmScriptWithExtName(file,"Map30s5_RoofEvents","data\\maps\\entries\\map30\\5-roof-events",0xAB39A,0xAB39C,"");
    produceAsmScriptWithExtName(file,"Map30s6_WarpEvents","data\\maps\\entries\\map30\\6-warp-events",0xAB39C,0xAB3A6,"");
    produceAsmScriptWithExtName(file,"Map30s7_ChestItems","data\\maps\\entries\\map30\\7-chest-items",0xAB3A6,0xAB3A8,"");
    produceAsmScriptWithExtName(file,"Map30s8_OtherItems","data\\maps\\entries\\map30\\8-other-items",0xAB3A8,0xAB3AE,"");
    produceAsmSection(file,"",0xAB3AE,0xAB564);
    produceAsmSection(file,"",0xAB564,0xAB610);
    
    produceAsmScriptWithExtName(file,"Map31","data\\maps\\entries\\map31\\00-tilesets",0xAB610,0xAB616,"");
    produceAsmSection(file,"",0xAB616,0xAB63E);
    produceAsmScriptWithExtName(file,"Map31s2_Areas","data\\maps\\entries\\map31\\2-areas",0xAB63E,0xAB65E,"");
    produceAsmScriptWithExtName(file,"Map31s3_FlagEvents","data\\maps\\entries\\map31\\3-flag-events",0xAB65E,0xAB670,"");
    produceAsmScriptWithExtName(file,"Map31s4_StepEvents","data\\maps\\entries\\map31\\4-step-events",0xAB670,0xAB69A,"");
    produceAsmScriptWithExtName(file,"Map31s5_RoofEvents","data\\maps\\entries\\map31\\5-roof-events",0xAB69A,0xAB6C4,"");
    produceAsmScriptWithExtName(file,"Map31s6_WarpEvents","data\\maps\\entries\\map31\\6-warp-events",0xAB6C4,0xAB6EE,"");
    produceAsmScriptWithExtName(file,"Map31s7_ChestItems","data\\maps\\entries\\map31\\7-chest-items",0xAB6EE,0xAB6F0,"");
    produceAsmScriptWithExtName(file,"Map31s8_OtherItems","data\\maps\\entries\\map31\\8-other-items",0xAB6F0,0xAB6F2,"");
    produceAsmSection(file,"",0xAB6F2,0xABF98);
    produceAsmSection(file,"",0xABF98,0xAC32C);
    
    produceAsmScriptWithExtName(file,"Map32","data\\maps\\entries\\map32\\00-tilesets",0xAC32C,0xAC332,"");
    produceAsmSection(file,"",0xAC332,0xAC35A);
    produceAsmScriptWithExtName(file,"Map32s2_Areas","data\\maps\\entries\\map32\\2-areas",0xAC35A,0xAC37A,"");
    produceAsmScriptWithExtName(file,"Map32s3_FlagEvents","data\\maps\\entries\\map32\\3-flag-events",0xAC37A,0xAC37C,"");
    produceAsmScriptWithExtName(file,"Map32s4_StepEvents","data\\maps\\entries\\map32\\4-step-events",0xAC37C,0xAC37E,"");
    produceAsmScriptWithExtName(file,"Map32s5_RoofEvents","data\\maps\\entries\\map32\\5-roof-events",0xAC37E,0xAC380,"");
    produceAsmScriptWithExtName(file,"Map32s6_WarpEvents","data\\maps\\entries\\map32\\6-warp-events",0xAC380,0xAC392,"");
    produceAsmScriptWithExtName(file,"Map32s7_ChestItems","data\\maps\\entries\\map32\\7-chest-items",0xAC392,0xAC3A4,"");
    produceAsmScriptWithExtName(file,"Map32s8_OtherItems","data\\maps\\entries\\map32\\8-other-items",0xAC3A4,0xAC3A6,"");
    produceAsmSection(file,"",0xAC3A6,0xAC554);
    produceAsmSection(file,"",0xAC554,0xAC642);
    
    produceAsmScriptWithExtName(file,"Map33","data\\maps\\entries\\map33\\00-tilesets",0xAC642,0xAC648,"");
    produceAsmSection(file,"",0xAC648,0xAC670);
    produceAsmScriptWithExtName(file,"Map33s2_Areas","data\\maps\\entries\\map33\\2-areas",0xAC670,0xAC6CC,"");
    produceAsmScriptWithExtName(file,"Map33s3_FlagEvents","data\\maps\\entries\\map33\\3-flag-events",0xAC6CC,0xAC6D6,"");
    produceAsmScriptWithExtName(file,"Map33s4_StepEvents","data\\maps\\entries\\map33\\4-step-events",0xAC6D6,0xAC700,"");
    produceAsmScriptWithExtName(file,"Map33s5_RoofEvents","data\\maps\\entries\\map33\\5-roof-events",0xAC700,0xAC722,"");
    produceAsmScriptWithExtName(file,"Map33s6_WarpEvents","data\\maps\\entries\\map33\\6-warp-events",0xAC722,0xAC734,"");
    produceAsmScriptWithExtName(file,"Map33s7_ChestItems","data\\maps\\entries\\map33\\7-chest-items",0xAC734,0xAC73A,"");
    produceAsmScriptWithExtName(file,"Map33s8_OtherItems","data\\maps\\entries\\map33\\8-other-items",0xAC73A,0xAC748,"");
    produceAsmSection(file,"",0xAC748,0xAD04C);
    produceAsmSection(file,"",0xAD04C,0xAD410);
    produceAsmScriptWithExtName(file,"Map33s9_Animations","data\\maps\\entries\\map33\\9-animations",0xAD410,0xAD426,"");
    
    produceAsmScriptWithExtName(file,"Map34","data\\maps\\entries\\map34\\00-tilesets",0xAD426,0xAD42C,"");
    produceAsmSection(file,"",0xAD42C,0xAD454);
    produceAsmScriptWithExtName(file,"Map34s2_Areas","data\\maps\\entries\\map34\\2-areas",0xAD454,0xAD492,"");
    produceAsmScriptWithExtName(file,"Map34s3_FlagEvents","data\\maps\\entries\\map34\\3-flag-events",0xAD492,0xAD494,"");
    produceAsmScriptWithExtName(file,"Map34s4_StepEvents","data\\maps\\entries\\map34\\4-step-events",0xAD494,0xAD496,"");
    produceAsmScriptWithExtName(file,"Map34s5_RoofEvents","data\\maps\\entries\\map34\\5-roof-events",0xAD496,0xAD498,"");
    produceAsmScriptWithExtName(file,"Map34s6_WarpEvents","data\\maps\\entries\\map34\\6-warp-events",0xAD498,0xAD4B2,"");
    produceAsmScriptWithExtName(file,"Map34s7_ChestItems","data\\maps\\entries\\map34\\7-chest-items",0xAD4B2,0xAD4B4,"");
    produceAsmScriptWithExtName(file,"Map34s8_OtherItems","data\\maps\\entries\\map34\\8-other-items",0xAD4B4,0xAD4B6,"");
    produceAsmSection(file,"",0xAD4B6,0xAD8D6);
    produceAsmSection(file,"",0xAD8D6,0xADA40);
    produceAsmScriptWithExtName(file,"Map34s9_Animations","data\\maps\\entries\\map34\\9-animations",0xADA40,0xADA66,"");
    
    produceAsmScriptWithExtName(file,"Map35","data\\maps\\entries\\map35\\00-tilesets",0xADA66,0xADA6C,"");
    produceAsmSection(file,"",0xADA6C,0xADA94);
    produceAsmScriptWithExtName(file,"Map35s2_Areas","data\\maps\\entries\\map35\\2-areas",0xADA94,0xADAB4,"");
    produceAsmScriptWithExtName(file,"Map35s3_FlagEvents","data\\maps\\entries\\map35\\3-flag-events",0xADAB4,0xADAB6,"");
    produceAsmScriptWithExtName(file,"Map35s4_StepEvents","data\\maps\\entries\\map35\\4-step-events",0xADAB6,0xADAB8,"");
    produceAsmScriptWithExtName(file,"Map35s5_RoofEvents","data\\maps\\entries\\map35\\5-roof-events",0xADAB8,0xADABA,"");
    produceAsmScriptWithExtName(file,"Map35s6_WarpEvents","data\\maps\\entries\\map35\\6-warp-events",0xADABA,0xADB1C,"");
    produceAsmScriptWithExtName(file,"Map35s7_ChestItems","data\\maps\\entries\\map35\\7-chest-items",0xADB1C,0xADB2A,"");
    produceAsmScriptWithExtName(file,"Map35s8_OtherItems","data\\maps\\entries\\map35\\8-other-items",0xADB2A,0xADB2C,"");
    produceAsmSection(file,"",0xADB2C,0xADDC6);
    produceAsmSection(file,"",0xADDC6,0xADF6E);
    
    produceAsmScriptWithExtName(file,"Map36","data\\maps\\entries\\map36\\00-tilesets",0xADF6E,0xADF74,"");
    produceAsmSection(file,"",0xADF74,0xADF9C);
    produceAsmScriptWithExtName(file,"Map36s2_Areas","data\\maps\\entries\\map36\\2-areas",0xADF9C,0xADFDA,"");
    produceAsmScriptWithExtName(file,"Map36s3_FlagEvents","data\\maps\\entries\\map36\\3-flag-events",0xADFDA,0xADFDC,"");
    produceAsmScriptWithExtName(file,"Map36s4_StepEvents","data\\maps\\entries\\map36\\4-step-events",0xADFDC,0xAE006,"");
    produceAsmScriptWithExtName(file,"Map36s5_RoofEvents","data\\maps\\entries\\map36\\5-roof-events",0xAE006,0xAE050,"");
    produceAsmScriptWithExtName(file,"Map36s6_WarpEvents","data\\maps\\entries\\map36\\6-warp-events",0xAE050,0xAE07A,"");
    produceAsmScriptWithExtName(file,"Map36s7_ChestItems","data\\maps\\entries\\map36\\7-chest-items",0xAE07A,0xAE080,"");
    produceAsmScriptWithExtName(file,"Map36s8_OtherItems","data\\maps\\entries\\map36\\8-other-items",0xAE080,0xAE08A,"");
    produceAsmSection(file,"",0xAE08A,0xAEA3E);
    produceAsmSection(file,"",0xAEA3E,0xAEE9E);
    
    produceAsmScriptWithExtName(file,"Map37","data\\maps\\entries\\map37\\00-tilesets",0xAEE9E,0xAEEA4,"");
    produceAsmSection(file,"",0xAEEA4,0xAEECC);
    produceAsmScriptWithExtName(file,"Map37s2_Areas","data\\maps\\entries\\map37\\2-areas",0xAEECC,0xAEEEC,"");
    produceAsmScriptWithExtName(file,"Map37s3_FlagEvents","data\\maps\\entries\\map37\\3-flag-events",0xAEEEC,0xAEEEE,"");
    produceAsmScriptWithExtName(file,"Map37s4_StepEvents","data\\maps\\entries\\map37\\4-step-events",0xAEEEE,0xAEEF0,"");
    produceAsmScriptWithExtName(file,"Map37s5_RoofEvents","data\\maps\\entries\\map37\\5-roof-events",0xAEEF0,0xAEEF2,"");
    produceAsmScriptWithExtName(file,"Map37s6_WarpEvents","data\\maps\\entries\\map37\\6-warp-events",0xAEEF2,0xAEEFC,"");
    produceAsmScriptWithExtName(file,"Map37s7_ChestItems","data\\maps\\entries\\map37\\7-chest-items",0xAEEFC,0xAEF02,"");
    produceAsmScriptWithExtName(file,"Map37s8_OtherItems","data\\maps\\entries\\map37\\8-other-items",0xAEF02,0xAEF04,"");
    produceAsmSection(file,"",0xAEF04,0xAF894);
    produceAsmSection(file,"",0xAF894,0xAFBE8);
    
    produceAsmScriptWithExtName(file,"Map38","data\\maps\\entries\\map38\\00-tilesets",0xAFBE8,0xAFBEE,"");
    produceAsmSection(file,"",0xAFBEE,0xAFC16);
    produceAsmScriptWithExtName(file,"Map38s2_Areas","data\\maps\\entries\\map38\\2-areas",0xAFC16,0xAFC90,"");
    produceAsmScriptWithExtName(file,"Map38s3_FlagEvents","data\\maps\\entries\\map38\\3-flag-events",0xAFC90,0xAFC92,"");
    produceAsmScriptWithExtName(file,"Map38s4_StepEvents","data\\maps\\entries\\map38\\4-step-events",0xAFC92,0xAFCBC,"");
    produceAsmScriptWithExtName(file,"Map38s5_RoofEvents","data\\maps\\entries\\map38\\5-roof-events",0xAFCBC,0xAFCD6,"");
    produceAsmScriptWithExtName(file,"Map38s6_WarpEvents","data\\maps\\entries\\map38\\6-warp-events",0xAFCD6,0xAFD20,"");
    produceAsmScriptWithExtName(file,"Map38s7_ChestItems","data\\maps\\entries\\map38\\7-chest-items",0xAFD20,0xAFD2A,"");
    produceAsmScriptWithExtName(file,"Map38s8_OtherItems","data\\maps\\entries\\map38\\8-other-items",0xAFD2A,0xAFD2C,"");
    produceAsmSection(file,"",0xAFD2C,0xB0446);
    produceAsmSection(file,"",0xB0446,0xB0736);
    //produceAsmScript(file,"data\\maps\\entries\\map38\\9-animations",0xA1516,0xA152C,"");
    
    produceAsmScriptWithExtName(file,"Map39","data\\maps\\entries\\map39\\00-tilesets",0xB0736,0xB073C,"");
    produceAsmSection(file,"",0xB073C,0xB0764);
    produceAsmScriptWithExtName(file,"Map39s2_Areas","data\\maps\\entries\\map39\\2-areas",0xB0764,0xB0784,"");
    produceAsmScriptWithExtName(file,"Map39s3_FlagEvents","data\\maps\\entries\\map39\\3-flag-events",0xB0784,0xB0786,"");
    produceAsmScriptWithExtName(file,"Map39s4_StepEvents","data\\maps\\entries\\map39\\4-step-events",0xB0786,0xB0790,"");
    produceAsmScriptWithExtName(file,"Map39s5_RoofEvents","data\\maps\\entries\\map39\\5-roof-events",0xB0790,0xB0792,"");
    produceAsmScriptWithExtName(file,"Map39s6_WarpEvents","data\\maps\\entries\\map39\\6-warp-events",0xB0792,0xB07A4,"");
    produceAsmScriptWithExtName(file,"Map39s7_ChestItems","data\\maps\\entries\\map39\\7-chest-items",0xB07A4,0xB07A6,"");
    produceAsmScriptWithExtName(file,"Map39s8_OtherItems","data\\maps\\entries\\map39\\8-other-items",0xB07A6,0xB07B0,"");
    produceAsmSection(file,"",0xB07B0,0xB097C);
    produceAsmSection(file,"",0xB097C,0xB0A68);
    //produceAsmScript(file,"data\\maps\\entries\\map39\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map40","data\\maps\\entries\\map40\\00-tilesets",0xB0A68,0xB0A6E,"");
    produceAsmSection(file,"",0xB0A6E,0xB0A96);
    produceAsmScriptWithExtName(file,"Map40s2_Areas","data\\maps\\entries\\map40\\2-areas",0xB0A96,0xB0AB6,"");
    produceAsmScriptWithExtName(file,"Map40s3_FlagEvents","data\\maps\\entries\\map40\\3-flag-events",0xB0AB6,0xB0AB8,"");
    produceAsmScriptWithExtName(file,"Map40s4_StepEvents","data\\maps\\entries\\map40\\4-step-events",0xB0AB8,0xB0ABA,"");
    produceAsmScriptWithExtName(file,"Map40s5_RoofEvents","data\\maps\\entries\\map40\\5-roof-events",0xB0ABA,0xB0ABC,"");
    produceAsmScriptWithExtName(file,"Map40s6_WarpEvents","data\\maps\\entries\\map40\\6-warp-events",0xB0ABC,0xB0ACE,"");
    produceAsmScriptWithExtName(file,"Map40s7_ChestItems","data\\maps\\entries\\map40\\7-chest-items",0xB0ACE,0xB0AD0,"");
    produceAsmScriptWithExtName(file,"Map40s8_OtherItems","data\\maps\\entries\\map40\\8-other-items",0xB0AD0,0xB0AD6,"");
    produceAsmSection(file,"",0xB0AD6,0xB1216);
    produceAsmSection(file,"",0xB1216,0xB1490);
    
    produceAsmScriptWithExtName(file,"Map41","data\\maps\\entries\\map41\\00-tilesets",0xB1490,0xB1496,"");
    produceAsmSection(file,"",0xB1496,0xB14BE);
    produceAsmScriptWithExtName(file,"Map41s2_Areas","data\\maps\\entries\\map41\\2-areas",0xB14BE,0xB14FC,"");
    produceAsmScriptWithExtName(file,"Map41s3_FlagEvents","data\\maps\\entries\\map41\\3-flag-events",0xB14FC,0xB14FE,"");
    produceAsmScriptWithExtName(file,"Map41s4_StepEvents","data\\maps\\entries\\map41\\4-step-events",0xB14FE,0xB1508,"");
    produceAsmScriptWithExtName(file,"Map41s5_RoofEvents","data\\maps\\entries\\map41\\5-roof-events",0xB1508,0xB150A,"");
    produceAsmScriptWithExtName(file,"Map41s6_WarpEvents","data\\maps\\entries\\map41\\6-warp-events",0xB150A,0xB1534,"");
    produceAsmScriptWithExtName(file,"Map41s7_ChestItems","data\\maps\\entries\\map41\\7-chest-items",0xB1534,0xB1536,"");
    produceAsmScriptWithExtName(file,"Map41s8_OtherItems","data\\maps\\entries\\map41\\8-other-items",0xB1536,0xB153C,"");
    produceAsmScriptWithExtName(file,"Map41s9_Animations","data\\maps\\entries\\map41\\9-animations",0xB153C,0xB1552,"");
    produceAsmSection(file,"",0xB1552,0xB1914);
    produceAsmSection(file,"",0xB1914,0xB1A62);
    
    produceAsmScriptWithExtName(file,"Map42","data\\maps\\entries\\map42\\00-tilesets",0xB1A62,0xB1A68,"");
    produceAsmSection(file,"",0xB1A68,0xB1A90);
    produceAsmScriptWithExtName(file,"Map42s2_Areas","data\\maps\\entries\\map42\\2-areas",0xB1A90,0xB1B0A,"");
    produceAsmScriptWithExtName(file,"Map42s3_FlagEvents","data\\maps\\entries\\map42\\3-flag-events",0xB1B0A,0xB1B24,"");
    produceAsmScriptWithExtName(file,"Map42s4_StepEvents","data\\maps\\entries\\map42\\4-step-events",0xB1B24,0xB1B26,"");
    produceAsmScriptWithExtName(file,"Map42s5_RoofEvents","data\\maps\\entries\\map42\\5-roof-events",0xB1B26,0xB1B28,"");
    produceAsmScriptWithExtName(file,"Map42s6_WarpEvents","data\\maps\\entries\\map42\\6-warp-events",0xB1B28,0xB1B52,"");
    produceAsmScriptWithExtName(file,"Map42s7_ChestItems","data\\maps\\entries\\map42\\7-chest-items",0xB1B52,0xB1B5C,"");
    produceAsmScriptWithExtName(file,"Map42s8_OtherItems","data\\maps\\entries\\map42\\8-other-items",0xB1B5C,0xB1B5E,"");
    produceAsmSection(file,"",0xB1B5E,0xB1DCC);
    produceAsmSection(file,"",0xB1DCC,0xB1F74);
    
    produceAsmScriptWithExtName(file,"Map43","data\\maps\\entries\\map43\\00-tilesets",0xB1F74,0xB1F7A,"");
    produceAsmSection(file,"",0xB1F7A,0xB1FA2);
    produceAsmScriptWithExtName(file,"Map43s2_Areas","data\\maps\\entries\\map43\\2-areas",0xB1FA2,0xB1FC2,"");
    produceAsmScriptWithExtName(file,"Map43s3_FlagEvents","data\\maps\\entries\\map43\\3-flag-events",0xB1FC2,0xB1FC4,"");
    produceAsmScriptWithExtName(file,"Map43s4_StepEvents","data\\maps\\entries\\map43\\4-step-events",0xB1FC4,0xB1FDE,"");
    produceAsmScriptWithExtName(file,"Map43s5_RoofEvents","data\\maps\\entries\\map43\\5-roof-events",0xB1FDE,0xB1FF0,"");
    produceAsmScriptWithExtName(file,"Map43s6_WarpEvents","data\\maps\\entries\\map43\\6-warp-events",0xB1FF0,0xB1FFA,"");
    produceAsmScriptWithExtName(file,"Map43s7_ChestItems","data\\maps\\entries\\map43\\7-chest-items",0xB1FFA,0xB2004,"");
    produceAsmScriptWithExtName(file,"Map43s8_OtherItems","data\\maps\\entries\\map43\\8-other-items",0xB2004,0xB2006,"");
    produceAsmSection(file,"",0xB2006,0xB22BA);
    produceAsmSection(file,"",0xB22BA,0xB23A0);
    
    produceAsmScriptWithExtName(file,"Map44","data\\maps\\entries\\map44\\00-tilesets",0xB23A0,0xB23A6,"");
    produceAsmSection(file,"",0xB23A6,0xB23CE);
    produceAsmScriptWithExtName(file,"Map44s2_Areas","data\\maps\\entries\\map44\\2-areas",0xB23CE,0xB240C,"");
    produceAsmScriptWithExtName(file,"Map44s3_FlagEvents","data\\maps\\entries\\map44\\3-flag-events",0xB240C,0xB240E,"");
    produceAsmScriptWithExtName(file,"Map44s4_StepEvents","data\\maps\\entries\\map44\\4-step-events",0xB240E,0xB2410,"");
    produceAsmScriptWithExtName(file,"Map44s5_RoofEvents","data\\maps\\entries\\map44\\5-roof-events",0xB2410,0xB2412,"");
    produceAsmScriptWithExtName(file,"Map44s6_WarpEvents","data\\maps\\entries\\map44\\6-warp-events",0xB2412,0xB244C,"");
    produceAsmScriptWithExtName(file,"Map44s7_ChestItems","data\\maps\\entries\\map44\\7-chest-items",0xB244C,0xB244E,"");
    produceAsmScriptWithExtName(file,"Map44s8_OtherItems","data\\maps\\entries\\map44\\8-other-items",0xB244E,0xB2458,"");
    produceAsmScriptWithExtName(file,"Map44s9_Animations","data\\maps\\entries\\map44\\9-animations",0xB2458,0xB246E,"");
    produceAsmSection(file,"",0xB246E,0xB29EA);
    produceAsmSection(file,"",0xB29EA,0xB2BFE);
    
    produceAsmScriptWithExtName(file,"Map45","data\\maps\\entries\\map45\\00-tilesets",0xB2BFE,0xB2C04,"");
    produceAsmSection(file,"",0xB2C04,0xB2C2C);
    produceAsmScriptWithExtName(file,"Map45s2_Areas","data\\maps\\entries\\map45\\2-areas",0xB2C2C,0xB2C6A,"");
    produceAsmScriptWithExtName(file,"Map45s3_FlagEvents","data\\maps\\entries\\map45\\3-flag-events",0xB2C6A,0xB2C6C,"");
    produceAsmScriptWithExtName(file,"Map45s4_StepEvents","data\\maps\\entries\\map45\\4-step-events",0xB2C6C,0xB2C6E,"");
    produceAsmScriptWithExtName(file,"Map45s5_RoofEvents","data\\maps\\entries\\map45\\5-roof-events",0xB2C6E,0xB2C90,"");
    produceAsmScriptWithExtName(file,"Map45s6_WarpEvents","data\\maps\\entries\\map45\\6-warp-events",0xB2C90,0xB2CBA,"");
    produceAsmScriptWithExtName(file,"Map45s7_ChestItems","data\\maps\\entries\\map45\\7-chest-items",0xB2CBA,0xB2CC0,"");
    produceAsmScriptWithExtName(file,"Map45s8_OtherItems","data\\maps\\entries\\map45\\8-other-items",0xB2CC0,0xB2CCA,"");
    produceAsmScriptWithExtName(file,"Map45s9_Animations","data\\maps\\entries\\map45\\9-animations",0xB2CCA,0xB2CE0,"");
    produceAsmSection(file,"",0xB2CE0,0xB339C);
    produceAsmSection(file,"",0xB339C,0xB37B2);
    
    produceAsmScriptWithExtName(file,"Map46","data\\maps\\entries\\map46\\00-tilesets",0xB37B2,0xB37B8,"");
    produceAsmSection(file,"",0xB37B8,0xB37E0);
    produceAsmScriptWithExtName(file,"Map46s2_Areas","data\\maps\\entries\\map46\\2-areas",0xB37E0,0xB3800,"");
    produceAsmScriptWithExtName(file,"Map46s3_FlagEvents","data\\maps\\entries\\map46\\3-flag-events",0xB3800,0xB380A,"");
    produceAsmScriptWithExtName(file,"Map46s4_StepEvents","data\\maps\\entries\\map46\\4-step-events",0xB380A,0xB380C,"");
    produceAsmScriptWithExtName(file,"Map46s5_RoofEvents","data\\maps\\entries\\map46\\5-roof-events",0xB380C,0xB380E,"");
    produceAsmScriptWithExtName(file,"Map46s6_WarpEvents","data\\maps\\entries\\map46\\6-warp-events",0xB380E,0xB3818,"");
    produceAsmScriptWithExtName(file,"Map46s7_ChestItems","data\\maps\\entries\\map46\\7-chest-items",0xB3818,0xB381A,"");
    produceAsmScriptWithExtName(file,"Map46s8_OtherItems","data\\maps\\entries\\map46\\8-other-items",0xB381A,0xB3824,"");
    
    produceAsmScriptWithExtName(file,"Map47","data\\maps\\entries\\map47\\00-tilesets",0xB3824,0xB382A,"");
    produceAsmSection(file,"",0xB382A,0xB3852);
    produceAsmScriptWithExtName(file,"Map47s2_Areas","data\\maps\\entries\\map47\\2-areas",0xB3852,0xB3872,"");
    produceAsmScriptWithExtName(file,"Map47s3_FlagEvents","data\\maps\\entries\\map47\\3-flag-events",0xB3872,0xB3874,"");
    produceAsmScriptWithExtName(file,"Map47s4_StepEvents","data\\maps\\entries\\map47\\4-step-events",0xB3874,0xB3876,"");
    produceAsmScriptWithExtName(file,"Map47s5_RoofEvents","data\\maps\\entries\\map47\\5-roof-events",0xB3876,0xB3878,"");
    produceAsmScriptWithExtName(file,"Map47s6_WarpEvents","data\\maps\\entries\\map47\\6-warp-events",0xB3878,0xB388A,"");
    produceAsmScriptWithExtName(file,"Map47s7_ChestItems","data\\maps\\entries\\map47\\7-chest-items",0xB388A,0xB388C,"");
    //produceAsmScript(file,"data\\maps\\entries\\map47\\8-other-items",0xB388A,0xB388C,"");
    produceAsmScriptWithExtName(file,"Map47s9_Animations","data\\maps\\entries\\map47\\9-animations",0xB388C,0xB38B2,"");
    produceAsmSection(file,"",0xB38B2,0xB47EC);
    produceAsmSection(file,"",0xB47EC,0xB4AA4);
    
    produceAsmScriptWithExtName(file,"Map48","data\\maps\\entries\\map48\\00-tilesets",0xB4AA4,0xB4AAA,"");
    produceAsmSection(file,"",0xB4AAA,0xB4AD2);
    produceAsmScriptWithExtName(file,"Map48s2_Areas","data\\maps\\entries\\map48\\2-areas",0xB4AD2,0xB4B10,"");
    produceAsmScriptWithExtName(file,"Map48s3_FlagEvents","data\\maps\\entries\\map48\\3-flag-events",0xB4B10,0xB4B12,"");
    produceAsmScriptWithExtName(file,"Map48s4_StepEvents","data\\maps\\entries\\map48\\4-step-events",0xB4B12,0xB4B14,"");
    produceAsmScriptWithExtName(file,"Map48s5_RoofEvents","data\\maps\\entries\\map48\\5-roof-events",0xB4B14,0xB4B16,"");
    produceAsmScriptWithExtName(file,"Map48s6_WarpEvents","data\\maps\\entries\\map48\\6-warp-events",0xB4B16,0xB4B38,"");
    produceAsmScriptWithExtName(file,"Map48s7_ChestItems","data\\maps\\entries\\map48\\7-chest-items",0xB4B38,0xB4B42,"");
    produceAsmScriptWithExtName(file,"Map48s8_OtherItems","data\\maps\\entries\\map48\\8-other-items",0xB4B42,0xB4B44,"");
    produceAsmScriptWithExtName(file,"Map48s9_Animations","data\\maps\\entries\\map48\\9-animations",0xB4B44,0xB4B5A,"");
    produceAsmSection(file,"",0xB4B5A,0xB4F08);
    produceAsmSection(file,"",0xB4F08,0xB5186);
    
    produceAsmScriptWithExtName(file,"Map49","data\\maps\\entries\\map49\\00-tilesets",0xB5186,0xB518C,"");
    produceAsmSection(file,"",0xB518C,0xB51B4);
    produceAsmScriptWithExtName(file,"Map49s2_Areas","data\\maps\\entries\\map49\\2-areas",0xB51B4,0xB51D4,"");
    produceAsmScriptWithExtName(file,"Map49s3_FlagEvents","data\\maps\\entries\\map49\\3-flag-events",0xB51D4,0xB51D6,"");
    produceAsmScriptWithExtName(file,"Map49s4_StepEvents","data\\maps\\entries\\map49\\4-step-events",0xB51D6,0xB51D8,"");
    produceAsmScriptWithExtName(file,"Map49s5_RoofEvents","data\\maps\\entries\\map49\\5-roof-events",0xB51D8,0xB51DA,"");
    produceAsmScriptWithExtName(file,"Map49s6_WarpEvents","data\\maps\\entries\\map49\\6-warp-events",0xB51DA,0xB51DC,"");
    produceAsmScriptWithExtName(file,"Map49s7_ChestItems","data\\maps\\entries\\map49\\7-chest-items",0xB51DC,0xB51DE,"");
    produceAsmScriptWithExtName(file,"Map49s8_OtherItems","data\\maps\\entries\\map49\\8-other-items",0xB51DE,0xB51E0,"");
    produceAsmScriptWithExtName(file,"Map49s9_Animations","data\\maps\\entries\\map49\\9-animations",0xB51E0,0xB5326,"");
    produceAsmSection(file,"",0xB5326,0xB53EE);
    produceAsmSection(file,"",0xB53EE,0xB55AE);
    
    produceAsmScriptWithExtName(file,"Map50","data\\maps\\entries\\map50\\00-tilesets",0xB55AE,0xB55B4,"");
    produceAsmSection(file,"",0xB55B4,0xB55DC);
    produceAsmScriptWithExtName(file,"Map50s2_Areas","data\\maps\\entries\\map50\\2-areas",0xB55DC,0xB561A,"");
    produceAsmScriptWithExtName(file,"Map50s3_FlagEvents","data\\maps\\entries\\map50\\3-flag-events",0xB561A,0xB5624,"");
    produceAsmScriptWithExtName(file,"Map50s4_StepEvents","data\\maps\\entries\\map50\\4-step-events",0xB5624,0xB5626,"");
    produceAsmScriptWithExtName(file,"Map50s5_RoofEvents","data\\maps\\entries\\map50\\5-roof-events",0xB5626,0xB5628,"");
    produceAsmScriptWithExtName(file,"Map50s6_WarpEvents","data\\maps\\entries\\map50\\6-warp-events",0xB5628,0xB5642,"");
    produceAsmScriptWithExtName(file,"Map50s7_ChestItems","data\\maps\\entries\\map50\\7-chest-items",0xB5642,0xB5650,"");
    produceAsmScriptWithExtName(file,"Map50s8_OtherItems","data\\maps\\entries\\map50\\8-other-items",0xB5650,0xB5652,"");
    produceAsmScriptWithExtName(file,"Map50s9_Animations","data\\maps\\entries\\map50\\9-animations",0xB5652,0xB5668,"");
    produceAsmSection(file,"",0xB5668,0xB5952);
    produceAsmSection(file,"",0xB5952,0xB5BEC);
    
    produceAsmScriptWithExtName(file,"Map51","data\\maps\\entries\\map51\\00-tilesets",0xB5BEC,0xB5BF2,"");
    produceAsmSection(file,"",0xB5BF2,0xB5C1A);
    produceAsmScriptWithExtName(file,"Map51s2_Areas","data\\maps\\entries\\map51\\2-areas",0xB5C1A,0xB5C3A,"");
    produceAsmScriptWithExtName(file,"Map51s3_FlagEvents","data\\maps\\entries\\map51\\3-flag-events",0xB5C3A,0xB5C3C,"");
    produceAsmScriptWithExtName(file,"Map51s4_StepEvents","data\\maps\\entries\\map51\\4-step-events",0xB5C3C,0xB5C3E,"");
    produceAsmScriptWithExtName(file,"Map51s5_RoofEvents","data\\maps\\entries\\map51\\5-roof-events",0xB5C3E,0xB5C40,"");
    produceAsmScriptWithExtName(file,"Map51s6_WarpEvents","data\\maps\\entries\\map51\\6-warp-events",0xB5C40,0xB5C4A,"");
    produceAsmScriptWithExtName(file,"Map51s7_ChestItems","data\\maps\\entries\\map51\\7-chest-items",0xB5C4A,0xB5C4C,"");
    produceAsmScriptWithExtName(file,"Map51s8_OtherItems","data\\maps\\entries\\map51\\8-other-items",0xB5C4C,0xB5C52,"");
    produceAsmSection(file,"",0xB5C52,0xB5F4A);
    produceAsmSection(file,"",0xB5F4A,0xB607E);
    
    produceAsmScriptWithExtName(file,"Map52","data\\maps\\entries\\map52\\00-tilesets",0xB607E,0xB6084,"");
    produceAsmSection(file,"",0xB6084,0xB60AC);
    produceAsmScriptWithExtName(file,"Map52s2_Areas","data\\maps\\entries\\map52\\2-areas",0xB60AC,0xB60CC,"");
    produceAsmScriptWithExtName(file,"Map52s3_FlagEvents","data\\maps\\entries\\map52\\3-flag-events",0xB60CC,0xB60CE,"");
    produceAsmScriptWithExtName(file,"Map52s4_StepEvents","data\\maps\\entries\\map52\\4-step-events",0xB60CE,0xB60D0,"");
    produceAsmScriptWithExtName(file,"Map52s5_RoofEvents","data\\maps\\entries\\map52\\5-roof-events",0xB60D0,0xB60D2,"");
    produceAsmScriptWithExtName(file,"Map52s6_WarpEvents","data\\maps\\entries\\map52\\6-warp-events",0xB60D2,0xB60E4,"");
    produceAsmScriptWithExtName(file,"Map52s7_ChestItems","data\\maps\\entries\\map52\\7-chest-items",0xB60E4,0xB60E6,"");
    produceAsmScriptWithExtName(file,"Map52s8_OtherItems","data\\maps\\entries\\map52\\8-other-items",0xB60E6,0xB60E8,"");
    produceAsmSection(file,"",0xB60E8,0xB6984);
    produceAsmSection(file,"",0xB6984,0xB6C2E);
    
    produceAsmScriptWithExtName(file,"Map53","data\\maps\\entries\\map53\\00-tilesets",0xB6C2E,0xB6C34,"");
    produceAsmSection(file,"",0xB6C34,0xB6C5C);
    produceAsmScriptWithExtName(file,"Map53s2_Areas","data\\maps\\entries\\map53\\2-areas",0xB6C5C,0xB6C7C,"");
    produceAsmScriptWithExtName(file,"Map53s3_FlagEvents","data\\maps\\entries\\map53\\3-flag-events",0xB6C7C,0xB6C7E,"");
    produceAsmScriptWithExtName(file,"Map53s4_StepEvents","data\\maps\\entries\\map53\\4-step-events",0xB6C7E,0xB6C80,"");
    produceAsmScriptWithExtName(file,"Map53s5_RoofEvents","data\\maps\\entries\\map53\\5-roof-events",0xB6C80,0xB6C82,"");
    produceAsmScriptWithExtName(file,"Map53s6_WarpEvents","data\\maps\\entries\\map53\\6-warp-events",0xB6C82,0xB6C94,"");
    produceAsmScriptWithExtName(file,"Map53s7_ChestItems","data\\maps\\entries\\map53\\7-chest-items",0xB6C94,0xB6C9A,"");
    produceAsmScriptWithExtName(file,"Map53s8_OtherItems","data\\maps\\entries\\map53\\8-other-items",0xB6C9A,0xB6C9C,"");
    produceAsmSection(file,"",0xB6C9C,0xB6F84);
    produceAsmSection(file,"",0xB6F84,0xB718A);
    //produceAsmScript(file,"data\\maps\\entries\\map53\\9-animations",0x9AF6C,0x9AF82,"");
    
    produceAsmScriptWithExtName(file,"Map54","data\\maps\\entries\\map54\\00-tilesets",0xB718A,0xB7190,"");
    produceAsmSection(file,"",0xB7190,0xB71B8);
    produceAsmScriptWithExtName(file,"Map54s2_Areas","data\\maps\\entries\\map54\\2-areas",0xB71B8,0xB71D8,"");
    produceAsmScriptWithExtName(file,"Map54s3_FlagEvents","data\\maps\\entries\\map54\\3-flag-events",0xB71D8,0xB71EA,"");
    produceAsmScriptWithExtName(file,"Map54s4_StepEvents","data\\maps\\entries\\map54\\4-step-events",0xB71EA,0xB71EC,"");
    produceAsmScriptWithExtName(file,"Map54s5_RoofEvents","data\\maps\\entries\\map54\\5-roof-events",0xB71EC,0xB71EE,"");
    produceAsmScriptWithExtName(file,"Map54s6_WarpEvents","data\\maps\\entries\\map54\\6-warp-events",0xB71EE,0xB7200,"");
    produceAsmScriptWithExtName(file,"Map54s7_ChestItems","data\\maps\\entries\\map54\\7-chest-items",0xB7200,0xB7202,"");
    produceAsmScriptWithExtName(file,"Map54s8_OtherItems","data\\maps\\entries\\map54\\8-other-items",0xB7202,0xB7204,"");
    produceAsmSection(file,"",0xB7204,0xB75BA);
    produceAsmSection(file,"",0xB75BA,0xB78A2);
    produceAsmScriptWithExtName(file,"Map54s9_Animations","data\\maps\\entries\\map54\\9-animations",0xB78A2,0xB78B8,"");
    
    produceAsmScriptWithExtName(file,"Map55","data\\maps\\entries\\map55\\00-tilesets",0xB78B8,0xB78BE,"");
    produceAsmSection(file,"",0xB78BE,0xB78E6);
    produceAsmScriptWithExtName(file,"Map55s2_Areas","data\\maps\\entries\\map55\\2-areas",0xB78E6,0xB7906,"");
    produceAsmScriptWithExtName(file,"Map55s3_FlagEvents","data\\maps\\entries\\map55\\3-flag-events",0xB7906,0xB7908,"");
    produceAsmScriptWithExtName(file,"Map55s4_StepEvents","data\\maps\\entries\\map55\\4-step-events",0xB7908,0xB790A,"");
    produceAsmScriptWithExtName(file,"Map55s5_RoofEvents","data\\maps\\entries\\map55\\5-roof-events",0xB790A,0xB790C,"");
    produceAsmScriptWithExtName(file,"Map55s6_WarpEvents","data\\maps\\entries\\map55\\6-warp-events",0xB790C,0xB792E,"");
    produceAsmScriptWithExtName(file,"Map55s7_ChestItems","data\\maps\\entries\\map55\\7-chest-items",0xB792E,0xB7930,"");
    produceAsmScriptWithExtName(file,"Map55s8_OtherItems","data\\maps\\entries\\map55\\8-other-items",0xB7930,0xB7932,"");
    produceAsmSection(file,"",0xB7932,0xB7AC0);
    produceAsmSection(file,"",0xB7AC0,0xB7CA0);
    
    produceAsmScriptWithExtName(file,"Map56","data\\maps\\entries\\map56\\00-tilesets",0xB7CA0,0xB7CA6,"");
    produceAsmSection(file,"",0xB7CA6,0xB7CCE);
    produceAsmScriptWithExtName(file,"Map56s2_Areas","data\\maps\\entries\\map56\\2-areas",0xB7CCE,0xB7D2A,"");
    produceAsmScriptWithExtName(file,"Map56s3_FlagEvents","data\\maps\\entries\\map56\\3-flag-events",0xB7D2A,0xB7D2C,"");
    produceAsmScriptWithExtName(file,"Map56s4_StepEvents","data\\maps\\entries\\map56\\4-step-events",0xB7D2C,0xB7D2E,"");
    produceAsmScriptWithExtName(file,"Map56s5_RoofEvents","data\\maps\\entries\\map56\\5-roof-events",0xB7D2E,0xB7D30,"");
    produceAsmScriptWithExtName(file,"Map56s6_WarpEvents","data\\maps\\entries\\map56\\6-warp-events",0xB7D30,0xB7DA2,"");
    produceAsmScriptWithExtName(file,"Map56s7_ChestItems","data\\maps\\entries\\map56\\7-chest-items",0xB7DA2,0xB7DA4,"");
    produceAsmScriptWithExtName(file,"Map56s8_OtherItems","data\\maps\\entries\\map56\\8-other-items",0xB7DA4,0xB7DA6,"");
    produceAsmSection(file,"",0xB7DA6,0xB827C);
    produceAsmSection(file,"",0xB827C,0xB85B6);
    
    produceAsmScriptWithExtName(file,"Map57","data\\maps\\entries\\map57\\00-tilesets",0xB85B6,0xB85BC,"");
    produceAsmSection(file,"",0xB85BC,0xB85E4);
    produceAsmScriptWithExtName(file,"Map57s2_Areas","data\\maps\\entries\\map57\\2-areas",0xB85E4,0xB8604,"");
    produceAsmScriptWithExtName(file,"Map57s3_FlagEvents","data\\maps\\entries\\map57\\3-flag-events",0xB8604,0xB860E,"");
    produceAsmScriptWithExtName(file,"Map57s4_StepEvents","data\\maps\\entries\\map57\\4-step-events",0xB860E,0xB8610,"");
    produceAsmScriptWithExtName(file,"Map57s5_RoofEvents","data\\maps\\entries\\map57\\5-roof-events",0xB8610,0xB8612,"");
    produceAsmScriptWithExtName(file,"Map57s6_WarpEvents","data\\maps\\entries\\map57\\6-warp-events",0xB8612,0xB8624,"");
    produceAsmScriptWithExtName(file,"Map57s7_ChestItems","data\\maps\\entries\\map57\\7-chest-items",0xB8624,0xB8626,"");
    produceAsmScriptWithExtName(file,"Map57s8_OtherItems","data\\maps\\entries\\map57\\8-other-items",0xB8626,0xB8628,"");
    produceAsmSection(file,"",0xB8628,0xB8922);
    produceAsmSection(file,"",0xB8922,0xB89D2);
    
    produceAsmScriptWithExtName(file,"Map58","data\\maps\\entries\\map58\\00-tilesets",0xB89D2,0xB89D8,"");
    produceAsmSection(file,"",0xB89D8,0xB8A00);
    produceAsmScriptWithExtName(file,"Map58s2_Areas","data\\maps\\entries\\map58\\2-areas",0xB8A00,0xB8A20,"");
    produceAsmScriptWithExtName(file,"Map58s3_FlagEvents","data\\maps\\entries\\map58\\3-flag-events",0xB8A20,0xB8A22,"");
    produceAsmScriptWithExtName(file,"Map58s4_StepEvents","data\\maps\\entries\\map58\\4-step-events",0xB8A22,0xB8A24,"");
    produceAsmScriptWithExtName(file,"Map58s5_RoofEvents","data\\maps\\entries\\map58\\5-roof-events",0xB8A24,0xB8A26,"");
    produceAsmScriptWithExtName(file,"Map58s6_WarpEvents","data\\maps\\entries\\map58\\6-warp-events",0xB8A26,0xB8A30,"");
    produceAsmScriptWithExtName(file,"Map58s7_ChestItems","data\\maps\\entries\\map58\\7-chest-items",0xB8A30,0xB8A32,"");
    //produceAsmScript(file,"data\\maps\\entries\\map58\\8-other-items",0xB8A30,0xB8A32,"");
    produceAsmSection(file,"",0xB8A32,0xB9156);
    produceAsmSection(file,"",0xB9156,0xB9350);
    
    produceAsmScriptWithExtName(file,"Map59","data\\maps\\entries\\map59\\00-tilesets",0xB9350,0xB9356,"");
    produceAsmSection(file,"",0xB9356,0xB937E);
    produceAsmScriptWithExtName(file,"Map59s2_Areas","data\\maps\\entries\\map59\\2-areas",0xB937E,0xB939E,"");
    produceAsmScriptWithExtName(file,"Map59s3_FlagEvents","data\\maps\\entries\\map59\\3-flag-events",0xB939E,0xB93A8,"");
    produceAsmScriptWithExtName(file,"Map59s4_StepEvents","data\\maps\\entries\\map59\\4-step-events",0xB93A8,0xB93AA,"");
    produceAsmScriptWithExtName(file,"Map59s5_RoofEvents","data\\maps\\entries\\map59\\5-roof-events",0xB93AA,0xB93AC,"");
    produceAsmScriptWithExtName(file,"Map59s6_WarpEvents","data\\maps\\entries\\map59\\6-warp-events",0xB93AC,0xB93B6,"");
    produceAsmScriptWithExtName(file,"Map59s7_ChestItems","data\\maps\\entries\\map59\\7-chest-items",0xB93B6,0xB93B8,"");
    produceAsmScriptWithExtName(file,"Map59s8_OtherItems","data\\maps\\entries\\map59\\8-other-items",0xB93B8,0xB93BA,"");
    produceAsmSection(file,"",0xB93BA,0xB9B68);
    produceAsmSection(file,"",0xB9B68,0xB9E38);
    
    produceAsmScriptWithExtName(file,"Map60","data\\maps\\entries\\map60\\00-tilesets",0xB9E38,0xB9E3E,"");
    produceAsmSection(file,"",0xB9E3E,0xB9E66);
    produceAsmScriptWithExtName(file,"Map60s2_Areas","data\\maps\\entries\\map60\\2-areas",0xB9E66,0xB9F3A,"");
    produceAsmScriptWithExtName(file,"Map60s3_FlagEvents","data\\maps\\entries\\map60\\3-flag-events",0xB9F3A,0xB9F4C,"");
    produceAsmScriptWithExtName(file,"Map60s4_StepEvents","data\\maps\\entries\\map60\\4-step-events",0xB9F4C,0xB9F4E,"");
    produceAsmScriptWithExtName(file,"Map60s5_RoofEvents","data\\maps\\entries\\map60\\5-roof-events",0xB9F4E,0xB9F50,"");
    produceAsmScriptWithExtName(file,"Map60s6_WarpEvents","data\\maps\\entries\\map60\\6-warp-events",0xB9F50,0xBA00A,"");
    produceAsmScriptWithExtName(file,"Map60s7_ChestItems","data\\maps\\entries\\map60\\7-chest-items",0xBA00A,0xBA00C,"");
    produceAsmScriptWithExtName(file,"Map60s8_OtherItems","data\\maps\\entries\\map60\\8-other-items",0xBA00C,0xBA00E,"");
    produceAsmSection(file,"",0xBA00E,0xBA80E);
    produceAsmSection(file,"",0xBA80E,0xBABA2);
    
    produceAsmScriptWithExtName(file,"Map61","data\\maps\\entries\\map61\\00-tilesets",0xBABA2,0xBABA8,"");
    produceAsmSection(file,"",0xBABA8,0xBABD0);
    produceAsmScriptWithExtName(file,"Map61s2_Areas","data\\maps\\entries\\map61\\2-areas",0xBABD0,0xBABF0,"");
    produceAsmScriptWithExtName(file,"Map61s3_FlagEvents","data\\maps\\entries\\map61\\3-flag-events",0xBABF0,0xBABFA,"");
    produceAsmScriptWithExtName(file,"Map61s4_StepEvents","data\\maps\\entries\\map61\\4-step-events",0xBABFA,0xBABFC,"");
    produceAsmScriptWithExtName(file,"Map61s5_RoofEvents","data\\maps\\entries\\map61\\5-roof-events",0xBABFC,0xBABFE,"");
    produceAsmScriptWithExtName(file,"Map61s6_WarpEvents","data\\maps\\entries\\map61\\6-warp-events",0xBABFE,0xBAC10,"");
    produceAsmScriptWithExtName(file,"Map61s7_ChestItems","data\\maps\\entries\\map61\\7-chest-items",0xBAC10,0xBAC12,"");
    produceAsmScriptWithExtName(file,"Map61s8_OtherItems","data\\maps\\entries\\map61\\8-other-items",0xBAC12,0xBAC14,"");
    produceAsmSection(file,"",0xBAC14,0xBAD4E);
    produceAsmSection(file,"",0xBAD4E,0xBADAC);
    
    produceAsmScriptWithExtName(file,"Map62","data\\maps\\entries\\map62\\00-tilesets",0xBADAC,0xBADB2,"");
    produceAsmSection(file,"",0xBADB2,0xBADDA);
    produceAsmScriptWithExtName(file,"Map62s2_Areas","data\\maps\\entries\\map62\\2-areas",0xBADDA,0xBADFA,"");
    produceAsmScriptWithExtName(file,"Map62s3_FlagEvents","data\\maps\\entries\\map62\\3-flag-events",0xBADFA,0xBADFC,"");
    produceAsmScriptWithExtName(file,"Map62s4_StepEvents","data\\maps\\entries\\map62\\4-step-events",0xBADFC,0xBADFE,"");
    produceAsmScriptWithExtName(file,"Map62s5_RoofEvents","data\\maps\\entries\\map62\\5-roof-events",0xBADFE,0xBAE00,"");
    produceAsmScriptWithExtName(file,"Map62s6_WarpEvents","data\\maps\\entries\\map62\\6-warp-events",0xBAE00,0xBAE0A,"");
    produceAsmScriptWithExtName(file,"Map62s7_ChestItems","data\\maps\\entries\\map62\\7-chest-items",0xBAE0A,0xBAE10,"");
    produceAsmScriptWithExtName(file,"Map62s8_OtherItems","data\\maps\\entries\\map62\\8-other-items",0xBAE10,0xBAE12,"");
    produceAsmSection(file,"",0xBAE12,0xBAF28);
    produceAsmSection(file,"",0xBAF28,0xBAFB0);
    
    produceAsmScriptWithExtName(file,"Map63","data\\maps\\entries\\map63\\00-tilesets",0xBAFB0,0xBAFB6,"");
    produceAsmSection(file,"",0xBAFB6,0xBAFDE);
    produceAsmScriptWithExtName(file,"Map63s2_Areas","data\\maps\\entries\\map63\\2-areas",0xBAFDE,0xBB03A,"");
    produceAsmScriptWithExtName(file,"Map63s3_FlagEvents","data\\maps\\entries\\map63\\3-flag-events",0xBB03A,0xBB03C,"");
    produceAsmScriptWithExtName(file,"Map63s4_StepEvents","data\\maps\\entries\\map63\\4-step-events",0xBB03C,0xBB03E,"");
    produceAsmScriptWithExtName(file,"Map63s5_RoofEvents","data\\maps\\entries\\map63\\5-roof-events",0xBB03E,0xBB040,"");
    produceAsmScriptWithExtName(file,"Map63s6_WarpEvents","data\\maps\\entries\\map63\\6-warp-events",0xBB040,0xBB062,"");
    produceAsmScriptWithExtName(file,"Map63s7_ChestItems","data\\maps\\entries\\map63\\7-chest-items",0xBB062,0xBB064,"");
    produceAsmScriptWithExtName(file,"Map63s8_OtherItems","data\\maps\\entries\\map63\\8-other-items",0xBB064,0xBB066,"");
    produceAsmSection(file,"",0xBB066,0xBB36C);
    produceAsmSection(file,"",0xBB36C,0xBB6B2);
    
    produceAsmScriptWithExtName(file,"Map64","data\\maps\\entries\\map64\\00-tilesets",0xBB6B2,0xBB6B8,"");
    produceAsmSection(file,"",0xBB6B8,0xBB6E0);
    produceAsmScriptWithExtName(file,"Map64s2_Areas","data\\maps\\entries\\map64\\2-areas",0xBB6E0,0xBB700,"");
    produceAsmScriptWithExtName(file,"Map64s3_FlagEvents","data\\maps\\entries\\map64\\3-flag-events",0xBB700,0xBB702,"");
    produceAsmScriptWithExtName(file,"Map64s4_StepEvents","data\\maps\\entries\\map64\\4-step-events",0xBB702,0xBB704,"");
    produceAsmScriptWithExtName(file,"Map64s5_RoofEvents","data\\maps\\entries\\map64\\5-roof-events",0xBB704,0xBB706,"");
    produceAsmScriptWithExtName(file,"Map64s6_WarpEvents","data\\maps\\entries\\map64\\6-warp-events",0xBB706,0xBB708,"");
    produceAsmScriptWithExtName(file,"Map64s7_ChestItems","data\\maps\\entries\\map64\\7-chest-items",0xBB708,0xBB70A,"");
    produceAsmScriptWithExtName(file,"Map64s8_OtherItems","data\\maps\\entries\\map64\\8-other-items",0xBB70A,0xBB70E,"");
    produceAsmSection(file,"",0xBB70E,0xBB79E);
    produceAsmSection(file,"",0xBB79E,0xBB8D8);
    
    produceAsmScriptWithExtName(file,"Map65","data\\maps\\entries\\map65\\00-tilesets",0xBB8D8,0xBB8DE,"");
    produceAsmSection(file,"",0xBB8DE,0xBB906);
    produceAsmScriptWithExtName(file,"Map65s2_Areas","data\\maps\\entries\\map65\\2-areas",0xBB906,0xBB926,"");
    produceAsmScriptWithExtName(file,"Map65s3_FlagEvents","data\\maps\\entries\\map65\\3-flag-events",0xBB926,0xBB928,"");
    produceAsmScriptWithExtName(file,"Map65s4_StepEvents","data\\maps\\entries\\map65\\4-step-events",0xBB928,0xBB92A,"");
    produceAsmScriptWithExtName(file,"Map65s5_RoofEvents","data\\maps\\entries\\map65\\5-roof-events",0xBB92A,0xBB92C,"");
    produceAsmScriptWithExtName(file,"Map65s6_WarpEvents","data\\maps\\entries\\map65\\6-warp-events",0xBB92C,0xBB92E,"");
    produceAsmScriptWithExtName(file,"Map65s7_ChestItems","data\\maps\\entries\\map65\\7-chest-items",0xBB92E,0xBB930,"");
    produceAsmScriptWithExtName(file,"Map65s8_OtherItems","data\\maps\\entries\\map65\\8-other-items",0xBB930,0xBB932,"");
    produceAsmSection(file,"",0xBB932,0xBBC5A);
    produceAsmSection(file,"",0xBBC5A,0xBBD1A);
    
    produceAsmScriptWithExtName(file,"Map66","data\\maps\\entries\\map66\\00-tilesets",0xBBD1A,0xBBD20,"");
    produceAsmSection(file,"",0xBBD20,0xBBD48);
    produceAsmScriptWithExtName(file,"Map66s2_Areas","data\\maps\\entries\\map66\\2-areas",0xBBD48,0xBBD68,"");
    produceAsmScriptWithExtName(file,"Map66s3_FlagEvents","data\\maps\\entries\\map66\\3-flag-events",0xBBD68,0xBBD7A,"");
    produceAsmScriptWithExtName(file,"Map66s4_StepEvents","data\\maps\\entries\\map66\\4-step-events",0xBBD7A,0xBBD7C,"");
    produceAsmScriptWithExtName(file,"Map66s5_RoofEvents","data\\maps\\entries\\map66\\5-roof-events",0xBBD7C,0xBBD7E,"");
    produceAsmScriptWithExtName(file,"Map66s6_WarpEvents","data\\maps\\entries\\map66\\6-warp-events",0xBBD7E,0xBBDD0,"");
    produceAsmScriptWithExtName(file,"Map66s7_ChestItems","data\\maps\\entries\\map66\\7-chest-items",0xBBDD0,0xBBDD2,"");
    produceAsmScriptWithExtName(file,"Map66s8_OtherItems","data\\maps\\entries\\map66\\8-other-items",0xBBDD2,0xBBDD8,"");
    produceAsmSection(file,"",0xBBDD8,0xBCB9A);
    produceAsmSection(file,"",0xBCB9A,0xBD1F0);
    produceAsmScriptWithExtName(file,"Map66s9_Animations","data\\maps\\entries\\map66\\9-animations",0xBD1F0,0xBD206,"");
    
    produceAsmScriptWithExtName(file,"Map67","data\\maps\\entries\\map67\\00-tilesets",0xBD206,0xBD20C,"");
    produceAsmSection(file,"",0xBD20C,0xBD234);
    produceAsmScriptWithExtName(file,"Map67s2_Areas","data\\maps\\entries\\map67\\2-areas",0xBD234,0xBD254,"");
    produceAsmScriptWithExtName(file,"Map67s3_FlagEvents","data\\maps\\entries\\map67\\3-flag-events",0xBD254,0xBD25E,"");
    produceAsmScriptWithExtName(file,"Map67s4_StepEvents","data\\maps\\entries\\map67\\4-step-events",0xBD25E,0xBD260,"");
    produceAsmScriptWithExtName(file,"Map67s5_RoofEvents","data\\maps\\entries\\map67\\5-roof-events",0xBD260,0xBD262,"");
    produceAsmScriptWithExtName(file,"Map67s6_WarpEvents","data\\maps\\entries\\map67\\6-warp-events",0xBD262,0xBD28C,"");
    produceAsmScriptWithExtName(file,"Map67s7_ChestItems","data\\maps\\entries\\map67\\7-chest-items",0xBD28C,0xBD28E,"");
    produceAsmScriptWithExtName(file,"Map67s8_OtherItems","data\\maps\\entries\\map67\\8-other-items",0xBD28E,0xBD294,"");
    produceAsmSection(file,"",0xBD294,0xBD746);
    produceAsmSection(file,"",0xBD746,0xBD9F4);
    produceAsmScriptWithExtName(file,"Map67s9_Animations","data\\maps\\entries\\map67\\9-animations",0xBD9F4,0xBDA0A,"");
    
    produceAsmScriptWithExtName(file,"Map68","data\\maps\\entries\\map68\\00-tilesets",0xBDA0A,0xBDA10,"");
    produceAsmSection(file,"",0xBDA10,0xBDA38);
    produceAsmScriptWithExtName(file,"Map68s2_Areas","data\\maps\\entries\\map68\\2-areas",0xBDA38,0xBDA58,"");
    produceAsmScriptWithExtName(file,"Map68s3_FlagEvents","data\\maps\\entries\\map68\\3-flag-events",0xBDA58,0xBDA5A,"");
    produceAsmScriptWithExtName(file,"Map68s4_StepEvents","data\\maps\\entries\\map68\\4-step-events",0xBDA5A,0xBDA5C,"");
    produceAsmScriptWithExtName(file,"Map68s5_RoofEvents","data\\maps\\entries\\map68\\5-roof-events",0xBDA5C,0xBDA5E,"");
    produceAsmScriptWithExtName(file,"Map68s6_WarpEvents","data\\maps\\entries\\map68\\6-warp-events",0xBDA5E,0xBDA90,"");
    produceAsmScriptWithExtName(file,"Map68s7_ChestItems","data\\maps\\entries\\map68\\7-chest-items",0xBDA90,0xBDA92,"");
    produceAsmScriptWithExtName(file,"Map68s8_OtherItems","data\\maps\\entries\\map68\\8-other-items",0xBDA92,0xBDA94,"");
    produceAsmSection(file,"",0xBDA94,0xBE05E);
    produceAsmSection(file,"",0xBE05E,0xBE60E);
    produceAsmScriptWithExtName(file,"Map68s9_Animations","data\\maps\\entries\\map68\\9-animations",0xBE60E,0xBE624,"");
    
    produceAsmScriptWithExtName(file,"Map69","data\\maps\\entries\\map69\\00-tilesets",0xBE624,0xBE62A,"");
    produceAsmSection(file,"",0xBE62A,0xBE652);
    produceAsmScriptWithExtName(file,"Map69s2_Areas","data\\maps\\entries\\map69\\2-areas",0xBE652,0xBE672,"");
    produceAsmScriptWithExtName(file,"Map69s3_FlagEvents","data\\maps\\entries\\map69\\3-flag-events",0xBE672,0xBE67C,"");
    produceAsmScriptWithExtName(file,"Map69s4_StepEvents","data\\maps\\entries\\map69\\4-step-events",0xBE67C,0xBE67E,"");
    produceAsmScriptWithExtName(file,"Map69s5_RoofEvents","data\\maps\\entries\\map69\\5-roof-events",0xBE67E,0xBE680,"");
    produceAsmScriptWithExtName(file,"Map69s6_WarpEvents","data\\maps\\entries\\map69\\6-warp-events",0xBE680,0xBE6C2,"");
    produceAsmScriptWithExtName(file,"Map69s7_ChestItems","data\\maps\\entries\\map69\\7-chest-items",0xBE6C2,0xBE6C4,"");
    produceAsmScriptWithExtName(file,"Map69s8_OtherItems","data\\maps\\entries\\map69\\8-other-items",0xBE6C4,0xBE6C6,"");
    produceAsmSection(file,"",0xBE6C6,0xBEF8E);
    produceAsmSection(file,"",0xBEF8E,0xBF75C);
    produceAsmScriptWithExtName(file,"Map69s9_Animations","data\\maps\\entries\\map69\\9-animations",0xBF75C,0xBF772,"");
    
    produceAsmScriptWithExtName(file,"Map70","data\\maps\\entries\\map70\\00-tilesets",0xBF772,0xBF778,"");
    produceAsmSection(file,"",0xBF778,0xBF7A0);
    produceAsmScriptWithExtName(file,"Map70s2_Areas","data\\maps\\entries\\map70\\2-areas",0xBF7A0,0xBF7C0,"");
    produceAsmScriptWithExtName(file,"Map70s3_FlagEvents","data\\maps\\entries\\map70\\3-flag-events",0xBF7C0,0xBF7C2,"");
    produceAsmScriptWithExtName(file,"Map70s4_StepEvents","data\\maps\\entries\\map70\\4-step-events",0xBF7C2,0xBF7C4,"");
    produceAsmScriptWithExtName(file,"Map70s5_RoofEvents","data\\maps\\entries\\map70\\5-roof-events",0xBF7C4,0xBF7C6,"");
    produceAsmScriptWithExtName(file,"Map70s6_WarpEvents","data\\maps\\entries\\map70\\6-warp-events",0xBF7C6,0xBF7E0,"");
    produceAsmScriptWithExtName(file,"Map70s7_ChestItems","data\\maps\\entries\\map70\\7-chest-items",0xBF7E0,0xBF7E2,"");
    produceAsmScriptWithExtName(file,"Map70s8_OtherItems","data\\maps\\entries\\map70\\8-other-items",0xBF7E2,0xBF7E8,"");
    produceAsmSection(file,"",0xBF7E8,0xC004A);
    produceAsmSection(file,"",0xC004A,0xC062A);
    produceAsmScriptWithExtName(file,"Map70s9_Animations","data\\maps\\entries\\map70\\9-animations",0xC062A,0xC0640,"");
    
    produceAsmScriptWithExtName(file,"Map71","data\\maps\\entries\\map71\\00-tilesets",0xC0640,0xC0646,"");
    produceAsmSection(file,"",0xC0646,0xC066E);
    produceAsmScriptWithExtName(file,"Map71s2_Areas","data\\maps\\entries\\map71\\2-areas",0xC066E,0xC068E,"");
    produceAsmScriptWithExtName(file,"Map71s3_FlagEvents","data\\maps\\entries\\map71\\3-flag-events",0xC068E,0xC0690,"");
    produceAsmScriptWithExtName(file,"Map71s4_StepEvents","data\\maps\\entries\\map71\\4-step-events",0xC0690,0xC0692,"");
    produceAsmScriptWithExtName(file,"Map71s5_RoofEvents","data\\maps\\entries\\map71\\5-roof-events",0xC0692,0xC0694,"");
    produceAsmScriptWithExtName(file,"Map71s6_WarpEvents","data\\maps\\entries\\map71\\6-warp-events",0xC0694,0xC06BE,"");
    produceAsmScriptWithExtName(file,"Map71s7_ChestItems","data\\maps\\entries\\map71\\7-chest-items",0xC06BE,0xC06C0,"");
    produceAsmScriptWithExtName(file,"Map71s8_OtherItems","data\\maps\\entries\\map71\\8-other-items",0xC06C0,0xC06C2,"");
    produceAsmSection(file,"",0xC06C2,0xC1360);
    produceAsmSection(file,"",0xC1360,0xC1B8C);
    produceAsmScriptWithExtName(file,"Map71s9_Animations","data\\maps\\entries\\map71\\9-animations",0xC1B8C,0xC1BA2,"");
    
    produceAsmScriptWithExtName(file,"Map72","data\\maps\\entries\\map72\\00-tilesets",0xC1BA2,0xC1BA8,"");
    produceAsmSection(file,"",0xC1BA8,0xC1BD0);
    produceAsmScriptWithExtName(file,"Map72s2_Areas","data\\maps\\entries\\map72\\2-areas",0xC1BD0,0xC1BF0,"");
    produceAsmScriptWithExtName(file,"Map72s3_FlagEvents","data\\maps\\entries\\map72\\3-flag-events",0xC1BF0,0xC1BFA,"");
    produceAsmScriptWithExtName(file,"Map72s4_StepEvents","data\\maps\\entries\\map72\\4-step-events",0xC1BFA,0xC1BFC,"");
    produceAsmScriptWithExtName(file,"Map72s5_RoofEvents","data\\maps\\entries\\map72\\5-roof-events",0xC1BFC,0xC1BFE,"");
    produceAsmScriptWithExtName(file,"Map72s6_WarpEvents","data\\maps\\entries\\map72\\6-warp-events",0xC1BFE,0xC1C50,"");
    produceAsmScriptWithExtName(file,"Map72s7_ChestItems","data\\maps\\entries\\map72\\7-chest-items",0xC1C50,0xC1C52,"");
    produceAsmScriptWithExtName(file,"Map72s8_OtherItems","data\\maps\\entries\\map72\\8-other-items",0xC1C52,0xC1C54,"");
    produceAsmSection(file,"",0xC1C54,0xC2730);
    produceAsmSection(file,"",0xC2730,0xC2EE2);
    produceAsmScriptWithExtName(file,"Map72s9_Animations","data\\maps\\entries\\map72\\9-animations",0xC2EE2,0xC2EF8,"");
    
    produceAsmScriptWithExtName(file,"Map73","data\\maps\\entries\\map73\\00-tilesets",0xC2EF8,0xC2EFE,"");
    produceAsmSection(file,"",0xC2EFE,0xC2F26);
    produceAsmScriptWithExtName(file,"Map73s2_Areas","data\\maps\\entries\\map73\\2-areas",0xC2F26,0xC2F64,"");
    produceAsmScriptWithExtName(file,"Map73s3_FlagEvents","data\\maps\\entries\\map73\\3-flag-events",0xC2F64,0xC2F66,"");
    produceAsmScriptWithExtName(file,"Map73s4_StepEvents","data\\maps\\entries\\map73\\4-step-events",0xC2F66,0xC2F68,"");
    produceAsmScriptWithExtName(file,"Map73s5_RoofEvents","data\\maps\\entries\\map73\\5-roof-events",0xC2F68,0xC2F6A,"");
    produceAsmScriptWithExtName(file,"Map73s6_WarpEvents","data\\maps\\entries\\map73\\6-warp-events",0xC2F6A,0xC2F84,"");
    produceAsmScriptWithExtName(file,"Map73s7_ChestItems","data\\maps\\entries\\map73\\7-chest-items",0xC2F84,0xC2F86,"");
    produceAsmScriptWithExtName(file,"Map73s8_OtherItems","data\\maps\\entries\\map73\\8-other-items",0xC2F86,0xC2F88,"");
    produceAsmSection(file,"",0xC2F88,0xC32F0);
    produceAsmSection(file,"",0xC32F0,0xC3618);
    produceAsmScriptWithExtName(file,"Map73s9_Animations","data\\maps\\entries\\map73\\9-animations",0xC3618,0xC362E,"");
    
    produceAsmScriptWithExtName(file,"Map74","data\\maps\\entries\\map74\\00-tilesets",0xC362E,0xC3634,"");
    produceAsmSection(file,"",0xC3634,0xC365C);
    produceAsmScriptWithExtName(file,"Map74s2_Areas","data\\maps\\entries\\map74\\2-areas",0xC365C,0xC367C,"");
    produceAsmScriptWithExtName(file,"Map74s3_FlagEvents","data\\maps\\entries\\map74\\3-flag-events",0xC367C,0xC367E,"");
    produceAsmScriptWithExtName(file,"Map74s4_StepEvents","data\\maps\\entries\\map74\\4-step-events",0xC367E,0xC3680,"");
    produceAsmScriptWithExtName(file,"Map74s5_RoofEvents","data\\maps\\entries\\map74\\5-roof-events",0xC3680,0xC3682,"");
    produceAsmScriptWithExtName(file,"Map74s6_WarpEvents","data\\maps\\entries\\map74\\6-warp-events",0xC3682,0xC36C4,"");
    produceAsmScriptWithExtName(file,"Map74s7_ChestItems","data\\maps\\entries\\map74\\7-chest-items",0xC36C4,0xC36C6,"");
    produceAsmScriptWithExtName(file,"Map74s8_OtherItems","data\\maps\\entries\\map74\\8-other-items",0xC36C6,0xC36CC,"");
    produceAsmSection(file,"",0xC36CC,0xC4028);
    produceAsmSection(file,"",0xC4028,0xC486A);
    produceAsmScriptWithExtName(file,"Map74s9_Animations","data\\maps\\entries\\map74\\9-animations",0xC486A,0xC4880,"");
    
    produceAsmScriptWithExtName(file,"Map75","data\\maps\\entries\\map75\\00-tilesets",0xC4880,0xC4886,"");
    produceAsmSection(file,"",0xC4886,0xC48AE);
    produceAsmScriptWithExtName(file,"Map75s2_Areas","data\\maps\\entries\\map75\\2-areas",0xC48AE,0xC48CE,"");
    produceAsmScriptWithExtName(file,"Map75s3_FlagEvents","data\\maps\\entries\\map75\\3-flag-events",0xC48CE,0xC48E0,"");
    produceAsmScriptWithExtName(file,"Map75s4_StepEvents","data\\maps\\entries\\map75\\4-step-events",0xC48E0,0xC48E2,"");
    produceAsmScriptWithExtName(file,"Map75s5_RoofEvents","data\\maps\\entries\\map75\\5-roof-events",0xC48E2,0xC48E4,"");
    produceAsmScriptWithExtName(file,"Map75s6_WarpEvents","data\\maps\\entries\\map75\\6-warp-events",0xC48E4,0xC491E,"");
    produceAsmScriptWithExtName(file,"Map75s7_ChestItems","data\\maps\\entries\\map75\\7-chest-items",0xC491E,0xC4920,"");
    produceAsmScriptWithExtName(file,"Map75s8_OtherItems","data\\maps\\entries\\map75\\8-other-items",0xC4920,0xC4922,"");
    produceAsmSection(file,"",0xC4922,0xC4D8C);
    produceAsmSection(file,"",0xC4D8C,0xC4F2E);
    produceAsmScriptWithExtName(file,"Map75s9_Animations","data\\maps\\entries\\map75\\9-animations",0xC4F2E,0xC4F44,"");
    
    produceAsmScriptWithExtName(file,"Map76","data\\maps\\entries\\map76\\00-tilesets",0xC4F44,0xC4F4A,"");
    produceAsmSection(file,"",0xC4F4A,0xC4F72);
    produceAsmScriptWithExtName(file,"Map76s2_Areas","data\\maps\\entries\\map76\\2-areas",0xC4F72,0xC4F92,"");
    produceAsmScriptWithExtName(file,"Map76s3_FlagEvents","data\\maps\\entries\\map76\\3-flag-events",0xC4F92,0xC4F94,"");
    produceAsmScriptWithExtName(file,"Map76s4_StepEvents","data\\maps\\entries\\map76\\4-step-events",0xC4F94,0xC4F96,"");
    produceAsmScriptWithExtName(file,"Map76s5_RoofEvents","data\\maps\\entries\\map76\\5-roof-events",0xC4F96,0xC4F98,"");
    produceAsmScriptWithExtName(file,"Map76s6_WarpEvents","data\\maps\\entries\\map76\\6-warp-events",0xC4F98,0xC4FB2,"");
    produceAsmScriptWithExtName(file,"Map76s7_ChestItems","data\\maps\\entries\\map76\\7-chest-items",0xC4FB2,0xC4FB4,"");
    produceAsmScriptWithExtName(file,"Map76s8_OtherItems","data\\maps\\entries\\map76\\8-other-items",0xC4FB4,0xC4FB6,"");
    produceAsmSection(file,"",0xC4FB6,0xC57E8);
    produceAsmSection(file,"",0xC57E8,0xC5D06);
    produceAsmScriptWithExtName(file,"Map76s9_Animations","data\\maps\\entries\\map76\\9-animations",0xC5D06,0xC5D1C,"");
    
    produceAsmScriptWithExtName(file,"Map77","data\\maps\\entries\\map77\\00-tilesets",0xC5D1C,0xC5D22,"");
    produceAsmSection(file,"",0xC5D22,0xC5D4A);
    produceAsmScriptWithExtName(file,"Map77s2_Areas","data\\maps\\entries\\map77\\2-areas",0xC5D4A,0xC5D6A,"");
    produceAsmScriptWithExtName(file,"Map77s3_FlagEvents","data\\maps\\entries\\map77\\3-flag-events",0xC5D6A,0xC5D74,"");
    produceAsmScriptWithExtName(file,"Map77s4_StepEvents","data\\maps\\entries\\map77\\4-step-events",0xC5D74,0xC5D76,"");
    produceAsmScriptWithExtName(file,"Map77s5_RoofEvents","data\\maps\\entries\\map77\\5-roof-events",0xC5D76,0xC5D78,"");
    produceAsmScriptWithExtName(file,"Map77s6_WarpEvents","data\\maps\\entries\\map77\\6-warp-events",0xC5D78,0xC5DA2,"");
    produceAsmScriptWithExtName(file,"Map77s7_ChestItems","data\\maps\\entries\\map77\\7-chest-items",0xC5DA2,0xC5DA4,"");
    produceAsmScriptWithExtName(file,"Map77s8_OtherItems","data\\maps\\entries\\map77\\8-other-items",0xC5DA4,0xC5DA6,"");
    produceAsmSection(file,"",0xC5DA6,0xC6460);
    produceAsmSection(file,"",0xC6460,0xC697A);
    produceAsmScriptWithExtName(file,"Map77s9_Animations","data\\maps\\entries\\map77\\9-animations",0xC697A,0xC6990,"");
    
    produceAsmScriptWithExtName(file,"Map78","data\\maps\\entries\\map78\\00-tilesets",0xC6990,0xC6996,"");
    produceAsmSection(file,"",0xC6996,0xC69BE);
    produceAsmScriptWithExtName(file,"Map78s2_Areas","data\\maps\\entries\\map78\\2-areas",0xC69BE,0xC69DE,"");
    produceAsmScriptWithExtName(file,"Map78s3_FlagEvents","data\\maps\\entries\\map78\\3-flag-events",0xC69DE,0xC69E0,"");
    produceAsmScriptWithExtName(file,"Map78s4_StepEvents","data\\maps\\entries\\map78\\4-step-events",0xC69E0,0xC69E2,"");
    produceAsmScriptWithExtName(file,"Map78s5_RoofEvents","data\\maps\\entries\\map78\\5-roof-events",0xC69E2,0xC69E4,"");
    produceAsmScriptWithExtName(file,"Map78s6_WarpEvents","data\\maps\\entries\\map78\\6-warp-events",0xC69E4,0xC6A0E,"");
    produceAsmScriptWithExtName(file,"Map78s7_ChestItems","data\\maps\\entries\\map78\\7-chest-items",0xC6A0E,0xC6A10,"");
    produceAsmScriptWithExtName(file,"Map78s8_OtherItems","data\\maps\\entries\\map78\\8-other-items",0xC6A10,0xC6A12,"");
    produceAsmSection(file,"",0xC6A12,0xC768C);
    produceAsmSection(file,"",0xC768C,0xC7EB6);
    produceAsmScriptWithExtName(file,"Map78s9_Animations","data\\maps\\entries\\map78\\9-animations",0xC7EB6,0xC7ECC,"");
    
    fclose(file);
    Message("DONE.\n");    

}


static produceSpecificSectionNine(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x0%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"data\\graphics\\mapsprites\\entries",0xC8000,0xFFC48,"Map sprites");   
    produceAsmSection(file,"",0xFFC48,0x100000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionTen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s10_pointers",0x100000,0x100008,"Game Section 10 Pointers");
    produceAsmScript(file,"code\\specialscreens\\title\\title",0x100008,0x1002BE,"Title screen functions");    
    produceAsmScript(file,"code\\specialscreens\\title\\graphics",0x1002BE,0x101EE0,"Title Screen Graphics");
    produceAsmScript(file,"data\\graphics\\battles\\backgrounds\\entries",0x101EE0,0x12A2F8,"Battlescene Backgrounds");   
    produceAsmScript(file,"data\\graphics\\battles\\spells\\invocations\\entries",0x12A2F8,0x12FADE,"Invocation sprites");    
    produceAsmSection(file,"",0x12FADE,0x130000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionEleven(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s11_enemybattlespritespointer",0x130000,0x130004,"Game Section 11 Enemy Battlesprites Pointer");
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\enemies\\entries",0x130004,0x17FE4F,"Enemy battlesprites");  
    produceAsmSection(file,"",0x17FE4F,0x180000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionTwelve(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s12_pointers",0x180000,0x18001C,"Game Section 12 Pointers");
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\allies\\entries",0x18001C,0x1AA16E,"Ally battlesprites");    
    produceAsmScript(file,"data\\graphics\\battles\\tech\\statusanimation\\entries",0x1AA16E,0x1AA316,"Status effect animation tiles");
    produceAsmScript(file,"data\\graphics\\battles\\tech\\battlescenetransition\\entries",0x1AA316,0x1AA8CA,"Battlescene transition tiles");
    produceAsmScript(file,"data\\graphics\\battles\\spells\\animations\\boltanimdata",0x1AA8CA,0x1AAC3A,"Bolt spell animation data");    
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\allies\\animations\\entries",0x1AAC3A,0x1AB79E,"Ally animations");    
    produceAsmScript(file,"data\\graphics\\battles\\battlesprites\\enemies\\animations\\entries",0x1AB79E,0x1ABE52,"Enemy animations");    
    produceAsmSection(file,"",0x1ABE52,0x1AC000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionThirteen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\jumpinterfaces\\s13_jumpinterface",0x1AC000,0x1AC060,"Game Section 13 Jump Interface");
    produceAsmScript(file,"code\\common\\tech\\pointers\\s13_pointers",0x1AC060,0x1AC068,"Game Section 13 Pointers");
    produceAsmScript(file,"code\\common\\scripting\\endcredits",0x1AC068,0x1AC29C,"Ending credits functions");
    produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_1",0x1AC29C,0x1AC9B8,"Battle init, terrain, AI stuff to split more properly");            
    produceAsmScript(file,"data\\battles\\global\\laserbattles",0x1AC9B8,0x1AC9FC,"Laser battles data");
    produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_2",0x1AC9FC,0x1AD104,"Battle init, terrain, AI stuff to split more properly");
    produceAsmScript(file,"data\\battles\\terrainentries",0x1AD104,0x1B120A,"Battle terrain data");    
    produceAsmScript(file,"code\\gameflow\\battle\\battle_s13_3",0x1B120A,0x1B1A66,"Battle init, terrain, AI stuff to split more properly");        
    produceAsmScript(file,"data\\stats\\enemies\\enemydefs",0x1B1A66,0x1B30EE,"Enemy definitions");
    //produceAsmScript(file,"data\\battles\\spritesetentries",0x1B30EE,0x1B6DB0,"Battle spritesets");    
    produceAsmDataEntries(file,"data\\battles\\spritesets\\","spriteset",0x1B30EE,0x1B31A2,0x1B6DB0,0x1B6DB0,45,2,"Battle Spritesets");
    produceAsmScript(file,"data\\battles\\global\\randombattles",0x1B6DB0,0x1B6DDA,"Random battles list, and data related to UpgradeEnemyIndex function");
    produceAsmScript(file,"code\\specialscreens\\endkiss\\graphics",0x1B6DDA,0x1B7C9A,"End Kiss Graphics");
    produceAsmSection(file,"",0x1B7C9A,0x1B8000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionFourteen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s14_pointers",0x1B8000,0x1B8028,"Game Section 14 Pointers");
    produceAsmScript(file,"data\\graphics\\battles\\grounds\\entries",0x1B8028,0x1B9A9A,"Battlescene Grounds");    
    produceAsmScript(file,"data\\graphics\\battles\\weapons\\entries",0x1B9A9A,0x1BEE38,"Battlescene Weapons");    
    produceAsmScript(file,"data\\graphics\\battles\\weapons\\palettes\\entries",0x1BEE38,0x1BEEE0,"Battlescene Weapon Palettes");       
    produceAsmScript(file,"data\\graphics\\battles\\spells\\entries",0x1BEEE0,0x1C46C2,"Spell Graphics");
    produceAsmScript(file,"code\\specialscreens\\witch\\graphics",0x1C46C2,0x1C67C4,"Witch Screen");
    produceAsmScript(file,"code\\specialscreens\\witchend\\graphics",0x1C67C4,0x1C7F7C,"Witch End Screen");    
    produceAsmSection(file,"",0x1C7F7C,0x1C8000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionFifteen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmScript(file,"code\\common\\tech\\pointers\\s15_portraitspointer",0x1C8000,0x1C8004,"Game Section 15 Portraits Pointer");
    produceAsmScript(file,"data\\graphics\\portraits\\entries",0x1C8004,0x1D7E26,"Portraits");    
    produceAsmSection(file,"",0x1D7E26,0x1D8000);

    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionSixteen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));   

    produceAsmScript(file,"code\\common\\tech\\pointers\\s16_iconspointer",0x1D8000,0x1D8004,"Game Section 16 Icons Pointer");
    produceAsmScript(file,"data\\graphics\\icons\\entries",0x1D8004,0x1DFA44,"Icons");
    produceAsmSection(file,"",0x1DFA44,0x1E0000);
    
    fclose(file);
    Message("DONE.\n");    
}


static produceSpecificSectionSeventeen(mainFile,sectionName,start,end,fs,sectionComment){
    auto ea,itemSize,action,currentLine,previousLine,fileName,file;
    auto output, name, indent, comment, commentEx, commentIndent;
    fileName = form("layout\\sf2-%s-0x%s-0x%s.asm",sectionName,ltoa(start,16),ltoa(end,16));
    Message(form("Writing assembly section %s to %s (%s) ... ",sectionName,fileName,sectionComment));    
    action = 1;
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    writestr(file,form("\n; GAME SECTION %s :\n; %s\n",sectionName,sectionComment));
    writestr(file,form("; FREE SPACE : %d bytes.\n\n\n",fs));    

    produceAsmSection(file,"",0x1E0000,0x1EE000);
    produceAsmScript(file,"code\\common\\tech\\pointers\\s17_pointers",0x1EE000,0x1EE02C,"Game Section 17 Pointers");
    produceAsmScript(file,"data\\stats\\allies\\growthcurves",0x1EE02C,0x1EE270,"Stat growth curves");
    //produceAsmScript(file,"data\\stats\\allies\\stats\\entries",0x1EE270,0x1EE7D0,"Ally stats");    
    produceAsmDataEntries(file,"data\\stats\\allies\\stats\\","allystats",0x1EE270,0x1EE2F0,0x1EE7CF,0x1EE7CF,30,2,"Ally stats");
    produceAsmSection(file,"",0x1EE7CF,0x1EE7D0);
    produceAsmScript(file,"data\\stats\\allies\\allystartdefs",0x1EE7D0,0x1EE890,"Ally start definitions");
    produceAsmScript(file,"data\\stats\\allies\\classes\\classdefs",0x1EE890,0x1EE930,"Class definitions");
    produceAsmScript(file,"code\\specialscreens\\jewelend\\graphics",0x1EE930,0x1EF4BA,"Jewel End Graphics");    
    produceAsmScript(file,"code\\specialscreens\\suspend\\graphics",0x1EF4BA,0x1EF5A6,"Suspend String Graphics");    
    produceAsmSection(file,"",0x1EF5A6,0x1F0000);

    fclose(file);
    Message("DONE.\n");    
}

static produceAsmDataEntries(mainFile,sectionName,entryName,start,end,lastEntryDataEnd,chunkEnd,maxIndex,indexLength,sectionComment){
    auto fileName, file, addr, i, j, dref, dataEnd, from, index, entryFileName, entryComment;
    // Produce main file
    fileName = form("%sentries", sectionName);
    produceAsmScript(mainFile,fileName,start,end,sectionComment);
    file = fopen(form("disasm\\%s.asm", fileName),"a");
    // Produce individual entry files
    addr = start;
    i = 0;
    while(addr<end&&i<maxIndex){
        dref = Dfirst(addr);
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<lastEntryDataEnd){dataEnd = j;}
                from = DnextB(addr,from);
            }
            j++;
            if(j==lastEntryDataEnd){dataEnd = lastEntryDataEnd;}
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){index = form("0%s", index);}
        entryFileName = form("%s%s%s", sectionName,entryName,index);
        entryComment = form("%s %s", sectionComment,index);
        produceAsmScript(file,entryFileName,dref,dataEnd,entryComment);
        addr = addr+4;
        i++;
    }
    if(lastEntryDataEnd<chunkEnd){produceAsmSection(file,"",lastEntryDataEnd,chunkEnd);}
    fclose(file);
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
    writestr(mainFile,form("                include \"%s\"    ; %s\n",fileName,sectionComment));
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
        writeItem(file,"",ea);
        /*
        if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFunctionFooter(file,ea,prettyPrint);
        }        
        else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFChunkFooter(file,ea,prettyPrint);
        }                
        */
        ea = ea + itemSize;
    }
    fclose(file);
    Message("DONE.\n");    

}


static produceAsmScriptWithExtName(mainFile,extName,sectionName,start,end,sectionComment){
    produceAsmScriptWithConditionalInclude(mainFile,extName,sectionName,start,end,sectionComment,0);
}

static produceAsmScript(mainFile,sectionName,start,end,sectionComment){
    produceAsmScriptWithConditionalInclude(mainFile,"",sectionName,start,end,sectionComment,0);
}


static produceAsmScriptWithConditionalInclude(mainFile,extName,sectionName,start,end,sectionComment,conditionalIncludeType){
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
    indent = "                ";
    if(extName!=""){
        name = form("%s:",extName);
        while(strlen(name)<(strlen(indent))){
            name = form("%s ",name);
        }        
    }else{
        name = indent;
    }
    writestr(mainFile,form("%s%s \"%s\"    ; %s\n",name,include,fileName,sectionComment));
    file = fopen(form("disasm\\%s",fileName),"w");
    offsets = form("0x%s..0x%s",ltoa(start,16),ltoa(end,16));
    writestr(file,form("\n; ASM FILE %s.asm :\n; %s : %s\n",sectionName,offsets,sectionComment));
    produceAsmSection(file,extName,start,end);
    fclose(file);
    Message("DONE.\n");    

}

static produceAsmSection(file,extName,start,end){
    produceAsmSectionWithPrettyParam(file,extName,start,end,1);
}

static produceAsmSectionNoPretty(file,extName,start,end){
    produceAsmSectionWithPrettyParam(file,extName,start,end,0);
}

static produceAsmSectionWithPrettyParam(file,extName,start,end,prettyWriteFunctions){
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
        writeItemWithPrettyPrintParam(file,extName,ea,prettyWriteFunctions);
        /*
        if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFunctionFooter(file,ea,prettyWriteFunctions);
        }        
        else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
            writeFChunkFooter(file,ea,prettyWriteFunctions);
        }                
        */
        ea = ea + itemSize;
    }
}

static writeHeader(file){
    writestr(file,"\n");
    writestr(file,"   include \"sf2macros.asm\"\n");
    writestr(file,"   include \"sf2patches.asm\"\n");    
    writestr(file,"   include \"sf2enums.asm\"\n");
    writestr(file,"   include \"sf2const.asm\"\n");
    writestr(file,"\n");
    writestr(file,"   include \"layout\\sf2-00-romlayout.asm\"\n");
}

static writeFooter(file){
    writestr(file,"        END");
}

static writeFunctionHeader(file,ea,prettyWriteFunctions){
    auto funcCmt,frame,member,name,offset;
    
    if(prettyWriteFunctions!=0){
        writestr(file,"\n; =============== S U B R O U T I N E =======================================\n\n");
    }
    
    /* Write function comment */
    funcCmt = GetFunctionCmt(ea,0);
    if(funcCmt!=""){
        writestr(file,form("; %s\n",funcCmt));
        if(prettyWriteFunctions!=0){
            writestr(file,"\n");
        }
    }else{
        funcCmt = GetFunctionCmt(ea,1);
        if(funcCmt!=""){
            funcCmt = formatFuncRptCmt(funcCmt);
            writestr(file,form("; %s\n",funcCmt));
            if(prettyWriteFunctions!=0){
                writestr(file,"\n");
            }            
        }
    }
    
    /* Write local variables */
    frame = GetFrame(ea);
    DelStrucMember(frame,GetMemberOffset(frame," r"));
    DelStrucMember(frame,GetMemberOffset(frame," s"));
    member = GetFirstMember(frame);
    if(member!=-1){
        while(member!=-1 && member<=GetLastMember(frame)){
            name = GetMemberName(frame,member);
            if(name!=""){
                offset = GetFrameLvarSize(ea) - member;
                writestr(file,form("%s = -%d\n",name,offset));
                member = member + GetMemberSize(frame,member);
            }else{
                member++;
            }
        }
    }
    
    if(prettyWriteFunctions!=0){
        writestr(file,"\n");
    }
}

static undefineMultipleLineArray(ea){
    auto type;
            type = GuessType(ea);
            if(strstr(type,"char[")!=-1&&(strstr(GetDisasm(ea),"incbin")==-1)){
                    Message(form("\n%a : %s     <== UNDEFINE if on multiple lines.",ea,GuessType(ea)));
            }    
}

static writeFunctionFooter(file, ea,prettyWriteFunctions){
    auto funcName;
    funcName = GetFunctionName(ea);
    if(prettyWriteFunctions!=0){
        writestr(file,form("\n    ; End of function %s\n\n",funcName));
    }
}

static writeItem(file,extName,ea){
    writeItemWithPrettyPrintParam(file,extName,ea,1);
}

static writeItemWithPrettyPrintParam(file,extName,ea,prettyPrint){
    auto name,ln,indent,disasm,cmtIdx,commentIndent,comment,commentEx,lineA,lineB,disasmLen,manualInsn,output;
    auto i,itemSize;
    indent = "                ";
    commentIndent = "                                        ";
    name = GetTrueNameEx(ea,ea);
    if(name==""){
        name = Name(ea);
    }
    if(name!=""&&name!=extName){
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
            while(strlen(name)<(strlen(indent))){
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
    //lineA = LineA(ea,0);
    disasm = GetDisasm(ea);
    cmtIdx = strstr(disasm,";");
    //lineB = LineB(ea,0);
    if(cmtIdx!=-1){
        disasm = substr(disasm,0,cmtIdx);
    }
    if(comment!="" && comment!=" "){
        comment = form("; %s",comment);
    }
    if(strlen(name)>(strlen(indent))){
        name = form("%s\n%s",name,indent);
    }
    /*
    if(strstr(lineA,"\n")!=-1){
        lineA = form("%s%s",lineA,indent);
    }
    */
    
    /* Make sure there is at least one space between disasm and comment */
    disasmLen = strlen(indent)+strlen(disasm);
    if(disasmLen==strlen(commentIndent)&&substr(disasm,strlen(disasm)-1,-1)!=" "){
        disasmLen = disasmLen+1;
    }
    if(disasmLen>strlen(commentIndent)&&comment!=""&&comment!=" "){
        disasm = form("%s%s", disasm," ");
    }
    
    /* Put comment on a new line if disasm reached a certain length */
    if(strlen(disasm)>strlen(commentIndent)+12&&comment!=""&&comment!=" "){
        disasm = form("%s\n%s%s",disasm,indent,commentIndent);
    }
    
    /* Handle manual instructions spanning multiple lines */
    manualInsn = substr(GetManualInsn(ea),strstr(GetManualInsn(ea),"\n"),-1);
    if(manualInsn!=""){
        manualInsn = formatManualInsn(substr(manualInsn,1,-1));
    }
    
    /*
    Message(form("\nname=%s,lineA=%s,disasm=%s,comment=%s,lineB=%s",name,lineA,disasm,comment,lineB));
    output = form("%s%s%s%s\n%s%s",name,lineA,disasm,comment,lineB,manualInsn);
    writestr(file,output);
    */
    
    /* Write address name */
    writestr(file,name);
    
    /* Write anterior lines */
    i = 0;
    //lineA = "";
    while(LineA(ea,i)!="" && LineA(ea,i)!=" "){
        lineA = form("%s\n",LineA(ea,i));
        if(i==0 && strstr(lineA,indent)!=-1){
            lineA = substr(lineA,strlen(indent),-1);
        }
        writestr(file,lineA);
        i++;
        if(LineA(ea,i)=="" || LineA(ea,i)==" "){
            writestr(file,indent);
            break;
        }
    }
    
    /* Write disasm and comment */
    writestr(file,form("%s%s\n",disasm,comment));
    
    /* Write footers before posterior lines */
    itemSize = ItemSize(ea);
    if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
        writeFunctionFooter(file,ea,prettyPrint);
    }
    else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
        writeFChunkFooter(file,ea,prettyPrint);
    }
    
    /* Write posterior lines */
    i = 0;
    //lineB = "";
    while(LineB(ea,i)!="" && LineB(ea,i)!=" "){
        lineB = form("%s\n",LineB(ea,i));
        writestr(file,lineB);
        i++;
    }
    
    /* Write manual instruction */
    writestr(file,manualInsn);
    
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
        result = form("%s                                        ; %s",before,formatRptCmt(after));
        return result;
    }
    else{
        return cmt;
    }
}

static formatManualInsn(manualInsn){
    auto result, indent, searcher, next;
    result = "";
    indent = "                ";
    searcher = indent+manualInsn;
    next = 0;
    while(next!=-1){
        next = strstr(searcher,"\n");
        if(next==-1)
            break;
        result = result+substr(searcher,0,next)+"\n"+indent;
        searcher = substr(searcher,next+1,-1);
    }
    result = result+searcher+"\n";
    return result;
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