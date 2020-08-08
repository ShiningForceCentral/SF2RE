

#include <idc.idc>



static main(void){


    splitAll();


}







static splitAll(){
    auto file;

    Message("SPLITTING...\n");
    file = fopen("sf2splits.txt","w");
    initFile(file);

    Message("Pointer Tables...");
    splitPTs(file);
    Message(" DONE.\nSingle Chunks...");    
    splitSingleChunks(file);    
    Message(" DONE.\nMapsprites ...");
    splitMapsprites(file);
    Message(" DONE.\nMaps ...");
    splitMaps(file);
    Message(" DONE.\nGrounds...");    
    splitGrounds(file);
    Message(" DONE.\nTextBanks...");    
    splitTextbanks(file);
    Message(" DONE.\nWeaponPalettes...");    
    splitWeaponPalettes(file);
    Message(" DONE.\n");    
    
    writestr(file,"\nsplit    0x0,0x0,\\0x0 - .bin\n");
    fclose(file);
    Message("END OF SPLITS.\n");    
    
}


static initFile(file){
writestr(file,"/***********************Directories***************************/\n");
writestr(file,"#dir    data/\n");
writestr(file,"#dir    data/graphics/\n");
writestr(file,"#dir    data/graphics/portraits\n");
writestr(file,"#dir    data/graphics/mapsprites\n");
writestr(file,"#dir    data/graphics/specialsprites\n");
writestr(file,"#dir    data/graphics/battles\n");
writestr(file,"#dir    data/graphics/battles/battlesprites\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/allies\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/allies/animations/\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/enemies\n");
writestr(file,"#dir    data/graphics/battles/battlesprites/enemies/animations/\n");
writestr(file,"#dir    data/graphics/battles/weapons\n");
writestr(file,"#dir    data/graphics/battles/weapons/palettes\n");
writestr(file,"#dir    data/graphics/battles/spells\n");
writestr(file,"#dir    data/graphics/battles/spells/invocations/\n");
writestr(file,"#dir    data/graphics/battles/spells/animations/\n");
writestr(file,"#dir    data/graphics/battles/backgrounds\n");
writestr(file,"#dir    data/graphics/battles/grounds\n");
writestr(file,"#dir    data/graphics/specialscreens\n");
writestr(file,"#dir    data/graphics/specialscreens/titlescreen\n");
writestr(file,"#dir    data/graphics/specialscreens/witchscreen\n");
writestr(file,"#dir    data/graphics/specialscreens/suspendscreen\n");
writestr(file,"#dir    data/graphics/specialscreens/endingkiss\n");
writestr(file,"#dir    data/graphics/specialscreens/endingjewels\n");
writestr(file,"#dir    data/graphics/maps\n");
writestr(file,"#dir    data/graphics/maps/maptilesets\n");
writestr(file,"#dir    data/graphics/maps/mappalettes\n");
writestr(file,"#dir    data/graphics/icons\n");
writestr(file,"#dir    data/graphics/tech\n");
writestr(file,"#dir    data/graphics/tech/menus\n");
writestr(file,"#dir    data/graphics/tech/fonts\n");
writestr(file,"#dir    data/graphics/tech/windowlayouts\n");
writestr(file,"#dir    data/maps/\n");
writestr(file,"#dir    data/maps/global/\n");
writestr(file,"#dir    data/maps/entries/\n");
writeMapEntries(file);
writestr(file,"#dir    data/battles/\n");
writestr(file,"#dir    data/battles/global/\n");
writestr(file,"#dir    data/battles/entries/\n");
writeBattleEntries(file);
writestr(file,"#dir    data/stats\n");
writestr(file,"#dir    data/stats/items\n");
writestr(file,"#dir    data/stats/spells\n");
writestr(file,"#dir    data/stats/allies/\n");
writestr(file,"#dir    data/stats/allies/classes\n");
writestr(file,"#dir    data/stats/allies/stats\n");
writestr(file,"#dir    data/stats/enemies/\n");
writestr(file,"#dir    data/tech/\n");
writestr(file,"#dir    data/scripting/\n");
writestr(file,"#dir    data/scripting/text\n");
writestr(file,"#dir    data/sound/\n");
writestr(file,"\n");
writestr(file,"/***********************Data***************************/\n");
writestr(file,"\n");
}

static writeBattleEntries(file){
    auto i,index;
    for(i=0;i<=44;i++){
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        writestr(file,form("#dir\tdata/battles/entries/battle%s\n",index));
    }
}

static writeMapEntries(file){
    auto i,index;
    for(i=0;i<=78;i++){
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        writestr(file,form("#dir\tdata/maps/entries/map%s\n",index));
    }
}


/*
 *  Split simple pointer tables
 */
