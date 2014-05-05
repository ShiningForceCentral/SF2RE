//////////////////////////////////////////////////////////////////////////////
//      This file create IDA Enums  by parsing C/C++ .H include file
//
// Version: SF2 Special
//
// History of changes:
//
// v1.00  28.09.1998  Started by Leonid Lisovsky  <lly@aha.ru>.
// v1.01  02.12.1998  Bugfix & corrections to get more universality.
// v1.02  04.12.1998  First step to resolve expressions.
// v1.03  04.08.1999  More smart error messages,
//                    second approach to resolve arithmetic expressions.
// v1.04  08.08.1999  Arithmetic evaluator ready to use.
// v1.05  05.10.1999  Corrections due to changes in IDA 3.85,
//                    the right total counter was made. Constants
//                    will not more be cuted off on the first blank.
// v1.06  28.02.2000  Trailing spaces bugfix. C/C++ typecast workaround.
// v1.07  24.03.2000  Correct 'Esc' handling. One wildcard for filtering
//                    defines allowed now (Syntax: 'Prefix*Suffix').
// v1.09  01.03.2002  Bugfix - FindDelim() wasn't returned FIRST delimiter.
//
// v????              Totally morphed into something more modular. Thanks Leonid. -BNC

// TODO: GetAtom() - Smart constant recognizing.
//////////////////////////////////////////////////////////////////////////////

#include <idc.idc>

#define ENUM_TOKEN      "#enum"
#define DEFINE_TOKEN	"#define"
#define XREF_ARRAY	"h2enum_xrefs"
#define EXPR_ARRAY      "h2enum_expr"
#define ENUMID_ARRAY  "h2enum_eid"

//////////////////////////////////////////////////////////////////////////////

#define DO_OVERWRITE 1

//////////////////////////////////////////////////////////////////////////////

static pow(x,y)
{
    auto z;
    z=x;
    while (y>1)
    {
        z=z*x;
        y--;
    }
    return z;
}

// returns -1 if symbol is NOT 'space'
static is_space(c)
{
	return strstr(" \t\r\n\b",c);
}

// strip leading blank characters from string.
static ltrim(str)
{
	auto pos,c,l;

	l = strlen(str);
	pos = 0;
	while (pos < l)
	{
		c = substr(str,pos,pos+1);
		if (is_space(c) == -1) break;
		pos++;
	}
	return substr(str,pos,-1);
}

// strip trailing blank characters from string.
static rtrim(str)
{
	auto pos,c;

	pos = strlen(str);
	while (pos > 0)
	{
		c = substr(str,pos-1,pos);
		if (is_space(c) == -1) break;
		pos--;
	}
	return substr(str,0,pos);
}

static trim(str)
{
	return rtrim( ltrim(str) );
}

// Find first delimiter position in string (SPACE or TAB).
static FindDelim(str)
{
	auto pos1,pos2;

	pos1 = strstr(str," ");
	pos2 = strstr(str,"\t");
	if (pos1 == -1)  return pos2;
	if (pos2 == -1)  return pos1;
	if (pos1 < pos2) return pos1;
	else		 return pos2;
}

// Find C/C++ comment start position in string ( // or /* ).
static FindCcomment(str)
{
	auto pos;

	pos = strstr(str,"//");
	if (pos == -1) return strstr(str,"/*");
	else         return pos;
}

// Test string for pattern (only ONE wildcard allowed)
static pat1mat(str, pattern_R,pattern_L, wild_pos_R,wild_pos_L)
{
	// Starts with pattern
	if ((wild_pos_L > 0) && (substr(str,0,wild_pos_L) != pattern_L))
		return -1;
	// Ends with pattern
	if ((wild_pos_R > 0) && (substr(str,strlen(str)-wild_pos_R,-1) != pattern_R))
		return -1;
	return 0;
}

static DelConstByName(const_name)
{
    auto i, enum_size, enum_ID, const_idx, const_val, const_next;

    const_idx = GetConstByName(const_name);

    if (const_idx == -1)
        return 0;

    const_val = GetConstValue(const_idx);
    enum_ID = GetConstEnum(const_idx);
    enum_size = GetEnumSize(enum_ID);

    for (i=0; i<enum_size; i++)
    {
        const_next = GetConstEx(enum_ID, const_val, i, -1);

        if (const_next == -1) return 0;

        if (GetConstName(const_next) == const_name)
        {
            DelConstEx(enum_ID, const_val, i, -1);
            return 1;
        }
    }
}

