
/*
 *  FIXES SCRIPT 
 *  This script will contain all instruction for fixes
 *  on the IDB after the main IDC script has been applied.
 *
 *
 *  TABLE FIXES :
 *  IDA's IDC export function does not properly export 
 *  the following structures, when they
 *  are located after address 0xFFFF :
 *  - Relative Jump Tables (RJT, labeled with prefix "rjt_")
 *  - Branch Tables (BT, labeled with prefix "bt_")
 *  - Relative Pointer Tables (RPT, labeled with prefix "rpt_")
 *  This script contains the needed instructions to 
 *  fix all the RJTs/BTs/RPTs that are defined in the IDB. 
 *  Beware :
 *  Everytime a new RJT/BT/RPT is defined after 0xFFFF, 
 *  it also has    to be defined in this script.
 *
 *  
 *  INSTRUCTION FIXES :
 *  Some instructions are not properly represented by IDA.
 *  Details in more comments below.
 *
 */

#include <idc.idc>

static main(void) {

    Message("FIXING...\n");

    Message("Relative Jump Tables...");
    fixRJTs();
    Message(" DONE.\nMap Setups RJTs...");    
    fixMapSetups();
    fixMapSetupsSection4();
    Message(" DONE.\nRelative Pointer Tables...");        
    fixRPTs();
    Message(" DONE.\nInstruction Representations...");            
    fixInstructionRepresentations();
    Message(" DONE.\nSingle Instructions...");        
    fixSingleInstructions();
    Message(" DONE.\nSigned Operands...");  
    fixSignedOperands();
    Message(" DONE.\Unwanted Names...");        
    fixUnwantedNames();
    Message(" DONE.\nROM Expand Tweaks...");  
    insertRomExpandTweaks();
    Message(" DONE.\nFunction Local Names...");  
    fixFunctionLocalNames();
    Message(" DONE.\n");
    
    Message("END OF FIXES.\n");
    Batch(0);

}

static fixRJTs() {
    makeRjt(0x4F1C,0x4FBC);
    makeRjt(0x10408,0x10410);
    makeRjt(0x107F8,0x10800);
    makeRjt(0x10CBE,0x10CC6);
    makeRjt(0x14080,0x14088);
    makeRjt(0x183C0,0x183EA);
    makeRjt(0x1B7E8,0x1B828);    
    makeRjt(0x19F1C,0x19F5C);
    makeRjt(0x1A048,0x1A088);
    makeRjt(0x2200C,0x22014);
    makeRjt(0x2217E,0x22186);
    makeRjt(0x22562,0x2256A);
    makeRjtWithOneWordBetweenEachEntry(0x22A22,0x22A48);
    makeRjt(0x25C5A,0x25C6C);
    makeRjt(0x25D2E,0x25D40);
    makeRjt(0x4681A,0x4683A);
    makeRjt(0x47180,0x47234);
}

static fixRPTs() {
    makeRpt(0x47A88,0x47AE8);
    makeRpt(0x47B2C,0x47B8C);
    makeRpt(0x47BE8,0x47C48);
    makeRpt(0x47CF4,0x47D54);
}


/*
 *  IDC SCRIPT : FIX INSTRUCTION REPRESENSATIONS
 *
 *  It is known that IDA's mc68 module doesn't
 *  properly output certain instructions with 
 *  specific addressing modes. 
 *
 *  This script helps to fix these 
 *  instructions :  
 *  move.l a6,usp were displayed as move a6,usp.
 *  jsr (loc).w were displayed as jsr loc.
 *  jsr loc(pc) were displayed as jsr loc.
 *  jmp (loc).w were displayed as jmp loc.
 *  jmp loc(pc) were displayed as jmp loc.  
 *  lea loc(pc),a0 were displayed as lea loc, a0.
 *  lea loc(pc),a1 were displayed as lea loc, a1. 
 *  lea loc(pc),a2 were displayed as lea loc, a2. 
 *  lea loc(pc),a3 were displayed as lea loc, a3. 
 *  lea loc(pc),a4 were displayed as lea loc, a4. 
 *  lea loc(pc),a5 were displayed as lea loc, a5. 
 *  lea loc(pc),a6 were displayed as lea loc, a6. 
 *  lea loc(pc),a7 were displayed as lea loc, a7.
 *
 *  It finds every instructions 
 *  in formatted code and asks for each one
 *  of them if you want it to be properly formatted.
 *
 *  "No" skips the instruction.
 *  "Cancel" stops the script.
 *
 *  Be aware that it will only find instructions if they have been formatted as code. 
 *  They won't be identified if they are still known as pure data. 
 *
 */
