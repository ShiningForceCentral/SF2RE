/*
 * This script was written to unify both RAM and RAMFF segments into a single RAM segment.
 * This way, RAM offsets always point to the same segment with no doubles.
 * 
 * The script changes references to the old RAMFF segment so that they now point to the RAM segment adequately.
 *
 * This script should be executed after a new IDB is formed.
 *
 * How it works:
 * 1) Begin crawling the RAMFF space at (0xFFFF0000) one byte at a time.
 * 2) Iterate through all xrefs to the current addr pointer.
 * 3) Use the OpOffEx command to change the xref line's operand to be in terms of an offset from 0xFFFF0000.
 *
 */

#include <idc.idc>

static ReplaceNegRamOffset(addr, dref, n)
{
	auto opnd, before, after;
	
	opnd = GetOperandValue(dref, n);
	
	if (opnd == addr)
	{
		before = GetOpnd(dref, n);
		OpOffEx(dref, n, REF_OFF32, GetOperandValue(dref, n) - 0xFF000000, 0x0, 0xFF000000);
		add_dref(dref, GetOperandValue(dref, n) - 0xFF000000, fl_F | XREF_USER);
		after = GetOpnd(dref, n);
		
		if (before != after)
			Message("addr 0x%x, dref 0x%x, opnd %d, from %s to %s\n", addr, dref, n, before, after);
	}
	
	return;
}

// helper function for convenience to test xrefs from, not used but do not remove, could be useful
static PrintFirstXrefFrom(addr)
{
	Message("DREF From 0x%x to 0x%x, isRef %d \n", addr, Dfirst(addr), isRef(GetFlags(addr)));
}

static main(void) 
{

	auto addr, dref, next;

	addr = 0xFFFF0000;
	
	Message("\n-------------------------\n");
	Message("Running ram-migration.idc starting at address 0x%x\n", addr);

	for (addr = addr; addr != BADADDR; addr=addr+1)
	{
		
		if(addr < 0xFFFF8000)
			addr = 0xFFFF8000;
		
		for(dref=DfirstB(addr);dref!=-1;dref=DnextB(addr,dref))
		{
			ReplaceNegRamOffset(addr, dref, 0);
			ReplaceNegRamOffset(addr, dref, 1);
		}
	}

	Message("End of execution\n");
	Message("-------------------------\n\n");
	
}