// Add Constant with custom error messages
static H_AddConst(enum_ID,enum_elem_name,enum_elem_val,str_no)
{
	auto i, v_idx, const_idx, const_val, const_next, dupe_elem_name;

    const_idx = GetConstByName(enum_elem_name);
    const_val = GetConstValue(const_idx);

    if (DO_OVERWRITE)
        DelConstByName(enum_elem_name);

	v_idx = AddConstEx(enum_ID, enum_elem_name, enum_elem_val, -1);

	if (v_idx == CONST_ERROR_NAME)
	{
		Message("*DUPE* (line:%d) %s %0Xh\n", str_no, enum_elem_name, enum_elem_val);
	}
	else if (v_idx == CONST_ERROR_VALUE)
	{

		//dupe_elem_name = GetConstName(GetC,-1));
		//Message("*DUPE VALUE* (line:%d) %s == %s  %0Xh\n", str_no,enum_elem_name,dupe_elem_name,enum_elem_val);
	}
}

static SwitchEnum(enum_name)
{
    auto enum_ID;

    if ((enum_ID=GetEnum(enum_name)) == -1) // New enum
        if ((enum_ID=AddEnum(GetEnumQty() + 1, enum_name, FF_0NUMH)) == -1)
        {
            Warning("Couldn't create enumeration '%s'!",enum_name);
            return -2;
        }

    return enum_ID;
}

//----------------------------------------------------------------------------
// Arithmetic evaluator functions

#define TOK_NONE	-1
#define TOK_VAR		0
#define TOK_PLUS	1
#define TOK_MINUS	2
#define TOK_OR		3
#define TOK_AND		4
#define TOK_XOR		5
#define TOK_MULT	10
#define TOK_DIV		11
#define TOK_MOD		12
#define TOK_NOT		20
#define TOK_L_PAR	30
#define TOK_R_PAR	31
#define TOK_POW     -2
#define TOK_L_SHIFT -3
#define TOK_R_SHIFT -4

// Parse and evaluate arithmetic expression
static ParseExpr(str)
{
	auto expr_ID;
	auto startpos,pos,v_idx;
	auto c,is_token,token1,value;

	if ((expr_ID=GetArrayId(EXPR_ARRAY)) == -1)
		if ((expr_ID=CreateArray(EXPR_ARRAY)) == -1)
		{
			Warning("Couldn't create array '%s' for evaluating expressions !",EXPR_ARRAY);
			return;
		}

	// Fill array with tokens
	v_idx = 2;
	startpos = 0;
	is_token = 0;
	for(pos=0; pos<strlen(str); pos++)
	{

        c = substr(str,pos,pos+2);
		if ((c=="**") || (c=="<<") || (c==">>"))	// token delimiter checking
		{
			token1 = substr(str,startpos,pos);
			if (token1 != "")
			{	// Store variable or constant
				SetArrayString(expr_ID,v_idx++,token1);
			}
			startpos = pos+2;
			if ((c!=" ") && (c!="\t")) // Store operator
				SetArrayString(expr_ID,v_idx++,c);
			is_token = 0;
            pos++;
            continue;
		}

		c = substr(str,pos,pos+1);
		if ( (is_token==0) && (is_space(c)!=-1) )
		{
			startpos++;
			continue;
		}
		if ((c==" ") || (c=="\t") || (c=="(") || (c==")") ||
			(c=="+") || (c=="-") || (c=="*") || (c=="/") ||
			(c=="|") || (c=="~") || (c=="&") || (c=="^") ||
			(c=="%"))	// token delimiter checking
		{
			token1 = substr(str,startpos,pos);
			if (token1 != "")
			{	// Store variable or constant
				SetArrayString(expr_ID,v_idx++,token1);
			}
			startpos = pos+1;
			if ((c!=" ") && (c!="\t")) // Store operator
				SetArrayString(expr_ID,v_idx++,c);
			is_token = 0;
		}
		else is_token = 1;
	}
	if (is_token == 1)	// Store last token, if present
	{
		token1 = substr(str,startpos,-1);
		if (token1 != "")
		{
			SetArrayString(expr_ID,v_idx++,token1);
		}
	}
	SetArrayLong(expr_ID,0,2);	// Special elements: 0 - current token
	SetArrayLong(expr_ID,1,v_idx);	//                   1 - array size

	// Evaluating value
	if (v_idx > 2)
		value = eval_1(expr_ID,0);
	else
		value = 0;
	DeleteArray(expr_ID);
	return value;
}

// Add, Subtract, OR, AND , XOR
static eval_1(expr_ID, prev_val)
{
	auto value,op;

	value = eval_2(expr_ID, prev_val);
	while ( ((op=tok_type(expr_ID))==TOK_PLUS) || (op==TOK_MINUS) ||
		(op==TOK_OR) || (op==TOK_AND) || (op==TOK_XOR) )
	{
		SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);

		if      (op == TOK_PLUS)  value = value + eval_2(expr_ID, value);
		else if (op == TOK_MINUS) value = value - eval_2(expr_ID, value);
		else if (op == TOK_OR)    value = value | eval_2(expr_ID, value);
		else if (op == TOK_AND)   value = value & eval_2(expr_ID, value);
		else if (op == TOK_XOR)   value = value ^ eval_2(expr_ID, value);
	}
	return value;
}