static fixInstructionRepresentations(){
    
    auto batch;
    
    Batch(0);
    //batch = AskYN(1,"Fix Instruction Represensations : BATCH MODE ?");
    //if (batch==-1) return;
    //Batch(batch);
    
    fix("4E 66","move.l  a6,usp","move a6,usp","move.l a6,usp");
    
    fix("4E B8","jsr     (%s).w","jsr loc","jsr (loc).w");
    fix("4E BA","jsr     %s(pc)","jsr loc","jsr loc(pc)");
    fix("4E F8","jmp     (%s).w","jmp loc","jmp (loc).w");
    fix("4E FA","jmp     %s(pc)","jmp loc","jmp loc(pc)");
    
    fixWithMapscriptException("41 FA","lea     %s(pc), a0","lea loc, a0","lea loc(pc),a0");
    fix("43 FA","lea     %s(pc), a1","lea loc, a1","lea loc(pc),a1");
    fix("45 FA","lea     %s(pc), a2","lea loc, a2","lea loc(pc),a2");
    fix("47 FA","lea     %s(pc), a3","lea loc, a3","lea loc(pc),a3");
    fix("49 FA","lea     %s(pc), a4","lea loc, a4","lea loc(pc),a4");
    fix("4B FA","lea     %s(pc), a5","lea loc, a5","lea loc(pc),a5");
    fix("4D FA","lea     %s(pc), a6","lea loc, a6","lea loc(pc),a6");
    fix("4F FA","lea     %s(pc), a7","lea loc, a7","lea loc(pc),a7");

}

/*
 *      fixSingleInstructions()
 *
 *  Add a line to this function for every specific instruction that
 *  needs to be changed with its own individual logic.
 *
 *  For example, here we use OpHex commands to change falsely
 *  identified offsets into just hex values, so IDA doesn't create
 *  false xrefs and names.
 *
 */
 
static fixSingleInstructions(){

    /* Operands being interpreted as offsets wrongly */
    OpHex(0x128C0,1);
    OpHex(0x18A08,0);
    OpHex(0x18AF2,0);
    OpHex(0x19C58,0);    
    OpHex(0x19C7C,0);
    OpHex(0x1B3A0,0);
    OpHex(0x27982,1);
    OpHex(0x27A36,1);
    OpHex(0x27B16,0);
    OpHex(0x478A6,0);
    
    OpHex(0x55FE8,0);
    OpHex(0x55FD0,0);
    OpHex(0x55FD8,0);
    OpHex(0x55FE8,0);
    OpHex(0x56008,0);
    OpHex(0x56030,0);
    
    //SetManualInsn(0x1A4,"declareRomEnd");
    //SetManualInsn(0x1F0,"headerRegion");
    //SetManualInsn(0x279D8,"enableSram"); 
    SetManualInsn(0x7626,"lea RaftResetMapCoordinates-4(pc),a0");   
    
    /* Lost align directives */
    SetManualInsn(0x107E9,"wordAlign"); 
    

}

