
/*
 *	Attempt at producing ASM file from IDC script 
 *	instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

	auto seg,end,ea,segName,name,file;
	
	Message("\nWriting offset constants to sf2const.asm ...");
	file = fopen("sf2const.asm","w");
	writestr(file,"; SF2CONST.ASM INCLUDED AT START OF SF2.ASM\n\n");
	seg = FirstSeg();
	seg = NextSeg(seg);
	while(seg != BADADDR){
		end = SegEnd(seg);
		segName = SegName(seg);
		writestr(file,form("; START OF SEGMENT %s OFFSETS FROM %a TO %a\n",segName, seg, end));
		ea = seg;
		while(ea<end){
			name = GetTrueName(ea);
			if(name!=""){
				writestr(file,form("%s: equ $%s\n",name,ltoa(ea,16)));
			}
			ea = ea + ItemSize(ea);
		}
		writestr(file,form("; END OF SEGMENT %s OFFSETS FROM %a TO %a\n\n",segName, seg, end));
		seg = NextSeg(seg);
	}
	fclose(file);
	Message("DONE.\n");

}

