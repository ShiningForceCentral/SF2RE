

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
	Message(" DONE.\nBattleSceneGrounds...");	
	splitBattleSceneGrounds(file);
	Message(" DONE.\nScriptBanks...");	
	splitScriptbanks(file);
	Message(" DONE.\n");	
	
	writestr(file,"\nsplit	0x0,0x0,\\0x0 - .bin\n");
	fclose(file);
	Message("END OF SPLITS.\n");	
	
}

/*
 *	Split simple pointer tables
 */
static splitPTs(file){

	/*	Template
	 *	splitPT(start, end, lastEntryDataEnd, chunkEnd, "ptName", "entryName", "binDir", "binName", indexLength, align, file);
	 */
	splitPT(0x6400C, 0x641D8, 0x9494A, 0x9494A, "pt_MapTiles", "MapTiles", "maps/tilesets/", "tileset", 3, 0, file);
	splitPT(0x9494A, 0x9498A, 0x94B8A, 0x94B8A, "pt_MapPalettes", "MapPalette", "maps/palettes/", "mappalette", 2, 0, file);		
	splitPT(0xC8000, 0xC8B40, 0xFFC48, 0x100000, "pt_EntitySprites", "EntitySprite", "sprites/entities/", "entitysprite", 3, 15, file);	
	splitPT(0x101EE0, 0x101F58, 0x12A2F8, 0x12A2F8, "pt_Backgrounds", "Background", "backgrounds/", "background", 2, 0, file);
	splitPT(0x130004, 0x1300DC, 0x17FE4F, 0x180000, "pt_EnemyBattleSprites", "EnemyBattleSprite", "sprites/battlesprites/enemies/", "enemybattlesprite", 2, 15, file);
	splitPT(0x18001C, 0x18009C, 0x1AA16E, 0x1AA16E, "pt_AllyBattleSprites", "AllyBattleSprite", "sprites/battlesprites/allies/", "allybattlesprite", 2, 0, file);
	splitPT(0x1AAC3A, 0x1AAD96, 0x1AB79E, 0x1AB79E, "pt_AlliesAnimations", "AllyAnimation", "battles/animations/allies/", "allyanimation", 3, 0, file);
	splitPT(0x1AB79E, 0x1AB982, 0x1ABE52, 0x1AC000, "pt_EnemyAnimations", "EnemyAnimation", "battles/animations/enemies/", "enemyanimation", 3, 14, file);
	splitPT(0x1AD104, 0x1AD1B8, 0x1B120A, 0x1B120A, "pt_BattleTerrainData", "BattleTerrain", "battles/terrains/", "battleterrain", 2, 0, file);
	splitPT(0x1B30EE, 0x1B31A2, 0x1B6DB0, 0x1B6DB0, "pt_BattleEntities", "BattleEntitySetup", "battles/entitysetups/", "battleentitysetup", 2, 0, file);
	splitPT(0x1B9A9A, 0x1B9AF6, 0x1BEE38, 0x1BEE38, "pt_WeaponSprites", "WeaponSprite", "sprites/weapons/", "weaponsprite", 2, 0, file);					
	splitPT(0x1BEEE0, 0x1BEF3C, 0x1C46C2, 0x1C46C2, "pt_SpellGraphics", "SpellGraphics", "spells/", "spellgraphics", 2, 0, file);
	splitPT(0x1C8004, 0x1C80E4, 0x1D7E26, 0x1D8000, "pt_Portraits", "Portrait", "portraits/", "portrait", 2, 15, file);

}