static fixSignedOperands(){
    
    /* Manually specify signed operands */
    OpAlt(0x11BC,0,form("#$%X",Word(0x11BE)));
    OpAlt(0x1BB0,1,form("#%d",Word(0x1BB2)-0x10000));
    OpAlt(0x1E4C,1,form("#%d",Word(0x1E4E)-0x10000));
    OpAlt(0x3930,1,form("#%d",Word(0x3932)-0x10000));
    OpAlt(0x4FF8,1,form("#%d",Word(0x4FFA)-0x10000));
    OpAlt(0x5668,1,form("#%d",Word(0x566A)-0x10000));
    OpAlt(0x57EA,1,form("#%d",Word(0x57EC)-0x10000));
    OpAlt(0x7D54,1,form("#%d",Word(0x7D56)-0x10000));
    OpAlt(0x9488,1,form("#%d",Word(0x948A)-0x10000));
    OpAlt(0x9B96,1,form("#%d",Word(0x9B98)-0x10000));
    OpAlt(0xC71E,1,form("#%d",Word(0xC720)-0x10000));
    OpAlt(0xD434,1,form("#%d",Word(0xD436)-0x10000));
    OpAlt(0xDA86,1,form("#%d",Word(0xDA88)-0x10000));
    OpAlt(0xE3F2,1,form("#%d",Word(0xE3F4)-0x10000));
    OpAlt(0xE990,1,form("#%d",Word(0xE992)-0x10000));
    OpAlt(0xEDDA,1,form("#%d",Word(0xEDDC)-0x10000));
    OpAlt(0xF1D8,1,form("#%d",Word(0xF1DA)-0x10000));
    OpAlt(0xF526,1,form("#%d",Word(0xF528)-0x10000));
    OpAlt(0xF7A4,1,form("#%d",Word(0xF7A6)-0x10000));
    OpAlt(0xF8EE,1,form("#%d",Word(0xF8F0)-0x10000));
    OpAlt(0x100C8,1,form("#%d",Word(0x100CA)-0x10000));
    OpAlt(0x101FA,1,form("#%d",Word(0x101FC)-0x10000));
    OpAlt(0x1058C,1,form("#%d",Word(0x1058E)-0x10000));
    OpAlt(0x11442,1,form("#%d",Word(0x11444)-0x10000));
    OpAlt(0x118BE,1,form("#%d",Word(0x118C0)-0x10000));
    OpAlt(0x11C32,1,form("#%d",Word(0x11C34)-0x10000));
    OpAlt(0x11FF0,1,form("#%d",Word(0x11FF2)-0x10000));
    OpAlt(0x1288E,1,form("#%d",Word(0x12890)-0x10000));
    OpAlt(0x12F1E,1,form("#%d",Word(0x12F20)-0x10000));
    OpAlt(0x12F68,1,form("#%d",Word(0x12F6A)-0x10000));
    OpAlt(0x13066,1,form("#%d",Word(0x13068)-0x10000));
    OpAlt(0x135A6,1,form("#%d",Word(0x135A8)-0x10000));
    OpAlt(0x137BC,1,form("#%d",Word(0x137BE)-0x10000));
    OpAlt(0x14814,1,form("#%d",Word(0x14816)-0x10000));
    OpAlt(0x15292,1,form("#%d",Word(0x15294)-0x10000));
    OpAlt(0x15876,1,form("#%d",Word(0x15878)-0x10000));
    OpAlt(0x15BB4,1,form("#%d",Word(0x15BB6)-0x10000));
    OpAlt(0x16286,1,form("#%d",Word(0x16288)-0x10000));
    OpAlt(0x163C0,1,form("#%d",Word(0x163C2)-0x10000));
    OpAlt(0x1665C,1,form("#%d",Word(0x1665E)-0x10000));
    OpAlt(0x20068,1,form("#%d",Word(0x2006A)-0x10000));
    OpAlt(0x20A06,1,form("#%d",Word(0x20A08)-0x10000));
    OpAlt(0x21282,1,form("#%d",Word(0x21284)-0x10000));
    OpAlt(0x21A3E,1,form("#%d",Word(0x21A40)-0x10000));
    OpAlt(0x21FD6,1,form("#%d",Word(0x21FD8)-0x10000));
    OpAlt(0x22E1E,1,form("#%d",Word(0x22E20)-0x10000));
    OpAlt(0x22F8A,1,form("#%d",Word(0x22F8C)-0x10000));
    OpAlt(0x23EB8,1,form("#%d",Word(0x23EBA)-0x10000));
    OpAlt(0x24246,1,form("#%d",Word(0x24248)-0x10000));
    OpAlt(0x24496,1,form("#%d",Word(0x24498)-0x10000));
    OpAlt(0x27CA4,1,form("#%d",Word(0x27CA6)-0x10000));
    OpAlt(0x444A2,1,form("#%d",Word(0x444A4)-0x10000));
    OpAlt(0x4F574,1,form("#%d",Word(0x4F576)-0x10000));
    OpAlt(0x1AC72C,1,form("#%d",Word(0x1AC72E)-0x10000));
    OpAlt(0x1ACADA,1,form("#%d",Word(0x1ACADC)-0x10000));
    OpAlt(0x1ACC2A,1,form("#%d",Word(0x1ACC2C)-0x10000));
    
}

