

#include <idc.idc>


static main(void){

    parseAll();

}

static parseAll(){

    Message("\nPARSING...\n");
    Message("Battle Scene Commands...");
    parseBattleSceneCommands();
    Message(" DONE.\n");        
    Message("END OF PARSING.\n");    

}

/**********************************************
 *                                            *
 *                                            *
 *            BATTLE SCENE COMMANDS           *
 *                                            *
 *                                            *
 **********************************************/

static parseBattleSceneCommands(){
    // Main battle scene script
    parseBSC(0x9C3C,0x9C56);
    parseBSC(0x9C60,0x9C7A);
    parseBSC(0x9C8C,0x9CA6);
    parseBSC(0x9D1A,0x9D1E);
    parseBSC(0x9D74,0x9D78);
    parseBSC(0x9DB8,0x9DBC);
    
    // Create battle scene message
    parseBSC(0xA086,0xA09A);
    parseBSC(0xA13C,0xA14C);
    parseBSC(0xA15C,0xA170);
    parseBSC(0xA17C,0xA192);
    parseBSC(0xA1B4,0xA1C8);
    parseBSC(0xA1E6,0xA1FA);
    
    // Create battle scene animation
    parseBSC(0xA226,0xA236);
    parseBSC(0xA238,0xA248);
    parseBSC(0xA250,0xA254);
    parseBSC(0xA31E,0xA32E);
    parseBSC(0xA330,0xA340);
    
    // Battle scene end
    parseBSC(0xA352,0xA356);
    parseBSC(0xA3E6,0xA3EA);
    parseBSC(0xA3EA,0xA3EE);
    
    // Animate sprite
    parseBSC(0xA6EE,0xA6F6);
    parseBSC(0xA6F8,0xA700);
    
    // Switch targets
    parseBSC(0xA714,0xA718);
    parseBSC(0xA75E,0xA766);
    parseBSC(0xA766,0xA76E);
    parseBSC(0xA772,0xA778);
    parseBSC(0xA7AA,0xA7B2);
    parseBSC(0xA7B2,0xA7BA);
    parseBSC(0xA7BE,0xA7C4);
    
    // Idle sprite
    parseBSC(0xA7E8,0xA7EC);
    parseBSC(0xA7EE,0xA7F2);
    
    // EXP and gold
    parseBSC(0xA840,0xA846);
    parseBSC(0xA84E,0xA864);
    
    // Dodge attack
    parseBSC(0xAB96,0xABB0);
    
    // Inflict damage
    parseBSC(0xACFE,0xAD18);
    parseBSC(0xADC6,0xADD6);
    parseBSC(0xADD8,0xADE8);
    parseBSC(0xAE1A,0xAE30);
    
    // Inflict ailment
    parseBSC(0xAE62,0xAE74);
    parseBSC(0xAE76,0xAE88);
    parseBSC(0xAEA6,0xAEBC);
    parseBSC(0xAEC2,0xAED8);
    parseBSC(0xAEDE,0xAEF4);
    parseBSC(0xAEFA,0xAF10);
    parseBSC(0xAF52,0xAF68);
    
    // Inflict curse damage
    parseBSC(0xAFD2,0xAFE2);
    parseBSC(0xAFE4,0xAFF4);
    parseBSC(0xAFF4,0xAFF8);
    parseBSC(0xAFF8,0xB00C);
    
    // Death message
    parseBSC(0xB092,0xB0A6);
    
    // Break used item
    parseBSC(0xBC38,0xBC4C);
    parseBSC(0xBC64,0xBC78);
    
    // Enemy drop item
    parseBSC(0xBE02,0xBE1A);
    parseBSC(0xBE1A,0xBE32);
    
    // Spell effects
    parseBSC(0xB158,0xB168);
    parseBSC(0xB16A,0xB17A);
    parseBSC(0xB17A,0xB18E);
    
    parseBSC(0xB1E0,0xB1F2);
    parseBSC(0xB1F4,0xB206);
    parseBSC(0xB210,0xB226);
    parseBSC(0xB22C,0xB242);
    parseBSC(0xB248,0xB25E);
    
    parseBSC(0xB2A2,0xB2B4);
    parseBSC(0xB2B6,0xB2C8);
    parseBSC(0xB2D8,0xB2EC);
    parseBSC(0xB2F8,0xB30C);
    
    parseBSC(0xB33C,0xB34E);
    parseBSC(0xB350,0xB362);
    parseBSC(0xB372,0xB386);
    parseBSC(0xB392,0xB3A6);
    
    parseBSC(0xB3CE,0xB3E0);
    parseBSC(0xB3E2,0xB3F4);
    parseBSC(0xB404,0xB418);
    
    parseBSC(0xB446,0xB458);
    parseBSC(0xB45A,0xB46C);
    parseBSC(0xB470,0xB486);
    
    parseBSC(0xB4D6,0xB4E8);
    parseBSC(0xB4EA,0xB4FC);
    parseBSC(0xB500,0xB514);
    
    parseBSC(0xB528,0xB53A);
    parseBSC(0xB53C,0xB54E);
    parseBSC(0xB562,0xB576);
    
    parseBSC(0xB594,0xB5A6);
    parseBSC(0xB5A8,0xB5BA);
    parseBSC(0xB5BE,0xB5D4);
    
    parseBSC(0xB600,0xB610);
    parseBSC(0xB612,0xB622);
    parseBSC(0xB630,0xB640);
    parseBSC(0xB642,0xB652);
    parseBSC(0xB656,0xB65A);
    parseBSC(0xB66C,0xB67E);
    
    parseBSC(0xB68E,0xB6A0);
    parseBSC(0xB6A2,0xB6B4);
    parseBSC(0xB6BC,0xB6D4);
    
    parseBSC(0xB6F4,0xB706);
    parseBSC(0xB708,0xB71A);
    parseBSC(0xB722,0xB73A);
    
    parseBSC(0xB75A,0xB76C);
    parseBSC(0xB76E,0xB780);
    parseBSC(0xB788,0xB7A0);
    
    parseBSC(0xB7C0,0xB7D2);
    parseBSC(0xB7D4,0xB7E6);
    parseBSC(0xB802,0xB816);
    
    parseBSC(0xB834,0xB846);
    parseBSC(0xB848,0xB85A);
    parseBSC(0xB862,0xB87A);
    
    parseBSC(0xB8A6,0xB8B8);
    parseBSC(0xB8BA,0xB8CC);
    parseBSC(0xB8D4,0xB8EC);
    
    parseBSC(0xB926,0xB938);
    parseBSC(0xB93A,0xB94C);
    parseBSC(0xB950,0xB964);
    parseBSC(0xB968,0xB97C);
    parseBSC(0xB980,0xB994);
    parseBSC(0xB998,0xB9AC);
    parseBSC(0xB9B0,0xB9C4);
    parseBSC(0xB9C8,0xB9DC);
    parseBSC(0xB9EE,0xBA02);
    parseBSC(0xBA06,0xBA1A);
    
    parseBSC(0xBA5A,0xBA6A);
    parseBSC(0xBA6C,0xBA7C);
    parseBSC(0xBA7C,0xBA90);
    
    parseBSC(0xBAAC,0xBAC6);
    
    
    
}