static splitSingleChunks(file) {
	auto i,j,x,s,index,path;
	auto start,base,addr,end,dref,section,action;
	
	// Template : splitSingleChunk(0x,0x,"","",file);
	
	splitSingleChunk(0x7A36,0x7B71,"BattleMapCoords","battles/battlemapcoords.bin",file);
	
	MakeAlign(0x7FA6, 0x8000-0x7FA6,15);
	
	splitSingleChunk(0xBE52,0xBECC,"tbl_EnemyItemDrops","battles/enemyitemdrops.bin",file);
	splitSingleChunk(0xBECC,0xC024,"tbl_EnemyGold","battles/enemygold.bin",file);
	
	splitSingleChunk(0xC24E,0xC27A,"tbl_SpellElements","spells/spellelements.bin",file);
	
	splitSingleChunk(0xD824,0xD8F4,"t_MoveTypeTerrainCosts","battles/movetypeterraincosts.bin",file);
	
	splitSingleChunk(0xF9C4,0xFAD6,"SpellNames","spells/spellnames.bin",file);
	splitSingleChunk(0xFAD6,0xFB8A,"AllyNames","chardata/allynames.bin",file);
	splitSingleChunk(0xFB8A,0xFF87,"EnemyNames","chardata/enemynames.bin",file);
	MakeAlign(0xFF87, 0x10000-0xFF87,15);
	
	splitSingleChunk(0x16EA6,0x176A6,"ItemDefs","misc/itemdefs.bin",file);
	splitSingleChunk(0x176A6,0x1796E,"SpellDefs","spells/spelldefs.bin",file);
	splitSingleChunk(0x1796E,0x17F3E,"ItemNames","misc/itemnames.bin",file);
	splitSingleChunk(0x17F3E,0x17FDA,"ClassNames","chardata/classnames.bin",file);
	MakeAlign(0x17FDA, 0x18000-0x17FDA,15);
	
	splitSingleChunk(0x1F806,0x1F914,"tbl_CharacterBattleSprites","sprites/charbattlesprites.bin",file);
	splitSingleChunk(0x1F914,0x1F9E2,"tbl_MonsterBattleSprites","sprites/enemybattlesprites.bin",file);
	splitSingleChunk(0x1F9E2,0x1FA8A,"tbl_ItemBattleSprites","sprites/weaponsprites.bin",file);
	splitSingleChunk(0x1FA8A,0x1FAB8,"tbl_CustomBackgrounds","backgrounds/custombackgrounds.bin",file);
	
	splitSingleChunk(0x1FAD6,0x1FADD,"tbl_AllyBSpriteIdleAnimate","sprites/battlesprites/allyidlesprites.bin",file);
	splitSingleChunk(0x1FADD,0x1FAEA,"tbl_EnemyBSpriteIdleAnimate","sprites/battlesprites/enemyidlesprites.bin",file);
	
	MakeAlign(0x1FDEC, 0x20000-0x1FDEC,15);
	
	splitSingleChunk(0x21046,0x21072,"promotion_data","chardata/promotions.bin",file);
	
	splitSingleChunk(0x21F62,0x21F92,"tbl_MithrilWeaponClassLists","chardata/mithrilweaponclasses.bin",file);
	splitSingleChunk(0x21F92,0x21FD2,"tbl_MithrilWeaponLists","chardata/mithrilweapons.bin",file);
	
	splitSingleChunk(0x25DF6,0x261A6,"specialSprites_Taros","sprites/specialsprites/taros.bin",file);
	splitSingleChunk(0x261A6,0x26552,"specialSprites_Kraken","sprites/specialsprites/kraken.bin",file);
	splitSingleChunk(0x26552,0x268F2,"specialSprites_NazcaShip","sprites/specialsprites/nazcaship.bin",file);
	splitSingleChunk(0x268F2,0x26DB8,"specialSprites_EvilSpirit","sprites/specialsprites/evilspirit.bin",file);
	splitSingleChunk(0x26DB8,0x27264,"specialSprites_EvilSpiritAlt","sprites/specialsprites/evilspiritalt.bin",file);
	splitSingleChunk(0x27264,0x2784C,"specialSprites_Zeon","sprites/specialsprites/zeon.bin",file);
	
	MakeAlign(0x27D8E, 0x28000-0x27D8E,15);
	
	splitSingleChunk(0x2824C,0x28B12,"SegaLogo","misc/segalogo.bin",file);
	
	splitSingleChunk(0x29002,0x29A02,"VariableWidthFont","misc/variablewidthfont.bin",file);
	
	splitSingleChunk(0x29A02,0x2A9C2,"MenuTiles_Uncompressed","misc/menutiles.bin",file);
	splitSingleChunk(0x2A9C2,0x2ACF6,"MenuTiles_Item","misc/menutilesitem.bin",file);
	splitSingleChunk(0x2ACF6,0x2B072,"MenuTiles_BattleField","misc/menutilesbattlefield.bin",file);
	splitSingleChunk(0x2B072,0x2B418,"MenuTiles_Church","misc/menutileschurch.bin",file);
	splitSingleChunk(0x2B418,0x2B7C0,"MenuTiles_Shop","misc/menutilesshop.bin",file);
	splitSingleChunk(0x2B7C0,0x2BAE8,"MenuTiles_Caravan","misc/menutilescaravan.bin",file);
	splitSingleChunk(0x2BAE8,0x2BE2C,"MenuTiles_Depot","misc/menutilesdepot.bin",file);
	splitSingleChunk(0x2BE2C,0x2C01E,"MenuTiles_YesNo","misc/menutilesyesno.bin",file);
	
	splitSingleChunk(0x2C01E,0x2C03E,"plt_WitchChoice","misc/specialscreens/whitchchoicepalette.bin",file);
	
	splitSingleChunk(0x2C3FE,0x2C576,"SpeechBalloonTiles","misc/specialscreens/speechballoontiles.bin",file);
	
	splitSingleChunk(0x2DDDE,0x2E08E,"StaticWidthFont","misc/staticwidthfont.bin",file);
	
	splitSingleChunk(0x2E196,0x2EB34,"t_RelativeTreePointers","scriptbanks/scriptbanktrees.bin",file);
	
	splitSingleChunk(0x4201E,0x425E7,"GameStaff","misc/gamestaff.bin",file);
	MakeAlign(0x425ED, 0x44000-0x425ED,14);
	
	splitSingleChunk(0x4428A,0x44298,"OverworldMaps","maps/overworldmaps.bin",file);
	splitSingleChunk(0x44338,0x4433C,"OverworldFollowers","misc/overworldfollowoers.bin",file);
	splitSingleChunk(0x4433C,0x4438A,"Followers","misc/followers.bin",file);
	
	splitSingleChunk(0x44A5E,0x44A7C,"t_AllySprites","chardata/allyspriteids.bin",file);
	splitSingleChunk(0x44AA4,0x44B4A,"t_MonsterSprites","chardata/enemyspriteids.bin",file);
	
	splitSingleChunk(0x4567A,0x45858,"tbl_SpriteToPortraitnBlip","chardata/spriteportraitsnblips.bin",file);
	
	splitSingleChunk(0x47C8E,0x47CBC,"EnemyLeaderPresence","battles/enemyleaderpresence.bin",file);
	
	MakeAlign(0x6348C, 0x64000-0x6348C,14);
	
	splitSingleChunk(0x1002BE,0x10033E,"plt_TitleScreen","misc/specialscreens/titlepalettes.bin",file);
	splitSingleChunk(0x10033E,0x1014E0,"titleScreenTiles","misc/specialscreens/titletiles.bin",file);
	splitSingleChunk(0x1014E0,0x101BE0,"titleScreenLayoutA","misc/specialscreens/titlelayoutA.bin",file);
	splitSingleChunk(0x101BE0,0x101EE0,"titleScreenLayoutB","misc/specialscreens/titlelayoutB.bin",file);

	splitSingleChunk(0x12A308,0x12CD26,"invocationSpriteDao","battles/animations/invocations/dao.bin",file);
	splitSingleChunk(0x12CD26,0x12D9CA,"invocationSpriteApollo","battles/animations/invocations/apollo.bin",file);
	splitSingleChunk(0x12D9CA,0x12E988,"invocationSpriteNeptun","battles/animations/invocations/neptun.bin",file);
	splitSingleChunk(0x12E988,0x12FADE,"invocationSpriteAtlas","battles/animations/invocations/atlas.bin",file);
	MakeAlign(0x12FADE, 0x130000-0x12FADE,15);
	
	splitSingleChunk(0x1AA16E,0x1AA316,"statusAnimationTiles","misc/statusanimationtiles.bin",file);
	splitSingleChunk(0x1AA31E,0x1AA5FA,"battlesceneTransitionTilesA","misc/battlescenetransitiontilesa.bin",file);
	splitSingleChunk(0x1AA5FA,0x1AA8CA,"battlesceneTransitionTilesB","misc/battlescenetransitiontilesb.bin",file);
	splitSingleChunk(0x1AA8CA,0x1AAA82,"BoltAnimData_A","spells/boltanimdataa.bin",file);
	splitSingleChunk(0x1AAA82,0x1AAC3A,"BoltAnimData_B","spells/boltanimdatab.bin",file);		
	
	splitSingleChunk(0x1B1A66,0x1B30EE,"EnemyData","battles/enemydata.bin",file);
	
	splitSingleChunk(0x1B6DB0,0x1B6DBC,"SpecialBattles","battles/specialbattles.bin",file);	
	
	splitSingleChunk(0x1B6DDA,0x1B6DFA,"plt_endKiss","misc/specialscreens/endingkisspalette.bin",file);
	splitSingleChunk(0x1B6DFA,0x1B7C9A,"endKissPicture","misc/specialscreens/endingkisstiles.bin",file);
	MakeAlign(0x1B7C9A, 0x1B8000-0x1B7C9A,14);

	splitSingleChunk(0x1BEE38,0x1BEEE0,"plt_BattleSceneWeaponColors","sprites/weapons/weaponspalette.bin",file);

	splitSingleChunk(0x1C46C2,0x1C4702,"plt_Witch","misc/specialscreens/witchpalette.bin",file);
	splitSingleChunk(0x1C4702,0x1C4E88,"witchLayout","misc/specialscreens/witchlayout.bin",file);
	splitSingleChunk(0x1C4E88,0x1C67C4,"witchTiles","misc/specialscreens/witchtiles.bin",file);
	splitSingleChunk(0x1C67C4,0x1C67E4,"plt_WitchEnd","misc/specialscreens/endingwitchpalette.bin",file);
	splitSingleChunk(0x1C67E4,0x1C6F2C,"witchEndLayout","misc/specialscreens/endingwitchlayout.bin",file);
	splitSingleChunk(0x1C6F2C,0x1C7F7C,"witchEndTiles","misc/specialscreens/endingwitchtiles.bin",file);
	MakeAlign(0x1C7F7C, 0x1C8000-0x1C7F7C,15);	

	splitSingleChunk(0x1D8004,0x1DFA46,"Icons","icons/icons.bin",file);
	MakeAlign(0x1DFA46, 0x1E0000-0x1DFA46,15);	

	splitSingleChunk(0x1E0000,0x1E8000,"","sound/pcm/bank0.bin",file);
	splitSingleChunk(0x1E8000,0x1EB000,"","sound/pcm/bank1.bin",file);
	splitSingleChunk(0x1EB000,0x1EC000,"","sound/yminst.bin",file);
	splitSingleChunkWithCommentedSplitEntry(0x1EC000,0x1EE000,"Z80_SoundDriver","sound/driver/cube.bin",file);
	
	splitSingleChunk(0x1EE02C,0x1EE270,"StatGrowthCurves","chardata/growthcurves.bin",file);
	
	splitSingleChunk(0x1EE2F0, 0x1EE31C, "stats_Bowie", "chardata/stats/bowie.bin",file);
	splitSingleChunk(0x1EE31C, 0x1EE36B, "stats_Sarah", "chardata/stats/sarah.bin",file);
	splitSingleChunk(0x1EE36B, 0x1EE39E, "stats_Chester","chardata/stats/chester.bin",file);
	splitSingleChunk(0x1EE39E, 0x1EE3D1, "stats_Jaha", "chardata/stats/jaha.bin",file);
	splitSingleChunk(0x1EE3D1, 0x1EE426, "stats_Kazin", "chardata/stats/kazin.bin",file);
	splitSingleChunk(0x1EE426, 0x1EE454, "stats_Slade", "chardata/stats/slade.bin",file);
	splitSingleChunk(0x1EE454, 0x1EE476, "stats_Kiwi", "chardata/stats/kiwi.bin",file);
	splitSingleChunk(0x1EE476, 0x1EE498, "stats_Peter", "chardata/stats/peter.bin",file);
	splitSingleChunk(0x1EE498, 0x1EE4BA, "stats_May", "chardata/stats/may.bin",file);
	splitSingleChunk(0x1EE4BA, 0x1EE4DC, "stats_Gerhalt","chardata/stats/gerhalt.bin",file);
	splitSingleChunk(0x1EE4DC, 0x1EE4FE, "stats_Luke","chardata/stats/luke.bin",file);
	splitSingleChunk(0x1EE4FE, 0x1EE50F, "stats_Rohde", "chardata/stats/rohde.bin",file);
	splitSingleChunk(0x1EE50F, 0x1EE542, "stats_Rick", "chardata/stats/rick.bin",file);
	splitSingleChunk(0x1EE542, 0x1EE575, "stats_Elric", "chardata/stats/elric.bin",file);
	splitSingleChunk(0x1EE575, 0x1EE5A8, "stats_Eric", "chardata/stats/eric.bin",file);
	splitSingleChunk(0x1EE5A8, 0x1EE5F5, "stats_Karna", "chardata/stats/karna.bin",file);
	splitSingleChunk(0x1EE5F5, 0x1EE628, "stats_Randolf","chardata/stats/randolf.bin",file);
	splitSingleChunk(0x1EE628, 0x1EE685, "stats_Tyrin", "chardata/stats/tyrin.bin",file);
	splitSingleChunk(0x1EE685, 0x1EE6B8, "stats_Janet", "chardata/stats/janet.bin",file);
	splitSingleChunk(0x1EE6B8, 0x1EE6C9, "stats_Higins","chardata/stats/higins.bin",file);
	splitSingleChunk(0x1EE6C9, 0x1EE6DA, "stats_Skreech","chardata/stats/skreech.bin",file);
	splitSingleChunk(0x1EE6DA, 0x1EE6FB, "stats_Taya", "chardata/stats/taya.bin",file);
	splitSingleChunk(0x1EE6FB, 0x1EE726, "stats_Frayja","chardata/stats/frayja.bin",file);
	splitSingleChunk(0x1EE726, 0x1EE737, "stats_Jaro", "chardata/stats/jaro.bin",file);
	splitSingleChunk(0x1EE737, 0x1EE748, "stats_Gyan", "chardata/stats/gyan.bin",file);
	splitSingleChunk(0x1EE748, 0x1EE771, "stats_Sheela","chardata/stats/sheela.bin",file);
	splitSingleChunk(0x1EE771, 0x1EE782, "stats_Zynk", "chardata/stats/zynk.bin",file);
	splitSingleChunk(0x1EE782, 0x1EE7AD, "stats_Chaz", "chardata/stats/chaz.bin",file);
	splitSingleChunk(0x1EE7AD, 0x1EE7BE, "stats_Lemon", "chardata/stats/lemon.bin",file);
	splitSingleChunk(0x1EE7BE, 0x1EE7D0, "stats_Claude","chardata/stats/claude.bin",file);
	
	splitSingleChunk(0x1EE7D0, 0x1EE890, "CharacterStartData","chardata/startdata.bin",file);
	splitSingleChunk(0x1EE890, 0x1EE930, "ClassData","chardata/classdata.bin",file);
	splitSingleChunk(0x1EE930, 0x1EF102, "JewelsEndScreenLayout","misc/specialscreens/endingjewelslayout.bin",file);
	splitSingleChunk(0x1EF102, 0x1EF142, "plt_JewelsEndScreen","misc/specialscreens/endingjewelspalette.bin",file);
	splitSingleChunk(0x1EF142, 0x1EF4BA, "JewelsEndScreenTiles","misc/specialscreens/endingjewelstiles.bin",file);
	splitSingleChunk(0x1EF4BA, 0x1EF4DA, "plt_SuspendString","misc/specialscreens/suspendstringpalette.bin",file);
	splitSingleChunk(0x1EF4DA, 0x1EF5A6, "SuspendStringTiles","misc/specialscreens/suspendstringtiles.bin",file);
	splitSingleChunk(0x1EF5E6, 0x1EFE33, "baseTiles","misc/basetiles.bin",file);
	MakeAlign(0x1EFE33, 0x1F0000-0x1EFE33,15);
	splitSingleChunk(0x1F0000, 0x1F8000, "","sound/music/bank1.bin",file);
	splitSingleChunk(0x1F8000, 0x200000, "","sound/music/bank0.bin",file);

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
		writestr(file,form("#dir\tmaps/map%s\n",index));
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
					SetManualInsn   (section, form("incbin \"maps/map%s/section%d.bin\"",index,s));
					writestr(file,form("#split\t0x%s,0x%s,maps/map%s/section%d.bin\n",ltoa(section,16),ltoa(dataEnd,16),index,s));
				}
			}
		}
		addr=addr+4;
		i++;
		//action = AskYN(1,"Ok ?");
	}
	MakeAlign(lastEntryDataEnd, chunkEnd-lastEntryDataEnd,15);
}