static fixFunctionLocalNames(){
    
    /* Local names which are lost when re-creating IDB */
    MakeNameEx(0x897E,"@Loop",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8986,"@Done",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8C6A,"@Loop",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8C88,"@Next",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8C96,"@Break",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8C9C,"@Done",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8EC2,"@Loop",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8EE0,"@Next",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8F38,"@Loop",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x8F4E,"@Next",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x94BA,"@FindEndOfSpellList_Loop",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x96DC,"@Continue",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0xA086,"@Message_Attack",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0xB612,"@EnemyTarget",SN_LOCAL|SN_NON_AUTO);
    MakeNameEx(0x25542,"@Return",SN_LOCAL|SN_NON_AUTO);

}

static fixUnwantedNames(){

    /* Names generating errors about other local names in same function */
    MakeNameEx(0x20,"",0);
    MakeNameEx(0xFC,"",0);
    MakeNameEx(0x5018,"",0);
    MakeNameEx(0x651C,"",0);
    MakeNameEx(0x658C,"",0);
    MakeNameEx(0x6606,"",0);
    MakeNameEx(0x6644,"",0);
    MakeNameEx(0x6EDE,"",0);
    MakeNameEx(0x6F56,"",0);
    MakeNameEx(0x6FBA,"",0);
    MakeNameEx(0x702E,"",0);
    MakeNameEx(0x7E44,"",0);
    MakeNameEx(0x843C,"",0);
    MakeNameEx(0x85DC,"",0);
    MakeNameEx(0x8D56,"",0);
    MakeNameEx(0x8DBC,"",0);
    MakeNameEx(0x91DC,"",0);
    MakeName(0x94BA,"");
    MakeName(0x96DC,"");
    MakeNameEx(0x980C,"",0);
    MakeNameEx(0x9CE0,"",0);
    MakeName(0xA086,"");
    MakeNameEx(0xA13C,"",0);
    //MakeNameEx(0xA08E,"");
    MakeNameEx(0xA21A,"",0);
    MakeNameEx(0xA220,"",0);
    MakeNameEx(0xA476,"",0);
    MakeNameEx(0xA652,"",0);
    MakeNameEx(0xA926,"",0);
    MakeNameEx(0xAB96,"",0);
    MakeNameEx(0xABF2,"",0);
    MakeNameEx(0xAC00,"",0);
    MakeName(0xACC8,"");
    MakeName(0xAE62,"");
    //MakeNameEx(0xAE70,"",0);
    MakeNameEx(0xAF8A,"",0);
    MakeNameEx(0xAFBA,"",0);
    MakeNameEx(0xB010,"",0);
    MakeNameEx(0xB1D6,"",0);
    MakeNameEx(0xB210,"",0);
    MakeName(0xB612,"");
    //MakeNameEx(0xB616,"",0);
    MakeName(0xB6A2,"");
    //MakeNameEx(0xB6A6,"",0);
    MakeNameEx(0xB6BC,"",0);
    MakeNameEx(0xD2E4,"",0);
    MakeNameEx(0xEBB8,"",0);
    MakeNameEx(0x10000C,"",0);
    MakeNameEx(0x100020,"",0);
    MakeNameEx(0x130010,"",0);
    
    

}

