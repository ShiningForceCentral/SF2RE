

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
	Message(" DONE.\nMaps ...");
	splitMaps(file);
	Message(" DONE.\nGrounds...");	
	splitGrounds(file);
	Message(" DONE.\nTextBanks...");	
	splitScriptbanks(file);
	Message(" DONE.\n");	
	
	writestr(file,"\nsplit	0x0,0x0,\\0x0 - .bin\n");
	fclose(file);
	Message("END OF SPLITS.\n");	
	
}


static initFile(file){
writestr(file,"/***********************Directories***************************/\n");
writestr(file,"#dir	graphics/\n");
writestr(file,"#dir	graphics/portraits\n");
writestr(file,"#dir	graphics/mapsprites\n");
writestr(file,"#dir	graphics/specialsprites\n");
writestr(file,"#dir	graphics/battlesprites\n");
writestr(file,"#dir	graphics/battlesprites/allies\n");
writestr(file,"#dir	graphics/battlesprites/allies/animations/\n");
writestr(file,"#dir	graphics/battlesprites/enemies\n");
writestr(file,"#dir	graphics/battlesprites/enemies/animations/\n");
writestr(file,"#dir	graphics/weapons\n");
writestr(file,"#dir	graphics/spells\n");
writestr(file,"#dir	graphics/spells/invocations/\n");
writestr(file,"#dir	graphics/spells/animations/\n");
writestr(file,"#dir	graphics/backgrounds\n");
writestr(file,"#dir	graphics/grounds\n");
writestr(file,"#dir	graphics/specialscreens\n");
writestr(file,"#dir	graphics/maptilesets\n");
writestr(file,"#dir	graphics/icons\n");
writestr(file,"#dir	graphics/menus\n");
writestr(file,"#dir	graphics/fonts\n");
writestr(file,"#dir	graphics/palettes\n");
writestr(file,"#dir	maps/\n");
writestr(file,"#dir	maps/mapentries/\n");
writestr(file,"#dir	maps/spritesets/\n");
writestr(file,"#dir	battles/\n");
writestr(file,"#dir	battles/terrains/\n");
writestr(file,"#dir	battles/spritesets/\n");
writestr(file,"#dir	data/\n");
writestr(file,"#dir	data/classes\n");
writestr(file,"#dir	data/items\n");
writestr(file,"#dir	data/spells\n");
writestr(file,"#dir	data/allystats\n");
writestr(file,"#dir	scripting/\n");
writestr(file,"#dir	scripting/textbanks\n");
writestr(file,"#dir	scripting/dialogs\n");
writestr(file,"#dir	scripting/mapspritescripts\n");
writestr(file,"#dir	sound/\n");
writestr(file,"#dir	sound/driver\n");
writestr(file,"#dir	sound/pcm\n");
writestr(file,"#dir	sound/music\n");
writestr(file,"#dir	sound/instruments\n");
writestr(file,"#dir	sound/sfx\n");
writestr(file,"\n");
writestr(file,"/***********************Data***************************/\n");
writestr(file,"\n");
}


/*
 *	Split simple pointer tables
 */