static splitPTs(file){

    /*  Template
     *  splitPT(start, end, lastEntryDataEnd, chunkEnd, "ptName", "entryName", "binDir", 0, "binName", indexLength, align, file);
     */
    splitPT(0x6400C, 0x641D8, 0x9494A, 0x9494A, "pt_MapTilesets", "MapTileset", "data/graphics/maps/maptilesets/", 0, "maptileset", 3, 0, file);
    splitPT(0x9494A, 0x9498A, 0x94B8A, 0x94B8A, "pt_MapPalettes", "MapPalette", "data/graphics/maps/mappalettes/", 0, "mappalette", 2, 0, file);        
    //splitPT(0xC8000, 0xC8B40, 0xFFC48, 0x100000, "pt_MapSprites", "MapSprite", "data/graphics/mapsprites/", 0, "mapsprite", 3, 15, file);    
    splitPT(0x101EE0, 0x101F58, 0x12A2F8, 0x12A2F8, "pt_Backgrounds", "Background", "data/graphics/battles/backgrounds/", 0, "background", 2, 0, file);
    splitPT(0x130004, 0x1300DC, 0x17FE4F, 0x180000, "pt_EnemyBattleSprites", "EnemyBattleSprite", "data/graphics/battles/battlesprites/enemies/", 0, "enemybattlesprite", 2, 15, file);
    splitPT(0x18001C, 0x18009C, 0x1AA16E, 0x1AA16E, "pt_AllyBattleSprites", "AllyBattleSprite", "data/graphics/battles/battlesprites/allies/", 0, "allybattlesprite", 2, 0, file);
    splitPT(0x1AAC3A, 0x1AAD96, 0x1AB79E, 0x1AB79E, "pt_AlliesAnimations", "AllyAnimation", "data/graphics/battles/battlesprites/allies/animations/", 0, "allybattlespriteanimation", 3, 0, file);
    splitPT(0x1AB79E, 0x1AB982, 0x1ABE52, 0x1AC000, "pt_EnemyAnimations", "EnemyAnimation", "data/graphics/battles/battlesprites/enemies/animations/", 0, "enemybattlespriteanimation", 3, 14, file);
    splitPT(0x1AD104, 0x1AD1B8, 0x1B120A, 0x1B120A, "pt_BattleTerrainData", "BattleTerrain", "data/battles/entries/battle", 1, "/terrain", 2, 0, file);
    splitPT(0x1B30EE, 0x1B31A2, 0x1B6DB0, 0x1B6DB0, "pt_BattleSpriteSets", "BattleSpriteSet", "data/battles/entries/battle", 1, "/spriteset", 2, 0, file);
    splitPT(0x1B9A9A, 0x1B9AF6, 0x1BEE38, 0x1BEE38, "pt_WeaponSprites", "WeaponSprite", "data/graphics/battles/weapons/", 0, "weaponsprite", 2, 0, file);                    
    splitPT(0x1BEEE0, 0x1BEF3C, 0x1C46C2, 0x1C46C2, "pt_SpellGraphics", "SpellGraphics", "data/graphics/battles/spells/", 0, "spellgraphics", 2, 0, file);
    splitPT(0x1C8004, 0x1C80E4, 0x1D7E26, 0x1D8000, "pt_Portraits", "Portrait", "data/graphics/portraits/", 0, "portrait", 2, 15, file);
    //splitPT(0x1EE270, 0x1EE2F0, 0x1EE7D0, 0x1EE7D0, "pt_AllyStats", "AllyStats", "data/stats/allies/stats/", 0, "allystats", 2, 0, file);

}

