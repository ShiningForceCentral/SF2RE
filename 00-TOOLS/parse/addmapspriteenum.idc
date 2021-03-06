#include <idc.idc>


static main(void){

    addMapspriteEnumConstants();
    
}


static addMapspriteEnumConstants(){
    auto id,constId;
    id = GetEnum("Mapsprites");
    AddConstEx(id,"MAPSPRITE_BOWIE_BASE",0,-1);
    AddConstEx(id,"MAPSPRITE_BOWIE_PROMO",1 ,-1);
    SetConstCmt(GetConstEx(id,1,0,-1),"Unused : MAPSPRITE_BOWIE_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_SARAH_BASE",2,-1);
    AddConstEx(id,"MAPSPRITE_SARAH_PROMO",3,-1);
    AddConstEx(id,"MAPSPRITE_SARAH_SPECIAL",4,-1);
    AddConstEx(id,"MAPSPRITE_CHESTER_BASE",5,-1);
    AddConstEx(id,"MAPSPRITE_CHESTER_PROMO",6,-1);
    AddConstEx(id,"MAPSPRITE_CHESTER_SPECIAL",7,-1);
    AddConstEx(id,"MAPSPRITE_JAHA_BASE",8,-1);
    AddConstEx(id,"MAPSPRITE_JAHA_PROMO",9,-1);
    AddConstEx(id,"MAPSPRITE_JAHA_SPECIAL",10,-1);
    AddConstEx(id,"MAPSPRITE_KAZIN_BASE",11,-1);
    AddConstEx(id,"MAPSPRITE_KAZIN_PROMO",12,-1);
    AddConstEx(id,"MAPSPRITE_KAZIN_SPECIAL",13,-1);
    AddConstEx(id,"MAPSPRITE_SLADE_BASE",14,-1);
    AddConstEx(id,"MAPSPRITE_SLADE_PROMO",15 ,-1);
    SetConstCmt(GetConstEx(id,15,0,-1),"Unused : MAPSPRITE_SLADE_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_KIWI_BASE",16,-1);
    AddConstEx(id,"MAPSPRITE_KIWI_PROMO",17 ,-1); 
    SetConstCmt(GetConstEx(id,16,0,-1),"Unused : MAPSPRITE_KIWI_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_PETER_BASE",18,-1);
    AddConstEx(id,"MAPSPRITE_PETER_PROMO",19 ,-1); 
    SetConstCmt(GetConstEx(id,19,0,-1),"Unused : MAPSPRITE_PETER_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_MAY_BASE",20,-1);
    AddConstEx(id,"MAPSPRITE_MAY_PROMO",21 ,-1); 
    SetConstCmt(GetConstEx(id,21,0,-1),"Unused : MAPSPRITE_MAY_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_GERHALT_BASE",22,-1);
    AddConstEx(id,"MAPSPRITE_GERHALT_PROMO",23 ,-1); 
    SetConstCmt(GetConstEx(id,23,0,-1),"Unused : MAPSPRITE_GERHALT_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_LUKE_BASE",24,-1);
    AddConstEx(id,"MAPSPRITE_LUKE_PROMO",25 ,-1); 
    SetConstCmt(GetConstEx(id,25,0,-1),"Unused : MAPSPRITE_LUKE_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_ROHDE_SPECIAL",26 ,-1); 
    SetConstCmt(GetConstEx(id,26,0,-1),"Unused : MAPSPRITE_ROHDE_BASE, MAPSPRITE_ROHDE_PROMO",1);
    AddConstEx(id,"MAPSPRITE_RICK_BASE",27,-1);
    AddConstEx(id,"MAPSPRITE_RICK_PROMO",28,-1);
    AddConstEx(id,"MAPSPRITE_RICK_SPECIAL",29,-1);
    AddConstEx(id,"MAPSPRITE_ELRIC_BASE",30,-1);
    AddConstEx(id,"MAPSPRITE_ELRIC_PROMO",31,-1);
    AddConstEx(id,"MAPSPRITE_ELRIC_SPECIAL",32,-1);
    AddConstEx(id,"MAPSPRITE_ERIC_BASE",33,-1);
    AddConstEx(id,"MAPSPRITE_ERIC_PROMO",34,-1);
    AddConstEx(id,"MAPSPRITE_ERIC_SPECIAL",35,-1);
    AddConstEx(id,"MAPSPRITE_KARNA_BASE",36,-1);
    AddConstEx(id,"MAPSPRITE_KARNA_PROMO",37,-1);
    AddConstEx(id,"MAPSPRITE_KARNA_SPECIAL",38,-1);
    AddConstEx(id,"MAPSPRITE_RANDOLF_BASE",39,-1);
    AddConstEx(id,"MAPSPRITE_RANDOLF_PROMO",40,-1);
    AddConstEx(id,"MAPSPRITE_RANDOLF_SPECIAL",41,-1);
    AddConstEx(id,"MAPSPRITE_TYRIN_BASE",42,-1);
    AddConstEx(id,"MAPSPRITE_TYRIN_PROMO",43,-1);
    AddConstEx(id,"MAPSPRITE_TYRIN_SPECIAL",44,-1);
    AddConstEx(id,"MAPSPRITE_JANET_BASE",45,-1);
    AddConstEx(id,"MAPSPRITE_JANET_PROMO",46,-1);
    AddConstEx(id,"MAPSPRITE_JANET_SPECIAL",47,-1);
    AddConstEx(id,"MAPSPRITE_HIGINS_PROMO",48 ,-1); 
    SetConstCmt(GetConstEx(id,48,0,-1),"Unused : MAPSPRITE_HIGINS_BASE, MAPSPRITE_HIGINS_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_SKREECH_PROMO",49 ,-1); 
    SetConstCmt(GetConstEx(id,49,0,-1),"Unused : MAPSPRITE_SKREECH_BASE, MAPSPRITE_SKREECH_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_TAYA_SPECIAL",50 ,-1); 
    SetConstCmt(GetConstEx(id,50,0,-1),"Unused : MAPSPRITE_TAYA_BASE, MAPSPRITE_TAYA_PROMO",1);
    AddConstEx(id,"MAPSPRITE_FRAYJA_PROMO",51 ,-1); 
    SetConstCmt(GetConstEx(id,51,0,-1),"Unused : MAPSPRITE_FRAYJA_BASE, MAPSPRITE_FRAYJA_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_JARO_SPECIAL",52 ,-1); 
    SetConstCmt(GetConstEx(id,52,0,-1),"Unused : MAPSPRITE_JARO_BASE, MAPSPRITE_JARO_PROMO",1);
    AddConstEx(id,"MAPSPRITE_GYAN_PROMO",53 ,-1); 
    SetConstCmt(GetConstEx(id,53,0,-1),"Unused : MAPSPRITE_GYAN_BASE, MAPSPRITE_GYAN_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_SHEELA_SPECIAL",54 ,-1); 
    SetConstCmt(GetConstEx(id,54,0,-1),"Unused : MAPSPRITE_SHEELA_BASE, MAPSPRITE_SHEELA_PROMO",1);
    AddConstEx(id,"MAPSPRITE_ZYNK_PROMO",55 ,-1); 
    SetConstCmt(GetConstEx(id,55,0,-1),"Unused : MAPSPRITE_ZYNK_BASE, MAPSPRITE_ZYNK_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_CHAZ_PROMO",56 ,-1); 
    SetConstCmt(GetConstEx(id,56,0,-1),"Unused : MAPSPRITE_CHAZ_BASE, MAPSPRITE_CHAZ_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_LEMON_SPECIAL",57 ,-1); 
    SetConstCmt(GetConstEx(id,57,0,-1),"Unused : MAPSPRITE_LEMON_BASE, MAPSPRITE_LEMON_PROMO",1);
    AddConstEx(id,"MAPSPRITE_CLAUDE_PROMO",58 ,-1); 
    SetConstCmt(GetConstEx(id,58,0,-1),"Unused : MAPSPRITE_CLAUDE_BASE, MAPSPRITE_CLAUDE_SPECIAL, MAPSPRITE_NONAME1_BASE, MAPSPRITE_NONAME1_PROMO, MAPSPRITE_NONAME1_SPECIAL, MAPSPRITE_NONAME2_BASE, MAPSPRITE_NONAME2_PROMO, MAPSPRITE_NONAME2_SPECIAL",1);
    AddConstEx(id,"MAPSPRITE_POSE1",59,-1);
    AddConstEx(id,"MAPSPRITE_BLANK",60,-1);
    AddConstEx(id,"MAPSPRITE_RAFT",61,-1);
    AddConstEx(id,"MAPSPRITE_CARAVAN",62,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT1",63,-1);
    AddConstEx(id,"MAPSPRITE_OOZE",64,-1);
    AddConstEx(id,"MAPSPRITE_HUGE_RAT",65,-1);
    AddConstEx(id,"MAPSPRITE_GALAM_SOLDIER",66,-1);
    AddConstEx(id,"MAPSPRITE_GALAM_KNIGHT",67,-1);
    AddConstEx(id,"MAPSPRITE_GOBLIN",68,-1);
    AddConstEx(id,"MAPSPRITE_GREEN_OOZE",69,-1);
    AddConstEx(id,"MAPSPRITE_DARK_DWARF",70,-1);
    AddConstEx(id,"MAPSPRITE_HOBGOBLIN",71,-1);
    AddConstEx(id,"MAPSPRITE_ZOMBIE",72,-1);
    AddConstEx(id,"MAPSPRITE_GOLEM",73,-1);
    AddConstEx(id,"MAPSPRITE_KRAKEN_LEG",74,-1);
    AddConstEx(id,"MAPSPRITE_SOULSOWER",75,-1);
    AddConstEx(id,"MAPSPRITE_ORC",76,-1);
    AddConstEx(id,"MAPSPRITE_PAWN",77,-1);
    AddConstEx(id,"MAPSPRITE_KNIGHT",78,-1);
    AddConstEx(id,"MAPSPRITE_RAT",79,-1);
    AddConstEx(id,"MAPSPRITE_BUBBLING_OOZE",80,-1);
    AddConstEx(id,"MAPSPRITE_SKELETON",81,-1);
    AddConstEx(id,"MAPSPRITE_DARK_SOLDIER",82,-1);
    AddConstEx(id,"MAPSPRITE_LIZARDMAN",83,-1);
    AddConstEx(id,"MAPSPRITE_WORM",84,-1);
    AddConstEx(id,"MAPSPRITE_DARK_KNIGHT",85,-1);
    AddConstEx(id,"MAPSPRITE_ORC_LORD",86,-1);
    AddConstEx(id,"MAPSPRITE_DEVIL_SOLDIER",87,-1);
    AddConstEx(id,"MAPSPRITE_CERBERUS",88,-1);
    AddConstEx(id,"MAPSPRITE_MUD_MAN",89,-1);
    AddConstEx(id,"MAPSPRITE_DRAGONEWT",90,-1);
    AddConstEx(id,"MAPSPRITE_PURPLE_WORM",91,-1);
    AddConstEx(id,"MAPSPRITE_EXECUTIONER",92,-1);
    AddConstEx(id,"MAPSPRITE_HELL_HOUND",93,-1);
    AddConstEx(id,"MAPSPRITE_MINOTAUR",94,-1);
    AddConstEx(id,"MAPSPRITE_CYCLOPS",95,-1);
    AddConstEx(id,"MAPSPRITE_BURST_ROCK",96,-1);
    AddConstEx(id,"MAPSPRITE_HYDRA",97,-1);
    AddConstEx(id,"MAPSPRITE_CHAOS_WARRIOR",98,-1);
    AddConstEx(id,"MAPSPRITE_REAPER",99,-1);
    AddConstEx(id,"MAPSPRITE_EVIL_BEAST",100,-1);
    AddConstEx(id,"MAPSPRITE_PYROHYDRA",101,-1);
    AddConstEx(id,"MAPSPRITE_ZEON_GUARD",102,-1);
    AddConstEx(id,"MAPSPRITE_GIZMO",103,-1);
    AddConstEx(id,"MAPSPRITE_HUGE_BAT",104,-1);
    AddConstEx(id,"MAPSPRITE_VAMPIRE_BAT",105,-1);
    AddConstEx(id,"MAPSPRITE_EVIL_CLOUD",106,-1);
    AddConstEx(id,"MAPSPRITE_GARGOYLE",107,-1);
    AddConstEx(id,"MAPSPRITE_HARPY",108,-1);
    AddConstEx(id,"MAPSPRITE_LESSER_DEMON",109,-1);
    AddConstEx(id,"MAPSPRITE_WYVERN",110,-1);
    AddConstEx(id,"MAPSPRITE_HARPY_QUEEN",111,-1);
    AddConstEx(id,"MAPSPRITE_PEGASUS_KNIGHT",112,-1);
    AddConstEx(id,"MAPSPRITE_GRIFFIN",113,-1);
    AddConstEx(id,"MAPSPRITE_MIST_DEMON",114,-1);
    AddConstEx(id,"MAPSPRITE_WHITE_DRAGON",115,-1);
    AddConstEx(id,"MAPSPRITE_DEMON",116,-1);
    AddConstEx(id,"MAPSPRITE_CHAOS_DRAGON",117,-1);
    AddConstEx(id,"MAPSPRITE_DEVIL_GRIFFIN",118,-1);
    AddConstEx(id,"MAPSPRITE_ARCH_DEMON",119,-1);
    AddConstEx(id,"MAPSPRITE_GALAM_ARCHER",120,-1);
    AddConstEx(id,"MAPSPRITE_HUNTER_GOBLIN",121,-1);
    AddConstEx(id,"MAPSPRITE_DEATH_ARCHER",122,-1);
    AddConstEx(id,"MAPSPRITE_KRAKEN_ARM",123,-1);
    AddConstEx(id,"MAPSPRITE_ARROW_LAUNCHER",124,-1);
    AddConstEx(id,"MAPSPRITE_ROOK",125,-1);
    AddConstEx(id,"MAPSPRITE_DARK_SNIPER",126,-1);
    AddConstEx(id,"MAPSPRITE_BOW_MASTER",127,-1);
    AddConstEx(id,"MAPSPRITE_BOW_RIDER",128,-1);
    AddConstEx(id,"MAPSPRITE_DARK_GUNNER",129,-1);
    AddConstEx(id,"MAPSPRITE_HORSEMAN",130,-1);
    AddConstEx(id,"MAPSPRITE_GALAM_MAGE",131,-1);
    AddConstEx(id,"MAPSPRITE_WITCH",132,-1);
    AddConstEx(id,"MAPSPRITE_MASTER_MAGE",133,-1);
    AddConstEx(id,"MAPSPRITE_DARK_MADAM",134,-1);
    AddConstEx(id,"MAPSPRITE_QUEEN",135,-1);
    AddConstEx(id,"MAPSPRITE_WIZARD",136,-1);
    AddConstEx(id,"MAPSPRITE_NECROMANCER",137,-1);
    AddConstEx(id,"MAPSPRITE_CHAOS_WIZARD",138,-1);
    AddConstEx(id,"MAPSPRITE_DEMON_MASTER",139,-1);
    AddConstEx(id,"MAPSPRITE_DARK_CLERIC",140,-1);
    AddConstEx(id,"MAPSPRITE_DEATH_MONK",141,-1);
    AddConstEx(id,"MAPSPRITE_BLACK_MONK",142,-1);
    AddConstEx(id,"MAPSPRITE_HIGH_PRIEST",143,-1);
    AddConstEx(id,"MAPSPRITE_EVIL_BISHOP",144,-1);
    AddConstEx(id,"MAPSPRITE_DARK_BISHOP",145,-1);
    AddConstEx(id,"MAPSPRITE_MASTER_MONK",146,-1);
    AddConstEx(id,"MAPSPRITE_SHAMAN",147,-1);
    AddConstEx(id,"MAPSPRITE_EVIL_BISHOP",148,-1);
    AddConstEx(id,"MAPSPRITE_BLUE_SHAMAN",149,-1);
    AddConstEx(id,"MAPSPRITE_DARK_SMOKE",150,-1);
    AddConstEx(id,"MAPSPRITE_FILLER1",151,-1); 
    SetConstCmt(GetConstEx(id,151,0,-1),"Filling for KRAKEN HEAD",1);
    AddConstEx(id,"MAPSPRITE_FILLER2",152,-1); 
    SetConstCmt(GetConstEx(id,152,0,-1),"Filling for TAROS",1);
    AddConstEx(id,"MAPSPRITE_KING",153,-1);
    AddConstEx(id,"MAPSPRITE_WILLARD",154,-1);
    AddConstEx(id,"MAPSPRITE_ZALBARD",155,-1);
    AddConstEx(id,"MAPSPRITE_CAMEELA",156,-1);
    AddConstEx(id,"MAPSPRITE_PRISM_FLOWER",157,-1);
    AddConstEx(id,"MAPSPRITE_RED_BARON",158 ,-1); 
    SetConstCmt(GetConstEx(id,158,0,-1),"Duplicate of 57, go without Portrait",1);
    AddConstEx(id,"MAPSPRITE_GESHP",159,-1);
    AddConstEx(id,"MAPSPRITE_ODD_EYE",160,-1);
    AddConstEx(id,"MAPSPRITE_FILLER3",161,-1); 
    SetConstCmt(GetConstEx(id,161,0,-1),"Filling for ???",1);
    AddConstEx(id,"MAPSPRITE_FILLER4",162,-1); 
    SetConstCmt(GetConstEx(id,162,0,-1),"Filling for ???",1);
    AddConstEx(id,"MAPSPRITE_GALAM_ZEON",163,-1); 
    SetConstCmt(GetConstEx(id,163,0,-1),"go with Zeon Portrait (46)",1);
    AddConstEx(id,"MAPSPRITE_GALAM_EVIL",164,-1); 
    SetConstCmt(GetConstEx(id,164,0,-1),"Duplicate of 164, go with Evil Galam Portrait (39)",1);
    AddConstEx(id,"MAPSPRITE_FILLER5",165,-1); 
    SetConstCmt(GetConstEx(id,165,0,-1),"Filling for Zeon ???",1);
    AddConstEx(id,"MAPSPRITE_FILLER6",166,-1); 
    SetConstCmt(GetConstEx(id,166,0,-1),"Filling for Zeon ???",1);
    AddConstEx(id,"MAPSPRITE_FILLER7",167,-1); 
    SetConstCmt(GetConstEx(id,167,0,-1),"Filling for Zeon ???",1);
    AddConstEx(id,"MAPSPRITE_FILLER8",168,-1); 
    SetConstCmt(GetConstEx(id,168,0,-1),"Filling for Zeon ???",1);
    AddConstEx(id,"MAPSPRITE_FILLER9",169,-1); 
    SetConstCmt(GetConstEx(id,169,0,-1),"Filling for Zeon ???",1);
    AddConstEx(id,"MAPSPRITE_NPC_ROHDE",170,-1);
    AddConstEx(id,"MAPSPRITE_FLAME1",171,-1);
    AddConstEx(id,"MAPSPRITE_ORB",172,-1);
    AddConstEx(id,"MAPSPRITE_OBJECT1",173,-1);
    AddConstEx(id,"MAPSPRITE_POSE2",174,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT2",175,-1);
    AddConstEx(id,"MAPSPRITE_POSE3",176,-1);
    AddConstEx(id,"MAPSPRITE_POSE4",177,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT3",178,-1);
    AddConstEx(id,"MAPSPRITE_OBJECT2",179,-1);
    AddConstEx(id,"MAPSPRITE_OBJECT3",180,-1);
    AddConstEx(id,"MAPSPRITE_OBJECT4",181,-1);
    AddConstEx(id,"MAPSPRITE_CHICK_Flying",182,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT4",183,-1);
    AddConstEx(id,"MAPSPRITE_POSE5",184,-1);
    AddConstEx(id,"MAPSPRITE_ZELOT",185,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT5",186,-1);
    AddConstEx(id,"MAPSPRITE_EFFECT6",187,-1);
    AddConstEx(id,"MAPSPRITE_DESKTOP_KING",188,-1); 
    SetConstCmt(GetConstEx(id,188,0,-1),"Duplicate of 203, go without Portrait",1);
    AddConstEx(id,"MAPSPRITE_HAWEL",189,-1);
    AddConstEx(id,"MAPSPRITE_BLUE_FLAME",190,-1);
    AddConstEx(id,"MAPSPRITE_FILLER10",191 ,-1); 
    SetConstCmt(GetConstEx(id,191,0,-1),"Filling for ???",1);
    AddConstEx(id,"MAPSPRITE_PRIEST",192,-1);
    AddConstEx(id,"MAPSPRITE_SAILOR",193,-1);
    AddConstEx(id,"MAPSPRITE_MAN1",194,-1);
    AddConstEx(id,"MAPSPRITE_WOMAN1",195,-1);
    AddConstEx(id,"MAPSPRITE_MAN2",196,-1);
    AddConstEx(id,"MAPSPRITE_WOMAN2",197,-1);
    AddConstEx(id,"MAPSPRITE_MAN3",198,-1);
    AddConstEx(id,"MAPSPRITE_WOMAN3",199,-1);
    AddConstEx(id,"MAPSPRITE_BOY",200,-1);
    AddConstEx(id,"MAPSPRITE_GIRL",201,-1);
    AddConstEx(id,"MAPSPRITE_WORKER",202,-1);
    AddConstEx(id,"MAPSPRITE_GRANSEAL_KING",203,-1);
    AddConstEx(id,"MAPSPRITE_ELIS",204,-1);
    AddConstEx(id,"MAPSPRITE_MINISTER",205,-1);
    AddConstEx(id,"MAPSPRITE_SOLDIER1",206,-1);
    AddConstEx(id,"MAPSPRITE_SOLDIER2",207,-1);
    AddConstEx(id,"MAPSPRITE_MAID",208,-1);
    AddConstEx(id,"MAPSPRITE_ASTRAL",209,-1);
    AddConstEx(id,"MAPSPRITE_CAT",210,-1);
    AddConstEx(id,"MAPSPRITE_BOAT",211,-1);
    AddConstEx(id,"MAPSPRITE_CREED",212,-1);
    AddConstEx(id,"MAPSPRITE_ODDLER",213,-1);
    AddConstEx(id,"MAPSPRITE_GALAM_KING",214,-1);
    SetConstCmt(GetConstEx(id,214,0,-1),"Duplicate of 164, go with Old Galam Portrait (38)",1);
    AddConstEx(id,"MAPSPRITE_MITULA",215,-1);
    AddConstEx(id,"MAPSPRITE_POSE6",216,-1);
    AddConstEx(id,"MAPSPRITE_POSE7",217,-1);
    AddConstEx(id,"MAPSPRITE_DUCK",218,-1);
    AddConstEx(id,"MAPSPRITE_FAIRY",219,-1);
    AddConstEx(id,"MAPSPRITE_BEASTMAN1",220,-1);
    AddConstEx(id,"MAPSPRITE_TURTLE",221,-1);
    AddConstEx(id,"MAPSPRITE_BEASTMAN2",222,-1);
    AddConstEx(id,"MAPSPRITE_ELF_BOY",223,-1);
    AddConstEx(id,"MAPSPRITE_ELF_GIRL",224,-1);
    AddConstEx(id,"MAPSPRITE_VIKING",225,-1);
    AddConstEx(id,"MAPSPRITE_DWARF",226,-1);
    AddConstEx(id,"MAPSPRITE_BEDOE_KING",227,-1);
    AddConstEx(id,"MAPSPRITE_BEDOE_MINISTER",228,-1);
    AddConstEx(id,"MAPSPRITE_BEDOE_SOLDIER",229,-1);
    AddConstEx(id,"MAPSPRITE_CHICK",230,-1);
    AddConstEx(id,"MAPSPRITE_POCALON_KING",231,-1);
    AddConstEx(id,"MAPSPRITE_POCALON_PRINCESS",232,-1);
    AddConstEx(id,"MAPSPRITE_POCALON_SOLDIER",233,-1);
    AddConstEx(id,"MAPSPRITE_POCALON_MAID",234,-1);
    AddConstEx(id,"MAPSPRITE_HEN",235,-1);
    AddConstEx(id,"MAPSPRITE_BIRDMAN",236,-1);
    AddConstEx(id,"MAPSPRITE_END_LIST",237,-1);
    SetConstCmt(GetConstEx(id,237,0,-1),"to use 2 more sprite this one should become 239",1);
    AddConstEx(id,"MAPSPRITE_FREE_SPOT1",238,-1);
    AddConstEx(id,"MAPSPRITE_FREE_SPOT2",239,-1);
    AddConstEx(id,"MAPSPRITE_SPECIAL0",240 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL1",241 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL2",242 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL3",243 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL4",244 ,-1);
    AddConstEx(id,"MAPSPRITE_SPECIAL5",245 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL6",246 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL7",247 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL8",248 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL9",249 ,-1); 
    AddConstEx(id,"MAPSPRITE_SPECIAL10",250,-1);
    AddConstEx(id,"MAPSPRITE_ZEON",251,-1);
    AddConstEx(id,"MAPSPRITE_EVIL_SPIRIT",252,-1);
    AddConstEx(id,"MAPSPRITE_NAZCA_SHIP",253,-1);
    AddConstEx(id,"MAPSPRITE_KRAKEN",254,-1);
    AddConstEx(id,"MAPSPRITE_TAROS",255,-1);    
    return;
}
/*
AddConstEx(id,"MAPSPRITE_BOWIE_BASE",0,-1);
AddConstEx(id,"MAPSPRITE_BOWIE_PROMO",1 ,-1);
AddConstEx(id,"MAPSPRITE_SARAH_BASE",2,-1);
AddConstEx(id,"MAPSPRITE_SARAH_PROMO",3,-1);
AddConstEx(id,"MAPSPRITE_SARAH_SPECIAL",4,-1);
AddConstEx(id,"MAPSPRITE_CHESTER_BASE",5,-1);
AddConstEx(id,"MAPSPRITE_CHESTER_PROMO",6,-1);
AddConstEx(id,"MAPSPRITE_CHESTER_SPECIAL",7,-1);
AddConstEx(id,"MAPSPRITE_JAHA_BASE",8,-1);
AddConstEx(id,"MAPSPRITE_JAHA_PROMO",9,-1);
AddConstEx(id,"MAPSPRITE_JAHA_SPECIAL",10,-1);
AddConstEx(id,"MAPSPRITE_KAZIN_BASE",11,-1);
AddConstEx(id,"MAPSPRITE_KAZIN_PROMO",12,-1);
AddConstEx(id,"MAPSPRITE_KAZIN_SPECIAL",13,-1);
AddConstEx(id,"MAPSPRITE_SLADE_BASE",14,-1);
AddConstEx(id,"MAPSPRITE_SLADE_PROMO",15 ,-1); Unused : MAPSPRITE_SLADE_SPECIAL
AddConstEx(id,"MAPSPRITE_KIWI_BASE",16,-1);
AddConstEx(id,"MAPSPRITE_KIWI_PROMO",17 ,-1); Unused : MAPSPRITE_KIWI_SPECIAL
AddConstEx(id,"MAPSPRITE_PETER_BASE",18,-1);
AddConstEx(id,"MAPSPRITE_PETER_PROMO",19 ,-1); Unused : MAPSPRITE_PETER_SPECIAL
AddConstEx(id,"MAPSPRITE_MAY_BASE",20,-1);
AddConstEx(id,"MAPSPRITE_MAY_PROMO",21 ,-1); Unused : MAPSPRITE_MAY_SPECIAL
AddConstEx(id,"MAPSPRITE_GERHALT_BASE",22,-1);
AddConstEx(id,"MAPSPRITE_GERHALT_PROMO",23 ,-1); Unused : MAPSPRITE_GERHALT_SPECIAL
AddConstEx(id,"MAPSPRITE_LUKE_BASE",24,-1);
AddConstEx(id,"MAPSPRITE_LUKE_PROMO",25 ,-1); Unused : MAPSPRITE_LUKE_SPECIAL
AddConstEx(id,"MAPSPRITE_ROHDE_SPECIAL",26 ,-1); Unused : MAPSPRITE_ROHDE_BASE, MAPSPRITE_ROHDE_PROMO
AddConstEx(id,"MAPSPRITE_RICK_BASE",27,-1);
AddConstEx(id,"MAPSPRITE_RICK_PROMO",28,-1);
AddConstEx(id,"MAPSPRITE_RICK_SPECIAL",29,-1);
AddConstEx(id,"MAPSPRITE_ELRIC_BASE",30,-1);
AddConstEx(id,"MAPSPRITE_ELRIC_PROMO",31,-1);
AddConstEx(id,"MAPSPRITE_ELRIC_SPECIAL",32,-1);
AddConstEx(id,"MAPSPRITE_ERIC_BASE",33,-1);
AddConstEx(id,"MAPSPRITE_ERIC_PROMO",34,-1);
AddConstEx(id,"MAPSPRITE_ERIC_SPECIAL",35,-1);
AddConstEx(id,"MAPSPRITE_KARNA_BASE",36,-1);
AddConstEx(id,"MAPSPRITE_KARNA_PROMO",37,-1);
AddConstEx(id,"MAPSPRITE_KARNA_SPECIAL",38,-1);
AddConstEx(id,"MAPSPRITE_RANDOLF_BASE",39,-1);
AddConstEx(id,"MAPSPRITE_RANDOLF_PROMO",40,-1);
AddConstEx(id,"MAPSPRITE_RANDOLF_SPECIAL",41,-1);
AddConstEx(id,"MAPSPRITE_TYRIN_BASE",42,-1);
AddConstEx(id,"MAPSPRITE_TYRIN_PROMO",43,-1);
AddConstEx(id,"MAPSPRITE_TYRIN_SPECIAL",44,-1);
AddConstEx(id,"MAPSPRITE_JANET_BASE",45,-1);
AddConstEx(id,"MAPSPRITE_JANET_PROMO",46,-1);
AddConstEx(id,"MAPSPRITE_JANET_SPECIAL",47,-1);
AddConstEx(id,"MAPSPRITE_HIGINS_PROMO",48 ,-1); Unused : MAPSPRITE_HIGINS_BASE, MAPSPRITE_HIGINS_SPECIAL
AddConstEx(id,"MAPSPRITE_SKREECH_PROMO",49 ,-1); Unused : MAPSPRITE_SKREECH_BASE, MAPSPRITE_SKREECH_SPECIAL
AddConstEx(id,"MAPSPRITE_TAYA_SPECIAL",50 ,-1); Unused : MAPSPRITE_TAYA_BASE, MAPSPRITE_TAYA_PROMO
AddConstEx(id,"MAPSPRITE_FRAYJA_PROMO",51 ,-1); Unused : MAPSPRITE_FRAYJA_BASE, MAPSPRITE_FRAYJA_SPECIAL
AddConstEx(id,"MAPSPRITE_JARO_SPECIAL",52 ,-1); Unused : MAPSPRITE_JARO_BASE, MAPSPRITE_JARO_PROMO
AddConstEx(id,"MAPSPRITE_GYAN_PROMO",53 ,-1); Unused : MAPSPRITE_GYAN_BASE, MAPSPRITE_GYAN_SPECIAL
AddConstEx(id,"MAPSPRITE_SHEELA_SPECIAL",54 ,-1); Unused : MAPSPRITE_SHEELA_BASE, MAPSPRITE_SHEELA_PROMO
AddConstEx(id,"MAPSPRITE_ZYNK_PROMO",55 ,-1); Unused : MAPSPRITE_ZYNK_BASE, MAPSPRITE_ZYNK_SPECIAL
AddConstEx(id,"MAPSPRITE_CHAZ_PROMO",56 ,-1); Unused : MAPSPRITE_CHAZ_BASE, MAPSPRITE_CHAZ_SPECIAL
AddConstEx(id,"MAPSPRITE_LEMON_SPECIAL",57 ,-1); Unused : MAPSPRITE_LEMON_BASE, MAPSPRITE_LEMON_PROMO
AddConstEx(id,"MAPSPRITE_CLAUDE_PROMO",58 ,-1); Unused : MAPSPRITE_CLAUDE_BASE, MAPSPRITE_CLAUDE_SPECIAL, MAPSPRITE_NONAME1_BASE, MAPSPRITE_NONAME1_PROMO, MAPSPRITE_NONAME1_SPECIAL, MAPSPRITE_NONAME2_BASE, MAPSPRITE_NONAME2_PROMO, MAPSPRITE_NONAME2_SPECIAL
AddConstEx(id,"MAPSPRITE_POSE1",59,-1);
AddConstEx(id,"MAPSPRITE_BLANK",60,-1);
AddConstEx(id,"MAPSPRITE_RAFT",61,-1);
AddConstEx(id,"MAPSPRITE_CARAVAN",62,-1);
AddConstEx(id,"MAPSPRITE_EFFECT1",63,-1);
AddConstEx(id,"MAPSPRITE_OOZE",64,-1);
AddConstEx(id,"MAPSPRITE_HUGE_RAT",65,-1);
AddConstEx(id,"MAPSPRITE_GALAM_SOLDIER",66,-1);
AddConstEx(id,"MAPSPRITE_GALAM_KNIGHT",67,-1);
AddConstEx(id,"MAPSPRITE_GOBLIN",68,-1);
AddConstEx(id,"MAPSPRITE_GREEN_OOZE",69,-1);
AddConstEx(id,"MAPSPRITE_DARK_DWARF",70,-1);
AddConstEx(id,"MAPSPRITE_HOBGOBLIN",71,-1);
AddConstEx(id,"MAPSPRITE_ZOMBIE",72,-1);
AddConstEx(id,"MAPSPRITE_GOLEM",73,-1);
AddConstEx(id,"MAPSPRITE_KRAKEN_LEG",74,-1);
AddConstEx(id,"MAPSPRITE_SOULSOWER",75,-1);
AddConstEx(id,"MAPSPRITE_ORC",76,-1);
AddConstEx(id,"MAPSPRITE_PAWN",77,-1);
AddConstEx(id,"MAPSPRITE_KNIGHT",78,-1);
AddConstEx(id,"MAPSPRITE_RAT",79,-1);
AddConstEx(id,"MAPSPRITE_BUBBLING_OOZE",80,-1);
AddConstEx(id,"MAPSPRITE_SKELETON",81,-1);
AddConstEx(id,"MAPSPRITE_DARK_SOLDIER",82,-1);
AddConstEx(id,"MAPSPRITE_LIZARDMAN",83,-1);
AddConstEx(id,"MAPSPRITE_WORM",84,-1);
AddConstEx(id,"MAPSPRITE_DARK_KNIGHT",85,-1);
AddConstEx(id,"MAPSPRITE_ORC_LORD",86,-1);
AddConstEx(id,"MAPSPRITE_DEVIL_SOLDIER",87,-1);
AddConstEx(id,"MAPSPRITE_CERBERUS",88,-1);
AddConstEx(id,"MAPSPRITE_MUD_MAN",89,-1);
AddConstEx(id,"MAPSPRITE_DRAGONEWT",90,-1);
AddConstEx(id,"MAPSPRITE_PURPLE_WORM",91,-1);
AddConstEx(id,"MAPSPRITE_EXECUTIONER",92,-1);
AddConstEx(id,"MAPSPRITE_HELL_HOUND",93,-1);
AddConstEx(id,"MAPSPRITE_MINOTAUR",94,-1);
AddConstEx(id,"MAPSPRITE_CYCLOPS",95,-1);
AddConstEx(id,"MAPSPRITE_BURST_ROCK",96,-1);
AddConstEx(id,"MAPSPRITE_HYDRA",97,-1);
AddConstEx(id,"MAPSPRITE_CHAOS_WARRIOR",98,-1);
AddConstEx(id,"MAPSPRITE_REAPER",99,-1);
AddConstEx(id,"MAPSPRITE_EVIL_BEAST",100,-1);
AddConstEx(id,"MAPSPRITE_PYROHYDRA",101,-1);
AddConstEx(id,"MAPSPRITE_ZEON_GUARD",102,-1);
AddConstEx(id,"MAPSPRITE_GIZMO",103,-1);
AddConstEx(id,"MAPSPRITE_HUGE_BAT",104,-1);
AddConstEx(id,"MAPSPRITE_VAMPIRE_BAT",105,-1);
AddConstEx(id,"MAPSPRITE_EVIL_CLOUD",106,-1);
AddConstEx(id,"MAPSPRITE_GARGOYLE",107,-1);
AddConstEx(id,"MAPSPRITE_HARPY",108,-1);
AddConstEx(id,"MAPSPRITE_LESSER_DEMON",109,-1);
AddConstEx(id,"MAPSPRITE_WYVERN",110,-1);
AddConstEx(id,"MAPSPRITE_HARPY_QUEEN",111,-1);
AddConstEx(id,"MAPSPRITE_PEGASUS_KNIGHT",112,-1);
AddConstEx(id,"MAPSPRITE_GRIFFIN",113,-1);
AddConstEx(id,"MAPSPRITE_MIST_DEMON",114,-1);
AddConstEx(id,"MAPSPRITE_WHITE_DRAGON",115,-1);
AddConstEx(id,"MAPSPRITE_DEMON",116,-1);
AddConstEx(id,"MAPSPRITE_CHAOS_DRAGON",117,-1);
AddConstEx(id,"MAPSPRITE_DEVIL_GRIFFIN",118,-1);
AddConstEx(id,"MAPSPRITE_ARCH_DEMON",119,-1);
AddConstEx(id,"MAPSPRITE_GALAM_ARCHER",120,-1);
AddConstEx(id,"MAPSPRITE_HUNTER_GOBLIN",121,-1);
AddConstEx(id,"MAPSPRITE_DEATH_ARCHER",122,-1);
AddConstEx(id,"MAPSPRITE_KRAKEN_ARM",123,-1);
AddConstEx(id,"MAPSPRITE_ARROW_LAUNCHER",124,-1);
AddConstEx(id,"MAPSPRITE_ROOK",125,-1);
AddConstEx(id,"MAPSPRITE_DARK_SNIPER",126,-1);
AddConstEx(id,"MAPSPRITE_BOW_MASTER",127,-1);
AddConstEx(id,"MAPSPRITE_BOW_RIDER",128,-1);
AddConstEx(id,"MAPSPRITE_DARK_GUNNER",129,-1);
AddConstEx(id,"MAPSPRITE_HORSEMAN",130,-1);
AddConstEx(id,"MAPSPRITE_GALAM_MAGE",131,-1);
AddConstEx(id,"MAPSPRITE_WITCH",132,-1);
AddConstEx(id,"MAPSPRITE_MASTER_MAGE",133,-1);
AddConstEx(id,"MAPSPRITE_DARK_MADAM",134,-1);
AddConstEx(id,"MAPSPRITE_QUEEN",135,-1);
AddConstEx(id,"MAPSPRITE_WIZARD",136,-1);
AddConstEx(id,"MAPSPRITE_NECROMANCER",137,-1);
AddConstEx(id,"MAPSPRITE_CHAOS_WIZARD",138,-1);
AddConstEx(id,"MAPSPRITE_DEMON_MASTER",139,-1);
AddConstEx(id,"MAPSPRITE_DARK_CLERIC",140,-1);
AddConstEx(id,"MAPSPRITE_DEATH_MONK",141,-1);
AddConstEx(id,"MAPSPRITE_BLACK_MONK",142,-1);
AddConstEx(id,"MAPSPRITE_HIGH_PRIEST",143,-1);
AddConstEx(id,"MAPSPRITE_EVIL_BISHOP",144,-1);
AddConstEx(id,"MAPSPRITE_DARK_BISHOP",145,-1);
AddConstEx(id,"MAPSPRITE_MASTER_MONK",146,-1);
AddConstEx(id,"MAPSPRITE_SHAMAN",147,-1);
AddConstEx(id,"MAPSPRITE_EVIL_BISHOP",148,-1);
AddConstEx(id,"MAPSPRITE_BLUE_SHAMAN",149,-1);
AddConstEx(id,"MAPSPRITE_DARK_SMOKE",150,-1);
AddConstEx(id,"MAPSPRITE_FILLER1",151 ,-1); Filling for KRAKEN HEAD
AddConstEx(id,"MAPSPRITE_FILLER2",152 ,-1); Filling for TAROS
AddConstEx(id,"MAPSPRITE_KING",153,-1);
AddConstEx(id,"MAPSPRITE_WILLARD",154,-1);
AddConstEx(id,"MAPSPRITE_ZALBARD",155,-1);
AddConstEx(id,"MAPSPRITE_CAMEELA",156,-1);
AddConstEx(id,"MAPSPRITE_PRISM_FLOWER",157,-1);
AddConstEx(id,"MAPSPRITE_RED_BARON",158 ,-1); Duplicate of 57, go without Portrait
AddConstEx(id,"MAPSPRITE_GESHP",159,-1);
AddConstEx(id,"MAPSPRITE_ODD_EYE",160,-1);
AddConstEx(id,"MAPSPRITE_FILLER3",161 ,-1); Filling for ???
AddConstEx(id,"MAPSPRITE_FILLER4",162 ,-1); Filling for ???
AddConstEx(id,"MAPSPRITE_GALAM_ZEON",163 ,-1); go with Zeon Portrait (46)
AddConstEx(id,"MAPSPRITE_GALAM_EVIL",164 ,-1); Duplicate of 164, go with Evil Galam Portrait (39)
AddConstEx(id,"MAPSPRITE_FILLER5",165 ,-1); Filling for Zeon ???
AddConstEx(id,"MAPSPRITE_FILLER6",166 ,-1); Filling for Zeon ???
AddConstEx(id,"MAPSPRITE_FILLER7",167 ,-1); Filling for Zeon ???
AddConstEx(id,"MAPSPRITE_FILLER8",168 ,-1); Filling for Zeon ???
AddConstEx(id,"MAPSPRITE_FILLER9",169 ,-1); Filling for Zeon ???
AddConstEx(id,"MAPSPRITE_NPC_ROHDE",170,-1);
AddConstEx(id,"MAPSPRITE_FLAME1",171,-1);
AddConstEx(id,"MAPSPRITE_ORB",172,-1);
AddConstEx(id,"MAPSPRITE_OBJECT1",173,-1);
AddConstEx(id,"MAPSPRITE_POSE2",174,-1);
AddConstEx(id,"MAPSPRITE_EFFECT2",175,-1);
AddConstEx(id,"MAPSPRITE_POSE3",176,-1);
AddConstEx(id,"MAPSPRITE_POSE4",177,-1);
AddConstEx(id,"MAPSPRITE_EFFECT3",178,-1);
AddConstEx(id,"MAPSPRITE_OBJECT2",179,-1);
AddConstEx(id,"MAPSPRITE_OBJECT3",180,-1);
AddConstEx(id,"MAPSPRITE_OBJECT4",181,-1);
AddConstEx(id,"MAPSPRITE_CHICK_Flying",182,-1);
AddConstEx(id,"MAPSPRITE_EFFECT4",183,-1);
AddConstEx(id,"MAPSPRITE_POSE5",184,-1);
AddConstEx(id,"MAPSPRITE_ZELOT",185,-1);
AddConstEx(id,"MAPSPRITE_EFFECT5",186,-1);
AddConstEx(id,"MAPSPRITE_EFFECT6",187,-1);
AddConstEx(id,"MAPSPRITE_DESKTOP_KING",188 ,-1); Duplicate of 203, go without Portrait
AddConstEx(id,"MAPSPRITE_HAWEL",189,-1);
AddConstEx(id,"MAPSPRITE_BLUE_FLAME",190,-1);
AddConstEx(id,"MAPSPRITE_FILLER10",191 ,-1); Filling for ???
AddConstEx(id,"MAPSPRITE_PRIEST",192,-1);
AddConstEx(id,"MAPSPRITE_SAILOR",193,-1);
AddConstEx(id,"MAPSPRITE_MAN1",194,-1);
AddConstEx(id,"MAPSPRITE_WOMAN1",195,-1);
AddConstEx(id,"MAPSPRITE_MAN2",196,-1);
AddConstEx(id,"MAPSPRITE_WOMAN2",197,-1);
AddConstEx(id,"MAPSPRITE_MAN3",198,-1);
AddConstEx(id,"MAPSPRITE_WOMAN3",199,-1);
AddConstEx(id,"MAPSPRITE_BOY",200,-1);
AddConstEx(id,"MAPSPRITE_GIRL",201,-1);
AddConstEx(id,"MAPSPRITE_WORKER",202,-1);
AddConstEx(id,"MAPSPRITE_GRANSEAL_KING",203,-1);
AddConstEx(id,"MAPSPRITE_ELIS",204,-1);
AddConstEx(id,"MAPSPRITE_MINISTER",205,-1);
AddConstEx(id,"MAPSPRITE_SOLDIER1",206,-1);
AddConstEx(id,"MAPSPRITE_SOLDIER2",207,-1);
AddConstEx(id,"MAPSPRITE_MAID",208,-1);
AddConstEx(id,"MAPSPRITE_ASTRAL",209,-1);
AddConstEx(id,"MAPSPRITE_CAT",210,-1);
AddConstEx(id,"MAPSPRITE_BOAT",211,-1);
AddConstEx(id,"MAPSPRITE_CREED",212,-1);
AddConstEx(id,"MAPSPRITE_ODDLER",213,-1);
AddConstEx(id,"MAPSPRITE_GALAM_KING",214 ,-1); Duplicate of 164, go with Old Galam Portrait (38)
AddConstEx(id,"MAPSPRITE_MITULA",215,-1);
AddConstEx(id,"MAPSPRITE_POSE6",216,-1);
AddConstEx(id,"MAPSPRITE_POSE7",217,-1);
AddConstEx(id,"MAPSPRITE_DUCK",218,-1);
AddConstEx(id,"MAPSPRITE_FAIRY",219,-1);
AddConstEx(id,"MAPSPRITE_BEASTMAN1",220,-1);
AddConstEx(id,"MAPSPRITE_TURTLE",221,-1);
AddConstEx(id,"MAPSPRITE_BEASTMAN2",222,-1);
AddConstEx(id,"MAPSPRITE_ELF_BOY",223,-1);
AddConstEx(id,"MAPSPRITE_ELF_GIRL",224,-1);
AddConstEx(id,"MAPSPRITE_VIKING",225,-1);
AddConstEx(id,"MAPSPRITE_DWARF",226,-1);
AddConstEx(id,"MAPSPRITE_BEDOE_KING",227,-1);
AddConstEx(id,"MAPSPRITE_BEDOE_MINISTER",228,-1);
AddConstEx(id,"MAPSPRITE_BEDOE_SOLDIER",229,-1);
AddConstEx(id,"MAPSPRITE_CHICK",230,-1);
AddConstEx(id,"MAPSPRITE_POCALON_KING",231,-1);
AddConstEx(id,"MAPSPRITE_POCALON_PRINCESS",232,-1);
AddConstEx(id,"MAPSPRITE_POCALON_SOLDIER",233,-1);
AddConstEx(id,"MAPSPRITE_POCALON_MAID",234,-1);
AddConstEx(id,"MAPSPRITE_HEN",235,-1);
AddConstEx(id,"MAPSPRITE_BIRDMAN",236,-1);
AddConstEx(id,"MAPSPRITE_END_LIST",237 ,-1); to use 2 more sprite this one should become 239
AddConstEx(id,"MAPSPRITE_FREE_SPOT1",238,-1);
AddConstEx(id,"MAPSPRITE_FREE_SPOT2",239,-1);
AddConstEx(id,"MAPSPRITE_SPECIAL0",240 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL1",241 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL2",242 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL3",243 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL4",244 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL5",245 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL6",246 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL7",247 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL8",248 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL9",249 ,-1); ????
AddConstEx(id,"MAPSPRITE_SPECIAL10",250,-1);
AddConstEx(id,"MAPSPRITE_ZEON",251,-1);
AddConstEx(id,"MAPSPRITE_EVIL_SPIRIT",252,-1);
AddConstEx(id,"MAPSPRITE_NAZCA_SHIP",253,-1);
AddConstEx(id,"MAPSPRITE_KRAKEN",254,-1);
AddConstEx(id,"MAPSPRITE_TAROS",255,-1);
*/