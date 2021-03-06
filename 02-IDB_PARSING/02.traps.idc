
/*
 *    PARSETRAP0 SCRIPT 
 *    This script will scan "TRAP 0" instructions 
 *  and parse the following word to add corresponding sound command 
 *  as a constant from an Enum, for easier code readability.
 * 
 */

#include <idc.idc>



static main(void) {

    Message("\nINITIALIZING ARRAYS...\n");
    initializeArrays();

    Message("FIXING FUNCTION CHUNKS...\n");
    fixFChunks();

    Message("SCANNING TRAPS...\n");
    parseSoundTrap();
    parseFlagTraps();
    parseTextTrap();
    parseScriptTrap();

    Message("DELETING ARRAYS...\n");
    deleteArrays();
    
    Message("END OF TRAPS SCAN.\n");
    
    // Check if script running in batch mode, and exit once done
    if (Batch(1) == 1) {
        Exit(0);                              // exit to OS, error code 0 - success		
    }
    else {
        Batch(0);
    }

}






/* INITIALIZE ARRAYS OF STRINGS TO OPTIMIZE EXTERNAL FILE ACCESS */

static initializeArrays(){
    
    loadArray("flags.txt","Flags");
    loadArray("text.txt","Text");    
    
}

static loadArray(fileName, arrayName){

    auto file, arrayId, idx, str;
    
    file = fopen(fileName,"r");
    arrayId = CreateArray(arrayName);
    idx = 0;
    while(str!=-1){
        str = readstr(file);
        if(str!=-1){
            str = form("%s",substr(str,5,strlen(str)-1));
            SetArrayString(arrayId, idx, str);
        }
        idx++;
    }
    fclose(file);
    
}

/* DELETE ARRAYS FROM IDB AFTER USAGE */

static deleteArrays(){

    DeleteArray(GetArrayId("Flags")); 
    DeleteArray(GetArrayId("Text")); 
    
}



/* MANUALLY FIX FUNCTION CHUNKS IMPROPERLY PARSED BECAUSE OF TRAPS */