static splitPTs(file){

	/*	Template
	 *	splitPT(start, end, lastEntryDataEnd, chunkEnd, "ptName", "entryName", "binDir", "binName", indexLength, align, file);
	 */
	splitPT(0x6400C, 0x641D8, 0x9494A, 0x9494A, "pt_MapTilesets", "MapTileset", "graphics/maptilesets/", "maptileset", 3, 0, file);
	splitPT(0x9494A, 0x9498A, 0x94B8A, 0x94B8A, "pt_MapPalettes", "MapPalette", "graphics/palettes/", "mappalette", 2, 0, file);		
	splitPT(0xC8000, 0xC8B40, 0xFFC48, 0x100000, "pt_MapSprites", "MapSprite", "graphics/mapsprites/", "mapsprite", 3, 15, file);	
	splitPT(0x101EE0, 0x101F58, 0x12A2F8, 0x12A2F8, "pt_Backgrounds", "Background", "graphics/backgrounds/", "background", 2, 0, file);
	splitPT(0x130004, 0x1300DC, 0x17FE4F, 0x180000, "pt_EnemyBattleSprites", "EnemyBattleSprite", "graphics/battlesprites/enemies/", "enemybattlesprite", 2, 15, file);
	splitPT(0x18001C, 0x18009C, 0x1AA16E, 0x1AA16E, "pt_AllyBattleSprites", "AllyBattleSprite", "graphics/battlesprites/allies/", "allybattlesprite", 2, 0, file);
	splitPT(0x1AAC3A, 0x1AAD96, 0x1AB79E, 0x1AB79E, "pt_AlliesAnimations", "AllyAnimation", "graphics/battlesprites/allies/animations/", "allybattlespriteanimation", 3, 0, file);
	splitPT(0x1AB79E, 0x1AB982, 0x1ABE52, 0x1AC000, "pt_EnemyAnimations", "EnemyAnimation", "graphics/battlesprites/allies/animations/", "enemybattlespriteanimation", 3, 14, file);
	splitPT(0x1AD104, 0x1AD1B8, 0x1B120A, 0x1B120A, "pt_BattleTerrainData", "BattleTerrain", "battles/terrains/", "battleterrain", 2, 0, file);
	splitPT(0x1B30EE, 0x1B31A2, 0x1B6DB0, 0x1B6DB0, "pt_BattleSpriteSets", "BattleSpriteSet", "battles/spritesets/", "battlespriteset", 2, 0, file);
	splitPT(0x1B9A9A, 0x1B9AF6, 0x1BEE38, 0x1BEE38, "pt_WeaponSprites", "WeaponSprite", "graphics/weapons/", "weaponsprite", 2, 0, file);					
	splitPT(0x1BEEE0, 0x1BEF3C, 0x1C46C2, 0x1C46C2, "pt_SpellGraphics", "SpellGraphics", "graphics/spells/", "spellgraphics", 2, 0, file);
	splitPT(0x1C8004, 0x1C80E4, 0x1D7E26, 0x1D8000, "pt_Portraits", "Portrait", "graphics/portraits/", "portrait", 2, 15, file);
	splitPT(0x1EE270, 0x1EE2F0, 0x1EE7D0, 0x1EE7D0, "pt_AllyStats", "AllyStats", "data/allystats/", "allystats", 2, 0, file);

}

