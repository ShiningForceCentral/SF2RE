




#include <idc.idc>


static main(void){

    Message("\nPARSING MAP SETUPS...\n");
    parseMapSetups();    
    Message("END OF PARSING.\n");    


}


static parseMapSetups(){

    auto ea,action,start,mapId,isDef,flag;
    action = 1;
    start = 0x4F6E2;
    isDef = 1;
    
    ea = start;
    
    while(action==1&&Word(ea)!=0xFFFF){
    
        //Jump(ea);
    
        while(Word(ea)!=0xFFFD){
        
            if(isDef == 1){
                mapId = ltoa(Word(ea),10);
                MakeWord(ea);
                MakeDword(ea+2);
                OpOff(ea+2,0,0);
                MakeNameEx(Dword(ea+2),form("ms_map%s",mapId),0);
                parseMapSetup(Dword(ea+2),form("ms_map%s",mapId));
                isDef = 0;
                ea = ea + 6;
            }
            else{
                MakeWord(ea);
                flag = ltoa(Word(ea),16);
                MakeDword(ea+2);
                OpOff(ea+2,0,0);
                MakeNameEx(Dword(ea+2),form("ms_map%s_%s",mapId,flag),0);
                parseMapSetup(Dword(ea+2),form("ms_map%s_%s",mapId,flag));        
                ea = ea + 6;
            }
        }
        //action = AskYN(1,"Continue ?");
        isDef = 1;
        ea = ea + 2;
    }

}

static parseMapSetup(ea,baseName){

    auto j;

    for(j=ea+1;j<ea+0x18;j++){undefineByte(j);}

    MakeDword(ea);
    OpOff(ea,0,0);
    parseMapSetupEntities(Dword(ea),baseName);
    
    MakeDword(ea+4);
    OpOff(ea+4,0,0);
    parseMapSetupSection2(Dword(ea+4),baseName);
    
    MakeDword(ea+8);
    OpOff(ea+8,0,0);
    parseMapSetupSection3(Dword(ea+8),baseName);
    
    MakeDword(ea+12);
    OpOff(ea+12,0,0);
    parseMapSetupSection4(Dword(ea+12),baseName);
    
    MakeDword(ea+16);
    OpOff(ea+16,0,0);
    parseMapSetupSection5(Dword(ea+16),baseName);
    
    MakeDword(ea+20);
    OpOff(ea+20,0,0);
    parseMapSetupInitFunction(Dword(ea+0x14),baseName);
    
    

}

static parseMapSetupEntities(ea,baseName){
    auto j;
    MakeNameEx(ea,form("%s_Entities",baseName),0);
    while(Byte(ea)!=0xFF){
        for(j=ea+1;j<=ea+8;j++){undefineByte(j);}
        MakeByte(ea);
        MakeByte(ea+1);
        MakeByte(ea+2);
        MakeByte(ea+3);
        if(Byte(ea+4)!=0xFF&&Byte(ea+4)!=0xFE){
            MakeDword(ea+4);
            OpOff(ea+4,0,0);
        }
        else{
            MakeByte(ea+4);
            MakeByte(ea+5);
            MakeByte(ea+6);
            MakeByte(ea+7);
        }
        ea = ea + 8;
    }
    MakeWord(ea);
}


