
/*
 *    PARSETRAP5 SCRIPT 
 *    This script will scan "TRAP 1", "TRAP 2", "TRAP 3" and "TRAP 4" instructions 
 *  and parse the following word to add corresponding flag description in the comment,
 *  for easier code readability.
 *  Corresponding flag description is taken from file flagmap.txt created
 * thanks to Oddeye and Earl's discoveries.
 *  
 *  Execution requirement : put flagmap.txt in IDB directory.
 * 
 */

#include <idc.idc>

static main(void) {

    Message("SCANNING TRAP 1...\n");
    scanTrap("4E 41");
    Message("\nDONE. SCANNING TRAP 2...\n");
    scanTrap("4E 42");
    Message("\nDONE. SCANNING TRAP 3...\n");
    scanTrap("4E 43");
    Message("\nDONE. SCANNING TRAP 4...\n");
    scanTrap("4E 44");
    Message("\nDONE.\n");
    
    Message("END OF TRAP 1/2/3/4 SCAN.\n");
    Batch(0);

}


static scanTrap(trapHexString){

    auto addr; // current location
    auto parameter; // parameter found after TRAP
    auto action; // comment update confirmation asked to user
    auto cont; // script continuation asked to user
    auto flagDescription;
    auto newComment; // comment to add
    auto flagmapFile, currentLine, lineNumber; 
    action = 1;
    cont = 1;
    addr=0;
    lineNumber = 0;
    action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
    if (action==-1) return;
    if (action==1){
        addr = ScreenEA();
    }
    Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
    
    for(addr=FindBinary(addr+1,7,trapHexString);addr!=BADADDR;addr=FindBinary(addr+1,7,trapHexString)){
        flagDescription = "";
        Jump(addr);
        if(isCode(GetFlags(addr))){
        
            OpEnumEx(addr,0,GetEnum("Traps"),0);
            MakeWord(addr+2);
        
            parameter = ltoa(Word(addr+2),16);
            while(strlen(parameter)<4){
                parameter=form("0%s",parameter);
            }
            Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s in code : searching for flag description.",trapHexString, ltoa(Word(addr+2),16),ltoa(addr,16)));
            
            flagmapFile = fopen("flagmap.txt","r");
            while(flagDescription==""){
            lineNumber = lineNumber + 1;
                currentLine = readstr(flagmapFile);
                /* if(lineNumber % 100 == 0) {
                 Message(form("\nReading line %d with index %s : %s",lineNumber, substr(currentLine,0,4), currentLine));
                } */
                if(currentLine==-1){
                    Message(form("\nCould not find flag description for current parameter 0x%s",parameter));
                    break;
                }
                if(strlen(currentLine)>=4 && substr(currentLine,0,4)==parameter){
                    flagDescription = form("%s",substr(currentLine,5,strlen(currentLine)-1));
                }
            }
            fclose(flagmapFile);
            
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
            cont = AskYN(1,"Continue ?");
            if (cont==-1 || cont==0) return;    
        }
        else{
            Message(form("\nBinary value \"%s\" with parameter value 0x%s at address 0x%s not in code",trapHexString,ltoa(Word(addr+2),16),ltoa(addr,16)));
        }
    }
    
}