static splitSingleChunks(file) {
	auto i,j,x,s,index,path;
	auto start,base,addr,end,dref,section,action;
	
	// Template : splitSingleChunk(0x,0x,"","",file);
	
	splitSingleChunk(0x7A36,0x7B71,"BattleMapCoords","battles/battlemapcoords.bin",file);
	
	MakeAlign(0x7FA6, 0x8000-0x7FA6,15);
	
	splitSingleChunk(0xBE52,0xBECC,"tbl_EnemyItemDrops","battles/enemyitemdrops.bin",file);
	splitSingleChunk(0xBECC,0xC024,"tbl_EnemyGold","battles/enemygold.bin",file);
	
	splitSingleChunk(0xC24E,0xC27A,"tbl_SpellElements","data/spellelements.bin",file);
	
	splitSingleChunk(0xD824,0xD8F4,"t_MoveTypeTerrainCosts","data/movetypeterraincosts.bin",file);
	
	splitSingleChunk(0xF9C4,0xFAD6,"SpellNames","data/spells/spellnames.bin",file);
	splitSingleChunk(0xFAD6,0xFB8A,"AllyNames","data/allynames.bin",file);
	splitSingleChunk(0xFB8A,0xFF87,"EnemyNames","data/enemynames.bin",file);
	MakeAlign(0xFF87, 0x10000-0xFF87,15);
	
	splitSingleChunk(0x16EA6,0x176A6,"ItemDefs","data/itemdefs.bin",file);
	splitSingleChunk(0x176A6,0x1796E,"SpellDefs","data/spelldefs.bin",file);
	splitSingleChunk(0x1796E,0x17F3E,"ItemNames","data/items/itemnames.bin",file);
	splitSingleChunk(0x17F3E,0x17FDA,"ClassNames","data/classes/classnames.bin",file);
	MakeAlign(0x17FDA, 0x18000-0x17FDA,15);
	
	splitSingleChunk(0x1F806,0x1F914,"tbl_AllyBattleSprites","data/allybattlesprites.bin",file);
	splitSingleChunk(0x1F914,0x1F9E2,"tbl_EnemyBattleSprites","data/enemybattlesprites.bin",file);
	splitSingleChunk(0x1F9E2,0x1FA8A,"tbl_WeaponBattleSprites","data/weaponsprites.bin",file);
	splitSingleChunk(0x1FA8A,0x1FAB8,"tbl_CustomBackgrounds","data/custombackgrounds.bin",file);
	
	splitSingleChunk(0x1FAD6,0x1FADD,"tbl_AllyBSpriteIdleAnimate","data/allyidlesprites.bin",file);
	splitSingleChunk(0x1FADD,0x1FAEA,"tbl_EnemyBSpriteIdleAnimate","data/enemyidlesprites.bin",file);
	
	MakeAlign(0x1FDEC, 0x20000-0x1FDEC,15);
	
	splitSingleChunk(0x21046,0x21072,"Promotions","data/promotions.bin",file);
	
	splitSingleChunk(0x21F62,0x21F92,"tbl_MithrilWeaponClassLists","data/mithrilweaponclasses.bin",file);
	splitSingleChunk(0x21F92,0x21FD2,"tbl_MithrilWeaponLists","data/mithrilweapons.bin",file);
	
	splitSingleChunk(0x25DF6,0x261A6,"specialSprites_Taros","graphics/specialsprites/taros.bin",file);
	splitSingleChunk(0x261A6,0x26552,"specialSprites_Kraken","graphics/specialsprites/kraken.bin",file);
	splitSingleChunk(0x26552,0x268F2,"specialSprites_NazcaShip","graphics/specialsprites/nazcaship.bin",file);
	splitSingleChunk(0x268F2,0x26DB8,"specialSprites_EvilSpirit","graphics/specialsprites/evilspirit.bin",file);
	splitSingleChunk(0x26DB8,0x27264,"specialSprites_EvilSpiritAlt","graphics/specialsprites/evilspiritalt.bin",file);
	splitSingleChunk(0x27264,0x2784C,"specialSprites_Zeon","graphics/specialsprites/zeon.bin",file);
	
	MakeAlign(0x27D8E, 0x28000-0x27D8E,15);
	
	splitSingleChunk(0x2824C,0x28B12,"SegaLogo","graphics/segalogo.bin",file);
	
	splitSingleChunk(0x29002,0x29A02,"VariableWidthFont","graphics/fonts/variablewidthfont.bin",file);
	
	splitSingleChunk(0x29A02,0x2A9C2,"MenuTiles_Uncompressed","graphics/menus/menutiles.bin",file);
	splitSingleChunk(0x2A9C2,0x2ACF6,"MenuTiles_Item","graphics/menus/menutilesitem.bin",file);
	splitSingleChunk(0x2ACF6,0x2B072,"MenuTiles_BattleField","graphics/menus/menutilesbattlefield.bin",file);
	splitSingleChunk(0x2B072,0x2B418,"MenuTiles_Church","graphics/menus/menutileschurch.bin",file);
	splitSingleChunk(0x2B418,0x2B7C0,"MenuTiles_Shop","graphics/menus/menutilesshop.bin",file);
	splitSingleChunk(0x2B7C0,0x2BAE8,"MenuTiles_Caravan","graphics/menus/menutilescaravan.bin",file);
	splitSingleChunk(0x2BAE8,0x2BE2C,"MenuTiles_Depot","graphics/menus/menutilesdepot.bin",file);
	splitSingleChunk(0x2BE2C,0x2C01E,"MenuTiles_YesNo","graphics/menus/menutilesyesno.bin",file);
	
	splitSingleChunk(0x2C01E,0x2C03E,"plt_WitchChoice","graphics/specialscreens/whitchchoicepalette.bin",file);
	
	splitSingleChunk(0x2C3FE,0x2C576,"SpeechBalloonTiles","graphics/specialscreens/speechballoontiles.bin",file);
	
	splitSingleChunk(0x2DDDE,0x2E08E,"StaticWidthFont","graphics/fonts/staticwidthfont.bin",file);
	
	splitSingleChunk(0x2E196,0x2E394,"TextBankTreePointers","scripting/textbanks/textbanktreepointers.bin",file);
	splitSingleChunk(0x2E394,0x2EB34,"TextBankTreeData","scripting/textbanktreedata.bin",file);
	
	splitSingleChunk(0x4201E,0x425E7,"GameStaff","scripting/gamestaff.bin",file);
	MakeAlign(0x425ED, 0x44000-0x425ED,14);
	
	splitSingleChunk(0x4428A,0x44298,"OverworldMaps","maps/overworldmaps.bin",file);
	splitSingleChunk(0x44338,0x4433C,"OverworldFollowers","maps/overworldfollowoers.bin",file);
	splitSingleChunk(0x4433C,0x4438A,"Followers","maps/followers.bin",file);
	
	splitSingleChunk(0x44A5E,0x44A7C,"t_AllySprites","data/allyspriteids.bin",file);
	splitSingleChunk(0x44AA4,0x44B4A,"t_EnemySprites","data/enemyspriteids.bin",file);
	
	splitSingleChunk(0x4567A,0x45858,"tbl_SpriteToPortraitnBlip","data/spriteportraitsnblips.bin",file);
	
	splitSingleChunk(0x47C8E,0x47CBC,"EnemyLeaderPresence","battles/enemyleaderpresence.bin",file);
	
	MakeAlign(0x6348C, 0x64000-0x6348C,14);
	
	splitSingleChunk(0x1002BE,0x10033E,"plt_TitleScreen","graphics/specialscreens/titlepalettes.bin",file);
	splitSingleChunk(0x10033E,0x1014E0,"titleScreenTiles","graphics/specialscreens/titletiles.bin",file);
	splitSingleChunk(0x1014E0,0x101BE0,"titleScreenLayoutA","graphics/specialscreens/titlelayoutA.bin",file);
	splitSingleChunk(0x101BE0,0x101EE0,"titleScreenLayoutB","graphics/specialscreens/titlelayoutB.bin",file);

	splitSingleChunk(0x12A308,0x12CD26,"invocationSpriteDao","graphics/spells/invocations/dao.bin",file);
	splitSingleChunk(0x12CD26,0x12D9CA,"invocationSpriteApollo","graphics/spells/invocations/apollo.bin",file);
	splitSingleChunk(0x12D9CA,0x12E988,"invocationSpriteNeptun","graphics/spells/invocations/neptun.bin",file);
	splitSingleChunk(0x12E988,0x12FADE,"invocationSpriteAtlas","graphics/spells/invocations/atlas.bin",file);
	MakeAlign(0x12FADE, 0x130000-0x12FADE,15);
	
	splitSingleChunk(0x1AA16E,0x1AA316,"statusAnimationTiles","graphics/statusanimationtiles.bin",file);
	splitSingleChunk(0x1AA31E,0x1AA5FA,"battlesceneTransitionTilesA","graphics/battlescenetransitiontilesa.bin",file);
	splitSingleChunk(0x1AA5FA,0x1AA8CA,"battlesceneTransitionTilesB","graphics/battlescenetransitiontilesb.bin",file);
	splitSingleChunk(0x1AA8CA,0x1AAA82,"BoltAnimData_A","graphics/spells/animations/boltanimdataa.bin",file);
	splitSingleChunk(0x1AAA82,0x1AAC3A,"BoltAnimData_B","graphics/spells/animations/boltanimdatab.bin",file);		
	
	splitSingleChunk(0x1B1A66,0x1B30EE,"EnemyData","battles/enemydata.bin",file);
	
	splitSingleChunk(0x1B6DB0,0x1B6DBC,"SpecialBattles","battles/specialbattles.bin",file);	
	
	splitSingleChunk(0x1B6DDA,0x1B6DFA,"plt_endKiss","graphics/specialscreens/endingkisspalette.bin",file);
	splitSingleChunk(0x1B6DFA,0x1B7C9A,"endKissPicture","graphics/specialscreens/endingkisstiles.bin",file);
	MakeAlign(0x1B7C9A, 0x1B8000-0x1B7C9A,14);

	splitSingleChunk(0x1BEE38,0x1BEEE0,"plt_WeaponPalettes","graphics/weapons/weaponspalettes.bin",file);

	splitSingleChunk(0x1C46C2,0x1C4702,"plt_Witch","graphics/specialscreens/witchpalette.bin",file);
	splitSingleChunk(0x1C4702,0x1C4E88,"witchLayout","graphics/specialscreens/witchlayout.bin",file);
	splitSingleChunk(0x1C4E88,0x1C67C4,"witchTiles","graphics/specialscreens/witchtiles.bin",file);
	splitSingleChunk(0x1C67C4,0x1C67E4,"plt_WitchEnd","graphics/specialscreens/endingwitchpalette.bin",file);
	splitSingleChunk(0x1C67E4,0x1C6F2C,"witchEndLayout","graphics/specialscreens/endingwitchlayout.bin",file);
	splitSingleChunk(0x1C6F2C,0x1C7F7C,"witchEndTiles","graphics/specialscreens/endingwitchtiles.bin",file);
	MakeAlign(0x1C7F7C, 0x1C8000-0x1C7F7C,15);	

	splitSingleChunk(0x1D8004,0x1DFA46,"Icons","graphics/icons/icons.bin",file);
	MakeAlign(0x1DFA46, 0x1E0000-0x1DFA46,15);	

	splitSingleChunk(0x1E0000,0x1E8000,"","sound/pcmbank0.bin",file);
	splitSingleChunk(0x1E8000,0x1EB000,"","sound/pcmbank1.bin",file);
	splitSingleChunk(0x1EB000,0x1EC000,"","sound/yminst.bin",file);
	splitSingleChunkWithCommentedSplitEntry(0x1EC000,0x1EE000,"Z80_SoundDriver","sound/driver.bin",file);
	
	splitSingleChunk(0x1EE02C,0x1EE270,"StatGrowthCurves","data/growthcurves.bin",file);
	
	splitSingleChunk(0x1EE7D0, 0x1EE890, "AllyStartData","data/allystartdata.bin",file);
	splitSingleChunk(0x1EE890, 0x1EE930, "ClassData","data/classes/classdata.bin",file);
	splitSingleChunk(0x1EE930, 0x1EF102, "JewelsEndScreenLayout","graphics/specialscreens/endingjewelslayout.bin",file);
	splitSingleChunk(0x1EF102, 0x1EF142, "plt_JewelsEndScreen","graphics/specialscreens/endingjewelspalette.bin",file);
	splitSingleChunk(0x1EF142, 0x1EF4BA, "JewelsEndScreenTiles","graphics/specialscreens/endingjewelstiles.bin",file);
	splitSingleChunk(0x1EF4BA, 0x1EF4DA, "plt_SuspendString","graphics/specialscreens/suspendstringpalette.bin",file);
	splitSingleChunk(0x1EF4DA, 0x1EF5A6, "SuspendStringTiles","graphics/specialscreens/suspendstringtiles.bin",file);
	splitSingleChunk(0x1EF5E6, 0x1EFE33, "baseTiles","graphics/basetiles.bin",file);
	MakeAlign(0x1EFE33, 0x1F0000-0x1EFE33,15);
	splitSingleChunk(0x1F0000, 0x1F8000, "","sound/musicbank1.bin",file);
	splitSingleChunk(0x1F8000, 0x200000, "","sound/musicbank0.bin",file);

}

