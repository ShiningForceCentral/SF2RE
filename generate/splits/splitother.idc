#include <idc.idc>
static main(void) {

	auto i,j,x,s,index,path;
	auto start,base,addr,end,dref,section,action,file;

	file = fopen("splitother.txt","w");
	
	// Template : split(0x,0x,"","",file);
	
	MakeAlign(0x6348C, 0x64000-0x6348C,14);
	
	split(0x1002BE,0x10033E,"plt_TitleScreen","misc/specialscreens/titlepalettes.bin",file);
	split(0x10033E,0x1014E0,"titleScreenTiles","misc/specialscreens/titletiles.bin",file);
	split(0x1014E0,0x101BE0,"titleScreenLayoutA","misc/specialscreens/titlelayoutA.bin",file);
	split(0x101BE0,0x101EE0,"titleScreenLayoutB","misc/specialscreens/titlelayoutB.bin",file);

	split(0x12A308,0x12CD26,"invocationSpriteDao","battles/animations/invocations/dao.bin",file);
	split(0x12CD26,0x12D9CA,"invocationSpriteApollo","battles/animations/invocations/apollo.bin",file);
	split(0x12D9CA,0x12E988,"invocationSpriteNeptun","battles/animations/invocations/neptun.bin",file);
	split(0x12E988,0x12FADE,"invocationSpriteAtlas","battles/animations/invocations/atlas.bin",file);
	MakeAlign(0x12FADE, 0x130000-0x12FADE,15);
	
	split(0x1B6DDA,0x1B6DFA,"plt_endKiss","misc/specialscreens/endingkisspalette.bin",file);
	split(0x1B6DFA,0x1B7C9A,"endKissPicture","misc/specialscreens/endingkisstiles.bin",file);
	MakeAlign(0x1B7C9A, 0x1B8000-0x1B7C9A,14);

	
	split(0x1BEE38,0x1BEEE0,"plt_BattleSceneWeaponColors","sprites/weapons/weaponspalette.bin",file);

	split(0x1C46C2,0x1C4702,"plt_Witch","misc/specialscreens/witchpalette.bin",file);
	split(0x1C4702,0x1C4E88,"witchLayout","misc/specialscreens/witchlayout.bin",file);
	split(0x1C4E88,0x1C67C4,"witchTiles","misc/specialscreens/witchtiles.bin",file);
	split(0x1C67C4,0x1C67E4,"plt_WitchEnd","misc/specialscreens/endingwitchpalette.bin",file);
	split(0x1C67E4,0x1C6F2C,"witchEndLayout","misc/specialscreens/endingwitchlayout.bin",file);
	split(0x1C6F2C,0x1C7F7C,"witchEndTiles","misc/specialscreens/endingwitchtiles.bin",file);
	MakeAlign(0x1C7F7C, 0x1C8000-0x1C7F7C,15);	


	split(0x1D8004,0x1DFA46,"Icons","icons/icons.bin",file);
	MakeAlign(0x1DFA46, 0x1E0000-0x1DFA46,15);	

	split(0x1E0000,0x1E8000,"","sound/pcm/bank0.bin",file);
	split(0x1E8000,0x1EB000,"","sound/pcm/bank1.bin",file);
	split(0x1EB000,0x1EC000,"","sound/yminst.bin",file);
	split(0x1EC000,0x1EE000,"Z80_SoundDriver","sound/driver/cube.bin",file);
	
	split(0x1EE02C,0x1EE270,"StatGrowthCurves","chardata/growthcurves.bin",file);
	
	split(0x1EE2F0, 0x1EE31C, "stats_Bowie", "chardata/stats/bowie.bin",file);
	split(0x1EE31C, 0x1EE36B, "stats_Sarah", "chardata/stats/sarah.bin",file);
	split(0x1EE36B, 0x1EE39E, "stats_Chester","chardata/stats/chester.bin",file);
	split(0x1EE39E, 0x1EE3D1, "stats_Jaha", "chardata/stats/jaha.bin",file);
	split(0x1EE3D1, 0x1EE426, "stats_Kazin", "chardata/stats/kazin.bin",file);
	split(0x1EE426, 0x1EE454, "stats_Slade", "chardata/stats/slade.bin",file);
	split(0x1EE454, 0x1EE476, "stats_Kiwi", "chardata/stats/kiwi.bin",file);
	split(0x1EE476, 0x1EE498, "stats_Peter", "chardata/stats/peter.bin",file);
	split(0x1EE498, 0x1EE4BA, "stats_May", "chardata/stats/may.bin",file);
	split(0x1EE4BA, 0x1EE4DC, "stats_Gerhalt","chardata/stats/gerhalt.bin",file);
	split(0x1EE4DC, 0x1EE4FE, "stats_Luke","chardata/stats/luke.bin",file);
	split(0x1EE4FE, 0x1EE50F, "stats_Rohde", "chardata/stats/rohde.bin",file);
	split(0x1EE50F, 0x1EE542, "stats_Rick", "chardata/stats/rick.bin",file);
	split(0x1EE542, 0x1EE575, "stats_Elric", "chardata/stats/elric.bin",file);
	split(0x1EE575, 0x1EE5A8, "stats_Eric", "chardata/stats/eric.bin",file);
	split(0x1EE5A8, 0x1EE5F5, "stats_Karna", "chardata/stats/karna.bin",file);
	split(0x1EE5F5, 0x1EE628, "stats_Randolf","chardata/stats/randolf.bin",file);
	split(0x1EE628, 0x1EE685, "stats_Tyrin", "chardata/stats/tyrin.bin",file);
	split(0x1EE685, 0x1EE6B8, "stats_Janet", "chardata/stats/janet.bin",file);
	split(0x1EE6B8, 0x1EE6C9, "stats_Higins","chardata/stats/higins.bin",file);
	split(0x1EE6C9, 0x1EE6DA, "stats_Skreech","chardata/stats/skreech.bin",file);
	split(0x1EE6DA, 0x1EE6FB, "stats_Taya", "chardata/stats/taya.bin",file);
	split(0x1EE6FB, 0x1EE726, "stats_Frayja","chardata/stats/frayja.bin",file);
	split(0x1EE726, 0x1EE737, "stats_Jaro", "chardata/stats/jaro.bin",file);
	split(0x1EE737, 0x1EE748, "stats_Gyan", "chardata/stats/gyan.bin",file);
	split(0x1EE748, 0x1EE771, "stats_Sheela","chardata/stats/sheela.bin",file);
	split(0x1EE771, 0x1EE782, "stats_Zynk", "chardata/stats/zynk.bin",file);
	split(0x1EE782, 0x1EE7AD, "stats_Chaz", "chardata/stats/chaz.bin",file);
	split(0x1EE7AD, 0x1EE7BE, "stats_Lemon", "chardata/stats/lemon.bin",file);
	split(0x1EE7BE, 0x1EE7D0, "stats_Claude","chardata/stats/claude.bin",file);
	

	split(0x1EE7D0, 0x1EE890, "CharacterStartData","chardata/startdata.bin",file);
	split(0x1EE890, 0x1EE930, "ClassData","chardata/classdata.bin",file);
	split(0x1EE930, 0x1EF102, "JewelsEndScreenLayout","misc/specialscreens/endingjewelslayout.bin",file);
	split(0x1EF102, 0x1EF142, "plt_JewelsEndScreen","misc/specialscreens/endingjewelspalette.bin",file);
	split(0x1EF142, 0x1EF4BA, "JewelsEndScreenTiles","misc/specialscreens/endingjewelstiles.bin",file);
	split(0x1EF4BA, 0x1EF4DA, "plt_SuspendString","misc/specialscreens/suspendstringpalette.bin",file);
	split(0x1EF4DA, 0x1EF5A6, "SuspendStringTiles","misc/specialscreens/suspendstringtiles.bin",file);
	split(0x1EF5E6, 0x1EFE33, "baseTiles","misc/basetiles.bin",file);
	MakeAlign(0x1EFE33, 0x1F0000-0x1EFE33,15);
	split(0x1F0000, 0x1F8000, "","sound/music/bank1.bin",file);
	split(0x1F8000, 0x200000, "","sound/music/bank0.bin",file);


	fclose(file);

}

static split(start, end, nameString, binPath, splitFile){

	MakeData(start,FF_BYTE,end-start,1);
	MakeNameEx(start,nameString,0);
	SetManualInsn   (start, form("incbin \"%s\"",binPath));
	writestr(splitFile,form("#split\t0x%s,0x%s,%s\n",ltoa(start,16),ltoa(end,16),binPath));
	Jump(start);

}