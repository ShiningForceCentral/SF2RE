
/*
 *	Attempt at producing ASM file from IDC script 
 *	instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

	produceEnums();
	produceConst();
	produceMain();

}



static produceEnums(){
	auto i,j,enumQty,id,enumName,enumSize,constant,constId,output,file;
	file = fopen("sf2enums.asm","w");
	Message("\nWriting Enums to sf2enums.asm ...");
	enumQty = GetEnumQty();
	for(i=0;i<enumQty;i++){
		id = GetnEnum(i);
		enumName = GetEnumName(id);
		//Message("\n\n; ---------------------------------------------------------------------------\n");
		writestr(file,"\n\n; ---------------------------------------------------------------------------\n");
		//Message(form("\n; enum %s",enumName));
		writestr(file,form("\n; enum %s",enumName));
		enumSize = GetEnumSize(id);
		constant = GetFirstConst(id,-1);
		while(constant!=-1){
			j=0;
			constId = GetConstEx(id,constant,j,-1);
			while(constId != -1){
				output = form("\n%s: equ $%s",GetConstName(constId),ltoa(constant,16));
				//Message(output);
				writestr(file,output);
				j++;
				constId = GetConstEx(id,constant,j,-1);
			}
			constant = GetNextConst(id,constant,-1);
		}
	}
	
	writeFooter(file);
	
	fclose(file);
	Message("DONE.\n");
}


static produceConst(void) {

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


static produceMain(){

	auto seg,end,ea,itemSize,action,currentLine,previousLine,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	
	action = 1;
	
	file = fopen("sf2.asm","w");
	writeHeader(file);
	
	seg = FirstSeg();
	end = SegEnd(seg);
	ea = seg;
	while(ea<end){
	
		//Jump(ea);
		
		itemSize = ItemSize(ea);
		
		//Message(form("\nSTART %s, END %s, ea %s",ltoa(GetFunctionAttr(ea,FUNCATTR_START),16),ltoa(GetFunctionAttr(ea,FUNCATTR_END),16),ltoa(ea,16)));	

		if(GetFunctionAttr(ea,FUNCATTR_START)==ea){	
			writeFunctionHeader(file,ea);
		}
		else if(GetFchunkAttr(ea,FUNCATTR_START)==ea){	
			writeFChunkHeader(file,ea);
		}		

		writeItem(file,ea);
		
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea);
		}		
		else if(GetFchunkAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFChunkFooter(file,ea);
		}				

		

		//action = AskYN(1,"Continue ?");
		if(action!=1) break;
		
		ea = ea + itemSize;
	
	}

	fclose(file);
	Message("DONE.\n");	


}


static writeHeader(file){
	writestr(file,"\n\nalign macro\n");
	writestr(file,"   cnop 0,\\1\n");
	writestr(file,"   endm\n");
	writestr(file,"   include \"sf2enums.asm\"\n");
	writestr(file,"   include \"sf2const.asm\"\n");
	writestr(file,"\n\n");
}


static writeFooter(file){
	writestr(file,"		END");
}


static writeFunctionHeader(file, ea){

	auto funcCmt;

	writestr(file,"\n; =============== S U B R O U T I N E =======================================\n\n");
	funcCmt = GetFunctionCmt(ea,0);
	if(funcCmt!=""){
		writestr(file,form("; %s\n\n",funcCmt));
	}
	else{
		funcCmt = GetFunctionCmt(ea,1);
		if(funcCmt!=""){
			funcCmt = formatFuncRptCmt(funcCmt);
			writestr(file,form("; %s\n\n",funcCmt));
		}
	}
	
	writeFrame(file,ea);


}

static writeFrame(file,ea){

	auto id, i, firstM, lastM, mName, mSize, mFlag;

	id = GetFrame(ea);
	firstM = GetFirstMember(id);
	lastM = GetLastMember(id);
	i=firstM;
	while(i<=lastM){
		if(i!=-1&&GetMemberName(id,i)!=""&&GetMemberName(id,i)!=" r"&&GetMemberName(id,i)!=" s"){
			mName = GetMemberName(id,i); // Get the name
			mSize = GetMemberSize(id, i); // Get the size (in byte)
			mFlag = GetMemberFlag(id, i); // Get the flag
			Message("\n%a : %s %d %x", ea, mName, mSize, mFlag);
			DelStrucMember(id,i);		
			i = i+mSize;
		}
		else{
			i++;
		}	
	}


}


static writeFunctionFooter(file, ea){

	auto funcName;
	funcName = GetFunctionName(ea);
	writestr(file,form("\n	; End of function %s\n\n",funcName));


}


static writeItem(file,ea){

	auto name,tabLength,indent,disasm,cmtIdx,commentIndent,comment,commentEx,i,line,lineA,lineB,type,output;
	
	tabLength = 2;
	indent = "\t\t\t\t\t\t\t\t\t\t";
	commentIndent = "\t\t\t\t\t\t\t\t\t\t\t\t";

	name = GetTrueName(ea);
	if(name==""){
		name = Name(ea);
	}
	if(name!=""){
		name=form("%s:",name);
		if(GetFunctionAttr(ea,FUNCATTR_START)!=-1){
			name = form("%s\n%s",name,indent);
		}
		else{
			while(strlen(name)<(strlen(indent)*tabLength)){
				name = form("%s ",name);
			}		
		}
	}
	else {
		name = indent;
	}

	
	commentEx = CommentEx(ea,0);
	if(commentEx!=""){
		comment = commentEx;
	}
	else{
		commentEx = CommentEx(ea,1);
		if(commentEx!=""){
			comment = formatRptCmt(commentEx);
		}
	}
	
	disasm = GetDisasm(ea);
	cmtIdx = strstr(disasm,";");
	if(cmtIdx!=-1){
		disasm = substr(disasm,0,cmtIdx);
	}
	
	if(comment!=""){
		comment = form("; %s",comment);
	}
	
	if(strlen(name)>(strlen(indent)*tabLength)){
		//Message(form("indent length %d, name length %d",strlen(indent),strlen(name)));
		name = form("%s\n%s",name,indent);
	}
	
	if(strlen(disasm)>(strlen(commentIndent)*tabLength)&&comment!=""){
		disasm = form("%s\n%s%s",disasm,indent,commentIndent);
	}
	
	/* useless
	i=0;
	line = LineA(ea,i);
	while(line!=""){
		lineA = form("%s\n%s",lineA,line);
		i++;
		line = LineA(ea,i);
	}
	if(lineA!=""){
		lineA = form("%s\n",lineA);
	}
	
	i=0;
	line = LineB(ea,i);
	while(line!=""){
		lineA = form("%s\n%s",lineB,line);
		i++;
		line = LineB(ea,i);		
	}
	if(lineB!=""){
		lineB = form("%s\n",lineB);
	}
	*/
	
	output = form("%s%s%s%s\n%s",lineA,name,disasm,comment,lineB);
	/*type = GuessType(ea);
	if(strstr(type,"char[")!=-1){
			Message("%a %s : %s\n",ea,GuessType(ea),disasm);
	}*/

	writestr(file,output);

}

static writeFChunkHeader(file,ea){

	auto text,functionName;
	
	text = "; START OF FUNCTION CHUNK FOR ";
	functionName = GetFunctionName(ea);
	writestr(file,form("\n%s%s\n\n",text,functionName));

}

static writeFChunkFooter(file,ea){

	auto text,functionName;
	
	text = "; END OF FUNCTION CHUNK FOR ";
	functionName = GetFunctionName(ea);
	writestr(file,form("\n%s%s\n\n",text,functionName));

}


static formatFuncRptCmt(cmt){

	auto index, before, after, result;
	index = strstr(cmt,"\n");

	if(index!=-1){
		before = substr(cmt,0,index+1);
		after = substr(cmt,index+1,strlen(cmt));
		result = form("%s; %s",before,formatFuncRptCmt(after));
		return result;
	}
	else{
		return cmt;
	}

}


static formatRptCmt(cmt){

	auto index, before, after, result;
	index = strstr(cmt,"\n");

	if(index!=-1){
		before = substr(cmt,0,index+1);
		after = substr(cmt,index+1,strlen(cmt));
		result = form("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t; %s",before,formatRptCmt(after));
		return result;
	}
	else{
		return cmt;
	}

}