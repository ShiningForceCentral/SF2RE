
/*
 *    PARSETRAP0 SCRIPT 
 *    This script will scan "TRAP 0" instructions 
 *  and parse the following word to add corresponding sound command 
 *  as a constant from an Enum, for easier code readability.
 * 
 */

#include <idc.idc>

static main(void) {

    Message("SCANNING TRAP 0...\n");
    
    scanTrap0();
    Message("\nDONE.\n");
    
    Message("END OF TRAP 0 SCAN.\n");
    Batch(0);

}


static scanTrap0(){

    auto addr; // current location
    auto parameter; // parameter found after TRAP 0
    auto action; 
    auto cont; // script continuation asked to user
    action = 1;
    cont = 1;
    addr=0;
    action = AskYN(1,form("Start from current location 0x%s ?", ltoa(ScreenEA(),16)));
    if (action==-1) return;
    if (action==1){
        addr = ScreenEA();
    }
    Message(form("\nStarting from address 0x%s",ltoa(addr,16)));
    
    for(addr=FindBinary(addr+1,7,"4E 40");addr!=BADADDR;addr=FindBinary(addr+1,7,"4E 40")){

        Jump(addr);
        if(isCode(GetFlags(addr))){
        
            OpEnumEx(addr,0,GetEnum("Traps"),0);
            MakeWord(addr+2);
        
            parameter = Word(addr+2);

            Message(form("\nBinary value 0x4E40 with parameter value 0x%s at address 0x%s in code.",ltoa(parameter,16),ltoa(addr,16)));
            
            if(parameter == 0x20
                    || (parameter >= 0xF0 &&  parameter <= 0xFFFF)){
                    OpEnumEx(addr+2,0,GetEnum("SoundCommands"),0);
            }
            else if(parameter >= 0 && parameter <= 0x29){
                    OpEnumEx(addr+2,0,GetEnum("Music"),0);
            }
            else if(parameter >= 0x41 && parameter <= 0x78){
                    OpEnumEx(addr+2,0,GetEnum("Sfx"),0);
            }    
            else{
                Message(form("%s: could not process trap 0 value %d",ltoa(addr,16),parameter));
            }                    
            
            cont = AskYN(1,"Continue ?");
            if (cont==-1 || cont==0) return;    
        }
        else{
            Message(form("\nBinary value 0x4E40 with parameter value 0x%s at address 0x%s not in code",ltoa(Word(addr+2),16),ltoa(addr,16)));
        }
    }
    
}