static insertRomExpandTweaks(){
    auto ea;

    /* Align directives being not permissive enough 
    to remove data chunks for ROM expansion */
    SetManualInsn(0xFF87,"align $8000");
    SetManualInsn(0x17FDA,"align $18000");
    SetManualInsn(0x27D8E,"align $28000");
    SetManualInsn(0x425ED,"align $44000");
    SetManualInsn(0x6348C,"align $64000");
    SetManualInsn(0xC7ECC,"align $C8000");
    SetManualInsn(0xFFC48,"align $100000");
    SetManualInsn(0x12FADE,"align $130000");
    SetManualInsn(0x17FE4F,"align $180000");
    SetManualInsn(0x1ABE52,"align $1AC000");
    SetManualInsn(0x1B7C9A,"align $1B8000");
    SetManualInsn(0x1C7F7C,"align $1C8000");
    SetManualInsn(0x1D7E26,"align $1D8000");
    SetManualInsn(0x1DFA46,"align $1E0000");
    SetManualInsn(0x1EFE33,"align $1F0000");
    
    /* Conditional manual instructions when implied by moved data */
    //SetManualInsn(0x1B1640,"conditionalPc lea,pt_BattleSpriteSets,a0");
    //SetManualInsn(0x25CBA,"conditionalPc lea,(SpecialSprites_EvilSpirit+$20),a0");
    //SetManualInsn(0x25CC8,"conditionalPc lea,SpecialSprites_EvilSpiritAlt,a0");
    //SetManualInsn(0x25CCE,"conditionalPc lea,(SpecialSprites_Zeon+$20),a0");
    //SetManualInsn(0x10003C,"conditionalPc lea,TitleScreenTiles,a0");
    //SetManualInsn(0x10005E,"conditionalPc lea,TitleScreenLayoutA,a0");
    //SetManualInsn(0x100070,"conditionalPc lea,TitleScreenLayoutA,a0");
    //SetManualInsn(0x1000AC,"conditionalPc lea,TitleScreenLayoutB,a0");
    //SetManualInsn(0x10010E,"conditionalPc lea,plt_TitleScreen,a0");
    //SetManualInsn(0x100248,"conditionalPc lea,TitleScreenLayoutA,a0");
    ////SetManualInsn(0x4481A,"conditionalPc lea,BattleNeutralEntities,a0");
    //SetManualInsn(0x1AD0E0,"conditionalPc lea,pt_BattleTerrainData,a0");
    ////SetManualInsn(0x477A8,"conditionalPc lea,MapSetups,a1");
    ////SetManualInsn(0x54CAA,"conditionalBsr sub_4F48A");
    //SetManualInsn(0x427C,"conditionalWordAddr lea,BattleMapCoordinates,a0");
    //SetManualInsn(0x783A,"conditionalPc lea,BattleMapCoordinates,a0");
    //SetManualInsn(0x79B2,"conditionalPc lea,BattleMapCoordinates,a0");
    //SetManualInsn(0x7604,"conditionalPc lea,SavepointMapCoordinates,a0");
    //SetManualInsn(0x7626,"conditionalPc lea,RaftResetMapCoordinates-4,a0");
    
    


}

static fix(pattern, manualInstruction, wrongInstString, newInstString){

    auto addr; // current location
    auto opnd; // operand found at current location
    auto action; // action asked to user
    auto rep; // proper representation of instruction
    action = 1;
    
    // Start search from current address on screen
    for(addr=0;addr!=BADADDR;addr=FindBinary(addr+1,7,pattern)){
        opnd = GetOpnd(addr,0);
        if (opnd!=""){
            rep = form(manualInstruction,opnd);
            //Jump(addr);
            //action = AskYN(1,form("Change representation from %s to %s ?",wrongInstString, newInstString));
            if (action==-1) break;
            if (action==1){
                //Message(form("\n0x%d : %s changed to %s",addr,wrongInstString, newInstString));
                SetManualInsn(addr,rep);
            }
            else{
                //Message(form("\n0x%d : %s NOT changed to %s",addr,wrongInstString, newInstString));
            }
        }
    }
}