static splitSingleChunk(start, end, nameString, binPath, splitFile){
	auto j;
	//Message("Cleaning from %a to %a ...\n",start,end);
	for(j=start+1;j<end;j++){undefineByte(j);}
	MakeData(start,FF_BYTE,end-start,1);
	if(nameString!=""){
		MakeNameEx(start,nameString,0);
	}
	SetManualInsn   (start, form("incbin \"%s\"",binPath));
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
 *	Split one simple pointer table
 */
static splitPT(start, end, lastEntryDataEnd, chunkEnd, ptName, entryName, binDir, binName, indexLength, align, file) {
	auto i,j,x,s,index,path;
	auto addr,dataEnd,from,dref,section,action;
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
	 *	Each entry is delimited by its address and the next DATA XRef coming from current chunk
	 *	It can then be made into data and replaced by an incbin manual instruction.
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
			SetManualInsn   (dref, form("incbin \"%s%s%s.bin\"",binDir,binName,index));
			writestr(file,form("#split\t0x%s,0x%s,%s%s%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),binDir,binName,index));
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
	auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action;
	i = 0;
	start = 0x94B8A;
	end = 0x94CC6;
	addr = start;
	lastEntryDataEnd = 0xC7ECC;
	chunkEnd = 0xC8000;
	action=1;
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
		writestr(file,form("#dir\tmaps/mapentries/map%s\n",index));
		MakeData(dref, FF_BYTE, 0x1, 0);
		MakeData(dref+1, FF_BYTE, 0x1, 0);
		MakeData(dref+2, FF_BYTE, 0x1, 0);
		MakeData(dref+3, FF_BYTE, 0x1, 0);
		MakeData(dref+4, FF_BYTE, 0x1, 0);
		MakeData(dref+5, FF_BYTE, 0x1, 0);
		for(s=0;s!=10;s++){
			from = dref+6+4*s;
			MakeDword(from);
			section = Dword(from);
			add_dref(from,section,dr_O);
			MakeNameExC(section,form("Map%sSection%d",index,s),0);
		} 
		addr=addr+4;
		i++;
	}
	i = 0;
	addr = start;
	while(addr!=end&&action==1){
		dref = Dfirst(addr);		
		//Jump(dref); 
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
				index = ltoa(i,10);
				if(strlen(index)==1)index=form("0%s",index);
				//Message(form("Processing Map%s section%d at %s, dataEnd %s\n",index,s,ltoa(section,16),ltoa(dataEnd,16)));
				MakeData(section,FF_BYTE,dataEnd-section,1);
				if(strstr(GetDisasm(dref),"incbin")==-1){						
					SetManualInsn   (section, form("incbin \"maps/mapentries/map%s/section%d.bin\"",index,s));
					writestr(file,form("#split\t0x%s,0x%s,maps/mapentries/map%s/section%d.bin\n",ltoa(section,16),ltoa(dataEnd,16),index,s));
				}
			}
		}
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
			splitSingleChunk(dref, dref+6, "", form("graphics/grounds/ground%s_palette.bin",index),file);		
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
					SetManualInsn   (dref, form("incbin \"graphics/grounds/groundtiles%s.bin\"",index));
					writestr(file,form("#split\t0x%s,0x%s,graphics/grounds/groundtiles%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
				}
		addr=addr+4;
		i++;
		//action = AskYN(1,"Ok ?");
	}

}

static splitScriptbanks(file) {
	auto i,j,x,s,index,path;
	auto start,end,lastEntryDataEnd,chunkEnd,addr,dataEnd,from,dref,section,action;
	i = 0;
	start = 0x41FDA;
	end = 0x4201E;
	addr = start;
	lastEntryDataEnd = 0x41FDA;
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
		SetManualInsn   (dref, form("incbin \"scripting/textbanks/scriptbank%s.bin\"",index));
		writestr(file,form("#split\t0x%s,0x%s,scripting/textbanks/scriptbank%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
		addr=addr+4;
		i++;
		//action = AskYN(1,"Ok ?");
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
 *	Makes sure byte at addr is
 *	clean for new formatting
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