// Multiply, Divide, Mod
static eval_2(expr_ID, prev_val)
{
	auto value,op;

	value = eval_3(expr_ID, prev_val);
	while ( ((op=tok_type(expr_ID))==TOK_MULT) || (op==TOK_DIV) ||
		(op==TOK_MOD) )
	{
		SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);

		if      (op == TOK_MULT) value = value * eval_3(expr_ID, value);
		else if (op == TOK_DIV)  value = value / eval_3(expr_ID, value);
		else if (op == TOK_MOD)  value = value % eval_3(expr_ID, value);
	}
	return value;
}

// Unary -, NOT
static eval_3(expr_ID, prev_val)
{
	auto value,op;

	op = tok_type(expr_ID);
	if ( (op==TOK_MINUS) || (op==TOK_NOT) )
	{
		SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);

		if      (op==TOK_MINUS) value = - eval_4(expr_ID, 0);
		else if (op==TOK_NOT)   value = ~ eval_4(expr_ID, 0);
	}
	else	value = eval_4(expr_ID, prev_val);
	return value;
}

// Exponents, Shifts
static eval_4(expr_ID, prev_val)
{
	auto value,op;

	value = eval_5(expr_ID, prev_val);
	while ( ((op=tok_type(expr_ID))==TOK_POW) || (op==TOK_L_SHIFT) || (op==TOK_R_SHIFT) )
	{
		SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);

		if      (op == TOK_POW)  value = pow(value, eval_5(expr_ID, value));
        else if (op == TOK_L_SHIFT)  value = value << eval_5(expr_ID, value);
        else if (op == TOK_R_SHIFT)  value = value >> eval_5(expr_ID, value);
	}
	return value;
}

// Parentheses, constants
static eval_5(expr_ID, prev_val)
{
	auto value,op;

	op = tok_type(expr_ID);
	if (op==TOK_L_PAR)
	{
		SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);

		value = eval_1(expr_ID,prev_val);
		if (tok_type(expr_ID) == TOK_R_PAR)
			SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);
		else
			Message("*** Right parenthess missing!\n");
		// Typecast workaround
		op = tok_type(expr_ID);
		if ( (op==TOK_VAR) || (op==TOK_L_PAR) )
			value = eval_5(expr_ID,0);
	}
	else
	{
		if (op!=TOK_NONE)
		{
			value = GetAtom(GetArrayElement(AR_STR,expr_ID,GetArrayElement(AR_LONG,expr_ID,0)));

			SetArrayLong(expr_ID,0,GetArrayElement(AR_LONG,expr_ID,0)+1);
		}
		else value = 0;
	}
	return value;
}

// return token type
static tok_type(expr_ID)
{
	auto ind,tok;

	ind = GetArrayElement(AR_LONG,expr_ID,0);
	if (ind >= GetArrayElement(AR_LONG,expr_ID,1)) return TOK_NONE; // Out of bounds
	tok = GetArrayElement(AR_STR,expr_ID,ind);

	if ( tok == "+" ) return TOK_PLUS;
	if ( tok == "-" ) return TOK_MINUS;
	if ( tok == "|" ) return TOK_OR;
	if ( tok == "&" ) return TOK_AND;
	if ( tok == "^" ) return TOK_XOR;

	if ( tok == "*" ) return TOK_MULT;
	if ( tok == "/" ) return TOK_DIV;
	if ( tok == "%" ) return TOK_MOD;

	if ( tok == "~" ) return TOK_NOT;
	if ( tok == "(" ) return TOK_L_PAR;
	if ( tok == ")" ) return TOK_R_PAR;

    if ( tok == "**" ) return TOK_POW;
    if ( tok == "<<" ) return TOK_L_SHIFT;
    if ( tok == ">>" ) return TOK_R_SHIFT;

	return TOK_VAR;
}

// return value of constant or variable
static GetAtom(token)
{
	auto val;
	val = atol(token);		// try Decimal convert
	if (val == 0)
		val = xtol(token);	// try HEX convert
	if (val == 0)
		val = GetConstValue(GetConstByName(token));
	return val;
}

//////////////////////////////////////////////////////////////////////////////