static fixWithMapscriptException(pattern, manualInstruction, wrongInstString, newInstString){

    auto addr; // current location
    auto opnd; // operand found at current location
    auto action; // action asked to user
    auto rep; // proper representation of instruction
    action = 1;
    
    // Start search from current address on screen
    for(addr=0;addr!=BADADDR;addr=FindBinary(addr+1,7,pattern)){
        opnd = GetOpnd(addr,0);
        if (opnd!="" && Word(addr+4)!=0x4E46){
            rep = form(manualInstruction,opnd);
            //Jump(addr);
            //action = AskYN(1,form("Change representation from %s to %s ?",wrongInstString, newInstString));
            if (action==-1) break;
            if (action==1){
                //Message(form("\n0x%d : %s changed to %s",addr,wrongInstString, newInstString));
                SetManualInsn(addr,rep);
            }
            else{
                //Message(form("\n0x%d : %s NOT changed to %s",addr,wrongInstString, newInstString));
            }
        }
    }
}

static makeRpt(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}

static makeRjt(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}

static makeRjtWithOneWordBetweenEachEntry(base, end){
    auto addr;
    addr = base;
    while(addr < end){
        //Jump(addr);
        MakeData(addr, FF_WORD, 0x2, 0);
        addr = addr+2;
        MakeData(addr, FF_WORD, 0x2, 0);
        if(Word(addr) > 0x8000) {
            OpOffEx(addr, -1, REF_LOW16, base + (Word(addr)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
        }
        addr = addr+2;
    }
}



static fixMapSetups(){

    auto ea,start;
    start = 0x4F6E2;
    ea = start;
    while(Word(ea)!=0xFFFF){
        while(Word(ea)!=0xFFFD){
            fixSingleMapSetup(Dword(ea+2));
            ea = ea + 6;
        }
        ea = ea + 2;
    }
}


static fixSingleMapSetup(ea){
    fixMapSetupSection2(Dword(ea+4));
    fixMapSetupSection3(Dword(ea+8));
    fixMapSetupSection5(Dword(ea+16));
}

static fixMapSetupSection2(ea){
    auto base;
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    while(Byte(ea)!=0xFD){
        makeRelativeOffset(ea+2,base);
        ea = ea + 4;
    }
    makeRelativeOffset(ea+2,base);
}

static fixMapSetupSection3(ea){
    auto base;
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    while(Byte(ea)!=0xFD){
        makeRelativeOffset(ea+2,base);
        ea = ea + 4;
    }
    makeRelativeOffset(ea+2,base);
}

static fixMapSetupSection5(ea){
    auto base;
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    while(Byte(ea)!=0xFD){
        makeRelativeOffset(ea+4,base);
        ea = ea + 6;    
    }
    makeRelativeOffset(ea+4,base);
}

static fixMapSetupsSection4(){
    fixSingleMapSetuSection4(0x4FCDE);
    fixSingleMapSetuSection4(0x54D4C);
    fixSingleMapSetuSection4(0x54D9A);
    fixSingleMapSetuSection4(0x561FC);
    fixSingleMapSetuSection4(0x5D584);
    fixSingleMapSetuSection4(0x5E736);
    fixSingleMapSetuSection4(0x5F41E);
    fixSingleMapSetuSection4(0x5FE34);
    fixSingleMapSetuSection4(0x60558);
}

static fixSingleMapSetuSection4(ea){
    auto base;
    base = ea;
    while(Byte(ea)!=0xFD){
        if(Byte(ea+3)!=0){
            makeRelativeOffset(ea+4,base);
        }        
        ea = ea + 6;    
    }
}

static makeRelativeOffset(ea,base){
        if(Word(ea) > 0x8000) {
            OpOffEx(ea, -1, REF_LOW16, base + (Word(ea)+0xFFFF0000), base, 0);
        }
        else{
            OpOffEx(ea, -1, REF_OFF32, -1, base, 0);
        }
}