static parseMapSetupSection2(ea,baseName){
    auto base;
    MakeNameEx(ea,form("%s_EntityEvents",baseName),0);
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    while(Byte(ea)!=0xFD){
        MakeByte(ea);
        MakeByte(ea+1);
        undefineByte(ea+2);
        undefineByte(ea+3);
        MakeWord(ea+2);
        if(Word(ea+2) > 0x8000) {
            OpOffEx(ea+2, -1, REF_LOW16, base + (Word(ea+2)+0xFFFF0000), base, 0);
            MakeCode(base+Word(ea+2)-0x10000);
        }
        else{
            OpOffEx(ea+2, -1, REF_OFF32, -1, base, 0);
            MakeCode(base+Word(ea+2));
        }
            
        ea = ea + 4;
    }
    MakeWord(ea);
    undefineByte(ea+2);
    undefineByte(ea+3);
    MakeWord(ea+2);
    if(Word(ea+2) > 0x8000) {
        OpOffEx(ea+2, -1, REF_LOW16, base + (Word(ea+2)+0xFFFF0000), base, 0);
        MakeCode(base+Word(ea+2)-0x10000);
    }
    else{
        OpOffEx(ea+2, -1, REF_OFF32, -1, base, 0);
        MakeCode(base+Word(ea+2));
    }
}


static parseMapSetupSection3(ea,baseName){
    auto base;
    MakeNameEx(ea,form("%s_Section3",baseName),0);
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    while(Byte(ea)!=0xFD){
        MakeByte(ea);
        MakeByte(ea+1);
        undefineByte(ea+2);
        undefineByte(ea+3);
        MakeWord(ea+2);
        if(Word(ea+2) > 0x8000) {
            OpOffEx(ea+2, -1, REF_LOW16, base + (Word(ea+4)+0xFFFF0000), base, 0);
            MakeCode(base+Word(ea+2)-0x10000);
        }
        else{
            OpOffEx(ea+2, -1, REF_OFF32, -1, base, 0);
            MakeCode(base+Word(ea+2));
        }
            
        ea = ea + 4;
    }
    MakeWord(ea);
    undefineByte(ea+2);
    undefineByte(ea+3);
    MakeWord(ea+2);
    if(Word(ea+2) > 0x8000) {
        OpOffEx(ea+2, -1, REF_LOW16, base + (Word(ea+4)+0xFFFF0000), base, 0);
        MakeCode(base+Word(ea+2)-0x10000);
    }
    else{
        OpOffEx(ea+2, -1, REF_OFF32, -1, base, 0);
        MakeCode(base+Word(ea+2));
    }
}

static parseMapSetupSection4(ea,baseName){

    MakeCode(ea);
    MakeNameEx(ea,form("%s_Section4",baseName),0);

}

static parseMapSetupSection5(ea,baseName){
    auto base;
    base = ea;
    if(Word(ea)==0x4E75){
        return;
    }
    MakeNameEx(ea,form("%s_Section5",baseName),0);
    while(Byte(ea)!=0xFD){
        MakeByte(ea);
        MakeByte(ea+1);
        MakeByte(ea+2);
        MakeByte(ea+3);    
        MakeWord(ea+4);        
        if(Word(ea+4) > 0x8000) {
            OpOffEx(ea+4, -1, REF_LOW16, base + (Word(ea+4)+0xFFFF0000), base, 0);
            MakeCode(base+Word(ea+4)-0x10000);
        }
        else{
            OpOffEx(ea+4, -1, REF_OFF32, -1, base, 0);
            MakeCode(base+Word(ea+4));
        }
        ea = ea + 6;    
    }
    MakeByte(ea);
    MakeByte(ea+1);
    MakeByte(ea+2);
    MakeByte(ea+3);    
    MakeWord(ea+4);        
    if(Word(ea+4) > 0x8000) {
        OpOffEx(ea+4, -1, REF_LOW16, base + (Word(ea+4)+0xFFFF0000), base, 0);
        MakeCode(base+Word(ea+4)-0x10000);
    }
    else{
        OpOffEx(ea+4, -1, REF_OFF32, -1, base, 0);
        MakeCode(base+Word(ea+4));
    }
}

static parseMapSetupInitFunction(ea,baseName){
    MakeNameEx(ea,form("%s_InitFunction",baseName),0);
    if(Word(ea)!=0xFFFF){
        MakeCode(ea);
    }
    else{
        MakeWord(ea);
    }

}


/* 
 *  Makes sure byte at addr is
 *  clean for new formatting
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