// Main conversion routine
static ImportConsts(H_File_Name)
{
    auto enum_ID,xref_ID,eid_ID,v_idx,total;
    auto enum_name,enum_pattern;
    auto enum_elem_name,enum_elem_val;
	auto enum_Tok_Pat_R,enum_Tok_Pat_L,enum_Tok_R,enum_Tok_L;
	auto hh,in_str,pos,wrk_str,str_no,c;

    if ((hh=fopen(H_File_Name,"r")) == 0)
	{
		Warning("Couldn't open file '%s'!",H_File_Name);
		return -1;
	}

    if ((pos=strstr(enum_pattern,'*')) != -1)
	{	// Contain (or superseed) specified token
		enum_Tok_R = strlen(enum_pattern) - pos - 1;
		enum_Tok_L = pos;
		enum_Tok_Pat_R = substr(enum_pattern,pos+1,-1);
                enum_Tok_Pat_L = substr(enum_pattern,0,pos);
	}
	else	// Starts with specified token by default
	{
		enum_Tok_R = 0;
		enum_Tok_L = strlen(enum_pattern);
		enum_Tok_Pat_R = "";
		enum_Tok_Pat_L = enum_pattern;
	}

	if ((xref_ID=GetArrayId(XREF_ARRAY)) == -1)
		if ((xref_ID=CreateArray(XREF_ARRAY)) == -1)
		{
			Warning("Couldn't create array '%s' for xrefs !",XREF_ARRAY);
			return -3;
		}

	if ((eid_ID=GetArrayId(ENUMID_ARRAY)) == -1)
		if ((eid_ID=CreateArray(ENUMID_ARRAY)) == -1)
		{
			Warning("Couldn't create array '%s' for storing enum IDs !",ENUMID_ARRAY);
			return -4;
		}

	Message("Conversion started...\n");
	total = GetEnumSize(enum_ID);

//Pass 1 - import definitions

	str_no = 0;

	while ((in_str=readstr(hh)) != -1)
	{
		str_no++;

        pos = -1;

        if ((pos = strstr(in_str, ENUM_TOKEN)) != -1)
        {
            in_str = ltrim(substr(in_str,pos+strlen(ENUM_TOKEN),-1));

            enum_name = rtrim(in_str);

            enum_ID = SwitchEnum(enum_name);

            Message("Switching to enum '%s'.\n", enum_name);
        }
		else if ((pos = strstr(in_str, DEFINE_TOKEN)) != -1)
        {
            in_str = ltrim(substr(in_str,pos+strlen(DEFINE_TOKEN),-1));

            if ((pos=FindDelim(in_str))==-1) continue; // only 2 tokens i.e. "#define SOME"

            enum_elem_name = rtrim(substr(in_str,0,pos));

            if (pat1mat(enum_elem_name, enum_Tok_Pat_R, enum_Tok_Pat_L, enum_Tok_R, enum_Tok_L) == 0)
            {
                in_str = ltrim(substr(in_str,pos,-1));
                pos = FindCcomment(in_str);
                wrk_str = rtrim(substr(in_str,0,pos));
                enum_elem_val = GetAtom(wrk_str);
                //Message("%s - %d\n", enum_elem_name, enum_elem_val);
                if (enum_elem_val == 0)
                { // Possible regular expression - resolving later

                    if (SetHashString(eid_ID, enum_elem_name, enum_name)==0)
                        Message("*** Cannot Add enumID %s = %d\n",enum_elem_name,enum_ID);
                    if (SetHashString(xref_ID,enum_elem_name,wrk_str)==0)
                        Message("*** Cannot Add xref %s = '%s'\n",enum_elem_name,wrk_str);
                    continue;
                }

                H_AddConst(enum_ID,enum_elem_name,enum_elem_val,str_no);
            }
        }
	}

	fclose(hh);

// Pass 2 - resolving regular expressions
//
	for (enum_elem_name=GetFirstHashKey(xref_ID); enum_elem_name!=""; enum_elem_name=GetNextHashKey(xref_ID,enum_elem_name))
	{
		wrk_str = GetHashString(xref_ID,enum_elem_name);
        enum_name = GetHashString(eid_ID, enum_elem_name);
        enum_ID = SwitchEnum(enum_name);
 		enum_elem_val = ParseExpr(wrk_str);
       		H_AddConst(enum_ID,enum_elem_name,enum_elem_val,-1);
	}
        DeleteArray(xref_ID);

	total = GetEnumSize(enum_ID) - total;
	Message("Successful %d elements imported.\n",total);
	return 0;
}

static main()
{
	auto i, file_name, num_enums;

	file_name = AskFile(0, "SF2CONSTS.H", "Choose a header(.H) file to parse:");
	if (file_name == "") return;

    num_enums = GetEnumQty();
    if (AskYN(0, "Delete all existing constants? (BE CAREFUL)") == 1)
        for (i=0; i<num_enums; i++)
            DelEnum(GetnEnum(0));

	ImportConsts(file_name);
}
