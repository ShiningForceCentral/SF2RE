/*
 * 	IDA's IDC export function does not properly export 
 *	structures called Relative Pointer Tables, when they
 *	are after address 0xFFFF.
 *	This script contains the needed instructions to 
 *	fix all the RPTs that are defined in the IDB. 
 *	
 *	Everytime a new RPT is defined after 0xFFFF, 
 *	it also has	to be defined in this script.
 *
 */


#include <idc.idc>

static main(void) {

// RPT at 0x47A88
makeRpt(0x47A88,0x47AE8);
// RPT at 0x47B2C
makeRpt(0x47B2C,0x47B8C);
// RPT at 0x47BE8
makeRpt(0x47BE8,0x47C48);


}


static makeRpt(base, end){
	auto addr;
	addr = base;
	while(addr < end){
		MakeData(addr, FF_WORD, 0x2, 0);
		if(Word(addr) > 0x8000) {
			OpOffEx(addr, -1, REF_OFF32, base + Word(addr) - 0x10000, base, 0x10000);
		}
		else{
			OpOffEx(addr, -1, REF_OFF32, -1, base, 0);
		}
		addr = addr+2;
	}
}



