/*
 * 	IDA's IDC export function does not properly export 
 *	structures called Branch Tables, when they
 *	are after address 0xFFFF.
 *	This script contains the needed instructions to 
 *	fix all the BTs that are defined in the IDB. 
 *	
 *	Everytime a new BT is defined after 0xFFFF, 
 *	it also has	to be defined in this script.
 *
 */


#include <idc.idc>

static main(void) {

// BT at 0x183C0
makeBt(0x183C0,0x183EA);
// BT at 0x1B7E8
makeBt(0x1B7E8,0x1B828);


}


static makeBt(base, end){
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



