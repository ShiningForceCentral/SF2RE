/*
 * 	IDA's IDC export function does not properly export 
 *	structures called Relative Jump Tables.
 *	This script contains the needed instructions to 
 *	fix all the RJTs that are defined in the IDB. 
 *	
 *	Everytime a new RJT is defined, it also has
 *	to be defined in this script.
 *
 */


#include <idc.idc>

static main(void) {


// RJT at 0x10408
MakeData(0x10408, FF_WORD, 0x2, 0);
OpOffEx(0x10408, -1, REF_OFF32, -1, 0x10408, 0);
MakeData(0x1040A, FF_WORD, 0x2, 0);
OpOffEx(0x1040A, -1, REF_OFF32, -1, 0x10408, 0);
MakeData(0x1040C, FF_WORD, 0x2, 0);
OpOffEx(0x1040C, -1, REF_OFF32, -1, 0x10408, 0);
MakeData(0x1040E, FF_WORD, 0x2, 0);
OpOffEx(0x1040E, -1, REF_OFF32, -1, 0x10408, 0);




}


