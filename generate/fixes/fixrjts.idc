/*
 * 	IDA's IDC export function does not properly export 
 *	structures called Relative Jump Tables, when they
 *	are after address 0xFFFF.
 *	This script contains the needed instructions to 
 *	fix all the RJTs that are defined in the IDB. 
 *	
 *	Everytime a new RJT is defined after 0xFFFF, 
 *	it also has	to be defined in this script.
 *
 */


#include <idc.idc>

static main(void) {

// RJT at 0x10408
makeRjt(0x10408,0x10410);
// RJT at 0x107F8
makeRjt(0x107F8,0x10800);
// RJT at 0x10CBE
makeRjt(0x10CBE,0x10CC6);
// RJT at 0x14080
makeRjt(0x14080,0x14088);
// RJT of Spell Animations at 0x19F1C
makeRjt(0x19F1C,0x19F5C);
// RJT at 0x1A048
makeRjt(0x1A048,0x1A088);
// RJT at 0x2200C
makeRjt(0x2200C,0x22014);
// RJT at 0x2217E
makeRjt(0x2217E,0x22186);
// RJT at 0x22562
makeRjt(0x22562,0x2256A);
// RJT at 0x22A22
makeRjtWithOneWordBetweenEachEntry(0x22A22,0x22A48);
// RJT at 0x25C5A
makeRjt(0x25C5A,0x25C6C);
// RJT at 0x25D2E
makeRjt(0x25D2E,0x25D40);
// RJT at 0x25D2E
makeRjt(0x4681A,0x4683A);
// RJT for Cutscene Script Commands at 0x47180
makeRjt(0x47180,0x47234);


}


static makeRjt(base, end){
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

static makeRjtWithOneWordBetweenEachEntry(base, end){
	auto addr;
	addr = base;
	while(addr < end){
		MakeData(addr, FF_WORD, 0x2, 0);
		addr = addr+2;
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