static fixFChunks(){

    // InitGame
    RemoveFchunk(0x70D2, 0x71CE);
    AppendFchunk(0x70D2, 0x71CE, 0x73FE);
    
    // YesNoPrompt
    RemoveFchunk(0x15284, 0x1528E);
    RemoveFchunk(0x15284, 0x15328);
    RemoveFchunk(0x15284, 0x1533C);
    RemoveFchunk(0x15284, 0x153C0);
    AppendFchunk(0x15284, 0x1528E, 0x15422);
    
    // sa09_
    RemoveFchunk(0x1ABF4, 0x1AC08);
    AppendFchunk(0x1ABF4, 0x1AC08, 0x1ACC6);
    
    // CheckArea
    RemoveFchunk(0x23862, 0x239C8);
    RemoveFchunk(0x23862, 0x239EE);
    AppendFchunk(0x23862, 0x239C8, 0x23A84);
    
    // BattleLoop
    RemoveFchunk(0x23A84, 0x23CBA);
    AppendFchunk(0x23A84, 0x23CBA, 0x23D98);
    
    // sub_24662
    RemoveFchunk(0x24662, 0x24982);
    RemoveFchunk(0x24662, 0x249A8);
    RemoveFchunk(0x24662, 0x24A4A);
    RemoveFchunk(0x24662, 0x24A72);
    RemoveFchunk(0x24662, 0x24AC8);
    RemoveFchunk(0x24662, 0x24B06);
    RemoveFchunk(0x24662, 0x24B34);
    AppendFchunk(0x24662, 0x24982, 0x24C4E);

    RemoveFchunk(0x24662, 0x24D64);
    RemoveFchunk(0x24662, 0x24DCC);
    RemoveFchunk(0x24662, 0x24E26);
    RemoveFchunk(0x24662, 0x24F16);
    RemoveFchunk(0x24662, 0x24FFA);
    RemoveFchunk(0x24662, 0x25022);
    RemoveFchunk(0x24662, 0x25072);
    RemoveFchunk(0x24662, 0x250B0);
    RemoveFchunk(0x24662, 0x25188);
    AppendFchunk(0x24662, 0x24D64, 0x2519E);
    
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
            
            flagDescription = GetArrayElement(AR_STR, GetArrayId("Flags"), Word(addr+2));
            if(flagDescription==-1){
                flagDescription="";
            }
            
            /* Macro formatting */
            if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
                MakeUnkn(addr,DOUNK_DELNAMES);
                MakeUnkn(addr+1,DOUNK_DELNAMES);
                MakeUnkn(addr+2,DOUNK_DELNAMES);
                MakeUnkn(addr+3,DOUNK_DELNAMES);
                MakeData(addr,FF_BYTE,4,1);
                SetManualInsn(addr, form("chkFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,flagDescription);
            }else{
                SetManualInsn(addr, " ");
                SetManualInsn(addr+2, form("chkFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,"");
                MakeRptCmt(addr+2,flagDescription);
            }  
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
            
            flagDescription = GetArrayElement(AR_STR, GetArrayId("Flags"), Word(addr+2));
            if(flagDescription==-1){
                flagDescription="";
            }
            
            /* Macro formatting */
            if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
                MakeUnkn(addr,DOUNK_DELNAMES);
                MakeUnkn(addr+1,DOUNK_DELNAMES);
                MakeUnkn(addr+2,DOUNK_DELNAMES);
                MakeUnkn(addr+3,DOUNK_DELNAMES);
                MakeData(addr,FF_BYTE,4,1);
                SetManualInsn(addr, form("setFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,flagDescription);
            }else{
                SetManualInsn(addr, " ");
                SetManualInsn(addr+2, form("setFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,"");
                MakeRptCmt(addr+2,flagDescription);
            }
            
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
            
            flagDescription = GetArrayElement(AR_STR, GetArrayId("Flags"), Word(addr+2));
            if(flagDescription==-1){
                flagDescription="";
            }
            
            /* Macro formatting */
            if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
                MakeUnkn(addr,DOUNK_DELNAMES);
                MakeUnkn(addr+1,DOUNK_DELNAMES);
                MakeUnkn(addr+2,DOUNK_DELNAMES);
                MakeUnkn(addr+3,DOUNK_DELNAMES);
                MakeData(addr,FF_BYTE,4,1);
                SetManualInsn(addr, form("clrFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,flagDescription);
            }else{
                SetManualInsn(addr, " ");
                SetManualInsn(addr+2, form("clrFlg  %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,"");
                MakeRptCmt(addr+2,flagDescription);
            }
              
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
            
            flagDescription = GetArrayElement(AR_STR, GetArrayId("Flags"), Word(addr+2));
            if(flagDescription==-1){
                flagDescription="";
            }
            
            /* Macro formatting */
            if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
                MakeUnkn(addr,DOUNK_DELNAMES);
                MakeUnkn(addr+1,DOUNK_DELNAMES);
                MakeUnkn(addr+2,DOUNK_DELNAMES);
                MakeUnkn(addr+3,DOUNK_DELNAMES);
                MakeData(addr,FF_BYTE,4,1);
                SetManualInsn(addr, form("checkFlg %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,flagDescription);
            }else{
                SetManualInsn(addr, " ");
                SetManualInsn(addr+2, form("checkFlg %s", ltoa(Word(addr+2),10)));
                MakeRptCmt(addr,"");
                MakeRptCmt(addr+2,flagDescription);
            }
               
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
    //    addr = ScreenEA();
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
            
            if(Word(addr+2)!=0xFFFF){       
            
                dialogLine = GetArrayElement(AR_STR, GetArrayId("Text"), Word(addr+2));
                if(dialogLine==-1){
                    dialogLine="";
                }else{
                    dialogLine = form("\"%s\"",dialogLine);
                }
                
                if(addr!=GetFunctionAttr(addr,FUNCATTR_START)){
                    MakeUnkn(addr,DOUNK_DELNAMES);
                    MakeUnkn(addr+1,DOUNK_DELNAMES);
                    MakeUnkn(addr+2,DOUNK_DELNAMES);
                    MakeUnkn(addr+3,DOUNK_DELNAMES);
                    MakeData(addr,FF_BYTE,4,1);
                    SetManualInsn(addr, form("txt     %s", ltoa(Word(addr+2),10)));
                    MakeRptCmt(addr,dialogLine);
                }else{
                    SetManualInsn(addr, " ");
                    SetManualInsn(addr+2, form("txt     %s", ltoa(Word(addr+2),10)));
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