static splitSingleChunks(file) {
    auto i,j,x,s,index,path;
    auto start,base,addr,end,dref,section,action;
    
    // Template : splitSingleChunk(0x,0x,"","",file);
    
    splitSingleChunk(0xB1E,0xB96,"FadingData","data/graphics/tech/fadingdata.bin",file);
    
    splitSingleChunk(0x309E,0x30BE,"plt_BasePalette","data/graphics/tech/basepalette.bin",file);    
    
    splitSingleChunk(0x31CE,0x364E,"MapOffsetHashTable","data/maps/global/mapoffsethashtable.bin",file);
    
    //splitSingleChunk(0x7186,0x71C0,"DebugModeAvailableMaps","data/maps/global/debugmodeavailablemaps.bin",file);
    
    //splitSingleChunk(0x7988,0x799C,"FlagSwitchedMaps","data/maps/global/flagswitchedmaps.bin",file);
    
    //splitSingleChunk(0x7A36,0x7B71,"BattleMapCoords","data/battles/global/battlemapcoords.bin",file);
    //splitSingleChunk(0x7B71,0x7BCA,"SavepointMapCoords","data/battles/global/savepointmapcoords.bin",file);
    //splitSingleChunk(0x7BCA,0x7BDE,"RaftResetMapCoords","data/battles/global/raftresetmapcoords.bin",file);
    
    MakeAlign(0x7FA6, 0x8000-0x7FA6,15);
    
    //splitSingleChunk(0x853A,0x855A,"ClassTypes","data/stats/allies/classes/classtypes.bin",file);
    
    //splitSingleChunk(0xACCA,0xACEA,"CriticalHitSettings","data/stats/allies/classes/criticalhitsettings.bin",file);
    
    //splitSingleChunk(0xBCF0,0xBD24,"ItemBreakMessages","data/stats/items/itembreakmessages.bin",file);
    
    //splitSingleChunk(0xBE52,0xBECC,"EnemyItemDrops","data/battles/global/enemyitemdrops.bin",file);
    //splitSingleChunk(0xBECC,0xC024,"EnemyGold","data/stats/enemies/enemygold.bin",file);
    //splitSingleChunk(0xC24E,0xC27A,"SpellElements","data/stats/spells/spellelements.bin",file);
    
    //splitSingleChunk(0xD824,0xD8F4,"MoveTypeTerrainCosts","data/battles/global/movetypeterraincosts.bin",file);
    
    //splitSingleChunk(0xF9C4,0xFAD6,"SpellNames","data/stats/spells/spellnames.bin",file);
    //splitSingleChunk(0xFAD6,0xFB8A,"AllyNames","data/stats/allies/allynames.bin",file);
    //splitSingleChunk(0xFB8A,0xFF87,"EnemyNames","data/stats/enemies/enemynames.bin",file);
    MakeAlign(0xFF87, 0x10000-0xFF87,15);
    
    splitSingleChunk(0x1098A,0x10A4A,"IconHighlightTiles","data/graphics/tech/iconhighlighttiles.bin",file);    
    
    splitSingleChunk(0x10E1C,0x10EF4,"DiamondMenuLayout","data/graphics/tech/menus/diamondmenulayout.bin",file);
    splitSingleChunk(0x10EF4,0x10FCC,"UnidentifiedLayout01","data/graphics/tech/menus/unidentifiedlayout01.bin",file);
    splitSingleChunk(0x10FCC,0x110A4,"UnidentifiedLayout02","data/graphics/tech/menus/unidentifiedlayout02.bin",file);
    
    //splitSingleChunk(0x114BE,0x11572,"BattleEquipWindowLayout","data/graphics/tech/windowlayouts/battleequipwindowlayout.bin",file);
    
    splitSingleChunk(0x1264E,0x126EE,"WindowBorderTiles","data/graphics/tech/windowbordertiles.bin",file);
    //splitSingleChunk(0x126EE,0x1278E,"PortraitWindowLayout","data/graphics/tech/windowlayouts/portraitwindowlayout.bin",file);
    //splitSingleChunk(0x1278E,0x1284E,"AllyKillDefeatWindowLayout","data/graphics/tech/windowlayouts/allykilldefeatwindowlayout.bin",file);
    //splitSingleChunk(0x1284E,0x1288E,"CharacterStatsWindowLayout","data/graphics/tech/windowlayouts/characterstatsdefeatwindowlayout.bin",file);
    
    splitSingleChunk(0x13D9E,0x13EDE,"TextHighlightTiles","data/graphics/tech/texthighlighttiles.bin",file);
    
    splitSingleChunk(0x14EFC,0x14F7C,"ShopPriceTagTiles_Blank","data/graphics/tech/shoppricetagtiles-blank.bin",file);
    splitSingleChunk(0x14F7C,0x1505C,"ShopPriceTagTiles_Numbers","data/graphics/tech/shoppricetagtiles-numbers.bin",file);
    
    splitSingleChunk(0x151D6,0x15268,"ShopInventoryItemHighlightTiles","data/graphics/tech/shopinventoryitemhighlighttiles.bin",file);
    
    //splitSingleChunk(0x15A5A,0x15BB0,"BattleConfigWindowLayout","data/graphics/tech/windowlayouts/battleconfigwindowlayout.bin",file);
    
    //splitSingleChunk(0x1607C,0x160B4,"AlphabetTopBorderWindowLayout","data/graphics/tech/windowlayouts/alphabettopborderwindowlayout.bin",file);
    //splitSingleChunk(0x160B4,0x16204,"AlphabetWindowLayout","data/graphics/tech/windowlayouts/alphabetwindowlayout.bin",file);
    //splitSingleChunk(0x16204,0x1623A,"NameEntryWindowLayout","data/graphics/tech/windowlayouts/nameentrywindowlayout.bin",file);
    splitSingleChunk(0x1623A,0x16282,"AlphabetHighlightTiles","data/graphics/tech/alphabethighlighttiles.bin",file);
    
    //splitSingleChunk(0x16618,0x16658,"TimerWindowLayout","data/graphics/tech/windowlayouts/timerwindowwindowlayout.bin",file);
    
    //splitSingleChunk(0x16A62,0x16EA6,"MemberStatsWindowLayout","data/graphics/tech/windowlayouts/memberstatswindowslayout.bin",file);
    //splitSingleChunk(0x16EA6,0x176A6,"ItemDefs","data/stats/items/itemdefs.bin",file);
    //splitSingleChunk(0x176A6,0x1796E,"SpellDefs","data/stats/spells/spelldefs.bin",file);
    //splitSingleChunk(0x1796E,0x17F3E,"ItemNames","data/stats/items/itemnames.bin",file);
    //splitSingleChunk(0x17F3E,0x17FDA,"ClassNames","data/stats/allies/classes/classnames.bin",file);
    MakeAlign(0x17FDA, 0x18000-0x17FDA,15);
    
    splitSingleChunk(0x198A8,0x198C8,"plt_BattlesceneBasePalette","data/graphics/battles/plt_battlescenebasepalette.bin",file);
    
    //splitSingleChunk(0x19E5E,0x19E6E,"TerrainBackgrounds","data/battles/global/terrainbackgrounds.bin",file);
    
    //splitSingleChunk(0x1F806,0x1F914,"AllyBattleSprites","data/stats/allies/allybattlesprites.bin",file);
    //splitSingleChunk(0x1F914,0x1F9E2,"EnemyBattleSprites","data/stats/enemies/enemybattlesprites.bin",file);
    //splitSingleChunk(0x1F9E2,0x1FA8A,"WeaponBattleSprites","data/stats/items/weaponsprites.bin",file);
    //splitSingleChunk(0x1FA8A,0x1FAB8,"CustomBackgrounds","data/battles/global/custombackgrounds.bin",file);
    
    //splitSingleChunk(0x1FAD6,0x1FADD,"AllyBSpriteIdleAnimate","data/stats/allies/allyidlesprites.bin",file);
    //splitSingleChunk(0x1FADD,0x1FAEA,"EnemyBSpriteIdleAnimate","data/stats/enemies/enemyidlesprites.bin",file);
    
    splitSingleChunk(0x1FAEA,0x1FDEA,"BackgroundLayout","data/graphics/tech/backgroundlayout.bin",file);
    
    MakeAlign(0x1FDEA, 0x20000-0x1FDEA,17);
    
    //splitSingleChunk(0x20878,0x20A02,"ShopItems","data/stats/items/shopitems.bin",file);
    splitSingleChunk(0x20981,0x20A02,"DebugShop","data/stats/items/debugshop.bin",file);
    //splitSingleChunk(0x21046,0x21072,"Promotions","data/stats/allies/promotions.bin",file);
    
    //splitSingleChunk(0x21F62,0x21F92,"MithrilWeaponClassLists","data/stats/allies/classes/mithrilweaponclasses.bin",file);
    //splitSingleChunk(0x21F92,0x21FD2,"MithrilWeaponLists","data/stats/items/mithrilweapons.bin",file);
    
    //splitSingleChunk(0x228A2,0x228A8,"SpecialCaravanDescriptions","data/stats/items/specialcaravandescriptions.bin",file);
    
    //splitSingleChunk(0x229E2,0x229EC,"UsableOutsideBattleItems","data/stats/items/usableoutsidebattleitems.bin",file);
    
    splitSingleChunk(0x23658,0x23758,"UnitCursorTiles","data/graphics/tech/unitcursortiles.bin",file);
    
    //splitSingleChunk(0x239AE,0x239C8,"ChestGoldAmounts","data/maps/global/chestgoldamounts.bin",file);
    
    splitSingleChunk(0x25DF6,0x261A6,"SpecialSprites_Taros","data/graphics/specialsprites/taros.bin",file);
    splitSingleChunk(0x261A6,0x26552,"SpecialSprites_Kraken","data/graphics/specialsprites/kraken.bin",file);
    splitSingleChunk(0x26552,0x268F2,"SpecialSprites_NazcaShip","data/graphics/specialsprites/nazcaship.bin",file);
    splitSingleChunk(0x268F2,0x26DB8,"SpecialSprites_EvilSpirit","data/graphics/specialsprites/evilspirit.bin",file);
    splitSingleChunk(0x26DB8,0x27264,"SpecialSprites_EvilSpiritAlt","data/graphics/specialsprites/evilspiritalt.bin",file);
    splitSingleChunk(0x27264,0x2784C,"SpecialSprites_Zeon","data/graphics/specialsprites/zeon.bin",file);
    
    MakeAlign(0x27D8E, 0x28000-0x27D8E,15);
    
    splitSingleChunk(0x281AA,0x2822C,"SegaLogoColors","data/graphics/tech/segalogocolors.bin",file);
    splitSingleChunk(0x2822C,0x2824C,"SegaLogoPalette","data/graphics/tech/segalogopalette.bin",file);
    splitSingleChunk(0x2824C,0x28B12,"SegaLogo","data/graphics/tech/segalogo.bin",file);
    
    //splitSingleChunk(0x28FBC,0x28FCC,"InputSequence_ConfigurationMode","data/tech/configurationmodeinputsequence.bin",file);
    //splitSingleChunk(0x28FF0,0x29002,"InputSequence_DebugMode","data/tech/debugmodeinputsequence.bin",file);
    
    splitSingleChunk(0x29002,0x29A02,"VariableWidthFont","data/graphics/tech/fonts/variablewidthfont.bin",file);
    
    splitSingleChunk(0x29A02,0x2A9C2,"MenuTiles_Uncompressed","data/graphics/tech/menus/mainmenutiles.bin",file);
    splitSingleChunk(0x2A9C2,0x2ACF6,"MenuTiles_Item","data/graphics/tech/menus/menutilesitem.bin",file);
    splitSingleChunk(0x2ACF6,0x2B072,"MenuTiles_BattleField","data/graphics/tech/menus/menutilesbattlefield.bin",file);
    splitSingleChunk(0x2B072,0x2B418,"MenuTiles_Church","data/graphics/tech/menus/menutileschurch.bin",file);
    splitSingleChunk(0x2B418,0x2B7C0,"MenuTiles_Shop","data/graphics/tech/menus/menutilesshop.bin",file);
    splitSingleChunk(0x2B7C0,0x2BAE8,"MenuTiles_Caravan","data/graphics/tech/menus/menutilescaravan.bin",file);
    splitSingleChunk(0x2BAE8,0x2BE2C,"MenuTiles_Depot","data/graphics/tech/menus/menutilesdepot.bin",file);
    splitSingleChunk(0x2BE2C,0x2C01E,"MenuTiles_YesNo","data/graphics/tech/menus/menutilesyesno.bin",file);
    splitSingleChunk(0x2C01E,0x2C03E,"plt_WitchChoice","data/graphics/specialscreens/witchscreen/witchchoicepalette.bin",file);
    splitSingleChunk(0x2C03E,0x2C3FE,"WitchBubbleAnimation","data/graphics/specialscreens/witchscreen/witchbubbleanimation.bin",file);
    splitSingleChunk(0x2C3FE,0x2C576,"SpeechBalloonTiles","data/graphics/specialscreens/witchscreen/speechballoontiles.bin",file);
    
    splitSingleChunk(0x2C7A0,0x2DDDE,"UnusedCloudTiles","data/graphics/tech/unusedcloudtiles.bin",file);
    splitSingleChunk(0x2DDDE,0x2E08E,"StaticWidthFont","data/graphics/tech/fonts/staticwidthfont.bin",file);
    splitSingleChunk(0x2E08E,0x2E10E,"TitleScreenPalettes","data/graphics/specialscreens/titlescreen/titlescreenpalettes.bin",file);
    
    splitSingleChunk(0x2E196,0x2E394,"TextBankTreeOffsets","data/scripting/text/huffmantreeoffsets.bin",file);
    splitSingleChunk(0x2E394,0x2EB34,"TextBankTreeData","data/scripting/text/huffmantrees.bin",file);
    
    splitSingleChunk(0x4201E,0x425ED,"GameStaff","data/scripting/gamestaff.bin",file);
    MakeAlign(0x425ED, 0x44000-0x425ED,14);
    
    //splitSingleChunk(0x4428A,0x44298,"OverworldMaps","data/maps/global/overworldmaps.bin",file);
    //splitSingleChunk(0x44338,0x4433C,"OverworldFollowers","data/overworldfollowers.bin",file);
    //splitSingleChunk(0x4433C,0x4438A,"Followers","data/followers.bin",file);
    
    //splitSingleChunk(0x44A5E,0x44A7C,"AllySprites","data/stats/allies/allyspriteids.bin",file);
    //splitSingleChunk(0x44AA4,0x44B4A,"EnemySprites","data/stats/enemies/enemyspriteids.bin",file);
    
    //splitSingleChunk(0x4567A,0x45858,"SpriteDialogProperties","data/spritedialogdefs.bin",file);
    
    //splitSingleChunk(0x47C8E,0x47CBC,"EnemyLeaderPresence","data/battles/global/enemyleaderpresence.bin",file);
    
    MakeAlign(0x6348C, 0x64000-0x6348C,14);
    
    splitSingleChunk(0x1002BE,0x10033E,"plt_TitleScreen","data/graphics/specialscreens/titlescreen/titlepalettes.bin",file);
    splitSingleChunk(0x10033E,0x1014E0,"TitleScreenTiles","data/graphics/specialscreens/titlescreen/titletiles.bin",file);
    splitSingleChunk(0x1014E0,0x101BE0,"TitleScreenLayoutA","data/graphics/specialscreens/titlescreen/titlelayoutA.bin",file);
    splitSingleChunk(0x101BE0,0x101EE0,"TitleScreenLayoutB","data/graphics/specialscreens/titlescreen/titlelayoutB.bin",file);

    splitSingleChunk(0x12A308,0x12CD26,"InvocationSpriteDao","data/graphics/battles/spells/invocations/dao.bin",file);
    splitSingleChunk(0x12CD26,0x12D9CA,"InvocationSpriteApollo","data/graphics/battles/spells/invocations/apollo.bin",file);
    splitSingleChunk(0x12D9CA,0x12E988,"InvocationSpriteNeptun","data/graphics/battles/spells/invocations/neptun.bin",file);
    splitSingleChunk(0x12E988,0x12FADE,"InvocationSpriteAtlas","data/graphics/battles/spells/invocations/atlas.bin",file);
    MakeAlign(0x12FADE, 0x130000-0x12FADE,15);
    
    splitSingleChunk(0x1AA16E,0x1AA316,"StatusAnimationTiles","data/graphics/tech/statusanimationtiles.bin",file);
    splitSingleChunk(0x1AA31E,0x1AA5FA,"BattlesceneTransitionTilesA","data/graphics/tech/battlescenetransitiontilesa.bin",file);
    splitSingleChunk(0x1AA5FA,0x1AA8CA,"BattlesceneTransitionTilesB","data/graphics/tech/battlescenetransitiontilesb.bin",file);
    splitSingleChunk(0x1AA8CA,0x1AAA82,"BoltAnimData_A","data/graphics/battles/spells/animations/boltanimdataa.bin",file);
    splitSingleChunk(0x1AAA82,0x1AAC3A,"BoltAnimData_B","data/graphics/battles/spells/animations/boltanimdatab.bin",file);        
    
    //splitSingleChunk(0x1B1A66,0x1B30EE,"EnemyData","data/stats/enemies/enemydata.bin",file);
    
    //splitSingleChunk(0x1B6DB0,0x1B6DBC,"SpecialBattles","data/battles/global/specialbattles.bin",file);    
    
    splitSingleChunk(0x1B6DDA,0x1B6DFA,"plt_EndKiss","data/graphics/specialscreens/endingkiss/endingkisspalette.bin",file);
    splitSingleChunk(0x1B6DFA,0x1B7C9A,"EndKissPicture","data/graphics/specialscreens/endingkiss/endingkisstiles.bin",file);
    MakeAlign(0x1B7C9A, 0x1B8000-0x1B7C9A,14);

    //splitSingleChunk(0x1BEE38,0x1BEEE0,"plt_WeaponPalettes","data/graphics/battles/weapons/weaponpalettes.bin",file);

    splitSingleChunk(0x1C46C2,0x1C4702,"plt_Witch","data/graphics/specialscreens/witchscreen/witchpalette.bin",file);
    splitSingleChunk(0x1C4702,0x1C4E88,"WitchLayout","data/graphics/specialscreens/witchscreen/witchlayout.bin",file);
    splitSingleChunk(0x1C4E88,0x1C67C4,"WitchTiles","data/graphics/specialscreens/witchscreen/witchtiles.bin",file);
    splitSingleChunk(0x1C67C4,0x1C67E4,"plt_WitchEnd","data/graphics/specialscreens/witchscreen/endingwitchpalette.bin",file);
    splitSingleChunk(0x1C67E4,0x1C6F2C,"WitchEndLayout","data/graphics/specialscreens/witchscreen/endingwitchlayout.bin",file);
    splitSingleChunk(0x1C6F2C,0x1C7F7C,"WitchEndTiles","data/graphics/specialscreens/witchscreen/endingwitchtiles.bin",file);
    MakeAlign(0x1C7F7C, 0x1C8000-0x1C7F7C,15);    

    splitSingleChunk(0x1D8004,0x1DFA46,"IconTiles","data/graphics/icons/icons.bin",file);
    MakeAlign(0x1DFA46, 0x1E0000-0x1DFA46,15);    

    splitSingleChunk(0x1E0000,0x1E8000,"","data/sound/pcmbank0.bin",file);
    splitSingleChunk(0x1E8000,0x1EB000,"","data/sound/pcmbank1.bin",file);
    splitSingleChunk(0x1EB000,0x1EC000,"","data/sound/yminst.bin",file);
    splitSingleChunkWithCommentedSplitEntry(0x1EC000,0x1EE000,"SoundDriver","data/sound/sounddriver.bin",file);
    
    //splitSingleChunk(0x1EE02C,0x1EE270,"StatGrowthCurves","data/stats/allies/growthcurves.bin",file);
    
    //splitSingleChunk(0x1EE7D0, 0x1EE890, "AllyStartData","data/stats/allies/allystartdata.bin",file);
    //splitSingleChunk(0x1EE890, 0x1EE930, "ClassData","data/stats/allies/classes/classdata.bin",file);
    splitSingleChunk(0x1EE930, 0x1EF102, "JewelsEndScreenLayout","data/graphics/specialscreens/endingjewels/endingjewelslayout.bin",file);
    splitSingleChunk(0x1EF102, 0x1EF142, "plt_JewelsEndScreen","data/graphics/specialscreens/endingjewels/endingjewelspalette.bin",file);
    splitSingleChunk(0x1EF142, 0x1EF4BA, "JewelsEndScreenTiles","data/graphics/specialscreens/endingjewels/endingjewelstiles.bin",file);
    splitSingleChunk(0x1EF4BA, 0x1EF4DA, "plt_SuspendString","data/graphics/specialscreens/suspendscreen/suspendstringpalette.bin",file);
    splitSingleChunk(0x1EF4DA, 0x1EF5A6, "SuspendStringTiles","data/graphics/specialscreens/suspendscreen/suspendstringtiles.bin",file);
    splitSingleChunk(0x1EF5A6, 0x1EF5E6, "unused_BasePalettes","data/graphics/tech/unusedbasepalettes.bin",file);
    splitSingleChunk(0x1EF5E6, 0x1EFE33, "BaseTiles","data/graphics/tech/basetiles.bin",file);
    MakeAlign(0x1EFE33, 0x1F0000-0x1EFE33,15);
    splitSingleChunk(0x1F0000, 0x1F8000, "","data/sound/musicbank1.bin",file);
    splitSingleChunk(0x1F8000, 0x200000, "","data/sound/musicbank0.bin",file);

}

