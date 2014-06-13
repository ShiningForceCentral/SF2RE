#include <idc.idc>

static main(void) {	
	
	auto ea,start,end,name,mapId,flagId,sectionName,desc,filename,file;
	file = 	fopen("producecommands.txt","w");
	
	start = 0x4FA70;
	end = 0x6348C;
	while(ea<end){
		name = Name(ea);
		if(strstr(name,"ms_map")!=-1){
			mapId = substr(name,6,8);
			if(strstr(mapId,"_")!=-1){
				mapId = substr(mapId,0,strstr(mapId,"_"));
			}
			if(strlen(mapId)==1){
				mapId = form("0%s",mapId);
			}
			if(strstr(name,"flag")!=-1){
				flagId = substr(name,strstr(name,"flag")+4,strstr(name,"flag")+7);
				if(strstr(flagId,"_")!=-1){
					flagId = substr(flagId,0,strstr(flagId,"_"));
				}
			}
			else{
				flagId = "";
			}
			if(flagId!=""){
				flagId = form("_%s",flagId);
			}
			if(strstr(name,"Entities")!=-1) sectionName = "s1";
			else if(strstr(name,"EntityEvents")!=-1) sectionName = "s2";
			else if(strstr(name,"Section3")!=-1) sectionName = "s3";
			else if(strstr(name,"Section4")!=-1) sectionName = "s4";
			else if(strstr(name,"Section5")!=-1) sectionName = "s5";
			else if(strstr(name,"InitFunction")!=-1) sectionName = "s6";
			else sectionName = "pt";
			filename = form("%s%s",sectionName,flagId);
			writestr(file,form("\nproduceAsmScript(file,\"mapsetups\\\\map%s\\\\%s\",0x%s,,\"%s\");",mapId,filename,ltoa(ea,16),desc));
		}
		ea = ea + ItemSize(ea);
	}

	fclose(file);
	
}
	