static parseBSC(start,end){

    auto ea,cmdName,cmdComment,cmdLength,tab,action,flag;
    auto paramOne,paramTwo,paramThree,paramFour;
    
    ea = start;
    cmdLength = end-start;
    action = 1;
    
    MakeUnknown(ea,cmdLength,DOUNK_SIMPLE);
    MakeCode(ea);
    SetManualInsn(ea,"");
    MakeRptCmt(ea,"");
    
    //Message(form("\n%a : START OF BSC PARSING",ea));

    while(ea<end && action==1){
        
        if(Word(ea+2)==0x0000){
            cmdName = "0000 ANIMATE ENEMY ACTION";
            cmdComment = "Animation Type, Spell/Item/Projectile";
            
            // Animation type
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // Animation effect
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("animateEnemyAction %s,%s",paramOne,paramTwo));
        }
        else if(Word(ea+2)==0x0001){
            cmdName = "0001 ANIMATE ALLY ACTION";
            cmdComment = "Animation Type, Spell/Item/Projectile";
            
            // Animation type
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // Animation effect
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("animateAllyAction %s,%s",paramOne,paramTwo));
        }
        else if(Word(ea+2)==0x0002){
            cmdName = "0002 MOVE ENEMY BATTLESPRITE";
            cmdComment = "";
            
            // 
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("moveEnemyBattleSprite %s",paramOne));
        }
        else if(Word(ea+2)==0x0003){
            cmdName = "0003 MOVE ALLY BATTLESPRITE";
            cmdComment = "";
            
            // 
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("moveAllyBattleSprite %s",paramOne));
        }
        else if(Word(ea+2)==0x0004){
            cmdName = "0004 MAKE ENEMY IDLE";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("makeEnemyIdle"));
        }
        else if(Word(ea+2)==0x0005){
            cmdName = "0005 MAKE ALLY IDLE";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("makeAllyIdle"));
        }
        else if(Word(ea+2)==0x0006){
            cmdName = "0006 SWITCH ENEMIES";
            cmdComment = "Combatant, Direction (0 = Right, 1 = Left)";
            
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // Direction
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1); 
            SetManualInsn(start,form("switchEnemies %s,%s",paramOne,paramTwo));        
        }
        else if(Word(ea+2)==0x0007){
            cmdName = "0007 SWITCH ALLIES";
            cmdComment = "Combatant, Direction (0 = Right, 1 = Left)";
            
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // Direction
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("switchAllies %s,%s",paramOne,paramTwo));
        }
        else if(Word(ea+2)==0x0008){
            cmdName = "0008 SWITCH TO ENEMY ALONE";
            cmdComment = "Combatant";
            
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("switchToEnemyAlone %s",paramOne));
        }
        else if(Word(ea+2)==0x0009){
            cmdName = "0009 SWITCH TO ALLY ALONE";
            cmdComment = "Combatant";
            
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("switchToAllyAlone %s",paramOne));
        }
        else if(Word(ea+2)==0x000A){
            cmdName = "000A EXECUTE ENEMY REACTION";
            cmdComment = "HP change (signed), MP change (signed), Status Effects, Flags";
            
            // HP change
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // MP change
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            // Status effects
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramThree = GetOpnd(ea,0);
            // Command flags
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramFour = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("executeEnemyReaction %s,%s,%s,%s",paramOne,paramTwo,paramThree,paramFour));
        }
        else if(Word(ea+2)==0x000B){
            cmdName = "000B EXECUTE ALLY REACTION";
            cmdComment = "HP change (signed), MP change (signed), Status Effects, Flags";
            
            // HP change
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            // MP change
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramTwo = GetOpnd(ea,0);
            // Status effects
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramThree = GetOpnd(ea,0);
            // Command flags
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramFour = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("executeAllyReaction %s,%s,%s,%s",paramOne,paramTwo,paramThree,paramFour));
        }
        else if(Word(ea+2)==0x000C){
            cmdName = "000C MAKE ACTOR IDLE AND END ANIMATION";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("makeActorIdleAndEndAnimation"));
        }
        else if(Word(ea+2)==0x000D){
            cmdName = "000D END ANIMATION";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("endAnimation"));            
        }
        else if(Word(ea+2)==0x000E){
            cmdName = "000E WAIT";
            cmdComment = "Duration (in frames)";
            
            // Duration
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("bscWait %s",paramOne));
        }
        else if(Word(ea+2)==0x000F){
            cmdName = "000F GIVE EXP";
            cmdComment = "";
            
            // EXP amount
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramOne = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("giveEXP %s",paramOne));
        }
        else if(Word(ea+2)==0x0010){
            cmdName = "0010 DISPLAY BATTLE MESSAGE";
            cmdComment = "Message, Combatant, Item or Spell, Number";
            
            // Message index
            ea = ItemEnd(ea);
            MakeCode(ea);
            if(Word(ea)==0x3CFC){
                paramOne = form("%s%s","#",GetConstName(GetConst(GetEnum("Messages"),Word(ea+2),-1)));
            }else{
                paramOne = GetOpnd(ea,0);
            }
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            if(strstr(GetDisasm(ea),"b")!=-1){
                ea = ItemEnd(ea);
                MakeCode(ea);
            }
            paramTwo = GetOpnd(ea,0);
            // Item or Spell index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramThree = GetOpnd(ea,0);
            // Displayed number
            ea = ItemEnd(ea);
            MakeCode(ea);
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramFour = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("displayMessage %s,%s,%s,%s",paramOne,paramTwo,paramThree,paramFour));
        }
        else if(Word(ea+2)==0x0011){
            cmdName = "0011 DISPLAY BATTLE MESSAGE WITH NO WAIT";
            cmdComment = "Message, Combatant, Item or Spell, Number";
            
            // Message index
            ea = ItemEnd(ea);
            MakeCode(ea);
            if(Word(ea)==0x3CFC){
                paramOne = form("%s%s","#",GetConstName(GetConst(GetEnum("Messages"),Word(ea+2),-1)));
            }else{
                paramOne = GetOpnd(ea,0);
            }
            // Combatant index
            ea = ItemEnd(ea);
            MakeCode(ea);
            if(strstr(GetDisasm(ea),"b")!=-1){
                ea = ItemEnd(ea);
                MakeCode(ea);
            }
            paramTwo = GetOpnd(ea,0);
            // Item or Spell index
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramThree = GetOpnd(ea,0);
            // Displayed number
            ea = ItemEnd(ea);
            MakeCode(ea);
            ea = ItemEnd(ea);
            MakeCode(ea);
            paramFour = GetOpnd(ea,0);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("displayMessageWithNoWait %s,%s,%s,%s",paramOne,paramTwo,paramThree,paramFour));
        }
        else if(Word(ea+2)==0x0012){
            cmdName = "0012 HIDE TEXT BOX";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("bscHideTextBox"));                
        }
        else if(Word(ea+2)==0x0013){
            cmdName = "0013 WAIT FOR PLAYER INPUT";
            cmdComment = "";
            cmdLength = 4;
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("bscWaitForPlayerInput"));            
        }
        else if(Word(ea+2)==0x0014){
            cmdName = "0014 NULL COMMAND";
            cmdComment = "";
            cmdLength = 4;
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("bscNullCommand"));
        }
        else if(Word(ea+2)==0xFFFF){
            cmdName = "FFFF BATTLESCENE END";
            cmdComment = "";
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeData(start,FF_BYTE,cmdLength,1);
            SetManualInsn(start,form("bscEnd"));
        }
        else{
            cmdComment = form("Unkown command : %s",ltoa(Word(ea),16));
            Message(form("\n%s%s",tab,cmdComment));
            MakeRptCmt(start,cmdComment);
            
            MakeUnknown(start,cmdLength,DOUNK_SIMPLE);
            MakeWord(start);
        }
        
        MakeRptCmt(start,form("%s%s",tab,cmdComment));
        //Message(form("\n%a : %s",ea,cmdComment));
        ea = start+cmdLength;

        
        //action = AskYN(1,"Continue ?");
    
    
        
    }
    
    //Message(form("\n%a : END OF BSC PARSING",ea));
    
    return ea;

}