static splitSingleChunk(start, end, nameString, binPath, splitFile){
    splitSingleChunkWithConditionalIncbin(start, end, nameString, binPath, splitFile, 0);
}

static splitSingleChunkWithConditionalIncbin(start, end, nameString, binPath, splitFile, incbinType){
    auto j,incbin;
    //Message("Cleaning from %a to %a ...\n",start,end);
    for(j=start+1;j<end;j++){undefineByte(j);}
    MakeData(start,FF_BYTE,end-start,1);
    if(nameString!=""){
        MakeNameEx(start,nameString,0);
    }
    if(incbinType==1){
        incbin = "incbinIfVanillaRom";
    }else{
        incbin = "incbin";
    }
    SetManualInsn   (start, form("%s \"%s\"",incbin,binPath));
    writestr(splitFile,form("#split\t0x%s,0x%s,%s\n",ltoa(start,16),ltoa(end,16),binPath));
    //Jump(start);
}

static splitSingleChunkWithCommentedSplitEntry(start, end, nameString, binPath, splitFile){
    auto j;
    //Message("Cleaning from %a to %a ...\n",start,end);
    for(j=start+1;j<end;j++){undefineByte(j);}
    MakeData(start,FF_BYTE,end-start,1);
    MakeNameEx(start,nameString,0);
    SetManualInsn   (start, form("incbin \"%s\"",binPath));
    writestr(splitFile,form("/*#split\t0x%s,0x%s,%s*/\n",ltoa(start,16),ltoa(end,16),binPath));
    //Jump(start);
}


