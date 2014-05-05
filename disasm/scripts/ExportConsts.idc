#include <idc.idc>

//////////////////////////////////////////////////////////////////////////////



// --------------------------------

// Main conversion routine
static ExportConsts(H_File_Name)
{
    auto enum_SID, enum_ID;
    auto const_ID, const_val, const_next;
    auto i, total, subtotal;

	auto hh;

    if ((hh=fopen(H_File_Name,"w")) == 0)
	{
		Warning("Couldn't open file '%s'!",H_File_Name);
		return -1;
	}

    for (enum_SID=0; enum_SID<GetEnumQty(); enum_SID++)
    {
        enum_ID = GetnEnum(enum_SID);
        //Message(GetEnumName(enum_ID)+"\n");
        writestr(hh, form("#enum %s\n\n", GetEnumName(enum_ID)));

        const_val = GetFirstConst(enum_ID, -1);

        subtotal = 0;

        while (const_val != -1)
        {
            for (i=0; i < 255; i++)
            {
                const_next = GetConstEx(enum_ID, const_val, i, -1);
                if (const_next == -1) continue;

                if (const_val >= 0 && const_val < 10)
                    writestr(hh, form("#define %s %s\n", GetConstName(const_next), ltoa(const_val, 10)));
                else
                    writestr(hh, form("#define %s 0x%s\n", GetConstName(const_next), ltoa(const_val, 16)));
                //Message(GetConstName(const_next)+"\n");
                total++;
            }
            const_val = GetNextConst(enum_ID, const_val, -1);
        }

        writestr(hh, "\n// --------\n\n");
    }

    fclose(hh);

	Message("Successful %d elements exported.\n",total);
	return 0;
}

static main()
{
	auto file_name;

	file_name = AskFile(1, "SF2CONSTS.H", "Choose a header(.H) file to export:");
	if (file_name == "") return;
	ExportConsts(file_name);
}