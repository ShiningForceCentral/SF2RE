
/*
 *	Attempt at producing ASM file from IDC script 
 *	instead of IDA's function, for more flexibility.
 */

#include <idc.idc>

static main(void) {

	auto seg,end,ea,itemSize,action,currentLine,previousLine,file;
	auto output, name, indent, comment, commentEx, commentIndent;
	
	action = 1;

	produceEnums();

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
		
		writeItem(file,ea);
		
		if(GetFunctionAttr(ea,FUNCATTR_END)==(ea+itemSize)){
			writeFunctionFooter(file,ea);
		}		

		

		//action = AskYN(1,"Continue ?");
		if(action!=1) break;
		
		ea = ea + itemSize;
	
	}

	fclose(file);
	Message("DONE.\n");

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

	/*
	GetFunctionAttr(ea,);
	 FUNCATTR_START   -- function start address
	 FUNCATTR_END     -- function end address
	 FUNCATTR_FLAGS   -- function flags
	 FUNCATTR_FRAME   -- function frame id
	 FUNCATTR_FRSIZE  -- size of local variables
	 FUNCATTR_FRREGS  -- size of saved registers area
	 FUNCATTR_ARGSIZE -- number of bytes purged from the stack
	 FUNCATTR_FPD     -- frame pointer delta
	 FUNCATTR_COLOR   -- function color code
	*/
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

	auto name,indent,commentIndent,comment,commentEx,output;
	
	indent = "                    ";
	commentIndent = "                    ";

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
			while(strlen(name)<strlen(indent)){
				name = form("%s ",name);
			}		
		}
	}
	else {
		name = indent;
	}
	
	
	commentEx = CommentEx(ea,1);
	while(strstr(comment,"\n")!=-1){
		//TODO manage repeatable comments
		
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
	
	output = form("%s%s%s\n",name,GetDisasm(ea),comment);
	//Message(output);
	writestr(file,output);

}

static writeFChunkHeader(file,ea){



}

static writeFChunkFooter(file,ea){


}


static formatFuncRptCmt(cmt){

	auto index, before, after, result;
	index = strstr(cmt,"\n");

	if(index!=-1){
		before = substr(cmt,0,index+1);
		after = substr(cmt,index+1,strlen(cmt)-1);
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
		after = substr(cmt,index+1,strlen(cmt)-1);
		result = form("%s                                            ; %s",before,formatRptCmt(after));
		return result;
	}
	else{
		return cmt;
	}

}