/*
 *  Split one simple pointer table
 */
static splitPT(start, end, lastEntryDataEnd, chunkEnd, ptName, entryName, binDir, entryDirs, binName, indexLength, align, file) {
    auto i,j,x,s,index,path;
    auto addr,dataEnd,from,dref,section,action;
    auto binDirIndex,binNameIndex;
    i = 0;
    addr = start;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        MakeNameExC(dref,form("%s%s",entryName,index),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    // Put align instruction for padding until chunkEnd
    if(align!=0)MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,align);
}


static splitMapsprites(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,binDirIndex,binNameIndex,ptName,binDir,entryDirs,binName,indexLength,align,entryName;
    auto facingId;
    i = 0;
    start = 0xC8000;
    end = 0xC8B40;
    addr = start;
    lastEntryDataEnd = 0xFFC48;
    chunkEnd = 0x100000;
    ptName = "pt_MapSprites";
    entryName = "MapSprite";
    binDir = "data/graphics/mapsprites/";
    entryDirs = 0;
    binName = "mapsprite";
    indexLength = 3;
    align = 15;
    action=1;
    // Cleaning whole chunk
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    // Naming pointer table
    MakeNameEx(addr,ptName,0);
    // Prepare whole chunk with new names and Data XRefs
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i/3,10);
        facingId = i%3;
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        MakeNameExC(dref,form("%s%s_%d",entryName,index,facingId),0);
        addr=addr+4;
        i++;
    }
    /*
     *  Each entry is delimited by its address and the next DATA XRef coming from current chunk
     *  It can then be made into data and replaced by an incbin manual instruction.
     */
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        // Finding entry's data end
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i/3,10);
        facingId = i%3;
        while(strlen(index)<indexLength){
            index=form("0%s",index);
        }
        index = form("%s-%d",index,facingId);
        //Message(form("Processing entry %s%s from %s, to %s\n",entryName,index,ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        if(strstr(GetDisasm(dref),"incbin")==-1){    
            if(entryDirs==0){
                binDirIndex = "";
                binNameIndex = index;
            } else{
                binDirIndex = index;
                binNameIndex = "";
            }
            SetManualInsn   (dref, form("incbin \"%s%s%s%s.bin\"",binDir,binDirIndex,binName,binNameIndex));
            writestr(file,form("#split\t0x%s,0x%s,%s%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binDirIndex,binName,binNameIndex));
        }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    // Put align instruction for padding until chunkEnd
    if(align!=0)MakeAlign(lastEntryDataEnd,chunkEnd-lastEntryDataEnd,align);
}