static splitBattleSceneGrounds(file) {

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
	MakeNameExC(addr,"pt_BattleSceneGrounds",0);
	while(addr<end&&action==1){
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);		
		//Jump(dref);
		if(strstr(GetTrueName(dref),"battlesceneGround")==-1){
			index = ltoa(i,10);
			if(strlen(index)==1)index=form("0%s",index);
			MakeNameExC(dref,form("battlesceneGround%s",index),0);
			/*MakeData(dref, FF_WORD, 0x2, 0);
			MakeData(dref+2, FF_WORD, 0x2, 0);
			MakeData(dref+4, FF_WORD, 0x2, 0);*/
			splitSingleChunk(dref, dref+6, "", form("battles/grounds/ground%s_palette.bin",index),file);		
			MakeData(dref+6, FF_WORD, 0x2, 0);
			MakeNameExC(dref+6,form("bsg%s_rpbase",index),0);
			base = dref+6;
			OpOffEx(base, -1, REF_OFF32, -1, base, 0);
			section = Word(base) + base;
			add_dref(base,section,dr_O);
			//Message("base %a, section %a\n",base, section);
			MakeNameExC(section,form("groundTiles%s",index),0);		
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
					SetManualInsn   (dref, form("incbin \"battles/grounds/ground%s.bin\"",index));
					writestr(file,form("#split\t0x%s,0x%s,battles/grounds/ground%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
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
	MakeNameEx(addr,"pt_ScriptBanks",0);
	while(addr<end&&action==1){
		MakeDword(addr);
		dref = Dword(addr);
		add_dref(addr,dref,dr_O);
		dref = Dfirst(addr);		
		//Jump(dref);
		index = ltoa(i,10);
		if(strlen(index)==1)index=form("0%s",index);
		MakeNameEx(dref,form("ScriptBank%s",index),0);
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
		SetManualInsn   (dref, form("incbin \"scriptbanks/scriptbank%s.bin\"",index));
		writestr(file,form("#split\t0x%s,0x%s,scriptbanks/scriptbank%s.bin\n",ltoa(dref,16),ltoa(dataEnd,16),index));
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



static initFile(file){
writestr(file,"/***********************Directories***************************/\n");
writestr(file,"#dir	sound/\n");
writestr(file,"#dir	sound/driver\n");
writestr(file,"#dir	sound/pcm\n");
writestr(file,"#dir	sound/music\n");
writestr(file,"#dir	scriptbanks/\n");
writestr(file,"#dir	battles/\n");
writestr(file,"#dir	battles/entitysetups/\n");
writestr(file,"#dir	battles/terrains/\n");
writestr(file,"#dir	battles/animations/\n");
writestr(file,"#dir	battles/animations/enemies/\n");
writestr(file,"#dir	battles/animations/allies/\n");
writestr(file,"#dir	battles/animations/invocations/\n");
writestr(file,"#dir	battles/grounds/\n");
writestr(file,"#dir	maps/\n");
writestr(file,"#dir	maps/tilesets/\n");
writestr(file,"#dir	maps/palettes/\n");
writestr(file,"#dir	sprites/\n");
writestr(file,"#dir	sprites/entities/\n");
writestr(file,"#dir	backgrounds/\n");
writestr(file,"#dir	sprites/battlesprites/\n");
writestr(file,"#dir	sprites/battlesprites/enemies/\n");
writestr(file,"#dir	sprites/battlesprites/allies/\n");
writestr(file,"#dir	sprites/specialsprites/\n");
writestr(file,"#dir	sprites/weapons/\n");
writestr(file,"#dir	spells/\n");
writestr(file,"#dir	portraits/\n");
writestr(file,"#dir	icons/\n");
writestr(file,"#dir	misc/\n");
writestr(file,"#dir	misc/specialscreens/\n");
writestr(file,"#dir	chardata/\n");
writestr(file,"#dir	chardata/stats/\n");
writestr(file,"\n");
writestr(file,"/***********************Data***************************/\n");
writestr(file,"\n");
}