static splitMaps(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action,sectionNamesForFiles,sectionNamesForLabels,currentSectionName;
    i = 0;
    start = 0x94B8A;
    end = 0x94CC6;
    addr = start;
    lastEntryDataEnd = 0xC7ECC;
    chunkEnd = 0xC8000;
    action=1;
    sectionNamesForFiles="0=blocks;1=layout;2=areas;3=flag-events;4=step-events;5=roof-events;6=warp-events;7=chest-items;8=other-items;9=animations;10";
    sectionNamesForLabels="0=Blocks;1=Layout;2=Areas;3=FlagEvents;4=StepEvents;5=RoofEvents;6=WarpEvents;7=ChestItems;8=OtherItems;9=Animations;10";
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);    
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    MakeNameEx(addr,"pt_MapData",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        MakeNameEx(dref,form("Map%s",index),0);
        //writestr(file,form("#dir\tdata/maps/entries/map%s\n",index));
                MakeData(dref,FF_BYTE,0x6,0);
                /*if(strstr(GetDisasm(dref),"incbin")==-1){    
                    SetManualInsn(dref, form("incbin \"data/maps/entries/map%s/00-tilesets.bin\"",index));
                    writestr(file,form("#split\t0x%s,0x%s,data/maps/entries/map%s/00-tilesets.bin\n",ltoa(dref,16),ltoa(dref+6,16),index));
                }    */    
                //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\00-tilesets.asm\",0x%s,0x%s,\"\");",index,ltoa(dref,16),ltoa(dref+6,16)));
        for(s=0;s!=10;s++){
            from = dref+6+4*s;
            MakeDword(from);
            section = Dword(from);
            add_dref(from,section,dr_O);
            currentSectionName = substr(sectionNamesForLabels,strstr(sectionNamesForLabels,form("%d",s))+2,strstr(sectionNamesForLabels,form("%d",s+1))-1);
            MakeNameExC(section,form("Map%ss%d_%s",index,s,currentSectionName),0);
        } 
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\00-tilesets.asm\",0x%s,0x%s,\"\");",index,ltoa(dref,16),ltoa(dref+6,16)));
        //Message(form("\nproduceAsmSection(file,0x%s,0x%s);",ltoa(dref+6,16),ltoa(dref+6+10*4,16)));
        for(s=0;s!=10;s++){
            section = Dfirst(dref+6+4*s);
            if(section!=BADADDR){
                dataEnd = 0;
                j = section+1;
                while(dataEnd==0){
                    from = DfirstB(j);
                    while(from!=BADADDR){
                        if(from>=start&&from<chunkEnd){
                            dataEnd = j;
                        }
                  from=DnextB(addr,from);      
                    }
                    j++;
                    if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
                }
                currentSectionName = substr(sectionNamesForFiles,strstr(sectionNamesForFiles,form("%d",s))+2,strstr(sectionNamesForFiles,form("%d",s+1))-1);
                //Message(form("Processing Map%s section%d at %s, dataEnd %s\n",index,s,ltoa(section,16),ltoa(dataEnd,16)));
                MakeData(section,FF_BYTE,dataEnd-section,1);
                if(strstr(GetDisasm(section),"incbin")==-1){    
                    if(s<2){
                        SetManualInsn(section, form("incbin \"data/maps/entries/map%s/%s-%s.bin\"",index,ltoa(s,10),currentSectionName));
                        writestr(file,form("#split\t0x%s,0x%s,data/maps/entries/map%s/%s-%s.bin\n",ltoa(section,16),ltoa(dataEnd,16),index,ltoa(s,10),currentSectionName));
                        //Message(form("\nproduceAsmSection(file,0x%s,0x%s);",ltoa(section,16),ltoa(dataEnd,16)));
                    }else{
                        SetManualInsn(section, "");
                        //Message(form("\nproduceAsmScript(file,\"data\\\\maps\\\\entries\\\\map%s\\\\%s-%s.asm\",0x%s,0x%s,\"\");",index,ltoa(s,10),currentSectionName,ltoa(section,16),ltoa(dataEnd,16)));
                    }
                }
            }
        }
        //Message("\n");
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    MakeAlign(lastEntryDataEnd, chunkEnd-lastEntryDataEnd,15);
}


static splitGrounds(file) {

    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,base,dataEnd,from,dref,section,action;
    i = 0;
    start = 0x1B8028;
    end = 0x1B80A0;
    addr = start;
    lastEntryDataEnd = 0x1B9A9A;
    chunkEnd = 0x1B9A9A;
    action=1;
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);    
    for(j=start;j<chunkEnd;j++){undefineByte(j);}
    MakeNameExC(addr,"pt_Grounds",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        if(strstr(GetTrueName(dref),"Ground")==-1){
            index = ltoa(i,10);
            if(strlen(index)==1)index=form("0%s",index);
            MakeNameExC(dref,form("Ground%s",index),0);
            /*MakeData(dref, FF_WORD, 0x2, 0);
            MakeData(dref+2, FF_WORD, 0x2, 0);
            MakeData(dref+4, FF_WORD, 0x2, 0);*/
            splitSingleChunk(dref, dref+6, "", form("data/graphics/battles/grounds/groundpalette%s.bin",index),file);        
            MakeData(dref+6, FF_WORD, 0x2, 0);
            MakeNameExC(dref+6,form("bsg%s_rpbase",index),0);
            base = dref+6;
            OpOffEx(base, -1, REF_OFF32, -1, base, 0);
            section = Word(base) + base;
            add_dref(base,section,dr_O);
            //Message("base %a, section %a\n",base, section);
            MakeNameExC(section,form("GroundTiles%s",index),0);        
        }
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);
        base = dref+6;
        dref = Word(base) + base;    
        //Jump(dref); 
                dataEnd = 0;
                j = dref+1;
                while(dataEnd==0){
                    from = DfirstB(j);
                    while(from!=BADADDR){
                        if(from>=start&&from<chunkEnd){
                            dataEnd = j;
                        }
                  from=DnextB(addr,from);      
                    }
                    j++;
                    if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
                }
                index = ltoa(i,10);
                if(strlen(index)==1)index=form("0%s",index);
                //Message(form("Processing ground%s at %s, dataEnd %s\n",index,ltoa(dref,16),ltoa(dataEnd,16)));
                MakeData(dref,FF_BYTE,dataEnd-dref,1);
                if(strstr(GetDisasm(dref),"incbin")==-1){
                    SetManualInsn   (dref, form("incbin \"data/graphics/battles/grounds/groundtiles%s.bin\"",index));
                    writestr(file,form("#split\t0x%s,0x%s,data/graphics/battles/grounds/groundtiles%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
                }
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }

}

static splitTextbanks(file) {
    auto i,j,x,s,index,path;
    auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action;
    i = 0;
    start = 0x41FDA;
    end = 0x4201E;
    addr = start;
    lastEntryDataEnd = 0x41FD9;
    chunkEnd = 0x4201E;
    action=1;
    //Message("Cleaning from %a to %a ...\n",start,chunkEnd);        
    for(j=0x2EB34;j<chunkEnd;j++){undefineByte(j);}
    MakeNameEx(addr,"pt_TextBanks",0);
    while(addr<end&&action==1){
        MakeDword(addr);
        dref = Dword(addr);
        add_dref(addr,dref,dr_O);
        dref = Dfirst(addr);        
        //Jump(dref);
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        MakeNameEx(dref,form("TextBank%s",index),0);
        addr=addr+4;
        i++;
    }
    i = 0;
    addr = start;
    while(addr!=end&&action==1){
        dref = Dfirst(addr);        
        //Jump(dref); 
        dataEnd = 0;
        j = dref+1;
        while(dataEnd==0){
            from = DfirstB(j);
            while(from!=BADADDR){
                if(from>=start&&from<chunkEnd){
                    dataEnd = j;
                }
          from=DnextB(addr,from);      
            }
            j++;
            if(j==lastEntryDataEnd) dataEnd = lastEntryDataEnd;
        }
        index = ltoa(i,10);
        if(strlen(index)==1)index=form("0%s",index);
        //Message(form("dref %s, dataEnd %s\n",ltoa(dref,16),ltoa(dataEnd,16)));
        MakeData(dref,FF_BYTE,dataEnd-dref,1);
        SetManualInsn   (dref, form("incbin \"data/scripting/text/textbank%s.bin\"",index));
        writestr(file,form("#split\t0x%s,0x%s,data/scripting/text/textbank%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
        addr=addr+4;
        i++;
        //action = AskYN(1,"Ok ?");
    }
    MakeAlign(0x41FD9, 0x41FDA-0x41FD9,1);
}


//splitSingleChunk(0x1BEE38,0x1BEEE0,"plt_WeaponPalettes","data/graphics/battles/weapons/weaponpalettes.bin",file);

static splitWeaponPalettes(file) {

    auto i,j,x,s,index;
    auto start,end,addr,base;
    i = 0;
    start = 0x1BEE38;
    end = 0x1BEEE0;
    addr = start;  
    for(j=start;j<end;j++){undefineByte(j);}
    while(addr<end){
        MakeData(addr,FF_BYTE,4,1);
        index = ltoa(i,10);
        while(strlen(index)<2){index=form("0%s",index);}
        MakeNameEx(addr,form("WeaponPalette%s",index),0);
        SetManualInsn(addr, form("incbin \"data/graphics/battles/weapons/palettes/weaponpalette%s.bin\"",index));
        writestr(file,form("#split\t0x%s,0x%s,data/graphics/battles/weapons/palettes/weaponpalette%s.bin\n",ltoa(addr,16),ltoa(addr+4,16),index));
        addr=addr+4;
        i++;
    }

}


static MakeNameExC(addr,name,flags){

    auto current;
    current = GetTrueName(addr);
    if(current=="" || strstr(current,"unk_")!=-1 || strstr(current,"byte_")!=-1 || strstr(current,"word_")!=-1 || strstr(current,"dword_")!=-1 || strstr(current,"off_")!=-1){
        MakeNameEx(addr,name,flags);
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
            //Message(form("Removed Code XRrf at addr %a, from %a\n",addr, from));
      DelCodeXref(from,addr,1);
      from=RnextB(addr,from);      
        }                
        MakeUnkn(addr,DOUNK_DELNAMES);
        MakeNameEx(addr,"",0);
        SetManualInsn(addr,"");
}




